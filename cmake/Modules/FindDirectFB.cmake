# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

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
