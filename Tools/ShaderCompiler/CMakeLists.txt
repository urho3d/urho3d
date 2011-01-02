# Define target name
set (TARGET_NAME ShaderCompiler)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Include directories
include_directories (
    ../../Engine/Common ../../Engine/Math ../../Engine/Resource ../../ThirdParty/TinyXML
)

# Define target & libraries to link
add_executable (${TARGET_NAME} ${SOURCE_FILES})
target_link_libraries (${TARGET_NAME} Common Resource TinyXML)
finalize_exe ()
