# Define target name
set (TARGET_NAME Recast)

# Define source files
file (GLOB CPP_FILES Source/*.cpp)
file (GLOB H_FILES Include/*.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define dependency libs
set (INCLUDE_DIRS_ONLY Include)

# Setup target
setup_library ()
