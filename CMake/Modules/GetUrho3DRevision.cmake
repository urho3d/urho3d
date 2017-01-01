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

# Get Urho3D library revision number

if (DEFINED ENV{TRAVIS_COMMIT})
    # Use the same commit-ish used by CI server to describe the repository
    set (ARG $ENV{TRAVIS_COMMIT})
else ()
    set (ARG --dirty)
endif ()
execute_process (COMMAND git describe ${ARG} RESULT_VARIABLE GIT_EXIT_CODE OUTPUT_VARIABLE LIB_REVISION ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
if (NOT GIT_EXIT_CODE EQUAL 0)
    # No GIT command line tool or not a GIT repository
    set (LIB_REVISION Unversioned)
endif ()
if (FILENAME)
    # Output complete revision number to a file
    file (WRITE ${FILENAME} "const char* revision=\"${LIB_REVISION}\";\n")
else ()
    # Output just major.minor.patch number to stdout
    string (REGEX MATCH "[^.]+\\.[^-]+" VERSION ${LIB_REVISION})            # Assume release tag always has major.minor format
    if (VERSION)
        string (REGEX MATCH "${VERSION}-([^-]+)" PATCH ${LIB_REVISION})     # Subsequent commits count after a release tag is treated as patch number
        if (PATCH)
            set (VERSION ${VERSION}.${CMAKE_MATCH_1})
        endif ()
    else ()
        set (VERSION 0.0)
    endif ()
    execute_process (COMMAND ${CMAKE_COMMAND} -E echo ${VERSION})
endif ()
