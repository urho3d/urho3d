# Define target name
set (TARGET_NAME Civetweb)

# Define source files
file (GLOB C_FILES src/*.c)
file (GLOB H_FILES include/*.h)
set (SOURCE_FILES ${C_FILES} ${H_FILES})

# Define include directory
set (INCLUDE_DIRS_ONLY include)

# Setup target
setup_library ()
