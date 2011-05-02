# Define target name
set (TARGET_NAME Graphics)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Include directories
include_directories (
    ../Core ../IO ../Math ../Resource ../Scene
)

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})
target_link_libraries (${TARGET_NAME} Core Math Resource Scene d3d9.lib)
enable_pch ()
finalize_lib ()