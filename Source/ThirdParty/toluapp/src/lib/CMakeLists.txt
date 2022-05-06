# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Define target name
set (TARGET_NAME toluapp)

# Define source files
define_source_files (GLOB_CPP_PATTERNS *.c)

# Define dependency libs
set (INCLUDE_DIRS ../../include ../../../Lua${JIT}/src)

# Setup target
setup_library ()

# Install headers for building and using the Urho3D library (no direct dependencies but library user may need them)
install_header_files (DIRECTORY ../../include/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/toluapp FILES_MATCHING PATTERN *.h)  # Note: the trailing slash is significant
