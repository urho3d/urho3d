rm -f CMakeCache.txt
cmake -G "Xcode" -DIOS=1 $@
sed -i.bak 's/OpenGL/Direct3D9/g' Doxyfile
#
# Below fix may no longer be required for newer version of CMake.
sed -i.bak 's/lastKnownFileType = sourcecode; name = "as_callfunc_arm_xcode.S"/lastKnownFileType = sourcecode.asm; name = "as_callfunc_arm_xcode.S"/g' Urho3D.xcodeproj/project.pbxproj
#
# Due to a bug in the CMake/Xcode generator where it has a wrong assumption of the IOS bundle structure which is slightly different from MacOSX bundle structure,
# below temporary fix is required to solve the auto-linking issue when dependent libraries is changed.
sed -i.bak 's/\/Contents\/MacOS//g' CMakeScripts/XCODE_DEPEND_HELPER.make
echo -e "\tsed -i.bak 's/\/Contents\/MacOS//g' CMakeScripts/XCODE_DEPEND_HELPER.make" >> CMakeScripts/ReRunCMake.make
