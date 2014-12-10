#
# Copyright (c) 2008-2014 the Urho3D project.
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
endif ()

# this one is important
set (CMAKE_SYSTEM_NAME Linux)
#this one not so much
set (CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
file (TO_CMAKE_PATH "$ENV{RPI_TOOL}" RPI_TOOL)
if (NOT EXISTS ${RPI_TOOL}/arm-linux-gnueabihf-gcc)
    message (FATAL_ERROR "Could not find Raspberry Pi cross compilation tool. "
        "Use RPI_TOOL environment variable to specify the location of the toolchain.")
endif ()
set (CMAKE_C_COMPILER   ${RPI_TOOL}/arm-linux-gnueabihf-gcc     CACHE PATH "C compiler")
set (CMAKE_CXX_COMPILER ${RPI_TOOL}/arm-linux-gnueabihf-c++     CACHE PATH "C++ compiler")
set (CMAKE_ASM_COMPILER ${RPI_TOOL}/arm-linux-gnueabihf-gcc     CACHE PATH "assembler")
set (CMAKE_STRIP        ${RPI_TOOL}/arm-linux-gnueabihf-strip   CACHE PATH "strip")
set (CMAKE_AR           ${RPI_TOOL}/arm-linux-gnueabihf-ar      CACHE PATH "archive")
set (CMAKE_LINKER       ${RPI_TOOL}/arm-linux-gnueabihf-ld      CACHE PATH "linker")
set (CMAKE_NM           ${RPI_TOOL}/arm-linux-gnueabihf-nm      CACHE PATH "nm")
set (CMAKE_OBJCOPY      ${RPI_TOOL}/arm-linux-gnueabihf-objcopy CACHE PATH "objcopy")
set (CMAKE_OBJDUMP      ${RPI_TOOL}/arm-linux-gnueabihf-objdump CACHE PATH "objdump")
set (CMAKE_RANLIB       ${RPI_TOOL}/arm-linux-gnueabihf-ranlib  CACHE PATH "ranlib")

# specify the system root
if (NOT BCM_VC_INCLUDE_DIRS)
    # Keep invalidating the cache until we found the BCM library and its include directory which hopefully also mean we have found the correct SYSROOT
    unset (RPI_SYSROOT CACHE)
    unset (CMAKE_INSTALL_PREFIX CACHE)
    file (TO_CMAKE_PATH "$ENV{RPI_ROOT}" RPI_ROOT)
    if (NOT EXISTS ${RPI_ROOT})
        message (FATAL_ERROR "Could not find Raspberry Pi system root. "
            "Use RPI_ROOT environment variable to specify the location of system root.")
    endif ()
    set (RPI_SYSROOT ${RPI_ROOT} CACHE PATH "Path to Raspberry Pi SYSROOT")
    mark_as_advanced (RPI_SYSROOT CMAKE_TOOLCHAIN_FILE)
    set (CMAKE_FIND_ROOT_PATH ${RPI_SYSROOT})
    set (CMAKE_INSTALL_PREFIX "${RPI_SYSROOT}/usr/local" CACHE PATH "Install path prefix, prepended onto install directories.")
endif ()

# only search programs, libraries, and headers in the target directories
set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ONLY)
set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
