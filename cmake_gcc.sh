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

# Define helpers
msg() {
    echo -e "\n$1\n================================================================================================="
}

post_cmake() {
    # Check if xmlstarlet software package is available for fixing the generated Eclipse project setting to get source code versioning to work
    if [ $HAS_XMLSTARLET ]; then
        # Move the Eclipse project setting files back to Source folder
        echo -- Eclipse project setting files have been relocated to: $( pwd )/Source
        for f in .project .cproject; do mv $1/$f Source; done

        #
        # Remove build type from project name
        # Replace [Source directory] linked resource to [Build] instead
        # Modify build argument to first change directory to Build folder
        #
        xmlstarlet ed -P -L \
            -u "/projectDescription/name/text()" -x "concat(substring-before(/projectDescription/name/text(), '-Release'), substring-before(/projectDescription/name/text(), '-Debug'), substring-before(/projectDescription/name/text(), '-RelWithDebInfo'))" \
            -u "/projectDescription/linkedResources/link/name/text()[. = '[Source directory]']" -v "[Build]" \
            -u "/projectDescription/linkedResources/link/location[../name/text() = '[Build]']" -v "$( pwd )/$1" \
            -u "/projectDescription/buildSpec/buildCommand/arguments/dictionary/value[../key/text() = 'org.eclipse.cdt.make.core.build.arguments']" -x "concat('-C ../$1 ', .)" \
            Source/.project
        #
        # Fix source path entry to Source folder and modify its filter condition
        # Fix output path entry to [Build] linked resource and modify its filter condition
        #
        xmlstarlet ed -P -L \
            -u "/cproject/storageModule/cconfiguration/storageModule/pathentry[@kind = 'src']/@path" -v "" \
            -s "/cproject/storageModule/cconfiguration/storageModule/pathentry[@kind = 'src']" -t attr -n "excluding" -v "[Subprojects]/|[Targets]/" \
            -u "/cproject/storageModule/cconfiguration/storageModule/pathentry[@kind = 'out']/@path" -v "[Build]" \
            -u "/cproject/storageModule/cconfiguration/storageModule/pathentry[@kind = 'out']/@excluding" -x "substring-after(., '[Source directory]/|')" \
            Source/.cproject
    fi
}

# Ensure we are in project root directory
cd $( dirname $0 )
SOURCE=`pwd`/Source

# Create out-of-source build directory
cmake -E make_directory Build
[ $RASPI_TOOL ] && cmake -E make_directory raspi-Build
[ $ANDROID_NDK ] && cmake -E make_directory android-Build

# Remove existing CMake cache and rules
rm -rf {Build,raspi-Build,android-Build}/CMakeCache.txt {Build,raspi-Build,android-Build}/CMakeFiles
# Do cleanup a few more times for old build directory created by previous version of cmake_gcc.sh, just in case
rm -rf {.,build,Android}/CMakeCache.txt {.,build,Android}/CMakeFiles
rm -rf {../build,../raspi-build,../android-build}/CMakeCache.txt {../build,../raspi-build,../android-build}/CMakeFiles

# Add support for Eclipse IDE
IFS=#
GENERATOR="Unix Makefiles"
[[ $1 =~ ^eclipse$ ]] && GENERATOR="Eclipse CDT4 - Unix Makefiles" && shift && xmlstarlet --version >/dev/null 2>&1 && HAS_XMLSTARLET=1

# Add support for both native and cross-compiling build for Raspberry Pi
[[ $( uname -p ) =~ ^armv6 ]] && PLATFORM="-DRASPI=1"

# Create project with the respective Cmake generators
OPT=
msg "Native build" && cmake -E chdir Build cmake $OPT -G $GENERATOR $PLATFORM $SOURCE $@ && post_cmake Build
[ $RASPI_TOOL ] && msg "Raspberry Pi build" && cmake -E chdir raspi-Build cmake $OPT -G $GENERATOR -DRASPI=1 -DCMAKE_TOOLCHAIN_FILE=$SOURCE/CMake/Toolchains/raspberrypi.toolchain.cmake $SOURCE $@ #&& post_cmake raspi-Build # Can only fix either native or raspi build, but not both as there is only one Source folder
[ $ANDROID_NDK ] && msg "Android build" && cmake -E chdir android-Build cmake $OPT -G $GENERATOR -DANDROID=1 -DCMAKE_TOOLCHAIN_FILE=$SOURCE/CMake/Toolchains/android.toolchain.cmake -DLIBRARY_OUTPUT_PATH_ROOT=. $SOURCE $@
unset IFS

# Assume GCC user uses OpenGL, comment out below sed if this is not true
sed 's/OpenGL/Direct3D9/g' Docs/Doxyfile.in >Doxyfile

# Create symbolic links in the build directories
if [ $ANDROID_NDK ]; then
    for dir in CoreData Data; do
        cmake -E create_symlink ../../../Bin/$dir Source/Android/assets/$dir
    done
    for f in AndroidManifest.xml build.xml project.properties src res assets; do
        cmake -E create_symlink ../Source/Android/$f android-Build/$f
    done
fi

# vi: set ts=4 sw=4 expandtab:
