# Define target name
set (TARGET_NAME GLee)

# Define source files
file (GLOB C_FILES *.c)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${C_FILES} ${H_FILES})

# Define dependency libs
set (LINK_LIBS_ONLY SDL)

# Setup target
setup_library ()
