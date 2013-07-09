rm -rf CMakeCache.txt CMakeFiles
cmake -E create_symlink ../../Bin/CoreData Android/assets/CoreData
cmake -E create_symlink ../../Bin/Data Android/assets/Data
cmake -G "Unix Makefiles" -DANDROID=1 -DCMAKE_TOOLCHAIN_FILE=Android/android.toolchain.cmake -DLIBRARY_OUTPUT_PATH_ROOT=Android -DCMAKE_BUILD_TYPE=Release $@
sed -i.bak 's/OpenGL/Direct3D9/g' Doxyfile
