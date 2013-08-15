#
# Copyright (c) 2008-2013 the Urho3D project.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#

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
sed -i.bak 's/lastKnownFileType = sourcecode; name = "as_callfunc_arm_xcode.S"/lastKnownFileType = sourcecode.asm; name = "as_callfunc_arm_xcode.S"/g' Build/*.xcodeproj/project.pbxproj

# Apple always uses OpenGL
sed 's/OpenGL/Direct3D9/g' Docs/Doxyfile.in >Doxyfile

if [ $1 == "-DIOS=1" ]; then
    # Due to a bug in the CMake/Xcode generator where it has wrongly assumed the IOS bundle structure to be the same as MacOSX bundle structure,
    # below temporary fix is required in order to solve the auto-linking issue when dependent libraries is changed.
    sed -i.bak 's/\/Contents\/MacOS//g' Build/CMakeScripts/XCODE_DEPEND_HELPER.make
    echo -e "\tsed -i.bak 's/\/Contents\/MacOS//g' CMakeScripts/XCODE_DEPEND_HELPER.make" >> Build/CMakeScripts/ReRunCMake.make
fi

# vi: set ts=4 sw=4 expandtab:
