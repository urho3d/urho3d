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

# Define target name
set (TARGET_NAME LuaScript)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define generated source files
file (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/generated)
file (GLOB_RECURSE PKG_FILES ${CMAKE_CURRENT_SOURCE_DIR}/pkgs/*.pkg)
add_custom_command (OUTPUT generated/AudioLuaAPI.cpp generated/ContainerLuaAPI.cpp generated/CoreLuaAPI.cpp generated/EngineLuaAPI.cpp generated/GraphicsLuaAPI.cpp
    generated/InputLuaAPI.cpp generated/IOLuaAPI.cpp generated/MathLuaAPI.cpp generated/NavigationLuaAPI.cpp generated/NetworkLuaAPI.cpp
    generated/PhysicsLuaAPI.cpp generated/ResourceLuaAPI.cpp generated/SceneLuaAPI.cpp generated/UILuaAPI.cpp generated/LuaScriptLuaAPI.cpp 
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/AudioLuaAPI.cpp AudioLuaAPI.pkg DEPENDS ${PKG_FILES}
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/ContainerLuaAPI.cpp ContainerLuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/CoreLuaAPI.cpp CoreLuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/EngineLuaAPI.cpp EngineLuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/GraphicsLuaAPI.cpp GraphicsLuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/InputLuaAPI.cpp InputLuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/IOLuaAPI.cpp IOLuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/MathLuaAPI.cpp MathLuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/NavigationLuaAPI.cpp NavigationLuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/NetworkLuaAPI.cpp NetworkLuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/PhysicsLuaAPI.cpp PhysicsLuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/ResourceLuaAPI.cpp ResourceLuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/SceneLuaAPI.cpp SceneLuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/UILuaAPI.cpp UILuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/LuaScriptLuaAPI.cpp LuaScriptLuaAPI.pkg
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/pkgs
    COMMENT "Generate Lua API binding on the fly")
set (SOURCE_FILES ${SOURCE_FILES} generated/AudioLuaAPI.cpp generated/ContainerLuaAPI generated/CoreLuaAPI.cpp generated/EngineLuaAPI.cpp generated/GraphicsLuaAPI.cpp
    generated/InputLuaAPI.cpp generated/IOLuaAPI.cpp generated/MathLuaAPI.cpp generated/NavigationLuaAPI.cpp generated/NetworkLuaAPI.cpp
    generated/PhysicsLuaAPI.cpp generated/ResourceLuaAPI.cpp generated/SceneLuaAPI.cpp generated/UILuaAPI.cpp generated/LuaScriptLuaAPI.cpp)

# Define dependency libs
set (LIBS ../../Engine/Audio ../../Engine/Container ../../Engine/Core ../../Engine/Engine ../../Engine/Graphics ../../Engine/Input ../../Engine/IO ../../Engine/Math ../../Engine/Navigation ../../Engine/Network
    ../../Engine/Physics ../../Engine/Resource ../../Engine/Scene ../../Engine/UI ../../ThirdParty/Lua/src)
set (LINK_LIBS_ONLY tolua++_static)
set (INCLUDE_DIRS_ONLY . ../../ThirdParty/Bullet/src ../../ThirdParty/kNet/include ../../ThirdParty/tolua++/include)

# Setup target
enable_pch ()
setup_library ()

# For IOS, Android, and Raspberry-Pi cross-compiling build to be successful, the "tolua++" tool must be already present in the "Bin" folder
# One way to achieve this is to first do a native desktop build where all the tools would be generated, then switch to IOS/Android/Raspberry-Pi cross-compiling build
# Intentionally do not include NOT RASPI in the condition below because the dependency is still required for Raspberry Pi native build
if (NOT IOS AND NOT ANDROID)
    # Add dependency to the "tolua++" bin tool
    add_dependencies (${TARGET_NAME} tolua++)
endif ()
