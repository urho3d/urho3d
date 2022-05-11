# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Define target name
set (TARGET_NAME Tests)

# Define source files
define_source_files (RECURSE GROUP)

# Setup target
setup_executable (TOOL)

# Setup test cases
setup_test ()
