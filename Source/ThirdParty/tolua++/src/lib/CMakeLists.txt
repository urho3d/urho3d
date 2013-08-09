# Define target name
set (TARGET_NAME tolua++_static)

# Define source files
file (GLOB CPP_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.c)
file (GLOB H_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define dependency libs
set (INCLUDE_DIRS_ONLY ../../include ../../../Lua/src)

# Setup target
setup_library ()
adjust_library_name ()
