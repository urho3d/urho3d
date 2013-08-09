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

# Find Urho3D library and include directories in the build tree or installed location
# For build tree detection to work, Urho3D library must be already been built
#
#  URHO3D_FOUND
#  URHO3D_INCLUDE_DIR
#  URHO3D_LIBRARY_DIR
#  URHO3D_LIBRARIES
#

set (URHO3D_FOUND 0)

set (URHO3D_HOME $ENV{URHO3D_HOME})
if (URHO3D_HOME)
    file (TO_CMAKE_PATH ${URHO3D_HOME} URHO3D_HOME)
    
    # Construct build tree paths from URHO3D_HOME environment variable
    find_file (BUILD_TREE_PATH Urho3D.h.in ${URHO3D_HOME}/Source/Engine NO_DEFAULT_PATH)
    if (BUILD_TREE_PATH)
        string (REPLACE "/Urho3D.h.in" "" BUILD_TREE_PATH ${BUILD_TREE_PATH})
        set (URHO3D_INCLUDE_DIR
            ${BUILD_TREE_PATH}
            ${BUILD_TREE_PATH}/Audio
            ${BUILD_TREE_PATH}/Container
            ${BUILD_TREE_PATH}/Core
            ${BUILD_TREE_PATH}/Engine
            ${BUILD_TREE_PATH}/Graphics
            ${BUILD_TREE_PATH}/Input
            ${BUILD_TREE_PATH}/IO
            ${BUILD_TREE_PATH}/Math
            ${BUILD_TREE_PATH}/Navigation
            ${BUILD_TREE_PATH}/Network
            ${BUILD_TREE_PATH}/Physics
            ${BUILD_TREE_PATH}/Resource
            ${BUILD_TREE_PATH}/Scene
            ${BUILD_TREE_PATH}/Script
            ${BUILD_TREE_PATH}/UI
            ${BUILD_TREE_PATH}/../Extras/LuaScript)

        if (RASPI AND CMAKE_CROSSCOMPILING)
            set (URHO3D_INCLUDE_DIR ${URHO3D_INCLUDE_DIR} ${URHO3D_HOME}/raspi-Build/Engine)
            set (URHO3D_LIB_SEARCH_PATH ${URHO3D_HOME}/Lib-CC)
        else ()
            set (URHO3D_INCLUDE_DIR ${URHO3D_INCLUDE_DIR} ${URHO3D_HOME}/Build/Engine)
            set (URHO3D_LIB_SEARCH_PATH ${URHO3D_HOME}/Lib)
        endif ()
        find_library (URHO3D_LIBRARIES Urho3D ${URHO3D_LIB_SEARCH_PATH} NO_DEFAULT_PATH)
    endif ()
else ()
    set (URHO3D_INC_SEARCH_PATH /opt/include)
    find_path (URHO3D_INCLUDE_DIR Engine.h PATH_SUFFIXES Urho3D ${URHO3D_INC_SEARCH_PATH})
    
    set (URHO3D_LIB_SEARCH_PATH /opt/lib)
    find_library (URHO3D_LIBRARIES Urho3D PATH_SUFFIXES Urho3D ${URHO3D_LIB_SEARCH_PATH})
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
        message (FATAL_ERROR "Could not find Urho3D installation or build tree via ENV{URHO3D_HOME}")
    endif ()
endif ()

mark_as_advanced (URHO3D_INCLUDE_DIR URHO3D_LIBRARIES)
