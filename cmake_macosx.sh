# Ensure we are in project root directory
cd $( dirname $0 )
SOURCE=`pwd`/Source

# Create out-of-source build directory
cmake -E make_directory Build

# Remove existing CMake cache and rules
rm -rf Build/CMakeCache.txt Build/CMakeFiles
# Do cleanup one more time for old build directory created by previous version of cmake_macosx.sh, just in case
rm -rf {../build,.,build}/CMakeCache.txt {../build,.,build}/CMakeFiles

# Create project with the Xcode generator
cmake -E chdir Build cmake -G "Xcode" $SOURCE $@

# Below temporary fix may no longer be required by newer version of CMake
sed -i.bak 's/lastKnownFileType = sourcecode; name = "as_callfunc_arm_xcode.S"/lastKnownFileType = sourcecode.asm; name = "as_callfunc_arm_xcode.S"/g' Build/Urho3D.xcodeproj/project.pbxproj

# Apple always uses OpenGL
sed 's/OpenGL/Direct3D9/g' Docs/Doxyfile.in >Doxyfile

if [ $1 == "-DIOS=1" ]
then
    # Due to a bug in the CMake/Xcode generator where it has wrongly assumed the IOS bundle structure to be the same as MacOSX bundle structure,
    # below temporary fix is required in order to solve the auto-linking issue when dependent libraries is changed.
    sed -i.bak 's/\/Contents\/MacOS//g' Build/CMakeScripts/XCODE_DEPEND_HELPER.make
    echo -e "\tsed -i.bak 's/\/Contents\/MacOS//g' CMakeScripts/XCODE_DEPEND_HELPER.make" >> Build/CMakeScripts/ReRunCMake.make
else
    # Create symbolic links in the respective Xcode configuration subdir to allow running Urho3D within the xcode itself
    mkdir -p Build/Tools/Urho3D
    cd Build/Tools/Urho3D
    for conf in Debug RelWithDebInfo Release; do
        if [ ! -d $conf ]; then mkdir $conf; fi
        for dir in CoreData Data; do
            cmake -E create_symlink ../../../../Bin/$dir $conf/$dir
        done
    done
fi

# vi: set ts=4 sw=4 expandtab:
