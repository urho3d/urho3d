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

# Get Urho3D library revision number

execute_process (COMMAND git describe --always --dirty RESULT_VARIABLE GIT_EXIT_CODE OUTPUT_VARIABLE LIB_REVISION ERROR_QUIET)
if (GIT_EXIT_CODE EQUAL 0)
    # Remove trailing end of line character
    string (STRIP ${LIB_REVISION} LIB_REVISION)
else ()
    # This should not happen, but just in case
    set (LIB_REVISION Unversioned)
endif ()
set (LIB_REVISION "const char* revision=\"${LIB_REVISION}\"\;\n")
file (WRITE ${FILENAME} ${LIB_REVISION})
