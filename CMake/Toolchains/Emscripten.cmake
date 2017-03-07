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

# Workaround try_compile() limitation where it cannot yet see cache variables during initial configuration
get_property (IN_TRY_COMPILE GLOBAL PROPERTY IN_TRY_COMPILE)
if (IN_TRY_COMPILE)
    foreach (VAR $ENV{VARS})
        set (${VAR} $ENV{${VAR}})
    endforeach ()
else ()
    # Prevent critical variables from changing after the initial configuration
    if (CMAKE_CROSSCOMPILING)
        set (SAVED_EMSCRIPTEN_ROOT_PATH ${EMSCRIPTEN_ROOT_PATH} CACHE INTERNAL "Initial value for EMSCRIPTEN_ROOT_PATH")
        set (SAVED_EMSCRIPTEN_SYSROOT ${EMSCRIPTEN_SYSROOT} CACHE INTERNAL "Initial value for EMSCRIPTEN_SYSROOT")
        # Save the initial values of CC and CXX environment variables
        set (SAVED_CC $ENV{CC} CACHE INTERNAL "Initial value for CC")
        set (SAVED_CXX $ENV{CXX} CACHE INTERNAL "Initial value for CXX")
        return ()
    elseif ((SAVED_EMSCRIPTEN_ROOT_PATH AND NOT SAVED_EMSCRIPTEN_ROOT_PATH STREQUAL EMSCRIPTEN_ROOT_PATH) OR (SAVED_EMSCRIPTEN_SYSROOT AND NOT SAVED_EMSCRIPTEN_SYSROOT STREQUAL EMSCRIPTEN_SYSROOT))
        set (EMSCRIPTEN_ROOT_PATH ${SAVED_EMSCRIPTEN_ROOT_PATH} CACHE STRING "Root path to Emscripten cross-compiler tools (Emscripten only)" FORCE)
        set (EMSCRIPTEN_SYSROOT ${SAVED_EMSCRIPTEN_SYSROOT} CACHE PATH "Path to Emscripten system root (Emscripten only)" FORCE)
        message (FATAL_ERROR "EMSCRIPTEN_ROOT_PATH and EMSCRIPTEN_SYSROOT cannot be changed after the initial configuration/generation. "
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
set (CMAKE_SYSTEM_VERSION 1)

# System root
if (NOT IN_TRY_COMPILE)
    if (NOT SAVED_EMSCRIPTEN_ROOT_PATH)
        if (NOT EMSCRIPTEN_ROOT_PATH)
            if (DEFINED ENV{EMSCRIPTEN_ROOT_PATH})
                file (TO_CMAKE_PATH $ENV{EMSCRIPTEN_ROOT_PATH} EMSCRIPTEN_ROOT_PATH)
            elseif (DEFINED ENV{EMSCRIPTEN})
                file (TO_CMAKE_PATH $ENV{EMSCRIPTEN} EMSCRIPTEN_ROOT_PATH)
            endif ()
        endif ()
        set (EMSCRIPTEN_ROOT_PATH ${EMSCRIPTEN_ROOT_PATH} CACHE STRING "Root path to Emscripten cross-compiler tools (Emscripten only)")
        if (NOT EXISTS ${EMSCRIPTEN_ROOT_PATH}/emcc${TOOL_EXT})
            message (FATAL_ERROR "Could not find Emscripten cross compilation tool. "
                "Use EMSCRIPTEN_ROOT_PATH environment variable or build option to specify the location of the toolchain. "
                "Or use the canonical EMSCRIPTEN environment variable by calling emsdk_env script.")
        endif ()
    endif ()
    if (NOT SAVED_EMSCRIPTEN_SYSROOT)
        if (NOT EMSCRIPTEN_SYSROOT)
            if (DEFINED ENV{EMSCRIPTEN_SYSROOT})
                file (TO_CMAKE_PATH $ENV{EMSCRIPTEN_SYSROOT} EMSCRIPTEN_SYSROOT)
            else ()
                set (EMSCRIPTEN_SYSROOT ${EMSCRIPTEN_ROOT_PATH}/system)
            endif ()
        endif ()
        set (EMSCRIPTEN_SYSROOT ${EMSCRIPTEN_SYSROOT} CACHE PATH "Path to Emscripten system root (Emscripten only)")
        if (NOT EXISTS ${EMSCRIPTEN_SYSROOT})
            message (FATAL_ERROR "Could not find Emscripten system root. "
                "Use EMSCRIPTEN_SYSROOT environment variable or build option to specify the location of system root.")
        endif ()
    endif ()
endif ()
set (CMAKE_SYSROOT ${EMSCRIPTEN_SYSROOT})
# Only search libraries and headers in sysroot
set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Cross compiler tools
if (CMAKE_HOST_WIN32)
    set (TOOL_EXT .bat)
endif ()
if (NOT EMSCRIPTEN_EMCC_VERSION)
    execute_process (COMMAND ${EMSCRIPTEN_ROOT_PATH}/emcc${TOOL_EXT} --version RESULT_VARIABLE EXIT_CODE OUTPUT_VARIABLE EMSCRIPTEN_EMCC_VERSION ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
    if (EXIT_CODE EQUAL 0)
        string (REGEX MATCH "[^ .]+\\.[^.]+\\.[^ ]+" EMSCRIPTEN_EMCC_VERSION "${EMSCRIPTEN_EMCC_VERSION}")
    else ()
        message (FATAL_ERROR "Could not determine the emcc version. Make sure you have installed and activated the Emscripten SDK correctly.")
    endif ()
    set (EMSCRIPTEN_EMCC_VERSION ${EMSCRIPTEN_EMCC_VERSION} CACHE INTERNAL "emcc version being used in this build tree")
endif ()
# ccache support could only be enabled for emcc prior to 1.31.3 when the CCACHE_CPP2 env var is also set to 1, newer emcc version could enable ccache support without this caveat (see https://github.com/kripken/emscripten/issues/3365 for more detail)
# The CCACHE_CPP2 env var tells ccache to fallback to use original input source file instead of preprocessed one when passing on the compilation task to the compiler proper
if (NOT EMSCRIPTEN_COMPILER_PATH)
    set (EMSCRIPTEN_COMPILER_PATH ${EMSCRIPTEN_ROOT_PATH})
    if ("$ENV{USE_CCACHE}" AND NOT CMAKE_HOST_WIN32 AND ("$ENV{CCACHE_CPP2}" OR NOT EMSCRIPTEN_EMCC_VERSION VERSION_LESS 1.31.3))
        execute_process (COMMAND whereis -b ccache COMMAND grep -o \\S*lib\\S* OUTPUT_VARIABLE CCACHE_SYMLINK ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
        if (CCACHE_SYMLINK AND EXISTS ${CCACHE_SYMLINK}/emcc AND EXISTS ${CCACHE_SYMLINK}/em++)
            set (EMSCRIPTEN_COMPILER_PATH ${CCACHE_SYMLINK})
        else ()
            # Fallback to create the ccache symlink in the build tree itself
            execute_process (COMMAND which ccache RESULT_VARIABLE EXIT_CODE OUTPUT_VARIABLE CCACHE ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
            if (EXIT_CODE EQUAL 0 AND CCACHE)
                foreach (TOOL emcc em++)
                    execute_process (COMMAND ${CMAKE_COMMAND} -E create_symlink ${CCACHE} ${CMAKE_BINARY_DIR}/${TOOL})
                endforeach ()
                set (EMSCRIPTEN_COMPILER_PATH ${CMAKE_BINARY_DIR})
            else ()
                message (WARNING "ccache may not have been installed on this host system. "
                    "This is required to enable ccache support for Emscripten compiler toolchain. "
                    "CMake has been configured to use the actual compiler toolchain instead of ccache. "
                    "In order to rectify this, the build tree must be regenerated after installing ccache.")
            endif ()
        endif ()
        if (NOT EMSCRIPTEN_COMPILER_PATH STREQUAL EMSCRIPTEN_ROOT_PATH AND NOT $ENV{PATH} MATCHES ${EMSCRIPTEN_ROOT_PATH})
            message (FATAL_ERROR "The bin directory containing the compiler toolchain (${EMSCRIPTEN_ROOT_PATH}) has not been added in the PATH environment variable. "
                "This is required to enable ccache support for Emscripten compiler toolchain.")
        endif ()
    endif ()
    set (EMSCRIPTEN_COMPILER_PATH ${EMSCRIPTEN_COMPILER_PATH} CACHE INTERNAL "Path to C/C++ compiler tool symlinks or to the actual tools if not using ccache")
endif ()
set (CMAKE_C_COMPILER   ${EMSCRIPTEN_COMPILER_PATH}/emcc${TOOL_EXT} CACHE PATH "C compiler")
set (CMAKE_CXX_COMPILER ${EMSCRIPTEN_COMPILER_PATH}/em++${TOOL_EXT} CACHE PATH "C++ compiler")
set (CMAKE_AR           ${EMSCRIPTEN_ROOT_PATH}/emar${TOOL_EXT}     CACHE PATH "archive")
set (CMAKE_RANLIB       ${EMSCRIPTEN_ROOT_PATH}/emranlib${TOOL_EXT} CACHE PATH "ranlib")
set (CMAKE_LINKER       ${EMSCRIPTEN_ROOT_PATH}/emlink.py           CACHE PATH "linker")
# Specific to Emscripten
set (EMRUN              ${EMSCRIPTEN_ROOT_PATH}/emrun${TOOL_EXT}    CACHE PATH "emrun")
set (EMPACKAGER         python ${EMSCRIPTEN_ROOT_PATH}/tools/file_packager.py CACHE PATH "file_packager.py")
set (EMBUILDER          python ${EMSCRIPTEN_ROOT_PATH}/embuilder.py CACHE PATH "embuilder.py")

# Still perform the compiler checks except for those stated otherwise below
foreach (LANG C CXX)
    # Since currently CMake does not able to identify Emscripten compiler toolchain, set the compiler identification explicitly
    set (CMAKE_${LANG}_COMPILER_ID_RUN TRUE)
    set (CMAKE_${LANG}_COMPILER_ID Clang)
    set (CMAKE_${LANG}_COMPILER_VERSION ${EMSCRIPTEN_EMCC_VERSION})
    # The ABI info could not be checked as per normal as CMake does not understand the test build output from Emscripten, so bypass it also
    set (CMAKE_${LANG}_ABI_COMPILED TRUE)
    set (CMAKE_${LANG}_SIZEOF_DATA_PTR 4)   # Assume it is always 32-bit for now (we could have used our CheckCompilerToolChains.cmake module here)
    # We could not set CMAKE_EXECUTABLE_SUFFIX directly because CMake processes platform configuration files after the toolchain file and since we tell CMake that we are cross-compiling for 'Linux' platform (Emscripten is not a valid platform yet in CMake) via CMAKE_SYSTEM_NAME variable, as such CMake force initializes the CMAKE_EXECUTABLE_SUFFIX to empty string (as expected for Linux platform); To workaround it we have to use CMAKE_EXECUTABLE_SUFFIX_C and CMAKE_EXECUTABLE_SUFFIX_CXX instead, which are fortunately not being touched by platform configuration files
    set (CMAKE_EXECUTABLE_SUFFIX_${LANG} .js)
    set (CMAKE_SHARED_LIBRARY_SUFFIX_${LANG} .bc)   # "linked" LLVM bitcode
    set (CMAKE_SHARED_MODULE_SUFFIX_${LANG} .js)    # side module
endforeach ()

# Set required compiler flags for various internal CMake checks which rely on the compiler/linker error to be occured for the check to be performed correctly
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

# Workaround try_compile() limitation where it cannot yet see cache variables during initial configuration
if (NOT IN_TRY_COMPILE)
    get_cmake_property (CACHE_VARIABLES CACHE_VARIABLES)
    foreach (VAR ${CACHE_VARIABLES})
        if (VAR MATCHES ^EMSCRIPTEN_|CMAKE_CX*_COMPILER)
            set (ENV{${VAR}} ${${VAR}})
            list (APPEND VARS ${VAR})
        endif ()
    endforeach ()
    set (ENV{VARS} "${VARS}")   # Stringify to keep the list together
endif ()

set (EMSCRIPTEN 1)
