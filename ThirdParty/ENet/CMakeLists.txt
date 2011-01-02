# Define target name
set (TARGET_NAME ENet)

# Define source files
file (GLOB C_FILES *.c)
file (GLOB H_FILES include/enet/*.h)
set (SOURCE_FILES ${C_FILES} ${H_FILES})

# Include directories
include_directories (
    include
)

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})
target_link_libraries (${TARGET_NAME} ws2_32.lib)
finalize_lib ()
