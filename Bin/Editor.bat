@ECHO OFF

IF [%1] == [] (
        "%~dp0Urho3DPlayer" Scripts/Editor.as -w -s
        )

IF NOT [%1] == [] (
        "%~dp0Urho3DPlayer" Scripts/Editor.as %*
        )
