# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Define target name
set (TARGET_NAME GLEW)

# Define preprocessor macros
add_definitions (-DGLEW_STATIC -DGLEW_NO_GLU)

# Define source files
define_source_files (GLOB_CPP_PATTERNS *.c)

# Define dependency libs
set (INCLUDE_DIRS .)

# Setup target
setup_library ()

# Install headers for building and using the Urho3D library (install dependency for OGLGraphicsImpl.h)
install_header_files (DIRECTORY ./ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/GLEW FILES_MATCHING PATTERN *.h)  # Note: the trailing slash is significant
