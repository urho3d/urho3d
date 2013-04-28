# Define target name
set (TARGET_NAME AngelScript)

# Define source files
file (GLOB CPP_FILES
    source/*.cpp
)
file (GLOB H_FILES
    include/*.h source/*.h
)

if (IOS)
    set (ASM_FILES source/as_callfunc_arm_xcode.S)
endif ()

if (MSVC AND ENABLE_64BIT)
    set (ASM_FILES source/as_callfunc_x64_msvc_asm.asm)
endif ()

set (SOURCE_FILES ${CPP_FILES} ${ASM_FILES} ${H_FILES})

# Define dependency libs
set (INCLUDE_DIRS_ONLY include source)

# Setup target
setup_library ()

