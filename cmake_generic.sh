#!/usr/bin/env bash
#
# Copyright (c) 2008-2016 the Urho3D project.
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
if [ "$1" ] && [[ ! "$1" =~ ^- ]]; then BUILD=$1; shift; elif [ -f $(pwd)/CMakeCache.txt ]; then BUILD=$(pwd); else caller=$(ps -o args= $PPID |cut -d' ' -f2); if [[ ! "$caller" =~ cmake_.*\.sh$ ]]; then caller=$0; fi; echo "Usage: ${caller##*/} /path/to/build-tree [build-options]"; exit 1; fi
SOURCE=$(cd ${0%/*}; pwd)
if [ "$BUILD" == "." ]; then BUILD=$(pwd); fi

# Define helpers
. "$SOURCE"/.bash_helpers.sh

# Detect CMake toolchains directory if it is not provided explicitly
[ "$TOOLCHAINS" == "" ] && TOOLCHAINS="$SOURCE"/CMake/Toolchains
[ ! -d "$TOOLCHAINS" -a -d "$URHO3D_HOME"/share/Urho3D/CMake/Toolchains ] && TOOLCHAINS="$URHO3D_HOME"/share/Urho3D/CMake/Toolchains

# Default to native generator and toolchain if none is specified explicitly
IFS=#
OPTS=
for a in $@; do
    case $a in
        --fix-scm)
            FIX_SCM=1
            ;;
        Eclipse\ CDT4\ -\ Unix\ Makefiles)
            ECLIPSE=1
            ;;
        -DIOS=1)
            IOS=1
            ;;
        -DANDROID=1)
            ANDROID=1 && OPTS="-DCMAKE_TOOLCHAIN_FILE=$TOOLCHAINS/android.toolchain.cmake"
            ;;
        -DRPI=1)
            if [[ ! $(uname -m) =~ ^arm ]]; then OPTS="-DCMAKE_TOOLCHAIN_FILE=$TOOLCHAINS/raspberrypi.toolchain.cmake"; fi
            ;;
        -DWIN32=1)
            OPTS="-DCMAKE_TOOLCHAIN_FILE=$TOOLCHAINS/mingw.toolchain.cmake"
            ;;
        -DWEB=1)
            OPTS="-DCMAKE_TOOLCHAIN_FILE=$TOOLCHAINS/emscripten.toolchain.cmake"
            ;;
    esac
done

# Create project with the chosen CMake generator and toolchain
cmake -E make_directory "$BUILD" && cmake -E chdir "$BUILD" cmake $OPTS $@ "$SOURCE" && post_cmake

# vi: set ts=4 sw=4 expandtab:
