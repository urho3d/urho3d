# Define target name
set (TARGET_NAME Input)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

# Define dependency libs
set (LIBS ../Container ../Core ../Graphics ../IO ../Math ../Resource ../Scene)
set (LINK_LIBS_ONLY SDL)

if (USE_OPENGL)
    set (INCLUDE_DIRS_ONLY ${INCLUDE_DIRS_ONLY} ../../ThirdParty/GLEW)
endif ()

# Setup target
setup_library ()
