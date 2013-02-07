# Define target name
set (TARGET_NAME LibCpuId)

# Define source files
file (GLOB C_FILES
    libcpuid/*.c
)

file (GLOB H_FILES
    libcpuid/*.h
)

set (SOURCE_FILES ${C_FILES} ${H_FILES})

# Define dependency libs
set (INCLUDE_DIRS_ONLY libcpuid)

# Setup target
setup_library ()
