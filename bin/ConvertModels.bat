@echo off
set /p ASSETDIR="Enter source assets dir: "
cd /d "%~dp0"
tool/OgreImporter %ASSETDIR%/Jack.mesh.xml Data/Models/Jack.mdl -t
tool/OgreImporter %ASSETDIR%/Level.mesh.xml Data/Models/NinjaSnowWar/Level.mdl -t
tool/OgreImporter %ASSETDIR%/Mushroom.mesh.xml Data/Models/Mushroom.mdl -t
tool/OgreImporter %ASSETDIR%/Ninja.mesh.xml Data/Models/NinjaSnowWar/Ninja.mdl -t
tool/OgreImporter %ASSETDIR%/Potion.mesh.xml Data/Models/NinjaSnowWar/Potion.mdl -t
tool/OgreImporter %ASSETDIR%/SnowBall.mesh.xml Data/Models/NinjaSnowWar/SnowBall.mdl -t
tool/OgreImporter %ASSETDIR%/SnowCrate.mesh.xml Data/Models/NinjaSnowWar/SnowCrate.mdl -t
