# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Set CMake minimum version
cmake_minimum_required (VERSION 3.10.2)

# Set project name
project (Urho3D-Launcher)

# Set CMake modules search path
set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/Modules)

# Include UrhoCommon.cmake module after setting project name
include (UrhoCommon)

add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/../../Source/Tools/Urho3DPlayer Urho3DPlayer)
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/../../Source/Samples Samples)
