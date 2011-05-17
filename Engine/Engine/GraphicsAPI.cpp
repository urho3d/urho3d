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
#include "AnimationController.h"
#include "AnimationState.h"
#include "APITemplates.h"
#include "Camera.h"
#include "DebugRenderer.h"
#include "Graphics.h"
#include "Light.h"
#include "Material.h"
#include "Octree.h"
#include "OctreeQuery.h"
#include "ParticleEmitter.h"
#include "Scene.h"
#include "Technique.h"
#include "Texture2D.h"
#include "TextureCube.h"
#include "Skybox.h"
#include "Zone.h"

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

static void RegisterCamera(asIScriptEngine* engine)
{
    RegisterComponent<Camera>(engine, "Camera");
    engine->RegisterObjectMethod("Camera", "void SetOrthoSize(const Vector2&in)", asMETHODPR(Camera, SetOrthoSize, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Frustum GetSplitFrustum(float, float)", asMETHOD(Camera, GetSplitFrustum), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Ray GetScreenRay(float, float)", asMETHOD(Camera, GetScreenRay), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float GetDistance(const Vector3&in)", asMETHOD(Camera, GetDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float GetDistanceSquared(const Vector3&in)", asMETHOD(Camera, GetDistanceSquared), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_nearClip(float)", asMETHOD(Camera, SetNearClip), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_nearClip() const", asMETHOD(Camera, GetNearClip), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_farClip(float)", asMETHOD(Camera, SetFarClip), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_farClip() const", asMETHOD(Camera, GetFarClip), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_fov(float)", asMETHOD(Camera, SetFov), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_fov() const", asMETHOD(Camera, SetFov), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_orthoSize(float)", asMETHODPR(Camera, SetOrthoSize, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_orthoSize() const", asMETHOD(Camera, GetOrthoSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_aspectRatio(float)", asMETHOD(Camera, SetAspectRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_aspectRatio() const", asMETHOD(Camera, GetAspectRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_zoom(float)", asMETHOD(Camera, SetZoom), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_zoom() const", asMETHOD(Camera, GetZoom), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_lodBias(float)", asMETHOD(Camera, SetLodBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_lodBias() const", asMETHOD(Camera, GetLodBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_orthographic(bool)", asMETHOD(Camera, SetOrthographic), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool get_orthographic() const", asMETHOD(Camera, IsOrthographic), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_autoAspectRatio(bool)", asMETHOD(Camera, SetAutoAspectRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool get_autoAspectRatio() const", asMETHOD(Camera, GetAutoAspectRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_viewMask(uint)", asMETHOD(Camera, SetViewMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "uint get_viewMask() const", asMETHOD(Camera, GetViewMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Frustum get_frustum()", asMETHOD(Camera, GetFrustum), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Frustum get_viewSpaceFrustum() const", asMETHOD(Camera, GetViewSpaceFrustum), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_halfViewSize() const", asMETHOD(Camera, GetHalfViewSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Vector3 get_forwardVector()", asMETHOD(Camera, GetForwardVector), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Vector3 get_rightVector()", asMETHOD(Camera, GetRightVector), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Vector3 get_upVector()", asMETHOD(Camera, GetUpVector), asCALL_THISCALL);
}

static Node* BoneGetNode(Bone* ptr)
{
    return ptr->node_;
}

static void RegisterSkeleton(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Bone", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("Bone", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Bone", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("Bone", "const String name", offsetof(Bone, name_));
    engine->RegisterObjectProperty("Bone", "const Vector3 initialPosition", offsetof(Bone, initialPosition_));
    engine->RegisterObjectProperty("Bone", "const Quaternion initialRotation", offsetof(Bone, initialRotation_));
    engine->RegisterObjectProperty("Bone", "const Vector3 initialScale", offsetof(Bone, initialScale_));
    engine->RegisterObjectProperty("Bone", "bool animated", offsetof(Bone, animated_));
    engine->RegisterObjectProperty("Bone", "float radius", offsetof(Bone, radius_));
    engine->RegisterObjectProperty("Bone", "const BoundingBox boundingBox", offsetof(Bone, boundingBox_));
    engine->RegisterObjectMethod("Bone", "Node@+ get_node()", asFUNCTION(BoneGetNode), asCALL_CDECL_OBJLAST);
    
    engine->RegisterObjectType("Skeleton", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("Skeleton", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Skeleton", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Skeleton", "void Reset()", asMETHOD(Skeleton, Reset), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skeleton", "Bone@+ GetBone(const String&in) const", asMETHODPR(Skeleton, GetBone, (const String&), Bone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skeleton", "Bone@+ get_rootBone() const", asMETHOD(Skeleton, GetRootBone), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skeleton", "uint get_numBones() const", asMETHOD(Skeleton, GetNumBones), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skeleton", "Bone@+ get_bones(uint)", asMETHODPR(Skeleton, GetBone, (unsigned), Bone*), asCALL_THISCALL);
}

static void ConstructViewport(Viewport* ptr)
{
    new(ptr) Viewport();
}

static void ConstructViewportCopy(const Viewport& viewport, Viewport* ptr)
{
    new(ptr) Viewport(viewport);
}

static void ConstructViewportSceneCamera(Scene* scene, Camera* camera, Viewport* ptr)
{
    new(ptr) Viewport(scene, camera);
}

static void ConstructViewportSceneCameraRect(Scene* scene, Camera* camera, const IntRect& rect, Viewport* ptr)
{
    new(ptr) Viewport(scene, camera, rect);
}

static void DestructViewport(Viewport* ptr)
{
    ptr->~Viewport();
}

static void ViewportSetScene(Scene* scene, Viewport* ptr)
{
    ptr->scene_ = scene;
}

static void ViewportSetCamera(Camera* camera, Viewport* ptr)
{
    ptr->camera_ = camera;
}

static Scene* ViewportGetScene(Viewport* ptr)
{
    return ptr->scene_;
}

static Camera* ViewportGetCamera(Viewport* ptr)
{
    return ptr->camera_;
}

static bool Texture2DLoad(Image* image, Texture2D* ptr)
{
    return ptr->Load(SharedPtr<Image>(image));
}

static bool TextureCubeLoad(CubeMapFace face, Image* image, TextureCube* ptr)
{
    return ptr->Load(face, SharedPtr<Image>(image));
}

static void RegisterTextures(asIScriptEngine* engine)
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
    
    RegisterTexture<Texture>(engine, "Texture");
    
    engine->RegisterObjectType("Viewport", sizeof(Viewport), asOBJ_VALUE | asOBJ_APP_CLASS_CDA);
    engine->RegisterObjectBehaviour("Viewport", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructViewport), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Viewport", asBEHAVE_CONSTRUCT, "void f(const Viewport&in)", asFUNCTION(ConstructViewportCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Viewport", asBEHAVE_CONSTRUCT, "void f(Scene@+, Camera@+)", asFUNCTION(ConstructViewportSceneCamera), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Viewport", asBEHAVE_CONSTRUCT, "void f(Scene@+, Camera@+, const IntRect&in)", asFUNCTION(ConstructViewportSceneCameraRect), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Viewport", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructViewport), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Viewport", "Viewport &opAssign(const Viewport&in)", asMETHOD(Viewport, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "void set_scene(Scene@+)", asFUNCTION(ViewportSetScene), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Viewport", "void set_camera(Camera@+)", asFUNCTION(ViewportSetCamera), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Viewport", "Scene@+ get_scene() const", asFUNCTION(ViewportGetScene), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Viewport", "Camera@+ get_camera() const", asFUNCTION(ViewportGetCamera), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("Viewport", "IntRect rect", offsetof(Viewport, rect_));
    
    engine->RegisterObjectType("RenderSurface", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("RenderSurface", asBEHAVE_ADDREF, "void f()", asMETHOD(RenderSurface, AddRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("RenderSurface", asBEHAVE_RELEASE, "void f()", asMETHOD(RenderSurface, ReleaseRef), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "Texture@+ get_parentTexture() const", asMETHOD(RenderSurface, GetParentTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "int get_width() const", asMETHOD(RenderSurface, GetWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "int get_height() const", asMETHOD(RenderSurface, GetHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "TextureUsage get_usage() const", asMETHOD(RenderSurface, GetUsage), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "void set_viewport(const Viewport&in)", asMETHOD(RenderSurface, SetViewport), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "const Viewport& get_viewport() const", asMETHOD(RenderSurface, GetViewport), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "void set_linkedRenderTarget(RenderSurface@+)", asMETHOD(RenderSurface, SetLinkedRenderTarget), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "RenderSurface@+ get_linkedRenderTarget() const", asMETHOD(RenderSurface, GetLinkedRenderTarget), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "void set_linkedDepthBuffer(RenderSurface@+)", asMETHOD(RenderSurface, SetLinkedDepthBuffer), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "RenderSurface@+ get_linkedDepthBuffer() const", asMETHOD(RenderSurface, GetLinkedDepthBuffer), asCALL_THISCALL);
    
    RegisterTexture<Texture2D>(engine, "Texture2D");
    engine->RegisterObjectMethod("Texture2D", "void SetSize(int, int, uint, TextureUsage)", asMETHOD(Texture2D, SetSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "bool Load(Image@+)", asFUNCTION(Texture2DLoad), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Texture2D", "RenderSurface@+ get_renderSurface() const", asMETHOD(Texture2D, GetRenderSurface), asCALL_THISCALL);
    
    RegisterTexture<TextureCube>(engine, "TextureCube");
    engine->RegisterObjectMethod("TextureCube", "void SetSize(int, uint, TextureUsage)", asMETHOD(TextureCube, SetSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "bool Load(CubeMapFace, Image@+)", asFUNCTION(TextureCubeLoad), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("TextureCube", "RenderSurface@+ get_renderSurface(CubeMapFace) const", asMETHOD(TextureCube, GetRenderSurface), asCALL_THISCALL);
}

static Vector4 MaterialGetVertexShaderParameter(VSParameter parameter, Material* ptr)
{
    const Map<VSParameter, Vector4>& parameters = ptr->GetVertexShaderParameters();
    Map<VSParameter, Vector4>::ConstIterator i = parameters.Find(parameter);
    if (i == parameters.End())
        return Vector4::ZERO;
    else
        return i->second_;
}

static Vector4 MaterialGetPixelShaderParameter(PSParameter parameter, Material* ptr)
{
    const Map<PSParameter, Vector4>& parameters = ptr->GetPixelShaderParameters();
    Map<PSParameter, Vector4>::ConstIterator i = parameters.Find(parameter);
    if (i == parameters.End())
        return Vector4::ZERO;
    else
        return i->second_;
}

static Material* MaterialClone(const String& cloneName, Material* ptr)
{
    SharedPtr<Material> clonedMaterial = ptr->Clone(cloneName);
    // The shared pointer will go out of scope, so have to increment the reference count
    // (here an auto handle can not be used)
    clonedMaterial->AddRef();
    return clonedMaterial.GetPtr();
}

static void RegisterMaterial(asIScriptEngine* engine)
{
    engine->RegisterEnum("VSParameter");
    engine->RegisterEnumValue("VSParameter", "VSP_UOFFSET", VSP_UOFFSET);
    engine->RegisterEnumValue("VSParameter", "VSP_VOFFSET", VSP_VOFFSET);
    
    engine->RegisterEnum("PSParameter");
    engine->RegisterEnumValue("PSParameter", "PSP_MATDIFFCOLOR", PSP_MATDIFFCOLOR);
    engine->RegisterEnumValue("PSParameter", "PSP_MATEMISSIVECOLOR", PSP_MATEMISSIVECOLOR);
    engine->RegisterEnumValue("PSParameter", "PSP_MATSPECPROPERTIES", PSP_MATSPECPROPERTIES);
    
    engine->RegisterEnum("TextureUnit");
    engine->RegisterEnumValue("TextureUnit", "TU_DIFFUSE", TU_DIFFUSE);
    engine->RegisterEnumValue("TextureUnit", "TU_NORMAL", TU_NORMAL);
    engine->RegisterEnumValue("TextureUnit", "TU_SPECULAR", TU_SPECULAR);
    engine->RegisterEnumValue("TextureUnit", "TU_DETAIL", TU_DETAIL);
    engine->RegisterEnumValue("TextureUnit", "TU_ENVIRONMENT", TU_ENVIRONMENT);
    engine->RegisterEnumValue("TextureUnit", "TU_EMISSIVE", TU_EMISSIVE);
    engine->RegisterEnumValue("TextureUnit", "MAX_MATERIAL_TEXTURE_UNITS", MAX_MATERIAL_TEXTURE_UNITS);
    
    engine->RegisterEnum("PassType");
    engine->RegisterEnumValue("PassType", "PASS_DEFERRED", PASS_DEFERRED);
    engine->RegisterEnumValue("PassType", "PASS_PREPASS", PASS_PREPASS);
    engine->RegisterEnumValue("PassType", "PASS_MATERIAL", PASS_MATERIAL);
    engine->RegisterEnumValue("PassType", "PASS_BASE", PASS_BASE);
    engine->RegisterEnumValue("PassType", "PASS_LITBASE", PASS_LITBASE);
    engine->RegisterEnumValue("PassType", "PASS_LIGHT", PASS_LIGHT);
    engine->RegisterEnumValue("PassType", "PASS_EXTRA", PASS_EXTRA);
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
    
    engine->RegisterObjectType("Pass", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("Pass", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Pass", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Pass", "void set_alphaMask(bool)", asMETHOD(Pass, SetAlphaMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "bool get_alphaMask() const", asMETHOD(Pass, GetAlphaMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_alphaTest(bool)", asMETHOD(Pass, SetAlphaTest), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "bool get_alphaTest() const", asMETHOD(Pass, GetAlphaTest), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_blendMode(BlendMode)", asMETHOD(Pass, SetBlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "BlendMode get_blendMode() const", asMETHOD(Pass, GetBlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_depthTestMode(CompareMode)", asMETHOD(Pass, SetDepthTestMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "CompareMode get_depthTestMode() const", asMETHOD(Pass, GetDepthTestMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_depthWrite(bool)", asMETHOD(Pass, SetDepthWrite), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "bool get_depthWrite() const", asMETHOD(Pass, GetDepthWrite), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_vertexShader(const String&in)", asMETHOD(Pass, SetVertexShader), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "const String& get_vertexShader() const", asMETHOD(Pass, GetVertexShaderName), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_pixelShader(const String&in)", asMETHOD(Pass, SetPixelShader), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "const String& get_pixelShader() const", asMETHOD(Pass, GetPixelShaderName), asCALL_THISCALL);
    
    RegisterResource<Technique>(engine, "Technique");
    engine->RegisterObjectMethod("Technique", "Pass@+ CreatePass(PassType)", asMETHOD(Technique, CreatePass), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "void RemovePass(PassType)", asMETHOD(Technique, RemovePass), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "bool HasPass(PassType) const", asMETHOD(Technique, HasPass), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "void set_sm3(bool)", asMETHOD(Technique, SetIsSM3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "bool get_sm3() const", asMETHOD(Technique, IsSM3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "Pass@+ get_pass(PassType)", asMETHOD(Technique, GetPass), asCALL_THISCALL);
    
    RegisterResource<Material>(engine, "Material");
    engine->RegisterObjectMethod("Material", "void SetUVTransform(const Vector2&in, float, const Vector2&in)", asMETHODPR(Material, SetUVTransform, (const Vector2&, float, const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void SetUVTransform(const Vector2&in, float, float)", asMETHODPR(Material, SetUVTransform, (const Vector2&, float, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "Material@ Clone(const String&in) const", asFUNCTION(MaterialClone), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Material", "void set_numTechniques(uint)", asMETHOD(Material, SetNumTechniques), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "uint get_numTechniques() const", asMETHOD(Material, GetNumTechniques), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "Technique@+ get_technique(uint)", asMETHOD(Material, GetTechnique), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_vertexShaderParameter(VSParameter, const Vector4&in)", asMETHOD(Material, SetVertexShaderParameter), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "Vector4 get_vertexShaderParameter(VSParameter) const", asFUNCTION(MaterialGetVertexShaderParameter), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Material", "void set_pixelShaderParameter(PSParameter, const Vector4&in)", asMETHOD(Material, SetPixelShaderParameter), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "Vector4 get_pixelShaderParameter(VSParameter) const", asFUNCTION(MaterialGetPixelShaderParameter), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Material", "void set_texture(TextureUnit, Texture@+)", asMETHOD(Material, SetTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "Texture@+ get_texture(TextureUnit) const", asMETHOD(Material, GetTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "bool get_occlusion()", asMETHOD(Material, GetOcclusion), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_cullMode(CullMode)", asMETHOD(Material, SetCullMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "CullMode get_cullMode() const", asMETHOD(Material, GetCullMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_shadowCullMode(CullMode)", asMETHOD(Material, SetShadowCullMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "CullMode get_shadowCullMode() const", asMETHOD(Material, GetShadowCullMode), asCALL_THISCALL);
}

static void RegisterModel(asIScriptEngine* engine)
{
    RegisterResource<Model>(engine, "Model");
    engine->RegisterObjectMethod("Model", "const BoundingBox& get_boundingBox() const", asMETHOD(Model, GetBoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "Skeleton@+ get_skeleton()", asMETHOD(Model, GetSkeleton), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "uint get_numGeometries() const", asMETHOD(Model, GetNumGeometries), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "uint get_numGeometryLodLevels(uint) const", asMETHOD(Model, GetNumGeometryLodLevels), asCALL_THISCALL);
    engine->RegisterObjectMethod("Model", "uint get_numMorphs() const", asMETHOD(Model, GetNumMorphs), asCALL_THISCALL);
}

static void RegisterAnimation(asIScriptEngine* engine)
{
    RegisterResource<Animation>(engine, "Animation");
    engine->RegisterObjectMethod("Animation", "const String& get_animationName() const", asMETHOD(Animation, GetAnimationName), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "float get_length() const", asMETHOD(Animation, GetLength), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "uint get_numTracks() const", asMETHOD(Animation, GetNumTracks), asCALL_THISCALL);
}

static void RegisterDrawable(asIScriptEngine* engine)
{
    engine->RegisterGlobalProperty("uint DRAWABLE_GEOMETRY", (void*)&DRAWABLE_GEOMETRY);
    engine->RegisterGlobalProperty("uint DRAWABLE_LIGHT", (void*)&DRAWABLE_LIGHT);
    engine->RegisterGlobalProperty("uint DRAWABLE_ZONE", (void*)&DRAWABLE_ZONE);
    engine->RegisterGlobalProperty("uint DEFAULT_VIEWMASK", (void*)&DEFAULT_VIEWMASK);
    engine->RegisterGlobalProperty("uint DEFAULT_LIGHTMASK", (void*)&DEFAULT_LIGHTMASK);
    
    RegisterDrawable<Drawable>(engine, "Drawable");
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

static void RegisterLight(asIScriptEngine* engine)
{
    engine->RegisterEnum("LightType");
    engine->RegisterEnumValue("LightType", "LIGHT_DIRECTIONAL", LIGHT_DIRECTIONAL);
    engine->RegisterEnumValue("LightType", "LIGHT_SPOT", LIGHT_SPOT);
    engine->RegisterEnumValue("LightType", "LIGHT_POINT", LIGHT_POINT);
    
    engine->RegisterObjectType("BiasParameters", sizeof(BiasParameters), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C);
    engine->RegisterObjectBehaviour("BiasParameters", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructBiasParameters), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("BiasParameters", asBEHAVE_CONSTRUCT, "void f(const BiasParameters&in)", asFUNCTION(ConstructBiasParametersCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("BiasParameters", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(ConstructBiasParametersInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("BiasParameters", "float constantBias", offsetof(BiasParameters, constantBias_));
    engine->RegisterObjectProperty("BiasParameters", "float slopeScaledBias", offsetof(BiasParameters, slopeScaledBias_));
    
    engine->RegisterObjectType("CascadeParameters", sizeof(CascadeParameters), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C);
    engine->RegisterObjectBehaviour("CascadeParameters", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructCascadeParameters), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("CascadeParameters", asBEHAVE_CONSTRUCT, "void f(const CascadeParameters&in)", asFUNCTION(ConstructCascadeParametersCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("CascadeParameters", asBEHAVE_CONSTRUCT, "void f(uint, float, float, float)", asFUNCTION(ConstructCascadeParametersInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("CascadeParameters", "uint splits", offsetof(CascadeParameters, splits_));
    engine->RegisterObjectProperty("CascadeParameters", "float lambda", offsetof(CascadeParameters, lambda_));
    engine->RegisterObjectProperty("CascadeParameters", "float splitFadeRange", offsetof(CascadeParameters, splitFadeRange_));
    engine->RegisterObjectProperty("CascadeParameters", "float shadowRange", offsetof(CascadeParameters, shadowRange_));
    
    engine->RegisterObjectType("FocusParameters", sizeof(FocusParameters), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C);
    engine->RegisterObjectBehaviour("FocusParameters", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructFocusParameters), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("FocusParameters", asBEHAVE_CONSTRUCT, "void f(const FocusParameters&in)", asFUNCTION(ConstructFocusParametersCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("FocusParameters", asBEHAVE_CONSTRUCT, "void f(bool, bool, bool, float, float)", asFUNCTION(ConstructFocusParametersInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("FocusParameters", "bool focus", offsetof(FocusParameters, focus_));
    engine->RegisterObjectProperty("FocusParameters", "bool nonUniform", offsetof(FocusParameters, nonUniform_));
    engine->RegisterObjectProperty("FocusParameters", "bool zoomOut", offsetof(FocusParameters, zoomOut_));
    engine->RegisterObjectProperty("FocusParameters", "float quantize", offsetof(FocusParameters, quantize_));
    engine->RegisterObjectProperty("FocusParameters", "float minView", offsetof(FocusParameters, minView_));
    
    RegisterDrawable<Light>(engine, "Light");
    engine->RegisterObjectMethod("Light", "void set_lightType(LightType)", asMETHOD(Light, SetLightType), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "LightType get_lightType() const", asMETHOD(Light, GetLightType), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_color(const Color&in)", asMETHOD(Light, SetColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const Color& get_color() const", asMETHOD(Light, GetColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_specularIntensity(float)", asMETHOD(Light, SetSpecularIntensity), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_specularIntensity() const", asMETHOD(Light, GetSpecularIntensity), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_range(float)", asMETHOD(Light, SetRange), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_range() const", asMETHOD(Light, GetRange), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_fov(float)", asMETHOD(Light, SetFov), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_fov() const", asMETHOD(Light, GetFov), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_aspectRatio(float)", asMETHOD(Light, SetAspectRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_aspectRatio() const", asMETHOD(Light, GetAspectRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_fadeDistance(float)", asMETHOD(Light, SetFadeDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_fadeDistance() const", asMETHOD(Light, GetFadeDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowBias(const BiasParameters&in)", asMETHOD(Light, SetShadowBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const BiasParameters& get_shadowBias() const", asMETHOD(Light, GetShadowBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowCascade(const CascadeParameters&in)", asMETHOD(Light, SetShadowCascade), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const CascadeParameters& get_shadowCascade() const", asMETHOD(Light, GetShadowCascade), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowFocus(const FocusParameters&in)", asMETHOD(Light, SetShadowFocus), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const FocusParameters& get_shadowFocus() const", asMETHOD(Light, GetShadowFocus), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowFadeDistance(float)", asMETHOD(Light, SetShadowFadeDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_shadowFadeDistance() const", asMETHOD(Light, GetShadowFadeDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowIntensity(float)", asMETHOD(Light, SetShadowIntensity), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_shadowIntensity() const", asMETHOD(Light, GetShadowIntensity), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowResolution(float)", asMETHOD(Light, SetShadowResolution), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_shadowResolution() const", asMETHOD(Light, GetShadowResolution), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowNearFarRatio(float)", asMETHOD(Light, SetShadowNearFarRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_shadowNearFarRatio() const", asMETHOD(Light, GetShadowNearFarRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_rampTexture(Texture@+)", asMETHOD(Light, SetRampTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "Texture@+ get_rampTexture() const", asMETHOD(Light, GetRampTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shapeTexture(Texture@+)", asMETHOD(Light, SetShapeTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "Texture@+ get_shapeTexture() const", asMETHOD(Light, GetShapeTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "Frustum get_frustum()", asMETHOD(Light, GetFrustum), asCALL_THISCALL);
}

static void RegisterZone(asIScriptEngine* engine)
{
    RegisterDrawable<Zone>(engine, "Zone");
    engine->RegisterObjectMethod("Zone", "void set_boundingBox(const BoundingBox&in)", asMETHOD(Zone, SetBoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const BoundingBox& get_boundingBox() const", asMETHOD(Zone, GetBoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_ambientColor(const Color&in)", asMETHOD(Zone, SetAmbientColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const Color& get_ambientColor() const", asMETHOD(Zone, GetAmbientColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_fogColor(const Color&in)", asMETHOD(Zone, SetFogColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const Color& get_fogColor() const", asMETHOD(Zone, GetFogColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_fogStart(float)", asMETHOD(Zone, SetFogStart), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "float get_fogStart() const", asMETHOD(Zone, GetFogStart), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_fogEnd(float)", asMETHOD(Zone, SetFogEnd), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "float get_fogEnd() const", asMETHOD(Zone, GetFogEnd), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_priority(int)", asMETHOD(Zone, SetPriority), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "int get_priority() const", asMETHOD(Zone, GetPriority), asCALL_THISCALL);
}

static void RegisterStaticModel(asIScriptEngine* engine)
{
    RegisterDrawable<StaticModel>(engine, "StaticModel");
    engine->RegisterObjectMethod("StaticModel", "void set_model(Model@+)", asMETHOD(StaticModel, SetModel), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "Model@+ get_model() const", asMETHOD(StaticModel, GetModel), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_material(Material@+)", asMETHODPR(StaticModel, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "bool set_materials(uint, Material@+)", asMETHODPR(StaticModel, SetMaterial, (unsigned, Material*), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "Material@+ get_materials(uint) const", asMETHOD(StaticModel, GetMaterial), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "const BoundingBox& get_boundingBox() const", asMETHOD(StaticModel, GetBoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "uint get_numGeometries() const", asMETHOD(StaticModel, GetNumGeometries), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_softwareLodLevel(uint) const", asMETHOD(StaticModel, SetSoftwareLodLevel), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "uint get_softwareLodLevel() const", asMETHOD(StaticModel, GetSoftwareLodLevel), asCALL_THISCALL);
}

static void RegisterSkybox(asIScriptEngine* engine)
{
    RegisterDrawable<StaticModel>(engine, "Skybox");
    engine->RegisterObjectMethod("Skybox", "void set_model(Model@+)", asMETHOD(Skybox, SetModel), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "Model@+ get_model() const", asMETHOD(Skybox, GetModel), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_material(Material@+)", asMETHODPR(Skybox, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "bool set_materials(uint, Material@+)", asMETHODPR(Skybox, SetMaterial, (unsigned, Material*), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "Material@+ get_materials(uint) const", asMETHOD(Skybox, GetMaterial), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "const BoundingBox& get_boundingBox() const", asMETHOD(Skybox, GetBoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "uint get_numGeometries() const", asMETHOD(Skybox, GetNumGeometries), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "void set_softwareLodLevel(uint) const", asMETHOD(Skybox, SetSoftwareLodLevel), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skybox", "uint get_softwareLodLevel() const", asMETHOD(Skybox, GetSoftwareLodLevel), asCALL_THISCALL);
}

static void AnimatedModelSetModel(Model* model, AnimatedModel* ptr)
{
    ptr->SetModel(model);
}

static void RegisterAnimatedModel(asIScriptEngine* engine)
{
    RegisterRefCounted<AnimationState>(engine, "AnimationState");
    engine->RegisterObjectMethod("AnimationState", "void AddWeight(float)", asMETHOD(AnimationState, AddWeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void AddTime(float)", asMETHOD(AnimationState, AddTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void set_startBone(Bone@+)", asMETHOD(AnimationState, SetStartBone), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "Bone@+ get_startBone() const", asMETHOD(AnimationState, GetStartBone), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void set_looped(bool)", asMETHOD(AnimationState, SetLooped), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "bool get_looped() const", asMETHOD(AnimationState, IsLooped), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void set_weight(float)", asMETHOD(AnimationState, SetWeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "float get_weight() const", asMETHOD(AnimationState, GetWeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void set_time(float)", asMETHOD(AnimationState, SetTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "float get_time() const", asMETHOD(AnimationState, GetTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void set_layer(int)", asMETHOD(AnimationState, SetLayer), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "int get_layer() const", asMETHOD(AnimationState, GetLayer), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void set_useNlerp(bool)", asMETHOD(AnimationState, SetUseNlerp), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "bool get_useNlerp() const", asMETHOD(AnimationState, GetUseNlerp), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "Animation@+ get_animation() const", asMETHOD(AnimationState, GetAnimation), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "bool get_enabled() const", asMETHOD(AnimationState, IsEnabled), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "float get_length() const", asMETHOD(AnimationState, GetLength), asCALL_THISCALL);
    
    RegisterDrawable<AnimatedModel>(engine, "AnimatedModel");
    engine->RegisterObjectMethod("AnimatedModel", "AnimationState@+ AddAnimationState(Animation@+)", asMETHOD(AnimatedModel, AddAnimationState), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void RemoveAnimationState(Animation@+)", asMETHODPR(AnimatedModel, RemoveAnimationState, (Animation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void RemoveAnimationState(const String&in)", asMETHODPR(AnimatedModel, RemoveAnimationState, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void RemoveAnimationState(AnimationState@+)", asMETHODPR(AnimatedModel, RemoveAnimationState, (AnimationState*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void RemoveAllAnimationStates()", asMETHOD(AnimatedModel, RemoveAllAnimationStates), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void SetMorphWeight(uint, float)", asMETHODPR(AnimatedModel, SetMorphWeight, (unsigned, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void ResetMorphWeights()", asMETHOD(AnimatedModel, ResetMorphWeights), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "float GetMorphWeight(uint) const", asMETHODPR(AnimatedModel, GetMorphWeight, (unsigned) const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "AnimationState@+ GetAnimationState(Animation@+) const", asMETHODPR(AnimatedModel, GetAnimationState, (Animation*) const, AnimationState*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "AnimationState@+ GetAnimationState(uint) const", asMETHODPR(AnimatedModel, GetAnimationState, (unsigned) const, AnimationState*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_model(Model@+)", asFUNCTION(AnimatedModelSetModel), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("AnimatedModel", "Model@+ get_model() const", asMETHOD(AnimatedModel, GetModel), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_material(Material@+)", asMETHODPR(AnimatedModel, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool set_materials(uint, Material@+)", asMETHODPR(AnimatedModel, SetMaterial, (unsigned, Material*), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "Material@+ get_materials(uint) const", asMETHOD(AnimatedModel, GetMaterial), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "const BoundingBox& get_boundingBox() const", asMETHOD(AnimatedModel, GetBoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_numGeometries() const", asMETHOD(AnimatedModel, GetNumGeometries), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_softwareLodLevel(uint) const", asMETHOD(AnimatedModel, SetSoftwareLodLevel), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_softwareLodLevel() const", asMETHOD(AnimatedModel, GetSoftwareLodLevel), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_animationLodBias(float)", asMETHOD(AnimatedModel, SetAnimationLodBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "float get_animationLodBias() const", asMETHOD(AnimatedModel, GetAnimationLodBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_invisibleLodFactor(float)", asMETHOD(AnimatedModel, SetInvisibleLodFactor), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "float get_invisibleLodFactor() const", asMETHOD(AnimatedModel, GetInvisibleLodFactor), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "Skeleton@+ get_skeleton()", asMETHOD(AnimatedModel, GetSkeleton), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_numAnimationStates() const", asMETHOD(AnimatedModel, GetNumAnimationStates), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "AnimationState@+ get_animationStates(const String&in) const", asMETHODPR(AnimatedModel, GetAnimationState, (const String&) const, AnimationState*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_numMorphs() const", asMETHOD(AnimatedModel, GetNumMorphs), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_morphWeight(const String&in, float)", asMETHODPR(AnimatedModel, SetMorphWeight, (const String&, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "float getMorphWeight(const String&in) const", asMETHODPR(AnimatedModel, GetMorphWeight, (const String&) const, float), asCALL_THISCALL);
}

static void RegisterAnimationController(asIScriptEngine* engine)
{
    RegisterComponent<AnimationController>(engine, "AnimationController");
    engine->RegisterObjectMethod("AnimationController", "bool Play(const String&in, int, bool, float fadeTime = 0.0f)", asMETHOD(AnimationController, Play), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool PlayExclusive(const String&in, int, bool, float fadeTime = 0.0f)", asMETHOD(AnimationController, PlayExclusive), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "void Stop(const String&in, float fadeTime = 0.0f)", asMETHOD(AnimationController, Stop), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "void StopLayer(int, float fadeTime = 0.0f)", asMETHOD(AnimationController, StopLayer), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "void StopAll(float fadeTime = 0.0f)", asMETHOD(AnimationController, StopAll), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool Fade(const String&in, float, float)", asMETHOD(AnimationController, Fade), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool FadeOthers(const String&in, float, float)", asMETHOD(AnimationController, FadeOthers), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool SetLayer(const String&in, int)", asMETHOD(AnimationController, SetLayer), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool SetStartBone(const String&in, const String&in)", asMETHOD(AnimationController, SetStartBone), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool SetTime(const String&in, float)", asMETHOD(AnimationController, SetTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool SetWeight(const String&in, float)", asMETHOD(AnimationController, SetWeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool SetLooped(const String&in, bool)", asMETHOD(AnimationController, SetLooped), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool SetSpeed(const String&in, float)", asMETHOD(AnimationController, SetSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool SetAutoFade(const String&in, float)", asMETHOD(AnimationController, SetAutoFade), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool IsPlaying(const String&in) const", asMETHOD(AnimationController, IsPlaying), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool IsFadingIn(const String&in) const", asMETHOD(AnimationController, IsFadingIn), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool IsFadingOut(const String&in) const", asMETHOD(AnimationController, IsFadingOut), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "int GetLayer(const String&in) const", asMETHOD(AnimationController, GetLayer), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "const String& GetStartBone(const String&in) const", asMETHOD(AnimationController, GetStartBoneName), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "float GetTime(const String&in) const", asMETHOD(AnimationController, GetTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "float GetWeight(const String&in) const", asMETHOD(AnimationController, GetWeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool GetLooped(const String&in) const", asMETHOD(AnimationController, IsLooped), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "float GetLength(const String&in) const", asMETHOD(AnimationController, GetLength), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "float GetSpeed(const String&in) const", asMETHOD(AnimationController, GetSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "float GetAutoFade(const String&in) const", asMETHOD(AnimationController, GetAutoFade), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "float GetFadeTarget(const String&in) const", asMETHOD(AnimationController, GetFadeTarget), asCALL_THISCALL);
}

static void RegisterBillboardSet(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Billboard", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("Billboard", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Billboard", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("Billboard", "Vector3 position", offsetof(Billboard, position_));
    engine->RegisterObjectProperty("Billboard", "Vector2 size", offsetof(Billboard, size_));
    engine->RegisterObjectProperty("Billboard", "Rect uv", offsetof(Billboard, uv_));
    engine->RegisterObjectProperty("Billboard", "Color color", offsetof(Billboard, color_));
    engine->RegisterObjectProperty("Billboard", "float rotation", offsetof(Billboard, rotation_));
    engine->RegisterObjectProperty("Billboard", "bool enabled", offsetof(Billboard, enabled_));
    
    RegisterDrawable<BillboardSet>(engine, "BillboardSet");
    engine->RegisterObjectMethod("BillboardSet", "void Updated()", asMETHOD(BillboardSet, Updated), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_material(Material@+)", asMETHOD(BillboardSet, SetMaterial), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "Material@+ get_material() const", asMETHOD(BillboardSet, SetMaterial), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_numBillboards(uint)", asMETHOD(BillboardSet, SetNumBillboards), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "uint get_numBillboards() const", asMETHOD(BillboardSet, GetNumBillboards), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_relative(bool)", asMETHOD(BillboardSet, SetRelative), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_relative() const", asMETHOD(BillboardSet, GetRelative), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_sorted(bool)", asMETHOD(BillboardSet, SetSorted), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_sorted() const", asMETHOD(BillboardSet, GetSorted), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_scaled(bool)", asMETHOD(BillboardSet, SetScaled), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_scaled() const", asMETHOD(BillboardSet, GetScaled), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_animationLodBias(float)", asMETHOD(BillboardSet, SetAnimationLodBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "float get_animationLodBias() const", asMETHOD(BillboardSet, GetAnimationLodBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "Billboard@+ get_billboards(uint)", asMETHOD(BillboardSet, GetBillboard), asCALL_THISCALL);
}

static void RegisterParticleEmitter(asIScriptEngine* engine)
{
    RegisterComponent<ParticleEmitter>(engine, "ParticleEmitter");
    engine->RegisterObjectMethod("ParticleEmitter", "void SetActive(bool, bool)", asMETHOD(ParticleEmitter, SetActive), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_material(Material@+)", asMETHOD(ParticleEmitter, SetMaterial), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "Material@+ get_material() const", asMETHOD(ParticleEmitter, SetMaterial), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_relative(bool)", asMETHOD(ParticleEmitter, SetRelative), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_relative() const", asMETHOD(ParticleEmitter, GetRelative), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_sorted(bool)", asMETHOD(ParticleEmitter, SetSorted), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_sorted() const", asMETHOD(ParticleEmitter, GetSorted), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_scaled(bool)", asMETHOD(ParticleEmitter, SetScaled), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_scaled() const", asMETHOD(ParticleEmitter, GetScaled), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_animationLodBias(float)", asMETHOD(ParticleEmitter, SetAnimationLodBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "float get_animationLodBias() const", asMETHOD(ParticleEmitter, GetAnimationLodBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool set_parameters(XMLFile@+ file)", asMETHOD(ParticleEmitter, LoadParameters), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "XMLFile@+ get_parameters() const", asMETHOD(ParticleEmitter, GetParameters), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_active() const", asMETHOD(ParticleEmitter, IsActive), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "uint get_numParticles() const", asMETHOD(ParticleEmitter, GetNumParticles), asCALL_THISCALL);
}


static CScriptArray* GraphicsGetResolutions(Graphics* ptr)
{
    return VectorToArray<IntVector2>(ptr->GetResolutions(), "Array<IntVector2>");
}

static CScriptArray* GraphicsGetMultiSampleLevels(Graphics* ptr)
{
    return VectorToArray<int>(ptr->GetMultiSampleLevels(), "Array<int>");
}

static Graphics* GetGraphics()
{
    return GetScriptContext()->GetSubsystem<Graphics>();
}

static void RegisterGraphics(asIScriptEngine* engine)
{
    engine->RegisterEnum("RenderMode");
    engine->RegisterEnumValue("RenderMode", "RENDER_DEFERRED", RENDER_DEFERRED);
    engine->RegisterEnumValue("RenderMode", "RENDER_PREPASS", RENDER_PREPASS);
    engine->RegisterEnumValue("RenderMode", "RENDER_FORWARD", RENDER_FORWARD);
    
    RegisterObject<Graphics>(engine, "Graphics");
    engine->RegisterObjectMethod("Graphics", "bool SetMode(RenderMode, int, int, bool, bool, int)", asMETHODPR(Graphics, SetMode, (RenderMode, int, int, bool, bool, int), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool SetMode(int, int)", asMETHODPR(Graphics, SetMode, (int, int), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool SetMode(RenderMode)", asMETHODPR(Graphics, SetMode, (RenderMode), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool ToggleFullscreen()", asMETHOD(Graphics, ToggleFullscreen), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "void Close()", asMETHOD(Graphics, Close), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool TakeScreenShot(Image@+)", asMETHOD(Graphics, TakeScreenShot), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "void set_flushGPU(bool)", asMETHOD(Graphics, SetFlushGPU), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_flushGPU() const", asMETHOD(Graphics, GetFlushGPU), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "void set_windowTitle(const String&in)", asMETHOD(Graphics, SetWindowTitle), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "const String& get_windowTitle() const", asMETHOD(Graphics, GetWindowTitle), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "RenderMode get_renderMode() const", asMETHOD(Graphics, GetRenderMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "int get_width() const", asMETHOD(Graphics, GetWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "int get_height() const", asMETHOD(Graphics, GetHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "int get_multiSample() const", asMETHOD(Graphics, GetMultiSample), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_fullscreen() const", asMETHOD(Graphics, GetFullscreen), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_vsync() const", asMETHOD(Graphics, GetVSync), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_initialized() const", asMETHOD(Graphics, IsInitialized), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_deviceLost() const", asMETHOD(Graphics, IsDeviceLost), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "uint get_numPrimitives() const", asMETHOD(Graphics, GetNumPrimitives), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "uint get_numBatches() const", asMETHOD(Graphics, GetNumBatches), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_deferredSupport() const", asMETHOD(Graphics, GetDeferredSupport), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_prepassSupport() const", asMETHOD(Graphics, GetPrepassSupport), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_sm3Support() const", asMETHOD(Graphics, GetSM3Support), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_hardwareShadowSupport() const", asMETHOD(Graphics, GetHardwareShadowSupport), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_hiresShadowSupport() const", asMETHOD(Graphics, GetHiresShadowSupport), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "Array<IntVector2>@ get_resolutions() const", asFUNCTION(GraphicsGetResolutions), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Graphics", "Array<int>@ get_multiSampleLevels() const", asFUNCTION(GraphicsGetMultiSampleLevels), asCALL_CDECL_OBJLAST);
    engine->RegisterGlobalFunction("Graphics@+ get_graphics()", asFUNCTION(GetGraphics), asCALL_CDECL);
}

static Renderer* GetRenderer()
{
    return GetScriptContext()->GetSubsystem<Renderer>();
}

static void RegisterRenderer(asIScriptEngine* engine)
{
    engine->RegisterGlobalProperty("const int QUALITY_LOW", (void*)&QUALITY_LOW);
    engine->RegisterGlobalProperty("const int QUALITY_MEDIUM", (void*)&QUALITY_MEDIUM);
    engine->RegisterGlobalProperty("const int QUALITY_HIGH", (void*)&QUALITY_HIGH);
    
    /// Set reuse of shadowmaps. Default is true, disabling allows transparent geometry shadowing
    void SetReuseShadowMaps(bool enable);
    /// Set number of full, half and quarter size shadowmaps. Only has effect if reuse of shadowmaps is disabled first
    void SetNumShadowMaps(unsigned full, unsigned half, unsigned quarter);
    /// Set dynamic instancing on/off
    void SetDynamicInstancing(bool enable);
    
    RegisterObject<Renderer>(engine, "Renderer");
    engine->RegisterObjectMethod("Renderer", "void SetNumShadowMaps(uint, uint, uint)", asMETHOD(Renderer, SetNumShadowMaps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void DrawDebugGeometry(bool) const", asMETHOD(Renderer, DrawDebugGeometry), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_numViewports(uint)", asMETHOD(Renderer, SetNumViewports), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numViewports() const", asMETHOD(Renderer, GetNumViewports), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_viewports(uint, const Viewport&in)", asMETHOD(Renderer, SetViewport), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "const Viewport& get_viewports(uint) const", asMETHOD(Renderer, GetViewport), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_specularLighting(bool)", asMETHOD(Renderer, SetSpecularLighting), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool get_specularLighting() const", asMETHOD(Renderer, GetSpecularLighting), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_drawShadows(bool)", asMETHOD(Renderer, SetDrawShadows), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool get_drawShadows() const", asMETHOD(Renderer, GetDrawShadows), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_textureAnisotropy(int)", asMETHOD(Renderer, SetTextureAnisotropy), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_textureAnisotropy() const", asMETHOD(Renderer, GetTextureAnisotropy), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_textureFilterMode(TextureFilterMode)", asMETHOD(Renderer, SetTextureFilterMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "TextureFilterMode get_textureFilterMode() const", asMETHOD(Renderer, GetTextureFilterMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_textureQuality(int)", asMETHOD(Renderer, SetTextureQuality), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_textureQuality() const", asMETHOD(Renderer, GetTextureQuality), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_materialQuality(int)", asMETHOD(Renderer, SetMaterialQuality), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_materialQuality() const", asMETHOD(Renderer, GetMaterialQuality), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_shadowMapSize(int)", asMETHOD(Renderer, SetShadowMapSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_shadowMapSize() const", asMETHOD(Renderer, GetShadowMapSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_shadowMapHiresDepth(bool)", asMETHOD(Renderer, SetShadowMapHiresDepth), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool get_shadowMapHiresDepth() const", asMETHOD(Renderer, GetShadowMapHiresDepth), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_reuseShadowMaps(bool)", asMETHOD(Renderer, SetReuseShadowMaps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool get_reuseShadowMaps() const", asMETHOD(Renderer, GetReuseShadowMaps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_dynamicInstancing(bool)", asMETHOD(Renderer, SetDynamicInstancing), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool get_dynamicInstancing() const", asMETHOD(Renderer, GetDynamicInstancing), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_maxOccluderTriangles(int)", asMETHOD(Renderer, SetMaxOccluderTriangles), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_maxOccluderTriangles() const", asMETHOD(Renderer, GetMaxOccluderTriangles), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_occlusionBufferSize(int)", asMETHOD(Renderer, SetOcclusionBufferSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_occlusionBufferSize() const", asMETHOD(Renderer, GetOcclusionBufferSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_occluderSizeThreshold(float)", asMETHOD(Renderer, SetOccluderSizeThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "float get_occluderSizeThreshold() const", asMETHOD(Renderer, GetOccluderSizeThreshold), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numPrimitives() const", asMETHOD(Renderer, GetNumPrimitives), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numBatches() const", asMETHOD(Renderer, GetNumBatches), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numViews() const", asMETHOD(Renderer, GetNumViews), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numGeometries(bool) const", asMETHOD(Renderer, GetNumGeometries), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numLights(bool) const", asMETHOD(Renderer, GetNumLights), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numShadowMaps(bool) const", asMETHOD(Renderer, GetNumShadowMaps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numOccluders(bool) const", asMETHOD(Renderer, GetNumOccluders), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numShadowOccluders(bool) const", asMETHOD(Renderer, GetNumShadowOccluders), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numFullShadowMaps() const", asMETHOD(Renderer, GetNumFullShadowMaps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numHalfShadowMaps() const", asMETHOD(Renderer, GetNumHalfShadowMaps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numQuarterShadowMaps() const", asMETHOD(Renderer, GetNumQuarterShadowMaps), asCALL_THISCALL);
    engine->RegisterGlobalFunction("Renderer@+ get_renderer()", asFUNCTION(GetRenderer), asCALL_CDECL);
}

static DebugRenderer* GetDebugRenderer()
{
    Scene* scene = GetScriptContextScene();
    if (scene)
        return scene->GetComponent<DebugRenderer>();
    else
        return 0;
}

static DebugRenderer* SceneGetDebugRenderer(Scene* ptr)
{
    return ptr->GetComponent<DebugRenderer>();
}

static void RegisterDebugRenderer(asIScriptEngine* engine)
{
    RegisterComponent<DebugRenderer>(engine, "DebugRenderer");
    engine->RegisterObjectMethod("DebugRenderer", "void AddLine(const Vector3&in, const Vector3&in, const Color&in, bool)", asMETHOD(DebugRenderer, AddLine), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void AddBoundingBox(const BoundingBox&in, const Color&in, bool)", asMETHODPR(DebugRenderer, AddBoundingBox, (const BoundingBox&, const Color&, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void AddFrustum(const Frustum&in, const Color&in, bool)", asMETHOD(DebugRenderer, AddFrustum), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void AddSkeleton(Skeleton@+, const Color&in, bool)", asMETHOD(DebugRenderer, AddSkeleton), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "DebugRenderer@+ get_debugRenderer() const", asFUNCTION(SceneGetDebugRenderer), asCALL_CDECL_OBJLAST);
    engine->RegisterGlobalFunction("DebugRenderer@+ get_debugRenderer()", asFUNCTION(GetDebugRenderer), asCALL_CDECL);
}

static void ConstructRayQueryResult(RayQueryResult* ptr)
{
    new(ptr) RayQueryResult();
    // Zero the drawable & node pointers for safety when constructing these from script
    ptr->drawable_ = 0;
    ptr->node_ = 0;
    ptr->distance_ = 0.0f;
    ptr->subObject_ = 0;
}

static Drawable* RayQueryResultGetDrawable(RayQueryResult* ptr)
{
    return ptr->drawable_;
}

static Node* RayQueryResultGetNode(RayQueryResult* ptr)
{
    return ptr->node_;
}

static CScriptArray* OctreeRaycast(const Ray& ray, unsigned char drawableFlags, float maxDistance, RayQueryLevel level, Octree* ptr)
{
    Vector<RayQueryResult> result;
    RayOctreeQuery query(result, ray, drawableFlags, false, false, maxDistance, level);
    ptr->GetDrawables(query);
    return VectorToArray<RayQueryResult>(result, "Array<RayQueryResult>");
}

static CScriptArray* OctreeGetDrawablesPoint(const Vector3& point, unsigned char drawableFlags, Octree* ptr)
{
    Vector<Drawable*> result;
    PointOctreeQuery query(result, point, drawableFlags);
    ptr->GetDrawables(query);
    return VectorToHandleArray<Drawable>(result, "Array<Drawable@>");
}

static CScriptArray* OctreeGetDrawablesBox(const BoundingBox& box, unsigned char drawableFlags, Octree* ptr)
{
    Vector<Drawable*> result;
    BoxOctreeQuery query(result, box, drawableFlags);
    ptr->GetDrawables(query);
    return VectorToHandleArray<Drawable>(result, "Array<Drawable@>");
}

static CScriptArray* OctreeGetDrawablesFrustum(const Frustum& frustum, unsigned char drawableFlags, Octree* ptr)
{
    Vector<Drawable*> result;
    FrustumOctreeQuery query(result, frustum, drawableFlags);
    ptr->GetDrawables(query);
    return VectorToHandleArray<Drawable>(result, "Array<Node@>");
}

static CScriptArray* OctreeGetDrawablesSphere(const Sphere& sphere, unsigned char drawableFlags, Octree* ptr)
{
    Vector<Drawable*> result;
    SphereOctreeQuery query(result, sphere, drawableFlags);
    ptr->GetDrawables(query);
    return VectorToHandleArray<Drawable>(result, "Array<Node@>");
}

static Octree* SceneGetOctree(Scene* ptr)
{
    return ptr->GetComponent<Octree>();
}

static Octree* GetOctree()
{
    Scene* scene = GetScriptContextScene();
    return scene ? scene->GetComponent<Octree>() : 0;
}

static void RegisterOctree(asIScriptEngine* engine)
{
    engine->RegisterEnum("RayQueryLevel");
    engine->RegisterEnumValue("RayQueryLevel", "RAY_AABB_NOSUBOBJECTS", RAY_AABB_NOSUBOBJECTS);
    engine->RegisterEnumValue("RayQueryLevel", "RAY_AABB", RAY_AABB_NOSUBOBJECTS);
    engine->RegisterEnumValue("RayQueryLevel", "RAY_OBB", RAY_OBB);
    engine->RegisterEnumValue("RayQueryLevel", "RAY_TRIANGLE", RAY_TRIANGLE);
    
    engine->RegisterObjectType("RayQueryResult", sizeof(RayQueryResult), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C);
    engine->RegisterObjectBehaviour("RayQueryResult", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructRayQueryResult), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("RayQueryResult", "Drawable@+ get_drawable() const", asFUNCTION(RayQueryResultGetDrawable), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("RayQueryResult", "Node@+ get_node() const", asFUNCTION(RayQueryResultGetNode), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("RayQueryResult", "float distance", offsetof(RayQueryResult, distance_));
    engine->RegisterObjectProperty("RayQueryResult", "uint subObject", offsetof(RayQueryResult, subObject_));
    
    RegisterComponent<Octree>(engine, "Octree");
    engine->RegisterObjectMethod("Octree", "void Resize(const BoundingBox&in, uint)", asMETHOD(Octree, Resize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "void DrawDebugGeometry(bool) const", asMETHOD(Octree, DrawDebugGeometry), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "Array<RayQueryResult>@ Raycast(const Ray&in, uint8, float, RayQueryLevel)", asFUNCTION(OctreeRaycast), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Octree", "Array<Node@>@ GetDrawables(const Vector3&in, uint8)", asFUNCTION(OctreeGetDrawablesPoint), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Octree", "Array<Node@>@ GetDrawables(const BoundingBox&in, uint8)", asFUNCTION(OctreeGetDrawablesBox), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Octree", "Array<Node@>@ GetDrawables(const Frustum&in, uint8)", asFUNCTION(OctreeGetDrawablesFrustum), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Octree", "Array<Node@>@ GetDrawables(const Sphere&in, uint8)", asFUNCTION(OctreeGetDrawablesSphere), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Octree", "const BoundingBox& get_worldBoundingBox() const", asMETHODPR(Octree, GetWorldBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "uint get_numLevels() const", asMETHOD(Octree, GetNumLevels), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Octree@+ get_octree() const", asFUNCTION(SceneGetOctree), asCALL_CDECL_OBJLAST);
    engine->RegisterGlobalFunction("Octree@+ get_octree()", asFUNCTION(GetOctree), asCALL_CDECL);
}

void RegisterGraphicsAPI(asIScriptEngine* engine)
{
    RegisterCamera(engine);
    RegisterSkeleton(engine);
    RegisterTextures(engine);
    RegisterMaterial(engine);
    RegisterModel(engine);
    RegisterAnimation(engine);
    RegisterDrawable(engine);
    RegisterLight(engine);
    RegisterZone(engine);
    RegisterStaticModel(engine);
    RegisterSkybox(engine);
    RegisterAnimatedModel(engine);
    RegisterAnimationController(engine);
    RegisterBillboardSet(engine);
    RegisterParticleEmitter(engine);
    RegisterDebugRenderer(engine);
    RegisterOctree(engine);
    RegisterGraphics(engine);
    RegisterRenderer(engine);
}
