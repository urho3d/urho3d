//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Graphics/GraphicsDefs.h"
#include "../Math/StringHash.h"
#include "../Math/Vector3.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern URHO3D_API const StringHash VSP_AMBIENTSTARTCOLOR("AmbientStartColor");
extern URHO3D_API const StringHash VSP_AMBIENTENDCOLOR("AmbientEndColor");
extern URHO3D_API const StringHash VSP_BILLBOARDROT("BillboardRot");
extern URHO3D_API const StringHash VSP_CAMERAPOS("CameraPos");
extern URHO3D_API const StringHash VSP_CAMERAROT("CameraRot");
extern URHO3D_API const StringHash VSP_NEARCLIP("NearClip");
extern URHO3D_API const StringHash VSP_FARCLIP("FarClip");
extern URHO3D_API const StringHash VSP_DEPTHMODE("DepthMode");
extern URHO3D_API const StringHash VSP_DELTATIME("DeltaTime");
extern URHO3D_API const StringHash VSP_ELAPSEDTIME("ElapsedTime");
extern URHO3D_API const StringHash VSP_FRUSTUMSIZE("FrustumSize");
extern URHO3D_API const StringHash VSP_GBUFFEROFFSETS("GBufferOffsets");
extern URHO3D_API const StringHash VSP_LIGHTDIR("LightDir");
extern URHO3D_API const StringHash VSP_LIGHTPOS("LightPos");
extern URHO3D_API const StringHash VSP_MODEL("Model");
extern URHO3D_API const StringHash VSP_VIEWPROJ("ViewProj");
extern URHO3D_API const StringHash VSP_UOFFSET("UOffset");
extern URHO3D_API const StringHash VSP_VOFFSET("VOffset");
extern URHO3D_API const StringHash VSP_ZONE("Zone");
extern URHO3D_API const StringHash VSP_LIGHTMATRICES("LightMatrices");
extern URHO3D_API const StringHash VSP_SKINMATRICES("SkinMatrices");
extern URHO3D_API const StringHash VSP_VERTEXLIGHTS("VertexLights");
extern URHO3D_API const StringHash PSP_AMBIENTCOLOR("AmbientColor");
extern URHO3D_API const StringHash PSP_CAMERAPOS("CameraPosPS");
extern URHO3D_API const StringHash PSP_DELTATIME("DeltaTimePS");
extern URHO3D_API const StringHash PSP_DEPTHRECONSTRUCT("DepthReconstruct");
extern URHO3D_API const StringHash PSP_ELAPSEDTIME("ElapsedTimePS");
extern URHO3D_API const StringHash PSP_FOGCOLOR("FogColor");
extern URHO3D_API const StringHash PSP_FOGPARAMS("FogParams");
extern URHO3D_API const StringHash PSP_GBUFFERINVSIZE("GBufferInvSize");
extern URHO3D_API const StringHash PSP_LIGHTCOLOR("LightColor");
extern URHO3D_API const StringHash PSP_LIGHTDIR("LightDirPS");
extern URHO3D_API const StringHash PSP_LIGHTPOS("LightPosPS");
extern URHO3D_API const StringHash PSP_MATDIFFCOLOR("MatDiffColor");
extern URHO3D_API const StringHash PSP_MATEMISSIVECOLOR("MatEmissiveColor");
extern URHO3D_API const StringHash PSP_MATENVMAPECOLOR("MatEnvMapColor");
extern URHO3D_API const StringHash PSP_MATSPECCOLOR("MatSpecColor");
extern URHO3D_API const StringHash PSP_NEARCLIP("NearClipPS");
extern URHO3D_API const StringHash PSP_FARCLIP("FarClipPS");
extern URHO3D_API const StringHash PSP_SHADOWCUBEADJUST("ShadowCubeAdjust");
extern URHO3D_API const StringHash PSP_SHADOWDEPTHFADE("ShadowDepthFade");
extern URHO3D_API const StringHash PSP_SHADOWINTENSITY("ShadowIntensity");
extern URHO3D_API const StringHash PSP_SHADOWMAPINVSIZE("ShadowMapInvSize");
extern URHO3D_API const StringHash PSP_SHADOWSPLITS("ShadowSplits");
extern URHO3D_API const StringHash PSP_LIGHTMATRICES("LightMatricesPS");

extern URHO3D_API const StringHash PASS_BASE("base");
extern URHO3D_API const StringHash PASS_LITBASE("litbase");
extern URHO3D_API const StringHash PASS_LIGHT("light");
extern URHO3D_API const StringHash PASS_ALPHA("alpha");
extern URHO3D_API const StringHash PASS_LITALPHA("litalpha");
extern URHO3D_API const StringHash PASS_SHADOW("shadow");
extern URHO3D_API const StringHash PASS_DEFERRED("deferred");
extern URHO3D_API const StringHash PASS_PREPASS("prepass");
extern URHO3D_API const StringHash PASS_MATERIAL("material");
extern URHO3D_API const StringHash PASS_POSTOPAQUE("postopaque");
extern URHO3D_API const StringHash PASS_REFRACT("refract");
extern URHO3D_API const StringHash PASS_POSTALPHA("postalpha");

extern URHO3D_API const Vector3 DOT_SCALE(1 / 3.0f, 1 / 3.0f, 1 / 3.0f);

}
