rm -f CMakeCache.txt
mkdir -p Urho3D/Release Urho3D/Debug Urho3D/RelWithDebInfo
cmake -E chdir Urho3D/Release cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ../..
cmake -E chdir Urho3D/Debug cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../..
cmake -E chdir Urho3D/RelWithDebInfo cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo ../..
sed -i.bak 's/OpenGL/Direct3D9/g' Doxyfile
#
# Create symbolic links in the respective Eclipse configuration subdir to allow running Urho3D within the Eclipse itself
cd Urho3D
for conf in Debug RelWithDebInfo Release; do
if [ ! -d $conf/Urho3D/CoreData ]
then
    ln -s ../../../Bin/CoreData $conf/Urho3D/.
    ln -s ../../../Bin/Data $conf/Urho3D/.
fi
done
