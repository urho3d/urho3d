# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Define target name
set (TARGET_NAME RampGenerator)

# Define preprocessor macros
if (MINGW AND (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 6.1.0 OR CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL 6.1.0) AND URHO3D_LIB_TYPE STREQUAL STATIC)
    # Workaround the "multiple definition of" linking issue in STATIC build
else ()
    add_definitions (-DSTB_IMAGE_WRITE_IMPLEMENTATION)
endif ()

# Define source files
define_source_files ()

# Setup target
setup_executable (TOOL)
