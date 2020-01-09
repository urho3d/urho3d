#
# Copyright (c) 2008-2020 the Urho3D project.
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

# Set CMake minimum version and CMake policy required by UrhoCommon module
cmake_minimum_required (VERSION 3.14.5)
if (COMMAND cmake_policy)
    # Libraries linked via full path no longer produce linker search paths
    cmake_policy (SET CMP0003 NEW)
    # INTERFACE_LINK_LIBRARIES defines the link interface
    cmake_policy (SET CMP0022 NEW)
    # Disallow use of the LOCATION target property - so we set to OLD as we still need it
    cmake_policy (SET CMP0026 OLD)
    # MACOSX_RPATH is enabled by default
    cmake_policy (SET CMP0042 NEW)
    # Honor the visibility properties for SHARED target types only
    cmake_policy (SET CMP0063 OLD)
endif ()

# Set project name
project (Urho3D)

# Set CMake modules search path
set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)

# Include UrhoCommon.cmake module after setting project name
include (UrhoCommon)

# Setup SDK install destinations
set (PATH_SUFFIX Urho3D)
if (WIN32)
    set (SCRIPT_EXT .bat)
    if (CMAKE_HOST_WIN32)
        set (PATH_SUFFIX .)
    endif ()
else ()
    set (SCRIPT_EXT .sh)
endif ()
if (URHO3D_64BIT)
    # Install to 'lib64' when one of these conditions is true
    if ((MINGW AND CMAKE_CROSSCOMPILING) OR URHO3D_USE_LIB64_RPM OR (HAS_LIB64 AND NOT URHO3D_USE_LIB_DEB))
        set (LIB_SUFFIX 64)
    endif ()
