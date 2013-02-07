# Define target name
set (TARGET_NAME RampGenerator)

# Define source files
set (SOURCE_FILES RampGenerator.cpp)

# Define dependency libs
set (LIBS ../../Engine/Container ../../Engine/Core ../../Engine/IO ../../Engine/Math ../../Engine/Resource ../../ThirdParty/STB)

# Setup target
setup_executable ()
