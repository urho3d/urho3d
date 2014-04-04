::
:: Copyright (c) 2008-2014 the Urho3D project.
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
pushd %~dp0
cmake -E make_directory Build
set "arch="
set "version=9 2008"
if exist Build\CMakeCache.txt. for /F "eol=/ delims=:= tokens=1-3" %%i in (Build\CMakeCache.txt) do if "%%i" == "URHO3D_64BIT" if "%%k" == "1" set "arch= Win64"
:loop
if not "%1" == "" (
    if "%1" == "-DURHO3D_64BIT" if "%~2" == "1" set "arch= Win64"
    if "%1" == "-DURHO3D_64BIT" if "%~2" == "0" set "arch="
    if "%1" == "VERSION" set "version=%~2"
    shift
    shift
    goto loop
)
echo on
@set "OPT="
cmake -E chdir Build cmake %OPT% -G "Visual Studio %version%%arch%" %* ..\Source
@popd
