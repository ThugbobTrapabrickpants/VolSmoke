-- ============================================================================
-- PROJECT: VolSmoke for BeamNG.drive.
-- COPYRIGHT (C) 2026 REALSMOKE 3D CONTRIBUTORS.
-- LICENSE: MIT (see LICENSE). Original project: https://github.com/ThugbobTrapabrickpants/VolSmoke
-- ============================================================================
-- VolSmoke game-engine bridge (Modular Dispatcher Facade).
-- Coordinates camera/world telemetry, submodules, and forwards per-wheel friction data.

local M = {}

local b = bit or bit32 or (type(require) == "function" and pcall(require, "bit") and require("bit"))
local telemetryProtocolVersion = 4
local provenanceBuildId = "v0.8.12.9-advanced-smoke-physics (baseline 0.8.12.9)"

-- Submodule Loader (compatible across all BeamNG filesystem modes and package paths)
local function loadSubmodule(moduleName)
  local paths = {
    "ge/extensions/realSmoke3D/" .. moduleName,
    "ge.extensions.realSmoke3D." .. moduleName,
    "lua/ge/extensions/realSmoke3D/" .. moduleName,
    "lua.ge.extensions.realSmoke3D." .. moduleName,
    "realSmoke3D/" .. moduleName,
  }
  for _, path in ipairs(paths) do
    local ok, mod = pcall(require, path)
    if ok and type(mod) == "table" then
      return mod
    end
  end
  if type(dofile) == "function" then
    local filePaths = {
      "lua/ge/extensions/realSmoke3D/" .. moduleName .. ".lua",
      "ge/extensions/realSmoke3D/" .. moduleName .. ".lua",
    }
    for _, fpath in ipairs(filePaths) do
      local ok, mod = pcall(dofile, fpath)
      if ok and type(mod) == "table" then
        return mod
      end
    end
  end
  error("CRITICAL: Failed to load VolSmoke submodule: " .. tostring(moduleName))
end

local diagnostics = loadSubmodule("diagnostics")
local uiBridge = loadSubmodule("uiBridge")
local replaySystem = loadSubmodule("replaySystem")
local networkBridge = loadSubmodule("networkBridge")
local telemetryReceiver = loadSubmodule("telemetryReceiver")

-- Bind tire parameter change notification from UI to vehicle Lua
uiBridge.setTireSyncCallback(function()
  telemetryReceiver.syncBurnoutEquityToVehicle(uiBridge.getUserParams())
end)

local activeVehicleId = -1
local updateCount = 0
local renderFrameId = 0
local lastError = nil
local uiTimer = 0

local function makeNativeWheelPayload(wheel)
  return telemetryReceiver.makeNativeWheelPayload(wheel)
end

local function sendUiTelemetry(uiWheels, totalEmission)
  uiBridge.sendUiTelemetry(uiWheels, totalEmission, diagnostics.getDiag())
end

function M.onVolSmokeWheelTelemetry(data)
  telemetryReceiver.onVolSmokeWheelTelemetry(data, activeVehicleId)
end

function M.onReplayStateChanged(state)
  replaySystem.onReplayStateChanged(state)
end

function M.onReplayCoreEvent(data)
  replaySystem.onReplayCoreEvent(data)
end

function M.onExtensionLoaded()
  networkBridge.initUDP()
  diagnostics.initHeartbeatReceiver()
  if log then log("I", "realSmoke3DGE", "Loaded " .. provenanceBuildId) end
end

function M.onExtensionUnloaded()
  replaySystem.finishReplayRecording(provenanceBuildId)
  telemetryReceiver.setFrameSynchronousWheelTelemetry(false, activeVehicleId)
  networkBridge.close()
  diagnostics.close()
end

function M.onVehicleSpawned(vehicleId)
  if vehicleId == nil or vehicleId == -1 or vehicleId == activeVehicleId then
    telemetryReceiver.resetVehicleState()
    replaySystem.requestReplayReset("vehicle spawned")
  end
end

function M.onVehicleReset(vehicleId)
  if vehicleId == nil or vehicleId == -1 or vehicleId == activeVehicleId then
    telemetryReceiver.resetVehicleState()
    replaySystem.requestReplayReset("vehicle reset")
  end
