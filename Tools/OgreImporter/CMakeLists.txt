# Define target name
set (TARGET_NAME OgreImporter)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define dependency libs
set (LIBS ../../Engine/Container ../../Engine/Core ../../Engine/Graphics ../../Engine/IO ../../Engine/Math ../../Engine/Resource)

# Setup target
if (APPLE)
    set (CMAKE_EXE_LINKER_FLAGS "-framework Foundation -framework CoreServices")
endif ()
setup_executable ()
