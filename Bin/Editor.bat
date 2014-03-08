@ECHO OFF

IF [%1] == [] (
        Urho3DPlayer.exe Scripts/Editor.as -w -s
        )

IF NOT [%1] == [] (
        Urho3DPlayer.exe Scripts/Editor.as %*
        )
