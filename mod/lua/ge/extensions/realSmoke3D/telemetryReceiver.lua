-- ============================================================================
-- PROJECT: VolSmoke for BeamNG.drive.
-- COPYRIGHT (C) 2026 REALSMOKE 3D CONTRIBUTORS.
-- LICENSE: MIT (see LICENSE). Original project: https://github.com/ThugbobTrapabrickpants/VolSmoke
-- ============================================================================
-- VolSmoke Telemetry Receiver Submodule.
-- Owns VLua wheel friction telemetry reception, cadence control, and contact patch geometry synthesis.

local M = {}

local b = bit or bit32 or (type(require) == "function" and pcall(require, "bit") and require("bit"))

local wheelTelemetry = nil
local wheelTelemetryAge = math.huge
local vehicleLoadTimer = math.huge
local frameSynchronousWheelTelemetry = false
local lastWheelProtocolVersion = 0
local lastVehicleProvenanceBuildId = nil
local geometryValidCount = 0
local normalValidCount = 0
local contactSourceCount = 0
local lastTelemetrySnapshot = nil
local velocityRejectCount = 0
local lastVehicleVelocityValid = true
local bodyColliderValid = false
local lastBodyHalfExtents = nil
local lastForwardVec = nil
local lastUpVec = nil
local lastVehiclePos = nil
local calculatedAngVel = vec3(0, 0, 0)
local lastParticleGuardActive = false
local lastVehicleProfile = { 0.50, 0.30, 0.50, 0.80 }

-- BeamNG can report a one-frame spawn/teleport velocity before the vehicle is
-- fully settled. Never feed that discontinuity into smoke advection.
-- Smoothly bounds velocities to physical highway/drag limits (<= 75 m/s, ~270 km/h)
-- to prevent collision impulse shockwaves from blowing up the fluid lattice.
local function sanitizeVelocity(value, maxSpeed)
  local x = value and tonumber(value.x) or 0
  local y = value and tonumber(value.y) or 0
  local z = value and tonumber(value.z) or 0
  local finite = x == x and y == y and z == z and
                 math.abs(x) < math.huge and math.abs(y) < math.huge and math.abs(z) < math.huge
  if not finite then
    return vec3(0, 0, 0), false
  end
  local lenSq = x * x + y * y + z * z
  local limit = maxSpeed or 75.0
  if lenSq > limit * limit then
    local len = math.sqrt(lenSq)
    if len > 1.0e-5 then
      local scale = limit / len
      return vec3(x * scale, y * scale, z * scale), true
    end
    return vec3(0, 0, 0), false
  end
  return vec3(x, y, z), true
end

local function sanitizeAngularVelocity(value, maxRadPerSec)
  local x = value and tonumber(value.x) or 0
  local y = value and tonumber(value.y) or 0
  local z = value and tonumber(value.z) or 0
  local finite = x == x and y == y and z == z and
                 math.abs(x) < math.huge and math.abs(y) < math.huge and math.abs(z) < math.huge
  if not finite then
    return vec3(0, 0, 0), false
  end
  local lenSq = x * x + y * y + z * z
  local maxMag = maxRadPerSec or 35.0
  if lenSq > maxMag * maxMag then
    local len = math.sqrt(lenSq)
    if len > 1.0e-5 then
      local scale = maxMag / len
      return vec3(x * scale, y * scale, z * scale), true
    end
    return vec3(0, 0, 0), false
  end
  return vec3(x, y, z), true
end

local function clamp01(value)
  return math.max(0, math.min(1, tonumber(value) or 0))
end

local function boundedNumber(value, fallback, magnitudeLimit)
  local number = tonumber(value)
  if not number or number ~= number or math.abs(number) >= math.huge or
     math.abs(number) > magnitudeLimit then
    return fallback
  end
  return number
end

