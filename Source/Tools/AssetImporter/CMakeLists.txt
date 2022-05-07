# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Define target name
set (TARGET_NAME AssetImporter)

# Define source files
define_source_files ()

# Define dependency libs
add_subdirectory (../../ThirdParty/Assimp ../../ThirdParty/Assimp)
set (LIBS Assimp)
set (INCLUDE_DIRS ../../ThirdParty/Assimp/include ${CMAKE_CURRENT_BINARY_DIR}/../../ThirdParty/Assimp/include)

# Setup target
setup_executable (TOOL)
