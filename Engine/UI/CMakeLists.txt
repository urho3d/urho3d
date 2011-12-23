# Define target name
set (TARGET_NAME UI)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Include directories
include_directories (
    ../Container ../Core ../Graphics ../Input ../IO ../Math ../Resource 
    ../../ThirdParty/FreeType/include
)

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})
target_link_libraries (${TARGET_NAME} Container Core FreeType Graphics Input IO Math Resource)
enable_pch ()
finalize_lib ()
