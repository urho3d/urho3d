# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Define target name
set (TARGET_NAME AutoBinder)

# Define source files
define_source_files ()

# Define dependency libs
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/../../ThirdParty/Mustache Mustache)

# Setup target
setup_executable (TOOL NODEPS)
install (DIRECTORY Templates DESTINATION ${DEST_RUNTIME_DIR})
add_dependencies (${TARGET_NAME} Mustache)
