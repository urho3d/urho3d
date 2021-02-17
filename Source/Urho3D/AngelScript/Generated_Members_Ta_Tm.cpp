// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// SharedPtr<Technique> Technique::Clone(const String& cloneName=String::EMPTY) const | File: ../Graphics/Technique.h
static Technique* Technique_Clone_String(Technique* ptr, const String& cloneName)
{
    SharedPtr<Technique> result = ptr->Clone(cloneName);
    return result.Detach();
}

// SharedPtr<Technique> Technique::CloneWithDefines(const String& vsDefines, const String& psDefines) | File: ../Graphics/Technique.h
static Technique* Technique_CloneWithDefines_String_String(Technique* ptr, const String& vsDefines, const String& psDefines)
{
    SharedPtr<Technique> result = ptr->CloneWithDefines(vsDefines, psDefines);
    return result.Detach();
}

// PODVector<Pass*> Technique::GetPasses() const | File: ../Graphics/Technique.h
static CScriptArray* Technique_GetPasses_void(Technique* ptr)
{
    PODVector<Pass*> result = ptr->GetPasses();
    return VectorToHandleArray(result, "Array<Pass@>");
}

// Vector<String> Technique::GetPassNames() const | File: ../Graphics/Technique.h
static CScriptArray* Technique_GetPassNames_void(Technique* ptr)
{
    Vector<String> result = ptr->GetPassNames();
    return VectorToArray<String>(result, "Array<String>");
}

