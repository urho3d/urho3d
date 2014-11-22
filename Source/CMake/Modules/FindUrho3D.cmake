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

# Find Urho3D library and include directories in the project root tree or installed location
# For project root tree detection to work, Urho3D library must be already been built
#
#  URHO3D_FOUND
#  URHO3D_INCLUDE_DIRS
#  URHO3D_LIBRARIES
#  URHO3D_LIBRARIES_REL
#  URHO3D_LIBRARIES_DBG
#

if (URHO3D_FOUND)
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

set (URHO3D_LIB_NAMES Urho3D)
if (WIN32)
    set (URHO3D_LIB_NAMES_DBG Urho3D_d)
endif ()

if (CMAKE_PROJECT_NAME STREQUAL Urho3D AND PROJECT_ROOT_DIR)
    set (URHO3D_HOME ${PROJECT_ROOT_DIR} CACHE PATH "Path to Urho3D project root tree" FORCE)
    set (IS_INTERNAL 1)
elseif (NOT URHO3D_HOME AND DEFINED ENV{URHO3D_HOME})
    file (TO_CMAKE_PATH "$ENV{URHO3D_HOME}" URHO3D_HOME)
    set (URHO3D_HOME ${URHO3D_HOME} CACHE PATH "Path to Urho3D project root tree")
endif ()
if (URHO3D_HOME)
    # Construct source tree paths from URHO3D_HOME environment variable
    find_file (URHO3D_SOURCE_TREE Urho3D.h.in ${URHO3D_HOME}/Source/Engine DOC "Path to Urho3D project source tree" NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
    if (URHO3D_SOURCE_TREE)
        get_filename_component (URHO3D_SOURCE_TREE ${URHO3D_SOURCE_TREE} PATH)
        set (URHO3D_INCLUDE_DIRS ${URHO3D_SOURCE_TREE})
        foreach (DIR Audio Container Core Engine Graphics Input IO LuaScript Math Navigation Network Physics Resource Scene Script UI Urho2D)
            list (APPEND URHO3D_INCLUDE_DIRS ${URHO3D_SOURCE_TREE}/${DIR})     # Note: variable change to list context after this
        endforeach ()
        set (DIRS SDL/include)
        if (URHO3D_ANGELSCRIPT)
            list (APPEND DIRS AngelScript/include)
        endif ()
        if (URHO3D_NETWORK)
            list (APPEND DIRS kNet/include)
        endif ()
        if (URHO3D_PHYSICS)
            list (APPEND DIRS Bullet/src)
        endif ()
        if (URHO3D_URHO2D)
            list (APPEND DIRS Box2D)
        endif ()
        foreach (DIR ${DIRS})
            list (APPEND URHO3D_INCLUDE_DIRS ${URHO3D_HOME}/Source/ThirdParty/${DIR})
        endforeach ()

        # For non Urho3D project using Urho3D as external library, Urho3D project itself must be built using predefined build directory as per specified in the provided build scripts.
        if (IS_INTERNAL)
            set (BINARY_DIR ${CMAKE_BINARY_DIR})
        elseif (ANDROID AND CMAKE_HOST_WIN32 AND NOT URHO3D_MKLINK)
            set (BINARY_DIR ${URHO3D_HOME}/Source/Android)
        else ()
            set (BINARY_DIR ${URHO3D_HOME}/${PLATFORM_PREFIX}Build)
        endif () 
        list (APPEND URHO3D_INCLUDE_DIRS ${BINARY_DIR}/Engine)
        if (ANDROID)
            if (IS_INTERNAL)
                set (URHO3D_LIB_SEARCH_PATH ${ANDROID_LIBRARY_OUTPUT_PATH})
            else ()
                set (URHO3D_LIB_SEARCH_PATH ${BINARY_DIR}/libs/${ANDROID_NDK_ABI_NAME})
            endif ()
        else ()
            set (URHO3D_LIB_SEARCH_PATH ${URHO3D_HOME}/${PLATFORM_PREFIX}Lib)
        endif ()
        if (TARGET Urho3D)
            set (URHO3D_LIBRARIES Urho3D)
            set (FOUND_MESSAGE "Found Urho3D: as CMake target")
        else ()
            find_library (URHO3D_LIBRARIES NAMES ${URHO3D_LIB_NAMES} PATHS ${URHO3D_LIB_SEARCH_PATH} NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
            if (WIN32)
                find_library (URHO3D_LIBRARIES_DBG NAMES ${URHO3D_LIB_NAMES_DBG} PATHS ${URHO3D_LIB_SEARCH_PATH} NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
            endif ()
        endif ()
    endif ()
else ()
    # If Urho3D SDK is not being installed in the default system location, use the CMAKE_PREFIX_PATH environment variable to specify the prefix path to that location
    # Note that the prefix path should not contain the "/include" or "/lib"
    # For example on Windows platform: CMAKE_PREFIX_PATH=C:/Users/john/Urho3D if the SDK is installed using CMAKE_INSTALL_PREFIX=C:/Users/john/Urho3D
    # For example on Linux platform: CMAKE_PREFIX_PATH=/home/john/usr/local if the SDK is installed using DESTDIR=/home/john and CMAKE_INSTALL_PREFIX=/usr/local
    if (CMAKE_HOST_WIN32)
        set (URHO3D_INC_SEARCH_PATH include)
        set (URHO3D_LIB_SEARCH_PATH lib)
    else ()
        set (PATH_SUFFIX Urho3D)
        if (IOS)
            set (CMAKE_LIBRARY_ARCHITECTURE ios)
        endif ()
    endif ()
    # Additional search paths are added by CMake by default which should already include most common platform specific paths
    find_path (URHO3D_INCLUDE_DIRS Urho3D.h PATHS ${URHO3D_INC_SEARCH_PATH} PATH_SUFFIXES ${PATH_SUFFIX})
    find_library (URHO3D_LIBRARIES NAMES ${URHO3D_LIB_NAMES} PATHS ${URHO3D_LIB_SEARCH_PATH} PATH_SUFFIXES ${PATH_SUFFIX})
    if (WIN32)
        find_library (URHO3D_LIBRARIES_DBG NAMES ${URHO3D_LIB_NAMES_DBG} PATHS ${URHO3D_LIB_SEARCH_PATH} PATH_SUFFIXES ${PATH_SUFFIX})
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
            "Could not find Urho3D library in default SDK installation location or Urho3D project root tree. "
            "For searching in a non-default Urho3D SDK installation, use 'CMAKE_PREFIX_PATH' environment variable to specify the prefix path of the installation location. "
            "For searching in a build tree of Urho3D project, use 'URHO3D_HOME' environment variable to specify the Urho3D project root directory. The Urho3D library itself must already be built successfully.")
    endif ()
endif ()

mark_as_advanced (URHO3D_INCLUDE_DIRS URHO3D_LIBRARIES URHO3D_SOURCE_TREE)
