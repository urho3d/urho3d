@echo off
cmake -E make_directory Build
del /F Build\CMakeCache.txt Source\CMakeCache.txt CMakeCache.txt
rd /S /Q Build\CMakeFiles Source\CMakeFiles CMakeFiles
cmake -E copy_if_different Docs\Doxyfile.in Doxyfile
echo on
cmake -E chdir Build cmake -G "MinGW Makefiles" ..\Source %*
