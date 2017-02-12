for abi in "armeabi" "armeabi-v7a" "arm64-v8a" "mips" "mips64";
do
mkdir -p libs
mkdir -p build
export ANDROID_ABI=$abi
./cmake_android.sh build -DURHO3D_LIB_TYPE=SHARED -DANDROID_ABI=${ANDROID_ABI} -DURHO3D_ANGELSCRIPT=0
cd build
make -j32
cd libs
cp -ar . ../../libs/
cd ../../
rm -rf build
done

