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

# Find Open Sound System development library
#
#  OSS_FOUND
#  OSS_INCLUDE_DIRS
#  OSS_LIBRARIES
#  OSS_USE_WORKAROUND_HEADER
#

find_path (OSS_INCLUDE_DIRS NAMES sys/soundcard.h soundcard.h PATH_SUFFIXES uClibc DOC "OSS include directory")
find_library (OSS_LIBRARIES NAMES OSSlib ossaudio DOC "OSS library")
find_file (OSS_USE_WORKAROUND_HEADER NAMES soundcard.h DOC "OSS use workaround header")

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (OSS REQUIRED_VARS OSS_INCLUDE_DIRS FAIL_MESSAGE "Could NOT find OSS development library")

mark_as_advanced (OSS_INCLUDE_DIRS OSS_LIBRARIES OSS_USE_WORKAROUND_HEADER)
