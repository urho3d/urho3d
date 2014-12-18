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

# Define target name
set (TARGET_NAME LuaScript)

# Optionally enable Lua / C++ wrapper safety checks
if (NOT URHO3D_SAFE_LUA)
    add_definitions (-DTOLUA_RELEASE)
endif ()

# The host tool must be built natively
if (CMAKE_CROSSCOMPILING OR IOS)
    # When cross-compiling, build the host tool as external project
    include (ExternalProject)
    if (IOS)
        # For iOS target, its host is MacOSX; Workaround a known CMake/Xcode generator bug which prevents it from installing binaries correctly
        set (OSX_HOST -DCMAKE_OSX_SYSROOT=macosx -DIPHONEOS_DEPLOYMENT_TARGET= BUILD_COMMAND bash -c "sed -i '' 's/EFFECTIVE_PLATFORM_NAME//g' CMakeScripts/install_postBuildPhase.make*")            
    endif ()
    ExternalProject_Add(tolua++
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/Source/ThirdParty/toluapp/src/bin
        CMAKE_ARGS -DJIT=${JIT} -DDEST_RUNTIME_DIR=${CMAKE_BINARY_DIR}/Bin/tool -DBAKED_CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR} ${OSX_HOST}
    )
else ()
    # Otherwise, build it internally as per normal
    add_subdirectory (../../ThirdParty/toluapp/src/bin ../../ThirdParty/toluapp/src/bin)
endif ()

# Define generated source files
file (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/generated)
file (GLOB API_PKG_FILES ${CMAKE_CURRENT_SOURCE_DIR}/pkgs/*.pkg)

# Remove NavigationLuaAPI.pkg
if (NOT URHO3D_NAVIGATION)
    list (REMOVE_ITEM API_PKG_FILES ${CMAKE_CURRENT_SOURCE_DIR}/pkgs/NavigationLuaAPI.pkg)
endif ()

# Remove NetworkLuaAPI.pkg
if (NOT URHO3D_NETWORK)
    list (REMOVE_ITEM API_PKG_FILES ${CMAKE_CURRENT_SOURCE_DIR}/pkgs/NetworkLuaAPI.pkg)
endif ()

# Remove PhysicsLuaAPI.pkg
if (NOT URHO3D_PHYSICS)
    list (REMOVE_ITEM API_PKG_FILES ${CMAKE_CURRENT_SOURCE_DIR}/pkgs/PhysicsLuaAPI.pkg)
endif ()

# Remove Urho2DLuaAPI.pkg
if (NOT URHO3D_URHO2D)
    list (REMOVE_ITEM API_PKG_FILES ${CMAKE_CURRENT_SOURCE_DIR}/pkgs/Urho2DLuaAPI.pkg)
endif ()

foreach (API_PKG_FILE ${API_PKG_FILES})
    get_filename_component (NAME ${API_PKG_FILE} NAME)
    string (REGEX REPLACE LuaAPI\\.pkg$ "" API ${NAME})
    set (GEN_CPP_FILE generated/${API}LuaAPI.cpp)
    set (GEN_CPP_FILES ${GEN_CPP_FILES} ${GEN_CPP_FILE})
    file (GLOB PKG_FILES ${CMAKE_CURRENT_SOURCE_DIR}/pkgs/${API}/*.pkg)
    add_custom_command (OUTPUT ${GEN_CPP_FILE} 
        COMMAND ${CMAKE_BINARY_DIR}/Bin/tool/tolua++ -L ToCppHook.lua -o ${CMAKE_CURRENT_BINARY_DIR}/${GEN_CPP_FILE} ${NAME}
        DEPENDS tolua++ ${API_PKG_FILE} ${PKG_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/pkgs/ToCppHook.lua
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/pkgs
        COMMENT "Generating tolua++ API binding on the fly for ${API}")
endforeach ()

# Define source files
define_source_files (EXTRA_CPP_FILES ${GEN_CPP_FILES})
install (FILES ${H_FILES} DESTINATION ${DEST_INCLUDE_DIR})

# Define dependency libs
set (LIBS ../../ThirdParty/Lua${JIT}/src)
set (LINK_LIBS_ONLY toluapp)
set (INCLUDE_DIRS_ONLY . .. ../Audio ../Container ../Core ../Engine ../Graphics ../Input ../IO ../Math ../Navigation ../Resource ../Scene ../UI
    ../../ThirdParty/SDL/include ../../ThirdParty/toluapp/include ${CMAKE_BINARY_DIR}/Source/Urho3D)

if (URHO3D_NAVIGATION)
    set (INCLUDE_DIRS_ONLY ${INCLUDE_DIRS_ONLY} ../Navigation)
endif ()

if (URHO3D_NETWORK)
    set (INCLUDE_DIRS_ONLY ${INCLUDE_DIRS_ONLY} ../Network ../../ThirdParty/kNet/include)
endif ()

if (URHO3D_PHYSICS)
    set (INCLUDE_DIRS_ONLY ${INCLUDE_DIRS_ONLY} ../Physics ../../ThirdParty/Bullet/src)
endif ()

if (URHO3D_URHO2D)
    set (INCLUDE_DIRS_ONLY ${INCLUDE_DIRS_ONLY} ../Urho2D ../../ThirdParty/Box2D)
endif ()

# Setup target
setup_library ()
