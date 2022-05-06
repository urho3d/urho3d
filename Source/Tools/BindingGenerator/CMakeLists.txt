# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

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

# Preventing VS from placing cpp and h files to different groups 
source_group (TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})
