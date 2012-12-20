# Define target name
set (TARGET_NAME JO)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})
finalize_lib ()

