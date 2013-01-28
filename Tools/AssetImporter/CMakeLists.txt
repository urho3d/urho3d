# Define target name
set (TARGET_NAME AssetImporter)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Include directories
include_directories (
    ../../Engine/Container ../../Engine/Core ../../Engine/Graphics ../../Engine/IO ../../Engine/Math
    ../../Engine/Resource ../../Engine/Physics ../../Engine/Scene ../../ThirdParty/Assimp/include
    ../../ThirdParty/Bullet/src
)

# Define target & libraries to link
if (APPLE)
    set (CMAKE_EXE_LINKER_FLAGS "-framework AudioUnit -framework Carbon -framework Cocoa -framework CoreAudio -framework ForceFeedback -framework IOKit -framework OpenGL -framework CoreServices")
endif ()
add_executable (${TARGET_NAME} ${SOURCE_FILES})
target_link_libraries (${TARGET_NAME} Assimp Container Core Graphics IO Math Physics Scene Resource)
finalize_exe ()

