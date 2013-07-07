@del /F CMakeCache.txt
cmake -G "Unix Makefiles" -DANDROID=1 -DCMAKE_TOOLCHAIN_FILE=Android/android.toolchain.cmake -DLIBRARY_OUTPUT_PATH_ROOT=Android