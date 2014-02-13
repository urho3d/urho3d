# Define target name
set (TARGET_NAME STB)

# Define source files
file (GLOB C_FILES *.c)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${C_FILES} ${H_FILES})
set (AMALG_EXCLUDES .)

# Setup target
setup_library ()
