@echo off
if exist "%~dp0Urho3DPlayer.exe" (set "DEBUG=") else (set "DEBUG=_d")
"%~dp0Urho3DPlayer%DEBUG%" Scripts/42_PBRMaterials.as -renderpath CoreData/RenderPaths/PBRDeferredHWDepth.xml %*
