# Define target name
set (TARGET_NAME Physics)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Include directories
include_directories (
    ../Common ../Math ../Renderer ../Resource ../Scene ../../ThirdParty/ODE/include
    ../../ThirdParty/StanHull
)

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})
target_link_libraries (${TARGET_NAME} Common Math ODE Renderer Resource Scene StanHull)
enable_pch ()
finalize_lib ()