end

function M.onVehicleResetted(vehicleId)
  M.onVehicleReset(vehicleId)
end

function M.onReset()
  M.onVehicleReset(activeVehicleId)
end

function M.onVehicleSwitched(oldVehicleId, newVehicleId)
  activeVehicleId = newVehicleId or -1
  telemetryReceiver.resetVehicleState()
  replaySystem.requestReplayReset("vehicle switched")
end

function M.onUpdate(dtReal, dtSim)
  updateCount = updateCount + 1
  local ok, err = pcall(function()
    local dt = math.max(0, tonumber(dtReal) or tonumber(dtSim) or 0)
    telemetryReceiver.advanceTimers(dt)
    uiTimer = uiTimer + dt

    local vehicle = (type(getPlayerVehicle) == "function" and getPlayerVehicle(0)) or
                    (be and be:getPlayerVehicle(0))
    diagnostics.updateDiagnostics(vehicle ~= nil, telemetryReceiver.isParticleGuardActive())
    diagnostics.logDiagnosticState()

    local diagState = diagnostics.getDiag()
    if diagState.status == "FAULT" and diagState.code == "ERROR_VERSION_MISMATCH" then
      networkBridge.poisonAndClose()
      if vehicle and type(vehicle.queueLuaCommand) == "function" then
        vehicle:queueLuaCommand("if extensions.realSmoke3DVE then extensions.realSmoke3DVE.emergencyShutdown() end")
      end
      if uiTimer >= 0.1 then
        uiTimer = 0
        sendUiTelemetry(nil, 0)
      end
      return
    end

    if not vehicle then
      if uiTimer >= 0.1 then
        uiTimer = 0
        sendUiTelemetry(nil, 0)
      end
      return
    end

    local vehicleId = telemetryReceiver.getVehicleId(vehicle)
    if vehicleId ~= activeVehicleId then
      activeVehicleId = vehicleId
      telemetryReceiver.resetVehicleState()
      replaySystem.requestReplayReset("vehicle switched")
    end
    if telemetryReceiver.getVehicleLoadTimer() >= 2.0 then
      telemetryReceiver.requestVehicleExtension(vehicle, uiBridge.getUserParams())
      telemetryReceiver.setVehicleLoadTimer(0)
    end

    -- Wheel-node offsets are relative to the vehicle reference node. BeamNG's
    -- ordinary scene-object position jumps on its floating-origin grid, while
    -- the absolute reference-node position is maintained on the precise world grid.
    local pos = nil
    if type(vehicle.getRefNodeAbsPositionXYZ) == "function" then
      local okPos, x, y, z = pcall(function() return vehicle:getRefNodeAbsPositionXYZ() end)
      if okPos and x and y and z then pos = vec3(x, y, z) end
    end
    if not pos and type(vehicle.getPositionXYZ) == "function" then
      local x, y, z = vehicle:getPositionXYZ()
      if x and y and z then pos = vec3(x, y, z) end
    end
    if not pos then pos = vehicle:getPosition() end
    if not pos then return end

    local rawVelocity = vehicle:getVelocity() or vec3(0, 0, 0)
    local vel, velocityValid = telemetryReceiver.sanitizeVelocity(rawVelocity, 75.0)
    telemetryReceiver.setLastVehicleVelocityValid(velocityValid)
    if not velocityValid then telemetryReceiver.incVelocityRejectCount() end

    local direction = vehicle:getDirectionVector() or vec3(0, 1, 0)
    local up = (type(vehicle.getDirectionVectorUp) == "function" and vehicle:getDirectionVectorUp()) or vec3(0, 0, 1)
    local forward = vec3(direction.x or 0, direction.y or 1, direction.z or 0):normalized()
    local upVector = vec3(up.x or 0, up.y or 0, up.z or 1):normalized()
    local right = forward:cross(upVector):normalized()

    local isDiscontinuous = true
    local lastVehiclePos = telemetryReceiver.getLastVehiclePos()
    if lastVehiclePos then
      local dx = pos.x - lastVehiclePos.x
      local dy = pos.y - lastVehiclePos.y
      local dz = pos.z - lastVehiclePos.z
      local distSq = dx * dx + dy * dy + dz * dz
      isDiscontinuous = distSq > 25.0
      if distSq > 16.0 then
        replaySystem.requestReplayReset("teleport jump")
      end
    end
    telemetryReceiver.setLastVehiclePos(vec3(pos.x, pos.y, pos.z))

    local calculatedAngVel = vec3(0, 0, 0)
    local lastForwardVec = telemetryReceiver.getLastForwardVec()
    local lastUpVec = telemetryReceiver.getLastUpVec()
    if not isDiscontinuous and lastForwardVec and lastUpVec and dtSim > 0.001 and dtSim < 0.25 then
      local df = (forward - lastForwardVec) / dtSim
      local du = (upVector - lastUpVec) / dtSim
      local w1 = forward:cross(df)
      local w2 = upVector:cross(du)
      calculatedAngVel = telemetryReceiver.sanitizeAngularVelocity((w1 + w2) * 0.5, 35.0)
    end
    telemetryReceiver.setCalculatedAngVel(calculatedAngVel)
    telemetryReceiver.setLastForwardVec(vec3(forward.x, forward.y, forward.z))
    telemetryReceiver.setLastUpVec(vec3(upVector.x, upVector.y, upVector.z))

    local bodyCenter, bodyRight, bodyForward, bodyUp, bodyHalf = pos, right, forward, upVector, vec3(0, 0, 0)
    local bodyColliderValid = false
    if type(vehicle.getSpawnWorldOOBB) == "function" then
      local okBody, box = pcall(function() return vehicle:getSpawnWorldOOBB() end)
      if okBody and box then
        local center = box:getCenter()
        local half = box:getHalfExtents()
        local axis0, axis1, axis2 = box:getAxis(0), box:getAxis(1), box:getAxis(2)
        if center and half and axis0 and axis1 and axis2 and half.x > 0.1 and half.y > 0.1 and half.z > 0.1 then
          local a0, a1, a2 = axis0:normalized(), axis1:normalized(), axis2:normalized()
          if a1:dot(forward) < 0 then a1 = -a1 end
          if a0:dot(right) < 0 then a0 = -a0 end
          if a2:dot(upVector) < 0 then a2 = -a2 end
          bodyCenter, bodyHalf = center, half
          bodyRight, bodyForward, bodyUp = a0, a1, a2
          bodyColliderValid = true
        end
      end
    end
    telemetryReceiver.setBodyColliderValid(bodyColliderValid)

    local fallback = {
      FL = {x = -0.82, y =  1.25, z = -0.45},
      FR = {x =  0.82, y =  1.25, z = -0.45},
      RL = {x = -0.82, y = -1.25, z = -0.45},
      RR = {x =  0.82, y = -1.25, z = -0.45}
    }
    local fresh = telemetryReceiver.getWheelTelemetryAge() <= 0.60 and
                  telemetryReceiver.getWheelTelemetry() and
                  telemetryReceiver.getWheelTelemetry().vehicleId == activeVehicleId
    local wheelData = {}
    local nativeWheelData = {}
    local uiWheels = {}
    local emissionSum = 0
    local geomCount = 0
    local normCount = 0
    local contactCount = 0

    local wheelNames = {"FL", "FR", "RL", "RR"}
    local telemetryByName = {}
    local worldPositionByName = {}
    local contactPositionByName = {}
    for _, name in ipairs(wheelNames) do
      local telemetry = fresh and telemetryReceiver.wheelByName(name) or nil
      local worldPos = nil
      if telemetry and telemetry.worldOffset then
        worldPos = pos + vec3(telemetry.worldOffset.x, telemetry.worldOffset.y, telemetry.worldOffset.z)
      else
        local localPos = fallback[name]
        worldPos = pos + right * localPos.x + forward * localPos.y + upVector * localPos.z
      end
      telemetryByName[name] = telemetry
      worldPositionByName[name] = worldPos
      if telemetry and telemetry.contactOffset then
        contactPositionByName[name] = pos + vec3(telemetry.contactOffset.x, telemetry.contactOffset.y, telemetry.contactOffset.z)
      else
        contactPositionByName[name] = worldPos
      end
    end

    if bodyColliderValid then
      local maxWheelLat = 0
      for _, name in ipairs(wheelNames) do
        local wpos = worldPositionByName[name]
        if wpos then
          local lat = math.abs((wpos - bodyCenter):dot(bodyRight))
          if lat > maxWheelLat then maxWheelLat = lat end
        end
      end
      local fenderHalfWidth = maxWheelLat + 0.12
      if fenderHalfWidth > 0.4 and bodyHalf.x > fenderHalfWidth + 0.03 then
        bodyHalf = vec3(fenderHalfWidth, bodyHalf.y, bodyHalf.z)
      end
    end
    telemetryReceiver.setLastBodyHalfExtents({bodyHalf.x, bodyHalf.y, bodyHalf.z})

    local supportNormal = upVector
    local supportNormalValid = false
    if telemetryByName.FL and telemetryByName.FR and telemetryByName.RL and telemetryByName.RR then
      local frontCenter = (contactPositionByName.FL + contactPositionByName.FR) * 0.5
      local rearCenter = (contactPositionByName.RL + contactPositionByName.RR) * 0.5
      local leftCenter = (contactPositionByName.FL + contactPositionByName.RL) * 0.5
      local rightCenter = (contactPositionByName.FR + contactPositionByName.RR) * 0.5
      local longitudinal = frontCenter - rearCenter
      local lateral = rightCenter - leftCenter
      local planeNormal = longitudinal:cross(lateral)
      if planeNormal:length() > 0.0001 then
        planeNormal = planeNormal:normalized()
        if planeNormal:dot(upVector) < 0 then planeNormal = planeNormal * -1 end
        supportNormal = planeNormal
        supportNormalValid = true
      end
    end

    local smokeSum = 0
    local dustSum = 0
    for _, name in ipairs(wheelNames) do
      local telemetry = telemetryByName[name]
      local wheel = telemetryReceiver.makeWheel(worldPositionByName[name], telemetry, pos, vel, supportNormal, supportNormalValid)
      wheelData[#wheelData + 1] = wheel
      nativeWheelData[#nativeWheelData + 1] = makeNativeWheelPayload(wheel)
      if wheel.geometryValid then geomCount = geomCount + 1 end
      if wheel.normalValid then normCount = normCount + 1 end
      if wheel.sourceValid then contactCount = contactCount + 1 end
      emissionSum = emissionSum + wheel.emit
      smokeSum = smokeSum + (tonumber(wheel.emitSmoke) or 0)
      dustSum = dustSum + (tonumber(wheel.emitDust) or 0)
      uiWheels[name] = {
        slip = telemetry and (tonumber(telemetry.slip) or 0) or 0,
        temperature = wheel.temperature,
        contactPatchTemperature = wheel.contactPatchTemperature,
        emission = wheel.emit
      }
    end
    local up = uiBridge.getUserParams()
    if up then
      if dustSum > smokeSum and dustSum > 0.005 then
        up.activeSimSurface = "sand"
      elseif smokeSum > dustSum and smokeSum > 0.005 then
        up.activeSimSurface = "asphalt"
      end
    end
    telemetryReceiver.setGeometryValidCount(geomCount)
    telemetryReceiver.setNormalValidCount(normCount)
    telemetryReceiver.setContactSourceCount(contactCount)

    local liveVehicleSnapshot = {
      pos = pos,
      vel = vel,
      bodyCenter = bodyCenter,
      bodyRight = bodyRight,
      bodyForward = bodyForward,
      bodyUp = bodyUp,
      bodyHalf = bodyHalf,
      angVel = calculatedAngVel,
      bodyValid = bodyColliderValid,
      profile = telemetryReceiver.getVehicleProfile()
    }

    local rState = replaySystem.getReplayState()
    if rState.state == "recording" then
      replaySystem.captureReplayFrame(nativeWheelData, liveVehicleSnapshot)
    elseif rState.state == "playback" then
      local replayWheels = replaySystem.sampledReplayWheels(replaySystem.replayTime(rState), pos)
      emissionSum = 0
      for index, name in ipairs(wheelNames) do
        if replayWheels then
          nativeWheelData[index] = replayWheels[index]
        else
          nativeWheelData[index].emit = 0
        end
        local replayEmission = tonumber(nativeWheelData[index].emit) or 0
        emissionSum = emissionSum + replayEmission
        uiWheels[name].emission = replayEmission
      end
    end

    local totalEmission = telemetryReceiver.clamp01(emissionSum * 0.5)

    telemetryReceiver.setLastTelemetrySnapshot({
      protocolVersion = telemetryReceiver.getLastWheelProtocolVersion(),
      sourceMode = contactCount == #wheelData and "contactPatch" or "mixedFallback",
      supportNormal = {supportNormal.x, supportNormal.y, supportNormal.z},
      supportNormalValid = supportNormalValid,
      wheels = wheelData
    })

    local outbound = liveVehicleSnapshot
    local outboundWheels = nativeWheelData
    local finishWarmup = false
    local resumeAfterWarmup = false
    local playback = replaySystem.getPlayback()
    if rState.state == "playback" and playback and playback.warmup then
      local warmup = playback.warmup
      if not warmup.anchorOffset then
        local recordedTarget = replaySystem.sampledReplayVehicle(warmup.targetTime, vec3(0, 0, 0))
        if recordedTarget then warmup.anchorOffset = pos - recordedTarget.pos end
      end
      local sampleTime = math.min(warmup.nextTime, warmup.targetTime)
      local historical = replaySystem.sampledReplayVehicle(sampleTime, warmup.anchorOffset)
      if historical then
        outbound = historical
        outboundWheels = historical.wheels
      end
      if sampleTime >= warmup.targetTime - 0.0001 then
        finishWarmup = true
        resumeAfterWarmup = warmup.resumeAfter == true
      else
        warmup.nextTime = sampleTime + replaySystem.replaySampleInterval
      end
    end

    networkBridge.sendVehicleTelemetry(activeVehicleId, outbound, outboundWheels, velocityValid)

    if finishWarmup and playback and playback.warmup then
      playback.warmup = nil
      replaySystem.setWarmupActive(false)
      if resumeAfterWarmup and core_replay and core_replay.pause then
        pcall(function() core_replay.pause(false) end)
      end
      if log then log("I", "realSmoke3DGE.replay", "Replay smoke warmup completed") end
    end

    if uiTimer >= 0.1 then
      uiTimer = 0
      sendUiTelemetry(uiWheels, totalEmission)
    end
  end)

  if ok then
    lastError = nil
  else
    lastError = tostring(err)
    if log then log("E", "realSmoke3DGE", lastError) end
  end
end

function M.onPreRender(dtReal, dtSim, dtRaw)
  renderFrameId = renderFrameId + 1
  replaySystem.onPreRender(dtReal, dtSim)
  pcall(function()
    telemetryReceiver.updateWheelTelemetryCadence(dtReal, dtSim, activeVehicleId)
  end)
  pcall(function()
    networkBridge.sendEnvironmentTelemetry(
      dtReal,
      dtSim,
      uiBridge.getUserParams(),
      renderFrameId,
      replaySystem.getResetSequence(),
      replaySystem.isWarmupActive(),
      activeVehicleId
    )
  end)
end

-- UI Tuning Interface delegation to uiBridge
function M.setSimulationQuality(val) uiBridge.setSimulationQuality(val) end
function M.getSimulationQuality() return uiBridge.getSimulationQuality() end
function M.setUnderbodyEject(val) uiBridge.setUnderbodyEject(val) end
function M.setWakeShielding(val) uiBridge.setWakeShielding(val) end
function M.setArchEject(val) uiBridge.setArchEject(val) end
function M.setVorticityStrength(val) uiBridge.setVorticityStrength(val) end
function M.setRoadDamping(val) uiBridge.setRoadDamping(val) end
function M.setSmokeDrag(val) uiBridge.setSmokeDrag(val) end
function M.setWakeSuction(val) uiBridge.setWakeSuction(val) end
function M.setSlipstream(val) uiBridge.setSlipstream(val) end
function M.setSlipstreamSpeedLimit(val) uiBridge.setSlipstreamSpeedLimit(val) end
function M.setSlipstreamHoldTime(val) uiBridge.setSlipstreamHoldTime(val) end
function M.setSlipstreamBezier(...) uiBridge.setSlipstreamBezier(...) end
function M.setSlipstreamTurbScale(val) uiBridge.setSlipstreamTurbScale(val) end
function M.setSlipstreamTurbStrength(val) uiBridge.setSlipstreamTurbStrength(val) end
function M.setCoreLifetime(val) uiBridge.setCoreLifetime(val) end
function M.setThermalBuoyancy(val) uiBridge.setThermalBuoyancy(val) end
function M.setTreadSaturation(val) uiBridge.setTreadSaturation(val) end
function M.setTreadCoupling(val) uiBridge.setTreadCoupling(val) end
function M.setEdgeDispersion(val) uiBridge.setEdgeDispersion(val) end
function M.setDispersionRate(val) uiBridge.setDispersionRate(val) end
function M.setTreadTurbulence(val) uiBridge.setTreadTurbulence(val) end
function M.setTurbScale1(val) uiBridge.setTurbScale1(val) end
function M.setTurbStrength1(val) uiBridge.setTurbStrength1(val) end
function M.setTurbScale2(val) uiBridge.setTurbScale2(val) end
function M.setTurbStrength2(val) uiBridge.setTurbStrength2(val) end
function M.setTurbTransition(val) uiBridge.setTurbTransition(val) end
function M.setTurbRelax(val) uiBridge.setTurbRelax(val) end
function M.setTurbArch(val) uiBridge.setTurbArch(val) end
function M.setTurbArchScale(val) uiBridge.setTurbArchScale(val) end
function M.setMicroFiber(val) uiBridge.setMicroFiber(val) end
function M.setFiberScale(val) uiBridge.setFiberScale(val) end
function M.setHazeNormals(val) uiBridge.setHazeNormals(val) end
function M.setCreviceShadow(val) uiBridge.setCreviceShadow(val) end
function M.setCoreOpacity(val) uiBridge.setCoreOpacity(val) end
function M.setVorticityDetail(val) uiBridge.setVorticityDetail(val) end
function M.setDebugWakeMode(val) uiBridge.setDebugWakeMode(val) end
function M.setHeatThreshold(val) uiBridge.setHeatThreshold(val) end
function M.setFrictionSens(val) uiBridge.setFrictionSens(val) end
function M.setFrictionTime(val) uiBridge.setFrictionTime(val) end
function M.setSmokeOnset(val) uiBridge.setSmokeOnset(val) end
function M.setSmokeOnsetBezier(...) uiBridge.setSmokeOnsetBezier(...) end
function M.setSmokeDecay(val) uiBridge.setSmokeDecay(val) end
function M.setSmokeDecayBezier(...) uiBridge.setSmokeDecayBezier(...) end
function M.setSandDustScale(val) uiBridge.setSandDustScale(val) end
function M.setSandDustSens(val) uiBridge.setSandDustSens(val) end
function M.setSandDustEnabled(val) uiBridge.setSandDustEnabled(val) end
function M.setAsphaltSmokeEnabled(val) uiBridge.setAsphaltSmokeEnabled(val) end
function M.setPhysicsParam(param, ...) uiBridge.setPhysicsParam(param, ...) end
function M.resetPhysicsDefaults() uiBridge.resetPhysicsDefaults() end
function M.setVoxelSize(size) uiBridge.setVoxelSize(size) end
function M.getVoxelSize() return uiBridge.getVoxelSize() end
function M.setDomainSize(size) uiBridge.setDomainSize(size) end
function M.getDomainSize() return uiBridge.getDomainSize() end
function M.applyPreset(presetData) return uiBridge.applyPreset(presetData) end
function M.saveSettingsToDisk(uiPayload) return uiBridge.saveSettingsToDisk(uiPayload) end
function M.loadSettingsFromDisk() return uiBridge.loadSettingsFromDisk() end
function M.getSavedSettingsJson() return uiBridge.getSavedUiStateJson() end
function M.syncUiStateToLua(stateJson) return uiBridge.syncUiStateToLua(stateJson) end

function M.getTelemetrySnapshot()
  return telemetryReceiver.getLastTelemetrySnapshot()
end

function M.getDebugState()
  local gridWidth, gridHeight, gridDepth = uiBridge.getGridSpec()
  local rState = replaySystem.getReplayState()
  local recording = replaySystem.getRecording()
  local playback = replaySystem.getPlayback()
  local d = diagnostics.getDiag()
  local userParams = uiBridge.getUserParams()

  local state = {
    updateCount = updateCount,
    activeVehicleId = activeVehicleId,
    telemetryProtocolVersion = telemetryProtocolVersion,
    renderFrameId = renderFrameId,
    replayState = rState.state,
    replayFile = rState.loadedFile,
    replayTime = replaySystem.replayTime(rState),
    replayResetSequence = replaySystem.getResetSequence(),
    replayRecordingFrames = recording and #recording.frames or 0,
    replayPlaybackFrames = playback and #playback.frames or 0,
    replaySidecarVersion = playback and playback.version or nil,
    replayWarmupActive = replaySystem.isWarmupActive(),
    replaySidecar = playback and playback.sidecar or nil,
    replayLastError = replaySystem.getLastError(),
    frameSynchronousWheelTelemetry = telemetryReceiver.isFrameSynchronous(),
    provenanceBuildId = provenanceBuildId,
    vehicleProvenanceBuildId = telemetryReceiver.getLastVehicleProvenanceBuildId(),
    lastWheelProtocolVersion = telemetryReceiver.getLastWheelProtocolVersion(),
    geometryValidCount = telemetryReceiver.getGeometryValidCount(),
    normalValidCount = telemetryReceiver.getNormalValidCount(),
    contactSourceCount = telemetryReceiver.getContactSourceCount(),
    velocityRejectCount = telemetryReceiver.getVelocityRejectCount(),
    lastVehicleVelocityValid = telemetryReceiver.getLastVehicleVelocityValid(),
    bodyColliderValid = telemetryReceiver.isBodyColliderValid(),
    bodyHalfExtents = telemetryReceiver.getLastBodyHalfExtents(),
    wheelTelemetryAge = telemetryReceiver.getWheelTelemetryAge(),
    hasWheelTelemetry = telemetryReceiver.getWheelTelemetry() ~= nil,
    udpReady = networkBridge.isUdpReady(),
    gridWidth = gridWidth,
    gridHeight = gridHeight,
    gridDepth = gridDepth,
    domainX = gridWidth * userParams.voxelSize,
    domainY = gridHeight * userParams.voxelSize,
    domainZ = gridDepth * userParams.voxelSize,
    lastError = lastError,
    lastVehicleSend = networkBridge.getLastVehicleSend(),
    lastVehicleSendError = networkBridge.getLastVehicleSendError(),
    lastEnvironmentSend = networkBridge.getLastEnvironmentSend(),
    lastEnvironmentSendError = networkBridge.getLastEnvironmentSendError(),
    diagStatus = d.status,
    diagCode = d.code,
    diagApi = d.api,
    diagFrames = d.frames,
    diagDepthOk = d.depthOk,
    diagLastHeartbeat = d.lastHeartbeatTime
  }
  for k, v in pairs(uiBridge.getDebugPhysicsState()) do
    state[k] = v
  end
  return state
end

extensions = extensions or {}
extensions.realSmoke3DGE = M
rawset(_G, "realSmoke3DGE", M)
rawset(_G, "setRealSmokeVoxelSize", function(size) return M.setVoxelSize(size) end)
rawset(_G, "setRealSmokeDomainSize", function(size) return M.setDomainSize(size) end)
rawset(_G, "setRealSmokePhysicsParam", function(param, val) return M.setPhysicsParam(param, val) end)
rawset(_G, "resetRealSmokePhysicsDefaults", function() return M.resetPhysicsDefaults() end)
rawset(_G, "setRealSmokeSimulationQuality", function(val) return M.setSimulationQuality(val) end)
rawset(_G, "applyRealSmokePreset", function(presetData) return M.applyPreset(presetData) end)
rawset(_G, "syncRealSmokeUiStateToLua", function(stateJson) return M.syncUiStateToLua(stateJson) end)
rawset(_G, "getSavedRealSmokeUiStateJson", function() return M.getSavedSettingsJson() end)
rawset(_G, "saveRealSmokeSettingsToDisk", function(uiPayload) return M.saveSettingsToDisk(uiPayload) end)

return M
