@echo off
if exist "%~dp0Urho3DPlayer.exe" (set "DEBUG=") else (set "DEBUG=_d")
if [%1] == [] ("%~dp0Urho3DPlayer%DEBUG%" Scripts/Editor.as -w -s) else ("%~dp0Urho3DPlayer%DEBUG%" Scripts/Editor.as %*)
