# Define target name
set (TARGET_NAME Engine)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Include directories
include_directories (
    ../Audio ../Common ../Input ../Math ../Network ../Physics ../Renderer ../Resource ../Scene ../Script
    ../UI ../../ThirdParty/AngelScript/include
)

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})
target_link_libraries (${TARGET_NAME} Audio Common Input Math Network Physics Renderer Resource
    Scene Script UI)
enable_pch ()
finalize_lib ()
