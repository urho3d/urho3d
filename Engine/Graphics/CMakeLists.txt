# Define target name
set (TARGET_NAME Graphics)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)

if (USE_OPENGL)
    file (GLOB IMPL_CPP_FILES OpenGL/*.cpp)
    file (GLOB IMPL_H_FILES OpenGL/*.h)
    set (SOURCE_FILES ${CPP_FILES} ${H_FILES} ${IMPL_CPP_FILES} ${IMPL_H_FILES})

    # Include directories
    include_directories (
        . ../Container ../Core ../IO ../Math ../Resource ../Scene ../../ThirdParty/GLee
    )

    # Define target & libraries to link
    add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})
    target_link_libraries (${TARGET_NAME} Container Core GLee Math Resource Scene opengl32.lib)
else ()
    file (GLOB IMPL_CPP_FILES Direct3D9/*.cpp)
    file (GLOB IMPL_H_FILES Direct3D9/*.h)
    set (SOURCE_FILES ${CPP_FILES} ${H_FILES} ${IMPL_CPP_FILES} ${IMPL_H_FILES})

    # Include directories
    include_directories (
        . ../Container ../Core ../IO ../Math ../Resource ../Scene
    )

    # Define target & libraries to link
    add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})
    target_link_libraries (${TARGET_NAME} Container Core Math Resource Scene d3d9.lib)
endif ()

enable_pch ()
finalize_lib ()