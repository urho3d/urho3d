#
# Simple DirectMedia Layer
# Copyright (C) 1997-2016 Sam Lantinga <slouken@libsdl.org>
#
# This software is provided 'as-is', without any express or implied
# warranty.  In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
# claim that you wrote the original software. If you use this software
# in a product, an acknowledgment in the product documentation would be
# appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
# misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.
#

# Modified by Yao Wei Tjong for Urho3D, the modified portion is licensed under below license

# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Urho3D - replaced FindLibraryAndSONAME macro with get_soname macro
macro (get_soname SONAME LIB)
  if (${LIB})
    get_filename_component (REALPATH ${${LIB}} REALPATH)
    get_filename_component (BASENAME ${REALPATH} NAME)
    if (BASENAME MATCHES \\.so)  # Extract soname from basename
      string (REGEX REPLACE "(\\.so\\.[^.]+).*$" \\1 ${SONAME} "${BASENAME}")  # Stringify for string replacement
    else ()
      set (${SONAME} ${BASENAME})  # If it is not .so (e.g. .dylib) then use whatever the basename is
    endif ()
  endif ()
endmacro ()

macro(CheckDLOPEN)
  # Urho3D - bug fix - to be consistent with the rest of the check macros here, only do the check when the feature is actually wanted
  if (SDL_LOADSO)
    # Urho3D - bypass the checks for Emscripten as they don't work but assume it is supported (https://github.com/kripken/emscripten/wiki/Linking#dlopen-dynamic-linking)
    if (EMSCRIPTEN)
      set (HAVE_DLOPEN TRUE)
    else ()
      # Urho3D - bug fix - use different variables for different checks because of CMake caches the result variable
      check_function_exists(dlopen DLOPEN_FOUND)
      if(NOT DLOPEN_FOUND)
        foreach(_LIBNAME dl tdl)
          check_library_exists("${_LIBNAME}" "dlopen" "" DLOPEN_LIB_${_LIBNAME}_FOUND)
          if(DLOPEN_LIB_${_LIBNAME}_FOUND)
            list(APPEND EXTRA_LIBS ${_LIBNAME})
            set(_DLLIB ${_LIBNAME})
            set(DLOPEN_FOUND TRUE)
            break()
          endif()
        endforeach()
      endif()
      if(DLOPEN_FOUND)
        if(_DLLIB)
          set(CMAKE_REQUIRED_LIBRARIES ${_DLLIB})
        endif()
        check_c_source_compiles("
           #include <dlfcn.h>
           int main(int argc, char **argv) {
             void *handle = dlopen(\"\", RTLD_NOW);
             const char *loaderror = (char *) dlerror();
           }" HAVE_DLOPEN)
        set(CMAKE_REQUIRED_LIBRARIES)
      endif()
    endif ()
    if(HAVE_DLOPEN)
      set(SDL_LOADSO_DLOPEN 1)
      set(HAVE_SDL_DLOPEN TRUE)
      file(GLOB DLOPEN_SOURCES ${SDL2_SOURCE_DIR}/src/loadso/dlopen/*.c)
      set(SOURCE_FILES ${SOURCE_FILES} ${DLOPEN_SOURCES})
      set(HAVE_SDL_LOADSO TRUE)
    endif()
  endif ()
endmacro()

# Requires:
# - n/a
macro(CheckOSS)
  if(OSS)
    # Urho3D - bug fix - should use different variables for different checks, however, we replace the whole checks with find_package() approach for consistency sake
    find_package (OSS)
    if(OSS_FOUND)
      include_directories (SYSTEM ${OSS_INCLUDE_DIRS})
      if (OSS_LIBRARIES)
        get_filename_component(NAME_WE ${OSS_LIBRARIES} NAME_WE)
        string (REGEX REPLACE ^lib "" NAME_WE "${NAME_WE}")    # Stringify for string replacement
        list(APPEND EXTRA_LIBS ${NAME_WE})
      endif ()
      set(HAVE_OSS TRUE)
      file(GLOB OSS_SOURCES ${SDL2_SOURCE_DIR}/src/audio/dsp/*.c)
      if(OSS_USE_WORKAROUND_HEADER)
        set(SDL_AUDIO_DRIVER_OSS_SOUNDCARD_H 1)
      endif()
      set(SDL_AUDIO_DRIVER_OSS 1)
      set(SOURCE_FILES ${SOURCE_FILES} ${OSS_SOURCES})
      set(HAVE_SDL_AUDIO TRUE)
    endif()
  endif()
endmacro()

# Requires:
# - n/a
# Optional:
# - ALSA_SHARED opt
# - HAVE_DLOPEN opt
macro(CheckALSA)
  if(ALSA)
    # Urho3D - bug fix - use the more trusted FindALSA module as it has been tested to work for both native and cross-compiling build
    find_package (ALSA)
    # todo: remove this fix when the minimum CMake version has been raised to higher than 2.8.7
    # There is a bug in older version of FindALSA.cmake module where it erroneously include 'alsa' directory component into the variable
    # For cross-compiling build to work correctly, this extra directory component must be removed
    if (ALSA_INCLUDE_DIRS MATCHES .*/alsa)
      get_filename_component (ALSA_INCLUDE_DIRS ${ALSA_INCLUDE_DIRS} PATH)
    endif ()
    if(ALSA_FOUND)
      include_directories (SYSTEM ${ALSA_INCLUDE_DIRS})
      set(HAVE_ALSA TRUE)
      file(GLOB ALSA_SOURCES ${SDL2_SOURCE_DIR}/src/audio/alsa/*.c)
      set(SOURCE_FILES ${SOURCE_FILES} ${ALSA_SOURCES})
      set(SDL_AUDIO_DRIVER_ALSA 1)
      if(ALSA_SHARED)
        if(NOT HAVE_DLOPEN)
          message_warn("You must have SDL_LoadObject() support for dynamic ALSA loading")
        else()
          get_soname (ASOUND_LIB_SONAME ALSA_LIBRARIES)
          set(SDL_AUDIO_DRIVER_ALSA_DYNAMIC "\"${ASOUND_LIB_SONAME}\"")
          set(HAVE_ALSA_SHARED TRUE)
        endif()
      else()
        list(APPEND EXTRA_LIBS asound)
      endif()
      set(HAVE_SDL_AUDIO TRUE)
    endif()
  endif()
endmacro()

# Requires:
# - n/a
# Optional:
# - PULSEAUDIO_SHARED opt
# - HAVE_DLOPEN opt
macro(CheckPulseAudio)
  if(PULSEAUDIO)
    # Urho3D - bug fix - do not use pkg-config tool for detection as it only works for host environment and not for rooted environment when cross-compiling
    find_package (PulseAudio)
    if(PULSEAUDIO_FOUND)
      include_directories (SYSTEM ${PULSEAUDIO_INCLUDE_DIRS})
      set(HAVE_PULSEAUDIO TRUE)
      file(GLOB PULSEAUDIO_SOURCES ${SDL2_SOURCE_DIR}/src/audio/pulseaudio/*.c)
      set(SOURCE_FILES ${SOURCE_FILES} ${PULSEAUDIO_SOURCES})
      set(SDL_AUDIO_DRIVER_PULSEAUDIO 1)
      # Urho3D - commented out appending EXTRA_CFLAGS for compiling with PulseAudio, there should not be any except "-D_REENTRANT" which is also redundant for our configuration setup as we use '-pthread' compiler flags to do the right things automatically
      if(PULSEAUDIO_SHARED)
        if(NOT HAVE_DLOPEN)
          message_warn("You must have SDL_LoadObject() support for dynamic PulseAudio loading")
        else()
          get_soname (PULSE_SIMPLE_LIB_SONAME PULSEAUDIO_LIBRARIES)
          set(SDL_AUDIO_DRIVER_PULSEAUDIO_DYNAMIC "\"${PULSE_SIMPLE_LIB_SONAME}\"")
          set(HAVE_PULSEAUDIO_SHARED TRUE)
        endif()
      else()
        list (APPEND EXTRA_LIBS pulse-simple pulse)
      endif()
      set(HAVE_SDL_AUDIO TRUE)
    endif()
  endif()
endmacro()

# Requires:
# - n/a
# Optional:
# - JACK_SHARED opt
# - HAVE_DLOPEN opt
macro(CheckJACK)
  if(JACK)
    # Urho3D - bug fix - do not use pkg-config tool for detection as it only works for host environment and not for rooted environment when cross-compiling
    find_package (Jack)
    if(JACK_FOUND)
      include_directories (SYSTEM ${JACK_INCLUDE_DIRS})
      set(HAVE_JACK TRUE)
      file(GLOB JACK_SOURCES ${SDL2_SOURCE_DIR}/src/audio/jack/*.c)
      set(SOURCE_FILES ${SOURCE_FILES} ${JACK_SOURCES})
      set(SDL_AUDIO_DRIVER_JACK 1)
      if(JACK_SHARED)
        if(NOT HAVE_DLOPEN)
          message_warn("You must have SDL_LoadObject() support for dynamic JACK audio loading")
        else()
          get_soname (JACK_LIB_SONAME JACK_LIBRARIES)
          set(SDL_AUDIO_DRIVER_JACK_DYNAMIC "\"${JACK_LIB_SONAME}\"")
          set(HAVE_JACK_SHARED TRUE)
        endif()
      else()
        list (APPEND EXTRA_LIBS jack)
      endif()
      set(HAVE_SDL_AUDIO TRUE)
    endif()
  endif()
endmacro()

# Requires:
# - PkgCheckModules
# Optional:
# - ESD_SHARED opt
# - HAVE_DLOPEN opt
macro(CheckESD)
  if(ESD)
    # Urho3D - bug fix - do not use pkg-config tool for detection as it only works for host environment and not for rooted environment when cross-compiling
    find_package (Esound)
    if(ESOUND_FOUND)
      include_directories (SYSTEM ${ESOUND_INCLUDE_DIRS})
      set(HAVE_ESD TRUE)
      file(GLOB ESD_SOURCES ${SDL2_SOURCE_DIR}/src/audio/esd/*.c)
      set(SOURCE_FILES ${SOURCE_FILES} ${ESD_SOURCES})
      set(SDL_AUDIO_DRIVER_ESD 1)
      if(ESD_SHARED)
        if(NOT HAVE_DLOPEN)
          message_warn("You must have SDL_LoadObject() support for dynamic ESD loading")
        else()
          get_soname (ESD_LIB_SONAME ESOUND_LIBRARIES)
          set(SDL_AUDIO_DRIVER_ESD_DYNAMIC "\"${ESD_LIB_SONAME}\"")
          set(HAVE_ESD_SHARED TRUE)
        endif()
      else()
        list (APPEND EXTRA_LIBS esd)
      endif()
      set(HAVE_SDL_AUDIO TRUE)
    endif()
  endif()
endmacro()

# Requires:
# - n/a
# Optional:
# - ARTS_SHARED opt
# - HAVE_DLOPEN opt
macro(CheckARTS)
  if(ARTS)
    # Urho3D - bug fix - do not use (host) arts-config tool for detection as it only works for host environment and not for rooted environment when cross-compiling
    find_package (aRts)
    if(ARTS_FOUND)
      include_directories (SYSTEM ${ARTS_INCLUDE_DIRS})
      file(GLOB ARTS_SOURCES ${SDL2_SOURCE_DIR}/src/audio/arts/*.c)
      set(SOURCE_FILES ${SOURCE_FILES} ${ARTS_SOURCES})
      set(SDL_AUDIO_DRIVER_ARTS 1)
      set(HAVE_ARTS TRUE)
      if(ARTS_SHARED)
        if(NOT HAVE_DLOPEN)
          message_warn("You must have SDL_LoadObject() support for dynamic ARTS loading")
        else()
          get_soname (ARTSC_LIB_SONAME ARTS_LIBRARIES)
          set(SDL_AUDIO_DRIVER_ARTS_DYNAMIC "\"${ARTSC_LIB_SONAME}\"")
          set(HAVE_ARTS_SHARED TRUE)
        endif()
      else()
        list (APPEND EXTRA_LIBS artsc)
      endif()
      set(HAVE_SDL_AUDIO TRUE)
    endif()
  endif()
endmacro()

# Requires:
# - n/a
# Optional:
# - NAS_SHARED opt
# - HAVE_DLOPEN opt
macro(CheckNAS)
  if(NAS)
    # Urho3D - bug fix - do not use check_include_file() for detection as it only works for host environment and not for rooted environment when cross-compiling
    find_package (NAS)
    if(NAS_FOUND)
      include_directories (SYSTEM ${NAS_INCLUDE_DIRS})
      set(HAVE_NAS TRUE)
      file(GLOB NAS_SOURCES ${SDL2_SOURCE_DIR}/src/audio/nas/*.c)
      set(SOURCE_FILES ${SOURCE_FILES} ${NAS_SOURCES})
      set(SDL_AUDIO_DRIVER_NAS 1)
      if(NAS_SHARED)
        if(NOT HAVE_DLOPEN)
          message_warn("You must have SDL_LoadObject() support for dynamic NAS loading")
        else()
          get_soname (AUDIO_LIB_SONAME NAS_LIBRARIES)
          set(SDL_AUDIO_DRIVER_NAS_DYNAMIC "\"${AUDIO_LIB_SONAME}\"")
          set(HAVE_NAS_SHARED TRUE)
        endif()
      else()
        list (APPEND EXTRA_LIBS audio)
      endif()
      set(HAVE_SDL_AUDIO TRUE)
    endif()
  endif()
endmacro()

# Requires:
# - n/a
# Optional:
# - SNDIO_SHARED opt
# - HAVE_DLOPEN opt
macro(CheckSNDIO)
  if(SNDIO)
    # Urho3D - bug fix - do not use check_include_file() for detection as it only works for host environment and not for rooted environment when cross-compiling
    find_package (SNDIO)
    if(SNDIO_FOUND)
      include_directories (SYSTEM ${SNDIO_INCLUDE_DIRS})
      set(HAVE_SNDIO TRUE)
      file(GLOB SNDIO_SOURCES ${SDL2_SOURCE_DIR}/src/audio/sndio/*.c)
      set(SOURCE_FILES ${SOURCE_FILES} ${SNDIO_SOURCES})
      set(SDL_AUDIO_DRIVER_SNDIO 1)
      if(SNDIO_SHARED)
        if(NOT HAVE_DLOPEN)
          message_warn("You must have SDL_LoadObject() support for dynamic sndio loading")
        else()
          get_soname (SNDIO_LIB_SONAME SNDIO_LIBRARIES)
          set(SDL_AUDIO_DRIVER_SNDIO_DYNAMIC "\"${SNDIO_LIB_SONAME}\"")
          set(HAVE_SNDIO_SHARED TRUE)
        endif()
      else()
        list(APPEND EXTRA_LIBS sndio)
      endif()
      set(HAVE_SDL_AUDIO TRUE)
    endif()
  endif()
endmacro()

# Requires:
# - n/a
# Optional:
# - FUSIONSOUND_SHARED opt
# - HAVE_DLOPEN opt
macro(CheckFusionSound)
  if(FUSIONSOUND)
    # Urho3D - bug fix - do not use pkg-config tool for detection as it only works for host environment and not for rooted environment when cross-compiling
    find_package (FusionSound 1.0.0)
    if(FUSIONSOUND_FOUND)
      include_directories (SYSTEM ${FUSIONSOUND_INCLUDE_DIRS})
      set(HAVE_FUSIONSOUND TRUE)
      file(GLOB FUSIONSOUND_SOURCES ${SDL2_SOURCE_DIR}/src/audio/fusionsound/*.c)
      set(SOURCE_FILES ${SOURCE_FILES} ${FUSIONSOUND_SOURCES})
      set(SDL_AUDIO_DRIVER_FUSIONSOUND 1)
      if(FUSIONSOUND_SHARED)
        if(NOT HAVE_DLOPEN)
          message_warn("You must have SDL_LoadObject() support for dynamic FusionSound loading")
        else()
          get_soname (FUSIONSOUND_LIB_SONAME FUSIONSOUND_LIBRARIES)
          set(SDL_AUDIO_DRIVER_FUSIONSOUND_DYNAMIC "\"${FUSIONSOUND_LIB_SONAME}\"")
          set(HAVE_FUSIONSOUND_SHARED TRUE)
        endif()
      else()
        list (APPEND EXTRA_LIBS fusionsound)
      endif()
      set(HAVE_SDL_AUDIO TRUE)
    endif()
  endif()
endmacro()

# Requires:
# - LIBSAMPLERATE
# Optional:
# - LIBSAMPLERATE_SHARED opt
# - HAVE_DLOPEN opt
macro(CheckLibSampleRate)
  if(LIBSAMPLERATE)
    # Urho3D - use custom CMake module to find the audio driver like the rest for consistency sake
    find_package (SecretRabbitCode)
    if(SECRETRABBITCODE_FOUND)
      include_directories (SYSTEM ${SECRETRABBITCODE_INCLUDE_DIRS})
      set (HAVE_LIBSAMPLERATE_H TRUE)
      if(LIBSAMPLERATE_SHARED)
        if(NOT HAVE_DLOPEN)
          message_warn("You must have SDL_LoadObject() support for dynamic libsamplerate loading")
        else()
          get_soname (SAMPLERATE_LIB_SONAME SECRETRABBITCODE_LIBRARIES)
          set(SDL_LIBSAMPLERATE_DYNAMIC "\"${SAMPLERATE_LIB_SONAME}\"")
          set(HAVE_LIBSAMPLERATE_SHARED TRUE)
        endif()
      else()
        list (APPEND EXTRA_LIBS samplerate)
      endif()
    endif()
  endif()
endmacro()

# Requires:
# - n/a
# Optional:
# - X11_SHARED opt
# - HAVE_DLOPEN opt
macro(CheckX11)
  if(VIDEO_X11)
    # Urho3D - bug fix - in order to make these checks below work on both native and cross-compiling builds we need to add the '-shared' compiler flags to ensure the linker does not attempt to statically link against X11 shared libs which would otherwise fail the test when in cross-compiling mode
    set(CMAKE_REQUIRED_FLAGS "-fPIC -shared ${ORIG_CMAKE_REQUIRED_FLAGS}")
    foreach (NAME X11 Xext Xcursor Xinerama Xi Xrandr Xrender Xss Xxf86vm)
      string (TOUPPER ${NAME} UPCASE_NAME)
      string (REGEX REPLACE \\..+$ "" UPCASE_NAME "${UPCASE_NAME}")  # Stringify for string replacement
      find_library (${UPCASE_NAME}_LIB ${NAME})
      get_soname (${UPCASE_NAME}_LIB_SONAME ${UPCASE_NAME}_LIB)
    endforeach ()

    # Urho3D - commented out setting of EXTRA_CFLAGS based on the search result for X11/Xlib.h using the default search path (if it is found then it is in default path anyway so no point to add it into compiler header search path again)
    # Urho3D - add check for Xdbe extension

    check_include_file(X11/Xcursor/Xcursor.h HAVE_XCURSOR_H)
    check_include_file(X11/extensions/Xinerama.h HAVE_XINERAMA_H)
    check_include_file(X11/extensions/XInput2.h HAVE_XINPUT_H)
    check_include_file(X11/extensions/Xrandr.h HAVE_XRANDR_H)
    check_include_file(X11/extensions/Xrender.h HAVE_XRENDER_H)
    check_include_file(X11/extensions/shape.h HAVE_XSHAPE_H)
    check_include_file(X11/extensions/scrnsaver.h HAVE_XSS_H)
    check_include_files("X11/Xlib.h;X11/Xproto.h;X11/extensions/Xdbe.h" HAVE_XDBE_H)
    check_include_files("X11/Xlib.h;X11/Xproto.h;X11/extensions/Xext.h" HAVE_XEXT_H)
    check_include_files("X11/Xlib.h;X11/extensions/xf86vmode.h" HAVE_XF86VM_H)

    if(X11_LIB)
      if(NOT HAVE_XEXT_H)
        message_error("Missing Xext.h, maybe you need to install the libxext-dev package?")
      endif()

      if (HAVE_XDBE_H)
        set(SDL_VIDEO_DRIVER_X11_XDBE 1)
      endif ()

      set(HAVE_VIDEO_X11 TRUE)
      set(HAVE_SDL_VIDEO TRUE)

      file(GLOB X11_SOURCES ${SDL2_SOURCE_DIR}/src/video/x11/*.c)
      set(SOURCE_FILES ${SOURCE_FILES} ${X11_SOURCES})
      set(SDL_VIDEO_DRIVER_X11 1)

      if(APPLE)
        set(X11_SHARED OFF)
      endif()

      check_function_exists("shmat" HAVE_SHMAT)
      if(NOT HAVE_SHMAT)
        # Urho3D - bug fix - use different variables for different checks because of CMake caches the result variable
        check_library_exists(ipc shmat "" HAVE_SHMAT_IN_IPC)
        if(HAVE_SHMAT_IN_IPC)
          list(APPEND EXTRA_LIBS ipc)
          set (HAVE_SHMAT TRUE)
        endif()
        if(NOT HAVE_SHMAT)
          add_definitions(-DNO_SHARED_MEMORY)
          list(APPEND EXTRA_CFLAGS "-DNO_SHARED_MEMORY")
        endif()
      endif()

      if(X11_SHARED)
        if(NOT HAVE_DLOPEN)
          message_warn("You must have SDL_LoadObject() support for dynamic X11 loading")
          set(HAVE_X11_SHARED FALSE)
        else()
          set(HAVE_X11_SHARED TRUE)
        endif()
        if(HAVE_X11_SHARED)
          set(SDL_VIDEO_DRIVER_X11_DYNAMIC "\"${X11_LIB_SONAME}\"")
          set(SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT "\"${XEXT_LIB_SONAME}\"")
        else()
          # Urho3D - bug fix - the EXTRA_LIBS is list of library names (not the fully-qualified path to the library itself)
          list (APPEND EXTRA_LIBS X11 Xext)
        endif()
      endif()

      set(CMAKE_REQUIRED_LIBRARIES ${X11_LIB} ${X11_LIB})
      check_c_source_compiles("
          #include <X11/Xlib.h>
          #include <X11/Xproto.h>
          #include <X11/extensions/Xext.h>
          #include <X11/extensions/extutil.h>
          extern XExtDisplayInfo* XextAddDisplay(XExtensionInfo* a,Display* b,_Xconst char* c,XExtensionHooks* d,int e,XPointer f);
          int main(int argc, char **argv) {}" HAVE_CONST_XEXT_ADDDISPLAY)
      if(HAVE_CONST_XEXT_ADDDISPLAY)
        set(SDL_VIDEO_DRIVER_X11_CONST_PARAM_XEXTADDDISPLAY 1)
      endif()

      check_c_source_compiles("
          #include <X11/Xlib.h>
          int main(int argc, char **argv) {
            Display *display;
            XEvent event;
            XGenericEventCookie *cookie = &event.xcookie;
            XNextEvent(display, &event);
            XGetEventData(display, cookie);
            XFreeEventData(display, cookie); }" HAVE_XGENERICEVENT)
      if(HAVE_XGENERICEVENT)
        set(SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS 1)
      endif()

      check_function_exists(XkbKeycodeToKeysym SDL_VIDEO_DRIVER_X11_HAS_XKBKEYCODETOKEYSYM)

      if(VIDEO_X11_XCURSOR AND HAVE_XCURSOR_H)
        set(HAVE_VIDEO_X11_XCURSOR TRUE)
        if(HAVE_X11_SHARED AND XCURSOR_LIB)
          set(SDL_VIDEO_DRIVER_X11_DYNAMIC_XCURSOR "\"${XCURSOR_LIB_SONAME}\"")
        else()
          list (APPEND EXTRA_LIBS Xcursor)
        endif()
        set(SDL_VIDEO_DRIVER_X11_XCURSOR 1)
      endif()

      if(VIDEO_X11_XINERAMA AND HAVE_XINERAMA_H)
        set(HAVE_VIDEO_X11_XINERAMA TRUE)
        if(HAVE_X11_SHARED AND XINERAMA_LIB)
          set(SDL_VIDEO_DRIVER_X11_DYNAMIC_XINERAMA "\"${XINERAMA_LIB_SONAME}\"")
        else()
          list (APPEND EXTRA_LIBS Xinerama)
        endif()
        set(SDL_VIDEO_DRIVER_X11_XINERAMA 1)
      endif()

      if(VIDEO_X11_XINPUT AND HAVE_XINPUT_H)
        set(HAVE_VIDEO_X11_XINPUT TRUE)
        if(HAVE_X11_SHARED AND XI_LIB)
          set(SDL_VIDEO_DRIVER_X11_DYNAMIC_XINPUT2 "\"${XI_LIB_SONAME}\"")
        else()
          list (APPEND EXTRA_LIBS Xi)
        endif()
        set(SDL_VIDEO_DRIVER_X11_XINPUT2 1)

        # Check for multitouch
        check_c_source_compiles("
            #include <X11/Xlib.h>
            #include <X11/Xproto.h>
            #include <X11/extensions/XInput2.h>
            int event_type = XI_TouchBegin;
            XITouchClassInfo *t;
            Status XIAllowTouchEvents(Display *a,int b,unsigned int c,Window d,int f)
            {
              return (Status)0;
            }
            int main(int argc, char **argv) {}" HAVE_XINPUT2_MULTITOUCH)
        if(HAVE_XINPUT2_MULTITOUCH)
          set(SDL_VIDEO_DRIVER_X11_XINPUT2_SUPPORTS_MULTITOUCH 1)
        endif()
      endif()

      if(VIDEO_X11_XRANDR AND HAVE_XRANDR_H)
        if(HAVE_X11_SHARED AND XRANDR_LIB)
          set(SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR "\"${XRANDR_LIB_SONAME}\"")
        else()
          list (APPEND EXTRA_LIBS Xrandr)
        endif()
        set(SDL_VIDEO_DRIVER_X11_XRANDR 1)
        set(HAVE_VIDEO_X11_XRANDR TRUE)
      endif()

      if(VIDEO_X11_XSCRNSAVER AND HAVE_XSS_H)
        if(HAVE_X11_SHARED AND XSS_LIB)
          set(SDL_VIDEO_DRIVER_X11_DYNAMIC_XSS "\"${XSS_LIB_SONAME}\"")
        else()
          list (APPEND EXTRA_LIBS Xss)
        endif()
        set(SDL_VIDEO_DRIVER_X11_XSCRNSAVER 1)
        set(HAVE_VIDEO_X11_XSCRNSAVER TRUE)
      endif()

      if(VIDEO_X11_XSHAPE AND HAVE_XSHAPE_H)
        set(SDL_VIDEO_DRIVER_X11_XSHAPE 1)
        set(HAVE_VIDEO_X11_XSHAPE TRUE)
      endif()

      if(VIDEO_X11_XVM AND HAVE_XF86VM_H)
        if(HAVE_X11_SHARED AND XXF86VM_LIB)
          set(SDL_VIDEO_DRIVER_X11_DYNAMIC_XVIDMODE "\"${XXF86VM_LIB_SONAME}\"")
        else()
          list (APPEND EXTRA_LIBS Xxf86vm)
        endif()
        set(SDL_VIDEO_DRIVER_X11_XVIDMODE 1)
        set(HAVE_VIDEO_X11_XVM TRUE)
      endif()

      set(CMAKE_REQUIRED_LIBRARIES)
      set(CMAKE_REQUIRED_FLAGS ${ORIG_CMAKE_REQUIRED_FLAGS})
    endif()
  endif()
endmacro()

macro(WaylandProtocolGen _SCANNER _XML _PROTL)
    set(_WAYLAND_PROT_C_CODE "${CMAKE_CURRENT_BINARY_DIR}/wayland-generated-protocols/${_PROTL}-protocol.c")
    set(_WAYLAND_PROT_H_CODE "${CMAKE_CURRENT_BINARY_DIR}/wayland-generated-protocols/${_PROTL}-client-protocol.h")

    add_custom_command(
        OUTPUT "${_WAYLAND_PROT_H_CODE}"
        DEPENDS "${_XML}"
        COMMAND "${_SCANNER}"
        ARGS client-header "${_XML}" "${_WAYLAND_PROT_H_CODE}"
    )

    add_custom_command(
        OUTPUT "${_WAYLAND_PROT_C_CODE}"
        DEPENDS "${_WAYLAND_PROT_H_CODE}"
        COMMAND "${_SCANNER}"
        ARGS code "${_XML}" "${_WAYLAND_PROT_C_CODE}"
    )

    set(SOURCE_FILES ${SOURCE_FILES} "${_WAYLAND_PROT_C_CODE}")
endmacro()

# Requires:
# - EGL
# Optional:
# - WAYLAND_SHARED opt
# - HAVE_DLOPEN opt
macro(CheckWayland)
  if(VIDEO_WAYLAND)
    # Urho3D - bug fix - do not use pkg-config tool for detection as it only works for host environment and not for rooted environment when cross-compiling
    find_package (Wayland)
    if(WAYLAND_FOUND)
      include_directories (SYSTEM ${WAYLAND_INCLUDE_DIRS})
      set(HAVE_VIDEO_WAYLAND TRUE)
      set(HAVE_SDL_VIDEO TRUE)

      file(GLOB WAYLAND_SOURCES ${SDL2_SOURCE_DIR}/src/video/wayland/*.c)
      set(SOURCE_FILES ${SOURCE_FILES} ${WAYLAND_SOURCES})

      # We have to generate some protocol interface code for some unstable Wayland features.
      file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/wayland-generated-protocols")
      include_directories("${CMAKE_CURRENT_BINARY_DIR}/wayland-generated-protocols")

      file(GLOB WAYLAND_PROTOCOLS_XML RELATIVE "${SDL2_SOURCE_DIR}/wayland-protocols/" "${SDL2_SOURCE_DIR}/wayland-protocols/*.xml")
      foreach(_XML ${WAYLAND_PROTOCOLS_XML})
        string(REGEX REPLACE "\\.xml$" "" _PROTL "${_XML}")
        WaylandProtocolGen("${WAYLAND_SCANNER}" "${SDL2_SOURCE_DIR}/wayland-protocols/${_XML}" "${_PROTL}")
      endforeach()

      if(VIDEO_WAYLAND_QT_TOUCH)
          set(SDL_VIDEO_DRIVER_WAYLAND_QT_TOUCH 1)
      endif()

      if(WAYLAND_SHARED)
        if(NOT HAVE_DLOPEN)
          message_warn("You must have SDL_LoadObject() support for dynamic Wayland loading")
        else()
          get_soname (WAYLAND_CLIENT_LIB_SONAME WAYLAND_CLIENT)
          get_soname (WAYLAND_EGL_LIB_SONAME WAYLAND_EGL)
          get_soname (WAYLAND_CURSOR_LIB_SONAME WAYLAND_CURSOR)
          get_soname (XKBCOMMON_LIB_SONAME XKB)
          set(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC "\"${WAYLAND_CLIENT_LIB_SONAME}\"")
          set(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_EGL "\"${WAYLAND_EGL_LIB_SONAME}\"")
          set(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_CURSOR "\"${WAYLAND_CURSOR_LIB_SONAME}\"")
          set(SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_XKBCOMMON "\"${XKBCOMMON_LIB_SONAME}\"")
          set(HAVE_WAYLAND_SHARED TRUE)
        endif()
      else()
        list (APPEND EXTRA_LIBS wayland-client)
      endif()

      set(SDL_VIDEO_DRIVER_WAYLAND 1)
      set(SDL_VIDEO_OPENGL_EGL 1)
    endif()
  endif()
endmacro()

# Urho3D - commented out CheckCOCOA macro as it does not perform any check at all, moved the code to SDL's CMakeLists.txt

# Requires:
# - n/a
# Optional:
# - DIRECTFB_SHARED opt
# - HAVE_DLOPEN opt
macro(CheckDirectFB)
  if(VIDEO_DIRECTFB)
    # Urho3D - bug fix - do not use pkg-config tool for detection as it only works for host environment and not for rooted environment when cross-compiling
    find_package (DirectFB 1.0.0)
    if(DIRECTFB_FOUND)
      include_directories (SYSTEM ${DIRECTFB_INCLUDE_DIRS})
      set(HAVE_VIDEO_DIRECTFB TRUE)
      file(GLOB DIRECTFB_SOURCES ${SDL2_SOURCE_DIR}/src/video/directfb/*.c)
      set(SOURCE_FILES ${SOURCE_FILES} ${DIRECTFB_SOURCES})
      set(SDL_VIDEO_DRIVER_DIRECTFB 1)
      set(SDL_VIDEO_RENDER_DIRECTFB 1)
      if(DIRECTFB_SHARED)
        if(NOT HAVE_DLOPEN)
          message_warn("You must have SDL_LoadObject() support for dynamic DirectFB loading")
        else()
          get_soname (DIRECTFB_LIB_SONAME DIRECTFB_LIBRARIES)
          set(SDL_VIDEO_DRIVER_DIRECTFB_DYNAMIC "\"${DIRECTFB_LIB_SONAME}\"")
          set(HAVE_DIRECTFB_SHARED TRUE)
        endif()
      else()
        list(APPEND EXTRA_LIBS directfb)
      endif()
      set(HAVE_SDL_VIDEO TRUE)
    endif()
  endif()
endmacro()

# Requires:
# - n/a
macro(CheckVivante)
  if(VIDEO_VIVANTE)
    # Urho3D - bug fix - when cross-compiling the headers are rooted, either use "--sysroot" compiler flag or use CMAKE_REQUIRED_INCLUDES (e.g. on RPI) to cater for it
    set (CMAKE_REQUIRED_INCLUDES_VIVANTE_SAVED ${CMAKE_REQUIRED_INCLUDES})
    if (CMAKE_CROSSCOMPILING AND NOT "${CMAKE_C_FLAGS} ${CMAKE_REQUIRED_FLAGS}" MATCHES --sysroot)
      find_path (VIVANTE_INCLUDE_DIRS NAMES gc_vdk.h EGL/eglvivante.h)
      if (VIVANTE_INCLUDE_DIRS)
        # Assume the header search path has not been adjusted elsewhere yet, there is no harm anyway when a same entry is added twice into the list
        list (APPEND CMAKE_REQUIRED_INCLUDES ${VIVANTE_INCLUDE_DIRS})
      endif ()
    endif ()
    check_c_source_compiles("
        #include <gc_vdk.h>
        int main(int argc, char** argv) {}" HAVE_VIDEO_VIVANTE_VDK)
    check_c_source_compiles("
        #define LINUX
        #define EGL_API_FB
        #include <EGL/eglvivante.h>
        int main(int argc, char** argv) {}" HAVE_VIDEO_VIVANTE_EGL_FB)
    if(HAVE_VIDEO_VIVANTE_VDK OR HAVE_VIDEO_VIVANTE_EGL_FB)
      set(HAVE_VIDEO_VIVANTE TRUE)
      set(HAVE_SDL_VIDEO TRUE)

      file(GLOB VIVANTE_SOURCES ${SDL2_SOURCE_DIR}/src/video/vivante/*.c)
      set(SOURCE_FILES ${SOURCE_FILES} ${VIVANTE_SOURCES})
      set(SDL_VIDEO_DRIVER_VIVANTE 1)
      if(HAVE_VIDEO_VIVANTE_VDK)
        set(SDL_VIDEO_DRIVER_VIVANTE_VDK 1)
        list(APPEND EXTRA_LIBS VDK VIVANTE)
      else()
        set(SDL_CFLAGS "${SDL_CFLAGS} -DLINUX -DEGL_API_FB")
        list(APPEND EXTRA_LIBS EGL)
      endif(HAVE_VIDEO_VIVANTE_VDK)
    endif(HAVE_VIDEO_VIVANTE_VDK OR HAVE_VIDEO_VIVANTE_EGL_FB)
    set (CMAKE_REQUIRED_INCLUDES ${CMAKE_REQUIRED_INCLUDES_VIVANTE_SAVED})
  endif(VIDEO_VIVANTE)
endmacro(CheckVivante)

# Requires:
# - nada
# Urho3D - rename the macro to be generic OpenGL check and make it also work for OSX platform
macro(CheckOpenGL)
  if(VIDEO_OPENGL)
    if (APPLE)
      check_c_source_compiles ("
        #include <OpenGL/OpenGL.h>
        #include <OpenGL/CGLRenderers.h>
        int main(int argc, char** argv) {}" HAVE_VIDEO_OPENGL)
    else ()
      check_c_source_compiles("
        #include <GL/gl.h>
        #include <GL/glx.h>
        int main(int argc, char** argv) {}" HAVE_VIDEO_OPENGL)
    endif ()

    if(HAVE_VIDEO_OPENGL)
      set(HAVE_VIDEO_OPENGL TRUE)
      set(SDL_VIDEO_OPENGL 1)
      if (APPLE)
        set (SDL_VIDEO_OPENGL_CGL 1)
      else ()
        set(SDL_VIDEO_OPENGL_GLX 1)
      endif ()
      set(SDL_VIDEO_RENDER_OGL 1)
    endif()
  endif()
endmacro()

# Requires:
# - nada
# Urho3D - rename the macro to be generic OpenGLES check and make it also work for iOS/tvOS platform
macro(CheckOpenGLES)
  if(VIDEO_OPENGLES)
    check_c_source_compiles("
        #define EGL_API_FB
        #include <EGL/egl.h>
        int main (int argc, char** argv) {}" HAVE_VIDEO_OPENGL_EGL)
    if(HAVE_VIDEO_OPENGL_EGL)
        set(SDL_VIDEO_OPENGL_EGL 1)
    endif()
    check_c_source_compiles("
      #include <GLES/gl.h>
      #include <GLES/glext.h>
      int main (int argc, char** argv) {}" HAVE_VIDEO_OPENGLES_V1)
    if(HAVE_VIDEO_OPENGLES_V1)
        set(HAVE_VIDEO_OPENGLES TRUE)
        set(SDL_VIDEO_OPENGL_ES 1)
        set(SDL_VIDEO_RENDER_OGL_ES 1)
    endif()
    check_c_source_compiles("
      #include <GLES2/gl2.h>
      #include <GLES2/gl2ext.h>
      int main (int argc, char** argv) {}" HAVE_VIDEO_OPENGLES_V2)
    if(HAVE_VIDEO_OPENGLES_V2)
        set(HAVE_VIDEO_OPENGLES TRUE)
        set(SDL_VIDEO_OPENGL_ES2 1)
        set(SDL_VIDEO_RENDER_OGL_ES2 1)
    endif()
  endif()
endmacro()

# Requires:
# - nada
# Optional:
# - THREADS opt
macro(CheckPTHREAD)
  if(PTHREADS)
    # Urho3D - remove hardcoding of pthread-related compiler and linker flags for each platform
    set(CMAKE_REQUIRED_FLAGS "-pthread ${ORIG_CMAKE_REQUIRED_FLAGS}")   # Android does not need this flag but it does no harm (i.e. appears to be no-op on Android)
    if(CMAKE_CROSSCOMPILING)
      check_c_source_compiles("
        #include <pthread.h>
        int main(int argc, char** argv) {
          pthread_attr_t type;
          pthread_attr_init(&type);
          return 0;
        }" HAVE_PTHREADS)
    else()
      check_c_source_runs("
        #include <pthread.h>
        int main(int argc, char** argv) {
          pthread_attr_t type;
          pthread_attr_init(&type);
          return 0;
        }" HAVE_PTHREADS)
    endif()
    if(HAVE_PTHREADS)
      set(SDL_THREAD_PTHREAD 1)
      # Urho3D - we configure to use "-pthread" compiler flags globally and expect the respective compiler toolchain to do the right things automatically
      set(SDL_CFLAGS "${SDL_CFLAGS} -pthread")

      check_c_source_compiles("
        #include <pthread.h>
        int main(int argc, char **argv) {
          pthread_mutexattr_t attr;
          pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
          return 0;
        }" HAVE_RECURSIVE_MUTEXES)
      if(HAVE_RECURSIVE_MUTEXES)
        set(SDL_THREAD_PTHREAD_RECURSIVE_MUTEX 1)
      else()
        check_c_source_compiles("
            #include <pthread.h>
            int main(int argc, char **argv) {
              pthread_mutexattr_t attr;
              pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
              return 0;
            }" HAVE_RECURSIVE_MUTEXES_NP)
        if(HAVE_RECURSIVE_MUTEXES_NP)
          set(SDL_THREAD_PTHREAD_RECURSIVE_MUTEX_NP 1)
        endif()
      endif()

      if(PTHREADS_SEM)
        check_c_source_compiles("#include <pthread.h>
                                 #include <semaphore.h>
                                 int main(int argc, char **argv) { return 0; }" HAVE_PTHREADS_SEM)
        if(HAVE_PTHREADS_SEM)
          check_c_source_compiles("
              #include <pthread.h>
              #include <semaphore.h>
              int main(int argc, char **argv) {
                  sem_timedwait(NULL, NULL);
                  return 0;
              }" HAVE_SEM_TIMEDWAIT)
        endif()
      endif()

      check_c_source_compiles("
          #include <pthread.h>
          #include <pthread_np.h>
          int main(int argc, char** argv) { return 0; }" HAVE_PTHREAD_NP_H)
      check_function_exists(pthread_setname_np HAVE_PTHREAD_SETNAME_NP)
      check_function_exists(pthread_set_name_np HAVE_PTHREAD_SET_NAME_NP)

      set(SOURCE_FILES ${SOURCE_FILES}
          ${SDL2_SOURCE_DIR}/src/thread/pthread/SDL_systhread.c
          ${SDL2_SOURCE_DIR}/src/thread/pthread/SDL_sysmutex.c   # Can be faked, if necessary
          ${SDL2_SOURCE_DIR}/src/thread/pthread/SDL_syscond.c    # Can be faked, if necessary
          ${SDL2_SOURCE_DIR}/src/thread/pthread/SDL_systls.c
          )
      if(HAVE_PTHREADS_SEM)
        set(SOURCE_FILES ${SOURCE_FILES}
            ${SDL2_SOURCE_DIR}/src/thread/pthread/SDL_syssem.c)
      else()
        set(SOURCE_FILES ${SOURCE_FILES}
            ${SDL2_SOURCE_DIR}/src/thread/generic/SDL_syssem.c)
      endif()
      set(HAVE_SDL_THREADS TRUE)
    endif()
    set(CMAKE_REQUIRED_FLAGS ${ORIG_CMAKE_REQUIRED_FLAGS})
  endif()
endmacro()

# Requires
# - nada
# Optional:
# Sets:
# USB_LIBS
# USB_CFLAGS
macro(CheckUSBHID)
  # Urho3D - no fix required - all these checks appear to be for BSD only, assume only native build
  #          Cannot fix them for X-compiling anyway as we/I don't have the necessary means to verify the changes
  check_library_exists(usbhid hid_init "" LIBUSBHID)
  if(LIBUSBHID)
    check_include_file(usbhid.h HAVE_USBHID_H)
    if(HAVE_USBHID_H)
      set(USB_CFLAGS "-DHAVE_USBHID_H")
    endif()

    check_include_file(libusbhid.h HAVE_LIBUSBHID_H)
    if(HAVE_LIBUSBHID_H)
      set(USB_CFLAGS "${USB_CFLAGS} -DHAVE_LIBUSBHID_H")
    endif()
    set(USB_LIBS ${USB_LIBS} usbhid)
  else()
    check_include_file(usb.h HAVE_USB_H)
    if(HAVE_USB_H)
      set(USB_CFLAGS "-DHAVE_USB_H")
    endif()
    check_include_file(libusb.h HAVE_LIBUSB_H)
    if(HAVE_LIBUSB_H)
      set(USB_CFLAGS "${USB_CFLAGS} -DHAVE_LIBUSB_H")
    endif()
    check_library_exists(usb hid_init "" LIBUSB)
    if(LIBUSB)
      set(USB_LIBS ${USB_LIBS} usb)
    endif()
  endif()

  set(CMAKE_REQUIRED_FLAGS "${USB_CFLAGS} ${ORIG_CMAKE_REQUIRED_FLAGS}")
  set(CMAKE_REQUIRED_LIBRARIES "${USB_LIBS}")
  check_c_source_compiles("
       #include <sys/types.h>
        #if defined(HAVE_USB_H)
        #include <usb.h>
        #endif
        #ifdef __DragonFly__
        # include <bus/usb/usb.h>
        # include <bus/usb/usbhid.h>
        #else
        # include <dev/usb/usb.h>
        # include <dev/usb/usbhid.h>
        #endif
        #if defined(HAVE_USBHID_H)
        #include <usbhid.h>
        #elif defined(HAVE_LIBUSB_H)
        #include <libusb.h>
        #elif defined(HAVE_LIBUSBHID_H)
        #include <libusbhid.h>
        #endif
        int main(int argc, char **argv) {
          struct report_desc *repdesc;
          struct usb_ctl_report *repbuf;
          hid_kind_t hidkind;
          return 0;
        }" HAVE_USBHID)
  if(HAVE_USBHID)
    check_c_source_compiles("
          #include <sys/types.h>
          #if defined(HAVE_USB_H)
          #include <usb.h>
          #endif
          #ifdef __DragonFly__
          # include <bus/usb/usb.h>
          # include <bus/usb/usbhid.h>
          #else
          # include <dev/usb/usb.h>
          # include <dev/usb/usbhid.h>
          #endif
          #if defined(HAVE_USBHID_H)
          #include <usbhid.h>
          #elif defined(HAVE_LIBUSB_H)
          #include <libusb.h>
          #elif defined(HAVE_LIBUSBHID_H)
          #include <libusbhid.h>
          #endif
          int main(int argc, char** argv) {
            struct usb_ctl_report buf;
            if (buf.ucr_data) { }
            return 0;
          }" HAVE_USBHID_UCR_DATA)
    if(HAVE_USBHID_UCR_DATA)
      set(USB_CFLAGS "${USB_CFLAGS} -DUSBHID_UCR_DATA")
    endif()

    check_c_source_compiles("
          #include <sys/types.h>
          #if defined(HAVE_USB_H)
          #include <usb.h>
          #endif
          #ifdef __DragonFly__
          #include <bus/usb/usb.h>
          #include <bus/usb/usbhid.h>
          #else
          #include <dev/usb/usb.h>
          #include <dev/usb/usbhid.h>
          #endif
          #if defined(HAVE_USBHID_H)
          #include <usbhid.h>
          #elif defined(HAVE_LIBUSB_H)
          #include <libusb.h>
          #elif defined(HAVE_LIBUSBHID_H)
          #include <libusbhid.h>
          #endif
          int main(int argc, char **argv) {
            report_desc_t d;
            hid_start_parse(d, 1, 1);
            return 0;
          }" HAVE_USBHID_NEW)
    if(HAVE_USBHID_NEW)
      set(USB_CFLAGS "${USB_CFLAGS} -DUSBHID_NEW")
    endif()

    check_c_source_compiles("
        #include <machine/joystick.h>
        int main(int argc, char** argv) {
            struct joystick t;
            return 0;
        }" HAVE_MACHINE_JOYSTICK)
    if(HAVE_MACHINE_JOYSTICK)
      set(SDL_JOYSTICK_USBHID_MACHINE_JOYSTICK_H 1)
    endif()
    set(SDL_JOYSTICK_USBHID 1)
    file(GLOB BSD_JOYSTICK_SOURCES ${SDL2_SOURCE_DIR}/src/joystick/bsd/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${BSD_JOYSTICK_SOURCES})
    list(APPEND EXTRA_CFLAGS ${USB_CFLAGS})
    list(APPEND EXTRA_LIBS ${USB_LIBS})
    set(HAVE_SDL_JOYSTICK TRUE)

    set(CMAKE_REQUIRED_LIBRARIES)
    set(CMAKE_REQUIRED_FLAGS ${ORIG_CMAKE_REQUIRED_FLAGS})
  endif()
endmacro()

# Check for HIDAPI joystick drivers. This is currently a Unix thing, not Windows or macOS!
macro(CheckHIDAPI)
  if(HIDAPI)
    if(HIDAPI_SKIP_LIBUSB)
      set(HAVE_HIDAPI TRUE)
    else()
      set(HAVE_HIDAPI FALSE)
      pkg_check_modules(LIBUSB libusb)
      if (LIBUSB_FOUND)
        check_include_file(libusb.h HAVE_LIBUSB_H)
        if (HAVE_LIBUSB_H)
          set(HAVE_HIDAPI TRUE)
        endif()
      endif()
    endif()

    if(HAVE_HIDAPI)
      set(SDL_JOYSTICK_HIDAPI 1)
      set(HAVE_SDL_JOYSTICK TRUE)
      file(GLOB HIDAPI_SOURCES ${SDL2_SOURCE_DIR}/src/joystick/hidapi/*.c)
      set(SOURCE_FILES ${SOURCE_FILES} ${HIDAPI_SOURCES})
      set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${LIBUSB_CFLAGS} -I\"${SDL2_SOURCE_DIR}/src/hidapi/hidapi\"")
      if(NOT HIDAPI_SKIP_LIBUSB)
        set(SOURCE_FILES ${SOURCE_FILES} ${SDL2_SOURCE_DIR}/src/hidapi/libusb/hid.c)
        list(APPEND EXTRA_LIBS ${LIBUSB_LIBS})
      endif()
    endif()
  endif()
endmacro()


# Requires:
# - n/a
macro(CheckRPI)
  if(VIDEO_RPI)
    # Urho3D - bug fix - commented out CMAKE_REQUIRED_LIBRARIES as it actually causes the detection to fail
    check_c_source_compiles("
        #include <bcm_host.h>
        int main(int argc, char **argv) {}" HAVE_VIDEO_RPI)
    if(SDL_VIDEO AND HAVE_VIDEO_RPI)
      set(HAVE_SDL_VIDEO TRUE)
      set(SDL_VIDEO_DRIVER_RPI 1)
      file(GLOB VIDEO_RPI_SOURCES ${SDL2_SOURCE_DIR}/src/video/raspberry/*.c)
      set(SOURCE_FILES ${SOURCE_FILES} ${VIDEO_RPI_SOURCES})
      list (APPEND EXTRA_LIBS bcm_host)
    endif(SDL_VIDEO AND HAVE_VIDEO_RPI)
  endif(VIDEO_RPI)
endmacro(CheckRPI)

# Requires:
# - EGL
# - PkgCheckModules
# Optional:
# - KMSDRM_SHARED opt
# - HAVE_DLOPEN opt
macro(CheckKMSDRM)
  if(VIDEO_KMSDRM)
    # Urho3D - bug fix - do not use pkg-config tool for detection as it only works for host environment and not for rooted environment when cross-compiling
    find_package (DRM)
    find_package (GBM)
    if(DRM_FOUND AND GBM_FOUND)
      include_directories (SYSTEM ${DRM_INCLUDE_DIRS} ${GBM_INCLUDE_DIRS})
      set(HAVE_VIDEO_KMSDRM TRUE)
      set(HAVE_SDL_VIDEO TRUE)

      file(GLOB KMSDRM_SOURCES ${SDL2_SOURCE_DIR}/src/video/kmsdrm/*.c)
      set(SOURCE_FILES ${SOURCE_FILES} ${KMSDRM_SOURCES})

      set(SDL_VIDEO_DRIVER_KMSDRM 1)

      if(KMSDRM_SHARED)
        if(NOT HAVE_DLOPEN)
          message_warn("You must have SDL_LoadObject() support for dynamic KMS/DRM loading")
        else()
          get_soname (DRM_LIB_SONAME DRM_LIBRARIES)
          get_soname (GBM_LIB_SONAME GBM_LIBRARIES)
          set(SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC "\"${DRM_LIB_SONAME}\"")
          set(SDL_VIDEO_DRIVER_KMSDRM_DYNAMIC_GBM "\"${GBM_LIB_SONAME}\"")
          set(HAVE_KMSDRM_SHARED TRUE)
        endif()
      else()
        list (APPEND EXTRA_LIBS drm gbm)
      endif()
    endif()
  endif()
endmacro()
