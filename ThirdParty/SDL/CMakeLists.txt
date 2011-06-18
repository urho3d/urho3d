# Define target name
set (TARGET_NAME SDL)

# Define source files
file (GLOB C_FILES
    src/*.c src/atomic/*.c src/audio/*.c src/audio/windx5/*.c src/audio/dummy/*.c src/core/windows/*.c src/cpuinfo/*.c src/events/*.c src/file/*.c src/libm/*.c src/loadso/windows/*.c src/render/*.c src/render/opengl/*.c src/render/software/*.c src/stdlib/*.c src/thread/*.c src/thread/windows/*.c src/timer/*.c src/timer/windows/*.c src/video/*.c src/video/windows/*.c)
    
file (GLOB H_FILES include/*.h)

set (SOURCE_FILES ${C_FILES} ${H_FILES})

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})
target_link_libraries (${TARGET_NAME} winmm.lib opengl32.lib)
finalize_lib ()
