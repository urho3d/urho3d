# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Define target name
set (TARGET_NAME Tracy)

# Definition
add_definitions (-DTRACY_ENABLE=1)

if (MINGW)
    add_definitions (-D_WIN32_WINNT=0x601)
endif ()

if (URHO3D_LIB_TYPE STREQUAL SHARED)
    add_definitions (-DTRACY_EXPORTS)
endif ()

# On Android, we define TRACY_TIMER_FALLBACK to make timer work on both physical and virtual devices
if (ANDROID)
    add_definitions (-DTRACY_TIMER_FALLBACK=1)
endif ()

# Define source files
define_source_files (TracyClient.cpp)

# Setup target
setup_library ()

# Install headers for building the Urho3D library
install_header_files (DIRECTORY ./ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/Tracy FILES_MATCHING PATTERN *.hpp *.h BUILD_TREE_ONLY)  # Note: the trailing slash is significant
