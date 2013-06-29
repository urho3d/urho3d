# Define target name
set (TARGET_NAME Tolua++)

# Define source files
file (GLOB CPP_FILES src/*.c)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define dependency libs
set (INCLUDE_DIRS_ONLY include ../lua)

# Setup target
setup_library ()
