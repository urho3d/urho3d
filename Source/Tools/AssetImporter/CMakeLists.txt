# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Define target name
set (TARGET_NAME AssetImporter)

# Urho3D: This hack allows build 32-bit version on Ubunti x64
# TODO: Why is it not being detected correctly?
if (CMAKE_LIBRARY_ARCHITECTURE STREQUAL "x86_64-linux-gnu" AND NOT URHO3D_64BIT)
    set (CMAKE_LIBRARY_ARCHITECTURE "i386-linux-gnu")
endif ()

# Define source files
define_source_files ()

# Define dependency libs
add_subdirectory (../../ThirdParty/Assimp ../../ThirdParty/Assimp)
set (LIBS Assimp)
set (INCLUDE_DIRS ../../ThirdParty/Assimp/include ${CMAKE_CURRENT_BINARY_DIR}/../../ThirdParty/Assimp/include)

# Setup target
setup_executable (TOOL)
