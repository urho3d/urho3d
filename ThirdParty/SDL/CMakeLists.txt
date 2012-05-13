# Define target name
set (TARGET_NAME SDL)

# Define source files
file (GLOB C_FILES
    src/*.c src/atomic/*.c src/audio/*.c src/audio/dummy/*.c src/cpuinfo/*.c src/events/*.c src/file/*.c src/joystick/*.c src/libm/*.c src/stdlib/*.c src/thread/*.c src/timer/*.c src/video/*.c src/video/dummy/*.c
)
    
if (WIN32)
    file (GLOB SYS_C_FILES
        src/audio/directsound/*.c src/joystick/windows/*.c src/core/windows/*.c src/loadso/windows/*.c src/thread/windows/*.c src/timer/windows/*.c src/video/windows/*.c
    )
elseif (APPLE)
    file (GLOB SYS_C_FILES
        src/audio/coreaudio/*.c src/joystick/darwin/*.c src/loadso/dlopen/*.c src/thread/pthread/*.c src/timer/unix/*.c src/video/cocoa/*.m
    )
else ()
    file (GLOB SYS_C_FILES
        src/audio/alsa/*.c src/audio/dma/*.c src/audio/dsp/*.c src/joystick/linux/*.c src/loadso/dlopen/*.c src/thread/pthread/*.c src/timer/unix/*.c src/video/x11/*.c
    )
endif ()

file (GLOB H_FILES include/*.h)

set_source_files_properties (${C_FILES} PROPERTIES LANGUAGE C)
set_source_files_properties (${SYS_FILES} PROPERTIES LANGUAGE C)
set (SOURCE_FILES ${C_FILES} ${SYS_C_FILES} ${H_FILES})

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})

if (WIN32)
    target_link_libraries (${TARGET_NAME} winmm.lib opengl32.lib)
elseif (APPLE)
    FIND_LIBRARY (AUDIOUNIT_FW AudioUnit)
    FIND_LIBRARY (CARBON_FW Carbon)
    FIND_LIBRARY (COCOA_FW Cocoa)
    FIND_LIBRARY (COREAUDIO_FW CoreAudio)
    FIND_LIBRARY (FORCEFEEDBACK_FW ForceFeedback)
    FIND_LIBRARY (IOKIT_FW IOKit)
    FIND_LIBRARY (OPENGL_FW OpenGL)
    target_link_libraries (${TARGET_NAME} dl pthread ${AUDIOUNIT_FW} ${CARBON_FW} ${COCOA_FW} ${COREAUDIO_FW} ${FORCEFEEDBACK_FW} ${IOKIT_FW} ${OPENGL_FW})
else ()
    target_link_libraries (${TARGET_NAME} dl pthread GL)
endif ()

finalize_lib ()
