-- ============================================================================
-- PROJECT: VolSmoke for BeamNG.drive.
-- COPYRIGHT (C) 2026 REALSMOKE 3D CONTRIBUTORS.
-- LICENSE: MIT (see LICENSE). Original project: https://github.com/ThugbobTrapabrickpants/VolSmoke
-- ============================================================================
-- VolSmoke UI Bridge Submodule.
-- Owns user tuning parameters, physics presets, and telemetry forwarding to AngularJS UI.

local M = {}

local PARAM_SPECS = {
  simulationQuality = { type = "number", min = 1.0, max = 5.0, default = 2.0 },
  voxelSize = { type = "number", min = 0.040, max = 0.100, default = 0.064 },
  domainSize = { type = "number", min = 6.0, max = 70.0, default = 13.5 },
  underbodyEject = { type = "number", min = 0.0, max = 3.0, default = 0.20, syncAlias = "wakeShielding" },
  wakeShielding = { aliasFor = "underbodyEject" },
  archEject = { type = "number", min = 0.0, max = 3.0, default = 0.15 },
  vorticityStrength = { aliasFor = "turbStrength1" },
  roadDamping = { type = "number", min = 0.0, max = 5.0, default = 0.55 },
  smokeDrag = { type = "number", min = 0.0, max = 5.0, default = 0.15 },
  wakeSuction = { type = "number", min = 0.0, max = 5.0, default = 0.00 },
  slipstream = { type = "number", min = 0.0, max = 5.0, default = 0.75 },
  slipstreamSpeedLimit = { type = "number", min = 5.0, max = 300.0, default = 50.0 },
  slipstreamHoldTime = { type = "number", min = 0.0, max = 2000.0, default = 200.0 },
  slipstreamBezier = { type = "bezier4", min = 0.0, max = 1.0, default = { 1.00, 1.00, 1.00, 0.00 } },
  slipstreamTurbScale = { type = "number", min = 0.10, max = 5.0, default = 0.30 },
  slipstreamTurbStrength = { type = "number", min = 0.0, max = 5.0, default = 0.50 },
  coreLifetime = { type = "number", min = 0.05, max = 2.5, default = 0.25 },
  thermalBuoyancy = { type = "number", min = 0.0, max = 2.5, default = 0.10 },
  treadSaturation = { type = "number", min = 0.1, max = 7.0, default = 1.00 },
  treadCoupling = { type = "number", min = 0.05, max = 1.00, default = 0.50 },
  edgeDispersion = { type = "number", min = 0.05, max = 2.50, default = 0.50 },
  dispersionRate = { type = "number", min = 0.1, max = 3.0, default = 0.40 },
  treadTurbulence = { aliasFor = "turbStrength2" },
  turbScale1 = { type = "number", min = 0.2, max = 3.0, default = 1.05 },
  turbStrength1 = { type = "number", min = 0.0, max = 3.0, default = 1.30, syncAlias = "vorticityStrength" },
  turbScale2 = { type = "number", min = 0.2, max = 3.0, default = 0.75 },
  turbStrength2 = { type = "number", min = 0.0, max = 3.0, default = 1.00, syncAlias = "treadTurbulence" },
  turbTransition = { type = "number", min = 0.0, max = 12.0, default = 1.20 },
  turbRelax = { type = "number", min = 0.2, max = 20.0, default = 2.00 },
  turbArch = { type = "number", min = 0.0, max = 8.0, default = 2.00 },
  turbArchScale = { type = "number", min = 0.2, max = 3.0, default = 0.25 },
  microFiber = { type = "number", min = 0.0, max = 3.0, default = 1.00 },
  fiberScale = { type = "number", min = 0.2, max = 3.0, default = 1.00 },
  hazeNormals = { type = "number", min = 0.0, max = 3.0, default = 1.00 },
  creviceShadow = { type = "number", min = 0.0, max = 3.0, default = 0.10 },
  coreOpacity = { type = "number", min = 0.0, max = 4.0, default = 1.00 },
  vorticityDetail = { type = "number", min = 0.0, max = 3.0, default = 1.00 },
  smokeColor = { type = "color", default = { 1.0, 1.0, 1.0 } },
  dustColor = { type = "color", default = { 0.76, 0.65, 0.50 } },
  debugWakeMode = { type = "integer", min = 0, max = 2, default = 0 },
  heatThreshold = { type = "number", min = 40.0, max = 120.0, default = 70.0, syncVehicle = true, syncBezierOnset = true },
  frictionSens = { type = "number", min = 0.05, max = 3.0, default = 0.35, syncVehicle = true },
  frictionTime = { type = "number", min = 0.0, max = 3.0, default = 2.00, syncVehicle = true },
  smokeOnset = { type = "number", min = 0.05, max = 3.0, default = 2.00, syncVehicle = true },
  smokeOnsetBezier = { type = "bezier8", default = { 70.0, 0.0, 0.25, 0.05, 0.55, 0.95, 220.0, 1.00 }, syncVehicle = true },
  smokeDecay = { type = "number", min = 0.0, max = 5.0, default = 1.50, syncVehicle = true, syncDecayBezier = true },
  smokeDecayBezier = { type = "bezier6", default = { 1.50, 1.00, 0.25, 0.95, 0.65, 0.15 }, syncVehicle = true },
  sandDustScale = { type = "number", min = 0.0, max = 3.0, default = 1.00, syncVehicle = true },
  sandDustSens = { type = "number", min = 0.05, max = 3.0, default = 1.00, syncVehicle = true },
  sandDustEnabled = { type = "boolean", default = true, syncVehicle = true },
  asphaltSmokeEnabled = { type = "boolean", default = true, syncVehicle = true },
  activeSurfaceProfile = { type = "string", default = "asphalt" }
}

