@echo off
SETLOCAL ENABLEDELAYEDEXPANSION
pushd %~dp0\..\Docs
echo Dumping AngelScript API...
..\Bin\ScriptCompiler -dumpapi ScriptAPI.dox AngelScriptAPI.h
if errorlevel 1 exit /B 1
set "dumpluaapi="
for %%l in (luajit lua) do call :dumpluaapi %%l
if not "%1" == "-a" exit /B 0
echo Converting Doxygen files to HTML...
doxygen Doxyfile 1>nul
echo Finish.
popd
goto :eof

:dumpluaapi
if "%dumpluaapi%" == "1" goto :eof
%~dp0\%1 -v 1>nul 2>&1
if not %errorlevel% == 0 goto :eof
echo Dumping LuaScript API...
set "out=%CD%\LuaScriptAPI.dox"
pushd ..\Source\Engine\LuaScript\pkgs
set "pkglist="
for %%f in (*.pkg) do set pkglist=!pkglist! "%%f"
%~dp0\%1 pkgToDox.lua %out% %pkglist%
if errorlevel 1 exit /B 1
popd
set "dumpluaapi=1"
