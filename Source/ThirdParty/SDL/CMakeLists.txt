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

#
# Copyright (c) 2008-2016 the Urho3D project.
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

# Urho3D - define target name
set (TARGET_NAME SDL)

# Urho3D - commented out in-source tree build prevention as Urho3D supports both out-of-source and in-source tree builds

# Urho3D - commented out setting SDL2 as project name as we want SDL sub-library to remain within Urho3D "umbrella" project
#          instead, just enable the required language support and set the extra variables associated with project() command
enable_language (C)
set (SDL2_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set (SDL2_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
include(CheckFunctionExists)
include(CheckLibraryExists)
include(CheckIncludeFiles)
include(CheckIncludeFile)
include(CheckSymbolExists)
include(CheckCSourceRuns)
include(CheckCCompilerFlag)
include(CheckTypeSize)
include(CheckStructHasMember)
include(CMakeDependentOption)
# Urho3D - bug fix - do not use pkg-config tool for detection as it only works for host environment and not for rooted environment when cross-compiling
# Urho3D - append SDL's CMake module directory into our global module search path
list (APPEND CMAKE_MODULE_PATH ${SDL2_SOURCE_DIR}/cmake)
include(${SDL2_SOURCE_DIR}/cmake/macros.cmake)
include(${SDL2_SOURCE_DIR}/cmake/sdlchecks.cmake)

# General settings
# Edit include/SDL_version.h and change the version, then:
#   SDL_MICRO_VERSION += 1;
#   SDL_INTERFACE_AGE += 1;
#   SDL_BINARY_AGE += 1;
# if any functions have been added, set SDL_INTERFACE_AGE to 0.
# if backwards compatibility has been broken,
# set SDL_BINARY_AGE and SDL_INTERFACE_AGE to 0.
set(SDL_MAJOR_VERSION 2)
set(SDL_MINOR_VERSION 0)
set(SDL_MICRO_VERSION 4)
set(SDL_INTERFACE_AGE 0)
set(SDL_BINARY_AGE 4)
set(SDL_VERSION "${SDL_MAJOR_VERSION}.${SDL_MINOR_VERSION}.${SDL_MICRO_VERSION}")

# Calculate a libtool-like version number
math(EXPR LT_CURRENT "${SDL_MICRO_VERSION} - ${SDL_INTERFACE_AGE}")
math(EXPR LT_AGE "${SDL_BINARY_AGE} - ${SDL_INTERFACE_AGE}")
math(EXPR LT_MAJOR "${LT_CURRENT}- ${LT_AGE}")
set(LT_REVISION "${SDL_INTERFACE_AGE}")
set(LT_RELEASE "${SDL_MAJOR_VERSION}.${SDL_MINOR_VERSION}")
set(LT_VERSION "${LT_MAJOR}.${LT_AGE}.${LT_REVISION}")

# Urho3D - commented out debug print

# General settings & flags
# Urho3D - commented out LIBRARY_OUTPUT_DIRECTORY configuration so that it does not mess up with our global configuration setup
# Check for 64 or 32 bit
# Urho3D - bug fix - using CMAKE_SIZEOF_VOID_P is not accurate in a situation where a multilib-capable compiler is chosen and user has opted to use non-native ABI; instead using URHO3D_64BIT build option as it also captures the user intention
if(URHO3D_64BIT)
  set(ARCH_64 TRUE)
  set(PROCESSOR_ARCH "x64")
else()
  set(ARCH_64 FALSE)
  set(PROCESSOR_ARCH "x86")
endif()
set(LIBNAME SDL2)
if(NOT LIBTYPE)
  set(LIBTYPE SHARED)
endif()

# Get the platform
if(WIN32)
  if(NOT WINDOWS)
    set(WINDOWS TRUE)
  endif()
elseif(UNIX AND NOT APPLE)
  if(CMAKE_SYSTEM_NAME MATCHES ".*Linux")
    set(LINUX TRUE)
  elseif(CMAKE_SYSTEM_NAME MATCHES "kFreeBSD.*")
    set(FREEBSD TRUE)
  elseif(CMAKE_SYSTEM_NAME MATCHES "kNetBSD.*|NetBSD.*")
    set(NETBSD TRUE)
  elseif(CMAKE_SYSTEM_NAME MATCHES "kOpenBSD.*|OpenBSD.*")
    set(OPENBSD TRUE)
  elseif(CMAKE_SYSTEM_NAME MATCHES ".*GNU.*")
    set(GNU TRUE)
  elseif(CMAKE_SYSTEM_NAME MATCHES ".*BSDI.*")
    set(BSDI TRUE)
  elseif(CMAKE_SYSTEM_NAME MATCHES "DragonFly.*|FreeBSD")
    set(FREEBSD TRUE)
  elseif(CMAKE_SYSTEM_NAME MATCHES "SYSV5.*")
    set(SYSV5 TRUE)
  elseif(CMAKE_SYSTEM_NAME MATCHES "Solaris.*")
    set(SOLARIS TRUE)
  elseif(CMAKE_SYSTEM_NAME MATCHES "HP-UX.*")
    set(HPUX TRUE)
  elseif(CMAKE_SYSTEM_NAME MATCHES "AIX.*")
    set(AIX TRUE)
  elseif(CMAKE_SYSTEM_NAME MATCHES "Minix.*")
    set(MINIX TRUE)
  endif()
elseif(APPLE)
  if(CMAKE_SYSTEM_NAME MATCHES ".*Darwin.*")
    set(DARWIN TRUE)
  elseif(CMAKE_SYSTEM_NAME MATCHES ".*MacOS.*")
    set(MACOSX TRUE)
  endif()
  # TODO: iOS?
elseif(CMAKE_SYSTEM_NAME MATCHES "BeOS.*")
  message_error("BeOS support has been removed as of SDL 2.0.2.")
elseif(CMAKE_SYSTEM_NAME MATCHES "Haiku.*")
  set(HAIKU TRUE)
endif()

# Don't mistake osx for unix
if(UNIX AND NOT APPLE)
  set(UNIX_SYS ON)
else()
  set(UNIX_SYS OFF)
endif()

if(UNIX OR APPLE)
  set(UNIX_OR_MAC_SYS ON)
else()
  set(UNIX_OR_MAC_SYS OFF)
endif()

if (UNIX_OR_MAC_SYS AND NOT EMSCRIPTEN) # JavaScript does not yet have threading support, so disable pthreads when building for Emscripten.
  set(SDL_PTHREADS_ENABLED_BY_DEFAULT ON)
else()
  set(SDL_PTHREADS_ENABLED_BY_DEFAULT OFF)
endif()

# Default option knobs
# Urho3D - commented out OPT_DEF_SSEMATH default variable as the underyling SSEMATH build option is also being commented out by us
if(UNIX OR MINGW OR MSYS)
  set(OPT_DEF_LIBC ON)
endif()

# Compiler info
if(CMAKE_COMPILER_IS_GNUCC)
  set(USE_GCC TRUE)
  set(OPT_DEF_ASM TRUE)
elseif(CMAKE_C_COMPILER_ID MATCHES "Clang")
  set(USE_CLANG TRUE)
  set(OPT_DEF_ASM TRUE)
elseif(MSVC_VERSION GREATER 1400) # VisualStudio 8.0+
  set(OPT_DEF_ASM TRUE)
  #set(CMAKE_C_FLAGS "/ZI /WX- /
else()
  set(OPT_DEF_ASM FALSE)
endif()

# Urho3D - commented out compiler/linker flags setup as we have configured all our compiler/linker flags as we want globally

# Those are used for pkg-config and friends, so that the SDL2.pc, sdl2-config, # etc. are created correctly.
# Urho3D - we do not use these variables for pkg-config setup for SDL library but we may need them later for Urho3D library
set (SDL_LIBS)
set (SDL_CFLAGS)

# Emscripten toolchain has a nonempty default value for this, and the checks
# in this file need to change that, so remember the original value, and
# restore back to that afterwards. For check_function_exists() to work in
# Emscripten, this value must be at its default value.
set(ORIG_CMAKE_REQUIRED_FLAGS ${CMAKE_REQUIRED_FLAGS})
# Urho3D - save the original CMake global settings, do not leave them to chances
set (ORIG_CMAKE_REQUIRED_INCLUDES ${CMAKE_REQUIRED_INCLUDES})
set (ORIG_CMAKE_REQUIRED_LIBRARIES ${CMAKE_REQUIRED_LIBRARIES})

if(CYGWIN)
  # We build SDL on cygwin without the UNIX emulation layer
  include_directories("-I/usr/include/mingw")
  set(CMAKE_REQUIRED_FLAGS "-mno-cygwin")
  check_c_source_compiles("int main(int argc, char **argv) {}"
    HAVE_GCC_NO_CYGWIN)
  set(CMAKE_REQUIRED_FLAGS ${ORIG_CMAKE_REQUIRED_FLAGS})
  if(HAVE_GCC_NO_CYGWIN)
    list(APPEND EXTRA_LDFLAGS "-mno-cygwin")
    list(APPEND SDL_LIBS "-mno-cygwin")
  endif()
  set(SDL_CFLAGS "${SDL_CFLAGS} -I/usr/include/mingw")
endif()

add_definitions(-DUSING_GENERATED_CONFIG_H)
# General includes
# Urho3D - use 'generated' path suffix for generated config header file, the suffic prevents overwriting the header file with the same name in the source tree in case of non out-of-source build tree is being used
set (INCLUDE_DIRS ${SDL2_BINARY_DIR}/include/generated ${SDL2_SOURCE_DIR}/include)

# All these ENABLED_BY_DEFAULT vars will default to ON if not specified, so
#  you only need to have a platform override them if they are disabling.
# Urho3D - bug fix - commented out double initialization of the OPT_DEF_ASM variable, it has been initialized properly in "Compiler info" section above
if(EMSCRIPTEN)
  # Set up default values for the currently supported set of subsystems:
  # Emscripten/Javascript does not have assembly support, a dynamic library
  # loading architecture, low-level CPU inspection or multithreading.
  set(OPT_DEF_ASM FALSE)
  set(SDL_SHARED_ENABLED_BY_DEFAULT OFF)
  set(SDL_ATOMIC_ENABLED_BY_DEFAULT OFF)
  set(SDL_THREADS_ENABLED_BY_DEFAULT OFF)
  set(SDL_LOADSO_ENABLED_BY_DEFAULT OFF)
  set(SDL_CPUINFO_ENABLED_BY_DEFAULT OFF)
  set(SDL_DLOPEN_ENABLED_BY_DEFAULT OFF)
endif()

# Urho3D - we always build internal sub-libraries as STATIC library type, so this build option is not applicable to us
set (SDL_SHARED_ENABLED_BY_DEFAULT OFF)
# Urho3D - we prefer to disable 2D render subsystem by default
if (NOT DEFINED SDL_RENDER_ENABLED_BY_DEFAULT)
    set (SDL_RENDER_ENABLED_BY_DEFAULT OFF)
endif ()

set(SDL_SUBSYSTEMS
    Atomic Audio Video Render Events Joystick Haptic Power Threads Timers
    File Loadso CPUinfo Filesystem Dlopen)
foreach(_SUB ${SDL_SUBSYSTEMS})
  string(TOUPPER ${_SUB} _OPT)
  if (NOT DEFINED SDL_${_OPT}_ENABLED_BY_DEFAULT)
    set(SDL_${_OPT}_ENABLED_BY_DEFAULT ON)
  endif()
  option(SDL_${_OPT} "Enable the ${_SUB} subsystem" ${SDL_${_OPT}_ENABLED_BY_DEFAULT})
endforeach()

# Urho3D - TODO - put all these options into SDL-specific namespace group, they are littering CMake-gui all over the place as it is now
option_string(ASSERTIONS "Enable internal sanity checks (auto/disabled/release/enabled/paranoid)" "auto")
#set_option(DEPENDENCY_TRACKING "Use gcc -MMD -MT dependency tracking" ON)
set_option(LIBC                "Use the system C library" ${OPT_DEF_LIBC})
set_option(GCC_ATOMICS         "Use gcc builtin atomics" ${USE_GCC})
set_option(ASSEMBLY            "Enable assembly routines" ${OPT_DEF_ASM})
# Urho3D - commented out SSEMATH, SSE, SSE2, MMX, 3DNOW, ALTIVEC build options as they have been reclassifified as Urho3D own build options
set_option(DISKAUDIO           "Support the disk writer audio driver" ON)
set_option(DUMMYAUDIO          "Support the dummy audio driver" ON)
set_option(VIDEO_DIRECTFB      "Use DirectFB video driver" OFF)
dep_option(DIRECTFB_SHARED     "Dynamically load directfb support" ON "VIDEO_DIRECTFB" OFF)
set_option(FUSIONSOUND         "Use FusionSound audio driver" OFF)
dep_option(FUSIONSOUND_SHARED  "Dynamically load fusionsound audio support" ON "FUSIONSOUND" OFF)
set_option(VIDEO_DUMMY         "Use dummy video driver" ON)
set_option(VIDEO_OPENGL        "Include OpenGL support" ON)
# Urho3D - hide OpenGLES option from MinGW platform because it does not have the necessary header file to build OpenGLES video driver
dep_option(VIDEO_OPENGLES      "Include OpenGL ES support" ON "NOT MINGW" OFF)
set_option(PTHREADS            "Use POSIX threads for multi-threading" ${SDL_PTHREADS_ENABLED_BY_DEFAULT})
dep_option(PTHREADS_SEM        "Use pthread semaphores" ON "PTHREADS" OFF)
set_option(SDL_DLOPEN          "Use dlopen for shared object loading" ${SDL_DLOPEN_ENABLED_BY_DEFAULT})
# Urho3D - hide Linux-specific audio driver options from Android platform
dep_option(OSS                 "Support the OSS audio API" ON "${UNIX_SYS} AND NOT ANDROID" OFF)
dep_option(ALSA                "Support the ALSA audio API" ON "UNIX_SYS AND NOT ANDROID" OFF)
dep_option(ALSA_SHARED         "Dynamically load ALSA audio support" ON "ALSA" OFF)
dep_option(ESD                 "Support the Enlightened Sound Daemon" ON "UNIX_SYS AND NOT ANDROID" OFF)
dep_option(ESD_SHARED          "Dynamically load ESD audio support" ON "ESD" OFF)
dep_option(PULSEAUDIO          "Use PulseAudio" ON "UNIX_SYS AND NOT ANDROID" OFF)
dep_option(PULSEAUDIO_SHARED   "Dynamically load PulseAudio support" ON "PULSEAUDIO" OFF)
dep_option(ARTS                "Support the Analog Real Time Synthesizer" ON "UNIX_SYS AND NOT ANDROID" OFF)
dep_option(ARTS_SHARED         "Dynamically load aRts audio support" ON "ARTS" OFF)
dep_option(NAS                 "Support the NAS audio API" ON "UNIX_SYS AND NOT ANDROID" OFF)
dep_option(NAS_SHARED          "Dynamically load NAS audio API" ON NAS OFF)
dep_option(SNDIO               "Support the Roar audio API" ON "${UNIX_SYS} AND NOT ANDROID" OFF)
# Urho3D - commented out RPATH as an option because Urho3D is configured to always use RPATH, so init the variable to always TRUE
set (RPATH TRUE)
set_option(CLOCK_GETTIME       "Use clock_gettime() instead of gettimeofday()" OFF)
set_option(INPUT_TSLIB         "Use the Touchscreen library for input" ${UNIX_SYS})
set_option(VIDEO_X11           "Use X11 video driver" ${UNIX_SYS})
dep_option(VIDEO_WAYLAND       "Use Wayland video driver" ON UNIX_SYS OFF)
dep_option(WAYLAND_SHARED      "Dynamically load Wayland support" ON "VIDEO_WAYLAND" OFF)
dep_option(VIDEO_WAYLAND_QT_TOUCH  "QtWayland server support for Wayland video driver" ON "VIDEO_WAYLAND" OFF)
dep_option(VIDEO_MIR           "Use Mir video driver" ON UNIX_SYS OFF)
dep_option(MIR_SHARED          "Dynamically load Mir support" ON "VIDEO_MIR" OFF)
# Urho3D - only make VIDEO_RPI option available on Raspberry-Pi platform
dep_option(VIDEO_RPI           "Use Raspberry Pi video driver" ON RPI OFF)
dep_option(X11_SHARED          "Dynamically load X11 support" ON "VIDEO_X11" OFF)
set(SDL_X11_OPTIONS Xcursor Xinerama XInput Xrandr Xscrnsaver XShape Xvm)
foreach(_SUB ${SDL_X11_OPTIONS})
  string(TOUPPER "VIDEO_X11_${_SUB}" _OPT)
  dep_option(${_OPT}           "Enable ${_SUB} support" ON "VIDEO_X11" OFF)
endforeach()
set_option(VIDEO_COCOA         "Use Cocoa video driver" ${APPLE})
# Urho3D - only make DIRECTX option available on Windows platform when URHO3D_OPENGL is enabled
if (WINDOWS)
  dep_option(DIRECTX             "Use DirectX for Windows audio/video" ON URHO3D_OPENGL ON)
endif ()
# Urho3D - commented out RENDER_D3D as an option to avoid potential conflict with our URHO3D_OPENGL and URHO3D_D3D11 build options on Windows platform
#          Instead just initialize the variable according to our build options; Urho3D also by default disables the SDL renderer subsystem
if (WINDOWS)
  if (URHO3D_OPENGL)
    set (RENDER_D3D FALSE)
  else ()
    set (RENDER_D3D TRUE)
  endif ()
endif ()
set_option(VIDEO_VIVANTE       "Use Vivante EGL video driver" ${UNIX_SYS})

# TODO: We should (should we?) respect cmake's ${BUILD_SHARED_LIBS} flag here
# The options below are for compatibility to configure's default behaviour.
set(SDL_SHARED ${SDL_SHARED_ENABLED_BY_DEFAULT} CACHE BOOL "Build a shared version of the library")
set(SDL_STATIC ON CACHE BOOL "Build a static version of the library")

# General source files
set (SOURCE_FILE_PATTERNS
  ${SDL2_SOURCE_DIR}/src/*.c
# Urho3D - we always disable dynamic API, so commented out ${SDL2_SOURCE_DIR}/src/dynapi/*.c
  ${SDL2_SOURCE_DIR}/src/libm/*.c
  ${SDL2_SOURCE_DIR}/src/stdlib/*.c)
# Urho3D - exclude source files from disabled subsystems
foreach (_SUB ATOMIC AUDIO CPUINFO EVENTS FILE RENDER THREADS TIMERS VIDEO)
  string (TOLOWER ${_SUB} _DIR)
  if (${SDL_${_SUB}})
    # Cater for SDL inconsistency in naming convention
    if (_DIR STREQUAL threads)
      set (_DIR thread)
    elseif (_DIR STREQUAL timers)
      set (_DIR timer)
    endif ()
    list (APPEND SOURCE_FILE_PATTERNS ${SDL2_SOURCE_DIR}/src/${_DIR}/*.c)
  endif ()
endforeach()
if (SDL_RENDER)
  list (APPEND ${SDL2_SOURCE_DIR}/src/render/*/*.c)   # Recurse one more level
endif ()
file(GLOB SOURCE_FILES ${SOURCE_FILE_PATTERNS})

if(ASSERTIONS STREQUAL "auto")
  # Do nada - use optimization settings to determine the assertion level
elseif(ASSERTIONS STREQUAL "disabled")
  set(SDL_DEFAULT_ASSERT_LEVEL 0)
elseif(ASSERTIONS STREQUAL "release")
  set(SDL_DEFAULT_ASSERT_LEVEL 1)
elseif(ASSERTIONS STREQUAL "enabled")
  set(SDL_DEFAULT_ASSERT_LEVEL 2)
elseif(ASSERTIONS STREQUAL "paranoid")
  set(SDL_DEFAULT_ASSERT_LEVEL 3)
else()
  message_error("unknown assertion level")
endif()
set(HAVE_ASSERTIONS ${ASSERTIONS})

# Compiler option evaluation
if(USE_GCC OR USE_CLANG)
  if(DEPENDENCY_TRACKING)
    check_c_source_compiles("
        #if !defined(__GNUC__) || __GNUC__ < 3
        #error Dependency tracking requires GCC 3.0 or newer
        #endif
        int main(int argc, char **argv) { }" HAVE_DEPENDENCY_TRACKING)
  endif()

  if(GCC_ATOMICS)
    check_c_source_compiles("int main(int argc, char **argv) {
        int a;
        void *x, *y, *z;
        __sync_lock_test_and_set(&a, 4);
        __sync_lock_test_and_set(&x, y);
        __sync_fetch_and_add(&a, 1);
        __sync_bool_compare_and_swap(&a, 5, 10);
        __sync_bool_compare_and_swap(&x, y, z); }" HAVE_GCC_ATOMICS)
    if(NOT HAVE_GCC_ATOMICS)
      check_c_source_compiles("int main(int argc, char **argv) {
          int a;
          __sync_lock_test_and_set(&a, 1);
          __sync_lock_release(&a); }" HAVE_GCC_SYNC_LOCK_TEST_AND_SET)
    endif()
  endif()

  set(CMAKE_REQUIRED_FLAGS "-mpreferred-stack-boundary=2")
  check_c_source_compiles("int x = 0; int main(int argc, char **argv) {}"
    HAVE_GCC_PREFERRED_STACK_BOUNDARY)
  set(CMAKE_REQUIRED_FLAGS ${ORIG_CMAKE_REQUIRED_FLAGS})

# Urho3D - we rely on GenerateExportHeader CMake module for configuring GCC/Clang visibility attribute support

  check_c_compiler_flag(-Wall HAVE_GCC_WALL)
  if(HAVE_GCC_WALL)
    list(APPEND EXTRA_CFLAGS "-Wall")
    if(HAIKU)
      # Urho3D - TODO - since we do not support HAIKU for now, we can leave the cflags configuration here
      #          However, when we do then it must be moved to our common module and/or just commented out
      set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-multichar")
    endif()
  endif()
  check_c_compiler_flag(-Wshadow HAVE_GCC_WSHADOW)
  if(HAVE_GCC_WSHADOW)
    list(APPEND EXTRA_CFLAGS "-Wshadow")
  endif()

  set(CMAKE_REQUIRED_FLAGS "-Wl,--no-undefined")
  check_c_compiler_flag("" HAVE_NO_UNDEFINED)
  set(CMAKE_REQUIRED_FLAGS ${ORIG_CMAKE_REQUIRED_FLAGS})
  if(HAVE_NO_UNDEFINED)
    list(APPEND EXTRA_LDFLAGS "-Wl,--no-undefined")
  endif()
endif()

if(ASSEMBLY)
  if(USE_GCC OR USE_CLANG)
    set(SDL_ASSEMBLY_ROUTINES 1)
    # TODO: Those all seem to be quite GCC specific - needs to be
    # reworked for better compiler support
    set(HAVE_ASSEMBLY TRUE)

    # Urho3D - move the altivec, mmx, 3dnow, sse and sse2 checks to Urho3D common module which then configure the compiler flags globally

    # Urho3D - bug fix - do not use "-mfpmath=387" in EXTRA_CFLAGS, instead let the compiler to choose what's the best by itself (i.e. '387' for x86 and 'sse' for x86_64) and also to keep SDL library being built with the same option as Urho3D library and all the other 3rd-party sub-libraries; besides the '387' is invalid when targeting arm64

    # Urho3D - commented out the HAVE_SSEMATH variable as it is not being used anywhere currently; furthermore compiler already emits __SSE_MATH__ or __SSE2_MATH__ as necessary on x86_64 ABI only; so instead of using HAVE_SSEMATH variable, we should actually use the __SSE_MATH__ or __SSE2_MATH__ compiler define if that is the original intention of having this variable

    if(URHO3D_ALTIVEC)
      set(SDL_ALTIVEC_BLITTERS 1)
    endif()
  elseif(MSVC_VERSION GREATER 1500)
    # TODO: SDL_cpuinfo.h needs to support the user's configuration wish
    # Urho3D - move the HAVE_MMX, HAVE_3DNOW, HAVE_SSE and HAVE_SSE2 initialization to Urho3D common module
    set(SDL_ASSEMBLY_ROUTINES 1)
  endif()
endif()

# TODO: Can't deactivate on FreeBSD? w/o LIBC, SDL_stdinc.h can't define
# anything.
if(LIBC)
  if(WINDOWS AND NOT MINGW)
    set(HAVE_LIBC TRUE)
    foreach(_HEADER stdio.h string.h ctype.h math.h)
      string(TOUPPER "HAVE_${_HEADER}" _UPPER)
      string(REPLACE "." "_" _HAVE_H ${_UPPER})
      set(${_HAVE_H} 1)
    endforeach()
    set(HAVE_SIGNAL_H 1)
    foreach(_FN
            malloc calloc realloc free qsort abs memset memcpy memmove memcmp
            strlen _strrev _strupr _strlwr strchr strrchr strstr itoa _ltoa
            _ultoa strtol strtoul strtoll strtod atoi atof strcmp strncmp
            _stricmp _strnicmp sscanf atan atan2 acos asin ceil copysign cos
            cosf fabs floor log pow scalbn sin sinf sqrt sqrtf tan tanf)
      string(TOUPPER ${_FN} _UPPER)
      set(HAVE_${_UPPER} 1)
    endforeach()
    if(NOT CYGWIN AND NOT MINGW)
      set(HAVE_ALLOCA 1)
    endif()
    set(HAVE_M_PI 1)
    add_definitions(-D_USE_MATH_DEFINES) # needed for M_PI
    set(STDC_HEADERS 1)
  else()
    set(HAVE_LIBC TRUE)
    # Urho3D - bug fix - starting since Raspbian Jessie the __USE_EXTERN_INLINE is defined in <features.h> causing stdlib.h to look for <bits/stdlib-bsearch.h> which is not in the system header search path on Raspberry-Pi platform
    if (RPI)
      find_path (STDLIB_BITS_INCLUDE_DIR NAMES bits/stdlib-bsearch.h PATH_SUFFIXES arm-linux-gnueabihf DOC "Raspberry-Pi stdlib's bits include directory")
      if (STDLIB_BITS_INCLUDE_DIR)
        include_directories (${STDLIB_BITS_INCLUDE_DIR})
      endif ()
    endif ()
    # Urho3D - bug fix - when cross-compiling the headers are rooted, either use "--sysroot" compiler flag or use CMAKE_REQUIRED_INCLUDES (e.g. on RPI) to cater for it
    set (CMAKE_REQUIRED_INCLUDES_SYS_TYPES_SAVED ${CMAKE_REQUIRED_INCLUDES})
    if (CMAKE_CROSSCOMPILING AND NOT "${CMAKE_C_FLAGS} ${CMAKE_REQUIRED_FLAGS}" MATCHES sysroot)
      find_path (SYS_TYPES_H_INCLUDE_DIRS NAMES sys/types.h)
      if (SYS_TYPES_H_INCLUDE_DIRS)
        # Assume the header search path has not been adjusted elsewhere yet, there is no harm anyway when a same entry is added twice into the list
        list (APPEND CMAKE_REQUIRED_INCLUDES ${SYS_TYPES_H_INCLUDE_DIRS})
      endif ()
    endif ()
    check_include_file(sys/types.h HAVE_SYS_TYPES_H)
    set (CMAKE_REQUIRED_INCLUDES ${CMAKE_REQUIRED_INCLUDES_SYS_TYPES_SAVED})
    # Urho3D - no fix required - it seems all the compiler toolchains (native and X-compiling) that have been tested are able to find these headers correctly
    #          Android NDK is able to find these headers with the help of "--sysroot" compiler flags, while others like MinGW and Linaro GCC for RPI work out of box
    foreach(_HEADER
            stdio.h stdlib.h stddef.h stdarg.h malloc.h memory.h string.h
            strings.h inttypes.h stdint.h ctype.h math.h iconv.h signal.h)
      string(TOUPPER "HAVE_${_HEADER}" _UPPER)
      string(REPLACE "." "_" _HAVE_H ${_UPPER})
      check_include_file("${_HEADER}" ${_HAVE_H})
    endforeach()
    # Urho3D - bug fix - MinGW has standard-C headers, except dlfcn.h
    set (CHECK_STDC_HEADERS stdint.h stddef.h inttypes.h stdlib.h strings.h string.h float.h)
    if (NOT MINGW)
      list (APPEND CHECK_STDC_HEADERS dlfcn.h)
    endif ()
    check_include_files("${CHECK_STDC_HEADERS}" STDC_HEADERS)   # Stringify the INCLUDE list variable as this macro does not expect to receive a list
    check_type_size("size_t" SIZEOF_SIZE_T)
    check_symbol_exists(M_PI math.h HAVE_M_PI)
    # Urho3D - for consistency sake use check_include_file() to check for HAVE_MPROTECT
    check_include_file (sys/mman.h HAVE_MPROTECT)
    foreach(_FN
            strtod malloc calloc realloc free getenv setenv putenv unsetenv
            qsort abs bcopy memset memcpy memmove memcmp strlen strlcpy strlcat
            strdup _strrev _strupr _strlwr strchr strrchr strstr itoa _ltoa
            _uitoa _ultoa strtol strtoul _i64toa _ui64toa strtoll strtoull
            atoi atof strcmp strncmp _stricmp strcasecmp _strnicmp strncasecmp
            vsscanf vsnprintf fseeko fseeko64 sigaction setjmp
            nanosleep sysconf sysctlbyname
            )
      string(TOUPPER ${_FN} _UPPER)
      set(_HAVEVAR "HAVE_${_UPPER}")
      check_function_exists("${_FN}" ${_HAVEVAR})
    endforeach()

    check_library_exists(m pow "" HAVE_LIBM)
    if(HAVE_LIBM)
      set(CMAKE_REQUIRED_LIBRARIES m)
      foreach(_FN
              atan atan2 ceil copysign cos cosf fabs floor log pow scalbn sin
              sinf sqrt sqrtf tan tanf acos asin)
        string(TOUPPER ${_FN} _UPPER)
        set(_HAVEVAR "HAVE_${_UPPER}")
        check_function_exists("${_FN}" ${_HAVEVAR})
      endforeach()
      set(CMAKE_REQUIRED_LIBRARIES)
      list(APPEND EXTRA_LIBS m)
    endif()

    check_library_exists(iconv iconv_open "" HAVE_LIBICONV)
    if(HAVE_LIBICONV)
      list(APPEND EXTRA_LIBS iconv)
      set(HAVE_ICONV 1)
    endif()

    # Urho3D - bug fix - cannot use check_function_exists() with alloca; with this bug fixed, the same check should work on Apple too so no more hardcoding
    check_include_file(alloca.h HAVE_ALLOCA_H)
    if (HAVE_ALLOCA_H)
      check_c_source_compiles ("
        #include <alloca.h>
        int main(int argc, char** argv) { alloca(0); }" HAVE_ALLOCA)
    endif ()

    check_struct_has_member("struct sigaction" "sa_sigaction" "signal.h" HAVE_SA_SIGACTION)
  endif()
else()
  if(WINDOWS)
    set(HAVE_STDARG_H 1)
    set(HAVE_STDDEF_H 1)
  endif()
endif()


# Enable/disable various subsystems of the SDL library
foreach(_SUB ${SDL_SUBSYSTEMS})
  string(TOUPPER ${_SUB} _OPT)
  if(NOT SDL_${_OPT})
    set(SDL_${_OPT}_DISABLED 1)
  endif()
endforeach()
if(SDL_JOYSTICK)
  file(GLOB JOYSTICK_SOURCES ${SDL2_SOURCE_DIR}/src/joystick/*.c)
  set(SOURCE_FILES ${SOURCE_FILES} ${JOYSTICK_SOURCES})
endif()
if(SDL_HAPTIC)
  if(NOT SDL_JOYSTICK)
    # Haptic requires some private functions from the joystick subsystem.
    message_error("SDL_HAPTIC requires SDL_JOYSTICK, which is not enabled")
  endif()
  file(GLOB HAPTIC_SOURCES ${SDL2_SOURCE_DIR}/src/haptic/*.c)
  set(SOURCE_FILES ${SOURCE_FILES} ${HAPTIC_SOURCES})
endif()
if(SDL_POWER)
  file(GLOB POWER_SOURCES ${SDL2_SOURCE_DIR}/src/power/*.c)
  set(SOURCE_FILES ${SOURCE_FILES} ${POWER_SOURCES})
endif()
# TODO: in configure.in, the test for LOADSO and SDL_DLOPEN is a bit weird:
# if LOADSO is not wanted, SDL_LOADSO_DISABLED is set
# If however on Unix or APPLE dlopen() is detected via CheckDLOPEN(),
# SDL_LOADSO_DISABLED will not be set, regardless of the LOADSO settings

# General SDL subsystem options, valid for all platforms
if(SDL_AUDIO)
  # CheckDummyAudio/CheckDiskAudio - valid for all platforms
  if(DUMMYAUDIO)
    set(SDL_AUDIO_DRIVER_DUMMY 1)
    file(GLOB DUMMYAUDIO_SOURCES ${SDL2_SOURCE_DIR}/src/audio/dummy/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${DUMMYAUDIO_SOURCES})
    set(HAVE_DUMMYAUDIO TRUE)
  endif()
  if(DISKAUDIO)
    set(SDL_AUDIO_DRIVER_DISK 1)
    file(GLOB DISKAUDIO_SOURCES ${SDL2_SOURCE_DIR}/src/audio/disk/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${DISKAUDIO_SOURCES})
    set(HAVE_DISKAUDIO TRUE)
  endif()
endif()

if(SDL_DLOPEN)
  # Relevant for Unix/Darwin only
  if(UNIX OR APPLE)
    CheckDLOPEN()
  endif()
endif()

if(SDL_VIDEO)
  if(VIDEO_DUMMY)
    set(SDL_VIDEO_DRIVER_DUMMY 1)
    file(GLOB VIDEO_DUMMY_SOURCES ${SDL2_SOURCE_DIR}/src/video/dummy/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${VIDEO_DUMMY_SOURCES})
    set(HAVE_VIDEO_DUMMY TRUE)
    set(HAVE_SDL_VIDEO TRUE)
  endif()
endif()

if(ANDROID)
  file(GLOB ANDROID_CORE_SOURCES ${SDL2_SOURCE_DIR}/src/core/android/*.c)
  set(SOURCE_FILES ${SOURCE_FILES} ${ANDROID_CORE_SOURCES})
  # Urho3D - bug fix - SDL_android_main.c will be added later when setting up actual Android targets
  if(SDL_AUDIO)
    set(SDL_AUDIO_DRIVER_ANDROID 1)
    file(GLOB ANDROID_AUDIO_SOURCES ${SDL2_SOURCE_DIR}/src/audio/android/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${ANDROID_AUDIO_SOURCES})
    set(HAVE_SDL_AUDIO TRUE)
  endif()
  if(SDL_FILESYSTEM)
    set(SDL_FILESYSTEM_ANDROID 1)
    file(GLOB ANDROID_FILESYSTEM_SOURCES ${SDL2_SOURCE_DIR}/src/filesystem/android/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${ANDROID_FILESYSTEM_SOURCES})
    set(HAVE_SDL_FILESYSTEM TRUE)
  endif()
  if(SDL_JOYSTICK)
    set(SDL_JOYSTICK_ANDROID 1)
    file(GLOB ANDROID_JOYSTICK_SOURCES ${SDL2_SOURCE_DIR}/src/joystick/android/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${ANDROID_JOYSTICK_SOURCES})
    set(HAVE_SDL_JOYSTICK TRUE)
  endif()
  if(SDL_POWER)
    set(SDL_POWER_ANDROID 1)
    file(GLOB ANDROID_POWER_SOURCES ${SDL2_SOURCE_DIR}/src/power/android/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${ANDROID_POWER_SOURCES})
    set(HAVE_SDL_POWER TRUE)
  endif()
  if(SDL_VIDEO)
    set(SDL_VIDEO_DRIVER_ANDROID 1)
    file(GLOB ANDROID_VIDEO_SOURCES ${SDL2_SOURCE_DIR}/src/video/android/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${ANDROID_VIDEO_SOURCES})
    set(HAVE_SDL_VIDEO TRUE)

    #enable gles
    if(VIDEO_OPENGLES)
      set(SDL_VIDEO_OPENGL_EGL 1)
      set(HAVE_VIDEO_OPENGLES TRUE)
      set(SDL_VIDEO_OPENGL_ES2 1)
      set(SDL_VIDEO_RENDER_OGL_ES2 1)
    endif()
  endif()
  list(APPEND EXTRA_LDFLAGS "-Wl,--undefined=Java_org_libsdl_app_SDLActivity_nativeInit")
endif()

# Platform-specific options and settings
if(EMSCRIPTEN)
  # Hide noisy warnings that intend to aid mostly during initial stages of porting a new
  # project. Uncomment at will for verbose cross-compiling -I/../ path info.
  add_definitions(-Wno-warn-absolute-paths)
  if(SDL_AUDIO)
    set(SDL_AUDIO_DRIVER_EMSCRIPTEN 1)
    file(GLOB EM_AUDIO_SOURCES ${SDL2_SOURCE_DIR}/src/audio/emscripten/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${EM_AUDIO_SOURCES})
    set(HAVE_SDL_AUDIO TRUE)
  endif()
  if(SDL_FILESYSTEM)
    set(SDL_FILESYSTEM_EMSCRIPTEN 1)
    file(GLOB EM_FILESYSTEM_SOURCES ${SDL2_SOURCE_DIR}/src/filesystem/emscripten/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${EM_FILESYSTEM_SOURCES})
    set(HAVE_SDL_FILESYSTEM TRUE)
  endif()
  if(SDL_JOYSTICK)
    set(SDL_JOYSTICK_EMSCRIPTEN 1)
    file(GLOB EM_JOYSTICK_SOURCES ${SDL2_SOURCE_DIR}/src/joystick/emscripten/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${EM_JOYSTICK_SOURCES})
    set(HAVE_SDL_JOYSTICK TRUE)
  endif()
  if(SDL_POWER)
    set(SDL_POWER_EMSCRIPTEN 1)
    file(GLOB EM_POWER_SOURCES ${SDL2_SOURCE_DIR}/src/power/emscripten/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${EM_POWER_SOURCES})
    set(HAVE_SDL_POWER TRUE)
  endif()
  if(SDL_VIDEO)
    set(SDL_VIDEO_DRIVER_EMSCRIPTEN 1)
    file(GLOB EM_VIDEO_SOURCES ${SDL2_SOURCE_DIR}/src/video/emscripten/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${EM_VIDEO_SOURCES})
    set(HAVE_SDL_VIDEO TRUE)

    #enable gles
    if(VIDEO_OPENGLES)
      set(SDL_VIDEO_OPENGL_EGL 1)
      set(HAVE_VIDEO_OPENGLES TRUE)
      set(SDL_VIDEO_OPENGL_ES2 1)
      set(SDL_VIDEO_RENDER_OGL_ES2 1)
    endif()
  endif()
elseif(UNIX AND NOT APPLE)
  if(SDL_AUDIO)
    if(SYSV5 OR SOLARIS OR HPUX)
        set(SDL_AUDIO_DRIVER_SUNAUDIO 1)
        file(GLOB SUN_AUDIO_SOURCES ${SDL2_SOURCE_DIR}/src/audio/sun/*.c)
        set(SOURCE_FILES ${SOURCE_FILES} ${SUN_AUDIO_SOURCES})
        set(HAVE_SDL_AUDIO TRUE)
    elseif(NETBSD OR OPENBSD)
        set(SDL_AUDIO_DRIVER_BSD 1)
        file(GLOB BSD_AUDIO_SOURCES ${SDL2_SOURCE_DIR}/src/audio/bsd/*.c)
        set(SOURCE_FILES ${SOURCE_FILES} ${BSD_AUDIO_SOURCES})
        set(HAVE_SDL_AUDIO TRUE)
    elseif(AIX)
        set(SDL_AUDIO_DRIVER_PAUDIO 1)
        file(GLOB AIX_AUDIO_SOURCES ${SDL2_SOURCE_DIR}/src/audio/paudio/*.c)
        set(SOURCE_FILES ${SOURCE_FILES} ${AIX_AUDIO_SOURCES})
        set(HAVE_SDL_AUDIO TRUE)
    endif()
    CheckOSS()
    CheckALSA()
    CheckPulseAudio()
    CheckESD()
    CheckARTS()
    CheckNAS()
    CheckSNDIO()
    CheckFusionSound()
  endif()

  if(SDL_VIDEO)
    # Need to check for Raspberry PI first and add platform specific compiler flags, otherwise the test for GLES fails!
    CheckRPI()
    CheckX11()
    CheckMir()
    CheckDirectFB()
    CheckOpenGLX11()
    CheckOpenGLESX11()
    CheckWayland()
    CheckVivante()
  endif()

  # Urho3D - bug fix - CMake only supports 'Android' as a platform since 3.1.0, prior to that version the CMake/Android toolchain has to masquerade it as 'Linux' platform
  #          So, we have to make sure Linux input event handling is not being enabled for Android platform when older CMake is used
  if(LINUX AND NOT ANDROID)
    check_c_source_compiles("
        #include <linux/input.h>
        #ifndef EVIOCGNAME
        #error EVIOCGNAME() ioctl not available
        #endif
        int main(int argc, char** argv) {}" HAVE_INPUT_EVENTS)

    check_c_source_compiles("
        #include <linux/kd.h>
        #include <linux/keyboard.h>

        int main(int argc, char **argv)
        {
            struct kbentry kbe;
            kbe.kb_table = KG_CTRL;
            ioctl(0, KDGKBENT, &kbe);
        }" HAVE_INPUT_KD)

    file(GLOB CORE_SOURCES ${SDL2_SOURCE_DIR}/src/core/linux/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${CORE_SOURCES})

    if(HAVE_INPUT_EVENTS)
      set(SDL_INPUT_LINUXEV 1)
    endif()

    if(SDL_HAPTIC AND HAVE_INPUT_EVENTS)
      set(SDL_HAPTIC_LINUX 1)
      file(GLOB HAPTIC_SOURCES ${SDL2_SOURCE_DIR}/src/haptic/linux/*.c)
      set(SOURCE_FILES ${SOURCE_FILES} ${HAPTIC_SOURCES})
      set(HAVE_SDL_HAPTIC TRUE)
    endif()

    if(HAVE_INPUT_KD)
      set(SDL_INPUT_LINUXKD 1)
    endif()

    # Urho3D - bug fix - when cross-compiling the headers are rooted, either use "--sysroot" compiler flag or use CMAKE_REQUIRED_INCLUDES (e.g. on RPI) to cater for it
    set (CMAKE_REQUIRED_INCLUDES_UDEV_DBUS_SAVED ${CMAKE_REQUIRED_INCLUDES})
    if (CMAKE_CROSSCOMPILING AND NOT "${CMAKE_C_FLAGS} ${CMAKE_REQUIRED_FLAGS}" MATCHES sysroot)
      find_path (UDEV_H_INCLUDE_DIRS libudev.h)
      if (UDEV_H_INCLUDE_DIRS)
        list (APPEND CMAKE_REQUIRED_INCLUDES ${UDEV_H_INCLUDE_DIRS} ${SYS_TYPES_H_INCLUDE_DIRS})
      endif ()
    endif ()
    check_include_file("libudev.h" HAVE_LIBUDEV_H)
    if (HAVE_LIBUDEV_H AND UDEV_H_INCLUDE_DIRS)
      include_directories (${UDEV_H_INCLUDE_DIRS})
    endif ()
    # Urho3D - bug fix - dbus/dbus.h is installed under path suffix 'dbus-1.0', so the following find_path() is needed even when not cross-compiling
    find_path (DBUS_H_INCLUDE_DIRS NAMES dbus/dbus.h PATH_SUFFIXES dbus-1.0)
    # Cater for both 32/64bit Redhat-based/Debian-based distros and 32-bit Raspberry-Pi as dbus-arch-deps header search paths are a little bit unusual
    # FIXME: Is there a better way than hardcoding these?
    if (URHO3D_64BIT)
      set (DBUS_INC_SEARCH_PATH /usr/lib64/dbus-1.0/include /usr/lib/x86_64-linux-gnu/dbus-1.0/include)
    else ()
      set (DBUS_INC_SEARCH_PATH /usr/lib/dbus-1.0/include /usr/lib/i386-linux-gnu/dbus-1.0/include /usr/lib/arm-linux-gnueabihf/dbus-1.0/include)
    endif ()
    find_path (DBUS_ARCH_DEPS_H_INCLUDE_DIRS NAMES dbus/dbus-arch-deps.h PATHS ${DBUS_INC_SEARCH_PATH})
    set (CMAKE_REQUIRED_INCLUDES ${CMAKE_REQUIRED_INCLUDES_UDEV_DBUS_SAVED} ${DBUS_H_INCLUDE_DIRS} ${DBUS_ARCH_DEPS_H_INCLUDE_DIRS})
    check_include_file("dbus/dbus.h" HAVE_DBUS_DBUS_H)
    if (HAVE_DBUS_DBUS_H AND DBUS_H_INCLUDE_DIRS AND DBUS_ARCH_DEPS_H_INCLUDE_DIRS)
      include_directories (${DBUS_H_INCLUDE_DIRS} ${DBUS_ARCH_DEPS_H_INCLUDE_DIRS})
    endif ()
    set (CMAKE_REQUIRED_INCLUDES ${CMAKE_REQUIRED_INCLUDES_UDEV_DBUS_SAVED})

    # Urho3D - bug fix - moved below logic from generic Unix block to Linux-specific block; this also prevents Linux power management from being enabled for Android platform when CMake prior to 3.1.0 is used
    if(SDL_POWER)
      set(SDL_POWER_LINUX 1)
      file(GLOB POWER_SOURCES ${SDL2_SOURCE_DIR}/src/power/linux/*.c)
      set(SOURCE_FILES ${SOURCE_FILES} ${POWER_SOURCES})
      set(HAVE_SDL_POWER TRUE)
    endif()
  endif()

  if(INPUT_TSLIB)
    # Urho3D - bug fix - when cross-compiling the headers are rooted, either use "--sysroot" compiler flag or use CMAKE_REQUIRED_INCLUDES (e.g. on RPI) to cater for it
    set (CMAKE_REQUIRED_INCLUDES_TSLIB_SAVED ${CMAKE_REQUIRED_INCLUDES})
    if (CMAKE_CROSSCOMPILING AND NOT "${CMAKE_C_FLAGS} ${CMAKE_REQUIRED_FLAGS}" MATCHES sysroot)
      find_path (TSLIB_H_INCLUDE_DIRS NAMES tslib.h)
      if (TSLIB_H_INCLUDE_DIRS)
        # Assume the header search path has not been adjusted elsewhere yet, there is no harm anyway when a same entry is added twice into the list
        list (APPEND CMAKE_REQUIRED_INCLUDES ${TSLIB_H_INCLUDE_DIRS})
      endif ()
    endif ()
    check_include_file (tslib.h HAVE_INPUT_TSLIB)
    if(HAVE_INPUT_TSLIB)
      set(SDL_INPUT_TSLIB 1)
      list(APPEND EXTRA_LIBS ts)
    endif()
    set (CMAKE_REQUIRED_INCLUDES ${CMAKE_REQUIRED_INCLUDES_TSLIB_SAVED})
  endif()

  if(SDL_JOYSTICK)
    CheckUSBHID()   # seems to be BSD specific - limit the test to BSD only?
    if(LINUX AND NOT ANDROID)
      set(SDL_JOYSTICK_LINUX 1)
      file(GLOB JOYSTICK_SOURCES ${SDL2_SOURCE_DIR}/src/joystick/linux/*.c)
      set(SOURCE_FILES ${SOURCE_FILES} ${JOYSTICK_SOURCES})
      set(HAVE_SDL_JOYSTICK TRUE)
    endif()
  endif()

  CheckPTHREAD()

  if(CLOCK_GETTIME)
    check_library_exists(rt clock_gettime "" FOUND_CLOCK_GETTIME)
    if(FOUND_CLOCK_GETTIME)
      list(APPEND EXTRA_LIBS rt)
      set(HAVE_CLOCK_GETTIME 1)
    else()
      check_library_exists(c clock_gettime "" FOUND_CLOCK_GETTIME)
      if(FOUND_CLOCK_GETTIME)
        set(HAVE_CLOCK_GETTIME 1)
      endif()
    endif()
  endif()

  # Urho3D - commented out setting of HAVE_LINUX_VERSION_H compiler define via cflags as that define is not being used at all, besides we prefer add_definitions()

  # Urho3D - bug fix - do not use Unix filesystem for Android platform
  if(SDL_FILESYSTEM AND NOT ANDROID)
    set(SDL_FILESYSTEM_UNIX 1)
    file(GLOB FILESYSTEM_SOURCES ${SDL2_SOURCE_DIR}/src/filesystem/unix/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${FILESYSTEM_SOURCES})
    set(HAVE_SDL_FILESYSTEM TRUE)
  endif()

  if(SDL_TIMERS)
    set(SDL_TIMER_UNIX 1)
    file(GLOB TIMER_SOURCES ${SDL2_SOURCE_DIR}/src/timer/unix/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${TIMER_SOURCES})
    set(HAVE_SDL_TIMERS TRUE)
  endif()

  if(RPATH)
    set(SDL_RLD_FLAGS "")
    if(BSDI OR FREEBSD OR LINUX OR NETBSD)
      set(SDL_RLD_FLAGS "-Wl,-rpath,\${libdir}")
    elseif(SOLARIS)
      set(SDL_RLD_FLAGS "-R\${libdir}")
    endif()
    # Urho3D - commented out RPATH setup as we have configured ours globally
    set(HAVE_RPATH TRUE)
  endif()

elseif(WINDOWS)
  # Urho3D - bug fix - when using MinGW in cross-compiling build, the windres tool is being prefixed as other GCC cross-compiling tools
  if (MINGW)
    if (CMAKE_CROSSCOMPILING)
      set (WINDRES ${CMAKE_RC_COMPILER})  # The CMAKE_RC_COMPILER variable is already initialized in our CMake/MinGW toolchain file
    else ()
      find_program(WINDRES windres)
    endif ()
  endif ()

  # Urho3D - replace the windows.h check by using check_include_file() instead of check_c_source_files()
  check_include_file (windows.h HAVE_WIN32_CC)

  file(GLOB CORE_SOURCES ${SDL2_SOURCE_DIR}/src/core/windows/*.c)
  set(SOURCE_FILES ${SOURCE_FILES} ${CORE_SOURCES})

  # Urho3D - commented out MSVC-specific compiler flags setup as we have configured MSVC compiler flags globally in Urho3D common module

  # Check for DirectX
  if(DIRECTX)
    # Urho3D - bug fix - use our own FindDirectX.cmake module which does not rely on DXSDK_DIR environment variable directly when DirectX SDK is being used
    # Urho3D - TODO - move the find_package(DirectX) call from Urho3D common module to here later after we have refactored the library dependency handling
  endif()

  if(SDL_AUDIO)
    set(SDL_AUDIO_DRIVER_WINMM 1)
    file(GLOB WINMM_AUDIO_SOURCES ${SDL2_SOURCE_DIR}/src/audio/winmm/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${WINMM_AUDIO_SOURCES})
    set(HAVE_SDL_AUDIO TRUE)

    if(HAVE_DSOUND_H)
      set(SDL_AUDIO_DRIVER_DSOUND 1)
      file(GLOB DSOUND_AUDIO_SOURCES ${SDL2_SOURCE_DIR}/src/audio/directsound/*.c)
      set(SOURCE_FILES ${SOURCE_FILES} ${DSOUND_AUDIO_SOURCES})
    endif()

    if(HAVE_XAUDIO2_H)
      set(SDL_AUDIO_DRIVER_XAUDIO2 1)
      file(GLOB XAUDIO2_AUDIO_SOURCES ${SDL2_SOURCE_DIR}/src/audio/xaudio2/*.c)
      set(SOURCE_FILES ${SOURCE_FILES} ${XAUDIO2_AUDIO_SOURCES})
    endif()
  endif()

  if(SDL_VIDEO)
    # requires SDL_LOADSO on Windows (IME, DX, etc.)
    if(NOT SDL_LOADSO)
      message_error("SDL_VIDEO requires SDL_LOADSO, which is not enabled")
    endif()
    set(SDL_VIDEO_DRIVER_WINDOWS 1)
    file(GLOB WIN_VIDEO_SOURCES ${SDL2_SOURCE_DIR}/src/video/windows/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${WIN_VIDEO_SOURCES})

    if(RENDER_D3D AND HAVE_D3D_H)
      set(SDL_VIDEO_RENDER_D3D 1)
      set(HAVE_RENDER_D3D TRUE)
    endif()
    if(RENDER_D3D AND HAVE_D3D11_H)
      set(SDL_VIDEO_RENDER_D3D11 1)
      set(HAVE_RENDER_D3D TRUE)
    endif()
    set(HAVE_SDL_VIDEO TRUE)
    # Urho3D - bug fix - we are going to need this later when we refactor the library dependency handling
    list (APPEND EXTRA_LIBS ${DIRECT3D_LIBRARIES})    # Empty when none of the D3D components is used
  endif()

  if(SDL_THREADS)
    set(SDL_THREAD_WINDOWS 1)
    set(SOURCE_FILES ${SOURCE_FILES}
      ${SDL2_SOURCE_DIR}/src/thread/windows/SDL_sysmutex.c
      ${SDL2_SOURCE_DIR}/src/thread/windows/SDL_syssem.c
      ${SDL2_SOURCE_DIR}/src/thread/windows/SDL_systhread.c
      ${SDL2_SOURCE_DIR}/src/thread/windows/SDL_systls.c
      ${SDL2_SOURCE_DIR}/src/thread/generic/SDL_syscond.c)
    set(HAVE_SDL_THREADS TRUE)
  endif()

  if(SDL_POWER)
    set(SDL_POWER_WINDOWS 1)
    set(SOURCE_FILES ${SOURCE_FILES} ${SDL2_SOURCE_DIR}/src/power/windows/SDL_syspower.c)
    set(HAVE_SDL_POWER TRUE)
  endif()

  if(SDL_FILESYSTEM)
    set(SDL_FILESYSTEM_WINDOWS 1)
    file(GLOB FILESYSTEM_SOURCES ${SDL2_SOURCE_DIR}/src/filesystem/windows/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${FILESYSTEM_SOURCES})
    set(HAVE_SDL_FILESYSTEM TRUE)
  endif()

  # Libraries for Win32 native and MinGW
  list(APPEND EXTRA_LIBS user32 gdi32 winmm imm32 ole32 oleaut32 version uuid)

  # TODO: in configure.in the check for timers is set on
  # cygwin | mingw32* - does this include mingw32CE?
  if(SDL_TIMERS)
    set(SDL_TIMER_WINDOWS 1)
    file(GLOB TIMER_SOURCES ${SDL2_SOURCE_DIR}/src/timer/windows/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${TIMER_SOURCES})
    set(HAVE_SDL_TIMERS TRUE)
  endif()

  if(SDL_LOADSO)
    set(SDL_LOADSO_WINDOWS 1)
    file(GLOB LOADSO_SOURCES ${SDL2_SOURCE_DIR}/src/loadso/windows/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${LOADSO_SOURCES})
    set(HAVE_SDL_LOADSO TRUE)
  endif()

  file(GLOB CORE_SOURCES ${SDL2_SOURCE_DIR}/src/core/windows/*.c)
  set(SOURCE_FILES ${SOURCE_FILES} ${CORE_SOURCES})

  if(SDL_VIDEO)
    if(VIDEO_OPENGL)
      set(SDL_VIDEO_OPENGL 1)
      set(SDL_VIDEO_OPENGL_WGL 1)
      set(SDL_VIDEO_RENDER_OGL 1)
      set(HAVE_VIDEO_OPENGL TRUE)
    endif()

    if(VIDEO_OPENGLES)
      set(SDL_VIDEO_OPENGL_EGL 1)
      set(SDL_VIDEO_OPENGL_ES2 1)
      set(SDL_VIDEO_RENDER_OGL_ES2 1)
      set(HAVE_VIDEO_OPENGLES TRUE)
    endif()
  endif()

  if(SDL_JOYSTICK)
    file(GLOB JOYSTICK_SOURCES ${SDL2_SOURCE_DIR}/src/joystick/windows/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${JOYSTICK_SOURCES})
    if(HAVE_DINPUT_H)
      set(SDL_JOYSTICK_DINPUT 1)
      list(APPEND EXTRA_LIBS dinput8 dxguid)
      if(CMAKE_COMPILER_IS_MINGW)
        list(APPEND EXTRA_LIBS dxerr8)
      elseif (NOT USE_WINSDK_DIRECTX)
        list(APPEND EXTRA_LIBS dxerr)
      endif()
    endif()
    if(HAVE_XINPUT_H)
      set(SDL_JOYSTICK_XINPUT 1)
    endif()
    if(NOT HAVE_DINPUT_H AND NOT HAVE_XINPUT_H)
      set(SDL_JOYSTICK_WINMM 1)
    endif()
    set(HAVE_SDL_JOYSTICK TRUE)

    if(SDL_HAPTIC)
      if(HAVE_DINPUT_H OR HAVE_XINPUT_H)
        file(GLOB HAPTIC_SOURCES ${SDL2_SOURCE_DIR}/src/haptic/windows/*.c)
        if(HAVE_DINPUT_H)
          set(SDL_HAPTIC_DINPUT 1)
        endif()
        if(HAVE_XINPUT_H)
          set(SDL_HAPTIC_XINPUT 1)
        endif()
      else()
        file(GLOB HAPTIC_SOURCES ${SDL2_SOURCE_DIR}/src/haptic/dummy/*.c)
        set(SDL_HAPTIC_DUMMY 1)
      endif()
      set(SOURCE_FILES ${SOURCE_FILES} ${HAPTIC_SOURCES})
      set(HAVE_SDL_HAPTIC TRUE)
    endif()
  endif()

  # Urho3D - commented out adding main entry point for Windows platform
  # Urho3D - commented out '-mwindows' linker flags setup as it appears to be automatically added by CMake; also commented out 'mingw32' library dependency as it does not appear to be needed, at least that the case for MinGW
elseif(APPLE)
  # TODO: rework this for proper MacOS X, iOS and Darwin support

  # Requires the darwin file implementation
  if(SDL_FILE)
    file(GLOB EXTRA_SOURCES ${SDL2_SOURCE_DIR}/src/file/cocoa/*.m)
    set(SOURCE_FILES ${EXTRA_SOURCES} ${SOURCE_FILES})
    set_source_files_properties(${EXTRA_SOURCES} PROPERTIES LANGUAGE C)
    set(HAVE_SDL_FILE TRUE)
    set(SDL_FRAMEWORK_COCOA 1)
    set(SDL_FRAMEWORK_COREVIDEO 1)
  else()
    message_error("SDL_FILE must be enabled to build on MacOS X")
  endif()

  if(SDL_AUDIO)
    set(SDL_AUDIO_DRIVER_COREAUDIO 1)
    file(GLOB AUDIO_SOURCES ${SDL2_SOURCE_DIR}/src/audio/coreaudio/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${AUDIO_SOURCES})
    set(HAVE_SDL_AUDIO TRUE)
    set(SDL_FRAMEWORK_COREAUDIO 1)
    set(SDL_FRAMEWORK_AUDIOUNIT 1)
  endif()

  if(SDL_JOYSTICK)
    set(SDL_JOYSTICK_IOKIT 1)
    file(GLOB JOYSTICK_SOURCES ${SDL2_SOURCE_DIR}/src/joystick/darwin/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${JOYSTICK_SOURCES})
    set(HAVE_SDL_JOYSTICK TRUE)
    set(SDL_FRAMEWORK_IOKIT 1)
    set(SDL_FRAMEWORK_FF 1)
  endif()

  if(SDL_HAPTIC)
    set(SDL_HAPTIC_IOKIT 1)
    file(GLOB HAPTIC_SOURCES ${SDL2_SOURCE_DIR}/src/haptic/darwin/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${HAPTIC_SOURCES})
    set(HAVE_SDL_HAPTIC TRUE)
    set(SDL_FRAMEWORK_IOKIT 1)
    set(SDL_FRAMEWORK_FF 1)
    if(NOT SDL_JOYSTICK)
      message(FATAL_ERROR "SDL_HAPTIC requires SDL_JOYSTICK to be enabled")
    endif()
  endif()

  if(SDL_POWER)
    set(SDL_POWER_MACOSX 1)
    file(GLOB POWER_SOURCES ${SDL2_SOURCE_DIR}/src/power/macosx/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${POWER_SOURCES})
    set(HAVE_SDL_POWER TRUE)
    set(SDL_FRAMEWORK_CARBON 1)
    set(SDL_FRAMEWORK_IOKIT 1)
  endif()

  if(SDL_TIMERS)
    set(SDL_TIMER_UNIX 1)
    file(GLOB TIMER_SOURCES ${SDL2_SOURCE_DIR}/src/timer/unix/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${TIMER_SOURCES})
    set(HAVE_SDL_TIMERS TRUE)
  endif(SDL_TIMERS)

  if(SDL_FILESYSTEM)
    set(SDL_FILESYSTEM_COCOA 1)
    file(GLOB FILESYSTEM_SOURCES ${SDL2_SOURCE_DIR}/src/filesystem/cocoa/*.m)
    set_source_files_properties(${FILESYSTEM_SOURCES} PROPERTIES LANGUAGE C)
    set(SOURCE_FILES ${SOURCE_FILES} ${FILESYSTEM_SOURCES})
    set(HAVE_SDL_FILESYSTEM TRUE)
  endif()

  # Actually load the frameworks at the end so we don't duplicate include.
  # Urho3D - TODO - this list in complete, do this when we refactor the library dependency handling
  if(SDL_FRAMEWORK_COREVIDEO)
    find_library(COREVIDEO CoreVideo)
    list(APPEND EXTRA_LIBS ${COREVIDEO})
  endif()
  if(SDL_FRAMEWORK_COCOA)
    find_library(COCOA_LIBRARY Cocoa)
    list(APPEND EXTRA_LIBS ${COCOA_LIBRARY})
  endif()
  if(SDL_FRAMEWORK_IOKIT)
    find_library(IOKIT IOKit)
    list(APPEND EXTRA_LIBS ${IOKIT})
  endif()
  if(SDL_FRAMEWORK_FF)
    find_library(FORCEFEEDBACK ForceFeedback)
    list(APPEND EXTRA_LIBS ${FORCEFEEDBACK})
  endif()
  if(SDL_FRAMEWORK_CARBON)
    find_library(CARBON_LIBRARY Carbon)
    list(APPEND EXTRA_LIBS ${CARBON_LIBRARY})
  endif()
  if(SDL_FRAMEWORK_COREAUDIO)
    find_library(COREAUDIO CoreAudio)
    list(APPEND EXTRA_LIBS ${COREAUDIO})
  endif()
  if(SDL_FRAMEWORK_AUDIOUNIT)
    find_library(AUDIOUNIT AudioUnit)
    list(APPEND EXTRA_LIBS ${AUDIOUNIT})
  endif()

  # iOS hack needed - http://code.google.com/p/ios-cmake/ ?
  if(SDL_VIDEO)
    CheckCOCOA()
    if(VIDEO_OPENGL)
      set(SDL_VIDEO_OPENGL 1)
      set(SDL_VIDEO_OPENGL_CGL 1)
      set(SDL_VIDEO_RENDER_OGL 1)
      set(HAVE_VIDEO_OPENGL TRUE)
    endif()
  endif()

  CheckPTHREAD()
elseif(HAIKU)
  if(SDL_VIDEO)
    set(SDL_VIDEO_DRIVER_HAIKU 1)
    file(GLOB HAIKUVIDEO_SOURCES ${SDL2_SOURCE_DIR}/src/video/haiku/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${HAIKUVIDEO_SOURCES})
    set(HAVE_SDL_VIDEO TRUE)

    set(SDL_FILESYSTEM_HAIKU 1)
    file(GLOB FILESYSTEM_SOURCES ${SDL2_SOURCE_DIR}/src/filesystem/haiku/*.cc)
    set(SOURCE_FILES ${SOURCE_FILES} ${FILESYSTEM_SOURCES})
    set(HAVE_SDL_FILESYSTEM TRUE)

    if(SDL_TIMERS)
      set(SDL_TIMER_HAIKU 1)
      file(GLOB TIMER_SOURCES ${SDL2_SOURCE_DIR}/src/timer/haiku/*.c)
      set(SOURCE_FILES ${SOURCE_FILES} ${TIMER_SOURCES})
      set(HAVE_SDL_TIMERS TRUE)
    endif(SDL_TIMERS)

    if(VIDEO_OPENGL)
      # TODO: Use FIND_PACKAGE(OpenGL) instead
      set(SDL_VIDEO_OPENGL 1)
      set(SDL_VIDEO_OPENGL_BGL 1)
      set(SDL_VIDEO_RENDER_OGL 1)
      list(APPEND EXTRA_LIBS GL)
      set(HAVE_VIDEO_OPENGL TRUE)
    endif()
  endif()

  CheckPTHREAD()
endif()

# Dummies
# configure.in does it differently:
# if not have X
#   if enable_X {  SDL_X_DISABLED = 1 }
#   [add dummy sources]
# so it always adds a dummy, without checking, if it was actually requested.
# This leads to missing internal references on building, since the
# src/X/*.c does not get included.
if(NOT HAVE_SDL_JOYSTICK)
  set(SDL_JOYSTICK_DISABLED 1)
  if(SDL_JOYSTICK AND NOT APPLE) # results in unresolved symbols on OSX

    file(GLOB JOYSTICK_SOURCES ${SDL2_SOURCE_DIR}/src/joystick/dummy/*.c)
    set(SOURCE_FILES ${SOURCE_FILES} ${JOYSTICK_SOURCES})
  endif()
endif()
if(NOT HAVE_SDL_HAPTIC)
  set(SDL_HAPTIC_DISABLED 1)
  file(GLOB HAPTIC_SOURCES ${SDL2_SOURCE_DIR}/src/haptic/dummy/*.c)
  set(SOURCE_FILES ${SOURCE_FILES} ${HAPTIC_SOURCES})
endif()
if(NOT HAVE_SDL_LOADSO)
  set(SDL_LOADSO_DISABLED 1)
  file(GLOB LOADSO_SOURCES ${SDL2_SOURCE_DIR}/src/loadso/dummy/*.c)
  set(SOURCE_FILES ${SOURCE_FILES} ${LOADSO_SOURCES})
endif()
if(NOT HAVE_SDL_FILESYSTEM)
  set(SDL_FILESYSTEM_DISABLED 1)
  file(GLOB FILESYSTEM_SOURCES ${SDL2_SOURCE_DIR}/src/filesystem/dummy/*.c)
  set(SOURCE_FILES ${SOURCE_FILES} ${FILESYSTEM_SOURCES})
endif()

# We always need to have threads and timers around
if(NOT HAVE_SDL_THREADS)
  set(SDL_THREADS_DISABLED 1)
  file(GLOB THREADS_SOURCES ${SDL2_SOURCE_DIR}/src/thread/generic/*.c)
  set(SOURCE_FILES ${SOURCE_FILES} ${THREADS_SOURCES})
endif()
if(NOT HAVE_SDL_TIMERS)
  set(SDL_TIMERS_DISABLED 1)
  file(GLOB TIMER_SOURCES ${SDL2_SOURCE_DIR}/src/timer/dummy/*.c)
  set(SOURCE_FILES ${SOURCE_FILES} ${TIMER_SOURCES})
endif()

# Urho3D - commented out inclusion of dummy main

# Append the -MMD -MT flags
# if(DEPENDENCY_TRACKING)
#   if(COMPILER_IS_GNUCC)
#     set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -MMD -MT \$@")
#   endif()
# endif()

# Urho3D - use 'generated' path suffix for generated config header file (need the suffix as we support both out-of-source in-source build tree)
configure_file("${SDL2_SOURCE_DIR}/include/SDL_config.h.cmake"
  "${SDL2_BINARY_DIR}/include/generated/SDL_config.h")

# Prepare the flags and remove duplicates
if(EXTRA_LDFLAGS)
  list(REMOVE_DUPLICATES EXTRA_LDFLAGS)
endif()
if(EXTRA_LIBS)
  list(REMOVE_DUPLICATES EXTRA_LIBS)
endif()
if(EXTRA_CFLAGS)
  list(REMOVE_DUPLICATES EXTRA_CFLAGS)
endif()
listtostr(EXTRA_CFLAGS _EXTRA_CFLAGS)
set(EXTRA_CFLAGS ${_EXTRA_CFLAGS})

# Compat helpers for the configuration files
if(NOT WINDOWS OR CYGWIN)
  # Urho3D - commeted out the call to updaterev.sh script as it won't work on any platform as it assumes hg to be the version source control which is not true in our case

  set(prefix ${CMAKE_INSTALL_PREFIX})
  set(exec_prefix "\${prefix}")
  set(libdir "\${exec_prefix}/lib${LIB_SUFFIX}")
  set(bindir "\${exec_prefix}/bin")
  set(includedir "\${prefix}/include")
  if(SDL_STATIC)
    set(ENABLE_STATIC_TRUE "")
    set(ENABLE_STATIC_FALSE "#")
  else()
    set(ENABLE_STATIC_TRUE "#")
    set(ENABLE_STATIC_FALSE "")
  endif()
  if(SDL_SHARED)
    set(ENABLE_SHARED_TRUE "")
    set(ENABLE_SHARED_FALSE "#")
  else()
    set(ENABLE_SHARED_TRUE "#")
    set(ENABLE_SHARED_FALSE "")
  endif()

  # Clean up the different lists
  listtostr(EXTRA_LIBS _EXTRA_LIBS "-l")
  set(SDL_STATIC_LIBS ${SDL_LIBS} ${EXTRA_LDFLAGS} ${_EXTRA_LIBS})
  list(REMOVE_DUPLICATES SDL_STATIC_LIBS)
  listtostr(SDL_STATIC_LIBS _SDL_STATIC_LIBS)
  set(SDL_STATIC_LIBS ${_SDL_STATIC_LIBS})
  listtostr(SDL_LIBS _SDL_LIBS)
  set(SDL_LIBS ${_SDL_LIBS})

  # Urho3D - commented out pkg-config configuration file generation
  # Urho3D - TODO - utilize the populated variables for pkg-config configuration file generation for Urho3D.pc
endif()

# Urho3D - restore the original CMake global settings
set (CMAKE_REQUIRED_FLAGS ${ORIG_CMAKE_REQUIRED_FLAGS})
set (CMAKE_REQUIRED_INCLUDES ${ORIG_CMAKE_REQUIRED_INCLUDES})
set (CMAKE_REQUIRED_LIBRARIES ${ORIG_CMAKE_REQUIRED_LIBRARIES})

# Urho3D - only echo the status once during initial configuration
if (NOT SDL_INFO_ECHOED_STATUS)
  set (SDL_INFO_ECHOED_STATUS TRUE CACHE INTERNAL "SDL info echoed status")
##### Info output #####
message(STATUS "")
message(STATUS "SDL2 was configured with the following options:")
message(STATUS "")
message(STATUS "Platform: ${CMAKE_SYSTEM}")
message(STATUS "64-bit:   ${ARCH_64}")
message(STATUS "Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "")
message(STATUS "Subsystems:")
foreach(_SUB ${SDL_SUBSYSTEMS})
  string(TOUPPER ${_SUB} _OPT)
  # Urho3D - use the same amount of spaces for padding
  string(LENGTH ${_SUB} _SUBLEN)
  math(EXPR _PADLEN "11 - ${_SUBLEN}")
  string(RANDOM LENGTH ${_PADLEN} ALPHABET " " _PADDING)
  message_bool_option(${_SUB} SDL_${_OPT} ${_PADDING})
endforeach()
message(STATUS "")
message(STATUS "Options:")
list(SORT ALLOPTIONS)
foreach(_OPT ${ALLOPTIONS})
  # Longest option is VIDEO_X11_XSCREENSAVER = 22 characters
  # Get the padding
  string(LENGTH ${_OPT} _OPTLEN)
  math(EXPR _PADLEN "23 - ${_OPTLEN}")
  string(RANDOM LENGTH ${_PADLEN} ALPHABET " " _PADDING)
  message_tested_option(${_OPT} ${_PADDING})
endforeach()
message(STATUS "")
message(STATUS " CFLAGS:        ${CMAKE_C_FLAGS}")
message(STATUS " EXTRA_CFLAGS:  ${EXTRA_CFLAGS}")
message(STATUS " EXTRA_LDFLAGS: ${EXTRA_LDFLAGS}")
message(STATUS " EXTRA_LIBS:    ${EXTRA_LIBS}")
message(STATUS "")
message(STATUS " Build Shared Library: ${SDL_SHARED}")
message(STATUS " Build Static Library: ${SDL_STATIC}")
message(STATUS "")
# Urho3D - commented out messages informing user to set the CFLAGS and LDFLAGS environment variables to workaround detection problems, our modified version does not support that
endif (NOT SDL_INFO_ECHOED_STATUS)

# Ensure that the extra cflags are used at compile time
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS}")

# Urho3D - commented out targets defined by original CMakeLists.txt, instead we setup our own target that meets our own needs

# Urho3D - use Emscripten's own SDL2 port
if (WEB)
  # Emscripten has its own SDL2 port, so just create a custom target to:
  #  1) Fetch this SDL2 port from its GitHub repository
  #  2) Install SDL2 headers to the build tree in the post-build step (Note: current configuration uses our own SDL2 header files instead of the ones provided by Emscripten port for no special reason)
  # Note that we still have to go through the whole detection logic so that we could generate SDL_config.h correctly
  add_custom_target (${TARGET_NAME} ALL ${CMAKE_COMMAND} -E touch dummy.cpp && ${CMAKE_CXX_COMPILER} -s USE_SDL=2 -o dummy.html dummy.cpp && ${CMAKE_COMMAND} -E remove dummy.*)
  set (STATIC_LIBRARY_TARGETS ${STATIC_LIBRARY_TARGETS} ${TARGET_NAME} PARENT_SCOPE)
else ()
  # Setup target as STATIC library (as the result we never use EXTRA_LDFLAGS linker flags)
  setup_library ()
endif ()

# Install headers for building and using the Urho3D library (install dependency for D3D9GraphicsImpl.h, OGLGraphicsImpl.h, InputEvents.h, File.h, and Cursor.h)
install_header_files (DIRECTORY include/ DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/SDL FILES_MATCHING PATTERN *.h USE_FILE_SYMLINK)    # Note: the trailing slash is significant
install_header_files (FILES ${SDL2_BINARY_DIR}/include/generated/SDL_config.h DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/SDL)
# Install dependency for SDL_android_main.c
if (ANDROID)
  install_header_files (DIRECTORY src/main/android DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/SDL)
  install_header_files (FILES src/SDL_internal.h DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/SDL)
  install_header_files (DIRECTORY src/dynapi DESTINATION ${DEST_INCLUDE_DIR}/ThirdParty/SDL FILES_MATCHING PATTERN *.h)
endif ()
