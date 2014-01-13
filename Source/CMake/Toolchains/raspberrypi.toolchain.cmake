#
# Copyright (c) 2008-2013 the Urho3D project.
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
file (TO_CMAKE_PATH "$ENV{RASPI_TOOL}" RASPI_TOOL)
set (CMAKE_C_COMPILER   ${RASPI_TOOL}/arm-linux-gnueabihf-gcc     CACHE PATH "C compiler")
set (CMAKE_CXX_COMPILER ${RASPI_TOOL}/arm-linux-gnueabihf-c++     CACHE PATH "C++ compiler")
set (CMAKE_ASM_COMPILER ${RASPI_TOOL}/arm-linux-gnueabihf-gcc     CACHE PATH "assembler")
set (CMAKE_STRIP        ${RASPI_TOOL}/arm-linux-gnueabihf-strip   CACHE PATH "strip")
set (CMAKE_AR           ${RASPI_TOOL}/arm-linux-gnueabihf-ar      CACHE PATH "archive")
set (CMAKE_LINKER       ${RASPI_TOOL}/arm-linux-gnueabihf-ld      CACHE PATH "linker")
set (CMAKE_NM           ${RASPI_TOOL}/arm-linux-gnueabihf-nm      CACHE PATH "nm")
set (CMAKE_OBJCOPY      ${RASPI_TOOL}/arm-linux-gnueabihf-objcopy CACHE PATH "objcopy")
set (CMAKE_OBJDUMP      ${RASPI_TOOL}/arm-linux-gnueabihf-objdump CACHE PATH "objdump")
set (CMAKE_RANLIB       ${RASPI_TOOL}/arm-linux-gnueabihf-ranlib  CACHE PATH "ranlib")
if (NOT CMAKE_CXX_COMPILER)
    message (FATAL_ERROR "Could not find Raspberry Pi cross compilation tool. "
        "Use RASPI_TOOL environment variable to specify the location of the toolchain. "
        "Use RASPI_ROOT environment variable to specify the location of system root.")
endif ()

# specify the system root
if (NOT BCM_VC_INCLUDE_DIR)
    # Keep invalidating the cache until we found the BCM library and its include directory which hopefully also mean we have found the correct SYSROOT
    unset (RASPI_SYSROOT CACHE)
    unset (CMAKE_INSTALL_PREFIX CACHE)
endif ()
file (TO_CMAKE_PATH "$ENV{RASPI_ROOT}" RASPI_ROOT)
if (NOT RASPI_ROOT)
    set (RASPI_ROOT ${RASPI_TOOL}/../arm-linux-gnueabihf/libc)
endif ()
set (RASPI_SYSROOT ${RASPI_ROOT} CACHE PATH "Path to Raspberry Pi SYSROOT")
set (CMAKE_FIND_ROOT_PATH ${RASPI_SYSROOT})

# only search programs, libraries, and headers in the target directories
set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ONLY)
set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# setup install destination prefix path
set (CMAKE_INSTALL_PREFIX "${RASPI_SYSROOT}/usr/local" CACHE PATH "Install path prefix, prepended onto install directories.")
