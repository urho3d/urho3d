# Define target name
set (TARGET_NAME MojoShader)

# Define source files
file (GLOB C_FILES *.c)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${C_FILES} ${H_FILES})

if (MSVC)
    add_definitions (-D_CRT_SECURE_NO_WARNINGS=1 -TP)
endif (MSVC)
set (AMALG_EXCLUDES .)

# Setup target
setup_library ()
