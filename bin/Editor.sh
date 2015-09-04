#!/usr/bin/env bash
if [ -d $(dirname $0)/../share/Urho3D/Resources ]; then OPT1="-pp ../share/Urho3D/Resources"; fi
if [ $# -eq 0 ]; then OPT2="-w -s"; fi
$(dirname $0)/Urho3DPlayer Scripts/Editor.as $OPT1 $OPT2 $@
