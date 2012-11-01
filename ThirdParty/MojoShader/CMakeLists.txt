# Define target name
set (TARGET_NAME MojoShader)

# Define source files
file (GLOB C_FILES *.c)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${C_FILES} ${H_FILES})

add_definitions(-DMOJOSHADER_NO_VERSION_INCLUDE)
if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS=1 -TP)
endif(MSVC)

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})
finalize_lib ()
