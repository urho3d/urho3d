#
# Copyright (c) 2008-2015 the Urho3D project.
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

# Find PulseAudio development library
#
#  PA_FOUND
#  PA_INCLUDE_DIRS
#  PA_LIBRARIES
#  PA_VERSION
#

find_path (PA_INCLUDE_DIRS NAMES pulse/pulseaudio.h DOC "PulseAudio include directory")
find_library (PA_LIBRARIES NAMES pulse-simple DOC "PulseAudio library")

if (NOT PA_VERSION AND PA_INCLUDE_DIRS AND EXISTS ${PA_INCLUDE_DIRS}/pulse/version.h)   # Only do this once
    file (STRINGS "${PA_INCLUDE_DIRS}/pulse/version.h" PA_VERSION REGEX "^.*pa_get_headers_version.+\"[^\"]*\".*$")
    string (REGEX REPLACE "^.*pa_get_headers_version.+\"([^\"]*)\".*$" \\1 PA_VERSION "${PA_VERSION}")      # Stringify to guard against empty variable
    set (PA_VERSION "${PA_VERSION}" CACHE INTERNAL "PulseAudio version")
endif ()

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (PA REQUIRED_VARS PA_LIBRARIES PA_INCLUDE_DIRS VERSION_VAR PA_VERSION FAIL_MESSAGE "Could NOT find PulseAudio development library")

mark_as_advanced (PA_INCLUDE_DIRS PA_LIBRARIES)
