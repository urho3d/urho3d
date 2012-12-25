rm -f CMakeCache.txt
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo
sed -i.bak 's/OpenGL/Direct3D9/g' Doxyfile
