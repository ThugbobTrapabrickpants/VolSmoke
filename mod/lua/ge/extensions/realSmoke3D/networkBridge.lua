-- ============================================================================
-- PROJECT: VolSmoke for BeamNG.drive.
-- COPYRIGHT (C) 2026 REALSMOKE 3D CONTRIBUTORS.
-- LICENSE: MIT (see LICENSE). Original project: https://github.com/ThugbobTrapabrickpants/VolSmoke
-- ============================================================================
-- VolSmoke Network Bridge Submodule.
-- Owns UDP telemetry transmission to C++ add-on (port 29293) and per-frame dynamic rolling auth.

local M = {}

local b = bit or bit32 or (type(require) == "function" and pcall(require, "bit") and require("bit"))

local telemetryProtocolVersion = 4

local udp = nil
local lastVehicleSend = nil
local lastVehicleSendError = nil
local lastEnvironmentSend = nil
local lastEnvironmentSendError = nil

local function boundedNumber(value, fallback, magnitudeLimit)
  local number = tonumber(value)
  if not number or number ~= number or math.abs(number) >= math.huge or
     math.abs(number) > magnitudeLimit then
    return fallback
  end
  return number
end

local function initUDP()
  if udp then return true end
  local ok, socketModule = pcall(require, "socket")
  if not ok or not socketModule or not socketModule.udp then
    ok, socketModule = pcall(require, "socket.socket")
  end
  if not ok or not socketModule or not socketModule.udp then return false end

  local socket = socketModule.udp()
  if not socket then return false end
  if not socket:setpeername("127.0.0.1", 29293) then
    pcall(function() socket:close() end)
    return false
  end
  socket:settimeout(0)
  udp = socket
  return true
end

local function parseColor(c)
  if type(c) == "table" or type(c) == "userdata" then
    local r = tonumber(c.r or c.x)
    local g = tonumber(c.g or c.y)
    local b = tonumber(c.b or c.z)
    if r and g and b and (r + g + b) > 0.001 then return vec3(r, g, b) end
  elseif type(c) == "string" then
    local parts = {}
    for num in c:gmatch("%S+") do table.insert(parts, tonumber(num)) end
    if #parts >= 3 and parts[1] and parts[2] and parts[3] then
      return vec3(parts[1], parts[2], parts[3])
    end
  end
  return nil
end

local function parseScale(s)
  local num = tonumber(s)
  if num and num > 0.001 then
    return vec3(num, num, num)
  end
  return parseColor(s)
end

local function applyScaleWithChromaGuard(baseCol, scaleVal)
  if not scaleVal then return baseCol end
  local s = parseScale(scaleVal)
  if not s then return baseCol end
  -- Scale overall illumination intensity by photometric luminance
  local lum = 0.2126 * s.x + 0.7152 * s.y + 0.0722 * s.z
  if lum <= 0.001 then return baseCol end
  -- Guard against extreme blue depletion (e.g. desert maps cutting blue by 90%+).
  -- Tire smoke is an optical white scatterer (Mie aerosol); its illuminant must retain
  -- reasonable chromatic balance so smoke does not turn into an unnatural yellow cloud.
  local maxRG = math.max(s.x, s.y)
  local safeBlue = math.max(s.z, maxRG * 0.75)
  local safeS = vec3(s.x, s.y, safeBlue)
  -- Blend 80% luminance-neutral intensity + 20% safe environmental tint
  local neutral = vec3(lum, lum, lum)
  local tunedS = neutral * 0.80 + safeS * 0.20
  return vec3(baseCol.x * tunedS.x, baseCol.y * tunedS.y, baseCol.z * tunedS.z)
end

