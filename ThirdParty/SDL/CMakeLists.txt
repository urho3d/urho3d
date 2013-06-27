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
elseif (IOS)
    file (GLOB SYS_C_FILES
        src/audio/coreaudio/*.c src/file/cocoa/*.m src/joystick/iphoneos/*.m src/loadso/dlopen/*.c src/thread/pthread/*.c src/timer/unix/*.c src/video/uikit/*.m src/video/uikit/*.c
    )
elseif (APPLE)
    file (GLOB SYS_C_FILES
        src/audio/coreaudio/*.c src/joystick/darwin/*.c src/loadso/dlopen/*.c src/thread/pthread/*.c src/timer/unix/*.c src/video/cocoa/*.m
    )
else ()
    include(CheckCSourceCompiles)

    # On Linux, make sure development libraries exist, and use their include file directories  
    find_package (OpenGL REQUIRED)
    find_package (X11 REQUIRED)
    if (NOT X11_Xrandr_FOUND)
        message (FATAL_ERROR "Could not find XRandR (libxrandr-dev)")
    endif ()
    find_package (ALSA REQUIRED)

    include_directories (${OpenGL_INCLUDE_DIRS})
    include_directories (${X11_INCLUDE_DIRS})  
    include_directories (${ALSA_INCLUDE_DIRS})

    set(CMAKE_REQUIRED_LIBRARIES ${X11_LIB} ${X11_LIB})
    message ("--")
    message ("-- Following tests check whether X11 library installed in this system uses _Xconst in below functions")
    message ("-- A failed test result simply means the installed X11 library does not use _Xconst")
    message ("-- It is OK to proceed to build Urho3D regardless of the test result")
    check_c_source_compiles("
        #include <X11/Xlib.h>
        #include <X11/Xproto.h>
        #include <X11/extensions/Xext.h>
        #include <X11/extensions/extutil.h>
        extern XExtDisplayInfo* XextAddDisplay(XExtensionInfo* a,Display* b,_Xconst char* c,XExtensionHooks* d,int e,XPointer f);
        int main(int argc, char **argv) {}" HAVE_CONST_XEXT_ADDDISPLAY)
    if (HAVE_CONST_XEXT_ADDDISPLAY)
        add_definitions (-DSDL_VIDEO_DRIVER_X11_CONST_PARAM_XEXTADDDISPLAY)
    endif ()
    check_c_source_compiles("
        #include <X11/Xlibint.h>
        extern int _XData32(Display *dpy,register _Xconst long *data,unsigned len);
        int main(int argc, char **argv) {}" HAVE_CONST_XDATA32)
    if (HAVE_CONST_XDATA32)
        add_definitions (-DSDL_VIDEO_DRIVER_X11_CONST_PARAM_XDATA32)
    endif ()
    message ("--")
    set(CMAKE_REQUIRED_LIBRARIES)

    file (GLOB SYS_C_FILES
        src/audio/alsa/*.c src/audio/dma/*.c src/audio/dsp/*.c src/joystick/linux/*.c src/loadso/dlopen/*.c src/thread/pthread/*.c src/timer/unix/*.c src/video/x11/*.c
    )
endif ()

file (GLOB H_FILES include/*.h)

set_source_files_properties (${C_FILES} PROPERTIES LANGUAGE C)
set_source_files_properties (${SYS_C_FILES} PROPERTIES LANGUAGE C)
set (SOURCE_FILES ${C_FILES} ${SYS_C_FILES} ${H_FILES})

# Define target & libraries to link
add_library (${TARGET_NAME} STATIC ${SOURCE_FILES})

if (WIN32)
    if (USE_OPENGL)
        target_link_libraries (${TARGET_NAME} winmm.lib opengl32.lib)
    else ()
        target_link_libraries (${TARGET_NAME} winmm.lib)
    endif ()
elseif (APPLE)
    target_link_libraries (${TARGET_NAME} dl pthread)
else ()
    target_link_libraries (${TARGET_NAME} dl pthread GL)
endif ()
