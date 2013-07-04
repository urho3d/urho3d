# Define target name
set (TARGET_NAME Lua)

# Define source files
file (GLOB C_FILES src/*.c)
file (GLOB H_FILES src/*.h)
set (SOURCE_FILES ${C_FILES} ${H_FILES})

# Setup target
setup_library ()
