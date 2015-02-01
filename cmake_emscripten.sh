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

# Ensure we are in project root directory
cd $( dirname $0 )
SOURCE=`pwd`/Source


# Detect CMake toolchains directory
TOOLCHAINS=$SOURCE/CMake/Toolchains
[ ! -d $TOOLCHAINS -a -d $URHO3D_HOME/Source/CMake/Toolchains ] && TOOLCHAINS=$URHO3D_HOME/Source/CMake/Toolchains

IFS=#
GENERATOR="Unix Makefiles"



# Create project with the respective CMake generators

cmake -E make_directory emscripten-Build && cmake -E chdir emscripten-Build cmake $OPT -G $GENERATOR -DCMAKE_BUILD_TYPE=Release -DEMSCRIPTEN=1 -DURHO3D_JAVASCRIPT=0 -DURHO3D_TBUI=0 -DURHO3D_ANGELSCRIPT=0 -DURHO3D_NETWORK=0 -DURHO3D_PHYSICS=1 -DURHO3D_NAVIGATION=1 -DURHO3D_64BIT=0 -DURHO3D_SSE=0 -DURHO3D_TOOLS=0 -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAINS/emscripten.toolchain.cmake -DLIBRARY_OUTPUT_PATH_ROOT=. $@ $SOURCE
unset IFS


exit 0

# vi: set ts=4 sw=4 expandtab:
