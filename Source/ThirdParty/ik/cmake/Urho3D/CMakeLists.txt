# Copyright (c) 2008-2017 the Urho3D project.
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

# memory debugging
if (CMAKE_BUILD_TYPE MATCHES Debug)
    option (IK_MEMORY_DEBUGGING "Global switch for memory options. Keeps track of the number of allocations and de-allocations and prints a report when the program shuts down" ON)
else ()
    option (IK_MEMORY_DEBUGGING "Global switch for memory options. Keeps track of the number of allocations and de-allocations and prints a report when the program shuts down" OFF)
endif ()
if (IK_MEMORY_DEBUGGING)
    if(${CMAKE_BUILD_TYPE} MATCHES Debug)
        option (IK_MEMORY_BACKTRACE "Generates backtraces for every malloc(), making it easy to track down memory leaks" ON)
    else ()
        option (IK_MEMORY_BACKTRACE "Generates backtraces for every malloc(), making it easy to track down memory leaks" OFF)
    endif ()
else ()
    option (IK_MEMORY_BACKTRACE "Generates backtraces for every malloc(), making it easy to track down memory leaks" OFF)
endif ()

set (IK_REAL "float" CACHE STRING "Type to use for real numbers")
option (IK_DOT_OUTPUT "When enabled, the generated chains are dumped to DOT for debug purposes" OFF)

set (EXPORT_H_TEMPLATE )

configure_file ("../../ik/include/ik/export.h.in"
                "../../include/ik/gen/export.h")
configure_file ("../../ik/include/ik/config.h.in"
                "../../include/ik/gen/config.h")

###############################################################################
# compiler flags
###############################################################################

if (${CMAKE_C_COMPILER_ID} STREQUAL "GNU")
    add_definitions (-W -Wall -Wextra -Werror -pedantic -Wno-unused-parameter -fno-math-errno -ffast-math)
elseif (${CMAKE_C_COMPILER_ID} STREQUAL "Clang")
    add_definitions (-W -Wall -Wextra -Werror -pedantic -Wno-unused-parameter -fno-math-errno -ffast-math)
elseif (${CMAKE_C_COMPILER_ID} STREQUAL "Intel")
elseif (${CMAKE_C_COMPILER_ID} STREQUAL "MSVC")
    add_definitions (-D_CRT_SECURE_NO_WARNINGS)
    if (CMAKE_BUILD_TYPE MATCHES Debug)
        STRING(REGEX REPLACE "/MDd" "" CMAKE_C_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
        add_definitions (-MTd)
    elseif (CMAKE_BUILD_TYPE MATCHES Release)
        STRING(REGEX REPLACE "/MD" "" CMAKE_C_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})
        add_definitions (-MT)
    endif ()
endif ()

# The library is being built
add_definitions (-DIK_BUILDING)

###############################################################################
# source files and library definition
###############################################################################

file (GLOB IK_HEADERS "../../ik/include/ik/*.h")
file (GLOB IK_SOURCES "../../ik/src/*.c")

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    file (GLOB IK_PLATFORM_SOURCES "../../ik/src/platform/linux/*.c")
endif ()
list (APPEND IK_SOURCES ${IK_PLATFORM_SOURCES})

set (TARGET_NAME IK)
set (SOURCE_FILES ${IK_SOURCES} ${IK_HEADERS})
set (INCLUDE_DIRS ../../ik/include ${CMAKE_CURRENT_BINARY_DIR}/../../include)

setup_library ()

###############################################################################
# install targets
###############################################################################

# Install headers for building and using the Urho3D library
install_header_files (DIRECTORY ../../ik/include/ik/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/ik)
install_header_files (DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../../include/ik/gen/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/ik/gen)
