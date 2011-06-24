# Define target name
set (TARGET_NAME GLFW)

# Define source files
file (GLOB C_FILES lib/*.c)

if (WIN32)
    file (GLOB SYS_C_FILES lib/win32/*.c)
elseif (APPLE)
    file (GLOB SYS_C_FILES lib/cocoa/*.m)
else ()
    file (GLOB SYS_C_FILES lib/x11/*.c)
endif ()

file (GLOB H_FILES include/GL/*.h)

set_source_files_properties (${C_FILES} PROPERTIES LANGUAGE C)
set_source_files_properties (${SYS_FILES} PROPERTIES LANGUAGE C)
set (SOURCE_FILES ${C_FILES} ${SYS_C_FILES} ${H_FILES})

# Include directories and definitions
include_directories (include lib)
if (WIN32)
    include_directories (lib/win32)
elseif (APPLE)
    include_directories (lib/cocoa)
else ()
    include_directories (lib/x11)
    add_definitions (-D_GLFW_HAS_XRANDR -D_GLFW_HAS_PTHREAD -D_GLFW_HAS_SCHED_YIELD -D_GLFW_HAS_GLXGETPROCADDRESS -D_GLFW_HAS_DLOPEN -D_GLFW_HAS_SYSCONF)
endif ()

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})

if (WIN32)
    include_directories (lib/win32)
    target_link_libraries (${TARGET_NAME} winmm.lib opengl32.lib)
elseif (APPLE)
    include_directories (lib/cocoa)
    find_library (CARBON_FW Carbon)
    find_library (COCOA_FW Cocoa)
    find_library (OPENGL_FW OpenGL)
    target_link_libraries (${TARGET_NAME} dl pthread ${CARBON_FW} ${COCOA_FW} ${OPENGL_FW})
else ()
    include_directories (lib/x11)
    target_link_libraries (${TARGET_NAME} GL X11 Xrandr pthread)
endif ()

finalize_lib ()
