# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Find Esound development library
#
#  ESOUND_FOUND
#  ESOUND_INCLUDE_DIRS
#  ESOUND_LIBRARIES
#

find_path (ESOUND_INCLUDE_DIRS NAMES esd.h DOC "Esound include directory")
find_library (ESOUND_LIBRARIES NAMES esd DOC "Esound library")

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (Esound REQUIRED_VARS ESOUND_LIBRARIES ESOUND_INCLUDE_DIRS FAIL_MESSAGE "Could NOT find Esound development library")

mark_as_advanced (ESOUND_INCLUDE_DIRS ESOUND_LIBRARIES)
