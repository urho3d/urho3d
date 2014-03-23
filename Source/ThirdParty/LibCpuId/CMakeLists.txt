# Define target name
set (TARGET_NAME LibCpuId)

# Define source files
file (GLOB C_FILES
    src/*.c
)

file (GLOB H_FILES
    src/*.h
)

if (MSVC AND ENABLE_64BIT)
    enable_language (ASM_MASM)
    # Commented out due to cmake bug
    #set (ASM_FILES src/masm-x64.asm)
    # As a temporary workaround
    add_custom_command (OUTPUT masm-x64.obj COMMAND ${CMAKE_ASM_MASM_COMPILER} -Fo ${CMAKE_CURRENT_BINARY_DIR}/masm-x64.obj -c ${CMAKE_CURRENT_SOURCE_DIR}/src/masm-x64.asm DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/masm-x64.asm COMMENT "Temporary workaround for MASM") 
    set (ASM_FILES ${CMAKE_CURRENT_BINARY_DIR}/masm-x64.obj ${CMAKE_CURRENT_SOURCE_DIR}/src/masm-x64.asm)
endif ()

set (SOURCE_FILES ${C_FILES} ${H_FILES} ${ASM_FILES})
set (AMALG_EXCLUDES asm-bits|recog)

# Define dependency libs
set (INCLUDE_DIRS_ONLY src)

# Setup target
setup_library ()