for _, k in ipairs({
  "underbodyEject", "archEject", "roadDamping", "smokeDrag",
  "coreLifetime", "thermalBuoyancy", "treadSaturation", "treadCoupling", "edgeDispersion", "dispersionRate",
  "turbScale1", "turbStrength1", "turbScale2", "turbStrength2", "turbTransition", "turbRelax", "turbArch", "turbArchScale", "microFiber", "fiberScale",
  "hazeNormals", "creviceShadow", "coreOpacity", "vorticityDetail"
}) do
  PARAM_SPECS[k].surfaceShared = true
end

local userParams = {}
local tireSyncCallback = nil
local isBatchUpdating = false

local function notifyTireSync()
  if tireSyncCallback then
    pcall(tireSyncCallback)
  end
end

local function resetPhysicsDefaults()
  userParams.surfaceProfiles = { asphalt = {}, sand = {} }
  userParams.activeSimSurface = "asphalt"
  for name, spec in pairs(PARAM_SPECS) do
    if not spec.aliasFor then
      if spec.type == "color" or spec.type == "bezier4" or spec.type == "bezier5" or spec.type == "bezier6" or spec.type == "bezier8" then
        local t = {}
        for i, val in ipairs(spec.default) do t[i] = val end
        userParams[name] = t
      else
        userParams[name] = spec.default
      end
      if spec.surfaceShared then
        userParams.surfaceProfiles.asphalt[name] = userParams[name]
        userParams.surfaceProfiles.sand[name] = userParams[name]
        if spec.syncAlias then
          userParams.surfaceProfiles.asphalt[spec.syncAlias] = userParams[name]
          userParams.surfaceProfiles.sand[spec.syncAlias] = userParams[name]
        end
      end
    end
  end
  -- Sync aliases
  userParams.wakeShielding = userParams.underbodyEject
  userParams.vorticityStrength = userParams.turbStrength1
  userParams.treadTurbulence = userParams.turbStrength2
  if userParams.smokeOnsetBezier and userParams.heatThreshold then
    userParams.smokeOnsetBezier[1] = userParams.heatThreshold
  end

  if not isBatchUpdating then
    notifyTireSync()
    if M.saveSettingsToDisk then M.saveSettingsToDisk() end
    print("[VolSmoke GE] Physics parameters reset to user defaults")
    if log then log("I", "realSmoke3DGE", "Physics parameters reset to user defaults") end
  end
end

-- Initialize userParams from PARAM_SPECS
resetPhysicsDefaults()

local function getGridSpec()
  local vSize = userParams.voxelSize or 0.064
  local dSize = userParams.domainSize or 13.5
  local rawWidth = math.floor(dSize / vSize + 0.999999)
  local rawDepth = math.floor(3.84 / vSize + 0.999999)
  local width = math.ceil(rawWidth / 8) * 8
  local depth = math.ceil(rawDepth / 4) * 4
  return width, width, depth
end

