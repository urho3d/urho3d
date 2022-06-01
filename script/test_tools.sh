#!/usr/bin/env bash

# Copyright (c) 2008-2022 the Urho3D project
# License: MIT

if [[ $# != 2 ]]
then
    echo "Usage: test_tools.sh repo_dir build_dir"
    exit 1
fi

repo_dir=$1
build_dir=$2

# Remove trailing slash in Unix and Windows
repo_dir=${repo_dir%/}
repo_dir=${repo_dir%\\}
build_dir=${build_dir%/}
build_dir=${build_dir%\\}

# ================== OgreImporter ==================

src_filenames=(
    Jack.mesh.xml
    Level.mesh.xml
    Mushroom.mesh.xml
    Ninja.mesh.xml
    Potion.mesh.xml
    SnowBall.mesh.xml
    SnowCrate.mesh.xml
)

result_filenames=(
    Jack_Walk.ani
    Ninja_Attack1.ani
    Ninja_Attack2.ani
    Ninja_Attack3.ani
    Ninja_Backflip.ani
    Ninja_Block.ani
    Ninja_Climb.ani
    Ninja_Crouch.ani
    Ninja_Death1.ani
    Ninja_Death2.ani
    Ninja_HighJump.ani
    Ninja_Idle1.ani
    Ninja_Idle2.ani
    Ninja_Idle3.ani
    Ninja_Jump.ani
    Ninja_JumpNoHeight.ani
    Ninja_Kick.ani
    Ninja_SideKick.ani
    Ninja_Spin.ani
    Ninja_Stealth.ani
    Ninja_Walk.ani
    Jack.mdl
    Level.mdl
    Mushroom.mdl
    Ninja.mdl
    Potion.mdl
    SnowBall.mdl
    SnowCrate.mdl
)

# This is not used because the result is compiler dependent.
# Perhaps this is due to the calculation error when using float
result_checksums=(
    a07f69d23b84b0039d7e9159a494d7c5a587ae6d # Jack_Walk.ani
    5abfe9cee41a2d8c4d8af8af5baf879fc6ab36cb # Ninja_Attack1.ani
    f73548094148f9d18d6a93b66eac647db50672eb # Ninja_Attack2.ani
    0549824bcbf73ebaff17964ba81ae2ca813ad684 # Ninja_Attack3.ani
    a2aab4ad61b9de9038135abf9b1e459e17d6bb20 # Ninja_Backflip.ani
    dec34fb0ec43f6fca8037328fc0dc8bd1e55d30d # Ninja_Block.ani
    ae20b728ca1f2776ab6bb66ab4855f56710e8d14 # Ninja_Climb.ani
    8f21ea4e1f999167a2b82a575c15de614f576a0f # Ninja_Crouch.ani
    b3314a675d1a41f97f818f06b562e20ab072de5a # Ninja_Death1.ani
    e3dd6aa2fb9b585180e3772b7c598828d935bf15 # Ninja_Death2.ani
    ff6766e3d55855a240fc35ccf7395a6517911c99 # Ninja_HighJump.ani
    d565fea93087a60df836637aad7f9c8184c28c6a # Ninja_Idle1.ani
    065f7d89e032c18dedeae0b64975984ec80d3557 # Ninja_Idle2.ani
    00b4d893b3cffbf58db4fb7f0e970990accb1155 # Ninja_Idle3.ani
    bad0c363ec9cf9283ca08b8ca44a86dc09068603 # Ninja_Jump.ani
    e55e9a21e635eb8a31b708fa009e9aca06ea9e7d # Ninja_JumpNoHeight.ani
    82fcc8eda8929809fd771805466b8e287af3a3c7 # Ninja_Kick.ani
    b09e8cc6e0fb58786c21184bcc0aa8dcd4b51b57 # Ninja_SideKick.ani
    63683537161f7352684bc50a44b753b5f9691af3 # Ninja_Spin.ani
    801383ba0ad30d4a0d401a69af5ca88bf5c6b39f # Ninja_Stealth.ani
    608a91452ff6980ef34ca68c4fd688fd719592c2 # Ninja_Walk.ani
    c8b032146ccde40058af94d5578e61345f6fb648 # Jack.mdl
    cde0671fced710d666f15cd941c9f385359a45e9 # Level.mdl
    39afeecb472b8be081fddb59419db595ccae2105 # Mushroom.mdl
    ef5b6c831566f45cef0c7652fe16a7eec7f57f4c # Ninja.mdl
    351044e86480d7ab0ee5bac2f557f800e6770925 # Potion.mdl
    4c3c7b1c47f62c5c0a99e1f33bd20463a64d6b93 # SnowBall.mdl
    110a90536d58e0a57ef6070b2b372341cb97bdaa # SnowCrate.mdl
)

result_sizes=(
    56410  # Jack_Walk.ani
    2916   # Ninja_Attack1.ani
    2788   # Ninja_Attack2.ani
    2628   # Ninja_Attack3.ani
    3141   # Ninja_Backflip.ani
    1186   # Ninja_Block.ani
    2466   # Ninja_Climb.ani
    4003   # Ninja_Crouch.ani
    2307   # Ninja_Death1.ani
    2723   # Ninja_Death2.ani
    5541   # Ninja_HighJump.ani
    3682   # Ninja_Idle1.ani
    2434   # Ninja_Idle2.ani
    2658   # Ninja_Idle3.ani
    2785   # Ninja_Jump.ani
    2857   # Ninja_JumpNoHeight.ani
    3745   # Ninja_Kick.ani
    2885   # Ninja_SideKick.ani
    2625   # Ninja_Spin.ani
    2244   # Ninja_Stealth.ani
    3201   # Ninja_Walk.ani
    433684 # Jack.mdl
    26100  # Level.mdl
    74196  # Mushroom.mdl
    66895  # Ninja.mdl
    7092   # Potion.mdl
    2484   # SnowBall.mdl
    11724  # SnowCrate.mdl
)

# Convert models
for (( i = 0; i < ${#src_filenames[*]}; ++i ))
do
    src_filepath=${repo_dir}/SourceAssets/${src_filenames[$i]}

    # Replace extension from .mesh.xml to .mdl
    output_filename=${src_filenames[$i]%.mesh.xml}.mdl

    ${build_dir}/bin/tool/OgreImporter $src_filepath $output_filename -t

    # Check exit code of the previous command
    if [[ $? != 0 ]]
    then
        exit 1
    fi
done

# Compare checksums
#for (( i = 0; i < ${#result_filenames[*]}; ++i ))
#do
#    checksum=$(sha1sum ${result_filenames[$i]})
#
#    # Check exit code of the previous command
#    if [[ $? != 0 ]]
#    then
#        exit 1
#    fi
#
#    # Extract checksum from string
#    checksum=$(echo $checksum | awk '{print $1}')
#
#    if [[ $checksum != ${result_checksums[$i]} ]]
#    then
#        echo "${result_filenames[$i]}: incorrect checksum"
#        exit 1
#    fi
#done

# Check sizes instead checksums
for (( i = 0; i < ${#result_filenames[*]}; ++i ))
do
    # This works on any platform
    file_size=$(wc -c ${result_filenames[$i]})

    # Check exit code of the previous command
    if [[ $? != 0 ]]
    then
        exit 1
    fi

    # Extract size from string
    file_size=$(echo $file_size | awk '{print $1}')

    if [[ $file_size != ${result_sizes[$i]} ]]
    then
        echo "${result_filenames[$i]}: incorrect size"
        exit 1
    fi
done

# ================== AssetImporter ==================

src_filenames=(
    TeaPot.blend
    Box.blend
)

result_filenames=(
    #Materials/Default.xml # Is rewritten by default.xml on Windows
    Materials/default.xml
    Materials/DefaultMaterial.xml
    Box.mdl
    TeaPot.mdl
)

result_sizes=(
    #256    # Materials/Default.xml
    306    # Materials/default.xml
    261    # Materials/DefaultMaterial.xml
    1456   # Box.mdl
    494912 # TeaPot.mdl
)

# Convert models
for (( i = 0; i < ${#src_filenames[*]}; ++i ))
do
    src_filepath=${repo_dir}/SourceAssets/${src_filenames[$i]}

    # Replace extension from .blend to .mdl
    output_filename=${src_filenames[$i]%.blend}.mdl

    ${build_dir}/bin/tool/AssetImporter model $src_filepath $output_filename -t

    # Check exit code of the previous command
    if [[ $? != 0 ]]
    then
        exit 1
    fi
done

# Check sizes instead checksums
for (( i = 0; i < ${#result_filenames[*]}; ++i ))
do
    # This works on any platform
    file_size=$(wc -c ${result_filenames[$i]})

    # Check exit code of the previous command
    if [[ $? != 0 ]]
    then
        exit 1
    fi

    # Extract size from string
    file_size=$(echo $file_size | awk '{print $1}')

    if [[ $file_size != ${result_sizes[$i]} ]]
    then
        echo "${result_filenames[$i]}: incorrect size"
        exit 1
    fi
done

# vi: set ts=4 sw=4 expandtab:
