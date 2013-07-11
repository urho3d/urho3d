# Create out-of-source build directory
cmake -E make_directory build
# Remove existing CMake cache and rules
rm -rf {.,build}/CMakeCache.txt CMakeFiles
# Create the Cmake generators
cmake -E chdir build cmake -G "Eclipse CDT4 - Unix Makefiles" .. $@
[ $ANDROID_NDK ] && cmake -E chdir Android cmake -G "Eclipse CDT4 - Unix Makefiles" -DANDROID=1 -DCMAKE_TOOLCHAIN_FILE=android.toolchain.cmake -DLIBRARY_OUTPUT_PATH_ROOT=. .. $@ \
                 && sed -i.bak 's/<value>all<\/value>/<value>install\/strip<\/value>/g' Android/.project
# Assume Eclipse user uses OpenGL, comment out below sed if this is not true
sed -i.bak 's/OpenGL/Direct3D9/g' Doxyfile
# Create symbolic links in the build and Android directories
for dir in CoreData Data; do
    cmake -E create_symlink ../../Bin/$dir build/Urho3D/$dir
    [ $ANDROID_NDK ] && cmake -E create_symlink ../../Bin/$dir Android/assets/$dir
done
