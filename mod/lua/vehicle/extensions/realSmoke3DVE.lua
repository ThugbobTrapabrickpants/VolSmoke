-- ============================================================================
-- PROJECT: VolSmoke for BeamNG.drive.
-- COPYRIGHT (C) 2026 REALSMOKE 3D CONTRIBUTORS.
-- LICENSE: MIT (see LICENSE). Original project: https://github.com/ThugbobTrapabrickpants/VolSmoke
-- ============================================================================
-- VolSmoke vehicle-side friction telemetry.
-- Uses the same wheel fields and normalization used by BeamNG's skid audio
-- and burnout statistic modules.

local M = {}

local max = math.max
local min = math.min
local abs = math.abs
local sqrt = math.sqrt
local exp = math.exp

local b = bit or bit32 or (type(require) == "function" and pcall(require, "bit") and require("bit"))


local updateTimer = 0
local protocolVersion = 3
local frameSynchronousTelemetry = false
local provenanceBuildId = "v0.8.12.9-advanced-smoke-physics (baseline 0.8.12.9)"
local previousHubOffset = {}
local tireSkinTemps = {}
local tireBulkTemps = {}
local tireFlashTemps = {}
local wheelFrictionDuration = {}
local wheelFilteredEmission = {}
local wheelFilteredSmoke = {}
local wheelFilteredDust = {}
local hasActiveFriction = false

-- Burnout Equity parameters
local heatThreshold = 70.0   -- °C threshold (default 70°C, 40°C - 120°C)
local frictionSens = 0.35    -- legacy parameter (unification: strictly physical Coulomb-Persson work)
local frictionTime = 2.00    -- legacy parameter (unification: strictly physical C_skin thermal mass)
local smokeOnset = 2.00
local smokeOnsetBezier = { 70.0, 0.0, 0.25, 0.05, 0.55, 0.95, 220.0, 1.00 } -- [onsetTemp, initialHaze, x1, y1, x2, y2, endTemp, maxDensity]
local smokeDecay = 1.50      -- seconds for hot-tire residual smoke dissipation (default 1.50s, range 0.0s - 5.0s)
local smokeDecayBezier = { 1.50, 1.00, 0.25, 0.95, 0.65, 0.15 } -- [duration, y0, x1, y1, x2, y2]
local wheelPeakSmoke = {}
local wheelDecayTimer = {}

-- Adaptive Vehicle Profile (extracted dynamically from JBeam mesh nodes)
local vehicleProfile = {
  hoodHeightRatio = 0.50,
  windshieldSpan = 0.30,
  rearDeckRatio = 0.50,
  roofWidthRatio = 0.80
}

