# Define target name
set (TARGET_NAME toluapp)

# Define source files
file (GLOB CPP_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.c)
file (GLOB H_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})
set (AMALG_SINGLE_TARGET 1)

# Define dependency libs
set (INCLUDE_DIRS_ONLY ../../include ../../../Lua${JIT}/src)

# Setup target
setup_library ()
