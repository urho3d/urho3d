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
set (CMAKE_SYSTEM_NAME Linux)
# this one not so much
set (CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
if (NOT RPI_PREFIX AND DEFINED ENV{RPI_PREFIX})
    file (TO_CMAKE_PATH $ENV{RPI_PREFIX} RPI_PREFIX)
endif ()
if (NOT EXISTS ${RPI_PREFIX}-gcc)
    message (FATAL_ERROR "Could not find Raspberry Pi cross compilation tool. "
        "Use RPI_PREFIX environment variable or build option to specify the location of the toolchain.")
endif ()
set (CMAKE_C_COMPILER   ${RPI_PREFIX}-gcc     CACHE PATH "C compiler")
set (CMAKE_CXX_COMPILER ${RPI_PREFIX}-c++     CACHE PATH "C++ compiler")
set (CMAKE_STRIP        ${RPI_PREFIX}-strip   CACHE PATH "strip")
set (CMAKE_AR           ${RPI_PREFIX}-ar      CACHE PATH "archive")
set (CMAKE_LINKER       ${RPI_PREFIX}-ld      CACHE PATH "linker")
set (CMAKE_NM           ${RPI_PREFIX}-nm      CACHE PATH "nm")
set (CMAKE_OBJCOPY      ${RPI_PREFIX}-objcopy CACHE PATH "objcopy")
set (CMAKE_OBJDUMP      ${RPI_PREFIX}-objdump CACHE PATH "objdump")
set (CMAKE_RANLIB       ${RPI_PREFIX}-ranlib  CACHE PATH "ranlib")

# specify the system root
if (NOT RPI_SYSROOT OR NOT BCM_VC_INCLUDE_DIRS OR NOT BCM_VC_LIBRARIES)
    if (DEFINED ENV{RPI_SYSROOT})
        file (TO_CMAKE_PATH $ENV{RPI_SYSROOT} RPI_SYSROOT)
    endif ()
    if (NOT EXISTS ${RPI_SYSROOT})
        message (FATAL_ERROR "Could not find Raspberry Pi system root. "
            "Use RPI_SYSROOT environment variable or build option to specify the location of system root.")
    endif ()
    set (RPI_PREFIX ${RPI_PREFIX} CACHE STRING "Prefix path to Raspberry Pi cross-compiler tools (RPI cross-compiling build only)" FORCE)
    set (RPI_SYSROOT ${RPI_SYSROOT} CACHE PATH "Path to Raspberry Pi system root (RPI cross-compiling build only)" FORCE)
endif ()
set (CMAKE_FIND_ROOT_PATH ${RPI_SYSROOT})

# only search programs, libraries, and headers in the target directories
set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
