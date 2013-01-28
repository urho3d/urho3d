# Define target name
set (TARGET_NAME OgreImporter)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Include directories
include_directories (
    ../../Engine/Container ../../Engine/Core ../../Engine/Graphics ../../Engine/IO ../../Engine/Math 
    ../../Engine/Physics ../../Engine/Resource
)

# Define target & libraries to link
if (APPLE)
    set (CMAKE_EXE_LINKER_FLAGS "-framework Foundation -framework CoreServices")
endif ()
add_executable (${TARGET_NAME} ${SOURCE_FILES})
target_link_libraries (${TARGET_NAME} Container Core Graphics IO Math Resource)
finalize_exe ()

