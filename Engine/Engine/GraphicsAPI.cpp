//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "DecalSet.h"
#include "Graphics.h"
#include "Light.h"
#include "Material.h"
#include "Octree.h"
#include "ParticleEmitter.h"
#include "PostProcess.h"
#include "Scene.h"
#include "SmoothedTransform.h"
#include "Technique.h"
#include "Terrain.h"
#include "TerrainPatch.h"
#include "Texture2D.h"
#include "TextureCube.h"
#include "Skybox.h"
#include "Zone.h"

#ifdef _MSC_VER
#pragma warning(disable:4345)
#endif

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

static void RegisterCamera(asIScriptEngine* engine)
{
    engine->RegisterGlobalProperty("const uint VO_NONE", (void*)&VO_NONE);
    engine->RegisterGlobalProperty("const uint VO_LOW_MATERIAL_QUALITY", (void*)&VO_LOW_MATERIAL_QUALITY);
    engine->RegisterGlobalProperty("const uint VO_DISABLE_SHADOWS", (void*)&VO_DISABLE_SHADOWS);
    engine->RegisterGlobalProperty("const uint VO_DISABLE_OCCLUSION", (void*)&VO_DISABLE_OCCLUSION);
    
    RegisterComponent<Camera>(engine, "Camera");
    engine->RegisterObjectMethod("Camera", "void SetOrthoSize(const Vector2&in)", asMETHODPR(Camera, SetOrthoSize, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Frustum GetSplitFrustum(float, float) const", asMETHOD(Camera, GetSplitFrustum), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Ray GetScreenRay(float, float)", asMETHOD(Camera, GetScreenRay), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float GetDistance(const Vector3&in) const", asMETHOD(Camera, GetDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float GetDistanceSquared(const Vector3&in) const", asMETHOD(Camera, GetDistanceSquared), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_nearClip(float)", asMETHOD(Camera, SetNearClip), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_nearClip() const", asMETHOD(Camera, GetNearClip), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_farClip(float)", asMETHOD(Camera, SetFarClip), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_farClip() const", asMETHOD(Camera, GetFarClip), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_fov(float)", asMETHOD(Camera, SetFov), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_fov() const", asMETHOD(Camera, GetFov), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Camera", "void set_projectionOffset(const Vector2&in)", asMETHOD(Camera, SetProjectionOffset), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "const Vector2& get_projectionOffset() const", asMETHOD(Camera, GetProjectionOffset), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_viewMask(uint)", asMETHOD(Camera, SetViewMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "uint get_viewMask() const", asMETHOD(Camera, GetViewMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_viewOverrideFlags(uint)", asMETHOD(Camera, SetViewOverrideFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "uint get_viewOverrideFlags() const", asMETHOD(Camera, GetViewOverrideFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "const Frustum& get_frustum() const", asMETHOD(Camera, GetFrustum), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "const Matrix4& get_projection() const", asMETHODPR(Camera, GetProjection, () const, const Matrix4&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "const Matrix3x4& get_inverseWorldTransform() const", asMETHOD(Camera, GetInverseWorldTransform), asCALL_THISCALL);
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

static void BoneSetNode(Node* node, Bone* ptr)
{
    ptr->node_ = node;
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
    engine->RegisterObjectMethod("Bone", "void set_node(Node@+)", asFUNCTION(BoneSetNode), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Bone", "Node@+ get_node() const", asFUNCTION(BoneGetNode), asCALL_CDECL_OBJLAST);
    
    engine->RegisterObjectType("Skeleton", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("Skeleton", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Skeleton", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Skeleton", "void Reset()", asMETHOD(Skeleton, Reset), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skeleton", "Bone@+ GetBone(const String&in) const", asMETHODPR(Skeleton, GetBone, (const String&), Bone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skeleton", "Bone@+ get_rootBone() const", asMETHOD(Skeleton, GetRootBone), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skeleton", "uint get_numBones() const", asMETHOD(Skeleton, GetNumBones), asCALL_THISCALL);
    engine->RegisterObjectMethod("Skeleton", "Bone@+ get_bones(uint)", asMETHODPR(Skeleton, GetBone, (unsigned), Bone*), asCALL_THISCALL);
}

static Viewport* ConstructViewport()
{
    return new Viewport();
}

static Viewport* ConstructViewportSceneCamera(Scene* scene, Camera* camera)
{
    return new Viewport(scene, camera);
}

static Viewport* ConstructViewportSceneCameraRect(Scene* scene, Camera* camera, const IntRect& rect)
{
    return new Viewport(scene, camera, rect);
}

static Viewport* ConstructViewportSceneCameraPostProcesses(Scene* scene, Camera* camera, CScriptArray* arr)
{
    Vector<SharedPtr<PostProcess> > vec;
    if (arr)
    {
        for (unsigned i = 0; i < arr->GetSize(); ++i)
            vec.Push(SharedPtr<PostProcess>(*(static_cast<PostProcess**>(arr->At(i)))));
    }
    
    return new Viewport(scene, camera, vec);
}

static Viewport* ConstructViewportSceneCameraRectPostProcesses(Scene* scene, Camera* camera, const IntRect& rect, CScriptArray* arr)
{
    Vector<SharedPtr<PostProcess> > vec;
    if (arr)
    {
        for (unsigned i = 0; i < arr->GetSize(); ++i)
            vec.Push(SharedPtr<PostProcess>(*(static_cast<PostProcess**>(arr->At(i)))));
    }
    
    return new Viewport(scene, camera, rect, vec);
}

static bool Texture2DLoad(Image* image, bool useAlpha, Texture2D* ptr)
{
    return ptr->Load(SharedPtr<Image>(image), useAlpha);
}

static bool TextureCubeLoad(CubeMapFace face, Image* image, bool useAlpha, TextureCube* ptr)
{
    return ptr->Load(face, SharedPtr<Image>(image), useAlpha);
}

static void RegisterTextures(asIScriptEngine* engine)
{
    /// \todo Expose getting/setting raw texture data
    
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
    
    // Must register PostProcess early as Viewport needs it
    RegisterObject<PostProcess>(engine, "PostProcess");
    RegisterRefCounted<Viewport>(engine, "Viewport");
    engine->RegisterObjectBehaviour("Viewport", asBEHAVE_FACTORY, "Viewport@+ f()", asFUNCTION(ConstructViewport), asCALL_CDECL);
    engine->RegisterObjectBehaviour("Viewport", asBEHAVE_FACTORY, "Viewport@+ f(Scene@+, Camera@+)", asFUNCTION(ConstructViewportSceneCamera), asCALL_CDECL);
    engine->RegisterObjectBehaviour("Viewport", asBEHAVE_FACTORY, "Viewport@+ f(Scene@+, Camera@+, const IntRect&in)", asFUNCTION(ConstructViewportSceneCameraRect), asCALL_CDECL);
    engine->RegisterObjectBehaviour("Viewport", asBEHAVE_FACTORY, "Viewport@+ f(Scene@+, Camera@+, Array<PostProcess@>@+)", asFUNCTION(ConstructViewportSceneCameraPostProcesses), asCALL_CDECL);
    engine->RegisterObjectBehaviour("Viewport", asBEHAVE_FACTORY, "Viewport@+ f(Scene@+, Camera@+, const IntRect&in, Array<PostProcess@>@+)", asFUNCTION(ConstructViewportSceneCameraRectPostProcesses), asCALL_CDECL);
    engine->RegisterObjectMethod("Viewport", "void AddPostProcess(PostProcess@+)", asMETHOD(Viewport, AddPostProcess), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "void InsertPostProcess(uint, PostProcess@+)", asMETHOD(Viewport, InsertPostProcess), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "void RemovePostProcess(PostProcess@+)", asMETHODPR(Viewport, RemovePostProcess, (PostProcess*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "void RemovePostProcess(uint)", asMETHODPR(Viewport, RemovePostProcess, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "void RemoveAllPostProcesses()", asMETHOD(Viewport, RemoveAllPostProcesses), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "void set_scene(Scene@+)", asMETHOD(Viewport, SetScene), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "Scene@+ get_scene() const", asMETHOD(Viewport, GetScene), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "void set_camera(Camera@+)", asMETHOD(Viewport, SetCamera), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "Camera@+ get_camera() const", asMETHOD(Viewport, GetCamera), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "void set_rect(const IntRect&in)", asMETHOD(Viewport, SetCamera), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "const IntRect& get_rect() const", asMETHOD(Viewport, GetCamera), asCALL_THISCALL);
    engine->RegisterObjectMethod("Viewport", "uint get_numPostProcesses() const", asMETHOD(Viewport, GetNumPostProcesses), asCALL_THISCALL);
    
    engine->RegisterObjectType("RenderSurface", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("RenderSurface", asBEHAVE_ADDREF, "void f()", asMETHOD(RenderSurface, AddRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("RenderSurface", asBEHAVE_RELEASE, "void f()", asMETHOD(RenderSurface, ReleaseRef), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "Texture@+ get_parentTexture() const", asMETHOD(RenderSurface, GetParentTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "int get_width() const", asMETHOD(RenderSurface, GetWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "int get_height() const", asMETHOD(RenderSurface, GetHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "TextureUsage get_usage() const", asMETHOD(RenderSurface, GetUsage), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "void set_viewport(Viewport@+)", asMETHOD(RenderSurface, SetViewport), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "Viewport@+ get_viewport() const", asMETHOD(RenderSurface, GetViewport), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "void set_linkedRenderTarget(RenderSurface@+)", asMETHOD(RenderSurface, SetLinkedRenderTarget), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "RenderSurface@+ get_linkedRenderTarget() const", asMETHOD(RenderSurface, GetLinkedRenderTarget), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "void set_linkedDepthStencil(RenderSurface@+)", asMETHOD(RenderSurface, SetLinkedDepthStencil), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "RenderSurface@+ get_linkedDepthStencil() const", asMETHOD(RenderSurface, GetLinkedDepthStencil), asCALL_THISCALL);
    
    RegisterTexture<Texture2D>(engine, "Texture2D");
    engine->RegisterObjectMethod("Texture2D", "bool SetSize(int, int, uint, TextureUsage usage = TEXTURE_STATIC)", asMETHOD(Texture2D, SetSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "bool Load(Image@+, bool useAlpha = false)", asFUNCTION(Texture2DLoad), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Texture2D", "RenderSurface@+ get_renderSurface() const", asMETHOD(Texture2D, GetRenderSurface), asCALL_THISCALL);
    
    RegisterTexture<TextureCube>(engine, "TextureCube");
    engine->RegisterObjectMethod("TextureCube", "bool SetSize(int, uint, TextureUsage usage = TEXTURE_STATIC)", asMETHOD(TextureCube, SetSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "bool Load(CubeMapFace, Image@+, bool useAlpha = false)", asFUNCTION(TextureCubeLoad), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("TextureCube", "RenderSurface@+ get_renderSurface(CubeMapFace) const", asMETHOD(TextureCube, GetRenderSurface), asCALL_THISCALL);
    
    engine->RegisterGlobalFunction("uint GetAlphaFormat()", asFUNCTION(Graphics::GetAlphaFormat), asCALL_CDECL);
    engine->RegisterGlobalFunction("uint GetLuminanceFormat()", asFUNCTION(Graphics::GetLuminanceFormat), asCALL_CDECL);
    engine->RegisterGlobalFunction("uint GetLuminanceAlphaFormat()", asFUNCTION(Graphics::GetLuminanceAlphaFormat), asCALL_CDECL);
    engine->RegisterGlobalFunction("uint GetRGBFormat()", asFUNCTION(Graphics::GetRGBFormat), asCALL_CDECL);
    engine->RegisterGlobalFunction("uint GetRGBAFormat()", asFUNCTION(Graphics::GetRGBAFormat), asCALL_CDECL);
    engine->RegisterGlobalFunction("uint GetFloatFormat()", asFUNCTION(Graphics::GetFloatFormat), asCALL_CDECL);
    engine->RegisterGlobalFunction("uint GetDepthStencilFormat()", asFUNCTION(Graphics::GetDepthStencilFormat), asCALL_CDECL);
}

static Material* MaterialClone(const String& cloneName, Material* ptr)
{
    SharedPtr<Material> clone = ptr->Clone(cloneName);
    // The shared pointer will go out of scope, so have to increment the reference count
    // (here an auto handle can not be used)
    clone->AddRef();
    return clone.Get();
}

static void RegisterMaterial(asIScriptEngine* engine)
{
    engine->RegisterEnum("TextureUnit");
    engine->RegisterEnumValue("TextureUnit", "TU_DIFFUSE", TU_DIFFUSE);
    engine->RegisterEnumValue("TextureUnit", "TU_NORMAL", TU_NORMAL);
    engine->RegisterEnumValue("TextureUnit", "TU_SPECULAR", TU_SPECULAR);
    engine->RegisterEnumValue("TextureUnit", "TU_EMISSIVE", TU_EMISSIVE);
    engine->RegisterEnumValue("TextureUnit", "TU_ENVIRONMENT", TU_ENVIRONMENT);
    engine->RegisterEnumValue("TextureUnit", "MAX_MATERIAL_TEXTURE_UNITS", MAX_MATERIAL_TEXTURE_UNITS);
    
    engine->RegisterEnum("PassType");
    engine->RegisterEnumValue("PassType", "PASS_BASE", PASS_BASE);
    engine->RegisterEnumValue("PassType", "PASS_LIGHT", PASS_LIGHT);
    engine->RegisterEnumValue("PassType", "PASS_PREALPHA", PASS_PREALPHA);
    engine->RegisterEnumValue("PassType", "PASS_POSTALPHA", PASS_POSTALPHA);
    engine->RegisterEnumValue("PassType", "PASS_PREPASS", PASS_PREPASS);
    engine->RegisterEnumValue("PassType", "PASS_MATERIAL", PASS_MATERIAL);
    engine->RegisterEnumValue("PassType", "PASS_DEFERRED", PASS_DEFERRED);
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
    
    RegisterRefCounted<Pass>(engine, "Pass");
    engine->RegisterObjectMethod("Pass", "void set_blendMode(BlendMode)", asMETHOD(Pass, SetBlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "BlendMode get_blendMode() const", asMETHOD(Pass, GetBlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_depthTestMode(CompareMode)", asMETHOD(Pass, SetDepthTestMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "CompareMode get_depthTestMode() const", asMETHOD(Pass, GetDepthTestMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_depthWrite(bool)", asMETHOD(Pass, SetDepthWrite), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "bool get_depthWrite() const", asMETHOD(Pass, GetDepthWrite), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_alphaMask(bool)", asMETHOD(Pass, SetAlphaMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "bool get_alphaMask() const", asMETHOD(Pass, GetAlphaMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_vertexShader(const String&in)", asMETHOD(Pass, SetVertexShader), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "const String& get_vertexShader() const", asMETHOD(Pass, GetVertexShader), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "void set_pixelShader(const String&in)", asMETHOD(Pass, SetPixelShader), asCALL_THISCALL);
    engine->RegisterObjectMethod("Pass", "const String& get_pixelShader() const", asMETHOD(Pass, GetPixelShader), asCALL_THISCALL);
    
    RegisterResource<Technique>(engine, "Technique");
    engine->RegisterObjectMethod("Technique", "Pass@+ CreatePass(PassType)", asMETHOD(Technique, CreatePass), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "void RemovePass(PassType)", asMETHOD(Technique, RemovePass), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "bool HasPass(PassType) const", asMETHOD(Technique, HasPass), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "void set_sm3(bool)", asMETHOD(Technique, SetIsSM3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "bool get_sm3() const", asMETHOD(Technique, IsSM3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "Pass@+ get_passes(PassType)", asMETHOD(Technique, GetPass), asCALL_THISCALL);
    
    RegisterResource<Material>(engine, "Material");
    engine->RegisterObjectMethod("Material", "void SetUVTransform(const Vector2&in, float, const Vector2&in)", asMETHODPR(Material, SetUVTransform, (const Vector2&, float, const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void SetUVTransform(const Vector2&in, float, float)", asMETHODPR(Material, SetUVTransform, (const Vector2&, float, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void RemoveShaderParameter(const String&in)", asMETHOD(Material, RemoveShaderParameter), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "Material@ Clone(const String&in cloneName = String()) const", asFUNCTION(MaterialClone), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Material", "void set_numTechniques(uint)", asMETHOD(Material, SetNumTechniques), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "uint get_numTechniques() const", asMETHOD(Material, GetNumTechniques), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "Technique@+ get_technique(uint)", asMETHOD(Material, GetTechnique), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_shaderParameters(const String&in, const Vector4&in)", asMETHOD(Material, SetShaderParameter), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "const Vector4& get_shaderParameters(const String&in) const", asMETHOD(Material, GetShaderParameter), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_textures(uint, Texture@+)", asMETHOD(Material, SetTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "Texture@+ get_textures(uint) const", asMETHOD(Material, GetTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "bool get_occlusion()", asMETHOD(Material, GetOcclusion), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_cullMode(CullMode)", asMETHOD(Material, SetCullMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "CullMode get_cullMode() const", asMETHOD(Material, GetCullMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "void set_shadowCullMode(CullMode)", asMETHOD(Material, SetShadowCullMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Material", "CullMode get_shadowCullMode() const", asMETHOD(Material, GetShadowCullMode), asCALL_THISCALL);
}

static PostProcess* PostProcessClone(PostProcess* ptr)
{
    SharedPtr<PostProcess> clone = ptr->Clone();
    // The shared pointer will go out of scope, so have to increment the reference count
    // (here an auto handle can not be used)
    clone->AddRef();
    return clone.Get();
}

static void RegisterPostProcess(asIScriptEngine* engine)
{
    RegisterRefCounted<PostProcessPass>(engine, "PostProcessPass");
    engine->RegisterObjectMethod("PostProcessPass", "void RemoveShaderParameter(const String&in)", asMETHOD(PostProcessPass, RemoveShaderParameter), asCALL_THISCALL);
    engine->RegisterObjectMethod("PostProcessPass", "void set_vertexShader(const String&in)", asMETHOD(PostProcessPass, SetVertexShader), asCALL_THISCALL);
    engine->RegisterObjectMethod("PostProcessPass", "const String& get_vertexShader() const", asMETHOD(PostProcessPass, GetVertexShader), asCALL_THISCALL);
    engine->RegisterObjectMethod("PostProcessPass", "void set_pixelShader(const String&in)", asMETHOD(PostProcessPass, SetPixelShader), asCALL_THISCALL);
    engine->RegisterObjectMethod("PostProcessPass", "const String& get_pixelShader() const", asMETHOD(PostProcessPass, GetPixelShader), asCALL_THISCALL);
    engine->RegisterObjectMethod("PostProcessPass", "void set_output(const String&in)", asMETHOD(PostProcessPass, SetOutput), asCALL_THISCALL);
    engine->RegisterObjectMethod("PostProcessPass", "const String& get_output() const", asMETHOD(PostProcessPass, GetOutput), asCALL_THISCALL);
    engine->RegisterObjectMethod("PostProcessPass", "void set_textures(uint, const String&in)", asMETHOD(PostProcessPass, SetTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("PostProcessPass", "const String& get_textures(uint) const", asMETHOD(PostProcessPass, GetTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("PostProcessPass", "void set_shaderParameters(const String&in, const Vector4&in)", asMETHOD(PostProcessPass, SetShaderParameter), asCALL_THISCALL);
    engine->RegisterObjectMethod("PostProcessPass", "Vector4 get_shaderParameters(const String&in) const", asMETHOD(PostProcessPass, GetShaderParameter), asCALL_THISCALL);
    
    RegisterObjectConstructor<PostProcess>(engine, "PostProcess");
    engine->RegisterObjectMethod("PostProcess", "bool CreateRenderTarget(const String&in, uint, uint, uint, bool, bool)", asMETHOD(PostProcess, CreateRenderTarget), asCALL_THISCALL);
    engine->RegisterObjectMethod("PostProcess", "void RemoveRenderTarget(const String&in)", asMETHOD(PostProcess, RemoveRenderTarget), asCALL_THISCALL);
    engine->RegisterObjectMethod("PostProcess", "void RemoveShaderParameter(const String&in)", asMETHOD(PostProcess, RemoveShaderParameter), asCALL_THISCALL);
    engine->RegisterObjectMethod("PostProcess", "PostProcess@ Clone() const", asFUNCTION(PostProcessClone), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("PostProcess", "bool HasRenderTarget(const String&in) const", asMETHOD(PostProcess, HasRenderTarget), asCALL_THISCALL);
    engine->RegisterObjectMethod("PostProcess", "bool set_parameters(XMLFile@+)", asMETHOD(PostProcess, LoadParameters), asCALL_THISCALL);
    engine->RegisterObjectMethod("PostProcess", "XMLFile@+ get_parameters() const", asMETHOD(PostProcess, GetParameters), asCALL_THISCALL);
    engine->RegisterObjectMethod("PostProcess", "void set_numPasses(uint)", asMETHOD(PostProcess, SetNumPasses), asCALL_THISCALL);
    engine->RegisterObjectMethod("PostProcess", "uint get_numPasses() const", asMETHOD(PostProcess, GetNumPasses), asCALL_THISCALL);
    engine->RegisterObjectMethod("PostProcess", "void set_shaderParameters(const String&in, const Vector4&in)", asMETHOD(PostProcess, SetShaderParameter), asCALL_THISCALL);
    engine->RegisterObjectMethod("PostProcess", "Vector4 get_shaderParameters(const String&in) const", asMETHOD(PostProcess, GetShaderParameter), asCALL_THISCALL);
    engine->RegisterObjectMethod("PostProcess", "void set_active(bool)", asMETHOD(PostProcess, SetActive), asCALL_THISCALL);
    engine->RegisterObjectMethod("PostProcess", "bool get_active() const", asMETHOD(PostProcess, IsActive), asCALL_THISCALL);
    engine->RegisterObjectMethod("PostProcess", "PostProcessPass@+ get_passes(uint) const", asMETHOD(PostProcess, GetPass), asCALL_THISCALL);
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
    engine->RegisterGlobalProperty("uint DRAWABLE_ANY", (void*)&DRAWABLE_ANY);
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
    new(ptr) CascadeParameters(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

static void ConstructCascadeParametersCopy(CascadeParameters& parameters, CascadeParameters* ptr)
{
    new(ptr) CascadeParameters(parameters);
}

static void ConstructCascadeParametersInit(float split1, float split2, float split3, float split4, float fadeStart, CascadeParameters* ptr)
{
    new(ptr) CascadeParameters(split1, split2, split3, split4, fadeStart);
}

static void ConstructFocusParameters(FocusParameters* ptr)
{
    new(ptr) FocusParameters(false, false, false, 0.0f, 0.0f);
}

static void ConstructFocusParametersCopy(FocusParameters& parameters, FocusParameters* ptr)
{
    new(ptr) FocusParameters(parameters);
}

static void ConstructFocusParametersInit(bool focus, bool nonUniform, bool autoSize, float quantize, float minView, FocusParameters* ptr)
{
    new(ptr) FocusParameters(focus, nonUniform, autoSize, quantize, minView);
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
    engine->RegisterObjectBehaviour("CascadeParameters", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float)", asFUNCTION(ConstructCascadeParametersInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("CascadeParameters", "float split1", offsetof(CascadeParameters, splits_[0]));
    engine->RegisterObjectProperty("CascadeParameters", "float split2", offsetof(CascadeParameters, splits_[1]));
    engine->RegisterObjectProperty("CascadeParameters", "float split3", offsetof(CascadeParameters, splits_[2]));
    engine->RegisterObjectProperty("CascadeParameters", "float split4", offsetof(CascadeParameters, splits_[3]));
    engine->RegisterObjectProperty("CascadeParameters", "float fadeStart", offsetof(CascadeParameters, fadeStart_));
    
    engine->RegisterObjectType("FocusParameters", sizeof(FocusParameters), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C);
    engine->RegisterObjectBehaviour("FocusParameters", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructFocusParameters), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("FocusParameters", asBEHAVE_CONSTRUCT, "void f(const FocusParameters&in)", asFUNCTION(ConstructFocusParametersCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("FocusParameters", asBEHAVE_CONSTRUCT, "void f(bool, bool, bool, float, float)", asFUNCTION(ConstructFocusParametersInit), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("FocusParameters", "bool focus", offsetof(FocusParameters, focus_));
    engine->RegisterObjectProperty("FocusParameters", "bool nonUniform", offsetof(FocusParameters, nonUniform_));
    engine->RegisterObjectProperty("FocusParameters", "bool autoSize", offsetof(FocusParameters, autoSize_));
    engine->RegisterObjectProperty("FocusParameters", "float quantize", offsetof(FocusParameters, quantize_));
    engine->RegisterObjectProperty("FocusParameters", "float minView", offsetof(FocusParameters, minView_));
    
    RegisterDrawable<Light>(engine, "Light");
    engine->RegisterObjectMethod("Light", "void set_lightType(LightType)", asMETHOD(Light, SetLightType), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "LightType get_lightType() const", asMETHOD(Light, GetLightType), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_perVertex(bool)", asMETHOD(Light, SetPerVertex), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool get_perVertex() const", asMETHOD(Light, GetPerVertex), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Zone", "const Matrix3x4& get_inverseWorldTransform() const", asMETHOD(Zone, GetInverseWorldTransform), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_ambientColor(const Color&in)", asMETHOD(Zone, SetAmbientColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const Color& get_ambientColor() const", asMETHOD(Zone, GetAmbientColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const Color& get_ambientStartColor()", asMETHOD(Zone, GetAmbientStartColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const Color& get_ambientEndColor()", asMETHOD(Zone, GetAmbientEndColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_fogColor(const Color&in)", asMETHOD(Zone, SetFogColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const Color& get_fogColor() const", asMETHOD(Zone, GetFogColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_fogStart(float)", asMETHOD(Zone, SetFogStart), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "float get_fogStart() const", asMETHOD(Zone, GetFogStart), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_fogEnd(float)", asMETHOD(Zone, SetFogEnd), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "float get_fogEnd() const", asMETHOD(Zone, GetFogEnd), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_priority(int)", asMETHOD(Zone, SetPriority), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "int get_priority() const", asMETHOD(Zone, GetPriority), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_override(bool)", asMETHOD(Zone, SetOverride), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_override() const", asMETHOD(Zone, GetOverride), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_ambientGradient(bool)", asMETHOD(Zone, SetAmbientGradient), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_ambientGradient() const", asMETHOD(Zone, GetAmbientGradient), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("StaticModel", "void set_occlusionLodLevel(uint) const", asMETHOD(StaticModel, SetOcclusionLodLevel), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "uint get_occlusionLodLevel() const", asMETHOD(StaticModel, GetOcclusionLodLevel), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "Zone@+ get_zone() const", asMETHOD(StaticModel, GetZone), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Skybox", "Zone@+ get_zone() const", asMETHOD(StaticModel, GetZone), asCALL_THISCALL);
}

static void AnimatedModelSetModel(Model* model, AnimatedModel* ptr)
{
    ptr->SetModel(model);
}

static const String& AnimatedModelGetMorphName(unsigned index, AnimatedModel* ptr)
{
    const Vector<ModelMorph>& morphs = ptr->GetMorphs();
    return index < morphs.Size() ? morphs[index].name_ : String::EMPTY;
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
    engine->RegisterObjectMethod("AnimationState", "void set_layer(uint8)", asMETHOD(AnimationState, SetLayer), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "uint8 get_layer() const", asMETHOD(AnimationState, GetLayer), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("AnimatedModel", "void set_animationLodBias(float)", asMETHOD(AnimatedModel, SetAnimationLodBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "float get_animationLodBias() const", asMETHOD(AnimatedModel, GetAnimationLodBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_invisibleLodFactor(float)", asMETHOD(AnimatedModel, SetInvisibleLodFactor), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "float get_invisibleLodFactor() const", asMETHOD(AnimatedModel, GetInvisibleLodFactor), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "Skeleton@+ get_skeleton()", asMETHOD(AnimatedModel, GetSkeleton), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_numAnimationStates() const", asMETHOD(AnimatedModel, GetNumAnimationStates), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "AnimationState@+ get_animationStates(const String&in) const", asMETHODPR(AnimatedModel, GetAnimationState, (const String&) const, AnimationState*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_numMorphs() const", asMETHOD(AnimatedModel, GetNumMorphs), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "const String& get_morphNames(uint) const", asFUNCTION(AnimatedModelGetMorphName), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("AnimatedModel", "void set_morphWeights(const String&in, float)", asMETHODPR(AnimatedModel, SetMorphWeight, (const String&, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "float get_morphWeights(const String&in) const", asMETHODPR(AnimatedModel, GetMorphWeight, (const String&) const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "Zone@+ get_zone() const", asMETHOD(AnimatedModel, GetZone), asCALL_THISCALL);
}

static void RegisterAnimationController(asIScriptEngine* engine)
{
    RegisterComponent<AnimationController>(engine, "AnimationController");
    engine->RegisterObjectMethod("AnimationController", "bool Play(const String&in, uint8, bool, float fadeTime = 0.0f)", asMETHOD(AnimationController, Play), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool PlayExclusive(const String&in, uint8, bool, float fadeTime = 0.0f)", asMETHOD(AnimationController, PlayExclusive), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "void Stop(const String&in, float fadeTime = 0.0f)", asMETHOD(AnimationController, Stop), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "void StopLayer(uint8, float fadeTime = 0.0f)", asMETHOD(AnimationController, StopLayer), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "void StopAll(float fadeTime = 0.0f)", asMETHOD(AnimationController, StopAll), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool Fade(const String&in, float, float)", asMETHOD(AnimationController, Fade), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool FadeOthers(const String&in, float, float)", asMETHOD(AnimationController, FadeOthers), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool SetLayer(const String&in, uint8)", asMETHOD(AnimationController, SetLayer), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool SetStartBone(const String&in, const String&in)", asMETHOD(AnimationController, SetStartBone), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool SetTime(const String&in, float)", asMETHOD(AnimationController, SetTime), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool SetWeight(const String&in, float)", asMETHOD(AnimationController, SetWeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool SetLooped(const String&in, bool)", asMETHOD(AnimationController, SetLooped), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool SetSpeed(const String&in, float)", asMETHOD(AnimationController, SetSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool SetAutoFade(const String&in, float)", asMETHOD(AnimationController, SetAutoFade), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool IsPlaying(const String&in) const", asMETHOD(AnimationController, IsPlaying), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool IsFadingIn(const String&in) const", asMETHOD(AnimationController, IsFadingIn), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool IsFadingOut(const String&in) const", asMETHOD(AnimationController, IsFadingOut), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "uint8 GetLayer(const String&in) const", asMETHOD(AnimationController, GetLayer), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("BillboardSet", "bool get_relative() const", asMETHOD(BillboardSet, IsRelative), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_sorted(bool)", asMETHOD(BillboardSet, SetSorted), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_sorted() const", asMETHOD(BillboardSet, IsSorted), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_scaled(bool)", asMETHOD(BillboardSet, SetScaled), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_scaled() const", asMETHOD(BillboardSet, IsScaled), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_animationLodBias(float)", asMETHOD(BillboardSet, SetAnimationLodBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "float get_animationLodBias() const", asMETHOD(BillboardSet, GetAnimationLodBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "Billboard@+ get_billboards(uint)", asMETHOD(BillboardSet, GetBillboard), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "Zone@+ get_zone() const", asMETHOD(BillboardSet, GetZone), asCALL_THISCALL);
}

static void RegisterParticleEmitter(asIScriptEngine* engine)
{
    RegisterDrawable<ParticleEmitter>(engine, "ParticleEmitter");
    engine->RegisterObjectMethod("ParticleEmitter", "void SetActive(bool, bool)", asMETHOD(ParticleEmitter, SetActive), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_material(Material@+)", asMETHOD(ParticleEmitter, SetMaterial), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "Material@+ get_material() const", asMETHOD(ParticleEmitter, SetMaterial), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_relative(bool)", asMETHOD(ParticleEmitter, SetRelative), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_relative() const", asMETHOD(ParticleEmitter, IsRelative), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_sorted(bool)", asMETHOD(ParticleEmitter, SetSorted), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_sorted() const", asMETHOD(ParticleEmitter, IsSorted), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_scaled(bool)", asMETHOD(ParticleEmitter, SetScaled), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_scaled() const", asMETHOD(ParticleEmitter, IsScaled), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "void set_animationLodBias(float)", asMETHOD(ParticleEmitter, SetAnimationLodBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "float get_animationLodBias() const", asMETHOD(ParticleEmitter, GetAnimationLodBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool set_parameters(XMLFile@+ file)", asMETHOD(ParticleEmitter, LoadParameters), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "XMLFile@+ get_parameters() const", asMETHOD(ParticleEmitter, GetParameters), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "bool get_active() const", asMETHOD(ParticleEmitter, IsActive), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "uint get_numParticles() const", asMETHOD(ParticleEmitter, GetNumParticles), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter", "Zone@+ get_zone() const", asMETHOD(ParticleEmitter, GetZone), asCALL_THISCALL);
}

static void RegisterDecalSet(asIScriptEngine* engine)
{
    RegisterDrawable<DecalSet>(engine, "DecalSet");
    engine->RegisterObjectMethod("DecalSet", "bool AddDecal(Drawable@+, const Vector3&in, const Quaternion&in, float, float, float, const Vector2&in, const Vector2&in, float timeToLive = 0.0, float normalCutoff = 0.1, float depthBias = 0.001, uint subGeometry = 0xffffffff)", asMETHOD(DecalSet, AddDecal), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void RemoveDecals(uint)", asMETHOD(DecalSet, RemoveDecals), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void RemoveAllDecals()", asMETHOD(DecalSet, RemoveAllDecals), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_material(Material@+)", asMETHOD(DecalSet, SetMaterial), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "Material@+ get_material() const", asMETHOD(DecalSet, GetMaterial), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_numDecals() const", asMETHOD(DecalSet, GetNumDecals), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_numVertices() const", asMETHOD(DecalSet, GetNumVertices), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_numIndices() const", asMETHOD(DecalSet, GetNumVertices), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_maxVertices(uint)", asMETHOD(DecalSet, SetMaxVertices), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_maxVertices() const", asMETHOD(DecalSet, GetMaxVertices), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "void set_maxIndices(uint)", asMETHOD(DecalSet, SetMaxIndices), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "uint get_maxIndices() const", asMETHOD(DecalSet, GetMaxIndices), asCALL_THISCALL);
    engine->RegisterObjectMethod("DecalSet", "Zone@+ get_zone() const", asMETHOD(DecalSet, GetZone), asCALL_THISCALL);
}

static void RegisterTerrain(asIScriptEngine* engine)
{
    RegisterDrawable<TerrainPatch>(engine, "TerrainPatch");
    RegisterComponent<Terrain>(engine, "Terrain");
    engine->RegisterObjectMethod("Terrain", "float GetHeight(const Vector3&in) const", asMETHOD(Terrain, GetHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_material(Material@+)", asMETHOD(Terrain, SetMaterial), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "Material@+ get_material() const", asMETHOD(Terrain, GetMaterial), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_heightMap(Image@+)", asMETHOD(Terrain, SetHeightMap), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "Image@+ get_heightMap() const", asMETHOD(Terrain, GetHeightMap), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_patchSize(uint)", asMETHOD(Terrain, SetPatchSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "uint get_patchSize() const", asMETHOD(Terrain, GetPatchSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_spacing(const Vector3&in)", asMETHOD(Terrain, SetSpacing), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "const Vector3& get_spacing() const", asMETHOD(Terrain, GetSpacing), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "const IntVector2& get_size() const", asMETHOD(Terrain, GetSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "uint get_numPatches() const", asMETHOD(Terrain, GetNumPatches), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "TerrainPatch@+ get_patches(uint) const", asMETHOD(Terrain, GetPatch), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_visible(bool)", asMETHOD(Terrain, SetVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool get_visible() const", asMETHOD(Terrain, IsVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_castShadows(bool)", asMETHOD(Terrain, SetCastShadows), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool get_castShadows() const", asMETHOD(Terrain, GetCastShadows), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_occluder(bool)", asMETHOD(Terrain, SetOccluder), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool get_occluder() const", asMETHOD(Terrain, IsOccluder), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_occludee(bool)", asMETHOD(Terrain, SetOccludee), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool get_occludee() const", asMETHOD(Terrain, IsOccludee), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_drawDistance(float)", asMETHOD(Terrain, SetDrawDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "float get_drawDistance() const", asMETHOD(Terrain, GetDrawDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_shadowDistance(float)", asMETHOD(Terrain, SetShadowDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "float get_shadowDistance() const", asMETHOD(Terrain, GetShadowDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_lodBias(float)", asMETHOD(Terrain, SetLodBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "float get_lodBias() const", asMETHOD(Terrain, GetLodBias), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_viewMask(uint)", asMETHOD(Terrain, SetViewMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "uint get_viewMask() const", asMETHOD(Terrain, GetViewMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_lightMask(uint)", asMETHOD(Terrain, SetLightMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "uint get_lightMask() const", asMETHOD(Terrain, GetLightMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_shadowMask(uint)", asMETHOD(Terrain, SetShadowMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "uint get_shadowMask() const", asMETHOD(Terrain, GetShadowMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_zoneMask(uint)", asMETHOD(Terrain, SetZoneMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "uint get_zoneMask() const", asMETHOD(Terrain, GetZoneMask), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_maxLights(uint)", asMETHOD(Terrain, SetMaxLights), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "uint get_maxLights() const", asMETHOD(Terrain, GetMaxLights), asCALL_THISCALL);
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
    RegisterObject<Graphics>(engine, "Graphics");
    engine->RegisterObjectMethod("Graphics", "bool SetMode(int, int, bool, bool, bool, int)", asMETHODPR(Graphics, SetMode, (int, int, bool, bool, bool, int), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool SetMode(int, int)", asMETHODPR(Graphics, SetMode, (int, int), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool ToggleFullscreen()", asMETHOD(Graphics, ToggleFullscreen), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "void Close()", asMETHOD(Graphics, Close), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool TakeScreenShot(Image@+)", asMETHOD(Graphics, TakeScreenShot), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "void set_windowTitle(const String&in)", asMETHOD(Graphics, SetWindowTitle), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "const String& get_windowTitle() const", asMETHOD(Graphics, GetWindowTitle), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "int get_width() const", asMETHOD(Graphics, GetWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "int get_height() const", asMETHOD(Graphics, GetHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "int get_multiSample() const", asMETHOD(Graphics, GetMultiSample), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_fullscreen() const", asMETHOD(Graphics, GetFullscreen), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_vsync() const", asMETHOD(Graphics, GetVSync), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_tripleBuffer() const", asMETHOD(Graphics, GetTripleBuffer), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_initialized() const", asMETHOD(Graphics, IsInitialized), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_deviceLost() const", asMETHOD(Graphics, IsDeviceLost), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "uint get_numPrimitives() const", asMETHOD(Graphics, GetNumPrimitives), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "uint get_numBatches() const", asMETHOD(Graphics, GetNumBatches), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_sm3Support() const", asMETHOD(Graphics, GetSM3Support), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_lightPrepassSupport() const", asMETHOD(Graphics, GetLightPrepassSupport), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_deferredSupport() const", asMETHOD(Graphics, GetDeferredSupport), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_hardwareDepthSupport() const", asMETHOD(Graphics, GetHardwareDepthSupport), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_hardwareShadowSupport() const", asMETHOD(Graphics, GetHardwareShadowSupport), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "void set_forceSM2(bool)", asMETHOD(Graphics, SetForceSM2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_forceSM2() const", asMETHOD(Graphics, GetForceSM2), asCALL_THISCALL);
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
    engine->RegisterEnum("RenderMode");
    engine->RegisterEnumValue("RenderMode", "RENDER_FORWARD", RENDER_FORWARD);
    engine->RegisterEnumValue("RenderMode", "RENDER_PREPASS", RENDER_PREPASS);
    engine->RegisterEnumValue("RenderMode", "RENDER_DEFERRED", RENDER_DEFERRED);
    
    engine->RegisterGlobalProperty("const int QUALITY_LOW", (void*)&QUALITY_LOW);
    engine->RegisterGlobalProperty("const int QUALITY_MEDIUM", (void*)&QUALITY_MEDIUM);
    engine->RegisterGlobalProperty("const int QUALITY_HIGH", (void*)&QUALITY_HIGH);
    
    engine->RegisterGlobalProperty("const int SHADOWQUALITY_LOW_16BIT", (void*)&SHADOWQUALITY_LOW_16BIT);
    engine->RegisterGlobalProperty("const int SHADOWQUALITY_LOW_24BIT", (void*)&SHADOWQUALITY_LOW_24BIT);
    engine->RegisterGlobalProperty("const int SHADOWQUALITY_HIGH_16BIT", (void*)&SHADOWQUALITY_HIGH_16BIT);
    engine->RegisterGlobalProperty("const int SHADOWQUALITY_HIGH_24BIT", (void*)&SHADOWQUALITY_HIGH_24BIT);
    
    RegisterObject<Renderer>(engine, "Renderer");
    engine->RegisterObjectMethod("Renderer", "void DrawDebugGeometry(bool) const", asMETHOD(Renderer, DrawDebugGeometry), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_numViewports(uint)", asMETHOD(Renderer, SetNumViewports), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numViewports() const", asMETHOD(Renderer, GetNumViewports), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool set_viewports(uint, Viewport@+)", asMETHOD(Renderer, SetViewport), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "Viewport@+ get_viewports(uint) const", asMETHOD(Renderer, GetViewport), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_renderMode(RenderMode)", asMETHOD(Renderer, SetRenderMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "RenderMode get_renderMode() const", asMETHOD(Renderer, GetRenderMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_specularLighting(bool)", asMETHOD(Renderer, SetSpecularLighting), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool get_specularLighting() const", asMETHOD(Renderer, GetSpecularLighting), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_textureAnisotropy(int)", asMETHOD(Renderer, SetTextureAnisotropy), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_textureAnisotropy() const", asMETHOD(Renderer, GetTextureAnisotropy), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_textureFilterMode(TextureFilterMode)", asMETHOD(Renderer, SetTextureFilterMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "TextureFilterMode get_textureFilterMode() const", asMETHOD(Renderer, GetTextureFilterMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_textureQuality(int)", asMETHOD(Renderer, SetTextureQuality), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_textureQuality() const", asMETHOD(Renderer, GetTextureQuality), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_materialQuality(int)", asMETHOD(Renderer, SetMaterialQuality), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_materialQuality() const", asMETHOD(Renderer, GetMaterialQuality), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_drawShadows(bool)", asMETHOD(Renderer, SetDrawShadows), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool get_drawShadows() const", asMETHOD(Renderer, GetDrawShadows), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_shadowMapSize(int)", asMETHOD(Renderer, SetShadowMapSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_shadowMapSize() const", asMETHOD(Renderer, GetShadowMapSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_shadowQuality(int)", asMETHOD(Renderer, SetShadowQuality), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_shadowQuality() const", asMETHOD(Renderer, GetShadowQuality), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_maxShadowCascades(int)", asMETHOD(Renderer, SetMaxShadowCascades), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_maxShadowCascades() const", asMETHOD(Renderer, GetMaxShadowCascades), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_maxShadowMaps(int)", asMETHOD(Renderer, SetMaxShadowMaps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_maxShadowMaps() const", asMETHOD(Renderer, GetMaxShadowMaps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_reuseShadowMaps(bool)", asMETHOD(Renderer, SetReuseShadowMaps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool get_reuseShadowMaps() const", asMETHOD(Renderer, GetReuseShadowMaps), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_dynamicInstancing(bool)", asMETHOD(Renderer, SetDynamicInstancing), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool get_dynamicInstancing() const", asMETHOD(Renderer, GetDynamicInstancing), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_maxInstanceTriangles(int)", asMETHOD(Renderer, SetMaxInstanceTriangles), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_maxInstanceTriangles() const", asMETHOD(Renderer, GetMaxInstanceTriangles), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_maxSortedInstances(int)", asMETHOD(Renderer, SetMaxSortedInstances), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_maxSortedInstances() const", asMETHOD(Renderer, GetMaxSortedInstances), asCALL_THISCALL);
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
    RegisterComponent<DebugRenderer>(engine, "DebugRenderer", true, false);
    engine->RegisterObjectMethod("DebugRenderer", "void AddLine(const Vector3&in, const Vector3&in, const Color&in, bool depthTest = true)", asMETHODPR(DebugRenderer, AddLine, (const Vector3&, const Vector3&, const Color&, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void AddNode(Node@+, float scale = 1.0, bool depthTest = true)", asMETHOD(DebugRenderer, AddNode), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void AddBoundingBox(const BoundingBox&in, const Color&in, bool depthTest = true)", asMETHODPR(DebugRenderer, AddBoundingBox, (const BoundingBox&, const Color&, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void AddFrustum(const Frustum&in, const Color&in, bool depthTest = true)", asMETHOD(DebugRenderer, AddFrustum), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void AddPolyhedron(const Polyhedron&in, const Color&in, bool depthTest = true)", asMETHOD(DebugRenderer, AddPolyhedron), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void AddSphere(const Sphere&in, const Color&in, bool depthTest = true)", asMETHOD(DebugRenderer, AddSphere), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void AddSkeleton(Skeleton@+, const Color&in, bool depthTest = true)", asMETHOD(DebugRenderer, AddSkeleton), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "DebugRenderer@+ get_debugRenderer() const", asFUNCTION(SceneGetDebugRenderer), asCALL_CDECL_OBJLAST);
    engine->RegisterGlobalFunction("DebugRenderer@+ get_debugRenderer()", asFUNCTION(GetDebugRenderer), asCALL_CDECL);
    
    // Component::DrawDebugGeometry() can be registered now
    engine->RegisterObjectMethod("Component", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHOD(Component, DrawDebugGeometry), asCALL_THISCALL);
    engine->RegisterObjectMethod("SmoothedTransform", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHOD(SmoothedTransform, DrawDebugGeometry), asCALL_THISCALL);
    engine->RegisterObjectMethod("DebugRenderer", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHOD(DebugRenderer, DrawDebugGeometry), asCALL_THISCALL);

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

static CScriptArray* OctreeRaycast(const Ray& ray, RayQueryLevel level, float maxDistance, unsigned char drawableFlags, unsigned viewMask, Octree* ptr)
{
    PODVector<RayQueryResult> result;
    RayOctreeQuery query(result, ray, level, maxDistance, drawableFlags, viewMask);
    ptr->Raycast(query);
    return VectorToArray<RayQueryResult>(result, "Array<RayQueryResult>");
}

static RayQueryResult OctreeRaycastSingle(const Ray& ray, RayQueryLevel level, float maxDistance, unsigned char drawableFlags, unsigned viewMask, Octree* ptr)
{
    PODVector<RayQueryResult> result;
    RayOctreeQuery query(result, ray, level, maxDistance, drawableFlags, viewMask);
    ptr->RaycastSingle(query);
    if (!query.result_.Empty())
        return query.result_[0];
    else
    {
        RayQueryResult empty;
        empty.drawable_ = 0;
        empty.node_ = 0;
        empty.distance_ = M_INFINITY;
        empty.subObject_ = 0;
        return empty;
    }
}

static CScriptArray* OctreeGetDrawablesPoint(const Vector3& point, unsigned char drawableFlags, unsigned viewMask, Octree* ptr)
{
    PODVector<Drawable*> result;
    PointOctreeQuery query(result, point, drawableFlags, viewMask);
    ptr->GetDrawables(query);
    return VectorToHandleArray<Drawable>(result, "Array<Drawable@>");
}

static CScriptArray* OctreeGetDrawablesBox(const BoundingBox& box, unsigned char drawableFlags, unsigned viewMask, Octree* ptr)
{
    PODVector<Drawable*> result;
    BoxOctreeQuery query(result, box, drawableFlags, viewMask);
    ptr->GetDrawables(query);
    return VectorToHandleArray<Drawable>(result, "Array<Drawable@>");
}

static CScriptArray* OctreeGetDrawablesFrustum(const Frustum& frustum, unsigned char drawableFlags, unsigned viewMask, Octree* ptr)
{
    PODVector<Drawable*> result;
    FrustumOctreeQuery query(result, frustum, drawableFlags, viewMask);
    ptr->GetDrawables(query);
    return VectorToHandleArray<Drawable>(result, "Array<Node@>");
}

static CScriptArray* OctreeGetDrawablesSphere(const Sphere& sphere, unsigned char drawableFlags, unsigned viewMask, Octree* ptr)
{
    PODVector<Drawable*> result;
    SphereOctreeQuery query(result, sphere, drawableFlags, viewMask);
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
    engine->RegisterObjectMethod("Octree", "void DrawDebugGeometry(bool) const", asMETHODPR(Octree, DrawDebugGeometry, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "void AddManualDrawable(Drawable@+)", asMETHOD(Octree, AddManualDrawable), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "void RemoveManualDrawable(Drawable@+)", asMETHOD(Octree, RemoveManualDrawable), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "Array<RayQueryResult>@ Raycast(const Ray&in, RayQueryLevel level = RAY_TRIANGLE, float maxDistance = M_INFINITY, uint8 drawableFlags = DRAWABLE_ANY, uint viewMask = DEFAULT_VIEWMASK) const", asFUNCTION(OctreeRaycast), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Octree", "RayQueryResult RaycastSingle(const Ray&in, RayQueryLevel level = RAY_TRIANGLE, float maxDistance = M_INFINITY, uint8 drawableFlags = DRAWABLE_ANY, uint viewMask = DEFAULT_VIEWMASK) const", asFUNCTION(OctreeRaycastSingle), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Octree", "Array<Node@>@ GetDrawables(const Vector3&in, uint8 drawableFlags = DRAWABLE_ANY, uint viewMask = DEFAULT_VIEWMASK)", asFUNCTION(OctreeGetDrawablesPoint), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Octree", "Array<Node@>@ GetDrawables(const BoundingBox&in, uint8 drawableFlags = DRAWABLE_ANY, uint viewMask = DEFAULT_VIEWMASK)", asFUNCTION(OctreeGetDrawablesBox), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Octree", "Array<Node@>@ GetDrawables(const Frustum&in, uint8 drawableFlags = DRAWABLE_ANY, uint viewMask = DEFAULT_VIEWMASK)", asFUNCTION(OctreeGetDrawablesFrustum), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Octree", "Array<Node@>@ GetDrawables(const Sphere&in, uint8 drawableFlags = DRAWABLE_ANY, uint viewMask = DEFAULT_VIEWMASK)", asFUNCTION(OctreeGetDrawablesSphere), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Octree", "const BoundingBox& get_worldBoundingBox() const", asMETHODPR(Octree, GetWorldBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "uint get_numLevels() const", asMETHOD(Octree, GetNumLevels), asCALL_THISCALL);
    engine->RegisterObjectMethod("Scene", "Octree@+ get_octree() const", asFUNCTION(SceneGetOctree), asCALL_CDECL_OBJLAST);
    engine->RegisterGlobalFunction("Octree@+ get_octree()", asFUNCTION(GetOctree), asCALL_CDECL);
}

void RegisterGraphicsAPI(asIScriptEngine* engine)
{
    RegisterSkeleton(engine);
    RegisterDebugRenderer(engine);
    RegisterCamera(engine);
    RegisterTextures(engine);
    RegisterMaterial(engine);
    RegisterPostProcess(engine);
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
    RegisterDecalSet(engine);
    RegisterTerrain(engine);
    RegisterOctree(engine);
    RegisterGraphics(engine);
    RegisterRenderer(engine);
}
