# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

if (NOT URHO3D_PHYSICS)
    return ()
endif ()

# Define target name
set (TARGET_NAME 19_VehicleDemo)

# Define source files
define_source_files (EXTRA_H_FILES ${COMMON_SAMPLE_H_FILES})

# Setup target with resource copying
if (EMSCRIPTEN)
    # Override the Urho3D default
    if (URHO3D_TESTING AND URHO3D_TEST_TIMEOUT LESS 15)
        set (URHO3D_TEST_TIMEOUT 15)
    endif ()
endif ()
setup_main_executable ()

# Setup test cases
setup_test ()