// explicit Technique::Technique(Context* context) | File: ../Graphics/Technique.h
static Technique* Technique_Technique_Context()
{
    return new Technique(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Technique_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Technique* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit Terrain::Terrain(Context* context) | File: ../Graphics/Terrain.h
static Terrain* Terrain_Terrain_Context()
{
    return new Terrain(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Terrain_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Terrain* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
static CScriptArray* TerrainPatch_GetLights_void(TerrainPatch* ptr)
{
    const PODVector<Light*>& result = ptr->GetLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
static CScriptArray* TerrainPatch_GetVertexLights_void(TerrainPatch* ptr)
{
    const PODVector<Light*>& result = ptr->GetVertexLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// explicit TerrainPatch::TerrainPatch(Context* context) | File: ../Graphics/TerrainPatch.h
static TerrainPatch* TerrainPatch_TerrainPatch_Context()
{
    return new TerrainPatch(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void TerrainPatch_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(TerrainPatch* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
static void Text_AddTags_StringVector(Text* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->AddTags(tags);
}

// const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
static CScriptArray* Text_GetChildren_void(Text* ptr)
{
    const Vector<SharedPtr<UIElement>>& result = ptr->GetChildren();
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
static CScriptArray* Text_GetChildren_bool(Text* ptr, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildren(recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
static CScriptArray* Text_GetChildrenWithTag_String_bool(Text* ptr, const String& tag, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildrenWithTag(tag, recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
static CScriptArray* Text_GetTags_void(Text* ptr)
{
    const StringVector& result = ptr->GetTags();
    return VectorToArray<String>(result, "Array<String>");
}

// void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
static void Text_SetTags_StringVector(Text* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->SetTags(tags);
}

// explicit Text::Text(Context* context) | File: ../UI/Text.h
static Text* Text_Text_Context()
{
    return new Text(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Text_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Text* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
static CScriptArray* Text3D_GetLights_void(Text3D* ptr)
{
    const PODVector<Light*>& result = ptr->GetLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
static CScriptArray* Text3D_GetVertexLights_void(Text3D* ptr)
{
    const PODVector<Light*>& result = ptr->GetVertexLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// explicit Text3D::Text3D(Context* context) | File: ../UI/Text3D.h
static Text3D* Text3D_Text3D_Context()
{
    return new Text3D(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Text3D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Text3D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit Texture::Texture(Context* context) | File: ../Graphics/Texture.h
static Texture* Texture_Texture_Context()
{
    return new Texture(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Texture_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Texture* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// SharedPtr<Image> Texture2D::GetImage() const | File: ../Graphics/Texture2D.h
static Image* Texture2D_GetImage_void(Texture2D* ptr)
{
    SharedPtr<Image> result = ptr->GetImage();
    return result.Detach();
}

// explicit Texture2D::Texture2D(Context* context) | File: ../Graphics/Texture2D.h
static Texture2D* Texture2D_Texture2D_Context()
{
    return new Texture2D(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Texture2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Texture2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit Texture2DArray::Texture2DArray(Context* context) | File: ../Graphics/Texture2DArray.h
static Texture2DArray* Texture2DArray_Texture2DArray_Context()
{
    return new Texture2DArray(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Texture2DArray_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Texture2DArray* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit Texture3D::Texture3D(Context* context) | File: ../Graphics/Texture3D.h
static Texture3D* Texture3D_Texture3D_Context()
{
    return new Texture3D(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Texture3D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Texture3D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// SharedPtr<Image> TextureCube::GetImage(CubeMapFace face) const | File: ../Graphics/TextureCube.h
static Image* TextureCube_GetImage_CubeMapFace(TextureCube* ptr, CubeMapFace face)
{
    SharedPtr<Image> result = ptr->GetImage(face);
    return result.Detach();
}

// explicit TextureCube::TextureCube(Context* context) | File: ../Graphics/TextureCube.h
static TextureCube* TextureCube_TextureCube_Context()
{
    return new TextureCube(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void TextureCube_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(TextureCube* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

#ifdef URHO3D_URHO2D
// Tile2D::Tile2D() | File: ../Urho2D/TileMapDefs2D.h
static Tile2D* Tile2D_Tile2D_void()
{
    return new Tile2D();
}
#endif

#ifdef URHO3D_URHO2D
// Vector<SharedPtr<TileMapObject2D>> TileMap2D::GetTileCollisionShapes(unsigned gid) const | File: ../Urho2D/TileMap2D.h
static CScriptArray* TileMap2D_GetTileCollisionShapes_unsigned(TileMap2D* ptr, unsigned gid)
{
    Vector<SharedPtr<TileMapObject2D>> result = ptr->GetTileCollisionShapes(gid);
    return VectorToHandleArray(result, "Array<TileMapObject2D@>");
}
#endif

#ifdef URHO3D_URHO2D
// explicit TileMap2D::TileMap2D(Context* context) | File: ../Urho2D/TileMap2D.h
static TileMap2D* TileMap2D_TileMap2D_Context()
{
    return new TileMap2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void TileMap2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(TileMap2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_URHO2D
// explicit TileMapLayer2D::TileMapLayer2D(Context* context) | File: ../Urho2D/TileMapLayer2D.h
static TileMapLayer2D* TileMapLayer2D_TileMapLayer2D_Context()
{
    return new TileMapLayer2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void TileMapLayer2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(TileMapLayer2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_URHO2D
// TileMapObject2D::TileMapObject2D() | File: ../Urho2D/TileMapDefs2D.h
static TileMapObject2D* TileMapObject2D_TileMapObject2D_void()
{
    return new TileMapObject2D();
}
#endif

// explicit Time::Time(Context* context) | File: ../Core/Timer.h
static Time* Time_Time_Context()
{
    return new Time(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Time_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Time* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

#ifdef URHO3D_URHO2D
// Vector<SharedPtr<TileMapObject2D>> TmxFile2D::GetTileCollisionShapes(unsigned gid) const | File: ../Urho2D/TmxFile2D.h
static CScriptArray* TmxFile2D_GetTileCollisionShapes_unsigned(TmxFile2D* ptr, unsigned gid)
{
    Vector<SharedPtr<TileMapObject2D>> result = ptr->GetTileCollisionShapes(gid);
    return VectorToHandleArray(result, "Array<TileMapObject2D@>");
}
#endif

#ifdef URHO3D_URHO2D
// explicit TmxFile2D::TmxFile2D(Context* context) | File: ../Urho2D/TmxFile2D.h
static TmxFile2D* TmxFile2D_TmxFile2D_Context()
{
    return new TmxFile2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void TmxFile2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(TmxFile2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_URHO2D
// explicit TmxImageLayer2D::TmxImageLayer2D(TmxFile2D* tmxFile) | File: ../Urho2D/TmxFile2D.h
static TmxImageLayer2D* TmxImageLayer2D_TmxImageLayer2D_TmxFile2D(TmxFile2D *tmxFile)
{
    return new TmxImageLayer2D(tmxFile);
}
#endif

#ifdef URHO3D_URHO2D
// TmxLayer2D::TmxLayer2D(TmxFile2D* tmxFile, TileMapLayerType2D type) | File: ../Urho2D/TmxFile2D.h
static TmxLayer2D* TmxLayer2D_TmxLayer2D_TmxFile2D_TileMapLayerType2D(TmxFile2D *tmxFile, TileMapLayerType2D type)
{
    return new TmxLayer2D(tmxFile, type);
}
#endif

#ifdef URHO3D_URHO2D
// explicit TmxObjectGroup2D::TmxObjectGroup2D(TmxFile2D* tmxFile) | File: ../Urho2D/TmxFile2D.h
static TmxObjectGroup2D* TmxObjectGroup2D_TmxObjectGroup2D_TmxFile2D(TmxFile2D *tmxFile)
{
    return new TmxObjectGroup2D(tmxFile);
}
#endif

#ifdef URHO3D_URHO2D
// explicit TmxTileLayer2D::TmxTileLayer2D(TmxFile2D* tmxFile) | File: ../Urho2D/TmxFile2D.h
static TmxTileLayer2D* TmxTileLayer2D_TmxTileLayer2D_TmxFile2D(TmxFile2D *tmxFile)
{
    return new TmxTileLayer2D(tmxFile);
}
#endif

// TechniqueEntry::TechniqueEntry(Technique* tech, MaterialQuality qualityLevel, float lodDistance) noexcept | File: ../Graphics/Material.h
static void TechniqueEntry_TechniqueEntry_Technique_MaterialQuality_float(TechniqueEntry* ptr, Technique *tech, MaterialQuality qualityLevel, float lodDistance)
{
    new(ptr) TechniqueEntry(tech, qualityLevel, lodDistance);
}

// TextureFrame::TextureFrame() | File: ../Graphics/ParticleEffect.h
static TextureFrame* TextureFrame_TextureFrame_void()
{
    return new TextureFrame();
}

void ASRegisterGenerated_Members_Ta_Tm(asIScriptEngine* engine)
{
    // unsigned Technique::alphaPassIndex | File: ../Graphics/Technique.h
    engine->SetDefaultNamespace("Technique");
    engine->RegisterGlobalProperty("uint alphaPassIndex", (void*)&Technique::alphaPassIndex);
    engine->SetDefaultNamespace("");
    // unsigned Technique::basePassIndex | File: ../Graphics/Technique.h
    engine->SetDefaultNamespace("Technique");
    engine->RegisterGlobalProperty("uint basePassIndex", (void*)&Technique::basePassIndex);
    engine->SetDefaultNamespace("");
    // unsigned Technique::deferredPassIndex | File: ../Graphics/Technique.h
    engine->SetDefaultNamespace("Technique");
    engine->RegisterGlobalProperty("uint deferredPassIndex", (void*)&Technique::deferredPassIndex);
    engine->SetDefaultNamespace("");
    // unsigned Technique::lightPassIndex | File: ../Graphics/Technique.h
    engine->SetDefaultNamespace("Technique");
    engine->RegisterGlobalProperty("uint lightPassIndex", (void*)&Technique::lightPassIndex);
    engine->SetDefaultNamespace("");
    // unsigned Technique::litAlphaPassIndex | File: ../Graphics/Technique.h
    engine->SetDefaultNamespace("Technique");
    engine->RegisterGlobalProperty("uint litAlphaPassIndex", (void*)&Technique::litAlphaPassIndex);
    engine->SetDefaultNamespace("");
    // unsigned Technique::litBasePassIndex | File: ../Graphics/Technique.h
    engine->SetDefaultNamespace("Technique");
    engine->RegisterGlobalProperty("uint litBasePassIndex", (void*)&Technique::litBasePassIndex);
    engine->SetDefaultNamespace("");
    // unsigned Technique::materialPassIndex | File: ../Graphics/Technique.h
    engine->SetDefaultNamespace("Technique");
    engine->RegisterGlobalProperty("uint materialPassIndex", (void*)&Technique::materialPassIndex);
    engine->SetDefaultNamespace("");
    // unsigned Technique::shadowPassIndex | File: ../Graphics/Technique.h
    engine->SetDefaultNamespace("Technique");
    engine->RegisterGlobalProperty("uint shadowPassIndex", (void*)&Technique::shadowPassIndex);
    engine->SetDefaultNamespace("");
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Technique", asBEHAVE_ADDREF, "void f()", asMETHODPR(Technique, AddRef, (), void), asCALL_THISCALL);
    // bool Technique::BeginLoad(Deserializer& source) override | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "bool BeginLoad(Deserializer&)", asMETHODPR(Technique, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // SharedPtr<Technique> Technique::Clone(const String& cloneName=String::EMPTY) const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "Technique@+ Clone(const String&in = String::EMPTY) const", asFUNCTION(Technique_Clone_String), asCALL_CDECL_OBJFIRST);
    // SharedPtr<Technique> Technique::CloneWithDefines(const String& vsDefines, const String& psDefines) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "Technique@+ CloneWithDefines(const String&in, const String&in)", asFUNCTION(Technique_CloneWithDefines_String_String), asCALL_CDECL_OBJFIRST);
    // Pass* Technique::CreatePass(const String& name) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "Pass@+ CreatePass(const String&in)", asMETHODPR(Technique, CreatePass, (const String&), Pass*), asCALL_THISCALL);
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "bool EndLoad()", asMETHODPR(Technique, EndLoad, (), bool), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(Technique, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "bool GetBlockEvents() const", asMETHODPR(Technique, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "const String& GetCategory() const", asMETHODPR(Technique, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "const String& get_category() const", asMETHODPR(Technique, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "VariantMap& GetEventDataMap() const", asMETHODPR(Technique, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "Object@+ GetEventSender() const", asMETHODPR(Technique, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Technique, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Technique, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "const VariantMap& GetGlobalVars() const", asMETHODPR(Technique, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "const VariantMap& get_globalVars() const", asMETHODPR(Technique, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "uint GetMemoryUse() const", asMETHODPR(Technique, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "uint get_memoryUse() const", asMETHODPR(Technique, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "const String& GetName() const", asMETHODPR(Technique, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "const String& get_name() const", asMETHODPR(Technique, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "StringHash GetNameHash() const", asMETHODPR(Technique, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // unsigned Technique::GetNumPasses() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "uint GetNumPasses() const", asMETHODPR(Technique, GetNumPasses, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "uint get_numPasses() const", asMETHODPR(Technique, GetNumPasses, () const, unsigned), asCALL_THISCALL);
    // Pass* Technique::GetPass(unsigned passIndex) const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "Pass@+ GetPass(uint) const", asMETHODPR(Technique, GetPass, (unsigned) const, Pass*), asCALL_THISCALL);
    // Pass* Technique::GetPass(const String& name) const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "Pass@+ GetPass(const String&in) const", asMETHODPR(Technique, GetPass, (const String&) const, Pass*), asCALL_THISCALL);
    // PODVector<Pass*> Technique::GetPasses() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "Array<Pass@>@ GetPasses() const", asFUNCTION(Technique_GetPasses_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Technique", "Array<Pass@>@ get_passes() const", asFUNCTION(Technique_GetPasses_void), asCALL_CDECL_OBJFIRST);
    // static unsigned Technique::GetPassIndex(const String& passName) | File: ../Graphics/Technique.h
    engine->SetDefaultNamespace("Technique");
    engine->RegisterGlobalFunction("uint GetPassIndex(const String&in)", asFUNCTIONPR(Technique::GetPassIndex, (const String&), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // Vector<String> Technique::GetPassNames() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "Array<String>@ GetPassNames() const", asFUNCTION(Technique_GetPassNames_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Technique", "Array<String>@ get_passNames() const", asFUNCTION(Technique_GetPassNames_void), asCALL_CDECL_OBJFIRST);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Technique, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // Pass* Technique::GetSupportedPass(unsigned passIndex) const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "Pass@+ GetSupportedPass(uint) const", asMETHODPR(Technique, GetSupportedPass, (unsigned) const, Pass*), asCALL_THISCALL);
    // Pass* Technique::GetSupportedPass(const String& name) const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "Pass@+ GetSupportedPass(const String&in) const", asMETHODPR(Technique, GetSupportedPass, (const String&) const, Pass*), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "StringHash GetType() const", asMETHODPR(Technique, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "StringHash get_type() const", asMETHODPR(Technique, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "const String& GetTypeName() const", asMETHODPR(Technique, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "const String& get_typeName() const", asMETHODPR(Technique, GetTypeName, () const, const String&), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "uint GetUseTimer()", asMETHODPR(Technique, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "uint get_useTimer()", asMETHODPR(Technique, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "bool HasEventHandlers() const", asMETHODPR(Technique, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Technique::HasPass(unsigned passIndex) const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "bool HasPass(uint) const", asMETHODPR(Technique, HasPass, (unsigned) const, bool), asCALL_THISCALL);
    // bool Technique::HasPass(const String& name) const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "bool HasPass(const String&in) const", asMETHODPR(Technique, HasPass, (const String&) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Technique, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Technique, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Technique::IsDesktop() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "bool IsDesktop() const", asMETHODPR(Technique, IsDesktop, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "bool get_desktop() const", asMETHODPR(Technique, IsDesktop, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "bool IsInstanceOf(StringHash) const", asMETHODPR(Technique, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Technique::IsSupported() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "bool IsSupported() const", asMETHODPR(Technique, IsSupported, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "bool get_supported() const", asMETHODPR(Technique, IsSupported, () const, bool), asCALL_THISCALL);
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "bool Load(Deserializer&)", asMETHODPR(Technique, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "bool LoadFile(const String&in)", asMETHODPR(Technique, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "bool Load(const String&in)", asMETHODPR(Technique, LoadFile, (const String&), bool), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Technique, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Technique", "int Refs() const", asMETHODPR(Technique, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "int get_refs() const", asMETHODPR(Technique, Refs, () const, int), asCALL_THISCALL);
    // static void Technique::RegisterObject(Context* context) | File: ../Graphics/Technique.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Technique", asBEHAVE_RELEASE, "void f()", asMETHODPR(Technique, ReleaseRef, (), void), asCALL_THISCALL);
    // void Technique::ReleaseShaders() | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "void ReleaseShaders()", asMETHODPR(Technique, ReleaseShaders, (), void), asCALL_THISCALL);
    // void Technique::RemovePass(const String& name) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "void RemovePass(const String&in)", asMETHODPR(Technique, RemovePass, (const String&), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "void ResetUseTimer()", asMETHODPR(Technique, ResetUseTimer, (), void), asCALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "bool Save(Serializer&) const", asMETHODPR(Technique, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "bool SaveFile(const String&in) const", asMETHODPR(Technique, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "bool Save(const String&in) const", asMETHODPR(Technique, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "void SendEvent(StringHash)", asMETHODPR(Technique, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Technique, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(Technique, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "void SetBlockEvents(bool)", asMETHODPR(Technique, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Technique, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Technique, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Technique::SetIsDesktop(bool enable) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "void SetIsDesktop(bool)", asMETHODPR(Technique, SetIsDesktop, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "void set_desktop(bool)", asMETHODPR(Technique, SetIsDesktop, (bool), void), asCALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "void SetMemoryUse(uint)", asMETHODPR(Technique, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "void SetName(const String&in)", asMETHODPR(Technique, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "void set_name(const String&in)", asMETHODPR(Technique, SetName, (const String&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit Technique::Technique(Context* context) | File: ../Graphics/Technique.h
    engine->RegisterObjectBehaviour("Technique", asBEHAVE_FACTORY, "Technique@+ f()", asFUNCTION(Technique_Technique_Context), asCALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "void UnsubscribeFromAllEvents()", asMETHODPR(Technique, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Technique_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Technique, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Technique, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Technique, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Technique", "int WeakRefs() const", asMETHODPR(Technique, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "int get_weakRefs() const", asMETHODPR(Technique, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(Technique, "Technique")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Technique, "Technique")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Technique, "Technique")
#endif
#ifdef REGISTER_MANUAL_PART_Technique
    REGISTER_MANUAL_PART_Technique(Technique, "Technique")
#endif
    RegisterSubclass<Resource, Technique>(engine, "Resource", "Technique");
    RegisterSubclass<Object, Technique>(engine, "Object", "Technique");
    RegisterSubclass<RefCounted, Technique>(engine, "RefCounted", "Technique");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Terrain", asBEHAVE_ADDREF, "void f()", asMETHODPR(Terrain, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "void AllocateNetworkState()", asMETHODPR(Terrain, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void Terrain::ApplyAttributes() override | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void ApplyAttributes()", asMETHODPR(Terrain, ApplyAttributes, (), void), asCALL_THISCALL);
    // void Terrain::ApplyHeightMap() | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void ApplyHeightMap()", asMETHODPR(Terrain, ApplyHeightMap, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Terrain::CreatePatchGeometry(TerrainPatch* patch) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void CreatePatchGeometry(TerrainPatch@+)", asMETHODPR(Terrain, CreatePatchGeometry, (TerrainPatch*), void), asCALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(Terrain, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "bool GetAnimationEnabled() const", asMETHODPR(Terrain, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool get_animationEnabled() const", asMETHODPR(Terrain, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "Variant GetAttribute(uint) const", asMETHODPR(Terrain, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "Variant get_attributes(uint) const", asMETHODPR(Terrain, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "Variant GetAttribute(const String&in) const", asMETHODPR(Terrain, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(Terrain, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(Terrain, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(Terrain, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(Terrain, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "Variant GetAttributeDefault(uint) const", asMETHODPR(Terrain, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "Variant get_attributeDefaults(uint) const", asMETHODPR(Terrain, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Terrain, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "bool GetBlockEvents() const", asMETHODPR(Terrain, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // bool Terrain::GetCastShadows() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "bool GetCastShadows() const", asMETHODPR(Terrain, GetCastShadows, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool get_castShadows() const", asMETHODPR(Terrain, GetCastShadows, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "const String& GetCategory() const", asMETHODPR(Terrain, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "const String& get_category() const", asMETHODPR(Terrain, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "Component@+ GetComponent(StringHash) const", asMETHODPR(Terrain, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // float Terrain::GetDrawDistance() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "float GetDrawDistance() const", asMETHODPR(Terrain, GetDrawDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "float get_drawDistance() const", asMETHODPR(Terrain, GetDrawDistance, () const, float), asCALL_THISCALL);
    // Terrain* Terrain::GetEastNeighbor() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "Terrain@+ GetEastNeighbor() const", asMETHODPR(Terrain, GetEastNeighbor, () const, Terrain*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "Terrain@+ get_eastNeighbor() const", asMETHODPR(Terrain, GetEastNeighbor, () const, Terrain*), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "VariantMap& GetEventDataMap() const", asMETHODPR(Terrain, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "Object@+ GetEventSender() const", asMETHODPR(Terrain, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Terrain, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Terrain, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "const VariantMap& GetGlobalVars() const", asMETHODPR(Terrain, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "const VariantMap& get_globalVars() const", asMETHODPR(Terrain, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // float Terrain::GetHeight(const Vector3& worldPosition) const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "float GetHeight(const Vector3&in) const", asMETHODPR(Terrain, GetHeight, (const Vector3&) const, float), asCALL_THISCALL);
    // SharedArrayPtr<float> Terrain::GetHeightData() const | File: ../Graphics/Terrain.h
    // Error: type "SharedArrayPtr<float>" can not automatically bind
    // Image* Terrain::GetHeightMap() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "Image@+ GetHeightMap() const", asMETHODPR(Terrain, GetHeightMap, () const, Image*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "Image@+ get_heightMap() const", asMETHODPR(Terrain, GetHeightMap, () const, Image*), asCALL_THISCALL);
    // ResourceRef Terrain::GetHeightMapAttr() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "ResourceRef GetHeightMapAttr() const", asMETHODPR(Terrain, GetHeightMapAttr, () const, ResourceRef), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "uint GetID() const", asMETHODPR(Terrain, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "uint get_id() const", asMETHODPR(Terrain, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Terrain, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // unsigned Terrain::GetLightMask() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "uint GetLightMask() const", asMETHODPR(Terrain, GetLightMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "uint get_lightMask() const", asMETHODPR(Terrain, GetLightMask, () const, unsigned), asCALL_THISCALL);
    // float Terrain::GetLodBias() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "float GetLodBias() const", asMETHODPR(Terrain, GetLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "float get_lodBias() const", asMETHODPR(Terrain, GetLodBias, () const, float), asCALL_THISCALL);
    // Material* Terrain::GetMaterial() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "Material@+ GetMaterial() const", asMETHODPR(Terrain, GetMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "Material@+ get_material() const", asMETHODPR(Terrain, GetMaterial, () const, Material*), asCALL_THISCALL);
    // ResourceRef Terrain::GetMaterialAttr() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "ResourceRef GetMaterialAttr() const", asMETHODPR(Terrain, GetMaterialAttr, () const, ResourceRef), asCALL_THISCALL);
    // unsigned Terrain::GetMaxLights() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "uint GetMaxLights() const", asMETHODPR(Terrain, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "uint get_maxLights() const", asMETHODPR(Terrain, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    // unsigned Terrain::GetMaxLodLevels() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "uint GetMaxLodLevels() const", asMETHODPR(Terrain, GetMaxLodLevels, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "uint get_maxLodLevels() const", asMETHODPR(Terrain, GetMaxLodLevels, () const, unsigned), asCALL_THISCALL);
    // TerrainPatch* Terrain::GetNeighborPatch(int x, int z) const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "TerrainPatch@+ GetNeighborPatch(int, int) const", asMETHODPR(Terrain, GetNeighborPatch, (int, int) const, TerrainPatch*), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "Node@+ GetNode() const", asMETHODPR(Terrain, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "Node@+ get_node() const", asMETHODPR(Terrain, GetNode, () const, Node*), asCALL_THISCALL);
    // Vector3 Terrain::GetNormal(const Vector3& worldPosition) const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "Vector3 GetNormal(const Vector3&in) const", asMETHODPR(Terrain, GetNormal, (const Vector3&) const, Vector3), asCALL_THISCALL);
    // Terrain* Terrain::GetNorthNeighbor() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "Terrain@+ GetNorthNeighbor() const", asMETHODPR(Terrain, GetNorthNeighbor, () const, Terrain*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "Terrain@+ get_northNeighbor() const", asMETHODPR(Terrain, GetNorthNeighbor, () const, Terrain*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "uint GetNumAttributes() const", asMETHODPR(Terrain, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "uint get_numAttributes() const", asMETHODPR(Terrain, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "uint GetNumNetworkAttributes() const", asMETHODPR(Terrain, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // const IntVector2& Terrain::GetNumPatches() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "const IntVector2& GetNumPatches() const", asMETHODPR(Terrain, GetNumPatches, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "const IntVector2& get_numPatches() const", asMETHODPR(Terrain, GetNumPatches, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& Terrain::GetNumVertices() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "const IntVector2& GetNumVertices() const", asMETHODPR(Terrain, GetNumVertices, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "const IntVector2& get_numVertices() const", asMETHODPR(Terrain, GetNumVertices, () const, const IntVector2&), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(Terrain, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(Terrain, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(Terrain, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // unsigned Terrain::GetOcclusionLodLevel() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "uint GetOcclusionLodLevel() const", asMETHODPR(Terrain, GetOcclusionLodLevel, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "uint get_occlusionLodLevel() const", asMETHODPR(Terrain, GetOcclusionLodLevel, () const, unsigned), asCALL_THISCALL);
    // TerrainPatch* Terrain::GetPatch(unsigned index) const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "TerrainPatch@+ GetPatch(uint) const", asMETHODPR(Terrain, GetPatch, (unsigned) const, TerrainPatch*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "TerrainPatch@+ get_patches(uint) const", asMETHODPR(Terrain, GetPatch, (unsigned) const, TerrainPatch*), asCALL_THISCALL);
    // TerrainPatch* Terrain::GetPatch(int x, int z) const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "TerrainPatch@+ GetPatch(int, int) const", asMETHODPR(Terrain, GetPatch, (int, int) const, TerrainPatch*), asCALL_THISCALL);
    // int Terrain::GetPatchSize() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "int GetPatchSize() const", asMETHODPR(Terrain, GetPatchSize, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "int get_patchSize() const", asMETHODPR(Terrain, GetPatchSize, () const, int), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "Scene@+ GetScene() const", asMETHODPR(Terrain, GetScene, () const, Scene*), asCALL_THISCALL);
    // float Terrain::GetShadowDistance() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "float GetShadowDistance() const", asMETHODPR(Terrain, GetShadowDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "float get_shadowDistance() const", asMETHODPR(Terrain, GetShadowDistance, () const, float), asCALL_THISCALL);
    // unsigned Terrain::GetShadowMask() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "uint GetShadowMask() const", asMETHODPR(Terrain, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "uint get_shadowMask() const", asMETHODPR(Terrain, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    // bool Terrain::GetSmoothing() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "bool GetSmoothing() const", asMETHODPR(Terrain, GetSmoothing, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool get_smoothing() const", asMETHODPR(Terrain, GetSmoothing, () const, bool), asCALL_THISCALL);
    // Terrain* Terrain::GetSouthNeighbor() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "Terrain@+ GetSouthNeighbor() const", asMETHODPR(Terrain, GetSouthNeighbor, () const, Terrain*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "Terrain@+ get_southNeighbor() const", asMETHODPR(Terrain, GetSouthNeighbor, () const, Terrain*), asCALL_THISCALL);
    // const Vector3& Terrain::GetSpacing() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "const Vector3& GetSpacing() const", asMETHODPR(Terrain, GetSpacing, () const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "const Vector3& get_spacing() const", asMETHODPR(Terrain, GetSpacing, () const, const Vector3&), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Terrain, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "StringHash GetType() const", asMETHODPR(Terrain, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "StringHash get_type() const", asMETHODPR(Terrain, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "const String& GetTypeName() const", asMETHODPR(Terrain, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "const String& get_typeName() const", asMETHODPR(Terrain, GetTypeName, () const, const String&), asCALL_THISCALL);
    // unsigned Terrain::GetViewMask() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "uint GetViewMask() const", asMETHODPR(Terrain, GetViewMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "uint get_viewMask() const", asMETHODPR(Terrain, GetViewMask, () const, unsigned), asCALL_THISCALL);
    // Terrain* Terrain::GetWestNeighbor() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "Terrain@+ GetWestNeighbor() const", asMETHODPR(Terrain, GetWestNeighbor, () const, Terrain*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "Terrain@+ get_westNeighbor() const", asMETHODPR(Terrain, GetWestNeighbor, () const, Terrain*), asCALL_THISCALL);
    // unsigned Terrain::GetZoneMask() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "uint GetZoneMask() const", asMETHODPR(Terrain, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "uint get_zoneMask() const", asMETHODPR(Terrain, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "bool HasEventHandlers() const", asMETHODPR(Terrain, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Terrain, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Terrain, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // Vector3 Terrain::HeightMapToWorld(const IntVector2& pixelPosition) const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "Vector3 HeightMapToWorld(const IntVector2&in) const", asMETHODPR(Terrain, HeightMapToWorld, (const IntVector2&) const, Vector3), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "bool IsEnabled() const", asMETHODPR(Terrain, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool get_enabled() const", asMETHODPR(Terrain, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "bool IsEnabledEffective() const", asMETHODPR(Terrain, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool get_enabledEffective() const", asMETHODPR(Terrain, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "bool IsInstanceOf(StringHash) const", asMETHODPR(Terrain, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Terrain::IsOccludee() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "bool IsOccludee() const", asMETHODPR(Terrain, IsOccludee, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool get_occludee() const", asMETHODPR(Terrain, IsOccludee, () const, bool), asCALL_THISCALL);
    // bool Terrain::IsOccluder() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "bool IsOccluder() const", asMETHODPR(Terrain, IsOccluder, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool get_occluder() const", asMETHODPR(Terrain, IsOccluder, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "bool IsReplicated() const", asMETHODPR(Terrain, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool get_replicated() const", asMETHODPR(Terrain, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "bool IsTemporary() const", asMETHODPR(Terrain, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool get_temporary() const", asMETHODPR(Terrain, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool Terrain::IsVisible() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "bool IsVisible() const", asMETHODPR(Terrain, IsVisible, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "bool Load(Deserializer&)", asMETHODPR(Terrain, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Terrain, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "bool LoadXML(const XMLElement&in)", asMETHODPR(Terrain, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "void MarkNetworkUpdate()", asMETHODPR(Terrain, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Terrain, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Terrain, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Terrain, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Terrain::OnSetEnabled() override | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void OnSetEnabled()", asMETHODPR(Terrain, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "void PrepareNetworkUpdate()", asMETHODPR(Terrain, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Terrain, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Terrain, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Terrain", "int Refs() const", asMETHODPR(Terrain, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "int get_refs() const", asMETHODPR(Terrain, Refs, () const, int), asCALL_THISCALL);
    // static void Terrain::RegisterObject(Context* context) | File: ../Graphics/Terrain.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Terrain", asBEHAVE_RELEASE, "void f()", asMETHODPR(Terrain, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "void Remove()", asMETHODPR(Terrain, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(Terrain, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "void RemoveInstanceDefault()", asMETHODPR(Terrain, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "void RemoveObjectAnimation()", asMETHODPR(Terrain, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "void ResetToDefault()", asMETHODPR(Terrain, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "bool Save(Serializer&) const", asMETHODPR(Terrain, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "bool SaveDefaultAttributes() const", asMETHODPR(Terrain, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "bool SaveJSON(JSONValue&) const", asMETHODPR(Terrain, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "bool SaveXML(XMLElement&) const", asMETHODPR(Terrain, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "void SendEvent(StringHash)", asMETHODPR(Terrain, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Terrain, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "void SetAnimationEnabled(bool)", asMETHODPR(Terrain, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_animationEnabled(bool)", asMETHODPR(Terrain, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "void SetAnimationTime(float)", asMETHODPR(Terrain, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Terrain, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Terrain, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Terrain, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Terrain, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(Terrain, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(Terrain, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Terrain, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "void SetBlockEvents(bool)", asMETHODPR(Terrain, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Terrain::SetCastShadows(bool enable) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetCastShadows(bool)", asMETHODPR(Terrain, SetCastShadows, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_castShadows(bool)", asMETHODPR(Terrain, SetCastShadows, (bool), void), asCALL_THISCALL);
    // void Terrain::SetDrawDistance(float distance) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetDrawDistance(float)", asMETHODPR(Terrain, SetDrawDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_drawDistance(float)", asMETHODPR(Terrain, SetDrawDistance, (float), void), asCALL_THISCALL);
    // void Terrain::SetEastNeighbor(Terrain* east) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetEastNeighbor(Terrain@+)", asMETHODPR(Terrain, SetEastNeighbor, (Terrain*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_eastNeighbor(Terrain@+)", asMETHODPR(Terrain, SetEastNeighbor, (Terrain*), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "void SetEnabled(bool)", asMETHODPR(Terrain, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_enabled(bool)", asMETHODPR(Terrain, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Terrain, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Terrain, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // bool Terrain::SetHeightMap(Image* image) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "bool SetHeightMap(Image@+)", asMETHODPR(Terrain, SetHeightMap, (Image*), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool set_heightMap(Image@+)", asMETHODPR(Terrain, SetHeightMap, (Image*), bool), asCALL_THISCALL);
    // void Terrain::SetHeightMapAttr(const ResourceRef& value) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetHeightMapAttr(const ResourceRef&in)", asMETHODPR(Terrain, SetHeightMapAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "void SetInstanceDefault(bool)", asMETHODPR(Terrain, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Terrain, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Terrain::SetLightMask(unsigned mask) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetLightMask(uint)", asMETHODPR(Terrain, SetLightMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_lightMask(uint)", asMETHODPR(Terrain, SetLightMask, (unsigned), void), asCALL_THISCALL);
    // void Terrain::SetLodBias(float bias) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetLodBias(float)", asMETHODPR(Terrain, SetLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_lodBias(float)", asMETHODPR(Terrain, SetLodBias, (float), void), asCALL_THISCALL);
    // void Terrain::SetMaterial(Material* material) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetMaterial(Material@+)", asMETHODPR(Terrain, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_material(Material@+)", asMETHODPR(Terrain, SetMaterial, (Material*), void), asCALL_THISCALL);
    // void Terrain::SetMaterialAttr(const ResourceRef& value) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetMaterialAttr(const ResourceRef&in)", asMETHODPR(Terrain, SetMaterialAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Terrain::SetMaxLights(unsigned num) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetMaxLights(uint)", asMETHODPR(Terrain, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_maxLights(uint)", asMETHODPR(Terrain, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    // void Terrain::SetMaxLodLevels(unsigned levels) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetMaxLodLevels(uint)", asMETHODPR(Terrain, SetMaxLodLevels, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_maxLodLevels(uint)", asMETHODPR(Terrain, SetMaxLodLevels, (unsigned), void), asCALL_THISCALL);
    // void Terrain::SetMaxLodLevelsAttr(unsigned value) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetMaxLodLevelsAttr(uint)", asMETHODPR(Terrain, SetMaxLodLevelsAttr, (unsigned), void), asCALL_THISCALL);
    // void Terrain::SetNeighbors(Terrain* north, Terrain* south, Terrain* west, Terrain* east) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetNeighbors(Terrain@+, Terrain@+, Terrain@+, Terrain@+)", asMETHODPR(Terrain, SetNeighbors, (Terrain*, Terrain*, Terrain*, Terrain*), void), asCALL_THISCALL);
    // void Terrain::SetNorthNeighbor(Terrain* north) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetNorthNeighbor(Terrain@+)", asMETHODPR(Terrain, SetNorthNeighbor, (Terrain*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_northNeighbor(Terrain@+)", asMETHODPR(Terrain, SetNorthNeighbor, (Terrain*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(Terrain, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(Terrain, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(Terrain, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Terrain::SetOccludee(bool enable) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetOccludee(bool)", asMETHODPR(Terrain, SetOccludee, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_occludee(bool)", asMETHODPR(Terrain, SetOccludee, (bool), void), asCALL_THISCALL);
    // void Terrain::SetOccluder(bool enable) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetOccluder(bool)", asMETHODPR(Terrain, SetOccluder, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_occluder(bool)", asMETHODPR(Terrain, SetOccluder, (bool), void), asCALL_THISCALL);
    // void Terrain::SetOcclusionLodLevel(unsigned level) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetOcclusionLodLevel(uint)", asMETHODPR(Terrain, SetOcclusionLodLevel, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_occlusionLodLevel(uint)", asMETHODPR(Terrain, SetOcclusionLodLevel, (unsigned), void), asCALL_THISCALL);
    // void Terrain::SetOcclusionLodLevelAttr(unsigned value) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetOcclusionLodLevelAttr(uint)", asMETHODPR(Terrain, SetOcclusionLodLevelAttr, (unsigned), void), asCALL_THISCALL);
    // void Terrain::SetPatchSize(int size) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetPatchSize(int)", asMETHODPR(Terrain, SetPatchSize, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_patchSize(int)", asMETHODPR(Terrain, SetPatchSize, (int), void), asCALL_THISCALL);
    // void Terrain::SetPatchSizeAttr(int value) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetPatchSizeAttr(int)", asMETHODPR(Terrain, SetPatchSizeAttr, (int), void), asCALL_THISCALL);
    // void Terrain::SetShadowDistance(float distance) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetShadowDistance(float)", asMETHODPR(Terrain, SetShadowDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_shadowDistance(float)", asMETHODPR(Terrain, SetShadowDistance, (float), void), asCALL_THISCALL);
    // void Terrain::SetShadowMask(unsigned mask) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetShadowMask(uint)", asMETHODPR(Terrain, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_shadowMask(uint)", asMETHODPR(Terrain, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    // void Terrain::SetSmoothing(bool enable) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetSmoothing(bool)", asMETHODPR(Terrain, SetSmoothing, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_smoothing(bool)", asMETHODPR(Terrain, SetSmoothing, (bool), void), asCALL_THISCALL);
    // void Terrain::SetSouthNeighbor(Terrain* south) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetSouthNeighbor(Terrain@+)", asMETHODPR(Terrain, SetSouthNeighbor, (Terrain*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_southNeighbor(Terrain@+)", asMETHODPR(Terrain, SetSouthNeighbor, (Terrain*), void), asCALL_THISCALL);
    // void Terrain::SetSpacing(const Vector3& spacing) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetSpacing(const Vector3&in)", asMETHODPR(Terrain, SetSpacing, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_spacing(const Vector3&in)", asMETHODPR(Terrain, SetSpacing, (const Vector3&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "void SetTemporary(bool)", asMETHODPR(Terrain, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_temporary(bool)", asMETHODPR(Terrain, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Terrain::SetViewMask(unsigned mask) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetViewMask(uint)", asMETHODPR(Terrain, SetViewMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_viewMask(uint)", asMETHODPR(Terrain, SetViewMask, (unsigned), void), asCALL_THISCALL);
    // void Terrain::SetWestNeighbor(Terrain* west) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetWestNeighbor(Terrain@+)", asMETHODPR(Terrain, SetWestNeighbor, (Terrain*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_westNeighbor(Terrain@+)", asMETHODPR(Terrain, SetWestNeighbor, (Terrain*), void), asCALL_THISCALL);
    // void Terrain::SetZoneMask(unsigned mask) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetZoneMask(uint)", asMETHODPR(Terrain, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_zoneMask(uint)", asMETHODPR(Terrain, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit Terrain::Terrain(Context* context) | File: ../Graphics/Terrain.h
    engine->RegisterObjectBehaviour("Terrain", asBEHAVE_FACTORY, "Terrain@+ f()", asFUNCTION(Terrain_Terrain_Context), asCALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "void UnsubscribeFromAllEvents()", asMETHODPR(Terrain, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Terrain_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Terrain, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Terrain, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Terrain, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void Terrain::UpdatePatchLod(TerrainPatch* patch) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void UpdatePatchLod(TerrainPatch@+)", asMETHODPR(Terrain, UpdatePatchLod, (TerrainPatch*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Terrain", "int WeakRefs() const", asMETHODPR(Terrain, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "int get_weakRefs() const", asMETHODPR(Terrain, WeakRefs, () const, int), asCALL_THISCALL);
    // IntVector2 Terrain::WorldToHeightMap(const Vector3& worldPosition) const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "IntVector2 WorldToHeightMap(const Vector3&in) const", asMETHODPR(Terrain, WorldToHeightMap, (const Vector3&) const, IntVector2), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Terrain, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Terrain, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Terrain, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(Terrain, "Terrain")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(Terrain, "Terrain")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Terrain, "Terrain")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Terrain, "Terrain")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Terrain, "Terrain")
#endif
#ifdef REGISTER_MANUAL_PART_Terrain
    REGISTER_MANUAL_PART_Terrain(Terrain, "Terrain")
#endif
    RegisterSubclass<Component, Terrain>(engine, "Component", "Terrain");
    RegisterSubclass<Animatable, Terrain>(engine, "Animatable", "Terrain");
    RegisterSubclass<Serializable, Terrain>(engine, "Serializable", "Terrain");
    RegisterSubclass<Object, Terrain>(engine, "Object", "Terrain");
    RegisterSubclass<RefCounted, Terrain>(engine, "RefCounted", "Terrain");

    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void AddLight(Light@+)", asMETHODPR(TerrainPatch, AddLight, (Light*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TerrainPatch", asBEHAVE_ADDREF, "void f()", asMETHODPR(TerrainPatch, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void AddVertexLight(Light@+)", asMETHODPR(TerrainPatch, AddVertexLight, (Light*), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "void AllocateNetworkState()", asMETHODPR(TerrainPatch, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "void ApplyAttributes()", asMETHODPR(TerrainPatch, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void TerrainPatch::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(TerrainPatch, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool TerrainPatch::DrawOcclusion(OcclusionBuffer* buffer) override | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "bool DrawOcclusion(OcclusionBuffer@+)", asMETHODPR(TerrainPatch, DrawOcclusion, (OcclusionBuffer*), bool), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool GetAnimationEnabled() const", asMETHODPR(TerrainPatch, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "bool get_animationEnabled() const", asMETHODPR(TerrainPatch, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "Variant GetAttribute(uint) const", asMETHODPR(TerrainPatch, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "Variant get_attributes(uint) const", asMETHODPR(TerrainPatch, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "Variant GetAttribute(const String&in) const", asMETHODPR(TerrainPatch, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(TerrainPatch, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(TerrainPatch, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(TerrainPatch, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(TerrainPatch, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "Variant GetAttributeDefault(uint) const", asMETHODPR(TerrainPatch, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "Variant get_attributeDefaults(uint) const", asMETHODPR(TerrainPatch, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(TerrainPatch, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "bool GetBlockEvents() const", asMETHODPR(TerrainPatch, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "const BoundingBox& GetBoundingBox() const", asMETHODPR(TerrainPatch, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "const BoundingBox& get_boundingBox() const", asMETHODPR(TerrainPatch, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool GetCastShadows() const", asMETHODPR(TerrainPatch, GetCastShadows, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "bool get_castShadows() const", asMETHODPR(TerrainPatch, GetCastShadows, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "const String& GetCategory() const", asMETHODPR(TerrainPatch, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "const String& get_category() const", asMETHODPR(TerrainPatch, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "Component@+ GetComponent(StringHash) const", asMETHODPR(TerrainPatch, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // const IntVector2& TerrainPatch::GetCoordinates() const | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "const IntVector2& GetCoordinates() const", asMETHODPR(TerrainPatch, GetCoordinates, () const, const IntVector2&), asCALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // float Drawable::GetDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "float GetDistance() const", asMETHODPR(TerrainPatch, GetDistance, () const, float), asCALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "uint8 GetDrawableFlags() const", asMETHODPR(TerrainPatch, GetDrawableFlags, () const, unsigned char), asCALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "float GetDrawDistance() const", asMETHODPR(TerrainPatch, GetDrawDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "float get_drawDistance() const", asMETHODPR(TerrainPatch, GetDrawDistance, () const, float), asCALL_THISCALL);
    // TerrainPatch* TerrainPatch::GetEastPatch() const | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "TerrainPatch@+ GetEastPatch() const", asMETHODPR(TerrainPatch, GetEastPatch, () const, TerrainPatch*), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "VariantMap& GetEventDataMap() const", asMETHODPR(TerrainPatch, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "Object@+ GetEventSender() const", asMETHODPR(TerrainPatch, GetEventSender, () const, Object*), asCALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "Light@+ GetFirstLight() const", asMETHODPR(TerrainPatch, GetFirstLight, () const, Light*), asCALL_THISCALL);
    // Geometry* TerrainPatch::GetGeometry() const | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "Geometry@+ GetGeometry() const", asMETHODPR(TerrainPatch, GetGeometry, () const, Geometry*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(TerrainPatch, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "const Variant& get_globalVar(StringHash) const", asMETHODPR(TerrainPatch, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "const VariantMap& GetGlobalVars() const", asMETHODPR(TerrainPatch, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "const VariantMap& get_globalVars() const", asMETHODPR(TerrainPatch, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "uint GetID() const", asMETHODPR(TerrainPatch, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "uint get_id() const", asMETHODPR(TerrainPatch, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(TerrainPatch, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "uint GetLightMask() const", asMETHODPR(TerrainPatch, GetLightMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "uint get_lightMask() const", asMETHODPR(TerrainPatch, GetLightMask, () const, unsigned), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "Array<Light@>@ GetLights() const", asFUNCTION(TerrainPatch_GetLights_void), asCALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "float GetLodBias() const", asMETHODPR(TerrainPatch, GetLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "float get_lodBias() const", asMETHODPR(TerrainPatch, GetLodBias, () const, float), asCALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "float GetLodDistance() const", asMETHODPR(TerrainPatch, GetLodDistance, () const, float), asCALL_THISCALL);
    // PODVector<float>& TerrainPatch::GetLodErrors() | File: ../Graphics/TerrainPatch.h
    // Error: type "PODVector<float>&" can not automatically bind
    // Geometry* TerrainPatch::GetLodGeometry(unsigned batchIndex, unsigned level) override | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "Geometry@+ GetLodGeometry(uint, uint)", asMETHODPR(TerrainPatch, GetLodGeometry, (unsigned, unsigned), Geometry*), asCALL_THISCALL);
    // unsigned TerrainPatch::GetLodLevel() const | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "uint GetLodLevel() const", asMETHODPR(TerrainPatch, GetLodLevel, () const, unsigned), asCALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "uint GetMaxLights() const", asMETHODPR(TerrainPatch, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "uint get_maxLights() const", asMETHODPR(TerrainPatch, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    // Geometry* TerrainPatch::GetMaxLodGeometry() const | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "Geometry@+ GetMaxLodGeometry() const", asMETHODPR(TerrainPatch, GetMaxLodGeometry, () const, Geometry*), asCALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "float GetMaxZ() const", asMETHODPR(TerrainPatch, GetMaxZ, () const, float), asCALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "float GetMinZ() const", asMETHODPR(TerrainPatch, GetMinZ, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "Node@+ GetNode() const", asMETHODPR(TerrainPatch, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "Node@+ get_node() const", asMETHODPR(TerrainPatch, GetNode, () const, Node*), asCALL_THISCALL);
    // TerrainPatch* TerrainPatch::GetNorthPatch() const | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "TerrainPatch@+ GetNorthPatch() const", asMETHODPR(TerrainPatch, GetNorthPatch, () const, TerrainPatch*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "uint GetNumAttributes() const", asMETHODPR(TerrainPatch, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "uint get_numAttributes() const", asMETHODPR(TerrainPatch, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "uint GetNumNetworkAttributes() const", asMETHODPR(TerrainPatch, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned TerrainPatch::GetNumOccluderTriangles() override | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "uint GetNumOccluderTriangles()", asMETHODPR(TerrainPatch, GetNumOccluderTriangles, (), unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(TerrainPatch, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(TerrainPatch, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(TerrainPatch, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Geometry* TerrainPatch::GetOcclusionGeometry() const | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "Geometry@+ GetOcclusionGeometry() const", asMETHODPR(TerrainPatch, GetOcclusionGeometry, () const, Geometry*), asCALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // Terrain* TerrainPatch::GetOwner() const | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "Terrain@+ GetOwner() const", asMETHODPR(TerrainPatch, GetOwner, () const, Terrain*), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "Scene@+ GetScene() const", asMETHODPR(TerrainPatch, GetScene, () const, Scene*), asCALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "float GetShadowDistance() const", asMETHODPR(TerrainPatch, GetShadowDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "float get_shadowDistance() const", asMETHODPR(TerrainPatch, GetShadowDistance, () const, float), asCALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "uint GetShadowMask() const", asMETHODPR(TerrainPatch, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "uint get_shadowMask() const", asMETHODPR(TerrainPatch, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "float GetSortValue() const", asMETHODPR(TerrainPatch, GetSortValue, () const, float), asCALL_THISCALL);
    // TerrainPatch* TerrainPatch::GetSouthPatch() const | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "TerrainPatch@+ GetSouthPatch() const", asMETHODPR(TerrainPatch, GetSouthPatch, () const, TerrainPatch*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(TerrainPatch, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "StringHash GetType() const", asMETHODPR(TerrainPatch, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "StringHash get_type() const", asMETHODPR(TerrainPatch, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "const String& GetTypeName() const", asMETHODPR(TerrainPatch, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "const String& get_typeName() const", asMETHODPR(TerrainPatch, GetTypeName, () const, const String&), asCALL_THISCALL);
    // UpdateGeometryType TerrainPatch::GetUpdateGeometryType() override | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "UpdateGeometryType GetUpdateGeometryType()", asMETHODPR(TerrainPatch, GetUpdateGeometryType, (), UpdateGeometryType), asCALL_THISCALL);
    // VertexBuffer* TerrainPatch::GetVertexBuffer() const | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "VertexBuffer@+ GetVertexBuffer() const", asMETHODPR(TerrainPatch, GetVertexBuffer, () const, VertexBuffer*), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "Array<Light@>@ GetVertexLights() const", asFUNCTION(TerrainPatch_GetVertexLights_void), asCALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "uint GetViewMask() const", asMETHODPR(TerrainPatch, GetViewMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "uint get_viewMask() const", asMETHODPR(TerrainPatch, GetViewMask, () const, unsigned), asCALL_THISCALL);
    // TerrainPatch* TerrainPatch::GetWestPatch() const | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "TerrainPatch@+ GetWestPatch() const", asMETHODPR(TerrainPatch, GetWestPatch, () const, TerrainPatch*), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "const BoundingBox& GetWorldBoundingBox()", asMETHODPR(TerrainPatch, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "const BoundingBox& get_worldBoundingBox()", asMETHODPR(TerrainPatch, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "Zone@+ GetZone() const", asMETHODPR(TerrainPatch, GetZone, () const, Zone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "Zone@+ get_zone() const", asMETHODPR(TerrainPatch, GetZone, () const, Zone*), asCALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "uint GetZoneMask() const", asMETHODPR(TerrainPatch, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "uint get_zoneMask() const", asMETHODPR(TerrainPatch, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool HasBasePass(uint) const", asMETHODPR(TerrainPatch, HasBasePass, (unsigned) const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "bool HasEventHandlers() const", asMETHODPR(TerrainPatch, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(TerrainPatch, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(TerrainPatch, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "bool IsEnabled() const", asMETHODPR(TerrainPatch, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "bool get_enabled() const", asMETHODPR(TerrainPatch, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "bool IsEnabledEffective() const", asMETHODPR(TerrainPatch, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "bool get_enabledEffective() const", asMETHODPR(TerrainPatch, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "bool IsInstanceOf(StringHash) const", asMETHODPR(TerrainPatch, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool IsInView() const", asMETHODPR(TerrainPatch, IsInView, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "bool get_inView() const", asMETHODPR(TerrainPatch, IsInView, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool IsInView(Camera@+) const", asMETHODPR(TerrainPatch, IsInView, (Camera*) const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool IsInView(const FrameInfo&in, bool = false) const", asMETHODPR(TerrainPatch, IsInView, (const FrameInfo&, bool) const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool IsOccludee() const", asMETHODPR(TerrainPatch, IsOccludee, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "bool get_occludee() const", asMETHODPR(TerrainPatch, IsOccludee, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool IsOccluder() const", asMETHODPR(TerrainPatch, IsOccluder, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "bool get_occluder() const", asMETHODPR(TerrainPatch, IsOccluder, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "bool IsReplicated() const", asMETHODPR(TerrainPatch, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "bool get_replicated() const", asMETHODPR(TerrainPatch, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool IsTemporary() const", asMETHODPR(TerrainPatch, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "bool get_temporary() const", asMETHODPR(TerrainPatch, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool IsZoneDirty() const", asMETHODPR(TerrainPatch, IsZoneDirty, () const, bool), asCALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void LimitLights()", asMETHODPR(TerrainPatch, LimitLights, (), void), asCALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void LimitVertexLights(bool)", asMETHODPR(TerrainPatch, LimitVertexLights, (bool), void), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool Load(Deserializer&)", asMETHODPR(TerrainPatch, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool LoadJSON(const JSONValue&in)", asMETHODPR(TerrainPatch, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool LoadXML(const XMLElement&in)", asMETHODPR(TerrainPatch, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void MarkForUpdate()", asMETHODPR(TerrainPatch, MarkForUpdate, (), void), asCALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void MarkInView(const FrameInfo&in)", asMETHODPR(TerrainPatch, MarkInView, (const FrameInfo&), void), asCALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void MarkInView(uint)", asMETHODPR(TerrainPatch, MarkInView, (unsigned), void), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "void MarkNetworkUpdate()", asMETHODPR(TerrainPatch, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(TerrainPatch, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(TerrainPatch, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(TerrainPatch, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Drawable::OnSetEnabled() override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void OnSetEnabled()", asMETHODPR(TerrainPatch, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "void PrepareNetworkUpdate()", asMETHODPR(TerrainPatch, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // void TerrainPatch::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override | File: ../Graphics/TerrainPatch.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(TerrainPatch, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(TerrainPatch, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TerrainPatch", "int Refs() const", asMETHODPR(TerrainPatch, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "int get_refs() const", asMETHODPR(TerrainPatch, Refs, () const, int), asCALL_THISCALL);
    // static void TerrainPatch::RegisterObject(Context* context) | File: ../Graphics/TerrainPatch.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TerrainPatch", asBEHAVE_RELEASE, "void f()", asMETHODPR(TerrainPatch, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "void Remove()", asMETHODPR(TerrainPatch, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(TerrainPatch, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "void RemoveInstanceDefault()", asMETHODPR(TerrainPatch, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "void RemoveObjectAnimation()", asMETHODPR(TerrainPatch, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void TerrainPatch::ResetLod() | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "void ResetLod()", asMETHODPR(TerrainPatch, ResetLod, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "void ResetToDefault()", asMETHODPR(TerrainPatch, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "bool Save(Serializer&) const", asMETHODPR(TerrainPatch, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool SaveDefaultAttributes() const", asMETHODPR(TerrainPatch, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "bool SaveJSON(JSONValue&) const", asMETHODPR(TerrainPatch, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "bool SaveXML(XMLElement&) const", asMETHODPR(TerrainPatch, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "void SendEvent(StringHash)", asMETHODPR(TerrainPatch, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(TerrainPatch, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetAnimationEnabled(bool)", asMETHODPR(TerrainPatch, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_animationEnabled(bool)", asMETHODPR(TerrainPatch, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetAnimationTime(float)", asMETHODPR(TerrainPatch, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(TerrainPatch, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "bool set_attributes(uint, const Variant&in)", asMETHODPR(TerrainPatch, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(TerrainPatch, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(TerrainPatch, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(TerrainPatch, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(TerrainPatch, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(TerrainPatch, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetBasePass(uint)", asMETHODPR(TerrainPatch, SetBasePass, (unsigned), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetBlockEvents(bool)", asMETHODPR(TerrainPatch, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void TerrainPatch::SetBoundingBox(const BoundingBox& box) | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetBoundingBox(const BoundingBox&in)", asMETHODPR(TerrainPatch, SetBoundingBox, (const BoundingBox&), void), asCALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetCastShadows(bool)", asMETHODPR(TerrainPatch, SetCastShadows, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_castShadows(bool)", asMETHODPR(TerrainPatch, SetCastShadows, (bool), void), asCALL_THISCALL);
    // void TerrainPatch::SetCoordinates(const IntVector2& coordinates) | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetCoordinates(const IntVector2&in)", asMETHODPR(TerrainPatch, SetCoordinates, (const IntVector2&), void), asCALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetDrawDistance(float)", asMETHODPR(TerrainPatch, SetDrawDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_drawDistance(float)", asMETHODPR(TerrainPatch, SetDrawDistance, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetEnabled(bool)", asMETHODPR(TerrainPatch, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_enabled(bool)", asMETHODPR(TerrainPatch, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(TerrainPatch, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(TerrainPatch, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetInstanceDefault(bool)", asMETHODPR(TerrainPatch, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(TerrainPatch, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetLightMask(uint)", asMETHODPR(TerrainPatch, SetLightMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_lightMask(uint)", asMETHODPR(TerrainPatch, SetLightMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetLodBias(float)", asMETHODPR(TerrainPatch, SetLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_lodBias(float)", asMETHODPR(TerrainPatch, SetLodBias, (float), void), asCALL_THISCALL);
    // void TerrainPatch::SetMaterial(Material* material) | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetMaterial(Material@+)", asMETHODPR(TerrainPatch, SetMaterial, (Material*), void), asCALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetMaxLights(uint)", asMETHODPR(TerrainPatch, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_maxLights(uint)", asMETHODPR(TerrainPatch, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetMinMaxZ(float, float)", asMETHODPR(TerrainPatch, SetMinMaxZ, (float, float), void), asCALL_THISCALL);
    // void TerrainPatch::SetNeighbors(TerrainPatch* north, TerrainPatch* south, TerrainPatch* west, TerrainPatch* east) | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetNeighbors(TerrainPatch@+, TerrainPatch@+, TerrainPatch@+, TerrainPatch@+)", asMETHODPR(TerrainPatch, SetNeighbors, (TerrainPatch*, TerrainPatch*, TerrainPatch*, TerrainPatch*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(TerrainPatch, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(TerrainPatch, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(TerrainPatch, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetOccludee(bool)", asMETHODPR(TerrainPatch, SetOccludee, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_occludee(bool)", asMETHODPR(TerrainPatch, SetOccludee, (bool), void), asCALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetOccluder(bool)", asMETHODPR(TerrainPatch, SetOccluder, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_occluder(bool)", asMETHODPR(TerrainPatch, SetOccluder, (bool), void), asCALL_THISCALL);
    // void TerrainPatch::SetOwner(Terrain* terrain) | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetOwner(Terrain@+)", asMETHODPR(TerrainPatch, SetOwner, (Terrain*), void), asCALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetShadowDistance(float)", asMETHODPR(TerrainPatch, SetShadowDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_shadowDistance(float)", asMETHODPR(TerrainPatch, SetShadowDistance, (float), void), asCALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetShadowMask(uint)", asMETHODPR(TerrainPatch, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_shadowMask(uint)", asMETHODPR(TerrainPatch, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetSortValue(float)", asMETHODPR(TerrainPatch, SetSortValue, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetTemporary(bool)", asMETHODPR(TerrainPatch, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_temporary(bool)", asMETHODPR(TerrainPatch, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetViewMask(uint)", asMETHODPR(TerrainPatch, SetViewMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_viewMask(uint)", asMETHODPR(TerrainPatch, SetViewMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetZone(Zone@+, bool = false)", asMETHODPR(TerrainPatch, SetZone, (Zone*, bool), void), asCALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetZoneMask(uint)", asMETHODPR(TerrainPatch, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_zoneMask(uint)", asMETHODPR(TerrainPatch, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit TerrainPatch::TerrainPatch(Context* context) | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectBehaviour("TerrainPatch", asBEHAVE_FACTORY, "TerrainPatch@+ f()", asFUNCTION(TerrainPatch_TerrainPatch_Context), asCALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "void UnsubscribeFromAllEvents()", asMETHODPR(TerrainPatch, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(TerrainPatch_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(TerrainPatch, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(TerrainPatch, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(TerrainPatch, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void Update(const FrameInfo&in)", asMETHODPR(TerrainPatch, Update, (const FrameInfo&), void), asCALL_THISCALL);
    // void TerrainPatch::UpdateBatches(const FrameInfo& frame) override | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "void UpdateBatches(const FrameInfo&in)", asMETHODPR(TerrainPatch, UpdateBatches, (const FrameInfo&), void), asCALL_THISCALL);
    // void TerrainPatch::UpdateGeometry(const FrameInfo& frame) override | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "void UpdateGeometry(const FrameInfo&in)", asMETHODPR(TerrainPatch, UpdateGeometry, (const FrameInfo&), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TerrainPatch", "int WeakRefs() const", asMETHODPR(TerrainPatch, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "int get_weakRefs() const", asMETHODPR(TerrainPatch, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(TerrainPatch, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(TerrainPatch, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(TerrainPatch, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Drawable
    REGISTER_MANUAL_PART_Drawable(TerrainPatch, "TerrainPatch")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(TerrainPatch, "TerrainPatch")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(TerrainPatch, "TerrainPatch")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(TerrainPatch, "TerrainPatch")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(TerrainPatch, "TerrainPatch")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(TerrainPatch, "TerrainPatch")
#endif
#ifdef REGISTER_MANUAL_PART_TerrainPatch
    REGISTER_MANUAL_PART_TerrainPatch(TerrainPatch, "TerrainPatch")
#endif
    RegisterSubclass<Drawable, TerrainPatch>(engine, "Drawable", "TerrainPatch");
    RegisterSubclass<Component, TerrainPatch>(engine, "Component", "TerrainPatch");
    RegisterSubclass<Animatable, TerrainPatch>(engine, "Animatable", "TerrainPatch");
    RegisterSubclass<Serializable, TerrainPatch>(engine, "Serializable", "TerrainPatch");
    RegisterSubclass<Object, TerrainPatch>(engine, "Object", "TerrainPatch");
    RegisterSubclass<RefCounted, TerrainPatch>(engine, "RefCounted", "TerrainPatch");

    // void UIElement::AddChild(UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void AddChild(UIElement@+)", asMETHODPR(Text, AddChild, (UIElement*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Text", asBEHAVE_ADDREF, "void f()", asMETHODPR(Text, AddRef, (), void), asCALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void AddTag(const String&in)", asMETHODPR(Text, AddTag, (const String&), void), asCALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void AddTags(const String&in, int8 = ';')", asMETHODPR(Text, AddTags, (const String&, char), void), asCALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void AddTags(Array<String>@+)", asFUNCTION(Text_AddTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void AdjustScissor(IntRect&)", asMETHODPR(Text, AdjustScissor, (IntRect&), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "void AllocateNetworkState()", asMETHODPR(Text, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void Text::ApplyAttributes() override | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void ApplyAttributes()", asMETHODPR(Text, ApplyAttributes, (), void), asCALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void BringToFront()", asMETHODPR(Text, BringToFront, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Text::ClearSelection() | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void ClearSelection()", asMETHODPR(Text, ClearSelection, (), void), asCALL_THISCALL);
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", asMETHODPR(Text, CreateChild, (StringHash, const String&, unsigned), UIElement*), asCALL_THISCALL);
    // template<class T> T* UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void DisableLayoutUpdate()", asMETHODPR(Text, DisableLayoutUpdate, (), void), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "IntVector2 ElementToScreen(const IntVector2&in)", asMETHODPR(Text, ElementToScreen, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void EnableLayoutUpdate()", asMETHODPR(Text, EnableLayoutUpdate, (), void), asCALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool FilterAttributes(XMLElement&) const", asMETHODPR(Text, FilterAttributes, (XMLElement&) const, bool), asCALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "uint FindChild(UIElement@+) const", asMETHODPR(Text, FindChild, (UIElement*) const, unsigned), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "bool GetAnimationEnabled() const", asMETHODPR(Text, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_animationEnabled() const", asMETHODPR(Text, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const String& GetAppliedStyle() const", asMETHODPR(Text, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const String& get_style() const", asMETHODPR(Text, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "Variant GetAttribute(uint) const", asMETHODPR(Text, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "Variant get_attributes(uint) const", asMETHODPR(Text, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "Variant GetAttribute(const String&in) const", asMETHODPR(Text, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(Text, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(Text, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(Text, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(Text, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "Variant GetAttributeDefault(uint) const", asMETHODPR(Text, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "Variant get_attributeDefaults(uint) const", asMETHODPR(Text, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Text, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Text::GetAutoLocalizable() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "bool GetAutoLocalizable() const", asMETHODPR(Text, GetAutoLocalizable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_autoLocalizable() const", asMETHODPR(Text, GetAutoLocalizable, () const, bool), asCALL_THISCALL);
    // void Text::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/Text.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "bool GetBlockEvents() const", asMETHODPR(Text, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool GetBringToBack() const", asMETHODPR(Text, GetBringToBack, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_bringToBack() const", asMETHODPR(Text, GetBringToBack, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool GetBringToFront() const", asMETHODPR(Text, GetBringToFront, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_bringToFront() const", asMETHODPR(Text, GetBringToFront, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "const String& GetCategory() const", asMETHODPR(Text, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const String& get_category() const", asMETHODPR(Text, GetCategory, () const, const String&), asCALL_THISCALL);
    // Vector2 Text::GetCharPosition(unsigned index) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "Vector2 GetCharPosition(uint)", asMETHODPR(Text, GetCharPosition, (unsigned), Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "Vector2 get_charPositions(uint)", asMETHODPR(Text, GetCharPosition, (unsigned), Vector2), asCALL_THISCALL);
    // Vector2 Text::GetCharSize(unsigned index) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "Vector2 GetCharSize(uint)", asMETHODPR(Text, GetCharSize, (unsigned), Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "Vector2 get_charSizes(uint)", asMETHODPR(Text, GetCharSize, (unsigned), Vector2), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "UIElement@+ GetChild(uint) const", asMETHODPR(Text, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "UIElement@+ get_children(uint) const", asMETHODPR(Text, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "UIElement@+ GetChild(const String&in, bool = false) const", asMETHODPR(Text, GetChild, (const String&, bool) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", asMETHODPR(Text, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), asCALL_THISCALL);
    // template<class T> T* UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const IntVector2& GetChildOffset() const", asMETHODPR(Text, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const IntVector2& get_childOffset() const", asMETHODPR(Text, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "Array<UIElement@>@ GetChildren() const", asFUNCTION(Text_GetChildren_void), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "Array<UIElement@>@ GetChildren(bool) const", asFUNCTION(Text_GetChildren_bool), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", asFUNCTION(Text_GetChildrenWithTag_String_bool), asCALL_CDECL_OBJFIRST);
    // template<class T> T* UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const IntRect& GetClipBorder() const", asMETHODPR(Text, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const IntRect& get_clipBorder() const", asMETHODPR(Text, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool GetClipChildren() const", asMETHODPR(Text, GetClipChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_clipChildren() const", asMETHODPR(Text, GetClipChildren, () const, bool), asCALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const Color& GetColor(Corner) const", asMETHODPR(Text, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const Color& get_colors(Corner) const", asMETHODPR(Text, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const Color& GetColorAttr() const", asMETHODPR(Text, GetColorAttr, () const, const Color&), asCALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "IntRect GetCombinedScreenRect()", asMETHODPR(Text, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "IntRect get_combinedScreenRect()", asMETHODPR(Text, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "XMLFile@+ GetDefaultStyle(bool = true) const", asMETHODPR(Text, GetDefaultStyle, (bool) const, XMLFile*), asCALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const Color& GetDerivedColor() const", asMETHODPR(Text, GetDerivedColor, () const, const Color&), asCALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "float GetDerivedOpacity() const", asMETHODPR(Text, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "float get_derivedOpacity() const", asMETHODPR(Text, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "MouseButtonFlags GetDragButtonCombo() const", asMETHODPR(Text, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "MouseButtonFlags get_dragButtonCombo() const", asMETHODPR(Text, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "uint GetDragButtonCount() const", asMETHODPR(Text, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "uint get_dragButtonCount() const", asMETHODPR(Text, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "DragAndDropModeFlags GetDragDropMode() const", asMETHODPR(Text, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "DragAndDropModeFlags get_dragDropMode() const", asMETHODPR(Text, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    // const Color& Text::GetEffectColor() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "const Color& GetEffectColor() const", asMETHODPR(Text, GetEffectColor, () const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const Color& get_effectColor() const", asMETHODPR(Text, GetEffectColor, () const, const Color&), asCALL_THISCALL);
    // float Text::GetEffectDepthBias() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "float GetEffectDepthBias() const", asMETHODPR(Text, GetEffectDepthBias, () const, float), asCALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "IntVector2 GetEffectiveMinSize() const", asMETHODPR(Text, GetEffectiveMinSize, () const, IntVector2), asCALL_THISCALL);
    // bool Text::GetEffectRoundStroke() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "bool GetEffectRoundStroke() const", asMETHODPR(Text, GetEffectRoundStroke, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_effectRoundStroke() const", asMETHODPR(Text, GetEffectRoundStroke, () const, bool), asCALL_THISCALL);
    // const IntVector2& Text::GetEffectShadowOffset() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "const IntVector2& GetEffectShadowOffset() const", asMETHODPR(Text, GetEffectShadowOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const IntVector2& get_effectShadowOffset() const", asMETHODPR(Text, GetEffectShadowOffset, () const, const IntVector2&), asCALL_THISCALL);
    // int Text::GetEffectStrokeThickness() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "int GetEffectStrokeThickness() const", asMETHODPR(Text, GetEffectStrokeThickness, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_effectStrokeThickness() const", asMETHODPR(Text, GetEffectStrokeThickness, () const, int), asCALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "UIElement@+ GetElementEventSender() const", asMETHODPR(Text, GetElementEventSender, () const, UIElement*), asCALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool GetEnableAnchor() const", asMETHODPR(Text, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_enableAnchor() const", asMETHODPR(Text, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "VariantMap& GetEventDataMap() const", asMETHODPR(Text, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "Object@+ GetEventSender() const", asMETHODPR(Text, GetEventSender, () const, Object*), asCALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "FocusMode GetFocusMode() const", asMETHODPR(Text, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "FocusMode get_focusMode() const", asMETHODPR(Text, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    // Font* Text::GetFont() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "Font@+ GetFont() const", asMETHODPR(Text, GetFont, () const, Font*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "Font@+ get_font() const", asMETHODPR(Text, GetFont, () const, Font*), asCALL_THISCALL);
    // ResourceRef Text::GetFontAttr() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "ResourceRef GetFontAttr() const", asMETHODPR(Text, GetFontAttr, () const, ResourceRef), asCALL_THISCALL);
    // float Text::GetFontSize() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "float GetFontSize() const", asMETHODPR(Text, GetFontSize, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "float get_fontSize() const", asMETHODPR(Text, GetFontSize, () const, float), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Text, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Text, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "const VariantMap& GetGlobalVars() const", asMETHODPR(Text, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const VariantMap& get_globalVars() const", asMETHODPR(Text, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "int GetHeight() const", asMETHODPR(Text, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_height() const", asMETHODPR(Text, GetHeight, () const, int), asCALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "HorizontalAlignment GetHorizontalAlignment() const", asMETHODPR(Text, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "HorizontalAlignment get_horizontalAlignment() const", asMETHODPR(Text, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    // const Color& UISelectable::GetHoverColor() const | File: ../UI/UISelectable.h
    engine->RegisterObjectMethod("Text", "const Color& GetHoverColor() const", asMETHODPR(Text, GetHoverColor, () const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const Color& get_hoverColor() const", asMETHODPR(Text, GetHoverColor, () const, const Color&), asCALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "int GetIndent() const", asMETHODPR(Text, GetIndent, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_indent() const", asMETHODPR(Text, GetIndent, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "int GetIndentSpacing() const", asMETHODPR(Text, GetIndentSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_indentSpacing() const", asMETHODPR(Text, GetIndentSpacing, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "int GetIndentWidth() const", asMETHODPR(Text, GetIndentWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_indentWidth() const", asMETHODPR(Text, GetIndentWidth, () const, int), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Text, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const IntRect& GetLayoutBorder() const", asMETHODPR(Text, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const IntRect& get_layoutBorder() const", asMETHODPR(Text, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "int GetLayoutElementMaxSize() const", asMETHODPR(Text, GetLayoutElementMaxSize, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const Vector2& GetLayoutFlexScale() const", asMETHODPR(Text, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const Vector2& get_layoutFlexScale() const", asMETHODPR(Text, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "LayoutMode GetLayoutMode() const", asMETHODPR(Text, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "LayoutMode get_layoutMode() const", asMETHODPR(Text, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "int GetLayoutSpacing() const", asMETHODPR(Text, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_layoutSpacing() const", asMETHODPR(Text, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const Vector2& GetMaxAnchor() const", asMETHODPR(Text, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const Vector2& get_maxAnchor() const", asMETHODPR(Text, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "int GetMaxHeight() const", asMETHODPR(Text, GetMaxHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_maxHeight() const", asMETHODPR(Text, GetMaxHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const IntVector2& GetMaxOffset() const", asMETHODPR(Text, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const IntVector2& get_maxOffset() const", asMETHODPR(Text, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const IntVector2& GetMaxSize() const", asMETHODPR(Text, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const IntVector2& get_maxSize() const", asMETHODPR(Text, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "int GetMaxWidth() const", asMETHODPR(Text, GetMaxWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_maxWidth() const", asMETHODPR(Text, GetMaxWidth, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const Vector2& GetMinAnchor() const", asMETHODPR(Text, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const Vector2& get_minAnchor() const", asMETHODPR(Text, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "int GetMinHeight() const", asMETHODPR(Text, GetMinHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_minHeight() const", asMETHODPR(Text, GetMinHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const IntVector2& GetMinOffset() const", asMETHODPR(Text, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const IntVector2& get_minOffset() const", asMETHODPR(Text, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const IntVector2& GetMinSize() const", asMETHODPR(Text, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const IntVector2& get_minSize() const", asMETHODPR(Text, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "int GetMinWidth() const", asMETHODPR(Text, GetMinWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_minWidth() const", asMETHODPR(Text, GetMinWidth, () const, int), asCALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const String& GetName() const", asMETHODPR(Text, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const String& get_name() const", asMETHODPR(Text, GetName, () const, const String&), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "uint GetNumAttributes() const", asMETHODPR(Text, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "uint get_numAttributes() const", asMETHODPR(Text, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Text::GetNumChars() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "uint GetNumChars() const", asMETHODPR(Text, GetNumChars, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "uint get_numChars() const", asMETHODPR(Text, GetNumChars, () const, unsigned), asCALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "uint GetNumChildren(bool = false) const", asMETHODPR(Text, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "uint get_numChildren(bool = false) const", asMETHODPR(Text, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "uint GetNumNetworkAttributes() const", asMETHODPR(Text, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Text::GetNumRows() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "uint GetNumRows() const", asMETHODPR(Text, GetNumRows, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "uint get_numRows() const", asMETHODPR(Text, GetNumRows, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(Text, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(Text, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(Text, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "float GetOpacity() const", asMETHODPR(Text, GetOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "float get_opacity() const", asMETHODPR(Text, GetOpacity, () const, float), asCALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "UIElement@+ GetParent() const", asMETHODPR(Text, GetParent, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "UIElement@+ get_parent() const", asMETHODPR(Text, GetParent, () const, UIElement*), asCALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const Vector2& GetPivot() const", asMETHODPR(Text, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const Vector2& get_pivot() const", asMETHODPR(Text, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const IntVector2& GetPosition() const", asMETHODPR(Text, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const IntVector2& get_position() const", asMETHODPR(Text, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "int GetPriority() const", asMETHODPR(Text, GetPriority, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_priority() const", asMETHODPR(Text, GetPriority, () const, int), asCALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "UIElement@+ GetRoot() const", asMETHODPR(Text, GetRoot, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "UIElement@+ get_root() const", asMETHODPR(Text, GetRoot, () const, UIElement*), asCALL_THISCALL);
    // float Text::GetRowHeight() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "float GetRowHeight() const", asMETHODPR(Text, GetRowHeight, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "float get_rowHeight() const", asMETHODPR(Text, GetRowHeight, () const, float), asCALL_THISCALL);
    // float Text::GetRowSpacing() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "float GetRowSpacing() const", asMETHODPR(Text, GetRowSpacing, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "float get_rowSpacing() const", asMETHODPR(Text, GetRowSpacing, () const, float), asCALL_THISCALL);
    // float Text::GetRowWidth(unsigned index) const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "float GetRowWidth(uint) const", asMETHODPR(Text, GetRowWidth, (unsigned) const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "float get_rowWidths(uint) const", asMETHODPR(Text, GetRowWidth, (unsigned) const, float), asCALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const IntVector2& GetScreenPosition() const", asMETHODPR(Text, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const IntVector2& get_screenPosition() const", asMETHODPR(Text, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    // const Color& UISelectable::GetSelectionColor() const | File: ../UI/UISelectable.h
    engine->RegisterObjectMethod("Text", "const Color& GetSelectionColor() const", asMETHODPR(Text, GetSelectionColor, () const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const Color& get_selectionColor() const", asMETHODPR(Text, GetSelectionColor, () const, const Color&), asCALL_THISCALL);
    // unsigned Text::GetSelectionLength() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "uint GetSelectionLength() const", asMETHODPR(Text, GetSelectionLength, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "uint get_selectionLength() const", asMETHODPR(Text, GetSelectionLength, () const, unsigned), asCALL_THISCALL);
    // unsigned Text::GetSelectionStart() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "uint GetSelectionStart() const", asMETHODPR(Text, GetSelectionStart, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "uint get_selectionStart() const", asMETHODPR(Text, GetSelectionStart, () const, unsigned), asCALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const IntVector2& GetSize() const", asMETHODPR(Text, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const IntVector2& get_size() const", asMETHODPR(Text, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool GetSortChildren() const", asMETHODPR(Text, GetSortChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_sortChildren() const", asMETHODPR(Text, GetSortChildren, () const, bool), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Text, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "Array<String>@ GetTags() const", asFUNCTION(Text_GetTags_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Text", "Array<String>@ get_tags() const", asFUNCTION(Text_GetTags_void), asCALL_CDECL_OBJFIRST);
    // const String& Text::GetText() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "const String& GetText() const", asMETHODPR(Text, GetText, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const String& get_text() const", asMETHODPR(Text, GetText, () const, const String&), asCALL_THISCALL);
    // HorizontalAlignment Text::GetTextAlignment() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "HorizontalAlignment GetTextAlignment() const", asMETHODPR(Text, GetTextAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "HorizontalAlignment get_textAlignment() const", asMETHODPR(Text, GetTextAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    // String Text::GetTextAttr() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "String GetTextAttr() const", asMETHODPR(Text, GetTextAttr, () const, String), asCALL_THISCALL);
    // TextEffect Text::GetTextEffect() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "TextEffect GetTextEffect() const", asMETHODPR(Text, GetTextEffect, () const, TextEffect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "TextEffect get_textEffect() const", asMETHODPR(Text, GetTextEffect, () const, TextEffect), asCALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "TraversalMode GetTraversalMode() const", asMETHODPR(Text, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "TraversalMode get_traversalMode() const", asMETHODPR(Text, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "StringHash GetType() const", asMETHODPR(Text, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "StringHash get_type() const", asMETHODPR(Text, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "const String& GetTypeName() const", asMETHODPR(Text, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const String& get_typeName() const", asMETHODPR(Text, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool GetUseDerivedOpacity() const", asMETHODPR(Text, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_useDerivedOpacity() const", asMETHODPR(Text, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const Variant& GetVar(const StringHash&in) const", asMETHODPR(Text, GetVar, (const StringHash&) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const VariantMap& GetVars() const", asMETHODPR(Text, GetVars, () const, const VariantMap&), asCALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "VerticalAlignment GetVerticalAlignment() const", asMETHODPR(Text, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "VerticalAlignment get_verticalAlignment() const", asMETHODPR(Text, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "int GetWidth() const", asMETHODPR(Text, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_width() const", asMETHODPR(Text, GetWidth, () const, int), asCALL_THISCALL);
    // bool Text::GetWordwrap() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "bool GetWordwrap() const", asMETHODPR(Text, GetWordwrap, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_wordwrap() const", asMETHODPR(Text, GetWordwrap, () const, bool), asCALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool HasColorGradient() const", asMETHODPR(Text, HasColorGradient, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_colorGradient() const", asMETHODPR(Text, HasColorGradient, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "bool HasEventHandlers() const", asMETHODPR(Text, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool HasFocus() const", asMETHODPR(Text, HasFocus, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_focus() const", asMETHODPR(Text, HasFocus, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Text, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Text, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool HasTag(const String&in) const", asMETHODPR(Text, HasTag, (const String&) const, bool), asCALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void InsertChild(uint, UIElement@+)", asMETHODPR(Text, InsertChild, (unsigned, UIElement*), void), asCALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsChildOf(UIElement@+) const", asMETHODPR(Text, IsChildOf, (UIElement*) const, bool), asCALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsEditable() const", asMETHODPR(Text, IsEditable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_editable() const", asMETHODPR(Text, IsEditable, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsElementEventSender() const", asMETHODPR(Text, IsElementEventSender, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_elementEventSender() const", asMETHODPR(Text, IsElementEventSender, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsEnabled() const", asMETHODPR(Text, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_enabled() const", asMETHODPR(Text, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsEnabledSelf() const", asMETHODPR(Text, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_enabledSelf() const", asMETHODPR(Text, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsFixedHeight() const", asMETHODPR(Text, IsFixedHeight, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_fixedHeight() const", asMETHODPR(Text, IsFixedHeight, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsFixedSize() const", asMETHODPR(Text, IsFixedSize, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_fixedSize() const", asMETHODPR(Text, IsFixedSize, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsFixedWidth() const", asMETHODPR(Text, IsFixedWidth, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_fixedWidth() const", asMETHODPR(Text, IsFixedWidth, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsHovering() const", asMETHODPR(Text, IsHovering, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_hovering() const", asMETHODPR(Text, IsHovering, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsInside(IntVector2, bool)", asMETHODPR(Text, IsInside, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsInsideCombined(IntVector2, bool)", asMETHODPR(Text, IsInsideCombined, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "bool IsInstanceOf(StringHash) const", asMETHODPR(Text, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsInternal() const", asMETHODPR(Text, IsInternal, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_internal() const", asMETHODPR(Text, IsInternal, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsSelected() const", asMETHODPR(Text, IsSelected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_selected() const", asMETHODPR(Text, IsSelected, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "bool IsTemporary() const", asMETHODPR(Text, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_temporary() const", asMETHODPR(Text, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsVisible() const", asMETHODPR(Text, IsVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_visible() const", asMETHODPR(Text, IsVisible, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsVisibleEffective() const", asMETHODPR(Text, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_visibleEffective() const", asMETHODPR(Text, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsWheelHandler() const", asMETHODPR(Text, IsWheelHandler, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsWithinScissor(const IntRect&in)", asMETHODPR(Text, IsWithinScissor, (const IntRect&), bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "bool Load(Deserializer&)", asMETHODPR(Text, Load, (Deserializer&), bool), asCALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", asMETHODPR(Text, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Text, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool LoadXML(const XMLElement&in)", asMETHODPR(Text, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool LoadXML(const XMLElement&in, XMLFile@+)", asMETHODPR(Text, LoadXML, (const XMLElement&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool LoadXML(Deserializer&)", asMETHODPR(Text, LoadXML, (Deserializer&), bool), asCALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "void MarkNetworkUpdate()", asMETHODPR(Text, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Text, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", asMETHODPR(Text, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Text, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Text, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(Text, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool OnDragDropFinish(UIElement@+)", asMETHODPR(Text, OnDragDropFinish, (UIElement*), bool), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool OnDragDropTest(UIElement@+)", asMETHODPR(Text, OnDragDropTest, (UIElement*), bool), asCALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(Text, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Text, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Text, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Text, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Text, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // void Text::OnIndentSet() override | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void OnIndentSet()", asMETHODPR(Text, OnIndentSet, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", asMETHODPR(Text, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnPositionSet(const IntVector2&in)", asMETHODPR(Text, OnPositionSet, (const IntVector2&), void), asCALL_THISCALL);
    // void Text::OnResize(const IntVector2& newSize, const IntVector2& delta) override | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void OnResize(const IntVector2&in, const IntVector2&in)", asMETHODPR(Text, OnResize, (const IntVector2&, const IntVector2&), void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Text, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnSetEditable()", asMETHODPR(Text, OnSetEditable, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnTextInput(const String&in)", asMETHODPR(Text, OnTextInput, (const String&), void), asCALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", asMETHODPR(Text, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Text, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Text, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Text", "int Refs() const", asMETHODPR(Text, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_refs() const", asMETHODPR(Text, Refs, () const, int), asCALL_THISCALL);
    // static void Text::RegisterObject(Context* context) | File: ../UI/Text.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Text", asBEHAVE_RELEASE, "void f()", asMETHODPR(Text, ReleaseRef, (), void), asCALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void Remove()", asMETHODPR(Text, Remove, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void RemoveAllChildren()", asMETHODPR(Text, RemoveAllChildren, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void RemoveAllTags()", asMETHODPR(Text, RemoveAllTags, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(Text, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void RemoveChild(UIElement@+, uint = 0)", asMETHODPR(Text, RemoveChild, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void RemoveChildAtIndex(uint)", asMETHODPR(Text, RemoveChildAtIndex, (unsigned), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "void RemoveInstanceDefault()", asMETHODPR(Text, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "void RemoveObjectAnimation()", asMETHODPR(Text, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool RemoveTag(const String&in)", asMETHODPR(Text, RemoveTag, (const String&), bool), asCALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void ResetDeepEnabled()", asMETHODPR(Text, ResetDeepEnabled, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "void ResetToDefault()", asMETHODPR(Text, ResetToDefault, (), void), asCALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "bool Save(Serializer&) const", asMETHODPR(Text, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "bool SaveDefaultAttributes() const", asMETHODPR(Text, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "bool SaveJSON(JSONValue&) const", asMETHODPR(Text, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool SaveXML(XMLElement&) const", asMETHODPR(Text, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool SaveXML(Serializer&, const String&in = \"\t\") const", asMETHODPR(Text, SaveXML, (Serializer&, const String&) const, bool), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "IntVector2 ScreenToElement(const IntVector2&in)", asMETHODPR(Text, ScreenToElement, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "void SendEvent(StringHash)", asMETHODPR(Text, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Text, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", asMETHODPR(Text, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "void SetAnimationEnabled(bool)", asMETHODPR(Text, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_animationEnabled(bool)", asMETHODPR(Text, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "void SetAnimationTime(float)", asMETHODPR(Text, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Text, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Text, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Text, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Text, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(Text, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(Text, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Text, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Text::SetAutoLocalizable(bool enable) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetAutoLocalizable(bool)", asMETHODPR(Text, SetAutoLocalizable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_autoLocalizable(bool)", asMETHODPR(Text, SetAutoLocalizable, (bool), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "void SetBlockEvents(bool)", asMETHODPR(Text, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetBringToBack(bool)", asMETHODPR(Text, SetBringToBack, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_bringToBack(bool)", asMETHODPR(Text, SetBringToBack, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetBringToFront(bool)", asMETHODPR(Text, SetBringToFront, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_bringToFront(bool)", asMETHODPR(Text, SetBringToFront, (bool), void), asCALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetChildOffset(const IntVector2&in)", asMETHODPR(Text, SetChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetClipBorder(const IntRect&in)", asMETHODPR(Text, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_clipBorder(const IntRect&in)", asMETHODPR(Text, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetClipChildren(bool)", asMETHODPR(Text, SetClipChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_clipChildren(bool)", asMETHODPR(Text, SetClipChildren, (bool), void), asCALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetColor(const Color&in)", asMETHODPR(Text, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_color(const Color&in)", asMETHODPR(Text, SetColor, (const Color&), void), asCALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetColor(Corner, const Color&in)", asMETHODPR(Text, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_colors(Corner, const Color&in)", asMETHODPR(Text, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetDeepEnabled(bool)", asMETHODPR(Text, SetDeepEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetDefaultStyle(XMLFile@+)", asMETHODPR(Text, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_defaultStyle(XMLFile@+)", asMETHODPR(Text, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetDragDropMode(DragAndDropModeFlags)", asMETHODPR(Text, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_dragDropMode(DragAndDropModeFlags)", asMETHODPR(Text, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetEditable(bool)", asMETHODPR(Text, SetEditable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_editable(bool)", asMETHODPR(Text, SetEditable, (bool), void), asCALL_THISCALL);
    // void Text::SetEffectColor(const Color& effectColor) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetEffectColor(const Color&in)", asMETHODPR(Text, SetEffectColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_effectColor(const Color&in)", asMETHODPR(Text, SetEffectColor, (const Color&), void), asCALL_THISCALL);
    // void Text::SetEffectDepthBias(float bias) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetEffectDepthBias(float)", asMETHODPR(Text, SetEffectDepthBias, (float), void), asCALL_THISCALL);
    // void Text::SetEffectRoundStroke(bool roundStroke) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetEffectRoundStroke(bool)", asMETHODPR(Text, SetEffectRoundStroke, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_effectRoundStroke(bool)", asMETHODPR(Text, SetEffectRoundStroke, (bool), void), asCALL_THISCALL);
    // void Text::SetEffectShadowOffset(const IntVector2& offset) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetEffectShadowOffset(const IntVector2&in)", asMETHODPR(Text, SetEffectShadowOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_effectShadowOffset(const IntVector2&in)", asMETHODPR(Text, SetEffectShadowOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void Text::SetEffectStrokeThickness(int thickness) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetEffectStrokeThickness(int)", asMETHODPR(Text, SetEffectStrokeThickness, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_effectStrokeThickness(int)", asMETHODPR(Text, SetEffectStrokeThickness, (int), void), asCALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetElementEventSender(bool)", asMETHODPR(Text, SetElementEventSender, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_elementEventSender(bool)", asMETHODPR(Text, SetElementEventSender, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetEnableAnchor(bool)", asMETHODPR(Text, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_enableAnchor(bool)", asMETHODPR(Text, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetEnabled(bool)", asMETHODPR(Text, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_enabled(bool)", asMETHODPR(Text, SetEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetEnabledRecursive(bool)", asMETHODPR(Text, SetEnabledRecursive, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetFixedHeight(int)", asMETHODPR(Text, SetFixedHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetFixedSize(const IntVector2&in)", asMETHODPR(Text, SetFixedSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetFixedSize(int, int)", asMETHODPR(Text, SetFixedSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetFixedWidth(int)", asMETHODPR(Text, SetFixedWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetFocus(bool)", asMETHODPR(Text, SetFocus, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_focus(bool)", asMETHODPR(Text, SetFocus, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetFocusMode(FocusMode)", asMETHODPR(Text, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_focusMode(FocusMode)", asMETHODPR(Text, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    // bool Text::SetFont(const String& fontName, float size=DEFAULT_FONT_SIZE) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "bool SetFont(const String&in, float = DEFAULT_FONT_SIZE)", asMETHODPR(Text, SetFont, (const String&, float), bool), asCALL_THISCALL);
    // bool Text::SetFont(Font* font, float size=DEFAULT_FONT_SIZE) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "bool SetFont(Font@+, float = DEFAULT_FONT_SIZE)", asMETHODPR(Text, SetFont, (Font*, float), bool), asCALL_THISCALL);
    // void Text::SetFontAttr(const ResourceRef& value) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetFontAttr(const ResourceRef&in)", asMETHODPR(Text, SetFontAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // bool Text::SetFontSize(float size) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "bool SetFontSize(float)", asMETHODPR(Text, SetFontSize, (float), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool set_fontSize(float)", asMETHODPR(Text, SetFontSize, (float), bool), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Text, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Text, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetHeight(int)", asMETHODPR(Text, SetHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_height(int)", asMETHODPR(Text, SetHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetHorizontalAlignment(HorizontalAlignment)", asMETHODPR(Text, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_horizontalAlignment(HorizontalAlignment)", asMETHODPR(Text, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    // void UISelectable::SetHoverColor(const Color& color) | File: ../UI/UISelectable.h
    engine->RegisterObjectMethod("Text", "void SetHoverColor(const Color&in)", asMETHODPR(Text, SetHoverColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_hoverColor(const Color&in)", asMETHODPR(Text, SetHoverColor, (const Color&), void), asCALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetHovering(bool)", asMETHODPR(Text, SetHovering, (bool), void), asCALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetIndent(int)", asMETHODPR(Text, SetIndent, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_indent(int)", asMETHODPR(Text, SetIndent, (int), void), asCALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetIndentSpacing(int)", asMETHODPR(Text, SetIndentSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_indentSpacing(int)", asMETHODPR(Text, SetIndentSpacing, (int), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "void SetInstanceDefault(bool)", asMETHODPR(Text, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Text, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetInternal(bool)", asMETHODPR(Text, SetInternal, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_internal(bool)", asMETHODPR(Text, SetInternal, (bool), void), asCALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", asMETHODPR(Text, SetLayout, (LayoutMode, int, const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetLayoutBorder(const IntRect&in)", asMETHODPR(Text, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_layoutBorder(const IntRect&in)", asMETHODPR(Text, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetLayoutFlexScale(const Vector2&in)", asMETHODPR(Text, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_layoutFlexScale(const Vector2&in)", asMETHODPR(Text, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetLayoutMode(LayoutMode)", asMETHODPR(Text, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_layoutMode(LayoutMode)", asMETHODPR(Text, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetLayoutSpacing(int)", asMETHODPR(Text, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_layoutSpacing(int)", asMETHODPR(Text, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMaxAnchor(const Vector2&in)", asMETHODPR(Text, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_maxAnchor(const Vector2&in)", asMETHODPR(Text, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMaxAnchor(float, float)", asMETHODPR(Text, SetMaxAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMaxHeight(int)", asMETHODPR(Text, SetMaxHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_maxHeight(int)", asMETHODPR(Text, SetMaxHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMaxOffset(const IntVector2&in)", asMETHODPR(Text, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_maxOffset(const IntVector2&in)", asMETHODPR(Text, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMaxSize(const IntVector2&in)", asMETHODPR(Text, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_maxSize(const IntVector2&in)", asMETHODPR(Text, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMaxSize(int, int)", asMETHODPR(Text, SetMaxSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMaxWidth(int)", asMETHODPR(Text, SetMaxWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_maxWidth(int)", asMETHODPR(Text, SetMaxWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMinAnchor(const Vector2&in)", asMETHODPR(Text, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_minAnchor(const Vector2&in)", asMETHODPR(Text, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMinAnchor(float, float)", asMETHODPR(Text, SetMinAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMinHeight(int)", asMETHODPR(Text, SetMinHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_minHeight(int)", asMETHODPR(Text, SetMinHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMinOffset(const IntVector2&in)", asMETHODPR(Text, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_minOffset(const IntVector2&in)", asMETHODPR(Text, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMinSize(const IntVector2&in)", asMETHODPR(Text, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_minSize(const IntVector2&in)", asMETHODPR(Text, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMinSize(int, int)", asMETHODPR(Text, SetMinSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMinWidth(int)", asMETHODPR(Text, SetMinWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_minWidth(int)", asMETHODPR(Text, SetMinWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetName(const String&in)", asMETHODPR(Text, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_name(const String&in)", asMETHODPR(Text, SetName, (const String&), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(Text, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(Text, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(Text, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetOpacity(float)", asMETHODPR(Text, SetOpacity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_opacity(float)", asMETHODPR(Text, SetOpacity, (float), void), asCALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", asMETHODPR(Text, SetParent, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetPivot(const Vector2&in)", asMETHODPR(Text, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_pivot(const Vector2&in)", asMETHODPR(Text, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetPivot(float, float)", asMETHODPR(Text, SetPivot, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetPosition(const IntVector2&in)", asMETHODPR(Text, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_position(const IntVector2&in)", asMETHODPR(Text, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetPosition(int, int)", asMETHODPR(Text, SetPosition, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetPriority(int)", asMETHODPR(Text, SetPriority, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_priority(int)", asMETHODPR(Text, SetPriority, (int), void), asCALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetRenderTexture(Texture2D@+)", asMETHODPR(Text, SetRenderTexture, (Texture2D*), void), asCALL_THISCALL);
    // void Text::SetRowSpacing(float spacing) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetRowSpacing(float)", asMETHODPR(Text, SetRowSpacing, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_rowSpacing(float)", asMETHODPR(Text, SetRowSpacing, (float), void), asCALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetSelected(bool)", asMETHODPR(Text, SetSelected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_selected(bool)", asMETHODPR(Text, SetSelected, (bool), void), asCALL_THISCALL);
    // void Text::SetSelection(unsigned start, unsigned length=M_MAX_UNSIGNED) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetSelection(uint, uint = M_MAX_UNSIGNED)", asMETHODPR(Text, SetSelection, (unsigned, unsigned), void), asCALL_THISCALL);
    // void UISelectable::SetSelectionColor(const Color& color) | File: ../UI/UISelectable.h
    engine->RegisterObjectMethod("Text", "void SetSelectionColor(const Color&in)", asMETHODPR(Text, SetSelectionColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_selectionColor(const Color&in)", asMETHODPR(Text, SetSelectionColor, (const Color&), void), asCALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetSize(const IntVector2&in)", asMETHODPR(Text, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_size(const IntVector2&in)", asMETHODPR(Text, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetSize(int, int)", asMETHODPR(Text, SetSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetSortChildren(bool)", asMETHODPR(Text, SetSortChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_sortChildren(bool)", asMETHODPR(Text, SetSortChildren, (bool), void), asCALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool SetStyle(const String&in, XMLFile@+ = null)", asMETHODPR(Text, SetStyle, (const String&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool SetStyle(const XMLElement&in)", asMETHODPR(Text, SetStyle, (const XMLElement&), bool), asCALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool SetStyleAuto(XMLFile@+ = null)", asMETHODPR(Text, SetStyleAuto, (XMLFile*), bool), asCALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetTags(Array<String>@+)", asFUNCTION(Text_SetTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "void SetTemporary(bool)", asMETHODPR(Text, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_temporary(bool)", asMETHODPR(Text, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Text::SetText(const String& text) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetText(const String&in)", asMETHODPR(Text, SetText, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_text(const String&in)", asMETHODPR(Text, SetText, (const String&), void), asCALL_THISCALL);
    // void Text::SetTextAlignment(HorizontalAlignment align) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetTextAlignment(HorizontalAlignment)", asMETHODPR(Text, SetTextAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_textAlignment(HorizontalAlignment)", asMETHODPR(Text, SetTextAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    // void Text::SetTextAttr(const String& value) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetTextAttr(const String&in)", asMETHODPR(Text, SetTextAttr, (const String&), void), asCALL_THISCALL);
    // void Text::SetTextEffect(TextEffect textEffect) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetTextEffect(TextEffect)", asMETHODPR(Text, SetTextEffect, (TextEffect), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_textEffect(TextEffect)", asMETHODPR(Text, SetTextEffect, (TextEffect), void), asCALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetTraversalMode(TraversalMode)", asMETHODPR(Text, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_traversalMode(TraversalMode)", asMETHODPR(Text, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetUseDerivedOpacity(bool)", asMETHODPR(Text, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_useDerivedOpacity(bool)", asMETHODPR(Text, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetVar(StringHash, const Variant&in)", asMETHODPR(Text, SetVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetVerticalAlignment(VerticalAlignment)", asMETHODPR(Text, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_verticalAlignment(VerticalAlignment)", asMETHODPR(Text, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetVisible(bool)", asMETHODPR(Text, SetVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_visible(bool)", asMETHODPR(Text, SetVisible, (bool), void), asCALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetWidth(int)", asMETHODPR(Text, SetWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_width(int)", asMETHODPR(Text, SetWidth, (int), void), asCALL_THISCALL);
    // void Text::SetWordwrap(bool enable) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetWordwrap(bool)", asMETHODPR(Text, SetWordwrap, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_wordwrap(bool)", asMETHODPR(Text, SetWordwrap, (bool), void), asCALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SortChildren()", asMETHODPR(Text, SortChildren, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit Text::Text(Context* context) | File: ../UI/Text.h
    engine->RegisterObjectBehaviour("Text", asBEHAVE_FACTORY, "Text@+ f()", asFUNCTION(Text_Text_Context), asCALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "void UnsubscribeFromAllEvents()", asMETHODPR(Text, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Text_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Text, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Text, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Text, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void UIElement::Update(float timeStep) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void Update(float)", asMETHODPR(Text, Update, (float), void), asCALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void UpdateLayout()", asMETHODPR(Text, UpdateLayout, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Text", "int WeakRefs() const", asMETHODPR(Text, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_weakRefs() const", asMETHODPR(Text, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Text, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Text, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Text, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_UISelectable
    REGISTER_MANUAL_PART_UISelectable(Text, "Text")
#endif
#ifdef REGISTER_MANUAL_PART_UIElement
    REGISTER_MANUAL_PART_UIElement(Text, "Text")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(Text, "Text")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Text, "Text")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Text, "Text")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Text, "Text")
#endif
#ifdef REGISTER_MANUAL_PART_Text
    REGISTER_MANUAL_PART_Text(Text, "Text")
#endif
    RegisterSubclass<UISelectable, Text>(engine, "UISelectable", "Text");
    RegisterSubclass<UIElement, Text>(engine, "UIElement", "Text");
    RegisterSubclass<Animatable, Text>(engine, "Animatable", "Text");
    RegisterSubclass<Serializable, Text>(engine, "Serializable", "Text");
    RegisterSubclass<Object, Text>(engine, "Object", "Text");
    RegisterSubclass<RefCounted, Text>(engine, "RefCounted", "Text");

    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void AddLight(Light@+)", asMETHODPR(Text3D, AddLight, (Light*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Text3D", asBEHAVE_ADDREF, "void f()", asMETHODPR(Text3D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void AddVertexLight(Light@+)", asMETHODPR(Text3D, AddVertexLight, (Light*), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "void AllocateNetworkState()", asMETHODPR(Text3D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void Text3D::ApplyAttributes() override | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void ApplyAttributes()", asMETHODPR(Text3D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(Text3D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "bool DrawOcclusion(OcclusionBuffer@+)", asMETHODPR(Text3D, DrawOcclusion, (OcclusionBuffer*), bool), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "bool GetAnimationEnabled() const", asMETHODPR(Text3D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool get_animationEnabled() const", asMETHODPR(Text3D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "Variant GetAttribute(uint) const", asMETHODPR(Text3D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "Variant get_attributes(uint) const", asMETHODPR(Text3D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "Variant GetAttribute(const String&in) const", asMETHODPR(Text3D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(Text3D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(Text3D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(Text3D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(Text3D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "Variant GetAttributeDefault(uint) const", asMETHODPR(Text3D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "Variant get_attributeDefaults(uint) const", asMETHODPR(Text3D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Text3D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "bool GetBlockEvents() const", asMETHODPR(Text3D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "const BoundingBox& GetBoundingBox() const", asMETHODPR(Text3D, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "const BoundingBox& get_boundingBox() const", asMETHODPR(Text3D, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "bool GetCastShadows() const", asMETHODPR(Text3D, GetCastShadows, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool get_castShadows() const", asMETHODPR(Text3D, GetCastShadows, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "const String& GetCategory() const", asMETHODPR(Text3D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "const String& get_category() const", asMETHODPR(Text3D, GetCategory, () const, const String&), asCALL_THISCALL);
    // Vector2 Text3D::GetCharPosition(unsigned index) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "Vector2 GetCharPosition(uint)", asMETHODPR(Text3D, GetCharPosition, (unsigned), Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "Vector2 get_charPositions(uint)", asMETHODPR(Text3D, GetCharPosition, (unsigned), Vector2), asCALL_THISCALL);
    // Vector2 Text3D::GetCharSize(unsigned index) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "Vector2 GetCharSize(uint)", asMETHODPR(Text3D, GetCharSize, (unsigned), Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "Vector2 get_charSizes(uint)", asMETHODPR(Text3D, GetCharSize, (unsigned), Vector2), asCALL_THISCALL);
    // const Color& Text3D::GetColor(Corner corner) const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "const Color& GetColor(Corner) const", asMETHODPR(Text3D, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "const Color& get_colors(Corner) const", asMETHODPR(Text3D, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    // const Color& Text3D::GetColorAttr() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "const Color& GetColorAttr() const", asMETHODPR(Text3D, GetColorAttr, () const, const Color&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "Component@+ GetComponent(StringHash) const", asMETHODPR(Text3D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // float Drawable::GetDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "float GetDistance() const", asMETHODPR(Text3D, GetDistance, () const, float), asCALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "uint8 GetDrawableFlags() const", asMETHODPR(Text3D, GetDrawableFlags, () const, unsigned char), asCALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "float GetDrawDistance() const", asMETHODPR(Text3D, GetDrawDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "float get_drawDistance() const", asMETHODPR(Text3D, GetDrawDistance, () const, float), asCALL_THISCALL);
    // const Color& Text3D::GetEffectColor() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "const Color& GetEffectColor() const", asMETHODPR(Text3D, GetEffectColor, () const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "const Color& get_effectColor() const", asMETHODPR(Text3D, GetEffectColor, () const, const Color&), asCALL_THISCALL);
    // float Text3D::GetEffectDepthBias() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "float GetEffectDepthBias() const", asMETHODPR(Text3D, GetEffectDepthBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "float get_effectDepthBias() const", asMETHODPR(Text3D, GetEffectDepthBias, () const, float), asCALL_THISCALL);
    // bool Text3D::GetEffectRoundStroke() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "bool GetEffectRoundStroke() const", asMETHODPR(Text3D, GetEffectRoundStroke, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool get_effectRoundStroke() const", asMETHODPR(Text3D, GetEffectRoundStroke, () const, bool), asCALL_THISCALL);
    // const IntVector2& Text3D::GetEffectShadowOffset() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "const IntVector2& GetEffectShadowOffset() const", asMETHODPR(Text3D, GetEffectShadowOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "const IntVector2& get_effectShadowOffset() const", asMETHODPR(Text3D, GetEffectShadowOffset, () const, const IntVector2&), asCALL_THISCALL);
    // int Text3D::GetEffectStrokeThickness() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "int GetEffectStrokeThickness() const", asMETHODPR(Text3D, GetEffectStrokeThickness, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "int get_effectStrokeThickness() const", asMETHODPR(Text3D, GetEffectStrokeThickness, () const, int), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "VariantMap& GetEventDataMap() const", asMETHODPR(Text3D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "Object@+ GetEventSender() const", asMETHODPR(Text3D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // FaceCameraMode Text3D::GetFaceCameraMode() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "FaceCameraMode GetFaceCameraMode() const", asMETHODPR(Text3D, GetFaceCameraMode, () const, FaceCameraMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "FaceCameraMode get_faceCameraMode() const", asMETHODPR(Text3D, GetFaceCameraMode, () const, FaceCameraMode), asCALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "Light@+ GetFirstLight() const", asMETHODPR(Text3D, GetFirstLight, () const, Light*), asCALL_THISCALL);
    // Font* Text3D::GetFont() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "Font@+ GetFont() const", asMETHODPR(Text3D, GetFont, () const, Font*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "Font@+ get_font() const", asMETHODPR(Text3D, GetFont, () const, Font*), asCALL_THISCALL);
    // ResourceRef Text3D::GetFontAttr() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "ResourceRef GetFontAttr() const", asMETHODPR(Text3D, GetFontAttr, () const, ResourceRef), asCALL_THISCALL);
    // float Text3D::GetFontSize() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "float GetFontSize() const", asMETHODPR(Text3D, GetFontSize, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "float get_fontSize() const", asMETHODPR(Text3D, GetFontSize, () const, float), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Text3D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Text3D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "const VariantMap& GetGlobalVars() const", asMETHODPR(Text3D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "const VariantMap& get_globalVars() const", asMETHODPR(Text3D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int Text3D::GetHeight() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "int GetHeight() const", asMETHODPR(Text3D, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "int get_height() const", asMETHODPR(Text3D, GetHeight, () const, int), asCALL_THISCALL);
    // HorizontalAlignment Text3D::GetHorizontalAlignment() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "HorizontalAlignment GetHorizontalAlignment() const", asMETHODPR(Text3D, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "HorizontalAlignment get_horizontalAlignment() const", asMETHODPR(Text3D, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "uint GetID() const", asMETHODPR(Text3D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "uint get_id() const", asMETHODPR(Text3D, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Text3D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "uint GetLightMask() const", asMETHODPR(Text3D, GetLightMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "uint get_lightMask() const", asMETHODPR(Text3D, GetLightMask, () const, unsigned), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "Array<Light@>@ GetLights() const", asFUNCTION(Text3D_GetLights_void), asCALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "float GetLodBias() const", asMETHODPR(Text3D, GetLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "float get_lodBias() const", asMETHODPR(Text3D, GetLodBias, () const, float), asCALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "float GetLodDistance() const", asMETHODPR(Text3D, GetLodDistance, () const, float), asCALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "Geometry@+ GetLodGeometry(uint, uint)", asMETHODPR(Text3D, GetLodGeometry, (unsigned, unsigned), Geometry*), asCALL_THISCALL);
    // Material* Text3D::GetMaterial() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "Material@+ GetMaterial() const", asMETHODPR(Text3D, GetMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "Material@+ get_material() const", asMETHODPR(Text3D, GetMaterial, () const, Material*), asCALL_THISCALL);
    // ResourceRef Text3D::GetMaterialAttr() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "ResourceRef GetMaterialAttr() const", asMETHODPR(Text3D, GetMaterialAttr, () const, ResourceRef), asCALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "uint GetMaxLights() const", asMETHODPR(Text3D, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "uint get_maxLights() const", asMETHODPR(Text3D, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "float GetMaxZ() const", asMETHODPR(Text3D, GetMaxZ, () const, float), asCALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "float GetMinZ() const", asMETHODPR(Text3D, GetMinZ, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "Node@+ GetNode() const", asMETHODPR(Text3D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "Node@+ get_node() const", asMETHODPR(Text3D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "uint GetNumAttributes() const", asMETHODPR(Text3D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "uint get_numAttributes() const", asMETHODPR(Text3D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Text3D::GetNumChars() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "uint GetNumChars() const", asMETHODPR(Text3D, GetNumChars, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "uint get_numChars() const", asMETHODPR(Text3D, GetNumChars, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "uint GetNumNetworkAttributes() const", asMETHODPR(Text3D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "uint GetNumOccluderTriangles()", asMETHODPR(Text3D, GetNumOccluderTriangles, (), unsigned), asCALL_THISCALL);
    // unsigned Text3D::GetNumRows() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "uint GetNumRows() const", asMETHODPR(Text3D, GetNumRows, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "uint get_numRows() const", asMETHODPR(Text3D, GetNumRows, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(Text3D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(Text3D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(Text3D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // float Text3D::GetOpacity() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "float GetOpacity() const", asMETHODPR(Text3D, GetOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "float get_opacity() const", asMETHODPR(Text3D, GetOpacity, () const, float), asCALL_THISCALL);
    // int Text3D::GetRowHeight() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "int GetRowHeight() const", asMETHODPR(Text3D, GetRowHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "int get_rowHeight() const", asMETHODPR(Text3D, GetRowHeight, () const, int), asCALL_THISCALL);
    // float Text3D::GetRowSpacing() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "float GetRowSpacing() const", asMETHODPR(Text3D, GetRowSpacing, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "float get_rowSpacing() const", asMETHODPR(Text3D, GetRowSpacing, () const, float), asCALL_THISCALL);
    // int Text3D::GetRowWidth(unsigned index) const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "int GetRowWidth(uint) const", asMETHODPR(Text3D, GetRowWidth, (unsigned) const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "int get_rowWidths(uint) const", asMETHODPR(Text3D, GetRowWidth, (unsigned) const, int), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "Scene@+ GetScene() const", asMETHODPR(Text3D, GetScene, () const, Scene*), asCALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "float GetShadowDistance() const", asMETHODPR(Text3D, GetShadowDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "float get_shadowDistance() const", asMETHODPR(Text3D, GetShadowDistance, () const, float), asCALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "uint GetShadowMask() const", asMETHODPR(Text3D, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "uint get_shadowMask() const", asMETHODPR(Text3D, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "float GetSortValue() const", asMETHODPR(Text3D, GetSortValue, () const, float), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Text3D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const String& Text3D::GetText() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "const String& GetText() const", asMETHODPR(Text3D, GetText, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "const String& get_text() const", asMETHODPR(Text3D, GetText, () const, const String&), asCALL_THISCALL);
    // HorizontalAlignment Text3D::GetTextAlignment() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "HorizontalAlignment GetTextAlignment() const", asMETHODPR(Text3D, GetTextAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "HorizontalAlignment get_textAlignment() const", asMETHODPR(Text3D, GetTextAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    // String Text3D::GetTextAttr() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "String GetTextAttr() const", asMETHODPR(Text3D, GetTextAttr, () const, String), asCALL_THISCALL);
    // TextEffect Text3D::GetTextEffect() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "TextEffect GetTextEffect() const", asMETHODPR(Text3D, GetTextEffect, () const, TextEffect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "TextEffect get_textEffect() const", asMETHODPR(Text3D, GetTextEffect, () const, TextEffect), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "StringHash GetType() const", asMETHODPR(Text3D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "StringHash get_type() const", asMETHODPR(Text3D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "const String& GetTypeName() const", asMETHODPR(Text3D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "const String& get_typeName() const", asMETHODPR(Text3D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // UpdateGeometryType Text3D::GetUpdateGeometryType() override | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "UpdateGeometryType GetUpdateGeometryType()", asMETHODPR(Text3D, GetUpdateGeometryType, (), UpdateGeometryType), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "Array<Light@>@ GetVertexLights() const", asFUNCTION(Text3D_GetVertexLights_void), asCALL_CDECL_OBJFIRST);
    // VerticalAlignment Text3D::GetVerticalAlignment() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "VerticalAlignment GetVerticalAlignment() const", asMETHODPR(Text3D, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "VerticalAlignment get_verticalAlignment() const", asMETHODPR(Text3D, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "uint GetViewMask() const", asMETHODPR(Text3D, GetViewMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "uint get_viewMask() const", asMETHODPR(Text3D, GetViewMask, () const, unsigned), asCALL_THISCALL);
    // int Text3D::GetWidth() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "int GetWidth() const", asMETHODPR(Text3D, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "int get_width() const", asMETHODPR(Text3D, GetWidth, () const, int), asCALL_THISCALL);
    // bool Text3D::GetWordwrap() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "bool GetWordwrap() const", asMETHODPR(Text3D, GetWordwrap, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool get_wordwrap() const", asMETHODPR(Text3D, GetWordwrap, () const, bool), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "const BoundingBox& GetWorldBoundingBox()", asMETHODPR(Text3D, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "const BoundingBox& get_worldBoundingBox()", asMETHODPR(Text3D, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "Zone@+ GetZone() const", asMETHODPR(Text3D, GetZone, () const, Zone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "Zone@+ get_zone() const", asMETHODPR(Text3D, GetZone, () const, Zone*), asCALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "uint GetZoneMask() const", asMETHODPR(Text3D, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "uint get_zoneMask() const", asMETHODPR(Text3D, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "bool HasBasePass(uint) const", asMETHODPR(Text3D, HasBasePass, (unsigned) const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "bool HasEventHandlers() const", asMETHODPR(Text3D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Text3D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Text3D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "bool IsEnabled() const", asMETHODPR(Text3D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool get_enabled() const", asMETHODPR(Text3D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "bool IsEnabledEffective() const", asMETHODPR(Text3D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool get_enabledEffective() const", asMETHODPR(Text3D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Text3D::IsFixedScreenSize() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "bool IsFixedScreenSize() const", asMETHODPR(Text3D, IsFixedScreenSize, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool get_fixedScreenSize() const", asMETHODPR(Text3D, IsFixedScreenSize, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "bool IsInstanceOf(StringHash) const", asMETHODPR(Text3D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "bool IsInView() const", asMETHODPR(Text3D, IsInView, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool get_inView() const", asMETHODPR(Text3D, IsInView, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "bool IsInView(Camera@+) const", asMETHODPR(Text3D, IsInView, (Camera*) const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "bool IsInView(const FrameInfo&in, bool = false) const", asMETHODPR(Text3D, IsInView, (const FrameInfo&, bool) const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "bool IsOccludee() const", asMETHODPR(Text3D, IsOccludee, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool get_occludee() const", asMETHODPR(Text3D, IsOccludee, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "bool IsOccluder() const", asMETHODPR(Text3D, IsOccluder, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool get_occluder() const", asMETHODPR(Text3D, IsOccluder, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "bool IsReplicated() const", asMETHODPR(Text3D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool get_replicated() const", asMETHODPR(Text3D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "bool IsTemporary() const", asMETHODPR(Text3D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool get_temporary() const", asMETHODPR(Text3D, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "bool IsZoneDirty() const", asMETHODPR(Text3D, IsZoneDirty, () const, bool), asCALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void LimitLights()", asMETHODPR(Text3D, LimitLights, (), void), asCALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void LimitVertexLights(bool)", asMETHODPR(Text3D, LimitVertexLights, (bool), void), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "bool Load(Deserializer&)", asMETHODPR(Text3D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Text3D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "bool LoadXML(const XMLElement&in)", asMETHODPR(Text3D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void MarkForUpdate()", asMETHODPR(Text3D, MarkForUpdate, (), void), asCALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void MarkInView(const FrameInfo&in)", asMETHODPR(Text3D, MarkInView, (const FrameInfo&), void), asCALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void MarkInView(uint)", asMETHODPR(Text3D, MarkInView, (unsigned), void), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "void MarkNetworkUpdate()", asMETHODPR(Text3D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Text3D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Text3D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Text3D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Drawable::OnSetEnabled() override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void OnSetEnabled()", asMETHODPR(Text3D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "void PrepareNetworkUpdate()", asMETHODPR(Text3D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) | File: ../Graphics/Drawable.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Text3D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Text3D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Text3D", "int Refs() const", asMETHODPR(Text3D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "int get_refs() const", asMETHODPR(Text3D, Refs, () const, int), asCALL_THISCALL);
    // static void Text3D::RegisterObject(Context* context) | File: ../UI/Text3D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Text3D", asBEHAVE_RELEASE, "void f()", asMETHODPR(Text3D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "void Remove()", asMETHODPR(Text3D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(Text3D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "void RemoveInstanceDefault()", asMETHODPR(Text3D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "void RemoveObjectAnimation()", asMETHODPR(Text3D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "void ResetToDefault()", asMETHODPR(Text3D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "bool Save(Serializer&) const", asMETHODPR(Text3D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "bool SaveDefaultAttributes() const", asMETHODPR(Text3D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "bool SaveJSON(JSONValue&) const", asMETHODPR(Text3D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "bool SaveXML(XMLElement&) const", asMETHODPR(Text3D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "void SendEvent(StringHash)", asMETHODPR(Text3D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Text3D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Text3D::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", asMETHODPR(Text3D, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "void SetAnimationEnabled(bool)", asMETHODPR(Text3D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_animationEnabled(bool)", asMETHODPR(Text3D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "void SetAnimationTime(float)", asMETHODPR(Text3D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Text3D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Text3D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Text3D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Text3D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(Text3D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(Text3D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Text3D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetBasePass(uint)", asMETHODPR(Text3D, SetBasePass, (unsigned), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "void SetBlockEvents(bool)", asMETHODPR(Text3D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetCastShadows(bool)", asMETHODPR(Text3D, SetCastShadows, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_castShadows(bool)", asMETHODPR(Text3D, SetCastShadows, (bool), void), asCALL_THISCALL);
    // void Text3D::SetColor(const Color& color) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetColor(const Color&in)", asMETHODPR(Text3D, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_color(const Color&in)", asMETHODPR(Text3D, SetColor, (const Color&), void), asCALL_THISCALL);
    // void Text3D::SetColor(Corner corner, const Color& color) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetColor(Corner, const Color&in)", asMETHODPR(Text3D, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_colors(Corner, const Color&in)", asMETHODPR(Text3D, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetDrawDistance(float)", asMETHODPR(Text3D, SetDrawDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_drawDistance(float)", asMETHODPR(Text3D, SetDrawDistance, (float), void), asCALL_THISCALL);
    // void Text3D::SetEffectColor(const Color& effectColor) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetEffectColor(const Color&in)", asMETHODPR(Text3D, SetEffectColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_effectColor(const Color&in)", asMETHODPR(Text3D, SetEffectColor, (const Color&), void), asCALL_THISCALL);
    // void Text3D::SetEffectDepthBias(float bias) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetEffectDepthBias(float)", asMETHODPR(Text3D, SetEffectDepthBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_effectDepthBias(float)", asMETHODPR(Text3D, SetEffectDepthBias, (float), void), asCALL_THISCALL);
    // void Text3D::SetEffectRoundStroke(bool roundStroke) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetEffectRoundStroke(bool)", asMETHODPR(Text3D, SetEffectRoundStroke, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_effectRoundStroke(bool)", asMETHODPR(Text3D, SetEffectRoundStroke, (bool), void), asCALL_THISCALL);
    // void Text3D::SetEffectShadowOffset(const IntVector2& offset) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetEffectShadowOffset(const IntVector2&in)", asMETHODPR(Text3D, SetEffectShadowOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_effectShadowOffset(const IntVector2&in)", asMETHODPR(Text3D, SetEffectShadowOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void Text3D::SetEffectStrokeThickness(int thickness) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetEffectStrokeThickness(int)", asMETHODPR(Text3D, SetEffectStrokeThickness, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_effectStrokeThickness(int)", asMETHODPR(Text3D, SetEffectStrokeThickness, (int), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "void SetEnabled(bool)", asMETHODPR(Text3D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_enabled(bool)", asMETHODPR(Text3D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Text3D::SetFaceCameraMode(FaceCameraMode mode) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetFaceCameraMode(FaceCameraMode)", asMETHODPR(Text3D, SetFaceCameraMode, (FaceCameraMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_faceCameraMode(FaceCameraMode)", asMETHODPR(Text3D, SetFaceCameraMode, (FaceCameraMode), void), asCALL_THISCALL);
    // void Text3D::SetFixedScreenSize(bool enable) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetFixedScreenSize(bool)", asMETHODPR(Text3D, SetFixedScreenSize, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_fixedScreenSize(bool)", asMETHODPR(Text3D, SetFixedScreenSize, (bool), void), asCALL_THISCALL);
    // bool Text3D::SetFont(const String& fontName, float size=DEFAULT_FONT_SIZE) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "bool SetFont(const String&in, float = DEFAULT_FONT_SIZE)", asMETHODPR(Text3D, SetFont, (const String&, float), bool), asCALL_THISCALL);
    // bool Text3D::SetFont(Font* font, float size=DEFAULT_FONT_SIZE) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "bool SetFont(Font@+, float = DEFAULT_FONT_SIZE)", asMETHODPR(Text3D, SetFont, (Font*, float), bool), asCALL_THISCALL);
    // void Text3D::SetFontAttr(const ResourceRef& value) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetFontAttr(const ResourceRef&in)", asMETHODPR(Text3D, SetFontAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // bool Text3D::SetFontSize(float size) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "bool SetFontSize(float)", asMETHODPR(Text3D, SetFontSize, (float), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool set_fontSize(float)", asMETHODPR(Text3D, SetFontSize, (float), bool), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Text3D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Text3D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Text3D::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetHorizontalAlignment(HorizontalAlignment)", asMETHODPR(Text3D, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_horizontalAlignment(HorizontalAlignment)", asMETHODPR(Text3D, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "void SetInstanceDefault(bool)", asMETHODPR(Text3D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Text3D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetLightMask(uint)", asMETHODPR(Text3D, SetLightMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_lightMask(uint)", asMETHODPR(Text3D, SetLightMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetLodBias(float)", asMETHODPR(Text3D, SetLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_lodBias(float)", asMETHODPR(Text3D, SetLodBias, (float), void), asCALL_THISCALL);
    // void Text3D::SetMaterial(Material* material) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetMaterial(Material@+)", asMETHODPR(Text3D, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_material(Material@+)", asMETHODPR(Text3D, SetMaterial, (Material*), void), asCALL_THISCALL);
    // void Text3D::SetMaterialAttr(const ResourceRef& value) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetMaterialAttr(const ResourceRef&in)", asMETHODPR(Text3D, SetMaterialAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetMaxLights(uint)", asMETHODPR(Text3D, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_maxLights(uint)", asMETHODPR(Text3D, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetMinMaxZ(float, float)", asMETHODPR(Text3D, SetMinMaxZ, (float, float), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(Text3D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(Text3D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(Text3D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetOccludee(bool)", asMETHODPR(Text3D, SetOccludee, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_occludee(bool)", asMETHODPR(Text3D, SetOccludee, (bool), void), asCALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetOccluder(bool)", asMETHODPR(Text3D, SetOccluder, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_occluder(bool)", asMETHODPR(Text3D, SetOccluder, (bool), void), asCALL_THISCALL);
    // void Text3D::SetOpacity(float opacity) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetOpacity(float)", asMETHODPR(Text3D, SetOpacity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_opacity(float)", asMETHODPR(Text3D, SetOpacity, (float), void), asCALL_THISCALL);
    // void Text3D::SetRowSpacing(float spacing) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetRowSpacing(float)", asMETHODPR(Text3D, SetRowSpacing, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_rowSpacing(float)", asMETHODPR(Text3D, SetRowSpacing, (float), void), asCALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetShadowDistance(float)", asMETHODPR(Text3D, SetShadowDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_shadowDistance(float)", asMETHODPR(Text3D, SetShadowDistance, (float), void), asCALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetShadowMask(uint)", asMETHODPR(Text3D, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_shadowMask(uint)", asMETHODPR(Text3D, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetSortValue(float)", asMETHODPR(Text3D, SetSortValue, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "void SetTemporary(bool)", asMETHODPR(Text3D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_temporary(bool)", asMETHODPR(Text3D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Text3D::SetText(const String& text) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetText(const String&in)", asMETHODPR(Text3D, SetText, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_text(const String&in)", asMETHODPR(Text3D, SetText, (const String&), void), asCALL_THISCALL);
    // void Text3D::SetTextAlignment(HorizontalAlignment align) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetTextAlignment(HorizontalAlignment)", asMETHODPR(Text3D, SetTextAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_textAlignment(HorizontalAlignment)", asMETHODPR(Text3D, SetTextAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    // void Text3D::SetTextAttr(const String& value) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetTextAttr(const String&in)", asMETHODPR(Text3D, SetTextAttr, (const String&), void), asCALL_THISCALL);
    // void Text3D::SetTextEffect(TextEffect textEffect) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetTextEffect(TextEffect)", asMETHODPR(Text3D, SetTextEffect, (TextEffect), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_textEffect(TextEffect)", asMETHODPR(Text3D, SetTextEffect, (TextEffect), void), asCALL_THISCALL);
    // void Text3D::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetVerticalAlignment(VerticalAlignment)", asMETHODPR(Text3D, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_verticalAlignment(VerticalAlignment)", asMETHODPR(Text3D, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetViewMask(uint)", asMETHODPR(Text3D, SetViewMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_viewMask(uint)", asMETHODPR(Text3D, SetViewMask, (unsigned), void), asCALL_THISCALL);
    // void Text3D::SetWidth(int width) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetWidth(int)", asMETHODPR(Text3D, SetWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_width(int)", asMETHODPR(Text3D, SetWidth, (int), void), asCALL_THISCALL);
    // void Text3D::SetWordwrap(bool enable) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetWordwrap(bool)", asMETHODPR(Text3D, SetWordwrap, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_wordwrap(bool)", asMETHODPR(Text3D, SetWordwrap, (bool), void), asCALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetZone(Zone@+, bool = false)", asMETHODPR(Text3D, SetZone, (Zone*, bool), void), asCALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetZoneMask(uint)", asMETHODPR(Text3D, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_zoneMask(uint)", asMETHODPR(Text3D, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit Text3D::Text3D(Context* context) | File: ../UI/Text3D.h
    engine->RegisterObjectBehaviour("Text3D", asBEHAVE_FACTORY, "Text3D@+ f()", asFUNCTION(Text3D_Text3D_Context), asCALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "void UnsubscribeFromAllEvents()", asMETHODPR(Text3D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Text3D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Text3D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Text3D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Text3D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void Update(const FrameInfo&in)", asMETHODPR(Text3D, Update, (const FrameInfo&), void), asCALL_THISCALL);
    // void Text3D::UpdateBatches(const FrameInfo& frame) override | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void UpdateBatches(const FrameInfo&in)", asMETHODPR(Text3D, UpdateBatches, (const FrameInfo&), void), asCALL_THISCALL);
    // void Text3D::UpdateGeometry(const FrameInfo& frame) override | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void UpdateGeometry(const FrameInfo&in)", asMETHODPR(Text3D, UpdateGeometry, (const FrameInfo&), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Text3D", "int WeakRefs() const", asMETHODPR(Text3D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "int get_weakRefs() const", asMETHODPR(Text3D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Text3D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Text3D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Text3D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Drawable
    REGISTER_MANUAL_PART_Drawable(Text3D, "Text3D")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(Text3D, "Text3D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(Text3D, "Text3D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Text3D, "Text3D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Text3D, "Text3D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Text3D, "Text3D")
#endif
#ifdef REGISTER_MANUAL_PART_Text3D
    REGISTER_MANUAL_PART_Text3D(Text3D, "Text3D")
#endif
    RegisterSubclass<Drawable, Text3D>(engine, "Drawable", "Text3D");
    RegisterSubclass<Component, Text3D>(engine, "Component", "Text3D");
    RegisterSubclass<Animatable, Text3D>(engine, "Animatable", "Text3D");
    RegisterSubclass<Serializable, Text3D>(engine, "Serializable", "Text3D");
    RegisterSubclass<Object, Text3D>(engine, "Object", "Text3D");
    RegisterSubclass<RefCounted, Text3D>(engine, "RefCounted", "Text3D");

    // void ResourceWithMetadata::AddMetadata(const String& name, const Variant& value) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "void AddMetadata(const String&in, const Variant&in)", asMETHODPR(Texture, AddMetadata, (const String&, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "void set_metadata(const String&in, const Variant&in)", asMETHODPR(Texture, AddMetadata, (const String&, const Variant&), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Texture", asBEHAVE_ADDREF, "void f()", asMETHODPR(Texture, AddRef, (), void), asCALL_THISCALL);
    // virtual bool Resource::BeginLoad(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "bool BeginLoad(Deserializer&)", asMETHODPR(Texture, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // static unsigned Texture::CheckMaxLevels(int width, int height, unsigned requestedLevels) | File: ../Graphics/Texture.h
    engine->SetDefaultNamespace("Texture");
    engine->RegisterGlobalFunction("uint CheckMaxLevels(int, int, uint)", asFUNCTIONPR(Texture::CheckMaxLevels, (int, int, unsigned), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Texture::CheckMaxLevels(int width, int height, int depth, unsigned requestedLevels) | File: ../Graphics/Texture.h
    engine->SetDefaultNamespace("Texture");
    engine->RegisterGlobalFunction("uint CheckMaxLevels(int, int, int, uint)", asFUNCTIONPR(Texture::CheckMaxLevels, (int, int, int, unsigned), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // void GPUObject::ClearDataLost() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture", "void ClearDataLost()", asMETHODPR(Texture, ClearDataLost, (), void), asCALL_THISCALL);
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "bool EndLoad()", asMETHODPR(Texture, EndLoad, (), bool), asCALL_THISCALL);
    // TextureAddressMode Texture::GetAddressMode(TextureCoordinate coord) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "TextureAddressMode GetAddressMode(TextureCoordinate) const", asMETHODPR(Texture, GetAddressMode, (TextureCoordinate) const, TextureAddressMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "TextureAddressMode get_addressMode(TextureCoordinate) const", asMETHODPR(Texture, GetAddressMode, (TextureCoordinate) const, TextureAddressMode), asCALL_THISCALL);
    // unsigned Texture::GetAnisotropy() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "uint GetAnisotropy() const", asMETHODPR(Texture, GetAnisotropy, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "uint get_anisotropy() const", asMETHODPR(Texture, GetAnisotropy, () const, unsigned), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(Texture, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // bool Texture::GetAutoResolve() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "bool GetAutoResolve() const", asMETHODPR(Texture, GetAutoResolve, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "bool get_autoResolve() const", asMETHODPR(Texture, GetAutoResolve, () const, bool), asCALL_THISCALL);
    // Texture* Texture::GetBackupTexture() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "Texture@+ GetBackupTexture() const", asMETHODPR(Texture, GetBackupTexture, () const, Texture*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "Texture@+ get_backupTexture() const", asMETHODPR(Texture, GetBackupTexture, () const, Texture*), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "bool GetBlockEvents() const", asMETHODPR(Texture, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const Color& Texture::GetBorderColor() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "const Color& GetBorderColor() const", asMETHODPR(Texture, GetBorderColor, () const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "const Color& get_borderColor() const", asMETHODPR(Texture, GetBorderColor, () const, const Color&), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "const String& GetCategory() const", asMETHODPR(Texture, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "const String& get_category() const", asMETHODPR(Texture, GetCategory, () const, const String&), asCALL_THISCALL);
    // unsigned Texture::GetComponents() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "uint GetComponents() const", asMETHODPR(Texture, GetComponents, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "uint get_components() const", asMETHODPR(Texture, GetComponents, () const, unsigned), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // unsigned Texture::GetDataSize(int width, int height) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "uint GetDataSize(int, int) const", asMETHODPR(Texture, GetDataSize, (int, int) const, unsigned), asCALL_THISCALL);
    // unsigned Texture::GetDataSize(int width, int height, int depth) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "uint GetDataSize(int, int, int) const", asMETHODPR(Texture, GetDataSize, (int, int, int) const, unsigned), asCALL_THISCALL);
    // static unsigned Texture::GetDataType(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // int Texture::GetDepth() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "int GetDepth() const", asMETHODPR(Texture, GetDepth, () const, int), asCALL_THISCALL);
    // static unsigned Texture::GetDSVFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "VariantMap& GetEventDataMap() const", asMETHODPR(Texture, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "Object@+ GetEventSender() const", asMETHODPR(Texture, GetEventSender, () const, Object*), asCALL_THISCALL);
    // static unsigned Texture::GetExternalFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // TextureFilterMode Texture::GetFilterMode() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "TextureFilterMode GetFilterMode() const", asMETHODPR(Texture, GetFilterMode, () const, TextureFilterMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "TextureFilterMode get_filterMode() const", asMETHODPR(Texture, GetFilterMode, () const, TextureFilterMode), asCALL_THISCALL);
    // unsigned Texture::GetFormat() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "uint GetFormat() const", asMETHODPR(Texture, GetFormat, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "uint get_format() const", asMETHODPR(Texture, GetFormat, () const, unsigned), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Texture, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Texture, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "const VariantMap& GetGlobalVars() const", asMETHODPR(Texture, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "const VariantMap& get_globalVars() const", asMETHODPR(Texture, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // void* GPUObject::GetGPUObject() const | File: ../Graphics/GPUObject.h
    // Error: type "void*" can not automatically bind
    // unsigned GPUObject::GetGPUObjectName() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture", "uint GetGPUObjectName() const", asMETHODPR(Texture, GetGPUObjectName, () const, unsigned), asCALL_THISCALL);
    // Graphics* GPUObject::GetGraphics() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture", "Graphics@+ GetGraphics() const", asMETHODPR(Texture, GetGraphics, () const, Graphics*), asCALL_THISCALL);
    // int Texture::GetHeight() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "int GetHeight() const", asMETHODPR(Texture, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "int get_height() const", asMETHODPR(Texture, GetHeight, () const, int), asCALL_THISCALL);
    // int Texture::GetLevelDepth(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "int GetLevelDepth(uint) const", asMETHODPR(Texture, GetLevelDepth, (unsigned) const, int), asCALL_THISCALL);
    // int Texture::GetLevelHeight(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "int GetLevelHeight(uint) const", asMETHODPR(Texture, GetLevelHeight, (unsigned) const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "int get_levelHeight(uint) const", asMETHODPR(Texture, GetLevelHeight, (unsigned) const, int), asCALL_THISCALL);
    // unsigned Texture::GetLevels() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "uint GetLevels() const", asMETHODPR(Texture, GetLevels, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "uint get_levels() const", asMETHODPR(Texture, GetLevels, () const, unsigned), asCALL_THISCALL);
    // bool Texture::GetLevelsDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "bool GetLevelsDirty() const", asMETHODPR(Texture, GetLevelsDirty, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "bool get_levelsDirty() const", asMETHODPR(Texture, GetLevelsDirty, () const, bool), asCALL_THISCALL);
    // int Texture::GetLevelWidth(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "int GetLevelWidth(uint) const", asMETHODPR(Texture, GetLevelWidth, (unsigned) const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "int get_levelWidth(uint) const", asMETHODPR(Texture, GetLevelWidth, (unsigned) const, int), asCALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "uint GetMemoryUse() const", asMETHODPR(Texture, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "uint get_memoryUse() const", asMETHODPR(Texture, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // const Variant& ResourceWithMetadata::GetMetadata(const String& name) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "const Variant& GetMetadata(const String&in) const", asMETHODPR(Texture, GetMetadata, (const String&) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "const Variant& get_metadata(const String&in) const", asMETHODPR(Texture, GetMetadata, (const String&) const, const Variant&), asCALL_THISCALL);
    // int Texture::GetMipsToSkip(MaterialQuality quality) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "int GetMipsToSkip(MaterialQuality) const", asMETHODPR(Texture, GetMipsToSkip, (MaterialQuality) const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "int get_mipsToSkip(MaterialQuality) const", asMETHODPR(Texture, GetMipsToSkip, (MaterialQuality) const, int), asCALL_THISCALL);
    // int Texture::GetMultiSample() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "int GetMultiSample() const", asMETHODPR(Texture, GetMultiSample, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "int get_multiSample() const", asMETHODPR(Texture, GetMultiSample, () const, int), asCALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "const String& GetName() const", asMETHODPR(Texture, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "const String& get_name() const", asMETHODPR(Texture, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "StringHash GetNameHash() const", asMETHODPR(Texture, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // bool Texture::GetParametersDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "bool GetParametersDirty() const", asMETHODPR(Texture, GetParametersDirty, () const, bool), asCALL_THISCALL);
    // void* Texture::GetResolveTexture() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // unsigned Texture::GetRowDataSize(int width) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "uint GetRowDataSize(int) const", asMETHODPR(Texture, GetRowDataSize, (int) const, unsigned), asCALL_THISCALL);
    // void* Texture::GetSampler() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // void* Texture::GetShaderResourceView() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // bool Texture::GetShadowCompare() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "bool GetShadowCompare() const", asMETHODPR(Texture, GetShadowCompare, () const, bool), asCALL_THISCALL);
    // bool Texture::GetSRGB() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "bool GetSRGB() const", asMETHODPR(Texture, GetSRGB, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "bool get_sRGB() const", asMETHODPR(Texture, GetSRGB, () const, bool), asCALL_THISCALL);
    // unsigned Texture::GetSRGBFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // static unsigned Texture::GetSRVFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Texture, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // unsigned Texture::GetTarget() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "uint GetTarget() const", asMETHODPR(Texture, GetTarget, () const, unsigned), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "StringHash GetType() const", asMETHODPR(Texture, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "StringHash get_type() const", asMETHODPR(Texture, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "const String& GetTypeName() const", asMETHODPR(Texture, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "const String& get_typeName() const", asMETHODPR(Texture, GetTypeName, () const, const String&), asCALL_THISCALL);
    // TextureUsage Texture::GetUsage() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "TextureUsage GetUsage() const", asMETHODPR(Texture, GetUsage, () const, TextureUsage), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "TextureUsage get_usage() const", asMETHODPR(Texture, GetUsage, () const, TextureUsage), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "uint GetUseTimer()", asMETHODPR(Texture, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "uint get_useTimer()", asMETHODPR(Texture, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // int Texture::GetWidth() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "int GetWidth() const", asMETHODPR(Texture, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "int get_width() const", asMETHODPR(Texture, GetWidth, () const, int), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "bool HasEventHandlers() const", asMETHODPR(Texture, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool ResourceWithMetadata::HasMetadata() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "bool HasMetadata() const", asMETHODPR(Texture, HasMetadata, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "bool get_hasMetadata() const", asMETHODPR(Texture, HasMetadata, () const, bool), asCALL_THISCALL);
    // bool GPUObject::HasPendingData() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture", "bool HasPendingData() const", asMETHODPR(Texture, HasPendingData, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Texture, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Texture, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Texture::IsCompressed() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "bool IsCompressed() const", asMETHODPR(Texture, IsCompressed, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "bool get_compressed() const", asMETHODPR(Texture, IsCompressed, () const, bool), asCALL_THISCALL);
    // bool GPUObject::IsDataLost() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture", "bool IsDataLost() const", asMETHODPR(Texture, IsDataLost, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "bool get_dataLost() const", asMETHODPR(Texture, IsDataLost, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "bool IsInstanceOf(StringHash) const", asMETHODPR(Texture, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Texture::IsResolveDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "bool IsResolveDirty() const", asMETHODPR(Texture, IsResolveDirty, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "bool get_resolveDirty() const", asMETHODPR(Texture, IsResolveDirty, () const, bool), asCALL_THISCALL);
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "bool Load(Deserializer&)", asMETHODPR(Texture, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "bool LoadFile(const String&in)", asMETHODPR(Texture, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "bool Load(const String&in)", asMETHODPR(Texture, LoadFile, (const String&), bool), asCALL_THISCALL);
    // virtual void GPUObject::OnDeviceLost() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture", "void OnDeviceLost()", asMETHODPR(Texture, OnDeviceLost, (), void), asCALL_THISCALL);
    // virtual void GPUObject::OnDeviceReset() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture", "void OnDeviceReset()", asMETHODPR(Texture, OnDeviceReset, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Texture, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Texture", "int Refs() const", asMETHODPR(Texture, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "int get_refs() const", asMETHODPR(Texture, Refs, () const, int), asCALL_THISCALL);
    // void Texture::RegenerateLevels() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void RegenerateLevels()", asMETHODPR(Texture, RegenerateLevels, (), void), asCALL_THISCALL);
    // virtual void GPUObject::Release() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture", "void Release()", asMETHODPR(Texture, Release, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Texture", asBEHAVE_RELEASE, "void f()", asMETHODPR(Texture, ReleaseRef, (), void), asCALL_THISCALL);
    // void ResourceWithMetadata::RemoveAllMetadata() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "void RemoveAllMetadata()", asMETHODPR(Texture, RemoveAllMetadata, (), void), asCALL_THISCALL);
    // void ResourceWithMetadata::RemoveMetadata(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "void RemoveMetadata(const String&in)", asMETHODPR(Texture, RemoveMetadata, (const String&), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "void ResetUseTimer()", asMETHODPR(Texture, ResetUseTimer, (), void), asCALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "bool Save(Serializer&) const", asMETHODPR(Texture, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "bool SaveFile(const String&in) const", asMETHODPR(Texture, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "bool Save(const String&in) const", asMETHODPR(Texture, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "void SendEvent(StringHash)", asMETHODPR(Texture, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Texture, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Texture::SetAddressMode(TextureCoordinate coord, TextureAddressMode mode) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetAddressMode(TextureCoordinate, TextureAddressMode)", asMETHODPR(Texture, SetAddressMode, (TextureCoordinate, TextureAddressMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "void set_addressMode(TextureCoordinate, TextureAddressMode)", asMETHODPR(Texture, SetAddressMode, (TextureCoordinate, TextureAddressMode), void), asCALL_THISCALL);
    // void Texture::SetAnisotropy(unsigned level) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetAnisotropy(uint)", asMETHODPR(Texture, SetAnisotropy, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "void set_anisotropy(uint)", asMETHODPR(Texture, SetAnisotropy, (unsigned), void), asCALL_THISCALL);
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(Texture, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void Texture::SetBackupTexture(Texture* texture) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetBackupTexture(Texture@+)", asMETHODPR(Texture, SetBackupTexture, (Texture*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "void set_backupTexture(Texture@+)", asMETHODPR(Texture, SetBackupTexture, (Texture*), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "void SetBlockEvents(bool)", asMETHODPR(Texture, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Texture::SetBorderColor(const Color& color) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetBorderColor(const Color&in)", asMETHODPR(Texture, SetBorderColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "void set_borderColor(const Color&in)", asMETHODPR(Texture, SetBorderColor, (const Color&), void), asCALL_THISCALL);
    // void Texture::SetFilterMode(TextureFilterMode mode) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetFilterMode(TextureFilterMode)", asMETHODPR(Texture, SetFilterMode, (TextureFilterMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "void set_filterMode(TextureFilterMode)", asMETHODPR(Texture, SetFilterMode, (TextureFilterMode), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Texture, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Texture, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Texture::SetLevelsDirty() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetLevelsDirty()", asMETHODPR(Texture, SetLevelsDirty, (), void), asCALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "void SetMemoryUse(uint)", asMETHODPR(Texture, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void Texture::SetMipsToSkip(MaterialQuality quality, int toSkip) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetMipsToSkip(MaterialQuality, int)", asMETHODPR(Texture, SetMipsToSkip, (MaterialQuality, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "void set_mipsToSkip(MaterialQuality, int)", asMETHODPR(Texture, SetMipsToSkip, (MaterialQuality, int), void), asCALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "void SetName(const String&in)", asMETHODPR(Texture, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "void set_name(const String&in)", asMETHODPR(Texture, SetName, (const String&), void), asCALL_THISCALL);
    // void Texture::SetNumLevels(unsigned levels) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetNumLevels(uint)", asMETHODPR(Texture, SetNumLevels, (unsigned), void), asCALL_THISCALL);
    // void Texture::SetParameters(XMLFile* file) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetParameters(XMLFile@+)", asMETHODPR(Texture, SetParameters, (XMLFile*), void), asCALL_THISCALL);
    // void Texture::SetParameters(const XMLElement& element) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetParameters(const XMLElement&in)", asMETHODPR(Texture, SetParameters, (const XMLElement&), void), asCALL_THISCALL);
    // void Texture::SetParametersDirty() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetParametersDirty()", asMETHODPR(Texture, SetParametersDirty, (), void), asCALL_THISCALL);
    // void Texture::SetResolveDirty(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetResolveDirty(bool)", asMETHODPR(Texture, SetResolveDirty, (bool), void), asCALL_THISCALL);
    // void Texture::SetShadowCompare(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetShadowCompare(bool)", asMETHODPR(Texture, SetShadowCompare, (bool), void), asCALL_THISCALL);
    // void Texture::SetSRGB(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetSRGB(bool)", asMETHODPR(Texture, SetSRGB, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "void set_sRGB(bool)", asMETHODPR(Texture, SetSRGB, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit Texture::Texture(Context* context) | File: ../Graphics/Texture.h
    engine->RegisterObjectBehaviour("Texture", asBEHAVE_FACTORY, "Texture@+ f()", asFUNCTION(Texture_Texture_Context), asCALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "void UnsubscribeFromAllEvents()", asMETHODPR(Texture, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Texture_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Texture, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Texture, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Texture, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void Texture::UpdateParameters() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void UpdateParameters()", asMETHODPR(Texture, UpdateParameters, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Texture", "int WeakRefs() const", asMETHODPR(Texture, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "int get_weakRefs() const", asMETHODPR(Texture, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_ResourceWithMetadata
    REGISTER_MANUAL_PART_ResourceWithMetadata(Texture, "Texture")
#endif
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(Texture, "Texture")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Texture, "Texture")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Texture, "Texture")
#endif
#ifdef REGISTER_MANUAL_PART_GPUObject
    REGISTER_MANUAL_PART_GPUObject(Texture, "Texture")
#endif
#ifdef REGISTER_MANUAL_PART_Texture
    REGISTER_MANUAL_PART_Texture(Texture, "Texture")
#endif
    RegisterSubclass<ResourceWithMetadata, Texture>(engine, "ResourceWithMetadata", "Texture");
    RegisterSubclass<Resource, Texture>(engine, "Resource", "Texture");
    RegisterSubclass<Object, Texture>(engine, "Object", "Texture");
    RegisterSubclass<RefCounted, Texture>(engine, "RefCounted", "Texture");

    // void ResourceWithMetadata::AddMetadata(const String& name, const Variant& value) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "void AddMetadata(const String&in, const Variant&in)", asMETHODPR(Texture2D, AddMetadata, (const String&, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "void set_metadata(const String&in, const Variant&in)", asMETHODPR(Texture2D, AddMetadata, (const String&, const Variant&), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Texture2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(Texture2D, AddRef, (), void), asCALL_THISCALL);
    // bool Texture2D::BeginLoad(Deserializer& source) override | File: ../Graphics/Texture2D.h
    engine->RegisterObjectMethod("Texture2D", "bool BeginLoad(Deserializer&)", asMETHODPR(Texture2D, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // static unsigned Texture::CheckMaxLevels(int width, int height, unsigned requestedLevels) | File: ../Graphics/Texture.h
    engine->SetDefaultNamespace("Texture2D");
    engine->RegisterGlobalFunction("uint CheckMaxLevels(int, int, uint)", asFUNCTIONPR(Texture2D::CheckMaxLevels, (int, int, unsigned), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Texture::CheckMaxLevels(int width, int height, int depth, unsigned requestedLevels) | File: ../Graphics/Texture.h
    engine->SetDefaultNamespace("Texture2D");
    engine->RegisterGlobalFunction("uint CheckMaxLevels(int, int, int, uint)", asFUNCTIONPR(Texture2D::CheckMaxLevels, (int, int, int, unsigned), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // void GPUObject::ClearDataLost() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture2D", "void ClearDataLost()", asMETHODPR(Texture2D, ClearDataLost, (), void), asCALL_THISCALL);
    // bool Texture2D::EndLoad() override | File: ../Graphics/Texture2D.h
    engine->RegisterObjectMethod("Texture2D", "bool EndLoad()", asMETHODPR(Texture2D, EndLoad, (), bool), asCALL_THISCALL);
    // TextureAddressMode Texture::GetAddressMode(TextureCoordinate coord) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "TextureAddressMode GetAddressMode(TextureCoordinate) const", asMETHODPR(Texture2D, GetAddressMode, (TextureCoordinate) const, TextureAddressMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "TextureAddressMode get_addressMode(TextureCoordinate) const", asMETHODPR(Texture2D, GetAddressMode, (TextureCoordinate) const, TextureAddressMode), asCALL_THISCALL);
    // unsigned Texture::GetAnisotropy() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "uint GetAnisotropy() const", asMETHODPR(Texture2D, GetAnisotropy, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "uint get_anisotropy() const", asMETHODPR(Texture2D, GetAnisotropy, () const, unsigned), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(Texture2D, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // bool Texture::GetAutoResolve() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "bool GetAutoResolve() const", asMETHODPR(Texture2D, GetAutoResolve, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "bool get_autoResolve() const", asMETHODPR(Texture2D, GetAutoResolve, () const, bool), asCALL_THISCALL);
    // Texture* Texture::GetBackupTexture() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "Texture@+ GetBackupTexture() const", asMETHODPR(Texture2D, GetBackupTexture, () const, Texture*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "Texture@+ get_backupTexture() const", asMETHODPR(Texture2D, GetBackupTexture, () const, Texture*), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "bool GetBlockEvents() const", asMETHODPR(Texture2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const Color& Texture::GetBorderColor() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "const Color& GetBorderColor() const", asMETHODPR(Texture2D, GetBorderColor, () const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "const Color& get_borderColor() const", asMETHODPR(Texture2D, GetBorderColor, () const, const Color&), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "const String& GetCategory() const", asMETHODPR(Texture2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "const String& get_category() const", asMETHODPR(Texture2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // unsigned Texture::GetComponents() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "uint GetComponents() const", asMETHODPR(Texture2D, GetComponents, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "uint get_components() const", asMETHODPR(Texture2D, GetComponents, () const, unsigned), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // bool Texture2D::GetData(unsigned level, void* dest) const | File: ../Graphics/Texture2D.h
    // Error: type "void*" can not automatically bind
    // unsigned Texture::GetDataSize(int width, int height) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "uint GetDataSize(int, int) const", asMETHODPR(Texture2D, GetDataSize, (int, int) const, unsigned), asCALL_THISCALL);
    // unsigned Texture::GetDataSize(int width, int height, int depth) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "uint GetDataSize(int, int, int) const", asMETHODPR(Texture2D, GetDataSize, (int, int, int) const, unsigned), asCALL_THISCALL);
    // static unsigned Texture::GetDataType(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // int Texture::GetDepth() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "int GetDepth() const", asMETHODPR(Texture2D, GetDepth, () const, int), asCALL_THISCALL);
    // static unsigned Texture::GetDSVFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "VariantMap& GetEventDataMap() const", asMETHODPR(Texture2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "Object@+ GetEventSender() const", asMETHODPR(Texture2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // static unsigned Texture::GetExternalFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // TextureFilterMode Texture::GetFilterMode() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "TextureFilterMode GetFilterMode() const", asMETHODPR(Texture2D, GetFilterMode, () const, TextureFilterMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "TextureFilterMode get_filterMode() const", asMETHODPR(Texture2D, GetFilterMode, () const, TextureFilterMode), asCALL_THISCALL);
    // unsigned Texture::GetFormat() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "uint GetFormat() const", asMETHODPR(Texture2D, GetFormat, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "uint get_format() const", asMETHODPR(Texture2D, GetFormat, () const, unsigned), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Texture2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Texture2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(Texture2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "const VariantMap& get_globalVars() const", asMETHODPR(Texture2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // void* GPUObject::GetGPUObject() const | File: ../Graphics/GPUObject.h
    // Error: type "void*" can not automatically bind
    // unsigned GPUObject::GetGPUObjectName() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture2D", "uint GetGPUObjectName() const", asMETHODPR(Texture2D, GetGPUObjectName, () const, unsigned), asCALL_THISCALL);
    // Graphics* GPUObject::GetGraphics() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture2D", "Graphics@+ GetGraphics() const", asMETHODPR(Texture2D, GetGraphics, () const, Graphics*), asCALL_THISCALL);
    // int Texture::GetHeight() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "int GetHeight() const", asMETHODPR(Texture2D, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "int get_height() const", asMETHODPR(Texture2D, GetHeight, () const, int), asCALL_THISCALL);
    // bool Texture2D::GetImage(Image& image) const | File: ../Graphics/Texture2D.h
    engine->RegisterObjectMethod("Texture2D", "bool GetImage(Image&) const", asMETHODPR(Texture2D, GetImage, (Image&) const, bool), asCALL_THISCALL);
    // SharedPtr<Image> Texture2D::GetImage() const | File: ../Graphics/Texture2D.h
    engine->RegisterObjectMethod("Texture2D", "Image@+ GetImage() const", asFUNCTION(Texture2D_GetImage_void), asCALL_CDECL_OBJFIRST);
    // int Texture::GetLevelDepth(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "int GetLevelDepth(uint) const", asMETHODPR(Texture2D, GetLevelDepth, (unsigned) const, int), asCALL_THISCALL);
    // int Texture::GetLevelHeight(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "int GetLevelHeight(uint) const", asMETHODPR(Texture2D, GetLevelHeight, (unsigned) const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "int get_levelHeight(uint) const", asMETHODPR(Texture2D, GetLevelHeight, (unsigned) const, int), asCALL_THISCALL);
    // unsigned Texture::GetLevels() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "uint GetLevels() const", asMETHODPR(Texture2D, GetLevels, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "uint get_levels() const", asMETHODPR(Texture2D, GetLevels, () const, unsigned), asCALL_THISCALL);
    // bool Texture::GetLevelsDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "bool GetLevelsDirty() const", asMETHODPR(Texture2D, GetLevelsDirty, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "bool get_levelsDirty() const", asMETHODPR(Texture2D, GetLevelsDirty, () const, bool), asCALL_THISCALL);
    // int Texture::GetLevelWidth(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "int GetLevelWidth(uint) const", asMETHODPR(Texture2D, GetLevelWidth, (unsigned) const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "int get_levelWidth(uint) const", asMETHODPR(Texture2D, GetLevelWidth, (unsigned) const, int), asCALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "uint GetMemoryUse() const", asMETHODPR(Texture2D, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "uint get_memoryUse() const", asMETHODPR(Texture2D, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // const Variant& ResourceWithMetadata::GetMetadata(const String& name) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "const Variant& GetMetadata(const String&in) const", asMETHODPR(Texture2D, GetMetadata, (const String&) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "const Variant& get_metadata(const String&in) const", asMETHODPR(Texture2D, GetMetadata, (const String&) const, const Variant&), asCALL_THISCALL);
    // int Texture::GetMipsToSkip(MaterialQuality quality) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "int GetMipsToSkip(MaterialQuality) const", asMETHODPR(Texture2D, GetMipsToSkip, (MaterialQuality) const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "int get_mipsToSkip(MaterialQuality) const", asMETHODPR(Texture2D, GetMipsToSkip, (MaterialQuality) const, int), asCALL_THISCALL);
    // int Texture::GetMultiSample() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "int GetMultiSample() const", asMETHODPR(Texture2D, GetMultiSample, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "int get_multiSample() const", asMETHODPR(Texture2D, GetMultiSample, () const, int), asCALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "const String& GetName() const", asMETHODPR(Texture2D, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "const String& get_name() const", asMETHODPR(Texture2D, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "StringHash GetNameHash() const", asMETHODPR(Texture2D, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // bool Texture::GetParametersDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "bool GetParametersDirty() const", asMETHODPR(Texture2D, GetParametersDirty, () const, bool), asCALL_THISCALL);
    // RenderSurface* Texture2D::GetRenderSurface() const | File: ../Graphics/Texture2D.h
    engine->RegisterObjectMethod("Texture2D", "RenderSurface@+ GetRenderSurface() const", asMETHODPR(Texture2D, GetRenderSurface, () const, RenderSurface*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "RenderSurface@+ get_renderSurface() const", asMETHODPR(Texture2D, GetRenderSurface, () const, RenderSurface*), asCALL_THISCALL);
    // void* Texture::GetResolveTexture() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // unsigned Texture::GetRowDataSize(int width) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "uint GetRowDataSize(int) const", asMETHODPR(Texture2D, GetRowDataSize, (int) const, unsigned), asCALL_THISCALL);
    // void* Texture::GetSampler() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // void* Texture::GetShaderResourceView() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // bool Texture::GetShadowCompare() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "bool GetShadowCompare() const", asMETHODPR(Texture2D, GetShadowCompare, () const, bool), asCALL_THISCALL);
    // bool Texture::GetSRGB() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "bool GetSRGB() const", asMETHODPR(Texture2D, GetSRGB, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "bool get_sRGB() const", asMETHODPR(Texture2D, GetSRGB, () const, bool), asCALL_THISCALL);
    // unsigned Texture::GetSRGBFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // static unsigned Texture::GetSRVFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Texture2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // unsigned Texture::GetTarget() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "uint GetTarget() const", asMETHODPR(Texture2D, GetTarget, () const, unsigned), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "StringHash GetType() const", asMETHODPR(Texture2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "StringHash get_type() const", asMETHODPR(Texture2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "const String& GetTypeName() const", asMETHODPR(Texture2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "const String& get_typeName() const", asMETHODPR(Texture2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // TextureUsage Texture::GetUsage() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "TextureUsage GetUsage() const", asMETHODPR(Texture2D, GetUsage, () const, TextureUsage), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "TextureUsage get_usage() const", asMETHODPR(Texture2D, GetUsage, () const, TextureUsage), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "uint GetUseTimer()", asMETHODPR(Texture2D, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "uint get_useTimer()", asMETHODPR(Texture2D, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // int Texture::GetWidth() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "int GetWidth() const", asMETHODPR(Texture2D, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "int get_width() const", asMETHODPR(Texture2D, GetWidth, () const, int), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "bool HasEventHandlers() const", asMETHODPR(Texture2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool ResourceWithMetadata::HasMetadata() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "bool HasMetadata() const", asMETHODPR(Texture2D, HasMetadata, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "bool get_hasMetadata() const", asMETHODPR(Texture2D, HasMetadata, () const, bool), asCALL_THISCALL);
    // bool GPUObject::HasPendingData() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture2D", "bool HasPendingData() const", asMETHODPR(Texture2D, HasPendingData, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Texture2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Texture2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Texture::IsCompressed() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "bool IsCompressed() const", asMETHODPR(Texture2D, IsCompressed, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "bool get_compressed() const", asMETHODPR(Texture2D, IsCompressed, () const, bool), asCALL_THISCALL);
    // bool GPUObject::IsDataLost() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture2D", "bool IsDataLost() const", asMETHODPR(Texture2D, IsDataLost, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "bool get_dataLost() const", asMETHODPR(Texture2D, IsDataLost, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(Texture2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Texture::IsResolveDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "bool IsResolveDirty() const", asMETHODPR(Texture2D, IsResolveDirty, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "bool get_resolveDirty() const", asMETHODPR(Texture2D, IsResolveDirty, () const, bool), asCALL_THISCALL);
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "bool Load(Deserializer&)", asMETHODPR(Texture2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "bool LoadFile(const String&in)", asMETHODPR(Texture2D, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "bool Load(const String&in)", asMETHODPR(Texture2D, LoadFile, (const String&), bool), asCALL_THISCALL);
    // void Texture2D::OnDeviceLost() override | File: ../Graphics/Texture2D.h
    engine->RegisterObjectMethod("Texture2D", "void OnDeviceLost()", asMETHODPR(Texture2D, OnDeviceLost, (), void), asCALL_THISCALL);
    // void Texture2D::OnDeviceReset() override | File: ../Graphics/Texture2D.h
    engine->RegisterObjectMethod("Texture2D", "void OnDeviceReset()", asMETHODPR(Texture2D, OnDeviceReset, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Texture2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Texture2D", "int Refs() const", asMETHODPR(Texture2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "int get_refs() const", asMETHODPR(Texture2D, Refs, () const, int), asCALL_THISCALL);
    // void Texture::RegenerateLevels() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void RegenerateLevels()", asMETHODPR(Texture2D, RegenerateLevels, (), void), asCALL_THISCALL);
    // static void Texture2D::RegisterObject(Context* context) | File: ../Graphics/Texture2D.h
    // Not registered because have @nobind mark
    // void Texture2D::Release() override | File: ../Graphics/Texture2D.h
    engine->RegisterObjectMethod("Texture2D", "void Release()", asMETHODPR(Texture2D, Release, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Texture2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(Texture2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void ResourceWithMetadata::RemoveAllMetadata() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "void RemoveAllMetadata()", asMETHODPR(Texture2D, RemoveAllMetadata, (), void), asCALL_THISCALL);
    // void ResourceWithMetadata::RemoveMetadata(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "void RemoveMetadata(const String&in)", asMETHODPR(Texture2D, RemoveMetadata, (const String&), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "void ResetUseTimer()", asMETHODPR(Texture2D, ResetUseTimer, (), void), asCALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "bool Save(Serializer&) const", asMETHODPR(Texture2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "bool SaveFile(const String&in) const", asMETHODPR(Texture2D, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "bool Save(const String&in) const", asMETHODPR(Texture2D, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "void SendEvent(StringHash)", asMETHODPR(Texture2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Texture2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Texture::SetAddressMode(TextureCoordinate coord, TextureAddressMode mode) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetAddressMode(TextureCoordinate, TextureAddressMode)", asMETHODPR(Texture2D, SetAddressMode, (TextureCoordinate, TextureAddressMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "void set_addressMode(TextureCoordinate, TextureAddressMode)", asMETHODPR(Texture2D, SetAddressMode, (TextureCoordinate, TextureAddressMode), void), asCALL_THISCALL);
    // void Texture::SetAnisotropy(unsigned level) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetAnisotropy(uint)", asMETHODPR(Texture2D, SetAnisotropy, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "void set_anisotropy(uint)", asMETHODPR(Texture2D, SetAnisotropy, (unsigned), void), asCALL_THISCALL);
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(Texture2D, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void Texture::SetBackupTexture(Texture* texture) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetBackupTexture(Texture@+)", asMETHODPR(Texture2D, SetBackupTexture, (Texture*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "void set_backupTexture(Texture@+)", asMETHODPR(Texture2D, SetBackupTexture, (Texture*), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "void SetBlockEvents(bool)", asMETHODPR(Texture2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Texture::SetBorderColor(const Color& color) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetBorderColor(const Color&in)", asMETHODPR(Texture2D, SetBorderColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "void set_borderColor(const Color&in)", asMETHODPR(Texture2D, SetBorderColor, (const Color&), void), asCALL_THISCALL);
    // bool Texture2D::SetData(unsigned level, int x, int y, int width, int height, const void* data) | File: ../Graphics/Texture2D.h
    // Error: type "const void*" can not automatically bind
    // bool Texture2D::SetData(Image* image, bool useAlpha=false) | File: ../Graphics/Texture2D.h
    engine->RegisterObjectMethod("Texture2D", "bool SetData(Image@+, bool = false)", asMETHODPR(Texture2D, SetData, (Image*, bool), bool), asCALL_THISCALL);
    // void Texture::SetFilterMode(TextureFilterMode mode) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetFilterMode(TextureFilterMode)", asMETHODPR(Texture2D, SetFilterMode, (TextureFilterMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "void set_filterMode(TextureFilterMode)", asMETHODPR(Texture2D, SetFilterMode, (TextureFilterMode), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Texture2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Texture2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Texture::SetLevelsDirty() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetLevelsDirty()", asMETHODPR(Texture2D, SetLevelsDirty, (), void), asCALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "void SetMemoryUse(uint)", asMETHODPR(Texture2D, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void Texture::SetMipsToSkip(MaterialQuality quality, int toSkip) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetMipsToSkip(MaterialQuality, int)", asMETHODPR(Texture2D, SetMipsToSkip, (MaterialQuality, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "void set_mipsToSkip(MaterialQuality, int)", asMETHODPR(Texture2D, SetMipsToSkip, (MaterialQuality, int), void), asCALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "void SetName(const String&in)", asMETHODPR(Texture2D, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "void set_name(const String&in)", asMETHODPR(Texture2D, SetName, (const String&), void), asCALL_THISCALL);
    // void Texture::SetNumLevels(unsigned levels) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetNumLevels(uint)", asMETHODPR(Texture2D, SetNumLevels, (unsigned), void), asCALL_THISCALL);
    // void Texture::SetParameters(XMLFile* file) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetParameters(XMLFile@+)", asMETHODPR(Texture2D, SetParameters, (XMLFile*), void), asCALL_THISCALL);
    // void Texture::SetParameters(const XMLElement& element) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetParameters(const XMLElement&in)", asMETHODPR(Texture2D, SetParameters, (const XMLElement&), void), asCALL_THISCALL);
    // void Texture::SetParametersDirty() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetParametersDirty()", asMETHODPR(Texture2D, SetParametersDirty, (), void), asCALL_THISCALL);
    // void Texture::SetResolveDirty(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetResolveDirty(bool)", asMETHODPR(Texture2D, SetResolveDirty, (bool), void), asCALL_THISCALL);
    // void Texture::SetShadowCompare(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetShadowCompare(bool)", asMETHODPR(Texture2D, SetShadowCompare, (bool), void), asCALL_THISCALL);
    // bool Texture2D::SetSize(int width, int height, unsigned format, TextureUsage usage=TEXTURE_STATIC, int multiSample=1, bool autoResolve=true) | File: ../Graphics/Texture2D.h
    engine->RegisterObjectMethod("Texture2D", "bool SetSize(int, int, uint, TextureUsage = TEXTURE_STATIC, int = 1, bool = true)", asMETHODPR(Texture2D, SetSize, (int, int, unsigned, TextureUsage, int, bool), bool), asCALL_THISCALL);
    // void Texture::SetSRGB(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetSRGB(bool)", asMETHODPR(Texture2D, SetSRGB, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "void set_sRGB(bool)", asMETHODPR(Texture2D, SetSRGB, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit Texture2D::Texture2D(Context* context) | File: ../Graphics/Texture2D.h
    engine->RegisterObjectBehaviour("Texture2D", asBEHAVE_FACTORY, "Texture2D@+ f()", asFUNCTION(Texture2D_Texture2D_Context), asCALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "void UnsubscribeFromAllEvents()", asMETHODPR(Texture2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Texture2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Texture2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Texture2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Texture2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void Texture::UpdateParameters() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void UpdateParameters()", asMETHODPR(Texture2D, UpdateParameters, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Texture2D", "int WeakRefs() const", asMETHODPR(Texture2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "int get_weakRefs() const", asMETHODPR(Texture2D, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Texture
    REGISTER_MANUAL_PART_Texture(Texture2D, "Texture2D")
#endif
#ifdef REGISTER_MANUAL_PART_ResourceWithMetadata
    REGISTER_MANUAL_PART_ResourceWithMetadata(Texture2D, "Texture2D")
#endif
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(Texture2D, "Texture2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Texture2D, "Texture2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Texture2D, "Texture2D")
#endif
#ifdef REGISTER_MANUAL_PART_GPUObject
    REGISTER_MANUAL_PART_GPUObject(Texture2D, "Texture2D")
#endif
#ifdef REGISTER_MANUAL_PART_Texture2D
    REGISTER_MANUAL_PART_Texture2D(Texture2D, "Texture2D")
#endif
    RegisterSubclass<Texture, Texture2D>(engine, "Texture", "Texture2D");
    RegisterSubclass<ResourceWithMetadata, Texture2D>(engine, "ResourceWithMetadata", "Texture2D");
    RegisterSubclass<Resource, Texture2D>(engine, "Resource", "Texture2D");
    RegisterSubclass<Object, Texture2D>(engine, "Object", "Texture2D");
    RegisterSubclass<RefCounted, Texture2D>(engine, "RefCounted", "Texture2D");

    // void ResourceWithMetadata::AddMetadata(const String& name, const Variant& value) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "void AddMetadata(const String&in, const Variant&in)", asMETHODPR(Texture2DArray, AddMetadata, (const String&, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "void set_metadata(const String&in, const Variant&in)", asMETHODPR(Texture2DArray, AddMetadata, (const String&, const Variant&), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Texture2DArray", asBEHAVE_ADDREF, "void f()", asMETHODPR(Texture2DArray, AddRef, (), void), asCALL_THISCALL);
    // bool Texture2DArray::BeginLoad(Deserializer& source) override | File: ../Graphics/Texture2DArray.h
    engine->RegisterObjectMethod("Texture2DArray", "bool BeginLoad(Deserializer&)", asMETHODPR(Texture2DArray, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // static unsigned Texture::CheckMaxLevels(int width, int height, unsigned requestedLevels) | File: ../Graphics/Texture.h
    engine->SetDefaultNamespace("Texture2DArray");
    engine->RegisterGlobalFunction("uint CheckMaxLevels(int, int, uint)", asFUNCTIONPR(Texture2DArray::CheckMaxLevels, (int, int, unsigned), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Texture::CheckMaxLevels(int width, int height, int depth, unsigned requestedLevels) | File: ../Graphics/Texture.h
    engine->SetDefaultNamespace("Texture2DArray");
    engine->RegisterGlobalFunction("uint CheckMaxLevels(int, int, int, uint)", asFUNCTIONPR(Texture2DArray::CheckMaxLevels, (int, int, int, unsigned), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // void GPUObject::ClearDataLost() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture2DArray", "void ClearDataLost()", asMETHODPR(Texture2DArray, ClearDataLost, (), void), asCALL_THISCALL);
    // bool Texture2DArray::EndLoad() override | File: ../Graphics/Texture2DArray.h
    engine->RegisterObjectMethod("Texture2DArray", "bool EndLoad()", asMETHODPR(Texture2DArray, EndLoad, (), bool), asCALL_THISCALL);
    // TextureAddressMode Texture::GetAddressMode(TextureCoordinate coord) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "TextureAddressMode GetAddressMode(TextureCoordinate) const", asMETHODPR(Texture2DArray, GetAddressMode, (TextureCoordinate) const, TextureAddressMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "TextureAddressMode get_addressMode(TextureCoordinate) const", asMETHODPR(Texture2DArray, GetAddressMode, (TextureCoordinate) const, TextureAddressMode), asCALL_THISCALL);
    // unsigned Texture::GetAnisotropy() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "uint GetAnisotropy() const", asMETHODPR(Texture2DArray, GetAnisotropy, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "uint get_anisotropy() const", asMETHODPR(Texture2DArray, GetAnisotropy, () const, unsigned), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(Texture2DArray, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // bool Texture::GetAutoResolve() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "bool GetAutoResolve() const", asMETHODPR(Texture2DArray, GetAutoResolve, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "bool get_autoResolve() const", asMETHODPR(Texture2DArray, GetAutoResolve, () const, bool), asCALL_THISCALL);
    // Texture* Texture::GetBackupTexture() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "Texture@+ GetBackupTexture() const", asMETHODPR(Texture2DArray, GetBackupTexture, () const, Texture*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "Texture@+ get_backupTexture() const", asMETHODPR(Texture2DArray, GetBackupTexture, () const, Texture*), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "bool GetBlockEvents() const", asMETHODPR(Texture2DArray, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const Color& Texture::GetBorderColor() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "const Color& GetBorderColor() const", asMETHODPR(Texture2DArray, GetBorderColor, () const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "const Color& get_borderColor() const", asMETHODPR(Texture2DArray, GetBorderColor, () const, const Color&), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "const String& GetCategory() const", asMETHODPR(Texture2DArray, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "const String& get_category() const", asMETHODPR(Texture2DArray, GetCategory, () const, const String&), asCALL_THISCALL);
    // unsigned Texture::GetComponents() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "uint GetComponents() const", asMETHODPR(Texture2DArray, GetComponents, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "uint get_components() const", asMETHODPR(Texture2DArray, GetComponents, () const, unsigned), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // bool Texture2DArray::GetData(unsigned layer, unsigned level, void* dest) const | File: ../Graphics/Texture2DArray.h
    // Error: type "void*" can not automatically bind
    // unsigned Texture::GetDataSize(int width, int height) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "uint GetDataSize(int, int) const", asMETHODPR(Texture2DArray, GetDataSize, (int, int) const, unsigned), asCALL_THISCALL);
    // unsigned Texture::GetDataSize(int width, int height, int depth) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "uint GetDataSize(int, int, int) const", asMETHODPR(Texture2DArray, GetDataSize, (int, int, int) const, unsigned), asCALL_THISCALL);
    // static unsigned Texture::GetDataType(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // int Texture::GetDepth() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "int GetDepth() const", asMETHODPR(Texture2DArray, GetDepth, () const, int), asCALL_THISCALL);
    // static unsigned Texture::GetDSVFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "VariantMap& GetEventDataMap() const", asMETHODPR(Texture2DArray, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "Object@+ GetEventSender() const", asMETHODPR(Texture2DArray, GetEventSender, () const, Object*), asCALL_THISCALL);
    // static unsigned Texture::GetExternalFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // TextureFilterMode Texture::GetFilterMode() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "TextureFilterMode GetFilterMode() const", asMETHODPR(Texture2DArray, GetFilterMode, () const, TextureFilterMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "TextureFilterMode get_filterMode() const", asMETHODPR(Texture2DArray, GetFilterMode, () const, TextureFilterMode), asCALL_THISCALL);
    // unsigned Texture::GetFormat() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "uint GetFormat() const", asMETHODPR(Texture2DArray, GetFormat, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "uint get_format() const", asMETHODPR(Texture2DArray, GetFormat, () const, unsigned), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Texture2DArray, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Texture2DArray, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "const VariantMap& GetGlobalVars() const", asMETHODPR(Texture2DArray, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "const VariantMap& get_globalVars() const", asMETHODPR(Texture2DArray, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // void* GPUObject::GetGPUObject() const | File: ../Graphics/GPUObject.h
    // Error: type "void*" can not automatically bind
    // unsigned GPUObject::GetGPUObjectName() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture2DArray", "uint GetGPUObjectName() const", asMETHODPR(Texture2DArray, GetGPUObjectName, () const, unsigned), asCALL_THISCALL);
    // Graphics* GPUObject::GetGraphics() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture2DArray", "Graphics@+ GetGraphics() const", asMETHODPR(Texture2DArray, GetGraphics, () const, Graphics*), asCALL_THISCALL);
    // int Texture::GetHeight() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "int GetHeight() const", asMETHODPR(Texture2DArray, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "int get_height() const", asMETHODPR(Texture2DArray, GetHeight, () const, int), asCALL_THISCALL);
    // unsigned Texture2DArray::GetLayers() const | File: ../Graphics/Texture2DArray.h
    engine->RegisterObjectMethod("Texture2DArray", "uint GetLayers() const", asMETHODPR(Texture2DArray, GetLayers, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "uint get_layers() const", asMETHODPR(Texture2DArray, GetLayers, () const, unsigned), asCALL_THISCALL);
    // int Texture::GetLevelDepth(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "int GetLevelDepth(uint) const", asMETHODPR(Texture2DArray, GetLevelDepth, (unsigned) const, int), asCALL_THISCALL);
    // int Texture::GetLevelHeight(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "int GetLevelHeight(uint) const", asMETHODPR(Texture2DArray, GetLevelHeight, (unsigned) const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "int get_levelHeight(uint) const", asMETHODPR(Texture2DArray, GetLevelHeight, (unsigned) const, int), asCALL_THISCALL);
    // unsigned Texture::GetLevels() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "uint GetLevels() const", asMETHODPR(Texture2DArray, GetLevels, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "uint get_levels() const", asMETHODPR(Texture2DArray, GetLevels, () const, unsigned), asCALL_THISCALL);
    // bool Texture::GetLevelsDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "bool GetLevelsDirty() const", asMETHODPR(Texture2DArray, GetLevelsDirty, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "bool get_levelsDirty() const", asMETHODPR(Texture2DArray, GetLevelsDirty, () const, bool), asCALL_THISCALL);
    // int Texture::GetLevelWidth(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "int GetLevelWidth(uint) const", asMETHODPR(Texture2DArray, GetLevelWidth, (unsigned) const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "int get_levelWidth(uint) const", asMETHODPR(Texture2DArray, GetLevelWidth, (unsigned) const, int), asCALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "uint GetMemoryUse() const", asMETHODPR(Texture2DArray, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "uint get_memoryUse() const", asMETHODPR(Texture2DArray, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // const Variant& ResourceWithMetadata::GetMetadata(const String& name) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "const Variant& GetMetadata(const String&in) const", asMETHODPR(Texture2DArray, GetMetadata, (const String&) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "const Variant& get_metadata(const String&in) const", asMETHODPR(Texture2DArray, GetMetadata, (const String&) const, const Variant&), asCALL_THISCALL);
    // int Texture::GetMipsToSkip(MaterialQuality quality) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "int GetMipsToSkip(MaterialQuality) const", asMETHODPR(Texture2DArray, GetMipsToSkip, (MaterialQuality) const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "int get_mipsToSkip(MaterialQuality) const", asMETHODPR(Texture2DArray, GetMipsToSkip, (MaterialQuality) const, int), asCALL_THISCALL);
    // int Texture::GetMultiSample() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "int GetMultiSample() const", asMETHODPR(Texture2DArray, GetMultiSample, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "int get_multiSample() const", asMETHODPR(Texture2DArray, GetMultiSample, () const, int), asCALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "const String& GetName() const", asMETHODPR(Texture2DArray, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "const String& get_name() const", asMETHODPR(Texture2DArray, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "StringHash GetNameHash() const", asMETHODPR(Texture2DArray, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // bool Texture::GetParametersDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "bool GetParametersDirty() const", asMETHODPR(Texture2DArray, GetParametersDirty, () const, bool), asCALL_THISCALL);
    // RenderSurface* Texture2DArray::GetRenderSurface() const | File: ../Graphics/Texture2DArray.h
    engine->RegisterObjectMethod("Texture2DArray", "RenderSurface@+ GetRenderSurface() const", asMETHODPR(Texture2DArray, GetRenderSurface, () const, RenderSurface*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "RenderSurface@+ get_renderSurface() const", asMETHODPR(Texture2DArray, GetRenderSurface, () const, RenderSurface*), asCALL_THISCALL);
    // void* Texture::GetResolveTexture() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // unsigned Texture::GetRowDataSize(int width) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "uint GetRowDataSize(int) const", asMETHODPR(Texture2DArray, GetRowDataSize, (int) const, unsigned), asCALL_THISCALL);
    // void* Texture::GetSampler() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // void* Texture::GetShaderResourceView() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // bool Texture::GetShadowCompare() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "bool GetShadowCompare() const", asMETHODPR(Texture2DArray, GetShadowCompare, () const, bool), asCALL_THISCALL);
    // bool Texture::GetSRGB() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "bool GetSRGB() const", asMETHODPR(Texture2DArray, GetSRGB, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "bool get_sRGB() const", asMETHODPR(Texture2DArray, GetSRGB, () const, bool), asCALL_THISCALL);
    // unsigned Texture::GetSRGBFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // static unsigned Texture::GetSRVFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Texture2DArray, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // unsigned Texture::GetTarget() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "uint GetTarget() const", asMETHODPR(Texture2DArray, GetTarget, () const, unsigned), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "StringHash GetType() const", asMETHODPR(Texture2DArray, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "StringHash get_type() const", asMETHODPR(Texture2DArray, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "const String& GetTypeName() const", asMETHODPR(Texture2DArray, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "const String& get_typeName() const", asMETHODPR(Texture2DArray, GetTypeName, () const, const String&), asCALL_THISCALL);
    // TextureUsage Texture::GetUsage() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "TextureUsage GetUsage() const", asMETHODPR(Texture2DArray, GetUsage, () const, TextureUsage), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "TextureUsage get_usage() const", asMETHODPR(Texture2DArray, GetUsage, () const, TextureUsage), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "uint GetUseTimer()", asMETHODPR(Texture2DArray, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "uint get_useTimer()", asMETHODPR(Texture2DArray, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // int Texture::GetWidth() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "int GetWidth() const", asMETHODPR(Texture2DArray, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "int get_width() const", asMETHODPR(Texture2DArray, GetWidth, () const, int), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "bool HasEventHandlers() const", asMETHODPR(Texture2DArray, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool ResourceWithMetadata::HasMetadata() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "bool HasMetadata() const", asMETHODPR(Texture2DArray, HasMetadata, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "bool get_hasMetadata() const", asMETHODPR(Texture2DArray, HasMetadata, () const, bool), asCALL_THISCALL);
    // bool GPUObject::HasPendingData() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture2DArray", "bool HasPendingData() const", asMETHODPR(Texture2DArray, HasPendingData, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Texture2DArray, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Texture2DArray, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Texture::IsCompressed() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "bool IsCompressed() const", asMETHODPR(Texture2DArray, IsCompressed, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "bool get_compressed() const", asMETHODPR(Texture2DArray, IsCompressed, () const, bool), asCALL_THISCALL);
    // bool GPUObject::IsDataLost() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture2DArray", "bool IsDataLost() const", asMETHODPR(Texture2DArray, IsDataLost, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "bool get_dataLost() const", asMETHODPR(Texture2DArray, IsDataLost, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "bool IsInstanceOf(StringHash) const", asMETHODPR(Texture2DArray, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Texture::IsResolveDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "bool IsResolveDirty() const", asMETHODPR(Texture2DArray, IsResolveDirty, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "bool get_resolveDirty() const", asMETHODPR(Texture2DArray, IsResolveDirty, () const, bool), asCALL_THISCALL);
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "bool Load(Deserializer&)", asMETHODPR(Texture2DArray, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "bool LoadFile(const String&in)", asMETHODPR(Texture2DArray, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "bool Load(const String&in)", asMETHODPR(Texture2DArray, LoadFile, (const String&), bool), asCALL_THISCALL);
    // void Texture2DArray::OnDeviceLost() override | File: ../Graphics/Texture2DArray.h
    engine->RegisterObjectMethod("Texture2DArray", "void OnDeviceLost()", asMETHODPR(Texture2DArray, OnDeviceLost, (), void), asCALL_THISCALL);
    // void Texture2DArray::OnDeviceReset() override | File: ../Graphics/Texture2DArray.h
    engine->RegisterObjectMethod("Texture2DArray", "void OnDeviceReset()", asMETHODPR(Texture2DArray, OnDeviceReset, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Texture2DArray, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Texture2DArray", "int Refs() const", asMETHODPR(Texture2DArray, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "int get_refs() const", asMETHODPR(Texture2DArray, Refs, () const, int), asCALL_THISCALL);
    // void Texture::RegenerateLevels() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void RegenerateLevels()", asMETHODPR(Texture2DArray, RegenerateLevels, (), void), asCALL_THISCALL);
    // static void Texture2DArray::RegisterObject(Context* context) | File: ../Graphics/Texture2DArray.h
    // Not registered because have @nobind mark
    // void Texture2DArray::Release() override | File: ../Graphics/Texture2DArray.h
    engine->RegisterObjectMethod("Texture2DArray", "void Release()", asMETHODPR(Texture2DArray, Release, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Texture2DArray", asBEHAVE_RELEASE, "void f()", asMETHODPR(Texture2DArray, ReleaseRef, (), void), asCALL_THISCALL);
    // void ResourceWithMetadata::RemoveAllMetadata() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "void RemoveAllMetadata()", asMETHODPR(Texture2DArray, RemoveAllMetadata, (), void), asCALL_THISCALL);
    // void ResourceWithMetadata::RemoveMetadata(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "void RemoveMetadata(const String&in)", asMETHODPR(Texture2DArray, RemoveMetadata, (const String&), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "void ResetUseTimer()", asMETHODPR(Texture2DArray, ResetUseTimer, (), void), asCALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "bool Save(Serializer&) const", asMETHODPR(Texture2DArray, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "bool SaveFile(const String&in) const", asMETHODPR(Texture2DArray, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "bool Save(const String&in) const", asMETHODPR(Texture2DArray, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "void SendEvent(StringHash)", asMETHODPR(Texture2DArray, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Texture2DArray, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Texture::SetAddressMode(TextureCoordinate coord, TextureAddressMode mode) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetAddressMode(TextureCoordinate, TextureAddressMode)", asMETHODPR(Texture2DArray, SetAddressMode, (TextureCoordinate, TextureAddressMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "void set_addressMode(TextureCoordinate, TextureAddressMode)", asMETHODPR(Texture2DArray, SetAddressMode, (TextureCoordinate, TextureAddressMode), void), asCALL_THISCALL);
    // void Texture::SetAnisotropy(unsigned level) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetAnisotropy(uint)", asMETHODPR(Texture2DArray, SetAnisotropy, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "void set_anisotropy(uint)", asMETHODPR(Texture2DArray, SetAnisotropy, (unsigned), void), asCALL_THISCALL);
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(Texture2DArray, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void Texture::SetBackupTexture(Texture* texture) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetBackupTexture(Texture@+)", asMETHODPR(Texture2DArray, SetBackupTexture, (Texture*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "void set_backupTexture(Texture@+)", asMETHODPR(Texture2DArray, SetBackupTexture, (Texture*), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetBlockEvents(bool)", asMETHODPR(Texture2DArray, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Texture::SetBorderColor(const Color& color) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetBorderColor(const Color&in)", asMETHODPR(Texture2DArray, SetBorderColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "void set_borderColor(const Color&in)", asMETHODPR(Texture2DArray, SetBorderColor, (const Color&), void), asCALL_THISCALL);
    // bool Texture2DArray::SetData(unsigned layer, unsigned level, int x, int y, int width, int height, const void* data) | File: ../Graphics/Texture2DArray.h
    // Error: type "const void*" can not automatically bind
    // bool Texture2DArray::SetData(unsigned layer, Deserializer& source) | File: ../Graphics/Texture2DArray.h
    engine->RegisterObjectMethod("Texture2DArray", "bool SetData(uint, Deserializer&)", asMETHODPR(Texture2DArray, SetData, (unsigned, Deserializer&), bool), asCALL_THISCALL);
    // bool Texture2DArray::SetData(unsigned layer, Image* image, bool useAlpha=false) | File: ../Graphics/Texture2DArray.h
    engine->RegisterObjectMethod("Texture2DArray", "bool SetData(uint, Image@+, bool = false)", asMETHODPR(Texture2DArray, SetData, (unsigned, Image*, bool), bool), asCALL_THISCALL);
    // void Texture::SetFilterMode(TextureFilterMode mode) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetFilterMode(TextureFilterMode)", asMETHODPR(Texture2DArray, SetFilterMode, (TextureFilterMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "void set_filterMode(TextureFilterMode)", asMETHODPR(Texture2DArray, SetFilterMode, (TextureFilterMode), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Texture2DArray, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Texture2DArray, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Texture2DArray::SetLayers(unsigned layers) | File: ../Graphics/Texture2DArray.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetLayers(uint)", asMETHODPR(Texture2DArray, SetLayers, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "void set_layers(uint)", asMETHODPR(Texture2DArray, SetLayers, (unsigned), void), asCALL_THISCALL);
    // void Texture::SetLevelsDirty() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetLevelsDirty()", asMETHODPR(Texture2DArray, SetLevelsDirty, (), void), asCALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetMemoryUse(uint)", asMETHODPR(Texture2DArray, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void Texture::SetMipsToSkip(MaterialQuality quality, int toSkip) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetMipsToSkip(MaterialQuality, int)", asMETHODPR(Texture2DArray, SetMipsToSkip, (MaterialQuality, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "void set_mipsToSkip(MaterialQuality, int)", asMETHODPR(Texture2DArray, SetMipsToSkip, (MaterialQuality, int), void), asCALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetName(const String&in)", asMETHODPR(Texture2DArray, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "void set_name(const String&in)", asMETHODPR(Texture2DArray, SetName, (const String&), void), asCALL_THISCALL);
    // void Texture::SetNumLevels(unsigned levels) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetNumLevels(uint)", asMETHODPR(Texture2DArray, SetNumLevels, (unsigned), void), asCALL_THISCALL);
    // void Texture::SetParameters(XMLFile* file) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetParameters(XMLFile@+)", asMETHODPR(Texture2DArray, SetParameters, (XMLFile*), void), asCALL_THISCALL);
    // void Texture::SetParameters(const XMLElement& element) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetParameters(const XMLElement&in)", asMETHODPR(Texture2DArray, SetParameters, (const XMLElement&), void), asCALL_THISCALL);
    // void Texture::SetParametersDirty() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetParametersDirty()", asMETHODPR(Texture2DArray, SetParametersDirty, (), void), asCALL_THISCALL);
    // void Texture::SetResolveDirty(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetResolveDirty(bool)", asMETHODPR(Texture2DArray, SetResolveDirty, (bool), void), asCALL_THISCALL);
    // void Texture::SetShadowCompare(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetShadowCompare(bool)", asMETHODPR(Texture2DArray, SetShadowCompare, (bool), void), asCALL_THISCALL);
    // bool Texture2DArray::SetSize(unsigned layers, int width, int height, unsigned format, TextureUsage usage=TEXTURE_STATIC) | File: ../Graphics/Texture2DArray.h
    engine->RegisterObjectMethod("Texture2DArray", "bool SetSize(uint, int, int, uint, TextureUsage = TEXTURE_STATIC)", asMETHODPR(Texture2DArray, SetSize, (unsigned, int, int, unsigned, TextureUsage), bool), asCALL_THISCALL);
    // void Texture::SetSRGB(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetSRGB(bool)", asMETHODPR(Texture2DArray, SetSRGB, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "void set_sRGB(bool)", asMETHODPR(Texture2DArray, SetSRGB, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit Texture2DArray::Texture2DArray(Context* context) | File: ../Graphics/Texture2DArray.h
    engine->RegisterObjectBehaviour("Texture2DArray", asBEHAVE_FACTORY, "Texture2DArray@+ f()", asFUNCTION(Texture2DArray_Texture2DArray_Context), asCALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "void UnsubscribeFromAllEvents()", asMETHODPR(Texture2DArray, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Texture2DArray_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Texture2DArray, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Texture2DArray, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Texture2DArray, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void Texture::UpdateParameters() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void UpdateParameters()", asMETHODPR(Texture2DArray, UpdateParameters, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Texture2DArray", "int WeakRefs() const", asMETHODPR(Texture2DArray, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "int get_weakRefs() const", asMETHODPR(Texture2DArray, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Texture
    REGISTER_MANUAL_PART_Texture(Texture2DArray, "Texture2DArray")
#endif
#ifdef REGISTER_MANUAL_PART_ResourceWithMetadata
    REGISTER_MANUAL_PART_ResourceWithMetadata(Texture2DArray, "Texture2DArray")
#endif
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(Texture2DArray, "Texture2DArray")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Texture2DArray, "Texture2DArray")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Texture2DArray, "Texture2DArray")
#endif
#ifdef REGISTER_MANUAL_PART_GPUObject
    REGISTER_MANUAL_PART_GPUObject(Texture2DArray, "Texture2DArray")
#endif
#ifdef REGISTER_MANUAL_PART_Texture2DArray
    REGISTER_MANUAL_PART_Texture2DArray(Texture2DArray, "Texture2DArray")
#endif
    RegisterSubclass<Texture, Texture2DArray>(engine, "Texture", "Texture2DArray");
    RegisterSubclass<ResourceWithMetadata, Texture2DArray>(engine, "ResourceWithMetadata", "Texture2DArray");
    RegisterSubclass<Resource, Texture2DArray>(engine, "Resource", "Texture2DArray");
    RegisterSubclass<Object, Texture2DArray>(engine, "Object", "Texture2DArray");
    RegisterSubclass<RefCounted, Texture2DArray>(engine, "RefCounted", "Texture2DArray");

    // void ResourceWithMetadata::AddMetadata(const String& name, const Variant& value) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "void AddMetadata(const String&in, const Variant&in)", asMETHODPR(Texture3D, AddMetadata, (const String&, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "void set_metadata(const String&in, const Variant&in)", asMETHODPR(Texture3D, AddMetadata, (const String&, const Variant&), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Texture3D", asBEHAVE_ADDREF, "void f()", asMETHODPR(Texture3D, AddRef, (), void), asCALL_THISCALL);
    // bool Texture3D::BeginLoad(Deserializer& source) override | File: ../Graphics/Texture3D.h
    engine->RegisterObjectMethod("Texture3D", "bool BeginLoad(Deserializer&)", asMETHODPR(Texture3D, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // static unsigned Texture::CheckMaxLevels(int width, int height, unsigned requestedLevels) | File: ../Graphics/Texture.h
    engine->SetDefaultNamespace("Texture3D");
    engine->RegisterGlobalFunction("uint CheckMaxLevels(int, int, uint)", asFUNCTIONPR(Texture3D::CheckMaxLevels, (int, int, unsigned), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Texture::CheckMaxLevels(int width, int height, int depth, unsigned requestedLevels) | File: ../Graphics/Texture.h
    engine->SetDefaultNamespace("Texture3D");
    engine->RegisterGlobalFunction("uint CheckMaxLevels(int, int, int, uint)", asFUNCTIONPR(Texture3D::CheckMaxLevels, (int, int, int, unsigned), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // void GPUObject::ClearDataLost() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture3D", "void ClearDataLost()", asMETHODPR(Texture3D, ClearDataLost, (), void), asCALL_THISCALL);
    // bool Texture3D::EndLoad() override | File: ../Graphics/Texture3D.h
    engine->RegisterObjectMethod("Texture3D", "bool EndLoad()", asMETHODPR(Texture3D, EndLoad, (), bool), asCALL_THISCALL);
    // TextureAddressMode Texture::GetAddressMode(TextureCoordinate coord) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "TextureAddressMode GetAddressMode(TextureCoordinate) const", asMETHODPR(Texture3D, GetAddressMode, (TextureCoordinate) const, TextureAddressMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "TextureAddressMode get_addressMode(TextureCoordinate) const", asMETHODPR(Texture3D, GetAddressMode, (TextureCoordinate) const, TextureAddressMode), asCALL_THISCALL);
    // unsigned Texture::GetAnisotropy() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "uint GetAnisotropy() const", asMETHODPR(Texture3D, GetAnisotropy, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "uint get_anisotropy() const", asMETHODPR(Texture3D, GetAnisotropy, () const, unsigned), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(Texture3D, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // bool Texture::GetAutoResolve() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "bool GetAutoResolve() const", asMETHODPR(Texture3D, GetAutoResolve, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "bool get_autoResolve() const", asMETHODPR(Texture3D, GetAutoResolve, () const, bool), asCALL_THISCALL);
    // Texture* Texture::GetBackupTexture() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "Texture@+ GetBackupTexture() const", asMETHODPR(Texture3D, GetBackupTexture, () const, Texture*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "Texture@+ get_backupTexture() const", asMETHODPR(Texture3D, GetBackupTexture, () const, Texture*), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "bool GetBlockEvents() const", asMETHODPR(Texture3D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const Color& Texture::GetBorderColor() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "const Color& GetBorderColor() const", asMETHODPR(Texture3D, GetBorderColor, () const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "const Color& get_borderColor() const", asMETHODPR(Texture3D, GetBorderColor, () const, const Color&), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "const String& GetCategory() const", asMETHODPR(Texture3D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "const String& get_category() const", asMETHODPR(Texture3D, GetCategory, () const, const String&), asCALL_THISCALL);
    // unsigned Texture::GetComponents() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "uint GetComponents() const", asMETHODPR(Texture3D, GetComponents, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "uint get_components() const", asMETHODPR(Texture3D, GetComponents, () const, unsigned), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // bool Texture3D::GetData(unsigned level, void* dest) const | File: ../Graphics/Texture3D.h
    // Error: type "void*" can not automatically bind
    // unsigned Texture::GetDataSize(int width, int height) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "uint GetDataSize(int, int) const", asMETHODPR(Texture3D, GetDataSize, (int, int) const, unsigned), asCALL_THISCALL);
    // unsigned Texture::GetDataSize(int width, int height, int depth) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "uint GetDataSize(int, int, int) const", asMETHODPR(Texture3D, GetDataSize, (int, int, int) const, unsigned), asCALL_THISCALL);
    // static unsigned Texture::GetDataType(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // int Texture::GetDepth() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "int GetDepth() const", asMETHODPR(Texture3D, GetDepth, () const, int), asCALL_THISCALL);
    // static unsigned Texture::GetDSVFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "VariantMap& GetEventDataMap() const", asMETHODPR(Texture3D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "Object@+ GetEventSender() const", asMETHODPR(Texture3D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // static unsigned Texture::GetExternalFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // TextureFilterMode Texture::GetFilterMode() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "TextureFilterMode GetFilterMode() const", asMETHODPR(Texture3D, GetFilterMode, () const, TextureFilterMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "TextureFilterMode get_filterMode() const", asMETHODPR(Texture3D, GetFilterMode, () const, TextureFilterMode), asCALL_THISCALL);
    // unsigned Texture::GetFormat() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "uint GetFormat() const", asMETHODPR(Texture3D, GetFormat, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "uint get_format() const", asMETHODPR(Texture3D, GetFormat, () const, unsigned), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Texture3D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Texture3D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "const VariantMap& GetGlobalVars() const", asMETHODPR(Texture3D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "const VariantMap& get_globalVars() const", asMETHODPR(Texture3D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // void* GPUObject::GetGPUObject() const | File: ../Graphics/GPUObject.h
    // Error: type "void*" can not automatically bind
    // unsigned GPUObject::GetGPUObjectName() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture3D", "uint GetGPUObjectName() const", asMETHODPR(Texture3D, GetGPUObjectName, () const, unsigned), asCALL_THISCALL);
    // Graphics* GPUObject::GetGraphics() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture3D", "Graphics@+ GetGraphics() const", asMETHODPR(Texture3D, GetGraphics, () const, Graphics*), asCALL_THISCALL);
    // int Texture::GetHeight() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "int GetHeight() const", asMETHODPR(Texture3D, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "int get_height() const", asMETHODPR(Texture3D, GetHeight, () const, int), asCALL_THISCALL);
    // int Texture::GetLevelDepth(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "int GetLevelDepth(uint) const", asMETHODPR(Texture3D, GetLevelDepth, (unsigned) const, int), asCALL_THISCALL);
    // int Texture::GetLevelHeight(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "int GetLevelHeight(uint) const", asMETHODPR(Texture3D, GetLevelHeight, (unsigned) const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "int get_levelHeight(uint) const", asMETHODPR(Texture3D, GetLevelHeight, (unsigned) const, int), asCALL_THISCALL);
    // unsigned Texture::GetLevels() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "uint GetLevels() const", asMETHODPR(Texture3D, GetLevels, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "uint get_levels() const", asMETHODPR(Texture3D, GetLevels, () const, unsigned), asCALL_THISCALL);
    // bool Texture::GetLevelsDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "bool GetLevelsDirty() const", asMETHODPR(Texture3D, GetLevelsDirty, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "bool get_levelsDirty() const", asMETHODPR(Texture3D, GetLevelsDirty, () const, bool), asCALL_THISCALL);
    // int Texture::GetLevelWidth(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "int GetLevelWidth(uint) const", asMETHODPR(Texture3D, GetLevelWidth, (unsigned) const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "int get_levelWidth(uint) const", asMETHODPR(Texture3D, GetLevelWidth, (unsigned) const, int), asCALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "uint GetMemoryUse() const", asMETHODPR(Texture3D, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "uint get_memoryUse() const", asMETHODPR(Texture3D, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // const Variant& ResourceWithMetadata::GetMetadata(const String& name) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "const Variant& GetMetadata(const String&in) const", asMETHODPR(Texture3D, GetMetadata, (const String&) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "const Variant& get_metadata(const String&in) const", asMETHODPR(Texture3D, GetMetadata, (const String&) const, const Variant&), asCALL_THISCALL);
    // int Texture::GetMipsToSkip(MaterialQuality quality) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "int GetMipsToSkip(MaterialQuality) const", asMETHODPR(Texture3D, GetMipsToSkip, (MaterialQuality) const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "int get_mipsToSkip(MaterialQuality) const", asMETHODPR(Texture3D, GetMipsToSkip, (MaterialQuality) const, int), asCALL_THISCALL);
    // int Texture::GetMultiSample() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "int GetMultiSample() const", asMETHODPR(Texture3D, GetMultiSample, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "int get_multiSample() const", asMETHODPR(Texture3D, GetMultiSample, () const, int), asCALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "const String& GetName() const", asMETHODPR(Texture3D, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "const String& get_name() const", asMETHODPR(Texture3D, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "StringHash GetNameHash() const", asMETHODPR(Texture3D, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // bool Texture::GetParametersDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "bool GetParametersDirty() const", asMETHODPR(Texture3D, GetParametersDirty, () const, bool), asCALL_THISCALL);
    // void* Texture::GetResolveTexture() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // unsigned Texture::GetRowDataSize(int width) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "uint GetRowDataSize(int) const", asMETHODPR(Texture3D, GetRowDataSize, (int) const, unsigned), asCALL_THISCALL);
    // void* Texture::GetSampler() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // void* Texture::GetShaderResourceView() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // bool Texture::GetShadowCompare() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "bool GetShadowCompare() const", asMETHODPR(Texture3D, GetShadowCompare, () const, bool), asCALL_THISCALL);
    // bool Texture::GetSRGB() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "bool GetSRGB() const", asMETHODPR(Texture3D, GetSRGB, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "bool get_sRGB() const", asMETHODPR(Texture3D, GetSRGB, () const, bool), asCALL_THISCALL);
    // unsigned Texture::GetSRGBFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // static unsigned Texture::GetSRVFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Texture3D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // unsigned Texture::GetTarget() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "uint GetTarget() const", asMETHODPR(Texture3D, GetTarget, () const, unsigned), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "StringHash GetType() const", asMETHODPR(Texture3D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "StringHash get_type() const", asMETHODPR(Texture3D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "const String& GetTypeName() const", asMETHODPR(Texture3D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "const String& get_typeName() const", asMETHODPR(Texture3D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // TextureUsage Texture::GetUsage() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "TextureUsage GetUsage() const", asMETHODPR(Texture3D, GetUsage, () const, TextureUsage), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "TextureUsage get_usage() const", asMETHODPR(Texture3D, GetUsage, () const, TextureUsage), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "uint GetUseTimer()", asMETHODPR(Texture3D, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "uint get_useTimer()", asMETHODPR(Texture3D, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // int Texture::GetWidth() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "int GetWidth() const", asMETHODPR(Texture3D, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "int get_width() const", asMETHODPR(Texture3D, GetWidth, () const, int), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "bool HasEventHandlers() const", asMETHODPR(Texture3D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool ResourceWithMetadata::HasMetadata() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "bool HasMetadata() const", asMETHODPR(Texture3D, HasMetadata, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "bool get_hasMetadata() const", asMETHODPR(Texture3D, HasMetadata, () const, bool), asCALL_THISCALL);
    // bool GPUObject::HasPendingData() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture3D", "bool HasPendingData() const", asMETHODPR(Texture3D, HasPendingData, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Texture3D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Texture3D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Texture::IsCompressed() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "bool IsCompressed() const", asMETHODPR(Texture3D, IsCompressed, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "bool get_compressed() const", asMETHODPR(Texture3D, IsCompressed, () const, bool), asCALL_THISCALL);
    // bool GPUObject::IsDataLost() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture3D", "bool IsDataLost() const", asMETHODPR(Texture3D, IsDataLost, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "bool get_dataLost() const", asMETHODPR(Texture3D, IsDataLost, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "bool IsInstanceOf(StringHash) const", asMETHODPR(Texture3D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Texture::IsResolveDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "bool IsResolveDirty() const", asMETHODPR(Texture3D, IsResolveDirty, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "bool get_resolveDirty() const", asMETHODPR(Texture3D, IsResolveDirty, () const, bool), asCALL_THISCALL);
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "bool Load(Deserializer&)", asMETHODPR(Texture3D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "bool LoadFile(const String&in)", asMETHODPR(Texture3D, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "bool Load(const String&in)", asMETHODPR(Texture3D, LoadFile, (const String&), bool), asCALL_THISCALL);
    // void Texture3D::OnDeviceLost() override | File: ../Graphics/Texture3D.h
    engine->RegisterObjectMethod("Texture3D", "void OnDeviceLost()", asMETHODPR(Texture3D, OnDeviceLost, (), void), asCALL_THISCALL);
    // void Texture3D::OnDeviceReset() override | File: ../Graphics/Texture3D.h
    engine->RegisterObjectMethod("Texture3D", "void OnDeviceReset()", asMETHODPR(Texture3D, OnDeviceReset, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Texture3D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Texture3D", "int Refs() const", asMETHODPR(Texture3D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "int get_refs() const", asMETHODPR(Texture3D, Refs, () const, int), asCALL_THISCALL);
    // void Texture::RegenerateLevels() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void RegenerateLevels()", asMETHODPR(Texture3D, RegenerateLevels, (), void), asCALL_THISCALL);
    // static void Texture3D::RegisterObject(Context* context) | File: ../Graphics/Texture3D.h
    // Not registered because have @nobind mark
    // void Texture3D::Release() override | File: ../Graphics/Texture3D.h
    engine->RegisterObjectMethod("Texture3D", "void Release()", asMETHODPR(Texture3D, Release, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Texture3D", asBEHAVE_RELEASE, "void f()", asMETHODPR(Texture3D, ReleaseRef, (), void), asCALL_THISCALL);
    // void ResourceWithMetadata::RemoveAllMetadata() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "void RemoveAllMetadata()", asMETHODPR(Texture3D, RemoveAllMetadata, (), void), asCALL_THISCALL);
    // void ResourceWithMetadata::RemoveMetadata(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "void RemoveMetadata(const String&in)", asMETHODPR(Texture3D, RemoveMetadata, (const String&), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "void ResetUseTimer()", asMETHODPR(Texture3D, ResetUseTimer, (), void), asCALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "bool Save(Serializer&) const", asMETHODPR(Texture3D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "bool SaveFile(const String&in) const", asMETHODPR(Texture3D, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "bool Save(const String&in) const", asMETHODPR(Texture3D, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "void SendEvent(StringHash)", asMETHODPR(Texture3D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Texture3D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Texture::SetAddressMode(TextureCoordinate coord, TextureAddressMode mode) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetAddressMode(TextureCoordinate, TextureAddressMode)", asMETHODPR(Texture3D, SetAddressMode, (TextureCoordinate, TextureAddressMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "void set_addressMode(TextureCoordinate, TextureAddressMode)", asMETHODPR(Texture3D, SetAddressMode, (TextureCoordinate, TextureAddressMode), void), asCALL_THISCALL);
    // void Texture::SetAnisotropy(unsigned level) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetAnisotropy(uint)", asMETHODPR(Texture3D, SetAnisotropy, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "void set_anisotropy(uint)", asMETHODPR(Texture3D, SetAnisotropy, (unsigned), void), asCALL_THISCALL);
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(Texture3D, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void Texture::SetBackupTexture(Texture* texture) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetBackupTexture(Texture@+)", asMETHODPR(Texture3D, SetBackupTexture, (Texture*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "void set_backupTexture(Texture@+)", asMETHODPR(Texture3D, SetBackupTexture, (Texture*), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "void SetBlockEvents(bool)", asMETHODPR(Texture3D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Texture::SetBorderColor(const Color& color) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetBorderColor(const Color&in)", asMETHODPR(Texture3D, SetBorderColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "void set_borderColor(const Color&in)", asMETHODPR(Texture3D, SetBorderColor, (const Color&), void), asCALL_THISCALL);
    // bool Texture3D::SetData(unsigned level, int x, int y, int z, int width, int height, int depth, const void* data) | File: ../Graphics/Texture3D.h
    // Error: type "const void*" can not automatically bind
    // bool Texture3D::SetData(Image* image, bool useAlpha=false) | File: ../Graphics/Texture3D.h
    engine->RegisterObjectMethod("Texture3D", "bool SetData(Image@+, bool = false)", asMETHODPR(Texture3D, SetData, (Image*, bool), bool), asCALL_THISCALL);
    // void Texture::SetFilterMode(TextureFilterMode mode) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetFilterMode(TextureFilterMode)", asMETHODPR(Texture3D, SetFilterMode, (TextureFilterMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "void set_filterMode(TextureFilterMode)", asMETHODPR(Texture3D, SetFilterMode, (TextureFilterMode), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Texture3D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Texture3D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Texture::SetLevelsDirty() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetLevelsDirty()", asMETHODPR(Texture3D, SetLevelsDirty, (), void), asCALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "void SetMemoryUse(uint)", asMETHODPR(Texture3D, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void Texture::SetMipsToSkip(MaterialQuality quality, int toSkip) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetMipsToSkip(MaterialQuality, int)", asMETHODPR(Texture3D, SetMipsToSkip, (MaterialQuality, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "void set_mipsToSkip(MaterialQuality, int)", asMETHODPR(Texture3D, SetMipsToSkip, (MaterialQuality, int), void), asCALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "void SetName(const String&in)", asMETHODPR(Texture3D, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "void set_name(const String&in)", asMETHODPR(Texture3D, SetName, (const String&), void), asCALL_THISCALL);
    // void Texture::SetNumLevels(unsigned levels) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetNumLevels(uint)", asMETHODPR(Texture3D, SetNumLevels, (unsigned), void), asCALL_THISCALL);
    // void Texture::SetParameters(XMLFile* file) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetParameters(XMLFile@+)", asMETHODPR(Texture3D, SetParameters, (XMLFile*), void), asCALL_THISCALL);
    // void Texture::SetParameters(const XMLElement& element) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetParameters(const XMLElement&in)", asMETHODPR(Texture3D, SetParameters, (const XMLElement&), void), asCALL_THISCALL);
    // void Texture::SetParametersDirty() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetParametersDirty()", asMETHODPR(Texture3D, SetParametersDirty, (), void), asCALL_THISCALL);
    // void Texture::SetResolveDirty(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetResolveDirty(bool)", asMETHODPR(Texture3D, SetResolveDirty, (bool), void), asCALL_THISCALL);
    // void Texture::SetShadowCompare(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetShadowCompare(bool)", asMETHODPR(Texture3D, SetShadowCompare, (bool), void), asCALL_THISCALL);
    // bool Texture3D::SetSize(int width, int height, int depth, unsigned format, TextureUsage usage=TEXTURE_STATIC) | File: ../Graphics/Texture3D.h
    engine->RegisterObjectMethod("Texture3D", "bool SetSize(int, int, int, uint, TextureUsage = TEXTURE_STATIC)", asMETHODPR(Texture3D, SetSize, (int, int, int, unsigned, TextureUsage), bool), asCALL_THISCALL);
    // void Texture::SetSRGB(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetSRGB(bool)", asMETHODPR(Texture3D, SetSRGB, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "void set_sRGB(bool)", asMETHODPR(Texture3D, SetSRGB, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit Texture3D::Texture3D(Context* context) | File: ../Graphics/Texture3D.h
    engine->RegisterObjectBehaviour("Texture3D", asBEHAVE_FACTORY, "Texture3D@+ f()", asFUNCTION(Texture3D_Texture3D_Context), asCALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "void UnsubscribeFromAllEvents()", asMETHODPR(Texture3D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Texture3D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Texture3D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Texture3D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Texture3D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void Texture::UpdateParameters() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void UpdateParameters()", asMETHODPR(Texture3D, UpdateParameters, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Texture3D", "int WeakRefs() const", asMETHODPR(Texture3D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "int get_weakRefs() const", asMETHODPR(Texture3D, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Texture
    REGISTER_MANUAL_PART_Texture(Texture3D, "Texture3D")
#endif
#ifdef REGISTER_MANUAL_PART_ResourceWithMetadata
    REGISTER_MANUAL_PART_ResourceWithMetadata(Texture3D, "Texture3D")
#endif
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(Texture3D, "Texture3D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Texture3D, "Texture3D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Texture3D, "Texture3D")
#endif
#ifdef REGISTER_MANUAL_PART_GPUObject
    REGISTER_MANUAL_PART_GPUObject(Texture3D, "Texture3D")
#endif
#ifdef REGISTER_MANUAL_PART_Texture3D
    REGISTER_MANUAL_PART_Texture3D(Texture3D, "Texture3D")
#endif
    RegisterSubclass<Texture, Texture3D>(engine, "Texture", "Texture3D");
    RegisterSubclass<ResourceWithMetadata, Texture3D>(engine, "ResourceWithMetadata", "Texture3D");
    RegisterSubclass<Resource, Texture3D>(engine, "Resource", "Texture3D");
    RegisterSubclass<Object, Texture3D>(engine, "Object", "Texture3D");
    RegisterSubclass<RefCounted, Texture3D>(engine, "RefCounted", "Texture3D");

    // void ResourceWithMetadata::AddMetadata(const String& name, const Variant& value) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "void AddMetadata(const String&in, const Variant&in)", asMETHODPR(TextureCube, AddMetadata, (const String&, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "void set_metadata(const String&in, const Variant&in)", asMETHODPR(TextureCube, AddMetadata, (const String&, const Variant&), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TextureCube", asBEHAVE_ADDREF, "void f()", asMETHODPR(TextureCube, AddRef, (), void), asCALL_THISCALL);
    // bool TextureCube::BeginLoad(Deserializer& source) override | File: ../Graphics/TextureCube.h
    engine->RegisterObjectMethod("TextureCube", "bool BeginLoad(Deserializer&)", asMETHODPR(TextureCube, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // static unsigned Texture::CheckMaxLevels(int width, int height, unsigned requestedLevels) | File: ../Graphics/Texture.h
    engine->SetDefaultNamespace("TextureCube");
    engine->RegisterGlobalFunction("uint CheckMaxLevels(int, int, uint)", asFUNCTIONPR(TextureCube::CheckMaxLevels, (int, int, unsigned), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Texture::CheckMaxLevels(int width, int height, int depth, unsigned requestedLevels) | File: ../Graphics/Texture.h
    engine->SetDefaultNamespace("TextureCube");
    engine->RegisterGlobalFunction("uint CheckMaxLevels(int, int, int, uint)", asFUNCTIONPR(TextureCube::CheckMaxLevels, (int, int, int, unsigned), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // void GPUObject::ClearDataLost() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("TextureCube", "void ClearDataLost()", asMETHODPR(TextureCube, ClearDataLost, (), void), asCALL_THISCALL);
    // bool TextureCube::EndLoad() override | File: ../Graphics/TextureCube.h
    engine->RegisterObjectMethod("TextureCube", "bool EndLoad()", asMETHODPR(TextureCube, EndLoad, (), bool), asCALL_THISCALL);
    // TextureAddressMode Texture::GetAddressMode(TextureCoordinate coord) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "TextureAddressMode GetAddressMode(TextureCoordinate) const", asMETHODPR(TextureCube, GetAddressMode, (TextureCoordinate) const, TextureAddressMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "TextureAddressMode get_addressMode(TextureCoordinate) const", asMETHODPR(TextureCube, GetAddressMode, (TextureCoordinate) const, TextureAddressMode), asCALL_THISCALL);
    // unsigned Texture::GetAnisotropy() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "uint GetAnisotropy() const", asMETHODPR(TextureCube, GetAnisotropy, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "uint get_anisotropy() const", asMETHODPR(TextureCube, GetAnisotropy, () const, unsigned), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(TextureCube, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // bool Texture::GetAutoResolve() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "bool GetAutoResolve() const", asMETHODPR(TextureCube, GetAutoResolve, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "bool get_autoResolve() const", asMETHODPR(TextureCube, GetAutoResolve, () const, bool), asCALL_THISCALL);
    // Texture* Texture::GetBackupTexture() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "Texture@+ GetBackupTexture() const", asMETHODPR(TextureCube, GetBackupTexture, () const, Texture*), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "Texture@+ get_backupTexture() const", asMETHODPR(TextureCube, GetBackupTexture, () const, Texture*), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "bool GetBlockEvents() const", asMETHODPR(TextureCube, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const Color& Texture::GetBorderColor() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "const Color& GetBorderColor() const", asMETHODPR(TextureCube, GetBorderColor, () const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "const Color& get_borderColor() const", asMETHODPR(TextureCube, GetBorderColor, () const, const Color&), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "const String& GetCategory() const", asMETHODPR(TextureCube, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "const String& get_category() const", asMETHODPR(TextureCube, GetCategory, () const, const String&), asCALL_THISCALL);
    // unsigned Texture::GetComponents() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "uint GetComponents() const", asMETHODPR(TextureCube, GetComponents, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "uint get_components() const", asMETHODPR(TextureCube, GetComponents, () const, unsigned), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // bool TextureCube::GetData(CubeMapFace face, unsigned level, void* dest) const | File: ../Graphics/TextureCube.h
    // Error: type "void*" can not automatically bind
    // unsigned Texture::GetDataSize(int width, int height) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "uint GetDataSize(int, int) const", asMETHODPR(TextureCube, GetDataSize, (int, int) const, unsigned), asCALL_THISCALL);
    // unsigned Texture::GetDataSize(int width, int height, int depth) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "uint GetDataSize(int, int, int) const", asMETHODPR(TextureCube, GetDataSize, (int, int, int) const, unsigned), asCALL_THISCALL);
    // static unsigned Texture::GetDataType(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // int Texture::GetDepth() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "int GetDepth() const", asMETHODPR(TextureCube, GetDepth, () const, int), asCALL_THISCALL);
    // static unsigned Texture::GetDSVFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "VariantMap& GetEventDataMap() const", asMETHODPR(TextureCube, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "Object@+ GetEventSender() const", asMETHODPR(TextureCube, GetEventSender, () const, Object*), asCALL_THISCALL);
    // static unsigned Texture::GetExternalFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // TextureFilterMode Texture::GetFilterMode() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "TextureFilterMode GetFilterMode() const", asMETHODPR(TextureCube, GetFilterMode, () const, TextureFilterMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "TextureFilterMode get_filterMode() const", asMETHODPR(TextureCube, GetFilterMode, () const, TextureFilterMode), asCALL_THISCALL);
    // unsigned Texture::GetFormat() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "uint GetFormat() const", asMETHODPR(TextureCube, GetFormat, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "uint get_format() const", asMETHODPR(TextureCube, GetFormat, () const, unsigned), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(TextureCube, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "const Variant& get_globalVar(StringHash) const", asMETHODPR(TextureCube, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "const VariantMap& GetGlobalVars() const", asMETHODPR(TextureCube, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "const VariantMap& get_globalVars() const", asMETHODPR(TextureCube, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // void* GPUObject::GetGPUObject() const | File: ../Graphics/GPUObject.h
    // Error: type "void*" can not automatically bind
    // unsigned GPUObject::GetGPUObjectName() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("TextureCube", "uint GetGPUObjectName() const", asMETHODPR(TextureCube, GetGPUObjectName, () const, unsigned), asCALL_THISCALL);
    // Graphics* GPUObject::GetGraphics() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("TextureCube", "Graphics@+ GetGraphics() const", asMETHODPR(TextureCube, GetGraphics, () const, Graphics*), asCALL_THISCALL);
    // int Texture::GetHeight() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "int GetHeight() const", asMETHODPR(TextureCube, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "int get_height() const", asMETHODPR(TextureCube, GetHeight, () const, int), asCALL_THISCALL);
    // SharedPtr<Image> TextureCube::GetImage(CubeMapFace face) const | File: ../Graphics/TextureCube.h
    engine->RegisterObjectMethod("TextureCube", "Image@+ GetImage(CubeMapFace) const", asFUNCTION(TextureCube_GetImage_CubeMapFace), asCALL_CDECL_OBJFIRST);
    // int Texture::GetLevelDepth(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "int GetLevelDepth(uint) const", asMETHODPR(TextureCube, GetLevelDepth, (unsigned) const, int), asCALL_THISCALL);
    // int Texture::GetLevelHeight(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "int GetLevelHeight(uint) const", asMETHODPR(TextureCube, GetLevelHeight, (unsigned) const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "int get_levelHeight(uint) const", asMETHODPR(TextureCube, GetLevelHeight, (unsigned) const, int), asCALL_THISCALL);
    // unsigned Texture::GetLevels() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "uint GetLevels() const", asMETHODPR(TextureCube, GetLevels, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "uint get_levels() const", asMETHODPR(TextureCube, GetLevels, () const, unsigned), asCALL_THISCALL);
    // bool Texture::GetLevelsDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "bool GetLevelsDirty() const", asMETHODPR(TextureCube, GetLevelsDirty, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "bool get_levelsDirty() const", asMETHODPR(TextureCube, GetLevelsDirty, () const, bool), asCALL_THISCALL);
    // int Texture::GetLevelWidth(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "int GetLevelWidth(uint) const", asMETHODPR(TextureCube, GetLevelWidth, (unsigned) const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "int get_levelWidth(uint) const", asMETHODPR(TextureCube, GetLevelWidth, (unsigned) const, int), asCALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "uint GetMemoryUse() const", asMETHODPR(TextureCube, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "uint get_memoryUse() const", asMETHODPR(TextureCube, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // const Variant& ResourceWithMetadata::GetMetadata(const String& name) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "const Variant& GetMetadata(const String&in) const", asMETHODPR(TextureCube, GetMetadata, (const String&) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "const Variant& get_metadata(const String&in) const", asMETHODPR(TextureCube, GetMetadata, (const String&) const, const Variant&), asCALL_THISCALL);
    // int Texture::GetMipsToSkip(MaterialQuality quality) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "int GetMipsToSkip(MaterialQuality) const", asMETHODPR(TextureCube, GetMipsToSkip, (MaterialQuality) const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "int get_mipsToSkip(MaterialQuality) const", asMETHODPR(TextureCube, GetMipsToSkip, (MaterialQuality) const, int), asCALL_THISCALL);
    // int Texture::GetMultiSample() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "int GetMultiSample() const", asMETHODPR(TextureCube, GetMultiSample, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "int get_multiSample() const", asMETHODPR(TextureCube, GetMultiSample, () const, int), asCALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "const String& GetName() const", asMETHODPR(TextureCube, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "const String& get_name() const", asMETHODPR(TextureCube, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "StringHash GetNameHash() const", asMETHODPR(TextureCube, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // bool Texture::GetParametersDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "bool GetParametersDirty() const", asMETHODPR(TextureCube, GetParametersDirty, () const, bool), asCALL_THISCALL);
    // RenderSurface* TextureCube::GetRenderSurface(CubeMapFace face) const | File: ../Graphics/TextureCube.h
    engine->RegisterObjectMethod("TextureCube", "RenderSurface@+ GetRenderSurface(CubeMapFace) const", asMETHODPR(TextureCube, GetRenderSurface, (CubeMapFace) const, RenderSurface*), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "RenderSurface@+ get_renderSurfaces(CubeMapFace) const", asMETHODPR(TextureCube, GetRenderSurface, (CubeMapFace) const, RenderSurface*), asCALL_THISCALL);
    // void* Texture::GetResolveTexture() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // unsigned Texture::GetRowDataSize(int width) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "uint GetRowDataSize(int) const", asMETHODPR(TextureCube, GetRowDataSize, (int) const, unsigned), asCALL_THISCALL);
    // void* Texture::GetSampler() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // void* Texture::GetShaderResourceView() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // bool Texture::GetShadowCompare() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "bool GetShadowCompare() const", asMETHODPR(TextureCube, GetShadowCompare, () const, bool), asCALL_THISCALL);
    // bool Texture::GetSRGB() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "bool GetSRGB() const", asMETHODPR(TextureCube, GetSRGB, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "bool get_sRGB() const", asMETHODPR(TextureCube, GetSRGB, () const, bool), asCALL_THISCALL);
    // unsigned Texture::GetSRGBFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // static unsigned Texture::GetSRVFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(TextureCube, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // unsigned Texture::GetTarget() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "uint GetTarget() const", asMETHODPR(TextureCube, GetTarget, () const, unsigned), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "StringHash GetType() const", asMETHODPR(TextureCube, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "StringHash get_type() const", asMETHODPR(TextureCube, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "const String& GetTypeName() const", asMETHODPR(TextureCube, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "const String& get_typeName() const", asMETHODPR(TextureCube, GetTypeName, () const, const String&), asCALL_THISCALL);
    // TextureUsage Texture::GetUsage() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "TextureUsage GetUsage() const", asMETHODPR(TextureCube, GetUsage, () const, TextureUsage), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "TextureUsage get_usage() const", asMETHODPR(TextureCube, GetUsage, () const, TextureUsage), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "uint GetUseTimer()", asMETHODPR(TextureCube, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "uint get_useTimer()", asMETHODPR(TextureCube, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // int Texture::GetWidth() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "int GetWidth() const", asMETHODPR(TextureCube, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "int get_width() const", asMETHODPR(TextureCube, GetWidth, () const, int), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "bool HasEventHandlers() const", asMETHODPR(TextureCube, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool ResourceWithMetadata::HasMetadata() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "bool HasMetadata() const", asMETHODPR(TextureCube, HasMetadata, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "bool get_hasMetadata() const", asMETHODPR(TextureCube, HasMetadata, () const, bool), asCALL_THISCALL);
    // bool GPUObject::HasPendingData() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("TextureCube", "bool HasPendingData() const", asMETHODPR(TextureCube, HasPendingData, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(TextureCube, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(TextureCube, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Texture::IsCompressed() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "bool IsCompressed() const", asMETHODPR(TextureCube, IsCompressed, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "bool get_compressed() const", asMETHODPR(TextureCube, IsCompressed, () const, bool), asCALL_THISCALL);
    // bool GPUObject::IsDataLost() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("TextureCube", "bool IsDataLost() const", asMETHODPR(TextureCube, IsDataLost, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "bool get_dataLost() const", asMETHODPR(TextureCube, IsDataLost, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "bool IsInstanceOf(StringHash) const", asMETHODPR(TextureCube, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Texture::IsResolveDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "bool IsResolveDirty() const", asMETHODPR(TextureCube, IsResolveDirty, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "bool get_resolveDirty() const", asMETHODPR(TextureCube, IsResolveDirty, () const, bool), asCALL_THISCALL);
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "bool Load(Deserializer&)", asMETHODPR(TextureCube, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "bool LoadFile(const String&in)", asMETHODPR(TextureCube, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "bool Load(const String&in)", asMETHODPR(TextureCube, LoadFile, (const String&), bool), asCALL_THISCALL);
    // void TextureCube::OnDeviceLost() override | File: ../Graphics/TextureCube.h
    engine->RegisterObjectMethod("TextureCube", "void OnDeviceLost()", asMETHODPR(TextureCube, OnDeviceLost, (), void), asCALL_THISCALL);
    // void TextureCube::OnDeviceReset() override | File: ../Graphics/TextureCube.h
    engine->RegisterObjectMethod("TextureCube", "void OnDeviceReset()", asMETHODPR(TextureCube, OnDeviceReset, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(TextureCube, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TextureCube", "int Refs() const", asMETHODPR(TextureCube, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "int get_refs() const", asMETHODPR(TextureCube, Refs, () const, int), asCALL_THISCALL);
    // void Texture::RegenerateLevels() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void RegenerateLevels()", asMETHODPR(TextureCube, RegenerateLevels, (), void), asCALL_THISCALL);
    // static void TextureCube::RegisterObject(Context* context) | File: ../Graphics/TextureCube.h
    // Not registered because have @nobind mark
    // void TextureCube::Release() override | File: ../Graphics/TextureCube.h
    engine->RegisterObjectMethod("TextureCube", "void Release()", asMETHODPR(TextureCube, Release, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TextureCube", asBEHAVE_RELEASE, "void f()", asMETHODPR(TextureCube, ReleaseRef, (), void), asCALL_THISCALL);
    // void ResourceWithMetadata::RemoveAllMetadata() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "void RemoveAllMetadata()", asMETHODPR(TextureCube, RemoveAllMetadata, (), void), asCALL_THISCALL);
    // void ResourceWithMetadata::RemoveMetadata(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "void RemoveMetadata(const String&in)", asMETHODPR(TextureCube, RemoveMetadata, (const String&), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "void ResetUseTimer()", asMETHODPR(TextureCube, ResetUseTimer, (), void), asCALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "bool Save(Serializer&) const", asMETHODPR(TextureCube, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "bool SaveFile(const String&in) const", asMETHODPR(TextureCube, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "bool Save(const String&in) const", asMETHODPR(TextureCube, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "void SendEvent(StringHash)", asMETHODPR(TextureCube, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(TextureCube, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Texture::SetAddressMode(TextureCoordinate coord, TextureAddressMode mode) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetAddressMode(TextureCoordinate, TextureAddressMode)", asMETHODPR(TextureCube, SetAddressMode, (TextureCoordinate, TextureAddressMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "void set_addressMode(TextureCoordinate, TextureAddressMode)", asMETHODPR(TextureCube, SetAddressMode, (TextureCoordinate, TextureAddressMode), void), asCALL_THISCALL);
    // void Texture::SetAnisotropy(unsigned level) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetAnisotropy(uint)", asMETHODPR(TextureCube, SetAnisotropy, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "void set_anisotropy(uint)", asMETHODPR(TextureCube, SetAnisotropy, (unsigned), void), asCALL_THISCALL);
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(TextureCube, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void Texture::SetBackupTexture(Texture* texture) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetBackupTexture(Texture@+)", asMETHODPR(TextureCube, SetBackupTexture, (Texture*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "void set_backupTexture(Texture@+)", asMETHODPR(TextureCube, SetBackupTexture, (Texture*), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "void SetBlockEvents(bool)", asMETHODPR(TextureCube, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Texture::SetBorderColor(const Color& color) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetBorderColor(const Color&in)", asMETHODPR(TextureCube, SetBorderColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "void set_borderColor(const Color&in)", asMETHODPR(TextureCube, SetBorderColor, (const Color&), void), asCALL_THISCALL);
    // bool TextureCube::SetData(CubeMapFace face, unsigned level, int x, int y, int width, int height, const void* data) | File: ../Graphics/TextureCube.h
    // Error: type "const void*" can not automatically bind
    // bool TextureCube::SetData(CubeMapFace face, Deserializer& source) | File: ../Graphics/TextureCube.h
    engine->RegisterObjectMethod("TextureCube", "bool SetData(CubeMapFace, Deserializer&)", asMETHODPR(TextureCube, SetData, (CubeMapFace, Deserializer&), bool), asCALL_THISCALL);
    // bool TextureCube::SetData(CubeMapFace face, Image* image, bool useAlpha=false) | File: ../Graphics/TextureCube.h
    engine->RegisterObjectMethod("TextureCube", "bool SetData(CubeMapFace, Image@+, bool = false)", asMETHODPR(TextureCube, SetData, (CubeMapFace, Image*, bool), bool), asCALL_THISCALL);
    // void Texture::SetFilterMode(TextureFilterMode mode) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetFilterMode(TextureFilterMode)", asMETHODPR(TextureCube, SetFilterMode, (TextureFilterMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "void set_filterMode(TextureFilterMode)", asMETHODPR(TextureCube, SetFilterMode, (TextureFilterMode), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(TextureCube, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(TextureCube, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Texture::SetLevelsDirty() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetLevelsDirty()", asMETHODPR(TextureCube, SetLevelsDirty, (), void), asCALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "void SetMemoryUse(uint)", asMETHODPR(TextureCube, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void Texture::SetMipsToSkip(MaterialQuality quality, int toSkip) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetMipsToSkip(MaterialQuality, int)", asMETHODPR(TextureCube, SetMipsToSkip, (MaterialQuality, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "void set_mipsToSkip(MaterialQuality, int)", asMETHODPR(TextureCube, SetMipsToSkip, (MaterialQuality, int), void), asCALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "void SetName(const String&in)", asMETHODPR(TextureCube, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "void set_name(const String&in)", asMETHODPR(TextureCube, SetName, (const String&), void), asCALL_THISCALL);
    // void Texture::SetNumLevels(unsigned levels) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetNumLevels(uint)", asMETHODPR(TextureCube, SetNumLevels, (unsigned), void), asCALL_THISCALL);
    // void Texture::SetParameters(XMLFile* file) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetParameters(XMLFile@+)", asMETHODPR(TextureCube, SetParameters, (XMLFile*), void), asCALL_THISCALL);
    // void Texture::SetParameters(const XMLElement& element) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetParameters(const XMLElement&in)", asMETHODPR(TextureCube, SetParameters, (const XMLElement&), void), asCALL_THISCALL);
    // void Texture::SetParametersDirty() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetParametersDirty()", asMETHODPR(TextureCube, SetParametersDirty, (), void), asCALL_THISCALL);
    // void Texture::SetResolveDirty(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetResolveDirty(bool)", asMETHODPR(TextureCube, SetResolveDirty, (bool), void), asCALL_THISCALL);
    // void Texture::SetShadowCompare(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetShadowCompare(bool)", asMETHODPR(TextureCube, SetShadowCompare, (bool), void), asCALL_THISCALL);
    // bool TextureCube::SetSize(int size, unsigned format, TextureUsage usage=TEXTURE_STATIC, int multiSample=1) | File: ../Graphics/TextureCube.h
    engine->RegisterObjectMethod("TextureCube", "bool SetSize(int, uint, TextureUsage = TEXTURE_STATIC, int = 1)", asMETHODPR(TextureCube, SetSize, (int, unsigned, TextureUsage, int), bool), asCALL_THISCALL);
    // void Texture::SetSRGB(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetSRGB(bool)", asMETHODPR(TextureCube, SetSRGB, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "void set_sRGB(bool)", asMETHODPR(TextureCube, SetSRGB, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit TextureCube::TextureCube(Context* context) | File: ../Graphics/TextureCube.h
    engine->RegisterObjectBehaviour("TextureCube", asBEHAVE_FACTORY, "TextureCube@+ f()", asFUNCTION(TextureCube_TextureCube_Context), asCALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "void UnsubscribeFromAllEvents()", asMETHODPR(TextureCube, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(TextureCube_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(TextureCube, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(TextureCube, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(TextureCube, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void Texture::UpdateParameters() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void UpdateParameters()", asMETHODPR(TextureCube, UpdateParameters, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TextureCube", "int WeakRefs() const", asMETHODPR(TextureCube, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "int get_weakRefs() const", asMETHODPR(TextureCube, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Texture
    REGISTER_MANUAL_PART_Texture(TextureCube, "TextureCube")
#endif
#ifdef REGISTER_MANUAL_PART_ResourceWithMetadata
    REGISTER_MANUAL_PART_ResourceWithMetadata(TextureCube, "TextureCube")
#endif
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(TextureCube, "TextureCube")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(TextureCube, "TextureCube")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(TextureCube, "TextureCube")
#endif
#ifdef REGISTER_MANUAL_PART_GPUObject
    REGISTER_MANUAL_PART_GPUObject(TextureCube, "TextureCube")
#endif
#ifdef REGISTER_MANUAL_PART_TextureCube
    REGISTER_MANUAL_PART_TextureCube(TextureCube, "TextureCube")
#endif
    RegisterSubclass<Texture, TextureCube>(engine, "Texture", "TextureCube");
    RegisterSubclass<ResourceWithMetadata, TextureCube>(engine, "ResourceWithMetadata", "TextureCube");
    RegisterSubclass<Resource, TextureCube>(engine, "Resource", "TextureCube");
    RegisterSubclass<Object, TextureCube>(engine, "Object", "TextureCube");
    RegisterSubclass<RefCounted, TextureCube>(engine, "RefCounted", "TextureCube");

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Tile2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(Tile2D, AddRef, (), void), asCALL_THISCALL);
    // bool Tile2D::GetFlipX() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("Tile2D", "bool GetFlipX() const", asMETHODPR(Tile2D, GetFlipX, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Tile2D", "bool get_flipX() const", asMETHODPR(Tile2D, GetFlipX, () const, bool), asCALL_THISCALL);
    // bool Tile2D::GetFlipY() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("Tile2D", "bool GetFlipY() const", asMETHODPR(Tile2D, GetFlipY, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Tile2D", "bool get_flipY() const", asMETHODPR(Tile2D, GetFlipY, () const, bool), asCALL_THISCALL);
    // unsigned Tile2D::GetGid() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("Tile2D", "uint GetGid() const", asMETHODPR(Tile2D, GetGid, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Tile2D", "uint get_gid() const", asMETHODPR(Tile2D, GetGid, () const, unsigned), asCALL_THISCALL);
    // const String& Tile2D::GetProperty(const String& name) const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("Tile2D", "const String& GetProperty(const String&in) const", asMETHODPR(Tile2D, GetProperty, (const String&) const, const String&), asCALL_THISCALL);
    // Sprite2D* Tile2D::GetSprite() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("Tile2D", "Sprite2D@+ GetSprite() const", asMETHODPR(Tile2D, GetSprite, () const, Sprite2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Tile2D", "Sprite2D@+ get_sprite() const", asMETHODPR(Tile2D, GetSprite, () const, Sprite2D*), asCALL_THISCALL);
    // bool Tile2D::GetSwapXY() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("Tile2D", "bool GetSwapXY() const", asMETHODPR(Tile2D, GetSwapXY, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Tile2D", "bool get_swapXY() const", asMETHODPR(Tile2D, GetSwapXY, () const, bool), asCALL_THISCALL);
    // bool Tile2D::HasProperty(const String& name) const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("Tile2D", "bool HasProperty(const String&in) const", asMETHODPR(Tile2D, HasProperty, (const String&) const, bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Tile2D", "int Refs() const", asMETHODPR(Tile2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Tile2D", "int get_refs() const", asMETHODPR(Tile2D, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Tile2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(Tile2D, ReleaseRef, (), void), asCALL_THISCALL);
    // Tile2D::Tile2D() | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectBehaviour("Tile2D", asBEHAVE_FACTORY, "Tile2D@+ f()", asFUNCTION(Tile2D_Tile2D_void), asCALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Tile2D", "int WeakRefs() const", asMETHODPR(Tile2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Tile2D", "int get_weakRefs() const", asMETHODPR(Tile2D, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Tile2D, "Tile2D")
#endif
#ifdef REGISTER_MANUAL_PART_Tile2D
    REGISTER_MANUAL_PART_Tile2D(Tile2D, "Tile2D")
#endif
    RegisterSubclass<RefCounted, Tile2D>(engine, "RefCounted", "Tile2D");
#endif

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TileMap2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(TileMap2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "void AllocateNetworkState()", asMETHODPR(TileMap2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "void ApplyAttributes()", asMETHODPR(TileMap2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void TileMap2D::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectMethod("TileMap2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(TileMap2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // void TileMap2D::DrawDebugGeometry() | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectMethod("TileMap2D", "void DrawDebugGeometry()", asMETHODPR(TileMap2D, DrawDebugGeometry, (), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "bool GetAnimationEnabled() const", asMETHODPR(TileMap2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "bool get_animationEnabled() const", asMETHODPR(TileMap2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "Variant GetAttribute(uint) const", asMETHODPR(TileMap2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "Variant get_attributes(uint) const", asMETHODPR(TileMap2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "Variant GetAttribute(const String&in) const", asMETHODPR(TileMap2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(TileMap2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(TileMap2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(TileMap2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(TileMap2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(TileMap2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(TileMap2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(TileMap2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "bool GetBlockEvents() const", asMETHODPR(TileMap2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "const String& GetCategory() const", asMETHODPR(TileMap2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "const String& get_category() const", asMETHODPR(TileMap2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(TileMap2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "VariantMap& GetEventDataMap() const", asMETHODPR(TileMap2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "Object@+ GetEventSender() const", asMETHODPR(TileMap2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(TileMap2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(TileMap2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(TileMap2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "const VariantMap& get_globalVars() const", asMETHODPR(TileMap2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "uint GetID() const", asMETHODPR(TileMap2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "uint get_id() const", asMETHODPR(TileMap2D, GetID, () const, unsigned), asCALL_THISCALL);
    // const TileMapInfo2D& TileMap2D::GetInfo() const | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectMethod("TileMap2D", "const TileMapInfo2D& GetInfo() const", asMETHODPR(TileMap2D, GetInfo, () const, const TileMapInfo2D&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "const TileMapInfo2D& get_info() const", asMETHODPR(TileMap2D, GetInfo, () const, const TileMapInfo2D&), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(TileMap2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // TileMapLayer2D* TileMap2D::GetLayer(unsigned index) const | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectMethod("TileMap2D", "TileMapLayer2D@+ GetLayer(uint) const", asMETHODPR(TileMap2D, GetLayer, (unsigned) const, TileMapLayer2D*), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "Node@+ GetNode() const", asMETHODPR(TileMap2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "Node@+ get_node() const", asMETHODPR(TileMap2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "uint GetNumAttributes() const", asMETHODPR(TileMap2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "uint get_numAttributes() const", asMETHODPR(TileMap2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned TileMap2D::GetNumLayers() const | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectMethod("TileMap2D", "uint GetNumLayers() const", asMETHODPR(TileMap2D, GetNumLayers, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "uint get_numLayers() const", asMETHODPR(TileMap2D, GetNumLayers, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "uint GetNumNetworkAttributes() const", asMETHODPR(TileMap2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(TileMap2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(TileMap2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(TileMap2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "Scene@+ GetScene() const", asMETHODPR(TileMap2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(TileMap2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // Vector<SharedPtr<TileMapObject2D>> TileMap2D::GetTileCollisionShapes(unsigned gid) const | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectMethod("TileMap2D", "Array<TileMapObject2D@>@ GetTileCollisionShapes(uint) const", asFUNCTION(TileMap2D_GetTileCollisionShapes_unsigned), asCALL_CDECL_OBJFIRST);
    // TmxFile2D* TileMap2D::GetTmxFile() const | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectMethod("TileMap2D", "TmxFile2D@+ GetTmxFile() const", asMETHODPR(TileMap2D, GetTmxFile, () const, TmxFile2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "TmxFile2D@+ get_tmxFile() const", asMETHODPR(TileMap2D, GetTmxFile, () const, TmxFile2D*), asCALL_THISCALL);
    // ResourceRef TileMap2D::GetTmxFileAttr() const | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectMethod("TileMap2D", "ResourceRef GetTmxFileAttr() const", asMETHODPR(TileMap2D, GetTmxFileAttr, () const, ResourceRef), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "StringHash GetType() const", asMETHODPR(TileMap2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "StringHash get_type() const", asMETHODPR(TileMap2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "const String& GetTypeName() const", asMETHODPR(TileMap2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "const String& get_typeName() const", asMETHODPR(TileMap2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "bool HasEventHandlers() const", asMETHODPR(TileMap2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(TileMap2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(TileMap2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "bool IsEnabled() const", asMETHODPR(TileMap2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "bool get_enabled() const", asMETHODPR(TileMap2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "bool IsEnabledEffective() const", asMETHODPR(TileMap2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "bool get_enabledEffective() const", asMETHODPR(TileMap2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(TileMap2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "bool IsReplicated() const", asMETHODPR(TileMap2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "bool get_replicated() const", asMETHODPR(TileMap2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "bool IsTemporary() const", asMETHODPR(TileMap2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "bool get_temporary() const", asMETHODPR(TileMap2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "bool Load(Deserializer&)", asMETHODPR(TileMap2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(TileMap2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(TileMap2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "void MarkNetworkUpdate()", asMETHODPR(TileMap2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(TileMap2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(TileMap2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(TileMap2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "void OnSetEnabled()", asMETHODPR(TileMap2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // bool TileMap2D::PositionToTileIndex(int& x, int& y, const Vector2& position) const | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectMethod("TileMap2D", "bool PositionToTileIndex(int&, int&, const Vector2&in) const", asMETHODPR(TileMap2D, PositionToTileIndex, (int&, int&, const Vector2&) const, bool), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "void PrepareNetworkUpdate()", asMETHODPR(TileMap2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(TileMap2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(TileMap2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TileMap2D", "int Refs() const", asMETHODPR(TileMap2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "int get_refs() const", asMETHODPR(TileMap2D, Refs, () const, int), asCALL_THISCALL);
    // static void TileMap2D::RegisterObject(Context* context) | File: ../Urho2D/TileMap2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TileMap2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(TileMap2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "void Remove()", asMETHODPR(TileMap2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(TileMap2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "void RemoveInstanceDefault()", asMETHODPR(TileMap2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "void RemoveObjectAnimation()", asMETHODPR(TileMap2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "void ResetToDefault()", asMETHODPR(TileMap2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "bool Save(Serializer&) const", asMETHODPR(TileMap2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "bool SaveDefaultAttributes() const", asMETHODPR(TileMap2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(TileMap2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "bool SaveXML(XMLElement&) const", asMETHODPR(TileMap2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "void SendEvent(StringHash)", asMETHODPR(TileMap2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(TileMap2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "void SetAnimationEnabled(bool)", asMETHODPR(TileMap2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "void set_animationEnabled(bool)", asMETHODPR(TileMap2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "void SetAnimationTime(float)", asMETHODPR(TileMap2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(TileMap2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(TileMap2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(TileMap2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(TileMap2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(TileMap2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(TileMap2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(TileMap2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "void SetBlockEvents(bool)", asMETHODPR(TileMap2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "void SetEnabled(bool)", asMETHODPR(TileMap2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "void set_enabled(bool)", asMETHODPR(TileMap2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(TileMap2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(TileMap2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "void SetInstanceDefault(bool)", asMETHODPR(TileMap2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(TileMap2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(TileMap2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(TileMap2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(TileMap2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "void SetTemporary(bool)", asMETHODPR(TileMap2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "void set_temporary(bool)", asMETHODPR(TileMap2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void TileMap2D::SetTmxFile(TmxFile2D* tmxFile) | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectMethod("TileMap2D", "void SetTmxFile(TmxFile2D@+)", asMETHODPR(TileMap2D, SetTmxFile, (TmxFile2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "void set_tmxFile(TmxFile2D@+)", asMETHODPR(TileMap2D, SetTmxFile, (TmxFile2D*), void), asCALL_THISCALL);
    // void TileMap2D::SetTmxFileAttr(const ResourceRef& value) | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectMethod("TileMap2D", "void SetTmxFileAttr(const ResourceRef&in)", asMETHODPR(TileMap2D, SetTmxFileAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // Vector2 TileMap2D::TileIndexToPosition(int x, int y) const | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectMethod("TileMap2D", "Vector2 TileIndexToPosition(int, int) const", asMETHODPR(TileMap2D, TileIndexToPosition, (int, int) const, Vector2), asCALL_THISCALL);
    // explicit TileMap2D::TileMap2D(Context* context) | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectBehaviour("TileMap2D", asBEHAVE_FACTORY, "TileMap2D@+ f()", asFUNCTION(TileMap2D_TileMap2D_Context), asCALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "void UnsubscribeFromAllEvents()", asMETHODPR(TileMap2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(TileMap2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(TileMap2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(TileMap2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(TileMap2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TileMap2D", "int WeakRefs() const", asMETHODPR(TileMap2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "int get_weakRefs() const", asMETHODPR(TileMap2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(TileMap2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(TileMap2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(TileMap2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(TileMap2D, "TileMap2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(TileMap2D, "TileMap2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(TileMap2D, "TileMap2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(TileMap2D, "TileMap2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(TileMap2D, "TileMap2D")
#endif
#ifdef REGISTER_MANUAL_PART_TileMap2D
    REGISTER_MANUAL_PART_TileMap2D(TileMap2D, "TileMap2D")
#endif
    RegisterSubclass<Component, TileMap2D>(engine, "Component", "TileMap2D");
    RegisterSubclass<Animatable, TileMap2D>(engine, "Animatable", "TileMap2D");
    RegisterSubclass<Serializable, TileMap2D>(engine, "Serializable", "TileMap2D");
    RegisterSubclass<Object, TileMap2D>(engine, "Object", "TileMap2D");
    RegisterSubclass<RefCounted, TileMap2D>(engine, "RefCounted", "TileMap2D");
#endif

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TileMapLayer2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(TileMapLayer2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void AllocateNetworkState()", asMETHODPR(TileMapLayer2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void ApplyAttributes()", asMETHODPR(TileMapLayer2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void TileMapLayer2D::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(TileMapLayer2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool GetAnimationEnabled() const", asMETHODPR(TileMapLayer2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "bool get_animationEnabled() const", asMETHODPR(TileMapLayer2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Variant GetAttribute(uint) const", asMETHODPR(TileMapLayer2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "Variant get_attributes(uint) const", asMETHODPR(TileMapLayer2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Variant GetAttribute(const String&in) const", asMETHODPR(TileMapLayer2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(TileMapLayer2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(TileMapLayer2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(TileMapLayer2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(TileMapLayer2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(TileMapLayer2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(TileMapLayer2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(TileMapLayer2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool GetBlockEvents() const", asMETHODPR(TileMapLayer2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "const String& GetCategory() const", asMETHODPR(TileMapLayer2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "const String& get_category() const", asMETHODPR(TileMapLayer2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(TileMapLayer2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // int TileMapLayer2D::GetDrawOrder() const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "int GetDrawOrder() const", asMETHODPR(TileMapLayer2D, GetDrawOrder, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "int get_drawOrder() const", asMETHODPR(TileMapLayer2D, GetDrawOrder, () const, int), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "VariantMap& GetEventDataMap() const", asMETHODPR(TileMapLayer2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Object@+ GetEventSender() const", asMETHODPR(TileMapLayer2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(TileMapLayer2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(TileMapLayer2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(TileMapLayer2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "const VariantMap& get_globalVars() const", asMETHODPR(TileMapLayer2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int TileMapLayer2D::GetHeight() const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "int GetHeight() const", asMETHODPR(TileMapLayer2D, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "int get_height() const", asMETHODPR(TileMapLayer2D, GetHeight, () const, int), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "uint GetID() const", asMETHODPR(TileMapLayer2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "uint get_id() const", asMETHODPR(TileMapLayer2D, GetID, () const, unsigned), asCALL_THISCALL);
    // Node* TileMapLayer2D::GetImageNode() const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Node@+ GetImageNode() const", asMETHODPR(TileMapLayer2D, GetImageNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "Node@+ get_imageNode() const", asMETHODPR(TileMapLayer2D, GetImageNode, () const, Node*), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(TileMapLayer2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // TileMapLayerType2D TileMapLayer2D::GetLayerType() const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "TileMapLayerType2D GetLayerType() const", asMETHODPR(TileMapLayer2D, GetLayerType, () const, TileMapLayerType2D), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "TileMapLayerType2D get_layerType() const", asMETHODPR(TileMapLayer2D, GetLayerType, () const, TileMapLayerType2D), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Node@+ GetNode() const", asMETHODPR(TileMapLayer2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "Node@+ get_node() const", asMETHODPR(TileMapLayer2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "uint GetNumAttributes() const", asMETHODPR(TileMapLayer2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "uint get_numAttributes() const", asMETHODPR(TileMapLayer2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "uint GetNumNetworkAttributes() const", asMETHODPR(TileMapLayer2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned TileMapLayer2D::GetNumObjects() const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "uint GetNumObjects() const", asMETHODPR(TileMapLayer2D, GetNumObjects, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "uint get_numObjects() const", asMETHODPR(TileMapLayer2D, GetNumObjects, () const, unsigned), asCALL_THISCALL);
    // TileMapObject2D* TileMapLayer2D::GetObject(unsigned index) const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "TileMapObject2D@+ GetObject(uint) const", asMETHODPR(TileMapLayer2D, GetObject, (unsigned) const, TileMapObject2D*), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(TileMapLayer2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(TileMapLayer2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(TileMapLayer2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Node* TileMapLayer2D::GetObjectNode(unsigned index) const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Node@+ GetObjectNode(uint) const", asMETHODPR(TileMapLayer2D, GetObjectNode, (unsigned) const, Node*), asCALL_THISCALL);
    // const String& TileMapLayer2D::GetProperty(const String& name) const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "const String& GetProperty(const String&in) const", asMETHODPR(TileMapLayer2D, GetProperty, (const String&) const, const String&), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Scene@+ GetScene() const", asMETHODPR(TileMapLayer2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(TileMapLayer2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // Tile2D* TileMapLayer2D::GetTile(int x, int y) const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Tile2D@+ GetTile(int, int) const", asMETHODPR(TileMapLayer2D, GetTile, (int, int) const, Tile2D*), asCALL_THISCALL);
    // TileMap2D* TileMapLayer2D::GetTileMap() const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "TileMap2D@+ GetTileMap() const", asMETHODPR(TileMapLayer2D, GetTileMap, () const, TileMap2D*), asCALL_THISCALL);
    // Node* TileMapLayer2D::GetTileNode(int x, int y) const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Node@+ GetTileNode(int, int) const", asMETHODPR(TileMapLayer2D, GetTileNode, (int, int) const, Node*), asCALL_THISCALL);
    // const TmxLayer2D* TileMapLayer2D::GetTmxLayer() const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "TmxLayer2D@+ GetTmxLayer() const", asMETHODPR(TileMapLayer2D, GetTmxLayer, () const, const TmxLayer2D*), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "StringHash GetType() const", asMETHODPR(TileMapLayer2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "StringHash get_type() const", asMETHODPR(TileMapLayer2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "const String& GetTypeName() const", asMETHODPR(TileMapLayer2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "const String& get_typeName() const", asMETHODPR(TileMapLayer2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // int TileMapLayer2D::GetWidth() const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "int GetWidth() const", asMETHODPR(TileMapLayer2D, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "int get_width() const", asMETHODPR(TileMapLayer2D, GetWidth, () const, int), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool HasEventHandlers() const", asMETHODPR(TileMapLayer2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool TileMapLayer2D::HasProperty(const String& name) const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool HasProperty(const String&in) const", asMETHODPR(TileMapLayer2D, HasProperty, (const String&) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(TileMapLayer2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(TileMapLayer2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // void TileMapLayer2D::Initialize(TileMap2D* tileMap, const TmxLayer2D* tmxLayer) | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void Initialize(TileMap2D@+, TmxLayer2D@+)", asMETHODPR(TileMapLayer2D, Initialize, (TileMap2D*, const TmxLayer2D*), void), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool IsEnabled() const", asMETHODPR(TileMapLayer2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "bool get_enabled() const", asMETHODPR(TileMapLayer2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool IsEnabledEffective() const", asMETHODPR(TileMapLayer2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "bool get_enabledEffective() const", asMETHODPR(TileMapLayer2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(TileMapLayer2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool IsReplicated() const", asMETHODPR(TileMapLayer2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "bool get_replicated() const", asMETHODPR(TileMapLayer2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool IsTemporary() const", asMETHODPR(TileMapLayer2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "bool get_temporary() const", asMETHODPR(TileMapLayer2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool TileMapLayer2D::IsVisible() const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool IsVisible() const", asMETHODPR(TileMapLayer2D, IsVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "bool get_visible() const", asMETHODPR(TileMapLayer2D, IsVisible, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool Load(Deserializer&)", asMETHODPR(TileMapLayer2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(TileMapLayer2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(TileMapLayer2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void MarkNetworkUpdate()", asMETHODPR(TileMapLayer2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(TileMapLayer2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(TileMapLayer2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(TileMapLayer2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void OnSetEnabled()", asMETHODPR(TileMapLayer2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void PrepareNetworkUpdate()", asMETHODPR(TileMapLayer2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(TileMapLayer2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(TileMapLayer2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TileMapLayer2D", "int Refs() const", asMETHODPR(TileMapLayer2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "int get_refs() const", asMETHODPR(TileMapLayer2D, Refs, () const, int), asCALL_THISCALL);
    // static void TileMapLayer2D::RegisterObject(Context* context) | File: ../Urho2D/TileMapLayer2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TileMapLayer2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(TileMapLayer2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void Remove()", asMETHODPR(TileMapLayer2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(TileMapLayer2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void RemoveInstanceDefault()", asMETHODPR(TileMapLayer2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void RemoveObjectAnimation()", asMETHODPR(TileMapLayer2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void ResetToDefault()", asMETHODPR(TileMapLayer2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool Save(Serializer&) const", asMETHODPR(TileMapLayer2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool SaveDefaultAttributes() const", asMETHODPR(TileMapLayer2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(TileMapLayer2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool SaveXML(XMLElement&) const", asMETHODPR(TileMapLayer2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SendEvent(StringHash)", asMETHODPR(TileMapLayer2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(TileMapLayer2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetAnimationEnabled(bool)", asMETHODPR(TileMapLayer2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "void set_animationEnabled(bool)", asMETHODPR(TileMapLayer2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetAnimationTime(float)", asMETHODPR(TileMapLayer2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(TileMapLayer2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(TileMapLayer2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(TileMapLayer2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(TileMapLayer2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(TileMapLayer2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(TileMapLayer2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(TileMapLayer2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetBlockEvents(bool)", asMETHODPR(TileMapLayer2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void TileMapLayer2D::SetDrawOrder(int drawOrder) | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetDrawOrder(int)", asMETHODPR(TileMapLayer2D, SetDrawOrder, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "void set_drawOrder(int)", asMETHODPR(TileMapLayer2D, SetDrawOrder, (int), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetEnabled(bool)", asMETHODPR(TileMapLayer2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "void set_enabled(bool)", asMETHODPR(TileMapLayer2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(TileMapLayer2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(TileMapLayer2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetInstanceDefault(bool)", asMETHODPR(TileMapLayer2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(TileMapLayer2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(TileMapLayer2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(TileMapLayer2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(TileMapLayer2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetTemporary(bool)", asMETHODPR(TileMapLayer2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "void set_temporary(bool)", asMETHODPR(TileMapLayer2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void TileMapLayer2D::SetVisible(bool visible) | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetVisible(bool)", asMETHODPR(TileMapLayer2D, SetVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "void set_visible(bool)", asMETHODPR(TileMapLayer2D, SetVisible, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit TileMapLayer2D::TileMapLayer2D(Context* context) | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectBehaviour("TileMapLayer2D", asBEHAVE_FACTORY, "TileMapLayer2D@+ f()", asFUNCTION(TileMapLayer2D_TileMapLayer2D_Context), asCALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void UnsubscribeFromAllEvents()", asMETHODPR(TileMapLayer2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(TileMapLayer2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(TileMapLayer2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(TileMapLayer2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(TileMapLayer2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TileMapLayer2D", "int WeakRefs() const", asMETHODPR(TileMapLayer2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "int get_weakRefs() const", asMETHODPR(TileMapLayer2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(TileMapLayer2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(TileMapLayer2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(TileMapLayer2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(TileMapLayer2D, "TileMapLayer2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(TileMapLayer2D, "TileMapLayer2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(TileMapLayer2D, "TileMapLayer2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(TileMapLayer2D, "TileMapLayer2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(TileMapLayer2D, "TileMapLayer2D")
#endif
#ifdef REGISTER_MANUAL_PART_TileMapLayer2D
    REGISTER_MANUAL_PART_TileMapLayer2D(TileMapLayer2D, "TileMapLayer2D")
#endif
    RegisterSubclass<Component, TileMapLayer2D>(engine, "Component", "TileMapLayer2D");
    RegisterSubclass<Animatable, TileMapLayer2D>(engine, "Animatable", "TileMapLayer2D");
    RegisterSubclass<Serializable, TileMapLayer2D>(engine, "Serializable", "TileMapLayer2D");
    RegisterSubclass<Object, TileMapLayer2D>(engine, "Object", "TileMapLayer2D");
    RegisterSubclass<RefCounted, TileMapLayer2D>(engine, "RefCounted", "TileMapLayer2D");
#endif

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TileMapObject2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(TileMapObject2D, AddRef, (), void), asCALL_THISCALL);
    // const String& TileMapObject2D::GetName() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "const String& GetName() const", asMETHODPR(TileMapObject2D, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "const String& get_name() const", asMETHODPR(TileMapObject2D, GetName, () const, const String&), asCALL_THISCALL);
    // unsigned TileMapObject2D::GetNumPoints() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "uint GetNumPoints() const", asMETHODPR(TileMapObject2D, GetNumPoints, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "uint get_numPoints() const", asMETHODPR(TileMapObject2D, GetNumPoints, () const, unsigned), asCALL_THISCALL);
    // TileMapObjectType2D TileMapObject2D::GetObjectType() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "TileMapObjectType2D GetObjectType() const", asMETHODPR(TileMapObject2D, GetObjectType, () const, TileMapObjectType2D), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "TileMapObjectType2D get_objectType() const", asMETHODPR(TileMapObject2D, GetObjectType, () const, TileMapObjectType2D), asCALL_THISCALL);
    // const Vector2& TileMapObject2D::GetPoint(unsigned index) const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "const Vector2& GetPoint(uint) const", asMETHODPR(TileMapObject2D, GetPoint, (unsigned) const, const Vector2&), asCALL_THISCALL);
    // const Vector2& TileMapObject2D::GetPosition() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "const Vector2& GetPosition() const", asMETHODPR(TileMapObject2D, GetPosition, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "const Vector2& get_position() const", asMETHODPR(TileMapObject2D, GetPosition, () const, const Vector2&), asCALL_THISCALL);
    // const String& TileMapObject2D::GetProperty(const String& name) const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "const String& GetProperty(const String&in) const", asMETHODPR(TileMapObject2D, GetProperty, (const String&) const, const String&), asCALL_THISCALL);
    // const Vector2& TileMapObject2D::GetSize() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "const Vector2& GetSize() const", asMETHODPR(TileMapObject2D, GetSize, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "const Vector2& get_size() const", asMETHODPR(TileMapObject2D, GetSize, () const, const Vector2&), asCALL_THISCALL);
    // bool TileMapObject2D::GetTileFlipX() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "bool GetTileFlipX() const", asMETHODPR(TileMapObject2D, GetTileFlipX, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "bool get_tileFlipX() const", asMETHODPR(TileMapObject2D, GetTileFlipX, () const, bool), asCALL_THISCALL);
    // bool TileMapObject2D::GetTileFlipY() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "bool GetTileFlipY() const", asMETHODPR(TileMapObject2D, GetTileFlipY, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "bool get_tileFlipY() const", asMETHODPR(TileMapObject2D, GetTileFlipY, () const, bool), asCALL_THISCALL);
    // unsigned TileMapObject2D::GetTileGid() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "uint GetTileGid() const", asMETHODPR(TileMapObject2D, GetTileGid, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "uint get_tileGid() const", asMETHODPR(TileMapObject2D, GetTileGid, () const, unsigned), asCALL_THISCALL);
    // Sprite2D* TileMapObject2D::GetTileSprite() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "Sprite2D@+ GetTileSprite() const", asMETHODPR(TileMapObject2D, GetTileSprite, () const, Sprite2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "Sprite2D@+ get_tileSprite() const", asMETHODPR(TileMapObject2D, GetTileSprite, () const, Sprite2D*), asCALL_THISCALL);
    // bool TileMapObject2D::GetTileSwapXY() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "bool GetTileSwapXY() const", asMETHODPR(TileMapObject2D, GetTileSwapXY, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "bool get_tileSwapXY() const", asMETHODPR(TileMapObject2D, GetTileSwapXY, () const, bool), asCALL_THISCALL);
    // const String& TileMapObject2D::GetType() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "const String& GetType() const", asMETHODPR(TileMapObject2D, GetType, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "const String& get_type() const", asMETHODPR(TileMapObject2D, GetType, () const, const String&), asCALL_THISCALL);
    // bool TileMapObject2D::HasProperty(const String& name) const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "bool HasProperty(const String&in) const", asMETHODPR(TileMapObject2D, HasProperty, (const String&) const, bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TileMapObject2D", "int Refs() const", asMETHODPR(TileMapObject2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "int get_refs() const", asMETHODPR(TileMapObject2D, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TileMapObject2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(TileMapObject2D, ReleaseRef, (), void), asCALL_THISCALL);
    // TileMapObject2D::TileMapObject2D() | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectBehaviour("TileMapObject2D", asBEHAVE_FACTORY, "TileMapObject2D@+ f()", asFUNCTION(TileMapObject2D_TileMapObject2D_void), asCALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TileMapObject2D", "int WeakRefs() const", asMETHODPR(TileMapObject2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "int get_weakRefs() const", asMETHODPR(TileMapObject2D, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(TileMapObject2D, "TileMapObject2D")
#endif
#ifdef REGISTER_MANUAL_PART_TileMapObject2D
    REGISTER_MANUAL_PART_TileMapObject2D(TileMapObject2D, "TileMapObject2D")
#endif
    RegisterSubclass<RefCounted, TileMapObject2D>(engine, "RefCounted", "TileMapObject2D");
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Time", asBEHAVE_ADDREF, "void f()", asMETHODPR(Time, AddRef, (), void), asCALL_THISCALL);
    // void Time::BeginFrame(float timeStep) | File: ../Core/Timer.h
    engine->RegisterObjectMethod("Time", "void BeginFrame(float)", asMETHODPR(Time, BeginFrame, (float), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Time::EndFrame() | File: ../Core/Timer.h
    engine->RegisterObjectMethod("Time", "void EndFrame()", asMETHODPR(Time, EndFrame, (), void), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "bool GetBlockEvents() const", asMETHODPR(Time, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "const String& GetCategory() const", asMETHODPR(Time, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Time", "const String& get_category() const", asMETHODPR(Time, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float Time::GetElapsedTime() | File: ../Core/Timer.h
    engine->RegisterObjectMethod("Time", "float GetElapsedTime()", asMETHODPR(Time, GetElapsedTime, (), float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Time", "float get_elapsedTime()", asMETHODPR(Time, GetElapsedTime, (), float), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "VariantMap& GetEventDataMap() const", asMETHODPR(Time, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "Object@+ GetEventSender() const", asMETHODPR(Time, GetEventSender, () const, Object*), asCALL_THISCALL);
    // unsigned Time::GetFrameNumber() const | File: ../Core/Timer.h
    engine->RegisterObjectMethod("Time", "uint GetFrameNumber() const", asMETHODPR(Time, GetFrameNumber, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Time", "uint get_frameNumber() const", asMETHODPR(Time, GetFrameNumber, () const, unsigned), asCALL_THISCALL);
    // float Time::GetFramesPerSecond() const | File: ../Core/Timer.h
    engine->RegisterObjectMethod("Time", "float GetFramesPerSecond() const", asMETHODPR(Time, GetFramesPerSecond, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Time", "float get_framesPerSecond() const", asMETHODPR(Time, GetFramesPerSecond, () const, float), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Time, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Time", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Time, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "const VariantMap& GetGlobalVars() const", asMETHODPR(Time, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Time", "const VariantMap& get_globalVars() const", asMETHODPR(Time, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Time, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // static unsigned Time::GetSystemTime() | File: ../Core/Timer.h
    engine->SetDefaultNamespace("Time");
    engine->RegisterGlobalFunction("uint GetSystemTime()", asFUNCTIONPR(Time::GetSystemTime, (), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // unsigned Time::GetTimerPeriod() const | File: ../Core/Timer.h
    engine->RegisterObjectMethod("Time", "uint GetTimerPeriod() const", asMETHODPR(Time, GetTimerPeriod, () const, unsigned), asCALL_THISCALL);
    // static unsigned Time::GetTimeSinceEpoch() | File: ../Core/Timer.h
    engine->SetDefaultNamespace("Time");
    engine->RegisterGlobalFunction("uint GetTimeSinceEpoch()", asFUNCTIONPR(Time::GetTimeSinceEpoch, (), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // static String Time::GetTimeStamp() | File: ../Core/Timer.h
    engine->SetDefaultNamespace("Time");
    engine->RegisterGlobalFunction("String GetTimeStamp()", asFUNCTIONPR(Time::GetTimeStamp, (), String), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // float Time::GetTimeStep() const | File: ../Core/Timer.h
    engine->RegisterObjectMethod("Time", "float GetTimeStep() const", asMETHODPR(Time, GetTimeStep, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Time", "float get_timeStep() const", asMETHODPR(Time, GetTimeStep, () const, float), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "StringHash GetType() const", asMETHODPR(Time, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Time", "StringHash get_type() const", asMETHODPR(Time, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "const String& GetTypeName() const", asMETHODPR(Time, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Time", "const String& get_typeName() const", asMETHODPR(Time, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "bool HasEventHandlers() const", asMETHODPR(Time, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Time, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Time, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "bool IsInstanceOf(StringHash) const", asMETHODPR(Time, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Time, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Time", "int Refs() const", asMETHODPR(Time, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Time", "int get_refs() const", asMETHODPR(Time, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Time", asBEHAVE_RELEASE, "void f()", asMETHODPR(Time, ReleaseRef, (), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "void SendEvent(StringHash)", asMETHODPR(Time, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Time, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "void SetBlockEvents(bool)", asMETHODPR(Time, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Time, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Time", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Time, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Time::SetTimerPeriod(unsigned mSec) | File: ../Core/Timer.h
    engine->RegisterObjectMethod("Time", "void SetTimerPeriod(uint)", asMETHODPR(Time, SetTimerPeriod, (unsigned), void), asCALL_THISCALL);
    // static void Time::Sleep(unsigned mSec) | File: ../Core/Timer.h
    engine->SetDefaultNamespace("Time");
    engine->RegisterGlobalFunction("void Sleep(uint)", asFUNCTIONPR(Time::Sleep, (unsigned), void), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit Time::Time(Context* context) | File: ../Core/Timer.h
    engine->RegisterObjectBehaviour("Time", asBEHAVE_FACTORY, "Time@+ f()", asFUNCTION(Time_Time_Context), asCALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "void UnsubscribeFromAllEvents()", asMETHODPR(Time, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Time_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Time, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Time, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Time, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Time", "int WeakRefs() const", asMETHODPR(Time, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Time", "int get_weakRefs() const", asMETHODPR(Time, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Time, "Time")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Time, "Time")
#endif
#ifdef REGISTER_MANUAL_PART_Time
    REGISTER_MANUAL_PART_Time(Time, "Time")
#endif
    RegisterSubclass<Object, Time>(engine, "Object", "Time");
    RegisterSubclass<RefCounted, Time>(engine, "RefCounted", "Time");

    // unsigned Timer::GetMSec(bool reset) | File: ../Core/Timer.h
    engine->RegisterObjectMethod("Timer", "uint GetMSec(bool)", asMETHODPR(Timer, GetMSec, (bool), unsigned), asCALL_THISCALL);
    // void Timer::Reset() | File: ../Core/Timer.h
    engine->RegisterObjectMethod("Timer", "void Reset()", asMETHODPR(Timer, Reset, (), void), asCALL_THISCALL);
    // Timer& Timer::operator=(const Timer&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Timer>(engine, "Timer");
#ifdef REGISTER_MANUAL_PART_Timer
    REGISTER_MANUAL_PART_Timer(Timer, "Timer")
#endif

#ifdef URHO3D_URHO2D
    // void TmxFile2D::AddLayer(unsigned index, TmxLayer2D* layer) | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxFile2D", "void AddLayer(uint, TmxLayer2D@+)", asMETHODPR(TmxFile2D, AddLayer, (unsigned, TmxLayer2D*), void), asCALL_THISCALL);
    // void TmxFile2D::AddLayer(Urho3D::TmxLayer2D* layer) | File: ../Urho2D/TmxFile2D.h
    // Error: type "Urho3D::TmxLayer2D*" can not automatically bind
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TmxFile2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(TmxFile2D, AddRef, (), void), asCALL_THISCALL);
    // bool TmxFile2D::BeginLoad(Deserializer& source) override | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxFile2D", "bool BeginLoad(Deserializer&)", asMETHODPR(TmxFile2D, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool TmxFile2D::EndLoad() override | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxFile2D", "bool EndLoad()", asMETHODPR(TmxFile2D, EndLoad, (), bool), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(TmxFile2D, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "bool GetBlockEvents() const", asMETHODPR(TmxFile2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "const String& GetCategory() const", asMETHODPR(TmxFile2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "const String& get_category() const", asMETHODPR(TmxFile2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "VariantMap& GetEventDataMap() const", asMETHODPR(TmxFile2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "Object@+ GetEventSender() const", asMETHODPR(TmxFile2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(TmxFile2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(TmxFile2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(TmxFile2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "const VariantMap& get_globalVars() const", asMETHODPR(TmxFile2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // const TileMapInfo2D& TmxFile2D::GetInfo() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxFile2D", "const TileMapInfo2D& GetInfo() const", asMETHODPR(TmxFile2D, GetInfo, () const, const TileMapInfo2D&), asCALL_THISCALL);
    // const TmxLayer2D* TmxFile2D::GetLayer(unsigned index) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxFile2D", "TmxLayer2D@+ GetLayer(uint) const", asMETHODPR(TmxFile2D, GetLayer, (unsigned) const, const TmxLayer2D*), asCALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "uint GetMemoryUse() const", asMETHODPR(TmxFile2D, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "uint get_memoryUse() const", asMETHODPR(TmxFile2D, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "const String& GetName() const", asMETHODPR(TmxFile2D, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "const String& get_name() const", asMETHODPR(TmxFile2D, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "StringHash GetNameHash() const", asMETHODPR(TmxFile2D, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // unsigned TmxFile2D::GetNumLayers() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxFile2D", "uint GetNumLayers() const", asMETHODPR(TmxFile2D, GetNumLayers, () const, unsigned), asCALL_THISCALL);
    // float TmxFile2D::GetSpriteTextureEdgeOffset() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxFile2D", "float GetSpriteTextureEdgeOffset() const", asMETHODPR(TmxFile2D, GetSpriteTextureEdgeOffset, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "float get_edgeOffset() const", asMETHODPR(TmxFile2D, GetSpriteTextureEdgeOffset, () const, float), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(TmxFile2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // Vector<SharedPtr<TileMapObject2D>> TmxFile2D::GetTileCollisionShapes(unsigned gid) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxFile2D", "Array<TileMapObject2D@>@ GetTileCollisionShapes(uint) const", asFUNCTION(TmxFile2D_GetTileCollisionShapes_unsigned), asCALL_CDECL_OBJFIRST);
    // PropertySet2D* TmxFile2D::GetTilePropertySet(unsigned gid) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxFile2D", "PropertySet2D@+ GetTilePropertySet(uint) const", asMETHODPR(TmxFile2D, GetTilePropertySet, (unsigned) const, PropertySet2D*), asCALL_THISCALL);
    // Sprite2D* TmxFile2D::GetTileSprite(unsigned gid) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxFile2D", "Sprite2D@+ GetTileSprite(uint) const", asMETHODPR(TmxFile2D, GetTileSprite, (unsigned) const, Sprite2D*), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "StringHash GetType() const", asMETHODPR(TmxFile2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "StringHash get_type() const", asMETHODPR(TmxFile2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "const String& GetTypeName() const", asMETHODPR(TmxFile2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "const String& get_typeName() const", asMETHODPR(TmxFile2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "uint GetUseTimer()", asMETHODPR(TmxFile2D, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "uint get_useTimer()", asMETHODPR(TmxFile2D, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "bool HasEventHandlers() const", asMETHODPR(TmxFile2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(TmxFile2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(TmxFile2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(TmxFile2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "bool Load(Deserializer&)", asMETHODPR(TmxFile2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "bool LoadFile(const String&in)", asMETHODPR(TmxFile2D, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "bool Load(const String&in)", asMETHODPR(TmxFile2D, LoadFile, (const String&), bool), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(TmxFile2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TmxFile2D", "int Refs() const", asMETHODPR(TmxFile2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "int get_refs() const", asMETHODPR(TmxFile2D, Refs, () const, int), asCALL_THISCALL);
    // static void TmxFile2D::RegisterObject(Context* context) | File: ../Urho2D/TmxFile2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TmxFile2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(TmxFile2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "void ResetUseTimer()", asMETHODPR(TmxFile2D, ResetUseTimer, (), void), asCALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "bool Save(Serializer&) const", asMETHODPR(TmxFile2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "bool SaveFile(const String&in) const", asMETHODPR(TmxFile2D, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "bool Save(const String&in) const", asMETHODPR(TmxFile2D, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "void SendEvent(StringHash)", asMETHODPR(TmxFile2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(TmxFile2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(TmxFile2D, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "void SetBlockEvents(bool)", asMETHODPR(TmxFile2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(TmxFile2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(TmxFile2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // bool TmxFile2D::SetInfo(Orientation2D orientation, int width, int height, float tileWidth, float tileHeight) | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxFile2D", "bool SetInfo(Orientation2D, int, int, float, float)", asMETHODPR(TmxFile2D, SetInfo, (Orientation2D, int, int, float, float), bool), asCALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "void SetMemoryUse(uint)", asMETHODPR(TmxFile2D, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "void SetName(const String&in)", asMETHODPR(TmxFile2D, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "void set_name(const String&in)", asMETHODPR(TmxFile2D, SetName, (const String&), void), asCALL_THISCALL);
    // void TmxFile2D::SetSpriteTextureEdgeOffset(float offset) | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxFile2D", "void SetSpriteTextureEdgeOffset(float)", asMETHODPR(TmxFile2D, SetSpriteTextureEdgeOffset, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "void set_edgeOffset(float)", asMETHODPR(TmxFile2D, SetSpriteTextureEdgeOffset, (float), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit TmxFile2D::TmxFile2D(Context* context) | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectBehaviour("TmxFile2D", asBEHAVE_FACTORY, "TmxFile2D@+ f()", asFUNCTION(TmxFile2D_TmxFile2D_Context), asCALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "void UnsubscribeFromAllEvents()", asMETHODPR(TmxFile2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(TmxFile2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(TmxFile2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(TmxFile2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(TmxFile2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TmxFile2D", "int WeakRefs() const", asMETHODPR(TmxFile2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "int get_weakRefs() const", asMETHODPR(TmxFile2D, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(TmxFile2D, "TmxFile2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(TmxFile2D, "TmxFile2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(TmxFile2D, "TmxFile2D")
#endif
#ifdef REGISTER_MANUAL_PART_TmxFile2D
    REGISTER_MANUAL_PART_TmxFile2D(TmxFile2D, "TmxFile2D")
#endif
    RegisterSubclass<Resource, TmxFile2D>(engine, "Resource", "TmxFile2D");
    RegisterSubclass<Object, TmxFile2D>(engine, "Object", "TmxFile2D");
    RegisterSubclass<RefCounted, TmxFile2D>(engine, "RefCounted", "TmxFile2D");
#endif

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TmxImageLayer2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(TmxImageLayer2D, AddRef, (), void), asCALL_THISCALL);
    // int TmxLayer2D::GetHeight() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "int GetHeight() const", asMETHODPR(TmxImageLayer2D, GetHeight, () const, int), asCALL_THISCALL);
    // const String& TmxLayer2D::GetName() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "const String& GetName() const", asMETHODPR(TmxImageLayer2D, GetName, () const, const String&), asCALL_THISCALL);
    // const Vector2& TmxImageLayer2D::GetPosition() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "const Vector2& GetPosition() const", asMETHODPR(TmxImageLayer2D, GetPosition, () const, const Vector2&), asCALL_THISCALL);
    // const String& TmxLayer2D::GetProperty(const String& name) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "const String& GetProperty(const String&in) const", asMETHODPR(TmxImageLayer2D, GetProperty, (const String&) const, const String&), asCALL_THISCALL);
    // const String& TmxImageLayer2D::GetSource() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "const String& GetSource() const", asMETHODPR(TmxImageLayer2D, GetSource, () const, const String&), asCALL_THISCALL);
    // Sprite2D* TmxImageLayer2D::GetSprite() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "Sprite2D@+ GetSprite() const", asMETHODPR(TmxImageLayer2D, GetSprite, () const, Sprite2D*), asCALL_THISCALL);
    // TmxFile2D* TmxLayer2D::GetTmxFile() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "TmxFile2D@+ GetTmxFile() const", asMETHODPR(TmxImageLayer2D, GetTmxFile, () const, TmxFile2D*), asCALL_THISCALL);
    // TileMapLayerType2D TmxLayer2D::GetType() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "TileMapLayerType2D GetType() const", asMETHODPR(TmxImageLayer2D, GetType, () const, TileMapLayerType2D), asCALL_THISCALL);
    // int TmxLayer2D::GetWidth() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "int GetWidth() const", asMETHODPR(TmxImageLayer2D, GetWidth, () const, int), asCALL_THISCALL);
    // bool TmxLayer2D::HasProperty(const String& name) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "bool HasProperty(const String&in) const", asMETHODPR(TmxImageLayer2D, HasProperty, (const String&) const, bool), asCALL_THISCALL);
    // bool TmxLayer2D::IsVisible() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "bool IsVisible() const", asMETHODPR(TmxImageLayer2D, IsVisible, () const, bool), asCALL_THISCALL);
    // bool TmxImageLayer2D::Load(const XMLElement& element, const TileMapInfo2D& info) | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "bool Load(const XMLElement&in, const TileMapInfo2D&in)", asMETHODPR(TmxImageLayer2D, Load, (const XMLElement&, const TileMapInfo2D&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "int Refs() const", asMETHODPR(TmxImageLayer2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TmxImageLayer2D", "int get_refs() const", asMETHODPR(TmxImageLayer2D, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TmxImageLayer2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(TmxImageLayer2D, ReleaseRef, (), void), asCALL_THISCALL);
    // explicit TmxImageLayer2D::TmxImageLayer2D(TmxFile2D* tmxFile) | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectBehaviour("TmxImageLayer2D", asBEHAVE_FACTORY, "TmxImageLayer2D@+ f(TmxFile2D@+)", asFUNCTION(TmxImageLayer2D_TmxImageLayer2D_TmxFile2D), asCALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "int WeakRefs() const", asMETHODPR(TmxImageLayer2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TmxImageLayer2D", "int get_weakRefs() const", asMETHODPR(TmxImageLayer2D, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_TmxLayer2D
    REGISTER_MANUAL_PART_TmxLayer2D(TmxImageLayer2D, "TmxImageLayer2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(TmxImageLayer2D, "TmxImageLayer2D")
#endif
#ifdef REGISTER_MANUAL_PART_TmxImageLayer2D
    REGISTER_MANUAL_PART_TmxImageLayer2D(TmxImageLayer2D, "TmxImageLayer2D")
#endif
    RegisterSubclass<TmxLayer2D, TmxImageLayer2D>(engine, "TmxLayer2D", "TmxImageLayer2D");
    RegisterSubclass<RefCounted, TmxImageLayer2D>(engine, "RefCounted", "TmxImageLayer2D");
#endif

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TmxLayer2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(TmxLayer2D, AddRef, (), void), asCALL_THISCALL);
    // int TmxLayer2D::GetHeight() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxLayer2D", "int GetHeight() const", asMETHODPR(TmxLayer2D, GetHeight, () const, int), asCALL_THISCALL);
    // const String& TmxLayer2D::GetName() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxLayer2D", "const String& GetName() const", asMETHODPR(TmxLayer2D, GetName, () const, const String&), asCALL_THISCALL);
    // const String& TmxLayer2D::GetProperty(const String& name) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxLayer2D", "const String& GetProperty(const String&in) const", asMETHODPR(TmxLayer2D, GetProperty, (const String&) const, const String&), asCALL_THISCALL);
    // TmxFile2D* TmxLayer2D::GetTmxFile() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxLayer2D", "TmxFile2D@+ GetTmxFile() const", asMETHODPR(TmxLayer2D, GetTmxFile, () const, TmxFile2D*), asCALL_THISCALL);
    // TileMapLayerType2D TmxLayer2D::GetType() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxLayer2D", "TileMapLayerType2D GetType() const", asMETHODPR(TmxLayer2D, GetType, () const, TileMapLayerType2D), asCALL_THISCALL);
    // int TmxLayer2D::GetWidth() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxLayer2D", "int GetWidth() const", asMETHODPR(TmxLayer2D, GetWidth, () const, int), asCALL_THISCALL);
    // bool TmxLayer2D::HasProperty(const String& name) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxLayer2D", "bool HasProperty(const String&in) const", asMETHODPR(TmxLayer2D, HasProperty, (const String&) const, bool), asCALL_THISCALL);
    // bool TmxLayer2D::IsVisible() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxLayer2D", "bool IsVisible() const", asMETHODPR(TmxLayer2D, IsVisible, () const, bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TmxLayer2D", "int Refs() const", asMETHODPR(TmxLayer2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TmxLayer2D", "int get_refs() const", asMETHODPR(TmxLayer2D, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TmxLayer2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(TmxLayer2D, ReleaseRef, (), void), asCALL_THISCALL);
    // TmxLayer2D::TmxLayer2D(TmxFile2D* tmxFile, TileMapLayerType2D type) | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectBehaviour("TmxLayer2D", asBEHAVE_FACTORY, "TmxLayer2D@+ f(TmxFile2D@+, TileMapLayerType2D)", asFUNCTION(TmxLayer2D_TmxLayer2D_TmxFile2D_TileMapLayerType2D), asCALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TmxLayer2D", "int WeakRefs() const", asMETHODPR(TmxLayer2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TmxLayer2D", "int get_weakRefs() const", asMETHODPR(TmxLayer2D, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(TmxLayer2D, "TmxLayer2D")
#endif
#ifdef REGISTER_MANUAL_PART_TmxLayer2D
    REGISTER_MANUAL_PART_TmxLayer2D(TmxLayer2D, "TmxLayer2D")
#endif
    RegisterSubclass<RefCounted, TmxLayer2D>(engine, "RefCounted", "TmxLayer2D");
#endif

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TmxObjectGroup2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(TmxObjectGroup2D, AddRef, (), void), asCALL_THISCALL);
    // int TmxLayer2D::GetHeight() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "int GetHeight() const", asMETHODPR(TmxObjectGroup2D, GetHeight, () const, int), asCALL_THISCALL);
    // const String& TmxLayer2D::GetName() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "const String& GetName() const", asMETHODPR(TmxObjectGroup2D, GetName, () const, const String&), asCALL_THISCALL);
    // unsigned TmxObjectGroup2D::GetNumObjects() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "uint GetNumObjects() const", asMETHODPR(TmxObjectGroup2D, GetNumObjects, () const, unsigned), asCALL_THISCALL);
    // TileMapObject2D* TmxObjectGroup2D::GetObject(unsigned index) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "TileMapObject2D@+ GetObject(uint) const", asMETHODPR(TmxObjectGroup2D, GetObject, (unsigned) const, TileMapObject2D*), asCALL_THISCALL);
    // const String& TmxLayer2D::GetProperty(const String& name) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "const String& GetProperty(const String&in) const", asMETHODPR(TmxObjectGroup2D, GetProperty, (const String&) const, const String&), asCALL_THISCALL);
    // TmxFile2D* TmxLayer2D::GetTmxFile() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "TmxFile2D@+ GetTmxFile() const", asMETHODPR(TmxObjectGroup2D, GetTmxFile, () const, TmxFile2D*), asCALL_THISCALL);
    // TileMapLayerType2D TmxLayer2D::GetType() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "TileMapLayerType2D GetType() const", asMETHODPR(TmxObjectGroup2D, GetType, () const, TileMapLayerType2D), asCALL_THISCALL);
    // int TmxLayer2D::GetWidth() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "int GetWidth() const", asMETHODPR(TmxObjectGroup2D, GetWidth, () const, int), asCALL_THISCALL);
    // bool TmxLayer2D::HasProperty(const String& name) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "bool HasProperty(const String&in) const", asMETHODPR(TmxObjectGroup2D, HasProperty, (const String&) const, bool), asCALL_THISCALL);
    // bool TmxLayer2D::IsVisible() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "bool IsVisible() const", asMETHODPR(TmxObjectGroup2D, IsVisible, () const, bool), asCALL_THISCALL);
    // bool TmxObjectGroup2D::Load(const XMLElement& element, const TileMapInfo2D& info) | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "bool Load(const XMLElement&in, const TileMapInfo2D&in)", asMETHODPR(TmxObjectGroup2D, Load, (const XMLElement&, const TileMapInfo2D&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "int Refs() const", asMETHODPR(TmxObjectGroup2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TmxObjectGroup2D", "int get_refs() const", asMETHODPR(TmxObjectGroup2D, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TmxObjectGroup2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(TmxObjectGroup2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void TmxObjectGroup2D::StoreObject(const XMLElement& objectElem, const SharedPtr<TileMapObject2D>& object, const TileMapInfo2D& info, bool isTile=false) | File: ../Urho2D/TmxFile2D.h
    // Error: type "const SharedPtr<TileMapObject2D>&" can not automatically bind
    // explicit TmxObjectGroup2D::TmxObjectGroup2D(TmxFile2D* tmxFile) | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectBehaviour("TmxObjectGroup2D", asBEHAVE_FACTORY, "TmxObjectGroup2D@+ f(TmxFile2D@+)", asFUNCTION(TmxObjectGroup2D_TmxObjectGroup2D_TmxFile2D), asCALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "int WeakRefs() const", asMETHODPR(TmxObjectGroup2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TmxObjectGroup2D", "int get_weakRefs() const", asMETHODPR(TmxObjectGroup2D, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_TmxLayer2D
    REGISTER_MANUAL_PART_TmxLayer2D(TmxObjectGroup2D, "TmxObjectGroup2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(TmxObjectGroup2D, "TmxObjectGroup2D")
#endif
#ifdef REGISTER_MANUAL_PART_TmxObjectGroup2D
    REGISTER_MANUAL_PART_TmxObjectGroup2D(TmxObjectGroup2D, "TmxObjectGroup2D")
#endif
    RegisterSubclass<TmxLayer2D, TmxObjectGroup2D>(engine, "TmxLayer2D", "TmxObjectGroup2D");
    RegisterSubclass<RefCounted, TmxObjectGroup2D>(engine, "RefCounted", "TmxObjectGroup2D");
#endif

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TmxTileLayer2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(TmxTileLayer2D, AddRef, (), void), asCALL_THISCALL);
    // int TmxLayer2D::GetHeight() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxTileLayer2D", "int GetHeight() const", asMETHODPR(TmxTileLayer2D, GetHeight, () const, int), asCALL_THISCALL);
    // const String& TmxLayer2D::GetName() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxTileLayer2D", "const String& GetName() const", asMETHODPR(TmxTileLayer2D, GetName, () const, const String&), asCALL_THISCALL);
    // const String& TmxLayer2D::GetProperty(const String& name) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxTileLayer2D", "const String& GetProperty(const String&in) const", asMETHODPR(TmxTileLayer2D, GetProperty, (const String&) const, const String&), asCALL_THISCALL);
    // Tile2D* TmxTileLayer2D::GetTile(int x, int y) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxTileLayer2D", "Tile2D@+ GetTile(int, int) const", asMETHODPR(TmxTileLayer2D, GetTile, (int, int) const, Tile2D*), asCALL_THISCALL);
    // TmxFile2D* TmxLayer2D::GetTmxFile() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxTileLayer2D", "TmxFile2D@+ GetTmxFile() const", asMETHODPR(TmxTileLayer2D, GetTmxFile, () const, TmxFile2D*), asCALL_THISCALL);
    // TileMapLayerType2D TmxLayer2D::GetType() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxTileLayer2D", "TileMapLayerType2D GetType() const", asMETHODPR(TmxTileLayer2D, GetType, () const, TileMapLayerType2D), asCALL_THISCALL);
    // int TmxLayer2D::GetWidth() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxTileLayer2D", "int GetWidth() const", asMETHODPR(TmxTileLayer2D, GetWidth, () const, int), asCALL_THISCALL);
    // bool TmxLayer2D::HasProperty(const String& name) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxTileLayer2D", "bool HasProperty(const String&in) const", asMETHODPR(TmxTileLayer2D, HasProperty, (const String&) const, bool), asCALL_THISCALL);
    // bool TmxLayer2D::IsVisible() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxTileLayer2D", "bool IsVisible() const", asMETHODPR(TmxTileLayer2D, IsVisible, () const, bool), asCALL_THISCALL);
    // bool TmxTileLayer2D::Load(const XMLElement& element, const TileMapInfo2D& info) | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxTileLayer2D", "bool Load(const XMLElement&in, const TileMapInfo2D&in)", asMETHODPR(TmxTileLayer2D, Load, (const XMLElement&, const TileMapInfo2D&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TmxTileLayer2D", "int Refs() const", asMETHODPR(TmxTileLayer2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TmxTileLayer2D", "int get_refs() const", asMETHODPR(TmxTileLayer2D, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TmxTileLayer2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(TmxTileLayer2D, ReleaseRef, (), void), asCALL_THISCALL);
    // explicit TmxTileLayer2D::TmxTileLayer2D(TmxFile2D* tmxFile) | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectBehaviour("TmxTileLayer2D", asBEHAVE_FACTORY, "TmxTileLayer2D@+ f(TmxFile2D@+)", asFUNCTION(TmxTileLayer2D_TmxTileLayer2D_TmxFile2D), asCALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TmxTileLayer2D", "int WeakRefs() const", asMETHODPR(TmxTileLayer2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TmxTileLayer2D", "int get_weakRefs() const", asMETHODPR(TmxTileLayer2D, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_TmxLayer2D
    REGISTER_MANUAL_PART_TmxLayer2D(TmxTileLayer2D, "TmxTileLayer2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(TmxTileLayer2D, "TmxTileLayer2D")
#endif
#ifdef REGISTER_MANUAL_PART_TmxTileLayer2D
    REGISTER_MANUAL_PART_TmxTileLayer2D(TmxTileLayer2D, "TmxTileLayer2D")
#endif
    RegisterSubclass<TmxLayer2D, TmxTileLayer2D>(engine, "TmxLayer2D", "TmxTileLayer2D");
    RegisterSubclass<RefCounted, TmxTileLayer2D>(engine, "RefCounted", "TmxTileLayer2D");
#endif

    // float TechniqueEntry::lodDistance_ | File: ../Graphics/Material.h
    engine->RegisterObjectProperty("TechniqueEntry", "float lodDistance", offsetof(TechniqueEntry, lodDistance_));
    // SharedPtr<Technique> TechniqueEntry::original_ | File: ../Graphics/Material.h
    // Error: type "SharedPtr<Technique>" can not automatically bind
    // MaterialQuality TechniqueEntry::qualityLevel_ | File: ../Graphics/Material.h
    engine->RegisterObjectProperty("TechniqueEntry", "MaterialQuality qualityLevel", offsetof(TechniqueEntry, qualityLevel_));
    // SharedPtr<Technique> TechniqueEntry::technique_ | File: ../Graphics/Material.h
    // Error: type "SharedPtr<Technique>" can not automatically bind
    // TechniqueEntry::TechniqueEntry(Technique* tech, MaterialQuality qualityLevel, float lodDistance) noexcept | File: ../Graphics/Material.h
    engine->RegisterObjectBehaviour("TechniqueEntry", asBEHAVE_CONSTRUCT, "void f(Technique@+, MaterialQuality, float)", asFUNCTION(TechniqueEntry_TechniqueEntry_Technique_MaterialQuality_float), asCALL_CDECL_OBJFIRST);
    // TechniqueEntry& TechniqueEntry::operator=(const TechniqueEntry&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<TechniqueEntry>(engine, "TechniqueEntry");
#ifdef REGISTER_MANUAL_PART_TechniqueEntry
    REGISTER_MANUAL_PART_TechniqueEntry(TechniqueEntry, "TechniqueEntry")
#endif

    // float TextureFrame::time_ | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectProperty("TextureFrame", "float time", offsetof(TextureFrame, time_));
    // Rect TextureFrame::uv_ | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectProperty("TextureFrame", "Rect uv", offsetof(TextureFrame, uv_));
    // TextureFrame::TextureFrame() | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectBehaviour("TextureFrame", asBEHAVE_FACTORY, "TextureFrame@+ f()", asFUNCTION(TextureFrame_TextureFrame_void), asCALL_CDECL);
    // TextureFrame& TextureFrame::operator=(const TextureFrame&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<TextureFrame>(engine, "TextureFrame");
    engine->RegisterObjectBehaviour("TextureFrame", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("TextureFrame", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
#ifdef REGISTER_MANUAL_PART_TextureFrame
    REGISTER_MANUAL_PART_TextureFrame(TextureFrame, "TextureFrame")
#endif

#ifdef URHO3D_URHO2D
    // int TileMapInfo2D::height_ | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectProperty("TileMapInfo2D", "int height", offsetof(TileMapInfo2D, height_));
    // Orientation2D TileMapInfo2D::orientation_ | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectProperty("TileMapInfo2D", "Orientation2D orientation", offsetof(TileMapInfo2D, orientation_));
    // float TileMapInfo2D::tileHeight_ | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectProperty("TileMapInfo2D", "float tileHeight", offsetof(TileMapInfo2D, tileHeight_));
    // float TileMapInfo2D::tileWidth_ | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectProperty("TileMapInfo2D", "float tileWidth", offsetof(TileMapInfo2D, tileWidth_));
    // int TileMapInfo2D::width_ | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectProperty("TileMapInfo2D", "int width", offsetof(TileMapInfo2D, width_));
    // Vector2 TileMapInfo2D::ConvertPosition(const Vector2& position) const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapInfo2D", "Vector2 ConvertPosition(const Vector2&in) const", asMETHODPR(TileMapInfo2D, ConvertPosition, (const Vector2&) const, Vector2), asCALL_THISCALL);
    // float TileMapInfo2D::GetMapHeight() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapInfo2D", "float GetMapHeight() const", asMETHODPR(TileMapInfo2D, GetMapHeight, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapInfo2D", "float get_mapHeight() const", asMETHODPR(TileMapInfo2D, GetMapHeight, () const, float), asCALL_THISCALL);
    // float TileMapInfo2D::GetMapWidth() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapInfo2D", "float GetMapWidth() const", asMETHODPR(TileMapInfo2D, GetMapWidth, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapInfo2D", "float get_mapWidth() const", asMETHODPR(TileMapInfo2D, GetMapWidth, () const, float), asCALL_THISCALL);
    // bool TileMapInfo2D::PositionToTileIndex(int& x, int& y, const Vector2& position) const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapInfo2D", "bool PositionToTileIndex(int&, int&, const Vector2&in) const", asMETHODPR(TileMapInfo2D, PositionToTileIndex, (int&, int&, const Vector2&) const, bool), asCALL_THISCALL);
    // Vector2 TileMapInfo2D::TileIndexToPosition(int x, int y) const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapInfo2D", "Vector2 TileIndexToPosition(int, int) const", asMETHODPR(TileMapInfo2D, TileIndexToPosition, (int, int) const, Vector2), asCALL_THISCALL);
    // TileMapInfo2D& TileMapInfo2D::operator=(const TileMapInfo2D&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<TileMapInfo2D>(engine, "TileMapInfo2D");
    engine->RegisterObjectBehaviour("TileMapInfo2D", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("TileMapInfo2D", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
#ifdef REGISTER_MANUAL_PART_TileMapInfo2D
    REGISTER_MANUAL_PART_TileMapInfo2D(TileMapInfo2D, "TileMapInfo2D")
#endif
#endif

}

}
