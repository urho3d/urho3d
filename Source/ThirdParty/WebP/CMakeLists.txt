# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Define target name
set (TARGET_NAME WebP)

# Define source files
define_source_files (RECURSE GLOB_CPP_PATTERNS src/*.c GLOB_H_PATTERNS src/*.h)

# Define dependency libs
if (ANDROID)
    set (INCLUDE_DIRS ${ANDROID_NDK}/sources/android/cpufeatures)
endif ()

# Setup target
setup_library ()

# Install headers for building the Urho3D library
install_header_files (DIRECTORY src/webp/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/webp FILES_MATCHING PATTERN *.h BUILD_TREE_ONLY)  # Note: the trailing slash is significant
