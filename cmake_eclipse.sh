rm -f CMakeCache.txt
proj=`pwd`
mkdir -p ../Urho3D-Eclipse-build/Release ../Urho3D-Eclipse-build/Debug ../Urho3D-Eclipse-build/RelWithDebInfo
cmake -E chdir ../Urho3D-Eclipse-build/Release cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Release $proj $@
cmake -E chdir ../Urho3D-Eclipse-build/Debug cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug $proj $@
cmake -E chdir ../Urho3D-Eclipse-build/RelWithDebInfo cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo $proj $@
sed -i.bak 's/OpenGL/Direct3D9/g' Doxyfile
#
# Create symbolic links in the respective Eclipse configuration subdir to allow running Urho3D within the Eclipse itself
cd ../Urho3D-Eclipse-build
for conf in Debug RelWithDebInfo Release; do
if [ ! -d $conf/Urho3D/CoreData ]
then
    ln -s $proj/Bin/CoreData $conf/Urho3D/.
    ln -s $proj/Bin/Data $conf/Urho3D/.
fi
done
