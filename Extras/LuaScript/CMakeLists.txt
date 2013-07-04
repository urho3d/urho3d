# Define target name
set (TARGET_NAME LuaScript)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define generated source files
file (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/generated)
add_custom_command (OUTPUT generated/AudioLuaAPI.cpp generated/ContainerLuaAPI.cpp generated/CoreLuaAPI.cpp generated/EngineLuaAPI.cpp generated/GraphicsLuaAPI.cpp
    generated/InputLuaAPI.cpp generated/IOLuaAPI.cpp generated/MathLuaAPI.cpp generated/NavigationLuaAPI.cpp generated/NetworkLuaAPI.cpp
    generated/PhysicsLuaAPI.cpp generated/ResourceLuaAPI.cpp generated/SceneLuaAPI.cpp generated/UILuaAPI.cpp generated/LuaScriptLuaAPI.cpp 
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/AudioLuaAPI.cpp AudioLuaAPI.pkg DEPENDS pkgs/AudioLuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/ContainerLuaAPI.cpp ContainerLuaAPI.pkg DEPENDS pkgs/ContainerLuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/CoreLuaAPI.cpp CoreLuaAPI.pkg DEPENDS pkgs/CoreLuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/EngineLuaAPI.cpp EngineLuaAPI.pkg DEPENDS pkgs/EngineLuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/GraphicsLuaAPI.cpp GraphicsLuaAPI.pkg DEPENDS pkgs/GraphicsLuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/InputLuaAPI.cpp InputLuaAPI.pkg DEPENDS pkgs/InputLuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/IOLuaAPI.cpp IOLuaAPI.pkg DEPENDS pkgs/IOLuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/MathLuaAPI.cpp MathLuaAPI.pkg DEPENDS pkgs/MathLuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/NavigationLuaAPI.cpp NavigationLuaAPI.pkg DEPENDS pkgs/NavigationLuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/NetworkLuaAPI.cpp NetworkLuaAPI.pkg DEPENDS pkgs/NetworkLuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/PhysicsLuaAPI.cpp PhysicsLuaAPI.pkg DEPENDS pkgs/PhysicsLuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/ResourceLuaAPI.cpp ResourceLuaAPI.pkg DEPENDS pkgs/ResourceLuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/SceneLuaAPI.cpp SceneLuaAPI.pkg DEPENDS pkgs/SceneLuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/UILuaAPI.cpp UILuaAPI.pkg DEPENDS pkgs/UILuaAPI.pkg
    COMMAND ${PROJECT_SOURCE_DIR}/Bin/tolua++ -L basic.lua -o ${CMAKE_CURRENT_BINARY_DIR}/generated/LuaScriptLuaAPI.cpp LuaScriptLuaAPI.pkg DEPENDS pkgs/LuaScriptLuaAPI.pkg
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/pkgs
    COMMENT "Generate Lua API binding on the fly")
set (SOURCE_FILES ${SOURCE_FILES} generated/AudioLuaAPI.cpp generated/ContainerLuaAPI generated/CoreLuaAPI.cpp generated/EngineLuaAPI.cpp generated/GraphicsLuaAPI.cpp
    generated/InputLuaAPI.cpp generated/IOLuaAPI.cpp generated/MathLuaAPI.cpp generated/NavigationLuaAPI.cpp generated/NetworkLuaAPI.cpp
    generated/PhysicsLuaAPI.cpp generated/ResourceLuaAPI.cpp generated/SceneLuaAPI.cpp generated/UILuaAPI.cpp generated/LuaScriptLuaAPI.cpp)

# Define dependency libs
set (LIBS ../../Engine/Audio ../../Engine/Container ../../Engine/Core ../../Engine/Engine ../../Engine/Graphics ../../Engine/Input ../../Engine/IO ../../Engine/Math ../../Engine/Navigation ../../Engine/Network
    ../../Engine/Physics ../../Engine/Resource ../../Engine/Scene ../../Engine/UI ../../ThirdParty/Lua/src ../../ThirdParty/tolua++_static)
set (INCLUDE_DIRS_ONLY . ../../ThirdParty/Bullet/src ../../ThirdParty/kNet/include ../../ThirdParty/tolua++/include)

# Setup target
enable_pch ()
setup_library ()

# For IOS build to be successful, the "tolua++" tool must be present in the "Bin" folder.
# One way to achieve this is to first build Urho3D for Mac OS X desktop build where all the tools would be generated, then switch to IOS build.
if (NOT IOS) 
    # Add dependency to the "tolua++" bin tool
    add_dependencies(${TARGET_NAME} tolua++)
endif ()
