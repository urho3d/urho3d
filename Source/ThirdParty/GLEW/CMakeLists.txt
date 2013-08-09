# Define target name
set (TARGET_NAME GLEW)

# Define source files
file (GLOB C_FILES *.c)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${C_FILES} ${H_FILES})

# Define dependency libs
set (INCLUDE_DIRS_ONLY .)

# Setup target
setup_library ()
