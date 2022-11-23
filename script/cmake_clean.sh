#!/usr/bin/env bash

# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Clean the CMake cache and CMake generated files in the build tree
if [[ "$1" ]] && [[ -f "$1"/CMakeCache.txt ]]; then BUILD=$1; elif [[ -f $(pwd)/CMakeCache.txt ]]; then BUILD=$(pwd); else echo Usage: ${0##*/} /path/to/build-tree; exit 1; fi
rm -rf "$BUILD"/{CMakeCache.txt,CMakeFiles}
touch "$BUILD"/CMakeCache.txt

# vi: set ts=4 sw=4 expandtab:
