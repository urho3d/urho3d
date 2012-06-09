# Define target name
set (TARGET_NAME AngelScript)

# Define source files
file (GLOB CPP_FILES
    source/*.cpp
)

file (GLOB H_FILES
    include/*.h source/*.h
)

if (NOT IOS)
    set (SOURCE_FILES ${CPP_FILES} ${H_FILES})
else ()
    set (ASM_FILES source/as_callfunc_arm_xcode.S)
    set (SOURCE_FILES ${CPP_FILES} ${ASM_FILES} ${H_FILES})
endif ()

# Include directories
include_directories (
    include source
)

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})
finalize_lib ()