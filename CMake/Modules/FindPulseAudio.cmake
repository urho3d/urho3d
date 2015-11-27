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
#

find_path (PA_INCLUDE_DIRS NAMES pulse/pulseaudio.h DOC "PulseAudio include directories")
find_library (PA_LIBRARIES NAMES pulse-simple DOC "PulseAudio libraries")

if (PA_INCLUDE_DIRS AND PA_LIBRARIES)
    set (PA_FOUND 1)
endif ()
if (PA_FOUND)
    include (FindPackageMessage)
    find_package_message (PulseAudio "Found PulseAudio: ${PA_LIBRARIES} ${PA_INCLUDE_DIRS}" "[${PA_LIBRARIES}][${PA_INCLUDE_DIRS}]")
elseif (PulseAudio_FIND_REQUIRED)
    message (FATAL_ERROR "Could not find PulseAudio")
endif ()

mark_as_advanced (PA_INCLUDE_DIRS PA_LIBRARIES)
