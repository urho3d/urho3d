# Define target name
set (TARGET_NAME NormalMapTool)

# Define source files
set (SOURCE_FILES NormalMapTool.cpp)

# Include directories
include_directories (
    ../../Engine/Common ../../Engine/Math ../../Engine/Resource ../../ThirdParty/STB
)

# Define target & libraries to link
add_executable (${TARGET_NAME} ${SOURCE_FILES})
target_link_libraries (${TARGET_NAME} Common Math Resource STB)
finalize_exe ()