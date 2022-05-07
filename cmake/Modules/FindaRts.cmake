# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

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
