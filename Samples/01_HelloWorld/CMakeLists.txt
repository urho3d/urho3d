# Define target name
set (TARGET_NAME 01_HelloWorld)

# Define source files
set (H_FILES ${H_FILES} HelloWorld.h)
set (CPP_FILES HelloWorld.cpp)

set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define dependency libs
set (LIBS ../../Engine/Container
          ../../Engine/Core
          ../../Engine/Engine
          ../../Engine/Graphics
          ../../Engine/Input
          ../../Engine/IO
          ../../Engine/Math
          ../../Engine/Resource
          ../../Engine/Scene
          ../../Engine/UI)

# Setup target with resource copying
setup_main_executable ()
