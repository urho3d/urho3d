#
# Copyright (c) 2008-2020 the Urho3D project.
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

if (NOT CMAKE_PROJECT_NAME STREQUAL Urho3D)
    # Set CMake minimum version and CMake policy required by UrhoCommon module
    cmake_minimum_required (VERSION 3.10.2)
    if (COMMAND cmake_policy)
        # Libraries linked via full path no longer produce linker search paths
        cmake_policy (SET CMP0003 NEW)
        # INTERFACE_LINK_LIBRARIES defines the link interface
        cmake_policy (SET CMP0022 NEW)
        # Disallow use of the LOCATION target property - so we set to OLD as we still need it
        cmake_policy (SET CMP0026 OLD)
        # MACOSX_RPATH is enabled by default
        cmake_policy (SET CMP0042 NEW)
        # Honor the visibility properties for SHARED target types only
        cmake_policy (SET CMP0063 OLD)
    endif ()

    # Set project name
    project (Urho3D-ExternalProject-tolua++)

    # Set CMake modules search path
    set (CMAKE_MODULE_PATH ${BAKED_CMAKE_SOURCE_DIR}/CMake/Modules)

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
