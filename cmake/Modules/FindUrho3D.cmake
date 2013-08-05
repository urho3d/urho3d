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
    find_file (BUILD_TREE_PATH Urho3D.h.in ${URHO3D_HOME} NO_DEFAULT_PATH)
    if (NOT BUILD_TREE_PATH)
        find_file (BUILD_TREE_PATH Urho3D.h.in ${URHO3D_HOME}/trunk NO_DEFAULT_PATH)
    endif ()
    if (BUILD_TREE_PATH)
        string (REPLACE "/Urho3D.h.in" "" BUILD_TREE_PATH ${BUILD_TREE_PATH})
        set (URHO3D_INCLUDE_DIR
            ${BUILD_TREE_PATH}/Engine/Audio
            ${BUILD_TREE_PATH}/Engine/Container
            ${BUILD_TREE_PATH}/Engine/Core
            ${BUILD_TREE_PATH}/Engine/Engine
            ${BUILD_TREE_PATH}/Engine/Graphics
            ${BUILD_TREE_PATH}/Engine/Input
            ${BUILD_TREE_PATH}/Engine/IO
            ${BUILD_TREE_PATH}/Engine/Math
            ${BUILD_TREE_PATH}/Engine/Navigation
            ${BUILD_TREE_PATH}/Engine/Network
            ${BUILD_TREE_PATH}/Engine/Physics
            ${BUILD_TREE_PATH}/Engine/Resource
            ${BUILD_TREE_PATH}/Engine/Scene
            ${BUILD_TREE_PATH}/Engine/Script
            ${BUILD_TREE_PATH}/Engine/UI
            ${BUILD_TREE_PATH}/Extras/LuaScript
            ${BUILD_TREE_PATH}/Urho3D/lib)

        if (RASPI)            
            set (URHO3D_INCLUDE_DIR ${URHO3D_INCLUDE_DIR} ${BUILD_TREE_PATH}/../raspi-build)
            set (URHO3D_LIB_SEARCH_PATH ${BUILD_TREE_PATH}/../raspi-build/Urho3D/lib)
        else ()
            set (URHO3D_INCLUDE_DIR ${URHO3D_INCLUDE_DIR} ${BUILD_TREE_PATH}/../build)
            set (URHO3D_LIB_SEARCH_PATH ${BUILD_TREE_PATH}/../build/Urho3D/lib)
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
