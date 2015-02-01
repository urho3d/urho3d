::
:: Copyright (c) 2008-2015 the Urho3D project.
::
:: Permission is hereby granted, free of charge, to any person obtaining a copy
:: of this software and associated documentation files (the "Software"), to deal
:: in the Software without restriction, including without limitation the rights
:: to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
:: copies of the Software, and to permit persons to whom the Software is
:: furnished to do so, subject to the following conditions:
::
:: The above copyright notice and this permission notice shall be included in
:: all copies or substantial portions of the Software.
::
:: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
:: IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
:: FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
:: AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
:: LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
:: OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
:: THE SOFTWARE.
::

@echo off

:: Determine source tree and build tree
set "SOURCE=%~dp0"
set "BUILD="
if "%~1" == "" goto :continue
set "ARG1=%~1"
if "%ARG1:~0,1%" equ "-" goto :continue
set "BUILD=%~1"
shift
:continue
if "%BUILD%" == "" if exist "%cd%\CMakeCache.txt" (set "BUILD=%cd%") else (goto :error)

:: Detect CMake toolchains directory if it is not provided explicitly
if "%TOOLCHAINS%" == "" set "TOOLCHAINS=%SOURCE%/CMake/Toolchains"
if not exist "%TOOLCHAINS%" if exist "%URHO3D_HOME%/share/Urho3D/CMake/Toolchains" set "TOOLCHAINS=%URHO3D_HOME%/share/Urho3D/CMake/Toolchains"
:: BEWARE that the TOOLCHAINS variable leaks to caller's environment!

:: Default to native generator and toolchain if none is specified explicitly
set "OPTS="
set "arch="
if exist "%BUILD%\CMakeCache.txt" for /F "eol=/ delims=:= tokens=1-3" %%i in (%BUILD%\CMakeCache.txt) do if "%%i" == "URHO3D_64BIT" if "%%k" == "1" set "arch= Win64"
:loop
if not "%~1" == "" (
    if "%~1" == "-DANDROID" if "%~2" == "1" set "OPTS=-G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=%TOOLCHAINS%\android.toolchain.cmake"
    if "%~1" == "-DURHO3D_64BIT" if "%~2" == "1" set "arch= Win64"
    if "%~1" == "-DURHO3D_64BIT" if "%~2" == "0" set "arch="
    if "%~1" == "-VS" set "OPTS=-G "Visual Studio %~2%arch%""
    shift
    shift
    goto loop
)

:: Create project with the chosen CMake generator and toolchain
cmake -E make_directory %BUILD% && cmake -E chdir %BUILD% cmake %OPTS% %* %SOURCE%

goto :eof
:error
echo An error has occured, build tree has to be provided as the first argument OR call this script in a build tree itself
exit /B 1
:eof
