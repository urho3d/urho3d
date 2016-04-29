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

# Find Wayland display server
#
#  WAYLAND_FOUND
#  WAYLAND_INCLUDE_DIRS
#  WAYLAND_LIBRARIES
#  WAYLAND_CLIENT
#  WAYLAND_CURSOR
#  WAYLAND_EGL
#  XKB
#

# Only need to cater for debian distros as they are not in CMAKE_SYSTEM_PATH
if (URHO3D_64BIT)
    set (WAYLAND_LIB_SEARCH_PATH /usr/lib/x86_64-linux-gnu)
else ()
    set (WAYLAND_LIB_SEARCH_PATH /usr/lib/i386-linux-gnu)
endif ()

find_path (WAYLAND_INCLUDE_DIRS NAMES wayland-client.h DOC "Wayland include directory")
find_library (WAYLAND_CLIENT NAMES wayland-client PATHS ${WAYLAND_LIB_SEARCH_PATH} DOC "Wayland client library")
find_library (WAYLAND_CURSOR NAMES wayland-cursor PATHS ${WAYLAND_LIB_SEARCH_PATH} DOC "Wayland compositor infrastructure - cursor library")
find_library (WAYLAND_EGL NAMES wayland-egl PATHS ${WAYLAND_LIB_SEARCH_PATH} DOC "Wayland EGL platform - runtime")
find_library (XKB NAMES xkbcommon PATHS ${WAYLAND_LIB_SEARCH_PATH} DOC "X.Org library for compiling XKB maps into formats usable by the X Server or other display servers")

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (Wayland REQUIRED_VARS WAYLAND_CLIENT WAYLAND_CURSOR WAYLAND_EGL XKB WAYLAND_INCLUDE_DIRS FAIL_MESSAGE "Could NOT find Wayland display server")
if (WAYLAND_FOUND)
    set (WAYLAND_LIBRARIES ${WAYLAND_CLIENT} ${WAYLAND_CURSOR} ${WAYLAND_EGL} ${XKB})
endif ()

mark_as_advanced (WAYLAND_INCLUDE_DIRS WAYLAND_LIBRARIES WAYLAND_CLIENT WAYLAND_CURSOR WAYLAND_EGL XKB)