-- Keep this payload builder outside onUpdate's protected closure. BeamNG ships
-- LuaJIT with a hard limit of 60 upvalues per function; capturing userParams
-- as a single table reference permanently protects against LUAI_MAXUPVALUES overflows.
local function sendUiTelemetry(uiWheels, totalEmission, diag)
  local gridWidth, gridHeight, gridDepth = getGridSpec()
  local d = diag or {}
  guihooks.trigger("VolSmokeTelemetry", {
    wheels = uiWheels,
    totalEmission = totalEmission,
    simulationQuality = userParams.simulationQuality,
    voxelSize = userParams.voxelSize,
    domainSize = userParams.domainSize,
    gridWidth = gridWidth,
    gridHeight = gridHeight,
    gridDepth = gridDepth,
    domainX = gridWidth * userParams.voxelSize,
    domainY = gridHeight * userParams.voxelSize,
    domainZ = gridDepth * userParams.voxelSize,
    underbodyEject = userParams.underbodyEject,
    archEject = userParams.archEject,
    vorticityStrength = userParams.turbStrength1,
    roadDamping = userParams.roadDamping,
    smokeDrag = userParams.smokeDrag,
    wakeSuction = userParams.wakeSuction,
    slipstream = userParams.slipstream,
    slipstreamSpeedLimit = userParams.slipstreamSpeedLimit,
    slipstreamHoldTime = userParams.slipstreamHoldTime,
    slipstreamBezier = userParams.slipstreamBezier,
    slipstreamTurbScale = userParams.slipstreamTurbScale,
    slipstreamTurbStrength = userParams.slipstreamTurbStrength,
    coreLifetime = userParams.coreLifetime,
    thermalBuoyancy = userParams.thermalBuoyancy,
    treadSaturation = userParams.treadSaturation,
    treadCoupling = userParams.treadCoupling,
    edgeDispersion = userParams.edgeDispersion,
    dispersionRate = userParams.dispersionRate,
    treadTurbulence = userParams.turbStrength2,
    turbScale1 = userParams.turbScale1,
    turbStrength1 = userParams.turbStrength1,
    turbScale2 = userParams.turbScale2,
    turbStrength2 = userParams.turbStrength2,
    turbTransition = userParams.turbTransition,
    turbRelax = userParams.turbRelax,
    turbArch = userParams.turbArch,
    turbArchScale = userParams.turbArchScale,
    microFiber = userParams.microFiber,
    fiberScale = userParams.fiberScale,
    hazeNormals = userParams.hazeNormals,
    creviceShadow = userParams.creviceShadow,
    coreOpacity = userParams.coreOpacity,
    vorticityDetail = userParams.vorticityDetail,
    smokeColor = userParams.smokeColor,
    dustColor = userParams.dustColor,
    heatThreshold = userParams.heatThreshold,
    frictionSens = userParams.frictionSens,
    frictionTime = userParams.frictionTime,
    smokeOnset = userParams.smokeOnset,
    smokeOnsetBezier = userParams.smokeOnsetBezier,
    smokeDecay = userParams.smokeDecay,
    smokeDecayBezier = userParams.smokeDecayBezier,
    activeSurfaceProfile = userParams.activeSurfaceProfile or "asphalt",
    sandDustScale = userParams.sandDustScale,
    sandDustSens = userParams.sandDustSens,
    sandDustEnabled = userParams.sandDustEnabled,
    asphaltSmokeEnabled = userParams.asphaltSmokeEnabled,
    diagStatus = d.status or "CONNECTING",
    diagCode = d.code or "CONNECTING",
    diagApi = d.api or "UNKNOWN",
    diagApiLabel = d.apiLabel or d.api or "D3D11",
    diagScaled = d.scaled == true,
    diagScalePct = d.scalePct or 100,
    diagDepthW = d.depthW or 0,
    diagDepthH = d.depthH or 0,
    diagFrameW = d.frameW or 0,
    diagFrameH = d.frameH or 0,
    diagHdr = d.hdr == true,
    diagUiCaptured = d.uiCaptured ~= false,
    conflictingAddon = d.conflictingAddon,
    diagFrames = d.frames or 0,
    diagDepthOk = d.depthOk ~= false,
    diagFps = d.fps or 0,
    diagFpsAvg = d.fpsAvg or 0,
    diagFpsMin = d.fpsMin or 0,
    diagFrameMs = d.frameMs or 0,
    diagGpuMs = d.gpuMs or 0,
    particleConflict = d.particleConflict == true,
    particleConflictMod = d.particleConflictMod,
    particleSuppressed = d.particleSuppressed ~= false
  })
end

