#!/usr/bin/env bash

function get_build_dir() {
	if [ "$1" ] && [ -f "$1"/CMakeCache.txt ]
		then BUILD=$1
	elif [ -f $(pwd)/CMakeCache.txt ]
		then BUILD=$(pwd)
	elif [ -e $(pwd)/.git ]
		then BUILD=$(pwd)
	else echo "Current directory doesn't appear to be a 'build tree'. Please provide a build tree directory as the first argument, OR call this script in a build tree itself."
		exit 1
	fi
}
