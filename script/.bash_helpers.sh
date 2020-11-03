#
# Copyright (c) 2008-2020 the Urho3D project.
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
post_cmake() {
    if [ -e "$BUILD"/*.xcodeproj/project.pbxproj ] && perl -v >/dev/null 2>&1; then
        echo -- post_cmake: Fix generated Xcode project
        # Speed up build for Debug build configuration by building only active arch (currently this is not doable via CMake generator-expression as it only works for individual target instead of global)
        perl -i -pe 'BEGIN {$/=undef} s/(Debug \*\/ = {[^}]+?)SDKROOT/\1ONLY_ACTIVE_ARCH = YES; SDKROOT/s' "$BUILD"/*.xcodeproj/project.pbxproj
        # Speed up build for Debug build configuration by skipping dSYM file generation
        if [[ $IOS ]] || [[ $TVOS ]]; then
            perl -i -pe 'BEGIN {$/=undef} s/(Debug \*\/ = {[^}]+?)SDKROOT/\1DEBUG_INFORMATION_FORMAT = dwarf; SDKROOT/s' "$BUILD"/*.xcodeproj/project.pbxproj
        fi
    fi
}

# vi: set ts=4 sw=4 expandtab:
