# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Find Readline development library
#
#  READLINE_FOUND
#  READLINE_INCLUDE_DIRS
#  READLINE_LIBRARIES
#

if (APPLE AND NOT READLINE_INCLUDE_DIRS AND NOT READLINE_LIBRARIES)
    # Assuming GNU Readline development library is installed using Homebrew (keg-only - prebuilt universal binary)
    execute_process (COMMAND find /usr/local/Cellar/readline -type d -name include OUTPUT_VARIABLE INC_HINTS ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
    execute_process (COMMAND find /usr/local/Cellar/readline -type d -name lib OUTPUT_VARIABLE LIB_HINTS ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
elseif (NATIVE_64BIT AND NOT URHO3D_64BIT)
    # To cater for 32-bit build on 64-bit host system using Debian-based distros; no special handling required for Redhat-based distros but no harm done in doing below
    set (LIB_HINTS /usr/lib32)
endif ()
find_path (READLINE_INCLUDE_DIRS NAMES readline/readline.h HINTS ${INC_HINTS} PATH_SUFFIXES readline DOC "Readline include directory")
if (READLINE_INCLUDE_DIRS AND CMAKE_LIBRARY_ARCHITECTURE)
    list (APPEND READLINE_INCLUDE_DIRS ${READLINE_INCLUDE_DIRS}/${CMAKE_LIBRARY_ARCHITECTURE})
endif ()
find_library (READLINE_LIBRARIES NAMES readline HINTS ${LIB_HINTS} DOC "Readline library")
if (NOT APPLE AND NATIVE_64BIT AND NOT URHO3D_64BIT AND READLINE_LIBRARIES MATCHES 64)
    unset (READLINE_LIBRARIES CACHE)    # Nullify the search result if the ABI is not matched
    unset (READLINE_LIBRARIES)
endif ()

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (Readline REQUIRED_VARS READLINE_LIBRARIES READLINE_INCLUDE_DIRS FAIL_MESSAGE "Could NOT find Readline development library")

mark_as_advanced (READLINE_INCLUDE_DIRS READLINE_LIBRARIES)
