# Define target name
set (TARGET_NAME SDL)

# Define source files
file (GLOB C_FILES
    src/*.c src/atomic/*.c src/audio/*.c src/audio/dummy/*.c src/cpuinfo/*.c src/events/*.c src/file/*.c src/libm/*.c src/render/*.c src/render/opengl/*.c src/render/software/*.c src/stdlib/*.c src/thread/*.c src/timer/*.c src/video/*.c
)
    
if (WIN32)
    file (GLOB PLATFORM_C_FILES
        src/audio/windx5/*.c src/core/windows/*.c src/loadso/windows/*.c src/thread/windows/*.c src/timer/windows/*.c src/video/windows/*.c
    )
elseif (UNIX)
    file (GLOB PLATFORM_C_FILES
        src/audio/alsa/*.c src/audio/dma/*.c src/audio/dsp/*.c src/loadso/dlopen/*.c src/thread/pthread/*.c src/timer/unix/*.c src/video/x11/*.c        
    )
endif ()

file (GLOB H_FILES include/*.h)

set (SOURCE_FILES ${C_FILES} ${PLATFORM_C_FILES} ${H_FILES})

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})

if (WIN32)
    target_link_libraries (${TARGET_NAME} winmm.lib opengl32.lib)
elseif (UNIX)
    target_link_libraries (${TARGET_NAME} dl GL pthread)
endif ()

finalize_lib ()
