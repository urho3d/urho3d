#
# Copyright (c) 2008-2015 the Urho3D project.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#

# Find ODBC driver manager
#
#  ODBC_FOUND
#  ODBC_INCLUDE_DIRS
#  ODBC_LIBRARIES
#  ODBC_DEFINES
#  ODBC_VERSION
#

if (ODBC_FOUND)
    return ()
endif ()

if (WIN32)
    set (ODBC_INCLUDE_DIRS)     # The headers should be available in the default include search path
    set (ODBC_LIBRARIES odbc32) # This should be also the case for MinGW cross-compiler toolchain
    set (ODBC_DEFINES)
    set (ODBC_VERSION 3)        # Assume it is 3
    set (ODBC_FOUND 1)
else ()
    # On Unix-like host system, use the ODBC config tool
    find_program (ODBC_CONFIG NAMES odbc_config iodbc-config DOC "ODBC config tool" NO_CMAKE_FIND_ROOT_PATH)
    if (ODBC_CONFIG)
        # Get ODBC compile and link flags and turn them into include dirs and libraries list
        execute_process (COMMAND ${ODBC_CONFIG} --cflags OUTPUT_VARIABLE ODBC_COMPILE_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
        execute_process (COMMAND ${ODBC_CONFIG} --libs OUTPUT_VARIABLE ODBC_LINK_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
        string (REGEX REPLACE " *-I" ";" ODBC_INCLUDE_DIRS "${ODBC_COMPILE_FLAGS}")    # Stringify in case it returns empty string
        string (REGEX REPLACE " *-l" ";" ODBC_LIBRARIES "${ODBC_LINK_FLAGS}")
        list (GET ODBC_INCLUDE_DIRS 0 ODBC_DEFINES)     # Assume the list of defines always come before the list of include dirs
        list (REMOVE_AT ODBC_INCLUDE_DIRS 0)
        list (REMOVE_AT ODBC_LIBRARIES 0)
        # Get ODBC version
        execute_process (COMMAND ${ODBC_CONFIG} --odbcversion OUTPUT_VARIABLE ODBC_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
        set (ODBC_FOUND 1)
    endif ()
endif ()

if (ODBC_FOUND)
    include (FindPackageMessage)
    FIND_PACKAGE_MESSAGE (ODBC "Found ODBC driver manager: ${ODBC_LIBRARIES} ${ODBC_INCLUDE_DIRS}" "[${ODBC_LIBRARIES}][${ODBC_INCLUDE_DIRS}]")
elseif (ODBC_FIND_REQUIRED)
    message (FATAL_ERROR "Could not find ODBC driver manager, please install the development package of unixODBC or libiodbc")
endif ()

mark_as_advanced (ODBC_INCLUDE_DIRS ODBC_LIBRARIES ODBC_DEFINES ODBC_VERSION ODBC_CONFIG)
