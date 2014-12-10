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

# Find Urho3D include directories and library in source & build tree or installed Urho3D SDK.
#
#  URHO3D_FOUND
#  URHO3D_INCLUDE_DIRS
#  URHO3D_LIBRARIES
#  URHO3D_LIBRARIES_REL
#  URHO3D_LIBRARIES_DBG
#
#
# For Urho3D project, the Urho3D library "source tree" and "build tree" paths are already known.
#
# For external project that attempts to use the Urho3D source and build trees:
#   1) Set the URHO3D_HOME environment variable to poin to the location of Urho3D "source tree"
#   2) Set the URHO3D_BUILD_TREE environment variable to point to the location of Urho3D "build tree"
# This module would not assume the location of the build tree anymore as in the previous versions.
#
# For external project that attempts to use the installed Urho3D SDK:
#   1) Install the SDK into your filesystem.
#      If you change the default value of CMAKE_INSTALL_PREFIX variable and/or if you use DESTDIR variable during installation, then proceed to 2)
#   2) Set the CMAKE_PREFIX_PATH environment variable to point to the location of installed Urho3D SDK.
#      The CMAKE_PREFIX_PATH should be set to a parent directory containing both the "include" or "lib" subdirectories.
#      For example on Windows platform: set "CMAKE_PREFIX_PATH=C:/Users/john/Urho3D" if the SDK is installed using CMAKE_INSTALL_PREFIX=C:/Users/john/Urho3D
#      For example on Linux platform: export CMAKE_PREFIX_PATH=/home/john/usr/local if the SDK is installed using DESTDIR=/home/john and CMAKE_INSTALL_PREFIX=/usr/local
# You may use semicolon to separate multiple prefix paths to other SDKs intalled in custom location.
#

if (URHO3D_FOUND)
    # All the subprojects should use the same Urho3D library, so only need to search on the first (sub)project that requires Urho3D library
    return ()
endif ()

# If the URHO3D_LIB_TYPE build option changes then invalidate the found library cache
if (NOT URHO3D_LIB_TYPE STREQUAL URHO3D_FOUND_LIB_TYPE)
    unset (URHO3D_LIBRARIES CACHE)
    set (URHO3D_FOUND_LIB_TYPE ${URHO3D_LIB_TYPE} CACHE INTERNAL "Lib type when Urho3D library was last found")

    # Urho3D prefers static library type by default while CMake prefers shared one, so we need to change CMake preference to agree with Urho3D
    if (NOT URHO3D_LIB_TYPE STREQUAL SHARED)
        list (REVERSE CMAKE_FIND_LIBRARY_SUFFIXES)
    endif ()
endif ()

if (CMAKE_PROJECT_NAME STREQUAL Urho3D AND TARGET Urho3D)
    set (URHO3D_HOME ${CMAKE_SOURCE_DIR} CACHE PATH "Path to Urho3D source tree" FORCE)
    set (IS_INTERNAL 1)
elseif (NOT URHO3D_HOME AND DEFINED ENV{URHO3D_HOME})
    # The URHO3D_HOME variable should point to Urho3D's source tree, even when Urho3D is being used in an external project which has its own source tree
    if (NOT DEFINED ENV{URHO3D_BUILD_TREE})
        message (FATAL_ERROR "Could not determine the Urho3D build tree location. Use URHO3D_BUILD_TREE environment variable to specify the location of the build tree.")
    endif ()
    file (TO_CMAKE_PATH "$ENV{URHO3D_HOME}" URHO3D_HOME)
    set (URHO3D_HOME ${URHO3D_HOME} CACHE PATH "Path to Urho3D source tree")
    file (TO_CMAKE_PATH "$ENV{URHO3D_BUILD_TREE}" URHO3D_BUILD_TREE)
    set (URHO3D_BUILD_TREE ${URHO3D_BUILD_TREE} CACHE PATH "Path to Urho3D build tree")
endif ()

if (URHO3D_HOME)
    # Using source tree
    if (EXISTS ${URHO3D_HOME}/Source/Engine/Urho3D.h.in)
        set (ENGINE_DIRS Audio Container Core Engine Graphics Input IO Math Resource Scene UI)
        set (THIRDPARTY_DIRS SDL/include)
        if (URHO3D_ANGELSCRIPT)
            list (APPEND ENGINE_DIRS Script)
            list (APPEND THIRDPARTY_DIRS AngelScript/include)
        endif ()
        if (URHO3D_LUA)
            list (APPEND ENGINE_DIRS LuaScript)
        endif ()
        if (URHO3D_NETWORK)
            list (APPEND ENGINE_DIRS Network)
            list (APPEND THIRDPARTY_DIRS kNet/include)
        endif ()
        if (URHO3D_NAVIGATION)
            list (APPEND ENGINE_DIRS Navigation)
        endif ()
        if (URHO3D_PHYSICS)
            list (APPEND ENGINE_DIRS Physics)
            list (APPEND THIRDPARTY_DIRS Bullet/src)
        endif ()
        if (URHO3D_URHO2D)
            list (APPEND ENGINE_DIRS Urho2D)
            list (APPEND THIRDPARTY_DIRS Box2D)
        endif ()
        set (URHO3D_INCLUDE_DIRS ${URHO3D_HOME}/Source/Engine)
        if (IS_INTERNAL)
            list (APPEND URHO3D_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/Source/Engine)
        else ()
            list (APPEND URHO3D_INCLUDE_DIRS ${URHO3D_BUILD_TREE}/Source/Engine)
        endif ()
        foreach (DIR ${ENGINE_DIRS})
            list (APPEND URHO3D_INCLUDE_DIRS ${URHO3D_HOME}/Source/Engine/${DIR})
        endforeach ()
        foreach (DIR ${THIRDPARTY_DIRS})
            list (APPEND URHO3D_INCLUDE_DIRS ${URHO3D_HOME}/Source/ThirdParty/${DIR})
        endforeach ()
    endif ()