local function setPhysicsParam(param, val, p2, p3, p4, p5, p6, p7, p8)
  local spec = PARAM_SPECS[param]
  if not spec then return end
  if spec.aliasFor then
    setPhysicsParam(spec.aliasFor, val, p2, p3, p4, p5, p6, p7, p8)
    return
  end

  if spec.type == "number" then
    local num = tonumber(val) or spec.default
    userParams[param] = math.max(spec.min, math.min(spec.max, num))
    if spec.syncAlias then
      userParams[spec.syncAlias] = userParams[param]
    end
    if spec.surfaceShared then
      local activeProf = (userParams.activeSurfaceProfile == "sand") and "sand" or "asphalt"
      userParams.activeSimSurface = activeProf
      userParams.surfaceProfiles = userParams.surfaceProfiles or { asphalt = {}, sand = {} }
      userParams.surfaceProfiles[activeProf] = userParams.surfaceProfiles[activeProf] or {}
      userParams.surfaceProfiles[activeProf][param] = userParams[param]
      if spec.syncAlias then
        userParams.surfaceProfiles[activeProf][spec.syncAlias] = userParams[param]
      end
    end
    if spec.syncBezierOnset and userParams.smokeOnsetBezier then
      userParams.smokeOnsetBezier[1] = userParams[param]
    end
    if spec.syncDecayBezier and userParams.smokeDecayBezier then
      userParams.smokeDecayBezier[1] = userParams[param]
    end
  elseif spec.type == "integer" then
    local num = math.floor(tonumber(val) or spec.default)
    userParams[param] = math.max(spec.min, math.min(spec.max, num))
  elseif spec.type == "boolean" then
    userParams[param] = (val == true or val == 1 or val == "1" or val == "true")
  elseif spec.type == "string" then
    if type(val) == "string" and (val == "asphalt" or val == "sand") then
      userParams[param] = val
      if param == "activeSurfaceProfile" then
        userParams.activeSimSurface = val
        if userParams.surfaceProfiles and type(userParams.surfaceProfiles[val]) == "table" then
          local sp = userParams.surfaceProfiles[val]
          for name, s in pairs(PARAM_SPECS) do
            if s.surfaceShared and sp[name] ~= nil then
              userParams[name] = sp[name]
              if s.syncAlias then
                userParams[s.syncAlias] = sp[name]
              end
            end
          end
        end
      end
    end
  elseif spec.type == "color" then
    if type(val) == "table" then
      local r = tonumber(val[1] or val.r or val.x) or spec.default[1]
      local g = tonumber(val[2] or val.g or val.y) or spec.default[2]
      local b = tonumber(val[3] or val.b or val.z) or spec.default[3]
      userParams[param] = {
        math.max(0.0, math.min(1.0, r)),
        math.max(0.0, math.min(1.0, g)),
        math.max(0.0, math.min(1.0, b))
      }
    elseif type(val) == "string" and string.sub(val, 1, 1) == "#" then
      local hex = string.sub(val, 2)
      if #hex == 6 then
        local r = tonumber(string.sub(hex, 1, 2), 16) or 255
        local g = tonumber(string.sub(hex, 3, 4), 16) or 255
        local b = tonumber(string.sub(hex, 5, 6), 16) or 255
        userParams[param] = { r / 255.0, g / 255.0, b / 255.0 }
      end
    end
  elseif spec.type == "bezier4" then
    local x1, y1, x2, y2 = val, p2, p3, p4
    if type(val) == "table" then
      local t = val
      x1, y1, x2, y2 = t[1] or t.x1, t[2] or t.y1, t[3] or t.x2, t[4] or t.y2
    end
    userParams[param] = {
      math.max(0.0, math.min(1.0, tonumber(x1) or spec.default[1])),
      math.max(0.0, math.min(1.0, tonumber(y1) or spec.default[2])),
      math.max(0.0, math.min(1.0, tonumber(x2) or spec.default[3])),
      math.max(0.0, math.min(1.0, tonumber(y2) or spec.default[4]))
    }
  elseif spec.type == "bezier6" and param == "smokeDecayBezier" then
    local dur, y0, x1, y1, x2, y2 = val, p2, p3, p4, p5, p6
    if type(val) == "table" then
      local t = val
      if #t >= 6 then
        dur, y0, x1, y1, x2, y2 = t[1], t[2], t[3], t[4], t[5], t[6]
      elseif #t == 5 then
        dur, y0, x1, y1, x2, y2 = t[1], 1.00, t[2], t[3], t[4], t[5]
      else
        dur = t.duration or 1.50
        y0 = t.y0 or 1.00
        x1 = t.x1 or 0.25
        y1 = t.y1 or 0.95
        x2 = t.x2 or 0.65
        y2 = t.y2 or 0.15
      end
    end
    userParams[param] = {
      math.max(0.0, math.min(5.0, tonumber(dur) or 1.50)),
      math.max(0.00, math.min(1.00, tonumber(y0) or 1.00)),
      math.max(0.0, math.min(1.0, tonumber(x1) or 0.25)),
      math.max(0.0, math.min(1.0, tonumber(y1) or 0.95)),
      math.max(0.0, math.min(1.0, tonumber(x2) or 0.65)),
      math.max(0.0, math.min(1.0, tonumber(y2) or 0.15))
    }
    userParams.smokeDecay = userParams[param][1]
  elseif spec.type == "bezier8" or spec.type == "bezier6" then
    local b1, b2, b3, b4, b5, b6, b7, b8 = val, p2, p3, p4, p5, p6, p7, p8
    if type(val) == "table" then
      local t = val
      if #t >= 8 then
        b1, b2, b3, b4, b5, b6, b7, b8 = t[1], t[2], t[3], t[4], t[5], t[6], t[7], t[8]
      elseif #t >= 6 then
        b1, b2, b3, b4, b5, b6 = t[1], t[2], t[3], t[4], t[5], t[6]
        b7, b8 = 220.0, 1.00
      elseif t.x0 ~= nil then
        b1, b2, b3, b4 = t.x0, t.y0, t.x1, t.y1
        b5, b6 = t.x2, t.y2
        b7, b8 = t.x3 or 220.0, t.y3 or 1.00
      else
        b1, b2, b3, b4 = t[1] or t.x1, t[2] or t.y1, t[3] or t.x2, t[4] or t.y2
        b5, b6 = 0.55, 0.95
        b7, b8 = 220.0, 1.00
      end
    end
    if b5 ~= nil and b6 ~= nil then
      local onset = math.max(40.0, math.min(220.0, tonumber(b1) or userParams.heatThreshold or 70.0))
      userParams.heatThreshold = onset
      userParams[param] = {
        onset,
        math.max(0.0, math.min(1.00, tonumber(b2) or 0.0)),
        math.max(0.0, math.min(1.0, tonumber(b3) or 0.25)),
        math.max(0.0, math.min(1.0, tonumber(b4) or 0.05)),
        math.max(0.0, math.min(1.0, tonumber(b5) or 0.55)),
        math.max(0.0, math.min(1.0, tonumber(b6) or 0.95)),
        math.max(60.0, math.min(240.0, tonumber(b7) or 220.0)),
        math.max(0.0, math.min(1.00, tonumber(b8) or 1.00))
      }
    else
      userParams[param] = {
        userParams.heatThreshold or 70.0,
        0.0,
        math.max(0.0, math.min(1.0, tonumber(b1) or 0.25)),
        math.max(0.0, math.min(1.0, tonumber(b2) or 0.05)),
        math.max(0.0, math.min(1.0, tonumber(b3) or 0.55)),
        math.max(0.0, math.min(1.0, tonumber(b4) or 0.95)),
        220.0,
        1.00
      }
    end
  end

  if spec.syncVehicle and not isBatchUpdating then
    notifyTireSync()
  end

  if not isBatchUpdating then
    if M.saveSettingsToDisk then M.saveSettingsToDisk() end
    print("[VolSmoke GE] Physics param " .. tostring(param) .. " set to " .. tostring(val))
    if log then log("I", "realSmoke3DGE", "Physics param " .. tostring(param) .. " set to " .. tostring(val)) end
  end
