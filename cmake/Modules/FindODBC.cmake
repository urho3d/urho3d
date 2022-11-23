# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Find ODBC driver manager
#
#  ODBC_FOUND
#  ODBC_INCLUDE_DIRS
#  ODBC_LIBRARIES
#  ODBC_DEFINES
#  ODBC_VERSION
#

if (WIN32)
    set (ODBC_INCLUDE_DIRS " ")     # The headers should be available in the default include search path
    set (ODBC_LIBRARIES odbc32 odbccp32 ws2_32) # This should be also the case for MinGW cross-compiler toolchain
    set (ODBC_DEFINES)
    set (ODBC_VERSION 3)        # Assume it is 3
else ()
    # On Unix-like host system, use the ODBC config tool
    find_program (ODBC_CONFIG NAMES odbc_config iodbc-config DOC "ODBC config tool" NO_CMAKE_FIND_ROOT_PATH)
    if (ODBC_CONFIG AND NOT ODBC_INCLUDE_DIRS AND NOT ODBC_LIBRARIES)   # Only do this once
        # Get ODBC compile and link flags and turn them into include dirs and libraries list
        execute_process (COMMAND ${ODBC_CONFIG} --cflags OUTPUT_VARIABLE ODBC_COMPILE_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
        execute_process (COMMAND ${ODBC_CONFIG} --libs OUTPUT_VARIABLE ODBC_LINK_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
        string (REGEX REPLACE " *-I" ";" ODBC_INCLUDE_DIRS "${ODBC_COMPILE_FLAGS}")    # Stringify in case it returns empty string
        string (REGEX REPLACE " *-l" ";" ODBC_LIBRARIES "${ODBC_LINK_FLAGS}")
        list (GET ODBC_INCLUDE_DIRS 0 ODBC_DEFINES)     # Assume the list of defines always come before the list of include dirs
        list (REMOVE_AT ODBC_INCLUDE_DIRS 0)
        list (REMOVE_AT ODBC_LIBRARIES 0)
        set (ODBC_INCLUDE_DIRS ${ODBC_INCLUDE_DIRS} CACHE PATH "ODBC include directory")
        set (ODBC_LIBRARIES ${ODBC_LIBRARIES} CACHE STRING "ODBC library")
        set (ODBC_DEFINES ${ODBC_DEFINES} CACHE STRING "ODBC defines")
        # Get ODBC version
        execute_process (COMMAND ${ODBC_CONFIG} --odbcversion OUTPUT_VARIABLE ODBC_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
        set (ODBC_VERSION ${ODBC_VERSION} CACHE INTERNAL "ODBC version")
    endif ()
endif ()

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (ODBC REQUIRED_VARS ODBC_LIBRARIES ODBC_INCLUDE_DIRS VERSION_VAR ODBC_VERSION FAIL_MESSAGE "Could NOT find ODBC driver manager, please install the development package for unixODBC or libiodbc")

mark_as_advanced (ODBC_INCLUDE_DIRS ODBC_LIBRARIES ODBC_DEFINES ODBC_CONFIG)
