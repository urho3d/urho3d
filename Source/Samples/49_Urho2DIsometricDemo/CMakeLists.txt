# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

if (NOT URHO3D_URHO2D OR NOT URHO3D_PHYSICS2D)
    return ()
endif ()

# Define target name
set (TARGET_NAME 49_Urho2DIsometricDemo)

# Define source files
define_source_files (EXTRA_H_FILES ${COMMON_SAMPLE_H_FILES} ../Utilities2D/Sample2D.h ../Utilities2D/Sample2D.cpp ../Utilities2D/Mover.h ../Utilities2D/Mover.cpp)

# Setup target with resource copying
setup_main_executable ()

# Setup test cases
setup_test ()
