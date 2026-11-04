-- ============================================================================
-- PROJECT: VolSmoke for BeamNG.drive.
-- COPYRIGHT (C) 2026 REALSMOKE 3D CONTRIBUTORS.
-- LICENSE: MIT (see LICENSE). Original project: https://github.com/ThugbobTrapabrickpants/VolSmoke
-- ============================================================================
-- VolSmoke In-Game Auto-Diagnostics Submodule.
-- Owns ReShade/Vulkan triage, binary validation, and 1 Hz UDP heartbeat on port 29294.

local M = {}

local b = bit or bit32 or (type(require) == "function" and pcall(require, "bit") and require("bit"))

local EXPECTED_MOD_VERSION = "0.8.12.9"

local diag = {
  socket = nil,
  lastHeartbeatTime = 0,
  heartbeatReceived = false,
  api = "UNKNOWN",
  ver = "",
  frames = 0,
  simActive = false,
  depthOk = true,
  particleConflict = false,
  particleConflictMod = nil,
  particleSuppressed = true,
  scaled = false,
  scalePct = 100,
  depthW = 0,
  depthH = 0,
  frameW = 0,
  frameH = 0,
  hdr = false,
  uiCaptured = true,
  apiLabel = "D3D11",
  conflictingAddon = nil,
  status = "CONNECTING",
  code = "CONNECTING",
  lastLoggedCode = nil,
  lastLoggedTime = 0,
  initTime = os.clock()
}

local function checkDiskFile(relPath)
  -- 1. BeamNG VFS check
  if FS and type(FS.fileExists) == "function" then
    if FS:fileExists(relPath) or FS:fileExists("/" .. relPath) then
      return true
    end
    if type(FS.getGamePath) == "function" then
      local gp = FS:getGamePath()
      if gp and gp ~= "" then
        local f = io.open(gp .. relPath, "rb")
        if f then f:close(); return true end
      end
    end
  end
  -- 2. Direct relative io.open (relative to CWD)
  local f = io.open(relPath, "rb")
  if f then f:close(); return true end
  -- 3. If relPath is "Bin64/...", also try basename in case CWD is Bin64
  local baseName = string.match(relPath, "Bin64/(.+)$")
  if baseName then
    local fb = io.open(baseName, "rb")
    if fb then fb:close(); return true end
  end
  return false
end

local function isVulkanActive()
  -- 1. Native BeamNG Render adapter query (authoritative in BeamNG 0.3x)
  if Engine and Engine.Render and type(Engine.Render.getAdapterType) == "function" then
    local ok, adapter = pcall(Engine.Render.getAdapterType)
    if ok and adapter and string.find(string.lower(tostring(adapter)), "vulkan", 1, true) then
      return true
    end
  end
  -- 2. Engine Vulkan enabled query
  if Engine and type(Engine.getVulkanEnabled) == "function" then
    local ok, enabled = pcall(Engine.getVulkanEnabled)
    if ok and enabled == true then return true end
  end
  -- 3. GFXInit adapter query
  if GFXInit and type(GFXInit.getAdapterType) == "function" then
    local ok, adapter = pcall(GFXInit.getAdapterType)
    if ok and adapter and string.find(string.lower(tostring(adapter)), "vulkan", 1, true) then
      return true
    end
  end
  -- 4. Platform command line check
  if Engine and Engine.Platform and type(Engine.Platform.getCommandLine) == "function" then
    local ok, cmd = pcall(Engine.Platform.getCommandLine)
    if ok and cmd and string.find(string.lower(tostring(cmd)), "vulkan", 1, true) then
      return true
    end
  end
  -- 5. Settings / TorqueScript fallback
  if type(settings) == "table" and type(settings.getValue) == "function" then
    local renderer = tostring(settings.getValue('GraphicRenderer') or "")
    if string.find(string.lower(renderer), "vulkan", 1, true) then return true end
  end
  if type(TorqueScriptLua) == "table" and type(TorqueScriptLua.getVar) == "function" then
    local ok, dev = pcall(TorqueScriptLua.getVar, "$pref::Video::displayDevice")
    if ok and dev and string.find(string.lower(tostring(dev)), "vulkan", 1, true) then return true end
  end
  if type(TorqueScript) == "table" and type(TorqueScript.eval) == "function" then
    local ok, dev = pcall(TorqueScript.eval, "return $pref::Video::displayDevice;")
    if ok and dev and string.find(string.lower(tostring(dev)), "vulkan", 1, true) then return true end
  end
  return false
end

