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

cd $( dirname $0 )
./cmake_gcc.sh eclipse $@

# Install xmlstarlet software package (optional) for fixing the generated Eclipse project setting to get source code versioning to work
xmlstarlet --version >/dev/null 2>&1 || exit 0

# Move the Eclipse project setting files back to Source folder
echo -- Eclipse project setting files have been relocated to: $( pwd )/Source
mv Build/.project Source
mv Build/.cproject Source

#
# Remove build type from project name
# Replace [Source directory] linked resource to [Build] instead
# Modify build argument to first change directory to Build folder
#
xmlstarlet ed -P -L \
    -u "/projectDescription/name/text()" -x "concat(substring-before(/projectDescription/name/text(), '-Release'), substring-before(/projectDescription/name/text(), '-Debug'), substring-before(/projectDescription/name/text(), '-RelWithDebInfo'))" \
    -u "/projectDescription/linkedResources/link/name/text()[. = '[Source directory]']" -v "[Build]" \
    -u "/projectDescription/linkedResources/link/location[../name/text() = '[Build]']" -v "$( pwd )/Build" \
    -u "/projectDescription/buildSpec/buildCommand/arguments/dictionary/value[../key/text() = 'org.eclipse.cdt.make.core.build.arguments']" -x "concat('-C ../Build ', .)" \
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

# After importing the generated project into Eclipse workspace, set the [Build], [Subprojects], and [Targets] linked resources property as 'Derived'
# to exclude the derived resources in those folders from being listed in the Open Resource and Search Result list

# vi: set ts=4 sw=4 expandtab:
