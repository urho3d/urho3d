#
# Copyright (c) 2008-2013 the Urho3D project.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#

# Set project name
project (Urho3D)

# Set minimum version
cmake_minimum_required (VERSION 2.8.6)

if (COMMAND cmake_policy)
    cmake_policy (SET CMP0003 NEW)
endif ()

# Add cmake modules search path
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/Modules/")

# Include Urho3D cmake module
include (Urho3D-CMake-magic)

# Check existence of stdint.h for LibCpuId
include (CheckIncludeFiles)
CHECK_INCLUDE_FILES (stdint.h HAVE_STDINT_H)
if (HAVE_STDINT_H)
    add_definitions (-DHAVE_STDINT_H)
endif ()

# Add definitions for GLEW
if (NOT IOS AND NOT ANDROID AND NOT RASPI AND USE_OPENGL)
    add_definitions (-DGLEW_STATIC)
    add_definitions (-DGLEW_NO_GLU)
endif ()

# Add definition for Lua and LuaJIT
if (ENABLE_LUAJIT)
    add_definitions (-DENABLE_LUAJIT)
    set (JIT "JIT")
    # Implied ENABLE_LUA
    set (ENABLE_LUA 1)
endif ()
if (ENABLE_LUA)
    add_definitions (-DENABLE_LUA)
endif ()

# Add global include directories for export header and SDL header
include_directories (${CMAKE_BINARY_DIR}/Engine ThirdParty/SDL/include)

# Setup the compiler flags for building shared library
if (URHO3D_LIB_TYPE STREQUAL SHARED)
    # Hide the symbols that are not explicitly marked for export
    add_compiler_export_flags ()
    # Use PIC on platforms that support it 
    set (CMAKE_POSITION_INDEPENDENT_CODE true)
endif ()

# Add targets
foreach (TARGET Audio Container Core Engine Graphics Input IO Math Navigation Network Physics Resource Scene Script UI)
    add_subdirectory (Engine/${TARGET})
endforeach ()
foreach (TARGET AngelScript Bullet Civetweb Detour FreeType JO kNet LZ4 PugiXml Recast SDL StanHull STB)
    add_subdirectory (ThirdParty/${TARGET})
endforeach ()
if (ENABLE_LUA)
    add_subdirectory (Engine/LuaScript)
    add_subdirectory (ThirdParty/Lua${JIT})
    add_subdirectory (ThirdParty/tolua++/src/lib)
endif ()
if (NOT IOS AND NOT ANDROID AND NOT RASPI)
    if (USE_OPENGL)
        add_subdirectory (ThirdParty/GLEW)
    endif ()
    add_subdirectory (ThirdParty/LibCpuId)
endif ()

# Urho3D game engine library targets
add_subdirectory (Engine)

# Urho3D tool targets
add_subdirectory (Tools)

# Urho3D samples
# Samples are built on iOS platform too when enabled
# Although samples should also work for Android platform, currently there is no available mechanism to package each sample apps into individual *.apk
if (NOT ANDROID AND ENABLE_SAMPLES)
    add_subdirectory (Samples)
endif ()

# Do not build extras for iOS and Android regardless of its build option 
if (NOT IOS AND NOT ANDROID AND ENABLE_EXTRAS)   
    # Urho3D extras
    add_subdirectory (Extras/OgreBatchConverter)
endif ()

# Generate platform specific Doxyfile automatically
if (NOT USE_OPENGL EQUAL DOXYFILE_USE_OPENGL OR ${PROJECT_ROOT_DIR}/Docs/Doxyfile.in IS_NEWER_THAN ${PROJECT_ROOT_DIR}/Doxyfile)
    set (DOXYFILE_USE_OPENGL ${USE_OPENGL} CACHE INTERNAL "USE_OPENGL flag when Doxyfile was last generated")
    if (USE_OPENGL)
        set (EXCLUDE_GRAPHICS_API Direct3D9)
    else ()
        set (EXCLUDE_GRAPHICS_API OpenGL)
    endif ()
    configure_file (${PROJECT_ROOT_DIR}/Docs/Doxyfile.in ${PROJECT_ROOT_DIR}/Doxyfile) 
endif ()

# Reference supported build options that are potentially not being referenced due to platform or build type branching to suppress "unused variable" warning
if (ENABLE_SAMPLES AND ENABLE_EXTRAS AND ENABLE_TOOLS AND
    ENABLE_MINIDUMPS AND USE_MKLINK AND USE_STATIC_RUNTIME AND
    SCP_TO_TARGET AND
    ANDROID_ABI AND
    ENABLE_SAFE_LUA)
endif()