local function initHeartbeatReceiver()
  if diag.socket then return true end
  local ok, socketModule = pcall(require, "socket")
  if not ok or not socketModule or not socketModule.udp then
    ok, socketModule = pcall(require, "socket.socket")
  end
  if not ok or not socketModule or not socketModule.udp then return false end

  local s = socketModule.udp()
  if not s then return false end
  local bindOk = s:setsockname("127.0.0.1", 29294)
  if not bindOk then
    bindOk = s:setsockname("*", 29294)
  end
  if not bindOk then
    pcall(function() s:close() end)
    return false
  end
  s:settimeout(0)
  diag.socket = s
  return true
end

local function pollHeartbeat()
  if not diag.socket and not initHeartbeatReceiver() then return end
  while true do
    local data = diag.socket:receive()
    if not data then break end

    local jsonOk, packet = pcall(jsonDecode, data)
    if not jsonOk or type(packet) ~= "table" then
      packet = {}
      if string.find(data, '"type"%s*:%s*"heartbeat"') then
        packet.type = "heartbeat"
        packet.api = string.match(data, '"api"%s*:%s*"([^"]+)"')
        packet.ver = string.match(data, '"ver"%s*:%s*"([^"]+)"')
        packet.frames = tonumber(string.match(data, '"frames"%s*:%s*(%d+)')) or 0
        packet.simActive = string.find(data, '"simActive"%s*:%s*true') ~= nil
        packet.depthOk = string.find(data, '"depthOk"%s*:%s*false') == nil
        packet.scaled = string.find(data, '"scaled"%s*:%s*true') ~= nil
        packet.scalePct = tonumber(string.match(data, '"scalePct"%s*:%s*(%d+)')) or 100
        packet.depthW = tonumber(string.match(data, '"depthW"%s*:%s*(%d+)')) or 0
        packet.depthH = tonumber(string.match(data, '"depthH"%s*:%s*(%d+)')) or 0
        packet.frameW = tonumber(string.match(data, '"frameW"%s*:%s*(%d+)')) or 0
        packet.frameH = tonumber(string.match(data, '"frameH"%s*:%s*(%d+)')) or 0
        packet.hdr = string.find(data, '"hdr"%s*:%s*true') ~= nil
        packet.uiCaptured = string.find(data, '"uiCaptured"%s*:%s*false') == nil
      end
    end

    if packet and packet.type == "heartbeat" then
      diag.lastHeartbeatTime = os.clock()
      diag.heartbeatReceived = true
      if packet.api then diag.api = packet.api end
      if packet.ver then diag.ver = packet.ver end
      diag.frames = packet.frames or 0
      diag.simActive = (packet.simActive == true)
      diag.depthOk = (packet.depthOk ~= false)
      if packet.scaled ~= nil then diag.scaled = (packet.scaled == true) end
      if packet.scalePct ~= nil then diag.scalePct = tonumber(packet.scalePct) or 100 end
      if packet.depthW ~= nil then diag.depthW = tonumber(packet.depthW) or 0 end
      if packet.depthH ~= nil then diag.depthH = tonumber(packet.depthH) or 0 end
      if packet.frameW ~= nil then diag.frameW = tonumber(packet.frameW) or 0 end
      if packet.frameH ~= nil then diag.frameH = tonumber(packet.frameH) or 0 end
      if packet.hdr ~= nil then diag.hdr = (packet.hdr == true) end
      if packet.uiCaptured ~= nil then diag.uiCaptured = (packet.uiCaptured ~= false) end

      if diag.api == "D3D12" then
        if diag.scaled and diag.scalePct < 98 then
          if diag.hdr then
            diag.apiLabel = "D3D12 (DLSS/FSR " .. tostring(diag.scalePct) .. "% | HDR)"
          else
            diag.apiLabel = "D3D12 (DLSS/FSR " .. tostring(diag.scalePct) .. "%)"
          end
        elseif diag.hdr then
          diag.apiLabel = "D3D12 (HDR10)"
        else
          diag.apiLabel = "D3D12 (Native 100%)"
        end
      else
        diag.apiLabel = diag.api or "D3D11"
      end
    end
  end
end

local lastParticleScanTime = 0
local cachedParticleConflict = false
local cachedParticleConflictMod = nil

