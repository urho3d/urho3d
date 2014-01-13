# Define target name
set (TARGET_NAME AngelScript)

# Define source files
file (GLOB CPP_FILES
    source/*.cpp
)
file (GLOB H_FILES
    include/*.h source/*.h
)

if (IOS OR ANDROID OR RASPI)
    enable_language (ASM)
    if (IOS)
        set (ASM_FILES source/as_callfunc_arm_xcode.S)
    else ()
        set (ASM_FILES source/as_callfunc_arm_gcc.S)
    endif ()
endif ()

if (MSVC AND ENABLE_64BIT)
    enable_language(ASM_MASM)
    # Commented out due to cmake bug
    #set (ASM_FILES source/as_callfunc_x64_msvc_asm.asm)
    # As a temporary workaround
    add_custom_command(OUTPUT as_callfunc_x64_msvc_asm.obj COMMAND ${CMAKE_ASM_MASM_COMPILER} -Fo ${CMAKE_CURRENT_BINARY_DIR}/as_callfunc_x64_msvc_asm.obj -c ${CMAKE_CURRENT_SOURCE_DIR}/source/as_callfunc_x64_msvc_asm.asm DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/as_callfunc_x64_msvc_asm.asm COMMENT "Temporary workaround for MASM") 
    set (ASM_FILES ${CMAKE_CURRENT_BINARY_DIR}/as_callfunc_x64_msvc_asm.obj ${CMAKE_CURRENT_SOURCE_DIR}/source/as_callfunc_x64_msvc_asm.asm)
endif ()

set (SOURCE_FILES ${CPP_FILES} ${ASM_FILES} ${H_FILES})

# Install dependency for Engine/Script/APITemplates.h
install (DIRECTORY include/ DESTINATION ${DEST_INCLUDE_DIR}/AngelScript USE_SOURCE_PERMISSIONS FILES_MATCHING PATTERN *.h)     # Note: the trailing slash is significant
set (INSTALL_INCLUDE_DIRS ${INSTALL_INCLUDE_DIRS} AngelScript PARENT_SCOPE)

# Define dependency libs
set (INCLUDE_DIRS_ONLY include)

# Setup target
setup_library ()

