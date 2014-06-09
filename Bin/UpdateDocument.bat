@echo off
doxygen -v 1>nul 2>&1
if %errorlevel% == 0 goto :start
echo Could not update document because doxygen is not installed
exit /B 1
:start
pushd "%~dp0..\Docs"
echo Dumping AngelScript API...
"%~dp0ScriptCompiler" -dumpapi ScriptAPI.dox AngelScriptAPI.h
if errorlevel 1 exit /B 1
echo Dumping LuaScript API...
pushd ..\Source\Engine\LuaScript\pkgs
"%~dp0tolua++" -L ToDoxHook.lua -P -o "%~dp0..\Docs\LuaScriptAPI.dox" "%~dp0LuaPkgToDox.txt"
if errorlevel 1 exit /B 1
popd
echo Converting Doxygen files to HTML...
doxygen Doxyfile 1>nul
echo Finish.
popd
