#
# Copyright (c) 2008-2015 the Urho3D project.
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
    # Set project name
    project (ExternalProject-tolua++)

    # Set minimum version
    cmake_minimum_required (VERSION 2.8.6)

    if (COMMAND cmake_policy)
        cmake_policy (SET CMP0003 NEW)
        if (CMAKE_VERSION VERSION_GREATER 2.8.12 OR CMAKE_VERSION VERSION_EQUAL 2.8.12)
            # INTERFACE_LINK_LIBRARIES defines the link interface
            cmake_policy (SET CMP0022 NEW)
        endif ()
        if (CMAKE_VERSION VERSION_GREATER 3.0.0 OR CMAKE_VERSION VERSION_EQUAL 3.0.0)
            # Disallow use of the LOCATION target property - therefore we set to OLD as we still need it
            cmake_policy (SET CMP0026 OLD)
            # MACOSX_RPATH is enabled by default
            cmake_policy (SET CMP0042 NEW)
        endif ()
    endif ()

    # Set CMake modules search path
    set (CMAKE_MODULE_PATH ${BAKED_CMAKE_SOURCE_DIR}/CMake/Modules)

    # Include Urho3D Cmake common module
    include (Urho3D-CMake-common)

    # Add dependency targets
    add_subdirectory (${BAKED_CMAKE_SOURCE_DIR}/Source/ThirdParty/Lua${JIT} host/Lua${JIT})
    add_subdirectory (${BAKED_CMAKE_SOURCE_DIR}/Source/ThirdParty/toluapp/src/lib host/toluapp)
endif ()

# Define target name
set (TARGET_NAME tolua++)

# Define source files
define_source_files (GLOB_CPP_PATTERNS *.c)

# Define dependency libs
set (LIBS toluapp Lua${JIT})
if (NOT MSVC)
    list (APPEND LIBS m)
endif ()
set (INCLUDE_DIRS ../../include ../../../../ThirdParty/Lua${JIT}/src)

# All tools must be natively built and output to bin/tool subdir to differentiate them from platform-specific binaries in the bin directory
set_output_directories (${CMAKE_BINARY_DIR}/bin/tool RUNTIME PDB)
if (DEST_RUNTIME_DIR STREQUAL bin)
    set (DEST_RUNTIME_DIR bin/tool)
endif ()

# Setup target
if (APPLE)
    setup_macosx_linker_flags (CMAKE_EXE_LINKER_FLAGS)
endif ()
setup_executable (NODEPS)
