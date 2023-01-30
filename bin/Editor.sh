#!/usr/bin/env bash
if [[ $# -eq 0 ]]; then OPT1="-w -s"; fi
$(dirname $0)/Urho3DPlayer Editor/Scripts/Editor.as -p "EditorData;Data;CoreData" $OPT1 $@
