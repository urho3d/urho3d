#!/bin/bash

# This script assumes you have made Data.pak and CoreData.pak
# and have them in your $URHO_DIR/Bin folder. It's best to make them
# compressed with the -c option for PackageTool

# steps:
# 1) make sure emscripten is installed and you have set your environment
#    properly
# 2) run cmake_emscripten.sh 
# 3) change to the emscripten-build directory
# 4) copy this file there and make any necessary changes to directory names
# 5) build the library - I use make -j3
# 6) execute this script. It should build all the c++ samples.
#

# set this to the top level directory of your Urho build tree
URHO_DIR=~/urho.badpixels/Urho3D

#set this to where you want the html and other files to go
HTML_DIR=$URHO_DIR/Bin

cd #URHO_DIR/emscripten-Build

# make sure environment is set up for emscripten sdk
. ~/emscripten/emsdk_portable/emsdk_set_env.sh

# various include directories
INCLUDES="-I../../Engine/Physics/"
INCLUDES=$INCLUDES" -I../../ThirdParty/Bullet/src/"
INCLUDES=$INCLUDES" -I../../Engine/Network/"
INCLUDES=$INCLUDES" -I../../Engine/UI/"
INCLUDES=$INCLUDES" -I../../Engine/Graphics/"
INCLUDES=$INCLUDES" -I../../Engine/Scene/"
INCLUDES=$INCLUDES" -I../../Engine/Input/"
INCLUDES=$INCLUDES" -I../../Samples/"
INCLUDES=$INCLUDES" -I../../Engine/Engine/"
INCLUDES=$INCLUDES" -I../../Engine/Core/"
INCLUDES=$INCLUDES" -I../../Engine/Container/"
INCLUDES=$INCLUDES" -I../../../emscripten-Build/Engine/"
INCLUDES=$INCLUDES" -I../../Engine/Math/"
INCLUDES=$INCLUDES" -I../../Engine/IO/"
INCLUDES=$INCLUDES" -I../../Engine/Resource/" 
INCLUDES=$INCLUDES" -I../../Engine/Audio/" 
INCLUDES=$INCLUDES" -I../../Engine/Navigation/" 
INCLUDES=$INCLUDES" -I../../Engine/Urho2D/" 
INCLUDES=$INCLUDES" -I../../Engine/Script/" 
INCLUDES=$INCLUDES" -I../../ThirdParty/Box2D/" 

echo "INCLUDES:" $INCLUDES

BIN=$URHO_DIR/Bin

LIBS=" -L../../../Lib/"
echo "LIBS:" $LIBS

#MEMORY="-s TOTAL_MEMORY=32000000"
MEMORY="-s ALLOW_MEMORY_GROWTH=1"

OPTIMIZE="-O2"

function buildSample {
    APPNAME=$1
    echo Building $APPNAME
    cd $URHO_DIR/Source/Samples/$APPNAME
    ln $BIN/Data.pak Data.pak
    ln $BIN/CoreData.pak CoreData.pak
    SOURCES=`ls *.cpp`
    DEFINES=""
    emcc -s USE_SDL=2 $OPTIMIZE -o $HTML_DIR/$APPNAME.html $DEFINES $INCLUDES $LIBS $SOURCES -lUrho3D --preload-file Data.pak --preload-file CoreData.pak $MEMORY
    rm Data.pak CoreData.pak
}

SAMPLES=""
SAMPLES=$SAMPLES" 01_HelloWorld"
SAMPLES=$SAMPLES" 02_HelloGUI"
SAMPLES=$SAMPLES" 03_Sprites"
SAMPLES=$SAMPLES" 04_StaticScene"
SAMPLES=$SAMPLES" 05_AnimatingScene"
SAMPLES=$SAMPLES" 06_SkeletalAnimation"
SAMPLES=$SAMPLES" 07_Billboards"
SAMPLES=$SAMPLES" 08_Decals"
SAMPLES=$SAMPLES" 09_MultipleViewports"
SAMPLES=$SAMPLES" 10_RenderToTexture"
SAMPLES=$SAMPLES" 11_Physics"
SAMPLES=$SAMPLES" 12_PhysicsStressTest"
SAMPLES=$SAMPLES" 13_Ragdolls"
SAMPLES=$SAMPLES" 14_SoundEffects"
SAMPLES=$SAMPLES" 15_Navigation"
#SAMPLES=$SAMPLES" 16_Chat"
#SAMPLES=$SAMPLES" 17_SceneReplication"
SAMPLES=$SAMPLES" 18_CharacterDemo"
SAMPLES=$SAMPLES" 19_VehicleDemo"
SAMPLES=$SAMPLES" 20_HugeObjectCount"
#SAMPLES=$SAMPLES" 21_AngelScriptIntegration"
#SAMPLES=$SAMPLES" 22_LuaIntegration"
SAMPLES=$SAMPLES" 23_Water"
SAMPLES=$SAMPLES" 24_Urho2DSprite"
SAMPLES=$SAMPLES" 25_Urho2DParticle"
SAMPLES=$SAMPLES" 26_ConsoleInput"
SAMPLES=$SAMPLES" 27_Urho2DPhysics"
SAMPLES=$SAMPLES" 28_Urho2DPhysicsRope"
SAMPLES=$SAMPLES" 29_SoundSynthesis"
SAMPLES=$SAMPLES" 30_LightAnimation"
SAMPLES=$SAMPLES" 31_MaterialAnimation"
SAMPLES=$SAMPLES" 32_Urho2DConstraints"
SAMPLES=$SAMPLES" 33_Urho2DSpriterAnimation"
SAMPLES=$SAMPLES" 34_DynamicGeometry"
SAMPLES=$SAMPLES" 35_SignedDistanceFieldText"
SAMPLES=$SAMPLES" 36_Urho2DTileMap"
SAMPLES=$SAMPLES" 37_UIDrag"


for i in $SAMPLES; do
    buildSample $i
done