-- The native parser consumes only simulation fields. Sending UI diagnostics
-- with every wheel made otherwise valid packets depend on unrelated values and
-- caused intermittent rejection of the entire emission snapshot.
local function makeNativeWheelPayload(wheel)
  local x = boundedNumber(wheel.x, 0, 1.0e7)
  local y = boundedNumber(wheel.y, 0, 1.0e7)
  local z = boundedNumber(wheel.z, 0, 1.0e7)
  local forward = wheel.forward or {0, 1, 0}
  local hub = wheel.hub or {x, y, z}
  local hubVel = wheel.hubVel or {0, 0, 0}

  return {
    x = x,
    y = y,
    z = z,
    emit = clamp01(wheel.emit),
    emitSmoke = clamp01(wheel.emitSmoke or 0),
    emitDust = clamp01(wheel.emitDust or 0),
    dustTint = boundedNumber(wheel.dustTint or 0, 0, 10),
    omega = boundedNumber(wheel.omega, 0, 1.0e5),
    rollingOmega = boundedNumber(wheel.rollingOmega, 0, 1.0e5),
    wheelDir = boundedNumber(wheel.wheelDir, 1, 2),
    radius = math.max(0.05, math.min(5.0, boundedNumber(wheel.radius, 0.35, 5))),
    forward = {
      boundedNumber(forward[1], 0, 2),
      boundedNumber(forward[2], 1, 2),
      boundedNumber(forward[3], 0, 2)
    },
    hub = {
      boundedNumber(hub[1], x, 1.0e7),
      boundedNumber(hub[2], y, 1.0e7),
      boundedNumber(hub[3], z, 1.0e7)
    },
    hubVel = {
      boundedNumber(hubVel[1], 0, 1.0e5),
      boundedNumber(hubVel[2], 0, 1.0e5),
      boundedNumber(hubVel[3], 0, 1.0e5)
    }
  }
end

local function getVehicleId(vehicle)
  if not vehicle then return -1 end
  if type(vehicle.getId) == "function" then return vehicle:getId() end
  if type(vehicle.getID) == "function" then return vehicle:getID() end
  return -1
end

