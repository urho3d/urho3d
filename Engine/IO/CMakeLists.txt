# Define target name
set (TARGET_NAME IO)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)

if (APPLE AND NOT IOS)
    file (GLOB C_FILES *.m)
endif()

set (SOURCE_FILES ${CPP_FILES} ${C_FILES} ${H_FILES})

# Include directories
include_directories (
    ../Container ../Core ../Math
)

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})
target_link_libraries (${TARGET_NAME} Container Core Math)
enable_pch ()
finalize_lib ()
