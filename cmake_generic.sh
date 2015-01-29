#!/usr/bin/env bash
#
# Copyright (c) 2008-2014 the Urho3D project.
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

# Determine source tree and build tree
if [ "$1" ] && [[ ! "$1" =~ ^- ]]; then BUILD=$1; shift; elif [ -f $(pwd)/CMakeCache.txt ]; then BUILD=$(pwd); else echo An error has occured, build tree has to be provided as the first argument OR call this script in a build tree itself; exit 1; fi
SOURCE=$(dirname $0)
if [ "$SOURCE" == "." ]; then SOURCE=$(pwd); fi
if [ "$BUILD" == "." ]; then BUILD=$(pwd); fi

# Define helpers
. "$SOURCE"/.bash_helpers.sh

# Detect CMake toolchains directory if it is not provided explicitly
[ "$TOOLCHAINS" == "" ] && TOOLCHAINS=$SOURCE/CMake/Toolchains
[ ! -d "$TOOLCHAINS" -a -d $URHO3D_HOME/share/Urho3D/CMake/Toolchains ] && TOOLCHAINS=$URHO3D_HOME/share/Urho3D/CMake/Toolchains

# Default to native generator and toolchain if none is specified explicitly
IFS=#
OPTS=
for a in $@; do
    case $a in
        --fix-scm)
            FIX_SCM=1
            ;;
        Eclipse\ CDT4\ -\ Unix\ Makefiles)
            ECLIPSE=1 && if xmlstarlet --version >/dev/null 2>&1; then HAS_XMLSTARLET=1; fi
            ;;
        -DIOS=1)
            IOS=1
            ;;
        -DANDROID=1)
            ANDROID=1 && OPTS="-DCMAKE_TOOLCHAIN_FILE=$TOOLCHAINS/android.toolchain.cmake"
            ;;
        -DRPI=1)
            RPI=1 && if [[ ! $(uname -m) =~ ^armv6 ]]; then OPTS="-DCMAKE_TOOLCHAIN_FILE=$TOOLCHAINS/raspberrypi.toolchain.cmake"; fi
            ;;
        -DWIN32=1)
            WINDOWS=1 && OPTS="-DCMAKE_TOOLCHAIN_FILE=$TOOLCHAINS/mingw.toolchain.cmake"
            ;;
    esac
done

# Create project with the chosen CMake generator and toolchain
cmake -E make_directory "$BUILD" && cmake -E chdir "$BUILD" cmake $OPTS $@ "$SOURCE" && post_cmake
unset IFS

# vi: set ts=4 sw=4 expandtab:
