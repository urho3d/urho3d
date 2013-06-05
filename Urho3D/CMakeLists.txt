# Define target name
set (TARGET_NAME Urho3D)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define dependency libs
set (LIBS ../Engine/Container ../Engine/Core ../Engine/Engine ../Engine/IO ../Engine/Math ../Engine/Resource ../Engine/Script)

# Setup target with resource copying
setup_main_executable ()
