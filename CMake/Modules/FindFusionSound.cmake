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

# Find FusionSound development library
#
#  FUSIONSOUND_FOUND
#  FUSIONSOUND_INCLUDE_DIRS
#  FUSIONSOUND_LIBRARIES
#  FUSIONSOUND_VERSION
#

find_path (FUSIONSOUND_INCLUDE_DIRS NAMES fusionsound/fusionsound.h DOC "FusionSound include directory")
find_library (FUSIONSOUND_LIBRARIES NAMES fusionsound DOC "FusionSound library")

if (NOT FUSIONSOUND_VERSION AND FUSIONSOUND_INCLUDE_DIRS AND EXISTS ${FUSIONSOUND_INCLUDE_DIRS}/fusionsound/fusionsound_version.h)   # Only do this once
    file (STRINGS ${FUSIONSOUND_INCLUDE_DIRS}/fusionsound/fusionsound_version.h FUSIONSOUND_VERSION REGEX "^.*FUSIONSOUND_(MAJOR|MINOR|MACRO)_VERSION.+\([^\)]*\).*$")
    string (REGEX REPLACE "^.*FUSIONSOUND_MAJOR_VERSION.+\(([^\)]*)\).*$" \\1 FUSIONSOUND_MAJOR_VERSION "${FUSIONSOUND_VERSION}")      # Stringify to guard against empty variable
    string (REGEX REPLACE "^.*FUSIONSOUND_MINOR_VERSION.+\(([^\)]*)\).*$" \\1 FUSIONSOUND_MINOR_VERSION "${FUSIONSOUND_VERSION}")
    string (REGEX REPLACE "^.*FUSIONSOUND_MICRO_VERSION.+\(([^\)]*)\).*$" \\1 FUSIONSOUND_MICRO_VERSION "${FUSIONSOUND_VERSION}")
    set (FUSIONSOUND_VERSION "${FUSIONSOUND_MAJOR_VERSION}.${FUSIONSOUND_MINOR_VERSION}.${FUSIONSOUND_MICRO_VERSION}" CACHE INTERNAL "FusionSound version")
endif ()

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (FusionSound REQUIRED_VARS FUSIONSOUND_LIBRARIES FUSIONSOUND_INCLUDE_DIRS VERSION_VAR FUSIONSOUND_VERSION FAIL_MESSAGE "Could NOT find FusionSound development library")

mark_as_advanced (FUSIONSOUND_INCLUDE_DIRS FUSIONSOUND_LIBRARIES)