local function syncBurnoutEquityToVehicle(params)
  local vehicle = (type(getPlayerVehicle) == "function" and getPlayerVehicle(0)) or
                  (be and be:getPlayerVehicle(0))
  if not vehicle then return end
  local p = params or {}
  local userHeatThreshold = p.heatThreshold or 70.0
  local userFrictionSens = p.frictionSens or 0.35
  local userFrictionTime = p.frictionTime or 2.00
  local userSmokeOnset = p.smokeOnset or 2.00
  local userSmokeDecay = p.smokeDecay or 1.50
  local bzDecay = p.smokeDecayBezier or { userSmokeDecay, 1.00, 0.25, 0.95, 0.65, 0.15 }
  local decayDur = tonumber(bzDecay[1] or bzDecay.duration) or userSmokeDecay
  local decayY0  = (#bzDecay >= 6 and tonumber(bzDecay[2])) or tonumber(bzDecay.y0) or 1.00
  local decayX1  = (#bzDecay >= 6 and tonumber(bzDecay[3])) or tonumber(bzDecay[2] or bzDecay.x1) or 0.25
  local decayY1  = (#bzDecay >= 6 and tonumber(bzDecay[4])) or tonumber(bzDecay[3] or bzDecay.y1) or 0.95
  local decayX2  = (#bzDecay >= 6 and tonumber(bzDecay[5])) or tonumber(bzDecay[4] or bzDecay.x2) or 0.65
  local decayY2  = (#bzDecay >= 6 and tonumber(bzDecay[6])) or tonumber(bzDecay[5] or bzDecay.y2) or 0.15
  local bz = p.smokeOnsetBezier or { 70.0, 0.0, 0.25, 0.05, 0.55, 0.95, 220.0, 1.00 }
  local bzOnset = (#bz >= 6) and (bz[1] or 70.0) or userHeatThreshold
  local bzHaze  = (#bz >= 6) and (bz[2] or 0.0) or 0.0
  local bzX1    = (#bz >= 6) and (bz[3] or 0.25) or (bz[1] or 0.25)
  local bzY1    = (#bz >= 6) and (bz[4] or 0.05) or (bz[2] or 0.05)
  local bzX2    = (#bz >= 6) and (bz[5] or 0.55) or (bz[3] or 0.55)
  local bzY2    = (#bz >= 6) and (bz[6] or 0.95) or (bz[4] or 0.95)
  local bzX3    = (#bz >= 8) and (bz[7] or 220.0) or 220.0
  local bzY3    = (#bz >= 8) and (bz[8] or 1.00) or 1.00
  local userSandDustScale = p.sandDustScale ~= nil and p.sandDustScale or 1.00
  local userSandDustSens = p.sandDustSens ~= nil and p.sandDustSens or 1.00
  local userSandDustActive = (p.sandDustEnabled ~= false) and "true" or "false"
  local userAsphaltSmokeActive = (p.asphaltSmokeEnabled ~= false) and "true" or "false"
  pcall(function()
    vehicle:queueLuaCommand(
      "if (realSmoke3DVE or extensions.realSmoke3DVE) then " ..
      "local ve = (realSmoke3DVE or extensions.realSmoke3DVE); " ..
      "ve.setBurnoutEquity(" ..
      tostring(userHeatThreshold) .. ", " .. tostring(userFrictionSens) .. ", " .. tostring(userFrictionTime) .. ", " ..
      tostring(userSmokeOnset) .. ", " .. tostring(userSmokeDecay) .. ", " .. tostring(bzX1) .. ", " .. tostring(bzY1) .. ", " .. tostring(bzX2) .. ", " .. tostring(bzY2) .. "); " ..
      "if ve.setSmokeOnsetBezier then ve.setSmokeOnsetBezier(" .. tostring(bzOnset) .. ", " .. tostring(bzHaze) .. ", " .. tostring(bzX1) .. ", " .. tostring(bzY1) .. ", " .. tostring(bzX2) .. ", " .. tostring(bzY2) .. ", " .. tostring(bzX3) .. ", " .. tostring(bzY3) .. ") end; " ..
      "if ve.setSmokeDecayBezier then ve.setSmokeDecayBezier(" .. tostring(decayDur) .. ", " .. tostring(decayY0) .. ", " .. tostring(decayX1) .. ", " .. tostring(decayY1) .. ", " .. tostring(decayX2) .. ", " .. tostring(decayY2) .. ") end; " ..
      "if ve.setSurfaceTuning then ve.setSurfaceTuning(" ..
      tostring(userSandDustScale) .. ", " .. tostring(userSandDustSens) .. ", " ..
      userSandDustActive .. ", " .. userAsphaltSmokeActive .. ") end " ..
      "end")
  end)
end

local function requestVehicleExtension(vehicle, params)
  if not vehicle then return end
  local enabled = frameSynchronousWheelTelemetry and "true" or "false"
  local p = params or {}
  local userHeatThreshold = p.heatThreshold or 70.0
  local userFrictionSens = p.frictionSens or 0.35
  local userFrictionTime = p.frictionTime or 2.00
  local userSmokeOnset = p.smokeOnset or 2.00
  local userSmokeDecay = p.smokeDecay or 1.50
  local bzDecay = p.smokeDecayBezier or { userSmokeDecay, 1.00, 0.25, 0.95, 0.65, 0.15 }
  local decayDur = tonumber(bzDecay[1] or bzDecay.duration) or userSmokeDecay
  local decayY0  = (#bzDecay >= 6 and tonumber(bzDecay[2])) or tonumber(bzDecay.y0) or 1.00
  local decayX1  = (#bzDecay >= 6 and tonumber(bzDecay[3])) or tonumber(bzDecay[2] or bzDecay.x1) or 0.25
  local decayY1  = (#bzDecay >= 6 and tonumber(bzDecay[4])) or tonumber(bzDecay[3] or bzDecay.y1) or 0.95
  local decayX2  = (#bzDecay >= 6 and tonumber(bzDecay[5])) or tonumber(bzDecay[4] or bzDecay.x2) or 0.65
  local decayY2  = (#bzDecay >= 6 and tonumber(bzDecay[6])) or tonumber(bzDecay[5] or bzDecay.y2) or 0.15
  local bz = p.smokeOnsetBezier or { 70.0, 0.0, 0.25, 0.05, 0.55, 0.95, 220.0, 1.00 }
  local bzOnset = (#bz >= 6) and (bz[1] or 70.0) or userHeatThreshold
  local bzHaze  = (#bz >= 6) and (bz[2] or 0.0) or 0.0
  local bzX1    = (#bz >= 6) and (bz[3] or 0.25) or (bz[1] or 0.25)
  local bzY1    = (#bz >= 6) and (bz[4] or 0.05) or (bz[2] or 0.05)
  local bzX2    = (#bz >= 6) and (bz[5] or 0.55) or (bz[3] or 0.55)
  local bzY2    = (#bz >= 6) and (bz[6] or 0.95) or (bz[4] or 0.95)
  local bzX3    = (#bz >= 8) and (bz[7] or 220.0) or 220.0
  local bzY3    = (#bz >= 8) and (bz[8] or 1.00) or 1.00
  local userSandDustScale = p.sandDustScale ~= nil and p.sandDustScale or 1.00
  local userSandDustSens = p.sandDustSens ~= nil and p.sandDustSens or 1.00
  local userSandDustActive = (p.sandDustEnabled ~= false) and "true" or "false"
  local userAsphaltSmokeActive = (p.asphaltSmokeEnabled ~= false) and "true" or "false"
  pcall(function()
    vehicle:queueLuaCommand(
      "extensions.load('realSmoke3DVE'); " ..
      "if extensions.realSmoke3DVE then " ..
      "extensions.realSmoke3DVE.setFrameSynchronousTelemetry(" .. enabled .. "); " ..
      "extensions.realSmoke3DVE.setBurnoutEquity(" .. tostring(userHeatThreshold) .. ", " .. tostring(userFrictionSens) .. ", " .. tostring(userFrictionTime) .. ", " ..
      tostring(userSmokeOnset) .. ", " .. tostring(userSmokeDecay) .. ", " .. tostring(bzX1) .. ", " .. tostring(bzY1) .. ", " .. tostring(bzX2) .. ", " .. tostring(bzY2) .. "); " ..
      "if extensions.realSmoke3DVE.setSmokeOnsetBezier then extensions.realSmoke3DVE.setSmokeOnsetBezier(" .. tostring(bzOnset) .. ", " .. tostring(bzHaze) .. ", " .. tostring(bzX1) .. ", " .. tostring(bzY1) .. ", " .. tostring(bzX2) .. ", " .. tostring(bzY2) .. ", " .. tostring(bzX3) .. ", " .. tostring(bzY3) .. ") end; " ..
      "if extensions.realSmoke3DVE.setSmokeDecayBezier then extensions.realSmoke3DVE.setSmokeDecayBezier(" .. tostring(decayDur) .. ", " .. tostring(decayY0) .. ", " .. tostring(decayX1) .. ", " .. tostring(decayY1) .. ", " .. tostring(decayX2) .. ", " .. tostring(decayY2) .. ") end; " ..
      "if extensions.realSmoke3DVE.setSurfaceTuning then extensions.realSmoke3DVE.setSurfaceTuning(" ..
      tostring(userSandDustScale) .. ", " .. tostring(userSandDustSens) .. ", " ..
      userSandDustActive .. ", " .. userAsphaltSmokeActive .. ") end " ..
      "end")
  end)
end

local function setFrameSynchronousWheelTelemetry(enabled, activeVehicleId)
  if enabled == frameSynchronousWheelTelemetry then return end
  frameSynchronousWheelTelemetry = enabled

  local vehicle = (type(getPlayerVehicle) == "function" and getPlayerVehicle(0)) or
                  (be and be:getPlayerVehicle(0))
  if not vehicle or getVehicleId(vehicle) ~= activeVehicleId then return end

  local value = enabled and "true" or "false"
  pcall(function()
    vehicle:queueLuaCommand(
      "if extensions.realSmoke3DVE then extensions.realSmoke3DVE.setFrameSynchronousTelemetry(" ..
      value .. ") end")
  end)
end

local function updateWheelTelemetryCadence(dtReal, dtSim, activeVehicleId)
  local realDelta = tonumber(dtReal)
  local simulationDelta = tonumber(dtSim)
  if not realDelta or not simulationDelta or realDelta <= 0 then return end

  local ratio = simulationDelta / realDelta
  if frameSynchronousWheelTelemetry then
    if ratio > 0.90 then setFrameSynchronousWheelTelemetry(false, activeVehicleId) end
  elseif ratio < 0.80 then
    setFrameSynchronousWheelTelemetry(true, activeVehicleId)
  end
end

local function wheelByName(targetName)
  if not wheelTelemetry or type(wheelTelemetry.wheels) ~= "table" then return nil end
  local targetUpper = string.upper(tostring(targetName))
  -- 1. Exact match
  for _, wheel in ipairs(wheelTelemetry.wheels) do
    if wheel.name and string.upper(wheel.name) == targetUpper then return wheel end
  end
  -- 2. Substring match (e.g. "wheel_FL", "FL1", "front_FL")
  for _, wheel in ipairs(wheelTelemetry.wheels) do
    if wheel.name then
      local wNameUpper = string.upper(wheel.name)
      if string.find(wNameUpper, targetUpper, 1, true) then return wheel end
    end
  end
  -- 3. Position-based fallback if names are custom
  local posMapping = { FL = 1, FR = 2, RL = 3, RR = 4 }
  local idx = posMapping[targetUpper]
  if idx and wheelTelemetry.wheels[idx] then
    return wheelTelemetry.wheels[idx]
  end
  return nil
end

local function toWorldVector(vehiclePos, offset)
  if not offset then return nil end
  return {vehiclePos.x + offset.x, vehiclePos.y + offset.y, vehiclePos.z + offset.z}
end

local function toVectorTable(value)
  if not value then return nil end
  return {value.x, value.y, value.z}
end

local function makeWheel(worldPos, telemetry, vehiclePos, vehicleVelocity, supportNormal, supportNormalValid)
  local result = {
    x = worldPos.x,
    y = worldPos.y,
    z = worldPos.z,
    emit = telemetry and clamp01(telemetry.emit) or 0,
    emitSmoke = telemetry and clamp01(telemetry.emitSmoke or 0) or 0,
    emitDust = telemetry and clamp01(telemetry.emitDust or 0) or 0,
    dustTint = telemetry and boundedNumber(telemetry.dustTint, 0, 10) or 0
  }
  if not telemetry then return result end

  local chosenNormal = supportNormalValid and supportNormal or nil
  local rawTreadContact = toWorldVector(vehiclePos, telemetry.contactOffset)
  result.rawTreadContact = rawTreadContact
  result.contact = rawTreadContact
  result.hub = toWorldVector(vehiclePos, telemetry.hubOffset)
  result.legacySource = {worldPos.x, worldPos.y, worldPos.z}
  if telemetry.geometryValid == true and rawTreadContact and result.hub and chosenNormal then
    -- lastTreadContactNode is a rotating tread node, so its tangent-plane
    -- coordinates orbit the hub. Keep it only as a sample of the support
    -- plane height, then project the stable hub centre onto that plane.
    local hubPoint = vec3(result.hub[1], result.hub[2], result.hub[3])
    local treadPoint = vec3(rawTreadContact[1], rawTreadContact[2], rawTreadContact[3])
    local hubToTread = treadPoint - hubPoint
    local signedHubHeight = -hubToTread:dot(chosenNormal)
    local tangentOffset = hubToTread + chosenNormal * signedHubHeight
    local stableContact = hubPoint - chosenNormal * signedHubHeight
    result.contact = {stableContact.x, stableContact.y, stableContact.z}
    result.supportPlaneDistance = signedHubHeight
    result.rawTreadTangentialOffset = tangentOffset:length()
    result.x = result.contact[1]
    result.y = result.contact[2]
    result.z = result.contact[3]
    result.sourceMode = "contactPatch"
    result.sourceGeometry = "hubProjectedSupportPlane"
    result.sourceValid = true
  elseif telemetry.geometryValid == true and rawTreadContact then
    result.x = rawTreadContact[1]
    result.y = rawTreadContact[2]
    result.z = rawTreadContact[3]
    result.sourceMode = "contactPatch"
    result.sourceGeometry = "rawTreadFallback"
    result.sourceValid = true
  else
    result.sourceMode = "legacyFallback"
    result.sourceGeometry = "legacyFallback"
    result.sourceValid = false
  end
  local relativeHubVelocity = telemetry.hubVelocity or {x = 0, y = 0, z = 0}
  local combinedHubVelocity, hubVelocityValid = sanitizeVelocity({
    x = vehicleVelocity.x + (tonumber(relativeHubVelocity.x) or 0),
    y = vehicleVelocity.y + (tonumber(relativeHubVelocity.y) or 0),
    z = vehicleVelocity.z + (tonumber(relativeHubVelocity.z) or 0)
  }, 75.0)
  result.hubVel = {combinedHubVelocity.x, combinedHubVelocity.y, combinedHubVelocity.z}
  result.hubVelocityValid = hubVelocityValid
  result.spinAxis = toVectorTable(telemetry.spinAxis)
  result.axleAxis = toVectorTable(telemetry.axleAxis)
  result.normal = chosenNormal and {chosenNormal.x, chosenNormal.y, chosenNormal.z} or toVectorTable(telemetry.groundNormal)
  if chosenNormal and telemetry.axleAxis then
    local axle = vec3(telemetry.axleAxis.x, telemetry.axleAxis.y, telemetry.axleAxis.z)
    local wheelForward = axle:cross(chosenNormal)
    if wheelForward:length() > 0.0001 then wheelForward = wheelForward:normalized() end
    result.forward = {wheelForward.x, wheelForward.y, wheelForward.z}
  else
    result.forward = toVectorTable(telemetry.forwardDir)
  end
  result.omega = tonumber(telemetry.rollingAngularVelocity) or tonumber(telemetry.angularVelocity) or 0
  result.rollingOmega = tonumber(telemetry.rollingAngularVelocity) or 0
  result.radius = tonumber(telemetry.radius) or 0.35
  result.width = tonumber(telemetry.width) or 0.20
  result.wheelDir = tonumber(telemetry.wheelDir) or 1
  result.slip = tonumber(telemetry.slip) or 0
  result.slipEnergy = tonumber(telemetry.slipEnergy) or 0
  local rawTemp = tonumber(telemetry.temperature) or 20.0
  result.temperature = math.max(15.0, math.min(250.0, rawTemp))
  local rawPatchTemp = tonumber(telemetry.contactPatchTemperature) or result.temperature
  result.contactPatchTemperature = math.max(15.0, math.min(260.0, rawPatchTemp))
  result.normalLoad = tonumber(telemetry.normalLoad) or 0
  result.contactDepth = tonumber(telemetry.contactDepth) or 0
  result.material1 = tonumber(telemetry.material1) or -1
  result.material2 = tonumber(telemetry.material2) or -1
  result.geometryValid = telemetry.geometryValid == true
  result.normalValid = supportNormalValid or telemetry.normalValid == true
  return result
end

local function onVolSmokeWheelTelemetry(data, activeVehicleId)
  if type(data) ~= "table" then return end
  local vehicleId = tonumber(data.vehicleId) or -1
  if activeVehicleId >= 0 and vehicleId ~= activeVehicleId then return end
  wheelTelemetry = data
  wheelTelemetryAge = 0
  lastWheelProtocolVersion = tonumber(data.protocolVersion) or 1
  lastVehicleProvenanceBuildId = data.provenanceBuildId
  if data.particleGuardActive ~= nil then
    lastParticleGuardActive = (data.particleGuardActive == true)
  end
  if data.profile and type(data.profile) == "table" and #data.profile >= 4 then
    lastVehicleProfile = data.profile
  end
end

local function resetVehicleState()
  vehicleLoadTimer = math.huge
  wheelTelemetry = nil
  wheelTelemetryAge = math.huge
  lastForwardVec = nil
  lastUpVec = nil
  lastVehiclePos = nil
  calculatedAngVel = vec3(0, 0, 0)
  lastParticleGuardActive = false
end

local function advanceTimers(dt)
  wheelTelemetryAge = wheelTelemetryAge + dt
  vehicleLoadTimer = vehicleLoadTimer + dt
end

M.sanitizeVelocity = sanitizeVelocity
M.sanitizeAngularVelocity = sanitizeAngularVelocity
M.clamp01 = clamp01
M.boundedNumber = boundedNumber
M.makeNativeWheelPayload = makeNativeWheelPayload
M.getVehicleId = getVehicleId
M.syncBurnoutEquityToVehicle = syncBurnoutEquityToVehicle
M.requestVehicleExtension = requestVehicleExtension
M.setFrameSynchronousWheelTelemetry = setFrameSynchronousWheelTelemetry
M.updateWheelTelemetryCadence = updateWheelTelemetryCadence
M.wheelByName = wheelByName
M.toWorldVector = toWorldVector
M.toVectorTable = toVectorTable
M.makeWheel = makeWheel
M.onVolSmokeWheelTelemetry = onVolSmokeWheelTelemetry
M.resetVehicleState = resetVehicleState
M.advanceTimers = advanceTimers
M.getVehicleProfile = function() return lastVehicleProfile or { 0.50, 0.30, 0.50, 0.80 } end

M.getWheelTelemetry = function() return wheelTelemetry end
M.getWheelTelemetryAge = function() return wheelTelemetryAge end
M.getVehicleLoadTimer = function() return vehicleLoadTimer end
M.setVehicleLoadTimer = function(t) vehicleLoadTimer = t end
M.isFrameSynchronous = function() return frameSynchronousWheelTelemetry end
M.getLastWheelProtocolVersion = function() return lastWheelProtocolVersion end
M.getLastVehicleProvenanceBuildId = function() return lastVehicleProvenanceBuildId end
M.getGeometryValidCount = function() return geometryValidCount end
M.setGeometryValidCount = function(c) geometryValidCount = c end
M.getNormalValidCount = function() return normalValidCount end
M.setNormalValidCount = function(c) normalValidCount = c end
M.getContactSourceCount = function() return contactSourceCount end
M.setContactSourceCount = function(c) contactSourceCount = c end
M.getLastTelemetrySnapshot = function() return lastTelemetrySnapshot end
M.setLastTelemetrySnapshot = function(s) lastTelemetrySnapshot = s end
M.getVelocityRejectCount = function() return velocityRejectCount end
M.incVelocityRejectCount = function() velocityRejectCount = velocityRejectCount + 1 end
M.getLastVehicleVelocityValid = function() return lastVehicleVelocityValid end
M.setLastVehicleVelocityValid = function(v) lastVehicleVelocityValid = v end
M.isBodyColliderValid = function() return bodyColliderValid end
M.setBodyColliderValid = function(v) bodyColliderValid = v end
M.getLastBodyHalfExtents = function() return lastBodyHalfExtents end
M.setLastBodyHalfExtents = function(e) lastBodyHalfExtents = e end
M.getLastForwardVec = function() return lastForwardVec end
M.setLastForwardVec = function(v) lastForwardVec = v end
M.getLastUpVec = function() return lastUpVec end
M.setLastUpVec = function(v) lastUpVec = v end
M.getLastVehiclePos = function() return lastVehiclePos end
M.setLastVehiclePos = function(p) lastVehiclePos = p end
M.getCalculatedAngVel = function() return calculatedAngVel end
M.setCalculatedAngVel = function(w) calculatedAngVel = w end
M.isParticleGuardActive = function() return lastParticleGuardActive end

return M
