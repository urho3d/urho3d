@del /F CMakeCache.txt
@if "%1" == "Win64" (set "arch= %1") else (set "arch=")
cmake -G "Visual Studio 11%arch%"