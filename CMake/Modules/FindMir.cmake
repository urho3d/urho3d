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

# Find Mir display server
#
#  MIR_FOUND
#  MIR_INCLUDE_DIRS
#  MIR_CLIENT
#  MIR_COMMON
#  EGL
#  XKB
#

find_path (MIR_CLIENT_INCLUDE_DIR NAMES mir_toolkit/mir_client_library.h PATH_SUFFIXES mirclient DOC "Mir client include directory")
find_path (MIR_COMMON_INCLUDE_DIR NAMES mir_toolkit/common.h PATH_SUFFIXES mircommon DOC "Mir common include directory")
find_library (MIR_CLIENT NAMES mirclient DOC "Mir client library")
find_library (MIR_COMMON NAMES mircommon DOC "Mir common library")
find_library (EGL NAMES EGL DOC "EGL library")
find_library (XKB NAMES xkbcommon DOC "Xkb common library")

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (Mir REQUIRED_VARS MIR_CLIENT MIR_COMMON EGL XKB MIR_CLIENT_INCLUDE_DIR MIR_COMMON_INCLUDE_DIR FAIL_MESSAGE "Could NOT find Mir display server")
if (MIR_FOUND)
    set (MIR_INCLUDE_DIRS ${MIR_CLIENT_INCLUDE_DIR} ${MIR_COMMON_INCLUDE_DIR})
endif ()

mark_as_advanced (MIR_CLIENT_INCLUDE_DIR MIR_COMMON_INCLUDE_DIR MIR_CLIENT MIR_COMMON EGL XKB)
