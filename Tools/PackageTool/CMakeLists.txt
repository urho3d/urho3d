# Define target name
set (TARGET_NAME PackageTool)

# Define source files
set (SOURCE_FILES PackageTool.cpp)

# Define dependency libs
set (LIBS ../../Engine/Container ../../Engine/Core ../../Engine/IO ../../Engine/Math ../../Engine/Resource)

# Setup target
setup_executable ()