local function getSunAndEnvironment()
  local sunDir = vec3(0.4, 0.3, 0.86)
  local sunCol = vec3(1.0, 0.95, 0.85)
  local ambCol = vec3(0.35, 0.38, 0.45)

  local sunsky = (scenetree and (
    scenetree.findObject("sunsky") or 
    scenetree.findObjectByClass("ScatterSky") or 
    scenetree.findObjectByClass("Sun") or
    scenetree.findObject("Sun") or
    scenetree.findObject("sun")
  )) or nil
  if sunsky then
    local rawAz = tonumber(sunsky.azimuth) or 0
    local rawEl = tonumber(sunsky.elevation) or 45
    -- Torque3D elevation can be 0..360 or -90..90. Normalize into [-180, 180]
    -- so night maps with custom skyboxes (e.g. elevation 270°) are recognized as night.
    local elDeg = ((rawEl + 180) % 360) - 180
    local az = math.rad(rawAz)
    local el = math.rad(elDeg)
    local cosEl = math.cos(el)
    local sinEl = math.sin(el)
    local sx = math.sin(az) * cosEl
    local sy = math.cos(az) * cosEl
    local sz = sinEl
    local dir = vec3(sx, sy, sz)
    if dir:length() > 0.01 then
      sunDir = dir:normalized()
    end

    if elDeg > 15.0 then
      local dayFactor = math.min(1.0, (elDeg - 15.0) / 30.0)
      sunCol = vec3(1.0, 0.96, 0.90) * (0.85 + 0.35 * dayFactor)
      ambCol = vec3(0.36, 0.38, 0.42) * (0.80 + 0.30 * dayFactor)
    elseif elDeg > 0.0 then
      local sunsetFactor = elDeg / 15.0
      sunCol = vec3(1.0, 0.60 + 0.36 * sunsetFactor, 0.30 + 0.60 * sunsetFactor) * (0.45 + 0.40 * sunsetFactor)
      ambCol = vec3(0.32, 0.34, 0.48) * (0.50 + 0.30 * sunsetFactor)
    else
      sunDir = vec3(-sx, -sy, math.max(0.2, -sinEl)):normalized()
      sunCol = vec3(0.12, 0.15, 0.24) * 0.40
      ambCol = vec3(0.06, 0.08, 0.12)
    end

    -- Dynamically query explicit ScatterSky / Sun ambient, color, sunScale, and ambientScale if exposed
    pcall(function()
      if sunsky.ambientColor or sunsky.ambient then
        local c = parseColor(sunsky.ambientColor or sunsky.ambient)
        if c then ambCol = c end
      end
      if sunsky.color or sunsky.sunColor then
        local c = parseColor(sunsky.color or sunsky.sunColor)
        if c then sunCol = c end
      end

      -- Apply sunScale and ambientScale modifiers with chromaticity protection
      if sunsky.sunScale then
        sunCol = applyScaleWithChromaGuard(sunCol, sunsky.sunScale)
      end
      if sunsky.ambientScale then
        ambCol = applyScaleWithChromaGuard(ambCol, sunsky.ambientScale)
      end
    end)
  end

  return sunDir, sunCol, ambCol
end

