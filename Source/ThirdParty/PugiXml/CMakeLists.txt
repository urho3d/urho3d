# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Define target name
set (TARGET_NAME PugiXml)

# Define source files
define_source_files (GLOB_CPP_PATTERNS src/*.cpp GLOB_H_PATTERNS src/*.hpp)

# Setup target
setup_library ()

# Install headers for building the Urho3D library
install_header_files (DIRECTORY src/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/PugiXml FILES_MATCHING PATTERN *.hpp BUILD_TREE_ONLY)  # Note: the trailing slash is significant
