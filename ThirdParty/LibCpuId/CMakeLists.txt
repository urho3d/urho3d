# Define target name
set (TARGET_NAME LibCpuId)

# Define source files
file (GLOB C_FILES
    libcpuid/*.c
)

file (GLOB H_FILES
    libcpuid/*.h
)

if (MSVC AND ENABLE_64BIT)
    # Commented out due to cmake bug
    #enable_language(ASM_MASM)
    #set (ASM_FILES libcpuid/masm-x64.asm)
    # As a temporary workaround
    add_custom_command(OUTPUT masm-x64.obj COMMAND ${CMAKE_ASM_MASM_COMPILER} -c libcpuid/masm-x64.asm DEPENDS libcpuid/masm-x64.asm COMMENT "Temporary workaround for MASM") 
    set (ASM_FILES masm-x64.obj)
endif ()

set (SOURCE_FILES ${C_FILES} ${H_FILES} ${ASM_FILES})

# Define dependency libs
set (INCLUDE_DIRS_ONLY libcpuid)

# Setup target
setup_library ()
