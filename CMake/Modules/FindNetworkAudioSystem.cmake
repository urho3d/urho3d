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

# Find NetworkAudioSystem development library
#
#  NAS_FOUND
#  NAS_INCLUDE_DIRS
#  NAS_LIBRARIES
#

find_path (NAS_INCLUDE_DIRS NAMES audio/audiolib.h nas/audiolib.h DOC "NetworkAudioSystem include directory")
find_library (NAS_LIBRARIES NAMES audio DOC "NetworkAudioSystem library")

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (NAS REQUIRED_VARS NAS_LIBRARIES NAS_INCLUDE_DIRS FAIL_MESSAGE "Could NOT find NetworkAudioSystem development library")

mark_as_advanced (NAS_INCLUDE_DIRS NAS_LIBRARIES)
