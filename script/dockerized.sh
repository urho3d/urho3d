#!/usr/bin/env bash
#
# Copyright (c) 2008-2018 the Urho3D project.
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

if [[ $# -eq 0 ]]; then echo "Usage: dockerized.sh native|mingw|android|rpi|arm|web [command [params]]"; exit 1; fi

PROJECT_DIR=$(cd ${0%/*}/..; pwd)
PLATFORM=$1; shift

docker run -it --rm -h fishtank \
    -e HOST_UID=$(id -u) -e HOST_GID=$(id -g) \
    --env-file $PROJECT_DIR/.env-file \
    --mount type=bind,source=$PROJECT_DIR,target=/project_dir \
    --mount source=ccache_dir,target=/ccache_dir \
    --name dockerized-$PLATFORM \
    urho3d/dockerized-$PLATFORM $@

# vi: set ts=4 sw=4 expandtab:
