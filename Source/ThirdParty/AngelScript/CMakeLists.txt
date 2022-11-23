# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Define target name
set (TARGET_NAME AngelScript)

# Define preprocessor macros
if (CLANG_PRE_STANDARD)
    add_definitions (-DCLANG_PRE_STANDARD)
endif ()
if (NOT EXCEPTIONS)
    add_definitions (-DAS_NO_EXCEPTIONS)
endif ()

if (URHO3D_FORCE_AS_MAX_PORTABILITY)
    add_definitions (-DAS_MAX_PORTABILITY)
endif ()

# Define source files
define_source_files (GLOB_CPP_PATTERNS source/*.cpp GLOB_H_PATTERNS include/*.h source/*.h)
if (ARM)
    enable_language (ASM)
    if (XCODE)
        # It is safe to add this assembler code in universal binary build because it has sufficient preprocessor define guards to exclude unsupported archs
        set (ASM_FILES source/as_callfunc_arm_xcode.S)
    else ()
		if (URHO3D_64BIT)
			set (ASM_FILES source/as_callfunc_arm64_gcc.S)
		else ()
			set (ASM_FILES source/as_callfunc_arm_gcc.S)
		endif ()
        set (CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${ARM_CFLAGS}")
    endif ()
elseif (MSVC AND URHO3D_64BIT)
    enable_language (ASM_MASM)
    # Commented out due to cmake bug - todo: Recheck if this workaround is still necessary when increasing CMake minimum version
    #set (ASM_FILES source/as_callfunc_x64_msvc_asm.asm)
    # As a temporary workaround
    add_custom_command (OUTPUT as_callfunc_x64_msvc_asm.obj COMMAND ${CMAKE_ASM_MASM_COMPILER} -Fo ${CMAKE_CURRENT_BINARY_DIR}/as_callfunc_x64_msvc_asm.obj -c ${CMAKE_CURRENT_SOURCE_DIR}/source/as_callfunc_x64_msvc_asm.asm DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/as_callfunc_x64_msvc_asm.asm COMMENT "Temporary workaround for MASM")
    set (ASM_FILES ${CMAKE_CURRENT_BINARY_DIR}/as_callfunc_x64_msvc_asm.obj ${CMAKE_CURRENT_SOURCE_DIR}/source/as_callfunc_x64_msvc_asm.asm)
endif ()
list (APPEND SOURCE_FILES ${ASM_FILES})

# Define dependency libs
set (INCLUDE_DIRS include)

# Setup target
setup_library ()

# Install headers for building and using the Urho3D library (install dependency for Urho3D/Script/APITemplates.h)
install_header_files (DIRECTORY include/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/AngelScript FILES_MATCHING PATTERN *.h)     # Note: the trailing slash is significant
