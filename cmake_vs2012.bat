@echo off
cd Source
del /F CMakeCache.txt
rd /S /Q CMakeFiles
cd ..
del /F CMakeCache.txt
rd /S /Q CMakeFiles
set "arch="
for %%n in (%*) do if "%%n" == "-DENABLE_64BIT" set "arch= Win64"
set "version=11"
set "parm=%1"
if "%parm:~0,9%" == "-DVERSION" set "version=%~2"
echo on
cmake -E chdir Source cmake -G "Visual Studio %version%%arch%" %*
