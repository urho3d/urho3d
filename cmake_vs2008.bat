del /F CMakeCache.txt
if "%1" == "Win64" set "arch= %1"
cmake -G "Visual Studio 9 2008%arch%"