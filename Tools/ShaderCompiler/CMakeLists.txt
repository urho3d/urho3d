# Define target name
set (TARGET_NAME ShaderCompiler)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define dependency libs
set (LIBS ../../Engine/Container ../../Engine/Core ../../Engine/Graphics ../../Engine/IO ../../Engine/Math ../../Engine/Resource ../../Engine/Scene ../../ThirdParty/MojoShader)
set (LINK_LIBS_ONLY d3dcompiler.lib)

# Setup target
add_definitions(-DMOJOSHADER_NO_VERSION_INCLUDE)
setup_executable ()
