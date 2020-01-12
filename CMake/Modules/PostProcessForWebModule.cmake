#
# Copyright (c) 2008-2020 the Urho3D project.
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

# Post process to glue the main module and side module(s) together

string (REPLACE " " .js',' SIDE_MODULES "'${SIDE_MODULES}.js'")              # Stringify for string replacement
if (HAS_SHELL_FILE)
    file (READ ${TARGET_FILE} CONTENT)
    string (REPLACE ${TARGET_NAME}.js libUrho3D.js CONTENT "${CONTENT}")     # Stringify to preserve semicolons
    # Assume HTML shell-file has Module object without the 'dynamicLibraries' prop defined yet
    string (REGEX REPLACE "(var Module *= *{)" \\1dynamicLibraries:[${SIDE_MODULES}], CONTENT "${CONTENT}")
    file (WRITE ${TARGET_FILE} "${CONTENT}")
else ()
    file (READ ${TARGET_DIR}/libUrho3D.js CONTENT)
    file (WRITE ${TARGET_DIR}/${TARGET_NAME}.main.js "var Module={dynamicLibraries:[${SIDE_MODULES}]};${CONTENT}")
endif ()
