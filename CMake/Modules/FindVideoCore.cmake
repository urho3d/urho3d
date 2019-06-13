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

# Find Broadcom VideoCore firmware installation
#
#  VIDEOCORE_FOUND
#  VIDEOCORE_INCLUDE_DIRS
#  VIDEOCORE_LIBRARY_DIRS
#  VIDEOCORE_LIBRARIES
#

# Only need to cater for raspbian as they are not in CMAKE_SYSTEM_PATH
set (VIDEOCORE_INC_SEARCH_PATH /opt/vc/include)
set (VIDEOCORE_LIB_SEARCH_PATH /opt/vc/lib)

find_path (VIDEOCORE_INCLUDE_DIRS bcm_host.h PATHS ${VIDEOCORE_INC_SEARCH_PATH} PATH_SUFFIXES vc DOC "Broadcom VideoCore include directory")
find_library (VIDEOCORE_LIBRARIES bcm_host PATHS ${VIDEOCORE_LIB_SEARCH_PATH} PATH_SUFFIXES vc DOC "Broadcom VideoCore BCM_HOST library")

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (VideoCore REQUIRED_VARS VIDEOCORE_LIBRARIES VIDEOCORE_INCLUDE_DIRS FAIL_MESSAGE "Could NOT find Broadcom VideoCore firmware")
if (VIDEOCORE_FOUND)
    # Assume all the other headers are installed at same relative path as bcm_host.h
    list (APPEND VIDEOCORE_INCLUDE_DIRS ${VIDEOCORE_INCLUDE_DIRS}/interface/vcos/pthreads ${VIDEOCORE_INCLUDE_DIRS}/interface/vmcs_host/linux)
    # Assume all the other libraries are installed at same relative path as libbcm_host.so
    get_filename_component (VIDEOCORE_LIBRARY_DIRS ${VIDEOCORE_LIBRARIES} PATH)
    set (VIDEOCORE_LIBRARIES bcm_host)
endif ()

mark_as_advanced (VIDEOCORE_INCLUDE_DIRS VIDEOCORE_LIBRARIES)
