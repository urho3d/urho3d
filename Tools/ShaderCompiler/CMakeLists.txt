# Define target name
set (TARGET_NAME ShaderCompiler)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Include directories
include_directories (
    ../../Engine/Container ../../Engine/Core ../../Engine/IO ../../Engine/Math ../../Engine/Resource
)

# Define target & libraries to link
add_executable (${TARGET_NAME} ${SOURCE_FILES})
target_link_libraries (${TARGET_NAME} Container Core IO Math Resource d3dx9.lib)
finalize_exe ()
