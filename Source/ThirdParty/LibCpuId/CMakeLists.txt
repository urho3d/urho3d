# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Define target name
set (TARGET_NAME LibCpuId)

# Define preprocessor macros
add_definitions (-DVERSION="0.4.0+")
if (HAVE_STDINT_H)
    add_definitions (-DHAVE_STDINT_H)
endif ()

# Define generated source files
if (MSVC AND URHO3D_64BIT)
    enable_language (ASM_MASM)
    # Commented out due to cmake bug
    #set (ASM_FILES src/masm-x64.asm)
    # As a temporary workaround
    add_custom_command (OUTPUT masm-x64.obj COMMAND ${CMAKE_ASM_MASM_COMPILER} -Fo ${CMAKE_CURRENT_BINARY_DIR}/masm-x64.obj -c ${CMAKE_CURRENT_SOURCE_DIR}/src/masm-x64.asm DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/masm-x64.asm COMMENT "Temporary workaround for MASM")
    set (ASM_FILES ${CMAKE_CURRENT_BINARY_DIR}/masm-x64.obj ${CMAKE_CURRENT_SOURCE_DIR}/src/masm-x64.asm)
endif ()

# Define source files
define_source_files (GLOB_CPP_PATTERNS src/*.c GLOB_H_PATTERNS src/*.h)
list (APPEND SOURCE_FILES ${ASM_FILES})

# Define dependency libs
set (INCLUDE_DIRS src)

# Setup target
setup_library ()

# Install headers for building the Urho3D library
install_header_files (DIRECTORY src/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/LibCpuId FILES_MATCHING PATTERN *.h BUILD_TREE_ONLY)  # Note: the trailing slash is significant
