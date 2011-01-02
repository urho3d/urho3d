# Define target name
set (TARGET_NAME PackageTool)

# Define source files
set (SOURCE_FILES PackageTool.cpp)

# Include directories
include_directories (
    ../../Engine/Common ../../Engine/Math ../../Engine/Resource
)

# Define target & libraries to link
add_executable (${TARGET_NAME} ${SOURCE_FILES})
target_link_libraries (${TARGET_NAME} Common Math Resource)
finalize_exe ()