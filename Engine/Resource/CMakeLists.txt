# Define target name
set (TARGET_NAME Resource)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Include directories
include_directories (
    ../Container ../Core ../IO ../Math ../../ThirdParty/STB ../../ThirdParty/TinyXML
)

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})
target_link_libraries (${TARGET_NAME} Container Core IO Math STB TinyXML)
enable_pch ()
finalize_lib ()
