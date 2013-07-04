# Define target name
set (TARGET_NAME Graphics)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)

if (USE_OPENGL)
    file (GLOB SYS_CPP_FILES OpenGL/*.cpp)
    file (GLOB SYS_H_FILES OpenGL/*.h)
else ()
    file (GLOB SYS_CPP_FILES Direct3D9/*.cpp)
    file (GLOB SYS_H_FILES Direct3D9/*.h)
endif ()

set (SOURCE_FILES ${CPP_FILES} ${H_FILES} ${SYS_CPP_FILES} ${SYS_H_FILES})

# Define dependency libs
set (LIBS ../Container ../Core ../IO ../Math ../Resource ../Scene)
set (INCLUDE_DIRS_ONLY .)
set (LINK_LIBS_ONLY SDL)

if (USE_OPENGL)
    if (NOT IOS)
        set (LIBS ${LIBS} ../../ThirdParty/GLEW)
    endif ()
    if (WIN32)
        set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} opengl32.lib)
    endif ()
else ()
    set (LINK_LIBS_ONLY ${LINK_LIBS_ONLY} d3d9.lib)
endif ()

# Setup target
enable_pch ()
setup_library ()
