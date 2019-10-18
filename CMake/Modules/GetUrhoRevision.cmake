#
# Copyright (c) 2008-2019 the Urho3D project.
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
    set (LIB_REVISION "0.0-Unversioned")
endif ()

# Output just major.minor.patch number to stdout
string (REGEX MATCH "[^.]+\\.[^-]+" VERSION ${LIB_REVISION})            # Assume release tag always has major.minor format
if (VERSION)
    string (REGEX MATCH "${VERSION}-([^-]+)" PATCH ${LIB_REVISION})     # Subsequent commits count after a release tag is treated as patch number
    if (PATCH)
        set (VERSION ${VERSION}.${CMAKE_MATCH_1})
    endif ()
else ()
    set (VERSION 0.0.0)
endif ()

set (URHO3D_VERSION_MAJOR 0)
set (URHO3D_VERSION_MINOR 0)
set (URHO3D_VERSION_PATCH 0)

string (REGEX MATCH "([^.]+)\\.([^.]+)\\.(.+)" MATCHED ${VERSION})
if (MATCHED)
    set (URHO3D_VERSION_MAJOR ${CMAKE_MATCH_1})
    set (URHO3D_VERSION_MINOR ${CMAKE_MATCH_2})
    set (URHO3D_VERSION_PATCH ${CMAKE_MATCH_3})
    
    string (REGEX MATCH "(^[0-9]+)" PATCH ${CMAKE_MATCH_3})
    if (NOT PATCH)
        set (URHO3D_VERSION_PATCH 0)
    endif ()
endif ()

if (FILENAME)
    # Output complete revision number to a file
    file (WRITE ${FILENAME} "#pragma once\n")
    file (APPEND ${FILENAME} "const char* revision=\"${LIB_REVISION}\";\n")

    file (APPEND ${FILENAME} "/**"
        "\n*  \\brief Information the version of Urho3D in use."
        "\n*"
        "\n*  Represents the library's version as three levels: major revision"
        "\n*  (increments with massive changes, additions, and enhancements),"
        "\n*  minor revision (increments with backwards-compatible changes to the"
        "\n*  major revision), and patchlevel (increments with fixes to the minor"
        "\n*  revision)."
        "\n*"
        "\n*  \\sa URHO3D_VERSION"
        "\n*  \\sa ::Urho3D::GetVersion"
        "\n*/"
        "\ntypedef struct UrhoVersion"
        "\n{"
        "\n    ///major version"
        "\n    unsigned char major;"
        "\n    ///minor version"
        "\n    unsigned char minor;"
        "\n    ///patch version"
        "\n    unsigned char patch;"
        "\n} UrhoVersion;"
    )

file (APPEND ${FILENAME} "\n\n///Printable format: \"%d.%d.%d\", MAJOR, MINOR, PATCHLEVEL"
    "\n#define URHO3D_MAJOR_VERSION   " ${URHO3D_VERSION_MAJOR}
    "\n#define URHO3D_MINOR_VERSION   " ${URHO3D_VERSION_MINOR}
    "\n#define URHO3D_PATCHLEVEL      " ${URHO3D_VERSION_PATCH})

file (APPEND ${FILENAME} "\n\n/**"
    "\n*  \\brief Macro to determine Urho3D version program was compiled against."
    "\n*"
    "\n*  This macro fills in a UrhoVersion structure with the version of the"
    "\n*  library you compiled against. This is determined by what header the"
    "\n*  compiler uses. Note that if you dynamically linked the library, you might"
    "\n*  have a slightly newer or older version at runtime. That version can be"
    "\n*  determined with SDL_GetVersion(), which, unlike SDL_VERSION(),"
    "\n*  is not a macro."
    "\n*"
    "\n*  \\param x A pointer to a UrhoVersion struct to initialize."
    "\n*"
    "\n*  \\sa UrhoVersion"
    "\n*  \\sa SDL_GetVersion"
    "\n*/"
    "\n#define URHO3D_VERSION(x) {                        " "\\"
    "\n    (x)->major = URHO3D_MAJOR_VERSION;           " "\\"
    "\n    (x)->minor = URHO3D_MINOR_VERSION;           " "\\"
    "\n    (x)->patch = URHO3D_PATCHLEVEL;              " "\\"
    "\n}")

file (APPEND ${FILENAME} "\n\n///This macro turns the version numbers into a numeric value:"
    "\n///    (1,2,3) -> (1203)"
    "\n///This assumes that there will never be more than 100 patchlevels."
    "\n#define URHO3D_VERSIONNUM(X, Y, Z) " "\\"
    "\n    ((X)*1000 + (Y)*100 + (Z))")

file (APPEND ${FILENAME} "\n\n///This is the version number macro for the current URHO version."
    "\n#define URHO3D_COMPILEDVERSION " "\\"
    "\n    URHO3D_VERSIONNUM(URHO3D_MAJOR_VERSION, URHO3D_MINOR_VERSION, URHO3D_PATCHLEVEL)")

file (APPEND ${FILENAME} "\n\n///This macro will evaluate to true if compiled with URHO at least X.Y.Z."
    "\n#define URHO3D_VERSION_ATLEAST(X, Y, Z) " "\\"
    "\n    (URHO3D_COMPILEDVERSION >= URHO3D_VERSIONNUM(X, Y, Z))")

else ()
    # Output just major.minor.patch number to stdout
    execute_process (COMMAND ${CMAKE_COMMAND} -E echo ${VERSION})
endif ()
