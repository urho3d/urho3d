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

# Find aRts development library
#
#  ARTS_FOUND
#  ARTS_INCLUDE_DIRS
#  ARTS_LIBRARIES
#  ARTS_VERSION
#

find_path (ARTS_INCLUDE_DIRS NAMES artsc/artsc.h PATH_SUFFIXES kde DOC "aRts include directory")
find_library (ARTS_LIBRARIES NAMES artsc DOC "aRts library")

if (NOT ARTS_VERSION AND ARTS_INCLUDE_DIRS AND EXISTS ${ARTS_INCLUDE_DIRS}/arts/artsversion.h)   # Only do this once
    file (STRINGS ${ARTS_INCLUDE_DIRS}/arts/artsversion.h ARTS_VERSION REGEX "^.*ARTS_VERSION.+\"[^\"]*\".*$")
    string (REGEX REPLACE "^.*ARTS_VERSION.+\"([^\"]*)\".*$" \\1 ARTS_VERSION "${ARTS_VERSION}")      # Stringify to guard against empty variable
    set (ARTS_VERSION "${ARTS_VERSION}" CACHE INTERNAL "aRts version")
endif ()

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (aRts REQUIRED_VARS ARTS_LIBRARIES ARTS_INCLUDE_DIRS VERSION_VAR ARTS_VERSION FAIL_MESSAGE "Could NOT find aRts development library")

mark_as_advanced (ARTS_INCLUDE_DIRS ARTS_LIBRARIES)
