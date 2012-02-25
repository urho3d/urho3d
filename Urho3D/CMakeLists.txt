# Define target name
set (TARGET_NAME Urho3D)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Include directories
include_directories (
    ../Engine/Container ../Engine/Core ../Engine/Engine ../Engine/IO ../Engine/Math ../Engine/Resource 
    ../Engine/Script
)

# Define target & libraries to link
if (WIN32)
    add_executable (${TARGET_NAME} WIN32 ${SOURCE_FILES})
else ()
    add_executable (${TARGET_NAME} ${SOURCE_FILES})
endif ()

target_link_libraries (${TARGET_NAME} Container Core Engine IO Math Resource Script ${DBGHELP_LIB})
finalize_exe ()
