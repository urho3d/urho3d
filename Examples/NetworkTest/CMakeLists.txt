# Define target name
set (TARGET_NAME NetworkTest)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Include directories
include_directories (
    ../../Engine/Common ../../Engine/Event ../../Engine/Math ../../Engine/Network
)

# Define target & libraries to link
add_executable (${TARGET_NAME} ${SOURCE_FILES})
set_target_properties (${TARGET_NAME} PROPERTIES DEBUG_POSTFIX _d)
target_link_libraries (${TARGET_NAME} Common Event Math Network)
finalize_exe ()