endif ()

if (IS_INTERNAL)
    set (URHO3D_LIBRARIES Urho3D)
    set (FOUND_MESSAGE "Found Urho3D: as CMake target")
else ()
    set (URHO3D_LIB_NAMES Urho3D)
    if (WIN32)
        set (URHO3D_LIB_NAMES_DBG ${URHO3D_LIB_NAMES}_d)
    endif ()
    if (URHO3D_BUILD_TREE)
        # Using build tree
        if (ANDROID)
            set (URHO3D_LIB_SEARCH_PATH ${URHO3D_BUILD_TREE}/libs/${ANDROID_NDK_ABI_NAME})
        else ()
            set (URHO3D_LIB_SEARCH_PATH ${URHO3D_BUILD_TREE}/Lib)
        endif ()
        # Only perform a non-rooted search in the specified path
        find_library (URHO3D_LIBRARIES NAMES ${URHO3D_LIB_NAMES} PATHS ${URHO3D_LIB_SEARCH_PATH} NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
        if (WIN32)
            find_library (URHO3D_LIBRARIES_DBG NAMES ${URHO3D_LIB_NAMES_DBG} PATHS ${URHO3D_LIB_SEARCH_PATH} NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
        endif ()
    else ()
        # Using SDK installation
        if (NOT CMAKE_HOST_WIN32)
            set (PATH_SUFFIX Urho3D)
            if (IOS)
                set (CMAKE_LIBRARY_ARCHITECTURE ios)
            endif ()
        endif ()
        if (ANDROID)
            if (PATH_SUFFIX)
                set (PATH_SUFFIX ${PATH_SUFFIX}/${ANDROID_NDK_ABI_NAME})
            else ()
                set (PATH_SUFFIX ${ANDROID_NDK_ABI_NAME})
            endif ()
        endif ()
        # Perform a full search including a rooted search
        find_path (URHO3D_INCLUDE_DIRS Urho3D.h PATH_SUFFIXES ${PATH_SUFFIX})
        find_library (URHO3D_LIBRARIES NAMES ${URHO3D_LIB_NAMES} PATH_SUFFIXES ${PATH_SUFFIX})
        if (WIN32)
            find_library (URHO3D_LIBRARIES_DBG NAMES ${URHO3D_LIB_NAMES_DBG} PATH_SUFFIXES ${PATH_SUFFIX})
        endif ()
        if (URHO3D_INCLUDE_DIRS)
            set (BASE_DIR ${URHO3D_INCLUDE_DIRS})
            set (DIRS SDL)
            if (URHO3D_ANGELSCRIPT)
                list (APPEND DIRS AngelScript)
            endif ()
            if (URHO3D_NETWORK)
                list (APPEND DIRS kNet)
            endif ()
            if (URHO3D_PHYSICS)
                list (APPEND DIRS Bullet)
            endif ()
            if (URHO3D_URHO2D)
                list (APPEND DIRS Box2D)
            endif ()
            foreach (DIR ${DIRS})
                list (APPEND URHO3D_INCLUDE_DIRS ${BASE_DIR}/${DIR})     # Note: variable change to list context after this, so we need BASE_DIR to remain the same
            endforeach ()
        endif ()
    endif ()
endif ()

if (WIN32)
    set (URHO3D_LIBRARIES_REL ${URHO3D_LIBRARIES})
    if (URHO3D_LIBRARIES)
        if (URHO3D_LIBRARIES_DBG)
            list (APPEND URHO3D_LIBRARIES ${URHO3D_LIBRARIES_DBG})
        endif ()
    else ()
        set (URHO3D_LIBRARIES ${URHO3D_LIBRARIES_DBG})
    endif ()
endif ()

if (URHO3D_INCLUDE_DIRS AND URHO3D_LIBRARIES)
    set (URHO3D_FOUND 1)
    if (NOT FOUND_MESSAGE)
        set (FOUND_MESSAGE "Found Urho3D: ${URHO3D_LIBRARIES}")
    endif ()
endif ()

if (URHO3D_FOUND)
    include (FindPackageMessage)
    FIND_PACKAGE_MESSAGE (Urho3D ${FOUND_MESSAGE} "[${URHO3D_LIBRARIES}][${URHO3D_INCLUDE_DIRS}]")
else ()
    if (Urho3D_FIND_REQUIRED)
        message (FATAL_ERROR
            "Could not find Urho3D library in Urho3D source/build trees or SDK installation. "
            "To search in Urho3D source/build trees, Use URHO3D_HOME and URHO3D_BUILD_TREE environment variables to specify the location of source and build tree, respectively. "
            "To search in a non-default Urho3D SDK installation location, use CMAKE_PREFIX_PATH environment variable to specify the prefix path of the installation location.")
    endif ()
endif ()

mark_as_advanced (URHO3D_INCLUDE_DIRS URHO3D_LIBRARIES URHO3D_HOME URHO3D_BUILD_TREE)
