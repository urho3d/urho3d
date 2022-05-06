# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Define target name
set (TARGET_NAME boost)

# Setup target
add_custom_target (${TARGET_NAME} ALL)   # Dummy target just so that its post-build step can install headers to the build tree
set (STATIC_LIBRARY_TARGETS ${STATIC_LIBRARY_TARGETS} ${TARGET_NAME} PARENT_SCOPE)

# Install headers for building and using the Urho3D library (install dependency for Urho3D/ThirdParty/AngelScript/wrap.h)
install_header_files (DIRECTORY ./ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/boost FILES_MATCHING PATTERN *.hpp USE_FILE_SYMLINK)  # Note: the trailing slash is significant
