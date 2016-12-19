@echo off
if exist "%~dp0Urho3DPlayer.exe" (set "DEBUG=") else (set "DEBUG=_d")
if [%1] == [] (set "OPT1=-w -s") else (set "OPT1=")
start "" "%~dp0Urho3DPlayer%DEBUG%" Scripts/Editor.as %OPT1% %*
