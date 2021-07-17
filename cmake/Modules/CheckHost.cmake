#
# Copyright (c) 2008-2021 the Urho3D project.
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

# Check the capability of the host system
#
#  NULL_DEVICE
#
# WIN32 only:
#  HAS_MKLINK (capable to create mklink which is analogous to symlink)
#
# non-WIN32:
#  HAS_LIB64 (multilib capable)
#  CCACHE_VERSION (when ccache is used)
#
# Neither here nor there:
#  BASH_ON_WINDOWS
#

if (CMAKE_HOST_WIN32)
    set (NULL_DEVICE nul)
    if (NOT DEFINED HAS_MKLINK)
        # Test whether the host system is capable of setting up symbolic link
        execute_process (COMMAND cmd /C mklink test-link CMakeCache.txt WORKING_DIRECTORY ${CMAKE_BINARY_DIR} RESULT_VARIABLE MKLINK_EXIT_CODE OUTPUT_QUIET ERROR_QUIET)
        if (MKLINK_EXIT_CODE EQUAL 0)
            set (HAS_MKLINK TRUE)
            file (REMOVE ${CMAKE_BINARY_DIR}/test-link)
        else ()
            set (HAS_MKLINK FALSE)
            message (WARNING "Could not use MKLINK to setup symbolic links as this Windows user account does not have the privilege to do so. "
                "When MKLINK is not available then the build system will fallback to use file/directory copy of the library headers from source tree to build tree. "
                "In order to prevent stale headers being used in the build, this file/directory copy will be redone also as a post-build step for each library targets. "
                "This may slow down the build unnecessarily or even cause other unforseen issues due to incomplete or stale headers in the build tree. "
                "Request your Windows Administrator to grant your user account to have privilege to create symlink via MKLINK command. "
                "You are NOT advised to use the Administrator account directly to generate build tree in all cases.")
        endif ()
        set (HAS_MKLINK ${HAS_MKLINK} CACHE INTERNAL "MKLINK capability")
    endif ()
else ()
    set (NULL_DEVICE /dev/null)
    if (NOT DEFINED HAS_LIB64)
        if (EXISTS /usr/lib64)
            set (HAS_LIB64 TRUE)
        else ()
            set (HAS_LIB64 FALSE)
        endif ()
        set (HAS_LIB64 ${HAS_LIB64} CACHE INTERNAL "Multilib capability")
    endif ()
    # Test if it is a userspace bash on Windows host system
    if (NOT DEFINED BASH_ON_WINDOWS)
        execute_process (COMMAND grep -cq Microsoft /proc/version RESULT_VARIABLE GREP_EXIT_CODE OUTPUT_QUIET ERROR_QUIET)
        if (GREP_EXIT_CODE EQUAL 0)
            set (BASH_ON_WINDOWS TRUE)
        endif ()
        set (BASH_ON_WINDOWS ${BASH_ON_WINDOWS} CACHE INTERNAL "Bash on Ubuntu on Windows")
    endif ()
    if ("$ENV{USE_CCACHE}" AND NOT DEFINED CCACHE_VERSION)
        execute_process (COMMAND ccache --version COMMAND head -1 RESULT_VARIABLE CCACHE_EXIT_CODE OUTPUT_VARIABLE CCACHE_VERSION ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
        string (REGEX MATCH "[^ .]+\\.[^.]+\\.[^ ]+" CCACHE_VERSION "${CCACHE_VERSION}")    # Stringify as it could be empty when an error has occurred
        if (CCACHE_EXIT_CODE EQUAL 0)
           set (CCACHE_VERSION ${CCACHE_VERSION} CACHE INTERNAL "ccache version")
       endif ()
    endif ()
endif ()
