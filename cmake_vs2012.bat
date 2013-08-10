@echo off
cmake -E make_directory Build
del /F Build\CMakeCache.txt Source\CMakeCache.txt CMakeCache.txt
rd /S /Q Build\CMakeFiles Source\CMakeFiles CMakeFiles
set "arch="
for %%n in (%*) do if "%%n" == "-DENABLE_64BIT" set "arch= Win64"
set "version=11"
set "parm=%1"
if "%parm:~0,9%" == "-DVERSION" set "version=%~2"
echo on
cmake -E chdir Build cmake -G "Visual Studio %version%%arch%" ../Source %*
