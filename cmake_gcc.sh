# Create out-of-source build directory
cmake -E make_directory build
# Remove existing CMake cache and rules
rm -rf {.,build}/CMakeCache.txt CMakeFiles
# Create the Cmake generators
cmake -E chdir build cmake -G "Unix Makefiles" .. $@
[ $ANDROID_NDK ] && cmake -E chdir Android cmake -G "Unix Makefiles" -DANDROID=1 -DCMAKE_TOOLCHAIN_FILE=android.toolchain.cmake -DLIBRARY_OUTPUT_PATH_ROOT=. .. $@
# Assume GCC user uses OpenGL, comment out below sed if this is not true
sed -i.bak 's/OpenGL/Direct3D9/g' Doxyfile
# Create symbolic links in the Android directory
[ $ANDROID_NDK ] && for dir in CoreData Data; do cmake -E create_symlink ../../Bin/$dir Android/assets/$dir; done
