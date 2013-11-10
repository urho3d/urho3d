@echo off
echo "Dumping AngelScript API..."
ScriptCompiler -dumpapi ../Docs/ScriptAPI.dox ../Docs/AngelScriptAPI.h
if errorlevel 1 exit /B 1
lua -v 1>nul 2>&1
if %errorlevel%== 0 (
    echo "Dumping LuaScript API..."
    set "out=%cd%/../Docs/LuaScriptAPI.dox"
    pushd ..\Source\Engine\LuaScript\pkgs
    lua pkgToDox.lua %out% *.pkg
    if errorlevel 1 exit /B 1
    popd
)
if not "%1" == "-a" exit /B 0
echo "Converting Doxygen files to HTML..."
cd .. && doxygen Doxyfile 1>nul
echo "Finish."
