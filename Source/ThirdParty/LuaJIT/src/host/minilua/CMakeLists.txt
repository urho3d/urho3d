# Define target name
set (TARGET_NAME minilua)

# Define source files
set (SOURCE_FILES ../minilua.c)

# Define dependency libs
if (NOT MSVC)
    set (LINK_LIBS_ONLY m)
endif ()

# Setup target
setup_executable ()
