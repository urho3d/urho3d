# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Find PulseAudio development library
#
#  PULSEAUDIO_FOUND
#  PULSEAUDIO_INCLUDE_DIRS
#  PULSEAUDIO_LIBRARIES
#  PULSEAUDIO_VERSION
#

find_path (PULSEAUDIO_INCLUDE_DIRS NAMES pulse/pulseaudio.h DOC "PulseAudio include directory")
find_library (PULSEAUDIO_LIBRARIES NAMES pulse-simple DOC "PulseAudio library")

if (NOT PULSEAUDIO_VERSION AND PULSEAUDIO_INCLUDE_DIRS AND EXISTS ${PULSEAUDIO_INCLUDE_DIRS}/pulse/version.h)   # Only do this once
    file (STRINGS ${PULSEAUDIO_INCLUDE_DIRS}/pulse/version.h PULSEAUDIO_VERSION REGEX "^.*pa_get_headers_version.+\"[^\"]*\".*$")
    string (REGEX REPLACE "^.*pa_get_headers_version.+\"([^\"]*)\".*$" \\1 PULSEAUDIO_VERSION "${PULSEAUDIO_VERSION}")      # Stringify to guard against empty variable
    set (PULSEAUDIO_VERSION "${PULSEAUDIO_VERSION}" CACHE INTERNAL "PulseAudio version")
endif ()

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (PulseAudio REQUIRED_VARS PULSEAUDIO_LIBRARIES PULSEAUDIO_INCLUDE_DIRS VERSION_VAR PULSEAUDIO_VERSION FAIL_MESSAGE "Could NOT find PulseAudio development library")

mark_as_advanced (PULSEAUDIO_INCLUDE_DIRS PULSEAUDIO_LIBRARIES)
