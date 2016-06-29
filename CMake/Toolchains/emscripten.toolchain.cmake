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

if (CMAKE_TOOLCHAIN_FILE)
    # Reference toolchain variable to suppress "unused variable" warning
    mark_as_advanced (CMAKE_TOOLCHAIN_FILE)
endif ()

# this one is important
set (CMAKE_SYSTEM_NAME Linux)
# this one not so much
set (CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
if (CMAKE_HOST_WIN32)
    set (TOOL_EXT .bat)
endif ()
if (NOT EMSCRIPTEN_ROOT_PATH)
    if (DEFINED ENV{EMSCRIPTEN_ROOT_PATH})
        file (TO_CMAKE_PATH $ENV{EMSCRIPTEN_ROOT_PATH} EMSCRIPTEN_ROOT_PATH)
    elseif (DEFINED ENV{EMSCRIPTEN})
        file (TO_CMAKE_PATH $ENV{EMSCRIPTEN} EMSCRIPTEN_ROOT_PATH)
    endif ()
endif ()
if (NOT EXISTS ${EMSCRIPTEN_ROOT_PATH}/emcc${TOOL_EXT})
    message (FATAL_ERROR "Could not find Emscripten cross compilation tool. "
        "Use EMSCRIPTEN_ROOT_PATH environment variable or build option to specify the location of the toolchain. "
        "Or use the canonical EMSCRIPTEN environment variable by calling emsdk_env script.")
endif ()
if (NOT EMCC_VERSION)
    execute_process (COMMAND ${EMSCRIPTEN_ROOT_PATH}/emcc${TOOL_EXT} --version RESULT_VARIABLE EXIT_CODE OUTPUT_VARIABLE EMCC_VERSION ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
    if (EXIT_CODE EQUAL 0)
        string (REGEX MATCH "[^ .]+\\.[^.]+\\.[^ ]+" EMCC_VERSION "${EMCC_VERSION}")    # Stringify as it could be empty when an error has occured
    else ()
        message (FATAL_ERROR "Could not determine the emcc version. Make sure you have installed and activated the Emscripten SDK correctly.")
    endif ()
    set (EMCC_VERSION ${EMCC_VERSION} CACHE STRING "emcc version being used in this build tree")    # Cache the result even when there was error in determining the version
endif ()
set (COMPILER_PATH ${EMSCRIPTEN_ROOT_PATH})
# ccache support could only be enabled for emcc prior to 1.31.3 when the CCACHE_CPP2 env var is also set to 1, newer emcc version could enable ccache support without this caveat (see https://github.com/kripken/emscripten/issues/3365 for more detail)
# The CCACHE_CPP2 env var tells ccache to fallback to use original input source file instead of preprocessed one when passing on the compilation task to the compiler proper
if (NOT CMAKE_C_COMPILER AND "$ENV{USE_CCACHE}" AND NOT CMAKE_HOST_WIN32 AND ("$ENV{CCACHE_CPP2}" OR NOT EMCC_VERSION VERSION_LESS 1.31.3))
    if (NOT $ENV{PATH} MATCHES ${EMSCRIPTEN_ROOT_PATH})
        message (FATAL_ERROR "The bin directory containing the compiler toolchain (${EMSCRIPTEN_ROOT_PATH}) has not been added in the PATH environment variable. "
            "This is required to enable ccache support for Emscripten compiler toolchain.")
    endif ()
    execute_process (COMMAND which ccache RESULT_VARIABLE EXIT_CODE OUTPUT_VARIABLE CCACHE ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
    if (EXIT_CODE EQUAL 0)
        foreach (name emcc em++)
            execute_process (COMMAND ${CMAKE_COMMAND} -E create_symlink ${CCACHE} ${CMAKE_BINARY_DIR}/${name})
        endforeach ()
        set (COMPILER_PATH ${CMAKE_BINARY_DIR})
    else ()
        message (WARNING "ccache may not have been installed on this host system. "
            "This is required to enable ccache support for Emscripten compiler toolchain. CMake has been configured to use the actual compiler toolchain instead of ccache. "
            "In order to rectify this, the build tree must be regenerated after installing ccache.")
    endif ()
endif ()
set (CMAKE_C_COMPILER   ${COMPILER_PATH}/emcc${TOOL_EXT}            CACHE PATH "C compiler")
set (CMAKE_CXX_COMPILER ${COMPILER_PATH}/em++${TOOL_EXT}            CACHE PATH "C++ compiler")
set (CMAKE_AR           ${EMSCRIPTEN_ROOT_PATH}/emar${TOOL_EXT}     CACHE PATH "archive")
set (CMAKE_RANLIB       ${EMSCRIPTEN_ROOT_PATH}/emranlib${TOOL_EXT} CACHE PATH "ranlib")
set (CMAKE_LINKER       ${EMSCRIPTEN_ROOT_PATH}/emlink.py           CACHE PATH "linker")
# Specific to Emscripten
set (EMRUN              ${EMSCRIPTEN_ROOT_PATH}/emrun${TOOL_EXT}    CACHE PATH "emrun")
set (EMPACKAGER         python ${EMSCRIPTEN_ROOT_PATH}/tools/file_packager.py CACHE PATH "file_packager.py")
set (EMBUILDER          python ${EMSCRIPTEN_ROOT_PATH}/embuilder.py CACHE PATH "embuilder.py")

# specify the system root
if (NOT EMSCRIPTEN_SYSROOT)
    if (DEFINED ENV{EMSCRIPTEN_SYSROOT})
        file (TO_CMAKE_PATH $ENV{EMSCRIPTEN_SYSROOT} EMSCRIPTEN_SYSROOT)
    else ()
        set (EMSCRIPTEN_SYSROOT ${EMSCRIPTEN_ROOT_PATH}/system)
    endif ()
    if (NOT EXISTS ${EMSCRIPTEN_SYSROOT})
        message (FATAL_ERROR "Could not find Emscripten system root. "
            "Use EMSCRIPTEN_SYSROOT environment variable or build option to specify the location of system root.")
    endif ()
    set (EMSCRIPTEN_ROOT_PATH ${EMSCRIPTEN_ROOT_PATH} CACHE STRING "Root path to Emscripten cross-compiler tools (Emscripten cross-compiling build only)" FORCE)
    set (EMSCRIPTEN_SYSROOT ${EMSCRIPTEN_SYSROOT} CACHE PATH "Path to Emscripten system root (Emscripten cross-compiling build only)" FORCE)
endif ()
set (CMAKE_FIND_ROOT_PATH ${EMSCRIPTEN_SYSROOT})

# only search libraries, and headers in the target directories
set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Still perform the compiler checks except for those stated otherwise below
foreach (LANG C CXX)
    # Since currently CMake does not able to identify Emscripten compiler toolchain, set the compiler identification explicitly
    set (CMAKE_${LANG}_COMPILER_ID_RUN TRUE)
    set (CMAKE_${LANG}_COMPILER_ID Clang)
    # The ABI info could not be checked as per normal as CMake does not understand the test build output from Emscripten, so bypass it also
    set (CMAKE_${LANG}_ABI_COMPILED TRUE)
    set (CMAKE_${LANG}_SIZEOF_DATA_PTR 4)   # Assume it is always 32-bit for now (we could have used our CheckCompilerToolChains.cmake module here)
    # There could be a bug in CMake itself where setting CMAKE_EXECUTABLE_SUFFIX variable outside of the scope, where it processes the platform configuration files, does not being honored by try_compile() command and as a result all the check macros that depend on try_compile() do not work properly when the CMAKE_EXECUTABLE_SUFFIX variable is only being set later futher down the road; At least one of the CMake devs has the opinion that this is the intended behavior but it is an unconvincing explanation because setting CMAKE_EXECUTABLE_SUFFIX variable later does have the desired effect everywhere else EXCEPT the try_compile() command
    # We are forced to set CMAKE_EXECUTABLE_SUFFIX_C and CMAKE_EXECUTABLE_SUFFIX_CXX here as a workaround; we could not just set CMAKE_EXECUTABLE_SUFFIX directly because CMake processes platform configuration files after the toolchain file and since we tell CMake that we are cross-compiling for 'Linux' platform via CMAKE_SYSTEM_NAME variable, CMake initializes the CMAKE_EXECUTABLE_SUFFIX to empty string (as expected for Linux platform); the workaround avoids our setting from being overwritten by platform configuration files by using the C and CXX language variants of the variable
    # The executable suffix needs to be .js for the below Emscripten-specific compiler setting to be effective
    set (CMAKE_EXECUTABLE_SUFFIX_${LANG} .js)
endforeach ()

# Set required compiler flags for internal CMake various check_xxx() macros which rely on the error to occur for the check to be performed correctly
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

set (WEB 1)
set (EMSCRIPTEN 1)
