# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

if (NOT CMAKE_PROJECT_NAME STREQUAL Urho3D)
    # Set CMake minimum version
    cmake_minimum_required (VERSION 3.10.2)

    # Set project name
    project (Urho3D-ExternalProject-tolua++)

    # Set CMake modules search path
    set (CMAKE_MODULE_PATH ${BAKED_CMAKE_SOURCE_DIR}/cmake/Modules)

    # Include UrhoCommon.cmake module after setting project name
    include (UrhoCommon)

    # When performing Xcode CI build suppress all the warnings for 3rd party libraries because there are just too many of them
    if (XCODE AND DEFINED ENV{CI})
        set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w")
    endif ()

    # Add dependency targets
    add_subdirectory (${BAKED_CMAKE_SOURCE_DIR}/Source/ThirdParty/Lua host/Lua)
    add_subdirectory (${BAKED_CMAKE_SOURCE_DIR}/Source/ThirdParty/toluapp/src/lib host/toluapp)
endif ()

# Define target name
set (TARGET_NAME tolua++)

# Define generated source files
if (URHO3D_UPDATE_SOURCE_TREE)
    set (UPDATE_COMMAND COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/generated/toluabind.c ${CMAKE_CURRENT_SOURCE_DIR}/toluabind.c)
endif ()
file (GLOB TOLUA lua/*.lua)
add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/generated/toluabind.c
    COMMAND ${CMAKE_BINARY_DIR}/bin/tool/tolua++ -o ${CMAKE_CURRENT_BINARY_DIR}/generated/toluabind.c -H ${CMAKE_CURRENT_BINARY_DIR}/generated/toluabind.h -n tolua tolua_scons.pkg 2>${NULL_DEVICE} || ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/toluabind.c ${CMAKE_CURRENT_BINARY_DIR}/generated/toluabind.c
    ${UPDATE_COMMAND}
    DEPENDS ${TOLUA} tolua_scons.pkg
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating toluabind.c and toluabind.h")

# Define source files
define_source_files (EXTRA_CPP_FILES tolua.c ${CMAKE_CURRENT_BINARY_DIR}/generated/toluabind.c)

# Define dependency libs
set (LIBS toluapp Lua)
if (NOT MSVC)
    list (APPEND LIBS m)
endif ()
set (INCLUDE_DIRS ../../include ../../../../ThirdParty/Lua/src)

# Setup target
setup_executable (TOOL NODEPS)
