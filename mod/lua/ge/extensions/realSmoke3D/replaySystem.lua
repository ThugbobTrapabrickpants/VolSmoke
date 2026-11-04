-- ============================================================================
-- PROJECT: VolSmoke for BeamNG.drive.
-- COPYRIGHT (C) 2026 REALSMOKE 3D CONTRIBUTORS.
-- LICENSE: MIT (see LICENSE). Original project: https://github.com/ThugbobTrapabrickpants/VolSmoke
-- ============================================================================
-- VolSmoke Replay System Submodule.
-- Owns trajectory recording to .realsmoke3d.json sidecars, sampled playback, and 3s fluid warmup.

local M = {}

local replaySidecarVersion = 2
local replaySampleInterval = 0.05
local replayMaximumFrames = 150000
local replayWarmupWindow = 3.0
local replayState = {state = "inactive", loadedFile = "", positionSeconds = 0, framePositionSeconds = 0}
local replayResetSequence = 0
local replayRecording = nil
local replayPlayback = nil
local replayLastTime = nil
local replayLastError = nil
local replayWarmupActive = false

local function clamp01(value)
  return math.max(0, math.min(1, tonumber(value) or 0))
end

local function replayTime(state)
  if type(state) ~= "table" then return 0 end
  -- positionSeconds is BeamNG's interpolated playback clock. The legacy Replay
  -- UI explicitly labels framePositionSeconds as "without interpolation"; using
  -- that stepped clock makes the entire smoke domain visibly judder.
  return math.max(0, tonumber(state.positionSeconds) or tonumber(state.framePositionSeconds) or 0)
end

local function validReplayPath(path)
  if type(path) ~= "string" then return nil end
  local normalized = string.gsub(path, "\\", "/")
  if string.sub(normalized, 1, 8) ~= "replays/" or
     string.sub(normalized, -4) ~= ".rpl" or
     string.find(normalized, "..", 1, true) then return nil end
  return normalized
end

local function replaySidecarPath(path)
  local replayPath = validReplayPath(path)
  return replayPath and (replayPath .. ".realsmoke3d.json") or nil
end

local function requestReplayReset(reason)
  replayResetSequence = replayResetSequence + 1
  if log then log("I", "realSmoke3DGE.replay", "Fluid reset requested: " .. tostring(reason)) end
end

local function compactReplayWheel(wheel, vehiclePos)
  local forward = wheel.forward or {0, 1, 0}
  local hub = wheel.hub or {wheel.x, wheel.y, wheel.z}
  local hubVel = wheel.hubVel or {0, 0, 0}
  return {
    wheel.x - vehiclePos.x, wheel.y - vehiclePos.y, wheel.z - vehiclePos.z,
    wheel.emit, forward[1], forward[2], forward[3], wheel.omega,
    wheel.rollingOmega, wheel.wheelDir, wheel.radius,
    hub[1] - vehiclePos.x, hub[2] - vehiclePos.y, hub[3] - vehiclePos.z,
    hubVel[1], hubVel[2], hubVel[3],
    wheel.emitSmoke or wheel.emit or 0,
    wheel.emitDust or 0,
    wheel.dustTint or 0
  }
end

local function compactReplayVehicle(vehicle)
  local pos = vehicle.pos
  local center = vehicle.bodyCenter
  return {
    pos.x, pos.y, pos.z,
    vehicle.vel.x, vehicle.vel.y, vehicle.vel.z,
    center.x - pos.x, center.y - pos.y, center.z - pos.z,
    vehicle.bodyRight.x, vehicle.bodyRight.y, vehicle.bodyRight.z,
    vehicle.bodyForward.x, vehicle.bodyForward.y, vehicle.bodyForward.z,
    vehicle.bodyUp.x, vehicle.bodyUp.y, vehicle.bodyUp.z,
    vehicle.bodyHalf.x, vehicle.bodyHalf.y, vehicle.bodyHalf.z,
    vehicle.angVel.x, vehicle.angVel.y, vehicle.angVel.z,
    vehicle.bodyValid and 1 or 0
  }
end

