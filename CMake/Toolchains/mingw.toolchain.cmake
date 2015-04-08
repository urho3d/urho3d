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

cmake_minimum_required (VERSION 2.6.3)

if (CMAKE_TOOLCHAIN_FILE)
    # Reference toolchain variable to suppress "unused variable" warning
    mark_as_advanced (CMAKE_TOOLCHAIN_FILE)
endif ()

# this one is important
set (CMAKE_SYSTEM_NAME Windows)
# this one not so much
set (CMAKE_SYSTEM_PROCESSOR x86)

# specify the cross compiler
if (NOT MINGW_PREFIX AND DEFINED ENV{MINGW_PREFIX})
    file (TO_CMAKE_PATH $ENV{MINGW_PREFIX} MINGW_PREFIX)
endif ()
if (NOT EXISTS ${MINGW_PREFIX}-gcc)
    message (FATAL_ERROR "Could not find MinGW cross compilation tool. "
        "Use MINGW_PREFIX environment variable or build option to specify the location of the toolchain.")
endif ()
set (CMAKE_C_COMPILER   ${MINGW_PREFIX}-gcc     CACHE PATH "C compiler")
set (CMAKE_CXX_COMPILER ${MINGW_PREFIX}-g++     CACHE PATH "C++ compiler")
set (CMAKE_STRIP        ${MINGW_PREFIX}-strip   CACHE PATH "strip")
set (CMAKE_AR           ${MINGW_PREFIX}-ar      CACHE PATH "archive")
set (CMAKE_LINKER       ${MINGW_PREFIX}-ld      CACHE PATH "linker")
set (CMAKE_NM           ${MINGW_PREFIX}-nm      CACHE PATH "nm")
set (CMAKE_OBJCOPY      ${MINGW_PREFIX}-objcopy CACHE PATH "objcopy")
set (CMAKE_OBJDUMP      ${MINGW_PREFIX}-objdump CACHE PATH "objdump")
set (CMAKE_RANLIB       ${MINGW_PREFIX}-ranlib  CACHE PATH "ranlib")
set (CMAKE_RC_COMPILER  ${MINGW_PREFIX}-windres CACHE PATH "RC compiler")

# specify the system root
if (NOT MINGW_SYSROOT)
    if (DEFINED ENV{MINGW_SYSROOT})
        file (TO_CMAKE_PATH $ENV{MINGW_SYSROOT} MINGW_SYSROOT)
    else ()
        get_filename_component (NAME ${MINGW_PREFIX} NAME)
        if (EXISTS /usr/${NAME}/sys-root)
            # Redhat based system
            set (MINGW_SYSROOT /usr/${NAME}/sys-root/mingw)
        else ()
            # Debian based system
            set (MINGW_SYSROOT /usr/${NAME})
        endif ()
    endif ()
    if (NOT EXISTS ${MINGW_SYSROOT})
        message (FATAL_ERROR "Could not find MinGW system root. "
            "Use MINGW_SYSROOT environment variable or build option to specify the location of system root.")
    endif ()
    set (MINGW_PREFIX ${MINGW_PREFIX} CACHE STRING "Prefix path to MinGW cross-compiler tools (MinGW cross-compiling build only)" FORCE)
    set (MINGW_SYSROOT ${MINGW_SYSROOT} CACHE PATH "Path to MinGW system root (MinGW cross-compiling build only)" FORCE)
endif ()
set (CMAKE_FIND_ROOT_PATH ${MINGW_SYSROOT})

# only search libraries and headers in the target directories
set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
