#!/usr/bin/env bash
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

if [[ $# -eq 0 ]]; then echo "Usage: dockerized.sh native|mingw|android|rpi|arm|web [command [params]]"; exit 1; fi

PROJECT_DIR=$(cd ${0%/*}/..; pwd)

if [[ ! $DBE_TAG ]]; then
    DBE_TAG=$(git describe --exact-match 2>/dev/null)
    # If the command failed or not on a tag then use ':master' by default
    if [[ $? -ne 0 ]]; then DBE_TAG=:master; fi
fi

BuildEnvironment=-$1; shift
BuildEnvironment=${BuildEnvironment/-base}

# Workaround Travis-CI intermittent network I/O error
if [[ $TRAVIS ]]; then while (! docker pull urho3d/dockerized$BuildEnvironment); do sleep 10; done; fi

if [[ $(docker version -f {{.Client.Version}}) =~ ^([0-9]+)\.0*([0-9]+)\. ]] && (( ${BASH_REMATCH[1]} * 100 + ${BASH_REMATCH[2]} >= 1809 )); then
    docker run -it --rm -h fishtank \
        -e HOST_UID=$(id -u) -e HOST_GID=$(id -g) -e PROJECT_DIR=$PROJECT_DIR \
        --env-file $PROJECT_DIR/script/.env-file \
        --mount type=bind,source=$PROJECT_DIR,target=$PROJECT_DIR \
        --mount source=$(id -u).urho3d_home_dir,target=/home/urho3d \
        --name dockerized$BuildEnvironment \
        urho3d/dockerized$BuildEnvironment$DBE_TAG $@
else
    # Fallback workaround on older Docker CLI version
    docker run -it --rm -h fishtank \
        -e HOST_UID=$(id -u) -e HOST_GID=$(id -g) -e PROJECT_DIR=$PROJECT_DIR \
        --env-file <(perl -ne 'chomp; print "$_\n" if defined $ENV{$_}' $PROJECT_DIR/script/.env-file) \
        --mount type=bind,source=$PROJECT_DIR,target=$PROJECT_DIR \
        --mount source=$(id -u).urho3d_home_dir,target=/home/urho3d \
        --name dockerized$BuildEnvironment \
        urho3d/dockerized$BuildEnvironment$DBE_TAG $@
fi

# vi: set ts=4 sw=4 expandtab:
