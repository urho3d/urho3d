# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Get Urho3D library revision number

# Use the same commit-ish used by CI server to describe the repository
if (DEFINED ENV{TRAVIS_COMMIT})
    set (ARG $ENV{TRAVIS_COMMIT})
elseif (DEFINED ENV{APPVEYOR})
    set (ARG $ENV{APPVEYOR_REPO_COMMIT})
else ()
    set (ARG --dirty)
endif ()
execute_process (COMMAND git describe ${ARG} RESULT_VARIABLE GIT_EXIT_CODE OUTPUT_VARIABLE LIB_REVISION ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
if (NOT GIT_EXIT_CODE EQUAL 0)
    # No GIT command line tool or not a GIT repository
    set (LIB_REVISION Unversioned)
endif ()
if (FILENAME)
    # Output complete revision number to a file
    file (WRITE ${FILENAME} "const char* revision=\"${LIB_REVISION}\";\n")
else ()
    # Output just major.minor.patch number to stdout
    string (REGEX MATCH "[^.]+\\.[^-]+" VERSION ${LIB_REVISION})            # Assume release tag always has major.minor format with possible pre-release identifier
    if (VERSION)
        string (REGEX MATCH "${VERSION}-([A-Z]+)" PRE_ID ${LIB_REVISION})   # Workaround as CMake's regex does not support look around
        if (PRE_ID)
            set (VERSION ${VERSION}-${CMAKE_MATCH_1})
        endif ()
        string (REGEX MATCH "${VERSION}-([^-]+)" PATCH ${LIB_REVISION})     # Subsequent commits count after a release tag is treated as patch number
        if (PATCH)
            set (VERSION ${VERSION}.${CMAKE_MATCH_1})
        else ()
            set (VERSION ${VERSION}.0)
        endif ()
    else ()
        set (VERSION 0.0.0)
    endif ()
    execute_process (COMMAND ${CMAKE_COMMAND} -E echo ${VERSION})
endif ()
