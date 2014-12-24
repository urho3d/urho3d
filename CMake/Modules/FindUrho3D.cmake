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
# For internal Urho3D project, the Urho3D "build tree" path is already known.
#
# For external project that attempts to use the Urho3D build tree or installed Urho3D SDK,
# use URHO3D_HOME environment variable to specify the path (not needed when the path is a system-wide default location).
# When setting URHO3D_HOME environment variable, it should be set to a parent directory containing both the "include" or "lib" subdirectories.
# For example: set URHO3D_HOME=/home/john/usr/local, if the SDK is installed using DESTDIR=/home/john and CMAKE_INSTALL_PREFIX=/usr/local
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

set (PATH_SUFFIX Urho3D)
if (CMAKE_PROJECT_NAME STREQUAL Urho3D AND TARGET Urho3D)
    # Library location is already known to be in the build tree
    set (URHO3D_HOME ${CMAKE_BINARY_DIR})
    set (URHO3D_INCLUDE_DIRS ${URHO3D_HOME}/include/${PATH_SUFFIX} ${URHO3D_HOME}/include)
    set (URHO3D_LIBRARIES Urho3D)
    set (FOUND_MESSAGE "Found Urho3D: as CMake target")
else ()
    # Library location would be searched (based on URHO3D_HOME variable if provided)
    if (NOT URHO3D_HOME AND DEFINED ENV{URHO3D_HOME})
        file (TO_CMAKE_PATH "$ENV{URHO3D_HOME}" URHO3D_HOME)
    endif ()
    if (URHO3D_HOME)
        list (APPEND CMAKE_PREFIX_PATH ${URHO3D_HOME})
        set (SEARCH_OPT NO_CMAKE_FIND_ROOT_PATH)
    endif ()
    set (URHO3D_LIB_NAMES Urho3D)
    if (IOS)
        set (CMAKE_LIBRARY_ARCHITECTURE ios)
    elseif (ANDROID)
        set (URHO3D_LIB_SEARCH_HINT HINTS ${URHO3D_HOME}/libs/${ANDROID_NDK_ABI_NAME})
    endif ()
    if (NOT URHO3D_64BIT)
        set_property (GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS FALSE)
    elseif (WIN32)
        set_property (GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS TRUE)
    endif ()
    find_path (URHO3D_INCLUDE_DIRS Urho3D.h PATH_SUFFIXES ${PATH_SUFFIX} ${SEARCH_OPT})
    find_library (URHO3D_LIBRARIES NAMES ${URHO3D_LIB_NAMES} ${URHO3D_LIB_SEARCH_HINT} PATH_SUFFIXES ${PATH_SUFFIX} ${SEARCH_OPT})
    if (WIN32)
        find_library (URHO3D_LIBRARIES_DBG NAMES ${URHO3D_LIB_NAMES}_d ${URHO3D_LIB_SEARCH_HINT} PATH_SUFFIXES ${PATH_SUFFIX} ${SEARCH_OPT})
    endif ()
    if (URHO3D_INCLUDE_DIRS)
        get_filename_component (PATH ${URHO3D_INCLUDE_DIRS} PATH)
        list (APPEND URHO3D_INCLUDE_DIRS ${PATH})
        if (NOT URHO3D_HOME)
            # URHO3D_HOME is not set when using SDK installed on system-wide default location, so set it now
            get_filename_component (PATH ${PATH} PATH)
            set (URHO3D_HOME ${PATH})
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
endif ()

if (URHO3D_INCLUDE_DIRS AND URHO3D_LIBRARIES)
    set (URHO3D_FOUND 1)
    if (NOT FOUND_MESSAGE)
        set (FOUND_MESSAGE "Found Urho3D: ${URHO3D_LIBRARIES}")
    endif ()
    include (FindPackageMessage)
    FIND_PACKAGE_MESSAGE (Urho3D ${FOUND_MESSAGE} "[${URHO3D_LIBRARIES}][${URHO3D_INCLUDE_DIRS}]")
    set (URHO3D_HOME ${URHO3D_HOME} CACHE PATH "Path to Urho3D build tree or SDK installation location")
elseif (Urho3D_FIND_REQUIRED)
    message (FATAL_ERROR
        "Could not find Urho3D library in Urho3D build tree or SDK installation. "
        "Use URHO3D_HOME environment variable to specify the location of the build tree or SDK installation.")
endif ()

mark_as_advanced (URHO3D_INCLUDE_DIRS URHO3D_LIBRARIES URHO3D_HOME)
