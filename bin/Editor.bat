@echo off
if exist "%~dp0Urho3DPlayer.exe" (set "DEBUG=") else (set "DEBUG=_d")
if exist "%~dp0..\share\Urho3D\Resources" (set "OPT1=-pp ..\share\Urho3D\Resources") else (set "OPT1=")
if [%1] == [] (set "OPT2=-w -s") else (set "OPT2=")
"%~dp0Urho3DPlayer%DEBUG%" Scripts/Editor.as %OPT1% %OPT2% %*
