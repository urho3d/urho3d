#
# Copyright (c) 2008-2015 the Urho3D project.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#

# Define target name
set (TARGET_NAME SDL)

if (EMSCRIPTEN)
    # Emscripten has its own SDL2 port, so just create a custom target to:
    #  1) Fetch this SDL2 port from its GitHub repository
    #  2) Install SDL2 headers to the build tree in the post-build step (Note: current configuration uses our own SDL2 header files instead of the ones provided by Emscripten port for no special reason)
    add_custom_target (${TARGET_NAME} ALL ${CMAKE_COMMAND} -E touch dummy.cpp && ${CMAKE_CXX_COMPILER} -s USE_SDL=2 -o dummy.html dummy.cpp && ${CMAKE_COMMAND} -E remove dummy.*)
    set (STATIC_LIBRARY_TARGETS ${STATIC_LIBRARY_TARGETS} ${TARGET_NAME} PARENT_SCOPE)
    install_header_files (DIRECTORY include/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/SDL FILES_MATCHING PATTERN *.h USE_FILE_SYMLINK)    # Note: the trailing slash is significant
    return ()
endif ()

# Define source files
file (GLOB C_FILES
    src/*.c src/atomic/*.c src/audio/*.c src/audio/disk/*.c src/audio/dummy/*.c src/cpuinfo/*.c src/events/*.c src/file/*.c
    src/haptic/*.c src/joystick/*.c src/libm/*.c src/power/*.c src/stdlib/*.c
    src/thread/*.c src/timer/*.c src/video/*.c src/video/dummy/*.c
)

if (WIN32)
    # New MinGW versions may evaluate whether to use A or W postfix on functions before SDL gets to define UNICODE on its own,
    # so make sure it is already defined
    if (MINGW)
        add_definitions (-DUNICODE=1)
    endif ()
    CHECK_INCLUDE_FILES (wbemcli.h HAVE_WBEMCLI_H)
    if (HAVE_WBEMCLI_H)
        add_definitions (-DSDL_JOYSTICK_DINPUT)
        add_definitions (-DSDL_HAPTIC_DINPUT)
        set (HAPTIC_DRIVER windows)
    else ()
        message (STATUS "Building SDL without DX joystick support due to missing wbemcli.h")
        message (STATUS "For MSVC, get it from Windows 7 SDK. For MinGW, get it from eg. Wine sources or from MinGW-w64")
        add_definitions (-DSDL_JOYSTICK_WINMM)
        add_definitions (-DSDL_HAPTIC_DUMMY)
        set (HAPTIC_DRIVER dummy)
    endif ()
    file (GLOB SYS_C_FILES
        src/audio/directsound/*.c src/haptic/${HAPTIC_DRIVER}/*.c src/joystick/windows/*.c src/core/windows/*.c src/loadso/windows/*.c
        src/power/windows/*.c src/thread/windows/*.c src/thread/generic/SDL_syscond.c src/timer/windows/*.c src/video/windows/*.c src/joystick/dummy/*.c
        src/filesystem/windows/*.c
    )
elseif (IOS)
    file (GLOB SYS_C_FILES
        src/audio/coreaudio/*.c src/file/cocoa/*.m src/joystick/iphoneos/*.m src/loadso/dlopen/*.c src/power/uikit/*.m
        src/thread/pthread/*.c src/timer/unix/*.c src/video/uikit/*.m src/video/uikit/*.c src/haptic/dummy/*.c
        src/filesystem/cocoa/*.m
    )
elseif (APPLE)
    file (GLOB SYS_C_FILES
        src/audio/coreaudio/*.c src/file/cocoa/*.m src/haptic/darwin/*.c src/joystick/darwin/*.c src/loadso/dlopen/*.c
        src/power/macosx/*.c src/thread/pthread/*.c src/timer/unix/*.c src/video/cocoa/*.m src/filesystem/cocoa/*.m
    )
elseif (ANDROID)
    file (GLOB SYS_C_FILES
        src/audio/android/*.c src/core/android/*.c src/joystick/android/*.c src/loadso/dlopen/*.c src/power/android/*.c
        src/thread/pthread/*.c src/timer/unix/*.c src/video/android/*.c src/haptic/dummy/*.c src/filesystem/dummy/*.c
    )
else ()
    # On Linux, make sure development libraries exist, and use their include file directories
    if (RPI)
        file (GLOB VIDEO_DRIVER_C_FILES src/video/raspberry/*.c src/core/linux/*.c)
    else ()
        find_package (OpenGL REQUIRED)
        include_directories (${OpenGL_INCLUDE_DIRS})

        find_package (X11 REQUIRED)
        if (NOT X11_Xrandr_FOUND)
            message (FATAL_ERROR "Could not find XRandR (libxrandr-dev)")
        endif ()
        include_directories (${X11_INCLUDE_DIRS})

        include (CheckCSourceCompiles)
        set  (CMAKE_REQUIRED_LIBRARIES ${X11_LIB} ${X11_LIB})
        check_c_source_compiles ("
            #include <X11/Xlib.h>
            #include <X11/Xproto.h>
            #include <X11/extensions/Xext.h>
            #include <X11/extensions/extutil.h>
            extern XExtDisplayInfo* XextAddDisplay(XExtensionInfo* a,Display* b,_Xconst char* c,XExtensionHooks* d,int e,XPointer f);
            int main(int argc, char **argv) {}" HAVE_CONST_XEXT_ADDDISPLAY)
        if (HAVE_CONST_XEXT_ADDDISPLAY)
            add_definitions (-DSDL_VIDEO_DRIVER_X11_CONST_PARAM_XEXTADDDISPLAY)
        endif ()
        check_c_source_compiles ("
            #include <X11/Xlibint.h>
            extern int _XData32(Display *dpy,register _Xconst long *data,unsigned len);
            int main(int argc, char **argv) {}" HAVE_CONST_XDATA32)
        if (HAVE_CONST_XDATA32)
            add_definitions (-DSDL_VIDEO_DRIVER_X11_CONST_PARAM_XDATA32)
        endif ()
        set (CMAKE_REQUIRED_LIBRARIES)

        file (GLOB VIDEO_DRIVER_C_FILES src/video/x11/*.c)
    endif ()

    find_package (ALSA REQUIRED)
    # todo: remove this fix when the minimum CMake version has been raised to higher than 2.8.7
    # There is a bug in older version of FindALSA.cmake module where it erroneously include 'alsa' directory component into the variable
    # For cross-compiling build to work correctly, this extra directory component must be removed
    if (ALSA_INCLUDE_DIRS MATCHES .*/alsa)
        get_filename_component (ALSA_INCLUDE_DIRS ${ALSA_INCLUDE_DIRS} PATH)
    endif ()
    # end todo
    include_directories (${ALSA_INCLUDE_DIRS})

    find_package (PulseAudio)
    if (PA_FOUND)
      include_directories (${PA_INCLUDE_DIRS})
      get_filename_component (PA_SIMPLE ${PA_LIBRARIES} NAME)
      add_definitions (-DSDL_AUDIO_DRIVER_PULSEAUDIO=1 -DSDL_AUDIO_DRIVER_PULSEAUDIO_DYNAMIC="${PA_SIMPLE}")
      file (GLOB PULSEAUDIO_SOURCES src/audio/pulseaudio/*.c)
    endif ()

    file (GLOB SYS_C_FILES
        src/audio/alsa/*.c src/audio/dma/*.c src/audio/dsp/*.c src/haptic/linux/*.c src/joystick/linux/*.c src/loadso/dlopen/*.c
        src/power/linux/*.c src/thread/pthread/*.c src/timer/unix/*.c src/filesystem/unix/*.c
    )
    set (SYS_C_FILES ${SYS_C_FILES} ${VIDEO_DRIVER_C_FILES} ${PULSEAUDIO_SOURCES})
endif ()

file (GLOB H_FILES include/*.h)

# Define source files
set_source_files_properties (${C_FILES} PROPERTIES LANGUAGE C)
set_source_files_properties (${SYS_C_FILES} PROPERTIES LANGUAGE C)
set (SOURCE_FILES ${C_FILES} ${SYS_C_FILES} ${H_FILES})

# Define dependency libs
set (INCLUDE_DIRS include)

# Setup target
setup_library ()

# Install headers for building and using the Urho3D library (install dependency for D3D9GraphicsImpl.h, OGLGraphicsImpl.h, InputEvents.h, File.h, and Cursor.h)
install_header_files (DIRECTORY include/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/SDL FILES_MATCHING PATTERN *.h USE_FILE_SYMLINK)    # Note: the trailing slash is significant
# Install dependency for SDL_android_main.c
if (ANDROID)
    install_header_files (DIRECTORY src/main/android DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/SDL)
    install_header_files (FILES src/SDL_internal.h DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/SDL)
    install_header_files (DIRECTORY src/dynapi DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/SDL FILES_MATCHING PATTERN *.h)
endif ()