end

local function setSimulationQuality(val)
  setPhysicsParam("simulationQuality", val)
  if not isBatchUpdating and log then
    log("I", "realSmoke3DGE", "Simulation quality set to " .. tostring(userParams.simulationQuality) .. "x")
  end
end

local function getSimulationQuality()
  return userParams.simulationQuality
end

local function setVoxelSize(size)
  local n = tonumber(size) or 0.064
  local millimeters = (n > 1.0) and math.floor(n + 0.5) or math.floor(n * 1000 + 0.5)
  millimeters = math.max(40, math.min(100, millimeters))
  userParams.voxelSize = millimeters / 1000
  if not isBatchUpdating then
    if M.saveSettingsToDisk then M.saveSettingsToDisk() end
    print("[VolSmoke GE] Voxel size set to " .. tostring(millimeters) .. " mm (" .. tostring(userParams.voxelSize) .. " m)")
    if log then log("I", "realSmoke3DGE", "Voxel size set to " .. tostring(millimeters) .. " mm") end
  end
end

local function getVoxelSize()
  return userParams.voxelSize
end

local function setDomainSize(size)
  local n = tonumber(size) or 13.5
  userParams.domainSize = math.max(6.0, math.min(70.0, n))
  if not isBatchUpdating then
    if M.saveSettingsToDisk then M.saveSettingsToDisk() end
    print("[VolSmoke GE] Domain size set to " .. tostring(userParams.domainSize) .. " m")
    if log then log("I", "realSmoke3DGE", "Domain size set to " .. tostring(userParams.domainSize) .. " m") end
  end
end

local function getDomainSize()
  return userParams.domainSize
end

