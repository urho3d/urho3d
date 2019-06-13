#
# Copyright (c) 2008-2019 the Urho3D project.
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
#  WAYLAND_CORE_PROTOCOL_DIR
#  WAYLAND_PROTOCOLS_DIR
#  WAYLAND_CLIENT
#  WAYLAND_SCANNER
#  WAYLAND_CURSOR
#  WAYLAND_EGL
#  EGL
#  XKB
#

find_path (WAYLAND_INCLUDE_DIRS NAMES wayland-client.h DOC "Wayland include directory")
find_path (WAYLAND_CORE_PROTOCOL_DIR NAMES wayland.xml PATHS /usr/share/wayland DOC "Wayland core protocol directory")
find_path (WAYLAND_PROTOCOLS_DIR NAMES stable unstable PATHS /usr/share/wayland-protocols DOC "Wayland protocol directory")
find_library (WAYLAND_CLIENT NAMES wayland-client DOC "Wayland client library")
find_program (WAYLAND_SCANNER NAMES wayland-scanner DOC "Wayland scanner host tool")
find_library (WAYLAND_CURSOR NAMES wayland-cursor DOC "Wayland compositor infrastructure - cursor library")
find_library (WAYLAND_EGL NAMES wayland-egl DOC "Wayland EGL library")
find_library (EGL NAMES EGL DOC "EGL library")
find_library (XKB NAMES xkbcommon DOC "Xkb common library")

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (Wayland REQUIRED_VARS WAYLAND_CLIENT WAYLAND_SCANNER WAYLAND_CURSOR WAYLAND_EGL EGL XKB WAYLAND_INCLUDE_DIRS WAYLAND_CORE_PROTOCOL_DIR WAYLAND_PROTOCOLS_DIR FAIL_MESSAGE "Could NOT find Wayland display server")

mark_as_advanced (WAYLAND_INCLUDE_DIRS WAYLAND_CORE_PROTOCOL_DIR WAYLAND_PROTOCOLS_DIR WAYLAND_CLIENT WAYLAND_SCANNER WAYLAND_CURSOR WAYLAND_EGL EGL XKB)
