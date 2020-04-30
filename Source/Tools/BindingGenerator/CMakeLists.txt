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
    project (Urho3D-ExternalProject-BindingGenerator)

    # Set CMake modules search path
    set (CMAKE_MODULE_PATH ${BAKED_CMAKE_SOURCE_DIR}/CMake/Modules)

    # Include UrhoCommon.cmake module after setting project name
    include (UrhoCommon)

    # Add dependency targets
    add_subdirectory (${BAKED_CMAKE_SOURCE_DIR}/Source/ThirdParty/PugiXml host/PugiXml)

    # Setup SDK-like include dir in the build tree for building the host-tools
    set (DEST_INCLUDE_DIR include/Urho3D)
    set (INCLUDE_DIRS ${BAKED_CMAKE_BINARY_DIR}/${DEST_INCLUDE_DIR}/ThirdParty)
endif ()

# Define target name
set (TARGET_NAME BindingGenerator)

# Define source files
define_source_files ()

# Define dependency libs
set (LIBS PugiXml)

# Setup target
setup_executable (TOOL NODEPS)