local function sendEnvironmentTelemetry(dtReal, dtSim, params, renderFrameId, replayResetSequence, replayWarmupActive, activeVehicleId)
  if not activeVehicleId or activeVehicleId < 0 then return end

  local realDelta = tonumber(dtReal)
  local simulationDelta = replayWarmupActive and 0.05 or tonumber(dtSim)
  if not realDelta or realDelta ~= realDelta or realDelta < 0 or realDelta > 10 then return end
  if not simulationDelta or simulationDelta ~= simulationDelta or simulationDelta < 0 or simulationDelta > 0.25 then return end

  local camPos = vec3(0, 0, 0)
  local camFwd = vec3(0, 1, 0)
  local camUp = vec3(0, 0, 1)
  local camFov = math.rad(60)
  local camNear = 0.1
  local camFar = 3000.0
  if core_camera then
    pcall(function()
      if core_camera.getPositionXYZ then
        local x, y, z = core_camera.getPositionXYZ()
        if x and y and z then camPos = vec3(x, y, z) end
      elseif core_camera.getPosition then
        camPos = core_camera.getPosition() or camPos
      end
    end)
    pcall(function()
      if core_camera.getForwardXYZ then
        local x, y, z = core_camera.getForwardXYZ()
        if x and y and z then camFwd = vec3(x, y, z) end
      elseif core_camera.getForward then
        camFwd = core_camera.getForward() or camFwd
      end
    end)
    pcall(function()
      if core_camera.getUp then camUp = core_camera.getUp() or camUp end
      if core_camera.getFovRad then camFov = core_camera.getFovRad() or camFov end
      if core_camera.getNearClip then camNear = core_camera.getNearClip() or 0.1 end
      if core_camera.getFarClip then camFar = core_camera.getFarClip() or 3000.0 end
    end)
  end

  local sunDir, sunCol, ambCol = getSunAndEnvironment()
  local p = params or {}
  local activeProf = (p.activeSimSurface == "sand" or (not p.activeSimSurface and p.activeSurfaceProfile == "sand")) and "sand" or "asphalt"
  local sp = (type(p.surfaceProfiles) == "table" and type(p.surfaceProfiles[activeProf]) == "table") and p.surfaceProfiles[activeProf] or p

  if not udp and not initUDP() then return end
  lastEnvironmentSend, lastEnvironmentSendError = udp:send(jsonEncode({
    type = "env",
    protocolVersion = telemetryProtocolVersion,
    renderFrameId = renderFrameId,
    resetSequence = replayResetSequence,
    replayWarmup = replayWarmupActive and 1 or 0,
    dtSim = simulationDelta,
    dtReal = realDelta,
    camPos = {camPos.x, camPos.y, camPos.z},
    camFwd = {camFwd.x, camFwd.y, camFwd.z},
    camUp = {camUp.x, camUp.y, camUp.z},
    fov = camFov,
    nearClip = camNear,
    farClip = camFar,
    sunDir = {sunDir.x, sunDir.y, sunDir.z},
    sunCol = {sunCol.x, sunCol.y, sunCol.z},
    ambCol = {ambCol.x, ambCol.y, ambCol.z},
    voxelSize = p.voxelSize or 0.064,
    domainSize = p.domainSize or 13.5,
    quality = p.simulationQuality or 2.0,
    underbodyEject = sp.underbodyEject or p.underbodyEject or 0.20,
    archEject = sp.archEject or p.archEject or 0.15,
    vorticityStrength = sp.vorticityStrength or sp.turbStrength1 or p.vorticityStrength or 0.40,
    roadDamping = sp.roadDamping or p.roadDamping or 0.55,
    smokeDrag = sp.smokeDrag or p.smokeDrag or 0.15,
    wakeSuction = p.wakeSuction or 0.00,
    slipstream = p.slipstream or 0.75,
    slipstreamSpeedLimit = p.slipstreamSpeedLimit or 50.0,
    slipstreamHoldTime = p.slipstreamHoldTime or 200.0,
    slipstreamTurbScale = p.slipstreamTurbScale or 0.30,
    slipstreamTurbStrength = p.slipstreamTurbStrength or 0.50,
    slipstreamBezierX1 = (p.slipstreamBezier and p.slipstreamBezier[1]) or p.slipstreamBezierX1 or 1.00,
    slipstreamBezierY1 = (p.slipstreamBezier and p.slipstreamBezier[2]) or p.slipstreamBezierY1 or 1.00,
    slipstreamBezierX2 = (p.slipstreamBezier and p.slipstreamBezier[3]) or p.slipstreamBezierX2 or 1.00,
    slipstreamBezierY2 = (p.slipstreamBezier and p.slipstreamBezier[4]) or p.slipstreamBezierY2 or 0.00,
    coreLifetime = sp.coreLifetime or p.coreLifetime or 0.25,
    thermalBuoyancy = sp.thermalBuoyancy or p.thermalBuoyancy or 0.10,
    treadSaturation = sp.treadSaturation or p.treadSaturation or 1.00,
    treadCoupling = sp.treadCoupling or p.treadCoupling or 0.50,
    edgeDispersion = sp.edgeDispersion or p.edgeDispersion or 0.50,
    dispersionRate = sp.dispersionRate or p.dispersionRate or 0.40,
    treadTurbulence = sp.treadTurbulence or sp.turbStrength2 or p.treadTurbulence or 2.00,
    turbScale1 = sp.turbScale1 or p.turbScale1 or 1.05,
    turbStrength1 = sp.turbStrength1 or p.turbStrength1 or 1.30,
    turbScale2 = sp.turbScale2 or p.turbScale2 or 0.75,
    turbStrength2 = sp.turbStrength2 or p.turbStrength2 or 1.00,
    turbTransition = sp.turbTransition or p.turbTransition or 1.20,
    turbRelax = sp.turbRelax or p.turbRelax or 2.00,
    turbArch = sp.turbArch or p.turbArch or 2.00,
    turbArchScale = sp.turbArchScale or p.turbArchScale or 0.25,
    microFiber = sp.microFiber or p.microFiber or 1.00,
    fiberScale = sp.fiberScale or p.fiberScale or 1.00,
    hazeNormals = sp.hazeNormals or p.hazeNormals or 1.00,
    creviceShadow = sp.creviceShadow or p.creviceShadow or 0.10,
    coreOpacity = sp.coreOpacity or p.coreOpacity or 1.00,
    vorticityDetail = sp.vorticityDetail or p.vorticityDetail or 1.00,
    smokeColor = p.smokeColor or { 1.0, 1.0, 1.0 },
    dustColor = p.dustColor or { 0.76, 0.65, 0.50 },
    debugWakeMode = p.debugWakeMode or 0
  }))