endif ()
set (DEST_INCLUDE_DIR include/Urho3D)    # The include directory path contains the 'Urho3D' suffix regardless of PATH_SUFFIX variable
set (DEST_SHARE_DIR share/${PATH_SUFFIX})
set (DEST_BUNDLE_DIR ${DEST_SHARE_DIR}/Applications)
# Note to package maintainer: ${PATH_SUFFIX} for library could be removed if the extra path is not desired, but if so then the RPATH setting in Source's CMakeLists.txt needs to be adjusted accordingly
set (DEST_LIBRARY_DIR lib${LIB_SUFFIX}/${PATH_SUFFIX})
set (DEST_PKGCONFIG_DIR lib${LIB_SUFFIX}/pkgconfig)
# Install application launcher scripts
file (GLOB APP_SCRIPTS ${CMAKE_SOURCE_DIR}/bin/*${SCRIPT_EXT})
install (PROGRAMS ${APP_SCRIPTS} DESTINATION ${DEST_RUNTIME_DIR})   # DEST_RUNTIME_DIR variable is set by the set_output_directories() macro call in the UrhoCommon module
# Install CMake modules and toolchains provided by and for Urho3D
install (DIRECTORY ${CMAKE_SOURCE_DIR}/CMake/ DESTINATION ${DEST_SHARE_DIR}/CMake)    # Note: the trailing slash is significant
# Install CMake build scripts
file (GLOB CMAKE_SCRIPTS ${CMAKE_SOURCE_DIR}/script/*${SCRIPT_EXT})
install (PROGRAMS ${CMAKE_SCRIPTS} DESTINATION ${DEST_SHARE_DIR}/Scripts)

# Setup package variables
set (URHO3D_DESCRIPTION "Urho3D is a free lightweight, cross-platform 2D and 3D game engine implemented in C++ and released under the MIT license. Greatly inspired by OGRE (http://www.ogre3d.org) and Horde3D (http://www.horde3d.org).")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY ${URHO3D_DESCRIPTION})
set (URHO3D_URL "https://github.com/urho3d/Urho3D")
set (CPACK_PACKAGE_VENDOR ${URHO3D_URL})
set (CPACK_PACKAGE_CONTACT ${URHO3D_URL})
execute_process (COMMAND ${CMAKE_COMMAND} -P ${CMAKE_SOURCE_DIR}/CMake/Modules/GetUrhoRevision.cmake WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} OUTPUT_VARIABLE URHO3D_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
set (CPACK_PACKAGE_VERSION ${URHO3D_VERSION})
string (REGEX MATCH "([^.]+)\\.([^.]+)\\.(.+)" MATCHED ${URHO3D_VERSION})
if (MATCHED)
    set (CPACK_PACKAGE_VERSION_MAJOR ${CMAKE_MATCH_1})
    set (CPACK_PACKAGE_VERSION_MINOR ${CMAKE_MATCH_2})
    set (CPACK_PACKAGE_VERSION_PATCH ${CMAKE_MATCH_3})
endif ()
set (CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENSE)
set (CPACK_SYSTEM_NAME ${CMAKE_SYSTEM_NAME})
set (CPACK_GENERATOR TGZ)
if (ANDROID)
    set (CPACK_SYSTEM_NAME Android)
elseif (IOS)
    set (CPACK_SYSTEM_NAME iOS)
elseif (TVOS)
    set (CPACK_SYSTEM_NAME tvOS)
elseif (APPLE)
    set (CPACK_SYSTEM_NAME macOS)
elseif (WIN32)
    if (MINGW)
        set (CPACK_SYSTEM_NAME MinGW)   # MinGW implies Windows platform
    endif ()
    if (CMAKE_HOST_WIN32)
        set (CPACK_GENERATOR ZIP)       # Differentiate artifacts generated from Windows host system
    endif ()
elseif (WEB)
    set (CPACK_SYSTEM_NAME Web)
elseif (CPACK_SYSTEM_NAME STREQUAL Linux)
    if (RPI)
        set (CPACK_SYSTEM_NAME Raspberry-Pi)
        set (CPACK_DEBIAN_PACKAGE_ARCHITECTURE armhf)
    elseif (ARM)
        set (CPACK_SYSTEM_NAME ARM)     # Generic ARM
        if (URHO3D_64BIT)
            set (CPACK_DEBIAN_PACKAGE_ARCHITECTURE arm64)
        else ()
            set (CPACK_DEBIAN_PACKAGE_ARCHITECTURE armhf)
        endif ()
    elseif (NOT URHO3D_64BIT)
        set (CPACK_DEBIAN_PACKAGE_ARCHITECTURE i386)
        set (CPACK_RPM_PACKAGE_ARCHITECTURE i686)       # The 'package' target should be built with the help of 'setarch i686' command on a 64-bit host system
    endif ()
    # TODO: Temporary disable RPM and DEB package generation for CI as it has run out of disk space for a few of the target platforms.
    if (NOT DEFINED ENV{CI})
        if (NOT URHO3D_64BIT OR HAS_LIB64)
            list (APPEND CPACK_GENERATOR RPM)
        endif ()
        if (NOT URHO3D_64BIT OR NOT HAS_LIB64)
            list (APPEND CPACK_GENERATOR DEB)
        endif ()
        if (URHO3D_64BIT)
            if (URHO3D_USE_LIB64_RPM AND NOT HAS_LIB64)
                set (CPACK_GENERATOR RPM)
            elseif (URHO3D_USE_LIB_DEB AND HAS_LIB64)
                set (CPACK_GENERATOR DEB)
            endif ()
        endif ()
    endif ()
endif ()
if (URHO3D_64BIT)
    set (CPACK_SYSTEM_NAME ${CPACK_SYSTEM_NAME}-64bit)
endif ()
set (CPACK_SYSTEM_NAME ${CPACK_SYSTEM_NAME}-${URHO3D_LIB_TYPE})
if (WIN32 AND NOT URHO3D_OPENGL)
    if (URHO3D_D3D11)
        set (CPACK_SYSTEM_NAME ${CPACK_SYSTEM_NAME}-3D11)   # The artifact name has a space constraint on our website when viewed in a mobile browser, 3D11 stands for Direct3D 11
    else ()
        set (CPACK_SYSTEM_NAME ${CPACK_SYSTEM_NAME}-3D9)
    endif ()
elseif (ANDROID)
    set (CPACK_SYSTEM_NAME ${CPACK_SYSTEM_NAME}-${ANDROID_ABI})
elseif (RPI AND RPI_ABI MATCHES ^armeabi-v7a)
    set (CPACK_SYSTEM_NAME ${CPACK_SYSTEM_NAME}-v7a)
elseif (ARM_ABI_FLAGS)
    string (REGEX REPLACE "^.*mcpu=([^ ]+).*$" -\\1 CPU_NAME "${ARM_ABI_FLAGS}")
    string (REGEX REPLACE .*- - CPU_NAME "${CPU_NAME}")
    string (TOUPPER "${CPU_NAME}" CPU_NAME)
    set (CPACK_SYSTEM_NAME ${CPACK_SYSTEM_NAME}${CPU_NAME})
endif ()
if (NOT DEFINED ENV{RELEASE_TAG})
    set (CPACK_SYSTEM_NAME ${CPACK_SYSTEM_NAME}-snapshot)
endif ()
include (CPack)

# Setup macOS, iOS, and tvOS bundle variables
if (URHO3D_MACOSX_BUNDLE OR (APPLE AND ARM))
    if (NOT MACOSX_BUNDLE_ICON_FILE)
        set (MACOSX_BUNDLE_ICON_FILE UrhoIcon)
    endif ()
    if (NOT MACOSX_BUNDLE_BUNDLE_VERSION)
        set (MACOSX_BUNDLE_BUNDLE_VERSION ${URHO3D_VERSION})
    endif ()
    if (NOT MACOSX_BUNDLE_LONG_VERSION_STRING)
        set (MACOSX_BUNDLE_LONG_VERSION_STRING ${URHO3D_VERSION})
    endif ()
    if (NOT MACOSX_BUNDLE_SHORT_VERSION_STRING)
        set (MACOSX_BUNDLE_SHORT_VERSION_STRING ${URHO3D_VERSION})
    endif ()
    if (NOT MACOSX_BUNDLE_COPYRIGHT)
        set (MACOSX_BUNDLE_COPYRIGHT "Copyright (c) 2008-2020 the Urho3D project.")
    endif ()
endif ()

# Setup SDK-like include dir in the build tree for building the Urho3D library
if (ANDROID AND GRADLE_BUILD_DIR)
    set (THIRD_PARTY_INCLUDE_DIR ${GRADLE_BUILD_DIR}/tree/${CMAKE_BUILD_TYPE}/${ANDROID_ABI}/${DEST_INCLUDE_DIR}/ThirdParty)
else ()
    set (THIRD_PARTY_INCLUDE_DIR ${CMAKE_BINARY_DIR}/${DEST_INCLUDE_DIR}/ThirdParty)
endif ()
file (MAKE_DIRECTORY ${THIRD_PARTY_INCLUDE_DIR})

# Urho3D source
add_subdirectory (Source)

# Urho3D documentation
add_subdirectory (Docs)
