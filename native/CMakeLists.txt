cmake_minimum_required(VERSION 3.24)
project(RealSmoke3DAddon LANGUAGES CXX)

# Reconstruction scaffold only. Supply RESHADE_INCLUDE_DIR for a compatible
# ReShade SDK checkout. The implementation sources are added as they are
# reconstructed; this project is not currently a complete add-on build.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RESHADE_INCLUDE_DIR "" CACHE PATH "Directory containing reshade.hpp")
if(NOT RESHADE_INCLUDE_DIR)
  message(STATUS "Set RESHADE_INCLUDE_DIR to a compatible ReShade add-on SDK before adding native targets.")
endif()