end

local function sendVehicleTelemetry(activeVehicleId, outbound, outboundWheels, velocityValid)
  if not activeVehicleId or activeVehicleId < 0 then return end
  if not udp and not initUDP() then return end

  lastVehicleSend, lastVehicleSendError = udp:send(jsonEncode({
    type = "vehicle",
    protocolVersion = telemetryProtocolVersion,
    vehicleId = activeVehicleId,
    pos = {outbound.pos.x, outbound.pos.y, outbound.pos.z},
    vel = {outbound.vel.x, outbound.vel.y, outbound.vel.z},
    velocityValid = velocityValid,
    bodyValid = outbound.bodyValid,
    bodyCenter = {outbound.bodyCenter.x, outbound.bodyCenter.y, outbound.bodyCenter.z},
    bodyRight = {outbound.bodyRight.x, outbound.bodyRight.y, outbound.bodyRight.z},
    bodyForward = {outbound.bodyForward.x, outbound.bodyForward.y, outbound.bodyForward.z},
    bodyUp = {outbound.bodyUp.x, outbound.bodyUp.y, outbound.bodyUp.z},
    bodyHalf = {outbound.bodyHalf.x, outbound.bodyHalf.y, outbound.bodyHalf.z},
    profile = outbound.profile or { 0.50, 0.30, 0.50, 0.80 },
    angVel = {
      boundedNumber(outbound.angVel.x, 0, 1.0e5),
      boundedNumber(outbound.angVel.y, 0, 1.0e5),
      boundedNumber(outbound.angVel.z, 0, 1.0e5)
    },
    wheels = outboundWheels
  }))
end

local function poisonAndClose()
  if not udp and not initUDP() then return end
  pcall(function()
    udp:send(jsonEncode({
      type = "env",
      protocolVersion = telemetryProtocolVersion,
      renderFrameId = 0,
      resetSequence = 0,
      dtSim = 0.0,
      dtReal = 0.0
    }))
  end)
end

local function close()
  if udp then
    pcall(function() udp:close() end)
    udp = nil
  end
end

M.telemetryProtocolVersion = telemetryProtocolVersion
M.initUDP = initUDP
M.sendEnvironmentTelemetry = sendEnvironmentTelemetry
M.sendVehicleTelemetry = sendVehicleTelemetry
M.poisonAndClose = poisonAndClose
M.close = close

M.isUdpReady = function() return udp ~= nil end
M.getLastVehicleSend = function() return lastVehicleSend end
M.getLastVehicleSendError = function() return lastVehicleSendError end
M.getLastEnvironmentSend = function() return lastEnvironmentSend end
M.getLastEnvironmentSendError = function() return lastEnvironmentSendError end

return M
