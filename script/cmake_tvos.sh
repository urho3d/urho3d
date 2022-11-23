#!/usr/bin/env bash

# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

$(dirname $0)/cmake_generic.sh "$@" -G Xcode -D TVOS=1 -T buildsystem=1

# vi: set ts=4 sw=4 expandtab:
