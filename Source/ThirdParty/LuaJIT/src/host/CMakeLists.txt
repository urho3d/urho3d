# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

if (NOT CMAKE_PROJECT_NAME STREQUAL Urho3D)
    # Set CMake minimum version
    cmake_minimum_required (VERSION 3.10.2)

    # Set project name
    project (Urho3D-ExternalProject-buildvm)

    # Set CMake modules search path
    set (CMAKE_MODULE_PATH ${BAKED_CMAKE_SOURCE_DIR}/cmake/Modules)

    # Include UrhoCommon.cmake module after setting project name
    include (UrhoCommon)

    # Unescape the variables
    foreach (ESCAPED_VAR HOST_XCFLAGS TARGET_ARCH DASM_FLAGS DASM_ARCH)
        string (REPLACE +D -D ${ESCAPED_VAR} "${${ESCAPED_VAR}}")       # Stringify against empty variable
        string (REPLACE , ";" ${ESCAPED_VAR} "${${ESCAPED_VAR}}")
    endforeach ()
endif ()

# When performing Xcode CI build suppress all the warnings for 3rd party libraries because there are just too many of them
if (XCODE AND DEFINED ENV{CI})
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w")
endif ()

# Add dependency target
set (TARGET_NAME minilua)
set (SOURCE_FILES minilua.c)
if (NOT MSVC)
    set (LIBS m)
endif ()
setup_executable (PRIVATE TOOL NODEPS)
unset (LIBS)

# Define target name
set (TARGET_NAME buildvm)

# Add definitions specific for host C compiler
add_definitions (${HOST_XCFLAGS} ${TARGET_ARCH})

# Define generated source files
set (GEN_ARCH_H ${CMAKE_CURRENT_BINARY_DIR}/buildvm_arch.h)
set (DASM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../dynasm)
set (DASM ${DASM_DIR}/dynasm.lua)
set (DASM_DASC ${CMAKE_CURRENT_SOURCE_DIR}/../vm_${DASM_ARCH}.dasc)
file (GLOB DASM_LUA ${DASM_DIR}/*.lua)
add_custom_command (OUTPUT ${GEN_ARCH_H}
    COMMAND minilua ${DASM} ${DASM_FLAGS} -o ${GEN_ARCH_H} ${DASM_DASC}
    DEPENDS minilua ${DASM_LUA} ${DASM_DASC}
    WORKING_DIRECTORY ${DASM_DIR}
    COMMENT "Generating buildvm arch header file")

# Define source files
file (GLOB C_FILES buildvm*.c)
set (SOURCE_FILES ${C_FILES} ${GEN_ARCH_H})

# Define dependency libs
set (INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR} ..)

# Setup target
setup_executable (${PRIVATE} TOOL NODEPS)