local function setUnderbodyEject(val) setPhysicsParam("underbodyEject", val) end
local function setWakeShielding(val) setPhysicsParam("underbodyEject", val) end
local function setArchEject(val) setPhysicsParam("archEject", val) end
local function setVorticityStrength(val) setPhysicsParam("turbStrength1", val) end
local function setRoadDamping(val) setPhysicsParam("roadDamping", val) end
local function setSmokeDrag(val) setPhysicsParam("smokeDrag", val) end
local function setWakeSuction(val) setPhysicsParam("wakeSuction", val) end
local function setSlipstream(val) setPhysicsParam("slipstream", val) end
local function setSlipstreamSpeedLimit(val) setPhysicsParam("slipstreamSpeedLimit", val) end
local function setSlipstreamHoldTime(val) setPhysicsParam("slipstreamHoldTime", val) end
local function setSlipstreamBezier(x1, y1, x2, y2) setPhysicsParam("slipstreamBezier", x1, y1, x2, y2) end
local function setSlipstreamTurbScale(val) setPhysicsParam("slipstreamTurbScale", val) end
local function setSlipstreamTurbStrength(val) setPhysicsParam("slipstreamTurbStrength", val) end
local function setCoreLifetime(val) setPhysicsParam("coreLifetime", val) end
local function setThermalBuoyancy(val) setPhysicsParam("thermalBuoyancy", val) end
local function setTreadSaturation(val) setPhysicsParam("treadSaturation", val) end
local function setTreadCoupling(val) setPhysicsParam("treadCoupling", val) end
local function setEdgeDispersion(val) setPhysicsParam("edgeDispersion", val) end
local function setDispersionRate(val) setPhysicsParam("dispersionRate", val) end
local function setTreadTurbulence(val) setPhysicsParam("turbStrength2", val) end
local function setTurbScale1(val) setPhysicsParam("turbScale1", val) end
local function setTurbStrength1(val) setPhysicsParam("turbStrength1", val) end
local function setTurbScale2(val) setPhysicsParam("turbScale2", val) end
local function setTurbStrength2(val) setPhysicsParam("turbStrength2", val) end
local function setTurbTransition(val) setPhysicsParam("turbTransition", val) end
local function setTurbRelax(val) setPhysicsParam("turbRelax", val) end
local function setTurbArch(val) setPhysicsParam("turbArch", val) end
local function setTurbArchScale(val) setPhysicsParam("turbArchScale", val) end
local function setMicroFiber(val) setPhysicsParam("microFiber", val) end
local function setFiberScale(val) setPhysicsParam("fiberScale", val) end
local function setHazeNormals(val) setPhysicsParam("hazeNormals", val) end
local function setCreviceShadow(val) setPhysicsParam("creviceShadow", val) end
local function setCoreOpacity(val) setPhysicsParam("coreOpacity", val) end
local function setVorticityDetail(val) setPhysicsParam("vorticityDetail", val) end
local function setDebugWakeMode(val) setPhysicsParam("debugWakeMode", val) end
local function setHeatThreshold(val) setPhysicsParam("heatThreshold", val) end
local function setFrictionSens(val) setPhysicsParam("frictionSens", val) end
local function setFrictionTime(val) setPhysicsParam("frictionTime", val) end
local function setSmokeOnset(val) setPhysicsParam("smokeOnset", val) end
local function setSmokeOnsetBezier(p1, p2, p3, p4, p5, p6, p7, p8) setPhysicsParam("smokeOnsetBezier", p1, p2, p3, p4, p5, p6, p7, p8) end
local function setSmokeDecay(val) setPhysicsParam("smokeDecay", val) end
local function setSmokeDecayBezier(...) setPhysicsParam("smokeDecayBezier", ...) end
local function setSandDustScale(val) setPhysicsParam("sandDustScale", val) end
local function setSandDustSens(val) setPhysicsParam("sandDustSens", val) end
local function setSandDustEnabled(val) setPhysicsParam("sandDustEnabled", val) end
local function setAsphaltSmokeEnabled(val) setPhysicsParam("asphaltSmokeEnabled", val) end
local function setSmokeColor(val) setPhysicsParam("smokeColor", val) end
local function setDustColor(val) setPhysicsParam("dustColor", val) end

local SETTINGS_FILE_PATH = "settings/realSmoke3D_settings.json"
local savedUiState = nil

local function applySurfaceProfilesTable(spTable)
  if type(spTable) ~= "table" then return end
  userParams.surfaceProfiles = userParams.surfaceProfiles or { asphalt = {}, sand = {} }
  for _, prof in ipairs({ "asphalt", "sand" }) do
    local src = spTable[prof]
    if type(src) == "table" then
      userParams.surfaceProfiles[prof] = userParams.surfaceProfiles[prof] or {}
      for k, v in pairs(src) do
        local spec = PARAM_SPECS[k]
        local targetKey = k
        if spec and spec.aliasFor then
          targetKey = spec.aliasFor
          spec = PARAM_SPECS[targetKey]
        end
        if spec and spec.surfaceShared and spec.type == "number" then
          local num = tonumber(v) or spec.default
          local clamped = math.max(spec.min, math.min(spec.max, num))
          userParams.surfaceProfiles[prof][targetKey] = clamped
          if spec.syncAlias then
            userParams.surfaceProfiles[prof][spec.syncAlias] = clamped
          end
        end
      end
    end
  end
  local activeProf = (userParams.activeSurfaceProfile == "sand") and "sand" or "asphalt"
  local activeMap = userParams.surfaceProfiles[activeProf]
  if type(activeMap) == "table" then
    for name, s in pairs(PARAM_SPECS) do
      if s.surfaceShared and activeMap[name] ~= nil then
        userParams[name] = activeMap[name]
        if s.syncAlias then
          userParams[s.syncAlias] = activeMap[name]
        end
      end
    end
  end
end

local function saveSettingsToDisk(uiPayload)
  local payload = {
    version = "0.8.12.9",
    timestamp = os.time(),
    userParams = userParams
  }
  if type(uiPayload) == "string" then
    local ok, dec = pcall(jsonDecode, uiPayload)
    if ok and type(dec) == "table" then uiPayload = dec end
  end
  if type(uiPayload) == "table" and (uiPayload.presets ~= nil or uiPayload.activePresetId ~= nil or uiPayload.lang ~= nil) then
    savedUiState = savedUiState or {}
    if uiPayload.presets ~= nil then savedUiState.presets = uiPayload.presets end
    if uiPayload.activePresetId ~= nil then savedUiState.activePresetId = uiPayload.activePresetId end
    if uiPayload.lang ~= nil then savedUiState.lang = uiPayload.lang end
  end
  if type(savedUiState) == "table" then
    if savedUiState.presets ~= nil then payload.presets = savedUiState.presets end
    if savedUiState.activePresetId ~= nil then payload.activePresetId = savedUiState.activePresetId end
    if savedUiState.lang ~= nil then payload.lang = savedUiState.lang end
  end
  pcall(jsonWriteFile, SETTINGS_FILE_PATH, payload, true)
