@echo off
pushd %~dp0\..\Docs
echo Dumping AngelScript API...
%~dp0\ScriptCompiler -dumpapi ScriptAPI.dox AngelScriptAPI.h
if errorlevel 1 exit /B 1
echo Dumping LuaScript API...
set "out=%CD%\LuaScriptAPI.dox"
pushd ..\Source\Engine\LuaScript\pkgs
%~dp0\tolua++ -L ToDoxHook.lua -P -o %out% %~dp0\LuaPkgToDox.txt
if errorlevel 1 exit /B 1
popd
echo Converting Doxygen files to HTML...
doxygen Doxyfile 1>nul
echo Finish.
popd
