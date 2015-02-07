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

# Based on cmake/Modules/Platform/Emscripten.cmake from https://github.com/kripken/emscripten

cmake_minimum_required (VERSION 2.6.3)

if (CMAKE_TOOLCHAIN_FILE)
    # Reference toolchain variable to suppress "unused variable" warning
    mark_as_advanced (CMAKE_TOOLCHAIN_FILE)
endif ()

# this one is important
set (CMAKE_SYSTEM_NAME Linux)
# this one not so much
set (CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
if (NOT EMSCRIPTEN_ROOT_PATH AND DEFINED ENV{EMSCRIPTEN_ROOT_PATH})
    file (TO_CMAKE_PATH $ENV{EMSCRIPTEN_ROOT_PATH} EMSCRIPTEN_ROOT_PATH)
endif ()
if (NOT EXISTS ${EMSCRIPTEN_ROOT_PATH}/emcc)
    message (FATAL_ERROR "Could not find Emscripten cross compilation tool. "
        "Use EMSCRIPTEN_ROOT_PATH environment variable or build option to specify the location of the toolchain.")
endif ()
if (CMAKE_HOST_WIN32)
    set (TOOL_EXT .bat)
endif ()
set (CMAKE_C_COMPILER   ${EMSCRIPTEN_ROOT_PATH}/emcc${TOOL_EXT}     CACHE PATH "C compiler")
set (CMAKE_CXX_COMPILER ${EMSCRIPTEN_ROOT_PATH}/em++${TOOL_EXT}     CACHE PATH "C++ compiler")
set (CMAKE_AR           ${EMSCRIPTEN_ROOT_PATH}/emar${TOOL_EXT}     CACHE PATH "archive")
set (CMAKE_RANLIB       ${EMSCRIPTEN_ROOT_PATH}/emranlib${TOOL_EXT} CACHE PATH "ranlib")

# specify the system root
if (NOT EMSCRIPTEN_SYSROOT)
    if (DEFINED ENV{EMSCRIPTEN_SYSROOT})
        file (TO_CMAKE_PATH $ENV{EMSCRIPTEN_SYSROOT} EMSCRIPTEN_SYSROOT)
    else ()
        set (EMSCRIPTEN_SYSROOT ${EMSCRIPTEN_ROOT_PATH}/system)
    endif ()
    if (NOT EXISTS ${EMSCRIPTEN_SYSROOT})
        message (FATAL_ERROR "Could not find Emscripten system root. "
            "Use EMSCRIPTEN_SYSROOT environment variable or build option to specify the location of system root.")
    endif ()
    set (EMSCRIPTEN_ROOT_PATH ${EMSCRIPTEN_ROOT_PATH} CACHE STRING "Root path to Emscripten cross-compiler tools (Emscripten cross-compiling build only)" FORCE)
    set (EMSCRIPTEN_SYSROOT ${EMSCRIPTEN_SYSROOT} CACHE PATH "Path to Emscripten system root (Emscripten cross-compiling build only)" FORCE)
endif ()
set (CMAKE_FIND_ROOT_PATH ${EMSCRIPTEN_SYSROOT})

# only search libraries, and headers in the target directories
set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Don't do compiler autodetection, since we are cross-compiling.
include (CMakeForceCompiler)
CMAKE_FORCE_C_COMPILER ("${CMAKE_C_COMPILER}" Clang)
CMAKE_FORCE_CXX_COMPILER ("${CMAKE_CXX_COMPILER}" Clang)

# Hardwire support for cmake-2.8/Modules/CMakeBackwardsCompatibilityC.cmake without having CMake to try complex things
# to autodetect these:
set (CMAKE_SKIP_COMPATIBILITY_TESTS 1)
set (CMAKE_SIZEOF_CHAR 1)
set (CMAKE_SIZEOF_UNSIGNED_SHORT 2)
set (CMAKE_SIZEOF_SHORT 2)
set (CMAKE_SIZEOF_INT 4)
set (CMAKE_SIZEOF_UNSIGNED_LONG 4)
set (CMAKE_SIZEOF_UNSIGNED_INT 4)
set (CMAKE_SIZEOF_LONG 4)
set (CMAKE_SIZEOF_VOID_P 4)
set (CMAKE_SIZEOF_FLOAT 4)
set (CMAKE_SIZEOF_DOUBLE 8)
set (CMAKE_C_SIZEOF_DATA_PTR 4)
set (CMAKE_CXX_SIZEOF_DATA_PTR 4)
set (CMAKE_HAVE_LIMITS_H 1)
set (CMAKE_HAVE_UNISTD_H 1)
set (CMAKE_HAVE_PTHREAD_H 1)
set (CMAKE_HAVE_SYS_PRCTL_H 1)
set (CMAKE_WORDS_BIGENDIAN 0)
set (CMAKE_DL_LIBS)

# In order for check_function_exists() detection to work, we must signal it to pass an additional flag, which causes the compilation
# to abort if linking results in any undefined symbols. The CMake detection mechanism depends on the undefined symbol error to be raised.
set (CMAKE_REQUIRED_FLAGS "-s ERROR_ON_UNDEFINED_SYMBOLS=1")

# Use response files on Windows host
if (CMAKE_HOST_WIN32)
    foreach (lang C CXX)
        foreach (cat LIBRARIES OBJECTS INCLUDES)
            set (CMAKE_${lang}_USE_RESPONSE_FILE_FOR_${cat} 1)
        endforeach ()
        set (CMAKE_${lang}_CREATE_STATIC_LIBRARY "<CMAKE_AR> cr <TARGET> <LINK_FLAGS> <OBJECTS>")
    endforeach ()
endif ()

set (EMSCRIPTEN 1)
