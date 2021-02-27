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
    engine->RegisterObjectBehaviour("Technique", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Technique, AddRef, (), void), AS_CALL_THISCALL);
    // bool Technique::BeginLoad(Deserializer& source) override | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "bool BeginLoad(Deserializer&)", AS_METHODPR(Technique, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // SharedPtr<Technique> Technique::Clone(const String& cloneName=String::EMPTY) const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "Technique@+ Clone(const String&in = String::EMPTY) const", AS_FUNCTION_OBJFIRST(Technique_Clone_String), AS_CALL_CDECL_OBJFIRST);
    // SharedPtr<Technique> Technique::CloneWithDefines(const String& vsDefines, const String& psDefines) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "Technique@+ CloneWithDefines(const String&in, const String&in)", AS_FUNCTION_OBJFIRST(Technique_CloneWithDefines_String_String), AS_CALL_CDECL_OBJFIRST);
    // Pass* Technique::CreatePass(const String& name) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "Pass@+ CreatePass(const String&in)", AS_METHODPR(Technique, CreatePass, (const String&), Pass*), AS_CALL_THISCALL);
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "bool EndLoad()", AS_METHODPR(Technique, EndLoad, (), bool), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(Technique, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "bool GetBlockEvents() const", AS_METHODPR(Technique, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "const String& GetCategory() const", AS_METHODPR(Technique, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "const String& get_category() const", AS_METHODPR(Technique, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "VariantMap& GetEventDataMap() const", AS_METHODPR(Technique, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "Object@+ GetEventSender() const", AS_METHODPR(Technique, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Technique, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Technique, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Technique, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "const VariantMap& get_globalVars() const", AS_METHODPR(Technique, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "uint GetMemoryUse() const", AS_METHODPR(Technique, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "uint get_memoryUse() const", AS_METHODPR(Technique, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "const String& GetName() const", AS_METHODPR(Technique, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "const String& get_name() const", AS_METHODPR(Technique, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "StringHash GetNameHash() const", AS_METHODPR(Technique, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // unsigned Technique::GetNumPasses() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "uint GetNumPasses() const", AS_METHODPR(Technique, GetNumPasses, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "uint get_numPasses() const", AS_METHODPR(Technique, GetNumPasses, () const, unsigned), AS_CALL_THISCALL);
    // Pass* Technique::GetPass(unsigned passIndex) const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "Pass@+ GetPass(uint) const", AS_METHODPR(Technique, GetPass, (unsigned) const, Pass*), AS_CALL_THISCALL);
    // Pass* Technique::GetPass(const String& name) const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "Pass@+ GetPass(const String&in) const", AS_METHODPR(Technique, GetPass, (const String&) const, Pass*), AS_CALL_THISCALL);
    // PODVector<Pass*> Technique::GetPasses() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "Array<Pass@>@ GetPasses() const", AS_FUNCTION_OBJFIRST(Technique_GetPasses_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Technique", "Array<Pass@>@ get_passes() const", AS_FUNCTION_OBJFIRST(Technique_GetPasses_void), AS_CALL_CDECL_OBJFIRST);
    // static unsigned Technique::GetPassIndex(const String& passName) | File: ../Graphics/Technique.h
    engine->SetDefaultNamespace("Technique");
    engine->RegisterGlobalFunction("uint GetPassIndex(const String&in)", AS_FUNCTIONPR(Technique::GetPassIndex, (const String&), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // Vector<String> Technique::GetPassNames() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "Array<String>@ GetPassNames() const", AS_FUNCTION_OBJFIRST(Technique_GetPassNames_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Technique", "Array<String>@ get_passNames() const", AS_FUNCTION_OBJFIRST(Technique_GetPassNames_void), AS_CALL_CDECL_OBJFIRST);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Technique, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // Pass* Technique::GetSupportedPass(unsigned passIndex) const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "Pass@+ GetSupportedPass(uint) const", AS_METHODPR(Technique, GetSupportedPass, (unsigned) const, Pass*), AS_CALL_THISCALL);
    // Pass* Technique::GetSupportedPass(const String& name) const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "Pass@+ GetSupportedPass(const String&in) const", AS_METHODPR(Technique, GetSupportedPass, (const String&) const, Pass*), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "StringHash GetType() const", AS_METHODPR(Technique, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "StringHash get_type() const", AS_METHODPR(Technique, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "const String& GetTypeName() const", AS_METHODPR(Technique, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "const String& get_typeName() const", AS_METHODPR(Technique, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "uint GetUseTimer()", AS_METHODPR(Technique, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "uint get_useTimer()", AS_METHODPR(Technique, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "bool HasEventHandlers() const", AS_METHODPR(Technique, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Technique::HasPass(unsigned passIndex) const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "bool HasPass(uint) const", AS_METHODPR(Technique, HasPass, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool Technique::HasPass(const String& name) const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "bool HasPass(const String&in) const", AS_METHODPR(Technique, HasPass, (const String&) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Technique, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Technique, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Technique::IsDesktop() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "bool IsDesktop() const", AS_METHODPR(Technique, IsDesktop, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "bool get_desktop() const", AS_METHODPR(Technique, IsDesktop, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Technique, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Technique::IsSupported() const | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "bool IsSupported() const", AS_METHODPR(Technique, IsSupported, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "bool get_supported() const", AS_METHODPR(Technique, IsSupported, () const, bool), AS_CALL_THISCALL);
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "bool Load(Deserializer&)", AS_METHODPR(Technique, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "bool LoadFile(const String&in)", AS_METHODPR(Technique, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "bool Load(const String&in)", AS_METHODPR(Technique, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Technique, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Technique", "int Refs() const", AS_METHODPR(Technique, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "int get_refs() const", AS_METHODPR(Technique, Refs, () const, int), AS_CALL_THISCALL);
    // static void Technique::RegisterObject(Context* context) | File: ../Graphics/Technique.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Technique", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Technique, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Technique::ReleaseShaders() | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "void ReleaseShaders()", AS_METHODPR(Technique, ReleaseShaders, (), void), AS_CALL_THISCALL);
    // void Technique::RemovePass(const String& name) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "void RemovePass(const String&in)", AS_METHODPR(Technique, RemovePass, (const String&), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "void ResetUseTimer()", AS_METHODPR(Technique, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "bool Save(Serializer&) const", AS_METHODPR(Technique, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "bool SaveFile(const String&in) const", AS_METHODPR(Technique, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "bool Save(const String&in) const", AS_METHODPR(Technique, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "void SendEvent(StringHash)", AS_METHODPR(Technique, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Technique, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(Technique, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "void SetBlockEvents(bool)", AS_METHODPR(Technique, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Technique, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Technique, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Technique::SetIsDesktop(bool enable) | File: ../Graphics/Technique.h
    engine->RegisterObjectMethod("Technique", "void SetIsDesktop(bool)", AS_METHODPR(Technique, SetIsDesktop, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "void set_desktop(bool)", AS_METHODPR(Technique, SetIsDesktop, (bool), void), AS_CALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "void SetMemoryUse(uint)", AS_METHODPR(Technique, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Technique", "void SetName(const String&in)", AS_METHODPR(Technique, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "void set_name(const String&in)", AS_METHODPR(Technique, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit Technique::Technique(Context* context) | File: ../Graphics/Technique.h
    engine->RegisterObjectBehaviour("Technique", asBEHAVE_FACTORY, "Technique@+ f()", AS_FUNCTION(Technique_Technique_Context), AS_CALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "void UnsubscribeFromAllEvents()", AS_METHODPR(Technique, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Technique_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Technique, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Technique, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Technique", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Technique, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Technique", "int WeakRefs() const", AS_METHODPR(Technique, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Technique", "int get_weakRefs() const", AS_METHODPR(Technique, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("Terrain", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Terrain, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "void AllocateNetworkState()", AS_METHODPR(Terrain, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void Terrain::ApplyAttributes() override | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void ApplyAttributes()", AS_METHODPR(Terrain, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void Terrain::ApplyHeightMap() | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void ApplyHeightMap()", AS_METHODPR(Terrain, ApplyHeightMap, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Terrain::CreatePatchGeometry(TerrainPatch* patch) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void CreatePatchGeometry(TerrainPatch@+)", AS_METHODPR(Terrain, CreatePatchGeometry, (TerrainPatch*), void), AS_CALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(Terrain, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "bool GetAnimationEnabled() const", AS_METHODPR(Terrain, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool get_animationEnabled() const", AS_METHODPR(Terrain, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "Variant GetAttribute(uint) const", AS_METHODPR(Terrain, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "Variant get_attributes(uint) const", AS_METHODPR(Terrain, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "Variant GetAttribute(const String&in) const", AS_METHODPR(Terrain, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(Terrain, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(Terrain, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(Terrain, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(Terrain, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Terrain, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Terrain, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Terrain, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "bool GetBlockEvents() const", AS_METHODPR(Terrain, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // bool Terrain::GetCastShadows() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "bool GetCastShadows() const", AS_METHODPR(Terrain, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool get_castShadows() const", AS_METHODPR(Terrain, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "const String& GetCategory() const", AS_METHODPR(Terrain, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "const String& get_category() const", AS_METHODPR(Terrain, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "Component@+ GetComponent(StringHash) const", AS_METHODPR(Terrain, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Terrain", "float GetDrawDistance() const", AS_METHODPR(Terrain, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "float get_drawDistance() const", AS_METHODPR(Terrain, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    // Terrain* Terrain::GetEastNeighbor() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "Terrain@+ GetEastNeighbor() const", AS_METHODPR(Terrain, GetEastNeighbor, () const, Terrain*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "Terrain@+ get_eastNeighbor() const", AS_METHODPR(Terrain, GetEastNeighbor, () const, Terrain*), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "VariantMap& GetEventDataMap() const", AS_METHODPR(Terrain, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "Object@+ GetEventSender() const", AS_METHODPR(Terrain, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Terrain, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Terrain, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Terrain, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "const VariantMap& get_globalVars() const", AS_METHODPR(Terrain, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // float Terrain::GetHeight(const Vector3& worldPosition) const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "float GetHeight(const Vector3&in) const", AS_METHODPR(Terrain, GetHeight, (const Vector3&) const, float), AS_CALL_THISCALL);
    // SharedArrayPtr<float> Terrain::GetHeightData() const | File: ../Graphics/Terrain.h
    // Error: type "SharedArrayPtr<float>" can not automatically bind
    // Image* Terrain::GetHeightMap() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "Image@+ GetHeightMap() const", AS_METHODPR(Terrain, GetHeightMap, () const, Image*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "Image@+ get_heightMap() const", AS_METHODPR(Terrain, GetHeightMap, () const, Image*), AS_CALL_THISCALL);
    // ResourceRef Terrain::GetHeightMapAttr() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "ResourceRef GetHeightMapAttr() const", AS_METHODPR(Terrain, GetHeightMapAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "uint GetID() const", AS_METHODPR(Terrain, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "uint get_id() const", AS_METHODPR(Terrain, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Terrain, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // unsigned Terrain::GetLightMask() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "uint GetLightMask() const", AS_METHODPR(Terrain, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "uint get_lightMask() const", AS_METHODPR(Terrain, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    // float Terrain::GetLodBias() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "float GetLodBias() const", AS_METHODPR(Terrain, GetLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "float get_lodBias() const", AS_METHODPR(Terrain, GetLodBias, () const, float), AS_CALL_THISCALL);
    // Material* Terrain::GetMaterial() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "Material@+ GetMaterial() const", AS_METHODPR(Terrain, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "Material@+ get_material() const", AS_METHODPR(Terrain, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    // ResourceRef Terrain::GetMaterialAttr() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "ResourceRef GetMaterialAttr() const", AS_METHODPR(Terrain, GetMaterialAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // unsigned Terrain::GetMaxLights() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "uint GetMaxLights() const", AS_METHODPR(Terrain, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "uint get_maxLights() const", AS_METHODPR(Terrain, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Terrain::GetMaxLodLevels() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "uint GetMaxLodLevels() const", AS_METHODPR(Terrain, GetMaxLodLevels, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "uint get_maxLodLevels() const", AS_METHODPR(Terrain, GetMaxLodLevels, () const, unsigned), AS_CALL_THISCALL);
    // TerrainPatch* Terrain::GetNeighborPatch(int x, int z) const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "TerrainPatch@+ GetNeighborPatch(int, int) const", AS_METHODPR(Terrain, GetNeighborPatch, (int, int) const, TerrainPatch*), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "Node@+ GetNode() const", AS_METHODPR(Terrain, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "Node@+ get_node() const", AS_METHODPR(Terrain, GetNode, () const, Node*), AS_CALL_THISCALL);
    // Vector3 Terrain::GetNormal(const Vector3& worldPosition) const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "Vector3 GetNormal(const Vector3&in) const", AS_METHODPR(Terrain, GetNormal, (const Vector3&) const, Vector3), AS_CALL_THISCALL);
    // Terrain* Terrain::GetNorthNeighbor() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "Terrain@+ GetNorthNeighbor() const", AS_METHODPR(Terrain, GetNorthNeighbor, () const, Terrain*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "Terrain@+ get_northNeighbor() const", AS_METHODPR(Terrain, GetNorthNeighbor, () const, Terrain*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "uint GetNumAttributes() const", AS_METHODPR(Terrain, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "uint get_numAttributes() const", AS_METHODPR(Terrain, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "uint GetNumNetworkAttributes() const", AS_METHODPR(Terrain, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // const IntVector2& Terrain::GetNumPatches() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "const IntVector2& GetNumPatches() const", AS_METHODPR(Terrain, GetNumPatches, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "const IntVector2& get_numPatches() const", AS_METHODPR(Terrain, GetNumPatches, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& Terrain::GetNumVertices() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "const IntVector2& GetNumVertices() const", AS_METHODPR(Terrain, GetNumVertices, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "const IntVector2& get_numVertices() const", AS_METHODPR(Terrain, GetNumVertices, () const, const IntVector2&), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(Terrain, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(Terrain, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(Terrain, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // unsigned Terrain::GetOcclusionLodLevel() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "uint GetOcclusionLodLevel() const", AS_METHODPR(Terrain, GetOcclusionLodLevel, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "uint get_occlusionLodLevel() const", AS_METHODPR(Terrain, GetOcclusionLodLevel, () const, unsigned), AS_CALL_THISCALL);
    // TerrainPatch* Terrain::GetPatch(unsigned index) const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "TerrainPatch@+ GetPatch(uint) const", AS_METHODPR(Terrain, GetPatch, (unsigned) const, TerrainPatch*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "TerrainPatch@+ get_patches(uint) const", AS_METHODPR(Terrain, GetPatch, (unsigned) const, TerrainPatch*), AS_CALL_THISCALL);
    // TerrainPatch* Terrain::GetPatch(int x, int z) const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "TerrainPatch@+ GetPatch(int, int) const", AS_METHODPR(Terrain, GetPatch, (int, int) const, TerrainPatch*), AS_CALL_THISCALL);
    // int Terrain::GetPatchSize() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "int GetPatchSize() const", AS_METHODPR(Terrain, GetPatchSize, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "int get_patchSize() const", AS_METHODPR(Terrain, GetPatchSize, () const, int), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "Scene@+ GetScene() const", AS_METHODPR(Terrain, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // float Terrain::GetShadowDistance() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "float GetShadowDistance() const", AS_METHODPR(Terrain, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "float get_shadowDistance() const", AS_METHODPR(Terrain, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    // unsigned Terrain::GetShadowMask() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "uint GetShadowMask() const", AS_METHODPR(Terrain, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "uint get_shadowMask() const", AS_METHODPR(Terrain, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    // bool Terrain::GetSmoothing() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "bool GetSmoothing() const", AS_METHODPR(Terrain, GetSmoothing, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool get_smoothing() const", AS_METHODPR(Terrain, GetSmoothing, () const, bool), AS_CALL_THISCALL);
    // Terrain* Terrain::GetSouthNeighbor() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "Terrain@+ GetSouthNeighbor() const", AS_METHODPR(Terrain, GetSouthNeighbor, () const, Terrain*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "Terrain@+ get_southNeighbor() const", AS_METHODPR(Terrain, GetSouthNeighbor, () const, Terrain*), AS_CALL_THISCALL);
    // const Vector3& Terrain::GetSpacing() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "const Vector3& GetSpacing() const", AS_METHODPR(Terrain, GetSpacing, () const, const Vector3&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "const Vector3& get_spacing() const", AS_METHODPR(Terrain, GetSpacing, () const, const Vector3&), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Terrain, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "StringHash GetType() const", AS_METHODPR(Terrain, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "StringHash get_type() const", AS_METHODPR(Terrain, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "const String& GetTypeName() const", AS_METHODPR(Terrain, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "const String& get_typeName() const", AS_METHODPR(Terrain, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Terrain::GetViewMask() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "uint GetViewMask() const", AS_METHODPR(Terrain, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "uint get_viewMask() const", AS_METHODPR(Terrain, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    // Terrain* Terrain::GetWestNeighbor() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "Terrain@+ GetWestNeighbor() const", AS_METHODPR(Terrain, GetWestNeighbor, () const, Terrain*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "Terrain@+ get_westNeighbor() const", AS_METHODPR(Terrain, GetWestNeighbor, () const, Terrain*), AS_CALL_THISCALL);
    // unsigned Terrain::GetZoneMask() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "uint GetZoneMask() const", AS_METHODPR(Terrain, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "uint get_zoneMask() const", AS_METHODPR(Terrain, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "bool HasEventHandlers() const", AS_METHODPR(Terrain, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Terrain, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Terrain, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // Vector3 Terrain::HeightMapToWorld(const IntVector2& pixelPosition) const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "Vector3 HeightMapToWorld(const IntVector2&in) const", AS_METHODPR(Terrain, HeightMapToWorld, (const IntVector2&) const, Vector3), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "bool IsEnabled() const", AS_METHODPR(Terrain, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool get_enabled() const", AS_METHODPR(Terrain, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "bool IsEnabledEffective() const", AS_METHODPR(Terrain, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool get_enabledEffective() const", AS_METHODPR(Terrain, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Terrain, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Terrain::IsOccludee() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "bool IsOccludee() const", AS_METHODPR(Terrain, IsOccludee, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool get_occludee() const", AS_METHODPR(Terrain, IsOccludee, () const, bool), AS_CALL_THISCALL);
    // bool Terrain::IsOccluder() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "bool IsOccluder() const", AS_METHODPR(Terrain, IsOccluder, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool get_occluder() const", AS_METHODPR(Terrain, IsOccluder, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "bool IsReplicated() const", AS_METHODPR(Terrain, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool get_replicated() const", AS_METHODPR(Terrain, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "bool IsTemporary() const", AS_METHODPR(Terrain, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool get_temporary() const", AS_METHODPR(Terrain, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool Terrain::IsVisible() const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "bool IsVisible() const", AS_METHODPR(Terrain, IsVisible, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "bool Load(Deserializer&)", AS_METHODPR(Terrain, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Terrain, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Terrain, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "void MarkNetworkUpdate()", AS_METHODPR(Terrain, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Terrain, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Terrain, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Terrain, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Terrain::OnSetEnabled() override | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void OnSetEnabled()", AS_METHODPR(Terrain, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "void PrepareNetworkUpdate()", AS_METHODPR(Terrain, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Terrain, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Terrain, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Terrain", "int Refs() const", AS_METHODPR(Terrain, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "int get_refs() const", AS_METHODPR(Terrain, Refs, () const, int), AS_CALL_THISCALL);
    // static void Terrain::RegisterObject(Context* context) | File: ../Graphics/Terrain.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Terrain", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Terrain, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "void Remove()", AS_METHODPR(Terrain, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(Terrain, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "void RemoveInstanceDefault()", AS_METHODPR(Terrain, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "void RemoveObjectAnimation()", AS_METHODPR(Terrain, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "void ResetToDefault()", AS_METHODPR(Terrain, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "bool Save(Serializer&) const", AS_METHODPR(Terrain, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "bool SaveDefaultAttributes() const", AS_METHODPR(Terrain, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "bool SaveJSON(JSONValue&) const", AS_METHODPR(Terrain, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "bool SaveXML(XMLElement&) const", AS_METHODPR(Terrain, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "void SendEvent(StringHash)", AS_METHODPR(Terrain, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Terrain, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "void SetAnimationEnabled(bool)", AS_METHODPR(Terrain, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_animationEnabled(bool)", AS_METHODPR(Terrain, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "void SetAnimationTime(float)", AS_METHODPR(Terrain, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Terrain, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Terrain, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Terrain, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Terrain, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(Terrain, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(Terrain, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Terrain, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "void SetBlockEvents(bool)", AS_METHODPR(Terrain, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Terrain::SetCastShadows(bool enable) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetCastShadows(bool)", AS_METHODPR(Terrain, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_castShadows(bool)", AS_METHODPR(Terrain, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    // void Terrain::SetDrawDistance(float distance) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetDrawDistance(float)", AS_METHODPR(Terrain, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_drawDistance(float)", AS_METHODPR(Terrain, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    // void Terrain::SetEastNeighbor(Terrain* east) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetEastNeighbor(Terrain@+)", AS_METHODPR(Terrain, SetEastNeighbor, (Terrain*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_eastNeighbor(Terrain@+)", AS_METHODPR(Terrain, SetEastNeighbor, (Terrain*), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Terrain", "void SetEnabled(bool)", AS_METHODPR(Terrain, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_enabled(bool)", AS_METHODPR(Terrain, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Terrain, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Terrain, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // bool Terrain::SetHeightMap(Image* image) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "bool SetHeightMap(Image@+)", AS_METHODPR(Terrain, SetHeightMap, (Image*), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "bool set_heightMap(Image@+)", AS_METHODPR(Terrain, SetHeightMap, (Image*), bool), AS_CALL_THISCALL);
    // void Terrain::SetHeightMapAttr(const ResourceRef& value) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetHeightMapAttr(const ResourceRef&in)", AS_METHODPR(Terrain, SetHeightMapAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "void SetInstanceDefault(bool)", AS_METHODPR(Terrain, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Terrain, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Terrain::SetLightMask(unsigned mask) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetLightMask(uint)", AS_METHODPR(Terrain, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_lightMask(uint)", AS_METHODPR(Terrain, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    // void Terrain::SetLodBias(float bias) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetLodBias(float)", AS_METHODPR(Terrain, SetLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_lodBias(float)", AS_METHODPR(Terrain, SetLodBias, (float), void), AS_CALL_THISCALL);
    // void Terrain::SetMaterial(Material* material) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetMaterial(Material@+)", AS_METHODPR(Terrain, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_material(Material@+)", AS_METHODPR(Terrain, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    // void Terrain::SetMaterialAttr(const ResourceRef& value) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetMaterialAttr(const ResourceRef&in)", AS_METHODPR(Terrain, SetMaterialAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Terrain::SetMaxLights(unsigned num) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetMaxLights(uint)", AS_METHODPR(Terrain, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_maxLights(uint)", AS_METHODPR(Terrain, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    // void Terrain::SetMaxLodLevels(unsigned levels) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetMaxLodLevels(uint)", AS_METHODPR(Terrain, SetMaxLodLevels, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_maxLodLevels(uint)", AS_METHODPR(Terrain, SetMaxLodLevels, (unsigned), void), AS_CALL_THISCALL);
    // void Terrain::SetMaxLodLevelsAttr(unsigned value) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetMaxLodLevelsAttr(uint)", AS_METHODPR(Terrain, SetMaxLodLevelsAttr, (unsigned), void), AS_CALL_THISCALL);
    // void Terrain::SetNeighbors(Terrain* north, Terrain* south, Terrain* west, Terrain* east) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetNeighbors(Terrain@+, Terrain@+, Terrain@+, Terrain@+)", AS_METHODPR(Terrain, SetNeighbors, (Terrain*, Terrain*, Terrain*, Terrain*), void), AS_CALL_THISCALL);
    // void Terrain::SetNorthNeighbor(Terrain* north) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetNorthNeighbor(Terrain@+)", AS_METHODPR(Terrain, SetNorthNeighbor, (Terrain*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_northNeighbor(Terrain@+)", AS_METHODPR(Terrain, SetNorthNeighbor, (Terrain*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(Terrain, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(Terrain, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Terrain", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(Terrain, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Terrain::SetOccludee(bool enable) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetOccludee(bool)", AS_METHODPR(Terrain, SetOccludee, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_occludee(bool)", AS_METHODPR(Terrain, SetOccludee, (bool), void), AS_CALL_THISCALL);
    // void Terrain::SetOccluder(bool enable) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetOccluder(bool)", AS_METHODPR(Terrain, SetOccluder, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_occluder(bool)", AS_METHODPR(Terrain, SetOccluder, (bool), void), AS_CALL_THISCALL);
    // void Terrain::SetOcclusionLodLevel(unsigned level) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetOcclusionLodLevel(uint)", AS_METHODPR(Terrain, SetOcclusionLodLevel, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_occlusionLodLevel(uint)", AS_METHODPR(Terrain, SetOcclusionLodLevel, (unsigned), void), AS_CALL_THISCALL);
    // void Terrain::SetOcclusionLodLevelAttr(unsigned value) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetOcclusionLodLevelAttr(uint)", AS_METHODPR(Terrain, SetOcclusionLodLevelAttr, (unsigned), void), AS_CALL_THISCALL);
    // void Terrain::SetPatchSize(int size) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetPatchSize(int)", AS_METHODPR(Terrain, SetPatchSize, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_patchSize(int)", AS_METHODPR(Terrain, SetPatchSize, (int), void), AS_CALL_THISCALL);
    // void Terrain::SetPatchSizeAttr(int value) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetPatchSizeAttr(int)", AS_METHODPR(Terrain, SetPatchSizeAttr, (int), void), AS_CALL_THISCALL);
    // void Terrain::SetShadowDistance(float distance) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetShadowDistance(float)", AS_METHODPR(Terrain, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_shadowDistance(float)", AS_METHODPR(Terrain, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    // void Terrain::SetShadowMask(unsigned mask) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetShadowMask(uint)", AS_METHODPR(Terrain, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_shadowMask(uint)", AS_METHODPR(Terrain, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    // void Terrain::SetSmoothing(bool enable) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetSmoothing(bool)", AS_METHODPR(Terrain, SetSmoothing, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_smoothing(bool)", AS_METHODPR(Terrain, SetSmoothing, (bool), void), AS_CALL_THISCALL);
    // void Terrain::SetSouthNeighbor(Terrain* south) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetSouthNeighbor(Terrain@+)", AS_METHODPR(Terrain, SetSouthNeighbor, (Terrain*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_southNeighbor(Terrain@+)", AS_METHODPR(Terrain, SetSouthNeighbor, (Terrain*), void), AS_CALL_THISCALL);
    // void Terrain::SetSpacing(const Vector3& spacing) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetSpacing(const Vector3&in)", AS_METHODPR(Terrain, SetSpacing, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_spacing(const Vector3&in)", AS_METHODPR(Terrain, SetSpacing, (const Vector3&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "void SetTemporary(bool)", AS_METHODPR(Terrain, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_temporary(bool)", AS_METHODPR(Terrain, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Terrain::SetViewMask(unsigned mask) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetViewMask(uint)", AS_METHODPR(Terrain, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_viewMask(uint)", AS_METHODPR(Terrain, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    // void Terrain::SetWestNeighbor(Terrain* west) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetWestNeighbor(Terrain@+)", AS_METHODPR(Terrain, SetWestNeighbor, (Terrain*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_westNeighbor(Terrain@+)", AS_METHODPR(Terrain, SetWestNeighbor, (Terrain*), void), AS_CALL_THISCALL);
    // void Terrain::SetZoneMask(unsigned mask) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void SetZoneMask(uint)", AS_METHODPR(Terrain, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "void set_zoneMask(uint)", AS_METHODPR(Terrain, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit Terrain::Terrain(Context* context) | File: ../Graphics/Terrain.h
    engine->RegisterObjectBehaviour("Terrain", asBEHAVE_FACTORY, "Terrain@+ f()", AS_FUNCTION(Terrain_Terrain_Context), AS_CALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "void UnsubscribeFromAllEvents()", AS_METHODPR(Terrain, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Terrain_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Terrain, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Terrain, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Terrain", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Terrain, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void Terrain::UpdatePatchLod(TerrainPatch* patch) | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "void UpdatePatchLod(TerrainPatch@+)", AS_METHODPR(Terrain, UpdatePatchLod, (TerrainPatch*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Terrain", "int WeakRefs() const", AS_METHODPR(Terrain, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Terrain", "int get_weakRefs() const", AS_METHODPR(Terrain, WeakRefs, () const, int), AS_CALL_THISCALL);
    // IntVector2 Terrain::WorldToHeightMap(const Vector3& worldPosition) const | File: ../Graphics/Terrain.h
    engine->RegisterObjectMethod("Terrain", "IntVector2 WorldToHeightMap(const Vector3&in) const", AS_METHODPR(Terrain, WorldToHeightMap, (const Vector3&) const, IntVector2), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Terrain, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Terrain, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Terrain", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Terrain, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("TerrainPatch", "void AddLight(Light@+)", AS_METHODPR(TerrainPatch, AddLight, (Light*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TerrainPatch", asBEHAVE_ADDREF, "void f()", AS_METHODPR(TerrainPatch, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void AddVertexLight(Light@+)", AS_METHODPR(TerrainPatch, AddVertexLight, (Light*), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "void AllocateNetworkState()", AS_METHODPR(TerrainPatch, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "void ApplyAttributes()", AS_METHODPR(TerrainPatch, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void TerrainPatch::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(TerrainPatch, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool TerrainPatch::DrawOcclusion(OcclusionBuffer* buffer) override | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "bool DrawOcclusion(OcclusionBuffer@+)", AS_METHODPR(TerrainPatch, DrawOcclusion, (OcclusionBuffer*), bool), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool GetAnimationEnabled() const", AS_METHODPR(TerrainPatch, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "bool get_animationEnabled() const", AS_METHODPR(TerrainPatch, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "Variant GetAttribute(uint) const", AS_METHODPR(TerrainPatch, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "Variant get_attributes(uint) const", AS_METHODPR(TerrainPatch, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "Variant GetAttribute(const String&in) const", AS_METHODPR(TerrainPatch, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(TerrainPatch, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(TerrainPatch, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(TerrainPatch, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(TerrainPatch, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "Variant GetAttributeDefault(uint) const", AS_METHODPR(TerrainPatch, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "Variant get_attributeDefaults(uint) const", AS_METHODPR(TerrainPatch, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(TerrainPatch, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "bool GetBlockEvents() const", AS_METHODPR(TerrainPatch, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "const BoundingBox& GetBoundingBox() const", AS_METHODPR(TerrainPatch, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "const BoundingBox& get_boundingBox() const", AS_METHODPR(TerrainPatch, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool GetCastShadows() const", AS_METHODPR(TerrainPatch, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "bool get_castShadows() const", AS_METHODPR(TerrainPatch, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "const String& GetCategory() const", AS_METHODPR(TerrainPatch, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "const String& get_category() const", AS_METHODPR(TerrainPatch, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "Component@+ GetComponent(StringHash) const", AS_METHODPR(TerrainPatch, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // const IntVector2& TerrainPatch::GetCoordinates() const | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "const IntVector2& GetCoordinates() const", AS_METHODPR(TerrainPatch, GetCoordinates, () const, const IntVector2&), AS_CALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // float Drawable::GetDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "float GetDistance() const", AS_METHODPR(TerrainPatch, GetDistance, () const, float), AS_CALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "uint8 GetDrawableFlags() const", AS_METHODPR(TerrainPatch, GetDrawableFlags, () const, unsigned char), AS_CALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "float GetDrawDistance() const", AS_METHODPR(TerrainPatch, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "float get_drawDistance() const", AS_METHODPR(TerrainPatch, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    // TerrainPatch* TerrainPatch::GetEastPatch() const | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "TerrainPatch@+ GetEastPatch() const", AS_METHODPR(TerrainPatch, GetEastPatch, () const, TerrainPatch*), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "VariantMap& GetEventDataMap() const", AS_METHODPR(TerrainPatch, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "Object@+ GetEventSender() const", AS_METHODPR(TerrainPatch, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "Light@+ GetFirstLight() const", AS_METHODPR(TerrainPatch, GetFirstLight, () const, Light*), AS_CALL_THISCALL);
    // Geometry* TerrainPatch::GetGeometry() const | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "Geometry@+ GetGeometry() const", AS_METHODPR(TerrainPatch, GetGeometry, () const, Geometry*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(TerrainPatch, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(TerrainPatch, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "const VariantMap& GetGlobalVars() const", AS_METHODPR(TerrainPatch, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "const VariantMap& get_globalVars() const", AS_METHODPR(TerrainPatch, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "uint GetID() const", AS_METHODPR(TerrainPatch, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "uint get_id() const", AS_METHODPR(TerrainPatch, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(TerrainPatch, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "uint GetLightMask() const", AS_METHODPR(TerrainPatch, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "uint get_lightMask() const", AS_METHODPR(TerrainPatch, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "Array<Light@>@ GetLights() const", AS_FUNCTION_OBJFIRST(TerrainPatch_GetLights_void), AS_CALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "float GetLodBias() const", AS_METHODPR(TerrainPatch, GetLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "float get_lodBias() const", AS_METHODPR(TerrainPatch, GetLodBias, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "float GetLodDistance() const", AS_METHODPR(TerrainPatch, GetLodDistance, () const, float), AS_CALL_THISCALL);
    // PODVector<float>& TerrainPatch::GetLodErrors() | File: ../Graphics/TerrainPatch.h
    // Error: type "PODVector<float>&" can not automatically bind
    // Geometry* TerrainPatch::GetLodGeometry(unsigned batchIndex, unsigned level) override | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "Geometry@+ GetLodGeometry(uint, uint)", AS_METHODPR(TerrainPatch, GetLodGeometry, (unsigned, unsigned), Geometry*), AS_CALL_THISCALL);
    // unsigned TerrainPatch::GetLodLevel() const | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "uint GetLodLevel() const", AS_METHODPR(TerrainPatch, GetLodLevel, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "uint GetMaxLights() const", AS_METHODPR(TerrainPatch, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "uint get_maxLights() const", AS_METHODPR(TerrainPatch, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    // Geometry* TerrainPatch::GetMaxLodGeometry() const | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "Geometry@+ GetMaxLodGeometry() const", AS_METHODPR(TerrainPatch, GetMaxLodGeometry, () const, Geometry*), AS_CALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "float GetMaxZ() const", AS_METHODPR(TerrainPatch, GetMaxZ, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "float GetMinZ() const", AS_METHODPR(TerrainPatch, GetMinZ, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "Node@+ GetNode() const", AS_METHODPR(TerrainPatch, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "Node@+ get_node() const", AS_METHODPR(TerrainPatch, GetNode, () const, Node*), AS_CALL_THISCALL);
    // TerrainPatch* TerrainPatch::GetNorthPatch() const | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "TerrainPatch@+ GetNorthPatch() const", AS_METHODPR(TerrainPatch, GetNorthPatch, () const, TerrainPatch*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "uint GetNumAttributes() const", AS_METHODPR(TerrainPatch, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "uint get_numAttributes() const", AS_METHODPR(TerrainPatch, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "uint GetNumNetworkAttributes() const", AS_METHODPR(TerrainPatch, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned TerrainPatch::GetNumOccluderTriangles() override | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "uint GetNumOccluderTriangles()", AS_METHODPR(TerrainPatch, GetNumOccluderTriangles, (), unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(TerrainPatch, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(TerrainPatch, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(TerrainPatch, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Geometry* TerrainPatch::GetOcclusionGeometry() const | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "Geometry@+ GetOcclusionGeometry() const", AS_METHODPR(TerrainPatch, GetOcclusionGeometry, () const, Geometry*), AS_CALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // Terrain* TerrainPatch::GetOwner() const | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "Terrain@+ GetOwner() const", AS_METHODPR(TerrainPatch, GetOwner, () const, Terrain*), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "Scene@+ GetScene() const", AS_METHODPR(TerrainPatch, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "float GetShadowDistance() const", AS_METHODPR(TerrainPatch, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "float get_shadowDistance() const", AS_METHODPR(TerrainPatch, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "uint GetShadowMask() const", AS_METHODPR(TerrainPatch, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "uint get_shadowMask() const", AS_METHODPR(TerrainPatch, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "float GetSortValue() const", AS_METHODPR(TerrainPatch, GetSortValue, () const, float), AS_CALL_THISCALL);
    // TerrainPatch* TerrainPatch::GetSouthPatch() const | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "TerrainPatch@+ GetSouthPatch() const", AS_METHODPR(TerrainPatch, GetSouthPatch, () const, TerrainPatch*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(TerrainPatch, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "StringHash GetType() const", AS_METHODPR(TerrainPatch, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "StringHash get_type() const", AS_METHODPR(TerrainPatch, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "const String& GetTypeName() const", AS_METHODPR(TerrainPatch, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "const String& get_typeName() const", AS_METHODPR(TerrainPatch, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // UpdateGeometryType TerrainPatch::GetUpdateGeometryType() override | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "UpdateGeometryType GetUpdateGeometryType()", AS_METHODPR(TerrainPatch, GetUpdateGeometryType, (), UpdateGeometryType), AS_CALL_THISCALL);
    // VertexBuffer* TerrainPatch::GetVertexBuffer() const | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "VertexBuffer@+ GetVertexBuffer() const", AS_METHODPR(TerrainPatch, GetVertexBuffer, () const, VertexBuffer*), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "Array<Light@>@ GetVertexLights() const", AS_FUNCTION_OBJFIRST(TerrainPatch_GetVertexLights_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "uint GetViewMask() const", AS_METHODPR(TerrainPatch, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "uint get_viewMask() const", AS_METHODPR(TerrainPatch, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    // TerrainPatch* TerrainPatch::GetWestPatch() const | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "TerrainPatch@+ GetWestPatch() const", AS_METHODPR(TerrainPatch, GetWestPatch, () const, TerrainPatch*), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "const BoundingBox& GetWorldBoundingBox()", AS_METHODPR(TerrainPatch, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "const BoundingBox& get_worldBoundingBox()", AS_METHODPR(TerrainPatch, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "Zone@+ GetZone() const", AS_METHODPR(TerrainPatch, GetZone, () const, Zone*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "Zone@+ get_zone() const", AS_METHODPR(TerrainPatch, GetZone, () const, Zone*), AS_CALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "uint GetZoneMask() const", AS_METHODPR(TerrainPatch, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "uint get_zoneMask() const", AS_METHODPR(TerrainPatch, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool HasBasePass(uint) const", AS_METHODPR(TerrainPatch, HasBasePass, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "bool HasEventHandlers() const", AS_METHODPR(TerrainPatch, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(TerrainPatch, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(TerrainPatch, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "bool IsEnabled() const", AS_METHODPR(TerrainPatch, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "bool get_enabled() const", AS_METHODPR(TerrainPatch, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "bool IsEnabledEffective() const", AS_METHODPR(TerrainPatch, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "bool get_enabledEffective() const", AS_METHODPR(TerrainPatch, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "bool IsInstanceOf(StringHash) const", AS_METHODPR(TerrainPatch, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool IsInView() const", AS_METHODPR(TerrainPatch, IsInView, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "bool get_inView() const", AS_METHODPR(TerrainPatch, IsInView, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool IsInView(Camera@+) const", AS_METHODPR(TerrainPatch, IsInView, (Camera*) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool IsInView(const FrameInfo&in, bool = false) const", AS_METHODPR(TerrainPatch, IsInView, (const FrameInfo&, bool) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool IsOccludee() const", AS_METHODPR(TerrainPatch, IsOccludee, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "bool get_occludee() const", AS_METHODPR(TerrainPatch, IsOccludee, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool IsOccluder() const", AS_METHODPR(TerrainPatch, IsOccluder, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "bool get_occluder() const", AS_METHODPR(TerrainPatch, IsOccluder, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "bool IsReplicated() const", AS_METHODPR(TerrainPatch, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "bool get_replicated() const", AS_METHODPR(TerrainPatch, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool IsTemporary() const", AS_METHODPR(TerrainPatch, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "bool get_temporary() const", AS_METHODPR(TerrainPatch, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool IsZoneDirty() const", AS_METHODPR(TerrainPatch, IsZoneDirty, () const, bool), AS_CALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void LimitLights()", AS_METHODPR(TerrainPatch, LimitLights, (), void), AS_CALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void LimitVertexLights(bool)", AS_METHODPR(TerrainPatch, LimitVertexLights, (bool), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool Load(Deserializer&)", AS_METHODPR(TerrainPatch, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(TerrainPatch, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool LoadXML(const XMLElement&in)", AS_METHODPR(TerrainPatch, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void MarkForUpdate()", AS_METHODPR(TerrainPatch, MarkForUpdate, (), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void MarkInView(const FrameInfo&in)", AS_METHODPR(TerrainPatch, MarkInView, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void MarkInView(uint)", AS_METHODPR(TerrainPatch, MarkInView, (unsigned), void), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "void MarkNetworkUpdate()", AS_METHODPR(TerrainPatch, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(TerrainPatch, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(TerrainPatch, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(TerrainPatch, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Drawable::OnSetEnabled() override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void OnSetEnabled()", AS_METHODPR(TerrainPatch, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "void PrepareNetworkUpdate()", AS_METHODPR(TerrainPatch, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void TerrainPatch::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override | File: ../Graphics/TerrainPatch.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(TerrainPatch, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(TerrainPatch, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TerrainPatch", "int Refs() const", AS_METHODPR(TerrainPatch, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "int get_refs() const", AS_METHODPR(TerrainPatch, Refs, () const, int), AS_CALL_THISCALL);
    // static void TerrainPatch::RegisterObject(Context* context) | File: ../Graphics/TerrainPatch.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TerrainPatch", asBEHAVE_RELEASE, "void f()", AS_METHODPR(TerrainPatch, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "void Remove()", AS_METHODPR(TerrainPatch, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(TerrainPatch, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "void RemoveInstanceDefault()", AS_METHODPR(TerrainPatch, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "void RemoveObjectAnimation()", AS_METHODPR(TerrainPatch, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void TerrainPatch::ResetLod() | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "void ResetLod()", AS_METHODPR(TerrainPatch, ResetLod, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "void ResetToDefault()", AS_METHODPR(TerrainPatch, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "bool Save(Serializer&) const", AS_METHODPR(TerrainPatch, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool SaveDefaultAttributes() const", AS_METHODPR(TerrainPatch, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "bool SaveJSON(JSONValue&) const", AS_METHODPR(TerrainPatch, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "bool SaveXML(XMLElement&) const", AS_METHODPR(TerrainPatch, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "void SendEvent(StringHash)", AS_METHODPR(TerrainPatch, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(TerrainPatch, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetAnimationEnabled(bool)", AS_METHODPR(TerrainPatch, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_animationEnabled(bool)", AS_METHODPR(TerrainPatch, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetAnimationTime(float)", AS_METHODPR(TerrainPatch, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(TerrainPatch, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(TerrainPatch, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(TerrainPatch, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(TerrainPatch, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(TerrainPatch, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(TerrainPatch, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(TerrainPatch, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetBasePass(uint)", AS_METHODPR(TerrainPatch, SetBasePass, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetBlockEvents(bool)", AS_METHODPR(TerrainPatch, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void TerrainPatch::SetBoundingBox(const BoundingBox& box) | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetBoundingBox(const BoundingBox&in)", AS_METHODPR(TerrainPatch, SetBoundingBox, (const BoundingBox&), void), AS_CALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetCastShadows(bool)", AS_METHODPR(TerrainPatch, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_castShadows(bool)", AS_METHODPR(TerrainPatch, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    // void TerrainPatch::SetCoordinates(const IntVector2& coordinates) | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetCoordinates(const IntVector2&in)", AS_METHODPR(TerrainPatch, SetCoordinates, (const IntVector2&), void), AS_CALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetDrawDistance(float)", AS_METHODPR(TerrainPatch, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_drawDistance(float)", AS_METHODPR(TerrainPatch, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetEnabled(bool)", AS_METHODPR(TerrainPatch, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_enabled(bool)", AS_METHODPR(TerrainPatch, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(TerrainPatch, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(TerrainPatch, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetInstanceDefault(bool)", AS_METHODPR(TerrainPatch, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(TerrainPatch, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetLightMask(uint)", AS_METHODPR(TerrainPatch, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_lightMask(uint)", AS_METHODPR(TerrainPatch, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetLodBias(float)", AS_METHODPR(TerrainPatch, SetLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_lodBias(float)", AS_METHODPR(TerrainPatch, SetLodBias, (float), void), AS_CALL_THISCALL);
    // void TerrainPatch::SetMaterial(Material* material) | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetMaterial(Material@+)", AS_METHODPR(TerrainPatch, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetMaxLights(uint)", AS_METHODPR(TerrainPatch, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_maxLights(uint)", AS_METHODPR(TerrainPatch, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetMinMaxZ(float, float)", AS_METHODPR(TerrainPatch, SetMinMaxZ, (float, float), void), AS_CALL_THISCALL);
    // void TerrainPatch::SetNeighbors(TerrainPatch* north, TerrainPatch* south, TerrainPatch* west, TerrainPatch* east) | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetNeighbors(TerrainPatch@+, TerrainPatch@+, TerrainPatch@+, TerrainPatch@+)", AS_METHODPR(TerrainPatch, SetNeighbors, (TerrainPatch*, TerrainPatch*, TerrainPatch*, TerrainPatch*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(TerrainPatch, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(TerrainPatch, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(TerrainPatch, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetOccludee(bool)", AS_METHODPR(TerrainPatch, SetOccludee, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_occludee(bool)", AS_METHODPR(TerrainPatch, SetOccludee, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetOccluder(bool)", AS_METHODPR(TerrainPatch, SetOccluder, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_occluder(bool)", AS_METHODPR(TerrainPatch, SetOccluder, (bool), void), AS_CALL_THISCALL);
    // void TerrainPatch::SetOwner(Terrain* terrain) | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetOwner(Terrain@+)", AS_METHODPR(TerrainPatch, SetOwner, (Terrain*), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetShadowDistance(float)", AS_METHODPR(TerrainPatch, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_shadowDistance(float)", AS_METHODPR(TerrainPatch, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetShadowMask(uint)", AS_METHODPR(TerrainPatch, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_shadowMask(uint)", AS_METHODPR(TerrainPatch, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetSortValue(float)", AS_METHODPR(TerrainPatch, SetSortValue, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetTemporary(bool)", AS_METHODPR(TerrainPatch, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_temporary(bool)", AS_METHODPR(TerrainPatch, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetViewMask(uint)", AS_METHODPR(TerrainPatch, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_viewMask(uint)", AS_METHODPR(TerrainPatch, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetZone(Zone@+, bool = false)", AS_METHODPR(TerrainPatch, SetZone, (Zone*, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void SetZoneMask(uint)", AS_METHODPR(TerrainPatch, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "void set_zoneMask(uint)", AS_METHODPR(TerrainPatch, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit TerrainPatch::TerrainPatch(Context* context) | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectBehaviour("TerrainPatch", asBEHAVE_FACTORY, "TerrainPatch@+ f()", AS_FUNCTION(TerrainPatch_TerrainPatch_Context), AS_CALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "void UnsubscribeFromAllEvents()", AS_METHODPR(TerrainPatch, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(TerrainPatch_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(TerrainPatch, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(TerrainPatch, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TerrainPatch", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(TerrainPatch, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("TerrainPatch", "void Update(const FrameInfo&in)", AS_METHODPR(TerrainPatch, Update, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void TerrainPatch::UpdateBatches(const FrameInfo& frame) override | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "void UpdateBatches(const FrameInfo&in)", AS_METHODPR(TerrainPatch, UpdateBatches, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void TerrainPatch::UpdateGeometry(const FrameInfo& frame) override | File: ../Graphics/TerrainPatch.h
    engine->RegisterObjectMethod("TerrainPatch", "void UpdateGeometry(const FrameInfo&in)", AS_METHODPR(TerrainPatch, UpdateGeometry, (const FrameInfo&), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TerrainPatch", "int WeakRefs() const", AS_METHODPR(TerrainPatch, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TerrainPatch", "int get_weakRefs() const", AS_METHODPR(TerrainPatch, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(TerrainPatch, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(TerrainPatch, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TerrainPatch", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(TerrainPatch, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Text", "void AddChild(UIElement@+)", AS_METHODPR(Text, AddChild, (UIElement*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Text", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Text, AddRef, (), void), AS_CALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void AddTag(const String&in)", AS_METHODPR(Text, AddTag, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void AddTags(const String&in, int8 = ';')", AS_METHODPR(Text, AddTags, (const String&, char), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void AddTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(Text_AddTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void AdjustScissor(IntRect&)", AS_METHODPR(Text, AdjustScissor, (IntRect&), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "void AllocateNetworkState()", AS_METHODPR(Text, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void Text::ApplyAttributes() override | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void ApplyAttributes()", AS_METHODPR(Text, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void BringToFront()", AS_METHODPR(Text, BringToFront, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Text::ClearSelection() | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void ClearSelection()", AS_METHODPR(Text, ClearSelection, (), void), AS_CALL_THISCALL);
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", AS_METHODPR(Text, CreateChild, (StringHash, const String&, unsigned), UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void DisableLayoutUpdate()", AS_METHODPR(Text, DisableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "IntVector2 ElementToScreen(const IntVector2&in)", AS_METHODPR(Text, ElementToScreen, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void EnableLayoutUpdate()", AS_METHODPR(Text, EnableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool FilterAttributes(XMLElement&) const", AS_METHODPR(Text, FilterAttributes, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "uint FindChild(UIElement@+) const", AS_METHODPR(Text, FindChild, (UIElement*) const, unsigned), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "bool GetAnimationEnabled() const", AS_METHODPR(Text, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_animationEnabled() const", AS_METHODPR(Text, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const String& GetAppliedStyle() const", AS_METHODPR(Text, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const String& get_style() const", AS_METHODPR(Text, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "Variant GetAttribute(uint) const", AS_METHODPR(Text, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "Variant get_attributes(uint) const", AS_METHODPR(Text, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "Variant GetAttribute(const String&in) const", AS_METHODPR(Text, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(Text, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(Text, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(Text, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(Text, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Text, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Text, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Text, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Text::GetAutoLocalizable() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "bool GetAutoLocalizable() const", AS_METHODPR(Text, GetAutoLocalizable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_autoLocalizable() const", AS_METHODPR(Text, GetAutoLocalizable, () const, bool), AS_CALL_THISCALL);
    // void Text::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/Text.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "bool GetBlockEvents() const", AS_METHODPR(Text, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool GetBringToBack() const", AS_METHODPR(Text, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_bringToBack() const", AS_METHODPR(Text, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool GetBringToFront() const", AS_METHODPR(Text, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_bringToFront() const", AS_METHODPR(Text, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "const String& GetCategory() const", AS_METHODPR(Text, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const String& get_category() const", AS_METHODPR(Text, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Vector2 Text::GetCharPosition(unsigned index) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "Vector2 GetCharPosition(uint)", AS_METHODPR(Text, GetCharPosition, (unsigned), Vector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "Vector2 get_charPositions(uint)", AS_METHODPR(Text, GetCharPosition, (unsigned), Vector2), AS_CALL_THISCALL);
    // Vector2 Text::GetCharSize(unsigned index) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "Vector2 GetCharSize(uint)", AS_METHODPR(Text, GetCharSize, (unsigned), Vector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "Vector2 get_charSizes(uint)", AS_METHODPR(Text, GetCharSize, (unsigned), Vector2), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "UIElement@+ GetChild(uint) const", AS_METHODPR(Text, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "UIElement@+ get_children(uint) const", AS_METHODPR(Text, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "UIElement@+ GetChild(const String&in, bool = false) const", AS_METHODPR(Text, GetChild, (const String&, bool) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", AS_METHODPR(Text, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const IntVector2& GetChildOffset() const", AS_METHODPR(Text, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const IntVector2& get_childOffset() const", AS_METHODPR(Text, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "Array<UIElement@>@ GetChildren() const", AS_FUNCTION_OBJFIRST(Text_GetChildren_void), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "Array<UIElement@>@ GetChildren(bool) const", AS_FUNCTION_OBJFIRST(Text_GetChildren_bool), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", AS_FUNCTION_OBJFIRST(Text_GetChildrenWithTag_String_bool), AS_CALL_CDECL_OBJFIRST);
    // template<class T> T* UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const IntRect& GetClipBorder() const", AS_METHODPR(Text, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const IntRect& get_clipBorder() const", AS_METHODPR(Text, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool GetClipChildren() const", AS_METHODPR(Text, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_clipChildren() const", AS_METHODPR(Text, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const Color& GetColor(Corner) const", AS_METHODPR(Text, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const Color& get_colors(Corner) const", AS_METHODPR(Text, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const Color& GetColorAttr() const", AS_METHODPR(Text, GetColorAttr, () const, const Color&), AS_CALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "IntRect GetCombinedScreenRect()", AS_METHODPR(Text, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "IntRect get_combinedScreenRect()", AS_METHODPR(Text, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "XMLFile@+ GetDefaultStyle(bool = true) const", AS_METHODPR(Text, GetDefaultStyle, (bool) const, XMLFile*), AS_CALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const Color& GetDerivedColor() const", AS_METHODPR(Text, GetDerivedColor, () const, const Color&), AS_CALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "float GetDerivedOpacity() const", AS_METHODPR(Text, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "float get_derivedOpacity() const", AS_METHODPR(Text, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "MouseButtonFlags GetDragButtonCombo() const", AS_METHODPR(Text, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "MouseButtonFlags get_dragButtonCombo() const", AS_METHODPR(Text, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "uint GetDragButtonCount() const", AS_METHODPR(Text, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "uint get_dragButtonCount() const", AS_METHODPR(Text, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "DragAndDropModeFlags GetDragDropMode() const", AS_METHODPR(Text, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "DragAndDropModeFlags get_dragDropMode() const", AS_METHODPR(Text, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    // const Color& Text::GetEffectColor() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "const Color& GetEffectColor() const", AS_METHODPR(Text, GetEffectColor, () const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const Color& get_effectColor() const", AS_METHODPR(Text, GetEffectColor, () const, const Color&), AS_CALL_THISCALL);
    // float Text::GetEffectDepthBias() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "float GetEffectDepthBias() const", AS_METHODPR(Text, GetEffectDepthBias, () const, float), AS_CALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "IntVector2 GetEffectiveMinSize() const", AS_METHODPR(Text, GetEffectiveMinSize, () const, IntVector2), AS_CALL_THISCALL);
    // bool Text::GetEffectRoundStroke() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "bool GetEffectRoundStroke() const", AS_METHODPR(Text, GetEffectRoundStroke, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_effectRoundStroke() const", AS_METHODPR(Text, GetEffectRoundStroke, () const, bool), AS_CALL_THISCALL);
    // const IntVector2& Text::GetEffectShadowOffset() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "const IntVector2& GetEffectShadowOffset() const", AS_METHODPR(Text, GetEffectShadowOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const IntVector2& get_effectShadowOffset() const", AS_METHODPR(Text, GetEffectShadowOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // int Text::GetEffectStrokeThickness() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "int GetEffectStrokeThickness() const", AS_METHODPR(Text, GetEffectStrokeThickness, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_effectStrokeThickness() const", AS_METHODPR(Text, GetEffectStrokeThickness, () const, int), AS_CALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "UIElement@+ GetElementEventSender() const", AS_METHODPR(Text, GetElementEventSender, () const, UIElement*), AS_CALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool GetEnableAnchor() const", AS_METHODPR(Text, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_enableAnchor() const", AS_METHODPR(Text, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "VariantMap& GetEventDataMap() const", AS_METHODPR(Text, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "Object@+ GetEventSender() const", AS_METHODPR(Text, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "FocusMode GetFocusMode() const", AS_METHODPR(Text, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "FocusMode get_focusMode() const", AS_METHODPR(Text, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    // Font* Text::GetFont() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "Font@+ GetFont() const", AS_METHODPR(Text, GetFont, () const, Font*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "Font@+ get_font() const", AS_METHODPR(Text, GetFont, () const, Font*), AS_CALL_THISCALL);
    // ResourceRef Text::GetFontAttr() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "ResourceRef GetFontAttr() const", AS_METHODPR(Text, GetFontAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float Text::GetFontSize() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "float GetFontSize() const", AS_METHODPR(Text, GetFontSize, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "float get_fontSize() const", AS_METHODPR(Text, GetFontSize, () const, float), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Text, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Text, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Text, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const VariantMap& get_globalVars() const", AS_METHODPR(Text, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "int GetHeight() const", AS_METHODPR(Text, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_height() const", AS_METHODPR(Text, GetHeight, () const, int), AS_CALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "HorizontalAlignment GetHorizontalAlignment() const", AS_METHODPR(Text, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "HorizontalAlignment get_horizontalAlignment() const", AS_METHODPR(Text, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    // const Color& UISelectable::GetHoverColor() const | File: ../UI/UISelectable.h
    engine->RegisterObjectMethod("Text", "const Color& GetHoverColor() const", AS_METHODPR(Text, GetHoverColor, () const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const Color& get_hoverColor() const", AS_METHODPR(Text, GetHoverColor, () const, const Color&), AS_CALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "int GetIndent() const", AS_METHODPR(Text, GetIndent, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_indent() const", AS_METHODPR(Text, GetIndent, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "int GetIndentSpacing() const", AS_METHODPR(Text, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_indentSpacing() const", AS_METHODPR(Text, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "int GetIndentWidth() const", AS_METHODPR(Text, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_indentWidth() const", AS_METHODPR(Text, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Text, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const IntRect& GetLayoutBorder() const", AS_METHODPR(Text, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const IntRect& get_layoutBorder() const", AS_METHODPR(Text, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "int GetLayoutElementMaxSize() const", AS_METHODPR(Text, GetLayoutElementMaxSize, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const Vector2& GetLayoutFlexScale() const", AS_METHODPR(Text, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const Vector2& get_layoutFlexScale() const", AS_METHODPR(Text, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "LayoutMode GetLayoutMode() const", AS_METHODPR(Text, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "LayoutMode get_layoutMode() const", AS_METHODPR(Text, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "int GetLayoutSpacing() const", AS_METHODPR(Text, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_layoutSpacing() const", AS_METHODPR(Text, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const Vector2& GetMaxAnchor() const", AS_METHODPR(Text, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const Vector2& get_maxAnchor() const", AS_METHODPR(Text, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "int GetMaxHeight() const", AS_METHODPR(Text, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_maxHeight() const", AS_METHODPR(Text, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const IntVector2& GetMaxOffset() const", AS_METHODPR(Text, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const IntVector2& get_maxOffset() const", AS_METHODPR(Text, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const IntVector2& GetMaxSize() const", AS_METHODPR(Text, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const IntVector2& get_maxSize() const", AS_METHODPR(Text, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "int GetMaxWidth() const", AS_METHODPR(Text, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_maxWidth() const", AS_METHODPR(Text, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const Vector2& GetMinAnchor() const", AS_METHODPR(Text, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const Vector2& get_minAnchor() const", AS_METHODPR(Text, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "int GetMinHeight() const", AS_METHODPR(Text, GetMinHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_minHeight() const", AS_METHODPR(Text, GetMinHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const IntVector2& GetMinOffset() const", AS_METHODPR(Text, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const IntVector2& get_minOffset() const", AS_METHODPR(Text, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const IntVector2& GetMinSize() const", AS_METHODPR(Text, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const IntVector2& get_minSize() const", AS_METHODPR(Text, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "int GetMinWidth() const", AS_METHODPR(Text, GetMinWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_minWidth() const", AS_METHODPR(Text, GetMinWidth, () const, int), AS_CALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const String& GetName() const", AS_METHODPR(Text, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const String& get_name() const", AS_METHODPR(Text, GetName, () const, const String&), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "uint GetNumAttributes() const", AS_METHODPR(Text, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "uint get_numAttributes() const", AS_METHODPR(Text, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Text::GetNumChars() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "uint GetNumChars() const", AS_METHODPR(Text, GetNumChars, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "uint get_numChars() const", AS_METHODPR(Text, GetNumChars, () const, unsigned), AS_CALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "uint GetNumChildren(bool = false) const", AS_METHODPR(Text, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "uint get_numChildren(bool = false) const", AS_METHODPR(Text, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "uint GetNumNetworkAttributes() const", AS_METHODPR(Text, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Text::GetNumRows() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "uint GetNumRows() const", AS_METHODPR(Text, GetNumRows, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "uint get_numRows() const", AS_METHODPR(Text, GetNumRows, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(Text, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(Text, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(Text, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "float GetOpacity() const", AS_METHODPR(Text, GetOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "float get_opacity() const", AS_METHODPR(Text, GetOpacity, () const, float), AS_CALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "UIElement@+ GetParent() const", AS_METHODPR(Text, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "UIElement@+ get_parent() const", AS_METHODPR(Text, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const Vector2& GetPivot() const", AS_METHODPR(Text, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const Vector2& get_pivot() const", AS_METHODPR(Text, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const IntVector2& GetPosition() const", AS_METHODPR(Text, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const IntVector2& get_position() const", AS_METHODPR(Text, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "int GetPriority() const", AS_METHODPR(Text, GetPriority, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_priority() const", AS_METHODPR(Text, GetPriority, () const, int), AS_CALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "UIElement@+ GetRoot() const", AS_METHODPR(Text, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "UIElement@+ get_root() const", AS_METHODPR(Text, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    // float Text::GetRowHeight() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "float GetRowHeight() const", AS_METHODPR(Text, GetRowHeight, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "float get_rowHeight() const", AS_METHODPR(Text, GetRowHeight, () const, float), AS_CALL_THISCALL);
    // float Text::GetRowSpacing() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "float GetRowSpacing() const", AS_METHODPR(Text, GetRowSpacing, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "float get_rowSpacing() const", AS_METHODPR(Text, GetRowSpacing, () const, float), AS_CALL_THISCALL);
    // float Text::GetRowWidth(unsigned index) const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "float GetRowWidth(uint) const", AS_METHODPR(Text, GetRowWidth, (unsigned) const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "float get_rowWidths(uint) const", AS_METHODPR(Text, GetRowWidth, (unsigned) const, float), AS_CALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const IntVector2& GetScreenPosition() const", AS_METHODPR(Text, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const IntVector2& get_screenPosition() const", AS_METHODPR(Text, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // const Color& UISelectable::GetSelectionColor() const | File: ../UI/UISelectable.h
    engine->RegisterObjectMethod("Text", "const Color& GetSelectionColor() const", AS_METHODPR(Text, GetSelectionColor, () const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const Color& get_selectionColor() const", AS_METHODPR(Text, GetSelectionColor, () const, const Color&), AS_CALL_THISCALL);
    // unsigned Text::GetSelectionLength() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "uint GetSelectionLength() const", AS_METHODPR(Text, GetSelectionLength, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "uint get_selectionLength() const", AS_METHODPR(Text, GetSelectionLength, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Text::GetSelectionStart() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "uint GetSelectionStart() const", AS_METHODPR(Text, GetSelectionStart, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "uint get_selectionStart() const", AS_METHODPR(Text, GetSelectionStart, () const, unsigned), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const IntVector2& GetSize() const", AS_METHODPR(Text, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const IntVector2& get_size() const", AS_METHODPR(Text, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool GetSortChildren() const", AS_METHODPR(Text, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_sortChildren() const", AS_METHODPR(Text, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Text, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "Array<String>@ GetTags() const", AS_FUNCTION_OBJFIRST(Text_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Text", "Array<String>@ get_tags() const", AS_FUNCTION_OBJFIRST(Text_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    // const String& Text::GetText() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "const String& GetText() const", AS_METHODPR(Text, GetText, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const String& get_text() const", AS_METHODPR(Text, GetText, () const, const String&), AS_CALL_THISCALL);
    // HorizontalAlignment Text::GetTextAlignment() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "HorizontalAlignment GetTextAlignment() const", AS_METHODPR(Text, GetTextAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "HorizontalAlignment get_textAlignment() const", AS_METHODPR(Text, GetTextAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    // String Text::GetTextAttr() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "String GetTextAttr() const", AS_METHODPR(Text, GetTextAttr, () const, String), AS_CALL_THISCALL);
    // TextEffect Text::GetTextEffect() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "TextEffect GetTextEffect() const", AS_METHODPR(Text, GetTextEffect, () const, TextEffect), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "TextEffect get_textEffect() const", AS_METHODPR(Text, GetTextEffect, () const, TextEffect), AS_CALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "TraversalMode GetTraversalMode() const", AS_METHODPR(Text, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "TraversalMode get_traversalMode() const", AS_METHODPR(Text, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "StringHash GetType() const", AS_METHODPR(Text, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "StringHash get_type() const", AS_METHODPR(Text, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "const String& GetTypeName() const", AS_METHODPR(Text, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "const String& get_typeName() const", AS_METHODPR(Text, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool GetUseDerivedOpacity() const", AS_METHODPR(Text, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_useDerivedOpacity() const", AS_METHODPR(Text, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const Variant& GetVar(const StringHash&in) const", AS_METHODPR(Text, GetVar, (const StringHash&) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "const VariantMap& GetVars() const", AS_METHODPR(Text, GetVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "VerticalAlignment GetVerticalAlignment() const", AS_METHODPR(Text, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "VerticalAlignment get_verticalAlignment() const", AS_METHODPR(Text, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "int GetWidth() const", AS_METHODPR(Text, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_width() const", AS_METHODPR(Text, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool Text::GetWordwrap() const | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "bool GetWordwrap() const", AS_METHODPR(Text, GetWordwrap, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_wordwrap() const", AS_METHODPR(Text, GetWordwrap, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool HasColorGradient() const", AS_METHODPR(Text, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_colorGradient() const", AS_METHODPR(Text, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "bool HasEventHandlers() const", AS_METHODPR(Text, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool HasFocus() const", AS_METHODPR(Text, HasFocus, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_focus() const", AS_METHODPR(Text, HasFocus, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Text, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Text, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool HasTag(const String&in) const", AS_METHODPR(Text, HasTag, (const String&) const, bool), AS_CALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void InsertChild(uint, UIElement@+)", AS_METHODPR(Text, InsertChild, (unsigned, UIElement*), void), AS_CALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsChildOf(UIElement@+) const", AS_METHODPR(Text, IsChildOf, (UIElement*) const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsEditable() const", AS_METHODPR(Text, IsEditable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_editable() const", AS_METHODPR(Text, IsEditable, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsElementEventSender() const", AS_METHODPR(Text, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_elementEventSender() const", AS_METHODPR(Text, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsEnabled() const", AS_METHODPR(Text, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_enabled() const", AS_METHODPR(Text, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsEnabledSelf() const", AS_METHODPR(Text, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_enabledSelf() const", AS_METHODPR(Text, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsFixedHeight() const", AS_METHODPR(Text, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_fixedHeight() const", AS_METHODPR(Text, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsFixedSize() const", AS_METHODPR(Text, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_fixedSize() const", AS_METHODPR(Text, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsFixedWidth() const", AS_METHODPR(Text, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_fixedWidth() const", AS_METHODPR(Text, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsHovering() const", AS_METHODPR(Text, IsHovering, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_hovering() const", AS_METHODPR(Text, IsHovering, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsInside(IntVector2, bool)", AS_METHODPR(Text, IsInside, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsInsideCombined(IntVector2, bool)", AS_METHODPR(Text, IsInsideCombined, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Text, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsInternal() const", AS_METHODPR(Text, IsInternal, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_internal() const", AS_METHODPR(Text, IsInternal, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsSelected() const", AS_METHODPR(Text, IsSelected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_selected() const", AS_METHODPR(Text, IsSelected, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "bool IsTemporary() const", AS_METHODPR(Text, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_temporary() const", AS_METHODPR(Text, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsVisible() const", AS_METHODPR(Text, IsVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_visible() const", AS_METHODPR(Text, IsVisible, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsVisibleEffective() const", AS_METHODPR(Text, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool get_visibleEffective() const", AS_METHODPR(Text, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsWheelHandler() const", AS_METHODPR(Text, IsWheelHandler, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool IsWithinScissor(const IntRect&in)", AS_METHODPR(Text, IsWithinScissor, (const IntRect&), bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "bool Load(Deserializer&)", AS_METHODPR(Text, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(Text, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Text, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Text, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool LoadXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(Text, LoadXML, (const XMLElement&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool LoadXML(Deserializer&)", AS_METHODPR(Text, LoadXML, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "void MarkNetworkUpdate()", AS_METHODPR(Text, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Text, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", AS_METHODPR(Text, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Text, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Text, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(Text, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool OnDragDropFinish(UIElement@+)", AS_METHODPR(Text, OnDragDropFinish, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool OnDragDropTest(UIElement@+)", AS_METHODPR(Text, OnDragDropTest, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(Text, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Text, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Text, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Text, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Text, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // void Text::OnIndentSet() override | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void OnIndentSet()", AS_METHODPR(Text, OnIndentSet, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", AS_METHODPR(Text, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnPositionSet(const IntVector2&in)", AS_METHODPR(Text, OnPositionSet, (const IntVector2&), void), AS_CALL_THISCALL);
    // void Text::OnResize(const IntVector2& newSize, const IntVector2& delta) override | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void OnResize(const IntVector2&in, const IntVector2&in)", AS_METHODPR(Text, OnResize, (const IntVector2&, const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Text, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnSetEditable()", AS_METHODPR(Text, OnSetEditable, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnTextInput(const String&in)", AS_METHODPR(Text, OnTextInput, (const String&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", AS_METHODPR(Text, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Text, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Text, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Text", "int Refs() const", AS_METHODPR(Text, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_refs() const", AS_METHODPR(Text, Refs, () const, int), AS_CALL_THISCALL);
    // static void Text::RegisterObject(Context* context) | File: ../UI/Text.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Text", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Text, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void Remove()", AS_METHODPR(Text, Remove, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void RemoveAllChildren()", AS_METHODPR(Text, RemoveAllChildren, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void RemoveAllTags()", AS_METHODPR(Text, RemoveAllTags, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(Text, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void RemoveChild(UIElement@+, uint = 0)", AS_METHODPR(Text, RemoveChild, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void RemoveChildAtIndex(uint)", AS_METHODPR(Text, RemoveChildAtIndex, (unsigned), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "void RemoveInstanceDefault()", AS_METHODPR(Text, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "void RemoveObjectAnimation()", AS_METHODPR(Text, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool RemoveTag(const String&in)", AS_METHODPR(Text, RemoveTag, (const String&), bool), AS_CALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void ResetDeepEnabled()", AS_METHODPR(Text, ResetDeepEnabled, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "void ResetToDefault()", AS_METHODPR(Text, ResetToDefault, (), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "bool Save(Serializer&) const", AS_METHODPR(Text, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "bool SaveDefaultAttributes() const", AS_METHODPR(Text, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "bool SaveJSON(JSONValue&) const", AS_METHODPR(Text, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool SaveXML(XMLElement&) const", AS_METHODPR(Text, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool SaveXML(Serializer&, const String&in = \"\t\") const", AS_METHODPR(Text, SaveXML, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "IntVector2 ScreenToElement(const IntVector2&in)", AS_METHODPR(Text, ScreenToElement, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "void SendEvent(StringHash)", AS_METHODPR(Text, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Text, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", AS_METHODPR(Text, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "void SetAnimationEnabled(bool)", AS_METHODPR(Text, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_animationEnabled(bool)", AS_METHODPR(Text, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "void SetAnimationTime(float)", AS_METHODPR(Text, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Text, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Text, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Text, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Text, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(Text, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(Text, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Text, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Text::SetAutoLocalizable(bool enable) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetAutoLocalizable(bool)", AS_METHODPR(Text, SetAutoLocalizable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_autoLocalizable(bool)", AS_METHODPR(Text, SetAutoLocalizable, (bool), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "void SetBlockEvents(bool)", AS_METHODPR(Text, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetBringToBack(bool)", AS_METHODPR(Text, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_bringToBack(bool)", AS_METHODPR(Text, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetBringToFront(bool)", AS_METHODPR(Text, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_bringToFront(bool)", AS_METHODPR(Text, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetChildOffset(const IntVector2&in)", AS_METHODPR(Text, SetChildOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetClipBorder(const IntRect&in)", AS_METHODPR(Text, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_clipBorder(const IntRect&in)", AS_METHODPR(Text, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetClipChildren(bool)", AS_METHODPR(Text, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_clipChildren(bool)", AS_METHODPR(Text, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetColor(const Color&in)", AS_METHODPR(Text, SetColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_color(const Color&in)", AS_METHODPR(Text, SetColor, (const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetColor(Corner, const Color&in)", AS_METHODPR(Text, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_colors(Corner, const Color&in)", AS_METHODPR(Text, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetDeepEnabled(bool)", AS_METHODPR(Text, SetDeepEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetDefaultStyle(XMLFile@+)", AS_METHODPR(Text, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_defaultStyle(XMLFile@+)", AS_METHODPR(Text, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetDragDropMode(DragAndDropModeFlags)", AS_METHODPR(Text, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_dragDropMode(DragAndDropModeFlags)", AS_METHODPR(Text, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetEditable(bool)", AS_METHODPR(Text, SetEditable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_editable(bool)", AS_METHODPR(Text, SetEditable, (bool), void), AS_CALL_THISCALL);
    // void Text::SetEffectColor(const Color& effectColor) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetEffectColor(const Color&in)", AS_METHODPR(Text, SetEffectColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_effectColor(const Color&in)", AS_METHODPR(Text, SetEffectColor, (const Color&), void), AS_CALL_THISCALL);
    // void Text::SetEffectDepthBias(float bias) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetEffectDepthBias(float)", AS_METHODPR(Text, SetEffectDepthBias, (float), void), AS_CALL_THISCALL);
    // void Text::SetEffectRoundStroke(bool roundStroke) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetEffectRoundStroke(bool)", AS_METHODPR(Text, SetEffectRoundStroke, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_effectRoundStroke(bool)", AS_METHODPR(Text, SetEffectRoundStroke, (bool), void), AS_CALL_THISCALL);
    // void Text::SetEffectShadowOffset(const IntVector2& offset) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetEffectShadowOffset(const IntVector2&in)", AS_METHODPR(Text, SetEffectShadowOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_effectShadowOffset(const IntVector2&in)", AS_METHODPR(Text, SetEffectShadowOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void Text::SetEffectStrokeThickness(int thickness) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetEffectStrokeThickness(int)", AS_METHODPR(Text, SetEffectStrokeThickness, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_effectStrokeThickness(int)", AS_METHODPR(Text, SetEffectStrokeThickness, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetElementEventSender(bool)", AS_METHODPR(Text, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_elementEventSender(bool)", AS_METHODPR(Text, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetEnableAnchor(bool)", AS_METHODPR(Text, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_enableAnchor(bool)", AS_METHODPR(Text, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetEnabled(bool)", AS_METHODPR(Text, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_enabled(bool)", AS_METHODPR(Text, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetEnabledRecursive(bool)", AS_METHODPR(Text, SetEnabledRecursive, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetFixedHeight(int)", AS_METHODPR(Text, SetFixedHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetFixedSize(const IntVector2&in)", AS_METHODPR(Text, SetFixedSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetFixedSize(int, int)", AS_METHODPR(Text, SetFixedSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetFixedWidth(int)", AS_METHODPR(Text, SetFixedWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetFocus(bool)", AS_METHODPR(Text, SetFocus, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_focus(bool)", AS_METHODPR(Text, SetFocus, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetFocusMode(FocusMode)", AS_METHODPR(Text, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_focusMode(FocusMode)", AS_METHODPR(Text, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    // bool Text::SetFont(const String& fontName, float size=DEFAULT_FONT_SIZE) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "bool SetFont(const String&in, float = DEFAULT_FONT_SIZE)", AS_METHODPR(Text, SetFont, (const String&, float), bool), AS_CALL_THISCALL);
    // bool Text::SetFont(Font* font, float size=DEFAULT_FONT_SIZE) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "bool SetFont(Font@+, float = DEFAULT_FONT_SIZE)", AS_METHODPR(Text, SetFont, (Font*, float), bool), AS_CALL_THISCALL);
    // void Text::SetFontAttr(const ResourceRef& value) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetFontAttr(const ResourceRef&in)", AS_METHODPR(Text, SetFontAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // bool Text::SetFontSize(float size) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "bool SetFontSize(float)", AS_METHODPR(Text, SetFontSize, (float), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "bool set_fontSize(float)", AS_METHODPR(Text, SetFontSize, (float), bool), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Text, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Text, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetHeight(int)", AS_METHODPR(Text, SetHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_height(int)", AS_METHODPR(Text, SetHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetHorizontalAlignment(HorizontalAlignment)", AS_METHODPR(Text, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_horizontalAlignment(HorizontalAlignment)", AS_METHODPR(Text, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    // void UISelectable::SetHoverColor(const Color& color) | File: ../UI/UISelectable.h
    engine->RegisterObjectMethod("Text", "void SetHoverColor(const Color&in)", AS_METHODPR(Text, SetHoverColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_hoverColor(const Color&in)", AS_METHODPR(Text, SetHoverColor, (const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetHovering(bool)", AS_METHODPR(Text, SetHovering, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetIndent(int)", AS_METHODPR(Text, SetIndent, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_indent(int)", AS_METHODPR(Text, SetIndent, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetIndentSpacing(int)", AS_METHODPR(Text, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_indentSpacing(int)", AS_METHODPR(Text, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "void SetInstanceDefault(bool)", AS_METHODPR(Text, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Text, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetInternal(bool)", AS_METHODPR(Text, SetInternal, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_internal(bool)", AS_METHODPR(Text, SetInternal, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", AS_METHODPR(Text, SetLayout, (LayoutMode, int, const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetLayoutBorder(const IntRect&in)", AS_METHODPR(Text, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_layoutBorder(const IntRect&in)", AS_METHODPR(Text, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetLayoutFlexScale(const Vector2&in)", AS_METHODPR(Text, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_layoutFlexScale(const Vector2&in)", AS_METHODPR(Text, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetLayoutMode(LayoutMode)", AS_METHODPR(Text, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_layoutMode(LayoutMode)", AS_METHODPR(Text, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetLayoutSpacing(int)", AS_METHODPR(Text, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_layoutSpacing(int)", AS_METHODPR(Text, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMaxAnchor(const Vector2&in)", AS_METHODPR(Text, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_maxAnchor(const Vector2&in)", AS_METHODPR(Text, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMaxAnchor(float, float)", AS_METHODPR(Text, SetMaxAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMaxHeight(int)", AS_METHODPR(Text, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_maxHeight(int)", AS_METHODPR(Text, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMaxOffset(const IntVector2&in)", AS_METHODPR(Text, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_maxOffset(const IntVector2&in)", AS_METHODPR(Text, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMaxSize(const IntVector2&in)", AS_METHODPR(Text, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_maxSize(const IntVector2&in)", AS_METHODPR(Text, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMaxSize(int, int)", AS_METHODPR(Text, SetMaxSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMaxWidth(int)", AS_METHODPR(Text, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_maxWidth(int)", AS_METHODPR(Text, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMinAnchor(const Vector2&in)", AS_METHODPR(Text, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_minAnchor(const Vector2&in)", AS_METHODPR(Text, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMinAnchor(float, float)", AS_METHODPR(Text, SetMinAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMinHeight(int)", AS_METHODPR(Text, SetMinHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_minHeight(int)", AS_METHODPR(Text, SetMinHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMinOffset(const IntVector2&in)", AS_METHODPR(Text, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_minOffset(const IntVector2&in)", AS_METHODPR(Text, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMinSize(const IntVector2&in)", AS_METHODPR(Text, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_minSize(const IntVector2&in)", AS_METHODPR(Text, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMinSize(int, int)", AS_METHODPR(Text, SetMinSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetMinWidth(int)", AS_METHODPR(Text, SetMinWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_minWidth(int)", AS_METHODPR(Text, SetMinWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetName(const String&in)", AS_METHODPR(Text, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_name(const String&in)", AS_METHODPR(Text, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(Text, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(Text, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(Text, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetOpacity(float)", AS_METHODPR(Text, SetOpacity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_opacity(float)", AS_METHODPR(Text, SetOpacity, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", AS_METHODPR(Text, SetParent, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetPivot(const Vector2&in)", AS_METHODPR(Text, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_pivot(const Vector2&in)", AS_METHODPR(Text, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetPivot(float, float)", AS_METHODPR(Text, SetPivot, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetPosition(const IntVector2&in)", AS_METHODPR(Text, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_position(const IntVector2&in)", AS_METHODPR(Text, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetPosition(int, int)", AS_METHODPR(Text, SetPosition, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetPriority(int)", AS_METHODPR(Text, SetPriority, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_priority(int)", AS_METHODPR(Text, SetPriority, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetRenderTexture(Texture2D@+)", AS_METHODPR(Text, SetRenderTexture, (Texture2D*), void), AS_CALL_THISCALL);
    // void Text::SetRowSpacing(float spacing) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetRowSpacing(float)", AS_METHODPR(Text, SetRowSpacing, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_rowSpacing(float)", AS_METHODPR(Text, SetRowSpacing, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetSelected(bool)", AS_METHODPR(Text, SetSelected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_selected(bool)", AS_METHODPR(Text, SetSelected, (bool), void), AS_CALL_THISCALL);
    // void Text::SetSelection(unsigned start, unsigned length=M_MAX_UNSIGNED) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetSelection(uint, uint = M_MAX_UNSIGNED)", AS_METHODPR(Text, SetSelection, (unsigned, unsigned), void), AS_CALL_THISCALL);
    // void UISelectable::SetSelectionColor(const Color& color) | File: ../UI/UISelectable.h
    engine->RegisterObjectMethod("Text", "void SetSelectionColor(const Color&in)", AS_METHODPR(Text, SetSelectionColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_selectionColor(const Color&in)", AS_METHODPR(Text, SetSelectionColor, (const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetSize(const IntVector2&in)", AS_METHODPR(Text, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_size(const IntVector2&in)", AS_METHODPR(Text, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetSize(int, int)", AS_METHODPR(Text, SetSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetSortChildren(bool)", AS_METHODPR(Text, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_sortChildren(bool)", AS_METHODPR(Text, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool SetStyle(const String&in, XMLFile@+ = null)", AS_METHODPR(Text, SetStyle, (const String&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool SetStyle(const XMLElement&in)", AS_METHODPR(Text, SetStyle, (const XMLElement&), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "bool SetStyleAuto(XMLFile@+ = null)", AS_METHODPR(Text, SetStyleAuto, (XMLFile*), bool), AS_CALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(Text_SetTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "void SetTemporary(bool)", AS_METHODPR(Text, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_temporary(bool)", AS_METHODPR(Text, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Text::SetText(const String& text) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetText(const String&in)", AS_METHODPR(Text, SetText, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_text(const String&in)", AS_METHODPR(Text, SetText, (const String&), void), AS_CALL_THISCALL);
    // void Text::SetTextAlignment(HorizontalAlignment align) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetTextAlignment(HorizontalAlignment)", AS_METHODPR(Text, SetTextAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_textAlignment(HorizontalAlignment)", AS_METHODPR(Text, SetTextAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    // void Text::SetTextAttr(const String& value) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetTextAttr(const String&in)", AS_METHODPR(Text, SetTextAttr, (const String&), void), AS_CALL_THISCALL);
    // void Text::SetTextEffect(TextEffect textEffect) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetTextEffect(TextEffect)", AS_METHODPR(Text, SetTextEffect, (TextEffect), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_textEffect(TextEffect)", AS_METHODPR(Text, SetTextEffect, (TextEffect), void), AS_CALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetTraversalMode(TraversalMode)", AS_METHODPR(Text, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_traversalMode(TraversalMode)", AS_METHODPR(Text, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetUseDerivedOpacity(bool)", AS_METHODPR(Text, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_useDerivedOpacity(bool)", AS_METHODPR(Text, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetVar(StringHash, const Variant&in)", AS_METHODPR(Text, SetVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetVerticalAlignment(VerticalAlignment)", AS_METHODPR(Text, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_verticalAlignment(VerticalAlignment)", AS_METHODPR(Text, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetVisible(bool)", AS_METHODPR(Text, SetVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_visible(bool)", AS_METHODPR(Text, SetVisible, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SetWidth(int)", AS_METHODPR(Text, SetWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_width(int)", AS_METHODPR(Text, SetWidth, (int), void), AS_CALL_THISCALL);
    // void Text::SetWordwrap(bool enable) | File: ../UI/Text.h
    engine->RegisterObjectMethod("Text", "void SetWordwrap(bool)", AS_METHODPR(Text, SetWordwrap, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "void set_wordwrap(bool)", AS_METHODPR(Text, SetWordwrap, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void SortChildren()", AS_METHODPR(Text, SortChildren, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit Text::Text(Context* context) | File: ../UI/Text.h
    engine->RegisterObjectBehaviour("Text", asBEHAVE_FACTORY, "Text@+ f()", AS_FUNCTION(Text_Text_Context), AS_CALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "void UnsubscribeFromAllEvents()", AS_METHODPR(Text, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Text_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Text, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Text, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Text, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void UIElement::Update(float timeStep) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void Update(float)", AS_METHODPR(Text, Update, (float), void), AS_CALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Text", "void UpdateLayout()", AS_METHODPR(Text, UpdateLayout, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Text", "int WeakRefs() const", AS_METHODPR(Text, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text", "int get_weakRefs() const", AS_METHODPR(Text, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Text, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Text, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Text, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Text3D", "void AddLight(Light@+)", AS_METHODPR(Text3D, AddLight, (Light*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Text3D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Text3D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void AddVertexLight(Light@+)", AS_METHODPR(Text3D, AddVertexLight, (Light*), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "void AllocateNetworkState()", AS_METHODPR(Text3D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void Text3D::ApplyAttributes() override | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void ApplyAttributes()", AS_METHODPR(Text3D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(Text3D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "bool DrawOcclusion(OcclusionBuffer@+)", AS_METHODPR(Text3D, DrawOcclusion, (OcclusionBuffer*), bool), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "bool GetAnimationEnabled() const", AS_METHODPR(Text3D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool get_animationEnabled() const", AS_METHODPR(Text3D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "Variant GetAttribute(uint) const", AS_METHODPR(Text3D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "Variant get_attributes(uint) const", AS_METHODPR(Text3D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "Variant GetAttribute(const String&in) const", AS_METHODPR(Text3D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(Text3D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(Text3D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(Text3D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(Text3D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Text3D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Text3D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Text3D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "bool GetBlockEvents() const", AS_METHODPR(Text3D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "const BoundingBox& GetBoundingBox() const", AS_METHODPR(Text3D, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "const BoundingBox& get_boundingBox() const", AS_METHODPR(Text3D, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "bool GetCastShadows() const", AS_METHODPR(Text3D, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool get_castShadows() const", AS_METHODPR(Text3D, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "const String& GetCategory() const", AS_METHODPR(Text3D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "const String& get_category() const", AS_METHODPR(Text3D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Vector2 Text3D::GetCharPosition(unsigned index) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "Vector2 GetCharPosition(uint)", AS_METHODPR(Text3D, GetCharPosition, (unsigned), Vector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "Vector2 get_charPositions(uint)", AS_METHODPR(Text3D, GetCharPosition, (unsigned), Vector2), AS_CALL_THISCALL);
    // Vector2 Text3D::GetCharSize(unsigned index) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "Vector2 GetCharSize(uint)", AS_METHODPR(Text3D, GetCharSize, (unsigned), Vector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "Vector2 get_charSizes(uint)", AS_METHODPR(Text3D, GetCharSize, (unsigned), Vector2), AS_CALL_THISCALL);
    // const Color& Text3D::GetColor(Corner corner) const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "const Color& GetColor(Corner) const", AS_METHODPR(Text3D, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "const Color& get_colors(Corner) const", AS_METHODPR(Text3D, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    // const Color& Text3D::GetColorAttr() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "const Color& GetColorAttr() const", AS_METHODPR(Text3D, GetColorAttr, () const, const Color&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(Text3D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Text3D", "float GetDistance() const", AS_METHODPR(Text3D, GetDistance, () const, float), AS_CALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "uint8 GetDrawableFlags() const", AS_METHODPR(Text3D, GetDrawableFlags, () const, unsigned char), AS_CALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "float GetDrawDistance() const", AS_METHODPR(Text3D, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "float get_drawDistance() const", AS_METHODPR(Text3D, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    // const Color& Text3D::GetEffectColor() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "const Color& GetEffectColor() const", AS_METHODPR(Text3D, GetEffectColor, () const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "const Color& get_effectColor() const", AS_METHODPR(Text3D, GetEffectColor, () const, const Color&), AS_CALL_THISCALL);
    // float Text3D::GetEffectDepthBias() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "float GetEffectDepthBias() const", AS_METHODPR(Text3D, GetEffectDepthBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "float get_effectDepthBias() const", AS_METHODPR(Text3D, GetEffectDepthBias, () const, float), AS_CALL_THISCALL);
    // bool Text3D::GetEffectRoundStroke() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "bool GetEffectRoundStroke() const", AS_METHODPR(Text3D, GetEffectRoundStroke, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool get_effectRoundStroke() const", AS_METHODPR(Text3D, GetEffectRoundStroke, () const, bool), AS_CALL_THISCALL);
    // const IntVector2& Text3D::GetEffectShadowOffset() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "const IntVector2& GetEffectShadowOffset() const", AS_METHODPR(Text3D, GetEffectShadowOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "const IntVector2& get_effectShadowOffset() const", AS_METHODPR(Text3D, GetEffectShadowOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // int Text3D::GetEffectStrokeThickness() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "int GetEffectStrokeThickness() const", AS_METHODPR(Text3D, GetEffectStrokeThickness, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "int get_effectStrokeThickness() const", AS_METHODPR(Text3D, GetEffectStrokeThickness, () const, int), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "VariantMap& GetEventDataMap() const", AS_METHODPR(Text3D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "Object@+ GetEventSender() const", AS_METHODPR(Text3D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // FaceCameraMode Text3D::GetFaceCameraMode() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "FaceCameraMode GetFaceCameraMode() const", AS_METHODPR(Text3D, GetFaceCameraMode, () const, FaceCameraMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "FaceCameraMode get_faceCameraMode() const", AS_METHODPR(Text3D, GetFaceCameraMode, () const, FaceCameraMode), AS_CALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "Light@+ GetFirstLight() const", AS_METHODPR(Text3D, GetFirstLight, () const, Light*), AS_CALL_THISCALL);
    // Font* Text3D::GetFont() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "Font@+ GetFont() const", AS_METHODPR(Text3D, GetFont, () const, Font*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "Font@+ get_font() const", AS_METHODPR(Text3D, GetFont, () const, Font*), AS_CALL_THISCALL);
    // ResourceRef Text3D::GetFontAttr() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "ResourceRef GetFontAttr() const", AS_METHODPR(Text3D, GetFontAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float Text3D::GetFontSize() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "float GetFontSize() const", AS_METHODPR(Text3D, GetFontSize, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "float get_fontSize() const", AS_METHODPR(Text3D, GetFontSize, () const, float), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Text3D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Text3D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Text3D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "const VariantMap& get_globalVars() const", AS_METHODPR(Text3D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int Text3D::GetHeight() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "int GetHeight() const", AS_METHODPR(Text3D, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "int get_height() const", AS_METHODPR(Text3D, GetHeight, () const, int), AS_CALL_THISCALL);
    // HorizontalAlignment Text3D::GetHorizontalAlignment() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "HorizontalAlignment GetHorizontalAlignment() const", AS_METHODPR(Text3D, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "HorizontalAlignment get_horizontalAlignment() const", AS_METHODPR(Text3D, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "uint GetID() const", AS_METHODPR(Text3D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "uint get_id() const", AS_METHODPR(Text3D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Text3D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "uint GetLightMask() const", AS_METHODPR(Text3D, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "uint get_lightMask() const", AS_METHODPR(Text3D, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "Array<Light@>@ GetLights() const", AS_FUNCTION_OBJFIRST(Text3D_GetLights_void), AS_CALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "float GetLodBias() const", AS_METHODPR(Text3D, GetLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "float get_lodBias() const", AS_METHODPR(Text3D, GetLodBias, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "float GetLodDistance() const", AS_METHODPR(Text3D, GetLodDistance, () const, float), AS_CALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "Geometry@+ GetLodGeometry(uint, uint)", AS_METHODPR(Text3D, GetLodGeometry, (unsigned, unsigned), Geometry*), AS_CALL_THISCALL);
    // Material* Text3D::GetMaterial() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "Material@+ GetMaterial() const", AS_METHODPR(Text3D, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "Material@+ get_material() const", AS_METHODPR(Text3D, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    // ResourceRef Text3D::GetMaterialAttr() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "ResourceRef GetMaterialAttr() const", AS_METHODPR(Text3D, GetMaterialAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "uint GetMaxLights() const", AS_METHODPR(Text3D, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "uint get_maxLights() const", AS_METHODPR(Text3D, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "float GetMaxZ() const", AS_METHODPR(Text3D, GetMaxZ, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "float GetMinZ() const", AS_METHODPR(Text3D, GetMinZ, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "Node@+ GetNode() const", AS_METHODPR(Text3D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "Node@+ get_node() const", AS_METHODPR(Text3D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "uint GetNumAttributes() const", AS_METHODPR(Text3D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "uint get_numAttributes() const", AS_METHODPR(Text3D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Text3D::GetNumChars() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "uint GetNumChars() const", AS_METHODPR(Text3D, GetNumChars, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "uint get_numChars() const", AS_METHODPR(Text3D, GetNumChars, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "uint GetNumNetworkAttributes() const", AS_METHODPR(Text3D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "uint GetNumOccluderTriangles()", AS_METHODPR(Text3D, GetNumOccluderTriangles, (), unsigned), AS_CALL_THISCALL);
    // unsigned Text3D::GetNumRows() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "uint GetNumRows() const", AS_METHODPR(Text3D, GetNumRows, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "uint get_numRows() const", AS_METHODPR(Text3D, GetNumRows, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(Text3D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(Text3D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(Text3D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // float Text3D::GetOpacity() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "float GetOpacity() const", AS_METHODPR(Text3D, GetOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "float get_opacity() const", AS_METHODPR(Text3D, GetOpacity, () const, float), AS_CALL_THISCALL);
    // int Text3D::GetRowHeight() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "int GetRowHeight() const", AS_METHODPR(Text3D, GetRowHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "int get_rowHeight() const", AS_METHODPR(Text3D, GetRowHeight, () const, int), AS_CALL_THISCALL);
    // float Text3D::GetRowSpacing() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "float GetRowSpacing() const", AS_METHODPR(Text3D, GetRowSpacing, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "float get_rowSpacing() const", AS_METHODPR(Text3D, GetRowSpacing, () const, float), AS_CALL_THISCALL);
    // int Text3D::GetRowWidth(unsigned index) const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "int GetRowWidth(uint) const", AS_METHODPR(Text3D, GetRowWidth, (unsigned) const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "int get_rowWidths(uint) const", AS_METHODPR(Text3D, GetRowWidth, (unsigned) const, int), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "Scene@+ GetScene() const", AS_METHODPR(Text3D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "float GetShadowDistance() const", AS_METHODPR(Text3D, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "float get_shadowDistance() const", AS_METHODPR(Text3D, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "uint GetShadowMask() const", AS_METHODPR(Text3D, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "uint get_shadowMask() const", AS_METHODPR(Text3D, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "float GetSortValue() const", AS_METHODPR(Text3D, GetSortValue, () const, float), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Text3D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const String& Text3D::GetText() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "const String& GetText() const", AS_METHODPR(Text3D, GetText, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "const String& get_text() const", AS_METHODPR(Text3D, GetText, () const, const String&), AS_CALL_THISCALL);
    // HorizontalAlignment Text3D::GetTextAlignment() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "HorizontalAlignment GetTextAlignment() const", AS_METHODPR(Text3D, GetTextAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "HorizontalAlignment get_textAlignment() const", AS_METHODPR(Text3D, GetTextAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    // String Text3D::GetTextAttr() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "String GetTextAttr() const", AS_METHODPR(Text3D, GetTextAttr, () const, String), AS_CALL_THISCALL);
    // TextEffect Text3D::GetTextEffect() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "TextEffect GetTextEffect() const", AS_METHODPR(Text3D, GetTextEffect, () const, TextEffect), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "TextEffect get_textEffect() const", AS_METHODPR(Text3D, GetTextEffect, () const, TextEffect), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "StringHash GetType() const", AS_METHODPR(Text3D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "StringHash get_type() const", AS_METHODPR(Text3D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "const String& GetTypeName() const", AS_METHODPR(Text3D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "const String& get_typeName() const", AS_METHODPR(Text3D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // UpdateGeometryType Text3D::GetUpdateGeometryType() override | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "UpdateGeometryType GetUpdateGeometryType()", AS_METHODPR(Text3D, GetUpdateGeometryType, (), UpdateGeometryType), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "Array<Light@>@ GetVertexLights() const", AS_FUNCTION_OBJFIRST(Text3D_GetVertexLights_void), AS_CALL_CDECL_OBJFIRST);
    // VerticalAlignment Text3D::GetVerticalAlignment() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "VerticalAlignment GetVerticalAlignment() const", AS_METHODPR(Text3D, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "VerticalAlignment get_verticalAlignment() const", AS_METHODPR(Text3D, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "uint GetViewMask() const", AS_METHODPR(Text3D, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "uint get_viewMask() const", AS_METHODPR(Text3D, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    // int Text3D::GetWidth() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "int GetWidth() const", AS_METHODPR(Text3D, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "int get_width() const", AS_METHODPR(Text3D, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool Text3D::GetWordwrap() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "bool GetWordwrap() const", AS_METHODPR(Text3D, GetWordwrap, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool get_wordwrap() const", AS_METHODPR(Text3D, GetWordwrap, () const, bool), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "const BoundingBox& GetWorldBoundingBox()", AS_METHODPR(Text3D, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "const BoundingBox& get_worldBoundingBox()", AS_METHODPR(Text3D, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "Zone@+ GetZone() const", AS_METHODPR(Text3D, GetZone, () const, Zone*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "Zone@+ get_zone() const", AS_METHODPR(Text3D, GetZone, () const, Zone*), AS_CALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "uint GetZoneMask() const", AS_METHODPR(Text3D, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "uint get_zoneMask() const", AS_METHODPR(Text3D, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "bool HasBasePass(uint) const", AS_METHODPR(Text3D, HasBasePass, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "bool HasEventHandlers() const", AS_METHODPR(Text3D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Text3D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Text3D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "bool IsEnabled() const", AS_METHODPR(Text3D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool get_enabled() const", AS_METHODPR(Text3D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "bool IsEnabledEffective() const", AS_METHODPR(Text3D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool get_enabledEffective() const", AS_METHODPR(Text3D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Text3D::IsFixedScreenSize() const | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "bool IsFixedScreenSize() const", AS_METHODPR(Text3D, IsFixedScreenSize, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool get_fixedScreenSize() const", AS_METHODPR(Text3D, IsFixedScreenSize, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Text3D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "bool IsInView() const", AS_METHODPR(Text3D, IsInView, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool get_inView() const", AS_METHODPR(Text3D, IsInView, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "bool IsInView(Camera@+) const", AS_METHODPR(Text3D, IsInView, (Camera*) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "bool IsInView(const FrameInfo&in, bool = false) const", AS_METHODPR(Text3D, IsInView, (const FrameInfo&, bool) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "bool IsOccludee() const", AS_METHODPR(Text3D, IsOccludee, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool get_occludee() const", AS_METHODPR(Text3D, IsOccludee, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "bool IsOccluder() const", AS_METHODPR(Text3D, IsOccluder, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool get_occluder() const", AS_METHODPR(Text3D, IsOccluder, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "bool IsReplicated() const", AS_METHODPR(Text3D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool get_replicated() const", AS_METHODPR(Text3D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "bool IsTemporary() const", AS_METHODPR(Text3D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool get_temporary() const", AS_METHODPR(Text3D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "bool IsZoneDirty() const", AS_METHODPR(Text3D, IsZoneDirty, () const, bool), AS_CALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void LimitLights()", AS_METHODPR(Text3D, LimitLights, (), void), AS_CALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void LimitVertexLights(bool)", AS_METHODPR(Text3D, LimitVertexLights, (bool), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "bool Load(Deserializer&)", AS_METHODPR(Text3D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Text3D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Text3D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void MarkForUpdate()", AS_METHODPR(Text3D, MarkForUpdate, (), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void MarkInView(const FrameInfo&in)", AS_METHODPR(Text3D, MarkInView, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void MarkInView(uint)", AS_METHODPR(Text3D, MarkInView, (unsigned), void), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "void MarkNetworkUpdate()", AS_METHODPR(Text3D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Text3D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Text3D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Text3D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Drawable::OnSetEnabled() override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void OnSetEnabled()", AS_METHODPR(Text3D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "void PrepareNetworkUpdate()", AS_METHODPR(Text3D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) | File: ../Graphics/Drawable.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Text3D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Text3D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Text3D", "int Refs() const", AS_METHODPR(Text3D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "int get_refs() const", AS_METHODPR(Text3D, Refs, () const, int), AS_CALL_THISCALL);
    // static void Text3D::RegisterObject(Context* context) | File: ../UI/Text3D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Text3D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Text3D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "void Remove()", AS_METHODPR(Text3D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(Text3D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "void RemoveInstanceDefault()", AS_METHODPR(Text3D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "void RemoveObjectAnimation()", AS_METHODPR(Text3D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "void ResetToDefault()", AS_METHODPR(Text3D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "bool Save(Serializer&) const", AS_METHODPR(Text3D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "bool SaveDefaultAttributes() const", AS_METHODPR(Text3D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(Text3D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "bool SaveXML(XMLElement&) const", AS_METHODPR(Text3D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "void SendEvent(StringHash)", AS_METHODPR(Text3D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Text3D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Text3D::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", AS_METHODPR(Text3D, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "void SetAnimationEnabled(bool)", AS_METHODPR(Text3D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_animationEnabled(bool)", AS_METHODPR(Text3D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "void SetAnimationTime(float)", AS_METHODPR(Text3D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Text3D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Text3D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Text3D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Text3D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(Text3D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(Text3D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Text3D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetBasePass(uint)", AS_METHODPR(Text3D, SetBasePass, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "void SetBlockEvents(bool)", AS_METHODPR(Text3D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetCastShadows(bool)", AS_METHODPR(Text3D, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_castShadows(bool)", AS_METHODPR(Text3D, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    // void Text3D::SetColor(const Color& color) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetColor(const Color&in)", AS_METHODPR(Text3D, SetColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_color(const Color&in)", AS_METHODPR(Text3D, SetColor, (const Color&), void), AS_CALL_THISCALL);
    // void Text3D::SetColor(Corner corner, const Color& color) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetColor(Corner, const Color&in)", AS_METHODPR(Text3D, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_colors(Corner, const Color&in)", AS_METHODPR(Text3D, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetDrawDistance(float)", AS_METHODPR(Text3D, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_drawDistance(float)", AS_METHODPR(Text3D, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    // void Text3D::SetEffectColor(const Color& effectColor) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetEffectColor(const Color&in)", AS_METHODPR(Text3D, SetEffectColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_effectColor(const Color&in)", AS_METHODPR(Text3D, SetEffectColor, (const Color&), void), AS_CALL_THISCALL);
    // void Text3D::SetEffectDepthBias(float bias) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetEffectDepthBias(float)", AS_METHODPR(Text3D, SetEffectDepthBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_effectDepthBias(float)", AS_METHODPR(Text3D, SetEffectDepthBias, (float), void), AS_CALL_THISCALL);
    // void Text3D::SetEffectRoundStroke(bool roundStroke) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetEffectRoundStroke(bool)", AS_METHODPR(Text3D, SetEffectRoundStroke, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_effectRoundStroke(bool)", AS_METHODPR(Text3D, SetEffectRoundStroke, (bool), void), AS_CALL_THISCALL);
    // void Text3D::SetEffectShadowOffset(const IntVector2& offset) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetEffectShadowOffset(const IntVector2&in)", AS_METHODPR(Text3D, SetEffectShadowOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_effectShadowOffset(const IntVector2&in)", AS_METHODPR(Text3D, SetEffectShadowOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void Text3D::SetEffectStrokeThickness(int thickness) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetEffectStrokeThickness(int)", AS_METHODPR(Text3D, SetEffectStrokeThickness, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_effectStrokeThickness(int)", AS_METHODPR(Text3D, SetEffectStrokeThickness, (int), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Text3D", "void SetEnabled(bool)", AS_METHODPR(Text3D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_enabled(bool)", AS_METHODPR(Text3D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Text3D::SetFaceCameraMode(FaceCameraMode mode) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetFaceCameraMode(FaceCameraMode)", AS_METHODPR(Text3D, SetFaceCameraMode, (FaceCameraMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_faceCameraMode(FaceCameraMode)", AS_METHODPR(Text3D, SetFaceCameraMode, (FaceCameraMode), void), AS_CALL_THISCALL);
    // void Text3D::SetFixedScreenSize(bool enable) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetFixedScreenSize(bool)", AS_METHODPR(Text3D, SetFixedScreenSize, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_fixedScreenSize(bool)", AS_METHODPR(Text3D, SetFixedScreenSize, (bool), void), AS_CALL_THISCALL);
    // bool Text3D::SetFont(const String& fontName, float size=DEFAULT_FONT_SIZE) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "bool SetFont(const String&in, float = DEFAULT_FONT_SIZE)", AS_METHODPR(Text3D, SetFont, (const String&, float), bool), AS_CALL_THISCALL);
    // bool Text3D::SetFont(Font* font, float size=DEFAULT_FONT_SIZE) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "bool SetFont(Font@+, float = DEFAULT_FONT_SIZE)", AS_METHODPR(Text3D, SetFont, (Font*, float), bool), AS_CALL_THISCALL);
    // void Text3D::SetFontAttr(const ResourceRef& value) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetFontAttr(const ResourceRef&in)", AS_METHODPR(Text3D, SetFontAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // bool Text3D::SetFontSize(float size) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "bool SetFontSize(float)", AS_METHODPR(Text3D, SetFontSize, (float), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "bool set_fontSize(float)", AS_METHODPR(Text3D, SetFontSize, (float), bool), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Text3D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Text3D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Text3D::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetHorizontalAlignment(HorizontalAlignment)", AS_METHODPR(Text3D, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_horizontalAlignment(HorizontalAlignment)", AS_METHODPR(Text3D, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "void SetInstanceDefault(bool)", AS_METHODPR(Text3D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Text3D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetLightMask(uint)", AS_METHODPR(Text3D, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_lightMask(uint)", AS_METHODPR(Text3D, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetLodBias(float)", AS_METHODPR(Text3D, SetLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_lodBias(float)", AS_METHODPR(Text3D, SetLodBias, (float), void), AS_CALL_THISCALL);
    // void Text3D::SetMaterial(Material* material) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetMaterial(Material@+)", AS_METHODPR(Text3D, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_material(Material@+)", AS_METHODPR(Text3D, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    // void Text3D::SetMaterialAttr(const ResourceRef& value) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetMaterialAttr(const ResourceRef&in)", AS_METHODPR(Text3D, SetMaterialAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetMaxLights(uint)", AS_METHODPR(Text3D, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_maxLights(uint)", AS_METHODPR(Text3D, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetMinMaxZ(float, float)", AS_METHODPR(Text3D, SetMinMaxZ, (float, float), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(Text3D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(Text3D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Text3D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(Text3D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetOccludee(bool)", AS_METHODPR(Text3D, SetOccludee, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_occludee(bool)", AS_METHODPR(Text3D, SetOccludee, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetOccluder(bool)", AS_METHODPR(Text3D, SetOccluder, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_occluder(bool)", AS_METHODPR(Text3D, SetOccluder, (bool), void), AS_CALL_THISCALL);
    // void Text3D::SetOpacity(float opacity) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetOpacity(float)", AS_METHODPR(Text3D, SetOpacity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_opacity(float)", AS_METHODPR(Text3D, SetOpacity, (float), void), AS_CALL_THISCALL);
    // void Text3D::SetRowSpacing(float spacing) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetRowSpacing(float)", AS_METHODPR(Text3D, SetRowSpacing, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_rowSpacing(float)", AS_METHODPR(Text3D, SetRowSpacing, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetShadowDistance(float)", AS_METHODPR(Text3D, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_shadowDistance(float)", AS_METHODPR(Text3D, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetShadowMask(uint)", AS_METHODPR(Text3D, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_shadowMask(uint)", AS_METHODPR(Text3D, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetSortValue(float)", AS_METHODPR(Text3D, SetSortValue, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "void SetTemporary(bool)", AS_METHODPR(Text3D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_temporary(bool)", AS_METHODPR(Text3D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Text3D::SetText(const String& text) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetText(const String&in)", AS_METHODPR(Text3D, SetText, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_text(const String&in)", AS_METHODPR(Text3D, SetText, (const String&), void), AS_CALL_THISCALL);
    // void Text3D::SetTextAlignment(HorizontalAlignment align) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetTextAlignment(HorizontalAlignment)", AS_METHODPR(Text3D, SetTextAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_textAlignment(HorizontalAlignment)", AS_METHODPR(Text3D, SetTextAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    // void Text3D::SetTextAttr(const String& value) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetTextAttr(const String&in)", AS_METHODPR(Text3D, SetTextAttr, (const String&), void), AS_CALL_THISCALL);
    // void Text3D::SetTextEffect(TextEffect textEffect) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetTextEffect(TextEffect)", AS_METHODPR(Text3D, SetTextEffect, (TextEffect), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_textEffect(TextEffect)", AS_METHODPR(Text3D, SetTextEffect, (TextEffect), void), AS_CALL_THISCALL);
    // void Text3D::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetVerticalAlignment(VerticalAlignment)", AS_METHODPR(Text3D, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_verticalAlignment(VerticalAlignment)", AS_METHODPR(Text3D, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetViewMask(uint)", AS_METHODPR(Text3D, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_viewMask(uint)", AS_METHODPR(Text3D, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    // void Text3D::SetWidth(int width) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetWidth(int)", AS_METHODPR(Text3D, SetWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_width(int)", AS_METHODPR(Text3D, SetWidth, (int), void), AS_CALL_THISCALL);
    // void Text3D::SetWordwrap(bool enable) | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void SetWordwrap(bool)", AS_METHODPR(Text3D, SetWordwrap, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_wordwrap(bool)", AS_METHODPR(Text3D, SetWordwrap, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetZone(Zone@+, bool = false)", AS_METHODPR(Text3D, SetZone, (Zone*, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void SetZoneMask(uint)", AS_METHODPR(Text3D, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "void set_zoneMask(uint)", AS_METHODPR(Text3D, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit Text3D::Text3D(Context* context) | File: ../UI/Text3D.h
    engine->RegisterObjectBehaviour("Text3D", asBEHAVE_FACTORY, "Text3D@+ f()", AS_FUNCTION(Text3D_Text3D_Context), AS_CALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "void UnsubscribeFromAllEvents()", AS_METHODPR(Text3D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Text3D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Text3D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Text3D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Text3D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Text3D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Text3D", "void Update(const FrameInfo&in)", AS_METHODPR(Text3D, Update, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Text3D::UpdateBatches(const FrameInfo& frame) override | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void UpdateBatches(const FrameInfo&in)", AS_METHODPR(Text3D, UpdateBatches, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Text3D::UpdateGeometry(const FrameInfo& frame) override | File: ../UI/Text3D.h
    engine->RegisterObjectMethod("Text3D", "void UpdateGeometry(const FrameInfo&in)", AS_METHODPR(Text3D, UpdateGeometry, (const FrameInfo&), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Text3D", "int WeakRefs() const", AS_METHODPR(Text3D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Text3D", "int get_weakRefs() const", AS_METHODPR(Text3D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Text3D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Text3D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Text3D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Text3D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Texture", "void AddMetadata(const String&in, const Variant&in)", AS_METHODPR(Texture, AddMetadata, (const String&, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "void set_metadata(const String&in, const Variant&in)", AS_METHODPR(Texture, AddMetadata, (const String&, const Variant&), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Texture", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Texture, AddRef, (), void), AS_CALL_THISCALL);
    // virtual bool Resource::BeginLoad(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "bool BeginLoad(Deserializer&)", AS_METHODPR(Texture, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // static unsigned Texture::CheckMaxLevels(int width, int height, unsigned requestedLevels) | File: ../Graphics/Texture.h
    engine->SetDefaultNamespace("Texture");
    engine->RegisterGlobalFunction("uint CheckMaxLevels(int, int, uint)", AS_FUNCTIONPR(Texture::CheckMaxLevels, (int, int, unsigned), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Texture::CheckMaxLevels(int width, int height, int depth, unsigned requestedLevels) | File: ../Graphics/Texture.h
    engine->SetDefaultNamespace("Texture");
    engine->RegisterGlobalFunction("uint CheckMaxLevels(int, int, int, uint)", AS_FUNCTIONPR(Texture::CheckMaxLevels, (int, int, int, unsigned), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // void GPUObject::ClearDataLost() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture", "void ClearDataLost()", AS_METHODPR(Texture, ClearDataLost, (), void), AS_CALL_THISCALL);
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "bool EndLoad()", AS_METHODPR(Texture, EndLoad, (), bool), AS_CALL_THISCALL);
    // TextureAddressMode Texture::GetAddressMode(TextureCoordinate coord) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "TextureAddressMode GetAddressMode(TextureCoordinate) const", AS_METHODPR(Texture, GetAddressMode, (TextureCoordinate) const, TextureAddressMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "TextureAddressMode get_addressMode(TextureCoordinate) const", AS_METHODPR(Texture, GetAddressMode, (TextureCoordinate) const, TextureAddressMode), AS_CALL_THISCALL);
    // unsigned Texture::GetAnisotropy() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "uint GetAnisotropy() const", AS_METHODPR(Texture, GetAnisotropy, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "uint get_anisotropy() const", AS_METHODPR(Texture, GetAnisotropy, () const, unsigned), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(Texture, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // bool Texture::GetAutoResolve() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "bool GetAutoResolve() const", AS_METHODPR(Texture, GetAutoResolve, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "bool get_autoResolve() const", AS_METHODPR(Texture, GetAutoResolve, () const, bool), AS_CALL_THISCALL);
    // Texture* Texture::GetBackupTexture() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "Texture@+ GetBackupTexture() const", AS_METHODPR(Texture, GetBackupTexture, () const, Texture*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "Texture@+ get_backupTexture() const", AS_METHODPR(Texture, GetBackupTexture, () const, Texture*), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "bool GetBlockEvents() const", AS_METHODPR(Texture, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const Color& Texture::GetBorderColor() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "const Color& GetBorderColor() const", AS_METHODPR(Texture, GetBorderColor, () const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "const Color& get_borderColor() const", AS_METHODPR(Texture, GetBorderColor, () const, const Color&), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "const String& GetCategory() const", AS_METHODPR(Texture, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "const String& get_category() const", AS_METHODPR(Texture, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // unsigned Texture::GetComponents() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "uint GetComponents() const", AS_METHODPR(Texture, GetComponents, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "uint get_components() const", AS_METHODPR(Texture, GetComponents, () const, unsigned), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // unsigned Texture::GetDataSize(int width, int height) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "uint GetDataSize(int, int) const", AS_METHODPR(Texture, GetDataSize, (int, int) const, unsigned), AS_CALL_THISCALL);
    // unsigned Texture::GetDataSize(int width, int height, int depth) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "uint GetDataSize(int, int, int) const", AS_METHODPR(Texture, GetDataSize, (int, int, int) const, unsigned), AS_CALL_THISCALL);
    // static unsigned Texture::GetDataType(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // int Texture::GetDepth() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "int GetDepth() const", AS_METHODPR(Texture, GetDepth, () const, int), AS_CALL_THISCALL);
    // static unsigned Texture::GetDSVFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "VariantMap& GetEventDataMap() const", AS_METHODPR(Texture, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "Object@+ GetEventSender() const", AS_METHODPR(Texture, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // static unsigned Texture::GetExternalFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // TextureFilterMode Texture::GetFilterMode() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "TextureFilterMode GetFilterMode() const", AS_METHODPR(Texture, GetFilterMode, () const, TextureFilterMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "TextureFilterMode get_filterMode() const", AS_METHODPR(Texture, GetFilterMode, () const, TextureFilterMode), AS_CALL_THISCALL);
    // unsigned Texture::GetFormat() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "uint GetFormat() const", AS_METHODPR(Texture, GetFormat, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "uint get_format() const", AS_METHODPR(Texture, GetFormat, () const, unsigned), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Texture, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Texture, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Texture, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "const VariantMap& get_globalVars() const", AS_METHODPR(Texture, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // void* GPUObject::GetGPUObject() const | File: ../Graphics/GPUObject.h
    // Error: type "void*" can not automatically bind
    // unsigned GPUObject::GetGPUObjectName() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture", "uint GetGPUObjectName() const", AS_METHODPR(Texture, GetGPUObjectName, () const, unsigned), AS_CALL_THISCALL);
    // Graphics* GPUObject::GetGraphics() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture", "Graphics@+ GetGraphics() const", AS_METHODPR(Texture, GetGraphics, () const, Graphics*), AS_CALL_THISCALL);
    // int Texture::GetHeight() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "int GetHeight() const", AS_METHODPR(Texture, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "int get_height() const", AS_METHODPR(Texture, GetHeight, () const, int), AS_CALL_THISCALL);
    // int Texture::GetLevelDepth(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "int GetLevelDepth(uint) const", AS_METHODPR(Texture, GetLevelDepth, (unsigned) const, int), AS_CALL_THISCALL);
    // int Texture::GetLevelHeight(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "int GetLevelHeight(uint) const", AS_METHODPR(Texture, GetLevelHeight, (unsigned) const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "int get_levelHeight(uint) const", AS_METHODPR(Texture, GetLevelHeight, (unsigned) const, int), AS_CALL_THISCALL);
    // unsigned Texture::GetLevels() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "uint GetLevels() const", AS_METHODPR(Texture, GetLevels, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "uint get_levels() const", AS_METHODPR(Texture, GetLevels, () const, unsigned), AS_CALL_THISCALL);
    // bool Texture::GetLevelsDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "bool GetLevelsDirty() const", AS_METHODPR(Texture, GetLevelsDirty, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "bool get_levelsDirty() const", AS_METHODPR(Texture, GetLevelsDirty, () const, bool), AS_CALL_THISCALL);
    // int Texture::GetLevelWidth(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "int GetLevelWidth(uint) const", AS_METHODPR(Texture, GetLevelWidth, (unsigned) const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "int get_levelWidth(uint) const", AS_METHODPR(Texture, GetLevelWidth, (unsigned) const, int), AS_CALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "uint GetMemoryUse() const", AS_METHODPR(Texture, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "uint get_memoryUse() const", AS_METHODPR(Texture, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // const Variant& ResourceWithMetadata::GetMetadata(const String& name) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "const Variant& GetMetadata(const String&in) const", AS_METHODPR(Texture, GetMetadata, (const String&) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "const Variant& get_metadata(const String&in) const", AS_METHODPR(Texture, GetMetadata, (const String&) const, const Variant&), AS_CALL_THISCALL);
    // int Texture::GetMipsToSkip(MaterialQuality quality) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "int GetMipsToSkip(MaterialQuality) const", AS_METHODPR(Texture, GetMipsToSkip, (MaterialQuality) const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "int get_mipsToSkip(MaterialQuality) const", AS_METHODPR(Texture, GetMipsToSkip, (MaterialQuality) const, int), AS_CALL_THISCALL);
    // int Texture::GetMultiSample() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "int GetMultiSample() const", AS_METHODPR(Texture, GetMultiSample, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "int get_multiSample() const", AS_METHODPR(Texture, GetMultiSample, () const, int), AS_CALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "const String& GetName() const", AS_METHODPR(Texture, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "const String& get_name() const", AS_METHODPR(Texture, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "StringHash GetNameHash() const", AS_METHODPR(Texture, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // bool Texture::GetParametersDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "bool GetParametersDirty() const", AS_METHODPR(Texture, GetParametersDirty, () const, bool), AS_CALL_THISCALL);
    // void* Texture::GetResolveTexture() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // unsigned Texture::GetRowDataSize(int width) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "uint GetRowDataSize(int) const", AS_METHODPR(Texture, GetRowDataSize, (int) const, unsigned), AS_CALL_THISCALL);
    // void* Texture::GetSampler() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // void* Texture::GetShaderResourceView() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // bool Texture::GetShadowCompare() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "bool GetShadowCompare() const", AS_METHODPR(Texture, GetShadowCompare, () const, bool), AS_CALL_THISCALL);
    // bool Texture::GetSRGB() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "bool GetSRGB() const", AS_METHODPR(Texture, GetSRGB, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "bool get_sRGB() const", AS_METHODPR(Texture, GetSRGB, () const, bool), AS_CALL_THISCALL);
    // unsigned Texture::GetSRGBFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // static unsigned Texture::GetSRVFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Texture, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // unsigned Texture::GetTarget() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "uint GetTarget() const", AS_METHODPR(Texture, GetTarget, () const, unsigned), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "StringHash GetType() const", AS_METHODPR(Texture, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "StringHash get_type() const", AS_METHODPR(Texture, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "const String& GetTypeName() const", AS_METHODPR(Texture, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "const String& get_typeName() const", AS_METHODPR(Texture, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // TextureUsage Texture::GetUsage() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "TextureUsage GetUsage() const", AS_METHODPR(Texture, GetUsage, () const, TextureUsage), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "TextureUsage get_usage() const", AS_METHODPR(Texture, GetUsage, () const, TextureUsage), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "uint GetUseTimer()", AS_METHODPR(Texture, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "uint get_useTimer()", AS_METHODPR(Texture, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // int Texture::GetWidth() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "int GetWidth() const", AS_METHODPR(Texture, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "int get_width() const", AS_METHODPR(Texture, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "bool HasEventHandlers() const", AS_METHODPR(Texture, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool ResourceWithMetadata::HasMetadata() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "bool HasMetadata() const", AS_METHODPR(Texture, HasMetadata, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "bool get_hasMetadata() const", AS_METHODPR(Texture, HasMetadata, () const, bool), AS_CALL_THISCALL);
    // bool GPUObject::HasPendingData() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture", "bool HasPendingData() const", AS_METHODPR(Texture, HasPendingData, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Texture, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Texture, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Texture::IsCompressed() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "bool IsCompressed() const", AS_METHODPR(Texture, IsCompressed, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "bool get_compressed() const", AS_METHODPR(Texture, IsCompressed, () const, bool), AS_CALL_THISCALL);
    // bool GPUObject::IsDataLost() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture", "bool IsDataLost() const", AS_METHODPR(Texture, IsDataLost, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "bool get_dataLost() const", AS_METHODPR(Texture, IsDataLost, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Texture, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Texture::IsResolveDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "bool IsResolveDirty() const", AS_METHODPR(Texture, IsResolveDirty, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "bool get_resolveDirty() const", AS_METHODPR(Texture, IsResolveDirty, () const, bool), AS_CALL_THISCALL);
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "bool Load(Deserializer&)", AS_METHODPR(Texture, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "bool LoadFile(const String&in)", AS_METHODPR(Texture, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "bool Load(const String&in)", AS_METHODPR(Texture, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // virtual void GPUObject::OnDeviceLost() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture", "void OnDeviceLost()", AS_METHODPR(Texture, OnDeviceLost, (), void), AS_CALL_THISCALL);
    // virtual void GPUObject::OnDeviceReset() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture", "void OnDeviceReset()", AS_METHODPR(Texture, OnDeviceReset, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Texture, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Texture", "int Refs() const", AS_METHODPR(Texture, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "int get_refs() const", AS_METHODPR(Texture, Refs, () const, int), AS_CALL_THISCALL);
    // void Texture::RegenerateLevels() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void RegenerateLevels()", AS_METHODPR(Texture, RegenerateLevels, (), void), AS_CALL_THISCALL);
    // virtual void GPUObject::Release() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture", "void Release()", AS_METHODPR(Texture, Release, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Texture", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Texture, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void ResourceWithMetadata::RemoveAllMetadata() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "void RemoveAllMetadata()", AS_METHODPR(Texture, RemoveAllMetadata, (), void), AS_CALL_THISCALL);
    // void ResourceWithMetadata::RemoveMetadata(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "void RemoveMetadata(const String&in)", AS_METHODPR(Texture, RemoveMetadata, (const String&), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "void ResetUseTimer()", AS_METHODPR(Texture, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "bool Save(Serializer&) const", AS_METHODPR(Texture, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "bool SaveFile(const String&in) const", AS_METHODPR(Texture, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "bool Save(const String&in) const", AS_METHODPR(Texture, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "void SendEvent(StringHash)", AS_METHODPR(Texture, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Texture, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Texture::SetAddressMode(TextureCoordinate coord, TextureAddressMode mode) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetAddressMode(TextureCoordinate, TextureAddressMode)", AS_METHODPR(Texture, SetAddressMode, (TextureCoordinate, TextureAddressMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "void set_addressMode(TextureCoordinate, TextureAddressMode)", AS_METHODPR(Texture, SetAddressMode, (TextureCoordinate, TextureAddressMode), void), AS_CALL_THISCALL);
    // void Texture::SetAnisotropy(unsigned level) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetAnisotropy(uint)", AS_METHODPR(Texture, SetAnisotropy, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "void set_anisotropy(uint)", AS_METHODPR(Texture, SetAnisotropy, (unsigned), void), AS_CALL_THISCALL);
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(Texture, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void Texture::SetBackupTexture(Texture* texture) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetBackupTexture(Texture@+)", AS_METHODPR(Texture, SetBackupTexture, (Texture*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "void set_backupTexture(Texture@+)", AS_METHODPR(Texture, SetBackupTexture, (Texture*), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "void SetBlockEvents(bool)", AS_METHODPR(Texture, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Texture::SetBorderColor(const Color& color) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetBorderColor(const Color&in)", AS_METHODPR(Texture, SetBorderColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "void set_borderColor(const Color&in)", AS_METHODPR(Texture, SetBorderColor, (const Color&), void), AS_CALL_THISCALL);
    // void Texture::SetFilterMode(TextureFilterMode mode) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetFilterMode(TextureFilterMode)", AS_METHODPR(Texture, SetFilterMode, (TextureFilterMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "void set_filterMode(TextureFilterMode)", AS_METHODPR(Texture, SetFilterMode, (TextureFilterMode), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Texture, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Texture, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Texture::SetLevelsDirty() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetLevelsDirty()", AS_METHODPR(Texture, SetLevelsDirty, (), void), AS_CALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "void SetMemoryUse(uint)", AS_METHODPR(Texture, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void Texture::SetMipsToSkip(MaterialQuality quality, int toSkip) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetMipsToSkip(MaterialQuality, int)", AS_METHODPR(Texture, SetMipsToSkip, (MaterialQuality, int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "void set_mipsToSkip(MaterialQuality, int)", AS_METHODPR(Texture, SetMipsToSkip, (MaterialQuality, int), void), AS_CALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture", "void SetName(const String&in)", AS_METHODPR(Texture, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "void set_name(const String&in)", AS_METHODPR(Texture, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Texture::SetNumLevels(unsigned levels) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetNumLevels(uint)", AS_METHODPR(Texture, SetNumLevels, (unsigned), void), AS_CALL_THISCALL);
    // void Texture::SetParameters(XMLFile* file) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetParameters(XMLFile@+)", AS_METHODPR(Texture, SetParameters, (XMLFile*), void), AS_CALL_THISCALL);
    // void Texture::SetParameters(const XMLElement& element) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetParameters(const XMLElement&in)", AS_METHODPR(Texture, SetParameters, (const XMLElement&), void), AS_CALL_THISCALL);
    // void Texture::SetParametersDirty() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetParametersDirty()", AS_METHODPR(Texture, SetParametersDirty, (), void), AS_CALL_THISCALL);
    // void Texture::SetResolveDirty(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetResolveDirty(bool)", AS_METHODPR(Texture, SetResolveDirty, (bool), void), AS_CALL_THISCALL);
    // void Texture::SetShadowCompare(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetShadowCompare(bool)", AS_METHODPR(Texture, SetShadowCompare, (bool), void), AS_CALL_THISCALL);
    // void Texture::SetSRGB(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void SetSRGB(bool)", AS_METHODPR(Texture, SetSRGB, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "void set_sRGB(bool)", AS_METHODPR(Texture, SetSRGB, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit Texture::Texture(Context* context) | File: ../Graphics/Texture.h
    engine->RegisterObjectBehaviour("Texture", asBEHAVE_FACTORY, "Texture@+ f()", AS_FUNCTION(Texture_Texture_Context), AS_CALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "void UnsubscribeFromAllEvents()", AS_METHODPR(Texture, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Texture_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Texture, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Texture, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Texture, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void Texture::UpdateParameters() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture", "void UpdateParameters()", AS_METHODPR(Texture, UpdateParameters, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Texture", "int WeakRefs() const", AS_METHODPR(Texture, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture", "int get_weakRefs() const", AS_METHODPR(Texture, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Texture2D", "void AddMetadata(const String&in, const Variant&in)", AS_METHODPR(Texture2D, AddMetadata, (const String&, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "void set_metadata(const String&in, const Variant&in)", AS_METHODPR(Texture2D, AddMetadata, (const String&, const Variant&), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Texture2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Texture2D, AddRef, (), void), AS_CALL_THISCALL);
    // bool Texture2D::BeginLoad(Deserializer& source) override | File: ../Graphics/Texture2D.h
    engine->RegisterObjectMethod("Texture2D", "bool BeginLoad(Deserializer&)", AS_METHODPR(Texture2D, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // static unsigned Texture::CheckMaxLevels(int width, int height, unsigned requestedLevels) | File: ../Graphics/Texture.h
    engine->SetDefaultNamespace("Texture2D");
    engine->RegisterGlobalFunction("uint CheckMaxLevels(int, int, uint)", AS_FUNCTIONPR(Texture2D::CheckMaxLevels, (int, int, unsigned), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Texture::CheckMaxLevels(int width, int height, int depth, unsigned requestedLevels) | File: ../Graphics/Texture.h
    engine->SetDefaultNamespace("Texture2D");
    engine->RegisterGlobalFunction("uint CheckMaxLevels(int, int, int, uint)", AS_FUNCTIONPR(Texture2D::CheckMaxLevels, (int, int, int, unsigned), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // void GPUObject::ClearDataLost() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture2D", "void ClearDataLost()", AS_METHODPR(Texture2D, ClearDataLost, (), void), AS_CALL_THISCALL);
    // bool Texture2D::EndLoad() override | File: ../Graphics/Texture2D.h
    engine->RegisterObjectMethod("Texture2D", "bool EndLoad()", AS_METHODPR(Texture2D, EndLoad, (), bool), AS_CALL_THISCALL);
    // TextureAddressMode Texture::GetAddressMode(TextureCoordinate coord) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "TextureAddressMode GetAddressMode(TextureCoordinate) const", AS_METHODPR(Texture2D, GetAddressMode, (TextureCoordinate) const, TextureAddressMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "TextureAddressMode get_addressMode(TextureCoordinate) const", AS_METHODPR(Texture2D, GetAddressMode, (TextureCoordinate) const, TextureAddressMode), AS_CALL_THISCALL);
    // unsigned Texture::GetAnisotropy() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "uint GetAnisotropy() const", AS_METHODPR(Texture2D, GetAnisotropy, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "uint get_anisotropy() const", AS_METHODPR(Texture2D, GetAnisotropy, () const, unsigned), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(Texture2D, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // bool Texture::GetAutoResolve() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "bool GetAutoResolve() const", AS_METHODPR(Texture2D, GetAutoResolve, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "bool get_autoResolve() const", AS_METHODPR(Texture2D, GetAutoResolve, () const, bool), AS_CALL_THISCALL);
    // Texture* Texture::GetBackupTexture() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "Texture@+ GetBackupTexture() const", AS_METHODPR(Texture2D, GetBackupTexture, () const, Texture*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "Texture@+ get_backupTexture() const", AS_METHODPR(Texture2D, GetBackupTexture, () const, Texture*), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "bool GetBlockEvents() const", AS_METHODPR(Texture2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const Color& Texture::GetBorderColor() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "const Color& GetBorderColor() const", AS_METHODPR(Texture2D, GetBorderColor, () const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "const Color& get_borderColor() const", AS_METHODPR(Texture2D, GetBorderColor, () const, const Color&), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "const String& GetCategory() const", AS_METHODPR(Texture2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "const String& get_category() const", AS_METHODPR(Texture2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // unsigned Texture::GetComponents() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "uint GetComponents() const", AS_METHODPR(Texture2D, GetComponents, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "uint get_components() const", AS_METHODPR(Texture2D, GetComponents, () const, unsigned), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // bool Texture2D::GetData(unsigned level, void* dest) const | File: ../Graphics/Texture2D.h
    // Error: type "void*" can not automatically bind
    // unsigned Texture::GetDataSize(int width, int height) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "uint GetDataSize(int, int) const", AS_METHODPR(Texture2D, GetDataSize, (int, int) const, unsigned), AS_CALL_THISCALL);
    // unsigned Texture::GetDataSize(int width, int height, int depth) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "uint GetDataSize(int, int, int) const", AS_METHODPR(Texture2D, GetDataSize, (int, int, int) const, unsigned), AS_CALL_THISCALL);
    // static unsigned Texture::GetDataType(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // int Texture::GetDepth() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "int GetDepth() const", AS_METHODPR(Texture2D, GetDepth, () const, int), AS_CALL_THISCALL);
    // static unsigned Texture::GetDSVFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(Texture2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "Object@+ GetEventSender() const", AS_METHODPR(Texture2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // static unsigned Texture::GetExternalFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // TextureFilterMode Texture::GetFilterMode() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "TextureFilterMode GetFilterMode() const", AS_METHODPR(Texture2D, GetFilterMode, () const, TextureFilterMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "TextureFilterMode get_filterMode() const", AS_METHODPR(Texture2D, GetFilterMode, () const, TextureFilterMode), AS_CALL_THISCALL);
    // unsigned Texture::GetFormat() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "uint GetFormat() const", AS_METHODPR(Texture2D, GetFormat, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "uint get_format() const", AS_METHODPR(Texture2D, GetFormat, () const, unsigned), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Texture2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Texture2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Texture2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "const VariantMap& get_globalVars() const", AS_METHODPR(Texture2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // void* GPUObject::GetGPUObject() const | File: ../Graphics/GPUObject.h
    // Error: type "void*" can not automatically bind
    // unsigned GPUObject::GetGPUObjectName() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture2D", "uint GetGPUObjectName() const", AS_METHODPR(Texture2D, GetGPUObjectName, () const, unsigned), AS_CALL_THISCALL);
    // Graphics* GPUObject::GetGraphics() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture2D", "Graphics@+ GetGraphics() const", AS_METHODPR(Texture2D, GetGraphics, () const, Graphics*), AS_CALL_THISCALL);
    // int Texture::GetHeight() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "int GetHeight() const", AS_METHODPR(Texture2D, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "int get_height() const", AS_METHODPR(Texture2D, GetHeight, () const, int), AS_CALL_THISCALL);
    // bool Texture2D::GetImage(Image& image) const | File: ../Graphics/Texture2D.h
    engine->RegisterObjectMethod("Texture2D", "bool GetImage(Image&) const", AS_METHODPR(Texture2D, GetImage, (Image&) const, bool), AS_CALL_THISCALL);
    // SharedPtr<Image> Texture2D::GetImage() const | File: ../Graphics/Texture2D.h
    engine->RegisterObjectMethod("Texture2D", "Image@+ GetImage() const", AS_FUNCTION_OBJFIRST(Texture2D_GetImage_void), AS_CALL_CDECL_OBJFIRST);
    // int Texture::GetLevelDepth(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "int GetLevelDepth(uint) const", AS_METHODPR(Texture2D, GetLevelDepth, (unsigned) const, int), AS_CALL_THISCALL);
    // int Texture::GetLevelHeight(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "int GetLevelHeight(uint) const", AS_METHODPR(Texture2D, GetLevelHeight, (unsigned) const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "int get_levelHeight(uint) const", AS_METHODPR(Texture2D, GetLevelHeight, (unsigned) const, int), AS_CALL_THISCALL);
    // unsigned Texture::GetLevels() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "uint GetLevels() const", AS_METHODPR(Texture2D, GetLevels, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "uint get_levels() const", AS_METHODPR(Texture2D, GetLevels, () const, unsigned), AS_CALL_THISCALL);
    // bool Texture::GetLevelsDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "bool GetLevelsDirty() const", AS_METHODPR(Texture2D, GetLevelsDirty, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "bool get_levelsDirty() const", AS_METHODPR(Texture2D, GetLevelsDirty, () const, bool), AS_CALL_THISCALL);
    // int Texture::GetLevelWidth(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "int GetLevelWidth(uint) const", AS_METHODPR(Texture2D, GetLevelWidth, (unsigned) const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "int get_levelWidth(uint) const", AS_METHODPR(Texture2D, GetLevelWidth, (unsigned) const, int), AS_CALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "uint GetMemoryUse() const", AS_METHODPR(Texture2D, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "uint get_memoryUse() const", AS_METHODPR(Texture2D, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // const Variant& ResourceWithMetadata::GetMetadata(const String& name) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "const Variant& GetMetadata(const String&in) const", AS_METHODPR(Texture2D, GetMetadata, (const String&) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "const Variant& get_metadata(const String&in) const", AS_METHODPR(Texture2D, GetMetadata, (const String&) const, const Variant&), AS_CALL_THISCALL);
    // int Texture::GetMipsToSkip(MaterialQuality quality) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "int GetMipsToSkip(MaterialQuality) const", AS_METHODPR(Texture2D, GetMipsToSkip, (MaterialQuality) const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "int get_mipsToSkip(MaterialQuality) const", AS_METHODPR(Texture2D, GetMipsToSkip, (MaterialQuality) const, int), AS_CALL_THISCALL);
    // int Texture::GetMultiSample() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "int GetMultiSample() const", AS_METHODPR(Texture2D, GetMultiSample, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "int get_multiSample() const", AS_METHODPR(Texture2D, GetMultiSample, () const, int), AS_CALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "const String& GetName() const", AS_METHODPR(Texture2D, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "const String& get_name() const", AS_METHODPR(Texture2D, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "StringHash GetNameHash() const", AS_METHODPR(Texture2D, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // bool Texture::GetParametersDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "bool GetParametersDirty() const", AS_METHODPR(Texture2D, GetParametersDirty, () const, bool), AS_CALL_THISCALL);
    // RenderSurface* Texture2D::GetRenderSurface() const | File: ../Graphics/Texture2D.h
    engine->RegisterObjectMethod("Texture2D", "RenderSurface@+ GetRenderSurface() const", AS_METHODPR(Texture2D, GetRenderSurface, () const, RenderSurface*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "RenderSurface@+ get_renderSurface() const", AS_METHODPR(Texture2D, GetRenderSurface, () const, RenderSurface*), AS_CALL_THISCALL);
    // void* Texture::GetResolveTexture() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // unsigned Texture::GetRowDataSize(int width) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "uint GetRowDataSize(int) const", AS_METHODPR(Texture2D, GetRowDataSize, (int) const, unsigned), AS_CALL_THISCALL);
    // void* Texture::GetSampler() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // void* Texture::GetShaderResourceView() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // bool Texture::GetShadowCompare() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "bool GetShadowCompare() const", AS_METHODPR(Texture2D, GetShadowCompare, () const, bool), AS_CALL_THISCALL);
    // bool Texture::GetSRGB() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "bool GetSRGB() const", AS_METHODPR(Texture2D, GetSRGB, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "bool get_sRGB() const", AS_METHODPR(Texture2D, GetSRGB, () const, bool), AS_CALL_THISCALL);
    // unsigned Texture::GetSRGBFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // static unsigned Texture::GetSRVFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Texture2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // unsigned Texture::GetTarget() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "uint GetTarget() const", AS_METHODPR(Texture2D, GetTarget, () const, unsigned), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "StringHash GetType() const", AS_METHODPR(Texture2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "StringHash get_type() const", AS_METHODPR(Texture2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "const String& GetTypeName() const", AS_METHODPR(Texture2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "const String& get_typeName() const", AS_METHODPR(Texture2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // TextureUsage Texture::GetUsage() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "TextureUsage GetUsage() const", AS_METHODPR(Texture2D, GetUsage, () const, TextureUsage), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "TextureUsage get_usage() const", AS_METHODPR(Texture2D, GetUsage, () const, TextureUsage), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "uint GetUseTimer()", AS_METHODPR(Texture2D, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "uint get_useTimer()", AS_METHODPR(Texture2D, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // int Texture::GetWidth() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "int GetWidth() const", AS_METHODPR(Texture2D, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "int get_width() const", AS_METHODPR(Texture2D, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "bool HasEventHandlers() const", AS_METHODPR(Texture2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool ResourceWithMetadata::HasMetadata() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "bool HasMetadata() const", AS_METHODPR(Texture2D, HasMetadata, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "bool get_hasMetadata() const", AS_METHODPR(Texture2D, HasMetadata, () const, bool), AS_CALL_THISCALL);
    // bool GPUObject::HasPendingData() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture2D", "bool HasPendingData() const", AS_METHODPR(Texture2D, HasPendingData, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Texture2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Texture2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Texture::IsCompressed() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "bool IsCompressed() const", AS_METHODPR(Texture2D, IsCompressed, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "bool get_compressed() const", AS_METHODPR(Texture2D, IsCompressed, () const, bool), AS_CALL_THISCALL);
    // bool GPUObject::IsDataLost() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture2D", "bool IsDataLost() const", AS_METHODPR(Texture2D, IsDataLost, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "bool get_dataLost() const", AS_METHODPR(Texture2D, IsDataLost, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Texture2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Texture::IsResolveDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "bool IsResolveDirty() const", AS_METHODPR(Texture2D, IsResolveDirty, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "bool get_resolveDirty() const", AS_METHODPR(Texture2D, IsResolveDirty, () const, bool), AS_CALL_THISCALL);
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "bool Load(Deserializer&)", AS_METHODPR(Texture2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "bool LoadFile(const String&in)", AS_METHODPR(Texture2D, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "bool Load(const String&in)", AS_METHODPR(Texture2D, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // void Texture2D::OnDeviceLost() override | File: ../Graphics/Texture2D.h
    engine->RegisterObjectMethod("Texture2D", "void OnDeviceLost()", AS_METHODPR(Texture2D, OnDeviceLost, (), void), AS_CALL_THISCALL);
    // void Texture2D::OnDeviceReset() override | File: ../Graphics/Texture2D.h
    engine->RegisterObjectMethod("Texture2D", "void OnDeviceReset()", AS_METHODPR(Texture2D, OnDeviceReset, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Texture2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Texture2D", "int Refs() const", AS_METHODPR(Texture2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "int get_refs() const", AS_METHODPR(Texture2D, Refs, () const, int), AS_CALL_THISCALL);
    // void Texture::RegenerateLevels() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void RegenerateLevels()", AS_METHODPR(Texture2D, RegenerateLevels, (), void), AS_CALL_THISCALL);
    // static void Texture2D::RegisterObject(Context* context) | File: ../Graphics/Texture2D.h
    // Not registered because have @nobind mark
    // void Texture2D::Release() override | File: ../Graphics/Texture2D.h
    engine->RegisterObjectMethod("Texture2D", "void Release()", AS_METHODPR(Texture2D, Release, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Texture2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Texture2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void ResourceWithMetadata::RemoveAllMetadata() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "void RemoveAllMetadata()", AS_METHODPR(Texture2D, RemoveAllMetadata, (), void), AS_CALL_THISCALL);
    // void ResourceWithMetadata::RemoveMetadata(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "void RemoveMetadata(const String&in)", AS_METHODPR(Texture2D, RemoveMetadata, (const String&), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "void ResetUseTimer()", AS_METHODPR(Texture2D, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "bool Save(Serializer&) const", AS_METHODPR(Texture2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "bool SaveFile(const String&in) const", AS_METHODPR(Texture2D, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "bool Save(const String&in) const", AS_METHODPR(Texture2D, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "void SendEvent(StringHash)", AS_METHODPR(Texture2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Texture2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Texture::SetAddressMode(TextureCoordinate coord, TextureAddressMode mode) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetAddressMode(TextureCoordinate, TextureAddressMode)", AS_METHODPR(Texture2D, SetAddressMode, (TextureCoordinate, TextureAddressMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "void set_addressMode(TextureCoordinate, TextureAddressMode)", AS_METHODPR(Texture2D, SetAddressMode, (TextureCoordinate, TextureAddressMode), void), AS_CALL_THISCALL);
    // void Texture::SetAnisotropy(unsigned level) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetAnisotropy(uint)", AS_METHODPR(Texture2D, SetAnisotropy, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "void set_anisotropy(uint)", AS_METHODPR(Texture2D, SetAnisotropy, (unsigned), void), AS_CALL_THISCALL);
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(Texture2D, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void Texture::SetBackupTexture(Texture* texture) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetBackupTexture(Texture@+)", AS_METHODPR(Texture2D, SetBackupTexture, (Texture*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "void set_backupTexture(Texture@+)", AS_METHODPR(Texture2D, SetBackupTexture, (Texture*), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "void SetBlockEvents(bool)", AS_METHODPR(Texture2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Texture::SetBorderColor(const Color& color) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetBorderColor(const Color&in)", AS_METHODPR(Texture2D, SetBorderColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "void set_borderColor(const Color&in)", AS_METHODPR(Texture2D, SetBorderColor, (const Color&), void), AS_CALL_THISCALL);
    // bool Texture2D::SetData(unsigned level, int x, int y, int width, int height, const void* data) | File: ../Graphics/Texture2D.h
    // Error: type "const void*" can not automatically bind
    // bool Texture2D::SetData(Image* image, bool useAlpha=false) | File: ../Graphics/Texture2D.h
    engine->RegisterObjectMethod("Texture2D", "bool SetData(Image@+, bool = false)", AS_METHODPR(Texture2D, SetData, (Image*, bool), bool), AS_CALL_THISCALL);
    // void Texture::SetFilterMode(TextureFilterMode mode) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetFilterMode(TextureFilterMode)", AS_METHODPR(Texture2D, SetFilterMode, (TextureFilterMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "void set_filterMode(TextureFilterMode)", AS_METHODPR(Texture2D, SetFilterMode, (TextureFilterMode), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Texture2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Texture2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Texture::SetLevelsDirty() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetLevelsDirty()", AS_METHODPR(Texture2D, SetLevelsDirty, (), void), AS_CALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "void SetMemoryUse(uint)", AS_METHODPR(Texture2D, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void Texture::SetMipsToSkip(MaterialQuality quality, int toSkip) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetMipsToSkip(MaterialQuality, int)", AS_METHODPR(Texture2D, SetMipsToSkip, (MaterialQuality, int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "void set_mipsToSkip(MaterialQuality, int)", AS_METHODPR(Texture2D, SetMipsToSkip, (MaterialQuality, int), void), AS_CALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2D", "void SetName(const String&in)", AS_METHODPR(Texture2D, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "void set_name(const String&in)", AS_METHODPR(Texture2D, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Texture::SetNumLevels(unsigned levels) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetNumLevels(uint)", AS_METHODPR(Texture2D, SetNumLevels, (unsigned), void), AS_CALL_THISCALL);
    // void Texture::SetParameters(XMLFile* file) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetParameters(XMLFile@+)", AS_METHODPR(Texture2D, SetParameters, (XMLFile*), void), AS_CALL_THISCALL);
    // void Texture::SetParameters(const XMLElement& element) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetParameters(const XMLElement&in)", AS_METHODPR(Texture2D, SetParameters, (const XMLElement&), void), AS_CALL_THISCALL);
    // void Texture::SetParametersDirty() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetParametersDirty()", AS_METHODPR(Texture2D, SetParametersDirty, (), void), AS_CALL_THISCALL);
    // void Texture::SetResolveDirty(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetResolveDirty(bool)", AS_METHODPR(Texture2D, SetResolveDirty, (bool), void), AS_CALL_THISCALL);
    // void Texture::SetShadowCompare(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetShadowCompare(bool)", AS_METHODPR(Texture2D, SetShadowCompare, (bool), void), AS_CALL_THISCALL);
    // bool Texture2D::SetSize(int width, int height, unsigned format, TextureUsage usage=TEXTURE_STATIC, int multiSample=1, bool autoResolve=true) | File: ../Graphics/Texture2D.h
    engine->RegisterObjectMethod("Texture2D", "bool SetSize(int, int, uint, TextureUsage = TEXTURE_STATIC, int = 1, bool = true)", AS_METHODPR(Texture2D, SetSize, (int, int, unsigned, TextureUsage, int, bool), bool), AS_CALL_THISCALL);
    // void Texture::SetSRGB(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void SetSRGB(bool)", AS_METHODPR(Texture2D, SetSRGB, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "void set_sRGB(bool)", AS_METHODPR(Texture2D, SetSRGB, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit Texture2D::Texture2D(Context* context) | File: ../Graphics/Texture2D.h
    engine->RegisterObjectBehaviour("Texture2D", asBEHAVE_FACTORY, "Texture2D@+ f()", AS_FUNCTION(Texture2D_Texture2D_Context), AS_CALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(Texture2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Texture2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Texture2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Texture2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Texture2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void Texture::UpdateParameters() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2D", "void UpdateParameters()", AS_METHODPR(Texture2D, UpdateParameters, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Texture2D", "int WeakRefs() const", AS_METHODPR(Texture2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2D", "int get_weakRefs() const", AS_METHODPR(Texture2D, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Texture2DArray", "void AddMetadata(const String&in, const Variant&in)", AS_METHODPR(Texture2DArray, AddMetadata, (const String&, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "void set_metadata(const String&in, const Variant&in)", AS_METHODPR(Texture2DArray, AddMetadata, (const String&, const Variant&), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Texture2DArray", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Texture2DArray, AddRef, (), void), AS_CALL_THISCALL);
    // bool Texture2DArray::BeginLoad(Deserializer& source) override | File: ../Graphics/Texture2DArray.h
    engine->RegisterObjectMethod("Texture2DArray", "bool BeginLoad(Deserializer&)", AS_METHODPR(Texture2DArray, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // static unsigned Texture::CheckMaxLevels(int width, int height, unsigned requestedLevels) | File: ../Graphics/Texture.h
    engine->SetDefaultNamespace("Texture2DArray");
    engine->RegisterGlobalFunction("uint CheckMaxLevels(int, int, uint)", AS_FUNCTIONPR(Texture2DArray::CheckMaxLevels, (int, int, unsigned), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Texture::CheckMaxLevels(int width, int height, int depth, unsigned requestedLevels) | File: ../Graphics/Texture.h
    engine->SetDefaultNamespace("Texture2DArray");
    engine->RegisterGlobalFunction("uint CheckMaxLevels(int, int, int, uint)", AS_FUNCTIONPR(Texture2DArray::CheckMaxLevels, (int, int, int, unsigned), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // void GPUObject::ClearDataLost() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture2DArray", "void ClearDataLost()", AS_METHODPR(Texture2DArray, ClearDataLost, (), void), AS_CALL_THISCALL);
    // bool Texture2DArray::EndLoad() override | File: ../Graphics/Texture2DArray.h
    engine->RegisterObjectMethod("Texture2DArray", "bool EndLoad()", AS_METHODPR(Texture2DArray, EndLoad, (), bool), AS_CALL_THISCALL);
    // TextureAddressMode Texture::GetAddressMode(TextureCoordinate coord) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "TextureAddressMode GetAddressMode(TextureCoordinate) const", AS_METHODPR(Texture2DArray, GetAddressMode, (TextureCoordinate) const, TextureAddressMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "TextureAddressMode get_addressMode(TextureCoordinate) const", AS_METHODPR(Texture2DArray, GetAddressMode, (TextureCoordinate) const, TextureAddressMode), AS_CALL_THISCALL);
    // unsigned Texture::GetAnisotropy() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "uint GetAnisotropy() const", AS_METHODPR(Texture2DArray, GetAnisotropy, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "uint get_anisotropy() const", AS_METHODPR(Texture2DArray, GetAnisotropy, () const, unsigned), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(Texture2DArray, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // bool Texture::GetAutoResolve() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "bool GetAutoResolve() const", AS_METHODPR(Texture2DArray, GetAutoResolve, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "bool get_autoResolve() const", AS_METHODPR(Texture2DArray, GetAutoResolve, () const, bool), AS_CALL_THISCALL);
    // Texture* Texture::GetBackupTexture() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "Texture@+ GetBackupTexture() const", AS_METHODPR(Texture2DArray, GetBackupTexture, () const, Texture*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "Texture@+ get_backupTexture() const", AS_METHODPR(Texture2DArray, GetBackupTexture, () const, Texture*), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "bool GetBlockEvents() const", AS_METHODPR(Texture2DArray, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const Color& Texture::GetBorderColor() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "const Color& GetBorderColor() const", AS_METHODPR(Texture2DArray, GetBorderColor, () const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "const Color& get_borderColor() const", AS_METHODPR(Texture2DArray, GetBorderColor, () const, const Color&), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "const String& GetCategory() const", AS_METHODPR(Texture2DArray, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "const String& get_category() const", AS_METHODPR(Texture2DArray, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // unsigned Texture::GetComponents() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "uint GetComponents() const", AS_METHODPR(Texture2DArray, GetComponents, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "uint get_components() const", AS_METHODPR(Texture2DArray, GetComponents, () const, unsigned), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // bool Texture2DArray::GetData(unsigned layer, unsigned level, void* dest) const | File: ../Graphics/Texture2DArray.h
    // Error: type "void*" can not automatically bind
    // unsigned Texture::GetDataSize(int width, int height) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "uint GetDataSize(int, int) const", AS_METHODPR(Texture2DArray, GetDataSize, (int, int) const, unsigned), AS_CALL_THISCALL);
    // unsigned Texture::GetDataSize(int width, int height, int depth) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "uint GetDataSize(int, int, int) const", AS_METHODPR(Texture2DArray, GetDataSize, (int, int, int) const, unsigned), AS_CALL_THISCALL);
    // static unsigned Texture::GetDataType(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // int Texture::GetDepth() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "int GetDepth() const", AS_METHODPR(Texture2DArray, GetDepth, () const, int), AS_CALL_THISCALL);
    // static unsigned Texture::GetDSVFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "VariantMap& GetEventDataMap() const", AS_METHODPR(Texture2DArray, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "Object@+ GetEventSender() const", AS_METHODPR(Texture2DArray, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // static unsigned Texture::GetExternalFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // TextureFilterMode Texture::GetFilterMode() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "TextureFilterMode GetFilterMode() const", AS_METHODPR(Texture2DArray, GetFilterMode, () const, TextureFilterMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "TextureFilterMode get_filterMode() const", AS_METHODPR(Texture2DArray, GetFilterMode, () const, TextureFilterMode), AS_CALL_THISCALL);
    // unsigned Texture::GetFormat() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "uint GetFormat() const", AS_METHODPR(Texture2DArray, GetFormat, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "uint get_format() const", AS_METHODPR(Texture2DArray, GetFormat, () const, unsigned), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Texture2DArray, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Texture2DArray, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Texture2DArray, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "const VariantMap& get_globalVars() const", AS_METHODPR(Texture2DArray, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // void* GPUObject::GetGPUObject() const | File: ../Graphics/GPUObject.h
    // Error: type "void*" can not automatically bind
    // unsigned GPUObject::GetGPUObjectName() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture2DArray", "uint GetGPUObjectName() const", AS_METHODPR(Texture2DArray, GetGPUObjectName, () const, unsigned), AS_CALL_THISCALL);
    // Graphics* GPUObject::GetGraphics() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture2DArray", "Graphics@+ GetGraphics() const", AS_METHODPR(Texture2DArray, GetGraphics, () const, Graphics*), AS_CALL_THISCALL);
    // int Texture::GetHeight() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "int GetHeight() const", AS_METHODPR(Texture2DArray, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "int get_height() const", AS_METHODPR(Texture2DArray, GetHeight, () const, int), AS_CALL_THISCALL);
    // unsigned Texture2DArray::GetLayers() const | File: ../Graphics/Texture2DArray.h
    engine->RegisterObjectMethod("Texture2DArray", "uint GetLayers() const", AS_METHODPR(Texture2DArray, GetLayers, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "uint get_layers() const", AS_METHODPR(Texture2DArray, GetLayers, () const, unsigned), AS_CALL_THISCALL);
    // int Texture::GetLevelDepth(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "int GetLevelDepth(uint) const", AS_METHODPR(Texture2DArray, GetLevelDepth, (unsigned) const, int), AS_CALL_THISCALL);
    // int Texture::GetLevelHeight(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "int GetLevelHeight(uint) const", AS_METHODPR(Texture2DArray, GetLevelHeight, (unsigned) const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "int get_levelHeight(uint) const", AS_METHODPR(Texture2DArray, GetLevelHeight, (unsigned) const, int), AS_CALL_THISCALL);
    // unsigned Texture::GetLevels() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "uint GetLevels() const", AS_METHODPR(Texture2DArray, GetLevels, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "uint get_levels() const", AS_METHODPR(Texture2DArray, GetLevels, () const, unsigned), AS_CALL_THISCALL);
    // bool Texture::GetLevelsDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "bool GetLevelsDirty() const", AS_METHODPR(Texture2DArray, GetLevelsDirty, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "bool get_levelsDirty() const", AS_METHODPR(Texture2DArray, GetLevelsDirty, () const, bool), AS_CALL_THISCALL);
    // int Texture::GetLevelWidth(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "int GetLevelWidth(uint) const", AS_METHODPR(Texture2DArray, GetLevelWidth, (unsigned) const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "int get_levelWidth(uint) const", AS_METHODPR(Texture2DArray, GetLevelWidth, (unsigned) const, int), AS_CALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "uint GetMemoryUse() const", AS_METHODPR(Texture2DArray, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "uint get_memoryUse() const", AS_METHODPR(Texture2DArray, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // const Variant& ResourceWithMetadata::GetMetadata(const String& name) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "const Variant& GetMetadata(const String&in) const", AS_METHODPR(Texture2DArray, GetMetadata, (const String&) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "const Variant& get_metadata(const String&in) const", AS_METHODPR(Texture2DArray, GetMetadata, (const String&) const, const Variant&), AS_CALL_THISCALL);
    // int Texture::GetMipsToSkip(MaterialQuality quality) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "int GetMipsToSkip(MaterialQuality) const", AS_METHODPR(Texture2DArray, GetMipsToSkip, (MaterialQuality) const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "int get_mipsToSkip(MaterialQuality) const", AS_METHODPR(Texture2DArray, GetMipsToSkip, (MaterialQuality) const, int), AS_CALL_THISCALL);
    // int Texture::GetMultiSample() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "int GetMultiSample() const", AS_METHODPR(Texture2DArray, GetMultiSample, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "int get_multiSample() const", AS_METHODPR(Texture2DArray, GetMultiSample, () const, int), AS_CALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "const String& GetName() const", AS_METHODPR(Texture2DArray, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "const String& get_name() const", AS_METHODPR(Texture2DArray, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "StringHash GetNameHash() const", AS_METHODPR(Texture2DArray, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // bool Texture::GetParametersDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "bool GetParametersDirty() const", AS_METHODPR(Texture2DArray, GetParametersDirty, () const, bool), AS_CALL_THISCALL);
    // RenderSurface* Texture2DArray::GetRenderSurface() const | File: ../Graphics/Texture2DArray.h
    engine->RegisterObjectMethod("Texture2DArray", "RenderSurface@+ GetRenderSurface() const", AS_METHODPR(Texture2DArray, GetRenderSurface, () const, RenderSurface*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "RenderSurface@+ get_renderSurface() const", AS_METHODPR(Texture2DArray, GetRenderSurface, () const, RenderSurface*), AS_CALL_THISCALL);
    // void* Texture::GetResolveTexture() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // unsigned Texture::GetRowDataSize(int width) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "uint GetRowDataSize(int) const", AS_METHODPR(Texture2DArray, GetRowDataSize, (int) const, unsigned), AS_CALL_THISCALL);
    // void* Texture::GetSampler() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // void* Texture::GetShaderResourceView() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // bool Texture::GetShadowCompare() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "bool GetShadowCompare() const", AS_METHODPR(Texture2DArray, GetShadowCompare, () const, bool), AS_CALL_THISCALL);
    // bool Texture::GetSRGB() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "bool GetSRGB() const", AS_METHODPR(Texture2DArray, GetSRGB, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "bool get_sRGB() const", AS_METHODPR(Texture2DArray, GetSRGB, () const, bool), AS_CALL_THISCALL);
    // unsigned Texture::GetSRGBFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // static unsigned Texture::GetSRVFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Texture2DArray, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // unsigned Texture::GetTarget() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "uint GetTarget() const", AS_METHODPR(Texture2DArray, GetTarget, () const, unsigned), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "StringHash GetType() const", AS_METHODPR(Texture2DArray, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "StringHash get_type() const", AS_METHODPR(Texture2DArray, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "const String& GetTypeName() const", AS_METHODPR(Texture2DArray, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "const String& get_typeName() const", AS_METHODPR(Texture2DArray, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // TextureUsage Texture::GetUsage() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "TextureUsage GetUsage() const", AS_METHODPR(Texture2DArray, GetUsage, () const, TextureUsage), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "TextureUsage get_usage() const", AS_METHODPR(Texture2DArray, GetUsage, () const, TextureUsage), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "uint GetUseTimer()", AS_METHODPR(Texture2DArray, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "uint get_useTimer()", AS_METHODPR(Texture2DArray, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // int Texture::GetWidth() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "int GetWidth() const", AS_METHODPR(Texture2DArray, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "int get_width() const", AS_METHODPR(Texture2DArray, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "bool HasEventHandlers() const", AS_METHODPR(Texture2DArray, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool ResourceWithMetadata::HasMetadata() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "bool HasMetadata() const", AS_METHODPR(Texture2DArray, HasMetadata, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "bool get_hasMetadata() const", AS_METHODPR(Texture2DArray, HasMetadata, () const, bool), AS_CALL_THISCALL);
    // bool GPUObject::HasPendingData() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture2DArray", "bool HasPendingData() const", AS_METHODPR(Texture2DArray, HasPendingData, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Texture2DArray, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Texture2DArray, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Texture::IsCompressed() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "bool IsCompressed() const", AS_METHODPR(Texture2DArray, IsCompressed, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "bool get_compressed() const", AS_METHODPR(Texture2DArray, IsCompressed, () const, bool), AS_CALL_THISCALL);
    // bool GPUObject::IsDataLost() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture2DArray", "bool IsDataLost() const", AS_METHODPR(Texture2DArray, IsDataLost, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "bool get_dataLost() const", AS_METHODPR(Texture2DArray, IsDataLost, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Texture2DArray, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Texture::IsResolveDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "bool IsResolveDirty() const", AS_METHODPR(Texture2DArray, IsResolveDirty, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "bool get_resolveDirty() const", AS_METHODPR(Texture2DArray, IsResolveDirty, () const, bool), AS_CALL_THISCALL);
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "bool Load(Deserializer&)", AS_METHODPR(Texture2DArray, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "bool LoadFile(const String&in)", AS_METHODPR(Texture2DArray, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "bool Load(const String&in)", AS_METHODPR(Texture2DArray, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // void Texture2DArray::OnDeviceLost() override | File: ../Graphics/Texture2DArray.h
    engine->RegisterObjectMethod("Texture2DArray", "void OnDeviceLost()", AS_METHODPR(Texture2DArray, OnDeviceLost, (), void), AS_CALL_THISCALL);
    // void Texture2DArray::OnDeviceReset() override | File: ../Graphics/Texture2DArray.h
    engine->RegisterObjectMethod("Texture2DArray", "void OnDeviceReset()", AS_METHODPR(Texture2DArray, OnDeviceReset, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Texture2DArray, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Texture2DArray", "int Refs() const", AS_METHODPR(Texture2DArray, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "int get_refs() const", AS_METHODPR(Texture2DArray, Refs, () const, int), AS_CALL_THISCALL);
    // void Texture::RegenerateLevels() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void RegenerateLevels()", AS_METHODPR(Texture2DArray, RegenerateLevels, (), void), AS_CALL_THISCALL);
    // static void Texture2DArray::RegisterObject(Context* context) | File: ../Graphics/Texture2DArray.h
    // Not registered because have @nobind mark
    // void Texture2DArray::Release() override | File: ../Graphics/Texture2DArray.h
    engine->RegisterObjectMethod("Texture2DArray", "void Release()", AS_METHODPR(Texture2DArray, Release, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Texture2DArray", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Texture2DArray, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void ResourceWithMetadata::RemoveAllMetadata() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "void RemoveAllMetadata()", AS_METHODPR(Texture2DArray, RemoveAllMetadata, (), void), AS_CALL_THISCALL);
    // void ResourceWithMetadata::RemoveMetadata(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "void RemoveMetadata(const String&in)", AS_METHODPR(Texture2DArray, RemoveMetadata, (const String&), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "void ResetUseTimer()", AS_METHODPR(Texture2DArray, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "bool Save(Serializer&) const", AS_METHODPR(Texture2DArray, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "bool SaveFile(const String&in) const", AS_METHODPR(Texture2DArray, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "bool Save(const String&in) const", AS_METHODPR(Texture2DArray, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "void SendEvent(StringHash)", AS_METHODPR(Texture2DArray, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Texture2DArray, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Texture::SetAddressMode(TextureCoordinate coord, TextureAddressMode mode) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetAddressMode(TextureCoordinate, TextureAddressMode)", AS_METHODPR(Texture2DArray, SetAddressMode, (TextureCoordinate, TextureAddressMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "void set_addressMode(TextureCoordinate, TextureAddressMode)", AS_METHODPR(Texture2DArray, SetAddressMode, (TextureCoordinate, TextureAddressMode), void), AS_CALL_THISCALL);
    // void Texture::SetAnisotropy(unsigned level) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetAnisotropy(uint)", AS_METHODPR(Texture2DArray, SetAnisotropy, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "void set_anisotropy(uint)", AS_METHODPR(Texture2DArray, SetAnisotropy, (unsigned), void), AS_CALL_THISCALL);
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(Texture2DArray, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void Texture::SetBackupTexture(Texture* texture) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetBackupTexture(Texture@+)", AS_METHODPR(Texture2DArray, SetBackupTexture, (Texture*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "void set_backupTexture(Texture@+)", AS_METHODPR(Texture2DArray, SetBackupTexture, (Texture*), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetBlockEvents(bool)", AS_METHODPR(Texture2DArray, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Texture::SetBorderColor(const Color& color) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetBorderColor(const Color&in)", AS_METHODPR(Texture2DArray, SetBorderColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "void set_borderColor(const Color&in)", AS_METHODPR(Texture2DArray, SetBorderColor, (const Color&), void), AS_CALL_THISCALL);
    // bool Texture2DArray::SetData(unsigned layer, unsigned level, int x, int y, int width, int height, const void* data) | File: ../Graphics/Texture2DArray.h
    // Error: type "const void*" can not automatically bind
    // bool Texture2DArray::SetData(unsigned layer, Deserializer& source) | File: ../Graphics/Texture2DArray.h
    engine->RegisterObjectMethod("Texture2DArray", "bool SetData(uint, Deserializer&)", AS_METHODPR(Texture2DArray, SetData, (unsigned, Deserializer&), bool), AS_CALL_THISCALL);
    // bool Texture2DArray::SetData(unsigned layer, Image* image, bool useAlpha=false) | File: ../Graphics/Texture2DArray.h
    engine->RegisterObjectMethod("Texture2DArray", "bool SetData(uint, Image@+, bool = false)", AS_METHODPR(Texture2DArray, SetData, (unsigned, Image*, bool), bool), AS_CALL_THISCALL);
    // void Texture::SetFilterMode(TextureFilterMode mode) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetFilterMode(TextureFilterMode)", AS_METHODPR(Texture2DArray, SetFilterMode, (TextureFilterMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "void set_filterMode(TextureFilterMode)", AS_METHODPR(Texture2DArray, SetFilterMode, (TextureFilterMode), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Texture2DArray, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Texture2DArray, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Texture2DArray::SetLayers(unsigned layers) | File: ../Graphics/Texture2DArray.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetLayers(uint)", AS_METHODPR(Texture2DArray, SetLayers, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "void set_layers(uint)", AS_METHODPR(Texture2DArray, SetLayers, (unsigned), void), AS_CALL_THISCALL);
    // void Texture::SetLevelsDirty() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetLevelsDirty()", AS_METHODPR(Texture2DArray, SetLevelsDirty, (), void), AS_CALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetMemoryUse(uint)", AS_METHODPR(Texture2DArray, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void Texture::SetMipsToSkip(MaterialQuality quality, int toSkip) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetMipsToSkip(MaterialQuality, int)", AS_METHODPR(Texture2DArray, SetMipsToSkip, (MaterialQuality, int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "void set_mipsToSkip(MaterialQuality, int)", AS_METHODPR(Texture2DArray, SetMipsToSkip, (MaterialQuality, int), void), AS_CALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetName(const String&in)", AS_METHODPR(Texture2DArray, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "void set_name(const String&in)", AS_METHODPR(Texture2DArray, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Texture::SetNumLevels(unsigned levels) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetNumLevels(uint)", AS_METHODPR(Texture2DArray, SetNumLevels, (unsigned), void), AS_CALL_THISCALL);
    // void Texture::SetParameters(XMLFile* file) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetParameters(XMLFile@+)", AS_METHODPR(Texture2DArray, SetParameters, (XMLFile*), void), AS_CALL_THISCALL);
    // void Texture::SetParameters(const XMLElement& element) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetParameters(const XMLElement&in)", AS_METHODPR(Texture2DArray, SetParameters, (const XMLElement&), void), AS_CALL_THISCALL);
    // void Texture::SetParametersDirty() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetParametersDirty()", AS_METHODPR(Texture2DArray, SetParametersDirty, (), void), AS_CALL_THISCALL);
    // void Texture::SetResolveDirty(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetResolveDirty(bool)", AS_METHODPR(Texture2DArray, SetResolveDirty, (bool), void), AS_CALL_THISCALL);
    // void Texture::SetShadowCompare(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetShadowCompare(bool)", AS_METHODPR(Texture2DArray, SetShadowCompare, (bool), void), AS_CALL_THISCALL);
    // bool Texture2DArray::SetSize(unsigned layers, int width, int height, unsigned format, TextureUsage usage=TEXTURE_STATIC) | File: ../Graphics/Texture2DArray.h
    engine->RegisterObjectMethod("Texture2DArray", "bool SetSize(uint, int, int, uint, TextureUsage = TEXTURE_STATIC)", AS_METHODPR(Texture2DArray, SetSize, (unsigned, int, int, unsigned, TextureUsage), bool), AS_CALL_THISCALL);
    // void Texture::SetSRGB(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void SetSRGB(bool)", AS_METHODPR(Texture2DArray, SetSRGB, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "void set_sRGB(bool)", AS_METHODPR(Texture2DArray, SetSRGB, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit Texture2DArray::Texture2DArray(Context* context) | File: ../Graphics/Texture2DArray.h
    engine->RegisterObjectBehaviour("Texture2DArray", asBEHAVE_FACTORY, "Texture2DArray@+ f()", AS_FUNCTION(Texture2DArray_Texture2DArray_Context), AS_CALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "void UnsubscribeFromAllEvents()", AS_METHODPR(Texture2DArray, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Texture2DArray_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Texture2DArray, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Texture2DArray, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture2DArray", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Texture2DArray, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void Texture::UpdateParameters() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture2DArray", "void UpdateParameters()", AS_METHODPR(Texture2DArray, UpdateParameters, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Texture2DArray", "int WeakRefs() const", AS_METHODPR(Texture2DArray, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture2DArray", "int get_weakRefs() const", AS_METHODPR(Texture2DArray, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Texture3D", "void AddMetadata(const String&in, const Variant&in)", AS_METHODPR(Texture3D, AddMetadata, (const String&, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "void set_metadata(const String&in, const Variant&in)", AS_METHODPR(Texture3D, AddMetadata, (const String&, const Variant&), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Texture3D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Texture3D, AddRef, (), void), AS_CALL_THISCALL);
    // bool Texture3D::BeginLoad(Deserializer& source) override | File: ../Graphics/Texture3D.h
    engine->RegisterObjectMethod("Texture3D", "bool BeginLoad(Deserializer&)", AS_METHODPR(Texture3D, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // static unsigned Texture::CheckMaxLevels(int width, int height, unsigned requestedLevels) | File: ../Graphics/Texture.h
    engine->SetDefaultNamespace("Texture3D");
    engine->RegisterGlobalFunction("uint CheckMaxLevels(int, int, uint)", AS_FUNCTIONPR(Texture3D::CheckMaxLevels, (int, int, unsigned), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Texture::CheckMaxLevels(int width, int height, int depth, unsigned requestedLevels) | File: ../Graphics/Texture.h
    engine->SetDefaultNamespace("Texture3D");
    engine->RegisterGlobalFunction("uint CheckMaxLevels(int, int, int, uint)", AS_FUNCTIONPR(Texture3D::CheckMaxLevels, (int, int, int, unsigned), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // void GPUObject::ClearDataLost() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture3D", "void ClearDataLost()", AS_METHODPR(Texture3D, ClearDataLost, (), void), AS_CALL_THISCALL);
    // bool Texture3D::EndLoad() override | File: ../Graphics/Texture3D.h
    engine->RegisterObjectMethod("Texture3D", "bool EndLoad()", AS_METHODPR(Texture3D, EndLoad, (), bool), AS_CALL_THISCALL);
    // TextureAddressMode Texture::GetAddressMode(TextureCoordinate coord) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "TextureAddressMode GetAddressMode(TextureCoordinate) const", AS_METHODPR(Texture3D, GetAddressMode, (TextureCoordinate) const, TextureAddressMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "TextureAddressMode get_addressMode(TextureCoordinate) const", AS_METHODPR(Texture3D, GetAddressMode, (TextureCoordinate) const, TextureAddressMode), AS_CALL_THISCALL);
    // unsigned Texture::GetAnisotropy() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "uint GetAnisotropy() const", AS_METHODPR(Texture3D, GetAnisotropy, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "uint get_anisotropy() const", AS_METHODPR(Texture3D, GetAnisotropy, () const, unsigned), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(Texture3D, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // bool Texture::GetAutoResolve() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "bool GetAutoResolve() const", AS_METHODPR(Texture3D, GetAutoResolve, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "bool get_autoResolve() const", AS_METHODPR(Texture3D, GetAutoResolve, () const, bool), AS_CALL_THISCALL);
    // Texture* Texture::GetBackupTexture() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "Texture@+ GetBackupTexture() const", AS_METHODPR(Texture3D, GetBackupTexture, () const, Texture*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "Texture@+ get_backupTexture() const", AS_METHODPR(Texture3D, GetBackupTexture, () const, Texture*), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "bool GetBlockEvents() const", AS_METHODPR(Texture3D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const Color& Texture::GetBorderColor() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "const Color& GetBorderColor() const", AS_METHODPR(Texture3D, GetBorderColor, () const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "const Color& get_borderColor() const", AS_METHODPR(Texture3D, GetBorderColor, () const, const Color&), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "const String& GetCategory() const", AS_METHODPR(Texture3D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "const String& get_category() const", AS_METHODPR(Texture3D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // unsigned Texture::GetComponents() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "uint GetComponents() const", AS_METHODPR(Texture3D, GetComponents, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "uint get_components() const", AS_METHODPR(Texture3D, GetComponents, () const, unsigned), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // bool Texture3D::GetData(unsigned level, void* dest) const | File: ../Graphics/Texture3D.h
    // Error: type "void*" can not automatically bind
    // unsigned Texture::GetDataSize(int width, int height) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "uint GetDataSize(int, int) const", AS_METHODPR(Texture3D, GetDataSize, (int, int) const, unsigned), AS_CALL_THISCALL);
    // unsigned Texture::GetDataSize(int width, int height, int depth) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "uint GetDataSize(int, int, int) const", AS_METHODPR(Texture3D, GetDataSize, (int, int, int) const, unsigned), AS_CALL_THISCALL);
    // static unsigned Texture::GetDataType(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // int Texture::GetDepth() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "int GetDepth() const", AS_METHODPR(Texture3D, GetDepth, () const, int), AS_CALL_THISCALL);
    // static unsigned Texture::GetDSVFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "VariantMap& GetEventDataMap() const", AS_METHODPR(Texture3D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "Object@+ GetEventSender() const", AS_METHODPR(Texture3D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // static unsigned Texture::GetExternalFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // TextureFilterMode Texture::GetFilterMode() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "TextureFilterMode GetFilterMode() const", AS_METHODPR(Texture3D, GetFilterMode, () const, TextureFilterMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "TextureFilterMode get_filterMode() const", AS_METHODPR(Texture3D, GetFilterMode, () const, TextureFilterMode), AS_CALL_THISCALL);
    // unsigned Texture::GetFormat() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "uint GetFormat() const", AS_METHODPR(Texture3D, GetFormat, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "uint get_format() const", AS_METHODPR(Texture3D, GetFormat, () const, unsigned), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Texture3D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Texture3D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Texture3D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "const VariantMap& get_globalVars() const", AS_METHODPR(Texture3D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // void* GPUObject::GetGPUObject() const | File: ../Graphics/GPUObject.h
    // Error: type "void*" can not automatically bind
    // unsigned GPUObject::GetGPUObjectName() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture3D", "uint GetGPUObjectName() const", AS_METHODPR(Texture3D, GetGPUObjectName, () const, unsigned), AS_CALL_THISCALL);
    // Graphics* GPUObject::GetGraphics() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture3D", "Graphics@+ GetGraphics() const", AS_METHODPR(Texture3D, GetGraphics, () const, Graphics*), AS_CALL_THISCALL);
    // int Texture::GetHeight() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "int GetHeight() const", AS_METHODPR(Texture3D, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "int get_height() const", AS_METHODPR(Texture3D, GetHeight, () const, int), AS_CALL_THISCALL);
    // int Texture::GetLevelDepth(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "int GetLevelDepth(uint) const", AS_METHODPR(Texture3D, GetLevelDepth, (unsigned) const, int), AS_CALL_THISCALL);
    // int Texture::GetLevelHeight(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "int GetLevelHeight(uint) const", AS_METHODPR(Texture3D, GetLevelHeight, (unsigned) const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "int get_levelHeight(uint) const", AS_METHODPR(Texture3D, GetLevelHeight, (unsigned) const, int), AS_CALL_THISCALL);
    // unsigned Texture::GetLevels() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "uint GetLevels() const", AS_METHODPR(Texture3D, GetLevels, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "uint get_levels() const", AS_METHODPR(Texture3D, GetLevels, () const, unsigned), AS_CALL_THISCALL);
    // bool Texture::GetLevelsDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "bool GetLevelsDirty() const", AS_METHODPR(Texture3D, GetLevelsDirty, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "bool get_levelsDirty() const", AS_METHODPR(Texture3D, GetLevelsDirty, () const, bool), AS_CALL_THISCALL);
    // int Texture::GetLevelWidth(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "int GetLevelWidth(uint) const", AS_METHODPR(Texture3D, GetLevelWidth, (unsigned) const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "int get_levelWidth(uint) const", AS_METHODPR(Texture3D, GetLevelWidth, (unsigned) const, int), AS_CALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "uint GetMemoryUse() const", AS_METHODPR(Texture3D, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "uint get_memoryUse() const", AS_METHODPR(Texture3D, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // const Variant& ResourceWithMetadata::GetMetadata(const String& name) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "const Variant& GetMetadata(const String&in) const", AS_METHODPR(Texture3D, GetMetadata, (const String&) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "const Variant& get_metadata(const String&in) const", AS_METHODPR(Texture3D, GetMetadata, (const String&) const, const Variant&), AS_CALL_THISCALL);
    // int Texture::GetMipsToSkip(MaterialQuality quality) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "int GetMipsToSkip(MaterialQuality) const", AS_METHODPR(Texture3D, GetMipsToSkip, (MaterialQuality) const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "int get_mipsToSkip(MaterialQuality) const", AS_METHODPR(Texture3D, GetMipsToSkip, (MaterialQuality) const, int), AS_CALL_THISCALL);
    // int Texture::GetMultiSample() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "int GetMultiSample() const", AS_METHODPR(Texture3D, GetMultiSample, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "int get_multiSample() const", AS_METHODPR(Texture3D, GetMultiSample, () const, int), AS_CALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "const String& GetName() const", AS_METHODPR(Texture3D, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "const String& get_name() const", AS_METHODPR(Texture3D, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "StringHash GetNameHash() const", AS_METHODPR(Texture3D, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // bool Texture::GetParametersDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "bool GetParametersDirty() const", AS_METHODPR(Texture3D, GetParametersDirty, () const, bool), AS_CALL_THISCALL);
    // void* Texture::GetResolveTexture() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // unsigned Texture::GetRowDataSize(int width) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "uint GetRowDataSize(int) const", AS_METHODPR(Texture3D, GetRowDataSize, (int) const, unsigned), AS_CALL_THISCALL);
    // void* Texture::GetSampler() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // void* Texture::GetShaderResourceView() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // bool Texture::GetShadowCompare() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "bool GetShadowCompare() const", AS_METHODPR(Texture3D, GetShadowCompare, () const, bool), AS_CALL_THISCALL);
    // bool Texture::GetSRGB() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "bool GetSRGB() const", AS_METHODPR(Texture3D, GetSRGB, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "bool get_sRGB() const", AS_METHODPR(Texture3D, GetSRGB, () const, bool), AS_CALL_THISCALL);
    // unsigned Texture::GetSRGBFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // static unsigned Texture::GetSRVFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Texture3D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // unsigned Texture::GetTarget() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "uint GetTarget() const", AS_METHODPR(Texture3D, GetTarget, () const, unsigned), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "StringHash GetType() const", AS_METHODPR(Texture3D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "StringHash get_type() const", AS_METHODPR(Texture3D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "const String& GetTypeName() const", AS_METHODPR(Texture3D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "const String& get_typeName() const", AS_METHODPR(Texture3D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // TextureUsage Texture::GetUsage() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "TextureUsage GetUsage() const", AS_METHODPR(Texture3D, GetUsage, () const, TextureUsage), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "TextureUsage get_usage() const", AS_METHODPR(Texture3D, GetUsage, () const, TextureUsage), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "uint GetUseTimer()", AS_METHODPR(Texture3D, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "uint get_useTimer()", AS_METHODPR(Texture3D, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // int Texture::GetWidth() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "int GetWidth() const", AS_METHODPR(Texture3D, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "int get_width() const", AS_METHODPR(Texture3D, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "bool HasEventHandlers() const", AS_METHODPR(Texture3D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool ResourceWithMetadata::HasMetadata() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "bool HasMetadata() const", AS_METHODPR(Texture3D, HasMetadata, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "bool get_hasMetadata() const", AS_METHODPR(Texture3D, HasMetadata, () const, bool), AS_CALL_THISCALL);
    // bool GPUObject::HasPendingData() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture3D", "bool HasPendingData() const", AS_METHODPR(Texture3D, HasPendingData, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Texture3D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Texture3D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Texture::IsCompressed() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "bool IsCompressed() const", AS_METHODPR(Texture3D, IsCompressed, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "bool get_compressed() const", AS_METHODPR(Texture3D, IsCompressed, () const, bool), AS_CALL_THISCALL);
    // bool GPUObject::IsDataLost() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("Texture3D", "bool IsDataLost() const", AS_METHODPR(Texture3D, IsDataLost, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "bool get_dataLost() const", AS_METHODPR(Texture3D, IsDataLost, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Texture3D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Texture::IsResolveDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "bool IsResolveDirty() const", AS_METHODPR(Texture3D, IsResolveDirty, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "bool get_resolveDirty() const", AS_METHODPR(Texture3D, IsResolveDirty, () const, bool), AS_CALL_THISCALL);
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "bool Load(Deserializer&)", AS_METHODPR(Texture3D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "bool LoadFile(const String&in)", AS_METHODPR(Texture3D, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "bool Load(const String&in)", AS_METHODPR(Texture3D, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // void Texture3D::OnDeviceLost() override | File: ../Graphics/Texture3D.h
    engine->RegisterObjectMethod("Texture3D", "void OnDeviceLost()", AS_METHODPR(Texture3D, OnDeviceLost, (), void), AS_CALL_THISCALL);
    // void Texture3D::OnDeviceReset() override | File: ../Graphics/Texture3D.h
    engine->RegisterObjectMethod("Texture3D", "void OnDeviceReset()", AS_METHODPR(Texture3D, OnDeviceReset, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Texture3D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Texture3D", "int Refs() const", AS_METHODPR(Texture3D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "int get_refs() const", AS_METHODPR(Texture3D, Refs, () const, int), AS_CALL_THISCALL);
    // void Texture::RegenerateLevels() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void RegenerateLevels()", AS_METHODPR(Texture3D, RegenerateLevels, (), void), AS_CALL_THISCALL);
    // static void Texture3D::RegisterObject(Context* context) | File: ../Graphics/Texture3D.h
    // Not registered because have @nobind mark
    // void Texture3D::Release() override | File: ../Graphics/Texture3D.h
    engine->RegisterObjectMethod("Texture3D", "void Release()", AS_METHODPR(Texture3D, Release, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Texture3D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Texture3D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void ResourceWithMetadata::RemoveAllMetadata() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "void RemoveAllMetadata()", AS_METHODPR(Texture3D, RemoveAllMetadata, (), void), AS_CALL_THISCALL);
    // void ResourceWithMetadata::RemoveMetadata(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "void RemoveMetadata(const String&in)", AS_METHODPR(Texture3D, RemoveMetadata, (const String&), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "void ResetUseTimer()", AS_METHODPR(Texture3D, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "bool Save(Serializer&) const", AS_METHODPR(Texture3D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "bool SaveFile(const String&in) const", AS_METHODPR(Texture3D, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "bool Save(const String&in) const", AS_METHODPR(Texture3D, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "void SendEvent(StringHash)", AS_METHODPR(Texture3D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Texture3D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Texture::SetAddressMode(TextureCoordinate coord, TextureAddressMode mode) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetAddressMode(TextureCoordinate, TextureAddressMode)", AS_METHODPR(Texture3D, SetAddressMode, (TextureCoordinate, TextureAddressMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "void set_addressMode(TextureCoordinate, TextureAddressMode)", AS_METHODPR(Texture3D, SetAddressMode, (TextureCoordinate, TextureAddressMode), void), AS_CALL_THISCALL);
    // void Texture::SetAnisotropy(unsigned level) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetAnisotropy(uint)", AS_METHODPR(Texture3D, SetAnisotropy, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "void set_anisotropy(uint)", AS_METHODPR(Texture3D, SetAnisotropy, (unsigned), void), AS_CALL_THISCALL);
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(Texture3D, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void Texture::SetBackupTexture(Texture* texture) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetBackupTexture(Texture@+)", AS_METHODPR(Texture3D, SetBackupTexture, (Texture*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "void set_backupTexture(Texture@+)", AS_METHODPR(Texture3D, SetBackupTexture, (Texture*), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "void SetBlockEvents(bool)", AS_METHODPR(Texture3D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Texture::SetBorderColor(const Color& color) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetBorderColor(const Color&in)", AS_METHODPR(Texture3D, SetBorderColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "void set_borderColor(const Color&in)", AS_METHODPR(Texture3D, SetBorderColor, (const Color&), void), AS_CALL_THISCALL);
    // bool Texture3D::SetData(unsigned level, int x, int y, int z, int width, int height, int depth, const void* data) | File: ../Graphics/Texture3D.h
    // Error: type "const void*" can not automatically bind
    // bool Texture3D::SetData(Image* image, bool useAlpha=false) | File: ../Graphics/Texture3D.h
    engine->RegisterObjectMethod("Texture3D", "bool SetData(Image@+, bool = false)", AS_METHODPR(Texture3D, SetData, (Image*, bool), bool), AS_CALL_THISCALL);
    // void Texture::SetFilterMode(TextureFilterMode mode) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetFilterMode(TextureFilterMode)", AS_METHODPR(Texture3D, SetFilterMode, (TextureFilterMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "void set_filterMode(TextureFilterMode)", AS_METHODPR(Texture3D, SetFilterMode, (TextureFilterMode), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Texture3D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Texture3D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Texture::SetLevelsDirty() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetLevelsDirty()", AS_METHODPR(Texture3D, SetLevelsDirty, (), void), AS_CALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "void SetMemoryUse(uint)", AS_METHODPR(Texture3D, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void Texture::SetMipsToSkip(MaterialQuality quality, int toSkip) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetMipsToSkip(MaterialQuality, int)", AS_METHODPR(Texture3D, SetMipsToSkip, (MaterialQuality, int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "void set_mipsToSkip(MaterialQuality, int)", AS_METHODPR(Texture3D, SetMipsToSkip, (MaterialQuality, int), void), AS_CALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Texture3D", "void SetName(const String&in)", AS_METHODPR(Texture3D, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "void set_name(const String&in)", AS_METHODPR(Texture3D, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Texture::SetNumLevels(unsigned levels) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetNumLevels(uint)", AS_METHODPR(Texture3D, SetNumLevels, (unsigned), void), AS_CALL_THISCALL);
    // void Texture::SetParameters(XMLFile* file) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetParameters(XMLFile@+)", AS_METHODPR(Texture3D, SetParameters, (XMLFile*), void), AS_CALL_THISCALL);
    // void Texture::SetParameters(const XMLElement& element) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetParameters(const XMLElement&in)", AS_METHODPR(Texture3D, SetParameters, (const XMLElement&), void), AS_CALL_THISCALL);
    // void Texture::SetParametersDirty() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetParametersDirty()", AS_METHODPR(Texture3D, SetParametersDirty, (), void), AS_CALL_THISCALL);
    // void Texture::SetResolveDirty(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetResolveDirty(bool)", AS_METHODPR(Texture3D, SetResolveDirty, (bool), void), AS_CALL_THISCALL);
    // void Texture::SetShadowCompare(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetShadowCompare(bool)", AS_METHODPR(Texture3D, SetShadowCompare, (bool), void), AS_CALL_THISCALL);
    // bool Texture3D::SetSize(int width, int height, int depth, unsigned format, TextureUsage usage=TEXTURE_STATIC) | File: ../Graphics/Texture3D.h
    engine->RegisterObjectMethod("Texture3D", "bool SetSize(int, int, int, uint, TextureUsage = TEXTURE_STATIC)", AS_METHODPR(Texture3D, SetSize, (int, int, int, unsigned, TextureUsage), bool), AS_CALL_THISCALL);
    // void Texture::SetSRGB(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void SetSRGB(bool)", AS_METHODPR(Texture3D, SetSRGB, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "void set_sRGB(bool)", AS_METHODPR(Texture3D, SetSRGB, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit Texture3D::Texture3D(Context* context) | File: ../Graphics/Texture3D.h
    engine->RegisterObjectBehaviour("Texture3D", asBEHAVE_FACTORY, "Texture3D@+ f()", AS_FUNCTION(Texture3D_Texture3D_Context), AS_CALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "void UnsubscribeFromAllEvents()", AS_METHODPR(Texture3D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Texture3D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Texture3D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Texture3D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Texture3D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Texture3D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void Texture::UpdateParameters() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("Texture3D", "void UpdateParameters()", AS_METHODPR(Texture3D, UpdateParameters, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Texture3D", "int WeakRefs() const", AS_METHODPR(Texture3D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Texture3D", "int get_weakRefs() const", AS_METHODPR(Texture3D, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("TextureCube", "void AddMetadata(const String&in, const Variant&in)", AS_METHODPR(TextureCube, AddMetadata, (const String&, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "void set_metadata(const String&in, const Variant&in)", AS_METHODPR(TextureCube, AddMetadata, (const String&, const Variant&), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TextureCube", asBEHAVE_ADDREF, "void f()", AS_METHODPR(TextureCube, AddRef, (), void), AS_CALL_THISCALL);
    // bool TextureCube::BeginLoad(Deserializer& source) override | File: ../Graphics/TextureCube.h
    engine->RegisterObjectMethod("TextureCube", "bool BeginLoad(Deserializer&)", AS_METHODPR(TextureCube, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // static unsigned Texture::CheckMaxLevels(int width, int height, unsigned requestedLevels) | File: ../Graphics/Texture.h
    engine->SetDefaultNamespace("TextureCube");
    engine->RegisterGlobalFunction("uint CheckMaxLevels(int, int, uint)", AS_FUNCTIONPR(TextureCube::CheckMaxLevels, (int, int, unsigned), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Texture::CheckMaxLevels(int width, int height, int depth, unsigned requestedLevels) | File: ../Graphics/Texture.h
    engine->SetDefaultNamespace("TextureCube");
    engine->RegisterGlobalFunction("uint CheckMaxLevels(int, int, int, uint)", AS_FUNCTIONPR(TextureCube::CheckMaxLevels, (int, int, int, unsigned), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // void GPUObject::ClearDataLost() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("TextureCube", "void ClearDataLost()", AS_METHODPR(TextureCube, ClearDataLost, (), void), AS_CALL_THISCALL);
    // bool TextureCube::EndLoad() override | File: ../Graphics/TextureCube.h
    engine->RegisterObjectMethod("TextureCube", "bool EndLoad()", AS_METHODPR(TextureCube, EndLoad, (), bool), AS_CALL_THISCALL);
    // TextureAddressMode Texture::GetAddressMode(TextureCoordinate coord) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "TextureAddressMode GetAddressMode(TextureCoordinate) const", AS_METHODPR(TextureCube, GetAddressMode, (TextureCoordinate) const, TextureAddressMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "TextureAddressMode get_addressMode(TextureCoordinate) const", AS_METHODPR(TextureCube, GetAddressMode, (TextureCoordinate) const, TextureAddressMode), AS_CALL_THISCALL);
    // unsigned Texture::GetAnisotropy() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "uint GetAnisotropy() const", AS_METHODPR(TextureCube, GetAnisotropy, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "uint get_anisotropy() const", AS_METHODPR(TextureCube, GetAnisotropy, () const, unsigned), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(TextureCube, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // bool Texture::GetAutoResolve() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "bool GetAutoResolve() const", AS_METHODPR(TextureCube, GetAutoResolve, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "bool get_autoResolve() const", AS_METHODPR(TextureCube, GetAutoResolve, () const, bool), AS_CALL_THISCALL);
    // Texture* Texture::GetBackupTexture() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "Texture@+ GetBackupTexture() const", AS_METHODPR(TextureCube, GetBackupTexture, () const, Texture*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "Texture@+ get_backupTexture() const", AS_METHODPR(TextureCube, GetBackupTexture, () const, Texture*), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "bool GetBlockEvents() const", AS_METHODPR(TextureCube, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const Color& Texture::GetBorderColor() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "const Color& GetBorderColor() const", AS_METHODPR(TextureCube, GetBorderColor, () const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "const Color& get_borderColor() const", AS_METHODPR(TextureCube, GetBorderColor, () const, const Color&), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "const String& GetCategory() const", AS_METHODPR(TextureCube, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "const String& get_category() const", AS_METHODPR(TextureCube, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // unsigned Texture::GetComponents() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "uint GetComponents() const", AS_METHODPR(TextureCube, GetComponents, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "uint get_components() const", AS_METHODPR(TextureCube, GetComponents, () const, unsigned), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // bool TextureCube::GetData(CubeMapFace face, unsigned level, void* dest) const | File: ../Graphics/TextureCube.h
    // Error: type "void*" can not automatically bind
    // unsigned Texture::GetDataSize(int width, int height) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "uint GetDataSize(int, int) const", AS_METHODPR(TextureCube, GetDataSize, (int, int) const, unsigned), AS_CALL_THISCALL);
    // unsigned Texture::GetDataSize(int width, int height, int depth) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "uint GetDataSize(int, int, int) const", AS_METHODPR(TextureCube, GetDataSize, (int, int, int) const, unsigned), AS_CALL_THISCALL);
    // static unsigned Texture::GetDataType(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // int Texture::GetDepth() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "int GetDepth() const", AS_METHODPR(TextureCube, GetDepth, () const, int), AS_CALL_THISCALL);
    // static unsigned Texture::GetDSVFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "VariantMap& GetEventDataMap() const", AS_METHODPR(TextureCube, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "Object@+ GetEventSender() const", AS_METHODPR(TextureCube, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // static unsigned Texture::GetExternalFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // TextureFilterMode Texture::GetFilterMode() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "TextureFilterMode GetFilterMode() const", AS_METHODPR(TextureCube, GetFilterMode, () const, TextureFilterMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "TextureFilterMode get_filterMode() const", AS_METHODPR(TextureCube, GetFilterMode, () const, TextureFilterMode), AS_CALL_THISCALL);
    // unsigned Texture::GetFormat() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "uint GetFormat() const", AS_METHODPR(TextureCube, GetFormat, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "uint get_format() const", AS_METHODPR(TextureCube, GetFormat, () const, unsigned), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(TextureCube, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(TextureCube, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "const VariantMap& GetGlobalVars() const", AS_METHODPR(TextureCube, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "const VariantMap& get_globalVars() const", AS_METHODPR(TextureCube, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // void* GPUObject::GetGPUObject() const | File: ../Graphics/GPUObject.h
    // Error: type "void*" can not automatically bind
    // unsigned GPUObject::GetGPUObjectName() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("TextureCube", "uint GetGPUObjectName() const", AS_METHODPR(TextureCube, GetGPUObjectName, () const, unsigned), AS_CALL_THISCALL);
    // Graphics* GPUObject::GetGraphics() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("TextureCube", "Graphics@+ GetGraphics() const", AS_METHODPR(TextureCube, GetGraphics, () const, Graphics*), AS_CALL_THISCALL);
    // int Texture::GetHeight() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "int GetHeight() const", AS_METHODPR(TextureCube, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "int get_height() const", AS_METHODPR(TextureCube, GetHeight, () const, int), AS_CALL_THISCALL);
    // SharedPtr<Image> TextureCube::GetImage(CubeMapFace face) const | File: ../Graphics/TextureCube.h
    engine->RegisterObjectMethod("TextureCube", "Image@+ GetImage(CubeMapFace) const", AS_FUNCTION_OBJFIRST(TextureCube_GetImage_CubeMapFace), AS_CALL_CDECL_OBJFIRST);
    // int Texture::GetLevelDepth(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "int GetLevelDepth(uint) const", AS_METHODPR(TextureCube, GetLevelDepth, (unsigned) const, int), AS_CALL_THISCALL);
    // int Texture::GetLevelHeight(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "int GetLevelHeight(uint) const", AS_METHODPR(TextureCube, GetLevelHeight, (unsigned) const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "int get_levelHeight(uint) const", AS_METHODPR(TextureCube, GetLevelHeight, (unsigned) const, int), AS_CALL_THISCALL);
    // unsigned Texture::GetLevels() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "uint GetLevels() const", AS_METHODPR(TextureCube, GetLevels, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "uint get_levels() const", AS_METHODPR(TextureCube, GetLevels, () const, unsigned), AS_CALL_THISCALL);
    // bool Texture::GetLevelsDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "bool GetLevelsDirty() const", AS_METHODPR(TextureCube, GetLevelsDirty, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "bool get_levelsDirty() const", AS_METHODPR(TextureCube, GetLevelsDirty, () const, bool), AS_CALL_THISCALL);
    // int Texture::GetLevelWidth(unsigned level) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "int GetLevelWidth(uint) const", AS_METHODPR(TextureCube, GetLevelWidth, (unsigned) const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "int get_levelWidth(uint) const", AS_METHODPR(TextureCube, GetLevelWidth, (unsigned) const, int), AS_CALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "uint GetMemoryUse() const", AS_METHODPR(TextureCube, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "uint get_memoryUse() const", AS_METHODPR(TextureCube, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // const Variant& ResourceWithMetadata::GetMetadata(const String& name) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "const Variant& GetMetadata(const String&in) const", AS_METHODPR(TextureCube, GetMetadata, (const String&) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "const Variant& get_metadata(const String&in) const", AS_METHODPR(TextureCube, GetMetadata, (const String&) const, const Variant&), AS_CALL_THISCALL);
    // int Texture::GetMipsToSkip(MaterialQuality quality) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "int GetMipsToSkip(MaterialQuality) const", AS_METHODPR(TextureCube, GetMipsToSkip, (MaterialQuality) const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "int get_mipsToSkip(MaterialQuality) const", AS_METHODPR(TextureCube, GetMipsToSkip, (MaterialQuality) const, int), AS_CALL_THISCALL);
    // int Texture::GetMultiSample() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "int GetMultiSample() const", AS_METHODPR(TextureCube, GetMultiSample, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "int get_multiSample() const", AS_METHODPR(TextureCube, GetMultiSample, () const, int), AS_CALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "const String& GetName() const", AS_METHODPR(TextureCube, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "const String& get_name() const", AS_METHODPR(TextureCube, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "StringHash GetNameHash() const", AS_METHODPR(TextureCube, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // bool Texture::GetParametersDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "bool GetParametersDirty() const", AS_METHODPR(TextureCube, GetParametersDirty, () const, bool), AS_CALL_THISCALL);
    // RenderSurface* TextureCube::GetRenderSurface(CubeMapFace face) const | File: ../Graphics/TextureCube.h
    engine->RegisterObjectMethod("TextureCube", "RenderSurface@+ GetRenderSurface(CubeMapFace) const", AS_METHODPR(TextureCube, GetRenderSurface, (CubeMapFace) const, RenderSurface*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "RenderSurface@+ get_renderSurfaces(CubeMapFace) const", AS_METHODPR(TextureCube, GetRenderSurface, (CubeMapFace) const, RenderSurface*), AS_CALL_THISCALL);
    // void* Texture::GetResolveTexture() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // unsigned Texture::GetRowDataSize(int width) const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "uint GetRowDataSize(int) const", AS_METHODPR(TextureCube, GetRowDataSize, (int) const, unsigned), AS_CALL_THISCALL);
    // void* Texture::GetSampler() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // void* Texture::GetShaderResourceView() const | File: ../Graphics/Texture.h
    // Error: type "void*" can not automatically bind
    // bool Texture::GetShadowCompare() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "bool GetShadowCompare() const", AS_METHODPR(TextureCube, GetShadowCompare, () const, bool), AS_CALL_THISCALL);
    // bool Texture::GetSRGB() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "bool GetSRGB() const", AS_METHODPR(TextureCube, GetSRGB, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "bool get_sRGB() const", AS_METHODPR(TextureCube, GetSRGB, () const, bool), AS_CALL_THISCALL);
    // unsigned Texture::GetSRGBFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // static unsigned Texture::GetSRVFormat(unsigned format) | File: ../Graphics/Texture.h
    // Not registered because have @nobind mark
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(TextureCube, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // unsigned Texture::GetTarget() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "uint GetTarget() const", AS_METHODPR(TextureCube, GetTarget, () const, unsigned), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "StringHash GetType() const", AS_METHODPR(TextureCube, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "StringHash get_type() const", AS_METHODPR(TextureCube, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "const String& GetTypeName() const", AS_METHODPR(TextureCube, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "const String& get_typeName() const", AS_METHODPR(TextureCube, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // TextureUsage Texture::GetUsage() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "TextureUsage GetUsage() const", AS_METHODPR(TextureCube, GetUsage, () const, TextureUsage), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "TextureUsage get_usage() const", AS_METHODPR(TextureCube, GetUsage, () const, TextureUsage), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "uint GetUseTimer()", AS_METHODPR(TextureCube, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "uint get_useTimer()", AS_METHODPR(TextureCube, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // int Texture::GetWidth() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "int GetWidth() const", AS_METHODPR(TextureCube, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "int get_width() const", AS_METHODPR(TextureCube, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "bool HasEventHandlers() const", AS_METHODPR(TextureCube, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool ResourceWithMetadata::HasMetadata() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "bool HasMetadata() const", AS_METHODPR(TextureCube, HasMetadata, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "bool get_hasMetadata() const", AS_METHODPR(TextureCube, HasMetadata, () const, bool), AS_CALL_THISCALL);
    // bool GPUObject::HasPendingData() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("TextureCube", "bool HasPendingData() const", AS_METHODPR(TextureCube, HasPendingData, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(TextureCube, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(TextureCube, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Texture::IsCompressed() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "bool IsCompressed() const", AS_METHODPR(TextureCube, IsCompressed, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "bool get_compressed() const", AS_METHODPR(TextureCube, IsCompressed, () const, bool), AS_CALL_THISCALL);
    // bool GPUObject::IsDataLost() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("TextureCube", "bool IsDataLost() const", AS_METHODPR(TextureCube, IsDataLost, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "bool get_dataLost() const", AS_METHODPR(TextureCube, IsDataLost, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "bool IsInstanceOf(StringHash) const", AS_METHODPR(TextureCube, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Texture::IsResolveDirty() const | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "bool IsResolveDirty() const", AS_METHODPR(TextureCube, IsResolveDirty, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "bool get_resolveDirty() const", AS_METHODPR(TextureCube, IsResolveDirty, () const, bool), AS_CALL_THISCALL);
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "bool Load(Deserializer&)", AS_METHODPR(TextureCube, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "bool LoadFile(const String&in)", AS_METHODPR(TextureCube, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "bool Load(const String&in)", AS_METHODPR(TextureCube, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // void TextureCube::OnDeviceLost() override | File: ../Graphics/TextureCube.h
    engine->RegisterObjectMethod("TextureCube", "void OnDeviceLost()", AS_METHODPR(TextureCube, OnDeviceLost, (), void), AS_CALL_THISCALL);
    // void TextureCube::OnDeviceReset() override | File: ../Graphics/TextureCube.h
    engine->RegisterObjectMethod("TextureCube", "void OnDeviceReset()", AS_METHODPR(TextureCube, OnDeviceReset, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(TextureCube, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TextureCube", "int Refs() const", AS_METHODPR(TextureCube, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "int get_refs() const", AS_METHODPR(TextureCube, Refs, () const, int), AS_CALL_THISCALL);
    // void Texture::RegenerateLevels() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void RegenerateLevels()", AS_METHODPR(TextureCube, RegenerateLevels, (), void), AS_CALL_THISCALL);
    // static void TextureCube::RegisterObject(Context* context) | File: ../Graphics/TextureCube.h
    // Not registered because have @nobind mark
    // void TextureCube::Release() override | File: ../Graphics/TextureCube.h
    engine->RegisterObjectMethod("TextureCube", "void Release()", AS_METHODPR(TextureCube, Release, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TextureCube", asBEHAVE_RELEASE, "void f()", AS_METHODPR(TextureCube, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void ResourceWithMetadata::RemoveAllMetadata() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "void RemoveAllMetadata()", AS_METHODPR(TextureCube, RemoveAllMetadata, (), void), AS_CALL_THISCALL);
    // void ResourceWithMetadata::RemoveMetadata(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "void RemoveMetadata(const String&in)", AS_METHODPR(TextureCube, RemoveMetadata, (const String&), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "void ResetUseTimer()", AS_METHODPR(TextureCube, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "bool Save(Serializer&) const", AS_METHODPR(TextureCube, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "bool SaveFile(const String&in) const", AS_METHODPR(TextureCube, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "bool Save(const String&in) const", AS_METHODPR(TextureCube, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "void SendEvent(StringHash)", AS_METHODPR(TextureCube, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(TextureCube, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Texture::SetAddressMode(TextureCoordinate coord, TextureAddressMode mode) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetAddressMode(TextureCoordinate, TextureAddressMode)", AS_METHODPR(TextureCube, SetAddressMode, (TextureCoordinate, TextureAddressMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "void set_addressMode(TextureCoordinate, TextureAddressMode)", AS_METHODPR(TextureCube, SetAddressMode, (TextureCoordinate, TextureAddressMode), void), AS_CALL_THISCALL);
    // void Texture::SetAnisotropy(unsigned level) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetAnisotropy(uint)", AS_METHODPR(TextureCube, SetAnisotropy, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "void set_anisotropy(uint)", AS_METHODPR(TextureCube, SetAnisotropy, (unsigned), void), AS_CALL_THISCALL);
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(TextureCube, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void Texture::SetBackupTexture(Texture* texture) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetBackupTexture(Texture@+)", AS_METHODPR(TextureCube, SetBackupTexture, (Texture*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "void set_backupTexture(Texture@+)", AS_METHODPR(TextureCube, SetBackupTexture, (Texture*), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "void SetBlockEvents(bool)", AS_METHODPR(TextureCube, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Texture::SetBorderColor(const Color& color) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetBorderColor(const Color&in)", AS_METHODPR(TextureCube, SetBorderColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "void set_borderColor(const Color&in)", AS_METHODPR(TextureCube, SetBorderColor, (const Color&), void), AS_CALL_THISCALL);
    // bool TextureCube::SetData(CubeMapFace face, unsigned level, int x, int y, int width, int height, const void* data) | File: ../Graphics/TextureCube.h
    // Error: type "const void*" can not automatically bind
    // bool TextureCube::SetData(CubeMapFace face, Deserializer& source) | File: ../Graphics/TextureCube.h
    engine->RegisterObjectMethod("TextureCube", "bool SetData(CubeMapFace, Deserializer&)", AS_METHODPR(TextureCube, SetData, (CubeMapFace, Deserializer&), bool), AS_CALL_THISCALL);
    // bool TextureCube::SetData(CubeMapFace face, Image* image, bool useAlpha=false) | File: ../Graphics/TextureCube.h
    engine->RegisterObjectMethod("TextureCube", "bool SetData(CubeMapFace, Image@+, bool = false)", AS_METHODPR(TextureCube, SetData, (CubeMapFace, Image*, bool), bool), AS_CALL_THISCALL);
    // void Texture::SetFilterMode(TextureFilterMode mode) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetFilterMode(TextureFilterMode)", AS_METHODPR(TextureCube, SetFilterMode, (TextureFilterMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "void set_filterMode(TextureFilterMode)", AS_METHODPR(TextureCube, SetFilterMode, (TextureFilterMode), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(TextureCube, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(TextureCube, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Texture::SetLevelsDirty() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetLevelsDirty()", AS_METHODPR(TextureCube, SetLevelsDirty, (), void), AS_CALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "void SetMemoryUse(uint)", AS_METHODPR(TextureCube, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void Texture::SetMipsToSkip(MaterialQuality quality, int toSkip) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetMipsToSkip(MaterialQuality, int)", AS_METHODPR(TextureCube, SetMipsToSkip, (MaterialQuality, int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "void set_mipsToSkip(MaterialQuality, int)", AS_METHODPR(TextureCube, SetMipsToSkip, (MaterialQuality, int), void), AS_CALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TextureCube", "void SetName(const String&in)", AS_METHODPR(TextureCube, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "void set_name(const String&in)", AS_METHODPR(TextureCube, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Texture::SetNumLevels(unsigned levels) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetNumLevels(uint)", AS_METHODPR(TextureCube, SetNumLevels, (unsigned), void), AS_CALL_THISCALL);
    // void Texture::SetParameters(XMLFile* file) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetParameters(XMLFile@+)", AS_METHODPR(TextureCube, SetParameters, (XMLFile*), void), AS_CALL_THISCALL);
    // void Texture::SetParameters(const XMLElement& element) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetParameters(const XMLElement&in)", AS_METHODPR(TextureCube, SetParameters, (const XMLElement&), void), AS_CALL_THISCALL);
    // void Texture::SetParametersDirty() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetParametersDirty()", AS_METHODPR(TextureCube, SetParametersDirty, (), void), AS_CALL_THISCALL);
    // void Texture::SetResolveDirty(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetResolveDirty(bool)", AS_METHODPR(TextureCube, SetResolveDirty, (bool), void), AS_CALL_THISCALL);
    // void Texture::SetShadowCompare(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetShadowCompare(bool)", AS_METHODPR(TextureCube, SetShadowCompare, (bool), void), AS_CALL_THISCALL);
    // bool TextureCube::SetSize(int size, unsigned format, TextureUsage usage=TEXTURE_STATIC, int multiSample=1) | File: ../Graphics/TextureCube.h
    engine->RegisterObjectMethod("TextureCube", "bool SetSize(int, uint, TextureUsage = TEXTURE_STATIC, int = 1)", AS_METHODPR(TextureCube, SetSize, (int, unsigned, TextureUsage, int), bool), AS_CALL_THISCALL);
    // void Texture::SetSRGB(bool enable) | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void SetSRGB(bool)", AS_METHODPR(TextureCube, SetSRGB, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "void set_sRGB(bool)", AS_METHODPR(TextureCube, SetSRGB, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit TextureCube::TextureCube(Context* context) | File: ../Graphics/TextureCube.h
    engine->RegisterObjectBehaviour("TextureCube", asBEHAVE_FACTORY, "TextureCube@+ f()", AS_FUNCTION(TextureCube_TextureCube_Context), AS_CALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "void UnsubscribeFromAllEvents()", AS_METHODPR(TextureCube, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(TextureCube_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(TextureCube, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(TextureCube, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TextureCube", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(TextureCube, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void Texture::UpdateParameters() | File: ../Graphics/Texture.h
    engine->RegisterObjectMethod("TextureCube", "void UpdateParameters()", AS_METHODPR(TextureCube, UpdateParameters, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TextureCube", "int WeakRefs() const", AS_METHODPR(TextureCube, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TextureCube", "int get_weakRefs() const", AS_METHODPR(TextureCube, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("Tile2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Tile2D, AddRef, (), void), AS_CALL_THISCALL);
    // bool Tile2D::GetFlipX() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("Tile2D", "bool GetFlipX() const", AS_METHODPR(Tile2D, GetFlipX, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Tile2D", "bool get_flipX() const", AS_METHODPR(Tile2D, GetFlipX, () const, bool), AS_CALL_THISCALL);
    // bool Tile2D::GetFlipY() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("Tile2D", "bool GetFlipY() const", AS_METHODPR(Tile2D, GetFlipY, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Tile2D", "bool get_flipY() const", AS_METHODPR(Tile2D, GetFlipY, () const, bool), AS_CALL_THISCALL);
    // unsigned Tile2D::GetGid() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("Tile2D", "uint GetGid() const", AS_METHODPR(Tile2D, GetGid, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Tile2D", "uint get_gid() const", AS_METHODPR(Tile2D, GetGid, () const, unsigned), AS_CALL_THISCALL);
    // const String& Tile2D::GetProperty(const String& name) const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("Tile2D", "const String& GetProperty(const String&in) const", AS_METHODPR(Tile2D, GetProperty, (const String&) const, const String&), AS_CALL_THISCALL);
    // Sprite2D* Tile2D::GetSprite() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("Tile2D", "Sprite2D@+ GetSprite() const", AS_METHODPR(Tile2D, GetSprite, () const, Sprite2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Tile2D", "Sprite2D@+ get_sprite() const", AS_METHODPR(Tile2D, GetSprite, () const, Sprite2D*), AS_CALL_THISCALL);
    // bool Tile2D::GetSwapXY() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("Tile2D", "bool GetSwapXY() const", AS_METHODPR(Tile2D, GetSwapXY, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Tile2D", "bool get_swapXY() const", AS_METHODPR(Tile2D, GetSwapXY, () const, bool), AS_CALL_THISCALL);
    // bool Tile2D::HasProperty(const String& name) const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("Tile2D", "bool HasProperty(const String&in) const", AS_METHODPR(Tile2D, HasProperty, (const String&) const, bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Tile2D", "int Refs() const", AS_METHODPR(Tile2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Tile2D", "int get_refs() const", AS_METHODPR(Tile2D, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Tile2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Tile2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Tile2D", "int WeakRefs() const", AS_METHODPR(Tile2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Tile2D", "int get_weakRefs() const", AS_METHODPR(Tile2D, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("TileMap2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(TileMap2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "void AllocateNetworkState()", AS_METHODPR(TileMap2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "void ApplyAttributes()", AS_METHODPR(TileMap2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void TileMap2D::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectMethod("TileMap2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(TileMap2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // void TileMap2D::DrawDebugGeometry() | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectMethod("TileMap2D", "void DrawDebugGeometry()", AS_METHODPR(TileMap2D, DrawDebugGeometry, (), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "bool GetAnimationEnabled() const", AS_METHODPR(TileMap2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "bool get_animationEnabled() const", AS_METHODPR(TileMap2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "Variant GetAttribute(uint) const", AS_METHODPR(TileMap2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "Variant get_attributes(uint) const", AS_METHODPR(TileMap2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(TileMap2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(TileMap2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(TileMap2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(TileMap2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(TileMap2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(TileMap2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(TileMap2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(TileMap2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "bool GetBlockEvents() const", AS_METHODPR(TileMap2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "const String& GetCategory() const", AS_METHODPR(TileMap2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "const String& get_category() const", AS_METHODPR(TileMap2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(TileMap2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("TileMap2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(TileMap2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "Object@+ GetEventSender() const", AS_METHODPR(TileMap2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(TileMap2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(TileMap2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(TileMap2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "const VariantMap& get_globalVars() const", AS_METHODPR(TileMap2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "uint GetID() const", AS_METHODPR(TileMap2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "uint get_id() const", AS_METHODPR(TileMap2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // const TileMapInfo2D& TileMap2D::GetInfo() const | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectMethod("TileMap2D", "const TileMapInfo2D& GetInfo() const", AS_METHODPR(TileMap2D, GetInfo, () const, const TileMapInfo2D&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "const TileMapInfo2D& get_info() const", AS_METHODPR(TileMap2D, GetInfo, () const, const TileMapInfo2D&), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(TileMap2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // TileMapLayer2D* TileMap2D::GetLayer(unsigned index) const | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectMethod("TileMap2D", "TileMapLayer2D@+ GetLayer(uint) const", AS_METHODPR(TileMap2D, GetLayer, (unsigned) const, TileMapLayer2D*), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "Node@+ GetNode() const", AS_METHODPR(TileMap2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "Node@+ get_node() const", AS_METHODPR(TileMap2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "uint GetNumAttributes() const", AS_METHODPR(TileMap2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "uint get_numAttributes() const", AS_METHODPR(TileMap2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned TileMap2D::GetNumLayers() const | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectMethod("TileMap2D", "uint GetNumLayers() const", AS_METHODPR(TileMap2D, GetNumLayers, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "uint get_numLayers() const", AS_METHODPR(TileMap2D, GetNumLayers, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(TileMap2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(TileMap2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(TileMap2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(TileMap2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "Scene@+ GetScene() const", AS_METHODPR(TileMap2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(TileMap2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // Vector<SharedPtr<TileMapObject2D>> TileMap2D::GetTileCollisionShapes(unsigned gid) const | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectMethod("TileMap2D", "Array<TileMapObject2D@>@ GetTileCollisionShapes(uint) const", AS_FUNCTION_OBJFIRST(TileMap2D_GetTileCollisionShapes_unsigned), AS_CALL_CDECL_OBJFIRST);
    // TmxFile2D* TileMap2D::GetTmxFile() const | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectMethod("TileMap2D", "TmxFile2D@+ GetTmxFile() const", AS_METHODPR(TileMap2D, GetTmxFile, () const, TmxFile2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "TmxFile2D@+ get_tmxFile() const", AS_METHODPR(TileMap2D, GetTmxFile, () const, TmxFile2D*), AS_CALL_THISCALL);
    // ResourceRef TileMap2D::GetTmxFileAttr() const | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectMethod("TileMap2D", "ResourceRef GetTmxFileAttr() const", AS_METHODPR(TileMap2D, GetTmxFileAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "StringHash GetType() const", AS_METHODPR(TileMap2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "StringHash get_type() const", AS_METHODPR(TileMap2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "const String& GetTypeName() const", AS_METHODPR(TileMap2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "const String& get_typeName() const", AS_METHODPR(TileMap2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "bool HasEventHandlers() const", AS_METHODPR(TileMap2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(TileMap2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(TileMap2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "bool IsEnabled() const", AS_METHODPR(TileMap2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "bool get_enabled() const", AS_METHODPR(TileMap2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "bool IsEnabledEffective() const", AS_METHODPR(TileMap2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "bool get_enabledEffective() const", AS_METHODPR(TileMap2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(TileMap2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "bool IsReplicated() const", AS_METHODPR(TileMap2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "bool get_replicated() const", AS_METHODPR(TileMap2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "bool IsTemporary() const", AS_METHODPR(TileMap2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "bool get_temporary() const", AS_METHODPR(TileMap2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "bool Load(Deserializer&)", AS_METHODPR(TileMap2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(TileMap2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(TileMap2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "void MarkNetworkUpdate()", AS_METHODPR(TileMap2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(TileMap2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(TileMap2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(TileMap2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "void OnSetEnabled()", AS_METHODPR(TileMap2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // bool TileMap2D::PositionToTileIndex(int& x, int& y, const Vector2& position) const | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectMethod("TileMap2D", "bool PositionToTileIndex(int&, int&, const Vector2&in) const", AS_METHODPR(TileMap2D, PositionToTileIndex, (int&, int&, const Vector2&) const, bool), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "void PrepareNetworkUpdate()", AS_METHODPR(TileMap2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(TileMap2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(TileMap2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TileMap2D", "int Refs() const", AS_METHODPR(TileMap2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "int get_refs() const", AS_METHODPR(TileMap2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void TileMap2D::RegisterObject(Context* context) | File: ../Urho2D/TileMap2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TileMap2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(TileMap2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "void Remove()", AS_METHODPR(TileMap2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(TileMap2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "void RemoveInstanceDefault()", AS_METHODPR(TileMap2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "void RemoveObjectAnimation()", AS_METHODPR(TileMap2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "void ResetToDefault()", AS_METHODPR(TileMap2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "bool Save(Serializer&) const", AS_METHODPR(TileMap2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "bool SaveDefaultAttributes() const", AS_METHODPR(TileMap2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(TileMap2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(TileMap2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "void SendEvent(StringHash)", AS_METHODPR(TileMap2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(TileMap2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "void SetAnimationEnabled(bool)", AS_METHODPR(TileMap2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "void set_animationEnabled(bool)", AS_METHODPR(TileMap2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "void SetAnimationTime(float)", AS_METHODPR(TileMap2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(TileMap2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(TileMap2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(TileMap2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(TileMap2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(TileMap2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(TileMap2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(TileMap2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "void SetBlockEvents(bool)", AS_METHODPR(TileMap2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMap2D", "void SetEnabled(bool)", AS_METHODPR(TileMap2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "void set_enabled(bool)", AS_METHODPR(TileMap2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(TileMap2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(TileMap2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "void SetInstanceDefault(bool)", AS_METHODPR(TileMap2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(TileMap2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(TileMap2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(TileMap2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMap2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(TileMap2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "void SetTemporary(bool)", AS_METHODPR(TileMap2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "void set_temporary(bool)", AS_METHODPR(TileMap2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void TileMap2D::SetTmxFile(TmxFile2D* tmxFile) | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectMethod("TileMap2D", "void SetTmxFile(TmxFile2D@+)", AS_METHODPR(TileMap2D, SetTmxFile, (TmxFile2D*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "void set_tmxFile(TmxFile2D@+)", AS_METHODPR(TileMap2D, SetTmxFile, (TmxFile2D*), void), AS_CALL_THISCALL);
    // void TileMap2D::SetTmxFileAttr(const ResourceRef& value) | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectMethod("TileMap2D", "void SetTmxFileAttr(const ResourceRef&in)", AS_METHODPR(TileMap2D, SetTmxFileAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // Vector2 TileMap2D::TileIndexToPosition(int x, int y) const | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectMethod("TileMap2D", "Vector2 TileIndexToPosition(int, int) const", AS_METHODPR(TileMap2D, TileIndexToPosition, (int, int) const, Vector2), AS_CALL_THISCALL);
    // explicit TileMap2D::TileMap2D(Context* context) | File: ../Urho2D/TileMap2D.h
    engine->RegisterObjectBehaviour("TileMap2D", asBEHAVE_FACTORY, "TileMap2D@+ f()", AS_FUNCTION(TileMap2D_TileMap2D_Context), AS_CALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(TileMap2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(TileMap2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(TileMap2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(TileMap2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMap2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(TileMap2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TileMap2D", "int WeakRefs() const", AS_METHODPR(TileMap2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "int get_weakRefs() const", AS_METHODPR(TileMap2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(TileMap2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(TileMap2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMap2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(TileMap2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("TileMapLayer2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(TileMapLayer2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void AllocateNetworkState()", AS_METHODPR(TileMapLayer2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void ApplyAttributes()", AS_METHODPR(TileMapLayer2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void TileMapLayer2D::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(TileMapLayer2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool GetAnimationEnabled() const", AS_METHODPR(TileMapLayer2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "bool get_animationEnabled() const", AS_METHODPR(TileMapLayer2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Variant GetAttribute(uint) const", AS_METHODPR(TileMapLayer2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "Variant get_attributes(uint) const", AS_METHODPR(TileMapLayer2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(TileMapLayer2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(TileMapLayer2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(TileMapLayer2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(TileMapLayer2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(TileMapLayer2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(TileMapLayer2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(TileMapLayer2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(TileMapLayer2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool GetBlockEvents() const", AS_METHODPR(TileMapLayer2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "const String& GetCategory() const", AS_METHODPR(TileMapLayer2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "const String& get_category() const", AS_METHODPR(TileMapLayer2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(TileMapLayer2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("TileMapLayer2D", "int GetDrawOrder() const", AS_METHODPR(TileMapLayer2D, GetDrawOrder, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "int get_drawOrder() const", AS_METHODPR(TileMapLayer2D, GetDrawOrder, () const, int), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(TileMapLayer2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Object@+ GetEventSender() const", AS_METHODPR(TileMapLayer2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(TileMapLayer2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(TileMapLayer2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(TileMapLayer2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "const VariantMap& get_globalVars() const", AS_METHODPR(TileMapLayer2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int TileMapLayer2D::GetHeight() const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "int GetHeight() const", AS_METHODPR(TileMapLayer2D, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "int get_height() const", AS_METHODPR(TileMapLayer2D, GetHeight, () const, int), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "uint GetID() const", AS_METHODPR(TileMapLayer2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "uint get_id() const", AS_METHODPR(TileMapLayer2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // Node* TileMapLayer2D::GetImageNode() const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Node@+ GetImageNode() const", AS_METHODPR(TileMapLayer2D, GetImageNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "Node@+ get_imageNode() const", AS_METHODPR(TileMapLayer2D, GetImageNode, () const, Node*), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(TileMapLayer2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // TileMapLayerType2D TileMapLayer2D::GetLayerType() const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "TileMapLayerType2D GetLayerType() const", AS_METHODPR(TileMapLayer2D, GetLayerType, () const, TileMapLayerType2D), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "TileMapLayerType2D get_layerType() const", AS_METHODPR(TileMapLayer2D, GetLayerType, () const, TileMapLayerType2D), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Node@+ GetNode() const", AS_METHODPR(TileMapLayer2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "Node@+ get_node() const", AS_METHODPR(TileMapLayer2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "uint GetNumAttributes() const", AS_METHODPR(TileMapLayer2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "uint get_numAttributes() const", AS_METHODPR(TileMapLayer2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(TileMapLayer2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned TileMapLayer2D::GetNumObjects() const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "uint GetNumObjects() const", AS_METHODPR(TileMapLayer2D, GetNumObjects, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "uint get_numObjects() const", AS_METHODPR(TileMapLayer2D, GetNumObjects, () const, unsigned), AS_CALL_THISCALL);
    // TileMapObject2D* TileMapLayer2D::GetObject(unsigned index) const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "TileMapObject2D@+ GetObject(uint) const", AS_METHODPR(TileMapLayer2D, GetObject, (unsigned) const, TileMapObject2D*), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(TileMapLayer2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(TileMapLayer2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(TileMapLayer2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Node* TileMapLayer2D::GetObjectNode(unsigned index) const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Node@+ GetObjectNode(uint) const", AS_METHODPR(TileMapLayer2D, GetObjectNode, (unsigned) const, Node*), AS_CALL_THISCALL);
    // const String& TileMapLayer2D::GetProperty(const String& name) const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "const String& GetProperty(const String&in) const", AS_METHODPR(TileMapLayer2D, GetProperty, (const String&) const, const String&), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Scene@+ GetScene() const", AS_METHODPR(TileMapLayer2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(TileMapLayer2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // Tile2D* TileMapLayer2D::GetTile(int x, int y) const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Tile2D@+ GetTile(int, int) const", AS_METHODPR(TileMapLayer2D, GetTile, (int, int) const, Tile2D*), AS_CALL_THISCALL);
    // TileMap2D* TileMapLayer2D::GetTileMap() const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "TileMap2D@+ GetTileMap() const", AS_METHODPR(TileMapLayer2D, GetTileMap, () const, TileMap2D*), AS_CALL_THISCALL);
    // Node* TileMapLayer2D::GetTileNode(int x, int y) const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "Node@+ GetTileNode(int, int) const", AS_METHODPR(TileMapLayer2D, GetTileNode, (int, int) const, Node*), AS_CALL_THISCALL);
    // const TmxLayer2D* TileMapLayer2D::GetTmxLayer() const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "TmxLayer2D@+ GetTmxLayer() const", AS_METHODPR(TileMapLayer2D, GetTmxLayer, () const, const TmxLayer2D*), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "StringHash GetType() const", AS_METHODPR(TileMapLayer2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "StringHash get_type() const", AS_METHODPR(TileMapLayer2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "const String& GetTypeName() const", AS_METHODPR(TileMapLayer2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "const String& get_typeName() const", AS_METHODPR(TileMapLayer2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // int TileMapLayer2D::GetWidth() const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "int GetWidth() const", AS_METHODPR(TileMapLayer2D, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "int get_width() const", AS_METHODPR(TileMapLayer2D, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool HasEventHandlers() const", AS_METHODPR(TileMapLayer2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool TileMapLayer2D::HasProperty(const String& name) const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool HasProperty(const String&in) const", AS_METHODPR(TileMapLayer2D, HasProperty, (const String&) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(TileMapLayer2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(TileMapLayer2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // void TileMapLayer2D::Initialize(TileMap2D* tileMap, const TmxLayer2D* tmxLayer) | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void Initialize(TileMap2D@+, TmxLayer2D@+)", AS_METHODPR(TileMapLayer2D, Initialize, (TileMap2D*, const TmxLayer2D*), void), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool IsEnabled() const", AS_METHODPR(TileMapLayer2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "bool get_enabled() const", AS_METHODPR(TileMapLayer2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool IsEnabledEffective() const", AS_METHODPR(TileMapLayer2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "bool get_enabledEffective() const", AS_METHODPR(TileMapLayer2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(TileMapLayer2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool IsReplicated() const", AS_METHODPR(TileMapLayer2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "bool get_replicated() const", AS_METHODPR(TileMapLayer2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool IsTemporary() const", AS_METHODPR(TileMapLayer2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "bool get_temporary() const", AS_METHODPR(TileMapLayer2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool TileMapLayer2D::IsVisible() const | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool IsVisible() const", AS_METHODPR(TileMapLayer2D, IsVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "bool get_visible() const", AS_METHODPR(TileMapLayer2D, IsVisible, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool Load(Deserializer&)", AS_METHODPR(TileMapLayer2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(TileMapLayer2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(TileMapLayer2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void MarkNetworkUpdate()", AS_METHODPR(TileMapLayer2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(TileMapLayer2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(TileMapLayer2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(TileMapLayer2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void OnSetEnabled()", AS_METHODPR(TileMapLayer2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void PrepareNetworkUpdate()", AS_METHODPR(TileMapLayer2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(TileMapLayer2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(TileMapLayer2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TileMapLayer2D", "int Refs() const", AS_METHODPR(TileMapLayer2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "int get_refs() const", AS_METHODPR(TileMapLayer2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void TileMapLayer2D::RegisterObject(Context* context) | File: ../Urho2D/TileMapLayer2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TileMapLayer2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(TileMapLayer2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void Remove()", AS_METHODPR(TileMapLayer2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(TileMapLayer2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void RemoveInstanceDefault()", AS_METHODPR(TileMapLayer2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void RemoveObjectAnimation()", AS_METHODPR(TileMapLayer2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void ResetToDefault()", AS_METHODPR(TileMapLayer2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool Save(Serializer&) const", AS_METHODPR(TileMapLayer2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool SaveDefaultAttributes() const", AS_METHODPR(TileMapLayer2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(TileMapLayer2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(TileMapLayer2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SendEvent(StringHash)", AS_METHODPR(TileMapLayer2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(TileMapLayer2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetAnimationEnabled(bool)", AS_METHODPR(TileMapLayer2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "void set_animationEnabled(bool)", AS_METHODPR(TileMapLayer2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetAnimationTime(float)", AS_METHODPR(TileMapLayer2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(TileMapLayer2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(TileMapLayer2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(TileMapLayer2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(TileMapLayer2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(TileMapLayer2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(TileMapLayer2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(TileMapLayer2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetBlockEvents(bool)", AS_METHODPR(TileMapLayer2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void TileMapLayer2D::SetDrawOrder(int drawOrder) | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetDrawOrder(int)", AS_METHODPR(TileMapLayer2D, SetDrawOrder, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "void set_drawOrder(int)", AS_METHODPR(TileMapLayer2D, SetDrawOrder, (int), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetEnabled(bool)", AS_METHODPR(TileMapLayer2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "void set_enabled(bool)", AS_METHODPR(TileMapLayer2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(TileMapLayer2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(TileMapLayer2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetInstanceDefault(bool)", AS_METHODPR(TileMapLayer2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(TileMapLayer2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(TileMapLayer2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(TileMapLayer2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(TileMapLayer2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetTemporary(bool)", AS_METHODPR(TileMapLayer2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "void set_temporary(bool)", AS_METHODPR(TileMapLayer2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void TileMapLayer2D::SetVisible(bool visible) | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void SetVisible(bool)", AS_METHODPR(TileMapLayer2D, SetVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "void set_visible(bool)", AS_METHODPR(TileMapLayer2D, SetVisible, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit TileMapLayer2D::TileMapLayer2D(Context* context) | File: ../Urho2D/TileMapLayer2D.h
    engine->RegisterObjectBehaviour("TileMapLayer2D", asBEHAVE_FACTORY, "TileMapLayer2D@+ f()", AS_FUNCTION(TileMapLayer2D_TileMapLayer2D_Context), AS_CALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(TileMapLayer2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(TileMapLayer2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(TileMapLayer2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(TileMapLayer2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(TileMapLayer2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TileMapLayer2D", "int WeakRefs() const", AS_METHODPR(TileMapLayer2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "int get_weakRefs() const", AS_METHODPR(TileMapLayer2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(TileMapLayer2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(TileMapLayer2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("TileMapLayer2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(TileMapLayer2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("TileMapObject2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(TileMapObject2D, AddRef, (), void), AS_CALL_THISCALL);
    // const String& TileMapObject2D::GetName() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "const String& GetName() const", AS_METHODPR(TileMapObject2D, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "const String& get_name() const", AS_METHODPR(TileMapObject2D, GetName, () const, const String&), AS_CALL_THISCALL);
    // unsigned TileMapObject2D::GetNumPoints() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "uint GetNumPoints() const", AS_METHODPR(TileMapObject2D, GetNumPoints, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "uint get_numPoints() const", AS_METHODPR(TileMapObject2D, GetNumPoints, () const, unsigned), AS_CALL_THISCALL);
    // TileMapObjectType2D TileMapObject2D::GetObjectType() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "TileMapObjectType2D GetObjectType() const", AS_METHODPR(TileMapObject2D, GetObjectType, () const, TileMapObjectType2D), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "TileMapObjectType2D get_objectType() const", AS_METHODPR(TileMapObject2D, GetObjectType, () const, TileMapObjectType2D), AS_CALL_THISCALL);
    // const Vector2& TileMapObject2D::GetPoint(unsigned index) const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "const Vector2& GetPoint(uint) const", AS_METHODPR(TileMapObject2D, GetPoint, (unsigned) const, const Vector2&), AS_CALL_THISCALL);
    // const Vector2& TileMapObject2D::GetPosition() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "const Vector2& GetPosition() const", AS_METHODPR(TileMapObject2D, GetPosition, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "const Vector2& get_position() const", AS_METHODPR(TileMapObject2D, GetPosition, () const, const Vector2&), AS_CALL_THISCALL);
    // const String& TileMapObject2D::GetProperty(const String& name) const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "const String& GetProperty(const String&in) const", AS_METHODPR(TileMapObject2D, GetProperty, (const String&) const, const String&), AS_CALL_THISCALL);
    // const Vector2& TileMapObject2D::GetSize() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "const Vector2& GetSize() const", AS_METHODPR(TileMapObject2D, GetSize, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "const Vector2& get_size() const", AS_METHODPR(TileMapObject2D, GetSize, () const, const Vector2&), AS_CALL_THISCALL);
    // bool TileMapObject2D::GetTileFlipX() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "bool GetTileFlipX() const", AS_METHODPR(TileMapObject2D, GetTileFlipX, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "bool get_tileFlipX() const", AS_METHODPR(TileMapObject2D, GetTileFlipX, () const, bool), AS_CALL_THISCALL);
    // bool TileMapObject2D::GetTileFlipY() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "bool GetTileFlipY() const", AS_METHODPR(TileMapObject2D, GetTileFlipY, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "bool get_tileFlipY() const", AS_METHODPR(TileMapObject2D, GetTileFlipY, () const, bool), AS_CALL_THISCALL);
    // unsigned TileMapObject2D::GetTileGid() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "uint GetTileGid() const", AS_METHODPR(TileMapObject2D, GetTileGid, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "uint get_tileGid() const", AS_METHODPR(TileMapObject2D, GetTileGid, () const, unsigned), AS_CALL_THISCALL);
    // Sprite2D* TileMapObject2D::GetTileSprite() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "Sprite2D@+ GetTileSprite() const", AS_METHODPR(TileMapObject2D, GetTileSprite, () const, Sprite2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "Sprite2D@+ get_tileSprite() const", AS_METHODPR(TileMapObject2D, GetTileSprite, () const, Sprite2D*), AS_CALL_THISCALL);
    // bool TileMapObject2D::GetTileSwapXY() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "bool GetTileSwapXY() const", AS_METHODPR(TileMapObject2D, GetTileSwapXY, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "bool get_tileSwapXY() const", AS_METHODPR(TileMapObject2D, GetTileSwapXY, () const, bool), AS_CALL_THISCALL);
    // const String& TileMapObject2D::GetType() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "const String& GetType() const", AS_METHODPR(TileMapObject2D, GetType, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "const String& get_type() const", AS_METHODPR(TileMapObject2D, GetType, () const, const String&), AS_CALL_THISCALL);
    // bool TileMapObject2D::HasProperty(const String& name) const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapObject2D", "bool HasProperty(const String&in) const", AS_METHODPR(TileMapObject2D, HasProperty, (const String&) const, bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TileMapObject2D", "int Refs() const", AS_METHODPR(TileMapObject2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "int get_refs() const", AS_METHODPR(TileMapObject2D, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TileMapObject2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(TileMapObject2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TileMapObject2D", "int WeakRefs() const", AS_METHODPR(TileMapObject2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "int get_weakRefs() const", AS_METHODPR(TileMapObject2D, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(TileMapObject2D, "TileMapObject2D")
#endif
#ifdef REGISTER_MANUAL_PART_TileMapObject2D
    REGISTER_MANUAL_PART_TileMapObject2D(TileMapObject2D, "TileMapObject2D")
#endif
    RegisterSubclass<RefCounted, TileMapObject2D>(engine, "RefCounted", "TileMapObject2D");
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Time", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Time, AddRef, (), void), AS_CALL_THISCALL);
    // void Time::BeginFrame(float timeStep) | File: ../Core/Timer.h
    engine->RegisterObjectMethod("Time", "void BeginFrame(float)", AS_METHODPR(Time, BeginFrame, (float), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Time::EndFrame() | File: ../Core/Timer.h
    engine->RegisterObjectMethod("Time", "void EndFrame()", AS_METHODPR(Time, EndFrame, (), void), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "bool GetBlockEvents() const", AS_METHODPR(Time, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "const String& GetCategory() const", AS_METHODPR(Time, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Time", "const String& get_category() const", AS_METHODPR(Time, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // float Time::GetElapsedTime() | File: ../Core/Timer.h
    engine->RegisterObjectMethod("Time", "float GetElapsedTime()", AS_METHODPR(Time, GetElapsedTime, (), float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Time", "float get_elapsedTime()", AS_METHODPR(Time, GetElapsedTime, (), float), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "VariantMap& GetEventDataMap() const", AS_METHODPR(Time, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "Object@+ GetEventSender() const", AS_METHODPR(Time, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // unsigned Time::GetFrameNumber() const | File: ../Core/Timer.h
    engine->RegisterObjectMethod("Time", "uint GetFrameNumber() const", AS_METHODPR(Time, GetFrameNumber, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Time", "uint get_frameNumber() const", AS_METHODPR(Time, GetFrameNumber, () const, unsigned), AS_CALL_THISCALL);
    // float Time::GetFramesPerSecond() const | File: ../Core/Timer.h
    engine->RegisterObjectMethod("Time", "float GetFramesPerSecond() const", AS_METHODPR(Time, GetFramesPerSecond, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Time", "float get_framesPerSecond() const", AS_METHODPR(Time, GetFramesPerSecond, () const, float), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Time, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Time", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Time, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Time, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Time", "const VariantMap& get_globalVars() const", AS_METHODPR(Time, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Time, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // static unsigned Time::GetSystemTime() | File: ../Core/Timer.h
    engine->SetDefaultNamespace("Time");
    engine->RegisterGlobalFunction("uint GetSystemTime()", AS_FUNCTIONPR(Time::GetSystemTime, (), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // unsigned Time::GetTimerPeriod() const | File: ../Core/Timer.h
    engine->RegisterObjectMethod("Time", "uint GetTimerPeriod() const", AS_METHODPR(Time, GetTimerPeriod, () const, unsigned), AS_CALL_THISCALL);
    // static unsigned Time::GetTimeSinceEpoch() | File: ../Core/Timer.h
    engine->SetDefaultNamespace("Time");
    engine->RegisterGlobalFunction("uint GetTimeSinceEpoch()", AS_FUNCTIONPR(Time::GetTimeSinceEpoch, (), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // static String Time::GetTimeStamp() | File: ../Core/Timer.h
    engine->SetDefaultNamespace("Time");
    engine->RegisterGlobalFunction("String GetTimeStamp()", AS_FUNCTIONPR(Time::GetTimeStamp, (), String), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // float Time::GetTimeStep() const | File: ../Core/Timer.h
    engine->RegisterObjectMethod("Time", "float GetTimeStep() const", AS_METHODPR(Time, GetTimeStep, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Time", "float get_timeStep() const", AS_METHODPR(Time, GetTimeStep, () const, float), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "StringHash GetType() const", AS_METHODPR(Time, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Time", "StringHash get_type() const", AS_METHODPR(Time, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "const String& GetTypeName() const", AS_METHODPR(Time, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Time", "const String& get_typeName() const", AS_METHODPR(Time, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "bool HasEventHandlers() const", AS_METHODPR(Time, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Time, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Time, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Time, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Time, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Time", "int Refs() const", AS_METHODPR(Time, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Time", "int get_refs() const", AS_METHODPR(Time, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Time", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Time, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "void SendEvent(StringHash)", AS_METHODPR(Time, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Time, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "void SetBlockEvents(bool)", AS_METHODPR(Time, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Time, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Time", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Time, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Time::SetTimerPeriod(unsigned mSec) | File: ../Core/Timer.h
    engine->RegisterObjectMethod("Time", "void SetTimerPeriod(uint)", AS_METHODPR(Time, SetTimerPeriod, (unsigned), void), AS_CALL_THISCALL);
    // static void Time::Sleep(unsigned mSec) | File: ../Core/Timer.h
    engine->SetDefaultNamespace("Time");
    engine->RegisterGlobalFunction("void Sleep(uint)", AS_FUNCTIONPR(Time::Sleep, (unsigned), void), AS_CALL_CDECL);
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
    engine->RegisterObjectBehaviour("Time", asBEHAVE_FACTORY, "Time@+ f()", AS_FUNCTION(Time_Time_Context), AS_CALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "void UnsubscribeFromAllEvents()", AS_METHODPR(Time, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Time_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Time, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Time, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Time", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Time, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Time", "int WeakRefs() const", AS_METHODPR(Time, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Time", "int get_weakRefs() const", AS_METHODPR(Time, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Timer", "uint GetMSec(bool)", AS_METHODPR(Timer, GetMSec, (bool), unsigned), AS_CALL_THISCALL);
    // void Timer::Reset() | File: ../Core/Timer.h
    engine->RegisterObjectMethod("Timer", "void Reset()", AS_METHODPR(Timer, Reset, (), void), AS_CALL_THISCALL);
    // Timer& Timer::operator=(const Timer&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Timer>(engine, "Timer");
#ifdef REGISTER_MANUAL_PART_Timer
    REGISTER_MANUAL_PART_Timer(Timer, "Timer")
#endif

#ifdef URHO3D_URHO2D
    // void TmxFile2D::AddLayer(unsigned index, TmxLayer2D* layer) | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxFile2D", "void AddLayer(uint, TmxLayer2D@+)", AS_METHODPR(TmxFile2D, AddLayer, (unsigned, TmxLayer2D*), void), AS_CALL_THISCALL);
    // void TmxFile2D::AddLayer(Urho3D::TmxLayer2D* layer) | File: ../Urho2D/TmxFile2D.h
    // Error: type "Urho3D::TmxLayer2D*" can not automatically bind
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TmxFile2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(TmxFile2D, AddRef, (), void), AS_CALL_THISCALL);
    // bool TmxFile2D::BeginLoad(Deserializer& source) override | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxFile2D", "bool BeginLoad(Deserializer&)", AS_METHODPR(TmxFile2D, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool TmxFile2D::EndLoad() override | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxFile2D", "bool EndLoad()", AS_METHODPR(TmxFile2D, EndLoad, (), bool), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(TmxFile2D, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "bool GetBlockEvents() const", AS_METHODPR(TmxFile2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "const String& GetCategory() const", AS_METHODPR(TmxFile2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "const String& get_category() const", AS_METHODPR(TmxFile2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(TmxFile2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "Object@+ GetEventSender() const", AS_METHODPR(TmxFile2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(TmxFile2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(TmxFile2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(TmxFile2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "const VariantMap& get_globalVars() const", AS_METHODPR(TmxFile2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // const TileMapInfo2D& TmxFile2D::GetInfo() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxFile2D", "const TileMapInfo2D& GetInfo() const", AS_METHODPR(TmxFile2D, GetInfo, () const, const TileMapInfo2D&), AS_CALL_THISCALL);
    // const TmxLayer2D* TmxFile2D::GetLayer(unsigned index) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxFile2D", "TmxLayer2D@+ GetLayer(uint) const", AS_METHODPR(TmxFile2D, GetLayer, (unsigned) const, const TmxLayer2D*), AS_CALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "uint GetMemoryUse() const", AS_METHODPR(TmxFile2D, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "uint get_memoryUse() const", AS_METHODPR(TmxFile2D, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "const String& GetName() const", AS_METHODPR(TmxFile2D, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "const String& get_name() const", AS_METHODPR(TmxFile2D, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "StringHash GetNameHash() const", AS_METHODPR(TmxFile2D, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // unsigned TmxFile2D::GetNumLayers() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxFile2D", "uint GetNumLayers() const", AS_METHODPR(TmxFile2D, GetNumLayers, () const, unsigned), AS_CALL_THISCALL);
    // float TmxFile2D::GetSpriteTextureEdgeOffset() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxFile2D", "float GetSpriteTextureEdgeOffset() const", AS_METHODPR(TmxFile2D, GetSpriteTextureEdgeOffset, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "float get_edgeOffset() const", AS_METHODPR(TmxFile2D, GetSpriteTextureEdgeOffset, () const, float), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(TmxFile2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // Vector<SharedPtr<TileMapObject2D>> TmxFile2D::GetTileCollisionShapes(unsigned gid) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxFile2D", "Array<TileMapObject2D@>@ GetTileCollisionShapes(uint) const", AS_FUNCTION_OBJFIRST(TmxFile2D_GetTileCollisionShapes_unsigned), AS_CALL_CDECL_OBJFIRST);
    // PropertySet2D* TmxFile2D::GetTilePropertySet(unsigned gid) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxFile2D", "PropertySet2D@+ GetTilePropertySet(uint) const", AS_METHODPR(TmxFile2D, GetTilePropertySet, (unsigned) const, PropertySet2D*), AS_CALL_THISCALL);
    // Sprite2D* TmxFile2D::GetTileSprite(unsigned gid) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxFile2D", "Sprite2D@+ GetTileSprite(uint) const", AS_METHODPR(TmxFile2D, GetTileSprite, (unsigned) const, Sprite2D*), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "StringHash GetType() const", AS_METHODPR(TmxFile2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "StringHash get_type() const", AS_METHODPR(TmxFile2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "const String& GetTypeName() const", AS_METHODPR(TmxFile2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "const String& get_typeName() const", AS_METHODPR(TmxFile2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "uint GetUseTimer()", AS_METHODPR(TmxFile2D, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "uint get_useTimer()", AS_METHODPR(TmxFile2D, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "bool HasEventHandlers() const", AS_METHODPR(TmxFile2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(TmxFile2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(TmxFile2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(TmxFile2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "bool Load(Deserializer&)", AS_METHODPR(TmxFile2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "bool LoadFile(const String&in)", AS_METHODPR(TmxFile2D, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "bool Load(const String&in)", AS_METHODPR(TmxFile2D, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(TmxFile2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TmxFile2D", "int Refs() const", AS_METHODPR(TmxFile2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "int get_refs() const", AS_METHODPR(TmxFile2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void TmxFile2D::RegisterObject(Context* context) | File: ../Urho2D/TmxFile2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TmxFile2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(TmxFile2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "void ResetUseTimer()", AS_METHODPR(TmxFile2D, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "bool Save(Serializer&) const", AS_METHODPR(TmxFile2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "bool SaveFile(const String&in) const", AS_METHODPR(TmxFile2D, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "bool Save(const String&in) const", AS_METHODPR(TmxFile2D, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "void SendEvent(StringHash)", AS_METHODPR(TmxFile2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(TmxFile2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(TmxFile2D, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "void SetBlockEvents(bool)", AS_METHODPR(TmxFile2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(TmxFile2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(TmxFile2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // bool TmxFile2D::SetInfo(Orientation2D orientation, int width, int height, float tileWidth, float tileHeight) | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxFile2D", "bool SetInfo(Orientation2D, int, int, float, float)", AS_METHODPR(TmxFile2D, SetInfo, (Orientation2D, int, int, float, float), bool), AS_CALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "void SetMemoryUse(uint)", AS_METHODPR(TmxFile2D, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("TmxFile2D", "void SetName(const String&in)", AS_METHODPR(TmxFile2D, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "void set_name(const String&in)", AS_METHODPR(TmxFile2D, SetName, (const String&), void), AS_CALL_THISCALL);
    // void TmxFile2D::SetSpriteTextureEdgeOffset(float offset) | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxFile2D", "void SetSpriteTextureEdgeOffset(float)", AS_METHODPR(TmxFile2D, SetSpriteTextureEdgeOffset, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "void set_edgeOffset(float)", AS_METHODPR(TmxFile2D, SetSpriteTextureEdgeOffset, (float), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit TmxFile2D::TmxFile2D(Context* context) | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectBehaviour("TmxFile2D", asBEHAVE_FACTORY, "TmxFile2D@+ f()", AS_FUNCTION(TmxFile2D_TmxFile2D_Context), AS_CALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(TmxFile2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(TmxFile2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(TmxFile2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(TmxFile2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("TmxFile2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(TmxFile2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TmxFile2D", "int WeakRefs() const", AS_METHODPR(TmxFile2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TmxFile2D", "int get_weakRefs() const", AS_METHODPR(TmxFile2D, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("TmxImageLayer2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(TmxImageLayer2D, AddRef, (), void), AS_CALL_THISCALL);
    // int TmxLayer2D::GetHeight() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "int GetHeight() const", AS_METHODPR(TmxImageLayer2D, GetHeight, () const, int), AS_CALL_THISCALL);
    // const String& TmxLayer2D::GetName() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "const String& GetName() const", AS_METHODPR(TmxImageLayer2D, GetName, () const, const String&), AS_CALL_THISCALL);
    // const Vector2& TmxImageLayer2D::GetPosition() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "const Vector2& GetPosition() const", AS_METHODPR(TmxImageLayer2D, GetPosition, () const, const Vector2&), AS_CALL_THISCALL);
    // const String& TmxLayer2D::GetProperty(const String& name) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "const String& GetProperty(const String&in) const", AS_METHODPR(TmxImageLayer2D, GetProperty, (const String&) const, const String&), AS_CALL_THISCALL);
    // const String& TmxImageLayer2D::GetSource() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "const String& GetSource() const", AS_METHODPR(TmxImageLayer2D, GetSource, () const, const String&), AS_CALL_THISCALL);
    // Sprite2D* TmxImageLayer2D::GetSprite() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "Sprite2D@+ GetSprite() const", AS_METHODPR(TmxImageLayer2D, GetSprite, () const, Sprite2D*), AS_CALL_THISCALL);
    // TmxFile2D* TmxLayer2D::GetTmxFile() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "TmxFile2D@+ GetTmxFile() const", AS_METHODPR(TmxImageLayer2D, GetTmxFile, () const, TmxFile2D*), AS_CALL_THISCALL);
    // TileMapLayerType2D TmxLayer2D::GetType() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "TileMapLayerType2D GetType() const", AS_METHODPR(TmxImageLayer2D, GetType, () const, TileMapLayerType2D), AS_CALL_THISCALL);
    // int TmxLayer2D::GetWidth() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "int GetWidth() const", AS_METHODPR(TmxImageLayer2D, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool TmxLayer2D::HasProperty(const String& name) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "bool HasProperty(const String&in) const", AS_METHODPR(TmxImageLayer2D, HasProperty, (const String&) const, bool), AS_CALL_THISCALL);
    // bool TmxLayer2D::IsVisible() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "bool IsVisible() const", AS_METHODPR(TmxImageLayer2D, IsVisible, () const, bool), AS_CALL_THISCALL);
    // bool TmxImageLayer2D::Load(const XMLElement& element, const TileMapInfo2D& info) | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "bool Load(const XMLElement&in, const TileMapInfo2D&in)", AS_METHODPR(TmxImageLayer2D, Load, (const XMLElement&, const TileMapInfo2D&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "int Refs() const", AS_METHODPR(TmxImageLayer2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TmxImageLayer2D", "int get_refs() const", AS_METHODPR(TmxImageLayer2D, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TmxImageLayer2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(TmxImageLayer2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // explicit TmxImageLayer2D::TmxImageLayer2D(TmxFile2D* tmxFile) | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectBehaviour("TmxImageLayer2D", asBEHAVE_FACTORY, "TmxImageLayer2D@+ f(TmxFile2D@+)", AS_FUNCTION(TmxImageLayer2D_TmxImageLayer2D_TmxFile2D), AS_CALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TmxImageLayer2D", "int WeakRefs() const", AS_METHODPR(TmxImageLayer2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TmxImageLayer2D", "int get_weakRefs() const", AS_METHODPR(TmxImageLayer2D, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("TmxLayer2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(TmxLayer2D, AddRef, (), void), AS_CALL_THISCALL);
    // int TmxLayer2D::GetHeight() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxLayer2D", "int GetHeight() const", AS_METHODPR(TmxLayer2D, GetHeight, () const, int), AS_CALL_THISCALL);
    // const String& TmxLayer2D::GetName() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxLayer2D", "const String& GetName() const", AS_METHODPR(TmxLayer2D, GetName, () const, const String&), AS_CALL_THISCALL);
    // const String& TmxLayer2D::GetProperty(const String& name) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxLayer2D", "const String& GetProperty(const String&in) const", AS_METHODPR(TmxLayer2D, GetProperty, (const String&) const, const String&), AS_CALL_THISCALL);
    // TmxFile2D* TmxLayer2D::GetTmxFile() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxLayer2D", "TmxFile2D@+ GetTmxFile() const", AS_METHODPR(TmxLayer2D, GetTmxFile, () const, TmxFile2D*), AS_CALL_THISCALL);
    // TileMapLayerType2D TmxLayer2D::GetType() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxLayer2D", "TileMapLayerType2D GetType() const", AS_METHODPR(TmxLayer2D, GetType, () const, TileMapLayerType2D), AS_CALL_THISCALL);
    // int TmxLayer2D::GetWidth() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxLayer2D", "int GetWidth() const", AS_METHODPR(TmxLayer2D, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool TmxLayer2D::HasProperty(const String& name) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxLayer2D", "bool HasProperty(const String&in) const", AS_METHODPR(TmxLayer2D, HasProperty, (const String&) const, bool), AS_CALL_THISCALL);
    // bool TmxLayer2D::IsVisible() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxLayer2D", "bool IsVisible() const", AS_METHODPR(TmxLayer2D, IsVisible, () const, bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TmxLayer2D", "int Refs() const", AS_METHODPR(TmxLayer2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TmxLayer2D", "int get_refs() const", AS_METHODPR(TmxLayer2D, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TmxLayer2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(TmxLayer2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // TmxLayer2D::TmxLayer2D(TmxFile2D* tmxFile, TileMapLayerType2D type) | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectBehaviour("TmxLayer2D", asBEHAVE_FACTORY, "TmxLayer2D@+ f(TmxFile2D@+, TileMapLayerType2D)", AS_FUNCTION(TmxLayer2D_TmxLayer2D_TmxFile2D_TileMapLayerType2D), AS_CALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TmxLayer2D", "int WeakRefs() const", AS_METHODPR(TmxLayer2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TmxLayer2D", "int get_weakRefs() const", AS_METHODPR(TmxLayer2D, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("TmxObjectGroup2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(TmxObjectGroup2D, AddRef, (), void), AS_CALL_THISCALL);
    // int TmxLayer2D::GetHeight() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "int GetHeight() const", AS_METHODPR(TmxObjectGroup2D, GetHeight, () const, int), AS_CALL_THISCALL);
    // const String& TmxLayer2D::GetName() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "const String& GetName() const", AS_METHODPR(TmxObjectGroup2D, GetName, () const, const String&), AS_CALL_THISCALL);
    // unsigned TmxObjectGroup2D::GetNumObjects() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "uint GetNumObjects() const", AS_METHODPR(TmxObjectGroup2D, GetNumObjects, () const, unsigned), AS_CALL_THISCALL);
    // TileMapObject2D* TmxObjectGroup2D::GetObject(unsigned index) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "TileMapObject2D@+ GetObject(uint) const", AS_METHODPR(TmxObjectGroup2D, GetObject, (unsigned) const, TileMapObject2D*), AS_CALL_THISCALL);
    // const String& TmxLayer2D::GetProperty(const String& name) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "const String& GetProperty(const String&in) const", AS_METHODPR(TmxObjectGroup2D, GetProperty, (const String&) const, const String&), AS_CALL_THISCALL);
    // TmxFile2D* TmxLayer2D::GetTmxFile() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "TmxFile2D@+ GetTmxFile() const", AS_METHODPR(TmxObjectGroup2D, GetTmxFile, () const, TmxFile2D*), AS_CALL_THISCALL);
    // TileMapLayerType2D TmxLayer2D::GetType() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "TileMapLayerType2D GetType() const", AS_METHODPR(TmxObjectGroup2D, GetType, () const, TileMapLayerType2D), AS_CALL_THISCALL);
    // int TmxLayer2D::GetWidth() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "int GetWidth() const", AS_METHODPR(TmxObjectGroup2D, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool TmxLayer2D::HasProperty(const String& name) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "bool HasProperty(const String&in) const", AS_METHODPR(TmxObjectGroup2D, HasProperty, (const String&) const, bool), AS_CALL_THISCALL);
    // bool TmxLayer2D::IsVisible() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "bool IsVisible() const", AS_METHODPR(TmxObjectGroup2D, IsVisible, () const, bool), AS_CALL_THISCALL);
    // bool TmxObjectGroup2D::Load(const XMLElement& element, const TileMapInfo2D& info) | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "bool Load(const XMLElement&in, const TileMapInfo2D&in)", AS_METHODPR(TmxObjectGroup2D, Load, (const XMLElement&, const TileMapInfo2D&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "int Refs() const", AS_METHODPR(TmxObjectGroup2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TmxObjectGroup2D", "int get_refs() const", AS_METHODPR(TmxObjectGroup2D, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TmxObjectGroup2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(TmxObjectGroup2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void TmxObjectGroup2D::StoreObject(const XMLElement& objectElem, const SharedPtr<TileMapObject2D>& object, const TileMapInfo2D& info, bool isTile=false) | File: ../Urho2D/TmxFile2D.h
    // Error: type "const SharedPtr<TileMapObject2D>&" can not automatically bind
    // explicit TmxObjectGroup2D::TmxObjectGroup2D(TmxFile2D* tmxFile) | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectBehaviour("TmxObjectGroup2D", asBEHAVE_FACTORY, "TmxObjectGroup2D@+ f(TmxFile2D@+)", AS_FUNCTION(TmxObjectGroup2D_TmxObjectGroup2D_TmxFile2D), AS_CALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TmxObjectGroup2D", "int WeakRefs() const", AS_METHODPR(TmxObjectGroup2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TmxObjectGroup2D", "int get_weakRefs() const", AS_METHODPR(TmxObjectGroup2D, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("TmxTileLayer2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(TmxTileLayer2D, AddRef, (), void), AS_CALL_THISCALL);
    // int TmxLayer2D::GetHeight() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxTileLayer2D", "int GetHeight() const", AS_METHODPR(TmxTileLayer2D, GetHeight, () const, int), AS_CALL_THISCALL);
    // const String& TmxLayer2D::GetName() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxTileLayer2D", "const String& GetName() const", AS_METHODPR(TmxTileLayer2D, GetName, () const, const String&), AS_CALL_THISCALL);
    // const String& TmxLayer2D::GetProperty(const String& name) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxTileLayer2D", "const String& GetProperty(const String&in) const", AS_METHODPR(TmxTileLayer2D, GetProperty, (const String&) const, const String&), AS_CALL_THISCALL);
    // Tile2D* TmxTileLayer2D::GetTile(int x, int y) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxTileLayer2D", "Tile2D@+ GetTile(int, int) const", AS_METHODPR(TmxTileLayer2D, GetTile, (int, int) const, Tile2D*), AS_CALL_THISCALL);
    // TmxFile2D* TmxLayer2D::GetTmxFile() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxTileLayer2D", "TmxFile2D@+ GetTmxFile() const", AS_METHODPR(TmxTileLayer2D, GetTmxFile, () const, TmxFile2D*), AS_CALL_THISCALL);
    // TileMapLayerType2D TmxLayer2D::GetType() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxTileLayer2D", "TileMapLayerType2D GetType() const", AS_METHODPR(TmxTileLayer2D, GetType, () const, TileMapLayerType2D), AS_CALL_THISCALL);
    // int TmxLayer2D::GetWidth() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxTileLayer2D", "int GetWidth() const", AS_METHODPR(TmxTileLayer2D, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool TmxLayer2D::HasProperty(const String& name) const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxTileLayer2D", "bool HasProperty(const String&in) const", AS_METHODPR(TmxTileLayer2D, HasProperty, (const String&) const, bool), AS_CALL_THISCALL);
    // bool TmxLayer2D::IsVisible() const | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxTileLayer2D", "bool IsVisible() const", AS_METHODPR(TmxTileLayer2D, IsVisible, () const, bool), AS_CALL_THISCALL);
    // bool TmxTileLayer2D::Load(const XMLElement& element, const TileMapInfo2D& info) | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectMethod("TmxTileLayer2D", "bool Load(const XMLElement&in, const TileMapInfo2D&in)", AS_METHODPR(TmxTileLayer2D, Load, (const XMLElement&, const TileMapInfo2D&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TmxTileLayer2D", "int Refs() const", AS_METHODPR(TmxTileLayer2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TmxTileLayer2D", "int get_refs() const", AS_METHODPR(TmxTileLayer2D, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TmxTileLayer2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(TmxTileLayer2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // explicit TmxTileLayer2D::TmxTileLayer2D(TmxFile2D* tmxFile) | File: ../Urho2D/TmxFile2D.h
    engine->RegisterObjectBehaviour("TmxTileLayer2D", asBEHAVE_FACTORY, "TmxTileLayer2D@+ f(TmxFile2D@+)", AS_FUNCTION(TmxTileLayer2D_TmxTileLayer2D_TmxFile2D), AS_CALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TmxTileLayer2D", "int WeakRefs() const", AS_METHODPR(TmxTileLayer2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TmxTileLayer2D", "int get_weakRefs() const", AS_METHODPR(TmxTileLayer2D, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("TechniqueEntry", asBEHAVE_CONSTRUCT, "void f(Technique@+, MaterialQuality, float)", AS_FUNCTION_OBJFIRST(TechniqueEntry_TechniqueEntry_Technique_MaterialQuality_float), AS_CALL_CDECL_OBJFIRST);
    // TechniqueEntry& TechniqueEntry::operator=(const TechniqueEntry&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<TechniqueEntry>(engine, "TechniqueEntry");
#ifdef REGISTER_MANUAL_PART_TechniqueEntry
    REGISTER_MANUAL_PART_TechniqueEntry(TechniqueEntry, "TechniqueEntry")
#endif

    // float TextureFrame::time_ | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectProperty("TextureFrame", "float time", offsetof(TextureFrame, time_));
    // Rect TextureFrame::uv_ | File: ../Graphics/ParticleEffect.h
    engine->RegisterObjectProperty("TextureFrame", "Rect uv", offsetof(TextureFrame, uv_));
    // TextureFrame& TextureFrame::operator=(const TextureFrame&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<TextureFrame>(engine, "TextureFrame");
    engine->RegisterObjectBehaviour("TextureFrame", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("TextureFrame", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);
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
    engine->RegisterObjectMethod("TileMapInfo2D", "Vector2 ConvertPosition(const Vector2&in) const", AS_METHODPR(TileMapInfo2D, ConvertPosition, (const Vector2&) const, Vector2), AS_CALL_THISCALL);
    // float TileMapInfo2D::GetMapHeight() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapInfo2D", "float GetMapHeight() const", AS_METHODPR(TileMapInfo2D, GetMapHeight, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapInfo2D", "float get_mapHeight() const", AS_METHODPR(TileMapInfo2D, GetMapHeight, () const, float), AS_CALL_THISCALL);
    // float TileMapInfo2D::GetMapWidth() const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapInfo2D", "float GetMapWidth() const", AS_METHODPR(TileMapInfo2D, GetMapWidth, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TileMapInfo2D", "float get_mapWidth() const", AS_METHODPR(TileMapInfo2D, GetMapWidth, () const, float), AS_CALL_THISCALL);
    // bool TileMapInfo2D::PositionToTileIndex(int& x, int& y, const Vector2& position) const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapInfo2D", "bool PositionToTileIndex(int&, int&, const Vector2&in) const", AS_METHODPR(TileMapInfo2D, PositionToTileIndex, (int&, int&, const Vector2&) const, bool), AS_CALL_THISCALL);
    // Vector2 TileMapInfo2D::TileIndexToPosition(int x, int y) const | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterObjectMethod("TileMapInfo2D", "Vector2 TileIndexToPosition(int, int) const", AS_METHODPR(TileMapInfo2D, TileIndexToPosition, (int, int) const, Vector2), AS_CALL_THISCALL);
    // TileMapInfo2D& TileMapInfo2D::operator=(const TileMapInfo2D&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<TileMapInfo2D>(engine, "TileMapInfo2D");
    engine->RegisterObjectBehaviour("TileMapInfo2D", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("TileMapInfo2D", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);
#ifdef REGISTER_MANUAL_PART_TileMapInfo2D
    REGISTER_MANUAL_PART_TileMapInfo2D(TileMapInfo2D, "TileMapInfo2D")
#endif
#endif

}

}
