# Define target name
set (TARGET_NAME PugiXml)

# Define source files
file (GLOB CPP_FILES src/*.cpp)
file (GLOB H_FILES src/*.hpp)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})
finalize_lib ()