end

local function loadSettingsFromDisk()
  local ok, data = pcall(jsonReadFile, SETTINGS_FILE_PATH)
  if ok and type(data) == "table" then
    savedUiState = data
    local p = data.userParams or data.params
    if type(p) == "table" then
      isBatchUpdating = true
      if p.activeSurfaceProfile ~= nil then
        setPhysicsParam("activeSurfaceProfile", p.activeSurfaceProfile)
      end
      if p.simulationQuality ~= nil then setSimulationQuality(p.simulationQuality) end
      if p.voxelMillimeters ~= nil then setVoxelSize(p.voxelMillimeters)
      elseif p.voxelSize ~= nil then
        local v = tonumber(p.voxelSize)
        if v and v < 1.0 then setVoxelSize(v * 1000) else setVoxelSize(v) end
      end
      if p.domainSize ~= nil then setDomainSize(p.domainSize) end

      -- Deterministic Pass 1: Scalars, colors, strings, booleans
      for k, v in pairs(p) do
        if k ~= "simulationQuality" and k ~= "voxelMillimeters" and k ~= "voxelSize" and k ~= "domainSize"
           and k ~= "smokeOnsetBezier" and k ~= "smokeDecayBezier" and k ~= "slipstreamBezier"
           and k ~= "activeSurfaceProfile" and k ~= "surfaceProfiles" and k ~= "surfaceParams" and k ~= "activeSimSurface" then
          setPhysicsParam(k, v)
        end
      end
      -- Deterministic Pass 2: Composite Bézier curves
      if p.smokeOnsetBezier then setPhysicsParam("smokeOnsetBezier", p.smokeOnsetBezier) end
      if p.smokeDecayBezier then setPhysicsParam("smokeDecayBezier", p.smokeDecayBezier) end
      if p.slipstreamBezier then setPhysicsParam("slipstreamBezier", p.slipstreamBezier) end
      -- Deterministic Pass 3: Per-surface isolated profiles ('asphalt' & 'sand')
      if type(p.surfaceProfiles) == "table" then
        applySurfaceProfilesTable(p.surfaceProfiles)
      elseif type(p.surfaceParams) == "table" then
        applySurfaceProfilesTable(p.surfaceParams)
      end
      isBatchUpdating = false
      notifyTireSync()
      if log then log("I", "realSmoke3DGE", "Loaded user settings from " .. SETTINGS_FILE_PATH) end
      return true
    end
  end
  return false
end

local function getSavedUiStateJson()
  if savedUiState and type(savedUiState) == "table" then
    local ok, encoded = pcall(jsonEncode, savedUiState)
    if ok and encoded then return encoded end
  end
  local ok, data = pcall(jsonReadFile, SETTINGS_FILE_PATH)
  if ok and type(data) == "table" then
    savedUiState = data
    local okEnc, encoded = pcall(jsonEncode, data)
    if okEnc and encoded then return encoded end
  end
  return "{}"
end

local function syncUiStateToLua(stateJson)
  if not stateJson then return false end
  local ok, dec = pcall(jsonDecode, stateJson)
  if ok and type(dec) == "table" then
    saveSettingsToDisk(dec)
    return true
  end
  return false
end

local function applyPreset(presetData)
  local data = presetData
  if type(data) == "string" then
    local ok, decoded = pcall(jsonDecode, data)
    if ok then
      data = decoded
      if type(data) == "string" then
        local ok2, decoded2 = pcall(jsonDecode, data)
        if ok2 and type(decoded2) == "table" then data = decoded2 end
      end
    end
  end
  if type(data) ~= "table" then return false end

  local p = data.params or data

  isBatchUpdating = true
  if p.activeSurfaceProfile ~= nil then
    setPhysicsParam("activeSurfaceProfile", p.activeSurfaceProfile)
  end
  if p.simulationQuality ~= nil then setSimulationQuality(p.simulationQuality) end
  if p.voxelMillimeters ~= nil then setVoxelSize(p.voxelMillimeters)
  elseif p.voxelSize ~= nil then
    local v = tonumber(p.voxelSize)
    if v and v < 1.0 then setVoxelSize(v * 1000) else setVoxelSize(v) end
  end
  if p.domainSize ~= nil then setDomainSize(p.domainSize) end

  -- Deterministic Pass 1: Apply all non-curve parameters first
  for k, v in pairs(p) do
    if k ~= "simulationQuality" and k ~= "voxelMillimeters" and k ~= "voxelSize" and k ~= "domainSize"
       and k ~= "smokeOnsetBezier" and k ~= "smokeDecayBezier" and k ~= "slipstreamBezier"
       and k ~= "activeSurfaceProfile" and k ~= "surfaceProfiles" and k ~= "surfaceParams" and k ~= "activeSimSurface" then
      setPhysicsParam(k, v)
    end
  end

  -- Deterministic Pass 2: Apply compound Bézier curves (superceding scalar thresholds)
  if p.smokeOnsetBezier then setPhysicsParam("smokeOnsetBezier", p.smokeOnsetBezier) end
  if p.smokeDecayBezier then setPhysicsParam("smokeDecayBezier", p.smokeDecayBezier) end
  if p.slipstreamBezier then setPhysicsParam("slipstreamBezier", p.slipstreamBezier) end

  -- Deterministic Pass 3: Enforce mute flags if provided in presetData
  local pe = data.paramEnabled
  if type(pe) == "table" then
    if pe.smokeDecay == false then
      userParams.smokeDecay = 0.0
      if userParams.smokeDecayBezier then userParams.smokeDecayBezier[1] = 0.0 end
    end
  end

  -- Deterministic Pass 4: Apply per-surface isolated parameter tables ('asphalt' & 'sand')
  if type(data.surfaceParams) == "table" then
    applySurfaceProfilesTable(data.surfaceParams)
  elseif type(p.surfaceProfiles) == "table" then
    applySurfaceProfilesTable(p.surfaceProfiles)
  elseif type(p.surfaceParams) == "table" then
    applySurfaceProfilesTable(p.surfaceParams)
  end

  isBatchUpdating = false
  notifyTireSync()
  saveSettingsToDisk(data)
  if log then log("I", "realSmoke3DGE", "Applied preset configuration") end
  return true
