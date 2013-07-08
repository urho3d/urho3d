@del /F CMakeCache.txt
@if /I "%1" == "ENABLE_64BIT" (set "arch= Win64") else (set "arch=")
@set "DEFINE="
@for %%n in (%*) do @call :concat %%n
cmake -G "Visual Studio 11%arch%" %DEFINE%
@goto :eof
:concat
@set "DEFINE=%DEFINE% -D%1=1"
@goto :eof
