//
// Copyright (c) 2008-2013 the Urho3D project.
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
#include "StringHash.h"
#include "Vector3.h"

#include "DebugNew.h"

namespace Urho3D
{

StringHash VSP_AMBIENTSTARTCOLOR("AmbientStartColor");
StringHash VSP_AMBIENTENDCOLOR("AmbientEndColor");
StringHash VSP_BILLBOARDROT("BillboardRot");
StringHash VSP_CAMERAPOS("CameraPos");
StringHash VSP_CAMERAROT("CameraRot");
StringHash VSP_NEARCLIP("NearClip");
StringHash VSP_FARCLIP("FarClip");
StringHash VSP_DEPTHMODE("DepthMode");
StringHash VSP_DELTATIME("DeltaTime");
StringHash VSP_ELAPSEDTIME("ElapsedTime");
StringHash VSP_FRUSTUMSIZE("FrustumSize");
StringHash VSP_GBUFFEROFFSETS("GBufferOffsets");
StringHash VSP_LIGHTDIR("LightDir");
StringHash VSP_LIGHTPOS("LightPos");
StringHash VSP_MODEL("Model");
StringHash VSP_VIEWPROJ("ViewProj");
StringHash VSP_UOFFSET("UOffset");
StringHash VSP_VOFFSET("VOffset");
StringHash VSP_ZONE("Zone");
StringHash VSP_LIGHTMATRICES("LightMatrices");
StringHash VSP_SKINMATRICES("SkinMatrices");
StringHash VSP_VERTEXLIGHTS("VertexLights");
StringHash PSP_AMBIENTCOLOR("AmbientColor");
StringHash PSP_DELTATIME("DeltaTimePS");
StringHash PSP_ELAPSEDTIME("ElapsedTimePS");
StringHash PSP_FOGCOLOR("FogColor");
StringHash PSP_FOGPARAMS("FogParams");
StringHash PSP_GBUFFERINVSIZE("GBufferInvSize");
StringHash PSP_LIGHTCOLOR("LightColor");
StringHash PSP_LIGHTDIR("LightDirPS");
StringHash PSP_LIGHTPOS("LightPosPS");
StringHash PSP_MATDIFFCOLOR("MatDiffColor");
StringHash PSP_MATEMISSIVECOLOR("MatEmissiveColor");
StringHash PSP_MATENVMAPECOLOR("MatEnvMapColor");
StringHash PSP_MATSPECCOLOR("MatSpecColor");
StringHash PSP_NEARCLIP("NearClipPS");
StringHash PSP_FARCLIP("FarClipPS");
StringHash PSP_SHADOWCUBEADJUST("ShadowCubeAdjust");
StringHash PSP_SHADOWDEPTHFADE("ShadowDepthFade");
StringHash PSP_SHADOWINTENSITY("ShadowIntensity");
StringHash PSP_SHADOWMAPINVSIZE("ShadowMapInvSize");
StringHash PSP_SHADOWSPLITS("ShadowSplits");
StringHash PSP_LIGHTMATRICES("LightMatricesPS");

StringHash PASS_BASE("base");
StringHash PASS_LITBASE("litbase");
StringHash PASS_LIGHT("light");
StringHash PASS_ALPHA("alpha");
StringHash PASS_LITALPHA("litalpha");
StringHash PASS_SHADOW("shadow");
StringHash PASS_DEFERRED("deferred");
StringHash PASS_PREPASS("prepass");
StringHash PASS_MATERIAL("material");
StringHash PASS_POSTOPAQUE("postopaque");
StringHash PASS_REFRACT("refract");
StringHash PASS_POSTALPHA("postalpha");

Vector3 DOT_SCALE(1 / 3.0f, 1 / 3.0f, 1 / 3.0f);

}
