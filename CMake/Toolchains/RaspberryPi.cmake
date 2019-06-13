#
# Copyright (c) 2008-2019 the Urho3D project.
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
        set (SAVED_RPI_SYSROOT ${RPI_SYSROOT} CACHE INTERNAL "Initial value for RPI_SYSROOT")
        set (SAVED_RPI_PREFIX ${RPI_PREFIX} CACHE INTERNAL "Initial value for RPI_PREFIX")
        # Save the initial values of CC and CXX environment variables
        set (SAVED_CC $ENV{CC} CACHE INTERNAL "Initial value for CC")
        set (SAVED_CXX $ENV{CXX} CACHE INTERNAL "Initial value for CXX")
        return ()
    elseif ((SAVED_RPI_SYSROOT AND NOT SAVED_RPI_SYSROOT STREQUAL RPI_SYSROOT) OR (SAVED_RPI_PREFIX AND NOT SAVED_RPI_PREFIX STREQUAL RPI_PREFIX))
        set (RPI_SYSROOT ${SAVED_RPI_SYSROOT} CACHE PATH "Path to Raspberry Pi system root (RPI cross-compiling build only)" FORCE)
        set (RPI_PREFIX ${SAVED_RPI_PREFIX} CACHE STRING "Prefix path to Raspberry Pi cross-compiler tools (RPI cross-compiling build only)" FORCE)
        message (FATAL_ERROR "RPI_SYSROOT and RPI_PREFIX cannot be changed after the initial configuration/generation. "
            "If you wish to change that then the build tree would have to be regenerated from scratch. Auto reverting to its initial value.")
    endif ()
endif ()

# Reference toolchain variable to suppress "unused variable" warning
if (CMAKE_TOOLCHAIN_FILE)
    mark_as_advanced (CMAKE_TOOLCHAIN_FILE)
endif ()

# This one is important
set (CMAKE_SYSTEM_NAME Linux)
# This one not so much
set (CMAKE_SYSTEM_PROCESSOR arm)
set (CMAKE_SYSTEM_VERSION 1)

# System root
if (NOT IN_TRY_COMPILE AND NOT SAVED_RPI_SYSROOT)
    if (NOT RPI_SYSROOT AND DEFINED ENV{RPI_SYSROOT})
        file (TO_CMAKE_PATH $ENV{RPI_SYSROOT} RPI_SYSROOT)
    endif ()
    set (RPI_SYSROOT ${RPI_SYSROOT} CACHE PATH "Path to Raspberry Pi system root (RPI cross-compiling build only)")
    if (NOT EXISTS ${RPI_SYSROOT})
        message (FATAL_ERROR "Could not find Raspberry Pi system root. "
            "Use RPI_SYSROOT environment variable or build option to specify the location of system root.")
    endif ()
endif ()
set (CMAKE_SYSROOT ${RPI_SYSROOT})
# Only search libraries and headers in sysroot
set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Cross compiler tools
if (NOT IN_TRY_COMPILE AND NOT SAVED_RPI_PREFIX)
    if (NOT RPI_PREFIX AND DEFINED ENV{RPI_PREFIX})
        file (TO_CMAKE_PATH $ENV{RPI_PREFIX} RPI_PREFIX)
    endif ()
    set (RPI_PREFIX ${RPI_PREFIX} CACHE STRING "Prefix path to Raspberry Pi cross-compiler tools (RPI cross-compiling build only)")
    if (NOT EXISTS ${RPI_PREFIX}-gcc)
        message (FATAL_ERROR "Could not find Raspberry Pi cross compilation tool. "
            "Use RPI_PREFIX environment variable or build option to specify the location of the toolchain.")
    endif ()
endif ()
if (NOT RPI_COMPILER_PREFIX)
    set (RPI_COMPILER_PREFIX ${RPI_PREFIX})
    if ("$ENV{USE_CCACHE}")
        get_filename_component (PATH ${RPI_PREFIX} PATH)
        get_filename_component (NAME ${RPI_PREFIX} NAME)
        execute_process (COMMAND whereis -b ccache COMMAND grep -o \\S*lib\\S* OUTPUT_VARIABLE CCACHE_SYMLINK ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
        if (CCACHE_SYMLINK AND EXISTS ${CCACHE_SYMLINK}/${NAME}-gcc AND EXISTS ${CCACHE_SYMLINK}/${NAME}-g++)
            set (RPI_COMPILER_PREFIX ${CCACHE_SYMLINK}/${NAME})
        else ()
            # Fallback to create the ccache symlink in the build tree itself
            execute_process (COMMAND which ccache RESULT_VARIABLE EXIT_CODE OUTPUT_VARIABLE CCACHE ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
            if (EXIT_CODE EQUAL 0 AND CCACHE)
                foreach (TOOL gcc g++)
                    execute_process (COMMAND ${CMAKE_COMMAND} -E create_symlink ${CCACHE} ${CMAKE_BINARY_DIR}/${NAME}-${TOOL})
                endforeach ()
                set (RPI_COMPILER_PREFIX ${CMAKE_BINARY_DIR}/${NAME})
            else ()
                message (WARNING "ccache may not have been installed on this host system. "
                    "This is required to enable ccache support for Raspberry-Pi compiler toolchain. "
                    "CMake has been configured to use the actual compiler toolchain instead of ccache. "
                    "In order to rectify this, the build tree must be regenerated after installing ccache.")
            endif ()
        endif ()
        if (NOT RPI_COMPILER_PREFIX STREQUAL RPI_PREFIX AND NOT $ENV{PATH} MATCHES ${PATH})
            message (FATAL_ERROR "The bin directory containing the compiler toolchain (${PATH}) has not been added in the PATH environment variable. "
                "This is required to enable ccache support for Raspberry-Pi compiler toolchain.")
        endif ()
    endif ()
    set (RPI_COMPILER_PREFIX ${RPI_COMPILER_PREFIX} CACHE INTERNAL "Path to C/C++ compiler tool symlinks or to the actual tools if not using ccache")
endif ()
set (CMAKE_C_COMPILER   ${RPI_COMPILER_PREFIX}-gcc CACHE PATH "C compiler")
set (CMAKE_CXX_COMPILER ${RPI_COMPILER_PREFIX}-g++ CACHE PATH "C++ compiler")
set (CMAKE_STRIP        ${RPI_PREFIX}-strip        CACHE PATH "strip")
set (CMAKE_AR           ${RPI_PREFIX}-ar           CACHE PATH "archive")
set (CMAKE_LINKER       ${RPI_PREFIX}-ld           CACHE PATH "linker")
set (CMAKE_NM           ${RPI_PREFIX}-nm           CACHE PATH "nm")
set (CMAKE_OBJCOPY      ${RPI_PREFIX}-objcopy      CACHE PATH "objcopy")
set (CMAKE_OBJDUMP      ${RPI_PREFIX}-objdump      CACHE PATH "objdump")
set (CMAKE_RANLIB       ${RPI_PREFIX}-ranlib       CACHE PATH "ranlib")

# Workaround try_compile() limitation where it cannot yet see cache variables during initial configuration
if (NOT IN_TRY_COMPILE)
    get_cmake_property (CACHE_VARIABLES CACHE_VARIABLES)
    foreach (VAR ${CACHE_VARIABLES})
        if (VAR MATCHES ^RPI_|CMAKE_CX*_COMPILER)
            set (ENV{${VAR}} ${${VAR}})
            list (APPEND VARS ${VAR})
        endif ()
    endforeach ()
    set (ENV{VARS} "${VARS}")   # Stringify to keep the list together
endif ()

set (RPI 1)
