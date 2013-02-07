# Define target name
set (TARGET_NAME AssetImporter)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define dependency libs
set (LIBS ../../Engine/Container ../../Engine/Core ../../Engine/Graphics ../../Engine/IO ../../Engine/Math ../../Engine/Physics ../../Engine/Resource ../../Engine/Scene ../../ThirdParty/Assimp/include)
set (INCLUDE_DIRS_ONLY ../../ThirdParty/Bullet/src)

# Setup target
if (APPLE)
    set (CMAKE_EXE_LINKER_FLAGS "-framework AudioUnit -framework Carbon -framework Cocoa -framework CoreAudio -framework ForceFeedback -framework IOKit -framework OpenGL -framework CoreServices")
endif ()
setup_executable ()
