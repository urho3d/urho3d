# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Define target name
set (TARGET_NAME rapidjson)

# Setup target
add_custom_target (${TARGET_NAME} ALL)   # Dummy target just so that its post-build step can install headers to the build tree
set (STATIC_LIBRARY_TARGETS ${STATIC_LIBRARY_TARGETS} ${TARGET_NAME} PARENT_SCOPE)

# Install headers for building the Urho3D library
install_header_files (DIRECTORY include/rapidjson/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/rapidjson FILES_MATCHING PATTERN *.h USE_FILE_SYMLINK BUILD_TREE_ONLY)  # Note: the trailing slash is significant