local function computeVehicleProfile()
  local profile = {
    hoodHeightRatio = 0.50,
    windshieldSpan = 0.30,
    rearDeckRatio = 0.50,
    roofWidthRatio = 0.80
  }
  
  local minX, maxX = 1e9, -1e9
  local minY, maxY = 1e9, -1e9
  local minZ, maxZ = 1e9, -1e9
  local nodePositions = {}
  
  if v and v.data and type(v.data.nodes) == "table" then
    for _, n in pairs(v.data.nodes) do
      if type(n) == "table" then
        local x = n.posX or (n.pos and n.pos.x) or n[1]
        local y = n.posY or (n.pos and n.pos.y) or n[2]
        local z = n.posZ or (n.pos and n.pos.z) or n[3]
        if type(x) == "number" and type(y) == "number" and type(z) == "number" then
          minX = min(minX, x); maxX = max(maxX, x)
          minY = min(minY, y); maxY = max(maxY, y)
          minZ = min(minZ, z); maxZ = max(maxZ, z)
          nodePositions[#nodePositions + 1] = { x = x, y = y, z = z }
        end
      end
    end
  elseif obj and type(obj.getNodeCount) == "function" and type(obj.getNodePosition) == "function" then
    local count = obj:getNodeCount() or 0
    for i = 0, count - 1 do
      local ok, p = pcall(function() return obj:getNodePosition(i) end)
      if ok and p then
        minX = min(minX, p.x); maxX = max(maxX, p.x)
        minY = min(minY, p.y); maxY = max(maxY, p.y)
        minZ = min(minZ, p.z); maxZ = max(maxZ, p.z)
        nodePositions[#nodePositions + 1] = { x = p.x, y = p.y, z = p.z }
      end
    end
  end

  local totalNodes = #nodePositions
  if totalNodes >= 12 and (maxY - minY) > 1.0 and (maxZ - minZ) > 0.4 then
    local length = maxY - minY
    local height = maxZ - minZ
    local width = max(0.5, maxX - minX)

    local yFrontBoundary = minY + length * 0.75
    local yRearBoundary = minY + length * 0.25

    local maxFrontZ = -1e9
    local maxCabinZ = -1e9
    local maxRearZ = -1e9

    for i = 1, totalNodes do
      local np = nodePositions[i]
      if np.y >= yFrontBoundary then
        if np.z > maxFrontZ then maxFrontZ = np.z end
      elseif np.y <= yRearBoundary then
        if np.z > maxRearZ then maxRearZ = np.z end
      else
        if np.z > maxCabinZ then maxCabinZ = np.z end
      end
    end

    local roofZ = max(maxCabinZ, max(maxFrontZ, maxRearZ))
    local baseZ = minZ

    if roofZ > baseZ + 0.1 then
      if maxFrontZ > -1e8 then
        profile.hoodHeightRatio = max(0.1, min(1.0, (maxFrontZ - baseZ) / (roofZ - baseZ)))
      end
      if maxRearZ > -1e8 then
        profile.rearDeckRatio = max(0.1, min(1.0, (maxRearZ - baseZ) / (roofZ - baseZ)))
      end
    end

    local roofCutZ = roofZ - height * 0.15
    local minRoofX, maxRoofX = 1e9, -1e9
    local roofNodeCount = 0
    for i = 1, totalNodes do
      local np = nodePositions[i]
      if np.z >= roofCutZ and np.y > yRearBoundary and np.y < yFrontBoundary then
        minRoofX = min(minRoofX, np.x)
        maxRoofX = max(maxRoofX, np.x)
        roofNodeCount = roofNodeCount + 1
      end
    end

    if roofNodeCount >= 2 and maxRoofX > minRoofX then
      local roofWidth = maxRoofX - minRoofX
      profile.roofWidthRatio = max(0.50, min(1.0, roofWidth / width))
    end

    local heightDiff = max(0.0, 1.0 - profile.hoodHeightRatio)
    profile.windshieldSpan = max(0.08, min(0.60, heightDiff * 0.55))
  end

  vehicleProfile = profile
  return profile
end

-- Surface profile parameters
local sandDustScale = 1.00       -- mineral dust density multiplier on sand (default 1.0x, 0.0x - 3.0x)
local sandDustSens = 1.00        -- mineral dust kinematic sensitivity on sand (default 1.0x, 0.05x - 3.0x)
local sandDustEnabled = true     -- sand dust activity toggle
local asphaltSmokeEnabled = true -- asphalt smoke activity toggle


local function evalCubicBezier(t, x1, y1, x2, y2)
  if not x1 or not y1 or not x2 or not y2 then
    return t * t * (3.0 - 2.0 * t)
  end
  local s = t
  for _ = 1, 4 do
    local omS = 1.0 - s
    local curX = 3.0 * omS * omS * s * x1 + 3.0 * omS * s * s * x2 + s * s * s
    local dX = 3.0 * omS * omS * x1 + 6.0 * omS * s * (x2 - x1) + 3.0 * s * s * (1.0 - x2)
    if math.abs(dX) < 1e-5 then break end
    s = math.max(0.0, math.min(1.0, s - (curX - t) / dX))
  end
  local omS = 1.0 - s
  local curY = 3.0 * omS * omS * s * y1 + 3.0 * omS * s * s * y2 + s * s * s
  return math.max(0.0, math.min(1.0, curY))
end

local function evalCubicBezierWithOnset(t, y0, x1, y1, x2, y2, y3)
  local yStart = y0 or 0.0
  local yEnd = y3 or 1.0
  if not x1 or not y1 or not x2 or not y2 then
    return yStart + (yEnd - yStart) * (t * t * (3.0 - 2.0 * t))
  end
  local s = t
  for _ = 1, 4 do
    local omS = 1.0 - s
    local curX = 3.0 * omS * omS * s * x1 + 3.0 * omS * s * s * x2 + s * s * s
    local dX = 3.0 * omS * omS * x1 + 6.0 * omS * s * (x2 - x1) + 3.0 * s * s * (1.0 - x2)
    if math.abs(dX) < 1e-5 then break end
    s = math.max(0.0, math.min(1.0, s - (curX - t) / dX))
  end
  local omS = 1.0 - s
  local curY = omS * omS * omS * yStart + 3.0 * omS * omS * s * y1 + 3.0 * omS * s * s * y2 + s * s * s * yEnd
  return math.max(0.0, math.min(1.0, curY))
end

local function clamp01(value)
  return max(0, min(1, tonumber(value) or 0))
end

local function resetTireThermals()
  tireSkinTemps = {}
  tireBulkTemps = {}
  tireFlashTemps = {}
  previousHubOffset = {}
  wheelFrictionDuration = {}
  wheelFilteredEmission = {}
  wheelFilteredSmoke = {}
  wheelFilteredDust = {}
  wheelPeakSmoke = {}
  wheelDecayTimer = {}
  hasActiveFriction = false
end

local particleFilterGuardHook = nil
local originalParticleNodeCollision = nil

-- Ironclad suppression of vanilla 2D billboard sprite smoke & dust:
-- Intercepts BeamNG's particlefilter.nodeCollision in the vehicle Lua VM.
-- If the collision involves tire rubber (materialID 4), 2D sprite emission is suppressed,
-- ensuring VolSmoke's Navier-Stokes fluid simulation has exclusive domain over tire smoke.
-- Non-rubber collisions (e.g. chassis metal scraping for sparks, wood, glass) pass through untouched.
local function installParticleFilterGuard()
  local pf = rawget(_G, "particlefilter") or particlefilter
  if not pf or type(pf.nodeCollision) ~= "function" then return end
  if pf.nodeCollision == particleFilterGuardHook then return end

  originalParticleNodeCollision = pf.nodeCollision
  particleFilterGuardHook = function(p)
    if p and (p.materialID1 == 4 or p.materialID2 == 4) then
      return
    end
    if originalParticleNodeCollision then
      return originalParticleNodeCollision(p)
    end
  end
  pf.nodeCollision = particleFilterGuardHook
  pf.__realSmokeGuardInstalled = true
end

-- Physical surface friction profiles and particulate emission classification
-- High-friction rigid road surfaces generate white tire pyrolysis smoke.
-- Loose granular surfaces (sand, dirt, gravel) eject ground mineral dust.
-- Soft vegetative (grass) and low-friction (snow, ice) surfaces generate zero smoke.
local surfaceProfiles = {
  -- ASPHALT / TARMAC (High friction, pure rubber pyrolysis smoke)
  [10] = { mu = 0.90, kind = "smoke", smokeScale = 1.0, dustScale = 0.0, dustTint = 0 },
  -- ASPHALT_WET (Reduced friction, partial steam)
  [11] = { mu = 0.50, kind = "smoke", smokeScale = 0.40, dustScale = 0.0, dustTint = 0 },
  -- RUMBLE_STRIP (Curb / kerb)
  [29] = { mu = 0.90, kind = "smoke", smokeScale = 1.0, dustScale = 0.0, dustTint = 0 },
  -- COBBLESTONE (Stone paving)
  [30] = { mu = 0.75, kind = "smoke", smokeScale = 0.75, dustScale = 0.0, dustTint = 0 },
  -- METAL (Ramps, plates, dyno)
  [2]  = { mu = 0.85, kind = "smoke", smokeScale = 0.90, dustScale = 0.0, dustTint = 0 },
  -- WOOD (Planks, docks)
  [6]  = { mu = 0.70, kind = "smoke", smokeScale = 0.70, dustScale = 0.0, dustTint = 0 },
  -- RUBBER ON RUBBER (Burnout pad / drag strip rubber groove)
  [4]  = { mu = 0.95, kind = "smoke", smokeScale = 1.0, dustScale = 0.0, dustTint = 0 },

  -- SAND / SANDY_ROAD / DIRT_DUSTY / DIRT / GRAVEL (Granular mineral dust, ochre/earthy tint)
  [16] = { mu = 0.40, kind = "dust", smokeScale = 0.0, dustScale = 1.00, dustTint = 1 }, -- SAND
  [17] = { mu = 0.45, kind = "dust", smokeScale = 0.0, dustScale = 1.00, dustTint = 1 }, -- SANDY_ROAD
  [14] = { mu = 0.45, kind = "dust", smokeScale = 0.0, dustScale = 0.95, dustTint = 1 }, -- DIRT_DUSTY
  [15] = { mu = 0.50, kind = "dust", smokeScale = 0.0, dustScale = 0.90, dustTint = 1 }, -- DIRT
  [18] = { mu = 0.35, kind = "dust", smokeScale = 0.0, dustScale = 0.65, dustTint = 1 }, -- MUD
  [19] = { mu = 0.45, kind = "dust", smokeScale = 0.0, dustScale = 0.80, dustTint = 1 }, -- GRAVEL
  [13] = { mu = 0.60, kind = "dust", smokeScale = 0.0, dustScale = 0.50, dustTint = 1 }, -- ROCK

  -- GRASS & FOLIAGE (Organic turf: low friction, grass shears, moisture, no tire pyrolysis)
  [20] = { mu = 0.25, kind = "none", smokeScale = 0.0, dustScale = 0.0, dustTint = 0 },
  [7]  = { mu = 0.20, kind = "none", smokeScale = 0.0, dustScale = 0.0, dustTint = 0 },
  [31] = { mu = 0.20, kind = "none", smokeScale = 0.0, dustScale = 0.0, dustTint = 0 },

  -- ICE / SNOW / WATER (Slippery, near zero friction, no smoke)
  [21] = { mu = 0.05, kind = "none", smokeScale = 0.0, dustScale = 0.0, dustTint = 0 },
  [22] = { mu = 0.15, kind = "none", smokeScale = 0.0, dustScale = 0.0, dustTint = 0 },
  [9]  = { mu = 0.10, kind = "none", smokeScale = 0.0, dustScale = 0.0, dustTint = 0 },

  -- Untyped collision / terrain mesh (default off-road surface: emits mineral dust, strictly NO white smoke)
  [0]  = { mu = 0.50, kind = "dust", smokeScale = 0.0, dustScale = 0.85, dustTint = 1 },
}

local function getGroundProfile(mat1, mat2)
  local groundMat = mat1
  if groundMat == 4 then
    groundMat = mat2
  elseif mat2 and mat2 ~= -1 and mat2 ~= 4 and surfaceProfiles[mat2] then
    groundMat = mat2
  end
  if groundMat and surfaceProfiles[groundMat] then
    return surfaceProfiles[groundMat], groundMat
  end
  -- Fail-closed default: on unmapped terrain, emit dust if slipping, NEVER white pyrolysis smoke!
  return { mu = 0.50, kind = "dust", smokeScale = 0.0, dustScale = 0.85, dustTint = 1 }, (groundMat or -1)
end

local function updateTireThermodynamics(wheel, sampleDt, groundSpeed, normalForce, longitudinalSlip, lateralSlip, wheelSpeed, profile)
  local name = wheel and wheel.name or "unknown"
  local dt = max(0.001, min(0.20, tonumber(sampleDt) or 0.05))

  -- 1. Ambient Air & Initial Conditions:
  -- True atmospheric temperature from BeamNG vehicle environment (in Kelvin converted to °C).
  -- Fail-closed default 20.0°C; never contaminated by brake rotor surface temperature.
  local ambient = 20.0
  if obj and type(obj.getEnvTemperature) == "function" then
    local ok, envK = pcall(function() return obj:getEnvTemperature() end)
    if ok and type(envK) == "number" and envK > 200.0 and envK < 350.0 then
      ambient = envK - 273.15
    end
  end

  local tBulk = tireBulkTemps[name] or ambient
  local tSkin = tireSkinTemps[name] or ambient
  local prevFlash = tireFlashTemps[name] or 0.0

  -- 2. First-Principles Instantaneous Mechanical Friction Power:
  -- Differentiates active driven wheelspin (burnout/power oversteer), locked/dragged braking,
  -- and free-rolling lateral cornering scrub across ANY wheel without hardcoding positions or fake flags.
  local rawSlip = wheel and tonumber(wheel.lastSlip)
  local longSlipSigned = rawSlip or ((wheelSpeed >= groundSpeed) and longitudinalSlip or -longitudinalSlip)
  local contactFwdSpeed = max(0.1, wheelSpeed - longSlipSigned)
  local driveSpinRatio = clamp01(max(0.0, longSlipSigned) / max(wheelSpeed, 3.0))
  local brakeLockRatio = clamp01(max(0.0, -longSlipSigned) / max(contactFwdSpeed, 3.0))
  local slidingSeverity = max(driveSpinRatio, brakeLockRatio)

  -- Brush tire mechanics (Pacejka / Guiggiani):
  -- On a free-rolling wheel (slidingSeverity ~ 0, e.g. front wheels in RWD drift or rear wheels in FWD),
  -- the forward rolling brings cool rubber continuously through the contact patch.
  -- The front 70-80% of the contact patch is adhered in the elastic stick zone,
  -- and only ~10-18% undergoes trailing-edge relaxation micro-scrub.
  -- Convective rolling cooling in ambient air dominates, naturally stabilizing tire temperature
  -- around 60-80°C (operating grip window, below the 80-100°C pyrolysis threshold).
  -- When the wheel is actively power-spinning (driveSpinRatio -> 1) OR locked by brakes (brakeLockRatio -> 1),
  -- the elastic stick zone collapses and 100% of the contact patch enters full kinetic Coulomb sliding.
  local latSlidingFactor = 0.10 + 0.90 * slidingSeverity
  local effectiveSlipSpeed = sqrt(longitudinalSlip * longitudinalSlip + (lateralSlip * latSlidingFactor) * (lateralSlip * latSlidingFactor))

  local maxKinematicSpeed = max(2.0, max(wheelSpeed, groundSpeed))
  local slipRatio = effectiveSlipSpeed / maxKinematicSpeed
  local slidingTransition = clamp01((slipRatio - 0.08) / 0.15)
  local effectiveSlip = effectiveSlipSpeed * slidingTransition

  local baseMu = (profile and profile.mu) or 0.85
  -- Molten rubber tribology & thermal softening friction drop (Persson):
  -- As tire surface exceeds 165°C - 230°C, the viscoelastic rubber undergoes surface melting
  -- and liquid volatile lubrication, reducing friction coefficient mu by 55% - 60%.
  local thermalMuDrop = 1.0 - 0.60 * clamp01((tSkin - 165.0) / 65.0)
  local mu = baseMu * thermalMuDrop
  -- Strict first-principles friction work: P = mu * F_N * v_slip (no artificial scale factors)
  local pFriction = mu * normalForce * effectiveSlip

  -- 3. Charron-Blok Effusivity Heat Partition:
  -- b_rubber ≈ 720, b_asphalt ≈ 1575 => gamma_rubber ≈ 0.314
  -- 31.4% enters tire rubber; 68.6% enters pavement.
  -- Loose surfaces (sand/dirt/gravel) shear inter-granularly and do not heat rubber to pyrolysis:
  local gammaRubber = 0.314
  local isPavedSmokeSurface = (profile and profile.kind == "smoke")
  local thermalPartition = isPavedSmokeSurface and 1.0 or 0.0
  local qRubber = pFriction * gammaRubber * thermalPartition

  -- 4. Blok-Jaeger Microscopic Flash Temperature Rise:
  -- Micro-asperity contact flash above tread skin. Calibrated to cFlash ≈ 5.5 K*(s/m)^0.5,
  -- producing ~15°C flash during hard wheelspin without creating an abrupt discontinuous cliff.
  local targetFlash = 0.0
  if isPavedSmokeSurface and effectiveSlip > 0.15 and normalForce > 100.0 then
    local cFlash = 5.5
    targetFlash = cFlash * mu * sqrt(effectiveSlip)
  end

  -- Flash temperature relaxes continuously with contact transit time (tau ≈ 0.80s),
  -- eliminating unphysical 1-frame discontinuous spikes and instantaneous temperature freezes:
  local flashAlpha = 1.0 - exp(-dt / 0.80)
  local currentFlash = prevFlash + (targetFlash - prevFlash) * flashAlpha
  tireFlashTemps[name] = currentFlash

  -- 5. Contact Skin Layer Dynamics (T_skin):
  -- Active outer tread contact skin (~2.0 mm depth, C_skin ≈ 1600 J/K, A_skin ≈ 0.42 m^2).
  -- Pure energy conservation: 100% of qRubber enters the tread surface.
  -- Thermal mass is physical and conserved across wheel rotation and standstill.
  local cSkin = 1600.0 -- J/K (physical 2 mm active pyrolysis skin layer of SBR tire rubber)
  local aSkin = 0.42 -- m^2
  local gCond = 14.0 -- W/K

  local qSkinIn = qRubber
  local qConduct = gCond * (tSkin - tBulk)

  -- High-Speed Forced Convection on Rotating Wheel (Churchill-Bernstein / SAE aerodynamics):
  -- Forward translational velocity combines with perimeter spin (at 12 o'clock, v_rel = v_ground + v_wheel).
  -- Rapid tread rotation and sipes shred the boundary layer, producing Re^0.85 turbulent thinning.
  local vEff = max(groundSpeed, wheelSpeed) + 0.35 * min(groundSpeed, wheelSpeed)
  local hAir = 12.0 + 5.5 * (vEff ^ 0.85)
  local qSkinCool = hAir * aSkin * (tSkin - ambient)

  -- Rolling Road Contact Conduction (Tire-to-Pavement Heat Transfer):
  -- When rolling on pavement, the contact patch (~0.030 m^2) presses against cold ground with high force.
  -- Cold asphalt (effusivity b ≈ 1575 J/(m^2*K*s^0.5)) acts as a massive thermal heat sink.
  -- Each wheel revolution continuously refreshes the interface with cold road surface.
  local qRoadCool = 0.0
  if isPavedSmokeSurface and normalForce > 100.0 then
    local rollFactor = clamp01(wheelSpeed / 3.0)
    local hRoad = 850.0 -- W/(m^2*K) transient contact conduction
    qRoadCool = hRoad * 0.030 * rollFactor * (tSkin - ambient)
  end

  -- Endothermic volatile degradation & ablation damping:
  -- As rubber approaches and exceeds pyrolysis temperatures (180°C - 225°C),
  -- endothermic phase changes and volatile mass ejection absorb thermal energy,
  -- naturally stabilizing the burnout surface temperature between 220°C and 245°C.
  local qAblation = 0.0
  if tSkin > 180.0 then
    local ablateProgress = clamp01((tSkin - 180.0) / 45.0)
    qAblation = qRubber * 0.88 * ablateProgress
  end

  -- Stefan-Boltzmann radiation cooling at high temperatures (T^4):
  local tSkinK = tSkin + 273.15
  local tAmbK = ambient + 273.15
  local qRad = 0.92 * 5.670374e-8 * aSkin * (tSkinK * tSkinK * tSkinK * tSkinK - tAmbK * tAmbK * tAmbK * tAmbK)

  local dSkin = (qSkinIn - qConduct - qSkinCool - qRoadCool - qAblation - qRad) / cSkin
  tSkin = max(ambient, min(450.0, tSkin + dSkin * dt))

  -- 6. Total Contact Surface Temperature (T_surface):
  -- Combined continuous skin accumulation + smoothly relaxing Blok-Jaeger flash
  local tSurface = max(ambient, min(450.0, tSkin + currentFlash))

  -- 7. Bulk Tread Ring Mass Dynamics (T_bulk):
  -- Bulk ring mass ~3.0 kg, C_bulk ≈ 5500 J/K, A_bulk ≈ 0.55 m^2 (inner rim cavity + sidewalls).
  local cBulk = 5500.0 -- J/K
  local aBulk = 0.55
  local hBulk = 10.0 + 3.0 * (vEff ^ 0.80)
  local qBulkCool = hBulk * aBulk * (tBulk - ambient)
  local dBulk = (qConduct - qBulkCool) / cBulk
  tBulk = max(ambient, min(220.0, tBulk + dBulk * dt))

  tireBulkTemps[name] = tBulk
  tireSkinTemps[name] = tSkin

  return tSurface, tSkin, tBulk, pFriction, effectiveSlip, slidingTransition
end

local function vecToTable(value)
  return {x = value.x, y = value.y, z = value.z}
end

local function safeNormalized(value, fallback)
  if value and value:length() > 0.0001 then return value:normalized() end
  return fallback
end

local function getWheelGeometry(wheel, sampleDt)
  local ok1, p1 = pcall(function() return obj:getNodePosition(wheel.node1) end)
  local ok2, p2 = pcall(function() return obj:getNodePosition(wheel.node2) end)
  if not ok1 or not ok2 or not p1 or not p2 then
    return {
      legacyContact = {x = 0, y = 0, z = 0},
      contact = {x = 0, y = 0, z = 0},
      hub = {x = 0, y = 0, z = 0},
      hubVelocity = {x = 0, y = 0, z = 0},
      spinAxis = {x = 1, y = 0, z = 0},
      axleAxis = {x = 1, y = 0, z = 0},
      groundNormal = {x = 0, y = 0, z = 1},
      forwardDir = {x = 0, y = 1, z = 0},
      geometryValid = false,
      normalValid = false
    }
  end

  local hub = (p1 + p2) * 0.5
  local radius = tonumber(wheel.dynamicRadius) or tonumber(wheel.radius) or 0.35
  local legacyContact = hub - vec3(0, 0, radius * 0.92)
  local contact = legacyContact
  if wheel.lastTreadContactNode ~= nil then
    local okContact, treadPosition = pcall(function() return obj:getNodePosition(wheel.lastTreadContactNode) end)
    if okContact and treadPosition then contact = treadPosition end
  end

  local rawSpinAxis = safeNormalized(p2 - p1, vec3(1, 0, 0))
  local wheelDir = tonumber(wheel.wheelDir) or 1
  local axleAxis = rawSpinAxis * wheelDir
  -- A support-plane normal is reconstructed in GE from all four tread contact
  -- points. Calling mapmgr.surfaceNormalBelow for every wheel here causes
  -- multi-millisecond VLUA spikes on complex levels.
  local groundNormal = safeNormalized(obj:getDirectionVectorUp(), vec3(0, 0, 1))
  local forwardDir = safeNormalized(axleAxis:cross(groundNormal), obj:getDirectionVector())

  local hubVelocity = vec3(0, 0, 0)
  local previousHub = previousHubOffset[wheel.name]
  if previousHub and sampleDt > 0.001 and sampleDt < 0.25 then
    local displacement = hub - previousHub
    if displacement:length() < 5.0 then hubVelocity = displacement / sampleDt end
  end
  previousHubOffset[wheel.name] = hub

  return {
    legacyContact = vecToTable(legacyContact),
    contact = vecToTable(contact),
    hub = vecToTable(hub),
    -- Finite differencing avoids eight expensive getNodeVelocity calls per
    -- sample while preserving suspension and vehicle translation motion.
    hubVelocity = vecToTable(hubVelocity),
    spinAxis = vecToTable(rawSpinAxis),
    axleAxis = vecToTable(axleAxis),
    groundNormal = vecToTable(groundNormal),
    forwardDir = vecToTable(forwardDir),
    geometryValid = true,
    normalValid = false
  }
end

local function calculateEmission(wheel, sampleDt, groundSpeed)
  if not wheel or wheel.isBroken then
    return 0, 0, 0, 0, 0, 0, 20.0, 20.0, 20.0
  end

  local mat1 = tonumber(wheel.contactMaterialID1) or -1
  local mat2 = tonumber(wheel.contactMaterialID2) or -1
  local downForce = max(0.0, min(25000.0, tonumber(wheel.downForce) or 0.0))

  -- Ground contact validation:
  -- A wheel only has authentic contact if both material IDs are valid and one is rubber (ID 4).
  local hasContact = (mat1 ~= -1 and mat2 ~= -1)
  local rubberContact = (mat1 == 4 or mat2 == 4)

  local wheelRadius = tonumber(wheel.dynamicRadius) or tonumber(wheel.radius) or 0.35
  local wheelSpeed = abs(tonumber(wheel.wheelSpeed) or (tonumber(wheel.angularVelocity) or 0) * wheelRadius)

  -- When airborne (jumping/bouncing) or during non-ground collisions (chassis/guardrail impact):
  -- Forced convection in ambient air continues cooling the spinning wheel,
  -- while contact friction, road conduction, and particulate emissions are strictly ZERO!
  if not hasContact or not rubberContact then
    local tSurface, tSkin, tBulk = updateTireThermodynamics(wheel, sampleDt, groundSpeed, 0.0, 0.0, 0.0, wheelSpeed, nil)
    return 0, 0, 0, 0, 0, 0, tSurface, tSkin, tBulk, nil, wheelSpeed, 0.0, 0.0
  end

  local profile, groundMat = getGroundProfile(mat1, mat2)

  local longitudinalSlip = abs(tonumber(wheel.lastSlip) or 0)
  local lateralSlip = abs(tonumber(wheel.lastSideSlip) or 0)
  local slip = sqrt(longitudinalSlip * longitudinalSlip + lateralSlip * lateralSlip)

  local wheelRadius = tonumber(wheel.dynamicRadius) or tonumber(wheel.radius) or 0.35
  local wheelSpeed = abs(tonumber(wheel.wheelSpeed) or (tonumber(wheel.angularVelocity) or 0) * wheelRadius)

  local normalForce = (hasContact and rubberContact) and downForce or 0.0
  local contactLong = (hasContact and rubberContact) and longitudinalSlip or 0.0
  local contactLat = (hasContact and rubberContact) and lateralSlip or 0.0

  local tSurface, tSkin, tBulk, pFriction, effectiveSlip, slidingTransition =
    updateTireThermodynamics(wheel, sampleDt, groundSpeed, normalForce, contactLong, contactLat, wheelSpeed, profile)

  -- 1. Mechanical mineral dust generation on loose surfaces (Sand / Sandy Road / Dusty Tracks):
  -- Loose sand grains are flung by wheel slip velocity, rotation speed, and normal load across all 4 wheels.
  -- Does NOT require rubber heating (sand shears underneath, no rubber pyrolysis).
  local dustEmission = 0.0
  if profile.dustScale > 0.001 and sandDustEnabled then
    local spinEject = abs(wheelSpeed - groundSpeed) * 0.70 + wheelSpeed * 0.25
    local ejectSpeed = max(slip, spinEject)
    if ejectSpeed > 0.35 then
      local dustSpeedFactor = clamp01((ejectSpeed - 0.35) / 4.0)
      local dustLoadFactor = clamp01(downForce / 1500.0)
      local sensFactor = max(0.10, sandDustSens)
      dustEmission = clamp01(profile.dustScale * dustSpeedFactor * dustLoadFactor * sandDustScale * sensFactor)
    end
  end

  -- 2. Rubber pyrolysis smoke generation on paved surfaces (Asphalt):
  -- Governed by surface contact temperature T_surface exceeding heatThreshold.
  -- Below heatThreshold (e.g. cold 20°C tires or gentle rolling), rawSmokeEmission is strictly 0.0!
  -- Progressive polymer pyrolysis curve:
  -- Soft, translucent haze (5-15%) at 80-100°C, thickening to medium (40-60%) at 140-160°C,
  -- and reaching 100% heavy billows only during violent thermal decomposition at 180-220°C+.
  local rawSmokeEmission = 0.0
  local onsetTemp = heatThreshold
  local initialHaze = 0.0
  local bx1, by1, bx2, by2 = 0.25, 0.05, 0.55, 0.95
  local endTemp = 220.0
  local maxDensity = 1.00
  if type(smokeOnsetBezier) == "table" then
    if #smokeOnsetBezier >= 8 then
      onsetTemp = tonumber(smokeOnsetBezier[1]) or heatThreshold
      initialHaze = tonumber(smokeOnsetBezier[2]) or 0.0
      bx1 = tonumber(smokeOnsetBezier[3]) or 0.25
      by1 = tonumber(smokeOnsetBezier[4]) or 0.05
      bx2 = tonumber(smokeOnsetBezier[5]) or 0.55
      by2 = tonumber(smokeOnsetBezier[6]) or 0.95
      endTemp = tonumber(smokeOnsetBezier[7]) or 220.0
      maxDensity = tonumber(smokeOnsetBezier[8]) or 1.00
    elseif #smokeOnsetBezier >= 6 then
      onsetTemp = tonumber(smokeOnsetBezier[1]) or heatThreshold
      initialHaze = tonumber(smokeOnsetBezier[2]) or 0.0
      bx1 = tonumber(smokeOnsetBezier[3]) or 0.25
      by1 = tonumber(smokeOnsetBezier[4]) or 0.05
      bx2 = tonumber(smokeOnsetBezier[5]) or 0.55
      by2 = tonumber(smokeOnsetBezier[6]) or 0.95
    elseif #smokeOnsetBezier >= 4 then
      bx1 = tonumber(smokeOnsetBezier[1]) or 0.25
      by1 = tonumber(smokeOnsetBezier[2]) or 0.05
      bx2 = tonumber(smokeOnsetBezier[3]) or 0.55
      by2 = tonumber(smokeOnsetBezier[4]) or 0.95
    end
  end

  if profile.smokeScale > 0.001 and asphaltSmokeEnabled and tSurface > onsetTemp then
    local tempRange = max(10.0, endTemp - onsetTemp)
    local tempProgress = clamp01((tSurface - onsetTemp) / tempRange)
    local thermalFactor = evalCubicBezierWithOnset(tempProgress, initialHaze, bx1, by1, bx2, by2, maxDensity)
    rawSmokeEmission = clamp01(profile.smokeScale * thermalFactor)
  end

  -- Cutoff when stationary and cold
  if wheelSpeed < 0.3 and groundSpeed < 0.3 and tSurface <= onsetTemp then
    rawSmokeEmission = 0.0
    dustEmission = 0.0
  end

  local combinedEmission = max(rawSmokeEmission, dustEmission)
  return combinedEmission, rawSmokeEmission, dustEmission, profile.dustTint, slip, pFriction, tSurface, tSkin, tBulk, profile, wheelSpeed, effectiveSlip, slidingTransition
end

local function sendTelemetry(sampleDt)
  if not wheels or type(wheels.wheels) ~= "table" then return end

  local result = {}
  local groundSpeed = abs(tonumber(obj:getGroundSpeed()) or 0)
  local count = tonumber(wheels.wheelCount) or 0
  local processed = {}
  local activeFrictionDetected = false

  local function processWheel(wheel)
    if not wheel or type(wheel) ~= "table" or not wheel.name or processed[wheel.name] then return end
    processed[wheel.name] = true
    local dt = max(0.001, min(0.20, tonumber(sampleDt) or 0.05))
    local rawEmission, rawSmoke, rawDust, dustTint, slip, pFriction, tSurface, tSkin, tBulk, profile, wheelSpeed, effectiveSlip, slidingTransition =
      calculateEmission(wheel, dt, groundSpeed)
    if not profile then profile, _ = getGroundProfile(tonumber(wheel.contactMaterialID1) or -1, tonumber(wheel.contactMaterialID2) or -1) end

    effectiveSlip = effectiveSlip or 0.0
    slidingTransition = slidingTransition or 0.0

    local isPavedSmokeSurface = (profile and profile.kind == "smoke")
    local rawSlip = wheel and tonumber(wheel.lastSlip)
    local slipVel = abs(rawSlip or (wheelSpeed - groundSpeed))

    -- First-principles kinetic sliding discrimination (Brush Tire Model / Pacejka):
    -- Hot rubber adheres elastically during normal acceleration grip (slipRatio < 8%, slidingTransition == 0).
    -- Genuine pyrolysis smoke requires macroscopic kinetic Coulomb sliding (slipRatio > 8..23%, effectiveSlip > 0.40 m/s),
    -- substantial longitudinal burnout differential (slipVel > 1.80 m/s), or heavy friction dissipation (pFriction > 2500 W):
    local isActivelySlipping = (slidingTransition > 0.05 and effectiveSlip > 0.40) or (slipVel > 1.80 and wheelSpeed > 2.0) or (pFriction > 2500.0)

    local onsetTemp = heatThreshold
    if type(smokeOnsetBezier) == "table" and #smokeOnsetBezier >= 6 then
      onsetTemp = tonumber(smokeOnsetBezier[1]) or heatThreshold
    end

    local activeSmoke = 0.0
    if isPavedSmokeSurface and asphaltSmokeEnabled and rawSmoke > 0.005 and isActivelySlipping then
      -- Kinetic sliding severity scaling:
      -- Transitions progressively from initial light chirp/spin (1.0 - 2.0 m/s) to full 100% burnout billows (> 4.5 m/s)
      -- or heavy normal-load friction work (> 12 kW):
      local slipIntensity = clamp01(effectiveSlip / 4.5)
      local spinIntensity = clamp01(slipVel / 5.0)
      local workIntensity = clamp01(pFriction / 12000.0)
      local kineticDrive = max(slipIntensity, spinIntensity, workIntensity)
      local slipScale = clamp01(max(slidingTransition, 0.20) * kineticDrive)
      activeSmoke = rawSmoke * slipScale
      wheelPeakSmoke[wheel.name] = max(wheelPeakSmoke[wheel.name] or 0.0, activeSmoke)
      wheelDecayTimer[wheel.name] = 0.0
    end

    local residualSmoke = 0.0
    local decayDuration = (type(smokeDecayBezier) == "table" and tonumber(smokeDecayBezier[1])) or smokeDecay or 1.50
    if isPavedSmokeSurface and asphaltSmokeEnabled and decayDuration > 0.02 and tSurface > onsetTemp then
      if not isActivelySlipping then
        local tTimer = (wheelDecayTimer[wheel.name] or 0.0) + dt
        wheelDecayTimer[wheel.name] = tTimer
        local peak = wheelPeakSmoke[wheel.name] or 0.0
        if peak > 0.01 and tTimer < decayDuration then
          local u = clamp01(tTimer / decayDuration)
          local dy0 = (type(smokeDecayBezier) == "table" and smokeDecayBezier[2]) or 1.00
          local dx1 = (type(smokeDecayBezier) == "table" and smokeDecayBezier[3]) or 0.25
          local dy1 = (type(smokeDecayBezier) == "table" and smokeDecayBezier[4]) or 0.95
          local dx2 = (type(smokeDecayBezier) == "table" and smokeDecayBezier[5]) or 0.65
          local dy2 = (type(smokeDecayBezier) == "table" and smokeDecayBezier[6]) or 0.15
          local decayCurve = evalCubicBezierWithOnset(u, dy0, dx1, dy1, dx2, dy2, 0.0)
          local thermalScale = clamp01((tSurface - onsetTemp) / 30.0)
          residualSmoke = peak * decayCurve * thermalScale
        else
          wheelPeakSmoke[wheel.name] = 0.0
        end
      end
    else
      wheelPeakSmoke[wheel.name] = 0.0
      wheelDecayTimer[wheel.name] = 0.0
    end

    local targetSmoke = max(activeSmoke, residualSmoke)

    local targetDust = 0.0
    if rawDust > 0.001 and sandDustEnabled and (profile and profile.kind == "dust") then
      targetDust = rawDust
    end

    local targetEmission = max(targetSmoke, targetDust)

    if targetEmission > 0.02 or slip > 1.0 or pFriction > 1500.0 or (isPavedSmokeSurface and tSurface > (onsetTemp - 5.0)) then
      activeFrictionDetected = true
    end

    -- Smooth attack and hot-tire residual decay filter:
    -- Smoke and Dust are filtered INDEPENDENTLY so that:
    -- 1. Settling sand dust never morphs into white rubber smoke upon touching asphalt.
    -- 2. Hot-tire pyrolysis decay retains its pure white balance independently of mineral dust.
    local prevSmoke = wheelFilteredSmoke[wheel.name] or 0.0
    local filteredSmoke = prevSmoke

    if targetSmoke > prevSmoke then
      if smokeOnset <= 0.05 then
        filteredSmoke = targetSmoke
      else
        local attackStep = dt / max(0.05, smokeOnset)
        filteredSmoke = min(targetSmoke, prevSmoke + attackStep)
      end
    else
      local decayStep = dt / max(0.05, decayDuration)
      filteredSmoke = max(targetSmoke, prevSmoke - decayStep)
    end
    filteredSmoke = clamp01(filteredSmoke)
    wheelFilteredSmoke[wheel.name] = filteredSmoke

    -- Mechanical granular dust dynamics:
    -- Immediate response upon wheel spin; fast settling (tau ≈ 0.30s) upon leaving loose terrain:
    local prevDust = wheelFilteredDust[wheel.name] or 0.0
    local filteredDust = prevDust
    if targetDust > prevDust then
      filteredDust = targetDust
    else
      local dustDecayStep = dt / 0.30
      filteredDust = max(targetDust, prevDust - dustDecayStep)
    end
    filteredDust = clamp01(filteredDust)
    wheelFilteredDust[wheel.name] = filteredDust

    local emission = max(filteredSmoke, filteredDust)
    if emergencyShutdownActive then
      filteredSmoke = 0.0
      filteredDust = 0.0
      emission = 0.0
    end
    wheelFilteredEmission[wheel.name] = emission
    
    local geometry = getWheelGeometry(wheel, sampleDt)
    local angularVelocity = tonumber(wheel.angularVelocity) or 0
    local wheelDir = tonumber(wheel.wheelDir) or 1
    result[#result + 1] = {
      name = wheel.name,
      worldOffset = geometry.legacyContact,
      contactOffset = geometry.contact,
      hubOffset = geometry.hub,
      hubVelocity = geometry.hubVelocity,
      spinAxis = geometry.spinAxis,
      axleAxis = geometry.axleAxis,
      groundNormal = geometry.groundNormal,
      forwardDir = geometry.forwardDir,
      angularVelocity = angularVelocity,
      rollingAngularVelocity = angularVelocity * wheelDir,
      wheelDir = wheelDir,
      radius = tonumber(wheel.dynamicRadius) or tonumber(wheel.radius) or 0.35,
      width = tonumber(wheel.tireWidth) or 0.20,
      contactDepth = tonumber(wheel.contactDepth) or 0,
      geometryValid = geometry.geometryValid,
      normalValid = geometry.normalValid,
      emit = emission,
      emitSmoke = filteredSmoke,
      emitDust = filteredDust,
      dustTint = dustTint,
      slip = slip,
      slipEnergy = tonumber(wheel.slipEnergy) or 0,
      normalLoad = tonumber(wheel.downForce) or 0,
      temperature = tSurface,
      contactPatchTemperature = tSurface,
      bulkTemperature = tBulk,
      skinTemperature = tSkin,
      material1 = tonumber(wheel.contactMaterialID1) or -1,
      material2 = tonumber(wheel.contactMaterialID2) or -1
    }
  end

  for index = 0, min(count - 1, 15) do
    processWheel(wheels.wheels[index])
  end
  for _, wheel in pairs(wheels.wheels) do
    processWheel(wheel)
  end

  hasActiveFriction = activeFrictionDetected

  local prof = vehicleProfile or computeVehicleProfile()
  local packet = {
    protocolVersion = protocolVersion,
    provenanceBuildId = provenanceBuildId,
    vehicleId = obj:getID(),
    wheels = result,
    profile = { prof.hoodHeightRatio, prof.windshieldSpan, prof.rearDeckRatio, prof.roofWidthRatio },
    particleGuardActive = (M.isParticleFilterGuardActive() == true)
  }
  obj:queueGameEngineLua("extensions.hook('onVolSmokeWheelTelemetry'," .. serialize(packet) .. ")")
end

local function checkTransientFriction()
  if not wheels or type(wheels.wheels) ~= "table" then return false end
  for _, wheel in pairs(wheels.wheels) do
    if wheel and not wheel.isBroken then
      local s1 = abs(tonumber(wheel.lastSlip) or 0)
      local s2 = abs(tonumber(wheel.lastSideSlip) or 0)
      if s1 > 1.0 or s2 > 1.0 then
        return true
      end
    end
  end
  return false
end

function M.updateGFX(dt)
  installParticleFilterGuard()
  updateTimer = updateTimer + max(0, tonumber(dt) or 0)
  if updateTimer <= 0 then return end
  local isTransient = hasActiveFriction or checkTransientFriction()
  if not isTransient and not frameSynchronousTelemetry and updateTimer < 0.05 then return end
  local sampleDt = updateTimer
  updateTimer = 0
  local ok, err = pcall(sendTelemetry, sampleDt)
  if not ok and log then log("E", "realSmoke3DVE", tostring(err)) end
end

function M.setFrameSynchronousTelemetry(enabled)
  frameSynchronousTelemetry = enabled == true
  updateTimer = 0
end

function M.setBurnoutEquity(thresh, sens, timeSec, onset, decay, bx1, by1, bx2, by2)
  if thresh ~= nil then heatThreshold = max(40.0, min(120.0, tonumber(thresh) or 70.0)) end
  if sens ~= nil then frictionSens = max(0.05, min(3.0, tonumber(sens) or 0.35)) end
  if timeSec ~= nil then frictionTime = max(0.0, min(3.0, tonumber(timeSec) or 2.00)) end
  if onset ~= nil then smokeOnset = max(0.05, min(3.0, tonumber(onset) or 2.00)) end
  if decay ~= nil then smokeDecay = max(0.0, min(5.0, tonumber(decay) or 1.50)) end
  if bx1 ~= nil and by1 ~= nil and bx2 ~= nil and by2 ~= nil then
    smokeOnsetBezier = {
      heatThreshold,
      0.0,
      max(0.0, min(1.0, tonumber(bx1) or 0.25)),
      max(0.0, min(1.0, tonumber(by1) or 0.05)),
      max(0.0, min(1.0, tonumber(bx2) or 0.55)),
      max(0.0, min(1.0, tonumber(by2) or 0.95))
    }
  end
end

function M.setSmokeDecayBezier(duration, y0, x1, y1, x2, y2)
  if type(duration) == "table" then
    local t = duration
    if #t >= 6 then
      smokeDecayBezier = {
        max(0.0, min(5.0, tonumber(t[1]) or 1.50)),
        max(0.00, min(1.00, tonumber(t[2]) or 1.00)),
        max(0.0, min(1.0, tonumber(t[3]) or 0.25)),
        max(0.0, min(1.0, tonumber(t[4]) or 0.95)),
        max(0.0, min(1.0, tonumber(t[5]) or 0.65)),
        max(0.0, min(1.0, tonumber(t[6]) or 0.15))
      }
    elseif #t == 5 then
      smokeDecayBezier = {
        max(0.0, min(5.0, tonumber(t[1]) or 1.50)),
        1.00,
        max(0.0, min(1.0, tonumber(t[2]) or 0.25)),
        max(0.0, min(1.0, tonumber(t[3]) or 0.95)),
        max(0.0, min(1.0, tonumber(t[4]) or 0.65)),
        max(0.0, min(1.0, tonumber(t[5]) or 0.15))
      }
    else
      smokeDecayBezier = {
        max(0.0, min(5.0, tonumber(t.duration) or 1.50)),
        max(0.00, min(1.00, tonumber(t.y0) or 1.00)),
        max(0.0, min(1.0, tonumber(t.x1) or 0.25)),
        max(0.0, min(1.0, tonumber(t.y1) or 0.95)),
        max(0.0, min(1.0, tonumber(t.x2) or 0.65)),
        max(0.0, min(1.0, tonumber(t.y2) or 0.15))
      }
    end
  elseif y2 ~= nil then
    smokeDecayBezier = {
      max(0.0, min(5.0, tonumber(duration) or 1.50)),
      max(0.00, min(1.00, tonumber(y0) or 1.00)),
      max(0.0, min(1.0, tonumber(x1) or 0.25)),
      max(0.0, min(1.0, tonumber(y1) or 0.95)),
      max(0.0, min(1.0, tonumber(x2) or 0.65)),
      max(0.0, min(1.0, tonumber(y2) or 0.15))
    }
  else
    smokeDecayBezier = {
      max(0.0, min(5.0, tonumber(duration) or 1.50)),
      1.00,
      max(0.0, min(1.0, tonumber(y0) or 0.25)),
      max(0.0, min(1.0, tonumber(x1) or 0.95)),
      max(0.0, min(1.0, tonumber(y1) or 0.65)),
      max(0.0, min(1.0, tonumber(x2) or 0.15))
    }
  end
  smokeDecay = smokeDecayBezier[1]
end

function M.setSmokeOnsetBezier(p1, p2, p3, p4, p5, p6, p7, p8)
  if p7 ~= nil and p8 ~= nil then
    -- 8 parameters: onsetTemp, initialHaze, x1, y1, x2, y2, endTemp, maxDensity
    heatThreshold = max(40.0, min(220.0, tonumber(p1) or 70.0))
    smokeOnsetBezier = {
      heatThreshold,
      max(0.0, min(1.00, tonumber(p2) or 0.0)),
      max(0.0, min(1.0, tonumber(p3) or 0.25)),
      max(0.0, min(1.0, tonumber(p4) or 0.05)),
      max(0.0, min(1.0, tonumber(p5) or 0.55)),
      max(0.0, min(1.0, tonumber(p6) or 0.95)),
      max(60.0, min(240.0, tonumber(p7) or 220.0)),
      max(0.0, min(1.00, tonumber(p8) or 1.00))
    }
  elseif p5 ~= nil and p6 ~= nil then
    -- 6 parameters: onsetTemp, initialHaze, x1, y1, x2, y2
    heatThreshold = max(40.0, min(120.0, tonumber(p1) or 70.0))
    smokeOnsetBezier = {
      heatThreshold,
      max(0.0, min(1.00, tonumber(p2) or 0.0)),
      max(0.0, min(1.0, tonumber(p3) or 0.25)),
      max(0.0, min(1.0, tonumber(p4) or 0.05)),
      max(0.0, min(1.0, tonumber(p5) or 0.55)),
      max(0.0, min(1.0, tonumber(p6) or 0.95)),
      220.0,
      1.00
    }
  elseif p1 ~= nil and p2 ~= nil and p3 ~= nil and p4 ~= nil then
    -- 4 parameters: x1, y1, x2, y2 (legacy)
    smokeOnsetBezier = {
      heatThreshold,
      0.0,
      max(0.0, min(1.0, tonumber(p1) or 0.25)),
      max(0.0, min(1.0, tonumber(p2) or 0.05)),
      max(0.0, min(1.0, tonumber(p3) or 0.55)),
      max(0.0, min(1.0, tonumber(p4) or 0.95)),
      220.0,
      1.00
    }
  end
end

function M.computeVehicleProfile()
  return computeVehicleProfile()
end

function M.getBurnoutEquity()
  return {
    heatThreshold = heatThreshold,
    frictionSens = frictionSens,
    frictionTime = frictionTime,
    smokeOnset = smokeOnset,
    smokeOnsetBezier = smokeOnsetBezier,
    smokeDecay = smokeDecay,
    smokeDecayBezier = smokeDecayBezier
  }
end

function M.setSurfaceTuning(sandScale, sandSens, sandActive, asphaltActive)
  if sandScale ~= nil then sandDustScale = max(0.0, min(3.0, tonumber(sandScale) or 1.00)) end
  if sandSens ~= nil then sandDustSens = max(0.05, min(3.0, tonumber(sandSens) or 1.00)) end
  if sandActive ~= nil then sandDustEnabled = (sandActive == true or sandActive == 1 or sandActive == "1") end
  if asphaltActive ~= nil then asphaltSmokeEnabled = (asphaltActive == true or asphaltActive == 1 or asphaltActive == "1") end
end

function M.getSurfaceTuning()
  return {
    sandDustScale = sandDustScale,
    sandDustSens = sandDustSens,
    sandDustEnabled = sandDustEnabled,
    asphaltSmokeEnabled = asphaltSmokeEnabled
  }
end

local emergencyShutdownActive = false

local function emergencyShutdown()
  emergencyShutdownActive = true
end
M.emergencyShutdown = emergencyShutdown

function M.onReset()
  emergencyShutdownActive = false
  resetTireThermals()
  installParticleFilterGuard()
  computeVehicleProfile()
  if obj and type(obj.queueGameEngineLua) == "function" then
    local vid = (type(obj.getID) == "function" and obj:getID()) or (type(obj.getId) == "function" and obj:getId()) or -1
    obj:queueGameEngineLua(string.format("if realSmoke3DGE and realSmoke3DGE.onVehicleReset then realSmoke3DGE.onVehicleReset(%d) end", vid))
  end
end

function M.reset()
  M.onReset()
end

function M.onExtensionLoaded()
  resetTireThermals()
  installParticleFilterGuard()
  computeVehicleProfile()
end

function M.isParticleFilterGuardActive()
  local pf = rawget(_G, "particlefilter") or particlefilter
  return (pf ~= nil and pf.nodeCollision == particleFilterGuardHook)
end

M.installParticleFilterGuard = installParticleFilterGuard

return M
