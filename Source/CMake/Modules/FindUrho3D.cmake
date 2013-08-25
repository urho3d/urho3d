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
#  URHO3D_LIBRARY_DIR
#  URHO3D_LIBRARIES
#

set (URHO3D_FOUND 0)

set (URHO3D_LIB_NAMES Urho3D)
if (WIN32)
    set (URHO3D_LIB_NAMES ${URHO3D_LIB_NAMES} Urho3D_d)
endif ()

set (URHO3D_HOME $ENV{URHO3D_HOME})
if (URHO3D_HOME)
    file (TO_CMAKE_PATH ${URHO3D_HOME} URHO3D_HOME)
    
    # Construct source tree paths from URHO3D_HOME environment variable
    find_file (SOURCE_TREE_PATH Urho3D.h.in ${URHO3D_HOME}/Source/Engine NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
    if (SOURCE_TREE_PATH)
        get_filename_component (SOURCE_TREE_PATH ${SOURCE_TREE_PATH} PATH)
        set (URHO3D_INCLUDE_DIR
            ${SOURCE_TREE_PATH}
            ${SOURCE_TREE_PATH}/Audio
            ${SOURCE_TREE_PATH}/Container
            ${SOURCE_TREE_PATH}/Core
            ${SOURCE_TREE_PATH}/Engine
            ${SOURCE_TREE_PATH}/Graphics
            ${SOURCE_TREE_PATH}/Input
            ${SOURCE_TREE_PATH}/IO
            ${SOURCE_TREE_PATH}/Math
            ${SOURCE_TREE_PATH}/Navigation
            ${SOURCE_TREE_PATH}/Network
            ${SOURCE_TREE_PATH}/Physics
            ${SOURCE_TREE_PATH}/Resource
            ${SOURCE_TREE_PATH}/Scene
            ${SOURCE_TREE_PATH}/Script
            ${SOURCE_TREE_PATH}/UI
            ${URHO3D_HOME}/Source/Extras/LuaScript
            ${URHO3D_HOME}/Source/ThirdParty/SDL/include
            ${URHO3D_HOME}/Source/ThirdParty/Bullet/src
            ${URHO3D_HOME}/Source/ThirdParty/kNet/include
            )

        if (ANDROID)
            set (URHO3D_INCLUDE_DIR ${URHO3D_INCLUDE_DIR} ${URHO3D_HOME}/android-Build/Engine)
            set (URHO3D_LIB_SEARCH_PATH ${URHO3D_HOME}/android-Build/libs/${ANDROID_NDK_ABI_NAME})
        elseif (RASPI AND CMAKE_CROSSCOMPILING)
            set (URHO3D_INCLUDE_DIR ${URHO3D_INCLUDE_DIR} ${URHO3D_HOME}/raspi-Build/Engine)
            set (URHO3D_LIB_SEARCH_PATH ${URHO3D_HOME}/Lib-CC)
        else ()
            set (URHO3D_INCLUDE_DIR ${URHO3D_INCLUDE_DIR} ${URHO3D_HOME}/Build/Engine)
            set (URHO3D_LIB_SEARCH_PATH ${URHO3D_HOME}/Lib)
        endif ()
        find_library (URHO3D_LIBRARIES NAMES ${URHO3D_LIB_NAMES} PATHS ${URHO3D_LIB_SEARCH_PATH} NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
    endif ()
else ()
    set (URHO3D_INC_SEARCH_PATH /opt/include)
    find_path (URHO3D_INCLUDE_DIR Urho3D.h ${URHO3D_INC_SEARCH_PATH} PATH_SUFFIXES Urho3D)
    
    set (URHO3D_LIB_SEARCH_PATH /opt/lib)
    find_library (URHO3D_LIBRARIES NAMES ${URHO3D_LIB_NAMES} PATHS ${URHO3D_LIB_SEARCH_PATH} PATH_SUFFIXES Urho3D)
endif ()

if (URHO3D_INCLUDE_DIR AND URHO3D_LIBRARIES)
    set (URHO3D_FOUND 1)
    get_filename_component (URHO3D_LIBRARY_DIR ${URHO3D_LIBRARIES} PATH)
endif ()

if (URHO3D_FOUND)
    include (FindPackageMessage)
    FIND_PACKAGE_MESSAGE (Urho3D "Found Urho3D: ${URHO3D_LIBRARIES} ${URHO3D_INCLUDE_DIR}" "[${URHO3D_LIBRARIES}][${URHO3D_INCLUDE_DIR}]")
else ()
    if (Urho3D_FIND_REQUIRED)
        message (FATAL_ERROR "Could not find Urho3D library installation or project root tree via ENV{URHO3D_HOME}")
    endif ()
endif ()

mark_as_advanced (URHO3D_INCLUDE_DIR URHO3D_LIBRARIES)
