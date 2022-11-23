#!/usr/bin/env bash

# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

# Determine source tree and build tree
if [[ "$1" ]] && [[ ! "$1" =~ ^- ]]; then BUILD=$1; shift; elif [[ -f $(pwd)/CMakeCache.txt ]]; then BUILD=$(pwd); else caller=$(ps -o args= $PPID |cut -d' ' -f2); if [[ ! "$caller" =~ cmake_.*\.sh$ ]]; then caller=$0; fi; echo "Usage: ${caller##*/} /path/to/build-tree [build-options]"; exit 1; fi
SOURCE=$(cd ${0%/*}/..; pwd)
if [[ "$BUILD" == "." ]]; then BUILD=$(pwd); fi

# Define helpers
. "$SOURCE"/script/.bash_helpers.sh

# Detect CMake toolchains directory if it is not provided explicitly
[ "$TOOLCHAINS" == "" ] && TOOLCHAINS="$SOURCE"/cmake/Toolchains
[ ! -d "$TOOLCHAINS" -a -d "$URHO3D_HOME"/share/Urho3D/cmake/Toolchains ] && TOOLCHAINS="$URHO3D_HOME"/share/Urho3D/cmake/Toolchains

# Default to native generator and toolchain if none is specified explicitly
IFS=#
OPTS=
for a in $@; do
    case ${a#-D} in
        RPI=1)
            if [[ ! $(uname -m) =~ ^(arm|aarch64) ]]; then OPTS=(-D CMAKE_TOOLCHAIN_FILE=$TOOLCHAINS/RaspberryPi.cmake); fi
            ;;
        ARM=1)
            if [[ ! $(uname -m) =~ ^(arm|aarch64) ]]; then OPTS=(-D CMAKE_TOOLCHAIN_FILE=$TOOLCHAINS/Arm.cmake); fi
            ;;
        MINGW=1)
            OPTS=(-D CMAKE_TOOLCHAIN_FILE=$TOOLCHAINS/MinGW.cmake)
            ;;
        WEB=1)
            TOOLCHAINS=(${EMSCRIPTEN_ROOT_PATH}/tools/cmake/Modules/Platform)
            OPTS=(-D CMAKE_TOOLCHAIN_FILE=$TOOLCHAINS/Emscripten.cmake)
            ;;
    esac
done

# Create project with the chosen CMake generator and toolchain
cmake -E make_directory "$BUILD" && cmake -E chdir "$BUILD" cmake ${OPTS[*]} $@ "$SOURCE" && post_cmake

# vi: set ts=4 sw=4 expandtab:
