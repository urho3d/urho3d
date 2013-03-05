# Define target name
set (TARGET_NAME ScriptAPIDumper)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define dependency libs
set (LIBS ../../Engine/Container ../../Engine/Core ../../Engine/Engine ../../Engine/IO ../../Engine/Math ../../Engine/Script)

# Setup target
if (APPLE)
    set (CMAKE_EXE_LINKER_FLAGS "-framework AudioUnit -framework Carbon -framework Cocoa -framework CoreAudio -framework ForceFeedback -framework IOKit -framework OpenGL")
endif ()
setup_executable ()
