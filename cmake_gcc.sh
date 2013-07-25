# Define helpers
msg() {
    echo -e "\n$1\n================================================================================================="
}

# Ensure we are in project source root directory
cd $( dirname $0 )
PROJ=`pwd`

# Create out-of-source build directory
cmake -E make_directory ../build
[ $RASPI_TOOL ] && cmake -E make_directory ../raspi-build
[ $ANDROID_NDK ] && cmake -E make_directory ../android-build

# Remove existing CMake cache and rules
rm -rf {../build,../raspi-build,../android-build}/CMakeCache.txt {../build,../raspi-build,../android-build}/CMakeFiles
# Do cleanup one more time for old build directory created by previous version of cmake_gcc.sh, just in case
rm -rf {.,build,Android}/CMakeCache.txt {.,build,Android}/CMakeFiles

# Add support for Eclipse IDE
IFS=#
GENERATOR="Unix Makefiles"
[[ $1 =~ ^eclipse$ ]] && GENERATOR="Eclipse CDT4 - Unix Makefiles" && ECLIPSE=1 && shift

# Add support for both native and cross-compiling build for Raspberry Pi
[[ $( uname -p ) =~ ^armv6 ]] && PLATFORM="-DRASPI=1"

# Create project with the respective Cmake generators
OPT=--no-warn-unused-cli
msg "Native build" && cmake -E chdir ../build cmake $OPT -G $GENERATOR $PLATFORM $PROJ $@
[ $RASPI_TOOL ] && msg "Raspberry Pi build" && cmake -E chdir ../raspi-build cmake $OPT -G $GENERATOR -DRASPI=1 -DCMAKE_TOOLCHAIN_FILE=$PROJ/cmake/Toolchains/raspberrypi.toolchain.cmake $PROJ $@
[ $ANDROID_NDK ] && msg "Android build" && cmake -E chdir ../android-build cmake $OPT -G $GENERATOR -DANDROID=1 -DCMAKE_TOOLCHAIN_FILE=$PROJ/cmake/Toolchains/android.toolchain.cmake -DLIBRARY_OUTPUT_PATH_ROOT=. $PROJ $@
unset IFS

# Assume GCC user uses OpenGL, comment out below sed if this is not true
sed -i.bak 's/OpenGL/Direct3D9/g' Doxyfile

# Create symbolic links in the build directories
for dir in CoreData Data; do
    [ $ECLIPSE ] && cmake -E create_symlink $PROJ/Bin/$dir ../build/Urho3D/$dir
    if [ $ANDROID_NDK ]; then
        cmake -E create_symlink ../../Bin/$dir Android/assets/$dir
        for f in AndroidManifest.xml build.xml project.properties src res assets; do
            cmake -E create_symlink $PROJ/Android/$f ../android-build/$f
        done
    fi
done

# vi: set ts=4 sw=4 expandtab:
