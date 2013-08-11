@echo off
cmake -E make_directory Build
del /F Build\CMakeCache.txt Source\CMakeCache.txt CMakeCache.txt
rd /S /Q Build\CMakeFiles Source\CMakeFiles CMakeFiles
set "arch="
set "version=11"
:loop
if not "%1" == "" (
    if "%1" == "-DENABLE_64BIT" if "%~2" == "1" set "arch= Win64"
    if "%1" == "-DVERSION" set "version=%~2"
    shift
    shift
    goto loop
)
cmake -E copy_if_different Docs/Doxyfile.in Doxyfile
echo on
cmake -E chdir Build cmake -G "Visual Studio %version%%arch%" ../Source %*
