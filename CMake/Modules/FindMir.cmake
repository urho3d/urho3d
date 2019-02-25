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

# Find Mir display server
#
#  MIR_FOUND
#  MIR_INCLUDE_DIRS
#  MIR_CLIENT
#  MIR_CLIENT_VERSION
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

if (NOT MIR_CLIENT_VERSION AND MIR_CLIENT_INCLUDE_DIR AND EXISTS ${MIR_CLIENT_INCLUDE_DIR}/mir_toolkit/version.h)   # Only do this once
    file (STRINGS ${MIR_CLIENT_INCLUDE_DIR}/mir_toolkit/version.h MIR_CLIENT_VERSION REGEX "^.*MIR_CLIENT_API_VERSION_(MAJOR|MINOR|PATCH).+\([^\)]*\).*$")
    string (REGEX REPLACE "^.*MIR_CLIENT_API_VERSION_MAJOR.+\(([^\)]*)\).*$" \\1 MIR_CLIENT_API_VERSION_MAJOR "${MIR_CLIENT_VERSION}")      # Stringify to guard against empty variable
    string (REGEX REPLACE "^.*MIR_CLIENT_API_VERSION_MINOR.+\(([^\)]*)\).*$" \\1 MIR_CLIENT_API_VERSION_MINOR "${MIR_CLIENT_VERSION}")
    string (REGEX REPLACE "^.*MIR_CLIENT_API_VERSION_PATCH.+\(([^\)]*)\).*$" \\1 MIR_CLIENT_API_VERSION_PATCH "${MIR_CLIENT_VERSION}")
    set (MIR_CLIENT_VERSION "${MIR_CLIENT_API_VERSION_MAJOR}.${MIR_CLIENT_API_VERSION_MINOR}.${MIR_CLIENT_API_VERSION_PATCH}" CACHE INTERNAL "Mirclient version")
endif ()

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (Mir REQUIRED_VARS MIR_CLIENT MIR_COMMON EGL XKB MIR_CLIENT_INCLUDE_DIR MIR_COMMON_INCLUDE_DIR VERSION_VAR MIR_CLIENT_VERSION FAIL_MESSAGE "Could NOT find Mir display server")
if (MIR_FOUND)
    set (MIR_INCLUDE_DIRS ${MIR_CLIENT_INCLUDE_DIR} ${MIR_COMMON_INCLUDE_DIR})
endif ()

mark_as_advanced (MIR_CLIENT_INCLUDE_DIR MIR_COMMON_INCLUDE_DIR MIR_CLIENT MIR_COMMON EGL XKB)
