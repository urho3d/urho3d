::
:: Copyright (c) 2008-2013 the Urho3D project.
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

:: This script is being called by CMake during MSVC build
:: PLEASE DO NOT EDIT unless you know what you are doing
@echo off
set "target=%1"
set "outdir=%2"
set "objdir=%3"
if not "%4" == "SENTINEL" echo |set /p=>%outdir%/%target%.objects.txt
for %%o in (%*) do call :append %%o
exit /B 0
:append
if not "%~x1" == ".cpp" if not "%~x1" == ".c" if not "%~x1" == ".o" goto :eof
if "%~x1" == ".o" (set "object=%~nx1") else (set "object=%~n1.obj")
echo |set /p=%objdir%/%object% >>%outdir%/%target%.objects.txt
