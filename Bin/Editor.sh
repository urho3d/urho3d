#!/usr/bin/env bash
if [ $# -eq 0 ]
then
    $( dirname $0 )/Urho3DPlayer Scripts/Editor.as -w -s
else
    $( dirname $0 )/Urho3DPlayer Scripts/Editor.as $@
fi
