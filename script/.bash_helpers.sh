# Copyright (c) 2008-2023 the Urho3D project
# License: MIT

# Define helpers
post_cmake() {
    if [ -e "$BUILD"/*.xcodeproj/project.pbxproj ] && perl -v >/dev/null 2>&1; then
        echo -- DISABLED: post_cmake: Fix generated Xcode project
    elif false; then
        # Speed up build for Debug build configuration by building only active arch (currently this is not doable via CMake generator-expression as it only works for individual target instead of global)
        perl -i -pe 'BEGIN {$/=undef} s/(Debug \*\/ = {[^}]+?)SDKROOT/\1ONLY_ACTIVE_ARCH = YES; SDKROOT/s' "$BUILD"/*.xcodeproj/project.pbxproj
        # Speed up build for Debug build configuration by skipping dSYM file generation
        if [[ $IOS ]] || [[ $TVOS ]]; then
            perl -i -pe 'BEGIN {$/=undef} s/(Debug \*\/ = {[^}]+?)SDKROOT/\1DEBUG_INFORMATION_FORMAT = dwarf; SDKROOT/s' "$BUILD"/*.xcodeproj/project.pbxproj
        fi
    fi
}

# vi: set ts=4 sw=4 expandtab:
