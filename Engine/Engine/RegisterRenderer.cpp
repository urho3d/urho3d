//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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
#include "AnimatedModel.h"
#include "Animation.h"
#include "AnimationState.h"
#include "BillboardSet.h"
#include "DebugRenderer.h"
#include "Engine.h"
#include "InstancedModel.h"
#include "Light.h"
#include "Material.h"
#include "Octree.h"
#include "OctreeQuery.h"
#include "Pipeline.h"
#include "RegisterTemplates.h"
#include "Renderer.h"
#include "Scene.h"
#include "ScriptInstance.h"
#include "Skybox.h"
#include "Texture2D.h"
#include "TextureCube.h"

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

static std::vector<RayQueryResult> rayQueryResult;
static std::vector<VolumeNode*> nodeResult;

static void registerCamera(asIScriptEngine* engine)
{
    engine->RegisterGlobalProperty("const uint VIEW_NONE", (void*)&VIEW_NONE);
    engine->RegisterGlobalProperty("const uint VIEW_MAIN", (void*)&VIEW_MAIN);
    engine->RegisterGlobalProperty("const uint VIEW_REFLECTION", (void*)&VIEW_REFLECTION);
    engine->RegisterGlobalProperty("const uint VIEW_CUBEREFLECTION", (void*)&VIEW_CUBEREFLECTION);
    engine->RegisterGlobalProperty("const uint VIEW_ALL", (void*)&VIEW_ALL);
    
    registerNode<Camera>(engine, "Camera");
    engine->RegisterObjectMethod("Camera", "void setNearClip(float)", asMETHOD(Camera, setNearClip), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void setFarClip(float)", asMETHOD(Camera, setFarClip), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void setFov(float)", asMETHOD(Camera, setFov), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void setOrthoSize(float)", asMETHODPR(Camera, setOrthoSize, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void setOrthoSize(const Vector2& in)", asMETHODPR(Camera, setOrthoSize, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void setAspectRatio(float)", asMETHOD(Camera, setAspectRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void setZoom(float)", asMETHOD(Camera, setZoom), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void setLodBias(float)", asMETHOD(Camera, setLodBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void setOrthographic(bool)", asMETHOD(Camera, setOrthographic), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void setAutoAspectRatio(bool)", asMETHOD(Camera, setAutoAspectRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void setViewMask(uint)", asMETHOD(Camera, setViewMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void setDrawShadowsOverride(bool)", asMETHOD(Camera, setDrawShadowsOverride), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void setLightDetailLevelOverride(int)", asMETHOD(Camera, setLightDetailLevelOverride), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void setMaterialQualityOverride(int)", asMETHOD(Camera, setMaterialQualityOverride), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void setMaxOccluderTrianglesOverride(int)", asMETHOD(Camera, setMaxOccluderTrianglesOverride), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float getFarClip() const", asMETHOD(Camera, getFarClip), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float getNearClip() const", asMETHOD(Camera, getNearClip), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float getFov() const", asMETHOD(Camera, getFov), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float getOrthoSize() const", asMETHOD(Camera, getOrthoSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float getAspectRatio() const", asMETHOD(Camera, getAspectRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float getZoom() const", asMETHOD(Camera, getZoom), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float getLodBias() const", asMETHOD(Camera, getLodBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool isOrthographic() const", asMETHOD(Camera, isOrthographic), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool getAutoAspectRatio() const", asMETHOD(Camera, getAutoAspectRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "uint getViewMask() const", asMETHOD(Camera, getViewMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool getDrawShadowsOverride() const", asMETHOD(Camera, getDrawShadowsOverride), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "int getLightDetailLevelOverride() const", asMETHOD(Camera, getLightDetailLevelOverride), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "int getMaterialQualityOverride() const", asMETHOD(Camera, getMaterialQualityOverride), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "int getMaxOccluderTrianglesOverride() const", asMETHOD(Camera, getMaxOccluderTrianglesOverride), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "const Frustum& getFrustum()", asMETHOD(Camera, getFrustum), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "const Vector3& getFrustumNearSize()", asMETHOD(Camera, getFrustumNearSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "const Vector3& getFrustumFarSize()", asMETHOD(Camera, getFrustumFarSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float getHalfViewSize() const", asMETHOD(Camera, getHalfViewSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Frustum getViewSpaceFrustum() const", asMETHOD(Camera, getViewSpaceFrustum), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Frustum getSplitFrustum(float, float)", asMETHOD(Camera, getSplitFrustum), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Ray getScreenRay(float, float)", asMETHOD(Camera, getScreenRay), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Vector3 getForwardVector()", asMETHOD(Camera, getForwardVector), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Vector3 getRightVector()", asMETHOD(Camera, getRightVector), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Vector3 getUpVector()", asMETHOD(Camera, getUpVector), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float getDistance(const Vector3& in)", asMETHOD(Camera, getDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float getDistanceSquared(const Vector3& in)", asMETHOD(Camera, getDistanceSquared), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool isInView(uint) const", asMETHOD(Camera, isInView), asCALL_THISCALL);
    registerRefCasts<Component, Camera>(engine, "Component", "Camera");
    registerRefCasts<Node, Camera>(engine, "Node", "Camera");
}

static void registerSkeleton(asIScriptEngine* engine)
{
    registerNode<Bone>(engine, "Bone");
    engine->RegisterObjectMethod("Bone", "void setAnimationEnabled(bool)", asMETHOD(Bone, setAnimationEnabled), asCALL_THISCALL);
    engine->RegisterObjectMethod("Bone", "void setRadius(float)", asMETHOD(Bone, setRadius), asCALL_THISCALL);
    engine->RegisterObjectMethod("Bone", "void setBoundingBox(const BoundingBox& in)", asMETHOD(Bone, setBoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("Bone", "void reset(bool)", asMETHOD(Bone, reset), asCALL_THISCALL);
    engine->RegisterObjectMethod("Bone", "Bone@+ getRootBone()", asMETHOD(Bone, getRootBone), asCALL_THISCALL);
    engine->RegisterObjectMethod("Bone", "float getRadius() const", asMETHOD(Bone, getRadius), asCALL_THISCALL);
    engine->RegisterObjectMethod("Bone", "const BoundingBox& getBoundingBox() const", asMETHOD(Bone, getBoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("Bone", "bool isAnimationEnabled() const", asMETHOD(Bone, isAnimationEnabled), asCALL_THISCALL);
    registerRefCasts<Component, Bone>(engine, "Component", "Bone");
    registerRefCasts<Node, Bone>(engine, "Node", "Bone");
    
    engine->RegisterObjectType("Skeleton", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("Skeleton", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Skeleton", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Skeleton", "void reset(bool)", asMETHOD(Skeleton, reset), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skeleton", "Bone@+ getRootBone() const", asMETHOD(Skeleton, getRootBone), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skeleton", "uint getNumBones() const", asMETHOD(Skeleton, getNumBones), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skeleton", "Bone@+ getBone(uint) const", asMETHODPR(Skeleton, getBone, (unsigned) const, Bone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skeleton", "Bone@+ getBone(const string& in) const", asMETHODPR(Skeleton, getBone, (const std::string&) const, Bone*), asCALL_THISCALL);
}

static Texture2D* ConstructTexture2D(TextureUsage usage, const std::string& name)
{
    TRY_CONSTRUCT(new Texture2D(getEngine()->getRenderer(), usage, name));
}

static void Texture2DSetSize(int width, int height, unsigned format, Texture2D* ptr)
{
    TRY_SAFE_RETHROW(ptr->setSize(width, height, format));
}

static void Texture2DLoad(Image* image, Texture2D* ptr)
{
    TRY_SAFE_RETHROW(ptr->load(SharedPtr<Image>(image)));
}

static TextureCube* ConstructTextureCube(TextureUsage usage, const std::string& name)
{
    TRY_CONSTRUCT(new TextureCube(getEngine()->getRenderer(), usage, name));
}

static void TextureCubeSetSize(int size, unsigned format, TextureCube* ptr)
{
    TRY_SAFE_RETHROW(ptr->setSize(size, format));
}

static void TextureCubeLoad(CubeMapFace face, Image* image, TextureCube* ptr)
{
    TRY_SAFE_RETHROW(ptr->load(face, SharedPtr<Image>(image)));
}

static void registerTexture(asIScriptEngine* engine)
{
    engine->RegisterEnum("TextureUsage");
    engine->RegisterEnumValue("TextureUsage", "TEXTURE_STATIC", TEXTURE_STATIC);
    engine->RegisterEnumValue("TextureUsage", "TEXTURE_DYNAMIC", TEXTURE_DYNAMIC);
    engine->RegisterEnumValue("TextureUsage", "TEXTURE_RENDERTARGET", TEXTURE_RENDERTARGET);
    engine->RegisterEnumValue("TextureUsage", "TEXTURE_DEPTHSTENCIL", TEXTURE_DEPTHSTENCIL);
    
    engine->RegisterEnum("TextureFilterMode");
    engine->RegisterEnumValue("TextureFilterMode", "FILTER_NEAREST", FILTER_NEAREST);
    engine->RegisterEnumValue("TextureFilterMode", "FILTER_BILINEAR", FILTER_BILINEAR);
    engine->RegisterEnumValue("TextureFilterMode", "FILTER_TRILINEAR", FILTER_TRILINEAR);
    engine->RegisterEnumValue("TextureFilterMode", "FILTER_ANISOTROPIC", FILTER_ANISOTROPIC);
    engine->RegisterEnumValue("TextureFilterMode", "FILTER_DEFAULT", FILTER_DEFAULT);
    
    engine->RegisterEnum("TextureAddressMode");
    engine->RegisterEnumValue("TextureAddressMode", "ADDRESS_WRAP", ADDRESS_WRAP);
    engine->RegisterEnumValue("TextureAddressMode", "ADDRESS_MIRROR", ADDRESS_MIRROR);
    engine->RegisterEnumValue("TextureAddressMode", "ADDRESS_CLAMP", ADDRESS_CLAMP);
    engine->RegisterEnumValue("TextureAddressMode", "ADDRESS_BORDER", ADDRESS_BORDER);
    
    engine->RegisterEnum("TextureCoordinate");
    engine->RegisterEnumValue("TextureCoordinate", "COORD_U", COORD_U);
    engine->RegisterEnumValue("TextureCoordinate", "COORD_V", COORD_V);
    engine->RegisterEnumValue("TextureCoordinate", "COORD_W", COORD_W);
    
    engine->RegisterEnum("CubeMapFace");
    engine->RegisterEnumValue("CubeMapFace", "FACE_POSITIVE_X", FACE_POSITIVE_X);
    engine->RegisterEnumValue("CubeMapFace", "FACE_NEGATIVE_X", FACE_NEGATIVE_X);
    engine->RegisterEnumValue("CubeMapFace", "FACE_POSITIVE_Y", FACE_POSITIVE_Y);
    engine->RegisterEnumValue("CubeMapFace", "FACE_NEGATIVE_Y", FACE_NEGATIVE_Y);
    engine->RegisterEnumValue("CubeMapFace", "FACE_POSITIVE_Z", FACE_POSITIVE_Z);
    engine->RegisterEnumValue("CubeMapFace", "FACE_NEGATIVE_Z", FACE_NEGATIVE_Z);
    
    registerTexture<Texture>(engine, "Texture");
    registerRefCasts<Resource, Texture>(engine, "Resource", "Texture");
    
    engine->RegisterObjectType("RenderSurface", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("RenderSurface", asBEHAVE_ADDREF, "void f()", asMETHOD(RenderSurface, addRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("RenderSurface", asBEHAVE_RELEASE, "void f()", asMETHOD(RenderSurface, releaseRef), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "void setCamera(Camera@+)", asMETHOD(RenderSurface, setCamera), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "void setLinkedRenderTarget(RenderSurface@+)", asMETHOD(RenderSurface, setLinkedRenderTarget), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "void setLinkedDepthBuffer(RenderSurface@+)", asMETHOD(RenderSurface, setLinkedDepthBuffer), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "Texture@+ getParentTexture() const", asMETHOD(RenderSurface, getParentTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "int getWidth() const", asMETHOD(RenderSurface, getWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "int getHeight() const", asMETHOD(RenderSurface, getHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "TextureUsage getUsage() const", asMETHOD(RenderSurface, getUsage), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "Camera@+ getCamera() const", asMETHOD(RenderSurface, getCamera), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "RenderSurface@+ getLinkedRenderTarget() const", asMETHOD(RenderSurface, getLinkedRenderTarget), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "RenderSurface@+ getLinkedDepthBuffer() const", asMETHOD(RenderSurface, getLinkedDepthBuffer), asCALL_THISCALL);
    
    registerTexture<Texture2D>(engine, "Texture2D");
    engine->RegisterObjectBehaviour("Texture2D", asBEHAVE_FACTORY, "Texture2D@+ f(TextureUsage, const string& in)", asFUNCTION(ConstructTexture2D), asCALL_CDECL);
    engine->RegisterObjectMethod("Texture2D", "void setSize(int, int, uint)", asFUNCTION(Texture2DSetSize), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Texture2D", "void load(Image@+)", asFUNCTION(Texture2DLoad), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Texture2D", "RenderSurface@+ getRenderSurface() const", asMETHOD(Texture2D, getRenderSurface), asCALL_THISCALL);
    registerRefCasts<Resource, Texture2D>(engine, "Resource", "Texture2D");
    registerRefCasts<Texture, Texture2D>(engine, "Texture", "Texture2D");
    
    registerTexture<TextureCube>(engine, "TextureCube");
    engine->RegisterObjectBehaviour("TextureCube", asBEHAVE_FACTORY, "TextureCube@+ f(TextureUsage, const string& in)", asFUNCTION(ConstructTextureCube), asCALL_CDECL);
    engine->RegisterObjectMethod("TextureCube", "void setSize(int, uint)", asFUNCTION(TextureCubeSetSize), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("TextureCube", "void load(CubeMapFace, Image@+)", asFUNCTION(TextureCubeLoad), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("TextureCube", "RenderSurface@+ getRenderSurface(CubeMapFace) const", asMETHOD(TextureCube, getRenderSurface), asCALL_THISCALL);
    registerRefCasts<Resource, TextureCube>(engine, "Resource", "TextureCube");
    registerRefCasts<Texture, TextureCube>(engine, "Texture", "TextureCube");
}

static Vector4 MaterialTechniqueGetVSParam(VSParameter parameter, MaterialTechnique* ptr)
{
    const std::map<VSParameter, Vector4>& parameters = ptr->getVertexShaderParameters();
    std::map<VSParameter, Vector4>::const_iterator i = parameters.find(parameter);
    if (i == parameters.end())
        return Vector4::sZero;
    else
        return i->second;
}

static Vector4 MaterialTechniqueGetPSParam(PSParameter parameter, MaterialTechnique* ptr)
{
    const std::map<PSParameter, Vector4>& parameters = ptr->getPixelShaderParameters();
    std::map<PSParameter, Vector4>::const_iterator i = parameters.find(parameter);
    if (i == parameters.end())
        return Vector4::sZero;
    else
        return i->second;
}

static Material* ConstructMaterial(const std::string& name)
{
    return new Material(name);
}

static Material* MaterialClone(const std::string& cloneName, Material* ptr)
{
    SharedPtr<Material> clonedMaterial = ptr->clone(cloneName);
    // The shared pointer will go out of scope, so have to increment the reference count
    // (here an auto handle can not be used)
    clonedMaterial->addRef();
    return clonedMaterial.getPtr();
}

static void registerMaterial(asIScriptEngine* engine)
{
    engine->RegisterEnum("VSParameter");
    engine->RegisterEnumValue("VSParameter", "VSP_AMBIENTCOLOR", VSP_AMBIENTCOLOR);
    engine->RegisterEnumValue("VSParameter", "VSP_DEPTHMODE", VSP_DEPTHMODE);
    engine->RegisterEnumValue("VSParameter", "VSP_ELAPSEDTIME", VSP_ELAPSEDTIME);
    engine->RegisterEnumValue("VSParameter", "VSP_FRUSTUMSIZE", VSP_FRUSTUMSIZE);
    engine->RegisterEnumValue("VSParameter", "VSP_GBUFFEROFFSETS", VSP_GBUFFEROFFSETS);
    engine->RegisterEnumValue("VSParameter", "VSP_MODEL", VSP_MODEL);
    engine->RegisterEnumValue("VSParameter", "VSP_MODELVIEWPROJ", VSP_MODELVIEWPROJ);
    engine->RegisterEnumValue("VSParameter", "VSP_SHADOWPROJ", VSP_SHADOWPROJ);
    engine->RegisterEnumValue("VSParameter", "VSP_SPOTPROJ", VSP_SPOTPROJ);
    engine->RegisterEnumValue("VSParameter", "VSP_VIEWINVERSE", VSP_VIEWINVERSE);
    engine->RegisterEnumValue("VSParameter", "VSP_VIEWPROJ", VSP_VIEWPROJ);
    engine->RegisterEnumValue("VSParameter", "VSP_UOFFSET", VSP_UOFFSET);
    engine->RegisterEnumValue("VSParameter", "VSP_VOFFSET", VSP_VOFFSET);
    engine->RegisterEnumValue("VSParameter", "VSP_VIEWRIGHTVECTOR", VSP_VIEWRIGHTVECTOR);
    engine->RegisterEnumValue("VSParameter", "VSP_VIEWUPVECTOR", VSP_VIEWUPVECTOR);
    engine->RegisterEnumValue("VSParameter", "VSP_MODELSKINMATRICES", VSP_MODELSKINMATRICES);
    engine->RegisterEnumValue("VSParameter", "VSP_MODELINSTANCES", VSP_MODELINSTANCES);
    
    engine->RegisterEnum("PSParameter");
    engine->RegisterEnumValue("PSParameter", "PSP_DEPTHRECONSTRUCT", PSP_DEPTHRECONSTRUCT);
    engine->RegisterEnumValue("PSParameter", "PSP_EDGEFILTERPARAMS", PSP_EDGEFILTERPARAMS);
    engine->RegisterEnumValue("PSParameter", "PSP_ELAPSEDTIME", PSP_ELAPSEDTIME);
    engine->RegisterEnumValue("PSParameter", "PSP_FOGCOLOR", PSP_FOGCOLOR);
    engine->RegisterEnumValue("PSParameter", "PSP_FOGPARAMS", PSP_FOGPARAMS);
    engine->RegisterEnumValue("PSParameter", "PSP_LIGHTATTEN", PSP_LIGHTATTEN);
    engine->RegisterEnumValue("PSParameter", "PSP_LIGHTCOLOR", PSP_LIGHTCOLOR);
    engine->RegisterEnumValue("PSParameter", "PSP_LIGHTDIR", PSP_LIGHTDIR);
    engine->RegisterEnumValue("PSParameter", "PSP_LIGHTPOS", PSP_LIGHTPOS);
    engine->RegisterEnumValue("PSParameter", "PSP_LIGHTSPLITS", PSP_LIGHTSPLITS);
    engine->RegisterEnumValue("PSParameter", "PSP_MATDIFFCOLOR", PSP_MATDIFFCOLOR);
    engine->RegisterEnumValue("PSParameter", "PSP_MATEMISSIVECOLOR", PSP_MATEMISSIVECOLOR);
    engine->RegisterEnumValue("PSParameter", "PSP_MATSPECPROPERTIES", PSP_MATSPECPROPERTIES);
    engine->RegisterEnumValue("PSParameter", "PSP_SAMPLEOFFSETS", PSP_SAMPLEOFFSETS);
    engine->RegisterEnumValue("PSParameter", "PSP_SHADOWPROJ", PSP_SHADOWPROJ);
    engine->RegisterEnumValue("PSParameter", "PSP_SPOTPROJ", PSP_SPOTPROJ);
    
    engine->RegisterEnum("TextureUnit");
    engine->RegisterEnumValue("TextureUnit", "TU_DIFFUSE", TU_DIFFUSE);
    engine->RegisterEnumValue("TextureUnit", "TU_NORMAL", TU_NORMAL);
    engine->RegisterEnumValue("TextureUnit", "TU_SPECULAR", TU_SPECULAR);
    engine->RegisterEnumValue("TextureUnit", "TU_DETAIL", TU_DETAIL);
    engine->RegisterEnumValue("TextureUnit", "TU_ENVIRONMENT", TU_ENVIRONMENT);
    engine->RegisterEnumValue("TextureUnit", "TU_EMISSIVE", TU_EMISSIVE);
    
    engine->RegisterEnum("PassType");
    engine->RegisterEnumValue("PassType", "PASS_DEFERRED", PASS_DEFERRED);
    engine->RegisterEnumValue("PassType", "PASS_PREPASS", PASS_PREPASS);
    engine->RegisterEnumValue("PassType", "PASS_MATERIAL", PASS_MATERIAL);
    engine->RegisterEnumValue("PassType", "PASS_EMISSIVE", PASS_EMISSIVE);
    engine->RegisterEnumValue("PassType", "PASS_POSTOPAQUE", PASS_POSTOPAQUE);
    engine->RegisterEnumValue("PassType", "PASS_AMBIENT", PASS_AMBIENT);
    engine->RegisterEnumValue("PassType", "PASS_NEGATIVE", PASS_NEGATIVE);
    engine->RegisterEnumValue("PassType", "PASS_LIGHT", PASS_LIGHT);
    engine->RegisterEnumValue("PassType", "PASS_SHADOW", PASS_SHADOW);
    
    engine->RegisterEnum("BlendMode");
    engine->RegisterEnumValue("BlendMode", "BLEND_REPLACE", BLEND_REPLACE);
    engine->RegisterEnumValue("BlendMode", "BLEND_ADD", BLEND_ADD);
    engine->RegisterEnumValue("BlendMode", "BLEND_MULTIPLY", BLEND_MULTIPLY);
    engine->RegisterEnumValue("BlendMode", "BLEND_ALPHA", BLEND_ALPHA);
    engine->RegisterEnumValue("BlendMode", "BLEND_ADDALPHA", BLEND_ADDALPHA);
    engine->RegisterEnumValue("BlendMode", "BLEND_PREMULALPHA", BLEND_PREMULALPHA);
    engine->RegisterEnumValue("BlendMode", "BLEND_INVDESTALPHA", BLEND_INVDESTALPHA);
    
    engine->RegisterEnum("CompareMode");
    engine->RegisterEnumValue("CompareMode", "CMP_ALWAYS", CMP_ALWAYS);
    engine->RegisterEnumValue("CompareMode", "CMP_EQUAL", CMP_EQUAL);
    engine->RegisterEnumValue("CompareMode", "CMP_NOTEQUAL", CMP_NOTEQUAL);
    engine->RegisterEnumValue("CompareMode", "CMP_LESS", CMP_LESS);
    engine->RegisterEnumValue("CompareMode", "CMP_LESSEQUAL", CMP_LESSEQUAL);
    engine->RegisterEnumValue("CompareMode", "CMP_GREATER", CMP_GREATER);
    engine->RegisterEnumValue("CompareMode", "CMP_GREATEREQUAL", CMP_GREATEREQUAL);
    
    engine->RegisterEnum("CullMode");
    engine->RegisterEnumValue("CullMode", "CULL_NONE", CULL_NONE);
    engine->RegisterEnumValue("CullMode", "CULL_CCW", CULL_CCW);
    engine->RegisterEnumValue("CullMode", "CULL_CW", CULL_CW);
    
    engine->RegisterObjectType("MaterialPass", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("MaterialPass", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("MaterialPass", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("MaterialPass", "void setAlphaMask(bool)", asMETHOD(MaterialPass, setAlphaMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialPass", "void setAlphaTest(bool)", asMETHOD(MaterialPass, setAlphaTest), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialPass", "void setBlendMode(BlendMode)", asMETHOD(MaterialPass, setBlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialPass", "void setCullMode(CullMode)", asMETHOD(MaterialPass, setCullMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialPass", "void setDepthTestMode(CompareMode)", asMETHOD(MaterialPass, setDepthTestMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialPass", "void setDepthWrite(bool)", asMETHOD(MaterialPass, setDepthWrite), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialPass", "void setVertexShader(const string& in)", asMETHOD(MaterialPass, setVertexShader), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialPass", "void setPixelShader(const string& in)", asMETHOD(MaterialPass, setPixelShader), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialPass", "bool getAlphaMask() const", asMETHOD(MaterialPass, getAlphaMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialPass", "bool getAlphaTest() const", asMETHOD(MaterialPass, getAlphaTest), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialPass", "BlendMode getBlendMode() const", asMETHOD(MaterialPass, getBlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialPass", "CullMode getCullMode() const", asMETHOD(MaterialPass, getCullMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialPass", "CompareMode getDepthTestMode() const", asMETHOD(MaterialPass, getDepthTestMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialPass", "bool getDepthWrite() const", asMETHOD(MaterialPass, getDepthWrite), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialPass", "const string& getVertexShaderName() const", asMETHOD(MaterialPass, getVertexShaderName), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialPass", "const string& getPixelShaderName() const", asMETHOD(MaterialPass, getPixelShaderName), asCALL_THISCALL);
    
    engine->RegisterObjectType("MaterialTechnique", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("MaterialTechnique", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("MaterialTechnique", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("MaterialTechnique", "void setQualityLevel(int)", asMETHOD(MaterialTechnique, setQualityLevel), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialTechnique", "void setLodDistance(float)", asMETHOD(MaterialTechnique, setLodDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialTechnique", "void setRequireSM3(bool)", asMETHOD(MaterialTechnique, setRequireSM3), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialTechnique", "void setVertexShaderParameter(VSParameter, const Vector4& in)", asMETHOD(MaterialTechnique, setVertexShaderParameter), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialTechnique", "void setPixelShaderParameter(PSParameter, const Vector4& in)", asMETHOD(Material, setPixelShaderParameter), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialTechnique", "void setTexture(TextureUnit, Texture@+)", asMETHOD(MaterialTechnique, setTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialTechnique", "void setUVTransform(const Vector2& in, float, const Vector2& in)", asMETHODPR(MaterialTechnique, setUVTransform, (const Vector2&, float, const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialTechnique", "void setUVTransform(const Vector2& in, float, float)", asMETHODPR(MaterialTechnique, setUVTransform, (const Vector2&, float, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialTechnique", "MaterialPass@+ createPass(PassType)", asMETHOD(MaterialTechnique, createPass), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialTechnique", "void removePass(PassType)", asMETHOD(MaterialTechnique, removePass), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialTechnique", "bool hasPass(PassType) const", asMETHOD(MaterialTechnique, hasPass), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialTechnique", "MaterialPass@+ getPass(PassType)", asMETHOD(MaterialTechnique, getPass), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialTechnique", "int getQualityLevel() const", asMETHOD(MaterialTechnique, getQualityLevel), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialTechnique", "float getLodDistance() const", asMETHOD(MaterialTechnique, getLodDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialTechnique", "bool getRequireSM3() const", asMETHOD(MaterialTechnique, getRequireSM3), asCALL_THISCALL);
    engine->RegisterObjectMethod("MaterialTechnique", "Vector4 getVertexShaderParameter(VSParameter) const", asFUNCTION(MaterialTechniqueGetVSParam), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("MaterialTechnique", "Vector4 getPixelShaderParameter(PSParameter) const", asFUNCTION(MaterialTechniqueGetPSParam), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("MaterialTechnique", "Texture@+ getTexture(TextureUnit) const", asMETHOD(MaterialTechnique, getTexture), asCALL_THISCALL);
    
    registerResource<Material>(engine, "Material");
    engine->RegisterObjectBehaviour("Material", asBEHAVE_FACTORY, "Material@+ f(const string& in)", asFUNCTION(ConstructMaterial), asCALL_CDECL);
    engine->RegisterObjectMethod("Material", "void setNumTechniques(uint)", asMETHOD(Material, setNumTechniques), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void setVertexShaderParameter(VSParameter, const Vector4& in)", asMETHOD(Material, setVertexShaderParameter), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void setPixelShaderParameter(PSParameter, const Vector4& in)", asMETHOD(Material, setPixelShaderParameter), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void setTexture(TextureUnit, Texture@+)", asMETHOD(Material, setTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void setUVTransform(const Vector2& in, float, const Vector2& in)", asMETHODPR(Material, setUVTransform, (const Vector2&, float, const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void setUVTransform(const Vector2& in, float, float)", asMETHODPR(Material, setUVTransform, (const Vector2&, float, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "Material@ clone(const string& in) const", asFUNCTION(MaterialClone), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Material", "uint getNumTechniques() const", asMETHOD(Material, getNumTechniques), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "MaterialTechnique@+ getTechnique(uint)", asMETHOD(Material, getTechnique), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "MaterialPass@+ getPass(uint, PassType)", asMETHOD(Material, getPass), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "bool getCastShadows()", asMETHOD(Material, getCastShadows), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "bool getOcclusion()", asMETHOD(Material, getOcclusion), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "CullMode getOcclusionCullMode()", asMETHOD(Material, getOcclusionCullMode), asCALL_THISCALL);
    registerRefCasts<Resource, Material>(engine, "Resource", "Material");
}

static void registerModel(asIScriptEngine* engine)
{
    registerResource<Model>(engine, "Model");
    engine->RegisterObjectMethod("Model", "const BoundingBox& getBoundingBox() const", asMETHOD(Model, getBoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "Skeleton@+ getSkeleton() const", asMETHOD(Model, getSkeleton), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "uint getNumGeometries() const", asMETHOD(Model, getNumGeometries), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "uint getNumGeometryLodLevels(uint) const", asMETHOD(Model, getNumGeometryLodLevels), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "uint getNumMorphs() const", asMETHOD(Model, getNumMorphs), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "uint getCollisionLodLevel() const", asMETHOD(Model, getCollisionLodLevel), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "uint getRaycastLodLevel() const", asMETHOD(Model, getRaycastLodLevel), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "uint getOcclusionLodLevel() const", asMETHOD(Model, getOcclusionLodLevel), asCALL_THISCALL);
    registerRefCasts<Resource, Model>(engine, "Resource", "Model");
}

static void registerAnimation(asIScriptEngine* engine)
{
    registerResource<Animation>(engine, "Animation");
    engine->RegisterObjectMethod("Animation", "const string& getAnimationName() const", asMETHOD(Animation, getAnimationName), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "float getLength() const", asMETHOD(Animation, getLength), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "uint getNumTracks() const", asMETHOD(Animation, getNumTracks), asCALL_THISCALL);
    registerRefCasts<Resource, Animation>(engine, "Resource", "Animation");
}

static void registerVolumeNode(asIScriptEngine* engine)
{
    registerVolumeNode<VolumeNode>(engine, "VolumeNode");
    registerRefCasts<Component, VolumeNode>(engine, "Component", "VolumeNode");
    registerRefCasts<Node, VolumeNode>(engine, "Node", "VolumeNode");
}

static void registerGeometryNode(asIScriptEngine* engine)
{
    registerGeometryNode<GeometryNode>(engine, "GeometryNode");
    registerRefCasts<Component, GeometryNode>(engine, "Component", "GeometryNode");
    registerRefCasts<Node, GeometryNode>(engine, "Node", "GeometryNode");
}

static void ConstructBiasParameters(BiasParameters* ptr)
{
    new(ptr) BiasParameters(0.0f, 0.0f);
}

static void ConstructBiasParametersCopy(BiasParameters& parameters, BiasParameters* ptr)
{
    new(ptr) BiasParameters(parameters);
}

static void ConstructBiasParametersInit(float constantBias, float slopeScaledBias, BiasParameters* ptr)
{
    new(ptr) BiasParameters(constantBias, slopeScaledBias);
}

static void ConstructCascadeParameters(CascadeParameters* ptr)
{
    new(ptr) CascadeParameters(1, 0.0f, 0.0f, 0.0f);
}

static void ConstructCascadeParametersCopy(CascadeParameters& parameters, CascadeParameters* ptr)
{
    new(ptr) CascadeParameters(parameters);
}

static void ConstructCascadeParametersInit(unsigned splits, float lambda, float splitFadeRange, float shadowRange, CascadeParameters* ptr)
{
    new(ptr) CascadeParameters(splits, lambda, splitFadeRange, shadowRange);
}

static void ConstructFocusParameters(FocusParameters* ptr)
{
    new(ptr) FocusParameters(false, false, false, 0.0f, 0.0f);
}

static void ConstructFocusParametersCopy(FocusParameters& parameters, FocusParameters* ptr)
{
    new(ptr) FocusParameters(parameters);
}

static void ConstructFocusParametersInit(bool focus, bool nonUniform, bool zoomOut, float quantize, float minView, FocusParameters* ptr)
{
    new(ptr) FocusParameters(focus, nonUniform, zoomOut, quantize, minView);
}

static void registerLight(asIScriptEngine* engine)
{
    engine->RegisterEnum("LightType");
    engine->RegisterEnumValue("LightType", "LIGHT_DIRECTIONAL", LIGHT_DIRECTIONAL);
    engine->RegisterEnumValue("LightType", "LIGHT_POINT", LIGHT_POINT);
    engine->RegisterEnumValue("LightType", "LIGHT_SPOT", LIGHT_SPOT);
    
    engine->RegisterObjectType("BiasParameters", sizeof(BiasParameters), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C);
    engine->RegisterObjectBehaviour("BiasParameters", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructBiasParameters), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("BiasParameters", asBEHAVE_CONSTRUCT, "void f(const BiasParameters& in)", asFUNCTION(ConstructBiasParametersCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("BiasParameters", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(ConstructBiasParametersInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("BiasParameters", "float constantBias", offsetof(BiasParameters, mConstantBias));
    engine->RegisterObjectProperty("BiasParameters", "float slopeScaledBias", offsetof(BiasParameters, mSlopeScaledBias));
    
    engine->RegisterObjectType("CascadeParameters", sizeof(CascadeParameters), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C);
    engine->RegisterObjectBehaviour("CascadeParameters", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructCascadeParameters), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("CascadeParameters", asBEHAVE_CONSTRUCT, "void f(const CascadeParameters& in)", asFUNCTION(ConstructCascadeParametersCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("CascadeParameters", asBEHAVE_CONSTRUCT, "void f(uint, float, float, float)", asFUNCTION(ConstructCascadeParametersInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("CascadeParameters", "uint splits", offsetof(CascadeParameters, mSplits));
    engine->RegisterObjectProperty("CascadeParameters", "float lambda", offsetof(CascadeParameters, mLambda));
    engine->RegisterObjectProperty("CascadeParameters", "float splitFadeRange", offsetof(CascadeParameters, mSplitFadeRange));
    engine->RegisterObjectProperty("CascadeParameters", "float shadowRange", offsetof(CascadeParameters, mShadowRange));
    
    engine->RegisterObjectType("FocusParameters", sizeof(FocusParameters), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C);
    engine->RegisterObjectBehaviour("FocusParameters", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructFocusParameters), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("FocusParameters", asBEHAVE_CONSTRUCT, "void f(const FocusParameters& in)", asFUNCTION(ConstructFocusParametersCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("FocusParameters", asBEHAVE_CONSTRUCT, "void f(bool, bool, bool, float, float)", asFUNCTION(ConstructFocusParametersInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("FocusParameters", "bool focus", offsetof(FocusParameters, mFocus));
    engine->RegisterObjectProperty("FocusParameters", "bool nonUniform", offsetof(FocusParameters, mNonUniform));
    engine->RegisterObjectProperty("FocusParameters", "bool zoomOut", offsetof(FocusParameters, mZoomOut));
    engine->RegisterObjectProperty("FocusParameters", "float quantize", offsetof(FocusParameters, mQuantize));
    engine->RegisterObjectProperty("FocusParameters", "float minView", offsetof(FocusParameters, mMinView));
    
    registerVolumeNode<Light>(engine, "Light");
    engine->RegisterObjectMethod("Light", "void setLightType(LightType)", asMETHOD(Light, setLightType), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void setDirection(const Vector3& in)", asMETHOD(Light, setDirection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void setColor(const Color& in)", asMETHOD(Light, setColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void setSpecularIntensity(float)", asMETHOD(Light, setSpecularIntensity), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void setRange(float)", asMETHOD(Light, setRange), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void setFov(float)", asMETHOD(Light, setFov), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void setAspectRatio(float)", asMETHOD(Light, setAspectRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void setFadeDistance(float)", asMETHOD(Light, setFadeDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void setDetailLevel(int, int)", asMETHOD(Light, setDetailLevel), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void setShadowBias(const BiasParameters& in)", asMETHOD(Light, setShadowBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void setShadowCascade(const CascadeParameters& in)", asMETHOD(Light, setShadowCascade), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void setShadowFocus(const FocusParameters& in)", asMETHOD(Light, setShadowFocus), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void setShadowFadeDistance(float)", asMETHOD(Light, setShadowFadeDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void setShadowIntensity(float)", asMETHOD(Light, setShadowIntensity), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void setShadowResolution(float)", asMETHOD(Light, setShadowResolution), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void setShadowNearFarRatio(float)", asMETHOD(Light, setShadowNearFarRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void setRampTexture(Texture@+)", asMETHOD(Light, setRampTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void setSpotTexture(Texture@+)", asMETHOD(Light, setSpotTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "LightType getLightType() const", asMETHOD(Light, getLightType), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const Vector3& getDirection() const", asMETHOD(Light, getDirection), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const Color& getColor() const", asMETHOD(Light, getColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float getSpecularIntensity() const", asMETHOD(Light, getSpecularIntensity), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool isNegative() const", asMETHOD(Light, isNegative), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float getRange() const", asMETHOD(Light, getRange), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float getFov() const", asMETHOD(Light, getFov), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float getAspectRatio() const", asMETHOD(Light, getAspectRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float getFadeDistance() const", asMETHOD(Light, getFadeDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "int getDetailLevel() const", asMETHOD(Light, getDetailLevel), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "int getShadowDetailLevel() const", asMETHOD(Light, getShadowDetailLevel), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const BiasParameters& getShadowBias() const", asMETHOD(Light, getShadowBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const CascadeParameters& getShadowCascade() const", asMETHOD(Light, getShadowCascade), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const FocusParameters& getShadowFocus() const", asMETHOD(Light, getShadowFocus), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float getShadowFadeDistance() const", asMETHOD(Light, getShadowFadeDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float getShadowIntensity() const", asMETHOD(Light, getShadowIntensity), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float getShadowResolution() const", asMETHOD(Light, getShadowResolution), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float getShadowNearFarRatio() const", asMETHOD(Light, getShadowNearFarRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "Texture@+ getRampTexture() const", asMETHOD(Light, getRampTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "Texture@+ getSpotTexture() const", asMETHOD(Light, getSpotTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const Frustum& getFrustum()", asMETHOD(Light, getFrustum), asCALL_THISCALL);
    registerRefCasts<Component, Light>(engine, "Component", "Light");
    registerRefCasts<Node, Light>(engine, "Node", "Light");
}

static void registerZone(asIScriptEngine* engine)
{
    registerVolumeNode<Zone>(engine, "Zone");
    engine->RegisterObjectMethod("Zone", "void setBoundingBox(const BoundingBox& in)", asMETHOD(Zone, setBoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void setAmbientColor(const Color& in)", asMETHOD(Zone, setAmbientColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void setFogColor(const Color& in)", asMETHOD(Zone, setFogColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void setFogStart(float)", asMETHOD(Zone, setFogStart), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void setFogEnd(float)", asMETHOD(Zone, setFogEnd), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void setPriority(int)", asMETHOD(Zone, setPriority), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const BoundingBox& getBoundingBox() const", asMETHOD(Zone, getBoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const Color& getAmbientColor() const", asMETHOD(Zone, getAmbientColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const Color& getFogColor() const", asMETHOD(Zone, getFogColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "float getFogStart() const", asMETHOD(Zone, getFogStart), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "float getFogEnd() const", asMETHOD(Zone, getFogEnd), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "int getPriority() const", asMETHOD(Zone, getPriority), asCALL_THISCALL);
    registerRefCasts<Component, Zone>(engine, "Component", "Zone");
    registerRefCasts<Node, Zone>(engine, "Node", "Zone");
}

static void registerStaticModel(asIScriptEngine* engine)
{
    registerGeometryNode<StaticModel>(engine, "StaticModel");
    engine->RegisterObjectMethod("StaticModel", "void setModel(Model@+)", asMETHOD(StaticModel, setModel), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void setMaterial(Material@+)", asMETHODPR(StaticModel, setMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "bool setMaterial(uint, Material@+)", asMETHODPR(StaticModel, setMaterial, (unsigned, Material*), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "const BoundingBox& getBoundingBox() const", asMETHOD(StaticModel, getBoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "uint getNumGeometries() const", asMETHOD(StaticModel, getNumGeometries), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "Material@+ getMaterial(uint) const", asMETHOD(StaticModel, getMaterial), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "Model@+ getModel() const", asMETHOD(StaticModel, getModel), asCALL_THISCALL);
    registerRefCasts<Component, StaticModel>(engine, "Component", "StaticModel");
    registerRefCasts<Node, StaticModel>(engine, "Node", "StaticModel");
}

static void registerSkybox(asIScriptEngine* engine)
{
    registerGeometryNode<Skybox>(engine, "Skybox");
    engine->RegisterObjectMethod("Skybox", "void setModel(Model@+)", asMETHOD(Skybox, setModel), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void setMaterial(Material@+)", asMETHODPR(Skybox, setMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "bool setMaterial(uint, Material@+)", asMETHODPR(Skybox, setMaterial, (unsigned, Material*), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "const BoundingBox& getBoundingBox() const", asMETHOD(Skybox, getBoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "uint getNumGeometries() const", asMETHOD(Skybox, getNumGeometries), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "Material@+ getMaterial(uint) const", asMETHOD(Skybox, getMaterial), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "Model@+ getModel() const", asMETHOD(Skybox, getModel), asCALL_THISCALL);
    registerRefCasts<Component, Skybox>(engine, "Component", "Skybox");
    registerRefCasts<Node, Skybox>(engine, "Node", "Skybox");
}

static void registerAnimatedModel(asIScriptEngine* engine)
{
    engine->RegisterObjectType("AnimationState", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("AnimationState", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("AnimationState", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("AnimationState", "void setStartBone(Bone@+)", asMETHOD(AnimationState, setStartBone), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void setLooped(bool)", asMETHOD(AnimationState, setLooped), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void setWeight(float)", asMETHOD(AnimationState, setWeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void setTime(float)", asMETHOD(AnimationState, setTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void addWeight(float)", asMETHOD(AnimationState, addWeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void addTime(float)", asMETHOD(AnimationState, addTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void setPriority(int)", asMETHOD(AnimationState, setPriority), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void setUseNlerp(bool)", asMETHOD(AnimationState, setUseNlerp), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "Animation@+ getAnimation() const", asMETHOD(AnimationState, getAnimation), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "Bone@+ getStartBone() const", asMETHOD(AnimationState, getStartBone), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "bool isEnabled() const", asMETHOD(AnimationState, isEnabled), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "bool isLooped() const", asMETHOD(AnimationState, isLooped), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "float getWeight() const", asMETHOD(AnimationState, getWeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "float getTime() const", asMETHOD(AnimationState, getTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "float getLength() const", asMETHOD(AnimationState, getLength), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "int getPriority() const", asMETHOD(AnimationState, getPriority), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "bool getUseNlerp() const", asMETHOD(AnimationState, getUseNlerp), asCALL_THISCALL);
    
    registerGeometryNode<AnimatedModel>(engine, "AnimatedModel");
    engine->RegisterObjectMethod("AnimatedModel", "void setModel(Model@+)", asMETHOD(AnimatedModel, setModel), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void setMaterial(Material@+)", asMETHODPR(AnimatedModel, setMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool setMaterial(uint, Material@+)", asMETHODPR(AnimatedModel, setMaterial, (unsigned, Material*), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "const BoundingBox& getBoundingBox() const", asMETHOD(AnimatedModel, getBoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint getNumGeometries() const", asMETHOD(AnimatedModel, getNumGeometries), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "Material@+ getMaterial(uint) const", asMETHOD(AnimatedModel, getMaterial), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "Model@+ getModel() const", asMETHOD(AnimatedModel, getModel), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "AnimationState@+ addAnimationState(Animation@+)", asMETHOD(AnimatedModel, addAnimationState), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void removeAnimationState(Animation@+)", asMETHODPR(AnimatedModel, removeAnimationState, (Animation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void removeAnimationState(const string& in)", asMETHODPR(AnimatedModel, removeAnimationState, (const std::string&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void removeAnimationState(AnimationState@+)", asMETHODPR(AnimatedModel, removeAnimationState, (AnimationState*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void removeAllAnimationStates()", asMETHOD(AnimatedModel, removeAllAnimationStates), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void setAnimationLodBias(float)", asMETHOD(AnimatedModel, setAnimationLodBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void setInvisibleLodFactor(float)", asMETHOD(AnimatedModel, setInvisibleLodFactor), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void setLocalAnimation(bool)", asMETHOD(AnimatedModel, setLocalAnimation), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void setMorphWeight(uint, float)", asMETHODPR(AnimatedModel, setMorphWeight, (unsigned, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void setMorphWeight(const string& in, float)", asMETHODPR(AnimatedModel, setMorphWeight, (const std::string&, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void resetMorphWeights()", asMETHOD(AnimatedModel, resetMorphWeights), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void syncAnimation(AnimatedModel@+)", asMETHOD(AnimatedModel, syncAnimation), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void syncMorphs(AnimatedModel@+)", asMETHOD(AnimatedModel, syncMorphs), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "Skeleton@+ getSkeleton() const", asMETHOD(AnimatedModel, getSkeleton), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint getNumAnimationStates() const", asMETHOD(AnimatedModel, getNumAnimationStates), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "AnimationState@+ getAnimationState(Animation@+) const", asMETHODPR(AnimatedModel, getAnimationState, (Animation*) const, AnimationState*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "AnimationState@+ getAnimationState(const string& in) const", asMETHODPR(AnimatedModel, getAnimationState, (const std::string&) const, AnimationState*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "AnimationState@+ getAnimationState(uint) const", asMETHODPR(AnimatedModel, getAnimationState, (unsigned) const, AnimationState*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "float getAnimationLodBias() const", asMETHOD(AnimatedModel, getAnimationLodBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "float getInvisibleLodFactor() const", asMETHOD(AnimatedModel, getInvisibleLodFactor), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool getLocalAnimation() const", asMETHOD(AnimatedModel, getLocalAnimation), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint getNumMorphs() const", asMETHOD(AnimatedModel, getNumMorphs), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "float getMorphWeight(uint) const", asMETHODPR(AnimatedModel, getMorphWeight, (unsigned) const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "float getMorphWeight(const string& in) const", asMETHODPR(AnimatedModel, getMorphWeight, (const std::string&) const, float), asCALL_THISCALL);
    registerRefCasts<Component, AnimatedModel>(engine, "Component", "AnimatedModel");
    registerRefCasts<Node, AnimatedModel>(engine, "Node", "AnimatedModel");
}

static void registerBillboardSet(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Billboard", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("Billboard", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Billboard", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("Billboard", "Vector3 position", offsetof(Billboard, mPosition));
    engine->RegisterObjectProperty("Billboard", "Vector2 size", offsetof(Billboard, mSize));
    engine->RegisterObjectProperty("Billboard", "Rect uv", offsetof(Billboard, mUV));
    engine->RegisterObjectProperty("Billboard", "Color color", offsetof(Billboard, mColor));
    engine->RegisterObjectProperty("Billboard", "float rotation", offsetof(Billboard, mRotation));
    engine->RegisterObjectProperty("Billboard", "bool enabled", offsetof(Billboard, mEnabled));
    
    registerGeometryNode<BillboardSet>(engine, "BillboardSet");
    engine->RegisterObjectMethod("BillboardSet", "void setMaterial(Material@+)", asMETHOD(BillboardSet, setMaterial), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void setNumBillboards(uint)", asMETHOD(BillboardSet, setNumBillboards), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void setBillboardsRelative(bool)", asMETHOD(BillboardSet, setBillboardsRelative), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void setBillboardsSorted(bool)", asMETHOD(BillboardSet, setBillboardsSorted), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void setScaleBillboards(bool)", asMETHOD(BillboardSet, setScaleBillboards), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void setAnimationLodBias(float)", asMETHOD(BillboardSet, setAnimationLodBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void updated()", asMETHOD(BillboardSet, updated), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "Material@+ getMaterial() const", asMETHOD(BillboardSet, getMaterial), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "uint getNumBillboards() const", asMETHOD(BillboardSet, getNumBillboards), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "Billboard@+ getBillboard(uint)", asMETHOD(BillboardSet, getBillboard), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool getBillboardsRelative() const", asMETHOD(BillboardSet, getBillboardsRelative), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool getBillboardsSorted() const", asMETHOD(BillboardSet, getBillboardsSorted), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool getScaleBillboards() const", asMETHOD(BillboardSet, getScaleBillboards), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "float getAnimationLodBias() const", asMETHOD(BillboardSet, getAnimationLodBias), asCALL_THISCALL);
    registerRefCasts<Component, BillboardSet>(engine, "Component", "BillboardSet");
    registerRefCasts<Node, BillboardSet>(engine, "Node", "BillboardSet");
}

static void registerInstancedModel(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Instance", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("Instance", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Instance", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("Instance", "Vector3 position", offsetof(Instance, mPosition));
    engine->RegisterObjectProperty("Instance", "Quaternion rotation", offsetof(Instance, mRotation));
    engine->RegisterObjectProperty("Instance", "Vector3 scale", offsetof(Instance, mScale));
    
    registerGeometryNode<InstancedModel>(engine, "InstancedModel");
    engine->RegisterObjectMethod("InstancedModel", "void setModel(Model@+)", asMETHOD(InstancedModel, setModel), asCALL_THISCALL);
    engine->RegisterObjectMethod("InstancedModel", "void setMaterial(Material@+)", asMETHODPR(InstancedModel, setMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("InstancedModel", "bool setMaterial(uint, Material@+)", asMETHODPR(InstancedModel, setMaterial, (unsigned, Material*), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("InstancedModel", "void setNumInstances(uint)", asMETHOD(InstancedModel, setNumInstances), asCALL_THISCALL);
    engine->RegisterObjectMethod("InstancedModel", "void setInstancesRelative(bool)", asMETHOD(InstancedModel, setInstancesRelative), asCALL_THISCALL);
    engine->RegisterObjectMethod("InstancedModel", "void updated()", asMETHOD(InstancedModel, updated), asCALL_THISCALL);
    engine->RegisterObjectMethod("InstancedModel", "const BoundingBox& getBoundingBox() const", asMETHOD(InstancedModel, getBoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("InstancedModel", "uint getNumGeometries() const", asMETHOD(InstancedModel, getNumGeometries), asCALL_THISCALL);
    engine->RegisterObjectMethod("InstancedModel", "Material@+ getMaterial(uint) const", asMETHOD(InstancedModel, getMaterial), asCALL_THISCALL);
    engine->RegisterObjectMethod("InstancedModel", "Model@+ getModel() const", asMETHOD(InstancedModel, getModel), asCALL_THISCALL);
    engine->RegisterObjectMethod("InstancedModel", "Instance@+ getInstance(uint)", asMETHOD(InstancedModel, getInstance), asCALL_THISCALL);
    engine->RegisterObjectMethod("InstancedModel", "bool getInstancesRelative() const", asMETHOD(InstancedModel, getInstancesRelative), asCALL_THISCALL);
    registerRefCasts<Component, InstancedModel>(engine, "Component", "InstancedModel");
    registerRefCasts<Node, InstancedModel>(engine, "Node", "InstancedModel");
}

static Renderer* GetRenderer()
{
    return getEngine()->getRenderer();
}

static void registerRenderer(asIScriptEngine* engine)
{
    engine->RegisterEnum("RenderMode");
    engine->RegisterEnumValue("RenderMode", "RENDER_DEFERRED", RENDER_DEFERRED);
    engine->RegisterEnumValue("RenderMode", "RENDER_PREPASS", RENDER_PREPASS);
    engine->RegisterEnumValue("RenderMode", "RENDER_FORWARD", RENDER_FORWARD);
    
    engine->RegisterObjectType("Renderer", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("Renderer", asBEHAVE_ADDREF, "void f()", asMETHOD(Renderer, addRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("Renderer", asBEHAVE_RELEASE, "void f()", asMETHOD(Renderer, releaseRef), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void setMode(RenderMode, int, int, bool, bool, int)", asMETHOD(Renderer, setMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void toggleFullscreen()", asMETHOD(Renderer, toggleFullscreen), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void close()", asMETHOD(Renderer, close), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool takeScreenShot(Image@+)", asMETHOD(Renderer, takeScreenShot), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void setForceSM2(bool)", asMETHOD(Renderer, setForceSM2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "const string& getWindowTitle() const", asMETHOD(Renderer, getWindowTitle), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "RenderMode getRenderMode() const", asMETHOD(Renderer, getRenderMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int getWidth() const", asMETHOD(Renderer, getWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int getHeight() const", asMETHOD(Renderer, getHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int getMultiSample() const", asMETHOD(Renderer, getMultiSample), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool getFullscreen() const", asMETHOD(Renderer, getFullscreen), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool getVsync() const", asMETHOD(Renderer, getVsync), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool isClosed() const", asMETHOD(Renderer, isClosed), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool isDeviceLost() const", asMETHOD(Renderer, isDeviceLost), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint getNumPrimitives() const", asMETHOD(Renderer, getNumPrimitives), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint getNumBatches() const", asMETHOD(Renderer, getNumBatches), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool getDeferredSupport() const", asMETHOD(Renderer, getDeferredSupport), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool getPrepassSupport() const", asMETHOD(Renderer, getPrepassSupport), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool getSM3Support() const", asMETHOD(Renderer, getSM3Support), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool getHardwareDepthSupport() const", asMETHOD(Renderer, getHardwareDepthSupport), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool getHardwareShadowSupport() const", asMETHOD(Renderer, getHardwareShadowSupport), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool getHiresShadowSupport() const", asMETHOD(Renderer, getHiresShadowSupport), asCALL_THISCALL);
    
    engine->RegisterGlobalFunction("Renderer@+ getRenderer()", asFUNCTION(GetRenderer), asCALL_CDECL);
    engine->RegisterGlobalFunction("Renderer@+ get_renderer()", asFUNCTION(GetRenderer), asCALL_CDECL);
}

static void ConstructEdgeFilterParameters(EdgeFilterParameters* ptr)
{
    new(ptr) EdgeFilterParameters(0.0f, 0.0f, 0.0f, 0.0f);
}

static void ConstructEdgeFilterParametersCopy(EdgeFilterParameters& parameters, EdgeFilterParameters* ptr)
{
    new(ptr) EdgeFilterParameters(parameters);
}

static void ConstructEdgeFilterParametersInit(float threshold, float filterStep, float maxFilter, float maxScale, EdgeFilterParameters* ptr)
{
    new(ptr) EdgeFilterParameters(threshold, filterStep, maxFilter, maxScale);
}

static Pipeline* GetPipeline()
{
    return getEngine()->getPipeline();
}

static void registerPipeline(asIScriptEngine* engine)
{
    engine->RegisterGlobalProperty("const int QUALITY_LOW", (void*)&QUALITY_LOW);
    engine->RegisterGlobalProperty("const int QUALITY_MEDIUM", (void*)&QUALITY_MEDIUM);
    engine->RegisterGlobalProperty("const int QUALITY_HIGH", (void*)&QUALITY_HIGH);
    
    engine->RegisterObjectType("EdgeFilterParameters", sizeof(EdgeFilterParameters), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C);
    engine->RegisterObjectBehaviour("EdgeFilterParameters", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructEdgeFilterParameters), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("EdgeFilterParameters", asBEHAVE_CONSTRUCT, "void f(const EdgeFilterParameters& in)", asFUNCTION(ConstructEdgeFilterParametersCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("EdgeFilterParameters", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(ConstructEdgeFilterParametersInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("EdgeFilterParameters", "float threshold", offsetof(EdgeFilterParameters, mThreshold));
    engine->RegisterObjectProperty("EdgeFilterParameters", "float filterStep", offsetof(EdgeFilterParameters, mFilterStep));
    engine->RegisterObjectProperty("EdgeFilterParameters", "float maxFilter", offsetof(EdgeFilterParameters, mMaxFilter));
    engine->RegisterObjectProperty("EdgeFilterParameters", "float maxScale", offsetof(EdgeFilterParameters, mMaxScale));
    
    engine->RegisterObjectType("Pipeline", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("Pipeline", asBEHAVE_ADDREF, "void f()", asMETHOD(Pipeline, addRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("Pipeline", asBEHAVE_RELEASE, "void f()", asMETHOD(Pipeline, releaseRef), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "void setNumViewports(uint)", asMETHOD(Pipeline, setNumViewports), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "void setViewport(uint, Scene@+, Camera@+, const IntRect& in)", asMETHOD(Pipeline, setViewport), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "void setViewportCamera(uint, Camera@+)", asMETHOD(Pipeline, setViewportCamera), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "void setViewportScreenRect(uint, Camera@+)", asMETHOD(Pipeline, setViewportScreenRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "void setSpecularLighting(bool)", asMETHOD(Pipeline, setSpecularLighting), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "void setDrawShadows(bool)", asMETHOD(Pipeline, setDrawShadows), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "void setTextureAnisotropy(int)", asMETHOD(Pipeline, setTextureAnisotropy), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "void setTextureFilterMode(TextureFilterMode)", asMETHOD(Pipeline, setTextureFilterMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "void setTextureQuality(int)", asMETHOD(Pipeline, setTextureQuality), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "void setMaterialQuality(int)", asMETHOD(Pipeline, setMaterialQuality), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "void setLightDetailLevel(int)", asMETHOD(Pipeline, setLightDetailLevel), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "void setShadowMapSize(int)", asMETHOD(Pipeline, setShadowMapSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "void setShadowMapHiresDepth(bool)", asMETHOD(Pipeline, setShadowMapHiresDepth), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "void setMaxOccluderTriangles(int)", asMETHOD(Pipeline, setMaxOccluderTriangles), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "void setOcclusionBufferSize(int)", asMETHOD(Pipeline, setOcclusionBufferSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "void setOccluderSizeThreshold(float)", asMETHOD(Pipeline, setOccluderSizeThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "void setEdgeFilter(const EdgeFilterParameters& in)", asMETHOD(Pipeline, setEdgeFilter), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "void drawDebugGeometry()", asMETHOD(Pipeline, drawDebugGeometry), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "uint getNumViewports() const", asMETHOD(Pipeline, getNumViewports), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "Scene@+ getViewportScene(uint) const", asMETHOD(Pipeline, getViewportScene), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "Camera@+ getViewportCamera(uint) const", asMETHOD(Pipeline, getViewportCamera), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "IntRect getViewportScreenRect(uint) const", asMETHOD(Pipeline, getViewportScreenRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "uint getFrameNumber() const", asMETHOD(Pipeline, getFrameNumber), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "float getElapsedTime() const", asMETHOD(Pipeline, getElapsedTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "bool getSpecularLighting() const", asMETHOD(Pipeline, getSpecularLighting), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "bool getDrawShadows() const", asMETHOD(Pipeline, getDrawShadows), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "int getTextureAnisotropy() const", asMETHOD(Pipeline, getTextureAnisotropy), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "TextureFilterMode getTextureFilterMode() const", asMETHOD(Pipeline, getTextureFilterMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "int getTextureQuality() const", asMETHOD(Pipeline, getTextureQuality), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "int getMaterialQuality() const", asMETHOD(Pipeline, getMaterialQuality), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "int getLightDetailLevel() const", asMETHOD(Pipeline, getLightDetailLevel), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "int getShadowMapSize() const", asMETHOD(Pipeline, getShadowMapSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "int getMaxOccluderTriangles() const", asMETHOD(Pipeline, getMaxOccluderTriangles), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "int getOcclusionBufferSize() const", asMETHOD(Pipeline, getOcclusionBufferSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "float getOccluderSizeThreshold() const", asMETHOD(Pipeline, getOccluderSizeThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "const EdgeFilterParameters& getEdgeFilter() const", asMETHOD(Pipeline, getEdgeFilter), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "uint getNumViews() const", asMETHOD(Pipeline, getNumViews), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "uint getNumGeometries(bool) const", asMETHOD(Pipeline, getNumGeometries), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "uint getNumLights(bool) const", asMETHOD(Pipeline, getNumLights), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "uint getNumShadowMaps(bool) const", asMETHOD(Pipeline, getNumShadowMaps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "uint getNumOccluders(bool) const", asMETHOD(Pipeline, getNumOccluders), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pipeline", "uint getNumShadowOccluders(bool) const", asMETHOD(Pipeline, getNumShadowOccluders), asCALL_THISCALL);
    
    engine->RegisterGlobalFunction("Pipeline@+ getPipeline()", asFUNCTION(GetPipeline), asCALL_CDECL);
    engine->RegisterGlobalFunction("Pipeline@+ get_pipeline()", asFUNCTION(GetPipeline), asCALL_CDECL);
}

static DebugRenderer* GetDebugRenderer()
{
    Scene* scene = getScriptContextScene();
    if (scene)
        return scene->getExtension<DebugRenderer>();
    else
        return 0;
}

static DebugRenderer* SceneGetDebugRenderer(Scene* ptr)
{
    return ptr->getExtension<DebugRenderer>();
}

static void registerDebugRenderer(asIScriptEngine* engine)
{
    engine->RegisterObjectType("DebugRenderer", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("DebugRenderer", asBEHAVE_ADDREF, "void f()", asMETHOD(DebugRenderer, addRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("DebugRenderer", asBEHAVE_RELEASE, "void f()", asMETHOD(DebugRenderer, releaseRef), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void addLine(const Vector3& in, const Vector3& in, const Color& in, bool)", asMETHOD(DebugRenderer, addLine), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void addBoundingBox(const BoundingBox& in, const Color& in, bool)", asMETHODPR(DebugRenderer, addBoundingBox, (const BoundingBox&, const Color&, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void addFrustum(const Frustum& in, const Color& in, bool)", asMETHOD(DebugRenderer, addFrustum), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void addSkeleton(Skeleton@+, const Color& in, bool)", asMETHOD(DebugRenderer, addSkeleton), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "DebugRenderer@+ getDebugRenderer() const", asFUNCTION(SceneGetDebugRenderer), asCALL_CDECL_OBJLAST);
    
    engine->RegisterGlobalFunction("DebugRenderer@+ getDebugRenderer()", asFUNCTION(GetDebugRenderer), asCALL_CDECL);
    engine->RegisterGlobalFunction("DebugRenderer@+ get_debugRenderer()", asFUNCTION(GetDebugRenderer), asCALL_CDECL);
}

static void ConstructRayQueryResult(RayQueryResult* ptr)
{
    new(ptr) RayQueryResult();
    // Zero the node pointer for safety when constructing these from script
    ptr->mNode = 0;
    ptr->mDistance = 0.0f;
}

static Node* RayQueryResultGetNode(RayQueryResult* ptr)
{
    return ptr->mNode;
}

static CScriptArray* OctreeRaycast(const Ray& ray, unsigned nodeFlags, float maxDistance, RayQueryLevel level, Octree* ptr)
{
    RayOctreeQuery query(rayQueryResult, ray, nodeFlags, false, false, maxDistance, level);
    ptr->getNodes(query);
    return vectorToArray<RayQueryResult>(rayQueryResult, "array<RayQueryResult>");
}

static CScriptArray* OctreeGetNodesPoint(const Vector3& point, unsigned nodeFlags, Octree* ptr)
{
    PointOctreeQuery query(nodeResult, point, nodeFlags);
    ptr->getNodes(query);
    return vectorToHandleArray<VolumeNode>(nodeResult, "array<Node@>");
}

static CScriptArray* OctreeGetNodesBox(const BoundingBox& box, unsigned nodeFlags, Octree* ptr)
{
    BoxOctreeQuery query(nodeResult, box, nodeFlags);
    ptr->getNodes(query);
    return vectorToHandleArray<VolumeNode>(nodeResult, "array<Node@>");
}

static CScriptArray* OctreeGetNodesFrustum(const Frustum& frustum, unsigned nodeFlags, Octree* ptr)
{
    FrustumOctreeQuery query(nodeResult, frustum, nodeFlags);
    ptr->getNodes(query);
    return vectorToHandleArray<VolumeNode>(nodeResult, "array<Node@>");
}

static CScriptArray* OctreeGetNodesSphere(const Sphere& sphere, unsigned nodeFlags, Octree* ptr)
{
    SphereOctreeQuery query(nodeResult, sphere, nodeFlags);
    ptr->getNodes(query);
    return vectorToHandleArray<VolumeNode>(nodeResult, "array<Node@>");
}

static Octree* SceneGetOctree(Scene* ptr)
{
    return ptr->getExtension<Octree>();
}

static bool SceneIsHeadless(Scene* ptr)
{
    Octree* octree = ptr->getExtension<Octree>();
    return octree ? octree->isHeadless() : true;
}

static Octree* GetOctree()
{
    Scene* scene = getScriptContextScene();
    return scene ? scene->getExtension<Octree>() : 0;
}

static void registerOctree(asIScriptEngine* engine)
{
    engine->RegisterEnum("RayQueryLevel");
    engine->RegisterEnumValue("RayQueryLevel", "RAY_AABB_NOSUBOBJECTS", RAY_AABB_NOSUBOBJECTS);
    engine->RegisterEnumValue("RayQueryLevel", "RAY_AABB", RAY_AABB_NOSUBOBJECTS);
    engine->RegisterEnumValue("RayQueryLevel", "RAY_OBB", RAY_OBB);
    engine->RegisterEnumValue("RayQueryLevel", "RAY_TRIANGLE", RAY_TRIANGLE);
    
    engine->RegisterObjectType("RayQueryResult", sizeof(RayQueryResult), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C);
    engine->RegisterObjectBehaviour("RayQueryResult", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructRayQueryResult), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("RayQueryResult", "Node@+ get_node() const", asFUNCTION(RayQueryResultGetNode), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("RayQueryResult", "float distance", offsetof(RayQueryResult, mDistance));
    engine->RegisterObjectProperty("RayQueryResult", "uint subObject", offsetof(RayQueryResult, mSubObject));
    
    registerHashedType<Octree>(engine, "Octree");
    engine->RegisterObjectMethod("Octree", "void resize(const BoundingBox& in, uint)", asMETHOD(Octree, resize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "void setExcludeFlags(uint)", asMETHOD(Octree, getExcludeFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "const BoundingBox& getWorldBoundingBox() const", asMETHODPR(Octree, getWorldBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "uint getNumLevels() const", asMETHOD(Octree, getNumLevels), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "uint getExcludeFlags() const", asMETHOD(Octree, getExcludeFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "bool isHeadless() const", asMETHOD(Octree, isHeadless), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "array<RayQueryResult>@ raycast(const Ray& in, uint, float, RayQueryLevel)", asFUNCTION(OctreeRaycast), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Octree", "array<Node@>@ getNodes(const Vector3& in, uint)", asFUNCTION(OctreeGetNodesPoint), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Octree", "array<Node@>@ getNodes(const BoundingBox& in, uint)", asFUNCTION(OctreeGetNodesBox), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Octree", "array<Node@>@ getNodes(const Frustum& in, uint)", asFUNCTION(OctreeGetNodesFrustum), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Octree", "array<Node@>@ getNodes(const Sphere& in, uint)", asFUNCTION(OctreeGetNodesSphere), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "Octree@+ getOctree() const", asFUNCTION(SceneGetOctree), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Scene", "bool isHeadless() const", asFUNCTION(SceneIsHeadless), asCALL_CDECL_OBJLAST);
    
    engine->RegisterGlobalFunction("Octree@+ getOctree()", asFUNCTION(GetOctree), asCALL_CDECL);
    engine->RegisterGlobalFunction("Octree@+ get_octree()", asFUNCTION(GetOctree), asCALL_CDECL);
}

void registerRendererLibrary(asIScriptEngine* engine)
{
    registerCamera(engine);
    registerSkeleton(engine);
    registerTexture(engine);
    registerMaterial(engine);
    registerModel(engine);
    registerAnimation(engine);
    registerVolumeNode(engine);
    registerGeometryNode(engine);
    registerLight(engine);
    registerZone(engine);
    registerStaticModel(engine);
    registerSkybox(engine);
    registerAnimatedModel(engine);
    registerBillboardSet(engine);
    registerInstancedModel(engine);
    registerRenderer(engine);
    registerPipeline(engine);
    registerDebugRenderer(engine);
    registerOctree(engine);
}
