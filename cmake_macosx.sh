cd $( dirname $0 )
rm -f CMakeCache.txt
cmake -G "Xcode" $@
sed -i.bak 's/lastKnownFileType = sourcecode; name = "as_callfunc_arm_xcode.S"/lastKnownFileType = sourcecode.asm; name = "as_callfunc_arm_xcode.S"/g' Urho3D.xcodeproj/project.pbxproj
sed -i.bak 's/OpenGL/Direct3D9/g' Doxyfile
#
# Create symbolic links in the respective xcode configuration subdir to allow running Urho3D within the xcode itself
cd Urho3D
for conf in Debug RelWithDebInfo Release; do
if [ ! -d $conf ]
then
    mkdir $conf
    ln -s ../../Bin/CoreData $conf/.
    ln -s ../../Bin/Data $conf/.
fi
done

# vi: set ts=4 sw=4 expandtab:
