#
# Copyright (c) 2008-2021 the Urho3D project.
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

# Find DirectFB development library
#
#  DIRECTFB_FOUND
#  DIRECTFB_INCLUDE_DIRS
#  DIRECTFB_LIBRARIES
#  DIRECTFB_VERSION
#

find_path (DIRECTFB_INCLUDE_DIRS NAMES directfb.h PATH_SUFFIXES directfb DOC "DirectFB include directory")
find_library (DIRECTFB_LIBRARIES NAMES directfb DOC "DirectFB library")

if (NOT DIRECTFB_VERSION AND DIRECTFB_INCLUDE_DIRS AND EXISTS ${DIRECTFB_INCLUDE_DIRS}/directfb_version.h)   # Only do this once
    file (STRINGS ${DIRECTFB_INCLUDE_DIRS}/directfb_version.h DIRECTFB_VERSION REGEX "^.*DIRECTFB_(MAJOR|MINOR|MACRO)_VERSION.+\([^\)]*\).*$")
    string (REGEX REPLACE "^.*DIRECTFB_MAJOR_VERSION.+\(([^\)]*)\).*$" \\1 DIRECTFB_MAJOR_VERSION "${DIRECTFB_VERSION}")      # Stringify to guard against empty variable
    string (REGEX REPLACE "^.*DIRECTFB_MINOR_VERSION.+\(([^\)]*)\).*$" \\1 DIRECTFB_MINOR_VERSION "${DIRECTFB_VERSION}")
    string (REGEX REPLACE "^.*DIRECTFB_MICRO_VERSION.+\(([^\)]*)\).*$" \\1 DIRECTFB_MICRO_VERSION "${DIRECTFB_VERSION}")
    set (DIRECTFB_VERSION "${DIRECTFB_MAJOR_VERSION}.${DIRECTFB_MINOR_VERSION}.${DIRECTFB_MICRO_VERSION}" CACHE INTERNAL "DirectFB version")
endif ()

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (DirectFB REQUIRED_VARS DIRECTFB_LIBRARIES DIRECTFB_INCLUDE_DIRS VERSION_VAR DIRECTFB_VERSION FAIL_MESSAGE "Could NOT find DirectFB development library")

mark_as_advanced (DIRECTFB_INCLUDE_DIRS DIRECTFB_LIBRARIES)
