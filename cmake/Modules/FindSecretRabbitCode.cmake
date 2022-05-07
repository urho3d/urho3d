# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Find Secret Rabbit Code development library
#
#  SECRETRABBITCODE_FOUND
#  SECRETRABBITCODE_INCLUDE_DIRS
#  SECRETRABBITCODE_LIBRARIES
#

find_path (SECRETRABBITCODE_INCLUDE_DIRS NAMES samplerate.h DOC "SecretRabbitCode include directory")
find_library (SECRETRABBITCODE_LIBRARIES NAMES samplerate DOC "SecretRabbitCode library")

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (SecretRabbitCode REQUIRED_VARS SECRETRABBITCODE_LIBRARIES SECRETRABBITCODE_INCLUDE_DIRS FAIL_MESSAGE "Could NOT find Secret Rabbit Code (aka libsamplerate) development library")

mark_as_advanced (SECRETRABBITCODE_INCLUDE_DIRS SECRETRABBITCODE_LIBRARIES)
