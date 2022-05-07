# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

if (NOT CMAKE_PROJECT_NAME STREQUAL Urho3D)
    # Set CMake minimum version
    cmake_minimum_required (VERSION 3.10.2)

    # Set project name
    project (Urho3D-ExternalProject-PackageTool)

    # Set CMake modules search path
    set (CMAKE_MODULE_PATH ${BAKED_CMAKE_SOURCE_DIR}/cmake/Modules)

    # Include UrhoCommon.cmake module after setting project name
    include (UrhoCommon)

    # Define additional source files
    set (MINI_URHO_CPP_FILES
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Container/Allocator.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Container/HashBase.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Container/RefCounted.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Container/Str.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Container/VectorBase.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Core/Context.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Core/EventProfiler.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Core/Mutex.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Core/Object.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Core/ProcessUtils.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Core/Profiler.cpp
        ${BAKED_CMAKE_SOURCE_DIR}/Source/Urho3D/Core/StringHashRegister.cpp
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

    # Define preprocessor macros
    add_definitions (-DMINI_URHO)

    # Setup SDK-like include dir in the build tree for building the mini-urho
    set (DEST_INCLUDE_DIR include/Urho3D)
    file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${DEST_INCLUDE_DIR}/ThirdParty)

    # Add dependency targets
    if (NOT CMAKE_SYSTEM_NAME STREQUAL Linux)
        include (CheckIncludeFile)
        check_include_file (stdint.h HAVE_STDINT_H)
        add_subdirectory (${BAKED_CMAKE_SOURCE_DIR}/Source/ThirdParty/LibCpuId host/LibCpuId)
        set (LIBS LibCpuId)
    endif ()
    add_subdirectory (${BAKED_CMAKE_SOURCE_DIR}/Source/ThirdParty/LZ4 host/LZ4)
    set (INCLUDE_DIRS ${BAKED_CMAKE_BINARY_DIR}/include ${BAKED_CMAKE_BINARY_DIR}/include/Urho3D ${CMAKE_BINARY_DIR}/${DEST_INCLUDE_DIR}/ThirdParty)
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
setup_executable (TOOL)
adjust_target_name ()   # Remove postfix from the executable/binary name
