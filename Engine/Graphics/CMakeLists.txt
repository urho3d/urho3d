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

# Include directories
include_directories (
    . ../Container ../Core ../IO ../Math ../Resource ../Scene
)

if (USE_OPENGL)
    include_directories (../../ThirdParty/GLee)
endif ()

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})
target_link_libraries (${TARGET_NAME} Container Core Math Resource Scene SDL)

if (USE_OPENGL)
    target_link_libraries (${TARGET_NAME} GLee)
else ()
    target_link_libraries (${TARGET_NAME} d3d9.lib)
endif ()

enable_pch ()
finalize_lib ()