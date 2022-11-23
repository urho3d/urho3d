# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Find Generic Buffer Management development library
#
#  GBM_FOUND
#  GBM_INCLUDE_DIRS
#  GBM_LIBRARIES
#

find_path (GBM_INCLUDE_DIRS NAMES gbm.h DOC "GenericBufferManagement include directory")
find_library (GBM_LIBRARIES NAMES gbm DOC "GenericBufferManagement library")

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (GBM REQUIRED_VARS GBM_LIBRARIES GBM_INCLUDE_DIRS FAIL_MESSAGE "Could NOT find Direct Generic Buffer Management development library")

mark_as_advanced (GBM_INCLUDE_DIRS GBM_LIBRARIES)
