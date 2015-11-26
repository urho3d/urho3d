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
    project (ExternalProject-PackageTool)

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

    # Define additional source files
    set (MINI_URHO_CPP_FILES
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Container/Allocator.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Container/HashBase.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Container/RefCounted.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Container/Str.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Container/VectorBase.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Core/Context.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Core/Mutex.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Core/Object.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Core/ProcessUtils.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Core/Profiler.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Core/StringUtils.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Core/Thread.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Core/Timer.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Core/Variant.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/IO/Deserializer.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/IO/File.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/IO/FileSystem.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/IO/Log.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/IO/MemoryBuffer.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/IO/PackageFile.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/IO/Serializer.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/IO/VectorBuffer.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Math/Color.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Math/Matrix3.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Math/Matrix3x4.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Math/Matrix4.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Math/Quaternion.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Math/Rect.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Math/StringHash.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Math/Vector2.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Math/Vector3.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Math/Vector4.cpp
    )

    # Check existence of stdint.h for LibCpuId
    include (CheckIncludeFiles)
    check_include_files (stdint.h HAVE_STDINT_H)
    if (HAVE_STDINT_H)
        add_definitions (-DHAVE_STDINT_H)
    endif ()

    # Define that we are building mini Urho
    add_definitions (-DMINI_URHO)

    # Setup SDK-like include dir in the build tree for building the mini-urho
    set (DEST_INCLUDE_DIR include/Urho3D)
    file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${DEST_INCLUDE_DIR}/ThirdParty)

    # Add dependency targets
    add_subdirectory (${BAKED_CMAKE_SOURCE_DIR}/Source/ThirdParty/LibCpuId host/LibCpuId)
    add_subdirectory (${BAKED_CMAKE_SOURCE_DIR}/Source/ThirdParty/LZ4 host/LZ4)
    set (INCLUDE_DIRS ${BAKED_CMAKE_BINARY_DIR}/include ${BAKED_CMAKE_BINARY_DIR}/include/Urho3D ${CMAKE_BINARY_DIR}/${DEST_INCLUDE_DIR}/ThirdParty)
    set (LIBS LibCpuId)
endif ()

# Define target name
if (TARGET PackageTool)     # The target name is already taken by host-tool external project, so use a postfix for the target-tool
    set (POSTFIX _target)
endif ()
set (TARGET_NAME PackageTool${POSTFIX})

# Define source files
define_source_files (EXTRA_CPP_FILES ${MINI_URHO_CPP_FILES})

# Define dependency libs
list (APPEND LIBS LZ4)

# Setup target
if (APPLE)
    setup_macosx_linker_flags (CMAKE_EXE_LINKER_FLAGS)
endif ()
setup_executable ()
adjust_target_name ()   # Remove postfix from the executable/binary name
