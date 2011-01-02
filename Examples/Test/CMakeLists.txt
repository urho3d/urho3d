# Define target name
set (TARGET_NAME Test)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Include directories
include_directories (
    ../../Engine/Audio ../../Engine/Common ../../Engine/Engine ../../Engine/Event ../../Engine/Input
    ../../Engine/Math ../../Engine/Network ../../Engine/Physics ../../Engine/Renderer ../../Engine/Resource
    ../../Engine/Scene ../../Engine/UI ../../ThirdParty/STB
)

# Define target & libraries to link
add_executable (${TARGET_NAME} WIN32 ${SOURCE_FILES})
set_target_properties (${TARGET_NAME} PROPERTIES DEBUG_POSTFIX _d)
target_link_libraries (${TARGET_NAME} Audio Common Engine Event Input Math Network Physics Renderer
    Resource Scene UI)
enable_pch ()
finalize_exe ()
