# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Find NetworkAudioSystem development library
#
#  NAS_FOUND
#  NAS_INCLUDE_DIRS
#  NAS_LIBRARIES
#

find_path (NAS_INCLUDE_DIRS NAMES audio/audiolib.h nas/audiolib.h DOC "NetworkAudioSystem include directory")
find_library (NAS_LIBRARIES NAMES audio DOC "NetworkAudioSystem library")

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (NAS REQUIRED_VARS NAS_LIBRARIES NAS_INCLUDE_DIRS FAIL_MESSAGE "Could NOT find NetworkAudioSystem development library")

mark_as_advanced (NAS_INCLUDE_DIRS NAS_LIBRARIES)
