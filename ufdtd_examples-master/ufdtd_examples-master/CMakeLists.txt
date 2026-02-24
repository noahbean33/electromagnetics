cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(ufdtd LANGUAGES C VERSION 0.1)

set(DEFAULT_BUILD_TYPE "Debug")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  # generate information for LSP servers
  set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
endif()

# Use pkg-config module
include(FindPkgConfig)
# Aux functions
include(cMake/functions.cmake)
include(cMake/SetupPETSC.cmake)
include(cMake/SetupMPI.cmake)

# Add examples target
add_subdirectory(examples)
