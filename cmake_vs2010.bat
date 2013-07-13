@del /F CMakeCache.txt
@rd /S /Q CMakeFiles
@set "arch="
@for %%n in (%*) do @if "%%n" == "-DENABLE_64BIT" (set "arch= Win64")
cmake -G "Visual Studio 10%arch%" %*
