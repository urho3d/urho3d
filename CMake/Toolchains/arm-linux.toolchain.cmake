#
# Copyright (c) 2008-2017 the Urho3D project.
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

if (DEFINED CMAKE_CROSSCOMPILING)
    return ()
endif ()

if (CMAKE_TOOLCHAIN_FILE)
    # Reference toolchain variable to suppress "unused variable" warning
    mark_as_advanced (CMAKE_TOOLCHAIN_FILE)
endif ()

# this one is important
set (CMAKE_SYSTEM_NAME Linux)
# this one not so much
set (CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
if (NOT ARM_PREFIX AND DEFINED ENV{ARM_PREFIX})
    file (TO_CMAKE_PATH $ENV{ARM_PREFIX} ARM_PREFIX)
endif ()
if (NOT EXISTS ${ARM_PREFIX}-gcc)
    message (FATAL_ERROR "Could not find ARM cross compilation tool. "
        "Use ARM_PREFIX environment variable or build option to specify the location of the toolchain.")
endif ()
set (COMPILER_PREFIX ${ARM_PREFIX})
if (NOT CMAKE_C_COMPILER AND "$ENV{USE_CCACHE}")
    get_filename_component (NAME ${ARM_PREFIX} NAME)
    execute_process (COMMAND whereis -b ccache COMMAND grep -o \\S*lib\\S* RESULT_VARIABLE EXIT_CODE OUTPUT_VARIABLE CCACHE_SYMLINK ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
    if (EXIT_CODE EQUAL 0 AND EXISTS ${CCACHE_SYMLINK}/${NAME}-gcc AND EXISTS ${CCACHE_SYMLINK}/${NAME}-g++)
        set (COMPILER_PREFIX ${CCACHE_SYMLINK}/${NAME})
    else ()
        # Most probably this is a custom compiler toolchain not provided by the distro's own repository
        get_filename_component (PATH ${ARM_PREFIX} PATH)
        if (NOT $ENV{PATH} MATCHES ${PATH})
            message (FATAL_ERROR "The bin directory containing the compiler toolchain (${PATH}) has not been added in the PATH environment variable. "
                "This is required to enable ccache support for ARM compiler toolchain.")
        endif ()
        execute_process (COMMAND which ccache RESULT_VARIABLE EXIT_CODE OUTPUT_VARIABLE CCACHE ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
        if (EXIT_CODE EQUAL 0)
            foreach (suffix gcc g++)
                execute_process (COMMAND ${CMAKE_COMMAND} -E create_symlink ${CCACHE} ${CMAKE_BINARY_DIR}/${NAME}-${suffix})
            endforeach ()
            set (COMPILER_PREFIX ${CMAKE_BINARY_DIR}/${NAME})
        else ()
            message (WARNING "ccache may not have been installed on this host system. "
                "This is required to enable ccache support for ARM compiler toolchain. CMake has been configured to use the actual compiler toolchain instead of ccache. "
                "In order to rectify this, the build tree must be regenerated after installing ccache.")
        endif ()
    endif ()
endif ()
set (CMAKE_C_COMPILER   ${COMPILER_PREFIX}-gcc CACHE PATH "C compiler")
set (CMAKE_CXX_COMPILER ${COMPILER_PREFIX}-g++ CACHE PATH "C++ compiler")
set (CMAKE_STRIP        ${ARM_PREFIX}-strip    CACHE PATH "strip")
set (CMAKE_AR           ${ARM_PREFIX}-ar       CACHE PATH "archive")
set (CMAKE_LINKER       ${ARM_PREFIX}-ld       CACHE PATH "linker")
set (CMAKE_NM           ${ARM_PREFIX}-nm       CACHE PATH "nm")
set (CMAKE_OBJCOPY      ${ARM_PREFIX}-objcopy  CACHE PATH "objcopy")
set (CMAKE_OBJDUMP      ${ARM_PREFIX}-objdump  CACHE PATH "objdump")
set (CMAKE_RANLIB       ${ARM_PREFIX}-ranlib   CACHE PATH "ranlib")

# specify the system root
if (NOT ARM_SYSROOT)
    if (DEFINED ENV{ARM_SYSROOT})
        file (TO_CMAKE_PATH $ENV{ARM_SYSROOT} ARM_SYSROOT)
    endif ()
    if (NOT EXISTS ${ARM_SYSROOT})
        message (FATAL_ERROR "Could not find ARM system root. "
            "Use ARM_SYSROOT environment variable or build option to specify the location of system root.")
    endif ()
    set (ARM_PREFIX ${ARM_PREFIX} CACHE STRING "Prefix path to ARM cross-compiler tools (ARM on Linux cross-compiling build only)" FORCE)
    set (ARM_SYSROOT ${ARM_SYSROOT} CACHE PATH "Path to ARM system root (ARM on Linux cross-compiling build only)" FORCE)
endif ()
set (CMAKE_FIND_ROOT_PATH ${ARM_SYSROOT})

# cache flags (use the same trick found in android.toolchain.cmake)
set (CMAKE_C_FLAGS "" CACHE STRING "C compiler flags")
set (CMAKE_CXX_FLAGS "" CACHE STRING "C++ compiler flags")
# finish flags
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --sysroot=${ARM_SYSROOT}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --sysroot=${ARM_SYSROOT}")

# only search libraries, and headers in the target directories
set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set (ARM 1)
