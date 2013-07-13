@del /F CMakeCache.txt
@rd /S /Q CMakeFiles
@cd Android
@del /F CMakeCache.txt
@rd /S /Q CMakeFiles
cmake -G "Unix Makefiles" -DANDROID=1 -DCMAKE_TOOLCHAIN_FILE=android.toolchain.cmake -DLIBRARY_OUTPUT_PATH_ROOT=. -DCMAKE_BUILD_TYPE=Release .. %*
@cd ..