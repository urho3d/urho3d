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

:: Clean the CMake cache and CMake generated files
set "BUILD="
if not "%~1" == "" if exist "%~1\CMakeCache.txt" set "BUILD=%~1"
if "%BUILD%" == "" if exist "%cd%\CMakeCache.txt" (set "BUILD=%cd%") else (goto :error)
del /F "%BUILD%\CMakeCache.txt"
if exist "%BUILD%\CMakeFiles" rd /S /Q "%BUILD%\CMakeFiles"
cmake -E touch "%BUILD%\CMakeCache.txt"

goto :eof
:error
echo An error has occured, build tree has to be provided as the first argument OR call this script in a build tree itself
exit /B 1
:eof