local function scanParticleConflicts()
  local now = os.clock()
  if (now - lastParticleScanTime) < 15.0 and lastParticleScanTime > 0 then
    return cachedParticleConflict, cachedParticleConflictMod
  end
  lastParticleScanTime = now

  if not FS or type(FS.getFileRealPath) ~= "function" then
    cachedParticleConflict = false
    cachedParticleConflictMod = nil
    return false, nil
  end

  local ok, realPath = pcall(FS.getFileRealPath, FS, "lua/common/particles.json")
  if not ok or not realPath or realPath == "" then
    cachedParticleConflict = false
    cachedParticleConflictMod = nil
    return false, nil
  end

  local norm = string.lower(string.gsub(tostring(realPath), "\\", "/"))
  -- Expected clean path: points to RealSmoke_3D.zip or inside our mod repository
  if string.find(norm, "realsmoke_3d.zip", 1, true) or string.find(norm, "realsmoke_3d", 1, true) then
    cachedParticleConflict = false
    cachedParticleConflictMod = nil
    return false, nil
  end

  -- If it points to vanilla game install
  if string.find(norm, "steamapps/common/beamng.drive", 1, true) then
    cachedParticleConflict = true
    cachedParticleConflictMod = "BeamNG Vanilla Default (Mod unmounted)"
    return true, cachedParticleConflictMod
  end

  -- If it comes from another mod zip or unpacked mod
  local modZip = string.match(norm, "([^/]+%.zip)")
  if modZip then
    cachedParticleConflict = true
    cachedParticleConflictMod = modZip
    return true, modZip
  end
  local unpackedMod = string.match(norm, "/mods/unpacked/([^/]+)")
  if unpackedMod then
    local uMod = "mods/unpacked/" .. unpackedMod
    cachedParticleConflict = true
    cachedParticleConflictMod = uMod
    return true, uMod
  end

  -- If it points to a loose file in user AppData
  if string.find(norm, "/lua/common/particles.json", 1, true) and not string.find(norm, ".zip", 1, true) then
    local looseMod = "User AppData Loose Override (" .. tostring(realPath) .. ")"
    cachedParticleConflict = true
    cachedParticleConflictMod = looseMod
    return true, looseMod
  end

  local rawMod = tostring(realPath)
  cachedParticleConflict = true
  cachedParticleConflictMod = rawMod
  return true, rawMod
end

local lastAddonScanTime = 0
local cachedConflictingAddon = nil

local function scanConflictingAddons()
  local now = os.clock()
  if (now - lastAddonScanTime) < 30.0 and lastAddonScanTime > 0 then
    return cachedConflictingAddon ~= nil, cachedConflictingAddon
  end
  lastAddonScanTime = now
  cachedConflictingAddon = nil

  local knownConflicting = {
    "ReshadeEffectShaderToggler.addon",
    "reshade-shaders.addon"
  }
  for _, a in ipairs(knownConflicting) do
    if checkDiskFile("Bin64/" .. a) then
      cachedConflictingAddon = a
      return true, a
    end
  end
  return false, nil
end

local function updateDiagnostics(hasVehicle, isGuardActive)
  local now = os.clock()
  pollHeartbeat()

  -- Priority 0.1: Version Synchronization Lock
  -- Ensures bit-exact version parity between native add-on (Bin64/RealSmoke_3D.addon) and BeamNG Lua mod.
  if diag.heartbeatReceived and diag.ver and diag.ver ~= "" then
    if diag.ver ~= EXPECTED_MOD_VERSION then
      diag.status = "FAULT"
      diag.code = "ERROR_VERSION_MISMATCH"
      return
    end
  end

  -- Background Particle Conflict Audit: Check if another mod overrides particles.json
  local hasParticleConflict, conflictMod = scanParticleConflicts()
  diag.particleConflict = (hasParticleConflict == true)
  diag.particleConflictMod = conflictMod
  if hasParticleConflict then
    local isSuppressed = (not hasVehicle) or (isGuardActive == true)
    diag.particleSuppressed = isSuppressed
  else
    diag.particleSuppressed = true
  end

  -- Background Addon Conflict Audit: Check if another ReShade add-on hooks depth in Bin64
  local hasConflictingAddon, addonName = scanConflictingAddons()
  diag.conflictingAddon = addonName

  -- Priority 1: Vulkan check - Vulkan is fundamentally incompatible with DirectX 11/12 hooks.
  -- Must be checked before anything else so that a silent add-on under Vulkan never misdiagnoses
  -- as "ReShade without add-on support".
  if isVulkanActive() then
    diag.status = "FAULT"
    diag.code = "ERROR_VULKAN_INCOMPATIBLE"
    return
  end

  -- Priority 2: Heartbeat received recently (< 3.5s) -> Add-on is online and actively rendering
  if diag.heartbeatReceived and (now - diag.lastHeartbeatTime) <= 3.5 then
    if hasVehicle and not diag.depthOk and (now - diag.initTime) > 6.0 then
      if diag.api == "D3D12" and not diag.uiCaptured then
        diag.status = "FAULT"
        diag.code = "ERROR_UI_LAYER_DESYNC"
      else
        diag.status = "FAULT"
        diag.code = "ERROR_DEPTH_BUFFER_OFFLINE"
      end
    elseif hasVehicle and diag.scaled and (diag.depthW == 0 or diag.depthH == 0) and (now - diag.initTime) > 6.0 then
      diag.status = "FAULT"
      diag.code = "ERROR_DEPTH_SCALE_MISMATCH"
    else
      diag.status = "OK"
      diag.code = "OK"
    end
    return
  end

  -- Priority 3: ReShade DLL presence check.
  -- ReShade requires dxgi.dll or d3d11.dll in Bin64. ReShade.ini alone is merely an inert config file.
  local hasDxgi = checkDiskFile("Bin64/dxgi.dll")
  local hasD3d11 = checkDiskFile("Bin64/d3d11.dll")
  if not hasDxgi and not hasD3d11 then
    diag.status = "FAULT"
    diag.code = "ERROR_RESHADE_NOT_INSTALLED"
    return
  end

  -- Priority 4: RealSmoke_3D.addon binary check in Bin64
  local hasAddon = checkDiskFile("Bin64/RealSmoke_3D.addon")
  if not hasAddon then
    diag.status = "FAULT"
    diag.code = "ERROR_ADDON_MISSING_FROM_BIN64"
    return
  end

  -- Priority 5: Both ReShade DLL and RealSmoke_3D.addon exist, but no heartbeat received.
  -- This occurs when a standard ReShade build (without add-on support) is installed,
  -- or when ReShade has blocked/failed add-on loading.
  if (now - diag.initTime) >= 3.5 or hasVehicle then
    diag.status = "FAULT"
    diag.code = "ERROR_ADDON_NOT_RESPONDING"
    return
  end

  diag.status = "CONNECTING"
  diag.code = "CONNECTING"
