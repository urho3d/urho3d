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

# Find Broadcom VideoCore firmware installation
#
#  VIDEOCORE_FOUND
#  VIDEOCORE_INCLUDE_DIRS
#  VIDEOCORE_LIBRARIES
#  VIDEOCORE_BCM_HOST
#  VIDEOCORE_EGL
#  VIDEOCORE_GLES2
#

# Only need to cater for raspbian as they are not in CMAKE_SYSTEM_PATH
set (VIDEOCORE_INC_SEARCH_PATH /opt/vc/include)
set (VIDEOCORE_LIB_SEARCH_PATH /opt/vc/lib)

# Assume all the other headers are installed at same relative path as bcm_host.h
find_path (VIDEOCORE_INCLUDE_DIRS bcm_host.h PATHS ${VIDEOCORE_INC_SEARCH_PATH} PATH_SUFFIXES vc DOC "Broadcom VideoCore include directory")

# Assume all the other libs are installed at the same relative path as libbcm_host.so
find_library (VIDEOCORE_BCM_HOST bcm_host PATHS ${VIDEOCORE_LIB_SEARCH_PATH} PATH_SUFFIXES vc DOC "Broadcom VideoCore BCM_HOST library")
find_library (VIDEOCORE_EGL EGL PATHS ${VIDEOCORE_LIB_SEARCH_PATH} PATH_SUFFIXES vc DOC "Broadcom VideoCore EGL library")
find_library (VIDEOCORE_GLES2 GLESv2 PATHS ${VIDEOCORE_LIB_SEARCH_PATH} PATH_SUFFIXES vc DOC "Broadcom VideoCore GLESv2 library")

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (VideoCore REQUIRED_VARS VIDEOCORE_BCM_HOST VIDEOCORE_EGL VIDEOCORE_GLES2 VIDEOCORE_INCLUDE_DIRS FAIL_MESSAGE "Could NOT find Broadcom VideoCore firmware")
if (VIDEOCORE_FOUND)
    list (APPEND VIDEOCORE_INCLUDE_DIRS ${VIDEOCORE_INCLUDE_DIRS}/interface/vcos/pthreads ${VIDEOCORE_INCLUDE_DIRS}/interface/vmcs_host/linux)  # Note: variable change to list context after this
    set (VIDEOCORE_LIBRARIES ${VIDEOCORE_BCM_HOST} ${VIDEOCORE_EGL} ${VIDEOCORE_GLES2})
endif ()

mark_as_advanced (VIDEOCORE_INCLUDE_DIRS VIDEOCORE_BCM_HOST VIDEOCORE_EGL VIDEOCORE_GLES2)
