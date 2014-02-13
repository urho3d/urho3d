@echo off
SETLOCAL ENABLEDELAYEDEXPANSION
pushd %~dp0\..\Docs
echo Dumping AngelScript API...
..\Bin\ScriptCompiler -dumpapi ScriptAPI.dox AngelScriptAPI.h
if errorlevel 1 exit /B 1
pushd %~dp0\..\Source\Engine\LuaScript\pkgs\
echo Dumping LuaScript API...
..\..\..\..\Bin\tolua++ -L ToDoxHook.lua -P -o ..\..\..\..\Docs\LuaScriptAPI.dox Urho3D.tolua
if errorlevel 1 exit /B 1
pushd %~dp0\..\Docs
echo Converting Doxygen files to HTML...
doxygen Doxyfile 1>nul
echo Finish.
popd