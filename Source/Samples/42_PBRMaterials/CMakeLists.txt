# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Emscripten build does not copy the PBR resources, and would not support the shaders
if (EMSCRIPTEN)
    return ()
endif ()

# Define target name
set (TARGET_NAME 42_PBRMaterials)

# Define source files
define_source_files (EXTRA_H_FILES ${COMMON_SAMPLE_H_FILES})
define_resource_dirs (EXTRA_DIRS ${CMAKE_SOURCE_DIR}/bin/Autoload)

# Setup target with resource copying
setup_main_executable ()

# Setup test cases
setup_test ()
