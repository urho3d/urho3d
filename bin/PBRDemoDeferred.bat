@echo off
setlocal
set "dirname=%~dp0"
if %0 == "%~dpnx0" where /q "%cd%:%~nx0" && set "dirname=%cd%\"
if exist "%dirname%Urho3DPlayer.exe" (set "DEBUG=") else (set "DEBUG=_d")
"%dirname%Urho3DPlayer%DEBUG%" Scripts/42_PBRMaterials.as -renderpath CoreData/RenderPaths/PBRDeferred.xml %*