end

local function getUserParams()
  return userParams
end

local function getDebugPhysicsState()
  return userParams
end

M.applyPreset = applyPreset
M.saveSettingsToDisk = saveSettingsToDisk
M.loadSettingsFromDisk = loadSettingsFromDisk
M.getSavedUiStateJson = getSavedUiStateJson
M.syncUiStateToLua = syncUiStateToLua
M.getGridSpec = getGridSpec
M.sendUiTelemetry = sendUiTelemetry
M.setSimulationQuality = setSimulationQuality
M.getSimulationQuality = getSimulationQuality
M.setUnderbodyEject = setUnderbodyEject
M.setWakeShielding = setWakeShielding
M.setArchEject = setArchEject
M.setVorticityStrength = setVorticityStrength
M.setRoadDamping = setRoadDamping
M.setSmokeDrag = setSmokeDrag
M.setWakeSuction = setWakeSuction
M.setSlipstream = setSlipstream
M.setSlipstreamSpeedLimit = setSlipstreamSpeedLimit
M.setSlipstreamHoldTime = setSlipstreamHoldTime
M.setSlipstreamBezier = setSlipstreamBezier
M.setSlipstreamTurbScale = setSlipstreamTurbScale
M.setSlipstreamTurbStrength = setSlipstreamTurbStrength
M.setCoreLifetime = setCoreLifetime
M.setThermalBuoyancy = setThermalBuoyancy
M.setTreadSaturation = setTreadSaturation
M.setTreadCoupling = setTreadCoupling
M.setEdgeDispersion = setEdgeDispersion
M.setDispersionRate = setDispersionRate
M.setTreadTurbulence = setTreadTurbulence
M.setTurbScale1 = setTurbScale1
M.setTurbStrength1 = setTurbStrength1
M.setTurbScale2 = setTurbScale2
M.setTurbStrength2 = setTurbStrength2
M.setTurbTransition = setTurbTransition
M.setTurbRelax = setTurbRelax
M.setTurbArch = setTurbArch
M.setTurbArchScale = setTurbArchScale
M.setMicroFiber = setMicroFiber
M.setFiberScale = setFiberScale
M.setHazeNormals = setHazeNormals
M.setCreviceShadow = setCreviceShadow
M.setCoreOpacity = setCoreOpacity
M.setVorticityDetail = setVorticityDetail
M.setDebugWakeMode = setDebugWakeMode
M.setHeatThreshold = setHeatThreshold
M.setFrictionSens = setFrictionSens
M.setFrictionTime = setFrictionTime
M.setSmokeOnset = setSmokeOnset
M.setSmokeOnsetBezier = setSmokeOnsetBezier
M.setSmokeDecay = setSmokeDecay
M.setSmokeDecayBezier = setSmokeDecayBezier
M.setSandDustScale = setSandDustScale
M.setSandDustSens = setSandDustSens
M.setSandDustEnabled = setSandDustEnabled
M.setAsphaltSmokeEnabled = setAsphaltSmokeEnabled
M.setSmokeColor = setSmokeColor
M.setDustColor = setDustColor
M.setPhysicsParam = setPhysicsParam
M.resetPhysicsDefaults = resetPhysicsDefaults
M.setVoxelSize = setVoxelSize
M.getVoxelSize = getVoxelSize
M.setDomainSize = setDomainSize
M.getDomainSize = getDomainSize
M.getDebugPhysicsState = getDebugPhysicsState
M.getUserParams = getUserParams
M.setTireSyncCallback = function(cb) tireSyncCallback = cb end

-- Load persisted user settings from settings/realSmoke3D_settings.json
pcall(loadSettingsFromDisk)

return M
