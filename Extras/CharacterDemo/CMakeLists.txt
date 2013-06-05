# Define target name
set (TARGET_NAME CharacterDemo)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define dependency libs
set (LIBS ../../Engine/Container ../../Engine/Core ../../Engine/Engine ../../Engine/Graphics ../../Engine/Input ../../Engine/IO ../../Engine/Math 
    ../../Engine/Network ../../Engine/Physics ../../Engine/Resource ../../Engine/Scene ../../Engine/UI)
set (INCLUDE_DIRS_ONLY ../../ThirdParty/Bullet/src)

# Setup target with resource copying
setup_main_executable ()
