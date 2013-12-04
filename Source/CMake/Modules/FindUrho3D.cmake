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

# Find Urho3D library and include directories in the project root tree or installed location
# For project root tree detection to work, Urho3D library must be already been built
#
#  URHO3D_FOUND
#  URHO3D_INCLUDE_DIR
#  URHO3D_LIBRARIES
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
    list (APPEND URHO3D_LIB_NAMES Urho3D_d)
endif ()

if (CMAKE_PROJECT_NAME MATCHES Urho3D.* AND PROJECT_ROOT_DIR)
    set (URHO3D_HOME ${PROJECT_ROOT_DIR} CACHE PATH "Path to Urho3D project root tree" FORCE)
else ()
    file (TO_CMAKE_PATH "$ENV{URHO3D_HOME}" URHO3D_HOME)
    set (URHO3D_HOME ${URHO3D_HOME} CACHE PATH "Path to Urho3D project root tree")
endif ()
if (URHO3D_HOME)
    # Construct source tree paths from URHO3D_HOME environment variable
    find_file (SOURCE_TREE_PATH Urho3D.h.in ${URHO3D_HOME}/Source/Engine NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
    if (SOURCE_TREE_PATH)
        get_filename_component (SOURCE_TREE_PATH ${SOURCE_TREE_PATH} PATH)
        set (URHO3D_INCLUDE_DIR ${SOURCE_TREE_PATH})
        foreach (DIR Audio Container Core Engine Graphics Input IO LuaScript Math Navigation Network Physics Resource Scene Script UI)
            list (APPEND URHO3D_INCLUDE_DIR ${SOURCE_TREE_PATH}/${DIR})     # Note: variable change to list context after this
        endforeach ()
        foreach (DIR Bullet/src kNet/include SDL/include)
            list (APPEND URHO3D_INCLUDE_DIR ${URHO3D_HOME}/Source/ThirdParty/${DIR})
        endforeach ()

        if (ANDROID)
            if (NOT CMAKE_HOST_WIN32 OR USE_MKLINK)
                set (BUILD_DIR android-Build)
            else ()
                set (BUILD_DIR Source/Android)
            endif ()
            list (APPEND URHO3D_INCLUDE_DIR ${URHO3D_HOME}/${BUILD_DIR}/Engine)
            set (URHO3D_LIB_SEARCH_PATH ${URHO3D_HOME}/${BUILD_DIR}/libs/${ANDROID_NDK_ABI_NAME})
        elseif (RASPI AND CMAKE_CROSSCOMPILING)
            list (APPEND URHO3D_INCLUDE_DIR ${URHO3D_HOME}/raspi-Build/Engine)
            set (URHO3D_LIB_SEARCH_PATH ${URHO3D_HOME}/Lib-CC)
        else ()
            if (IOS)
                set (BUILD_DIR ios-Build)
            else ()
                set (BUILD_DIR Build)
            endif ()
            list (APPEND URHO3D_INCLUDE_DIR ${URHO3D_HOME}/${BUILD_DIR}/Engine)
            set (URHO3D_LIB_SEARCH_PATH ${URHO3D_HOME}/Lib)
        endif ()
        if (TARGET Urho3D)
            set (URHO3D_LIBRARIES Urho3D)
            set (FOUND_MESSAGE "Found Urho3D: as CMake target")
        else ()
            find_library (URHO3D_LIBRARIES NAMES ${URHO3D_LIB_NAMES} PATHS ${URHO3D_LIB_SEARCH_PATH} NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
        endif ()
    endif ()
else ()
    # If Urho3D SDK is not being installed in the default system location, use the URHO3D_INSTALL_PREFIX environment variable to specify the prefix path to that location
    # Note that the prefix path should not contain the "/include" or "/lib"
    # For example on Windows platform: URHO3D_INSTALL_PREFIX=C:/Users/john/Urho3D if the SDK is installed using CMAKE_INSTALL_PREFIX=C:/Users/john/Urho3D
    # For example on Linux platform: URHO3D_INSTALL_PREFIX=/home/john/usr/local if the SDK is installed using DESTDIR=/home/john and CMAKE_INSTALL_PREFIX=/usr/local
    set (CMAKE_PREFIX_PATH $ENV{URHO3D_INSTALL_PREFIX} CACHE PATH "Prefix path to Urho3D SDK installation")
    if (WIN32)
        set (URHO3D_INC_SEARCH_PATH include)
        set (URHO3D_LIB_SEARCH_PATH lib)
    else ()
        set (PATH_SUFFIX Urho3D)
        if (IOS)
            set (CMAKE_LIBRARY_ARCHITECTURE ios)
        endif ()
        set (URHO3D_INC_SEARCH_PATH /opt/include)
        set (URHO3D_LIB_SEARCH_PATH /opt/lib)
    endif ()
    find_path (URHO3D_INCLUDE_DIR Urho3D.h PATHS ${URHO3D_INC_SEARCH_PATH} PATH_SUFFIXES ${PATH_SUFFIX})
    find_library (URHO3D_LIBRARIES NAMES ${URHO3D_LIB_NAMES} PATHS ${URHO3D_LIB_SEARCH_PATH} PATH_SUFFIXES ${PATH_SUFFIX})

    if (URHO3D_INCLUDE_DIR)
        set (BASE_DIR ${URHO3D_INCLUDE_DIR})
        foreach (DIR Bullet kNet SDL)
            list (APPEND URHO3D_INCLUDE_DIR ${BASE_DIR}/${DIR})     # Note: variable change to list context after this, so we need BASE_DIR to remain the same
        endforeach ()
    endif ()
endif ()

if (URHO3D_INCLUDE_DIR AND URHO3D_LIBRARIES)
    set (URHO3D_FOUND 1)
    if (NOT FOUND_MESSAGE)
        set (FOUND_MESSAGE "Found Urho3D: ${URHO3D_LIBRARIES}")
    endif ()
endif ()

if (URHO3D_FOUND)
    include (FindPackageMessage)
    FIND_PACKAGE_MESSAGE (Urho3D ${FOUND_MESSAGE} "[${URHO3D_LIBRARIES}][${URHO3D_INCLUDE_DIR}]")
else ()
    if (Urho3D_FIND_REQUIRED)
        message (FATAL_ERROR
            "Could not find Urho3D library in default SDK installation location or Urho3D project root tree. "
            "For searching in a non-default Urho3D SDK installation, use 'URHO3D_INSTALL_PREFIX' environment variable to specify the prefix path of the installation location. "
            "For searching in a build tree of Urho3D project, use 'URHO3D_HOME' environment variable to specify the Urho3D project root directory. The Urho3D library itself must already be built successfully.")
    endif ()
endif ()

mark_as_advanced (URHO3D_INCLUDE_DIR URHO3D_LIBRARIES)
