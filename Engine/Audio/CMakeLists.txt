# Define target name
set (TARGET_NAME Audio)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Include directories
include_directories (
    ../Core ../Graphics ../IO ../Math ../Resource ../Scene ../../ThirdParty/STB
)

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})
target_link_libraries (${TARGET_NAME} Core Graphics IO Math Resource Scene STB dsound.lib)
enable_pch ()
finalize_lib ()
