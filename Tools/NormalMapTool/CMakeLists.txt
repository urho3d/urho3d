# Define target name
set (TARGET_NAME NormalMapTool)

# Define source files
set (SOURCE_FILES NormalMapTool.cpp)

# Include directories
include_directories (
    ../../Engine/Core ../../Engine/IO ../../Engine/Math ../../Engine/Resource ../../ThirdParty/STB
)

# Define target & libraries to link
add_executable (${TARGET_NAME} ${SOURCE_FILES})
target_link_libraries (${TARGET_NAME} Core IO Math Resource STB)
finalize_exe ()