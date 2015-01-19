//
// Copyright (c) 2008-2014 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "Precompiled.h"
#include "../Graphics/GraphicsDefs.h"
#include "../Math/StringHash.h"
#include "../Math/Vector3.h"

#include "../DebugNew.h"

namespace Urho3D
{

URHO3D_API const StringHash VSP_AMBIENTSTARTCOLOR("AmbientStartColor");
URHO3D_API const StringHash VSP_AMBIENTENDCOLOR("AmbientEndColor");
URHO3D_API const StringHash VSP_BILLBOARDROT("BillboardRot");
URHO3D_API const StringHash VSP_CAMERAPOS("CameraPos");
URHO3D_API const StringHash VSP_CAMERAROT("CameraRot");
URHO3D_API const StringHash VSP_NEARCLIP("NearClip");
URHO3D_API const StringHash VSP_FARCLIP("FarClip");
URHO3D_API const StringHash VSP_DEPTHMODE("DepthMode");
URHO3D_API const StringHash VSP_DELTATIME("DeltaTime");
URHO3D_API const StringHash VSP_ELAPSEDTIME("ElapsedTime");
URHO3D_API const StringHash VSP_FRUSTUMSIZE("FrustumSize");
URHO3D_API const StringHash VSP_GBUFFEROFFSETS("GBufferOffsets");
URHO3D_API const StringHash VSP_LIGHTDIR("LightDir");
URHO3D_API const StringHash VSP_LIGHTPOS("LightPos");
URHO3D_API const StringHash VSP_MODEL("Model");
URHO3D_API const StringHash VSP_VIEWPROJ("ViewProj");
URHO3D_API const StringHash VSP_UOFFSET("UOffset");
URHO3D_API const StringHash VSP_VOFFSET("VOffset");
URHO3D_API const StringHash VSP_ZONE("Zone");
URHO3D_API const StringHash VSP_LIGHTMATRICES("LightMatrices");
URHO3D_API const StringHash VSP_SKINMATRICES("SkinMatrices");
URHO3D_API const StringHash VSP_VERTEXLIGHTS("VertexLights");
URHO3D_API const StringHash PSP_AMBIENTCOLOR("AmbientColor");
URHO3D_API const StringHash PSP_CAMERAPOS("CameraPosPS");
URHO3D_API const StringHash PSP_DELTATIME("DeltaTimePS");
URHO3D_API const StringHash PSP_DEPTHRECONSTRUCT("DepthReconstruct");
URHO3D_API const StringHash PSP_ELAPSEDTIME("ElapsedTimePS");
URHO3D_API const StringHash PSP_FOGCOLOR("FogColor");
URHO3D_API const StringHash PSP_FOGPARAMS("FogParams");
URHO3D_API const StringHash PSP_GBUFFERINVSIZE("GBufferInvSize");
URHO3D_API const StringHash PSP_LIGHTCOLOR("LightColor");
URHO3D_API const StringHash PSP_LIGHTDIR("LightDirPS");
URHO3D_API const StringHash PSP_LIGHTPOS("LightPosPS");
URHO3D_API const StringHash PSP_MATDIFFCOLOR("MatDiffColor");
URHO3D_API const StringHash PSP_MATEMISSIVECOLOR("MatEmissiveColor");
URHO3D_API const StringHash PSP_MATENVMAPECOLOR("MatEnvMapColor");
URHO3D_API const StringHash PSP_MATSPECCOLOR("MatSpecColor");
URHO3D_API const StringHash PSP_NEARCLIP("NearClipPS");
URHO3D_API const StringHash PSP_FARCLIP("FarClipPS");
URHO3D_API const StringHash PSP_SHADOWCUBEADJUST("ShadowCubeAdjust");
URHO3D_API const StringHash PSP_SHADOWDEPTHFADE("ShadowDepthFade");
URHO3D_API const StringHash PSP_SHADOWINTENSITY("ShadowIntensity");
URHO3D_API const StringHash PSP_SHADOWMAPINVSIZE("ShadowMapInvSize");
URHO3D_API const StringHash PSP_SHADOWSPLITS("ShadowSplits");
URHO3D_API const StringHash PSP_LIGHTMATRICES("LightMatricesPS");

URHO3D_API const StringHash PASS_BASE("base");
URHO3D_API const StringHash PASS_LITBASE("litbase");
URHO3D_API const StringHash PASS_LIGHT("light");
URHO3D_API const StringHash PASS_ALPHA("alpha");
URHO3D_API const StringHash PASS_LITALPHA("litalpha");
URHO3D_API const StringHash PASS_SHADOW("shadow");
URHO3D_API const StringHash PASS_DEFERRED("deferred");
URHO3D_API const StringHash PASS_PREPASS("prepass");
URHO3D_API const StringHash PASS_MATERIAL("material");
URHO3D_API const StringHash PASS_POSTOPAQUE("postopaque");
URHO3D_API const StringHash PASS_REFRACT("refract");
URHO3D_API const StringHash PASS_POSTALPHA("postalpha");

URHO3D_API const Vector3 DOT_SCALE(1 / 3.0f, 1 / 3.0f, 1 / 3.0f);

}
