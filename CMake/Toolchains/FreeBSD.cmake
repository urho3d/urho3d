#
# Copyright (c) 2016-2019 Yao Wei Tjong. All rights reserved.
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

# Workaround try_compile() limitation where it cannot yet see cache variables during initial configuration
get_property (IN_TRY_COMPILE GLOBAL PROPERTY IN_TRY_COMPILE)
if (IN_TRY_COMPILE)
    foreach (VAR $ENV{VARS})
        set (${VAR} $ENV{${VAR}})
    endforeach ()
else ()
    # Prevent critical variables from changing after the initial configuration
    if (CMAKE_CROSSCOMPILING)
        set (SAVED_FREEBSD_SYSROOT ${FREEBSD_SYSROOT} CACHE INTERNAL "Initial value for FREEBSD_SYSROOT")
        # Save the initial values of CC and CXX environment variables
        set (SAVED_CC $ENV{CC} CACHE INTERNAL "Initial value for CC")
        set (SAVED_CXX $ENV{CXX} CACHE INTERNAL "Initial value for CXX")
        return ()
    elseif (SAVED_FREEBSD_SYSROOT AND NOT SAVED_FREEBSD_SYSROOT STREQUAL FREEBSD_SYSROOT)
        set (FREEBSD_SYSROOT ${SAVED_FREEBSD_SYSROOT} CACHE PATH "Path to FreeBSD system root (Linux cross-compiling build only)" FORCE)
        message (FATAL_ERROR "FREEBSD_SYSROOT cannot be changed after the initial configuration/generation. "
            "If you wish to change that then the build tree would have to be regenerated from scratch. Auto reverting to its initial value.")
    endif ()
endif ()

# Reference toolchain variable to suppress "unused variable" warning
if (CMAKE_TOOLCHAIN_FILE)
    mark_as_advanced (CMAKE_TOOLCHAIN_FILE)
endif ()

# This one is important
set (CMAKE_SYSTEM_NAME FreeBSD)
# This one not so much
set (CMAKE_SYSTEM_PROCESSOR x86)
set (CMAKE_SYSTEM_VERSION 1)

# System root
if (NOT IN_TRY_COMPILE AND NOT SAVED_FREEBSD_SYSROOT)
    if (NOT FREEBSD_SYSROOT AND DEFINED ENV{FREEBSD_SYSROOT})
        file (TO_CMAKE_PATH $ENV{FREEBSD_SYSROOT} FREEBSD_SYSROOT)
    endif ()
    set (FREEBSD_SYSROOT ${FREEBSD_SYSROOT} CACHE PATH "Path to FreeBSD system root (Linux cross-compiling build only)")
    if (NOT EXISTS ${FREEBSD_SYSROOT})
        message (FATAL_ERROR "Could not find FreeBSD system root. "
            "Use FREEBSD_SYSROOT environment variable or build option to specify the location of system root.")
    endif ()
endif ()
set (CMAKE_SYSROOT ${FREEBSD_SYSROOT})
# Only search libraries and headers in sysroot
set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Cross compiler tools
if (NOT "$ENV{CC}" MATCHES clang OR NOT "$ENV{CXX}" MATCHES clang\\+\\+)
    message (FATAL_ERROR "Only support Clang for now. Install it and export CC and CXX environment variables accordingly.")
endif ()
set (triple x86_64-unknown-freebsd12.0)
set (CMAKE_C_COMPILER $ENV{CC})
set (CMAKE_C_COMPILER_TARGET ${triple})
set (CMAKE_CXX_COMPILER $ENV{CXX})
set (CMAKE_CXX_COMPILER_TARGET ${triple})
set (CMAKE_AR /usr/bin/ar CACHE PATH "archive")

# Workaround try_compile() limitation where it cannot yet see cache variables during initial configuration
if (NOT IN_TRY_COMPILE)
    get_cmake_property (CACHE_VARIABLES CACHE_VARIABLES)
    foreach (VAR ${CACHE_VARIABLES})
        if (VAR MATCHES ^FREEBSD_|CMAKE_CX*_COMPILER)
            set (ENV{${VAR}} ${${VAR}})
            list (APPEND VARS ${VAR})
        endif ()
    endforeach ()
    set (ENV{VARS} "${VARS}")   # Stringify to keep the list together
endif ()

set (FREEBSD 1)
