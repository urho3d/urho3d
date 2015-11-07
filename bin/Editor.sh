#!/usr/bin/env bash
if [ $# -eq 0 ]; then OPT1="-w -s"; fi
$(dirname $0)/Urho3DPlayer Scripts/Editor.as $OPT1 $@
