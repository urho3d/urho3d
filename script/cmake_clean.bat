:: Copyright (c) 2008-2022 the Urho3D project
:: License: MIT

@echo off

:: Clean the CMake cache and CMake generated files
set "BUILD="
if not "%~1" == "" if exist "%~1\CMakeCache.txt" set "BUILD=%~1"
if "%BUILD%" == "" if exist "%cd%\CMakeCache.txt" (set "BUILD=%cd%") else (goto :error)
del /F "%BUILD%\CMakeCache.txt"
if exist "%BUILD%\CMakeFiles" rd /S /Q "%BUILD%\CMakeFiles"
cmake -E touch "%BUILD%\CMakeCache.txt"

goto :eof
:error
echo Usage: %~nx0 \path\to\build-tree
exit /B 1
:eof