local function replayFrameIsValid(frame, version)
  local wheelSlot = version >= 2 and 3 or 2
  if type(frame) ~= "table" or type(frame[1]) ~= "number" or type(frame[wheelSlot]) ~= "table" then return false end
  if frame[1] < 0 or frame[1] > 86400 then return false end
  if version >= 2 then
    if type(frame[2]) ~= "table" or #frame[2] < 25 then return false end
    for valueIndex = 1, 25 do
      local value = tonumber(frame[2][valueIndex])
      if not value or value ~= value or math.abs(value) >= math.huge or math.abs(value) > 1.0e7 then return false end
    end
    if frame[2][25] ~= 0 and frame[2][25] ~= 1 then return false end
  end
  for wheelIndex = 1, 4 do
    local wheel = frame[wheelSlot][wheelIndex]
    if type(wheel) ~= "table" or #wheel < 17 then return false end
    local maxCheck = math.min(#wheel, 20)
    for valueIndex = 1, maxCheck do
      local value = tonumber(wheel[valueIndex])
      if not value or value ~= value or math.abs(value) >= math.huge then return false end
    end
    if wheel[4] < 0 or wheel[4] > 1 or wheel[11] < 0.05 or wheel[11] > 5 then return false end
  end
  return true
end

local function captureReplayFrame(nativeWheels, vehicle)
  if not replayRecording or replayState.state ~= "recording" then return end
  if #replayRecording.frames >= replayMaximumFrames then
    if not replayRecording.truncated then
      replayRecording.truncated = true
      replayLastError = "Smoke sidecar reached its bounded frame limit"
      if log then log("E", "realSmoke3DGE.replay", replayLastError) end
    end
    return
  end
  local time = replayTime(replayState)
  if replayRecording.lastSampleTime and time - replayRecording.lastSampleTime < replaySampleInterval - 0.005 then return end

  local compactWheels = {}
  for index = 1, math.min(4, #nativeWheels) do
    compactWheels[index] = compactReplayWheel(nativeWheels[index], vehicle.pos)
  end
  if #compactWheels ~= 4 then return end

  replayRecording.frames[#replayRecording.frames + 1] = {time, compactReplayVehicle(vehicle), compactWheels}
  replayRecording.lastSampleTime = time
end

local function beginReplayRecording(path)
  local replayPath = validReplayPath(path)
  if not replayPath then
    replayLastError = "Replay recording supplied an invalid path"
    return
  end
  replayRecording = {
    replayFile = replayPath,
    frames = {},
    lastSampleTime = nil,
    wasActive = false
  }
  replayLastError = nil
  if log then log("I", "realSmoke3DGE.replay", "Recording smoke sidecar for " .. replayPath) end
end

local function finishReplayRecording(provenanceBuildId)
  local recording = replayRecording
  replayRecording = nil
  if not recording or not FS or not FS:fileExists(recording.replayFile) then return end

  local sidecar = replaySidecarPath(recording.replayFile)
  if not sidecar then return end
  local temporary = sidecar .. ".tmp"
  local payload = {
    format = "VolSmokeReplay",
    version = replaySidecarVersion,
    provenanceBuildId = provenanceBuildId or "v0.8.13-surface-anchored-lattice",
    replayFile = recording.replayFile,
    replayFileSize = FS:fileSize(recording.replayFile),
    sampleInterval = replaySampleInterval,
    truncated = recording.truncated == true,
    frames = recording.frames
  }

  local ok, result = pcall(jsonWriteFile, temporary, payload, false, 5)
  if not ok or not result then
    replayLastError = "Failed to write smoke sidecar: " .. tostring(result)
    if log then log("E", "realSmoke3DGE.replay", replayLastError) end
    return
  end
  if FS:fileExists(sidecar) then FS:removeFile(sidecar) end
  if FS:renameFile(temporary, sidecar) ~= 0 then
    FS:removeFile(temporary)
    replayLastError = "Failed to finalize smoke sidecar: " .. sidecar
    if log then log("E", "realSmoke3DGE.replay", replayLastError) end
    return
  end
  replayLastError = nil
  if log then
    log("I", "realSmoke3DGE.replay", string.format("Saved %d smoke frames to %s", #recording.frames, sidecar))
  end
end

local function loadReplayPlayback(path)
  replayPlayback = nil
  local replayPath = validReplayPath(path)
  local sidecar = replaySidecarPath(replayPath)
  if not sidecar or not FS or not FS:fileExists(sidecar) then
    replayLastError = "No RealSmoke sidecar for this replay"
    if log then log("W", "realSmoke3DGE.replay", replayLastError .. ": " .. tostring(path)) end
    return
  end
  local size = tonumber(FS:fileSize(sidecar)) or 0
  if size <= 0 or size > 128 * 1024 * 1024 then
    replayLastError = "Smoke sidecar has an invalid size"
    return
  end

  local ok, payload = pcall(jsonReadFile, sidecar)
  local version = ok and type(payload) == "table" and tonumber(payload.version) or nil
  if not ok or type(payload) ~= "table" or payload.format ~= "VolSmokeReplay" or
     (version ~= 1 and version ~= replaySidecarVersion) or type(payload.frames) ~= "table" or
     #payload.frames > replayMaximumFrames then
    replayLastError = "Smoke sidecar is malformed or unsupported"
    if log then log("E", "realSmoke3DGE.replay", replayLastError .. ": " .. sidecar) end
    return
  end
  if FS:fileExists(replayPath) and tonumber(payload.replayFileSize) ~= tonumber(FS:fileSize(replayPath)) then
    replayLastError = "Smoke sidecar does not match the replay file"
    if log then log("E", "realSmoke3DGE.replay", replayLastError .. ": " .. sidecar) end
    return
  end
  local previousTime = -1
  for _, frame in ipairs(payload.frames) do
    if not replayFrameIsValid(frame, version) or frame[1] < previousTime then
      replayLastError = "Smoke sidecar contains invalid frame data"
      if log then log("E", "realSmoke3DGE.replay", replayLastError .. ": " .. sidecar) end
      return
    end
    previousTime = frame[1]
  end
  replayPlayback = {
    frames = payload.frames,
    version = version,
    cursor = 1,
    sidecar = sidecar,
    replayPath = replayPath,
    warmup = nil
  }
  replayLastError = nil
  if log then log("I", "realSmoke3DGE.replay", string.format("Loaded %d smoke frames from %s", #payload.frames, sidecar)) end
end

local function lerpReplayValue(a, b, alpha)
  return a + (b - a) * alpha
end

local function replayFramePair(time)
  local playback = replayPlayback
  if not playback or #playback.frames == 0 then return nil end
  local frames = playback.frames
  local low, high = 1, #frames
  while low <= high do
    local middle = math.floor((low + high) * 0.5)
    if frames[middle][1] <= time then low = middle + 1 else high = middle - 1 end
  end
  local beforeIndex = math.max(1, high)
  local afterIndex = math.min(#frames, beforeIndex + 1)
  local before, after = frames[beforeIndex], frames[afterIndex]
  local alpha = 0
  if after[1] > before[1] then alpha = math.max(0, math.min(1, (time - before[1]) / (after[1] - before[1]))) end
  return before, after, alpha
end

local function sampledReplayWheels(time, vehiclePos)
  local playback = replayPlayback
  if not playback or #playback.frames == 0 then return nil end
  local before, after, alpha = replayFramePair(time)
  if not before or not after then return nil end
  if time < before[1] - 0.075 or time > after[1] + 0.075 then return nil end
  local gap = after[1] - before[1]
  if gap > replaySampleInterval * 2.5 then
    if math.abs(time - before[1]) <= 0.075 then after = before
    elseif math.abs(time - after[1]) <= 0.075 then before = after
    else return nil end
  end

  local wheelSlot = playback.version >= 2 and 3 or 2
  local result = {}
  local terrain = (core_terrain and type(core_terrain.getTerrain) == "function" and core_terrain.getTerrain()) or
                  (scenetree and type(scenetree.findObject) == "function" and scenetree.findObject("terrain")) or nil
  local terrainQueryPos = vec3(0, 0, 0)

  for wheelIndex = 1, 4 do
    local a, b = before[wheelSlot][wheelIndex], after[wheelSlot][wheelIndex]
    local v = {}
    local len = math.min(#a, #b)
    for valueIndex = 1, math.min(17, len) do v[valueIndex] = lerpReplayValue(a[valueIndex], b[valueIndex], alpha) end
    local emit = clamp01(v[4])
    local emitSmoke = (len >= 18) and clamp01(lerpReplayValue(a[18], b[18], alpha)) or emit
    local emitDust = (len >= 19) and clamp01(lerpReplayValue(a[19], b[19], alpha)) or 0
    local dustTint = (len >= 20) and (alpha < 0.5 and a[20] or b[20]) or 0

    local wx = vehiclePos.x + v[1]
    local wy = vehiclePos.y + v[2]
    local wz = vehiclePos.z + v[3]

    -- Dynamic terrain fallback: If replay lacks dustTint or has emitDust == 0 on granular ground, query terrain
    if emit > 0 and emitDust <= 0.001 and dustTint == 0 and terrain and type(terrain.getMaterialIdxWs) == "function" and type(terrain.getMaterialName) == "function" then
      terrainQueryPos:set(wx, wy, 0)
      local ok, matIdx = pcall(function() return terrain:getMaterialIdxWs(terrainQueryPos) end)
      if ok and matIdx then
        local okName, name = pcall(function() return terrain:getMaterialName(matIdx) end)
        if okName and name then
          local lowerName = string.lower(tostring(name))
          if string.find(lowerName, "sand", 1, true) then
            dustTint = 1
            emitDust = emit
            emitSmoke = 0
          elseif string.find(lowerName, "dirt", 1, true) or string.find(lowerName, "mud", 1, true) or string.find(lowerName, "soil", 1, true) then
            dustTint = 2
            emitDust = emit
            emitSmoke = 0
          elseif string.find(lowerName, "gravel", 1, true) or string.find(lowerName, "rock", 1, true) then
            dustTint = 3
            emitDust = emit
            emitSmoke = 0
          end
        end
      end
    end

    result[wheelIndex] = {
      x = wx, y = wy, z = wz,
      emit = emit,
      emitSmoke = emitSmoke,
      emitDust = emitDust,
      dustTint = dustTint,
      forward = {v[5], v[6], v[7]}, omega = v[8], rollingOmega = v[9],
      wheelDir = alpha < 0.5 and a[10] or b[10], radius = v[11],
      hub = {vehiclePos.x + v[12], vehiclePos.y + v[13], vehiclePos.z + v[14]},
      hubVel = {v[15], v[16], v[17]}
    }
  end
  return result
end

local function scheduleReplayWarmup(targetTime)
  local playback = replayPlayback
  if not playback or playback.version < 2 or #playback.frames == 0 then
    replayWarmupActive = false
    return
  end
  local firstTime = playback.frames[1][1]
  local target = math.max(firstTime, tonumber(targetTime) or firstTime)
  playback.warmup = {
    nextTime = math.max(firstTime, target - replayWarmupWindow),
    targetTime = target,
    anchorOffset = nil,
    resumeAfter = replayState.paused ~= true
  }
  replayWarmupActive = true
  if core_replay and core_replay.pause then pcall(function() core_replay.pause(true) end) end
end

local function sampledReplayVehicle(time, anchorOffset)
  local playback = replayPlayback
  if not playback or playback.version < 2 then return nil end
  local before, after, alpha = replayFramePair(time)
  if not before then return nil end
  local a, b = before[2], after[2]
  local v = {}
  for valueIndex = 1, 24 do v[valueIndex] = lerpReplayValue(a[valueIndex], b[valueIndex], alpha) end
  local offset = anchorOffset or vec3(0, 0, 0)
  local pos = vec3(v[1] + offset.x, v[2] + offset.y, v[3] + offset.z)
  local wheels = {}
  for wheelIndex = 1, 4 do
    local wa, wb = before[3][wheelIndex], after[3][wheelIndex]
    local w = {}
    for valueIndex = 1, 17 do w[valueIndex] = lerpReplayValue(wa[valueIndex], wb[valueIndex], alpha) end
    wheels[wheelIndex] = {
      x = pos.x + w[1], y = pos.y + w[2], z = pos.z + w[3], emit = clamp01(w[4]),
      forward = {w[5], w[6], w[7]}, omega = w[8], rollingOmega = w[9],
      wheelDir = alpha < 0.5 and wa[10] or wb[10], radius = w[11],
      hub = {pos.x + w[12], pos.y + w[13], pos.z + w[14]},
      hubVel = {w[15], w[16], w[17]}
    }
  end
  return {
    pos = pos,
    vel = vec3(v[4], v[5], v[6]),
    bodyCenter = pos + vec3(v[7], v[8], v[9]),
    bodyRight = vec3(v[10], v[11], v[12]),
    bodyForward = vec3(v[13], v[14], v[15]),
    bodyUp = vec3(v[16], v[17], v[18]),
    bodyHalf = vec3(v[19], v[20], v[21]),
    angVel = vec3(v[22], v[23], v[24]),
    bodyValid = (alpha < 0.5 and a[25] or b[25]) == 1,
    wheels = wheels
  }
end

local function onReplayStateChanged(state)
  if type(state) ~= "table" then return end
  replayState = state
  -- The new Pause-menu player resumes after its asynchronous seek. If that
  -- arrives while pre-roll is running, preserve the user's resume intent but
  -- keep the replay frozen until the historical fluid state is complete.
  if replayWarmupActive and state.state == "playback" and state.paused == false then
    if replayPlayback and replayPlayback.warmup then replayPlayback.warmup.resumeAfter = true end
    if core_replay and core_replay.pause then pcall(function() core_replay.pause(true) end) end
  end
  if state.state ~= "playback" then replayLastTime = nil end
end

local function onReplayCoreEvent(data)
  if type(data) ~= "table" then return end
  local event = data.event
  local state = type(data.state) == "table" and data.state or replayState
  if event == "recordingStarted" then
    beginReplayRecording(state.loadedFile)
  elseif event == "recordingStopped" then
    finishReplayRecording()
  elseif event == "playbackStarted" then
    replayLastTime = nil
    replayWarmupActive = false
    loadReplayPlayback(state.loadedFile)
    requestReplayReset("playback started")
  elseif event == "loadedFileChanged" and state.state == "playback" then
    local replayPath = validReplayPath(state.loadedFile)
    if not replayPlayback or replayPlayback.replayPath ~= replayPath then
      loadReplayPlayback(state.loadedFile)
      requestReplayReset("replay file changed")
    end
  elseif event == "playbackStopped" then
    replayPlayback = nil
    replayLastTime = nil
    replayWarmupActive = false
    requestReplayReset("playback stopped")
  end
end

local function onPreRender(dtReal, dtSim)
  if replayState.state == "playback" then
    local time = replayTime(replayState)
    if replayLastTime then
      local delta = time - replayLastTime
      local expectedAdvance = replayState.paused and 0 or
        math.max(0, tonumber(dtReal) or 0) * math.max(0, tonumber(replayState.speed) or 1)
      local tolerance = math.max(0.15, expectedAdvance * 0.5)
      if delta < -0.02 or delta > expectedAdvance + tolerance then
        scheduleReplayWarmup(time)
        requestReplayReset("replay seek")
      end
    end
    replayLastTime = time
  end
end

M.replaySidecarVersion = replaySidecarVersion
M.replaySampleInterval = replaySampleInterval
M.replayMaximumFrames = replayMaximumFrames
M.replayWarmupWindow = replayWarmupWindow
M.replayTime = replayTime
M.validReplayPath = validReplayPath
M.replaySidecarPath = replaySidecarPath
M.requestReplayReset = requestReplayReset
M.compactReplayWheel = compactReplayWheel
M.compactReplayVehicle = compactReplayVehicle
M.replayFrameIsValid = replayFrameIsValid
M.captureReplayFrame = captureReplayFrame
M.beginReplayRecording = beginReplayRecording
M.finishReplayRecording = finishReplayRecording
M.loadReplayPlayback = loadReplayPlayback
M.lerpReplayValue = lerpReplayValue
M.replayFramePair = replayFramePair
M.sampledReplayWheels = sampledReplayWheels
M.scheduleReplayWarmup = scheduleReplayWarmup
M.sampledReplayVehicle = sampledReplayVehicle
M.onReplayStateChanged = onReplayStateChanged
M.onReplayCoreEvent = onReplayCoreEvent
M.onPreRender = onPreRender

M.getReplayState = function() return replayState end
M.getResetSequence = function() return replayResetSequence end
M.isWarmupActive = function() return replayWarmupActive end
M.setWarmupActive = function(val) replayWarmupActive = val end
M.getPlayback = function() return replayPlayback end
M.getRecording = function() return replayRecording end
M.getLastError = function() return replayLastError end
M.setLastTime = function(t) replayLastTime = t end

return M
