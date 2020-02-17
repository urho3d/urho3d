#!/usr/bin/env bash
#
# Copyright (c) 2008-2020 the Urho3D project.
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

PROJECT_DIR=$(cd "${0%/*}/.." || exit 1; pwd)

if [[ ! $DBE_TAG ]]; then
    # If the command failed or not on a tag then use 'master' by default; TRAVIS_COMMIT should be empty for non-CI usage
    DBE_TAG=$(git describe --exact-match "$TRAVIS_COMMIT" 2>/dev/null || echo master)
fi

BuildEnvironment=-$1; shift
BuildEnvironment=${BuildEnvironment/-base}

# Determine which tool is available to use
if ! docker --version >/dev/null 2>&1; then
    if podman --version >/dev/null 2>&1; then
        use_podman=1
        # Disable SELinux protection in order to mount Urho3D project root directory from host to container in unprivileged mode
        run_option="--security-opt label=disable"
        # Podman mount volume as 'noexec' by default but we need 'exec' for Android build (aapt2 permission denied otherwise)
        mount_option=,exec
    else
        echo "Could not find Docker client or podman"
        exit 1
    fi
fi

d () {
    if [[ $use_podman ]]; then
        podman "$@"
    else
        docker "$@"
    fi
}

if [[ $TRAVIS ]]; then
  # Workaround Travis-CI intermittent network I/O error
  while (! d pull "urho3d/dockerized$BuildEnvironment:$DBE_TAG"); do sleep 10; done;
elif [[ $DBE_REFRESH == 1 ]]; then
  d pull "urho3d/dockerized$BuildEnvironment:$DBE_TAG"
fi

if [[ $use_podman ]] || ( [[ $(d version -f '{{.Client.Version}}') =~ ^([0-9]+)\.0*([0-9]+)\. ]] && (( BASH_REMATCH[1] * 100 + BASH_REMATCH[2] >= 1809 )) ); then
    # podman or newer Docker client
    d run -it --rm -h fishtank $run_option \
        -e HOST_UID="$(id -u)" -e HOST_GID="$(id -g)" -e PROJECT_DIR="$PROJECT_DIR" \
        --env-file "$PROJECT_DIR/script/.env-file" \
        --mount type=bind,source="$PROJECT_DIR",target="$PROJECT_DIR" \
        --mount type=volume,source="$(id -u).urho3d_home_dir",target=/home/urho3d$mount_option \
        "urho3d/dockerized$BuildEnvironment:$DBE_TAG" "$@"
else
    # Fallback workaround on older Docker CLI version
    d run -it --rm -h fishtank \
        -e HOST_UID="$(id -u)" -e HOST_GID="$(id -g)" -e PROJECT_DIR="$PROJECT_DIR" \
        --env-file <(perl -ne 'chomp; print "$_\n" if defined $ENV{$_}' "$PROJECT_DIR/script/.env-file") \
        --mount type=bind,source="$PROJECT_DIR",target="$PROJECT_DIR" \
        --mount type=volume,source="$(id -u).urho3d_home_dir",target=/home/urho3d \
        "urho3d/dockerized$BuildEnvironment:$DBE_TAG" "$@"
fi

# vi: set ts=4 sw=4 expandtab:
