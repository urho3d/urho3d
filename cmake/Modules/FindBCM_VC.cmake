#
# Copyright (c) 2008-2013 the Urho3D project.
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
#  BCM_VC_INCLUDE_DIR
#  BCM_VC_LIBRARIES
#

if (RASPI)
    set (BCM_VC_FOUND 0)
  
    set (BCM_VC_INC_SEARCH_PATH
        /usr/include
        /opt/vc/include
    )

    set (BCM_VC_LIB_SEARCH_PATH
        /usr/lib
        /opt/vc/lib
    )

    # Assume all the other headers are installed at same relative path as bcm_host.h
    find_path (BCM_VC_INCLUDE_DIR bcm_host.h ${BCM_VC_INC_SEARCH_PATH})
    
    # Assume all the other libs are installed at the same relative path as libbcm_host.so
    find_library (BCM_VC_LIBRARIES bcm_host ${BCM_VC_LIB_SEARCH_PATH})

    if (BCM_VC_INCLUDE_DIR AND BCM_VC_LIBRARIES)
        set (BCM_VC_FOUND 1)
    endif ()

    if (BCM_VC_FOUND)
        include (FindPackageMessage)
        FIND_PACKAGE_MESSAGE (BCM_VC "Found Broadcom VideoCore firmware: ${BCM_VC_LIBRARIES} ${BCM_VC_INCLUDE_DIR}" "[${BCM_VC_LIBRARIES}][${BCM_VC_INCLUDE_DIR}]")
    else ()
        if (BCM_VC_FIND_REQUIRED)
            message (FATAL_ERROR "Could not find Broadcom VideoCore firmware")
        endif ()
    endif ()
 
    mark_as_advanced (BCM_VC_INCLUDE_DIR BCM_VC_LIBRARIES)
endif ()
