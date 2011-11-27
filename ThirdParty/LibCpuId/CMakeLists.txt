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

# Include directories
include_directories (
    libcpuid
)

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})
finalize_lib ()