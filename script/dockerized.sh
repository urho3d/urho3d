#!/usr/bin/env bash

# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

if [[ $# -eq 0 ]]; then echo "Usage: dockerized.sh linux|mingw|android|rpi|arm|web [command]"; exit 1; fi
if [[ $(id -u) -eq 0 ]]; then echo "Should not run using sudo or root user"; exit 1; fi

SCRIPT_DIR=$(cd "${0%/*}" || exit 1; pwd)
PROJECT_DIR=$(cd "${0%/*}/.." || exit 1; pwd)

# Determine which tool is available to use
if ! docker --version >/dev/null 2>&1; then
    if podman --version >/dev/null 2>&1; then
        use_podman=1
        # Disable SELinux protection in order to mount Urho3D project root directory from host to container in unprivileged mode
        run_option="--security-opt label=disable"
        # Podman mount volume as 'noexec' by default but we need 'exec' for Android build (aapt2 permission denied otherwise)
        mount_option=,exec
        # Podman by default pull from other OS registries before trying 'docker.io', so we need to be more explicit to avoid the retries
        registry=docker.io/
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

if [[ ! $DBE_NAME ]]; then
    DBE_NAME=${registry}urho3d/dockerized
fi

if [[ ! $DBE_TAG ]]; then
    # If the command failed or not on a tag then use 'master' by default
    DBE_TAG=$(git describe --exact-match 2>/dev/null || echo master)
fi

platform=$1; shift

if [[ "$DBE_NAMING_SCHEME" == "tag" ]]; then
  dbe_image=$DBE_NAME:$DBE_TAG-$platform
else
  dbe_image=$DBE_NAME-$platform:$DBE_TAG
fi

if [[ $DBE_REFRESH == 1 ]]; then
  d pull $dbe_image
fi
if [[ $GITHUB_ACTIONS ]]; then
  mkdir -p $GITHUB_WORKSPACE/build/cache
  mount_home_dir="--mount type=bind,source=$GITHUB_WORKSPACE/build/cache,target=/home/urho3d$mount_option"
else
  mount_home_dir="--mount type=volume,source=$(id -u).urho3d_home_dir,target=/home/urho3d$mount_option"
  interactive=-i
fi
if [[ $use_podman ]] || ( [[ $(d version -f '{{.Client.Version}}') =~ ^([0-9]+)\.0*([0-9]+)\. ]] && (( BASH_REMATCH[1] * 100 + BASH_REMATCH[2] >= 1809 )) ); then
    # podman or newer Docker client
    d run $interactive -t --rm -h fishtank $run_option \
        -e HOST_UID="$(id -u)" -e HOST_GID="$(id -g)" -e PROJECT_DIR="$PROJECT_DIR" \
        --env-file "$SCRIPT_DIR/.env-file" \
        --mount type=bind,source="$PROJECT_DIR",target="$PROJECT_DIR" \
        $mount_home_dir \
        $dbe_image "$@"
else
    # Fallback workaround on older Docker CLI version
    d run $interactive -t --rm -h fishtank \
        -e HOST_UID="$(id -u)" -e HOST_GID="$(id -g)" -e PROJECT_DIR="$PROJECT_DIR" \
        --env-file <(perl -ne 'chomp; print "$_\n" if defined $ENV{$_}' "$SCRIPT_DIR/.env-file") \
        --mount type=bind,source="$PROJECT_DIR",target="$PROJECT_DIR" \
        $mount_home_dir \
        $dbe_image "$@"
fi

# vi: set ts=4 sw=4 expandtab:
