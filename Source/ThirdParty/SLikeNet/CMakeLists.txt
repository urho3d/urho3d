#
# This file was taken from RakNet 4.082.
# Please see licenses/RakNet license.txt for the underlying license and related copyright.
#
#
#
# Modified work: Copyright (c) 2016, SLikeSoft UG (haftungsbeschränkt)
#
# This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
# license found in the license.txt file in the root directory of this source tree.
#

cmake_minimum_required(VERSION 2.6)

# Define target name
set (TARGET_NAME SLikeNet)

add_definitions (-DRAKNET_ENABLE_STATIC)

# Define source files
file (GLOB_RECURSE CPP_FILES *.cpp source)
file (GLOB_RECURSE H_FILES *.h include)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define dependency libs
set (INCLUDE_DIRS src/include)

# Setup target
setup_library ()

# Install headers for building and using the Urho3D library (install dependency for Urho3D)
install_header_files (DIRECTORY src/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/SLikeNet FILES_MATCHING PATTERN *.h USE_FILE_SYMLINK)

