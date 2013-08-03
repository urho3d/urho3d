#!/usr/bin/env bash
#
# Copyright (c) 2008-2013 the Urho3D project.
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

# This script is being called by CMake during GCC build
# PLEASE DO NOT EDIT unless you know what you are doing
[ "$1" == "OUTDIR" ] && shift || exit 1
outdir=$1; shift
[ "$1" == "OBJECTS" ] && shift || exit 1
while [ "$1" != "TARGETS" ]; do hasobjects=1; shift; done
[ "$1" == "TARGETS" ] && shift || exit 1
IFS=\;; for target in $1; do externalobjects="$externalobjects $(cat $outdir/$target.obj)"; done; unset IFS; shift
[ "$1" == "FRAMEWORKS" ] && shift || exit 1
while [ "$1" != "COMMAND" ]; do frameworks="$frameworks $1"; shift; done
[ "$1" == "COMMAND" ] && shift || exit 1
command=$@
[ $hasobjects ] && command="$command $externalobjects $frameworks"
$command
