# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Find Direct Rendering Manager development library
#
#  DRM_FOUND
#  DRM_INCLUDE_DIRS
#  DRM_LIBRARIES
#

find_path (DRM_INCLUDE_DIRS NAMES drm.h PATH_SUFFIXES libdrm DOC "DirectRenderingManager include directory")
find_library (DRM_LIBRARIES NAMES drm DOC "DirectRenderingManager library")

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (DRM REQUIRED_VARS DRM_LIBRARIES DRM_INCLUDE_DIRS FAIL_MESSAGE "Could NOT find Direct Rendering Manager development library")

mark_as_advanced (DRM_INCLUDE_DIRS DRM_LIBRARIES)
