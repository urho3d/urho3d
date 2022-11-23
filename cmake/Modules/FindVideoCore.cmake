# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

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
