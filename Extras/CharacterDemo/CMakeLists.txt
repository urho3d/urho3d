# Define target name
set (TARGET_NAME CharacterDemo)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define dependency libs
set (LIBS ../../Engine/Container ../../Engine/Core ../../Engine/Engine ../../Engine/Graphics ../../Engine/Input ../../Engine/IO ../../Engine/Math 
    ../../Engine/Network ../../Engine/Physics ../../Engine/Resource ../../Engine/Scene ../../Engine/UI ../../ThirdParty/Bullet/src)

# Setup target
if (WIN32)
    set (EXE_TYPE WIN32)
elseif (APPLE)
    set (CMAKE_EXE_LINKER_FLAGS "-framework AudioUnit -framework Carbon -framework Cocoa -framework CoreAudio -framework ForceFeedback -framework IOKit -framework OpenGL -framework CoreServices")
endif ()
setup_executable ()
