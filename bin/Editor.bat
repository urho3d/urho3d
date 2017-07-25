@echo off
if exist Urho3DPlayer.exe (set "DEBUG=") else (set "DEBUG=_d")
if [%1] == [] (set "OPT1=-w -s") else (set "OPT1=")
start "" Urho3DPlayer%DEBUG% Scripts/Editor.as %OPT1% %*
