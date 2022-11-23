# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Define target name
set (TARGET_NAME MojoShader)

# Define source files
define_source_files (GLOB_CPP_PATTERNS *.c)

if (MSVC)
    add_definitions (-D_CRT_SECURE_NO_WARNINGS=1 -TP)
endif (MSVC)

# Setup target
setup_library ()

# Install headers for building the Urho3D library
install_header_files (DIRECTORY ./ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/MojoShader FILES_MATCHING PATTERN *.h BUILD_TREE_ONLY)  # Note: the trailing slash is significant
