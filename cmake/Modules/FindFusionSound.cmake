# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

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
