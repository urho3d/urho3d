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

# Find Secret Rabbit Code development library
#
#  SECRETRABBITCODE_FOUND
#  SECRETRABBITCODE_INCLUDE_DIRS
#  SECRETRABBITCODE_LIBRARIES
#

find_path (SECRETRABBITCODE_INCLUDE_DIRS NAMES samplerate.h DOC "SecretRabbitCode include directory")
find_library (SECRETRABBITCODE_LIBRARIES NAMES samplerate DOC "SecretRabbitCode library")

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (SecretRabbitCode REQUIRED_VARS SECRETRABBITCODE_LIBRARIES SECRETRABBITCODE_INCLUDE_DIRS FAIL_MESSAGE "Could NOT find Secret Rabbit Code (aka libsamplerate) development library")

mark_as_advanced (SECRETRABBITCODE_INCLUDE_DIRS SECRETRABBITCODE_LIBRARIES)
