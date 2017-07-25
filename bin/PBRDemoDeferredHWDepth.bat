@echo off
if exist Urho3DPlayer.exe (set "DEBUG=") else (set "DEBUG=_d")
Urho3DPlayer%DEBUG% Scripts/42_PBRMaterials.as -renderpath CoreData/RenderPaths/PBRDeferredHWDepth.xml %*
