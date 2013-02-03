rm -f CMakeCache.txt
cmake -G "Xcode" -DIOS=1
sed -i.bak 's/lastKnownFileType = sourcecode; name = "as_callfunc_arm_xcode.S"/lastKnownFileType = sourcecode.asm; name = "as_callfunc_arm_xcode.S"/g' Urho3D.xcodeproj/project.pbxproj
sed -i.bak 's/OpenGL/Direct3D9/g' Doxyfile
#
# Below two empty files when present will force Xcode to always relink the executable and always copy resource folders on each builds, respectively
# Removed these empty files in the project folder and commented out these two commands below, if this is not desirable on slower machine
touch IOS_FORCE_COPY_RESOURCES 
touch IOS_FORCE_LINK
