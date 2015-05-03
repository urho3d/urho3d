@echo off

::
:: Helper script that builds the Game solution and then calls
:: the packaging script. Assumes you have VS2010 and Python installed.
::

:: set VS10_BIN=C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\bin
:: set VCVARS32="%VS10_BIN%\vcvars32.bat"

:: if not exist %VCVARS32% goto NO_VS10

set SOLUTION=%~dp0\.build\vs2008\Urho3D.sln
:: set PACKAGE=%~dp0\package.py

:: Setup the Visual Studio environment variables
:: call %VCVARS32%

msbuild %SOLUTION% /t:Build

:: Run the packaging script
:: python %PACKAGE%

goto END

:NO_VS10

echo Failed to find Visual Studio 2008! Please ensure it's installed.
echo Environment batch not found: %VCVARS32%

:END