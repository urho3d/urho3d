#
# Copyright (c) 2008-2014 the Urho3D project.
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

# Include Urho3D cmake common module
include (Urho3D-CMake-common)

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

# Setup package variables
set (URHO3D_DESCRIPTION "Urho3D is a lightweight, cross-platform rendering and game engine implemented in C++ and released under the MIT license. Greatly inspired by OGRE (http://www.ogre3d.org) and Horde3D (http://www.horde3d.org).")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY ${URHO3D_DESCRIPTION})
set (URHO3D_URL "https://github.com/urho3d/Urho3D")
set (CPACK_PACKAGE_VENDOR ${URHO3D_URL})
set (CPACK_PACKAGE_CONTACT ${URHO3D_URL})
execute_process (COMMAND ${CMAKE_COMMAND} -P ${PROJECT_SOURCE_DIR}/CMake/Modules/GetUrho3DRevision.cmake OUTPUT_VARIABLE URHO3D_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
set (CPACK_PACKAGE_VERSION ${URHO3D_VERSION})
string (REGEX MATCH "([^.]+)\\.([^.]+)\\.(.+)" MATCHED ${URHO3D_VERSION})
if (MATCHED)
    set (CPACK_PACKAGE_VERSION_MAJOR ${CMAKE_MATCH_1})
    set (CPACK_PACKAGE_VERSION_MINOR ${CMAKE_MATCH_2})
    set (CPACK_PACKAGE_VERSION_PATCH ${CMAKE_MATCH_3})
endif ()
set (CPACK_RESOURCE_FILE_LICENSE ${PROJECT_ROOT_DIR}/License.txt)
set (CPACK_SYSTEM_NAME ${CMAKE_SYSTEM_NAME})
set (CPACK_GENERATOR TGZ)
if (ANDROID)
    set (CPACK_SYSTEM_NAME Android)
elseif (RASPI)
    set (CPACK_SYSTEM_NAME Raspberry-Pi)
elseif (IOS)
    set (CPACK_SYSTEM_NAME iOS)
elseif (APPLE)
    set (CPACK_SYSTEM_NAME OSX)
elseif (WIN32)
    set (CPACK_GENERATOR ZIP)
elseif (CPACK_SYSTEM_NAME STREQUAL Linux)
    list (APPEND CPACK_GENERATOR RPM DEB)
endif ()
if (ENABLE_64BIT)
    set (CPACK_SYSTEM_NAME ${CPACK_SYSTEM_NAME}-64bit)
endif ()
set (CPACK_SYSTEM_NAME ${CPACK_SYSTEM_NAME}-${URHO3D_LIB_TYPE})
if ("$ENV{RELEASE_TAG}" STREQUAL "")
    set (CPACK_SYSTEM_NAME ${CPACK_SYSTEM_NAME}-snapshot)
endif ()
include (CPack)

# Add targets
foreach (TARGET Box2D Bullet Civetweb Detour FreeType JO kNet LZ4 PugiXml Recast SDL StanHull STB)
    add_subdirectory (ThirdParty/${TARGET})
endforeach ()
if (ENABLE_ANGELSCRIPT)
    add_subdirectory (ThirdParty/AngelScript)
endif ()
if (ENABLE_LUA)
    add_subdirectory (Engine/LuaScript)
    add_subdirectory (ThirdParty/Lua${JIT})
    add_subdirectory (ThirdParty/toluapp/src/lib)
endif ()
if (NOT IOS AND NOT ANDROID AND NOT RASPI)
    if (USE_OPENGL)
        add_subdirectory (ThirdParty/GLEW)
    else ()
        add_subdirectory (ThirdParty/MojoShader)
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
