# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Find RoarAudio development library
#
#  SNDIO_FOUND
#  SNDIO_INCLUDE_DIRS
#  SNDIO_LIBRARIES
#

find_path (SNDIO_INCLUDE_DIRS NAMES RoarAudio.h DOC "RoarAudio include directory")
find_library (SNDIO_LIBRARIES NAMES RoarAudio DOC "RoarAudio library")

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (SNDIO REQUIRED_VARS SNDIO_LIBRARIES SNDIO_INCLUDE_DIRS FAIL_MESSAGE "Could NOT find RoarAudio development library")

mark_as_advanced (SNDIO_INCLUDE_DIRS SNDIO_LIBRARIES)
