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

# Find Broadcom VideoCore firmware installation
#
#  BCM_VC_FOUND
#  BCM_VC_INCLUDE_DIRS
#  BCM_VC_LIBRARIES
#

# Only need to cater for raspbian as they are not in CMAKE_SYSTEM_PATH
set (BCM_VC_INC_SEARCH_PATH /opt/vc/include)
set (BCM_VC_LIB_SEARCH_PATH /opt/vc/lib)

# Assume all the other headers are installed at same relative path as bcm_host.h
find_path (BCM_VC_INCLUDE_DIRS bcm_host.h PATHS ${BCM_VC_INC_SEARCH_PATH} PATH_SUFFIXES vc DOC "Broadcom VideoCore include directory")

# Assume all the other libs are installed at the same relative path as libbcm_host.so
find_library (BCM_VC_LIB_BCM_HOST bcm_host PATHS ${BCM_VC_LIB_SEARCH_PATH} PATH_SUFFIXES vc DOC "Broadcom VideoCore BCM_HOST library directory")
find_library (BCM_VC_LIB_EGL EGL PATHS ${BCM_VC_LIB_SEARCH_PATH} PATH_SUFFIXES vc DOC "Broadcom VideoCore EGL library directory")
find_library (BCM_VC_LIB_GLES2 GLESv2 PATHS ${BCM_VC_LIB_SEARCH_PATH} PATH_SUFFIXES vc DOC "Broadcom VideoCore GLESv2 library directory")

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (BCM_VC REQUIRED_VARS BCM_VC_LIB_BCM_HOST BCM_VC_LIB_EGL BCM_VC_LIB_GLES2 BCM_VC_INCLUDE_DIRS FAIL_MESSAGE "Could NOT find Broadcom VideoCore firmware")
if (BCM_VC_FOUND)
    list (APPEND BCM_VC_INCLUDE_DIRS ${BCM_VC_INCLUDE_DIRS}/interface/vcos/pthreads)  # Note: variable change to list context after this
    set (BCM_VC_LIBRARIES ${BCM_VC_LIB_BCM_HOST} ${BCM_VC_LIB_EGL} ${BCM_VC_LIB_GLES2})
endif ()

mark_as_advanced (BCM_VC_INCLUDE_DIRS BCM_VC_LIBRARIES BCM_VC_LIB_BCM_HOST BCM_VC_LIB_EGL BCM_VC_LIB_GLES2)
