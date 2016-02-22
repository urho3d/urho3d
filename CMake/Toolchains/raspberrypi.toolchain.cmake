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
set (COMPILER_PREFIX ${RPI_PREFIX})
if (NOT CMAKE_C_COMPILER AND "$ENV{USE_CCACHE}")
    get_filename_component (NAME ${RPI_PREFIX} NAME)
    execute_process (COMMAND whereis -b ccache COMMAND grep -o \\S*lib\\S* RESULT_VARIABLE EXIT_CODE OUTPUT_VARIABLE CCACHE_SYMLINK ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
    if (EXIT_CODE EQUAL 0 AND EXISTS ${CCACHE_SYMLINK}/${NAME}-gcc AND EXISTS ${CCACHE_SYMLINK}/${NAME}-g++)
        set (COMPILER_PREFIX ${CCACHE_SYMLINK}/${NAME})
    else ()
        # Most probably this is a custom compiler toolchain not provided by the distro's own repository
        get_filename_component (PATH ${RPI_PREFIX} PATH)
        if (NOT $ENV{PATH} MATCHES ${PATH})
            message (FATAL_ERROR "The bin directory containing the compiler toolchain (${PATH}) has not been added in the PATH environment variable. "
                "This is required to enable ccache support for Raspberry-Pi compiler toolchain.")
        endif ()
        execute_process (COMMAND which ccache RESULT_VARIABLE EXIT_CODE OUTPUT_VARIABLE CCACHE ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
        if (EXIT_CODE EQUAL 0)
            foreach (suffix gcc g++)
                execute_process (COMMAND ${CMAKE_COMMAND} -E create_symlink ${CCACHE} ${CMAKE_BINARY_DIR}/${NAME}-${suffix})
            endforeach ()
            set (COMPILER_PREFIX ${CMAKE_BINARY_DIR}/${NAME})
        else ()
            message (WARNING "ccache may not have been installed on this host system. "
                "This is required to enable ccache support for Raspberry-Pi compiler toolchain. CMake has been configured to use the actual compiler toolchain instead of ccache. "
                "In order to rectify this, the build tree must be regenerated after installing ccache.")
        endif ()
    endif ()
endif ()
set (CMAKE_C_COMPILER   ${COMPILER_PREFIX}-gcc CACHE PATH "C compiler")
set (CMAKE_CXX_COMPILER ${COMPILER_PREFIX}-g++ CACHE PATH "C++ compiler")
set (CMAKE_STRIP        ${RPI_PREFIX}-strip    CACHE PATH "strip")
set (CMAKE_AR           ${RPI_PREFIX}-ar       CACHE PATH "archive")
set (CMAKE_LINKER       ${RPI_PREFIX}-ld       CACHE PATH "linker")
set (CMAKE_NM           ${RPI_PREFIX}-nm       CACHE PATH "nm")
set (CMAKE_OBJCOPY      ${RPI_PREFIX}-objcopy  CACHE PATH "objcopy")
set (CMAKE_OBJDUMP      ${RPI_PREFIX}-objdump  CACHE PATH "objdump")
set (CMAKE_RANLIB       ${RPI_PREFIX}-ranlib   CACHE PATH "ranlib")

# specify the system root
if (NOT RPI_SYSROOT OR NOT VIDEOCORE_INCLUDE_DIRS OR NOT VIDEOCORE_LIBRARIES)
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

# only search libraries, and headers in the target directories
set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set (RPI 1)
