@echo off
cd Source/Android
del /F CMakeCache.txt
rd /S /Q CMakeFiles
cd ../..
del /F CMakeCache.txt
rd /S /Q CMakeFiles
echo on
cmake -E chdir Source/Android cmake -G "Unix Makefiles" -DANDROID=1 -DCMAKE_TOOLCHAIN_FILE=../cmake/Toolchains/android.toolchain.cmake -DLIBRARY_OUTPUT_PATH_ROOT=. -DCMAKE_BUILD_TYPE=Release .. %*
