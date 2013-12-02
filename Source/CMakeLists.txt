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

# Set CMake modules search path
set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)

# Enable AngelScript by default
if (NOT DEFINED ENABLE_ANGEL_SCRIPT)
    set (ENABLE_ANGEL_SCRIPT 1)
endif ()

# Include Urho3D cmake module
include (Urho3D-CMake-magic)

# Check existence of stdint.h for LibCpuId
include (CheckIncludeFiles)
CHECK_INCLUDE_FILES (stdint.h HAVE_STDINT_H)
if (HAVE_STDINT_H)
    add_definitions (-DHAVE_STDINT_H)
endif ()

# Setup SDK install destinations
if (WIN32)
    # CMake already automatically prepends "Urho3D" to CMAKE_INSTALL_PREFIX on Windows platform
    set (SCRIPT_PATTERN *.bat)
else ()
    set (PATH_SUFFIX /Urho3D)
    if (ENABLE_64BIT)   # TODO: Revisit this again when ARM also supports 64bit, for now ARM architecture ignores ENABLE_64BIT build option
        if (NOT CMAKE_CROSSCOMPILING AND EXISTS /usr/lib64)
            # Probably target system is a RedHat-based distro
            set (LIB_SUFFIX 64)
        endif ()
    endif ()
    if (IOS)
        # Use 'ios' arch subdirectory to differentiate, in case both Mac OS X and iOS build are installed at the same destination
        set (LIB_SUFFIX ${LIB_SUFFIX}/ios)
    endif ()
    set (SCRIPT_PATTERN *.sh)
endif ()
set (DEST_INCLUDE_DIR include${PATH_SUFFIX})
set (DEST_SHARE_DIR share${PATH_SUFFIX})
set (DEST_RUNTIME_DIR ${DEST_SHARE_DIR}/Bin)
set (DEST_LIBRARY_DIR lib${LIB_SUFFIX}${PATH_SUFFIX})   # Note to Linux package maintainer: ${PATH_SUFFIX} for library could be patched out if the suffix is not desirable
set (DEST_PKGCONFIG_DIR lib${LIB_SUFFIX}/pkgconfig)
# Install application launcher scripts
file (GLOB APP_SCRIPTS ${PROJECT_ROOT_DIR}/Bin/${SCRIPT_PATTERN})
install (FILES ${APP_SCRIPTS} DESTINATION ${DEST_RUNTIME_DIR} PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)   # 755
# Install resource directories required by applications built with Urho3D library
install (DIRECTORY ${PROJECT_ROOT_DIR}/Bin/CoreData ${PROJECT_ROOT_DIR}/Bin/Data DESTINATION ${DEST_RUNTIME_DIR} USE_SOURCE_PERMISSIONS)
# Install CMake modules and toolchains provided by and for Urho3D
install (DIRECTORY ${PROJECT_ROOT_DIR}/Source/CMake/ DESTINATION ${DEST_SHARE_DIR}/CMake USE_SOURCE_PERMISSIONS)    # Note: the trailing slash is significant
# Install CMake launcher scripts
file (GLOB CMAKE_SCRIPTS ${PROJECT_ROOT_DIR}/${SCRIPT_PATTERN})
install (FILES ${CMAKE_SCRIPTS} DESTINATION ${DEST_SHARE_DIR}/Scripts PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

# Add targets
foreach (TARGET Bullet Civetweb Detour FreeType JO kNet LZ4 PugiXml Recast SDL StanHull STB)
    add_subdirectory (ThirdParty/${TARGET})
endforeach ()

if (ENABLE_ANGEL_SCRIPT)
    add_subdirectory(ThirdParty/AngelScript)
endif ()

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

# Urho3D game engine library
add_subdirectory (Engine)

# Urho3D tools
add_subdirectory (Tools)

# Urho3D samples
# Samples are built on iOS platform too when enabled
# Although samples should also work for Android platform, currently there is no available mechanism to package each sample apps into individual *.apk
if (NOT ANDROID AND ENABLE_SAMPLES)
    add_subdirectory (Samples)
endif ()

# Urho3D extras
# Do not build extras for iOS and Android regardless of its build option 
if (NOT IOS AND NOT ANDROID AND ENABLE_EXTRAS)   
    add_subdirectory (Extras)
endif ()

# Urho3D documentation
add_subdirectory (../Docs ${PROJECT_BINARY_DIR}/Docs)
