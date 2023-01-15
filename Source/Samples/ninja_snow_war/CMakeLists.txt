# Copyright (c) 2022-2023 the Dviglo project
# Copyright (c) 2008-2023 the Urho3D project
# License: MIT

# Define target name
set (TARGET_NAME ninja_snow_war)

# Define source files
define_source_files (GROUP RECURSE)

# Setup target with resource copying
setup_main_executable ()

# Setup test cases
setup_test ()
