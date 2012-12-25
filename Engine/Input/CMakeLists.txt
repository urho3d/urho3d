# Define target name
set (TARGET_NAME Input)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Include directories
include_directories (
    ../Container ../Core ../Graphics ../IO ../Math ../Resource ../Scene ../Engine
)

if (USE_OPENGL)
    include_directories (../../ThirdParty/GLee)
endif ()

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})
target_link_libraries (${TARGET_NAME} Container Core Graphics IO Math Resource Scene SDL)

finalize_lib ()
