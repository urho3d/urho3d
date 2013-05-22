del /F CMakeCache.txt
if "%1" == "Win64" set "arch= %1"
cmake -G "Visual Studio 10%arch%"