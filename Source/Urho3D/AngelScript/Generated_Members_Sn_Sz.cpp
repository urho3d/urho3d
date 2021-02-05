// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// SharedPtr<SoundStream> Sound::GetDecoderStream() const | File: ../Audio/Sound.h
static SoundStream* Sound_GetDecoderStream_void(Sound* ptr)
{
    SharedPtr<SoundStream> result = ptr->GetDecoderStream();
    return result.Detach();
}

// explicit Sound::Sound(Context* context) | File: ../Audio/Sound.h
static Sound* Sound_Sound_Context()
{
    return new Sound(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Sound_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Sound* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit SoundListener::SoundListener(Context* context) | File: ../Audio/SoundListener.h
static SoundListener* SoundListener_SoundListener_Context()
{
    return new SoundListener(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void SoundListener_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(SoundListener* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit SoundSource::SoundSource(Context* context) | File: ../Audio/SoundSource.h
static SoundSource* SoundSource_SoundSource_Context()
{
    return new SoundSource(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void SoundSource_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(SoundSource* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit SoundSource3D::SoundSource3D(Context* context) | File: ../Audio/SoundSource3D.h
static SoundSource3D* SoundSource3D_SoundSource3D_Context()
{
    return new SoundSource3D(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void SoundSource3D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(SoundSource3D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// Sphere::Sphere(const Sphere& sphere) noexcept=default | File: ../Math/Sphere.h
static void Sphere_Sphere_Sphere(Sphere* ptr, const Sphere &sphere)
{
    new(ptr) Sphere(sphere);
}

// Sphere::Sphere(const Vector3& center, float radius) noexcept | File: ../Math/Sphere.h
static void Sphere_Sphere_Vector3_float(Sphere* ptr, const Vector3 &center, float radius)
{
    new(ptr) Sphere(center, radius);
}

// explicit Sphere::Sphere(const BoundingBox& box) noexcept | File: ../Math/Sphere.h
static void Sphere_Sphere_BoundingBox(Sphere* ptr, const BoundingBox &box)
{
    new(ptr) Sphere(box);
}

// explicit Sphere::Sphere(const Frustum& frustum) noexcept | File: ../Math/Sphere.h
static void Sphere_Sphere_Frustum(Sphere* ptr, const Frustum &frustum)
{
    new(ptr) Sphere(frustum);
}

// explicit Sphere::Sphere(const Polyhedron& poly) noexcept | File: ../Math/Sphere.h
static void Sphere_Sphere_Polyhedron(Sphere* ptr, const Polyhedron &poly)
{
    new(ptr) Sphere(poly);
}

// explicit Spline::Spline(InterpolationMode mode) | File: ../Core/Spline.h
static void Spline_Spline_InterpolationMode(Spline* ptr, InterpolationMode mode)
{
    new(ptr) Spline(mode);
}

// Spline::Spline(const Spline& rhs)=default | File: ../Core/Spline.h
static void Spline_Spline_Spline(Spline* ptr, const Spline &rhs)
{
    new(ptr) Spline(rhs);
}

// explicit SplinePath::SplinePath(Context* context) | File: ../Scene/SplinePath.h
static SplinePath* SplinePath_SplinePath_Context()
{
    return new SplinePath(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void SplinePath_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(SplinePath* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
static void Sprite_AddTags_StringVector(Sprite* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->AddTags(tags);
}

// const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
static CScriptArray* Sprite_GetChildren_void(Sprite* ptr)
{
    const Vector<SharedPtr<UIElement>>& result = ptr->GetChildren();
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
static CScriptArray* Sprite_GetChildren_bool(Sprite* ptr, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildren(recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
static CScriptArray* Sprite_GetChildrenWithTag_String_bool(Sprite* ptr, const String& tag, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildrenWithTag(tag, recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
static CScriptArray* Sprite_GetTags_void(Sprite* ptr)
{
    const StringVector& result = ptr->GetTags();
    return VectorToArray<String>(result, "Array<String>");
}

// void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
static void Sprite_SetTags_StringVector(Sprite* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->SetTags(tags);
}

// explicit Sprite::Sprite(Context* context) | File: ../UI/Sprite.h
static Sprite* Sprite_Sprite_Context()
{
    return new Sprite(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Sprite_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Sprite* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

#ifdef URHO3D_URHO2D
// explicit Sprite2D::Sprite2D(Context* context) | File: ../Urho2D/Sprite2D.h
static Sprite2D* Sprite2D_Sprite2D_Context()
{
    return new Sprite2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Sprite2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Sprite2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_URHO2D
// explicit SpriteSheet2D::SpriteSheet2D(Context* context) | File: ../Urho2D/SpriteSheet2D.h
static SpriteSheet2D* SpriteSheet2D_SpriteSheet2D_Context()
{
    return new SpriteSheet2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void SpriteSheet2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(SpriteSheet2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

// const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
static CScriptArray* StaticModel_GetLights_void(StaticModel* ptr)
{
    const PODVector<Light*>& result = ptr->GetLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
static CScriptArray* StaticModel_GetVertexLights_void(StaticModel* ptr)
{
    const PODVector<Light*>& result = ptr->GetVertexLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// explicit StaticModel::StaticModel(Context* context) | File: ../Graphics/StaticModel.h
static StaticModel* StaticModel_StaticModel_Context()
{
    return new StaticModel(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void StaticModel_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(StaticModel* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
static CScriptArray* StaticModelGroup_GetLights_void(StaticModelGroup* ptr)
{
    const PODVector<Light*>& result = ptr->GetLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
static CScriptArray* StaticModelGroup_GetVertexLights_void(StaticModelGroup* ptr)
{
    const PODVector<Light*>& result = ptr->GetVertexLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// explicit StaticModelGroup::StaticModelGroup(Context* context) | File: ../Graphics/StaticModelGroup.h
static StaticModelGroup* StaticModelGroup_StaticModelGroup_Context()
{
    return new StaticModelGroup(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void StaticModelGroup_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(StaticModelGroup* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

#ifdef URHO3D_URHO2D
// const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
static CScriptArray* StaticSprite2D_GetLights_void(StaticSprite2D* ptr)
{
    const PODVector<Light*>& result = ptr->GetLights();
    return VectorToHandleArray(result, "Array<Light@>");
}
#endif

#ifdef URHO3D_URHO2D
// const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
static CScriptArray* StaticSprite2D_GetVertexLights_void(StaticSprite2D* ptr)
{
    const PODVector<Light*>& result = ptr->GetVertexLights();
    return VectorToHandleArray(result, "Array<Light@>");
}
#endif

#ifdef URHO3D_URHO2D
// explicit StaticSprite2D::StaticSprite2D(Context* context) | File: ../Urho2D/StaticSprite2D.h
static StaticSprite2D* StaticSprite2D_StaticSprite2D_Context()
{
    return new StaticSprite2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void StaticSprite2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(StaticSprite2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_URHO2D
// const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
static CScriptArray* StretchableSprite2D_GetLights_void(StretchableSprite2D* ptr)
{
    const PODVector<Light*>& result = ptr->GetLights();
    return VectorToHandleArray(result, "Array<Light@>");
}
#endif

#ifdef URHO3D_URHO2D
// const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
static CScriptArray* StretchableSprite2D_GetVertexLights_void(StretchableSprite2D* ptr)
{
    const PODVector<Light*>& result = ptr->GetVertexLights();
    return VectorToHandleArray(result, "Array<Light@>");
}
#endif

#ifdef URHO3D_URHO2D
// explicit StretchableSprite2D::StretchableSprite2D(Context* context) | File: ../Urho2D/StretchableSprite2D.h
static StretchableSprite2D* StretchableSprite2D_StretchableSprite2D_Context()
{
    return new StretchableSprite2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void StretchableSprite2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(StretchableSprite2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

// void String::Join(const Vector<String>& subStrings, const String& glue) | File: ../Container/Str.h
static void String_Join_VectorString_String(String* ptr, CScriptArray* subStrings_conv, const String& glue)
{
    Vector<String> subStrings = ArrayToVector<String>(subStrings_conv);
    ptr->Join(subStrings, glue);
}

// Vector<String> String::Split(char separator, bool keepEmptyStrings=false) const | File: ../Container/Str.h
static CScriptArray* String_Split_char_bool(String* ptr, char separator, bool keepEmptyStrings)
{
    Vector<String> result = ptr->Split(separator, keepEmptyStrings);
    return VectorToArray<String>(result, "Array<String>");
}

// String::String(const String& str) | File: ../Container/Str.h
static void String_String_String(String* ptr, const String &str)
{
    new(ptr) String(str);
}

// explicit String::String(int value) | File: ../Container/Str.h
static void String_String_int(String* ptr, int value)
{
    new(ptr) String(value);
}

// explicit String::String(short value) | File: ../Container/Str.h
static void String_String_short(String* ptr, short value)
{
    new(ptr) String(value);
}

// explicit String::String(long long value) | File: ../Container/Str.h
static void String_String_longlong(String* ptr, long long value)
{
    new(ptr) String(value);
}

// explicit String::String(unsigned value) | File: ../Container/Str.h
static void String_String_unsigned(String* ptr, unsigned value)
{
    new(ptr) String(value);
}

// explicit String::String(unsigned short value) | File: ../Container/Str.h
static void String_String_unsignedshort(String* ptr, unsigned short value)
{
    new(ptr) String(value);
}

// explicit String::String(unsigned long long value) | File: ../Container/Str.h
static void String_String_unsignedlonglong(String* ptr, unsigned long long value)
{
    new(ptr) String(value);
}

// explicit String::String(float value) | File: ../Container/Str.h
static void String_String_float(String* ptr, float value)
{
    new(ptr) String(value);
}

// explicit String::String(double value) | File: ../Container/Str.h
static void String_String_double(String* ptr, double value)
{
    new(ptr) String(value);
}

// explicit String::String(bool value) | File: ../Container/Str.h
static void String_String_bool(String* ptr, bool value)
{
    new(ptr) String(value);
}

// explicit String::String(char value) | File: ../Container/Str.h
static void String_String_char(String* ptr, char value)
{
    new(ptr) String(value);
}

// explicit String::String(char value, unsigned length) | File: ../Container/Str.h
static void String_String_char_unsigned(String* ptr, char value, unsigned length)
{
    new(ptr) String(value, length);
}

// bool String::operator<(const String& rhs) const | File: ../Container/Str.h
// bool String::operator>(const String& rhs) const | File: ../Container/Str.h
static int String_Comparison(const String& lhs, const String& rhs)
{
    if (lhs < rhs)
        return -1;

    if (lhs > rhs)
        return 1;

    return 0;
}

// StringHash::StringHash(const StringHash& rhs) noexcept=default | File: ../Math/StringHash.h
static void StringHash_StringHash_StringHash(StringHash* ptr, const StringHash &rhs)
{
    new(ptr) StringHash(rhs);
}

// explicit StringHash::StringHash(unsigned value) noexcept | File: ../Math/StringHash.h
static void StringHash_StringHash_unsigned(StringHash* ptr, unsigned value)
{
    new(ptr) StringHash(value);
}

// StringHash::StringHash(const String& str) noexcept | File: ../Math/StringHash.h
static void StringHash_StringHash_String(StringHash* ptr, const String &str)
{
    new(ptr) StringHash(str);
}

// bool StringHash::operator<(const StringHash& rhs) const | File: ../Math/StringHash.h
// bool StringHash::operator>(const StringHash& rhs) const | File: ../Math/StringHash.h
static int StringHash_Comparison(const StringHash& lhs, const StringHash& rhs)
{
    if (lhs < rhs)
        return -1;

    if (lhs > rhs)
        return 1;

    return 0;
}

// StringHashRegister::StringHashRegister(bool threadSafe) | File: ../Core/StringHashRegister.h
static void StringHashRegister_StringHashRegister_bool(StringHashRegister* ptr, bool threadSafe)
{
    new(ptr) StringHashRegister(threadSafe);
}

// SourceBatch::SourceBatch(const SourceBatch& batch) | File: ../Graphics/Drawable.h
static void SourceBatch_SourceBatch_SourceBatch(SourceBatch* ptr, const SourceBatch &batch)
{
    new(ptr) SourceBatch(batch);
}

// StoredLogMessage::StoredLogMessage(const String& message, int level, bool error) | File: ../IO/Log.h
static void StoredLogMessage_StoredLogMessage_String_int_bool(StoredLogMessage* ptr, const String &message, int level, bool error)
{
    new(ptr) StoredLogMessage(message, level, error);
}

void ASRegisterGenerated_Members_Sn_Sz(asIScriptEngine* engine)
{
    // void ResourceWithMetadata::AddMetadata(const String& name, const Variant& value) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "void AddMetadata(const String&in, const Variant&in)", asMETHODPR(Sound, AddMetadata, (const String&, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "void set_metadata(const String&in, const Variant&in)", asMETHODPR(Sound, AddMetadata, (const String&, const Variant&), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Sound", asBEHAVE_ADDREF, "void f()", asMETHODPR(Sound, AddRef, (), void), asCALL_THISCALL);
    // bool Sound::BeginLoad(Deserializer& source) override | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "bool BeginLoad(Deserializer&)", asMETHODPR(Sound, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "bool EndLoad()", asMETHODPR(Sound, EndLoad, (), bool), asCALL_THISCALL);
    // void Sound::FixInterpolation() | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "void FixInterpolation()", asMETHODPR(Sound, FixInterpolation, (), void), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(Sound, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "bool GetBlockEvents() const", asMETHODPR(Sound, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "const String& GetCategory() const", asMETHODPR(Sound, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "const String& get_category() const", asMETHODPR(Sound, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // SharedArrayPtr<signed char> Sound::GetData() const | File: ../Audio/Sound.h
    // Error: type "SharedArrayPtr<signed char>" can not automatically bind
    // unsigned Sound::GetDataSize() const | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "uint GetDataSize() const", asMETHODPR(Sound, GetDataSize, () const, unsigned), asCALL_THISCALL);
    // SharedPtr<SoundStream> Sound::GetDecoderStream() const | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "SoundStream@+ GetDecoderStream() const", asFUNCTION(Sound_GetDecoderStream_void), asCALL_CDECL_OBJFIRST);
    // signed char* Sound::GetEnd() const | File: ../Audio/Sound.h
    // Error: type "signed char*" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "VariantMap& GetEventDataMap() const", asMETHODPR(Sound, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "Object@+ GetEventSender() const", asMETHODPR(Sound, GetEventSender, () const, Object*), asCALL_THISCALL);
    // float Sound::GetFrequency() const | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "float GetFrequency() const", asMETHODPR(Sound, GetFrequency, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "float get_frequency() const", asMETHODPR(Sound, GetFrequency, () const, float), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Sound, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Sound, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "const VariantMap& GetGlobalVars() const", asMETHODPR(Sound, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "const VariantMap& get_globalVars() const", asMETHODPR(Sound, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Sound::GetIntFrequency() const | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "uint GetIntFrequency() const", asMETHODPR(Sound, GetIntFrequency, () const, unsigned), asCALL_THISCALL);
    // float Sound::GetLength() const | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "float GetLength() const", asMETHODPR(Sound, GetLength, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "float get_length() const", asMETHODPR(Sound, GetLength, () const, float), asCALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "uint GetMemoryUse() const", asMETHODPR(Sound, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "uint get_memoryUse() const", asMETHODPR(Sound, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // const Variant& ResourceWithMetadata::GetMetadata(const String& name) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "const Variant& GetMetadata(const String&in) const", asMETHODPR(Sound, GetMetadata, (const String&) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "const Variant& get_metadata(const String&in) const", asMETHODPR(Sound, GetMetadata, (const String&) const, const Variant&), asCALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "const String& GetName() const", asMETHODPR(Sound, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "const String& get_name() const", asMETHODPR(Sound, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "StringHash GetNameHash() const", asMETHODPR(Sound, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // signed char* Sound::GetRepeat() const | File: ../Audio/Sound.h
    // Error: type "signed char*" can not automatically bind
    // unsigned Sound::GetSampleSize() const | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "uint GetSampleSize() const", asMETHODPR(Sound, GetSampleSize, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "uint get_sampleSize() const", asMETHODPR(Sound, GetSampleSize, () const, unsigned), asCALL_THISCALL);
    // signed char* Sound::GetStart() const | File: ../Audio/Sound.h
    // Error: type "signed char*" can not automatically bind
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Sound, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "StringHash GetType() const", asMETHODPR(Sound, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "StringHash get_type() const", asMETHODPR(Sound, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "const String& GetTypeName() const", asMETHODPR(Sound, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "const String& get_typeName() const", asMETHODPR(Sound, GetTypeName, () const, const String&), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "uint GetUseTimer()", asMETHODPR(Sound, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "uint get_useTimer()", asMETHODPR(Sound, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "bool HasEventHandlers() const", asMETHODPR(Sound, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool ResourceWithMetadata::HasMetadata() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "bool HasMetadata() const", asMETHODPR(Sound, HasMetadata, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "bool get_hasMetadata() const", asMETHODPR(Sound, HasMetadata, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Sound, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Sound, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Sound::IsCompressed() const | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "bool IsCompressed() const", asMETHODPR(Sound, IsCompressed, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "bool get_compressed() const", asMETHODPR(Sound, IsCompressed, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "bool IsInstanceOf(StringHash) const", asMETHODPR(Sound, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Sound::IsLooped() const | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "bool IsLooped() const", asMETHODPR(Sound, IsLooped, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "bool get_looped() const", asMETHODPR(Sound, IsLooped, () const, bool), asCALL_THISCALL);
    // bool Sound::IsSixteenBit() const | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "bool IsSixteenBit() const", asMETHODPR(Sound, IsSixteenBit, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "bool get_sixteenBit() const", asMETHODPR(Sound, IsSixteenBit, () const, bool), asCALL_THISCALL);
    // bool Sound::IsStereo() const | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "bool IsStereo() const", asMETHODPR(Sound, IsStereo, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "bool get_stereo() const", asMETHODPR(Sound, IsStereo, () const, bool), asCALL_THISCALL);
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "bool Load(Deserializer&)", asMETHODPR(Sound, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "bool LoadFile(const String&in)", asMETHODPR(Sound, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "bool Load(const String&in)", asMETHODPR(Sound, LoadFile, (const String&), bool), asCALL_THISCALL);
    // bool Sound::LoadOggVorbis(Deserializer& source) | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "bool LoadOggVorbis(Deserializer&)", asMETHODPR(Sound, LoadOggVorbis, (Deserializer&), bool), asCALL_THISCALL);
    // bool Sound::LoadRaw(Deserializer& source) | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "bool LoadRaw(Deserializer&)", asMETHODPR(Sound, LoadRaw, (Deserializer&), bool), asCALL_THISCALL);
    // bool Sound::LoadWav(Deserializer& source) | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "bool LoadWav(Deserializer&)", asMETHODPR(Sound, LoadWav, (Deserializer&), bool), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Sound, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Sound", "int Refs() const", asMETHODPR(Sound, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "int get_refs() const", asMETHODPR(Sound, Refs, () const, int), asCALL_THISCALL);
    // static void Sound::RegisterObject(Context* context) | File: ../Audio/Sound.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Sound", asBEHAVE_RELEASE, "void f()", asMETHODPR(Sound, ReleaseRef, (), void), asCALL_THISCALL);
    // void ResourceWithMetadata::RemoveAllMetadata() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "void RemoveAllMetadata()", asMETHODPR(Sound, RemoveAllMetadata, (), void), asCALL_THISCALL);
    // void ResourceWithMetadata::RemoveMetadata(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "void RemoveMetadata(const String&in)", asMETHODPR(Sound, RemoveMetadata, (const String&), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "void ResetUseTimer()", asMETHODPR(Sound, ResetUseTimer, (), void), asCALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "bool Save(Serializer&) const", asMETHODPR(Sound, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "bool SaveFile(const String&in) const", asMETHODPR(Sound, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "bool Save(const String&in) const", asMETHODPR(Sound, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "void SendEvent(StringHash)", asMETHODPR(Sound, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Sound, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(Sound, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "void SetBlockEvents(bool)", asMETHODPR(Sound, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Sound::SetData(const void* data, unsigned dataSize) | File: ../Audio/Sound.h
    // Error: type "const void*" can not automatically bind
    // void Sound::SetFormat(unsigned frequency, bool sixteenBit, bool stereo) | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "void SetFormat(uint, bool, bool)", asMETHODPR(Sound, SetFormat, (unsigned, bool, bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Sound, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Sound, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Sound::SetLoop(unsigned repeatOffset, unsigned endOffset) | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "void SetLoop(uint, uint)", asMETHODPR(Sound, SetLoop, (unsigned, unsigned), void), asCALL_THISCALL);
    // void Sound::SetLooped(bool enable) | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "void SetLooped(bool)", asMETHODPR(Sound, SetLooped, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "void set_looped(bool)", asMETHODPR(Sound, SetLooped, (bool), void), asCALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "void SetMemoryUse(uint)", asMETHODPR(Sound, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "void SetName(const String&in)", asMETHODPR(Sound, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "void set_name(const String&in)", asMETHODPR(Sound, SetName, (const String&), void), asCALL_THISCALL);
    // void Sound::SetSize(unsigned dataSize) | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "void SetSize(uint)", asMETHODPR(Sound, SetSize, (unsigned), void), asCALL_THISCALL);
    // explicit Sound::Sound(Context* context) | File: ../Audio/Sound.h
    engine->RegisterObjectBehaviour("Sound", asBEHAVE_FACTORY, "Sound@+ f()", asFUNCTION(Sound_Sound_Context), asCALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "void UnsubscribeFromAllEvents()", asMETHODPR(Sound, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Sound_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Sound, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Sound, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Sound, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Sound", "int WeakRefs() const", asMETHODPR(Sound, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "int get_weakRefs() const", asMETHODPR(Sound, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_ResourceWithMetadata
    REGISTER_MANUAL_PART_ResourceWithMetadata(Sound, "Sound")
#endif
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(Sound, "Sound")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Sound, "Sound")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Sound, "Sound")
#endif
#ifdef REGISTER_MANUAL_PART_Sound
    REGISTER_MANUAL_PART_Sound(Sound, "Sound")
#endif
    RegisterSubclass<ResourceWithMetadata, Sound>(engine, "ResourceWithMetadata", "Sound");
    RegisterSubclass<Resource, Sound>(engine, "Resource", "Sound");
    RegisterSubclass<Object, Sound>(engine, "Object", "Sound");
    RegisterSubclass<RefCounted, Sound>(engine, "RefCounted", "Sound");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("SoundListener", asBEHAVE_ADDREF, "void f()", asMETHODPR(SoundListener, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "void AllocateNetworkState()", asMETHODPR(SoundListener, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "void ApplyAttributes()", asMETHODPR(SoundListener, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(SoundListener, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "bool GetAnimationEnabled() const", asMETHODPR(SoundListener, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "bool get_animationEnabled() const", asMETHODPR(SoundListener, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "Variant GetAttribute(uint) const", asMETHODPR(SoundListener, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "Variant get_attributes(uint) const", asMETHODPR(SoundListener, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "Variant GetAttribute(const String&in) const", asMETHODPR(SoundListener, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(SoundListener, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(SoundListener, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(SoundListener, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(SoundListener, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "Variant GetAttributeDefault(uint) const", asMETHODPR(SoundListener, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "Variant get_attributeDefaults(uint) const", asMETHODPR(SoundListener, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(SoundListener, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "bool GetBlockEvents() const", asMETHODPR(SoundListener, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "const String& GetCategory() const", asMETHODPR(SoundListener, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "const String& get_category() const", asMETHODPR(SoundListener, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "Component@+ GetComponent(StringHash) const", asMETHODPR(SoundListener, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
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
    engine->RegisterObjectMethod("SoundListener", "VariantMap& GetEventDataMap() const", asMETHODPR(SoundListener, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "Object@+ GetEventSender() const", asMETHODPR(SoundListener, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(SoundListener, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "const Variant& get_globalVar(StringHash) const", asMETHODPR(SoundListener, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "const VariantMap& GetGlobalVars() const", asMETHODPR(SoundListener, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "const VariantMap& get_globalVars() const", asMETHODPR(SoundListener, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "uint GetID() const", asMETHODPR(SoundListener, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "uint get_id() const", asMETHODPR(SoundListener, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(SoundListener, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "Node@+ GetNode() const", asMETHODPR(SoundListener, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "Node@+ get_node() const", asMETHODPR(SoundListener, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "uint GetNumAttributes() const", asMETHODPR(SoundListener, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "uint get_numAttributes() const", asMETHODPR(SoundListener, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "uint GetNumNetworkAttributes() const", asMETHODPR(SoundListener, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(SoundListener, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(SoundListener, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(SoundListener, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "Scene@+ GetScene() const", asMETHODPR(SoundListener, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(SoundListener, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "StringHash GetType() const", asMETHODPR(SoundListener, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "StringHash get_type() const", asMETHODPR(SoundListener, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "const String& GetTypeName() const", asMETHODPR(SoundListener, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "const String& get_typeName() const", asMETHODPR(SoundListener, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "bool HasEventHandlers() const", asMETHODPR(SoundListener, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(SoundListener, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(SoundListener, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "bool IsEnabled() const", asMETHODPR(SoundListener, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "bool get_enabled() const", asMETHODPR(SoundListener, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "bool IsEnabledEffective() const", asMETHODPR(SoundListener, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "bool get_enabledEffective() const", asMETHODPR(SoundListener, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "bool IsInstanceOf(StringHash) const", asMETHODPR(SoundListener, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "bool IsReplicated() const", asMETHODPR(SoundListener, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "bool get_replicated() const", asMETHODPR(SoundListener, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "bool IsTemporary() const", asMETHODPR(SoundListener, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "bool get_temporary() const", asMETHODPR(SoundListener, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "bool Load(Deserializer&)", asMETHODPR(SoundListener, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "bool LoadJSON(const JSONValue&in)", asMETHODPR(SoundListener, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "bool LoadXML(const XMLElement&in)", asMETHODPR(SoundListener, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "void MarkNetworkUpdate()", asMETHODPR(SoundListener, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(SoundListener, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(SoundListener, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(SoundListener, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "void OnSetEnabled()", asMETHODPR(SoundListener, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "void PrepareNetworkUpdate()", asMETHODPR(SoundListener, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(SoundListener, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(SoundListener, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SoundListener", "int Refs() const", asMETHODPR(SoundListener, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "int get_refs() const", asMETHODPR(SoundListener, Refs, () const, int), asCALL_THISCALL);
    // static void SoundListener::RegisterObject(Context* context) | File: ../Audio/SoundListener.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("SoundListener", asBEHAVE_RELEASE, "void f()", asMETHODPR(SoundListener, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "void Remove()", asMETHODPR(SoundListener, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(SoundListener, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "void RemoveInstanceDefault()", asMETHODPR(SoundListener, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "void RemoveObjectAnimation()", asMETHODPR(SoundListener, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "void ResetToDefault()", asMETHODPR(SoundListener, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "bool Save(Serializer&) const", asMETHODPR(SoundListener, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "bool SaveDefaultAttributes() const", asMETHODPR(SoundListener, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "bool SaveJSON(JSONValue&) const", asMETHODPR(SoundListener, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "bool SaveXML(XMLElement&) const", asMETHODPR(SoundListener, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "void SendEvent(StringHash)", asMETHODPR(SoundListener, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(SoundListener, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "void SetAnimationEnabled(bool)", asMETHODPR(SoundListener, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "void set_animationEnabled(bool)", asMETHODPR(SoundListener, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "void SetAnimationTime(float)", asMETHODPR(SoundListener, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(SoundListener, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "bool set_attributes(uint, const Variant&in)", asMETHODPR(SoundListener, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(SoundListener, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(SoundListener, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(SoundListener, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(SoundListener, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(SoundListener, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "void SetBlockEvents(bool)", asMETHODPR(SoundListener, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "void SetEnabled(bool)", asMETHODPR(SoundListener, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "void set_enabled(bool)", asMETHODPR(SoundListener, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(SoundListener, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(SoundListener, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "void SetInstanceDefault(bool)", asMETHODPR(SoundListener, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(SoundListener, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(SoundListener, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(SoundListener, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(SoundListener, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "void SetTemporary(bool)", asMETHODPR(SoundListener, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "void set_temporary(bool)", asMETHODPR(SoundListener, SetTemporary, (bool), void), asCALL_THISCALL);
    // explicit SoundListener::SoundListener(Context* context) | File: ../Audio/SoundListener.h
    engine->RegisterObjectBehaviour("SoundListener", asBEHAVE_FACTORY, "SoundListener@+ f()", asFUNCTION(SoundListener_SoundListener_Context), asCALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "void UnsubscribeFromAllEvents()", asMETHODPR(SoundListener, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(SoundListener_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(SoundListener, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(SoundListener, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(SoundListener, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SoundListener", "int WeakRefs() const", asMETHODPR(SoundListener, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "int get_weakRefs() const", asMETHODPR(SoundListener, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(SoundListener, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(SoundListener, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(SoundListener, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(SoundListener, "SoundListener")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(SoundListener, "SoundListener")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(SoundListener, "SoundListener")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(SoundListener, "SoundListener")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(SoundListener, "SoundListener")
#endif
#ifdef REGISTER_MANUAL_PART_SoundListener
    REGISTER_MANUAL_PART_SoundListener(SoundListener, "SoundListener")
#endif
    RegisterSubclass<Component, SoundListener>(engine, "Component", "SoundListener");
    RegisterSubclass<Animatable, SoundListener>(engine, "Animatable", "SoundListener");
    RegisterSubclass<Serializable, SoundListener>(engine, "Serializable", "SoundListener");
    RegisterSubclass<Object, SoundListener>(engine, "Object", "SoundListener");
    RegisterSubclass<RefCounted, SoundListener>(engine, "RefCounted", "SoundListener");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("SoundSource", asBEHAVE_ADDREF, "void f()", asMETHODPR(SoundSource, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "void AllocateNetworkState()", asMETHODPR(SoundSource, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "void ApplyAttributes()", asMETHODPR(SoundSource, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(SoundSource, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "bool GetAnimationEnabled() const", asMETHODPR(SoundSource, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "bool get_animationEnabled() const", asMETHODPR(SoundSource, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // float SoundSource::GetAttenuation() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "float GetAttenuation() const", asMETHODPR(SoundSource, GetAttenuation, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "float get_attenuation() const", asMETHODPR(SoundSource, GetAttenuation, () const, float), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "Variant GetAttribute(uint) const", asMETHODPR(SoundSource, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "Variant get_attributes(uint) const", asMETHODPR(SoundSource, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "Variant GetAttribute(const String&in) const", asMETHODPR(SoundSource, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(SoundSource, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(SoundSource, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(SoundSource, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(SoundSource, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "Variant GetAttributeDefault(uint) const", asMETHODPR(SoundSource, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "Variant get_attributeDefaults(uint) const", asMETHODPR(SoundSource, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(SoundSource, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // AutoRemoveMode SoundSource::GetAutoRemoveMode() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "AutoRemoveMode GetAutoRemoveMode() const", asMETHODPR(SoundSource, GetAutoRemoveMode, () const, AutoRemoveMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "AutoRemoveMode get_autoRemoveMode() const", asMETHODPR(SoundSource, GetAutoRemoveMode, () const, AutoRemoveMode), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "bool GetBlockEvents() const", asMETHODPR(SoundSource, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "const String& GetCategory() const", asMETHODPR(SoundSource, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "const String& get_category() const", asMETHODPR(SoundSource, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "Component@+ GetComponent(StringHash) const", asMETHODPR(SoundSource, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
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
    engine->RegisterObjectMethod("SoundSource", "VariantMap& GetEventDataMap() const", asMETHODPR(SoundSource, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "Object@+ GetEventSender() const", asMETHODPR(SoundSource, GetEventSender, () const, Object*), asCALL_THISCALL);
    // float SoundSource::GetFrequency() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "float GetFrequency() const", asMETHODPR(SoundSource, GetFrequency, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "float get_frequency() const", asMETHODPR(SoundSource, GetFrequency, () const, float), asCALL_THISCALL);
    // float SoundSource::GetGain() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "float GetGain() const", asMETHODPR(SoundSource, GetGain, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "float get_gain() const", asMETHODPR(SoundSource, GetGain, () const, float), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(SoundSource, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "const Variant& get_globalVar(StringHash) const", asMETHODPR(SoundSource, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "const VariantMap& GetGlobalVars() const", asMETHODPR(SoundSource, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "const VariantMap& get_globalVars() const", asMETHODPR(SoundSource, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "uint GetID() const", asMETHODPR(SoundSource, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "uint get_id() const", asMETHODPR(SoundSource, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(SoundSource, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "Node@+ GetNode() const", asMETHODPR(SoundSource, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "Node@+ get_node() const", asMETHODPR(SoundSource, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "uint GetNumAttributes() const", asMETHODPR(SoundSource, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "uint get_numAttributes() const", asMETHODPR(SoundSource, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "uint GetNumNetworkAttributes() const", asMETHODPR(SoundSource, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(SoundSource, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(SoundSource, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(SoundSource, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float SoundSource::GetPanning() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "float GetPanning() const", asMETHODPR(SoundSource, GetPanning, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "float get_panning() const", asMETHODPR(SoundSource, GetPanning, () const, float), asCALL_THISCALL);
    // volatile signed char* SoundSource::GetPlayPosition() const | File: ../Audio/SoundSource.h
    // Error: type "signed char*" can not automatically bind
    // int SoundSource::GetPositionAttr() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "int GetPositionAttr() const", asMETHODPR(SoundSource, GetPositionAttr, () const, int), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "Scene@+ GetScene() const", asMETHODPR(SoundSource, GetScene, () const, Scene*), asCALL_THISCALL);
    // Sound* SoundSource::GetSound() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "Sound@+ GetSound() const", asMETHODPR(SoundSource, GetSound, () const, Sound*), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "Sound@+ get_sound() const", asMETHODPR(SoundSource, GetSound, () const, Sound*), asCALL_THISCALL);
    // ResourceRef SoundSource::GetSoundAttr() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "ResourceRef GetSoundAttr() const", asMETHODPR(SoundSource, GetSoundAttr, () const, ResourceRef), asCALL_THISCALL);
    // String SoundSource::GetSoundType() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "String GetSoundType() const", asMETHODPR(SoundSource, GetSoundType, () const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "String get_soundType() const", asMETHODPR(SoundSource, GetSoundType, () const, String), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(SoundSource, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // float SoundSource::GetTimePosition() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "float GetTimePosition() const", asMETHODPR(SoundSource, GetTimePosition, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "float get_timePosition() const", asMETHODPR(SoundSource, GetTimePosition, () const, float), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "StringHash GetType() const", asMETHODPR(SoundSource, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "StringHash get_type() const", asMETHODPR(SoundSource, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "const String& GetTypeName() const", asMETHODPR(SoundSource, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "const String& get_typeName() const", asMETHODPR(SoundSource, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "bool HasEventHandlers() const", asMETHODPR(SoundSource, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(SoundSource, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(SoundSource, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "bool IsEnabled() const", asMETHODPR(SoundSource, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "bool get_enabled() const", asMETHODPR(SoundSource, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "bool IsEnabledEffective() const", asMETHODPR(SoundSource, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "bool get_enabledEffective() const", asMETHODPR(SoundSource, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "bool IsInstanceOf(StringHash) const", asMETHODPR(SoundSource, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool SoundSource::IsPlaying() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "bool IsPlaying() const", asMETHODPR(SoundSource, IsPlaying, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "bool get_playing() const", asMETHODPR(SoundSource, IsPlaying, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "bool IsReplicated() const", asMETHODPR(SoundSource, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "bool get_replicated() const", asMETHODPR(SoundSource, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "bool IsTemporary() const", asMETHODPR(SoundSource, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "bool get_temporary() const", asMETHODPR(SoundSource, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "bool Load(Deserializer&)", asMETHODPR(SoundSource, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "bool LoadJSON(const JSONValue&in)", asMETHODPR(SoundSource, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "bool LoadXML(const XMLElement&in)", asMETHODPR(SoundSource, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "void MarkNetworkUpdate()", asMETHODPR(SoundSource, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // void SoundSource::Mix(int* dest, unsigned samples, int mixRate, bool stereo, bool interpolation) | File: ../Audio/SoundSource.h
    // Error: type "int*" can not automatically bind
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(SoundSource, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(SoundSource, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(SoundSource, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "void OnSetEnabled()", asMETHODPR(SoundSource, OnSetEnabled, (), void), asCALL_THISCALL);
    // void SoundSource::Play(Sound* sound) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void Play(Sound@+)", asMETHODPR(SoundSource, Play, (Sound*), void), asCALL_THISCALL);
    // void SoundSource::Play(Sound* sound, float frequency) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void Play(Sound@+, float)", asMETHODPR(SoundSource, Play, (Sound*, float), void), asCALL_THISCALL);
    // void SoundSource::Play(Sound* sound, float frequency, float gain) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void Play(Sound@+, float, float)", asMETHODPR(SoundSource, Play, (Sound*, float, float), void), asCALL_THISCALL);
    // void SoundSource::Play(Sound* sound, float frequency, float gain, float panning) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void Play(Sound@+, float, float, float)", asMETHODPR(SoundSource, Play, (Sound*, float, float, float), void), asCALL_THISCALL);
    // void SoundSource::Play(SoundStream* stream) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void Play(SoundStream@+)", asMETHODPR(SoundSource, Play, (SoundStream*), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "void PrepareNetworkUpdate()", asMETHODPR(SoundSource, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(SoundSource, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(SoundSource, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SoundSource", "int Refs() const", asMETHODPR(SoundSource, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "int get_refs() const", asMETHODPR(SoundSource, Refs, () const, int), asCALL_THISCALL);
    // static void SoundSource::RegisterObject(Context* context) | File: ../Audio/SoundSource.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("SoundSource", asBEHAVE_RELEASE, "void f()", asMETHODPR(SoundSource, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "void Remove()", asMETHODPR(SoundSource, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(SoundSource, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "void RemoveInstanceDefault()", asMETHODPR(SoundSource, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "void RemoveObjectAnimation()", asMETHODPR(SoundSource, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "void ResetToDefault()", asMETHODPR(SoundSource, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "bool Save(Serializer&) const", asMETHODPR(SoundSource, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "bool SaveDefaultAttributes() const", asMETHODPR(SoundSource, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "bool SaveJSON(JSONValue&) const", asMETHODPR(SoundSource, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "bool SaveXML(XMLElement&) const", asMETHODPR(SoundSource, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void SoundSource::Seek(float seekTime) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void Seek(float)", asMETHODPR(SoundSource, Seek, (float), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "void SendEvent(StringHash)", asMETHODPR(SoundSource, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(SoundSource, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "void SetAnimationEnabled(bool)", asMETHODPR(SoundSource, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "void set_animationEnabled(bool)", asMETHODPR(SoundSource, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "void SetAnimationTime(float)", asMETHODPR(SoundSource, SetAnimationTime, (float), void), asCALL_THISCALL);
    // void SoundSource::SetAttenuation(float attenuation) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void SetAttenuation(float)", asMETHODPR(SoundSource, SetAttenuation, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(SoundSource, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "bool set_attributes(uint, const Variant&in)", asMETHODPR(SoundSource, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(SoundSource, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(SoundSource, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(SoundSource, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(SoundSource, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(SoundSource, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void SoundSource::SetAutoRemoveMode(AutoRemoveMode mode) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void SetAutoRemoveMode(AutoRemoveMode)", asMETHODPR(SoundSource, SetAutoRemoveMode, (AutoRemoveMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "void set_autoRemoveMode(AutoRemoveMode)", asMETHODPR(SoundSource, SetAutoRemoveMode, (AutoRemoveMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "void SetBlockEvents(bool)", asMETHODPR(SoundSource, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "void SetEnabled(bool)", asMETHODPR(SoundSource, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "void set_enabled(bool)", asMETHODPR(SoundSource, SetEnabled, (bool), void), asCALL_THISCALL);
    // void SoundSource::SetFrequency(float frequency) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void SetFrequency(float)", asMETHODPR(SoundSource, SetFrequency, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "void set_frequency(float)", asMETHODPR(SoundSource, SetFrequency, (float), void), asCALL_THISCALL);
    // void SoundSource::SetGain(float gain) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void SetGain(float)", asMETHODPR(SoundSource, SetGain, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "void set_gain(float)", asMETHODPR(SoundSource, SetGain, (float), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(SoundSource, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(SoundSource, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "void SetInstanceDefault(bool)", asMETHODPR(SoundSource, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(SoundSource, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(SoundSource, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(SoundSource, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(SoundSource, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void SoundSource::SetPanning(float panning) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void SetPanning(float)", asMETHODPR(SoundSource, SetPanning, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "void set_panning(float)", asMETHODPR(SoundSource, SetPanning, (float), void), asCALL_THISCALL);
    // void SoundSource::SetPlayingAttr(bool value) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void SetPlayingAttr(bool)", asMETHODPR(SoundSource, SetPlayingAttr, (bool), void), asCALL_THISCALL);
    // void SoundSource::SetPlayPosition(signed char* pos) | File: ../Audio/SoundSource.h
    // Error: type "signed char*" can not automatically bind
    // void SoundSource::SetPositionAttr(int value) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void SetPositionAttr(int)", asMETHODPR(SoundSource, SetPositionAttr, (int), void), asCALL_THISCALL);
    // void SoundSource::SetSoundAttr(const ResourceRef& value) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void SetSoundAttr(const ResourceRef&in)", asMETHODPR(SoundSource, SetSoundAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void SoundSource::SetSoundType(const String& type) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void SetSoundType(const String&in)", asMETHODPR(SoundSource, SetSoundType, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "void set_soundType(const String&in)", asMETHODPR(SoundSource, SetSoundType, (const String&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "void SetTemporary(bool)", asMETHODPR(SoundSource, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "void set_temporary(bool)", asMETHODPR(SoundSource, SetTemporary, (bool), void), asCALL_THISCALL);
    // explicit SoundSource::SoundSource(Context* context) | File: ../Audio/SoundSource.h
    engine->RegisterObjectBehaviour("SoundSource", asBEHAVE_FACTORY, "SoundSource@+ f()", asFUNCTION(SoundSource_SoundSource_Context), asCALL_CDECL);
    // void SoundSource::Stop() | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void Stop()", asMETHODPR(SoundSource, Stop, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "void UnsubscribeFromAllEvents()", asMETHODPR(SoundSource, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(SoundSource_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(SoundSource, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(SoundSource, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(SoundSource, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void SoundSource::Update(float timeStep) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void Update(float)", asMETHODPR(SoundSource, Update, (float), void), asCALL_THISCALL);
    // void SoundSource::UpdateMasterGain() | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void UpdateMasterGain()", asMETHODPR(SoundSource, UpdateMasterGain, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SoundSource", "int WeakRefs() const", asMETHODPR(SoundSource, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "int get_weakRefs() const", asMETHODPR(SoundSource, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(SoundSource, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(SoundSource, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(SoundSource, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(SoundSource, "SoundSource")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(SoundSource, "SoundSource")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(SoundSource, "SoundSource")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(SoundSource, "SoundSource")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(SoundSource, "SoundSource")
#endif
#ifdef REGISTER_MANUAL_PART_SoundSource
    REGISTER_MANUAL_PART_SoundSource(SoundSource, "SoundSource")
#endif
    RegisterSubclass<Component, SoundSource>(engine, "Component", "SoundSource");
    RegisterSubclass<Animatable, SoundSource>(engine, "Animatable", "SoundSource");
    RegisterSubclass<Serializable, SoundSource>(engine, "Serializable", "SoundSource");
    RegisterSubclass<Object, SoundSource>(engine, "Object", "SoundSource");
    RegisterSubclass<RefCounted, SoundSource>(engine, "RefCounted", "SoundSource");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("SoundSource3D", asBEHAVE_ADDREF, "void f()", asMETHODPR(SoundSource3D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "void AllocateNetworkState()", asMETHODPR(SoundSource3D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "void ApplyAttributes()", asMETHODPR(SoundSource3D, ApplyAttributes, (), void), asCALL_THISCALL);
    // void SoundSource3D::CalculateAttenuation() | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "void CalculateAttenuation()", asMETHODPR(SoundSource3D, CalculateAttenuation, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void SoundSource3D::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(SoundSource3D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "bool GetAnimationEnabled() const", asMETHODPR(SoundSource3D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "bool get_animationEnabled() const", asMETHODPR(SoundSource3D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // float SoundSource::GetAttenuation() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "float GetAttenuation() const", asMETHODPR(SoundSource3D, GetAttenuation, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "float get_attenuation() const", asMETHODPR(SoundSource3D, GetAttenuation, () const, float), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "Variant GetAttribute(uint) const", asMETHODPR(SoundSource3D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "Variant get_attributes(uint) const", asMETHODPR(SoundSource3D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "Variant GetAttribute(const String&in) const", asMETHODPR(SoundSource3D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(SoundSource3D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(SoundSource3D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(SoundSource3D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(SoundSource3D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "Variant GetAttributeDefault(uint) const", asMETHODPR(SoundSource3D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "Variant get_attributeDefaults(uint) const", asMETHODPR(SoundSource3D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(SoundSource3D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // AutoRemoveMode SoundSource::GetAutoRemoveMode() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "AutoRemoveMode GetAutoRemoveMode() const", asMETHODPR(SoundSource3D, GetAutoRemoveMode, () const, AutoRemoveMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "AutoRemoveMode get_autoRemoveMode() const", asMETHODPR(SoundSource3D, GetAutoRemoveMode, () const, AutoRemoveMode), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "bool GetBlockEvents() const", asMETHODPR(SoundSource3D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "const String& GetCategory() const", asMETHODPR(SoundSource3D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "const String& get_category() const", asMETHODPR(SoundSource3D, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "Component@+ GetComponent(StringHash) const", asMETHODPR(SoundSource3D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
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
    engine->RegisterObjectMethod("SoundSource3D", "VariantMap& GetEventDataMap() const", asMETHODPR(SoundSource3D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "Object@+ GetEventSender() const", asMETHODPR(SoundSource3D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // float SoundSource3D::GetFarDistance() const | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "float GetFarDistance() const", asMETHODPR(SoundSource3D, GetFarDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "float get_farDistance() const", asMETHODPR(SoundSource3D, GetFarDistance, () const, float), asCALL_THISCALL);
    // float SoundSource::GetFrequency() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "float GetFrequency() const", asMETHODPR(SoundSource3D, GetFrequency, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "float get_frequency() const", asMETHODPR(SoundSource3D, GetFrequency, () const, float), asCALL_THISCALL);
    // float SoundSource::GetGain() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "float GetGain() const", asMETHODPR(SoundSource3D, GetGain, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "float get_gain() const", asMETHODPR(SoundSource3D, GetGain, () const, float), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(SoundSource3D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(SoundSource3D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "const VariantMap& GetGlobalVars() const", asMETHODPR(SoundSource3D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "const VariantMap& get_globalVars() const", asMETHODPR(SoundSource3D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "uint GetID() const", asMETHODPR(SoundSource3D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "uint get_id() const", asMETHODPR(SoundSource3D, GetID, () const, unsigned), asCALL_THISCALL);
    // float SoundSource3D::GetInnerAngle() const | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "float GetInnerAngle() const", asMETHODPR(SoundSource3D, GetInnerAngle, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "float get_innerAngle() const", asMETHODPR(SoundSource3D, GetInnerAngle, () const, float), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(SoundSource3D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // float SoundSource3D::GetNearDistance() const | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "float GetNearDistance() const", asMETHODPR(SoundSource3D, GetNearDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "float get_nearDistance() const", asMETHODPR(SoundSource3D, GetNearDistance, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "Node@+ GetNode() const", asMETHODPR(SoundSource3D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "Node@+ get_node() const", asMETHODPR(SoundSource3D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "uint GetNumAttributes() const", asMETHODPR(SoundSource3D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "uint get_numAttributes() const", asMETHODPR(SoundSource3D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "uint GetNumNetworkAttributes() const", asMETHODPR(SoundSource3D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(SoundSource3D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(SoundSource3D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(SoundSource3D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float SoundSource3D::GetOuterAngle() const | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "float GetOuterAngle() const", asMETHODPR(SoundSource3D, GetOuterAngle, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "float get_outerAngle() const", asMETHODPR(SoundSource3D, GetOuterAngle, () const, float), asCALL_THISCALL);
    // float SoundSource::GetPanning() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "float GetPanning() const", asMETHODPR(SoundSource3D, GetPanning, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "float get_panning() const", asMETHODPR(SoundSource3D, GetPanning, () const, float), asCALL_THISCALL);
    // volatile signed char* SoundSource::GetPlayPosition() const | File: ../Audio/SoundSource.h
    // Error: type "signed char*" can not automatically bind
    // int SoundSource::GetPositionAttr() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "int GetPositionAttr() const", asMETHODPR(SoundSource3D, GetPositionAttr, () const, int), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "Scene@+ GetScene() const", asMETHODPR(SoundSource3D, GetScene, () const, Scene*), asCALL_THISCALL);
    // Sound* SoundSource::GetSound() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "Sound@+ GetSound() const", asMETHODPR(SoundSource3D, GetSound, () const, Sound*), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "Sound@+ get_sound() const", asMETHODPR(SoundSource3D, GetSound, () const, Sound*), asCALL_THISCALL);
    // ResourceRef SoundSource::GetSoundAttr() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "ResourceRef GetSoundAttr() const", asMETHODPR(SoundSource3D, GetSoundAttr, () const, ResourceRef), asCALL_THISCALL);
    // String SoundSource::GetSoundType() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "String GetSoundType() const", asMETHODPR(SoundSource3D, GetSoundType, () const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "String get_soundType() const", asMETHODPR(SoundSource3D, GetSoundType, () const, String), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(SoundSource3D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // float SoundSource::GetTimePosition() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "float GetTimePosition() const", asMETHODPR(SoundSource3D, GetTimePosition, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "float get_timePosition() const", asMETHODPR(SoundSource3D, GetTimePosition, () const, float), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "StringHash GetType() const", asMETHODPR(SoundSource3D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "StringHash get_type() const", asMETHODPR(SoundSource3D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "const String& GetTypeName() const", asMETHODPR(SoundSource3D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "const String& get_typeName() const", asMETHODPR(SoundSource3D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "bool HasEventHandlers() const", asMETHODPR(SoundSource3D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(SoundSource3D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(SoundSource3D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "bool IsEnabled() const", asMETHODPR(SoundSource3D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "bool get_enabled() const", asMETHODPR(SoundSource3D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "bool IsEnabledEffective() const", asMETHODPR(SoundSource3D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "bool get_enabledEffective() const", asMETHODPR(SoundSource3D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "bool IsInstanceOf(StringHash) const", asMETHODPR(SoundSource3D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool SoundSource::IsPlaying() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "bool IsPlaying() const", asMETHODPR(SoundSource3D, IsPlaying, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "bool get_playing() const", asMETHODPR(SoundSource3D, IsPlaying, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "bool IsReplicated() const", asMETHODPR(SoundSource3D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "bool get_replicated() const", asMETHODPR(SoundSource3D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "bool IsTemporary() const", asMETHODPR(SoundSource3D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "bool get_temporary() const", asMETHODPR(SoundSource3D, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "bool Load(Deserializer&)", asMETHODPR(SoundSource3D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(SoundSource3D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "bool LoadXML(const XMLElement&in)", asMETHODPR(SoundSource3D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "void MarkNetworkUpdate()", asMETHODPR(SoundSource3D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // void SoundSource::Mix(int* dest, unsigned samples, int mixRate, bool stereo, bool interpolation) | File: ../Audio/SoundSource.h
    // Error: type "int*" can not automatically bind
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(SoundSource3D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(SoundSource3D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(SoundSource3D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "void OnSetEnabled()", asMETHODPR(SoundSource3D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void SoundSource::Play(Sound* sound) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void Play(Sound@+)", asMETHODPR(SoundSource3D, Play, (Sound*), void), asCALL_THISCALL);
    // void SoundSource::Play(Sound* sound, float frequency) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void Play(Sound@+, float)", asMETHODPR(SoundSource3D, Play, (Sound*, float), void), asCALL_THISCALL);
    // void SoundSource::Play(Sound* sound, float frequency, float gain) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void Play(Sound@+, float, float)", asMETHODPR(SoundSource3D, Play, (Sound*, float, float), void), asCALL_THISCALL);
    // void SoundSource::Play(Sound* sound, float frequency, float gain, float panning) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void Play(Sound@+, float, float, float)", asMETHODPR(SoundSource3D, Play, (Sound*, float, float, float), void), asCALL_THISCALL);
    // void SoundSource::Play(SoundStream* stream) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void Play(SoundStream@+)", asMETHODPR(SoundSource3D, Play, (SoundStream*), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "void PrepareNetworkUpdate()", asMETHODPR(SoundSource3D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(SoundSource3D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(SoundSource3D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SoundSource3D", "int Refs() const", asMETHODPR(SoundSource3D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "int get_refs() const", asMETHODPR(SoundSource3D, Refs, () const, int), asCALL_THISCALL);
    // static void SoundSource3D::RegisterObject(Context* context) | File: ../Audio/SoundSource3D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("SoundSource3D", asBEHAVE_RELEASE, "void f()", asMETHODPR(SoundSource3D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "void Remove()", asMETHODPR(SoundSource3D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(SoundSource3D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "void RemoveInstanceDefault()", asMETHODPR(SoundSource3D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "void RemoveObjectAnimation()", asMETHODPR(SoundSource3D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "void ResetToDefault()", asMETHODPR(SoundSource3D, ResetToDefault, (), void), asCALL_THISCALL);
    // float SoundSource3D::RollAngleoffFactor() const | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "float RollAngleoffFactor() const", asMETHODPR(SoundSource3D, RollAngleoffFactor, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "float get_rolloffFactor() const", asMETHODPR(SoundSource3D, RollAngleoffFactor, () const, float), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "bool Save(Serializer&) const", asMETHODPR(SoundSource3D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "bool SaveDefaultAttributes() const", asMETHODPR(SoundSource3D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "bool SaveJSON(JSONValue&) const", asMETHODPR(SoundSource3D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "bool SaveXML(XMLElement&) const", asMETHODPR(SoundSource3D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void SoundSource::Seek(float seekTime) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void Seek(float)", asMETHODPR(SoundSource3D, Seek, (float), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "void SendEvent(StringHash)", asMETHODPR(SoundSource3D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(SoundSource3D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void SoundSource3D::SetAngleAttenuation(float innerAngle, float outerAngle) | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetAngleAttenuation(float, float)", asMETHODPR(SoundSource3D, SetAngleAttenuation, (float, float), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetAnimationEnabled(bool)", asMETHODPR(SoundSource3D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_animationEnabled(bool)", asMETHODPR(SoundSource3D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetAnimationTime(float)", asMETHODPR(SoundSource3D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // void SoundSource::SetAttenuation(float attenuation) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetAttenuation(float)", asMETHODPR(SoundSource3D, SetAttenuation, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(SoundSource3D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(SoundSource3D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(SoundSource3D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(SoundSource3D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(SoundSource3D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(SoundSource3D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(SoundSource3D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void SoundSource::SetAutoRemoveMode(AutoRemoveMode mode) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetAutoRemoveMode(AutoRemoveMode)", asMETHODPR(SoundSource3D, SetAutoRemoveMode, (AutoRemoveMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_autoRemoveMode(AutoRemoveMode)", asMETHODPR(SoundSource3D, SetAutoRemoveMode, (AutoRemoveMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetBlockEvents(bool)", asMETHODPR(SoundSource3D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void SoundSource3D::SetDistanceAttenuation(float nearDistance, float farDistance, float rolloffFactor) | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetDistanceAttenuation(float, float, float)", asMETHODPR(SoundSource3D, SetDistanceAttenuation, (float, float, float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetEnabled(bool)", asMETHODPR(SoundSource3D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_enabled(bool)", asMETHODPR(SoundSource3D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void SoundSource3D::SetFarDistance(float distance) | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetFarDistance(float)", asMETHODPR(SoundSource3D, SetFarDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_farDistance(float)", asMETHODPR(SoundSource3D, SetFarDistance, (float), void), asCALL_THISCALL);
    // void SoundSource::SetFrequency(float frequency) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetFrequency(float)", asMETHODPR(SoundSource3D, SetFrequency, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_frequency(float)", asMETHODPR(SoundSource3D, SetFrequency, (float), void), asCALL_THISCALL);
    // void SoundSource::SetGain(float gain) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetGain(float)", asMETHODPR(SoundSource3D, SetGain, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_gain(float)", asMETHODPR(SoundSource3D, SetGain, (float), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(SoundSource3D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(SoundSource3D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void SoundSource3D::SetInnerAngle(float angle) | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetInnerAngle(float)", asMETHODPR(SoundSource3D, SetInnerAngle, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_innerAngle(float)", asMETHODPR(SoundSource3D, SetInnerAngle, (float), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetInstanceDefault(bool)", asMETHODPR(SoundSource3D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(SoundSource3D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void SoundSource3D::SetNearDistance(float distance) | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetNearDistance(float)", asMETHODPR(SoundSource3D, SetNearDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_nearDistance(float)", asMETHODPR(SoundSource3D, SetNearDistance, (float), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(SoundSource3D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(SoundSource3D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(SoundSource3D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void SoundSource3D::SetOuterAngle(float angle) | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetOuterAngle(float)", asMETHODPR(SoundSource3D, SetOuterAngle, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_outerAngle(float)", asMETHODPR(SoundSource3D, SetOuterAngle, (float), void), asCALL_THISCALL);
    // void SoundSource::SetPanning(float panning) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetPanning(float)", asMETHODPR(SoundSource3D, SetPanning, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_panning(float)", asMETHODPR(SoundSource3D, SetPanning, (float), void), asCALL_THISCALL);
    // void SoundSource::SetPlayingAttr(bool value) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetPlayingAttr(bool)", asMETHODPR(SoundSource3D, SetPlayingAttr, (bool), void), asCALL_THISCALL);
    // void SoundSource::SetPlayPosition(signed char* pos) | File: ../Audio/SoundSource.h
    // Error: type "signed char*" can not automatically bind
    // void SoundSource::SetPositionAttr(int value) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetPositionAttr(int)", asMETHODPR(SoundSource3D, SetPositionAttr, (int), void), asCALL_THISCALL);
    // void SoundSource3D::SetRolloffFactor(float factor) | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetRolloffFactor(float)", asMETHODPR(SoundSource3D, SetRolloffFactor, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_rolloffFactor(float)", asMETHODPR(SoundSource3D, SetRolloffFactor, (float), void), asCALL_THISCALL);
    // void SoundSource::SetSoundAttr(const ResourceRef& value) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetSoundAttr(const ResourceRef&in)", asMETHODPR(SoundSource3D, SetSoundAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void SoundSource::SetSoundType(const String& type) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetSoundType(const String&in)", asMETHODPR(SoundSource3D, SetSoundType, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_soundType(const String&in)", asMETHODPR(SoundSource3D, SetSoundType, (const String&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetTemporary(bool)", asMETHODPR(SoundSource3D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_temporary(bool)", asMETHODPR(SoundSource3D, SetTemporary, (bool), void), asCALL_THISCALL);
    // explicit SoundSource3D::SoundSource3D(Context* context) | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectBehaviour("SoundSource3D", asBEHAVE_FACTORY, "SoundSource3D@+ f()", asFUNCTION(SoundSource3D_SoundSource3D_Context), asCALL_CDECL);
    // void SoundSource::Stop() | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void Stop()", asMETHODPR(SoundSource3D, Stop, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "void UnsubscribeFromAllEvents()", asMETHODPR(SoundSource3D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(SoundSource3D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(SoundSource3D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(SoundSource3D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(SoundSource3D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void SoundSource3D::Update(float timeStep) override | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "void Update(float)", asMETHODPR(SoundSource3D, Update, (float), void), asCALL_THISCALL);
    // void SoundSource::UpdateMasterGain() | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void UpdateMasterGain()", asMETHODPR(SoundSource3D, UpdateMasterGain, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SoundSource3D", "int WeakRefs() const", asMETHODPR(SoundSource3D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "int get_weakRefs() const", asMETHODPR(SoundSource3D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(SoundSource3D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(SoundSource3D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(SoundSource3D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_SoundSource
    REGISTER_MANUAL_PART_SoundSource(SoundSource3D, "SoundSource3D")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(SoundSource3D, "SoundSource3D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(SoundSource3D, "SoundSource3D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(SoundSource3D, "SoundSource3D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(SoundSource3D, "SoundSource3D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(SoundSource3D, "SoundSource3D")
#endif
#ifdef REGISTER_MANUAL_PART_SoundSource3D
    REGISTER_MANUAL_PART_SoundSource3D(SoundSource3D, "SoundSource3D")
#endif
    RegisterSubclass<SoundSource, SoundSource3D>(engine, "SoundSource", "SoundSource3D");
    RegisterSubclass<Component, SoundSource3D>(engine, "Component", "SoundSource3D");
    RegisterSubclass<Animatable, SoundSource3D>(engine, "Animatable", "SoundSource3D");
    RegisterSubclass<Serializable, SoundSource3D>(engine, "Serializable", "SoundSource3D");
    RegisterSubclass<Object, SoundSource3D>(engine, "Object", "SoundSource3D");
    RegisterSubclass<RefCounted, SoundSource3D>(engine, "RefCounted", "SoundSource3D");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("SoundStream", asBEHAVE_ADDREF, "void f()", asMETHODPR(SoundStream, AddRef, (), void), asCALL_THISCALL);
    // virtual unsigned SoundStream::GetData(signed char* dest, unsigned numBytes)=0 | File: ../Audio/SoundStream.h
    // Error: type "signed char*" can not automatically bind
    // float SoundStream::GetFrequency() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("SoundStream", "float GetFrequency() const", asMETHODPR(SoundStream, GetFrequency, () const, float), asCALL_THISCALL);
    // unsigned SoundStream::GetIntFrequency() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("SoundStream", "uint GetIntFrequency() const", asMETHODPR(SoundStream, GetIntFrequency, () const, unsigned), asCALL_THISCALL);
    // unsigned SoundStream::GetSampleSize() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("SoundStream", "uint GetSampleSize() const", asMETHODPR(SoundStream, GetSampleSize, () const, unsigned), asCALL_THISCALL);
    // bool SoundStream::GetStopAtEnd() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("SoundStream", "bool GetStopAtEnd() const", asMETHODPR(SoundStream, GetStopAtEnd, () const, bool), asCALL_THISCALL);
    // bool SoundStream::IsSixteenBit() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("SoundStream", "bool IsSixteenBit() const", asMETHODPR(SoundStream, IsSixteenBit, () const, bool), asCALL_THISCALL);
    // bool SoundStream::IsStereo() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("SoundStream", "bool IsStereo() const", asMETHODPR(SoundStream, IsStereo, () const, bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SoundStream", "int Refs() const", asMETHODPR(SoundStream, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundStream", "int get_refs() const", asMETHODPR(SoundStream, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("SoundStream", asBEHAVE_RELEASE, "void f()", asMETHODPR(SoundStream, ReleaseRef, (), void), asCALL_THISCALL);
    // virtual bool SoundStream::Seek(unsigned sample_number) | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("SoundStream", "bool Seek(uint)", asMETHODPR(SoundStream, Seek, (unsigned), bool), asCALL_THISCALL);
    // void SoundStream::SetFormat(unsigned frequency, bool sixteenBit, bool stereo) | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("SoundStream", "void SetFormat(uint, bool, bool)", asMETHODPR(SoundStream, SetFormat, (unsigned, bool, bool), void), asCALL_THISCALL);
    // void SoundStream::SetStopAtEnd(bool enable) | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("SoundStream", "void SetStopAtEnd(bool)", asMETHODPR(SoundStream, SetStopAtEnd, (bool), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SoundStream", "int WeakRefs() const", asMETHODPR(SoundStream, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("SoundStream", "int get_weakRefs() const", asMETHODPR(SoundStream, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(SoundStream, "SoundStream")
#endif
#ifdef REGISTER_MANUAL_PART_SoundStream
    REGISTER_MANUAL_PART_SoundStream(SoundStream, "SoundStream")
#endif
    RegisterSubclass<RefCounted, SoundStream>(engine, "RefCounted", "SoundStream");

    // Vector3 Sphere::center_ | File: ../Math/Sphere.h
    engine->RegisterObjectProperty("Sphere", "Vector3 center", offsetof(Sphere, center_));
    // float Sphere::radius_ | File: ../Math/Sphere.h
    engine->RegisterObjectProperty("Sphere", "float radius", offsetof(Sphere, radius_));
    // void Sphere::Clear() | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "void Clear()", asMETHODPR(Sphere, Clear, (), void), asCALL_THISCALL);
    // void Sphere::Define(const Sphere& sphere) | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "void Define(const Sphere&in)", asMETHODPR(Sphere, Define, (const Sphere&), void), asCALL_THISCALL);
    // void Sphere::Define(const Vector3& center, float radius) | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "void Define(const Vector3&in, float)", asMETHODPR(Sphere, Define, (const Vector3&, float), void), asCALL_THISCALL);
    // void Sphere::Define(const Vector3* vertices, unsigned count) | File: ../Math/Sphere.h
    // Error: type "const Vector3*" can not automatically bind
    // void Sphere::Define(const BoundingBox& box) | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "void Define(const BoundingBox&in)", asMETHODPR(Sphere, Define, (const BoundingBox&), void), asCALL_THISCALL);
    // void Sphere::Define(const Frustum& frustum) | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "void Define(const Frustum&in)", asMETHODPR(Sphere, Define, (const Frustum&), void), asCALL_THISCALL);
    // void Sphere::Define(const Polyhedron& poly) | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "void Define(const Polyhedron&in)", asMETHODPR(Sphere, Define, (const Polyhedron&), void), asCALL_THISCALL);
    // bool Sphere::Defined() const | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "bool Defined() const", asMETHODPR(Sphere, Defined, () const, bool), asCALL_THISCALL);
    // float Sphere::Distance(const Vector3& point) const | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "float Distance(const Vector3&in) const", asMETHODPR(Sphere, Distance, (const Vector3&) const, float), asCALL_THISCALL);
    // Vector3 Sphere::GetLocalPoint(float theta, float phi) const | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "Vector3 GetLocalPoint(float, float) const", asMETHODPR(Sphere, GetLocalPoint, (float, float) const, Vector3), asCALL_THISCALL);
    // Vector3 Sphere::GetPoint(float theta, float phi) const | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "Vector3 GetPoint(float, float) const", asMETHODPR(Sphere, GetPoint, (float, float) const, Vector3), asCALL_THISCALL);
    // Intersection Sphere::IsInside(const Vector3& point) const | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "Intersection IsInside(const Vector3&in) const", asMETHODPR(Sphere, IsInside, (const Vector3&) const, Intersection), asCALL_THISCALL);
    // Intersection Sphere::IsInside(const Sphere& sphere) const | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "Intersection IsInside(const Sphere&in) const", asMETHODPR(Sphere, IsInside, (const Sphere&) const, Intersection), asCALL_THISCALL);
    // Intersection Sphere::IsInside(const BoundingBox& box) const | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "Intersection IsInside(const BoundingBox&in) const", asMETHODPR(Sphere, IsInside, (const BoundingBox&) const, Intersection), asCALL_THISCALL);
    // Intersection Sphere::IsInsideFast(const Sphere& sphere) const | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "Intersection IsInsideFast(const Sphere&in) const", asMETHODPR(Sphere, IsInsideFast, (const Sphere&) const, Intersection), asCALL_THISCALL);
    // Intersection Sphere::IsInsideFast(const BoundingBox& box) const | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "Intersection IsInsideFast(const BoundingBox&in) const", asMETHODPR(Sphere, IsInsideFast, (const BoundingBox&) const, Intersection), asCALL_THISCALL);
    // void Sphere::Merge(const Vector3& point) | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "void Merge(const Vector3&in)", asMETHODPR(Sphere, Merge, (const Vector3&), void), asCALL_THISCALL);
    // void Sphere::Merge(const Vector3* vertices, unsigned count) | File: ../Math/Sphere.h
    // Error: type "const Vector3*" can not automatically bind
    // void Sphere::Merge(const BoundingBox& box) | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "void Merge(const BoundingBox&in)", asMETHODPR(Sphere, Merge, (const BoundingBox&), void), asCALL_THISCALL);
    // void Sphere::Merge(const Frustum& frustum) | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "void Merge(const Frustum&in)", asMETHODPR(Sphere, Merge, (const Frustum&), void), asCALL_THISCALL);
    // void Sphere::Merge(const Polyhedron& poly) | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "void Merge(const Polyhedron&in)", asMETHODPR(Sphere, Merge, (const Polyhedron&), void), asCALL_THISCALL);
    // void Sphere::Merge(const Sphere& sphere) | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "void Merge(const Sphere&in)", asMETHODPR(Sphere, Merge, (const Sphere&), void), asCALL_THISCALL);
    // Sphere& Sphere::operator=(const Sphere& rhs) noexcept=default | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "Sphere& opAssign(const Sphere&in)", asMETHODPR(Sphere, operator=, (const Sphere&), Sphere&), asCALL_THISCALL);
    // bool Sphere::operator==(const Sphere& rhs) const | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "bool opEquals(const Sphere&in) const", asMETHODPR(Sphere, operator==, (const Sphere&) const, bool), asCALL_THISCALL);
    // Sphere::Sphere(const Sphere& sphere) noexcept=default | File: ../Math/Sphere.h
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const Sphere&in)", asFUNCTION(Sphere_Sphere_Sphere), asCALL_CDECL_OBJFIRST);
    // Sphere::Sphere(const Vector3& center, float radius) noexcept | File: ../Math/Sphere.h
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, float)", asFUNCTION(Sphere_Sphere_Vector3_float), asCALL_CDECL_OBJFIRST);
    // Sphere::Sphere(const Vector3* vertices, unsigned count) noexcept | File: ../Math/Sphere.h
    // Error: type "const Vector3*" can not automatically bind
    // explicit Sphere::Sphere(const BoundingBox& box) noexcept | File: ../Math/Sphere.h
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const BoundingBox&in)", asFUNCTION(Sphere_Sphere_BoundingBox), asCALL_CDECL_OBJFIRST);
    // explicit Sphere::Sphere(const Frustum& frustum) noexcept | File: ../Math/Sphere.h
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const Frustum&in)", asFUNCTION(Sphere_Sphere_Frustum), asCALL_CDECL_OBJFIRST);
    // explicit Sphere::Sphere(const Polyhedron& poly) noexcept | File: ../Math/Sphere.h
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const Polyhedron&in)", asFUNCTION(Sphere_Sphere_Polyhedron), asCALL_CDECL_OBJFIRST);
#ifdef REGISTER_MANUAL_PART_Sphere
    REGISTER_MANUAL_PART_Sphere(Sphere, "Sphere")
#endif

    // void Spline::AddKnot(const Variant& knot) | File: ../Core/Spline.h
    engine->RegisterObjectMethod("Spline", "void AddKnot(const Variant&in)", asMETHODPR(Spline, AddKnot, (const Variant&), void), asCALL_THISCALL);
    // void Spline::AddKnot(const Variant& knot, unsigned index) | File: ../Core/Spline.h
    engine->RegisterObjectMethod("Spline", "void AddKnot(const Variant&in, uint)", asMETHODPR(Spline, AddKnot, (const Variant&, unsigned), void), asCALL_THISCALL);
    // void Spline::Clear() | File: ../Core/Spline.h
    engine->RegisterObjectMethod("Spline", "void Clear()", asMETHODPR(Spline, Clear, (), void), asCALL_THISCALL);
    // InterpolationMode Spline::GetInterpolationMode() const | File: ../Core/Spline.h
    engine->RegisterObjectMethod("Spline", "InterpolationMode GetInterpolationMode() const", asMETHODPR(Spline, GetInterpolationMode, () const, InterpolationMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Spline", "InterpolationMode get_interpolationMode() const", asMETHODPR(Spline, GetInterpolationMode, () const, InterpolationMode), asCALL_THISCALL);
    // Variant Spline::GetKnot(unsigned index) const | File: ../Core/Spline.h
    engine->RegisterObjectMethod("Spline", "Variant GetKnot(uint) const", asMETHODPR(Spline, GetKnot, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Spline", "Variant get_knot(uint) const", asMETHODPR(Spline, GetKnot, (unsigned) const, Variant), asCALL_THISCALL);
    // const VariantVector& Spline::GetKnots() const | File: ../Core/Spline.h
    // Error: type "const VariantVector&" can not automatically bind
    // Variant Spline::GetPoint(float f) const | File: ../Core/Spline.h
    engine->RegisterObjectMethod("Spline", "Variant GetPoint(float) const", asMETHODPR(Spline, GetPoint, (float) const, Variant), asCALL_THISCALL);
    // Spline& Spline::operator=(const Spline& rhs)=default | File: ../Core/Spline.h
    engine->RegisterObjectMethod("Spline", "Spline& opAssign(const Spline&in)", asMETHODPR(Spline, operator=, (const Spline&), Spline&), asCALL_THISCALL);
    // bool Spline::operator==(const Spline& rhs) const | File: ../Core/Spline.h
    engine->RegisterObjectMethod("Spline", "bool opEquals(const Spline&in) const", asMETHODPR(Spline, operator==, (const Spline&) const, bool), asCALL_THISCALL);
    // void Spline::RemoveKnot() | File: ../Core/Spline.h
    engine->RegisterObjectMethod("Spline", "void RemoveKnot()", asMETHODPR(Spline, RemoveKnot, (), void), asCALL_THISCALL);
    // void Spline::RemoveKnot(unsigned index) | File: ../Core/Spline.h
    engine->RegisterObjectMethod("Spline", "void RemoveKnot(uint)", asMETHODPR(Spline, RemoveKnot, (unsigned), void), asCALL_THISCALL);
    // void Spline::SetInterpolationMode(InterpolationMode interpolationMode) | File: ../Core/Spline.h
    engine->RegisterObjectMethod("Spline", "void SetInterpolationMode(InterpolationMode)", asMETHODPR(Spline, SetInterpolationMode, (InterpolationMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Spline", "void set_interpolationMode(InterpolationMode)", asMETHODPR(Spline, SetInterpolationMode, (InterpolationMode), void), asCALL_THISCALL);
    // void Spline::SetKnot(const Variant& knot, unsigned index) | File: ../Core/Spline.h
    engine->RegisterObjectMethod("Spline", "void SetKnot(const Variant&in, uint)", asMETHODPR(Spline, SetKnot, (const Variant&, unsigned), void), asCALL_THISCALL);
    // void Spline::SetKnots(const Vector<Variant>& knots) | File: ../Core/Spline.h
    // Error: type "const Vector<Variant>&" can not automatically bind
    // explicit Spline::Spline(InterpolationMode mode) | File: ../Core/Spline.h
    engine->RegisterObjectBehaviour("Spline", asBEHAVE_CONSTRUCT, "void f(InterpolationMode)", asFUNCTION(Spline_Spline_InterpolationMode), asCALL_CDECL_OBJFIRST);
    // explicit Spline::Spline(const Vector<Variant>& knots, InterpolationMode mode=BEZIER_CURVE) | File: ../Core/Spline.h
    // Error: type "const Vector<Variant>&" can not automatically bind
    // Spline::Spline(const Spline& rhs)=default | File: ../Core/Spline.h
    engine->RegisterObjectBehaviour("Spline", asBEHAVE_CONSTRUCT, "void f(const Spline&in)", asFUNCTION(Spline_Spline_Spline), asCALL_CDECL_OBJFIRST);
#ifdef REGISTER_MANUAL_PART_Spline
    REGISTER_MANUAL_PART_Spline(Spline, "Spline")
#endif

    // void SplinePath::AddControlPoint(Node* point, unsigned index=M_MAX_UNSIGNED) | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "void AddControlPoint(Node@+, uint = M_MAX_UNSIGNED)", asMETHODPR(SplinePath, AddControlPoint, (Node*, unsigned), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("SplinePath", asBEHAVE_ADDREF, "void f()", asMETHODPR(SplinePath, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "void AllocateNetworkState()", asMETHODPR(SplinePath, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void SplinePath::ApplyAttributes() override | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "void ApplyAttributes()", asMETHODPR(SplinePath, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void SplinePath::ClearControlPoints() | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "void ClearControlPoints()", asMETHODPR(SplinePath, ClearControlPoints, (), void), asCALL_THISCALL);
    // void SplinePath::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(SplinePath, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "bool GetAnimationEnabled() const", asMETHODPR(SplinePath, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "bool get_animationEnabled() const", asMETHODPR(SplinePath, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "Variant GetAttribute(uint) const", asMETHODPR(SplinePath, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "Variant get_attributes(uint) const", asMETHODPR(SplinePath, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "Variant GetAttribute(const String&in) const", asMETHODPR(SplinePath, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(SplinePath, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(SplinePath, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(SplinePath, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(SplinePath, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "Variant GetAttributeDefault(uint) const", asMETHODPR(SplinePath, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "Variant get_attributeDefaults(uint) const", asMETHODPR(SplinePath, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(SplinePath, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "bool GetBlockEvents() const", asMETHODPR(SplinePath, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "const String& GetCategory() const", asMETHODPR(SplinePath, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "const String& get_category() const", asMETHODPR(SplinePath, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "Component@+ GetComponent(StringHash) const", asMETHODPR(SplinePath, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // unsigned SplinePath::GetControlledIdAttr() const | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "uint GetControlledIdAttr() const", asMETHODPR(SplinePath, GetControlledIdAttr, () const, unsigned), asCALL_THISCALL);
    // Node* SplinePath::GetControlledNode() const | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "Node@+ GetControlledNode() const", asMETHODPR(SplinePath, GetControlledNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "Node@+ get_controlledNode() const", asMETHODPR(SplinePath, GetControlledNode, () const, Node*), asCALL_THISCALL);
    // const VariantVector& SplinePath::GetControlPointIdsAttr() const | File: ../Scene/SplinePath.h
    // Error: type "const VariantVector&" can not automatically bind
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "VariantMap& GetEventDataMap() const", asMETHODPR(SplinePath, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "Object@+ GetEventSender() const", asMETHODPR(SplinePath, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(SplinePath, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "const Variant& get_globalVar(StringHash) const", asMETHODPR(SplinePath, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "const VariantMap& GetGlobalVars() const", asMETHODPR(SplinePath, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "const VariantMap& get_globalVars() const", asMETHODPR(SplinePath, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "uint GetID() const", asMETHODPR(SplinePath, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "uint get_id() const", asMETHODPR(SplinePath, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(SplinePath, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // InterpolationMode SplinePath::GetInterpolationMode() const | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "InterpolationMode GetInterpolationMode() const", asMETHODPR(SplinePath, GetInterpolationMode, () const, InterpolationMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "InterpolationMode get_interpolationMode() const", asMETHODPR(SplinePath, GetInterpolationMode, () const, InterpolationMode), asCALL_THISCALL);
    // float SplinePath::GetLength() const | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "float GetLength() const", asMETHODPR(SplinePath, GetLength, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "float get_length() const", asMETHODPR(SplinePath, GetLength, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "Node@+ GetNode() const", asMETHODPR(SplinePath, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "Node@+ get_node() const", asMETHODPR(SplinePath, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "uint GetNumAttributes() const", asMETHODPR(SplinePath, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "uint get_numAttributes() const", asMETHODPR(SplinePath, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "uint GetNumNetworkAttributes() const", asMETHODPR(SplinePath, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(SplinePath, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(SplinePath, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(SplinePath, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Vector3 SplinePath::GetPoint(float factor) const | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "Vector3 GetPoint(float) const", asMETHODPR(SplinePath, GetPoint, (float) const, Vector3), asCALL_THISCALL);
    // Vector3 SplinePath::GetPosition() const | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "Vector3 GetPosition() const", asMETHODPR(SplinePath, GetPosition, () const, Vector3), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "Scene@+ GetScene() const", asMETHODPR(SplinePath, GetScene, () const, Scene*), asCALL_THISCALL);
    // float SplinePath::GetSpeed() const | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "float GetSpeed() const", asMETHODPR(SplinePath, GetSpeed, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "float get_speed() const", asMETHODPR(SplinePath, GetSpeed, () const, float), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(SplinePath, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "StringHash GetType() const", asMETHODPR(SplinePath, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "StringHash get_type() const", asMETHODPR(SplinePath, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "const String& GetTypeName() const", asMETHODPR(SplinePath, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "const String& get_typeName() const", asMETHODPR(SplinePath, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "bool HasEventHandlers() const", asMETHODPR(SplinePath, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(SplinePath, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(SplinePath, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "bool IsEnabled() const", asMETHODPR(SplinePath, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "bool get_enabled() const", asMETHODPR(SplinePath, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "bool IsEnabledEffective() const", asMETHODPR(SplinePath, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "bool get_enabledEffective() const", asMETHODPR(SplinePath, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool SplinePath::IsFinished() const | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "bool IsFinished() const", asMETHODPR(SplinePath, IsFinished, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "bool get_isFinished() const", asMETHODPR(SplinePath, IsFinished, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "bool IsInstanceOf(StringHash) const", asMETHODPR(SplinePath, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "bool IsReplicated() const", asMETHODPR(SplinePath, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "bool get_replicated() const", asMETHODPR(SplinePath, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "bool IsTemporary() const", asMETHODPR(SplinePath, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "bool get_temporary() const", asMETHODPR(SplinePath, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "bool Load(Deserializer&)", asMETHODPR(SplinePath, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "bool LoadJSON(const JSONValue&in)", asMETHODPR(SplinePath, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "bool LoadXML(const XMLElement&in)", asMETHODPR(SplinePath, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "void MarkNetworkUpdate()", asMETHODPR(SplinePath, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // void SplinePath::Move(float timeStep) | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "void Move(float)", asMETHODPR(SplinePath, Move, (float), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(SplinePath, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(SplinePath, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(SplinePath, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "void OnSetEnabled()", asMETHODPR(SplinePath, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "void PrepareNetworkUpdate()", asMETHODPR(SplinePath, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(SplinePath, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(SplinePath, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SplinePath", "int Refs() const", asMETHODPR(SplinePath, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "int get_refs() const", asMETHODPR(SplinePath, Refs, () const, int), asCALL_THISCALL);
    // static void SplinePath::RegisterObject(Context* context) | File: ../Scene/SplinePath.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("SplinePath", asBEHAVE_RELEASE, "void f()", asMETHODPR(SplinePath, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "void Remove()", asMETHODPR(SplinePath, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(SplinePath, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void SplinePath::RemoveControlPoint(Node* point) | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "void RemoveControlPoint(Node@+)", asMETHODPR(SplinePath, RemoveControlPoint, (Node*), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "void RemoveInstanceDefault()", asMETHODPR(SplinePath, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "void RemoveObjectAnimation()", asMETHODPR(SplinePath, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void SplinePath::Reset() | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "void Reset()", asMETHODPR(SplinePath, Reset, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "void ResetToDefault()", asMETHODPR(SplinePath, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "bool Save(Serializer&) const", asMETHODPR(SplinePath, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "bool SaveDefaultAttributes() const", asMETHODPR(SplinePath, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "bool SaveJSON(JSONValue&) const", asMETHODPR(SplinePath, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "bool SaveXML(XMLElement&) const", asMETHODPR(SplinePath, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "void SendEvent(StringHash)", asMETHODPR(SplinePath, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(SplinePath, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "void SetAnimationEnabled(bool)", asMETHODPR(SplinePath, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_animationEnabled(bool)", asMETHODPR(SplinePath, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "void SetAnimationTime(float)", asMETHODPR(SplinePath, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(SplinePath, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "bool set_attributes(uint, const Variant&in)", asMETHODPR(SplinePath, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(SplinePath, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(SplinePath, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(SplinePath, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(SplinePath, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(SplinePath, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "void SetBlockEvents(bool)", asMETHODPR(SplinePath, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void SplinePath::SetControlledIdAttr(unsigned value) | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "void SetControlledIdAttr(uint)", asMETHODPR(SplinePath, SetControlledIdAttr, (unsigned), void), asCALL_THISCALL);
    // void SplinePath::SetControlledNode(Node* controlled) | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "void SetControlledNode(Node@+)", asMETHODPR(SplinePath, SetControlledNode, (Node*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_controlledNode(Node@+)", asMETHODPR(SplinePath, SetControlledNode, (Node*), void), asCALL_THISCALL);
    // void SplinePath::SetControlPointIdsAttr(const VariantVector& value) | File: ../Scene/SplinePath.h
    // Error: type "const VariantVector&" can not automatically bind
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "void SetEnabled(bool)", asMETHODPR(SplinePath, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_enabled(bool)", asMETHODPR(SplinePath, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(SplinePath, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(SplinePath, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "void SetInstanceDefault(bool)", asMETHODPR(SplinePath, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(SplinePath, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void SplinePath::SetInterpolationMode(InterpolationMode interpolationMode) | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "void SetInterpolationMode(InterpolationMode)", asMETHODPR(SplinePath, SetInterpolationMode, (InterpolationMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_interpolationMode(InterpolationMode)", asMETHODPR(SplinePath, SetInterpolationMode, (InterpolationMode), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(SplinePath, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(SplinePath, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(SplinePath, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void SplinePath::SetPosition(float factor) | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "void SetPosition(float)", asMETHODPR(SplinePath, SetPosition, (float), void), asCALL_THISCALL);
    // void SplinePath::SetSpeed(float speed) | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "void SetSpeed(float)", asMETHODPR(SplinePath, SetSpeed, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_speed(float)", asMETHODPR(SplinePath, SetSpeed, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "void SetTemporary(bool)", asMETHODPR(SplinePath, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_temporary(bool)", asMETHODPR(SplinePath, SetTemporary, (bool), void), asCALL_THISCALL);
    // explicit SplinePath::SplinePath(Context* context) | File: ../Scene/SplinePath.h
    engine->RegisterObjectBehaviour("SplinePath", asBEHAVE_FACTORY, "SplinePath@+ f()", asFUNCTION(SplinePath_SplinePath_Context), asCALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "void UnsubscribeFromAllEvents()", asMETHODPR(SplinePath, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(SplinePath_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(SplinePath, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(SplinePath, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(SplinePath, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SplinePath", "int WeakRefs() const", asMETHODPR(SplinePath, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "int get_weakRefs() const", asMETHODPR(SplinePath, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(SplinePath, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(SplinePath, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(SplinePath, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(SplinePath, "SplinePath")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(SplinePath, "SplinePath")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(SplinePath, "SplinePath")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(SplinePath, "SplinePath")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(SplinePath, "SplinePath")
#endif
#ifdef REGISTER_MANUAL_PART_SplinePath
    REGISTER_MANUAL_PART_SplinePath(SplinePath, "SplinePath")
#endif
    RegisterSubclass<Component, SplinePath>(engine, "Component", "SplinePath");
    RegisterSubclass<Animatable, SplinePath>(engine, "Animatable", "SplinePath");
    RegisterSubclass<Serializable, SplinePath>(engine, "Serializable", "SplinePath");
    RegisterSubclass<Object, SplinePath>(engine, "Object", "SplinePath");
    RegisterSubclass<RefCounted, SplinePath>(engine, "RefCounted", "SplinePath");

    // void UIElement::AddChild(UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void AddChild(UIElement@+)", asMETHODPR(Sprite, AddChild, (UIElement*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Sprite", asBEHAVE_ADDREF, "void f()", asMETHODPR(Sprite, AddRef, (), void), asCALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void AddTag(const String&in)", asMETHODPR(Sprite, AddTag, (const String&), void), asCALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void AddTags(const String&in, int8 = ';')", asMETHODPR(Sprite, AddTags, (const String&, char), void), asCALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void AddTags(Array<String>@+)", asFUNCTION(Sprite_AddTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void AdjustScissor(IntRect&)", asMETHODPR(Sprite, AdjustScissor, (IntRect&), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "void AllocateNetworkState()", asMETHODPR(Sprite, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void ApplyAttributes()", asMETHODPR(Sprite, ApplyAttributes, (), void), asCALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void BringToFront()", asMETHODPR(Sprite, BringToFront, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", asMETHODPR(Sprite, CreateChild, (StringHash, const String&, unsigned), UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void DisableLayoutUpdate()", asMETHODPR(Sprite, DisableLayoutUpdate, (), void), asCALL_THISCALL);
    // IntVector2 Sprite::ElementToScreen(const IntVector2& position) override | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "IntVector2 ElementToScreen(const IntVector2&in)", asMETHODPR(Sprite, ElementToScreen, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void EnableLayoutUpdate()", asMETHODPR(Sprite, EnableLayoutUpdate, (), void), asCALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool FilterAttributes(XMLElement&) const", asMETHODPR(Sprite, FilterAttributes, (XMLElement&) const, bool), asCALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "uint FindChild(UIElement@+) const", asMETHODPR(Sprite, FindChild, (UIElement*) const, unsigned), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "bool GetAnimationEnabled() const", asMETHODPR(Sprite, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_animationEnabled() const", asMETHODPR(Sprite, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const String& GetAppliedStyle() const", asMETHODPR(Sprite, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const String& get_style() const", asMETHODPR(Sprite, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "Variant GetAttribute(uint) const", asMETHODPR(Sprite, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "Variant get_attributes(uint) const", asMETHODPR(Sprite, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "Variant GetAttribute(const String&in) const", asMETHODPR(Sprite, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(Sprite, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(Sprite, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(Sprite, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(Sprite, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "Variant GetAttributeDefault(uint) const", asMETHODPR(Sprite, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "Variant get_attributeDefaults(uint) const", asMETHODPR(Sprite, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Sprite, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // void Sprite::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/Sprite.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode Sprite::GetBlendMode() const | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "BlendMode GetBlendMode() const", asMETHODPR(Sprite, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "BlendMode get_blendMode() const", asMETHODPR(Sprite, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "bool GetBlockEvents() const", asMETHODPR(Sprite, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool GetBringToBack() const", asMETHODPR(Sprite, GetBringToBack, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_bringToBack() const", asMETHODPR(Sprite, GetBringToBack, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool GetBringToFront() const", asMETHODPR(Sprite, GetBringToFront, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_bringToFront() const", asMETHODPR(Sprite, GetBringToFront, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "const String& GetCategory() const", asMETHODPR(Sprite, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const String& get_category() const", asMETHODPR(Sprite, GetCategory, () const, const String&), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "UIElement@+ GetChild(uint) const", asMETHODPR(Sprite, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "UIElement@+ get_children(uint) const", asMETHODPR(Sprite, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "UIElement@+ GetChild(const String&in, bool = false) const", asMETHODPR(Sprite, GetChild, (const String&, bool) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", asMETHODPR(Sprite, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const IntVector2& GetChildOffset() const", asMETHODPR(Sprite, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const IntVector2& get_childOffset() const", asMETHODPR(Sprite, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "Array<UIElement@>@ GetChildren() const", asFUNCTION(Sprite_GetChildren_void), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "Array<UIElement@>@ GetChildren(bool) const", asFUNCTION(Sprite_GetChildren_bool), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", asFUNCTION(Sprite_GetChildrenWithTag_String_bool), asCALL_CDECL_OBJFIRST);
    // template<class T> T*  UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const IntRect& GetClipBorder() const", asMETHODPR(Sprite, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const IntRect& get_clipBorder() const", asMETHODPR(Sprite, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool GetClipChildren() const", asMETHODPR(Sprite, GetClipChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_clipChildren() const", asMETHODPR(Sprite, GetClipChildren, () const, bool), asCALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const Color& GetColor(Corner) const", asMETHODPR(Sprite, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const Color& get_colors(Corner) const", asMETHODPR(Sprite, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const Color& GetColorAttr() const", asMETHODPR(Sprite, GetColorAttr, () const, const Color&), asCALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "IntRect GetCombinedScreenRect()", asMETHODPR(Sprite, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "IntRect get_combinedScreenRect()", asMETHODPR(Sprite, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "XMLFile@+ GetDefaultStyle(bool = true) const", asMETHODPR(Sprite, GetDefaultStyle, (bool) const, XMLFile*), asCALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const Color& GetDerivedColor() const", asMETHODPR(Sprite, GetDerivedColor, () const, const Color&), asCALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "float GetDerivedOpacity() const", asMETHODPR(Sprite, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "float get_derivedOpacity() const", asMETHODPR(Sprite, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "MouseButtonFlags GetDragButtonCombo() const", asMETHODPR(Sprite, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "MouseButtonFlags get_dragButtonCombo() const", asMETHODPR(Sprite, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "uint GetDragButtonCount() const", asMETHODPR(Sprite, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "uint get_dragButtonCount() const", asMETHODPR(Sprite, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "DragAndDropModeFlags GetDragDropMode() const", asMETHODPR(Sprite, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "DragAndDropModeFlags get_dragDropMode() const", asMETHODPR(Sprite, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "IntVector2 GetEffectiveMinSize() const", asMETHODPR(Sprite, GetEffectiveMinSize, () const, IntVector2), asCALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "UIElement@+ GetElementEventSender() const", asMETHODPR(Sprite, GetElementEventSender, () const, UIElement*), asCALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool GetEnableAnchor() const", asMETHODPR(Sprite, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_enableAnchor() const", asMETHODPR(Sprite, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "VariantMap& GetEventDataMap() const", asMETHODPR(Sprite, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "Object@+ GetEventSender() const", asMETHODPR(Sprite, GetEventSender, () const, Object*), asCALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "FocusMode GetFocusMode() const", asMETHODPR(Sprite, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "FocusMode get_focusMode() const", asMETHODPR(Sprite, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Sprite, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Sprite, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "const VariantMap& GetGlobalVars() const", asMETHODPR(Sprite, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const VariantMap& get_globalVars() const", asMETHODPR(Sprite, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "int GetHeight() const", asMETHODPR(Sprite, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_height() const", asMETHODPR(Sprite, GetHeight, () const, int), asCALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "HorizontalAlignment GetHorizontalAlignment() const", asMETHODPR(Sprite, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "HorizontalAlignment get_horizontalAlignment() const", asMETHODPR(Sprite, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    // const IntVector2& Sprite::GetHotSpot() const | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "const IntVector2& GetHotSpot() const", asMETHODPR(Sprite, GetHotSpot, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const IntVector2& get_hotSpot() const", asMETHODPR(Sprite, GetHotSpot, () const, const IntVector2&), asCALL_THISCALL);
    // const IntRect& Sprite::GetImageRect() const | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "const IntRect& GetImageRect() const", asMETHODPR(Sprite, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const IntRect& get_imageRect() const", asMETHODPR(Sprite, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "int GetIndent() const", asMETHODPR(Sprite, GetIndent, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_indent() const", asMETHODPR(Sprite, GetIndent, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "int GetIndentSpacing() const", asMETHODPR(Sprite, GetIndentSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_indentSpacing() const", asMETHODPR(Sprite, GetIndentSpacing, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "int GetIndentWidth() const", asMETHODPR(Sprite, GetIndentWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_indentWidth() const", asMETHODPR(Sprite, GetIndentWidth, () const, int), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Sprite, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const IntRect& GetLayoutBorder() const", asMETHODPR(Sprite, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const IntRect& get_layoutBorder() const", asMETHODPR(Sprite, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "int GetLayoutElementMaxSize() const", asMETHODPR(Sprite, GetLayoutElementMaxSize, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const Vector2& GetLayoutFlexScale() const", asMETHODPR(Sprite, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const Vector2& get_layoutFlexScale() const", asMETHODPR(Sprite, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "LayoutMode GetLayoutMode() const", asMETHODPR(Sprite, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "LayoutMode get_layoutMode() const", asMETHODPR(Sprite, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "int GetLayoutSpacing() const", asMETHODPR(Sprite, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_layoutSpacing() const", asMETHODPR(Sprite, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const Vector2& GetMaxAnchor() const", asMETHODPR(Sprite, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const Vector2& get_maxAnchor() const", asMETHODPR(Sprite, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "int GetMaxHeight() const", asMETHODPR(Sprite, GetMaxHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_maxHeight() const", asMETHODPR(Sprite, GetMaxHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const IntVector2& GetMaxOffset() const", asMETHODPR(Sprite, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const IntVector2& get_maxOffset() const", asMETHODPR(Sprite, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const IntVector2& GetMaxSize() const", asMETHODPR(Sprite, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const IntVector2& get_maxSize() const", asMETHODPR(Sprite, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "int GetMaxWidth() const", asMETHODPR(Sprite, GetMaxWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_maxWidth() const", asMETHODPR(Sprite, GetMaxWidth, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const Vector2& GetMinAnchor() const", asMETHODPR(Sprite, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const Vector2& get_minAnchor() const", asMETHODPR(Sprite, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "int GetMinHeight() const", asMETHODPR(Sprite, GetMinHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_minHeight() const", asMETHODPR(Sprite, GetMinHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const IntVector2& GetMinOffset() const", asMETHODPR(Sprite, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const IntVector2& get_minOffset() const", asMETHODPR(Sprite, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const IntVector2& GetMinSize() const", asMETHODPR(Sprite, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const IntVector2& get_minSize() const", asMETHODPR(Sprite, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "int GetMinWidth() const", asMETHODPR(Sprite, GetMinWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_minWidth() const", asMETHODPR(Sprite, GetMinWidth, () const, int), asCALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const String& GetName() const", asMETHODPR(Sprite, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const String& get_name() const", asMETHODPR(Sprite, GetName, () const, const String&), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "uint GetNumAttributes() const", asMETHODPR(Sprite, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "uint get_numAttributes() const", asMETHODPR(Sprite, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "uint GetNumChildren(bool = false) const", asMETHODPR(Sprite, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "uint get_numChildren(bool = false) const", asMETHODPR(Sprite, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "uint GetNumNetworkAttributes() const", asMETHODPR(Sprite, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(Sprite, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(Sprite, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(Sprite, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "float GetOpacity() const", asMETHODPR(Sprite, GetOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "float get_opacity() const", asMETHODPR(Sprite, GetOpacity, () const, float), asCALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "UIElement@+ GetParent() const", asMETHODPR(Sprite, GetParent, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "UIElement@+ get_parent() const", asMETHODPR(Sprite, GetParent, () const, UIElement*), asCALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const Vector2& GetPivot() const", asMETHODPR(Sprite, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const Vector2& get_pivot() const", asMETHODPR(Sprite, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    // const Vector2& Sprite::GetPosition() const | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "const Vector2& GetPosition() const", asMETHODPR(Sprite, GetPosition, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const Vector2& get_position() const", asMETHODPR(Sprite, GetPosition, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "int GetPriority() const", asMETHODPR(Sprite, GetPriority, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_priority() const", asMETHODPR(Sprite, GetPriority, () const, int), asCALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "UIElement@+ GetRoot() const", asMETHODPR(Sprite, GetRoot, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "UIElement@+ get_root() const", asMETHODPR(Sprite, GetRoot, () const, UIElement*), asCALL_THISCALL);
    // float Sprite::GetRotation() const | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "float GetRotation() const", asMETHODPR(Sprite, GetRotation, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "float get_rotation() const", asMETHODPR(Sprite, GetRotation, () const, float), asCALL_THISCALL);
    // const Vector2& Sprite::GetScale() const | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "const Vector2& GetScale() const", asMETHODPR(Sprite, GetScale, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const Vector2& get_scale() const", asMETHODPR(Sprite, GetScale, () const, const Vector2&), asCALL_THISCALL);
    // const IntVector2& Sprite::GetScreenPosition() const override | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "const IntVector2& GetScreenPosition() const", asMETHODPR(Sprite, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const IntVector2& get_screenPosition() const", asMETHODPR(Sprite, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const IntVector2& GetSize() const", asMETHODPR(Sprite, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const IntVector2& get_size() const", asMETHODPR(Sprite, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool GetSortChildren() const", asMETHODPR(Sprite, GetSortChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_sortChildren() const", asMETHODPR(Sprite, GetSortChildren, () const, bool), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Sprite, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "Array<String>@ GetTags() const", asFUNCTION(Sprite_GetTags_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Sprite", "Array<String>@ get_tags() const", asFUNCTION(Sprite_GetTags_void), asCALL_CDECL_OBJFIRST);
    // Texture* Sprite::GetTexture() const | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "Texture@+ GetTexture() const", asMETHODPR(Sprite, GetTexture, () const, Texture*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "Texture@+ get_texture() const", asMETHODPR(Sprite, GetTexture, () const, Texture*), asCALL_THISCALL);
    // ResourceRef Sprite::GetTextureAttr() const | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "ResourceRef GetTextureAttr() const", asMETHODPR(Sprite, GetTextureAttr, () const, ResourceRef), asCALL_THISCALL);
    // const Matrix3x4& Sprite::GetTransform() const | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "const Matrix3x4& GetTransform() const", asMETHODPR(Sprite, GetTransform, () const, const Matrix3x4&), asCALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "TraversalMode GetTraversalMode() const", asMETHODPR(Sprite, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "TraversalMode get_traversalMode() const", asMETHODPR(Sprite, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "StringHash GetType() const", asMETHODPR(Sprite, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "StringHash get_type() const", asMETHODPR(Sprite, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "const String& GetTypeName() const", asMETHODPR(Sprite, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const String& get_typeName() const", asMETHODPR(Sprite, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool GetUseDerivedOpacity() const", asMETHODPR(Sprite, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_useDerivedOpacity() const", asMETHODPR(Sprite, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const Variant& GetVar(const StringHash&in) const", asMETHODPR(Sprite, GetVar, (const StringHash&) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const VariantMap& GetVars() const", asMETHODPR(Sprite, GetVars, () const, const VariantMap&), asCALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "VerticalAlignment GetVerticalAlignment() const", asMETHODPR(Sprite, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "VerticalAlignment get_verticalAlignment() const", asMETHODPR(Sprite, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "int GetWidth() const", asMETHODPR(Sprite, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_width() const", asMETHODPR(Sprite, GetWidth, () const, int), asCALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool HasColorGradient() const", asMETHODPR(Sprite, HasColorGradient, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_colorGradient() const", asMETHODPR(Sprite, HasColorGradient, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "bool HasEventHandlers() const", asMETHODPR(Sprite, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool HasFocus() const", asMETHODPR(Sprite, HasFocus, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_focus() const", asMETHODPR(Sprite, HasFocus, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Sprite, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Sprite, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool HasTag(const String&in) const", asMETHODPR(Sprite, HasTag, (const String&) const, bool), asCALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void InsertChild(uint, UIElement@+)", asMETHODPR(Sprite, InsertChild, (unsigned, UIElement*), void), asCALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsChildOf(UIElement@+) const", asMETHODPR(Sprite, IsChildOf, (UIElement*) const, bool), asCALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsEditable() const", asMETHODPR(Sprite, IsEditable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_editable() const", asMETHODPR(Sprite, IsEditable, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsElementEventSender() const", asMETHODPR(Sprite, IsElementEventSender, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_elementEventSender() const", asMETHODPR(Sprite, IsElementEventSender, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsEnabled() const", asMETHODPR(Sprite, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_enabled() const", asMETHODPR(Sprite, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsEnabledSelf() const", asMETHODPR(Sprite, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_enabledSelf() const", asMETHODPR(Sprite, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsFixedHeight() const", asMETHODPR(Sprite, IsFixedHeight, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_fixedHeight() const", asMETHODPR(Sprite, IsFixedHeight, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsFixedSize() const", asMETHODPR(Sprite, IsFixedSize, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_fixedSize() const", asMETHODPR(Sprite, IsFixedSize, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsFixedWidth() const", asMETHODPR(Sprite, IsFixedWidth, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_fixedWidth() const", asMETHODPR(Sprite, IsFixedWidth, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsHovering() const", asMETHODPR(Sprite, IsHovering, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_hovering() const", asMETHODPR(Sprite, IsHovering, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsInside(IntVector2, bool)", asMETHODPR(Sprite, IsInside, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsInsideCombined(IntVector2, bool)", asMETHODPR(Sprite, IsInsideCombined, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "bool IsInstanceOf(StringHash) const", asMETHODPR(Sprite, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsInternal() const", asMETHODPR(Sprite, IsInternal, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_internal() const", asMETHODPR(Sprite, IsInternal, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsSelected() const", asMETHODPR(Sprite, IsSelected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_selected() const", asMETHODPR(Sprite, IsSelected, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "bool IsTemporary() const", asMETHODPR(Sprite, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_temporary() const", asMETHODPR(Sprite, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsVisible() const", asMETHODPR(Sprite, IsVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_visible() const", asMETHODPR(Sprite, IsVisible, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsVisibleEffective() const", asMETHODPR(Sprite, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_visibleEffective() const", asMETHODPR(Sprite, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsWheelHandler() const", asMETHODPR(Sprite, IsWheelHandler, () const, bool), asCALL_THISCALL);
    // bool Sprite::IsWithinScissor(const IntRect& currentScissor) override | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "bool IsWithinScissor(const IntRect&in)", asMETHODPR(Sprite, IsWithinScissor, (const IntRect&), bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "bool Load(Deserializer&)", asMETHODPR(Sprite, Load, (Deserializer&), bool), asCALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", asMETHODPR(Sprite, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Sprite, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool LoadXML(const XMLElement&in)", asMETHODPR(Sprite, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool LoadXML(const XMLElement&in, XMLFile@+)", asMETHODPR(Sprite, LoadXML, (const XMLElement&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool LoadXML(Deserializer&)", asMETHODPR(Sprite, LoadXML, (Deserializer&), bool), asCALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "void MarkNetworkUpdate()", asMETHODPR(Sprite, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Sprite, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", asMETHODPR(Sprite, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Sprite, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Sprite, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(Sprite, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool OnDragDropFinish(UIElement@+)", asMETHODPR(Sprite, OnDragDropFinish, (UIElement*), bool), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool OnDragDropTest(UIElement@+)", asMETHODPR(Sprite, OnDragDropTest, (UIElement*), bool), asCALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(Sprite, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Sprite, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Sprite, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Sprite, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Sprite, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnIndentSet()", asMETHODPR(Sprite, OnIndentSet, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", asMETHODPR(Sprite, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // void Sprite::OnPositionSet(const IntVector2& newPosition) override | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void OnPositionSet(const IntVector2&in)", asMETHODPR(Sprite, OnPositionSet, (const IntVector2&), void), asCALL_THISCALL);
    // virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnResize(const IntVector2&in, const IntVector2&in)", asMETHODPR(Sprite, OnResize, (const IntVector2&, const IntVector2&), void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Sprite, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnSetEditable()", asMETHODPR(Sprite, OnSetEditable, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnTextInput(const String&in)", asMETHODPR(Sprite, OnTextInput, (const String&), void), asCALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", asMETHODPR(Sprite, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Sprite, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Sprite, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Sprite", "int Refs() const", asMETHODPR(Sprite, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_refs() const", asMETHODPR(Sprite, Refs, () const, int), asCALL_THISCALL);
    // static void Sprite::RegisterObject(Context* context) | File: ../UI/Sprite.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Sprite", asBEHAVE_RELEASE, "void f()", asMETHODPR(Sprite, ReleaseRef, (), void), asCALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void Remove()", asMETHODPR(Sprite, Remove, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void RemoveAllChildren()", asMETHODPR(Sprite, RemoveAllChildren, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void RemoveAllTags()", asMETHODPR(Sprite, RemoveAllTags, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(Sprite, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void RemoveChild(UIElement@+, uint = 0)", asMETHODPR(Sprite, RemoveChild, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void RemoveChildAtIndex(uint)", asMETHODPR(Sprite, RemoveChildAtIndex, (unsigned), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "void RemoveInstanceDefault()", asMETHODPR(Sprite, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "void RemoveObjectAnimation()", asMETHODPR(Sprite, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool RemoveTag(const String&in)", asMETHODPR(Sprite, RemoveTag, (const String&), bool), asCALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void ResetDeepEnabled()", asMETHODPR(Sprite, ResetDeepEnabled, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "void ResetToDefault()", asMETHODPR(Sprite, ResetToDefault, (), void), asCALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "bool Save(Serializer&) const", asMETHODPR(Sprite, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "bool SaveDefaultAttributes() const", asMETHODPR(Sprite, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "bool SaveJSON(JSONValue&) const", asMETHODPR(Sprite, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool SaveXML(XMLElement&) const", asMETHODPR(Sprite, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool SaveXML(Serializer&, const String&in = \"\t\") const", asMETHODPR(Sprite, SaveXML, (Serializer&, const String&) const, bool), asCALL_THISCALL);
    // IntVector2 Sprite::ScreenToElement(const IntVector2& screenPosition) override | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "IntVector2 ScreenToElement(const IntVector2&in)", asMETHODPR(Sprite, ScreenToElement, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "void SendEvent(StringHash)", asMETHODPR(Sprite, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Sprite, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", asMETHODPR(Sprite, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "void SetAnimationEnabled(bool)", asMETHODPR(Sprite, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_animationEnabled(bool)", asMETHODPR(Sprite, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "void SetAnimationTime(float)", asMETHODPR(Sprite, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Sprite, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Sprite, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Sprite, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Sprite, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(Sprite, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(Sprite, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Sprite, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Sprite::SetBlendMode(BlendMode mode) | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetBlendMode(BlendMode)", asMETHODPR(Sprite, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_blendMode(BlendMode)", asMETHODPR(Sprite, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "void SetBlockEvents(bool)", asMETHODPR(Sprite, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetBringToBack(bool)", asMETHODPR(Sprite, SetBringToBack, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_bringToBack(bool)", asMETHODPR(Sprite, SetBringToBack, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetBringToFront(bool)", asMETHODPR(Sprite, SetBringToFront, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_bringToFront(bool)", asMETHODPR(Sprite, SetBringToFront, (bool), void), asCALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetChildOffset(const IntVector2&in)", asMETHODPR(Sprite, SetChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetClipBorder(const IntRect&in)", asMETHODPR(Sprite, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_clipBorder(const IntRect&in)", asMETHODPR(Sprite, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetClipChildren(bool)", asMETHODPR(Sprite, SetClipChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_clipChildren(bool)", asMETHODPR(Sprite, SetClipChildren, (bool), void), asCALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetColor(const Color&in)", asMETHODPR(Sprite, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_color(const Color&in)", asMETHODPR(Sprite, SetColor, (const Color&), void), asCALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetColor(Corner, const Color&in)", asMETHODPR(Sprite, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_colors(Corner, const Color&in)", asMETHODPR(Sprite, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetDeepEnabled(bool)", asMETHODPR(Sprite, SetDeepEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetDefaultStyle(XMLFile@+)", asMETHODPR(Sprite, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_defaultStyle(XMLFile@+)", asMETHODPR(Sprite, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetDragDropMode(DragAndDropModeFlags)", asMETHODPR(Sprite, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_dragDropMode(DragAndDropModeFlags)", asMETHODPR(Sprite, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetEditable(bool)", asMETHODPR(Sprite, SetEditable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_editable(bool)", asMETHODPR(Sprite, SetEditable, (bool), void), asCALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetElementEventSender(bool)", asMETHODPR(Sprite, SetElementEventSender, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_elementEventSender(bool)", asMETHODPR(Sprite, SetElementEventSender, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetEnableAnchor(bool)", asMETHODPR(Sprite, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_enableAnchor(bool)", asMETHODPR(Sprite, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetEnabled(bool)", asMETHODPR(Sprite, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_enabled(bool)", asMETHODPR(Sprite, SetEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetEnabledRecursive(bool)", asMETHODPR(Sprite, SetEnabledRecursive, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetFixedHeight(int)", asMETHODPR(Sprite, SetFixedHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetFixedSize(const IntVector2&in)", asMETHODPR(Sprite, SetFixedSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetFixedSize(int, int)", asMETHODPR(Sprite, SetFixedSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetFixedWidth(int)", asMETHODPR(Sprite, SetFixedWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetFocus(bool)", asMETHODPR(Sprite, SetFocus, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_focus(bool)", asMETHODPR(Sprite, SetFocus, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetFocusMode(FocusMode)", asMETHODPR(Sprite, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_focusMode(FocusMode)", asMETHODPR(Sprite, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    // void Sprite::SetFullImageRect() | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetFullImageRect()", asMETHODPR(Sprite, SetFullImageRect, (), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Sprite, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Sprite, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetHeight(int)", asMETHODPR(Sprite, SetHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_height(int)", asMETHODPR(Sprite, SetHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetHorizontalAlignment(HorizontalAlignment)", asMETHODPR(Sprite, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_horizontalAlignment(HorizontalAlignment)", asMETHODPR(Sprite, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    // void Sprite::SetHotSpot(const IntVector2& hotSpot) | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetHotSpot(const IntVector2&in)", asMETHODPR(Sprite, SetHotSpot, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_hotSpot(const IntVector2&in)", asMETHODPR(Sprite, SetHotSpot, (const IntVector2&), void), asCALL_THISCALL);
    // void Sprite::SetHotSpot(int x, int y) | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetHotSpot(int, int)", asMETHODPR(Sprite, SetHotSpot, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetHovering(bool)", asMETHODPR(Sprite, SetHovering, (bool), void), asCALL_THISCALL);
    // void Sprite::SetImageRect(const IntRect& rect) | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetImageRect(const IntRect&in)", asMETHODPR(Sprite, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_imageRect(const IntRect&in)", asMETHODPR(Sprite, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetIndent(int)", asMETHODPR(Sprite, SetIndent, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_indent(int)", asMETHODPR(Sprite, SetIndent, (int), void), asCALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetIndentSpacing(int)", asMETHODPR(Sprite, SetIndentSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_indentSpacing(int)", asMETHODPR(Sprite, SetIndentSpacing, (int), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "void SetInstanceDefault(bool)", asMETHODPR(Sprite, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Sprite, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetInternal(bool)", asMETHODPR(Sprite, SetInternal, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_internal(bool)", asMETHODPR(Sprite, SetInternal, (bool), void), asCALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", asMETHODPR(Sprite, SetLayout, (LayoutMode, int, const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetLayoutBorder(const IntRect&in)", asMETHODPR(Sprite, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_layoutBorder(const IntRect&in)", asMETHODPR(Sprite, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetLayoutFlexScale(const Vector2&in)", asMETHODPR(Sprite, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_layoutFlexScale(const Vector2&in)", asMETHODPR(Sprite, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetLayoutMode(LayoutMode)", asMETHODPR(Sprite, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_layoutMode(LayoutMode)", asMETHODPR(Sprite, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetLayoutSpacing(int)", asMETHODPR(Sprite, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_layoutSpacing(int)", asMETHODPR(Sprite, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMaxAnchor(const Vector2&in)", asMETHODPR(Sprite, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_maxAnchor(const Vector2&in)", asMETHODPR(Sprite, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMaxAnchor(float, float)", asMETHODPR(Sprite, SetMaxAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMaxHeight(int)", asMETHODPR(Sprite, SetMaxHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_maxHeight(int)", asMETHODPR(Sprite, SetMaxHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMaxOffset(const IntVector2&in)", asMETHODPR(Sprite, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_maxOffset(const IntVector2&in)", asMETHODPR(Sprite, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMaxSize(const IntVector2&in)", asMETHODPR(Sprite, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_maxSize(const IntVector2&in)", asMETHODPR(Sprite, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMaxSize(int, int)", asMETHODPR(Sprite, SetMaxSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMaxWidth(int)", asMETHODPR(Sprite, SetMaxWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_maxWidth(int)", asMETHODPR(Sprite, SetMaxWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMinAnchor(const Vector2&in)", asMETHODPR(Sprite, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_minAnchor(const Vector2&in)", asMETHODPR(Sprite, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMinAnchor(float, float)", asMETHODPR(Sprite, SetMinAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMinHeight(int)", asMETHODPR(Sprite, SetMinHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_minHeight(int)", asMETHODPR(Sprite, SetMinHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMinOffset(const IntVector2&in)", asMETHODPR(Sprite, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_minOffset(const IntVector2&in)", asMETHODPR(Sprite, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMinSize(const IntVector2&in)", asMETHODPR(Sprite, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_minSize(const IntVector2&in)", asMETHODPR(Sprite, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMinSize(int, int)", asMETHODPR(Sprite, SetMinSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMinWidth(int)", asMETHODPR(Sprite, SetMinWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_minWidth(int)", asMETHODPR(Sprite, SetMinWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetName(const String&in)", asMETHODPR(Sprite, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_name(const String&in)", asMETHODPR(Sprite, SetName, (const String&), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(Sprite, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(Sprite, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(Sprite, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetOpacity(float)", asMETHODPR(Sprite, SetOpacity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_opacity(float)", asMETHODPR(Sprite, SetOpacity, (float), void), asCALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", asMETHODPR(Sprite, SetParent, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetPivot(const Vector2&in)", asMETHODPR(Sprite, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_pivot(const Vector2&in)", asMETHODPR(Sprite, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetPivot(float, float)", asMETHODPR(Sprite, SetPivot, (float, float), void), asCALL_THISCALL);
    // void Sprite::SetPosition(const Vector2& position) | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetPosition(const Vector2&in)", asMETHODPR(Sprite, SetPosition, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_position(const Vector2&in)", asMETHODPR(Sprite, SetPosition, (const Vector2&), void), asCALL_THISCALL);
    // void Sprite::SetPosition(float x, float y) | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetPosition(float, float)", asMETHODPR(Sprite, SetPosition, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetPriority(int)", asMETHODPR(Sprite, SetPriority, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_priority(int)", asMETHODPR(Sprite, SetPriority, (int), void), asCALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetRenderTexture(Texture2D@+)", asMETHODPR(Sprite, SetRenderTexture, (Texture2D*), void), asCALL_THISCALL);
    // void Sprite::SetRotation(float angle) | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetRotation(float)", asMETHODPR(Sprite, SetRotation, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_rotation(float)", asMETHODPR(Sprite, SetRotation, (float), void), asCALL_THISCALL);
    // void Sprite::SetScale(const Vector2& scale) | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetScale(const Vector2&in)", asMETHODPR(Sprite, SetScale, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_scale(const Vector2&in)", asMETHODPR(Sprite, SetScale, (const Vector2&), void), asCALL_THISCALL);
    // void Sprite::SetScale(float x, float y) | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetScale(float, float)", asMETHODPR(Sprite, SetScale, (float, float), void), asCALL_THISCALL);
    // void Sprite::SetScale(float scale) | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetScale(float)", asMETHODPR(Sprite, SetScale, (float), void), asCALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetSelected(bool)", asMETHODPR(Sprite, SetSelected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_selected(bool)", asMETHODPR(Sprite, SetSelected, (bool), void), asCALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetSize(const IntVector2&in)", asMETHODPR(Sprite, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_size(const IntVector2&in)", asMETHODPR(Sprite, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetSize(int, int)", asMETHODPR(Sprite, SetSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetSortChildren(bool)", asMETHODPR(Sprite, SetSortChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_sortChildren(bool)", asMETHODPR(Sprite, SetSortChildren, (bool), void), asCALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool SetStyle(const String&in, XMLFile@+ = null)", asMETHODPR(Sprite, SetStyle, (const String&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool SetStyle(const XMLElement&in)", asMETHODPR(Sprite, SetStyle, (const XMLElement&), bool), asCALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool SetStyleAuto(XMLFile@+ = null)", asMETHODPR(Sprite, SetStyleAuto, (XMLFile*), bool), asCALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetTags(Array<String>@+)", asFUNCTION(Sprite_SetTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "void SetTemporary(bool)", asMETHODPR(Sprite, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_temporary(bool)", asMETHODPR(Sprite, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Sprite::SetTexture(Texture* texture) | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetTexture(Texture@+)", asMETHODPR(Sprite, SetTexture, (Texture*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_texture(Texture@+)", asMETHODPR(Sprite, SetTexture, (Texture*), void), asCALL_THISCALL);
    // void Sprite::SetTextureAttr(const ResourceRef& value) | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetTextureAttr(const ResourceRef&in)", asMETHODPR(Sprite, SetTextureAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetTraversalMode(TraversalMode)", asMETHODPR(Sprite, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_traversalMode(TraversalMode)", asMETHODPR(Sprite, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetUseDerivedOpacity(bool)", asMETHODPR(Sprite, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_useDerivedOpacity(bool)", asMETHODPR(Sprite, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetVar(StringHash, const Variant&in)", asMETHODPR(Sprite, SetVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetVerticalAlignment(VerticalAlignment)", asMETHODPR(Sprite, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_verticalAlignment(VerticalAlignment)", asMETHODPR(Sprite, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetVisible(bool)", asMETHODPR(Sprite, SetVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_visible(bool)", asMETHODPR(Sprite, SetVisible, (bool), void), asCALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetWidth(int)", asMETHODPR(Sprite, SetWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_width(int)", asMETHODPR(Sprite, SetWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SortChildren()", asMETHODPR(Sprite, SortChildren, (), void), asCALL_THISCALL);
    // explicit Sprite::Sprite(Context* context) | File: ../UI/Sprite.h
    engine->RegisterObjectBehaviour("Sprite", asBEHAVE_FACTORY, "Sprite@+ f()", asFUNCTION(Sprite_Sprite_Context), asCALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "void UnsubscribeFromAllEvents()", asMETHODPR(Sprite, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Sprite_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Sprite, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Sprite, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Sprite, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void UIElement::Update(float timeStep) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void Update(float)", asMETHODPR(Sprite, Update, (float), void), asCALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void UpdateLayout()", asMETHODPR(Sprite, UpdateLayout, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Sprite", "int WeakRefs() const", asMETHODPR(Sprite, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_weakRefs() const", asMETHODPR(Sprite, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Sprite, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Sprite, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Sprite, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_UIElement
    REGISTER_MANUAL_PART_UIElement(Sprite, "Sprite")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(Sprite, "Sprite")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Sprite, "Sprite")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Sprite, "Sprite")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Sprite, "Sprite")
#endif
#ifdef REGISTER_MANUAL_PART_Sprite
    REGISTER_MANUAL_PART_Sprite(Sprite, "Sprite")
#endif
    RegisterSubclass<UIElement, Sprite>(engine, "UIElement", "Sprite");
    RegisterSubclass<Animatable, Sprite>(engine, "Animatable", "Sprite");
    RegisterSubclass<Serializable, Sprite>(engine, "Serializable", "Sprite");
    RegisterSubclass<Object, Sprite>(engine, "Object", "Sprite");
    RegisterSubclass<RefCounted, Sprite>(engine, "RefCounted", "Sprite");

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Sprite2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(Sprite2D, AddRef, (), void), asCALL_THISCALL);
    // bool Sprite2D::BeginLoad(Deserializer& source) override | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "bool BeginLoad(Deserializer&)", asMETHODPR(Sprite2D, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool Sprite2D::EndLoad() override | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "bool EndLoad()", asMETHODPR(Sprite2D, EndLoad, (), bool), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(Sprite2D, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "bool GetBlockEvents() const", asMETHODPR(Sprite2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "const String& GetCategory() const", asMETHODPR(Sprite2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "const String& get_category() const", asMETHODPR(Sprite2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // bool Sprite2D::GetDrawRectangle(Rect& rect, bool flipX=false, bool flipY=false) const | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "bool GetDrawRectangle(Rect&, bool = false, bool = false) const", asMETHODPR(Sprite2D, GetDrawRectangle, (Rect&, bool, bool) const, bool), asCALL_THISCALL);
    // bool Sprite2D::GetDrawRectangle(Rect& rect, const Vector2& hotSpot, bool flipX=false, bool flipY=false) const | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "bool GetDrawRectangle(Rect&, const Vector2&in, bool = false, bool = false) const", asMETHODPR(Sprite2D, GetDrawRectangle, (Rect&, const Vector2&, bool, bool) const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "VariantMap& GetEventDataMap() const", asMETHODPR(Sprite2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "Object@+ GetEventSender() const", asMETHODPR(Sprite2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Sprite2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Sprite2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(Sprite2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "const VariantMap& get_globalVars() const", asMETHODPR(Sprite2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // const Vector2& Sprite2D::GetHotSpot() const | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "const Vector2& GetHotSpot() const", asMETHODPR(Sprite2D, GetHotSpot, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "const Vector2& get_hotSpot() const", asMETHODPR(Sprite2D, GetHotSpot, () const, const Vector2&), asCALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "uint GetMemoryUse() const", asMETHODPR(Sprite2D, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "uint get_memoryUse() const", asMETHODPR(Sprite2D, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "const String& GetName() const", asMETHODPR(Sprite2D, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "const String& get_name() const", asMETHODPR(Sprite2D, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "StringHash GetNameHash() const", asMETHODPR(Sprite2D, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // const IntVector2& Sprite2D::GetOffset() const | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "const IntVector2& GetOffset() const", asMETHODPR(Sprite2D, GetOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "const IntVector2& get_offset() const", asMETHODPR(Sprite2D, GetOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntRect& Sprite2D::GetRectangle() const | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "const IntRect& GetRectangle() const", asMETHODPR(Sprite2D, GetRectangle, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "const IntRect& get_rectangle() const", asMETHODPR(Sprite2D, GetRectangle, () const, const IntRect&), asCALL_THISCALL);
    // SpriteSheet2D* Sprite2D::GetSpriteSheet() const | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "SpriteSheet2D@+ GetSpriteSheet() const", asMETHODPR(Sprite2D, GetSpriteSheet, () const, SpriteSheet2D*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Sprite2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // Texture2D* Sprite2D::GetTexture() const | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "Texture2D@+ GetTexture() const", asMETHODPR(Sprite2D, GetTexture, () const, Texture2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "Texture2D@+ get_texture() const", asMETHODPR(Sprite2D, GetTexture, () const, Texture2D*), asCALL_THISCALL);
    // float Sprite2D::GetTextureEdgeOffset() const | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "float GetTextureEdgeOffset() const", asMETHODPR(Sprite2D, GetTextureEdgeOffset, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "float get_textureEdgeOffset() const", asMETHODPR(Sprite2D, GetTextureEdgeOffset, () const, float), asCALL_THISCALL);
    // bool Sprite2D::GetTextureRectangle(Rect& rect, bool flipX=false, bool flipY=false) const | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "bool GetTextureRectangle(Rect&, bool = false, bool = false) const", asMETHODPR(Sprite2D, GetTextureRectangle, (Rect&, bool, bool) const, bool), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "StringHash GetType() const", asMETHODPR(Sprite2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "StringHash get_type() const", asMETHODPR(Sprite2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "const String& GetTypeName() const", asMETHODPR(Sprite2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "const String& get_typeName() const", asMETHODPR(Sprite2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "uint GetUseTimer()", asMETHODPR(Sprite2D, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "uint get_useTimer()", asMETHODPR(Sprite2D, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "bool HasEventHandlers() const", asMETHODPR(Sprite2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Sprite2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Sprite2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(Sprite2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "bool Load(Deserializer&)", asMETHODPR(Sprite2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "bool LoadFile(const String&in)", asMETHODPR(Sprite2D, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "bool Load(const String&in)", asMETHODPR(Sprite2D, LoadFile, (const String&), bool), asCALL_THISCALL);
    // static Sprite2D* Sprite2D::LoadFromResourceRef(Object* object, const ResourceRef& value) | File: ../Urho2D/Sprite2D.h
    engine->SetDefaultNamespace("Sprite2D");
    engine->RegisterGlobalFunction("Sprite2D@+ LoadFromResourceRef(Object@+, const ResourceRef&in)", asFUNCTIONPR(Sprite2D::LoadFromResourceRef, (Object*, const ResourceRef&), Sprite2D*), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Sprite2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Sprite2D", "int Refs() const", asMETHODPR(Sprite2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "int get_refs() const", asMETHODPR(Sprite2D, Refs, () const, int), asCALL_THISCALL);
    // static void Sprite2D::RegisterObject(Context* context) | File: ../Urho2D/Sprite2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Sprite2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(Sprite2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "void ResetUseTimer()", asMETHODPR(Sprite2D, ResetUseTimer, (), void), asCALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "bool Save(Serializer&) const", asMETHODPR(Sprite2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "bool SaveFile(const String&in) const", asMETHODPR(Sprite2D, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "bool Save(const String&in) const", asMETHODPR(Sprite2D, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // static ResourceRef Sprite2D::SaveToResourceRef(Sprite2D* sprite) | File: ../Urho2D/Sprite2D.h
    engine->SetDefaultNamespace("Sprite2D");
    engine->RegisterGlobalFunction("ResourceRef SaveToResourceRef(Sprite2D@+)", asFUNCTIONPR(Sprite2D::SaveToResourceRef, (Sprite2D*), ResourceRef), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "void SendEvent(StringHash)", asMETHODPR(Sprite2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Sprite2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(Sprite2D, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "void SetBlockEvents(bool)", asMETHODPR(Sprite2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Sprite2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Sprite2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Sprite2D::SetHotSpot(const Vector2& hotSpot) | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "void SetHotSpot(const Vector2&in)", asMETHODPR(Sprite2D, SetHotSpot, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "void set_hotSpot(const Vector2&in)", asMETHODPR(Sprite2D, SetHotSpot, (const Vector2&), void), asCALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "void SetMemoryUse(uint)", asMETHODPR(Sprite2D, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "void SetName(const String&in)", asMETHODPR(Sprite2D, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "void set_name(const String&in)", asMETHODPR(Sprite2D, SetName, (const String&), void), asCALL_THISCALL);
    // void Sprite2D::SetOffset(const IntVector2& offset) | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "void SetOffset(const IntVector2&in)", asMETHODPR(Sprite2D, SetOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "void set_offset(const IntVector2&in)", asMETHODPR(Sprite2D, SetOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void Sprite2D::SetRectangle(const IntRect& rectangle) | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "void SetRectangle(const IntRect&in)", asMETHODPR(Sprite2D, SetRectangle, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "void set_rectangle(const IntRect&in)", asMETHODPR(Sprite2D, SetRectangle, (const IntRect&), void), asCALL_THISCALL);
    // void Sprite2D::SetSpriteSheet(SpriteSheet2D* spriteSheet) | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "void SetSpriteSheet(SpriteSheet2D@+)", asMETHODPR(Sprite2D, SetSpriteSheet, (SpriteSheet2D*), void), asCALL_THISCALL);
    // void Sprite2D::SetTexture(Texture2D* texture) | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "void SetTexture(Texture2D@+)", asMETHODPR(Sprite2D, SetTexture, (Texture2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "void set_texture(Texture2D@+)", asMETHODPR(Sprite2D, SetTexture, (Texture2D*), void), asCALL_THISCALL);
    // void Sprite2D::SetTextureEdgeOffset(float offset) | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "void SetTextureEdgeOffset(float)", asMETHODPR(Sprite2D, SetTextureEdgeOffset, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "void set_textureEdgeOffset(float)", asMETHODPR(Sprite2D, SetTextureEdgeOffset, (float), void), asCALL_THISCALL);
    // explicit Sprite2D::Sprite2D(Context* context) | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectBehaviour("Sprite2D", asBEHAVE_FACTORY, "Sprite2D@+ f()", asFUNCTION(Sprite2D_Sprite2D_Context), asCALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "void UnsubscribeFromAllEvents()", asMETHODPR(Sprite2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Sprite2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Sprite2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Sprite2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Sprite2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Sprite2D", "int WeakRefs() const", asMETHODPR(Sprite2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "int get_weakRefs() const", asMETHODPR(Sprite2D, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(Sprite2D, "Sprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Sprite2D, "Sprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Sprite2D, "Sprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_Sprite2D
    REGISTER_MANUAL_PART_Sprite2D(Sprite2D, "Sprite2D")
#endif
    RegisterSubclass<Resource, Sprite2D>(engine, "Resource", "Sprite2D");
    RegisterSubclass<Object, Sprite2D>(engine, "Object", "Sprite2D");
    RegisterSubclass<RefCounted, Sprite2D>(engine, "RefCounted", "Sprite2D");
#endif

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("SpriteSheet2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(SpriteSheet2D, AddRef, (), void), asCALL_THISCALL);
    // bool SpriteSheet2D::BeginLoad(Deserializer& source) override | File: ../Urho2D/SpriteSheet2D.h
    engine->RegisterObjectMethod("SpriteSheet2D", "bool BeginLoad(Deserializer&)", asMETHODPR(SpriteSheet2D, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void SpriteSheet2D::DefineSprite(const String& name, const IntRect& rectangle, const Vector2& hotSpot=Vector2(0.5f, 0.5f), const IntVector2& offset=IntVector2::ZERO) | File: ../Urho2D/SpriteSheet2D.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void DefineSprite(const String&in, const IntRect&in, const Vector2&in = Vector2(0.5f, 0.5f), const IntVector2&in = IntVector2::ZERO)", asMETHODPR(SpriteSheet2D, DefineSprite, (const String&, const IntRect&, const Vector2&, const IntVector2&), void), asCALL_THISCALL);
    // bool SpriteSheet2D::EndLoad() override | File: ../Urho2D/SpriteSheet2D.h
    engine->RegisterObjectMethod("SpriteSheet2D", "bool EndLoad()", asMETHODPR(SpriteSheet2D, EndLoad, (), bool), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(SpriteSheet2D, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "bool GetBlockEvents() const", asMETHODPR(SpriteSheet2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "const String& GetCategory() const", asMETHODPR(SpriteSheet2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "const String& get_category() const", asMETHODPR(SpriteSheet2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "VariantMap& GetEventDataMap() const", asMETHODPR(SpriteSheet2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "Object@+ GetEventSender() const", asMETHODPR(SpriteSheet2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(SpriteSheet2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(SpriteSheet2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(SpriteSheet2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "const VariantMap& get_globalVars() const", asMETHODPR(SpriteSheet2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "uint GetMemoryUse() const", asMETHODPR(SpriteSheet2D, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "uint get_memoryUse() const", asMETHODPR(SpriteSheet2D, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "const String& GetName() const", asMETHODPR(SpriteSheet2D, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "const String& get_name() const", asMETHODPR(SpriteSheet2D, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "StringHash GetNameHash() const", asMETHODPR(SpriteSheet2D, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // Sprite2D* SpriteSheet2D::GetSprite(const String& name) const | File: ../Urho2D/SpriteSheet2D.h
    engine->RegisterObjectMethod("SpriteSheet2D", "Sprite2D@+ GetSprite(const String&in) const", asMETHODPR(SpriteSheet2D, GetSprite, (const String&) const, Sprite2D*), asCALL_THISCALL);
    // const HashMap<String, SharedPtr<Sprite2D>>& SpriteSheet2D::GetSpriteMapping() const | File: ../Urho2D/SpriteSheet2D.h
    // Error: type "const HashMap<String, SharedPtr<Sprite2D>>&" can not automatically bind
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(SpriteSheet2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // Texture2D* SpriteSheet2D::GetTexture() const | File: ../Urho2D/SpriteSheet2D.h
    engine->RegisterObjectMethod("SpriteSheet2D", "Texture2D@+ GetTexture() const", asMETHODPR(SpriteSheet2D, GetTexture, () const, Texture2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "Texture2D@+ get_texture() const", asMETHODPR(SpriteSheet2D, GetTexture, () const, Texture2D*), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "StringHash GetType() const", asMETHODPR(SpriteSheet2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "StringHash get_type() const", asMETHODPR(SpriteSheet2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "const String& GetTypeName() const", asMETHODPR(SpriteSheet2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "const String& get_typeName() const", asMETHODPR(SpriteSheet2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "uint GetUseTimer()", asMETHODPR(SpriteSheet2D, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "uint get_useTimer()", asMETHODPR(SpriteSheet2D, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "bool HasEventHandlers() const", asMETHODPR(SpriteSheet2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(SpriteSheet2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(SpriteSheet2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(SpriteSheet2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "bool Load(Deserializer&)", asMETHODPR(SpriteSheet2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "bool LoadFile(const String&in)", asMETHODPR(SpriteSheet2D, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "bool Load(const String&in)", asMETHODPR(SpriteSheet2D, LoadFile, (const String&), bool), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(SpriteSheet2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SpriteSheet2D", "int Refs() const", asMETHODPR(SpriteSheet2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "int get_refs() const", asMETHODPR(SpriteSheet2D, Refs, () const, int), asCALL_THISCALL);
    // static void SpriteSheet2D::RegisterObject(Context* context) | File: ../Urho2D/SpriteSheet2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("SpriteSheet2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(SpriteSheet2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void ResetUseTimer()", asMETHODPR(SpriteSheet2D, ResetUseTimer, (), void), asCALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "bool Save(Serializer&) const", asMETHODPR(SpriteSheet2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "bool SaveFile(const String&in) const", asMETHODPR(SpriteSheet2D, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "bool Save(const String&in) const", asMETHODPR(SpriteSheet2D, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void SendEvent(StringHash)", asMETHODPR(SpriteSheet2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(SpriteSheet2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(SpriteSheet2D, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void SetBlockEvents(bool)", asMETHODPR(SpriteSheet2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(SpriteSheet2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(SpriteSheet2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void SetMemoryUse(uint)", asMETHODPR(SpriteSheet2D, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void SetName(const String&in)", asMETHODPR(SpriteSheet2D, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "void set_name(const String&in)", asMETHODPR(SpriteSheet2D, SetName, (const String&), void), asCALL_THISCALL);
    // void SpriteSheet2D::SetTexture(Texture2D* texture) | File: ../Urho2D/SpriteSheet2D.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void SetTexture(Texture2D@+)", asMETHODPR(SpriteSheet2D, SetTexture, (Texture2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "void set_texture(Texture2D@+)", asMETHODPR(SpriteSheet2D, SetTexture, (Texture2D*), void), asCALL_THISCALL);
    // explicit SpriteSheet2D::SpriteSheet2D(Context* context) | File: ../Urho2D/SpriteSheet2D.h
    engine->RegisterObjectBehaviour("SpriteSheet2D", asBEHAVE_FACTORY, "SpriteSheet2D@+ f()", asFUNCTION(SpriteSheet2D_SpriteSheet2D_Context), asCALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void UnsubscribeFromAllEvents()", asMETHODPR(SpriteSheet2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(SpriteSheet2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(SpriteSheet2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(SpriteSheet2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(SpriteSheet2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SpriteSheet2D", "int WeakRefs() const", asMETHODPR(SpriteSheet2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "int get_weakRefs() const", asMETHODPR(SpriteSheet2D, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(SpriteSheet2D, "SpriteSheet2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(SpriteSheet2D, "SpriteSheet2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(SpriteSheet2D, "SpriteSheet2D")
#endif
#ifdef REGISTER_MANUAL_PART_SpriteSheet2D
    REGISTER_MANUAL_PART_SpriteSheet2D(SpriteSheet2D, "SpriteSheet2D")
#endif
    RegisterSubclass<Resource, SpriteSheet2D>(engine, "Resource", "SpriteSheet2D");
    RegisterSubclass<Object, SpriteSheet2D>(engine, "Object", "SpriteSheet2D");
    RegisterSubclass<RefCounted, SpriteSheet2D>(engine, "RefCounted", "SpriteSheet2D");
#endif

    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void AddLight(Light@+)", asMETHODPR(StaticModel, AddLight, (Light*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("StaticModel", asBEHAVE_ADDREF, "void f()", asMETHODPR(StaticModel, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void AddVertexLight(Light@+)", asMETHODPR(StaticModel, AddVertexLight, (Light*), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "void AllocateNetworkState()", asMETHODPR(StaticModel, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "void ApplyAttributes()", asMETHODPR(StaticModel, ApplyAttributes, (), void), asCALL_THISCALL);
    // void StaticModel::ApplyMaterialList(const String& fileName=String::EMPTY) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "void ApplyMaterialList(const String&in = String::EMPTY)", asMETHODPR(StaticModel, ApplyMaterialList, (const String&), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(StaticModel, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool StaticModel::DrawOcclusion(OcclusionBuffer* buffer) override | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "bool DrawOcclusion(OcclusionBuffer@+)", asMETHODPR(StaticModel, DrawOcclusion, (OcclusionBuffer*), bool), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "bool GetAnimationEnabled() const", asMETHODPR(StaticModel, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "bool get_animationEnabled() const", asMETHODPR(StaticModel, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "Variant GetAttribute(uint) const", asMETHODPR(StaticModel, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "Variant get_attributes(uint) const", asMETHODPR(StaticModel, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "Variant GetAttribute(const String&in) const", asMETHODPR(StaticModel, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(StaticModel, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(StaticModel, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(StaticModel, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(StaticModel, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "Variant GetAttributeDefault(uint) const", asMETHODPR(StaticModel, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "Variant get_attributeDefaults(uint) const", asMETHODPR(StaticModel, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(StaticModel, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "bool GetBlockEvents() const", asMETHODPR(StaticModel, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "const BoundingBox& GetBoundingBox() const", asMETHODPR(StaticModel, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "const BoundingBox& get_boundingBox() const", asMETHODPR(StaticModel, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "bool GetCastShadows() const", asMETHODPR(StaticModel, GetCastShadows, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "bool get_castShadows() const", asMETHODPR(StaticModel, GetCastShadows, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "const String& GetCategory() const", asMETHODPR(StaticModel, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "const String& get_category() const", asMETHODPR(StaticModel, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "Component@+ GetComponent(StringHash) const", asMETHODPR(StaticModel, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
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
    engine->RegisterObjectMethod("StaticModel", "float GetDistance() const", asMETHODPR(StaticModel, GetDistance, () const, float), asCALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "uint8 GetDrawableFlags() const", asMETHODPR(StaticModel, GetDrawableFlags, () const, unsigned char), asCALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "float GetDrawDistance() const", asMETHODPR(StaticModel, GetDrawDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "float get_drawDistance() const", asMETHODPR(StaticModel, GetDrawDistance, () const, float), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "VariantMap& GetEventDataMap() const", asMETHODPR(StaticModel, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "Object@+ GetEventSender() const", asMETHODPR(StaticModel, GetEventSender, () const, Object*), asCALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "Light@+ GetFirstLight() const", asMETHODPR(StaticModel, GetFirstLight, () const, Light*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(StaticModel, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "const Variant& get_globalVar(StringHash) const", asMETHODPR(StaticModel, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "const VariantMap& GetGlobalVars() const", asMETHODPR(StaticModel, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "const VariantMap& get_globalVars() const", asMETHODPR(StaticModel, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "uint GetID() const", asMETHODPR(StaticModel, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "uint get_id() const", asMETHODPR(StaticModel, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(StaticModel, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "uint GetLightMask() const", asMETHODPR(StaticModel, GetLightMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "uint get_lightMask() const", asMETHODPR(StaticModel, GetLightMask, () const, unsigned), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "Array<Light@>@ GetLights() const", asFUNCTION(StaticModel_GetLights_void), asCALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "float GetLodBias() const", asMETHODPR(StaticModel, GetLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "float get_lodBias() const", asMETHODPR(StaticModel, GetLodBias, () const, float), asCALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "float GetLodDistance() const", asMETHODPR(StaticModel, GetLodDistance, () const, float), asCALL_THISCALL);
    // Geometry* StaticModel::GetLodGeometry(unsigned batchIndex, unsigned level) override | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "Geometry@+ GetLodGeometry(uint, uint)", asMETHODPR(StaticModel, GetLodGeometry, (unsigned, unsigned), Geometry*), asCALL_THISCALL);
    // virtual Material* StaticModel::GetMaterial() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "Material@+ GetMaterial() const", asMETHODPR(StaticModel, GetMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "Material@+ get_material() const", asMETHODPR(StaticModel, GetMaterial, () const, Material*), asCALL_THISCALL);
    // virtual Material* StaticModel::GetMaterial(unsigned index) const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "Material@+ GetMaterial(uint) const", asMETHODPR(StaticModel, GetMaterial, (unsigned) const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "Material@+ get_materials(uint) const", asMETHODPR(StaticModel, GetMaterial, (unsigned) const, Material*), asCALL_THISCALL);
    // const ResourceRefList& StaticModel::GetMaterialsAttr() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "const ResourceRefList& GetMaterialsAttr() const", asMETHODPR(StaticModel, GetMaterialsAttr, () const, const ResourceRefList&), asCALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "uint GetMaxLights() const", asMETHODPR(StaticModel, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "uint get_maxLights() const", asMETHODPR(StaticModel, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "float GetMaxZ() const", asMETHODPR(StaticModel, GetMaxZ, () const, float), asCALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "float GetMinZ() const", asMETHODPR(StaticModel, GetMinZ, () const, float), asCALL_THISCALL);
    // Model* StaticModel::GetModel() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "Model@+ GetModel() const", asMETHODPR(StaticModel, GetModel, () const, Model*), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "Model@+ get_model() const", asMETHODPR(StaticModel, GetModel, () const, Model*), asCALL_THISCALL);
    // ResourceRef StaticModel::GetModelAttr() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "ResourceRef GetModelAttr() const", asMETHODPR(StaticModel, GetModelAttr, () const, ResourceRef), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "Node@+ GetNode() const", asMETHODPR(StaticModel, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "Node@+ get_node() const", asMETHODPR(StaticModel, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "uint GetNumAttributes() const", asMETHODPR(StaticModel, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "uint get_numAttributes() const", asMETHODPR(StaticModel, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned StaticModel::GetNumGeometries() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "uint GetNumGeometries() const", asMETHODPR(StaticModel, GetNumGeometries, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "uint get_numGeometries() const", asMETHODPR(StaticModel, GetNumGeometries, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "uint GetNumNetworkAttributes() const", asMETHODPR(StaticModel, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned StaticModel::GetNumOccluderTriangles() override | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "uint GetNumOccluderTriangles()", asMETHODPR(StaticModel, GetNumOccluderTriangles, (), unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(StaticModel, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(StaticModel, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(StaticModel, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // unsigned StaticModel::GetOcclusionLodLevel() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "uint GetOcclusionLodLevel() const", asMETHODPR(StaticModel, GetOcclusionLodLevel, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "uint get_occlusionLodLevel() const", asMETHODPR(StaticModel, GetOcclusionLodLevel, () const, unsigned), asCALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "Scene@+ GetScene() const", asMETHODPR(StaticModel, GetScene, () const, Scene*), asCALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "float GetShadowDistance() const", asMETHODPR(StaticModel, GetShadowDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "float get_shadowDistance() const", asMETHODPR(StaticModel, GetShadowDistance, () const, float), asCALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "uint GetShadowMask() const", asMETHODPR(StaticModel, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "uint get_shadowMask() const", asMETHODPR(StaticModel, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "float GetSortValue() const", asMETHODPR(StaticModel, GetSortValue, () const, float), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(StaticModel, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "StringHash GetType() const", asMETHODPR(StaticModel, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "StringHash get_type() const", asMETHODPR(StaticModel, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "const String& GetTypeName() const", asMETHODPR(StaticModel, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "const String& get_typeName() const", asMETHODPR(StaticModel, GetTypeName, () const, const String&), asCALL_THISCALL);
    // virtual UpdateGeometryType Drawable::GetUpdateGeometryType() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "UpdateGeometryType GetUpdateGeometryType()", asMETHODPR(StaticModel, GetUpdateGeometryType, (), UpdateGeometryType), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "Array<Light@>@ GetVertexLights() const", asFUNCTION(StaticModel_GetVertexLights_void), asCALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "uint GetViewMask() const", asMETHODPR(StaticModel, GetViewMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "uint get_viewMask() const", asMETHODPR(StaticModel, GetViewMask, () const, unsigned), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "const BoundingBox& GetWorldBoundingBox()", asMETHODPR(StaticModel, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "const BoundingBox& get_worldBoundingBox()", asMETHODPR(StaticModel, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "Zone@+ GetZone() const", asMETHODPR(StaticModel, GetZone, () const, Zone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "Zone@+ get_zone() const", asMETHODPR(StaticModel, GetZone, () const, Zone*), asCALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "uint GetZoneMask() const", asMETHODPR(StaticModel, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "uint get_zoneMask() const", asMETHODPR(StaticModel, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "bool HasBasePass(uint) const", asMETHODPR(StaticModel, HasBasePass, (unsigned) const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "bool HasEventHandlers() const", asMETHODPR(StaticModel, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(StaticModel, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(StaticModel, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "bool IsEnabled() const", asMETHODPR(StaticModel, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "bool get_enabled() const", asMETHODPR(StaticModel, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "bool IsEnabledEffective() const", asMETHODPR(StaticModel, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "bool get_enabledEffective() const", asMETHODPR(StaticModel, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool StaticModel::IsInside(const Vector3& point) const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "bool IsInside(const Vector3&in) const", asMETHODPR(StaticModel, IsInside, (const Vector3&) const, bool), asCALL_THISCALL);
    // bool StaticModel::IsInsideLocal(const Vector3& point) const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "bool IsInsideLocal(const Vector3&in) const", asMETHODPR(StaticModel, IsInsideLocal, (const Vector3&) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "bool IsInstanceOf(StringHash) const", asMETHODPR(StaticModel, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "bool IsInView() const", asMETHODPR(StaticModel, IsInView, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "bool get_inView() const", asMETHODPR(StaticModel, IsInView, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "bool IsInView(Camera@+) const", asMETHODPR(StaticModel, IsInView, (Camera*) const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "bool IsInView(const FrameInfo&in, bool = false) const", asMETHODPR(StaticModel, IsInView, (const FrameInfo&, bool) const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "bool IsOccludee() const", asMETHODPR(StaticModel, IsOccludee, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "bool get_occludee() const", asMETHODPR(StaticModel, IsOccludee, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "bool IsOccluder() const", asMETHODPR(StaticModel, IsOccluder, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "bool get_occluder() const", asMETHODPR(StaticModel, IsOccluder, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "bool IsReplicated() const", asMETHODPR(StaticModel, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "bool get_replicated() const", asMETHODPR(StaticModel, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "bool IsTemporary() const", asMETHODPR(StaticModel, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "bool get_temporary() const", asMETHODPR(StaticModel, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "bool IsZoneDirty() const", asMETHODPR(StaticModel, IsZoneDirty, () const, bool), asCALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void LimitLights()", asMETHODPR(StaticModel, LimitLights, (), void), asCALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void LimitVertexLights(bool)", asMETHODPR(StaticModel, LimitVertexLights, (bool), void), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "bool Load(Deserializer&)", asMETHODPR(StaticModel, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "bool LoadJSON(const JSONValue&in)", asMETHODPR(StaticModel, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "bool LoadXML(const XMLElement&in)", asMETHODPR(StaticModel, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void MarkForUpdate()", asMETHODPR(StaticModel, MarkForUpdate, (), void), asCALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void MarkInView(const FrameInfo&in)", asMETHODPR(StaticModel, MarkInView, (const FrameInfo&), void), asCALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void MarkInView(uint)", asMETHODPR(StaticModel, MarkInView, (unsigned), void), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "void MarkNetworkUpdate()", asMETHODPR(StaticModel, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(StaticModel, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(StaticModel, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(StaticModel, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Drawable::OnSetEnabled() override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void OnSetEnabled()", asMETHODPR(StaticModel, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "void PrepareNetworkUpdate()", asMETHODPR(StaticModel, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // void StaticModel::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override | File: ../Graphics/StaticModel.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(StaticModel, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(StaticModel, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("StaticModel", "int Refs() const", asMETHODPR(StaticModel, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "int get_refs() const", asMETHODPR(StaticModel, Refs, () const, int), asCALL_THISCALL);
    // static void StaticModel::RegisterObject(Context* context) | File: ../Graphics/StaticModel.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("StaticModel", asBEHAVE_RELEASE, "void f()", asMETHODPR(StaticModel, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "void Remove()", asMETHODPR(StaticModel, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(StaticModel, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "void RemoveInstanceDefault()", asMETHODPR(StaticModel, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "void RemoveObjectAnimation()", asMETHODPR(StaticModel, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "void ResetToDefault()", asMETHODPR(StaticModel, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "bool Save(Serializer&) const", asMETHODPR(StaticModel, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "bool SaveDefaultAttributes() const", asMETHODPR(StaticModel, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "bool SaveJSON(JSONValue&) const", asMETHODPR(StaticModel, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "bool SaveXML(XMLElement&) const", asMETHODPR(StaticModel, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "void SendEvent(StringHash)", asMETHODPR(StaticModel, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(StaticModel, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "void SetAnimationEnabled(bool)", asMETHODPR(StaticModel, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_animationEnabled(bool)", asMETHODPR(StaticModel, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "void SetAnimationTime(float)", asMETHODPR(StaticModel, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(StaticModel, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "bool set_attributes(uint, const Variant&in)", asMETHODPR(StaticModel, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(StaticModel, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(StaticModel, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(StaticModel, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(StaticModel, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(StaticModel, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetBasePass(uint)", asMETHODPR(StaticModel, SetBasePass, (unsigned), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "void SetBlockEvents(bool)", asMETHODPR(StaticModel, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetCastShadows(bool)", asMETHODPR(StaticModel, SetCastShadows, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_castShadows(bool)", asMETHODPR(StaticModel, SetCastShadows, (bool), void), asCALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetDrawDistance(float)", asMETHODPR(StaticModel, SetDrawDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_drawDistance(float)", asMETHODPR(StaticModel, SetDrawDistance, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "void SetEnabled(bool)", asMETHODPR(StaticModel, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_enabled(bool)", asMETHODPR(StaticModel, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(StaticModel, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(StaticModel, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "void SetInstanceDefault(bool)", asMETHODPR(StaticModel, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(StaticModel, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetLightMask(uint)", asMETHODPR(StaticModel, SetLightMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_lightMask(uint)", asMETHODPR(StaticModel, SetLightMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetLodBias(float)", asMETHODPR(StaticModel, SetLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_lodBias(float)", asMETHODPR(StaticModel, SetLodBias, (float), void), asCALL_THISCALL);
    // virtual void StaticModel::SetMaterial(Material* material) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "void SetMaterial(Material@+)", asMETHODPR(StaticModel, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_material(Material@+)", asMETHODPR(StaticModel, SetMaterial, (Material*), void), asCALL_THISCALL);
    // virtual bool StaticModel::SetMaterial(unsigned index, Material* material) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "bool SetMaterial(uint, Material@+)", asMETHODPR(StaticModel, SetMaterial, (unsigned, Material*), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "bool set_materials(uint, Material@+)", asMETHODPR(StaticModel, SetMaterial, (unsigned, Material*), bool), asCALL_THISCALL);
    // void StaticModel::SetMaterialsAttr(const ResourceRefList& value) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "void SetMaterialsAttr(const ResourceRefList&in)", asMETHODPR(StaticModel, SetMaterialsAttr, (const ResourceRefList&), void), asCALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetMaxLights(uint)", asMETHODPR(StaticModel, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_maxLights(uint)", asMETHODPR(StaticModel, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetMinMaxZ(float, float)", asMETHODPR(StaticModel, SetMinMaxZ, (float, float), void), asCALL_THISCALL);
    // virtual void StaticModel::SetModel(Model* model) | File: ../Graphics/StaticModel.h
    // Not registered because have @manualbind mark
    // void StaticModel::SetModelAttr(const ResourceRef& value) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "void SetModelAttr(const ResourceRef&in)", asMETHODPR(StaticModel, SetModelAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(StaticModel, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(StaticModel, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(StaticModel, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetOccludee(bool)", asMETHODPR(StaticModel, SetOccludee, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_occludee(bool)", asMETHODPR(StaticModel, SetOccludee, (bool), void), asCALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetOccluder(bool)", asMETHODPR(StaticModel, SetOccluder, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_occluder(bool)", asMETHODPR(StaticModel, SetOccluder, (bool), void), asCALL_THISCALL);
    // void StaticModel::SetOcclusionLodLevel(unsigned level) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "void SetOcclusionLodLevel(uint)", asMETHODPR(StaticModel, SetOcclusionLodLevel, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_occlusionLodLevel(uint)", asMETHODPR(StaticModel, SetOcclusionLodLevel, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetShadowDistance(float)", asMETHODPR(StaticModel, SetShadowDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_shadowDistance(float)", asMETHODPR(StaticModel, SetShadowDistance, (float), void), asCALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetShadowMask(uint)", asMETHODPR(StaticModel, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_shadowMask(uint)", asMETHODPR(StaticModel, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetSortValue(float)", asMETHODPR(StaticModel, SetSortValue, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "void SetTemporary(bool)", asMETHODPR(StaticModel, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_temporary(bool)", asMETHODPR(StaticModel, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetViewMask(uint)", asMETHODPR(StaticModel, SetViewMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_viewMask(uint)", asMETHODPR(StaticModel, SetViewMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetZone(Zone@+, bool = false)", asMETHODPR(StaticModel, SetZone, (Zone*, bool), void), asCALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetZoneMask(uint)", asMETHODPR(StaticModel, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_zoneMask(uint)", asMETHODPR(StaticModel, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    // explicit StaticModel::StaticModel(Context* context) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectBehaviour("StaticModel", asBEHAVE_FACTORY, "StaticModel@+ f()", asFUNCTION(StaticModel_StaticModel_Context), asCALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "void UnsubscribeFromAllEvents()", asMETHODPR(StaticModel, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(StaticModel_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(StaticModel, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(StaticModel, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(StaticModel, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void Update(const FrameInfo&in)", asMETHODPR(StaticModel, Update, (const FrameInfo&), void), asCALL_THISCALL);
    // void StaticModel::UpdateBatches(const FrameInfo& frame) override | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "void UpdateBatches(const FrameInfo&in)", asMETHODPR(StaticModel, UpdateBatches, (const FrameInfo&), void), asCALL_THISCALL);
    // virtual void Drawable::UpdateGeometry(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void UpdateGeometry(const FrameInfo&in)", asMETHODPR(StaticModel, UpdateGeometry, (const FrameInfo&), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("StaticModel", "int WeakRefs() const", asMETHODPR(StaticModel, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "int get_weakRefs() const", asMETHODPR(StaticModel, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(StaticModel, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(StaticModel, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(StaticModel, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Drawable
    REGISTER_MANUAL_PART_Drawable(StaticModel, "StaticModel")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(StaticModel, "StaticModel")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(StaticModel, "StaticModel")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(StaticModel, "StaticModel")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(StaticModel, "StaticModel")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(StaticModel, "StaticModel")
#endif
#ifdef REGISTER_MANUAL_PART_StaticModel
    REGISTER_MANUAL_PART_StaticModel(StaticModel, "StaticModel")
#endif
    RegisterSubclass<Drawable, StaticModel>(engine, "Drawable", "StaticModel");
    RegisterSubclass<Component, StaticModel>(engine, "Component", "StaticModel");
    RegisterSubclass<Animatable, StaticModel>(engine, "Animatable", "StaticModel");
    RegisterSubclass<Serializable, StaticModel>(engine, "Serializable", "StaticModel");
    RegisterSubclass<Object, StaticModel>(engine, "Object", "StaticModel");
    RegisterSubclass<RefCounted, StaticModel>(engine, "RefCounted", "StaticModel");

    // void StaticModelGroup::AddInstanceNode(Node* node) | File: ../Graphics/StaticModelGroup.h
    engine->RegisterObjectMethod("StaticModelGroup", "void AddInstanceNode(Node@+)", asMETHODPR(StaticModelGroup, AddInstanceNode, (Node*), void), asCALL_THISCALL);
    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void AddLight(Light@+)", asMETHODPR(StaticModelGroup, AddLight, (Light*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("StaticModelGroup", asBEHAVE_ADDREF, "void f()", asMETHODPR(StaticModelGroup, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void AddVertexLight(Light@+)", asMETHODPR(StaticModelGroup, AddVertexLight, (Light*), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void AllocateNetworkState()", asMETHODPR(StaticModelGroup, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void StaticModelGroup::ApplyAttributes() override | File: ../Graphics/StaticModelGroup.h
    engine->RegisterObjectMethod("StaticModelGroup", "void ApplyAttributes()", asMETHODPR(StaticModelGroup, ApplyAttributes, (), void), asCALL_THISCALL);
    // void StaticModel::ApplyMaterialList(const String& fileName=String::EMPTY) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "void ApplyMaterialList(const String&in = String::EMPTY)", asMETHODPR(StaticModelGroup, ApplyMaterialList, (const String&), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(StaticModelGroup, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool StaticModelGroup::DrawOcclusion(OcclusionBuffer* buffer) override | File: ../Graphics/StaticModelGroup.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool DrawOcclusion(OcclusionBuffer@+)", asMETHODPR(StaticModelGroup, DrawOcclusion, (OcclusionBuffer*), bool), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool GetAnimationEnabled() const", asMETHODPR(StaticModelGroup, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "bool get_animationEnabled() const", asMETHODPR(StaticModelGroup, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "Variant GetAttribute(uint) const", asMETHODPR(StaticModelGroup, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "Variant get_attributes(uint) const", asMETHODPR(StaticModelGroup, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "Variant GetAttribute(const String&in) const", asMETHODPR(StaticModelGroup, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(StaticModelGroup, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(StaticModelGroup, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(StaticModelGroup, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(StaticModelGroup, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "Variant GetAttributeDefault(uint) const", asMETHODPR(StaticModelGroup, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "Variant get_attributeDefaults(uint) const", asMETHODPR(StaticModelGroup, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(StaticModelGroup, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool GetBlockEvents() const", asMETHODPR(StaticModelGroup, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "const BoundingBox& GetBoundingBox() const", asMETHODPR(StaticModelGroup, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "const BoundingBox& get_boundingBox() const", asMETHODPR(StaticModelGroup, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool GetCastShadows() const", asMETHODPR(StaticModelGroup, GetCastShadows, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "bool get_castShadows() const", asMETHODPR(StaticModelGroup, GetCastShadows, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "const String& GetCategory() const", asMETHODPR(StaticModelGroup, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "const String& get_category() const", asMETHODPR(StaticModelGroup, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "Component@+ GetComponent(StringHash) const", asMETHODPR(StaticModelGroup, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
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
    engine->RegisterObjectMethod("StaticModelGroup", "float GetDistance() const", asMETHODPR(StaticModelGroup, GetDistance, () const, float), asCALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint8 GetDrawableFlags() const", asMETHODPR(StaticModelGroup, GetDrawableFlags, () const, unsigned char), asCALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "float GetDrawDistance() const", asMETHODPR(StaticModelGroup, GetDrawDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "float get_drawDistance() const", asMETHODPR(StaticModelGroup, GetDrawDistance, () const, float), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "VariantMap& GetEventDataMap() const", asMETHODPR(StaticModelGroup, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "Object@+ GetEventSender() const", asMETHODPR(StaticModelGroup, GetEventSender, () const, Object*), asCALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "Light@+ GetFirstLight() const", asMETHODPR(StaticModelGroup, GetFirstLight, () const, Light*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(StaticModelGroup, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "const Variant& get_globalVar(StringHash) const", asMETHODPR(StaticModelGroup, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "const VariantMap& GetGlobalVars() const", asMETHODPR(StaticModelGroup, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "const VariantMap& get_globalVars() const", asMETHODPR(StaticModelGroup, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint GetID() const", asMETHODPR(StaticModelGroup, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "uint get_id() const", asMETHODPR(StaticModelGroup, GetID, () const, unsigned), asCALL_THISCALL);
    // Node* StaticModelGroup::GetInstanceNode(unsigned index) const | File: ../Graphics/StaticModelGroup.h
    engine->RegisterObjectMethod("StaticModelGroup", "Node@+ GetInstanceNode(uint) const", asMETHODPR(StaticModelGroup, GetInstanceNode, (unsigned) const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "Node@+ get_instanceNodes(uint) const", asMETHODPR(StaticModelGroup, GetInstanceNode, (unsigned) const, Node*), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(StaticModelGroup, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint GetLightMask() const", asMETHODPR(StaticModelGroup, GetLightMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "uint get_lightMask() const", asMETHODPR(StaticModelGroup, GetLightMask, () const, unsigned), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "Array<Light@>@ GetLights() const", asFUNCTION(StaticModelGroup_GetLights_void), asCALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "float GetLodBias() const", asMETHODPR(StaticModelGroup, GetLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "float get_lodBias() const", asMETHODPR(StaticModelGroup, GetLodBias, () const, float), asCALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "float GetLodDistance() const", asMETHODPR(StaticModelGroup, GetLodDistance, () const, float), asCALL_THISCALL);
    // Geometry* StaticModel::GetLodGeometry(unsigned batchIndex, unsigned level) override | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "Geometry@+ GetLodGeometry(uint, uint)", asMETHODPR(StaticModelGroup, GetLodGeometry, (unsigned, unsigned), Geometry*), asCALL_THISCALL);
    // virtual Material* StaticModel::GetMaterial() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "Material@+ GetMaterial() const", asMETHODPR(StaticModelGroup, GetMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "Material@+ get_material() const", asMETHODPR(StaticModelGroup, GetMaterial, () const, Material*), asCALL_THISCALL);
    // virtual Material* StaticModel::GetMaterial(unsigned index) const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "Material@+ GetMaterial(uint) const", asMETHODPR(StaticModelGroup, GetMaterial, (unsigned) const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "Material@+ get_materials(uint) const", asMETHODPR(StaticModelGroup, GetMaterial, (unsigned) const, Material*), asCALL_THISCALL);
    // const ResourceRefList& StaticModel::GetMaterialsAttr() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "const ResourceRefList& GetMaterialsAttr() const", asMETHODPR(StaticModelGroup, GetMaterialsAttr, () const, const ResourceRefList&), asCALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint GetMaxLights() const", asMETHODPR(StaticModelGroup, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "uint get_maxLights() const", asMETHODPR(StaticModelGroup, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "float GetMaxZ() const", asMETHODPR(StaticModelGroup, GetMaxZ, () const, float), asCALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "float GetMinZ() const", asMETHODPR(StaticModelGroup, GetMinZ, () const, float), asCALL_THISCALL);
    // Model* StaticModel::GetModel() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "Model@+ GetModel() const", asMETHODPR(StaticModelGroup, GetModel, () const, Model*), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "Model@+ get_model() const", asMETHODPR(StaticModelGroup, GetModel, () const, Model*), asCALL_THISCALL);
    // ResourceRef StaticModel::GetModelAttr() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "ResourceRef GetModelAttr() const", asMETHODPR(StaticModelGroup, GetModelAttr, () const, ResourceRef), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "Node@+ GetNode() const", asMETHODPR(StaticModelGroup, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "Node@+ get_node() const", asMETHODPR(StaticModelGroup, GetNode, () const, Node*), asCALL_THISCALL);
    // const VariantVector& StaticModelGroup::GetNodeIDsAttr() const | File: ../Graphics/StaticModelGroup.h
    // Error: type "const VariantVector&" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint GetNumAttributes() const", asMETHODPR(StaticModelGroup, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "uint get_numAttributes() const", asMETHODPR(StaticModelGroup, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned StaticModel::GetNumGeometries() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint GetNumGeometries() const", asMETHODPR(StaticModelGroup, GetNumGeometries, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "uint get_numGeometries() const", asMETHODPR(StaticModelGroup, GetNumGeometries, () const, unsigned), asCALL_THISCALL);
    // unsigned StaticModelGroup::GetNumInstanceNodes() const | File: ../Graphics/StaticModelGroup.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint GetNumInstanceNodes() const", asMETHODPR(StaticModelGroup, GetNumInstanceNodes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "uint get_numInstanceNodes() const", asMETHODPR(StaticModelGroup, GetNumInstanceNodes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint GetNumNetworkAttributes() const", asMETHODPR(StaticModelGroup, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned StaticModelGroup::GetNumOccluderTriangles() override | File: ../Graphics/StaticModelGroup.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint GetNumOccluderTriangles()", asMETHODPR(StaticModelGroup, GetNumOccluderTriangles, (), unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(StaticModelGroup, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(StaticModelGroup, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(StaticModelGroup, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // unsigned StaticModel::GetOcclusionLodLevel() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint GetOcclusionLodLevel() const", asMETHODPR(StaticModelGroup, GetOcclusionLodLevel, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "uint get_occlusionLodLevel() const", asMETHODPR(StaticModelGroup, GetOcclusionLodLevel, () const, unsigned), asCALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "Scene@+ GetScene() const", asMETHODPR(StaticModelGroup, GetScene, () const, Scene*), asCALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "float GetShadowDistance() const", asMETHODPR(StaticModelGroup, GetShadowDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "float get_shadowDistance() const", asMETHODPR(StaticModelGroup, GetShadowDistance, () const, float), asCALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint GetShadowMask() const", asMETHODPR(StaticModelGroup, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "uint get_shadowMask() const", asMETHODPR(StaticModelGroup, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "float GetSortValue() const", asMETHODPR(StaticModelGroup, GetSortValue, () const, float), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(StaticModelGroup, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "StringHash GetType() const", asMETHODPR(StaticModelGroup, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "StringHash get_type() const", asMETHODPR(StaticModelGroup, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "const String& GetTypeName() const", asMETHODPR(StaticModelGroup, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "const String& get_typeName() const", asMETHODPR(StaticModelGroup, GetTypeName, () const, const String&), asCALL_THISCALL);
    // virtual UpdateGeometryType Drawable::GetUpdateGeometryType() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "UpdateGeometryType GetUpdateGeometryType()", asMETHODPR(StaticModelGroup, GetUpdateGeometryType, (), UpdateGeometryType), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "Array<Light@>@ GetVertexLights() const", asFUNCTION(StaticModelGroup_GetVertexLights_void), asCALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint GetViewMask() const", asMETHODPR(StaticModelGroup, GetViewMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "uint get_viewMask() const", asMETHODPR(StaticModelGroup, GetViewMask, () const, unsigned), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "const BoundingBox& GetWorldBoundingBox()", asMETHODPR(StaticModelGroup, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "const BoundingBox& get_worldBoundingBox()", asMETHODPR(StaticModelGroup, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "Zone@+ GetZone() const", asMETHODPR(StaticModelGroup, GetZone, () const, Zone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "Zone@+ get_zone() const", asMETHODPR(StaticModelGroup, GetZone, () const, Zone*), asCALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint GetZoneMask() const", asMETHODPR(StaticModelGroup, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "uint get_zoneMask() const", asMETHODPR(StaticModelGroup, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool HasBasePass(uint) const", asMETHODPR(StaticModelGroup, HasBasePass, (unsigned) const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool HasEventHandlers() const", asMETHODPR(StaticModelGroup, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(StaticModelGroup, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(StaticModelGroup, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsEnabled() const", asMETHODPR(StaticModelGroup, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "bool get_enabled() const", asMETHODPR(StaticModelGroup, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsEnabledEffective() const", asMETHODPR(StaticModelGroup, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "bool get_enabledEffective() const", asMETHODPR(StaticModelGroup, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool StaticModel::IsInside(const Vector3& point) const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsInside(const Vector3&in) const", asMETHODPR(StaticModelGroup, IsInside, (const Vector3&) const, bool), asCALL_THISCALL);
    // bool StaticModel::IsInsideLocal(const Vector3& point) const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsInsideLocal(const Vector3&in) const", asMETHODPR(StaticModelGroup, IsInsideLocal, (const Vector3&) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsInstanceOf(StringHash) const", asMETHODPR(StaticModelGroup, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsInView() const", asMETHODPR(StaticModelGroup, IsInView, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "bool get_inView() const", asMETHODPR(StaticModelGroup, IsInView, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsInView(Camera@+) const", asMETHODPR(StaticModelGroup, IsInView, (Camera*) const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsInView(const FrameInfo&in, bool = false) const", asMETHODPR(StaticModelGroup, IsInView, (const FrameInfo&, bool) const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsOccludee() const", asMETHODPR(StaticModelGroup, IsOccludee, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "bool get_occludee() const", asMETHODPR(StaticModelGroup, IsOccludee, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsOccluder() const", asMETHODPR(StaticModelGroup, IsOccluder, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "bool get_occluder() const", asMETHODPR(StaticModelGroup, IsOccluder, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsReplicated() const", asMETHODPR(StaticModelGroup, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "bool get_replicated() const", asMETHODPR(StaticModelGroup, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsTemporary() const", asMETHODPR(StaticModelGroup, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "bool get_temporary() const", asMETHODPR(StaticModelGroup, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsZoneDirty() const", asMETHODPR(StaticModelGroup, IsZoneDirty, () const, bool), asCALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void LimitLights()", asMETHODPR(StaticModelGroup, LimitLights, (), void), asCALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void LimitVertexLights(bool)", asMETHODPR(StaticModelGroup, LimitVertexLights, (bool), void), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool Load(Deserializer&)", asMETHODPR(StaticModelGroup, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool LoadJSON(const JSONValue&in)", asMETHODPR(StaticModelGroup, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool LoadXML(const XMLElement&in)", asMETHODPR(StaticModelGroup, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void MarkForUpdate()", asMETHODPR(StaticModelGroup, MarkForUpdate, (), void), asCALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void MarkInView(const FrameInfo&in)", asMETHODPR(StaticModelGroup, MarkInView, (const FrameInfo&), void), asCALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void MarkInView(uint)", asMETHODPR(StaticModelGroup, MarkInView, (unsigned), void), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "void MarkNetworkUpdate()", asMETHODPR(StaticModelGroup, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(StaticModelGroup, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(StaticModelGroup, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(StaticModelGroup, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Drawable::OnSetEnabled() override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void OnSetEnabled()", asMETHODPR(StaticModelGroup, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "void PrepareNetworkUpdate()", asMETHODPR(StaticModelGroup, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // void StaticModelGroup::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override | File: ../Graphics/StaticModelGroup.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(StaticModelGroup, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(StaticModelGroup, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("StaticModelGroup", "int Refs() const", asMETHODPR(StaticModelGroup, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "int get_refs() const", asMETHODPR(StaticModelGroup, Refs, () const, int), asCALL_THISCALL);
    // static void StaticModelGroup::RegisterObject(Context* context) | File: ../Graphics/StaticModelGroup.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("StaticModelGroup", asBEHAVE_RELEASE, "void f()", asMETHODPR(StaticModelGroup, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "void Remove()", asMETHODPR(StaticModelGroup, Remove, (), void), asCALL_THISCALL);
    // void StaticModelGroup::RemoveAllInstanceNodes() | File: ../Graphics/StaticModelGroup.h
    engine->RegisterObjectMethod("StaticModelGroup", "void RemoveAllInstanceNodes()", asMETHODPR(StaticModelGroup, RemoveAllInstanceNodes, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(StaticModelGroup, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void RemoveInstanceDefault()", asMETHODPR(StaticModelGroup, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void StaticModelGroup::RemoveInstanceNode(Node* node) | File: ../Graphics/StaticModelGroup.h
    engine->RegisterObjectMethod("StaticModelGroup", "void RemoveInstanceNode(Node@+)", asMETHODPR(StaticModelGroup, RemoveInstanceNode, (Node*), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void RemoveObjectAnimation()", asMETHODPR(StaticModelGroup, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void ResetToDefault()", asMETHODPR(StaticModelGroup, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool Save(Serializer&) const", asMETHODPR(StaticModelGroup, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool SaveDefaultAttributes() const", asMETHODPR(StaticModelGroup, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool SaveJSON(JSONValue&) const", asMETHODPR(StaticModelGroup, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool SaveXML(XMLElement&) const", asMETHODPR(StaticModelGroup, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SendEvent(StringHash)", asMETHODPR(StaticModelGroup, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(StaticModelGroup, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetAnimationEnabled(bool)", asMETHODPR(StaticModelGroup, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_animationEnabled(bool)", asMETHODPR(StaticModelGroup, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetAnimationTime(float)", asMETHODPR(StaticModelGroup, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(StaticModelGroup, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "bool set_attributes(uint, const Variant&in)", asMETHODPR(StaticModelGroup, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(StaticModelGroup, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(StaticModelGroup, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(StaticModelGroup, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(StaticModelGroup, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(StaticModelGroup, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetBasePass(uint)", asMETHODPR(StaticModelGroup, SetBasePass, (unsigned), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetBlockEvents(bool)", asMETHODPR(StaticModelGroup, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetCastShadows(bool)", asMETHODPR(StaticModelGroup, SetCastShadows, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_castShadows(bool)", asMETHODPR(StaticModelGroup, SetCastShadows, (bool), void), asCALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetDrawDistance(float)", asMETHODPR(StaticModelGroup, SetDrawDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_drawDistance(float)", asMETHODPR(StaticModelGroup, SetDrawDistance, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetEnabled(bool)", asMETHODPR(StaticModelGroup, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_enabled(bool)", asMETHODPR(StaticModelGroup, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(StaticModelGroup, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(StaticModelGroup, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetInstanceDefault(bool)", asMETHODPR(StaticModelGroup, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(StaticModelGroup, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetLightMask(uint)", asMETHODPR(StaticModelGroup, SetLightMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_lightMask(uint)", asMETHODPR(StaticModelGroup, SetLightMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetLodBias(float)", asMETHODPR(StaticModelGroup, SetLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_lodBias(float)", asMETHODPR(StaticModelGroup, SetLodBias, (float), void), asCALL_THISCALL);
    // virtual void StaticModel::SetMaterial(Material* material) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetMaterial(Material@+)", asMETHODPR(StaticModelGroup, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_material(Material@+)", asMETHODPR(StaticModelGroup, SetMaterial, (Material*), void), asCALL_THISCALL);
    // virtual bool StaticModel::SetMaterial(unsigned index, Material* material) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool SetMaterial(uint, Material@+)", asMETHODPR(StaticModelGroup, SetMaterial, (unsigned, Material*), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "bool set_materials(uint, Material@+)", asMETHODPR(StaticModelGroup, SetMaterial, (unsigned, Material*), bool), asCALL_THISCALL);
    // void StaticModel::SetMaterialsAttr(const ResourceRefList& value) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetMaterialsAttr(const ResourceRefList&in)", asMETHODPR(StaticModelGroup, SetMaterialsAttr, (const ResourceRefList&), void), asCALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetMaxLights(uint)", asMETHODPR(StaticModelGroup, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_maxLights(uint)", asMETHODPR(StaticModelGroup, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetMinMaxZ(float, float)", asMETHODPR(StaticModelGroup, SetMinMaxZ, (float, float), void), asCALL_THISCALL);
    // virtual void StaticModel::SetModel(Model* model) | File: ../Graphics/StaticModel.h
    // Not registered because have @manualbind mark
    // void StaticModel::SetModelAttr(const ResourceRef& value) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetModelAttr(const ResourceRef&in)", asMETHODPR(StaticModelGroup, SetModelAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void StaticModelGroup::SetNodeIDsAttr(const VariantVector& value) | File: ../Graphics/StaticModelGroup.h
    // Error: type "const VariantVector&" can not automatically bind
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(StaticModelGroup, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(StaticModelGroup, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(StaticModelGroup, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetOccludee(bool)", asMETHODPR(StaticModelGroup, SetOccludee, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_occludee(bool)", asMETHODPR(StaticModelGroup, SetOccludee, (bool), void), asCALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetOccluder(bool)", asMETHODPR(StaticModelGroup, SetOccluder, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_occluder(bool)", asMETHODPR(StaticModelGroup, SetOccluder, (bool), void), asCALL_THISCALL);
    // void StaticModel::SetOcclusionLodLevel(unsigned level) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetOcclusionLodLevel(uint)", asMETHODPR(StaticModelGroup, SetOcclusionLodLevel, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_occlusionLodLevel(uint)", asMETHODPR(StaticModelGroup, SetOcclusionLodLevel, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetShadowDistance(float)", asMETHODPR(StaticModelGroup, SetShadowDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_shadowDistance(float)", asMETHODPR(StaticModelGroup, SetShadowDistance, (float), void), asCALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetShadowMask(uint)", asMETHODPR(StaticModelGroup, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_shadowMask(uint)", asMETHODPR(StaticModelGroup, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetSortValue(float)", asMETHODPR(StaticModelGroup, SetSortValue, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetTemporary(bool)", asMETHODPR(StaticModelGroup, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_temporary(bool)", asMETHODPR(StaticModelGroup, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetViewMask(uint)", asMETHODPR(StaticModelGroup, SetViewMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_viewMask(uint)", asMETHODPR(StaticModelGroup, SetViewMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetZone(Zone@+, bool = false)", asMETHODPR(StaticModelGroup, SetZone, (Zone*, bool), void), asCALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetZoneMask(uint)", asMETHODPR(StaticModelGroup, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_zoneMask(uint)", asMETHODPR(StaticModelGroup, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    // explicit StaticModelGroup::StaticModelGroup(Context* context) | File: ../Graphics/StaticModelGroup.h
    engine->RegisterObjectBehaviour("StaticModelGroup", asBEHAVE_FACTORY, "StaticModelGroup@+ f()", asFUNCTION(StaticModelGroup_StaticModelGroup_Context), asCALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "void UnsubscribeFromAllEvents()", asMETHODPR(StaticModelGroup, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(StaticModelGroup_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(StaticModelGroup, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(StaticModelGroup, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(StaticModelGroup, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void Update(const FrameInfo&in)", asMETHODPR(StaticModelGroup, Update, (const FrameInfo&), void), asCALL_THISCALL);
    // void StaticModelGroup::UpdateBatches(const FrameInfo& frame) override | File: ../Graphics/StaticModelGroup.h
    engine->RegisterObjectMethod("StaticModelGroup", "void UpdateBatches(const FrameInfo&in)", asMETHODPR(StaticModelGroup, UpdateBatches, (const FrameInfo&), void), asCALL_THISCALL);
    // virtual void Drawable::UpdateGeometry(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void UpdateGeometry(const FrameInfo&in)", asMETHODPR(StaticModelGroup, UpdateGeometry, (const FrameInfo&), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("StaticModelGroup", "int WeakRefs() const", asMETHODPR(StaticModelGroup, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "int get_weakRefs() const", asMETHODPR(StaticModelGroup, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(StaticModelGroup, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(StaticModelGroup, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(StaticModelGroup, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_StaticModel
    REGISTER_MANUAL_PART_StaticModel(StaticModelGroup, "StaticModelGroup")
#endif
#ifdef REGISTER_MANUAL_PART_Drawable
    REGISTER_MANUAL_PART_Drawable(StaticModelGroup, "StaticModelGroup")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(StaticModelGroup, "StaticModelGroup")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(StaticModelGroup, "StaticModelGroup")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(StaticModelGroup, "StaticModelGroup")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(StaticModelGroup, "StaticModelGroup")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(StaticModelGroup, "StaticModelGroup")
#endif
#ifdef REGISTER_MANUAL_PART_StaticModelGroup
    REGISTER_MANUAL_PART_StaticModelGroup(StaticModelGroup, "StaticModelGroup")
#endif
    RegisterSubclass<StaticModel, StaticModelGroup>(engine, "StaticModel", "StaticModelGroup");
    RegisterSubclass<Drawable, StaticModelGroup>(engine, "Drawable", "StaticModelGroup");
    RegisterSubclass<Component, StaticModelGroup>(engine, "Component", "StaticModelGroup");
    RegisterSubclass<Animatable, StaticModelGroup>(engine, "Animatable", "StaticModelGroup");
    RegisterSubclass<Serializable, StaticModelGroup>(engine, "Serializable", "StaticModelGroup");
    RegisterSubclass<Object, StaticModelGroup>(engine, "Object", "StaticModelGroup");
    RegisterSubclass<RefCounted, StaticModelGroup>(engine, "RefCounted", "StaticModelGroup");

#ifdef URHO3D_URHO2D
    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void AddLight(Light@+)", asMETHODPR(StaticSprite2D, AddLight, (Light*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("StaticSprite2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(StaticSprite2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void AddVertexLight(Light@+)", asMETHODPR(StaticSprite2D, AddVertexLight, (Light*), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void AllocateNetworkState()", asMETHODPR(StaticSprite2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void ApplyAttributes()", asMETHODPR(StaticSprite2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(StaticSprite2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool DrawOcclusion(OcclusionBuffer@+)", asMETHODPR(StaticSprite2D, DrawOcclusion, (OcclusionBuffer*), bool), asCALL_THISCALL);
    // float StaticSprite2D::GetAlpha() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "float GetAlpha() const", asMETHODPR(StaticSprite2D, GetAlpha, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "float get_alpha() const", asMETHODPR(StaticSprite2D, GetAlpha, () const, float), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool GetAnimationEnabled() const", asMETHODPR(StaticSprite2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_animationEnabled() const", asMETHODPR(StaticSprite2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "Variant GetAttribute(uint) const", asMETHODPR(StaticSprite2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "Variant get_attributes(uint) const", asMETHODPR(StaticSprite2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "Variant GetAttribute(const String&in) const", asMETHODPR(StaticSprite2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(StaticSprite2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(StaticSprite2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(StaticSprite2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(StaticSprite2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(StaticSprite2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(StaticSprite2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(StaticSprite2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // BlendMode StaticSprite2D::GetBlendMode() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "BlendMode GetBlendMode() const", asMETHODPR(StaticSprite2D, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "BlendMode get_blendMode() const", asMETHODPR(StaticSprite2D, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool GetBlockEvents() const", asMETHODPR(StaticSprite2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "const BoundingBox& GetBoundingBox() const", asMETHODPR(StaticSprite2D, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "const BoundingBox& get_boundingBox() const", asMETHODPR(StaticSprite2D, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool GetCastShadows() const", asMETHODPR(StaticSprite2D, GetCastShadows, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_castShadows() const", asMETHODPR(StaticSprite2D, GetCastShadows, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "const String& GetCategory() const", asMETHODPR(StaticSprite2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "const String& get_category() const", asMETHODPR(StaticSprite2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // const Color& StaticSprite2D::GetColor() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "const Color& GetColor() const", asMETHODPR(StaticSprite2D, GetColor, () const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "const Color& get_color() const", asMETHODPR(StaticSprite2D, GetColor, () const, const Color&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(StaticSprite2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // Material* StaticSprite2D::GetCustomMaterial() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "Material@+ GetCustomMaterial() const", asMETHODPR(StaticSprite2D, GetCustomMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "Material@+ get_customMaterial() const", asMETHODPR(StaticSprite2D, GetCustomMaterial, () const, Material*), asCALL_THISCALL);
    // ResourceRef StaticSprite2D::GetCustomMaterialAttr() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "ResourceRef GetCustomMaterialAttr() const", asMETHODPR(StaticSprite2D, GetCustomMaterialAttr, () const, ResourceRef), asCALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // float Drawable::GetDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "float GetDistance() const", asMETHODPR(StaticSprite2D, GetDistance, () const, float), asCALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "uint8 GetDrawableFlags() const", asMETHODPR(StaticSprite2D, GetDrawableFlags, () const, unsigned char), asCALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "float GetDrawDistance() const", asMETHODPR(StaticSprite2D, GetDrawDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "float get_drawDistance() const", asMETHODPR(StaticSprite2D, GetDrawDistance, () const, float), asCALL_THISCALL);
    // const Rect& StaticSprite2D::GetDrawRect() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "const Rect& GetDrawRect() const", asMETHODPR(StaticSprite2D, GetDrawRect, () const, const Rect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "const Rect& get_drawRect() const", asMETHODPR(StaticSprite2D, GetDrawRect, () const, const Rect&), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "VariantMap& GetEventDataMap() const", asMETHODPR(StaticSprite2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "Object@+ GetEventSender() const", asMETHODPR(StaticSprite2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "Light@+ GetFirstLight() const", asMETHODPR(StaticSprite2D, GetFirstLight, () const, Light*), asCALL_THISCALL);
    // bool StaticSprite2D::GetFlipX() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool GetFlipX() const", asMETHODPR(StaticSprite2D, GetFlipX, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_flipX() const", asMETHODPR(StaticSprite2D, GetFlipX, () const, bool), asCALL_THISCALL);
    // bool StaticSprite2D::GetFlipY() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool GetFlipY() const", asMETHODPR(StaticSprite2D, GetFlipY, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_flipY() const", asMETHODPR(StaticSprite2D, GetFlipY, () const, bool), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(StaticSprite2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(StaticSprite2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(StaticSprite2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "const VariantMap& get_globalVars() const", asMETHODPR(StaticSprite2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // const Vector2& StaticSprite2D::GetHotSpot() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "const Vector2& GetHotSpot() const", asMETHODPR(StaticSprite2D, GetHotSpot, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "const Vector2& get_hotSpot() const", asMETHODPR(StaticSprite2D, GetHotSpot, () const, const Vector2&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "uint GetID() const", asMETHODPR(StaticSprite2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "uint get_id() const", asMETHODPR(StaticSprite2D, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(StaticSprite2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // int Drawable2D::GetLayer() const | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "int GetLayer() const", asMETHODPR(StaticSprite2D, GetLayer, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "int get_layer() const", asMETHODPR(StaticSprite2D, GetLayer, () const, int), asCALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "uint GetLightMask() const", asMETHODPR(StaticSprite2D, GetLightMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "uint get_lightMask() const", asMETHODPR(StaticSprite2D, GetLightMask, () const, unsigned), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "Array<Light@>@ GetLights() const", asFUNCTION(StaticSprite2D_GetLights_void), asCALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "float GetLodBias() const", asMETHODPR(StaticSprite2D, GetLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "float get_lodBias() const", asMETHODPR(StaticSprite2D, GetLodBias, () const, float), asCALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "float GetLodDistance() const", asMETHODPR(StaticSprite2D, GetLodDistance, () const, float), asCALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "Geometry@+ GetLodGeometry(uint, uint)", asMETHODPR(StaticSprite2D, GetLodGeometry, (unsigned, unsigned), Geometry*), asCALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "uint GetMaxLights() const", asMETHODPR(StaticSprite2D, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "uint get_maxLights() const", asMETHODPR(StaticSprite2D, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "float GetMaxZ() const", asMETHODPR(StaticSprite2D, GetMaxZ, () const, float), asCALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "float GetMinZ() const", asMETHODPR(StaticSprite2D, GetMinZ, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "Node@+ GetNode() const", asMETHODPR(StaticSprite2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "Node@+ get_node() const", asMETHODPR(StaticSprite2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "uint GetNumAttributes() const", asMETHODPR(StaticSprite2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "uint get_numAttributes() const", asMETHODPR(StaticSprite2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "uint GetNumNetworkAttributes() const", asMETHODPR(StaticSprite2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "uint GetNumOccluderTriangles()", asMETHODPR(StaticSprite2D, GetNumOccluderTriangles, (), unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(StaticSprite2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(StaticSprite2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(StaticSprite2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // int Drawable2D::GetOrderInLayer() const | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "int GetOrderInLayer() const", asMETHODPR(StaticSprite2D, GetOrderInLayer, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "int get_orderInLayer() const", asMETHODPR(StaticSprite2D, GetOrderInLayer, () const, int), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "Scene@+ GetScene() const", asMETHODPR(StaticSprite2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "float GetShadowDistance() const", asMETHODPR(StaticSprite2D, GetShadowDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "float get_shadowDistance() const", asMETHODPR(StaticSprite2D, GetShadowDistance, () const, float), asCALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "uint GetShadowMask() const", asMETHODPR(StaticSprite2D, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "uint get_shadowMask() const", asMETHODPR(StaticSprite2D, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "float GetSortValue() const", asMETHODPR(StaticSprite2D, GetSortValue, () const, float), asCALL_THISCALL);
    // const Vector<SourceBatch2D>& Drawable2D::GetSourceBatches() | File: ../Urho2D/Drawable2D.h
    // Error: type "const Vector<SourceBatch2D>&" can not automatically bind
    // Sprite2D* StaticSprite2D::GetSprite() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "Sprite2D@+ GetSprite() const", asMETHODPR(StaticSprite2D, GetSprite, () const, Sprite2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "Sprite2D@+ get_sprite() const", asMETHODPR(StaticSprite2D, GetSprite, () const, Sprite2D*), asCALL_THISCALL);
    // ResourceRef StaticSprite2D::GetSpriteAttr() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "ResourceRef GetSpriteAttr() const", asMETHODPR(StaticSprite2D, GetSpriteAttr, () const, ResourceRef), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(StaticSprite2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // bool StaticSprite2D::GetSwapXY() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool GetSwapXY() const", asMETHODPR(StaticSprite2D, GetSwapXY, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_swapXY() const", asMETHODPR(StaticSprite2D, GetSwapXY, () const, bool), asCALL_THISCALL);
    // const Rect& StaticSprite2D::GetTextureRect() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "const Rect& GetTextureRect() const", asMETHODPR(StaticSprite2D, GetTextureRect, () const, const Rect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "const Rect& get_textureRect() const", asMETHODPR(StaticSprite2D, GetTextureRect, () const, const Rect&), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "StringHash GetType() const", asMETHODPR(StaticSprite2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "StringHash get_type() const", asMETHODPR(StaticSprite2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "const String& GetTypeName() const", asMETHODPR(StaticSprite2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "const String& get_typeName() const", asMETHODPR(StaticSprite2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // virtual UpdateGeometryType Drawable::GetUpdateGeometryType() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "UpdateGeometryType GetUpdateGeometryType()", asMETHODPR(StaticSprite2D, GetUpdateGeometryType, (), UpdateGeometryType), asCALL_THISCALL);
    // bool StaticSprite2D::GetUseDrawRect() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool GetUseDrawRect() const", asMETHODPR(StaticSprite2D, GetUseDrawRect, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_useDrawRect() const", asMETHODPR(StaticSprite2D, GetUseDrawRect, () const, bool), asCALL_THISCALL);
    // bool StaticSprite2D::GetUseHotSpot() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool GetUseHotSpot() const", asMETHODPR(StaticSprite2D, GetUseHotSpot, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_useHotSpot() const", asMETHODPR(StaticSprite2D, GetUseHotSpot, () const, bool), asCALL_THISCALL);
    // bool StaticSprite2D::GetUseTextureRect() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool GetUseTextureRect() const", asMETHODPR(StaticSprite2D, GetUseTextureRect, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_useTextureRect() const", asMETHODPR(StaticSprite2D, GetUseTextureRect, () const, bool), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "Array<Light@>@ GetVertexLights() const", asFUNCTION(StaticSprite2D_GetVertexLights_void), asCALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "uint GetViewMask() const", asMETHODPR(StaticSprite2D, GetViewMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "uint get_viewMask() const", asMETHODPR(StaticSprite2D, GetViewMask, () const, unsigned), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "const BoundingBox& GetWorldBoundingBox()", asMETHODPR(StaticSprite2D, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "const BoundingBox& get_worldBoundingBox()", asMETHODPR(StaticSprite2D, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "Zone@+ GetZone() const", asMETHODPR(StaticSprite2D, GetZone, () const, Zone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "Zone@+ get_zone() const", asMETHODPR(StaticSprite2D, GetZone, () const, Zone*), asCALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "uint GetZoneMask() const", asMETHODPR(StaticSprite2D, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "uint get_zoneMask() const", asMETHODPR(StaticSprite2D, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool HasBasePass(uint) const", asMETHODPR(StaticSprite2D, HasBasePass, (unsigned) const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool HasEventHandlers() const", asMETHODPR(StaticSprite2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(StaticSprite2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(StaticSprite2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool IsEnabled() const", asMETHODPR(StaticSprite2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_enabled() const", asMETHODPR(StaticSprite2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool IsEnabledEffective() const", asMETHODPR(StaticSprite2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_enabledEffective() const", asMETHODPR(StaticSprite2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(StaticSprite2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool IsInView() const", asMETHODPR(StaticSprite2D, IsInView, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_inView() const", asMETHODPR(StaticSprite2D, IsInView, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool IsInView(Camera@+) const", asMETHODPR(StaticSprite2D, IsInView, (Camera*) const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool IsInView(const FrameInfo&in, bool = false) const", asMETHODPR(StaticSprite2D, IsInView, (const FrameInfo&, bool) const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool IsOccludee() const", asMETHODPR(StaticSprite2D, IsOccludee, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_occludee() const", asMETHODPR(StaticSprite2D, IsOccludee, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool IsOccluder() const", asMETHODPR(StaticSprite2D, IsOccluder, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_occluder() const", asMETHODPR(StaticSprite2D, IsOccluder, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool IsReplicated() const", asMETHODPR(StaticSprite2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_replicated() const", asMETHODPR(StaticSprite2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool IsTemporary() const", asMETHODPR(StaticSprite2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_temporary() const", asMETHODPR(StaticSprite2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool IsZoneDirty() const", asMETHODPR(StaticSprite2D, IsZoneDirty, () const, bool), asCALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void LimitLights()", asMETHODPR(StaticSprite2D, LimitLights, (), void), asCALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void LimitVertexLights(bool)", asMETHODPR(StaticSprite2D, LimitVertexLights, (bool), void), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool Load(Deserializer&)", asMETHODPR(StaticSprite2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(StaticSprite2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(StaticSprite2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void MarkForUpdate()", asMETHODPR(StaticSprite2D, MarkForUpdate, (), void), asCALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void MarkInView(const FrameInfo&in)", asMETHODPR(StaticSprite2D, MarkInView, (const FrameInfo&), void), asCALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void MarkInView(uint)", asMETHODPR(StaticSprite2D, MarkInView, (unsigned), void), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "void MarkNetworkUpdate()", asMETHODPR(StaticSprite2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(StaticSprite2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(StaticSprite2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(StaticSprite2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Drawable2D::OnSetEnabled() override | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void OnSetEnabled()", asMETHODPR(StaticSprite2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "void PrepareNetworkUpdate()", asMETHODPR(StaticSprite2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) | File: ../Graphics/Drawable.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(StaticSprite2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(StaticSprite2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("StaticSprite2D", "int Refs() const", asMETHODPR(StaticSprite2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "int get_refs() const", asMETHODPR(StaticSprite2D, Refs, () const, int), asCALL_THISCALL);
    // static void StaticSprite2D::RegisterObject(Context* context) | File: ../Urho2D/StaticSprite2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("StaticSprite2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(StaticSprite2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "void Remove()", asMETHODPR(StaticSprite2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(StaticSprite2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void RemoveInstanceDefault()", asMETHODPR(StaticSprite2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void RemoveObjectAnimation()", asMETHODPR(StaticSprite2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void ResetToDefault()", asMETHODPR(StaticSprite2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool Save(Serializer&) const", asMETHODPR(StaticSprite2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool SaveDefaultAttributes() const", asMETHODPR(StaticSprite2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(StaticSprite2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool SaveXML(XMLElement&) const", asMETHODPR(StaticSprite2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SendEvent(StringHash)", asMETHODPR(StaticSprite2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(StaticSprite2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void StaticSprite2D::SetAlpha(float alpha) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetAlpha(float)", asMETHODPR(StaticSprite2D, SetAlpha, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_alpha(float)", asMETHODPR(StaticSprite2D, SetAlpha, (float), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetAnimationEnabled(bool)", asMETHODPR(StaticSprite2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_animationEnabled(bool)", asMETHODPR(StaticSprite2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetAnimationTime(float)", asMETHODPR(StaticSprite2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(StaticSprite2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(StaticSprite2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(StaticSprite2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(StaticSprite2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(StaticSprite2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(StaticSprite2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(StaticSprite2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetBasePass(uint)", asMETHODPR(StaticSprite2D, SetBasePass, (unsigned), void), asCALL_THISCALL);
    // void StaticSprite2D::SetBlendMode(BlendMode blendMode) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetBlendMode(BlendMode)", asMETHODPR(StaticSprite2D, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_blendMode(BlendMode)", asMETHODPR(StaticSprite2D, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetBlockEvents(bool)", asMETHODPR(StaticSprite2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetCastShadows(bool)", asMETHODPR(StaticSprite2D, SetCastShadows, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_castShadows(bool)", asMETHODPR(StaticSprite2D, SetCastShadows, (bool), void), asCALL_THISCALL);
    // void StaticSprite2D::SetColor(const Color& color) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetColor(const Color&in)", asMETHODPR(StaticSprite2D, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_color(const Color&in)", asMETHODPR(StaticSprite2D, SetColor, (const Color&), void), asCALL_THISCALL);
    // void StaticSprite2D::SetCustomMaterial(Material* customMaterial) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetCustomMaterial(Material@+)", asMETHODPR(StaticSprite2D, SetCustomMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_customMaterial(Material@+)", asMETHODPR(StaticSprite2D, SetCustomMaterial, (Material*), void), asCALL_THISCALL);
    // void StaticSprite2D::SetCustomMaterialAttr(const ResourceRef& value) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetCustomMaterialAttr(const ResourceRef&in)", asMETHODPR(StaticSprite2D, SetCustomMaterialAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetDrawDistance(float)", asMETHODPR(StaticSprite2D, SetDrawDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_drawDistance(float)", asMETHODPR(StaticSprite2D, SetDrawDistance, (float), void), asCALL_THISCALL);
    // void StaticSprite2D::SetDrawRect(const Rect& rect) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetDrawRect(const Rect&in)", asMETHODPR(StaticSprite2D, SetDrawRect, (const Rect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_drawRect(const Rect&in)", asMETHODPR(StaticSprite2D, SetDrawRect, (const Rect&), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetEnabled(bool)", asMETHODPR(StaticSprite2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_enabled(bool)", asMETHODPR(StaticSprite2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void StaticSprite2D::SetFlip(bool flipX, bool flipY, bool swapXY=false) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetFlip(bool, bool, bool = false)", asMETHODPR(StaticSprite2D, SetFlip, (bool, bool, bool), void), asCALL_THISCALL);
    // void StaticSprite2D::SetFlipX(bool flipX) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetFlipX(bool)", asMETHODPR(StaticSprite2D, SetFlipX, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_flipX(bool)", asMETHODPR(StaticSprite2D, SetFlipX, (bool), void), asCALL_THISCALL);
    // void StaticSprite2D::SetFlipY(bool flipY) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetFlipY(bool)", asMETHODPR(StaticSprite2D, SetFlipY, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_flipY(bool)", asMETHODPR(StaticSprite2D, SetFlipY, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(StaticSprite2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(StaticSprite2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void StaticSprite2D::SetHotSpot(const Vector2& hotspot) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetHotSpot(const Vector2&in)", asMETHODPR(StaticSprite2D, SetHotSpot, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_hotSpot(const Vector2&in)", asMETHODPR(StaticSprite2D, SetHotSpot, (const Vector2&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetInstanceDefault(bool)", asMETHODPR(StaticSprite2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(StaticSprite2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Drawable2D::SetLayer(int layer) | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetLayer(int)", asMETHODPR(StaticSprite2D, SetLayer, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_layer(int)", asMETHODPR(StaticSprite2D, SetLayer, (int), void), asCALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetLightMask(uint)", asMETHODPR(StaticSprite2D, SetLightMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_lightMask(uint)", asMETHODPR(StaticSprite2D, SetLightMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetLodBias(float)", asMETHODPR(StaticSprite2D, SetLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_lodBias(float)", asMETHODPR(StaticSprite2D, SetLodBias, (float), void), asCALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetMaxLights(uint)", asMETHODPR(StaticSprite2D, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_maxLights(uint)", asMETHODPR(StaticSprite2D, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetMinMaxZ(float, float)", asMETHODPR(StaticSprite2D, SetMinMaxZ, (float, float), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(StaticSprite2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(StaticSprite2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(StaticSprite2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetOccludee(bool)", asMETHODPR(StaticSprite2D, SetOccludee, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_occludee(bool)", asMETHODPR(StaticSprite2D, SetOccludee, (bool), void), asCALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetOccluder(bool)", asMETHODPR(StaticSprite2D, SetOccluder, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_occluder(bool)", asMETHODPR(StaticSprite2D, SetOccluder, (bool), void), asCALL_THISCALL);
    // void Drawable2D::SetOrderInLayer(int orderInLayer) | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetOrderInLayer(int)", asMETHODPR(StaticSprite2D, SetOrderInLayer, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_orderInLayer(int)", asMETHODPR(StaticSprite2D, SetOrderInLayer, (int), void), asCALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetShadowDistance(float)", asMETHODPR(StaticSprite2D, SetShadowDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_shadowDistance(float)", asMETHODPR(StaticSprite2D, SetShadowDistance, (float), void), asCALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetShadowMask(uint)", asMETHODPR(StaticSprite2D, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_shadowMask(uint)", asMETHODPR(StaticSprite2D, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetSortValue(float)", asMETHODPR(StaticSprite2D, SetSortValue, (float), void), asCALL_THISCALL);
    // void StaticSprite2D::SetSprite(Sprite2D* sprite) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetSprite(Sprite2D@+)", asMETHODPR(StaticSprite2D, SetSprite, (Sprite2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_sprite(Sprite2D@+)", asMETHODPR(StaticSprite2D, SetSprite, (Sprite2D*), void), asCALL_THISCALL);
    // void StaticSprite2D::SetSpriteAttr(const ResourceRef& value) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetSpriteAttr(const ResourceRef&in)", asMETHODPR(StaticSprite2D, SetSpriteAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void StaticSprite2D::SetSwapXY(bool swapXY) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetSwapXY(bool)", asMETHODPR(StaticSprite2D, SetSwapXY, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_swapXY(bool)", asMETHODPR(StaticSprite2D, SetSwapXY, (bool), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetTemporary(bool)", asMETHODPR(StaticSprite2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_temporary(bool)", asMETHODPR(StaticSprite2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void StaticSprite2D::SetTextureRect(const Rect& rect) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetTextureRect(const Rect&in)", asMETHODPR(StaticSprite2D, SetTextureRect, (const Rect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_textureRect(const Rect&in)", asMETHODPR(StaticSprite2D, SetTextureRect, (const Rect&), void), asCALL_THISCALL);
    // void StaticSprite2D::SetUseDrawRect(bool useDrawRect) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetUseDrawRect(bool)", asMETHODPR(StaticSprite2D, SetUseDrawRect, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_useDrawRect(bool)", asMETHODPR(StaticSprite2D, SetUseDrawRect, (bool), void), asCALL_THISCALL);
    // void StaticSprite2D::SetUseHotSpot(bool useHotSpot) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetUseHotSpot(bool)", asMETHODPR(StaticSprite2D, SetUseHotSpot, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_useHotSpot(bool)", asMETHODPR(StaticSprite2D, SetUseHotSpot, (bool), void), asCALL_THISCALL);
    // void StaticSprite2D::SetUseTextureRect(bool useTextureRect) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetUseTextureRect(bool)", asMETHODPR(StaticSprite2D, SetUseTextureRect, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_useTextureRect(bool)", asMETHODPR(StaticSprite2D, SetUseTextureRect, (bool), void), asCALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetViewMask(uint)", asMETHODPR(StaticSprite2D, SetViewMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_viewMask(uint)", asMETHODPR(StaticSprite2D, SetViewMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetZone(Zone@+, bool = false)", asMETHODPR(StaticSprite2D, SetZone, (Zone*, bool), void), asCALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetZoneMask(uint)", asMETHODPR(StaticSprite2D, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_zoneMask(uint)", asMETHODPR(StaticSprite2D, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    // explicit StaticSprite2D::StaticSprite2D(Context* context) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectBehaviour("StaticSprite2D", asBEHAVE_FACTORY, "StaticSprite2D@+ f()", asFUNCTION(StaticSprite2D_StaticSprite2D_Context), asCALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "void UnsubscribeFromAllEvents()", asMETHODPR(StaticSprite2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(StaticSprite2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(StaticSprite2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(StaticSprite2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(StaticSprite2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void Update(const FrameInfo&in)", asMETHODPR(StaticSprite2D, Update, (const FrameInfo&), void), asCALL_THISCALL);
    // virtual void Drawable::UpdateBatches(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void UpdateBatches(const FrameInfo&in)", asMETHODPR(StaticSprite2D, UpdateBatches, (const FrameInfo&), void), asCALL_THISCALL);
    // virtual void Drawable::UpdateGeometry(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void UpdateGeometry(const FrameInfo&in)", asMETHODPR(StaticSprite2D, UpdateGeometry, (const FrameInfo&), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("StaticSprite2D", "int WeakRefs() const", asMETHODPR(StaticSprite2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "int get_weakRefs() const", asMETHODPR(StaticSprite2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(StaticSprite2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(StaticSprite2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(StaticSprite2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Drawable2D
    REGISTER_MANUAL_PART_Drawable2D(StaticSprite2D, "StaticSprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_Drawable
    REGISTER_MANUAL_PART_Drawable(StaticSprite2D, "StaticSprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(StaticSprite2D, "StaticSprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(StaticSprite2D, "StaticSprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(StaticSprite2D, "StaticSprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(StaticSprite2D, "StaticSprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(StaticSprite2D, "StaticSprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_StaticSprite2D
    REGISTER_MANUAL_PART_StaticSprite2D(StaticSprite2D, "StaticSprite2D")
#endif
    RegisterSubclass<Drawable2D, StaticSprite2D>(engine, "Drawable2D", "StaticSprite2D");
    RegisterSubclass<Drawable, StaticSprite2D>(engine, "Drawable", "StaticSprite2D");
    RegisterSubclass<Component, StaticSprite2D>(engine, "Component", "StaticSprite2D");
    RegisterSubclass<Animatable, StaticSprite2D>(engine, "Animatable", "StaticSprite2D");
    RegisterSubclass<Serializable, StaticSprite2D>(engine, "Serializable", "StaticSprite2D");
    RegisterSubclass<Object, StaticSprite2D>(engine, "Object", "StaticSprite2D");
    RegisterSubclass<RefCounted, StaticSprite2D>(engine, "RefCounted", "StaticSprite2D");
#endif

#ifdef URHO3D_URHO2D
    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void AddLight(Light@+)", asMETHODPR(StretchableSprite2D, AddLight, (Light*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("StretchableSprite2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(StretchableSprite2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void AddVertexLight(Light@+)", asMETHODPR(StretchableSprite2D, AddVertexLight, (Light*), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void AllocateNetworkState()", asMETHODPR(StretchableSprite2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void ApplyAttributes()", asMETHODPR(StretchableSprite2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(StretchableSprite2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool DrawOcclusion(OcclusionBuffer@+)", asMETHODPR(StretchableSprite2D, DrawOcclusion, (OcclusionBuffer*), bool), asCALL_THISCALL);
    // float StaticSprite2D::GetAlpha() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "float GetAlpha() const", asMETHODPR(StretchableSprite2D, GetAlpha, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "float get_alpha() const", asMETHODPR(StretchableSprite2D, GetAlpha, () const, float), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool GetAnimationEnabled() const", asMETHODPR(StretchableSprite2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_animationEnabled() const", asMETHODPR(StretchableSprite2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Variant GetAttribute(uint) const", asMETHODPR(StretchableSprite2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "Variant get_attributes(uint) const", asMETHODPR(StretchableSprite2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Variant GetAttribute(const String&in) const", asMETHODPR(StretchableSprite2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(StretchableSprite2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(StretchableSprite2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(StretchableSprite2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(StretchableSprite2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(StretchableSprite2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(StretchableSprite2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(StretchableSprite2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // BlendMode StaticSprite2D::GetBlendMode() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "BlendMode GetBlendMode() const", asMETHODPR(StretchableSprite2D, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "BlendMode get_blendMode() const", asMETHODPR(StretchableSprite2D, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool GetBlockEvents() const", asMETHODPR(StretchableSprite2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const IntRect& StretchableSprite2D::GetBorder() const | File: ../Urho2D/StretchableSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "const IntRect& GetBorder() const", asMETHODPR(StretchableSprite2D, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "const IntRect& get_border() const", asMETHODPR(StretchableSprite2D, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "const BoundingBox& GetBoundingBox() const", asMETHODPR(StretchableSprite2D, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "const BoundingBox& get_boundingBox() const", asMETHODPR(StretchableSprite2D, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool GetCastShadows() const", asMETHODPR(StretchableSprite2D, GetCastShadows, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_castShadows() const", asMETHODPR(StretchableSprite2D, GetCastShadows, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "const String& GetCategory() const", asMETHODPR(StretchableSprite2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "const String& get_category() const", asMETHODPR(StretchableSprite2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // const Color& StaticSprite2D::GetColor() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "const Color& GetColor() const", asMETHODPR(StretchableSprite2D, GetColor, () const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "const Color& get_color() const", asMETHODPR(StretchableSprite2D, GetColor, () const, const Color&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(StretchableSprite2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // Material* StaticSprite2D::GetCustomMaterial() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Material@+ GetCustomMaterial() const", asMETHODPR(StretchableSprite2D, GetCustomMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "Material@+ get_customMaterial() const", asMETHODPR(StretchableSprite2D, GetCustomMaterial, () const, Material*), asCALL_THISCALL);
    // ResourceRef StaticSprite2D::GetCustomMaterialAttr() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "ResourceRef GetCustomMaterialAttr() const", asMETHODPR(StretchableSprite2D, GetCustomMaterialAttr, () const, ResourceRef), asCALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // float Drawable::GetDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "float GetDistance() const", asMETHODPR(StretchableSprite2D, GetDistance, () const, float), asCALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "uint8 GetDrawableFlags() const", asMETHODPR(StretchableSprite2D, GetDrawableFlags, () const, unsigned char), asCALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "float GetDrawDistance() const", asMETHODPR(StretchableSprite2D, GetDrawDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "float get_drawDistance() const", asMETHODPR(StretchableSprite2D, GetDrawDistance, () const, float), asCALL_THISCALL);
    // const Rect& StaticSprite2D::GetDrawRect() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "const Rect& GetDrawRect() const", asMETHODPR(StretchableSprite2D, GetDrawRect, () const, const Rect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "const Rect& get_drawRect() const", asMETHODPR(StretchableSprite2D, GetDrawRect, () const, const Rect&), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "VariantMap& GetEventDataMap() const", asMETHODPR(StretchableSprite2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Object@+ GetEventSender() const", asMETHODPR(StretchableSprite2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Light@+ GetFirstLight() const", asMETHODPR(StretchableSprite2D, GetFirstLight, () const, Light*), asCALL_THISCALL);
    // bool StaticSprite2D::GetFlipX() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool GetFlipX() const", asMETHODPR(StretchableSprite2D, GetFlipX, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_flipX() const", asMETHODPR(StretchableSprite2D, GetFlipX, () const, bool), asCALL_THISCALL);
    // bool StaticSprite2D::GetFlipY() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool GetFlipY() const", asMETHODPR(StretchableSprite2D, GetFlipY, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_flipY() const", asMETHODPR(StretchableSprite2D, GetFlipY, () const, bool), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(StretchableSprite2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(StretchableSprite2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(StretchableSprite2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "const VariantMap& get_globalVars() const", asMETHODPR(StretchableSprite2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // const Vector2& StaticSprite2D::GetHotSpot() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "const Vector2& GetHotSpot() const", asMETHODPR(StretchableSprite2D, GetHotSpot, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "const Vector2& get_hotSpot() const", asMETHODPR(StretchableSprite2D, GetHotSpot, () const, const Vector2&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "uint GetID() const", asMETHODPR(StretchableSprite2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "uint get_id() const", asMETHODPR(StretchableSprite2D, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(StretchableSprite2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // int Drawable2D::GetLayer() const | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "int GetLayer() const", asMETHODPR(StretchableSprite2D, GetLayer, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "int get_layer() const", asMETHODPR(StretchableSprite2D, GetLayer, () const, int), asCALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "uint GetLightMask() const", asMETHODPR(StretchableSprite2D, GetLightMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "uint get_lightMask() const", asMETHODPR(StretchableSprite2D, GetLightMask, () const, unsigned), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Array<Light@>@ GetLights() const", asFUNCTION(StretchableSprite2D_GetLights_void), asCALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "float GetLodBias() const", asMETHODPR(StretchableSprite2D, GetLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "float get_lodBias() const", asMETHODPR(StretchableSprite2D, GetLodBias, () const, float), asCALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "float GetLodDistance() const", asMETHODPR(StretchableSprite2D, GetLodDistance, () const, float), asCALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Geometry@+ GetLodGeometry(uint, uint)", asMETHODPR(StretchableSprite2D, GetLodGeometry, (unsigned, unsigned), Geometry*), asCALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "uint GetMaxLights() const", asMETHODPR(StretchableSprite2D, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "uint get_maxLights() const", asMETHODPR(StretchableSprite2D, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "float GetMaxZ() const", asMETHODPR(StretchableSprite2D, GetMaxZ, () const, float), asCALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "float GetMinZ() const", asMETHODPR(StretchableSprite2D, GetMinZ, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Node@+ GetNode() const", asMETHODPR(StretchableSprite2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "Node@+ get_node() const", asMETHODPR(StretchableSprite2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "uint GetNumAttributes() const", asMETHODPR(StretchableSprite2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "uint get_numAttributes() const", asMETHODPR(StretchableSprite2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "uint GetNumNetworkAttributes() const", asMETHODPR(StretchableSprite2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "uint GetNumOccluderTriangles()", asMETHODPR(StretchableSprite2D, GetNumOccluderTriangles, (), unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(StretchableSprite2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(StretchableSprite2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(StretchableSprite2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // int Drawable2D::GetOrderInLayer() const | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "int GetOrderInLayer() const", asMETHODPR(StretchableSprite2D, GetOrderInLayer, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "int get_orderInLayer() const", asMETHODPR(StretchableSprite2D, GetOrderInLayer, () const, int), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Scene@+ GetScene() const", asMETHODPR(StretchableSprite2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "float GetShadowDistance() const", asMETHODPR(StretchableSprite2D, GetShadowDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "float get_shadowDistance() const", asMETHODPR(StretchableSprite2D, GetShadowDistance, () const, float), asCALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "uint GetShadowMask() const", asMETHODPR(StretchableSprite2D, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "uint get_shadowMask() const", asMETHODPR(StretchableSprite2D, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "float GetSortValue() const", asMETHODPR(StretchableSprite2D, GetSortValue, () const, float), asCALL_THISCALL);
    // const Vector<SourceBatch2D>& Drawable2D::GetSourceBatches() | File: ../Urho2D/Drawable2D.h
    // Error: type "const Vector<SourceBatch2D>&" can not automatically bind
    // Sprite2D* StaticSprite2D::GetSprite() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Sprite2D@+ GetSprite() const", asMETHODPR(StretchableSprite2D, GetSprite, () const, Sprite2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "Sprite2D@+ get_sprite() const", asMETHODPR(StretchableSprite2D, GetSprite, () const, Sprite2D*), asCALL_THISCALL);
    // ResourceRef StaticSprite2D::GetSpriteAttr() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "ResourceRef GetSpriteAttr() const", asMETHODPR(StretchableSprite2D, GetSpriteAttr, () const, ResourceRef), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(StretchableSprite2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // bool StaticSprite2D::GetSwapXY() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool GetSwapXY() const", asMETHODPR(StretchableSprite2D, GetSwapXY, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_swapXY() const", asMETHODPR(StretchableSprite2D, GetSwapXY, () const, bool), asCALL_THISCALL);
    // const Rect& StaticSprite2D::GetTextureRect() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "const Rect& GetTextureRect() const", asMETHODPR(StretchableSprite2D, GetTextureRect, () const, const Rect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "const Rect& get_textureRect() const", asMETHODPR(StretchableSprite2D, GetTextureRect, () const, const Rect&), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "StringHash GetType() const", asMETHODPR(StretchableSprite2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "StringHash get_type() const", asMETHODPR(StretchableSprite2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "const String& GetTypeName() const", asMETHODPR(StretchableSprite2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "const String& get_typeName() const", asMETHODPR(StretchableSprite2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // virtual UpdateGeometryType Drawable::GetUpdateGeometryType() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "UpdateGeometryType GetUpdateGeometryType()", asMETHODPR(StretchableSprite2D, GetUpdateGeometryType, (), UpdateGeometryType), asCALL_THISCALL);
    // bool StaticSprite2D::GetUseDrawRect() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool GetUseDrawRect() const", asMETHODPR(StretchableSprite2D, GetUseDrawRect, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_useDrawRect() const", asMETHODPR(StretchableSprite2D, GetUseDrawRect, () const, bool), asCALL_THISCALL);
    // bool StaticSprite2D::GetUseHotSpot() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool GetUseHotSpot() const", asMETHODPR(StretchableSprite2D, GetUseHotSpot, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_useHotSpot() const", asMETHODPR(StretchableSprite2D, GetUseHotSpot, () const, bool), asCALL_THISCALL);
    // bool StaticSprite2D::GetUseTextureRect() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool GetUseTextureRect() const", asMETHODPR(StretchableSprite2D, GetUseTextureRect, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_useTextureRect() const", asMETHODPR(StretchableSprite2D, GetUseTextureRect, () const, bool), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Array<Light@>@ GetVertexLights() const", asFUNCTION(StretchableSprite2D_GetVertexLights_void), asCALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "uint GetViewMask() const", asMETHODPR(StretchableSprite2D, GetViewMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "uint get_viewMask() const", asMETHODPR(StretchableSprite2D, GetViewMask, () const, unsigned), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "const BoundingBox& GetWorldBoundingBox()", asMETHODPR(StretchableSprite2D, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "const BoundingBox& get_worldBoundingBox()", asMETHODPR(StretchableSprite2D, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Zone@+ GetZone() const", asMETHODPR(StretchableSprite2D, GetZone, () const, Zone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "Zone@+ get_zone() const", asMETHODPR(StretchableSprite2D, GetZone, () const, Zone*), asCALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "uint GetZoneMask() const", asMETHODPR(StretchableSprite2D, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "uint get_zoneMask() const", asMETHODPR(StretchableSprite2D, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool HasBasePass(uint) const", asMETHODPR(StretchableSprite2D, HasBasePass, (unsigned) const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool HasEventHandlers() const", asMETHODPR(StretchableSprite2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(StretchableSprite2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(StretchableSprite2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool IsEnabled() const", asMETHODPR(StretchableSprite2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_enabled() const", asMETHODPR(StretchableSprite2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool IsEnabledEffective() const", asMETHODPR(StretchableSprite2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_enabledEffective() const", asMETHODPR(StretchableSprite2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(StretchableSprite2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool IsInView() const", asMETHODPR(StretchableSprite2D, IsInView, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_inView() const", asMETHODPR(StretchableSprite2D, IsInView, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool IsInView(Camera@+) const", asMETHODPR(StretchableSprite2D, IsInView, (Camera*) const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool IsInView(const FrameInfo&in, bool = false) const", asMETHODPR(StretchableSprite2D, IsInView, (const FrameInfo&, bool) const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool IsOccludee() const", asMETHODPR(StretchableSprite2D, IsOccludee, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_occludee() const", asMETHODPR(StretchableSprite2D, IsOccludee, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool IsOccluder() const", asMETHODPR(StretchableSprite2D, IsOccluder, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_occluder() const", asMETHODPR(StretchableSprite2D, IsOccluder, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool IsReplicated() const", asMETHODPR(StretchableSprite2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_replicated() const", asMETHODPR(StretchableSprite2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool IsTemporary() const", asMETHODPR(StretchableSprite2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_temporary() const", asMETHODPR(StretchableSprite2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool IsZoneDirty() const", asMETHODPR(StretchableSprite2D, IsZoneDirty, () const, bool), asCALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void LimitLights()", asMETHODPR(StretchableSprite2D, LimitLights, (), void), asCALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void LimitVertexLights(bool)", asMETHODPR(StretchableSprite2D, LimitVertexLights, (bool), void), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool Load(Deserializer&)", asMETHODPR(StretchableSprite2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(StretchableSprite2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(StretchableSprite2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void MarkForUpdate()", asMETHODPR(StretchableSprite2D, MarkForUpdate, (), void), asCALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void MarkInView(const FrameInfo&in)", asMETHODPR(StretchableSprite2D, MarkInView, (const FrameInfo&), void), asCALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void MarkInView(uint)", asMETHODPR(StretchableSprite2D, MarkInView, (unsigned), void), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void MarkNetworkUpdate()", asMETHODPR(StretchableSprite2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(StretchableSprite2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(StretchableSprite2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(StretchableSprite2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Drawable2D::OnSetEnabled() override | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void OnSetEnabled()", asMETHODPR(StretchableSprite2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void PrepareNetworkUpdate()", asMETHODPR(StretchableSprite2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) | File: ../Graphics/Drawable.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(StretchableSprite2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(StretchableSprite2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("StretchableSprite2D", "int Refs() const", asMETHODPR(StretchableSprite2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "int get_refs() const", asMETHODPR(StretchableSprite2D, Refs, () const, int), asCALL_THISCALL);
    // static void StretchableSprite2D::RegisterObject(Context* context) | File: ../Urho2D/StretchableSprite2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("StretchableSprite2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(StretchableSprite2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void Remove()", asMETHODPR(StretchableSprite2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(StretchableSprite2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void RemoveInstanceDefault()", asMETHODPR(StretchableSprite2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void RemoveObjectAnimation()", asMETHODPR(StretchableSprite2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void ResetToDefault()", asMETHODPR(StretchableSprite2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool Save(Serializer&) const", asMETHODPR(StretchableSprite2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool SaveDefaultAttributes() const", asMETHODPR(StretchableSprite2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(StretchableSprite2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool SaveXML(XMLElement&) const", asMETHODPR(StretchableSprite2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SendEvent(StringHash)", asMETHODPR(StretchableSprite2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(StretchableSprite2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void StaticSprite2D::SetAlpha(float alpha) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetAlpha(float)", asMETHODPR(StretchableSprite2D, SetAlpha, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_alpha(float)", asMETHODPR(StretchableSprite2D, SetAlpha, (float), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetAnimationEnabled(bool)", asMETHODPR(StretchableSprite2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_animationEnabled(bool)", asMETHODPR(StretchableSprite2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetAnimationTime(float)", asMETHODPR(StretchableSprite2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(StretchableSprite2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(StretchableSprite2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(StretchableSprite2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(StretchableSprite2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(StretchableSprite2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(StretchableSprite2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(StretchableSprite2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetBasePass(uint)", asMETHODPR(StretchableSprite2D, SetBasePass, (unsigned), void), asCALL_THISCALL);
    // void StaticSprite2D::SetBlendMode(BlendMode blendMode) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetBlendMode(BlendMode)", asMETHODPR(StretchableSprite2D, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_blendMode(BlendMode)", asMETHODPR(StretchableSprite2D, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetBlockEvents(bool)", asMETHODPR(StretchableSprite2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void StretchableSprite2D::SetBorder(const IntRect& border) | File: ../Urho2D/StretchableSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetBorder(const IntRect&in)", asMETHODPR(StretchableSprite2D, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_border(const IntRect&in)", asMETHODPR(StretchableSprite2D, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetCastShadows(bool)", asMETHODPR(StretchableSprite2D, SetCastShadows, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_castShadows(bool)", asMETHODPR(StretchableSprite2D, SetCastShadows, (bool), void), asCALL_THISCALL);
    // void StaticSprite2D::SetColor(const Color& color) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetColor(const Color&in)", asMETHODPR(StretchableSprite2D, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_color(const Color&in)", asMETHODPR(StretchableSprite2D, SetColor, (const Color&), void), asCALL_THISCALL);
    // void StaticSprite2D::SetCustomMaterial(Material* customMaterial) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetCustomMaterial(Material@+)", asMETHODPR(StretchableSprite2D, SetCustomMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_customMaterial(Material@+)", asMETHODPR(StretchableSprite2D, SetCustomMaterial, (Material*), void), asCALL_THISCALL);
    // void StaticSprite2D::SetCustomMaterialAttr(const ResourceRef& value) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetCustomMaterialAttr(const ResourceRef&in)", asMETHODPR(StretchableSprite2D, SetCustomMaterialAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetDrawDistance(float)", asMETHODPR(StretchableSprite2D, SetDrawDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_drawDistance(float)", asMETHODPR(StretchableSprite2D, SetDrawDistance, (float), void), asCALL_THISCALL);
    // void StaticSprite2D::SetDrawRect(const Rect& rect) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetDrawRect(const Rect&in)", asMETHODPR(StretchableSprite2D, SetDrawRect, (const Rect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_drawRect(const Rect&in)", asMETHODPR(StretchableSprite2D, SetDrawRect, (const Rect&), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetEnabled(bool)", asMETHODPR(StretchableSprite2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_enabled(bool)", asMETHODPR(StretchableSprite2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void StaticSprite2D::SetFlip(bool flipX, bool flipY, bool swapXY=false) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetFlip(bool, bool, bool = false)", asMETHODPR(StretchableSprite2D, SetFlip, (bool, bool, bool), void), asCALL_THISCALL);
    // void StaticSprite2D::SetFlipX(bool flipX) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetFlipX(bool)", asMETHODPR(StretchableSprite2D, SetFlipX, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_flipX(bool)", asMETHODPR(StretchableSprite2D, SetFlipX, (bool), void), asCALL_THISCALL);
    // void StaticSprite2D::SetFlipY(bool flipY) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetFlipY(bool)", asMETHODPR(StretchableSprite2D, SetFlipY, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_flipY(bool)", asMETHODPR(StretchableSprite2D, SetFlipY, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(StretchableSprite2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(StretchableSprite2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void StaticSprite2D::SetHotSpot(const Vector2& hotspot) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetHotSpot(const Vector2&in)", asMETHODPR(StretchableSprite2D, SetHotSpot, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_hotSpot(const Vector2&in)", asMETHODPR(StretchableSprite2D, SetHotSpot, (const Vector2&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetInstanceDefault(bool)", asMETHODPR(StretchableSprite2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(StretchableSprite2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Drawable2D::SetLayer(int layer) | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetLayer(int)", asMETHODPR(StretchableSprite2D, SetLayer, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_layer(int)", asMETHODPR(StretchableSprite2D, SetLayer, (int), void), asCALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetLightMask(uint)", asMETHODPR(StretchableSprite2D, SetLightMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_lightMask(uint)", asMETHODPR(StretchableSprite2D, SetLightMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetLodBias(float)", asMETHODPR(StretchableSprite2D, SetLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_lodBias(float)", asMETHODPR(StretchableSprite2D, SetLodBias, (float), void), asCALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetMaxLights(uint)", asMETHODPR(StretchableSprite2D, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_maxLights(uint)", asMETHODPR(StretchableSprite2D, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetMinMaxZ(float, float)", asMETHODPR(StretchableSprite2D, SetMinMaxZ, (float, float), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(StretchableSprite2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(StretchableSprite2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(StretchableSprite2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetOccludee(bool)", asMETHODPR(StretchableSprite2D, SetOccludee, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_occludee(bool)", asMETHODPR(StretchableSprite2D, SetOccludee, (bool), void), asCALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetOccluder(bool)", asMETHODPR(StretchableSprite2D, SetOccluder, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_occluder(bool)", asMETHODPR(StretchableSprite2D, SetOccluder, (bool), void), asCALL_THISCALL);
    // void Drawable2D::SetOrderInLayer(int orderInLayer) | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetOrderInLayer(int)", asMETHODPR(StretchableSprite2D, SetOrderInLayer, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_orderInLayer(int)", asMETHODPR(StretchableSprite2D, SetOrderInLayer, (int), void), asCALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetShadowDistance(float)", asMETHODPR(StretchableSprite2D, SetShadowDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_shadowDistance(float)", asMETHODPR(StretchableSprite2D, SetShadowDistance, (float), void), asCALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetShadowMask(uint)", asMETHODPR(StretchableSprite2D, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_shadowMask(uint)", asMETHODPR(StretchableSprite2D, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetSortValue(float)", asMETHODPR(StretchableSprite2D, SetSortValue, (float), void), asCALL_THISCALL);
    // void StaticSprite2D::SetSprite(Sprite2D* sprite) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetSprite(Sprite2D@+)", asMETHODPR(StretchableSprite2D, SetSprite, (Sprite2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_sprite(Sprite2D@+)", asMETHODPR(StretchableSprite2D, SetSprite, (Sprite2D*), void), asCALL_THISCALL);
    // void StaticSprite2D::SetSpriteAttr(const ResourceRef& value) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetSpriteAttr(const ResourceRef&in)", asMETHODPR(StretchableSprite2D, SetSpriteAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void StaticSprite2D::SetSwapXY(bool swapXY) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetSwapXY(bool)", asMETHODPR(StretchableSprite2D, SetSwapXY, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_swapXY(bool)", asMETHODPR(StretchableSprite2D, SetSwapXY, (bool), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetTemporary(bool)", asMETHODPR(StretchableSprite2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_temporary(bool)", asMETHODPR(StretchableSprite2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void StaticSprite2D::SetTextureRect(const Rect& rect) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetTextureRect(const Rect&in)", asMETHODPR(StretchableSprite2D, SetTextureRect, (const Rect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_textureRect(const Rect&in)", asMETHODPR(StretchableSprite2D, SetTextureRect, (const Rect&), void), asCALL_THISCALL);
    // void StaticSprite2D::SetUseDrawRect(bool useDrawRect) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetUseDrawRect(bool)", asMETHODPR(StretchableSprite2D, SetUseDrawRect, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_useDrawRect(bool)", asMETHODPR(StretchableSprite2D, SetUseDrawRect, (bool), void), asCALL_THISCALL);
    // void StaticSprite2D::SetUseHotSpot(bool useHotSpot) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetUseHotSpot(bool)", asMETHODPR(StretchableSprite2D, SetUseHotSpot, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_useHotSpot(bool)", asMETHODPR(StretchableSprite2D, SetUseHotSpot, (bool), void), asCALL_THISCALL);
    // void StaticSprite2D::SetUseTextureRect(bool useTextureRect) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetUseTextureRect(bool)", asMETHODPR(StretchableSprite2D, SetUseTextureRect, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_useTextureRect(bool)", asMETHODPR(StretchableSprite2D, SetUseTextureRect, (bool), void), asCALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetViewMask(uint)", asMETHODPR(StretchableSprite2D, SetViewMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_viewMask(uint)", asMETHODPR(StretchableSprite2D, SetViewMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetZone(Zone@+, bool = false)", asMETHODPR(StretchableSprite2D, SetZone, (Zone*, bool), void), asCALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetZoneMask(uint)", asMETHODPR(StretchableSprite2D, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_zoneMask(uint)", asMETHODPR(StretchableSprite2D, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    // explicit StretchableSprite2D::StretchableSprite2D(Context* context) | File: ../Urho2D/StretchableSprite2D.h
    engine->RegisterObjectBehaviour("StretchableSprite2D", asBEHAVE_FACTORY, "StretchableSprite2D@+ f()", asFUNCTION(StretchableSprite2D_StretchableSprite2D_Context), asCALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void UnsubscribeFromAllEvents()", asMETHODPR(StretchableSprite2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(StretchableSprite2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(StretchableSprite2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(StretchableSprite2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(StretchableSprite2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void Update(const FrameInfo&in)", asMETHODPR(StretchableSprite2D, Update, (const FrameInfo&), void), asCALL_THISCALL);
    // virtual void Drawable::UpdateBatches(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void UpdateBatches(const FrameInfo&in)", asMETHODPR(StretchableSprite2D, UpdateBatches, (const FrameInfo&), void), asCALL_THISCALL);
    // virtual void Drawable::UpdateGeometry(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void UpdateGeometry(const FrameInfo&in)", asMETHODPR(StretchableSprite2D, UpdateGeometry, (const FrameInfo&), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("StretchableSprite2D", "int WeakRefs() const", asMETHODPR(StretchableSprite2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "int get_weakRefs() const", asMETHODPR(StretchableSprite2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(StretchableSprite2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(StretchableSprite2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(StretchableSprite2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_StaticSprite2D
    REGISTER_MANUAL_PART_StaticSprite2D(StretchableSprite2D, "StretchableSprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_Drawable2D
    REGISTER_MANUAL_PART_Drawable2D(StretchableSprite2D, "StretchableSprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_Drawable
    REGISTER_MANUAL_PART_Drawable(StretchableSprite2D, "StretchableSprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(StretchableSprite2D, "StretchableSprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(StretchableSprite2D, "StretchableSprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(StretchableSprite2D, "StretchableSprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(StretchableSprite2D, "StretchableSprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(StretchableSprite2D, "StretchableSprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_StretchableSprite2D
    REGISTER_MANUAL_PART_StretchableSprite2D(StretchableSprite2D, "StretchableSprite2D")
#endif
    RegisterSubclass<StaticSprite2D, StretchableSprite2D>(engine, "StaticSprite2D", "StretchableSprite2D");
    RegisterSubclass<Drawable2D, StretchableSprite2D>(engine, "Drawable2D", "StretchableSprite2D");
    RegisterSubclass<Drawable, StretchableSprite2D>(engine, "Drawable", "StretchableSprite2D");
    RegisterSubclass<Component, StretchableSprite2D>(engine, "Component", "StretchableSprite2D");
    RegisterSubclass<Animatable, StretchableSprite2D>(engine, "Animatable", "StretchableSprite2D");
    RegisterSubclass<Serializable, StretchableSprite2D>(engine, "Serializable", "StretchableSprite2D");
    RegisterSubclass<Object, StretchableSprite2D>(engine, "Object", "StretchableSprite2D");
    RegisterSubclass<RefCounted, StretchableSprite2D>(engine, "RefCounted", "StretchableSprite2D");
#endif

    // const String String::EMPTY | File: ../Container/Str.h
    engine->SetDefaultNamespace("String");
    engine->RegisterGlobalProperty("const String EMPTY", (void*)&String::EMPTY);
    engine->SetDefaultNamespace("");
    // const unsigned String::MIN_CAPACITY | File: ../Container/Str.h
    engine->SetDefaultNamespace("String");
    engine->RegisterGlobalProperty("const uint MIN_CAPACITY", (void*)&String::MIN_CAPACITY);
    engine->SetDefaultNamespace("");
    // const unsigned String::NPOS | File: ../Container/Str.h
    engine->SetDefaultNamespace("String");
    engine->RegisterGlobalProperty("const uint NPOS", (void*)&String::NPOS);
    engine->SetDefaultNamespace("");
    // String& String::Append(const String& str) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& Append(const String&in)", asMETHODPR(String, Append, (const String&), String&), asCALL_THISCALL);
    // String& String::Append(const char* str) | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // String& String::Append(char c) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& Append(int8)", asMETHODPR(String, Append, (char), String&), asCALL_THISCALL);
    // String& String::Append(const char* str, unsigned length) | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // String& String::AppendUTF8(unsigned unicodeChar) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& AppendUTF8(uint)", asMETHODPR(String, AppendUTF8, (unsigned), String&), asCALL_THISCALL);
    // String& String::AppendWithFormat(const char* formatString,...) | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // String& String::AppendWithFormatArgs(const char* formatString, va_list args) | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // char& String::At(unsigned index) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "int8& At(uint)", asMETHODPR(String, At, (unsigned), char&), asCALL_THISCALL);
    // const char& String::At(unsigned index) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "const int8& At(uint) const", asMETHODPR(String, At, (unsigned) const, const char&), asCALL_THISCALL);
    // unsigned String::AtUTF8(unsigned index) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "uint AtUTF8(uint) const", asMETHODPR(String, AtUTF8, (unsigned) const, unsigned), asCALL_THISCALL);
    // char String::Back() const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "int8 Back() const", asMETHODPR(String, Back, () const, char), asCALL_THISCALL);
    // Iterator String::Begin() | File: ../Container/Str.h
    // Error: type "Iterator" can not automatically bind
    // ConstIterator String::Begin() const | File: ../Container/Str.h
    // Error: type "ConstIterator" can not automatically bind
    // unsigned String::ByteOffsetUTF8(unsigned index) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "uint ByteOffsetUTF8(uint) const", asMETHODPR(String, ByteOffsetUTF8, (unsigned) const, unsigned), asCALL_THISCALL);
    // unsigned String::Capacity() const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "uint Capacity() const", asMETHODPR(String, Capacity, () const, unsigned), asCALL_THISCALL);
    // void String::Clear() | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void Clear()", asMETHODPR(String, Clear, (), void), asCALL_THISCALL);
    // void String::Compact() | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void Compact()", asMETHODPR(String, Compact, (), void), asCALL_THISCALL);
    // int String::Compare(const String& str, bool caseSensitive=true) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "int Compare(const String&in, bool = true) const", asMETHODPR(String, Compare, (const String&, bool) const, int), asCALL_THISCALL);
    // int String::Compare(const char* str, bool caseSensitive=true) const | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // static int String::Compare(const char* lhs, const char* rhs, bool caseSensitive) | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // bool String::Contains(const String& str, bool caseSensitive=true) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "bool Contains(const String&in, bool = true) const", asMETHODPR(String, Contains, (const String&, bool) const, bool), asCALL_THISCALL);
    // bool String::Contains(char c, bool caseSensitive=true) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "bool Contains(int8, bool = true) const", asMETHODPR(String, Contains, (char, bool) const, bool), asCALL_THISCALL);
    // const char* String::CString() const | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // static unsigned String::CStringLength(const char* str) | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // static unsigned String::DecodeUTF8(const char*& src) | File: ../Container/Str.h
    // Error: type "const char*&" can not automatically bind
    // bool String::Empty() const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "bool Empty() const", asMETHODPR(String, Empty, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "bool get_empty() const", asMETHODPR(String, Empty, () const, bool), asCALL_THISCALL);
    // static void String::EncodeUTF8(char*& dest, unsigned unicodeChar) | File: ../Container/Str.h
    // Error: type "char*&" can not automatically bind
    // Iterator String::End() | File: ../Container/Str.h
    // Error: type "Iterator" can not automatically bind
    // ConstIterator String::End() const | File: ../Container/Str.h
    // Error: type "ConstIterator" can not automatically bind
    // bool String::EndsWith(const String& str, bool caseSensitive=true) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "bool EndsWith(const String&in, bool = true) const", asMETHODPR(String, EndsWith, (const String&, bool) const, bool), asCALL_THISCALL);
    // void String::Erase(unsigned pos, unsigned length=1) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void Erase(uint, uint = 1)", asMETHODPR(String, Erase, (unsigned, unsigned), void), asCALL_THISCALL);
    // Iterator String::Erase(const Iterator& it) | File: ../Container/Str.h
    // Error: type "const Iterator&" can not automatically bind
    // Iterator String::Erase(const Iterator& start, const Iterator& end) | File: ../Container/Str.h
    // Error: type "const Iterator&" can not automatically bind
    // unsigned String::Find(const String& str, unsigned startPos=0, bool caseSensitive=true) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "uint Find(const String&in, uint = 0, bool = true) const", asMETHODPR(String, Find, (const String&, unsigned, bool) const, unsigned), asCALL_THISCALL);
    // unsigned String::Find(char c, unsigned startPos=0, bool caseSensitive=true) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "uint Find(int8, uint = 0, bool = true) const", asMETHODPR(String, Find, (char, unsigned, bool) const, unsigned), asCALL_THISCALL);
    // unsigned String::FindLast(const String& str, unsigned startPos=NPOS, bool caseSensitive=true) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "uint FindLast(const String&in, uint = String::NPOS, bool = true) const", asMETHODPR(String, FindLast, (const String&, unsigned, bool) const, unsigned), asCALL_THISCALL);
    // unsigned String::FindLast(char c, unsigned startPos=NPOS, bool caseSensitive=true) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "uint FindLast(int8, uint = String::NPOS, bool = true) const", asMETHODPR(String, FindLast, (char, unsigned, bool) const, unsigned), asCALL_THISCALL);
    // char String::Front() const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "int8 Front() const", asMETHODPR(String, Front, () const, char), asCALL_THISCALL);
    // void String::Insert(unsigned pos, const String& str) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void Insert(uint, const String&in)", asMETHODPR(String, Insert, (unsigned, const String&), void), asCALL_THISCALL);
    // void String::Insert(unsigned pos, char c) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void Insert(uint, int8)", asMETHODPR(String, Insert, (unsigned, char), void), asCALL_THISCALL);
    // Iterator String::Insert(const Iterator& dest, const String& str) | File: ../Container/Str.h
    // Error: type "const Iterator&" can not automatically bind
    // Iterator String::Insert(const Iterator& dest, const Iterator& start, const Iterator& end) | File: ../Container/Str.h
    // Error: type "const Iterator&" can not automatically bind
    // Iterator String::Insert(const Iterator& dest, char c) | File: ../Container/Str.h
    // Error: type "const Iterator&" can not automatically bind
    // void String::Join(const Vector<String>& subStrings, const String& glue) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void Join(Array<String>@+, const String&in)", asFUNCTION(String_Join_VectorString_String), asCALL_CDECL_OBJFIRST);
    // static String String::Joined(const Vector<String>& subStrings, const String& glue) | File: ../Container/Str.h
    // Not registered because have @manualbind mark
    // unsigned String::Length() const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "uint Length() const", asMETHODPR(String, Length, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "uint get_length() const", asMETHODPR(String, Length, () const, unsigned), asCALL_THISCALL);
    // unsigned String::LengthUTF8() const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "uint LengthUTF8() const", asMETHODPR(String, LengthUTF8, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "uint get_utf8Length() const", asMETHODPR(String, LengthUTF8, () const, unsigned), asCALL_THISCALL);
    // unsigned String::NextUTF8Char(unsigned& byteOffset) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "uint NextUTF8Char(uint&) const", asMETHODPR(String, NextUTF8Char, (unsigned&) const, unsigned), asCALL_THISCALL);
    // String String::operator+(const String& rhs) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String opAdd(const String&in) const", asMETHODPR(String, operator+, (const String&) const, String), asCALL_THISCALL);
    // String String::operator+(const char* rhs) const | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // String& String::operator+=(const String& rhs) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& opAddAssign(const String&in)", asMETHODPR(String, operator+=, (const String&), String&), asCALL_THISCALL);
    // String& String::operator+=(const char* rhs) | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // String& String::operator+=(char rhs) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& opAddAssign(int8)", asMETHODPR(String, operator+=, (char), String&), asCALL_THISCALL);
    // String& String::operator+=(int rhs) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& opAddAssign(int)", asMETHODPR(String, operator+=, (int), String&), asCALL_THISCALL);
    // String& String::operator+=(short rhs) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& opAddAssign(int16)", asMETHODPR(String, operator+=, (short), String&), asCALL_THISCALL);
    // String& String::operator+=(long rhs) | File: ../Container/Str.h
    // Not registered because have @nobind mark
    // String& String::operator+=(long long rhs) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& opAddAssign(int64)", asMETHODPR(String, operator+=, (long long), String&), asCALL_THISCALL);
    // String& String::operator+=(unsigned rhs) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& opAddAssign(uint)", asMETHODPR(String, operator+=, (unsigned), String&), asCALL_THISCALL);
    // String& String::operator+=(unsigned short rhs) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& opAddAssign(uint16)", asMETHODPR(String, operator+=, (unsigned short), String&), asCALL_THISCALL);
    // String& String::operator+=(unsigned long rhs) | File: ../Container/Str.h
    // Not registered because have @nobind mark
    // String& String::operator+=(unsigned long long rhs) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& opAddAssign(uint64)", asMETHODPR(String, operator+=, (unsigned long long), String&), asCALL_THISCALL);
    // String& String::operator+=(float rhs) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& opAddAssign(float)", asMETHODPR(String, operator+=, (float), String&), asCALL_THISCALL);
    // String& String::operator+=(bool rhs) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& opAddAssign(bool)", asMETHODPR(String, operator+=, (bool), String&), asCALL_THISCALL);
    // template<class T> String& String::operator+=(const T& rhs) | File: ../Container/Str.h
    // Not registered because template
    // String& String::operator=(const String& rhs) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& opAssign(const String&in)", asMETHODPR(String, operator=, (const String&), String&), asCALL_THISCALL);
    // String& String::operator=(String&& rhs) noexcept | File: ../Container/Str.h
    // Error: type "String&&" can not automatically bind
    // String& String::operator=(const char* rhs) | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // bool String::operator==(const String& rhs) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "bool opEquals(const String&in) const", asMETHODPR(String, operator==, (const String&) const, bool), asCALL_THISCALL);
    // bool String::operator==(const char* rhs) const | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // char& String::operator[](unsigned index) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "int8& opIndex(uint)", asMETHODPR(String, operator[], (unsigned), char&), asCALL_THISCALL);
    // const char& String::operator[](unsigned index) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "const int8& opIndex(uint) const", asMETHODPR(String, operator[], (unsigned) const, const char&), asCALL_THISCALL);
    // void String::Replace(char replaceThis, char replaceWith, bool caseSensitive=true) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void Replace(int8, int8, bool = true)", asMETHODPR(String, Replace, (char, char, bool), void), asCALL_THISCALL);
    // void String::Replace(const String& replaceThis, const String& replaceWith, bool caseSensitive=true) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void Replace(const String&in, const String&in, bool = true)", asMETHODPR(String, Replace, (const String&, const String&, bool), void), asCALL_THISCALL);
    // void String::Replace(unsigned pos, unsigned length, const String& replaceWith) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void Replace(uint, uint, const String&in)", asMETHODPR(String, Replace, (unsigned, unsigned, const String&), void), asCALL_THISCALL);
    // void String::Replace(unsigned pos, unsigned length, const char* replaceWith) | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // Iterator String::Replace(const Iterator& start, const Iterator& end, const String& replaceWith) | File: ../Container/Str.h
    // Error: type "const Iterator&" can not automatically bind
    // String String::Replaced(char replaceThis, char replaceWith, bool caseSensitive=true) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String Replaced(int8, int8, bool = true) const", asMETHODPR(String, Replaced, (char, char, bool) const, String), asCALL_THISCALL);
    // String String::Replaced(const String& replaceThis, const String& replaceWith, bool caseSensitive=true) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String Replaced(const String&in, const String&in, bool = true) const", asMETHODPR(String, Replaced, (const String&, const String&, bool) const, String), asCALL_THISCALL);
    // void String::ReplaceUTF8(unsigned index, unsigned unicodeChar) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void ReplaceUTF8(uint, uint)", asMETHODPR(String, ReplaceUTF8, (unsigned, unsigned), void), asCALL_THISCALL);
    // void String::Reserve(unsigned newCapacity) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void Reserve(uint)", asMETHODPR(String, Reserve, (unsigned), void), asCALL_THISCALL);
    // void String::Resize(unsigned newLength) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void Resize(uint)", asMETHODPR(String, Resize, (unsigned), void), asCALL_THISCALL);
    // void String::SetUTF8FromLatin1(const char* str) | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // void String::SetUTF8FromWChar(const wchar_t* str) | File: ../Container/Str.h
    // Error: type "const wchar_t*" can not automatically bind
    // Vector<String> String::Split(char separator, bool keepEmptyStrings=false) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "Array<String>@ Split(int8, bool = false) const", asFUNCTION(String_Split_char_bool), asCALL_CDECL_OBJFIRST);
    // static Vector<String> String::Split(const char* str, char separator, bool keepEmptyStrings=false) | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // bool String::StartsWith(const String& str, bool caseSensitive=true) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "bool StartsWith(const String&in, bool = true) const", asMETHODPR(String, StartsWith, (const String&, bool) const, bool), asCALL_THISCALL);
    // String::String(const String& str) | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(const String&in)", asFUNCTION(String_String_String), asCALL_CDECL_OBJFIRST);
    // String::String(String&& str) noexcept | File: ../Container/Str.h
    // Error: type "String&&" can not automatically bind
    // String::String(const char* str) | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // String::String(char* str) | File: ../Container/Str.h
    // Error: type "char*" can not automatically bind
    // String::String(const char* str, unsigned length) | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // explicit String::String(const wchar_t* str) | File: ../Container/Str.h
    // Error: type "const wchar_t*" can not automatically bind
    // explicit String::String(wchar_t* str) | File: ../Container/Str.h
    // Error: type "wchar_t*" can not automatically bind
    // explicit String::String(const WString& str) | File: ../Container/Str.h
    // Error: type "WString" can not automatically bind bacause have @nobind mark
    // explicit String::String(int value) | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(int)", asFUNCTION(String_String_int), asCALL_CDECL_OBJFIRST);
    // explicit String::String(short value) | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(int16)", asFUNCTION(String_String_short), asCALL_CDECL_OBJFIRST);
    // explicit String::String(long value) | File: ../Container/Str.h
    // Not registered because have @nobind mark
    // explicit String::String(long long value) | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(int64)", asFUNCTION(String_String_longlong), asCALL_CDECL_OBJFIRST);
    // explicit String::String(unsigned value) | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(uint)", asFUNCTION(String_String_unsigned), asCALL_CDECL_OBJFIRST);
    // explicit String::String(unsigned short value) | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(uint16)", asFUNCTION(String_String_unsignedshort), asCALL_CDECL_OBJFIRST);
    // explicit String::String(unsigned long value) | File: ../Container/Str.h
    // Not registered because have @nobind mark
    // explicit String::String(unsigned long long value) | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(uint64)", asFUNCTION(String_String_unsignedlonglong), asCALL_CDECL_OBJFIRST);
    // explicit String::String(float value) | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(float)", asFUNCTION(String_String_float), asCALL_CDECL_OBJFIRST);
    // explicit String::String(double value) | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(double)", asFUNCTION(String_String_double), asCALL_CDECL_OBJFIRST);
    // explicit String::String(bool value) | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(bool)", asFUNCTION(String_String_bool), asCALL_CDECL_OBJFIRST);
    // explicit String::String(char value) | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(int8)", asFUNCTION(String_String_char), asCALL_CDECL_OBJFIRST);
    // explicit String::String(char value, unsigned length) | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(int8, uint)", asFUNCTION(String_String_char_unsigned), asCALL_CDECL_OBJFIRST);
    // template<class T> explicit String::String(const T& value) | File: ../Container/Str.h
    // Not registered because template
    // String String::Substring(unsigned pos) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String Substring(uint) const", asMETHODPR(String, Substring, (unsigned) const, String), asCALL_THISCALL);
    // String String::Substring(unsigned pos, unsigned length) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String Substring(uint, uint) const", asMETHODPR(String, Substring, (unsigned, unsigned) const, String), asCALL_THISCALL);
    // String String::SubstringUTF8(unsigned pos) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String SubstringUTF8(uint) const", asMETHODPR(String, SubstringUTF8, (unsigned) const, String), asCALL_THISCALL);
    // String String::SubstringUTF8(unsigned pos, unsigned length) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String SubstringUTF8(uint, uint) const", asMETHODPR(String, SubstringUTF8, (unsigned, unsigned) const, String), asCALL_THISCALL);
    // void String::Swap(String& str) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void Swap(String&)", asMETHODPR(String, Swap, (String&), void), asCALL_THISCALL);
    // unsigned String::ToHash() const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "uint ToHash() const", asMETHODPR(String, ToHash, () const, unsigned), asCALL_THISCALL);
    // String String::ToLower() const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String ToLower() const", asMETHODPR(String, ToLower, () const, String), asCALL_THISCALL);
    // String String::ToUpper() const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String ToUpper() const", asMETHODPR(String, ToUpper, () const, String), asCALL_THISCALL);
    // String String::Trimmed() const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String Trimmed() const", asMETHODPR(String, Trimmed, () const, String), asCALL_THISCALL);
    // bool String::operator<(const String& rhs) const | File: ../Container/Str.h
    // bool String::operator>(const String& rhs) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "int opCmp(const String&in) const", asFUNCTION(String_Comparison), asCALL_CDECL_OBJFIRST);
#ifdef REGISTER_MANUAL_PART_String
    REGISTER_MANUAL_PART_String(String, "String")
#endif

    // const StringHash StringHash::ZERO | File: ../Math/StringHash.h
    engine->SetDefaultNamespace("StringHash");
    engine->RegisterGlobalProperty("const StringHash ZERO", (void*)&StringHash::ZERO);
    engine->SetDefaultNamespace("");
    // static unsigned StringHash::Calculate(const char* str, unsigned hash=0) | File: ../Math/StringHash.h
    // Error: type "const char*" can not automatically bind
    // static StringHashRegister* StringHash::GetGlobalStringHashRegister() | File: ../Math/StringHash.h
    // Error: type "StringHashRegister*" can not automatically bind
    // explicit StringHash::operator bool() const | File: ../Math/StringHash.h
    engine->RegisterObjectMethod("StringHash", "bool opConv() const", asMETHODPR(StringHash, operator bool, () const, bool), asCALL_THISCALL);
    // StringHash StringHash::operator+(const StringHash& rhs) const | File: ../Math/StringHash.h
    engine->RegisterObjectMethod("StringHash", "StringHash opAdd(const StringHash&in) const", asMETHODPR(StringHash, operator+, (const StringHash&) const, StringHash), asCALL_THISCALL);
    // StringHash& StringHash::operator+=(const StringHash& rhs) | File: ../Math/StringHash.h
    engine->RegisterObjectMethod("StringHash", "StringHash& opAddAssign(const StringHash&in)", asMETHODPR(StringHash, operator+=, (const StringHash&), StringHash&), asCALL_THISCALL);
    // StringHash& StringHash::operator=(const StringHash& rhs) noexcept=default | File: ../Math/StringHash.h
    engine->RegisterObjectMethod("StringHash", "StringHash& opAssign(const StringHash&in)", asMETHODPR(StringHash, operator=, (const StringHash&), StringHash&), asCALL_THISCALL);
    // bool StringHash::operator==(const StringHash& rhs) const | File: ../Math/StringHash.h
    engine->RegisterObjectMethod("StringHash", "bool opEquals(const StringHash&in) const", asMETHODPR(StringHash, operator==, (const StringHash&) const, bool), asCALL_THISCALL);
    // String StringHash::Reverse() const | File: ../Math/StringHash.h
    engine->RegisterObjectMethod("StringHash", "String Reverse() const", asMETHODPR(StringHash, Reverse, () const, String), asCALL_THISCALL);
    // StringHash::StringHash(const StringHash& rhs) noexcept=default | File: ../Math/StringHash.h
    engine->RegisterObjectBehaviour("StringHash", asBEHAVE_CONSTRUCT, "void f(const StringHash&in)", asFUNCTION(StringHash_StringHash_StringHash), asCALL_CDECL_OBJFIRST);
    // explicit StringHash::StringHash(unsigned value) noexcept | File: ../Math/StringHash.h
    engine->RegisterObjectBehaviour("StringHash", asBEHAVE_CONSTRUCT, "void f(uint)", asFUNCTION(StringHash_StringHash_unsigned), asCALL_CDECL_OBJFIRST);
    // StringHash::StringHash(const char* str) noexcept | File: ../Math/StringHash.h
    // Error: type "const char*" can not automatically bind
    // StringHash::StringHash(const String& str) noexcept | File: ../Math/StringHash.h
    engine->RegisterObjectBehaviour("StringHash", asBEHAVE_CONSTRUCT, "void f(const String&in)", asFUNCTION(StringHash_StringHash_String), asCALL_CDECL_OBJFIRST);
    // unsigned StringHash::ToHash() const | File: ../Math/StringHash.h
    engine->RegisterObjectMethod("StringHash", "uint ToHash() const", asMETHODPR(StringHash, ToHash, () const, unsigned), asCALL_THISCALL);
    // String StringHash::ToString() const | File: ../Math/StringHash.h
    engine->RegisterObjectMethod("StringHash", "String ToString() const", asMETHODPR(StringHash, ToString, () const, String), asCALL_THISCALL);
    // unsigned StringHash::Value() const | File: ../Math/StringHash.h
    engine->RegisterObjectMethod("StringHash", "uint Value() const", asMETHODPR(StringHash, Value, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("StringHash", "uint get_value() const", asMETHODPR(StringHash, Value, () const, unsigned), asCALL_THISCALL);
    // bool StringHash::operator<(const StringHash& rhs) const | File: ../Math/StringHash.h
    // bool StringHash::operator>(const StringHash& rhs) const | File: ../Math/StringHash.h
    engine->RegisterObjectMethod("StringHash", "int opCmp(const StringHash&in) const", asFUNCTION(StringHash_Comparison), asCALL_CDECL_OBJFIRST);
#ifdef REGISTER_MANUAL_PART_StringHash
    REGISTER_MANUAL_PART_StringHash(StringHash, "StringHash")
#endif

    // bool StringHashRegister::Contains(const StringHash& hash) const | File: ../Core/StringHashRegister.h
    engine->RegisterObjectMethod("StringHashRegister", "bool Contains(const StringHash&in) const", asMETHODPR(StringHashRegister, Contains, (const StringHash&) const, bool), asCALL_THISCALL);
    // const StringMap& StringHashRegister::GetInternalMap() const | File: ../Core/StringHashRegister.h
    // Error: type "const StringMap&" can not automatically bind
    // const String& StringHashRegister::GetString(const StringHash& hash) const | File: ../Core/StringHashRegister.h
    engine->RegisterObjectMethod("StringHashRegister", "const String& GetString(const StringHash&in) const", asMETHODPR(StringHashRegister, GetString, (const StringHash&) const, const String&), asCALL_THISCALL);
    // String StringHashRegister::GetStringCopy(const StringHash& hash) const | File: ../Core/StringHashRegister.h
    engine->RegisterObjectMethod("StringHashRegister", "String GetStringCopy(const StringHash&in) const", asMETHODPR(StringHashRegister, GetStringCopy, (const StringHash&) const, String), asCALL_THISCALL);
    // StringHash StringHashRegister::RegisterString(const StringHash& hash, const char* string) | File: ../Core/StringHashRegister.h
    // Error: type "const char*" can not automatically bind
    // StringHash StringHashRegister::RegisterString(const char* string) | File: ../Core/StringHashRegister.h
    // Error: type "const char*" can not automatically bind
    // StringHashRegister::StringHashRegister(bool threadSafe) | File: ../Core/StringHashRegister.h
    engine->RegisterObjectBehaviour("StringHashRegister", asBEHAVE_CONSTRUCT, "void f(bool)", asFUNCTION(StringHashRegister_StringHashRegister_bool), asCALL_CDECL_OBJFIRST);
    // StringHashRegister& StringHashRegister::operator=(const StringHashRegister&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<StringHashRegister>(engine, "StringHashRegister");
#ifdef REGISTER_MANUAL_PART_StringHashRegister
    REGISTER_MANUAL_PART_StringHashRegister(StringHashRegister, "StringHashRegister")
#endif

    // float SourceBatch::distance_ | File: ../Graphics/Drawable.h
    engine->RegisterObjectProperty("SourceBatch", "float distance", offsetof(SourceBatch, distance_));
    // Geometry* SourceBatch::geometry_ | File: ../Graphics/Drawable.h
    // Geometry* can not be registered
    // GeometryType SourceBatch::geometryType_ | File: ../Graphics/Drawable.h
    engine->RegisterObjectProperty("SourceBatch", "GeometryType geometryType", offsetof(SourceBatch, geometryType_));
    // void* SourceBatch::instancingData_ | File: ../Graphics/Drawable.h
    // void* can not be registered
    // SharedPtr<Material> SourceBatch::material_ | File: ../Graphics/Drawable.h
    // Error: type "SharedPtr<Material>" can not automatically bind
    // unsigned SourceBatch::numWorldTransforms_ | File: ../Graphics/Drawable.h
    engine->RegisterObjectProperty("SourceBatch", "uint numWorldTransforms", offsetof(SourceBatch, numWorldTransforms_));
    // const Matrix3x4* SourceBatch::worldTransform_ | File: ../Graphics/Drawable.h
    // const Matrix3x4* can not be registered
    // SourceBatch& SourceBatch::operator=(const SourceBatch& rhs) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("SourceBatch", "SourceBatch& opAssign(const SourceBatch&in)", asMETHODPR(SourceBatch, operator=, (const SourceBatch&), SourceBatch&), asCALL_THISCALL);
    // SourceBatch::SourceBatch(const SourceBatch& batch) | File: ../Graphics/Drawable.h
    engine->RegisterObjectBehaviour("SourceBatch", asBEHAVE_CONSTRUCT, "void f(const SourceBatch&in)", asFUNCTION(SourceBatch_SourceBatch_SourceBatch), asCALL_CDECL_OBJFIRST);
#ifdef REGISTER_MANUAL_PART_SourceBatch
    REGISTER_MANUAL_PART_SourceBatch(SourceBatch, "SourceBatch")
#endif

#ifdef URHO3D_URHO2D
    // float SourceBatch2D::distance_ | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectProperty("SourceBatch2D", "float distance", offsetof(SourceBatch2D, distance_));
    // int SourceBatch2D::drawOrder_ | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectProperty("SourceBatch2D", "int drawOrder", offsetof(SourceBatch2D, drawOrder_));
    // SharedPtr<Material> SourceBatch2D::material_ | File: ../Urho2D/Drawable2D.h
    // Error: type "SharedPtr<Material>" can not automatically bind
    // WeakPtr<Drawable2D> SourceBatch2D::owner_ | File: ../Urho2D/Drawable2D.h
    // Error: type "WeakPtr<Drawable2D>" can not automatically bind
    // Vector<Vertex2D> SourceBatch2D::vertices_ | File: ../Urho2D/Drawable2D.h
    // Error: type "Vector<Vertex2D>" can not automatically bind
    // SourceBatch2D& SourceBatch2D::operator=(const SourceBatch2D&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<SourceBatch2D>(engine, "SourceBatch2D");
#ifdef REGISTER_MANUAL_PART_SourceBatch2D
    REGISTER_MANUAL_PART_SourceBatch2D(SourceBatch2D, "SourceBatch2D")
#endif
#endif

    // Vector3 StaticModelGeometryData::center_ | File: ../Graphics/StaticModel.h
    engine->RegisterObjectProperty("StaticModelGeometryData", "Vector3 center", offsetof(StaticModelGeometryData, center_));
    // unsigned StaticModelGeometryData::lodLevel_ | File: ../Graphics/StaticModel.h
    engine->RegisterObjectProperty("StaticModelGeometryData", "uint lodLevel", offsetof(StaticModelGeometryData, lodLevel_));
    // StaticModelGeometryData& StaticModelGeometryData::operator=(const StaticModelGeometryData&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<StaticModelGeometryData>(engine, "StaticModelGeometryData");
#ifdef REGISTER_MANUAL_PART_StaticModelGeometryData
    REGISTER_MANUAL_PART_StaticModelGeometryData(StaticModelGeometryData, "StaticModelGeometryData")
#endif

    // bool StoredLogMessage::error_ | File: ../IO/Log.h
    engine->RegisterObjectProperty("StoredLogMessage", "bool error", offsetof(StoredLogMessage, error_));
    // int StoredLogMessage::level_ | File: ../IO/Log.h
    engine->RegisterObjectProperty("StoredLogMessage", "int level", offsetof(StoredLogMessage, level_));
    // String StoredLogMessage::message_ | File: ../IO/Log.h
    engine->RegisterObjectProperty("StoredLogMessage", "String message", offsetof(StoredLogMessage, message_));
    // StoredLogMessage::StoredLogMessage(const String& message, int level, bool error) | File: ../IO/Log.h
    engine->RegisterObjectBehaviour("StoredLogMessage", asBEHAVE_CONSTRUCT, "void f(const String&in, int, bool)", asFUNCTION(StoredLogMessage_StoredLogMessage_String_int_bool), asCALL_CDECL_OBJFIRST);
    // StoredLogMessage& StoredLogMessage::operator=(const StoredLogMessage&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<StoredLogMessage>(engine, "StoredLogMessage");
#ifdef REGISTER_MANUAL_PART_StoredLogMessage
    REGISTER_MANUAL_PART_StoredLogMessage(StoredLogMessage, "StoredLogMessage")
#endif

}

}
