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

# Target operating system and architecture
set (CMAKE_SYSTEM_NAME Windows)
set (CMAKE_SYSTEM_PROCESSOR x86)

# Sanitate the path
file (TO_CMAKE_PATH "$ENV{MINGW_PREFIX}" MINGW_PREFIX)

# C/C++ compilers
set (CMAKE_C_COMPILER ${MINGW_PREFIX}-gcc      CACHE PATH "C compiler")
set (CMAKE_CXX_COMPILER ${MINGW_PREFIX}-g++    CACHE PATH "C++ compiler")
set (CMAKE_RC_COMPILER ${MINGW_PREFIX}-windres CACHE PATH "RC compiler")

# specify the system root
file (TO_CMAKE_PATH "$ENV{MINGW_ROOT}" MINGW_ROOT)
if (NOT MINGW_ROOT)
    get_filename_component (MINGW_PREFIX ${MINGW_PREFIX} NAME)
    set (MINGW_ROOT /usr/${MINGW_PREFIX}/sys-root/mingw)
endif ()
set (MINGW_SYSROOT ${MINGW_ROOT} CACHE PATH "Path to MinGW SYSROOT")
set (CMAKE_FIND_ROOT_PATH ${MINGW_SYSROOT})

# only search libraries and headers in the target directories
set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
