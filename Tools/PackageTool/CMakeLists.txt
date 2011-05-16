# Define target name
set (TARGET_NAME PackageTool)

# Define source files
set (SOURCE_FILES PackageTool.cpp)

# Include directories
include_directories (
    ../../Engine/Container ../../Engine/Core ../../Engine/IO ../../Engine/Math ../../Engine/Resource
)

# Define target & libraries to link
add_executable (${TARGET_NAME} ${SOURCE_FILES})
target_link_libraries (${TARGET_NAME} Container Core IO Math Resource)
finalize_exe ()