end

local function logDiagnosticState()
  if diag.code == diag.lastLoggedCode and (os.clock() - diag.lastLoggedTime) < 10.0 then return end
  diag.lastLoggedCode = diag.code
  diag.lastLoggedTime = os.clock()

  if diag.status == "FAULT" and log then
    local msgs = {
      ERROR_ADDON_NOT_RESPONDING = "3D smoke pipeline offline. Reason: ReShade lacks Add-on support. Download ReShade with full add-on support from reshade.me.",
      ERROR_VULKAN_INCOMPATIBLE = "3D smoke pipeline offline. Reason: Game running in Vulkan mode. VolSmoke requires DirectX 11/12.",
      ERROR_ADDON_MISSING_FROM_BIN64 = "3D smoke pipeline offline. Reason: RealSmoke_3D.addon missing from Bin64 folder.",
      ERROR_RESHADE_NOT_INSTALLED = "3D smoke pipeline offline. Reason: ReShade not detected in game Bin64 folder.",
      ERROR_DEPTH_BUFFER_OFFLINE = "3D smoke pipeline offline. Reason: ReShade scene depth buffer is unavailable or disabled.",
      ERROR_UI_LAYER_DESYNC = "3D smoke pipeline offline. Reason: Interface layer desynchronization. CEF UI composite interrupted by external overlay or display mode.",
      ERROR_DEPTH_SCALE_MISMATCH = "3D smoke pipeline offline. Reason: Temporal upscaling depth buffer scale mismatch.",
      ERROR_VERSION_MISMATCH = "3D smoke pipeline offline. Reason: Version mismatch between native add-on and BeamNG mod. Run install.bat to synchronize.",
    }
    local reason = msgs[diag.code] or diag.code
    log('E', 'VolSmoke', '[DIAGNOSTICS] ' .. reason)
  elseif diag.status == "OK" and log then
    log('I', 'VolSmoke', '[DIAGNOSTICS] 3D smoke pipeline online (' .. tostring(diag.api) .. ' v' .. tostring(diag.ver) .. ')')
    if diag.particleConflict then
      if diag.particleSuppressed then
        log('I', 'VolSmoke', '[DIAGNOSTICS] Third-party mod conflict: ' .. tostring(diag.particleConflictMod) .. ' overrides particles.json. 2D sprites silenced by Vehicle Lua guard.')
      else
        log('W', 'VolSmoke', '[DIAGNOSTICS] Third-party mod conflict: ' .. tostring(diag.particleConflictMod) .. ' overrides particles.json. 2D sprite suppression FAILED or guard inactive!')
      end
    end
  end
end

local function close()
  if diag.socket then
    pcall(function() diag.socket:close() end)
    diag.socket = nil
  end
end

M.diag = diag
M.getDiag = function() return diag end
M.initHeartbeatReceiver = initHeartbeatReceiver
M.pollHeartbeat = pollHeartbeat
M.scanParticleConflicts = scanParticleConflicts
M.updateDiagnostics = updateDiagnostics
M.logDiagnosticState = logDiagnosticState
M.checkDiskFile = checkDiskFile
M.isVulkanActive = isVulkanActive
M.close = close

return M
