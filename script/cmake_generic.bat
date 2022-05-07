:: Copyright (c) 2008-2022 the Urho3D project
:: License: MIT

@echo off

:: Determine source tree and build tree
setlocal
set "SOURCE=%~dp0"
set "SOURCE=%SOURCE:~0,-1%\.."
set "SOURCE=%cd%"
set "BUILD="
if "%~1" == "" goto :continue
set "ARG1=%~1"
if "%ARG1:~0,1%" equ "-" goto :continue
set "BUILD=%~1"
shift
:continue
if "%BUILD%" == "" if exist "%cd%\CMakeCache.txt" (set "BUILD=%cd%") else (echo Usage: %~nx0 \path\to\build-tree [build-options] && exit /B 1)

:: Detect CMake toolchains directory if it is not provided explicitly
if "%TOOLCHAINS%" == "" set "TOOLCHAINS=%SOURCE%\CMake\Toolchains"
if not exist "%TOOLCHAINS%" if exist "%URHO3D_HOME%\share\CMake\Toolchains" set "TOOLCHAINS=%URHO3D_HOME%\share\CMake\Toolchains"

:: Default to native generator and toolchain if none is specified explicitly
set "OPTS="
set "BUILD_OPTS="
set "arch="
:loop
if not "%~1" == "" (
    if "%~1" == "-D" (
        if "%~2" == "WEB" if "%~3" == "1" set "OPTS=-G "MinGW Makefiles" -D CMAKE_TOOLCHAIN_FILE="%TOOLCHAINS%\Emscripten.cmake""
        if "%~2" == "MINGW" if "%~3" == "1" set "OPTS=-G "MinGW Makefiles""
        if "%~2" == "URHO3D_64BIT" if "%~3" == "1" set "arch=-A x64"
        if "%~2" == "URHO3D_64BIT" if "%~3" == "0" set "arch=-A Win32"
        set "BUILD_OPTS=%BUILD_OPTS% -D %~2=%~3"
        shift
        shift
        shift
    )
    if "%~1" == "-VS" (
        set "OPTS=-G "Visual Studio %~2" %arch% %TOOLSET%"
        shift
        shift
    )
    if "%~1" == "-G" (
        set "OPTS=%OPTS% -G %~2"
        shift
        shift
    )
    goto loop
)
if exist "%BUILD%\CMakeCache.txt" set "OPTS="

:: Create project with the chosen CMake generator and toolchain
cmake -E make_directory "%BUILD%" && cmake -E chdir "%BUILD%" cmake %OPTS% %BUILD_OPTS% "%SOURCE%"
