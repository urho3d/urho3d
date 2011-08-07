# Define target name
set (TARGET_NAME Audio)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Include directories
include_directories (
    ../Container ../Core ../Graphics ../IO ../Math ../Resource ../Scene ../../ThirdParty/STB
)

if (USE_OPENGL)
    include_directories (../../ThirdParty/PortAudio/include)
endif ()

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})
target_link_libraries (${TARGET_NAME} Container Core Graphics IO Math Resource Scene STB)

if (USE_OPENGL)
    target_link_libraries (${TARGET_NAME} PortAudio)
else ()
    target_link_libraries (${TARGET_NAME} dsound.lib)
endif ()

enable_pch ()
finalize_lib ()
