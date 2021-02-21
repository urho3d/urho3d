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
    engine->RegisterObjectMethod("Sound", "void AddMetadata(const String&in, const Variant&in)", AS_METHODPR(Sound, AddMetadata, (const String&, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "void set_metadata(const String&in, const Variant&in)", AS_METHODPR(Sound, AddMetadata, (const String&, const Variant&), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Sound", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Sound, AddRef, (), void), AS_CALL_THISCALL);
    // bool Sound::BeginLoad(Deserializer& source) override | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "bool BeginLoad(Deserializer&)", AS_METHODPR(Sound, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "bool EndLoad()", AS_METHODPR(Sound, EndLoad, (), bool), AS_CALL_THISCALL);
    // void Sound::FixInterpolation() | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "void FixInterpolation()", AS_METHODPR(Sound, FixInterpolation, (), void), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(Sound, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "bool GetBlockEvents() const", AS_METHODPR(Sound, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "const String& GetCategory() const", AS_METHODPR(Sound, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "const String& get_category() const", AS_METHODPR(Sound, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // SharedArrayPtr<signed char> Sound::GetData() const | File: ../Audio/Sound.h
    // Error: type "SharedArrayPtr<signed char>" can not automatically bind
    // unsigned Sound::GetDataSize() const | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "uint GetDataSize() const", AS_METHODPR(Sound, GetDataSize, () const, unsigned), AS_CALL_THISCALL);
    // SharedPtr<SoundStream> Sound::GetDecoderStream() const | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "SoundStream@+ GetDecoderStream() const", AS_FUNCTION_OBJFIRST(Sound_GetDecoderStream_void), AS_CALL_CDECL_OBJFIRST);
    // signed char* Sound::GetEnd() const | File: ../Audio/Sound.h
    // Error: type "signed char*" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "VariantMap& GetEventDataMap() const", AS_METHODPR(Sound, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "Object@+ GetEventSender() const", AS_METHODPR(Sound, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // float Sound::GetFrequency() const | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "float GetFrequency() const", AS_METHODPR(Sound, GetFrequency, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "float get_frequency() const", AS_METHODPR(Sound, GetFrequency, () const, float), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Sound, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Sound, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Sound, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "const VariantMap& get_globalVars() const", AS_METHODPR(Sound, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Sound::GetIntFrequency() const | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "uint GetIntFrequency() const", AS_METHODPR(Sound, GetIntFrequency, () const, unsigned), AS_CALL_THISCALL);
    // float Sound::GetLength() const | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "float GetLength() const", AS_METHODPR(Sound, GetLength, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "float get_length() const", AS_METHODPR(Sound, GetLength, () const, float), AS_CALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "uint GetMemoryUse() const", AS_METHODPR(Sound, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "uint get_memoryUse() const", AS_METHODPR(Sound, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // const Variant& ResourceWithMetadata::GetMetadata(const String& name) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "const Variant& GetMetadata(const String&in) const", AS_METHODPR(Sound, GetMetadata, (const String&) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "const Variant& get_metadata(const String&in) const", AS_METHODPR(Sound, GetMetadata, (const String&) const, const Variant&), AS_CALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "const String& GetName() const", AS_METHODPR(Sound, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "const String& get_name() const", AS_METHODPR(Sound, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "StringHash GetNameHash() const", AS_METHODPR(Sound, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // signed char* Sound::GetRepeat() const | File: ../Audio/Sound.h
    // Error: type "signed char*" can not automatically bind
    // unsigned Sound::GetSampleSize() const | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "uint GetSampleSize() const", AS_METHODPR(Sound, GetSampleSize, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "uint get_sampleSize() const", AS_METHODPR(Sound, GetSampleSize, () const, unsigned), AS_CALL_THISCALL);
    // signed char* Sound::GetStart() const | File: ../Audio/Sound.h
    // Error: type "signed char*" can not automatically bind
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Sound, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "StringHash GetType() const", AS_METHODPR(Sound, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "StringHash get_type() const", AS_METHODPR(Sound, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "const String& GetTypeName() const", AS_METHODPR(Sound, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "const String& get_typeName() const", AS_METHODPR(Sound, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "uint GetUseTimer()", AS_METHODPR(Sound, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "uint get_useTimer()", AS_METHODPR(Sound, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "bool HasEventHandlers() const", AS_METHODPR(Sound, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool ResourceWithMetadata::HasMetadata() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "bool HasMetadata() const", AS_METHODPR(Sound, HasMetadata, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "bool get_hasMetadata() const", AS_METHODPR(Sound, HasMetadata, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Sound, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Sound, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Sound::IsCompressed() const | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "bool IsCompressed() const", AS_METHODPR(Sound, IsCompressed, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "bool get_compressed() const", AS_METHODPR(Sound, IsCompressed, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Sound, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Sound::IsLooped() const | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "bool IsLooped() const", AS_METHODPR(Sound, IsLooped, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "bool get_looped() const", AS_METHODPR(Sound, IsLooped, () const, bool), AS_CALL_THISCALL);
    // bool Sound::IsSixteenBit() const | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "bool IsSixteenBit() const", AS_METHODPR(Sound, IsSixteenBit, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "bool get_sixteenBit() const", AS_METHODPR(Sound, IsSixteenBit, () const, bool), AS_CALL_THISCALL);
    // bool Sound::IsStereo() const | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "bool IsStereo() const", AS_METHODPR(Sound, IsStereo, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "bool get_stereo() const", AS_METHODPR(Sound, IsStereo, () const, bool), AS_CALL_THISCALL);
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "bool Load(Deserializer&)", AS_METHODPR(Sound, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "bool LoadFile(const String&in)", AS_METHODPR(Sound, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "bool Load(const String&in)", AS_METHODPR(Sound, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // bool Sound::LoadOggVorbis(Deserializer& source) | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "bool LoadOggVorbis(Deserializer&)", AS_METHODPR(Sound, LoadOggVorbis, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Sound::LoadRaw(Deserializer& source) | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "bool LoadRaw(Deserializer&)", AS_METHODPR(Sound, LoadRaw, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Sound::LoadWav(Deserializer& source) | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "bool LoadWav(Deserializer&)", AS_METHODPR(Sound, LoadWav, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Sound, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Sound", "int Refs() const", AS_METHODPR(Sound, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "int get_refs() const", AS_METHODPR(Sound, Refs, () const, int), AS_CALL_THISCALL);
    // static void Sound::RegisterObject(Context* context) | File: ../Audio/Sound.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Sound", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Sound, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void ResourceWithMetadata::RemoveAllMetadata() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "void RemoveAllMetadata()", AS_METHODPR(Sound, RemoveAllMetadata, (), void), AS_CALL_THISCALL);
    // void ResourceWithMetadata::RemoveMetadata(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "void RemoveMetadata(const String&in)", AS_METHODPR(Sound, RemoveMetadata, (const String&), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "void ResetUseTimer()", AS_METHODPR(Sound, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "bool Save(Serializer&) const", AS_METHODPR(Sound, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "bool SaveFile(const String&in) const", AS_METHODPR(Sound, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "bool Save(const String&in) const", AS_METHODPR(Sound, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "void SendEvent(StringHash)", AS_METHODPR(Sound, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Sound, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(Sound, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "void SetBlockEvents(bool)", AS_METHODPR(Sound, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Sound::SetData(const void* data, unsigned dataSize) | File: ../Audio/Sound.h
    // Error: type "const void*" can not automatically bind
    // void Sound::SetFormat(unsigned frequency, bool sixteenBit, bool stereo) | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "void SetFormat(uint, bool, bool)", AS_METHODPR(Sound, SetFormat, (unsigned, bool, bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Sound, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Sound, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Sound::SetLoop(unsigned repeatOffset, unsigned endOffset) | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "void SetLoop(uint, uint)", AS_METHODPR(Sound, SetLoop, (unsigned, unsigned), void), AS_CALL_THISCALL);
    // void Sound::SetLooped(bool enable) | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "void SetLooped(bool)", AS_METHODPR(Sound, SetLooped, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "void set_looped(bool)", AS_METHODPR(Sound, SetLooped, (bool), void), AS_CALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "void SetMemoryUse(uint)", AS_METHODPR(Sound, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sound", "void SetName(const String&in)", AS_METHODPR(Sound, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "void set_name(const String&in)", AS_METHODPR(Sound, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Sound::SetSize(unsigned dataSize) | File: ../Audio/Sound.h
    engine->RegisterObjectMethod("Sound", "void SetSize(uint)", AS_METHODPR(Sound, SetSize, (unsigned), void), AS_CALL_THISCALL);
    // explicit Sound::Sound(Context* context) | File: ../Audio/Sound.h
    engine->RegisterObjectBehaviour("Sound", asBEHAVE_FACTORY, "Sound@+ f()", AS_FUNCTION(Sound_Sound_Context), AS_CALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "void UnsubscribeFromAllEvents()", AS_METHODPR(Sound, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Sound_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Sound, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Sound, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sound", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Sound, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Sound", "int WeakRefs() const", AS_METHODPR(Sound, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sound", "int get_weakRefs() const", AS_METHODPR(Sound, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("SoundListener", asBEHAVE_ADDREF, "void f()", AS_METHODPR(SoundListener, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "void AllocateNetworkState()", AS_METHODPR(SoundListener, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "void ApplyAttributes()", AS_METHODPR(SoundListener, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(SoundListener, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "bool GetAnimationEnabled() const", AS_METHODPR(SoundListener, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "bool get_animationEnabled() const", AS_METHODPR(SoundListener, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "Variant GetAttribute(uint) const", AS_METHODPR(SoundListener, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "Variant get_attributes(uint) const", AS_METHODPR(SoundListener, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "Variant GetAttribute(const String&in) const", AS_METHODPR(SoundListener, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(SoundListener, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(SoundListener, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(SoundListener, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(SoundListener, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "Variant GetAttributeDefault(uint) const", AS_METHODPR(SoundListener, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "Variant get_attributeDefaults(uint) const", AS_METHODPR(SoundListener, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(SoundListener, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "bool GetBlockEvents() const", AS_METHODPR(SoundListener, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "const String& GetCategory() const", AS_METHODPR(SoundListener, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "const String& get_category() const", AS_METHODPR(SoundListener, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "Component@+ GetComponent(StringHash) const", AS_METHODPR(SoundListener, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("SoundListener", "VariantMap& GetEventDataMap() const", AS_METHODPR(SoundListener, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "Object@+ GetEventSender() const", AS_METHODPR(SoundListener, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(SoundListener, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(SoundListener, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "const VariantMap& GetGlobalVars() const", AS_METHODPR(SoundListener, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "const VariantMap& get_globalVars() const", AS_METHODPR(SoundListener, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "uint GetID() const", AS_METHODPR(SoundListener, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "uint get_id() const", AS_METHODPR(SoundListener, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(SoundListener, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "Node@+ GetNode() const", AS_METHODPR(SoundListener, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "Node@+ get_node() const", AS_METHODPR(SoundListener, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "uint GetNumAttributes() const", AS_METHODPR(SoundListener, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "uint get_numAttributes() const", AS_METHODPR(SoundListener, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "uint GetNumNetworkAttributes() const", AS_METHODPR(SoundListener, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(SoundListener, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(SoundListener, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(SoundListener, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "Scene@+ GetScene() const", AS_METHODPR(SoundListener, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(SoundListener, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "StringHash GetType() const", AS_METHODPR(SoundListener, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "StringHash get_type() const", AS_METHODPR(SoundListener, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "const String& GetTypeName() const", AS_METHODPR(SoundListener, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "const String& get_typeName() const", AS_METHODPR(SoundListener, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "bool HasEventHandlers() const", AS_METHODPR(SoundListener, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(SoundListener, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(SoundListener, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "bool IsEnabled() const", AS_METHODPR(SoundListener, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "bool get_enabled() const", AS_METHODPR(SoundListener, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "bool IsEnabledEffective() const", AS_METHODPR(SoundListener, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "bool get_enabledEffective() const", AS_METHODPR(SoundListener, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "bool IsInstanceOf(StringHash) const", AS_METHODPR(SoundListener, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "bool IsReplicated() const", AS_METHODPR(SoundListener, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "bool get_replicated() const", AS_METHODPR(SoundListener, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "bool IsTemporary() const", AS_METHODPR(SoundListener, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "bool get_temporary() const", AS_METHODPR(SoundListener, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "bool Load(Deserializer&)", AS_METHODPR(SoundListener, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(SoundListener, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "bool LoadXML(const XMLElement&in)", AS_METHODPR(SoundListener, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "void MarkNetworkUpdate()", AS_METHODPR(SoundListener, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(SoundListener, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(SoundListener, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(SoundListener, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "void OnSetEnabled()", AS_METHODPR(SoundListener, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "void PrepareNetworkUpdate()", AS_METHODPR(SoundListener, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(SoundListener, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(SoundListener, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SoundListener", "int Refs() const", AS_METHODPR(SoundListener, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "int get_refs() const", AS_METHODPR(SoundListener, Refs, () const, int), AS_CALL_THISCALL);
    // static void SoundListener::RegisterObject(Context* context) | File: ../Audio/SoundListener.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("SoundListener", asBEHAVE_RELEASE, "void f()", AS_METHODPR(SoundListener, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "void Remove()", AS_METHODPR(SoundListener, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(SoundListener, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "void RemoveInstanceDefault()", AS_METHODPR(SoundListener, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "void RemoveObjectAnimation()", AS_METHODPR(SoundListener, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "void ResetToDefault()", AS_METHODPR(SoundListener, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "bool Save(Serializer&) const", AS_METHODPR(SoundListener, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "bool SaveDefaultAttributes() const", AS_METHODPR(SoundListener, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "bool SaveJSON(JSONValue&) const", AS_METHODPR(SoundListener, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "bool SaveXML(XMLElement&) const", AS_METHODPR(SoundListener, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "void SendEvent(StringHash)", AS_METHODPR(SoundListener, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(SoundListener, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "void SetAnimationEnabled(bool)", AS_METHODPR(SoundListener, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "void set_animationEnabled(bool)", AS_METHODPR(SoundListener, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "void SetAnimationTime(float)", AS_METHODPR(SoundListener, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(SoundListener, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(SoundListener, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(SoundListener, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(SoundListener, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(SoundListener, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(SoundListener, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(SoundListener, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "void SetBlockEvents(bool)", AS_METHODPR(SoundListener, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundListener", "void SetEnabled(bool)", AS_METHODPR(SoundListener, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "void set_enabled(bool)", AS_METHODPR(SoundListener, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(SoundListener, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(SoundListener, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "void SetInstanceDefault(bool)", AS_METHODPR(SoundListener, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(SoundListener, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(SoundListener, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(SoundListener, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundListener", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(SoundListener, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "void SetTemporary(bool)", AS_METHODPR(SoundListener, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "void set_temporary(bool)", AS_METHODPR(SoundListener, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // explicit SoundListener::SoundListener(Context* context) | File: ../Audio/SoundListener.h
    engine->RegisterObjectBehaviour("SoundListener", asBEHAVE_FACTORY, "SoundListener@+ f()", AS_FUNCTION(SoundListener_SoundListener_Context), AS_CALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "void UnsubscribeFromAllEvents()", AS_METHODPR(SoundListener, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(SoundListener_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(SoundListener, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(SoundListener, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundListener", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(SoundListener, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SoundListener", "int WeakRefs() const", AS_METHODPR(SoundListener, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundListener", "int get_weakRefs() const", AS_METHODPR(SoundListener, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(SoundListener, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(SoundListener, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundListener", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(SoundListener, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("SoundSource", asBEHAVE_ADDREF, "void f()", AS_METHODPR(SoundSource, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "void AllocateNetworkState()", AS_METHODPR(SoundSource, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "void ApplyAttributes()", AS_METHODPR(SoundSource, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(SoundSource, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "bool GetAnimationEnabled() const", AS_METHODPR(SoundSource, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "bool get_animationEnabled() const", AS_METHODPR(SoundSource, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // float SoundSource::GetAttenuation() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "float GetAttenuation() const", AS_METHODPR(SoundSource, GetAttenuation, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "float get_attenuation() const", AS_METHODPR(SoundSource, GetAttenuation, () const, float), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "Variant GetAttribute(uint) const", AS_METHODPR(SoundSource, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "Variant get_attributes(uint) const", AS_METHODPR(SoundSource, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "Variant GetAttribute(const String&in) const", AS_METHODPR(SoundSource, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(SoundSource, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(SoundSource, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(SoundSource, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(SoundSource, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "Variant GetAttributeDefault(uint) const", AS_METHODPR(SoundSource, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "Variant get_attributeDefaults(uint) const", AS_METHODPR(SoundSource, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(SoundSource, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // AutoRemoveMode SoundSource::GetAutoRemoveMode() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "AutoRemoveMode GetAutoRemoveMode() const", AS_METHODPR(SoundSource, GetAutoRemoveMode, () const, AutoRemoveMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "AutoRemoveMode get_autoRemoveMode() const", AS_METHODPR(SoundSource, GetAutoRemoveMode, () const, AutoRemoveMode), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "bool GetBlockEvents() const", AS_METHODPR(SoundSource, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "const String& GetCategory() const", AS_METHODPR(SoundSource, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "const String& get_category() const", AS_METHODPR(SoundSource, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "Component@+ GetComponent(StringHash) const", AS_METHODPR(SoundSource, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("SoundSource", "VariantMap& GetEventDataMap() const", AS_METHODPR(SoundSource, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "Object@+ GetEventSender() const", AS_METHODPR(SoundSource, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // float SoundSource::GetFrequency() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "float GetFrequency() const", AS_METHODPR(SoundSource, GetFrequency, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "float get_frequency() const", AS_METHODPR(SoundSource, GetFrequency, () const, float), AS_CALL_THISCALL);
    // float SoundSource::GetGain() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "float GetGain() const", AS_METHODPR(SoundSource, GetGain, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "float get_gain() const", AS_METHODPR(SoundSource, GetGain, () const, float), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(SoundSource, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(SoundSource, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "const VariantMap& GetGlobalVars() const", AS_METHODPR(SoundSource, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "const VariantMap& get_globalVars() const", AS_METHODPR(SoundSource, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "uint GetID() const", AS_METHODPR(SoundSource, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "uint get_id() const", AS_METHODPR(SoundSource, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(SoundSource, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "Node@+ GetNode() const", AS_METHODPR(SoundSource, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "Node@+ get_node() const", AS_METHODPR(SoundSource, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "uint GetNumAttributes() const", AS_METHODPR(SoundSource, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "uint get_numAttributes() const", AS_METHODPR(SoundSource, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "uint GetNumNetworkAttributes() const", AS_METHODPR(SoundSource, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(SoundSource, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(SoundSource, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(SoundSource, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float SoundSource::GetPanning() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "float GetPanning() const", AS_METHODPR(SoundSource, GetPanning, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "float get_panning() const", AS_METHODPR(SoundSource, GetPanning, () const, float), AS_CALL_THISCALL);
    // volatile signed char* SoundSource::GetPlayPosition() const | File: ../Audio/SoundSource.h
    // Error: type "signed char*" can not automatically bind
    // int SoundSource::GetPositionAttr() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "int GetPositionAttr() const", AS_METHODPR(SoundSource, GetPositionAttr, () const, int), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "Scene@+ GetScene() const", AS_METHODPR(SoundSource, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Sound* SoundSource::GetSound() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "Sound@+ GetSound() const", AS_METHODPR(SoundSource, GetSound, () const, Sound*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "Sound@+ get_sound() const", AS_METHODPR(SoundSource, GetSound, () const, Sound*), AS_CALL_THISCALL);
    // ResourceRef SoundSource::GetSoundAttr() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "ResourceRef GetSoundAttr() const", AS_METHODPR(SoundSource, GetSoundAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // String SoundSource::GetSoundType() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "String GetSoundType() const", AS_METHODPR(SoundSource, GetSoundType, () const, String), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "String get_soundType() const", AS_METHODPR(SoundSource, GetSoundType, () const, String), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(SoundSource, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // float SoundSource::GetTimePosition() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "float GetTimePosition() const", AS_METHODPR(SoundSource, GetTimePosition, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "float get_timePosition() const", AS_METHODPR(SoundSource, GetTimePosition, () const, float), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "StringHash GetType() const", AS_METHODPR(SoundSource, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "StringHash get_type() const", AS_METHODPR(SoundSource, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "const String& GetTypeName() const", AS_METHODPR(SoundSource, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "const String& get_typeName() const", AS_METHODPR(SoundSource, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "bool HasEventHandlers() const", AS_METHODPR(SoundSource, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(SoundSource, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(SoundSource, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "bool IsEnabled() const", AS_METHODPR(SoundSource, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "bool get_enabled() const", AS_METHODPR(SoundSource, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "bool IsEnabledEffective() const", AS_METHODPR(SoundSource, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "bool get_enabledEffective() const", AS_METHODPR(SoundSource, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "bool IsInstanceOf(StringHash) const", AS_METHODPR(SoundSource, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool SoundSource::IsPlaying() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "bool IsPlaying() const", AS_METHODPR(SoundSource, IsPlaying, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "bool get_playing() const", AS_METHODPR(SoundSource, IsPlaying, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "bool IsReplicated() const", AS_METHODPR(SoundSource, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "bool get_replicated() const", AS_METHODPR(SoundSource, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "bool IsTemporary() const", AS_METHODPR(SoundSource, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "bool get_temporary() const", AS_METHODPR(SoundSource, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "bool Load(Deserializer&)", AS_METHODPR(SoundSource, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(SoundSource, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "bool LoadXML(const XMLElement&in)", AS_METHODPR(SoundSource, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "void MarkNetworkUpdate()", AS_METHODPR(SoundSource, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void SoundSource::Mix(int* dest, unsigned samples, int mixRate, bool stereo, bool interpolation) | File: ../Audio/SoundSource.h
    // Error: type "int*" can not automatically bind
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(SoundSource, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(SoundSource, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(SoundSource, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "void OnSetEnabled()", AS_METHODPR(SoundSource, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void SoundSource::Play(Sound* sound) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void Play(Sound@+)", AS_METHODPR(SoundSource, Play, (Sound*), void), AS_CALL_THISCALL);
    // void SoundSource::Play(Sound* sound, float frequency) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void Play(Sound@+, float)", AS_METHODPR(SoundSource, Play, (Sound*, float), void), AS_CALL_THISCALL);
    // void SoundSource::Play(Sound* sound, float frequency, float gain) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void Play(Sound@+, float, float)", AS_METHODPR(SoundSource, Play, (Sound*, float, float), void), AS_CALL_THISCALL);
    // void SoundSource::Play(Sound* sound, float frequency, float gain, float panning) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void Play(Sound@+, float, float, float)", AS_METHODPR(SoundSource, Play, (Sound*, float, float, float), void), AS_CALL_THISCALL);
    // void SoundSource::Play(SoundStream* stream) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void Play(SoundStream@+)", AS_METHODPR(SoundSource, Play, (SoundStream*), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "void PrepareNetworkUpdate()", AS_METHODPR(SoundSource, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(SoundSource, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(SoundSource, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SoundSource", "int Refs() const", AS_METHODPR(SoundSource, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "int get_refs() const", AS_METHODPR(SoundSource, Refs, () const, int), AS_CALL_THISCALL);
    // static void SoundSource::RegisterObject(Context* context) | File: ../Audio/SoundSource.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("SoundSource", asBEHAVE_RELEASE, "void f()", AS_METHODPR(SoundSource, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "void Remove()", AS_METHODPR(SoundSource, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(SoundSource, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "void RemoveInstanceDefault()", AS_METHODPR(SoundSource, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "void RemoveObjectAnimation()", AS_METHODPR(SoundSource, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "void ResetToDefault()", AS_METHODPR(SoundSource, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "bool Save(Serializer&) const", AS_METHODPR(SoundSource, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "bool SaveDefaultAttributes() const", AS_METHODPR(SoundSource, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "bool SaveJSON(JSONValue&) const", AS_METHODPR(SoundSource, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "bool SaveXML(XMLElement&) const", AS_METHODPR(SoundSource, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void SoundSource::Seek(float seekTime) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void Seek(float)", AS_METHODPR(SoundSource, Seek, (float), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "void SendEvent(StringHash)", AS_METHODPR(SoundSource, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(SoundSource, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "void SetAnimationEnabled(bool)", AS_METHODPR(SoundSource, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "void set_animationEnabled(bool)", AS_METHODPR(SoundSource, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "void SetAnimationTime(float)", AS_METHODPR(SoundSource, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // void SoundSource::SetAttenuation(float attenuation) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void SetAttenuation(float)", AS_METHODPR(SoundSource, SetAttenuation, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(SoundSource, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(SoundSource, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(SoundSource, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(SoundSource, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(SoundSource, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(SoundSource, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(SoundSource, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void SoundSource::SetAutoRemoveMode(AutoRemoveMode mode) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void SetAutoRemoveMode(AutoRemoveMode)", AS_METHODPR(SoundSource, SetAutoRemoveMode, (AutoRemoveMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "void set_autoRemoveMode(AutoRemoveMode)", AS_METHODPR(SoundSource, SetAutoRemoveMode, (AutoRemoveMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "void SetBlockEvents(bool)", AS_METHODPR(SoundSource, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource", "void SetEnabled(bool)", AS_METHODPR(SoundSource, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "void set_enabled(bool)", AS_METHODPR(SoundSource, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void SoundSource::SetFrequency(float frequency) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void SetFrequency(float)", AS_METHODPR(SoundSource, SetFrequency, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "void set_frequency(float)", AS_METHODPR(SoundSource, SetFrequency, (float), void), AS_CALL_THISCALL);
    // void SoundSource::SetGain(float gain) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void SetGain(float)", AS_METHODPR(SoundSource, SetGain, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "void set_gain(float)", AS_METHODPR(SoundSource, SetGain, (float), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(SoundSource, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(SoundSource, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "void SetInstanceDefault(bool)", AS_METHODPR(SoundSource, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(SoundSource, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(SoundSource, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(SoundSource, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(SoundSource, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void SoundSource::SetPanning(float panning) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void SetPanning(float)", AS_METHODPR(SoundSource, SetPanning, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "void set_panning(float)", AS_METHODPR(SoundSource, SetPanning, (float), void), AS_CALL_THISCALL);
    // void SoundSource::SetPlayingAttr(bool value) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void SetPlayingAttr(bool)", AS_METHODPR(SoundSource, SetPlayingAttr, (bool), void), AS_CALL_THISCALL);
    // void SoundSource::SetPlayPosition(signed char* pos) | File: ../Audio/SoundSource.h
    // Error: type "signed char*" can not automatically bind
    // void SoundSource::SetPositionAttr(int value) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void SetPositionAttr(int)", AS_METHODPR(SoundSource, SetPositionAttr, (int), void), AS_CALL_THISCALL);
    // void SoundSource::SetSoundAttr(const ResourceRef& value) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void SetSoundAttr(const ResourceRef&in)", AS_METHODPR(SoundSource, SetSoundAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void SoundSource::SetSoundType(const String& type) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void SetSoundType(const String&in)", AS_METHODPR(SoundSource, SetSoundType, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "void set_soundType(const String&in)", AS_METHODPR(SoundSource, SetSoundType, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "void SetTemporary(bool)", AS_METHODPR(SoundSource, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "void set_temporary(bool)", AS_METHODPR(SoundSource, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // explicit SoundSource::SoundSource(Context* context) | File: ../Audio/SoundSource.h
    engine->RegisterObjectBehaviour("SoundSource", asBEHAVE_FACTORY, "SoundSource@+ f()", AS_FUNCTION(SoundSource_SoundSource_Context), AS_CALL_CDECL);
    // void SoundSource::Stop() | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void Stop()", AS_METHODPR(SoundSource, Stop, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "void UnsubscribeFromAllEvents()", AS_METHODPR(SoundSource, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(SoundSource_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(SoundSource, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(SoundSource, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(SoundSource, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void SoundSource::Update(float timeStep) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void Update(float)", AS_METHODPR(SoundSource, Update, (float), void), AS_CALL_THISCALL);
    // void SoundSource::UpdateMasterGain() | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource", "void UpdateMasterGain()", AS_METHODPR(SoundSource, UpdateMasterGain, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SoundSource", "int WeakRefs() const", AS_METHODPR(SoundSource, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource", "int get_weakRefs() const", AS_METHODPR(SoundSource, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(SoundSource, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(SoundSource, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(SoundSource, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("SoundSource3D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(SoundSource3D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "void AllocateNetworkState()", AS_METHODPR(SoundSource3D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "void ApplyAttributes()", AS_METHODPR(SoundSource3D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void SoundSource3D::CalculateAttenuation() | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "void CalculateAttenuation()", AS_METHODPR(SoundSource3D, CalculateAttenuation, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void SoundSource3D::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(SoundSource3D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "bool GetAnimationEnabled() const", AS_METHODPR(SoundSource3D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "bool get_animationEnabled() const", AS_METHODPR(SoundSource3D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // float SoundSource::GetAttenuation() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "float GetAttenuation() const", AS_METHODPR(SoundSource3D, GetAttenuation, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "float get_attenuation() const", AS_METHODPR(SoundSource3D, GetAttenuation, () const, float), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "Variant GetAttribute(uint) const", AS_METHODPR(SoundSource3D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "Variant get_attributes(uint) const", AS_METHODPR(SoundSource3D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "Variant GetAttribute(const String&in) const", AS_METHODPR(SoundSource3D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(SoundSource3D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(SoundSource3D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(SoundSource3D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(SoundSource3D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(SoundSource3D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(SoundSource3D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(SoundSource3D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // AutoRemoveMode SoundSource::GetAutoRemoveMode() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "AutoRemoveMode GetAutoRemoveMode() const", AS_METHODPR(SoundSource3D, GetAutoRemoveMode, () const, AutoRemoveMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "AutoRemoveMode get_autoRemoveMode() const", AS_METHODPR(SoundSource3D, GetAutoRemoveMode, () const, AutoRemoveMode), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "bool GetBlockEvents() const", AS_METHODPR(SoundSource3D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "const String& GetCategory() const", AS_METHODPR(SoundSource3D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "const String& get_category() const", AS_METHODPR(SoundSource3D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(SoundSource3D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("SoundSource3D", "VariantMap& GetEventDataMap() const", AS_METHODPR(SoundSource3D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "Object@+ GetEventSender() const", AS_METHODPR(SoundSource3D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // float SoundSource3D::GetFarDistance() const | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "float GetFarDistance() const", AS_METHODPR(SoundSource3D, GetFarDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "float get_farDistance() const", AS_METHODPR(SoundSource3D, GetFarDistance, () const, float), AS_CALL_THISCALL);
    // float SoundSource::GetFrequency() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "float GetFrequency() const", AS_METHODPR(SoundSource3D, GetFrequency, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "float get_frequency() const", AS_METHODPR(SoundSource3D, GetFrequency, () const, float), AS_CALL_THISCALL);
    // float SoundSource::GetGain() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "float GetGain() const", AS_METHODPR(SoundSource3D, GetGain, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "float get_gain() const", AS_METHODPR(SoundSource3D, GetGain, () const, float), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(SoundSource3D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(SoundSource3D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(SoundSource3D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "const VariantMap& get_globalVars() const", AS_METHODPR(SoundSource3D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "uint GetID() const", AS_METHODPR(SoundSource3D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "uint get_id() const", AS_METHODPR(SoundSource3D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // float SoundSource3D::GetInnerAngle() const | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "float GetInnerAngle() const", AS_METHODPR(SoundSource3D, GetInnerAngle, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "float get_innerAngle() const", AS_METHODPR(SoundSource3D, GetInnerAngle, () const, float), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(SoundSource3D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // float SoundSource3D::GetNearDistance() const | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "float GetNearDistance() const", AS_METHODPR(SoundSource3D, GetNearDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "float get_nearDistance() const", AS_METHODPR(SoundSource3D, GetNearDistance, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "Node@+ GetNode() const", AS_METHODPR(SoundSource3D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "Node@+ get_node() const", AS_METHODPR(SoundSource3D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "uint GetNumAttributes() const", AS_METHODPR(SoundSource3D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "uint get_numAttributes() const", AS_METHODPR(SoundSource3D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "uint GetNumNetworkAttributes() const", AS_METHODPR(SoundSource3D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(SoundSource3D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(SoundSource3D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(SoundSource3D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float SoundSource3D::GetOuterAngle() const | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "float GetOuterAngle() const", AS_METHODPR(SoundSource3D, GetOuterAngle, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "float get_outerAngle() const", AS_METHODPR(SoundSource3D, GetOuterAngle, () const, float), AS_CALL_THISCALL);
    // float SoundSource::GetPanning() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "float GetPanning() const", AS_METHODPR(SoundSource3D, GetPanning, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "float get_panning() const", AS_METHODPR(SoundSource3D, GetPanning, () const, float), AS_CALL_THISCALL);
    // volatile signed char* SoundSource::GetPlayPosition() const | File: ../Audio/SoundSource.h
    // Error: type "signed char*" can not automatically bind
    // int SoundSource::GetPositionAttr() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "int GetPositionAttr() const", AS_METHODPR(SoundSource3D, GetPositionAttr, () const, int), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "Scene@+ GetScene() const", AS_METHODPR(SoundSource3D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Sound* SoundSource::GetSound() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "Sound@+ GetSound() const", AS_METHODPR(SoundSource3D, GetSound, () const, Sound*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "Sound@+ get_sound() const", AS_METHODPR(SoundSource3D, GetSound, () const, Sound*), AS_CALL_THISCALL);
    // ResourceRef SoundSource::GetSoundAttr() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "ResourceRef GetSoundAttr() const", AS_METHODPR(SoundSource3D, GetSoundAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // String SoundSource::GetSoundType() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "String GetSoundType() const", AS_METHODPR(SoundSource3D, GetSoundType, () const, String), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "String get_soundType() const", AS_METHODPR(SoundSource3D, GetSoundType, () const, String), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(SoundSource3D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // float SoundSource::GetTimePosition() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "float GetTimePosition() const", AS_METHODPR(SoundSource3D, GetTimePosition, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "float get_timePosition() const", AS_METHODPR(SoundSource3D, GetTimePosition, () const, float), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "StringHash GetType() const", AS_METHODPR(SoundSource3D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "StringHash get_type() const", AS_METHODPR(SoundSource3D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "const String& GetTypeName() const", AS_METHODPR(SoundSource3D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "const String& get_typeName() const", AS_METHODPR(SoundSource3D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "bool HasEventHandlers() const", AS_METHODPR(SoundSource3D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(SoundSource3D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(SoundSource3D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "bool IsEnabled() const", AS_METHODPR(SoundSource3D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "bool get_enabled() const", AS_METHODPR(SoundSource3D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "bool IsEnabledEffective() const", AS_METHODPR(SoundSource3D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "bool get_enabledEffective() const", AS_METHODPR(SoundSource3D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(SoundSource3D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool SoundSource::IsPlaying() const | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "bool IsPlaying() const", AS_METHODPR(SoundSource3D, IsPlaying, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "bool get_playing() const", AS_METHODPR(SoundSource3D, IsPlaying, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "bool IsReplicated() const", AS_METHODPR(SoundSource3D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "bool get_replicated() const", AS_METHODPR(SoundSource3D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "bool IsTemporary() const", AS_METHODPR(SoundSource3D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "bool get_temporary() const", AS_METHODPR(SoundSource3D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "bool Load(Deserializer&)", AS_METHODPR(SoundSource3D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(SoundSource3D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(SoundSource3D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "void MarkNetworkUpdate()", AS_METHODPR(SoundSource3D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void SoundSource::Mix(int* dest, unsigned samples, int mixRate, bool stereo, bool interpolation) | File: ../Audio/SoundSource.h
    // Error: type "int*" can not automatically bind
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(SoundSource3D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(SoundSource3D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(SoundSource3D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "void OnSetEnabled()", AS_METHODPR(SoundSource3D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void SoundSource::Play(Sound* sound) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void Play(Sound@+)", AS_METHODPR(SoundSource3D, Play, (Sound*), void), AS_CALL_THISCALL);
    // void SoundSource::Play(Sound* sound, float frequency) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void Play(Sound@+, float)", AS_METHODPR(SoundSource3D, Play, (Sound*, float), void), AS_CALL_THISCALL);
    // void SoundSource::Play(Sound* sound, float frequency, float gain) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void Play(Sound@+, float, float)", AS_METHODPR(SoundSource3D, Play, (Sound*, float, float), void), AS_CALL_THISCALL);
    // void SoundSource::Play(Sound* sound, float frequency, float gain, float panning) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void Play(Sound@+, float, float, float)", AS_METHODPR(SoundSource3D, Play, (Sound*, float, float, float), void), AS_CALL_THISCALL);
    // void SoundSource::Play(SoundStream* stream) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void Play(SoundStream@+)", AS_METHODPR(SoundSource3D, Play, (SoundStream*), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "void PrepareNetworkUpdate()", AS_METHODPR(SoundSource3D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(SoundSource3D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(SoundSource3D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SoundSource3D", "int Refs() const", AS_METHODPR(SoundSource3D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "int get_refs() const", AS_METHODPR(SoundSource3D, Refs, () const, int), AS_CALL_THISCALL);
    // static void SoundSource3D::RegisterObject(Context* context) | File: ../Audio/SoundSource3D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("SoundSource3D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(SoundSource3D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "void Remove()", AS_METHODPR(SoundSource3D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(SoundSource3D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "void RemoveInstanceDefault()", AS_METHODPR(SoundSource3D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "void RemoveObjectAnimation()", AS_METHODPR(SoundSource3D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "void ResetToDefault()", AS_METHODPR(SoundSource3D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // float SoundSource3D::RollAngleoffFactor() const | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "float RollAngleoffFactor() const", AS_METHODPR(SoundSource3D, RollAngleoffFactor, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "float get_rolloffFactor() const", AS_METHODPR(SoundSource3D, RollAngleoffFactor, () const, float), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "bool Save(Serializer&) const", AS_METHODPR(SoundSource3D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "bool SaveDefaultAttributes() const", AS_METHODPR(SoundSource3D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(SoundSource3D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "bool SaveXML(XMLElement&) const", AS_METHODPR(SoundSource3D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void SoundSource::Seek(float seekTime) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void Seek(float)", AS_METHODPR(SoundSource3D, Seek, (float), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "void SendEvent(StringHash)", AS_METHODPR(SoundSource3D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(SoundSource3D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void SoundSource3D::SetAngleAttenuation(float innerAngle, float outerAngle) | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetAngleAttenuation(float, float)", AS_METHODPR(SoundSource3D, SetAngleAttenuation, (float, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetAnimationEnabled(bool)", AS_METHODPR(SoundSource3D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_animationEnabled(bool)", AS_METHODPR(SoundSource3D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetAnimationTime(float)", AS_METHODPR(SoundSource3D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // void SoundSource::SetAttenuation(float attenuation) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetAttenuation(float)", AS_METHODPR(SoundSource3D, SetAttenuation, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(SoundSource3D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(SoundSource3D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(SoundSource3D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(SoundSource3D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(SoundSource3D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(SoundSource3D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(SoundSource3D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void SoundSource::SetAutoRemoveMode(AutoRemoveMode mode) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetAutoRemoveMode(AutoRemoveMode)", AS_METHODPR(SoundSource3D, SetAutoRemoveMode, (AutoRemoveMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_autoRemoveMode(AutoRemoveMode)", AS_METHODPR(SoundSource3D, SetAutoRemoveMode, (AutoRemoveMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetBlockEvents(bool)", AS_METHODPR(SoundSource3D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void SoundSource3D::SetDistanceAttenuation(float nearDistance, float farDistance, float rolloffFactor) | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetDistanceAttenuation(float, float, float)", AS_METHODPR(SoundSource3D, SetDistanceAttenuation, (float, float, float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetEnabled(bool)", AS_METHODPR(SoundSource3D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_enabled(bool)", AS_METHODPR(SoundSource3D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void SoundSource3D::SetFarDistance(float distance) | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetFarDistance(float)", AS_METHODPR(SoundSource3D, SetFarDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_farDistance(float)", AS_METHODPR(SoundSource3D, SetFarDistance, (float), void), AS_CALL_THISCALL);
    // void SoundSource::SetFrequency(float frequency) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetFrequency(float)", AS_METHODPR(SoundSource3D, SetFrequency, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_frequency(float)", AS_METHODPR(SoundSource3D, SetFrequency, (float), void), AS_CALL_THISCALL);
    // void SoundSource::SetGain(float gain) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetGain(float)", AS_METHODPR(SoundSource3D, SetGain, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_gain(float)", AS_METHODPR(SoundSource3D, SetGain, (float), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(SoundSource3D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(SoundSource3D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void SoundSource3D::SetInnerAngle(float angle) | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetInnerAngle(float)", AS_METHODPR(SoundSource3D, SetInnerAngle, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_innerAngle(float)", AS_METHODPR(SoundSource3D, SetInnerAngle, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetInstanceDefault(bool)", AS_METHODPR(SoundSource3D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(SoundSource3D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void SoundSource3D::SetNearDistance(float distance) | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetNearDistance(float)", AS_METHODPR(SoundSource3D, SetNearDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_nearDistance(float)", AS_METHODPR(SoundSource3D, SetNearDistance, (float), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(SoundSource3D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(SoundSource3D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(SoundSource3D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void SoundSource3D::SetOuterAngle(float angle) | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetOuterAngle(float)", AS_METHODPR(SoundSource3D, SetOuterAngle, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_outerAngle(float)", AS_METHODPR(SoundSource3D, SetOuterAngle, (float), void), AS_CALL_THISCALL);
    // void SoundSource::SetPanning(float panning) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetPanning(float)", AS_METHODPR(SoundSource3D, SetPanning, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_panning(float)", AS_METHODPR(SoundSource3D, SetPanning, (float), void), AS_CALL_THISCALL);
    // void SoundSource::SetPlayingAttr(bool value) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetPlayingAttr(bool)", AS_METHODPR(SoundSource3D, SetPlayingAttr, (bool), void), AS_CALL_THISCALL);
    // void SoundSource::SetPlayPosition(signed char* pos) | File: ../Audio/SoundSource.h
    // Error: type "signed char*" can not automatically bind
    // void SoundSource::SetPositionAttr(int value) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetPositionAttr(int)", AS_METHODPR(SoundSource3D, SetPositionAttr, (int), void), AS_CALL_THISCALL);
    // void SoundSource3D::SetRolloffFactor(float factor) | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetRolloffFactor(float)", AS_METHODPR(SoundSource3D, SetRolloffFactor, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_rolloffFactor(float)", AS_METHODPR(SoundSource3D, SetRolloffFactor, (float), void), AS_CALL_THISCALL);
    // void SoundSource::SetSoundAttr(const ResourceRef& value) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetSoundAttr(const ResourceRef&in)", AS_METHODPR(SoundSource3D, SetSoundAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void SoundSource::SetSoundType(const String& type) | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetSoundType(const String&in)", AS_METHODPR(SoundSource3D, SetSoundType, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_soundType(const String&in)", AS_METHODPR(SoundSource3D, SetSoundType, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "void SetTemporary(bool)", AS_METHODPR(SoundSource3D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "void set_temporary(bool)", AS_METHODPR(SoundSource3D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // explicit SoundSource3D::SoundSource3D(Context* context) | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectBehaviour("SoundSource3D", asBEHAVE_FACTORY, "SoundSource3D@+ f()", AS_FUNCTION(SoundSource3D_SoundSource3D_Context), AS_CALL_CDECL);
    // void SoundSource::Stop() | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void Stop()", AS_METHODPR(SoundSource3D, Stop, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "void UnsubscribeFromAllEvents()", AS_METHODPR(SoundSource3D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(SoundSource3D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(SoundSource3D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(SoundSource3D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SoundSource3D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(SoundSource3D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void SoundSource3D::Update(float timeStep) override | File: ../Audio/SoundSource3D.h
    engine->RegisterObjectMethod("SoundSource3D", "void Update(float)", AS_METHODPR(SoundSource3D, Update, (float), void), AS_CALL_THISCALL);
    // void SoundSource::UpdateMasterGain() | File: ../Audio/SoundSource.h
    engine->RegisterObjectMethod("SoundSource3D", "void UpdateMasterGain()", AS_METHODPR(SoundSource3D, UpdateMasterGain, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SoundSource3D", "int WeakRefs() const", AS_METHODPR(SoundSource3D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundSource3D", "int get_weakRefs() const", AS_METHODPR(SoundSource3D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(SoundSource3D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(SoundSource3D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SoundSource3D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(SoundSource3D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("SoundStream", asBEHAVE_ADDREF, "void f()", AS_METHODPR(SoundStream, AddRef, (), void), AS_CALL_THISCALL);
    // virtual unsigned SoundStream::GetData(signed char* dest, unsigned numBytes)=0 | File: ../Audio/SoundStream.h
    // Error: type "signed char*" can not automatically bind
    // float SoundStream::GetFrequency() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("SoundStream", "float GetFrequency() const", AS_METHODPR(SoundStream, GetFrequency, () const, float), AS_CALL_THISCALL);
    // unsigned SoundStream::GetIntFrequency() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("SoundStream", "uint GetIntFrequency() const", AS_METHODPR(SoundStream, GetIntFrequency, () const, unsigned), AS_CALL_THISCALL);
    // unsigned SoundStream::GetSampleSize() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("SoundStream", "uint GetSampleSize() const", AS_METHODPR(SoundStream, GetSampleSize, () const, unsigned), AS_CALL_THISCALL);
    // bool SoundStream::GetStopAtEnd() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("SoundStream", "bool GetStopAtEnd() const", AS_METHODPR(SoundStream, GetStopAtEnd, () const, bool), AS_CALL_THISCALL);
    // bool SoundStream::IsSixteenBit() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("SoundStream", "bool IsSixteenBit() const", AS_METHODPR(SoundStream, IsSixteenBit, () const, bool), AS_CALL_THISCALL);
    // bool SoundStream::IsStereo() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("SoundStream", "bool IsStereo() const", AS_METHODPR(SoundStream, IsStereo, () const, bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SoundStream", "int Refs() const", AS_METHODPR(SoundStream, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundStream", "int get_refs() const", AS_METHODPR(SoundStream, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("SoundStream", asBEHAVE_RELEASE, "void f()", AS_METHODPR(SoundStream, ReleaseRef, (), void), AS_CALL_THISCALL);
    // virtual bool SoundStream::Seek(unsigned sample_number) | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("SoundStream", "bool Seek(uint)", AS_METHODPR(SoundStream, Seek, (unsigned), bool), AS_CALL_THISCALL);
    // void SoundStream::SetFormat(unsigned frequency, bool sixteenBit, bool stereo) | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("SoundStream", "void SetFormat(uint, bool, bool)", AS_METHODPR(SoundStream, SetFormat, (unsigned, bool, bool), void), AS_CALL_THISCALL);
    // void SoundStream::SetStopAtEnd(bool enable) | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("SoundStream", "void SetStopAtEnd(bool)", AS_METHODPR(SoundStream, SetStopAtEnd, (bool), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SoundStream", "int WeakRefs() const", AS_METHODPR(SoundStream, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SoundStream", "int get_weakRefs() const", AS_METHODPR(SoundStream, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Sphere", "void Clear()", AS_METHODPR(Sphere, Clear, (), void), AS_CALL_THISCALL);
    // void Sphere::Define(const Sphere& sphere) | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "void Define(const Sphere&in)", AS_METHODPR(Sphere, Define, (const Sphere&), void), AS_CALL_THISCALL);
    // void Sphere::Define(const Vector3& center, float radius) | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "void Define(const Vector3&in, float)", AS_METHODPR(Sphere, Define, (const Vector3&, float), void), AS_CALL_THISCALL);
    // void Sphere::Define(const Vector3* vertices, unsigned count) | File: ../Math/Sphere.h
    // Error: type "const Vector3*" can not automatically bind
    // void Sphere::Define(const BoundingBox& box) | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "void Define(const BoundingBox&in)", AS_METHODPR(Sphere, Define, (const BoundingBox&), void), AS_CALL_THISCALL);
    // void Sphere::Define(const Frustum& frustum) | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "void Define(const Frustum&in)", AS_METHODPR(Sphere, Define, (const Frustum&), void), AS_CALL_THISCALL);
    // void Sphere::Define(const Polyhedron& poly) | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "void Define(const Polyhedron&in)", AS_METHODPR(Sphere, Define, (const Polyhedron&), void), AS_CALL_THISCALL);
    // bool Sphere::Defined() const | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "bool Defined() const", AS_METHODPR(Sphere, Defined, () const, bool), AS_CALL_THISCALL);
    // float Sphere::Distance(const Vector3& point) const | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "float Distance(const Vector3&in) const", AS_METHODPR(Sphere, Distance, (const Vector3&) const, float), AS_CALL_THISCALL);
    // Vector3 Sphere::GetLocalPoint(float theta, float phi) const | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "Vector3 GetLocalPoint(float, float) const", AS_METHODPR(Sphere, GetLocalPoint, (float, float) const, Vector3), AS_CALL_THISCALL);
    // Vector3 Sphere::GetPoint(float theta, float phi) const | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "Vector3 GetPoint(float, float) const", AS_METHODPR(Sphere, GetPoint, (float, float) const, Vector3), AS_CALL_THISCALL);
    // Intersection Sphere::IsInside(const Vector3& point) const | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "Intersection IsInside(const Vector3&in) const", AS_METHODPR(Sphere, IsInside, (const Vector3&) const, Intersection), AS_CALL_THISCALL);
    // Intersection Sphere::IsInside(const Sphere& sphere) const | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "Intersection IsInside(const Sphere&in) const", AS_METHODPR(Sphere, IsInside, (const Sphere&) const, Intersection), AS_CALL_THISCALL);
    // Intersection Sphere::IsInside(const BoundingBox& box) const | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "Intersection IsInside(const BoundingBox&in) const", AS_METHODPR(Sphere, IsInside, (const BoundingBox&) const, Intersection), AS_CALL_THISCALL);
    // Intersection Sphere::IsInsideFast(const Sphere& sphere) const | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "Intersection IsInsideFast(const Sphere&in) const", AS_METHODPR(Sphere, IsInsideFast, (const Sphere&) const, Intersection), AS_CALL_THISCALL);
    // Intersection Sphere::IsInsideFast(const BoundingBox& box) const | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "Intersection IsInsideFast(const BoundingBox&in) const", AS_METHODPR(Sphere, IsInsideFast, (const BoundingBox&) const, Intersection), AS_CALL_THISCALL);
    // void Sphere::Merge(const Vector3& point) | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "void Merge(const Vector3&in)", AS_METHODPR(Sphere, Merge, (const Vector3&), void), AS_CALL_THISCALL);
    // void Sphere::Merge(const Vector3* vertices, unsigned count) | File: ../Math/Sphere.h
    // Error: type "const Vector3*" can not automatically bind
    // void Sphere::Merge(const BoundingBox& box) | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "void Merge(const BoundingBox&in)", AS_METHODPR(Sphere, Merge, (const BoundingBox&), void), AS_CALL_THISCALL);
    // void Sphere::Merge(const Frustum& frustum) | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "void Merge(const Frustum&in)", AS_METHODPR(Sphere, Merge, (const Frustum&), void), AS_CALL_THISCALL);
    // void Sphere::Merge(const Polyhedron& poly) | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "void Merge(const Polyhedron&in)", AS_METHODPR(Sphere, Merge, (const Polyhedron&), void), AS_CALL_THISCALL);
    // void Sphere::Merge(const Sphere& sphere) | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "void Merge(const Sphere&in)", AS_METHODPR(Sphere, Merge, (const Sphere&), void), AS_CALL_THISCALL);
    // Sphere& Sphere::operator=(const Sphere& rhs) noexcept=default | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "Sphere& opAssign(const Sphere&in)", AS_METHODPR(Sphere, operator=, (const Sphere&), Sphere&), AS_CALL_THISCALL);
    // bool Sphere::operator==(const Sphere& rhs) const | File: ../Math/Sphere.h
    engine->RegisterObjectMethod("Sphere", "bool opEquals(const Sphere&in) const", AS_METHODPR(Sphere, operator==, (const Sphere&) const, bool), AS_CALL_THISCALL);
    // Sphere::Sphere(const Sphere& sphere) noexcept=default | File: ../Math/Sphere.h
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const Sphere&in)", AS_FUNCTION_OBJFIRST(Sphere_Sphere_Sphere), AS_CALL_CDECL_OBJFIRST);
    // Sphere::Sphere(const Vector3& center, float radius) noexcept | File: ../Math/Sphere.h
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, float)", AS_FUNCTION_OBJFIRST(Sphere_Sphere_Vector3_float), AS_CALL_CDECL_OBJFIRST);
    // Sphere::Sphere(const Vector3* vertices, unsigned count) noexcept | File: ../Math/Sphere.h
    // Error: type "const Vector3*" can not automatically bind
    // explicit Sphere::Sphere(const BoundingBox& box) noexcept | File: ../Math/Sphere.h
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const BoundingBox&in)", AS_FUNCTION_OBJFIRST(Sphere_Sphere_BoundingBox), AS_CALL_CDECL_OBJFIRST);
    // explicit Sphere::Sphere(const Frustum& frustum) noexcept | File: ../Math/Sphere.h
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const Frustum&in)", AS_FUNCTION_OBJFIRST(Sphere_Sphere_Frustum), AS_CALL_CDECL_OBJFIRST);
    // explicit Sphere::Sphere(const Polyhedron& poly) noexcept | File: ../Math/Sphere.h
    engine->RegisterObjectBehaviour("Sphere", asBEHAVE_CONSTRUCT, "void f(const Polyhedron&in)", AS_FUNCTION_OBJFIRST(Sphere_Sphere_Polyhedron), AS_CALL_CDECL_OBJFIRST);
#ifdef REGISTER_MANUAL_PART_Sphere
    REGISTER_MANUAL_PART_Sphere(Sphere, "Sphere")
#endif

    // void Spline::AddKnot(const Variant& knot) | File: ../Core/Spline.h
    engine->RegisterObjectMethod("Spline", "void AddKnot(const Variant&in)", AS_METHODPR(Spline, AddKnot, (const Variant&), void), AS_CALL_THISCALL);
    // void Spline::AddKnot(const Variant& knot, unsigned index) | File: ../Core/Spline.h
    engine->RegisterObjectMethod("Spline", "void AddKnot(const Variant&in, uint)", AS_METHODPR(Spline, AddKnot, (const Variant&, unsigned), void), AS_CALL_THISCALL);
    // void Spline::Clear() | File: ../Core/Spline.h
    engine->RegisterObjectMethod("Spline", "void Clear()", AS_METHODPR(Spline, Clear, (), void), AS_CALL_THISCALL);
    // InterpolationMode Spline::GetInterpolationMode() const | File: ../Core/Spline.h
    engine->RegisterObjectMethod("Spline", "InterpolationMode GetInterpolationMode() const", AS_METHODPR(Spline, GetInterpolationMode, () const, InterpolationMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Spline", "InterpolationMode get_interpolationMode() const", AS_METHODPR(Spline, GetInterpolationMode, () const, InterpolationMode), AS_CALL_THISCALL);
    // Variant Spline::GetKnot(unsigned index) const | File: ../Core/Spline.h
    engine->RegisterObjectMethod("Spline", "Variant GetKnot(uint) const", AS_METHODPR(Spline, GetKnot, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Spline", "Variant get_knot(uint) const", AS_METHODPR(Spline, GetKnot, (unsigned) const, Variant), AS_CALL_THISCALL);
    // const VariantVector& Spline::GetKnots() const | File: ../Core/Spline.h
    // Error: type "const VariantVector&" can not automatically bind
    // Variant Spline::GetPoint(float f) const | File: ../Core/Spline.h
    engine->RegisterObjectMethod("Spline", "Variant GetPoint(float) const", AS_METHODPR(Spline, GetPoint, (float) const, Variant), AS_CALL_THISCALL);
    // Spline& Spline::operator=(const Spline& rhs)=default | File: ../Core/Spline.h
    engine->RegisterObjectMethod("Spline", "Spline& opAssign(const Spline&in)", AS_METHODPR(Spline, operator=, (const Spline&), Spline&), AS_CALL_THISCALL);
    // bool Spline::operator==(const Spline& rhs) const | File: ../Core/Spline.h
    engine->RegisterObjectMethod("Spline", "bool opEquals(const Spline&in) const", AS_METHODPR(Spline, operator==, (const Spline&) const, bool), AS_CALL_THISCALL);
    // void Spline::RemoveKnot() | File: ../Core/Spline.h
    engine->RegisterObjectMethod("Spline", "void RemoveKnot()", AS_METHODPR(Spline, RemoveKnot, (), void), AS_CALL_THISCALL);
    // void Spline::RemoveKnot(unsigned index) | File: ../Core/Spline.h
    engine->RegisterObjectMethod("Spline", "void RemoveKnot(uint)", AS_METHODPR(Spline, RemoveKnot, (unsigned), void), AS_CALL_THISCALL);
    // void Spline::SetInterpolationMode(InterpolationMode interpolationMode) | File: ../Core/Spline.h
    engine->RegisterObjectMethod("Spline", "void SetInterpolationMode(InterpolationMode)", AS_METHODPR(Spline, SetInterpolationMode, (InterpolationMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Spline", "void set_interpolationMode(InterpolationMode)", AS_METHODPR(Spline, SetInterpolationMode, (InterpolationMode), void), AS_CALL_THISCALL);
    // void Spline::SetKnot(const Variant& knot, unsigned index) | File: ../Core/Spline.h
    engine->RegisterObjectMethod("Spline", "void SetKnot(const Variant&in, uint)", AS_METHODPR(Spline, SetKnot, (const Variant&, unsigned), void), AS_CALL_THISCALL);
    // void Spline::SetKnots(const Vector<Variant>& knots) | File: ../Core/Spline.h
    // Error: type "const Vector<Variant>&" can not automatically bind
    // explicit Spline::Spline(InterpolationMode mode) | File: ../Core/Spline.h
    engine->RegisterObjectBehaviour("Spline", asBEHAVE_CONSTRUCT, "void f(InterpolationMode)", AS_FUNCTION_OBJFIRST(Spline_Spline_InterpolationMode), AS_CALL_CDECL_OBJFIRST);
    // explicit Spline::Spline(const Vector<Variant>& knots, InterpolationMode mode=BEZIER_CURVE) | File: ../Core/Spline.h
    // Error: type "const Vector<Variant>&" can not automatically bind
    // Spline::Spline(const Spline& rhs)=default | File: ../Core/Spline.h
    engine->RegisterObjectBehaviour("Spline", asBEHAVE_CONSTRUCT, "void f(const Spline&in)", AS_FUNCTION_OBJFIRST(Spline_Spline_Spline), AS_CALL_CDECL_OBJFIRST);
#ifdef REGISTER_MANUAL_PART_Spline
    REGISTER_MANUAL_PART_Spline(Spline, "Spline")
#endif

    // void SplinePath::AddControlPoint(Node* point, unsigned index=M_MAX_UNSIGNED) | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "void AddControlPoint(Node@+, uint = M_MAX_UNSIGNED)", AS_METHODPR(SplinePath, AddControlPoint, (Node*, unsigned), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("SplinePath", asBEHAVE_ADDREF, "void f()", AS_METHODPR(SplinePath, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "void AllocateNetworkState()", AS_METHODPR(SplinePath, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void SplinePath::ApplyAttributes() override | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "void ApplyAttributes()", AS_METHODPR(SplinePath, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void SplinePath::ClearControlPoints() | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "void ClearControlPoints()", AS_METHODPR(SplinePath, ClearControlPoints, (), void), AS_CALL_THISCALL);
    // void SplinePath::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(SplinePath, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "bool GetAnimationEnabled() const", AS_METHODPR(SplinePath, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "bool get_animationEnabled() const", AS_METHODPR(SplinePath, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "Variant GetAttribute(uint) const", AS_METHODPR(SplinePath, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "Variant get_attributes(uint) const", AS_METHODPR(SplinePath, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "Variant GetAttribute(const String&in) const", AS_METHODPR(SplinePath, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(SplinePath, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(SplinePath, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(SplinePath, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(SplinePath, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "Variant GetAttributeDefault(uint) const", AS_METHODPR(SplinePath, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "Variant get_attributeDefaults(uint) const", AS_METHODPR(SplinePath, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(SplinePath, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "bool GetBlockEvents() const", AS_METHODPR(SplinePath, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "const String& GetCategory() const", AS_METHODPR(SplinePath, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "const String& get_category() const", AS_METHODPR(SplinePath, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "Component@+ GetComponent(StringHash) const", AS_METHODPR(SplinePath, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // unsigned SplinePath::GetControlledIdAttr() const | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "uint GetControlledIdAttr() const", AS_METHODPR(SplinePath, GetControlledIdAttr, () const, unsigned), AS_CALL_THISCALL);
    // Node* SplinePath::GetControlledNode() const | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "Node@+ GetControlledNode() const", AS_METHODPR(SplinePath, GetControlledNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "Node@+ get_controlledNode() const", AS_METHODPR(SplinePath, GetControlledNode, () const, Node*), AS_CALL_THISCALL);
    // const VariantVector& SplinePath::GetControlPointIdsAttr() const | File: ../Scene/SplinePath.h
    // Error: type "const VariantVector&" can not automatically bind
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "VariantMap& GetEventDataMap() const", AS_METHODPR(SplinePath, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "Object@+ GetEventSender() const", AS_METHODPR(SplinePath, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(SplinePath, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(SplinePath, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "const VariantMap& GetGlobalVars() const", AS_METHODPR(SplinePath, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "const VariantMap& get_globalVars() const", AS_METHODPR(SplinePath, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "uint GetID() const", AS_METHODPR(SplinePath, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "uint get_id() const", AS_METHODPR(SplinePath, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(SplinePath, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // InterpolationMode SplinePath::GetInterpolationMode() const | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "InterpolationMode GetInterpolationMode() const", AS_METHODPR(SplinePath, GetInterpolationMode, () const, InterpolationMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "InterpolationMode get_interpolationMode() const", AS_METHODPR(SplinePath, GetInterpolationMode, () const, InterpolationMode), AS_CALL_THISCALL);
    // float SplinePath::GetLength() const | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "float GetLength() const", AS_METHODPR(SplinePath, GetLength, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "float get_length() const", AS_METHODPR(SplinePath, GetLength, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "Node@+ GetNode() const", AS_METHODPR(SplinePath, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "Node@+ get_node() const", AS_METHODPR(SplinePath, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "uint GetNumAttributes() const", AS_METHODPR(SplinePath, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "uint get_numAttributes() const", AS_METHODPR(SplinePath, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "uint GetNumNetworkAttributes() const", AS_METHODPR(SplinePath, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(SplinePath, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(SplinePath, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(SplinePath, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Vector3 SplinePath::GetPoint(float factor) const | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "Vector3 GetPoint(float) const", AS_METHODPR(SplinePath, GetPoint, (float) const, Vector3), AS_CALL_THISCALL);
    // Vector3 SplinePath::GetPosition() const | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "Vector3 GetPosition() const", AS_METHODPR(SplinePath, GetPosition, () const, Vector3), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "Scene@+ GetScene() const", AS_METHODPR(SplinePath, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // float SplinePath::GetSpeed() const | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "float GetSpeed() const", AS_METHODPR(SplinePath, GetSpeed, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "float get_speed() const", AS_METHODPR(SplinePath, GetSpeed, () const, float), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(SplinePath, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "StringHash GetType() const", AS_METHODPR(SplinePath, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "StringHash get_type() const", AS_METHODPR(SplinePath, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "const String& GetTypeName() const", AS_METHODPR(SplinePath, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "const String& get_typeName() const", AS_METHODPR(SplinePath, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "bool HasEventHandlers() const", AS_METHODPR(SplinePath, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(SplinePath, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(SplinePath, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "bool IsEnabled() const", AS_METHODPR(SplinePath, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "bool get_enabled() const", AS_METHODPR(SplinePath, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "bool IsEnabledEffective() const", AS_METHODPR(SplinePath, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "bool get_enabledEffective() const", AS_METHODPR(SplinePath, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool SplinePath::IsFinished() const | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "bool IsFinished() const", AS_METHODPR(SplinePath, IsFinished, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "bool get_isFinished() const", AS_METHODPR(SplinePath, IsFinished, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "bool IsInstanceOf(StringHash) const", AS_METHODPR(SplinePath, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "bool IsReplicated() const", AS_METHODPR(SplinePath, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "bool get_replicated() const", AS_METHODPR(SplinePath, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "bool IsTemporary() const", AS_METHODPR(SplinePath, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "bool get_temporary() const", AS_METHODPR(SplinePath, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "bool Load(Deserializer&)", AS_METHODPR(SplinePath, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(SplinePath, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "bool LoadXML(const XMLElement&in)", AS_METHODPR(SplinePath, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "void MarkNetworkUpdate()", AS_METHODPR(SplinePath, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void SplinePath::Move(float timeStep) | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "void Move(float)", AS_METHODPR(SplinePath, Move, (float), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(SplinePath, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(SplinePath, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(SplinePath, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "void OnSetEnabled()", AS_METHODPR(SplinePath, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "void PrepareNetworkUpdate()", AS_METHODPR(SplinePath, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(SplinePath, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(SplinePath, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SplinePath", "int Refs() const", AS_METHODPR(SplinePath, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "int get_refs() const", AS_METHODPR(SplinePath, Refs, () const, int), AS_CALL_THISCALL);
    // static void SplinePath::RegisterObject(Context* context) | File: ../Scene/SplinePath.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("SplinePath", asBEHAVE_RELEASE, "void f()", AS_METHODPR(SplinePath, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "void Remove()", AS_METHODPR(SplinePath, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(SplinePath, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void SplinePath::RemoveControlPoint(Node* point) | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "void RemoveControlPoint(Node@+)", AS_METHODPR(SplinePath, RemoveControlPoint, (Node*), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "void RemoveInstanceDefault()", AS_METHODPR(SplinePath, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "void RemoveObjectAnimation()", AS_METHODPR(SplinePath, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void SplinePath::Reset() | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "void Reset()", AS_METHODPR(SplinePath, Reset, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "void ResetToDefault()", AS_METHODPR(SplinePath, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "bool Save(Serializer&) const", AS_METHODPR(SplinePath, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "bool SaveDefaultAttributes() const", AS_METHODPR(SplinePath, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "bool SaveJSON(JSONValue&) const", AS_METHODPR(SplinePath, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "bool SaveXML(XMLElement&) const", AS_METHODPR(SplinePath, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "void SendEvent(StringHash)", AS_METHODPR(SplinePath, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(SplinePath, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "void SetAnimationEnabled(bool)", AS_METHODPR(SplinePath, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_animationEnabled(bool)", AS_METHODPR(SplinePath, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "void SetAnimationTime(float)", AS_METHODPR(SplinePath, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(SplinePath, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(SplinePath, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(SplinePath, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(SplinePath, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(SplinePath, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(SplinePath, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(SplinePath, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "void SetBlockEvents(bool)", AS_METHODPR(SplinePath, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void SplinePath::SetControlledIdAttr(unsigned value) | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "void SetControlledIdAttr(uint)", AS_METHODPR(SplinePath, SetControlledIdAttr, (unsigned), void), AS_CALL_THISCALL);
    // void SplinePath::SetControlledNode(Node* controlled) | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "void SetControlledNode(Node@+)", AS_METHODPR(SplinePath, SetControlledNode, (Node*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_controlledNode(Node@+)", AS_METHODPR(SplinePath, SetControlledNode, (Node*), void), AS_CALL_THISCALL);
    // void SplinePath::SetControlPointIdsAttr(const VariantVector& value) | File: ../Scene/SplinePath.h
    // Error: type "const VariantVector&" can not automatically bind
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("SplinePath", "void SetEnabled(bool)", AS_METHODPR(SplinePath, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_enabled(bool)", AS_METHODPR(SplinePath, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(SplinePath, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(SplinePath, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "void SetInstanceDefault(bool)", AS_METHODPR(SplinePath, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(SplinePath, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void SplinePath::SetInterpolationMode(InterpolationMode interpolationMode) | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "void SetInterpolationMode(InterpolationMode)", AS_METHODPR(SplinePath, SetInterpolationMode, (InterpolationMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_interpolationMode(InterpolationMode)", AS_METHODPR(SplinePath, SetInterpolationMode, (InterpolationMode), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(SplinePath, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(SplinePath, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("SplinePath", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(SplinePath, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void SplinePath::SetPosition(float factor) | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "void SetPosition(float)", AS_METHODPR(SplinePath, SetPosition, (float), void), AS_CALL_THISCALL);
    // void SplinePath::SetSpeed(float speed) | File: ../Scene/SplinePath.h
    engine->RegisterObjectMethod("SplinePath", "void SetSpeed(float)", AS_METHODPR(SplinePath, SetSpeed, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_speed(float)", AS_METHODPR(SplinePath, SetSpeed, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "void SetTemporary(bool)", AS_METHODPR(SplinePath, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_temporary(bool)", AS_METHODPR(SplinePath, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // explicit SplinePath::SplinePath(Context* context) | File: ../Scene/SplinePath.h
    engine->RegisterObjectBehaviour("SplinePath", asBEHAVE_FACTORY, "SplinePath@+ f()", AS_FUNCTION(SplinePath_SplinePath_Context), AS_CALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "void UnsubscribeFromAllEvents()", AS_METHODPR(SplinePath, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(SplinePath_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(SplinePath, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(SplinePath, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SplinePath", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(SplinePath, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SplinePath", "int WeakRefs() const", AS_METHODPR(SplinePath, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "int get_weakRefs() const", AS_METHODPR(SplinePath, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(SplinePath, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(SplinePath, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("SplinePath", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(SplinePath, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Sprite", "void AddChild(UIElement@+)", AS_METHODPR(Sprite, AddChild, (UIElement*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Sprite", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Sprite, AddRef, (), void), AS_CALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void AddTag(const String&in)", AS_METHODPR(Sprite, AddTag, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void AddTags(const String&in, int8 = ';')", AS_METHODPR(Sprite, AddTags, (const String&, char), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void AddTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(Sprite_AddTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void AdjustScissor(IntRect&)", AS_METHODPR(Sprite, AdjustScissor, (IntRect&), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "void AllocateNetworkState()", AS_METHODPR(Sprite, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void ApplyAttributes()", AS_METHODPR(Sprite, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void BringToFront()", AS_METHODPR(Sprite, BringToFront, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", AS_METHODPR(Sprite, CreateChild, (StringHash, const String&, unsigned), UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void DisableLayoutUpdate()", AS_METHODPR(Sprite, DisableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // IntVector2 Sprite::ElementToScreen(const IntVector2& position) override | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "IntVector2 ElementToScreen(const IntVector2&in)", AS_METHODPR(Sprite, ElementToScreen, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void EnableLayoutUpdate()", AS_METHODPR(Sprite, EnableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool FilterAttributes(XMLElement&) const", AS_METHODPR(Sprite, FilterAttributes, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "uint FindChild(UIElement@+) const", AS_METHODPR(Sprite, FindChild, (UIElement*) const, unsigned), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "bool GetAnimationEnabled() const", AS_METHODPR(Sprite, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_animationEnabled() const", AS_METHODPR(Sprite, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const String& GetAppliedStyle() const", AS_METHODPR(Sprite, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const String& get_style() const", AS_METHODPR(Sprite, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "Variant GetAttribute(uint) const", AS_METHODPR(Sprite, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "Variant get_attributes(uint) const", AS_METHODPR(Sprite, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "Variant GetAttribute(const String&in) const", AS_METHODPR(Sprite, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(Sprite, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(Sprite, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(Sprite, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(Sprite, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Sprite, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Sprite, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Sprite, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // void Sprite::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/Sprite.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode Sprite::GetBlendMode() const | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "BlendMode GetBlendMode() const", AS_METHODPR(Sprite, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "BlendMode get_blendMode() const", AS_METHODPR(Sprite, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "bool GetBlockEvents() const", AS_METHODPR(Sprite, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool GetBringToBack() const", AS_METHODPR(Sprite, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_bringToBack() const", AS_METHODPR(Sprite, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool GetBringToFront() const", AS_METHODPR(Sprite, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_bringToFront() const", AS_METHODPR(Sprite, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "const String& GetCategory() const", AS_METHODPR(Sprite, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const String& get_category() const", AS_METHODPR(Sprite, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "UIElement@+ GetChild(uint) const", AS_METHODPR(Sprite, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "UIElement@+ get_children(uint) const", AS_METHODPR(Sprite, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "UIElement@+ GetChild(const String&in, bool = false) const", AS_METHODPR(Sprite, GetChild, (const String&, bool) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", AS_METHODPR(Sprite, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const IntVector2& GetChildOffset() const", AS_METHODPR(Sprite, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const IntVector2& get_childOffset() const", AS_METHODPR(Sprite, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "Array<UIElement@>@ GetChildren() const", AS_FUNCTION_OBJFIRST(Sprite_GetChildren_void), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "Array<UIElement@>@ GetChildren(bool) const", AS_FUNCTION_OBJFIRST(Sprite_GetChildren_bool), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", AS_FUNCTION_OBJFIRST(Sprite_GetChildrenWithTag_String_bool), AS_CALL_CDECL_OBJFIRST);
    // template<class T> T* UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const IntRect& GetClipBorder() const", AS_METHODPR(Sprite, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const IntRect& get_clipBorder() const", AS_METHODPR(Sprite, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool GetClipChildren() const", AS_METHODPR(Sprite, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_clipChildren() const", AS_METHODPR(Sprite, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const Color& GetColor(Corner) const", AS_METHODPR(Sprite, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const Color& get_colors(Corner) const", AS_METHODPR(Sprite, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const Color& GetColorAttr() const", AS_METHODPR(Sprite, GetColorAttr, () const, const Color&), AS_CALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "IntRect GetCombinedScreenRect()", AS_METHODPR(Sprite, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "IntRect get_combinedScreenRect()", AS_METHODPR(Sprite, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "XMLFile@+ GetDefaultStyle(bool = true) const", AS_METHODPR(Sprite, GetDefaultStyle, (bool) const, XMLFile*), AS_CALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const Color& GetDerivedColor() const", AS_METHODPR(Sprite, GetDerivedColor, () const, const Color&), AS_CALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "float GetDerivedOpacity() const", AS_METHODPR(Sprite, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "float get_derivedOpacity() const", AS_METHODPR(Sprite, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "MouseButtonFlags GetDragButtonCombo() const", AS_METHODPR(Sprite, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "MouseButtonFlags get_dragButtonCombo() const", AS_METHODPR(Sprite, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "uint GetDragButtonCount() const", AS_METHODPR(Sprite, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "uint get_dragButtonCount() const", AS_METHODPR(Sprite, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "DragAndDropModeFlags GetDragDropMode() const", AS_METHODPR(Sprite, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "DragAndDropModeFlags get_dragDropMode() const", AS_METHODPR(Sprite, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "IntVector2 GetEffectiveMinSize() const", AS_METHODPR(Sprite, GetEffectiveMinSize, () const, IntVector2), AS_CALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "UIElement@+ GetElementEventSender() const", AS_METHODPR(Sprite, GetElementEventSender, () const, UIElement*), AS_CALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool GetEnableAnchor() const", AS_METHODPR(Sprite, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_enableAnchor() const", AS_METHODPR(Sprite, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "VariantMap& GetEventDataMap() const", AS_METHODPR(Sprite, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "Object@+ GetEventSender() const", AS_METHODPR(Sprite, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "FocusMode GetFocusMode() const", AS_METHODPR(Sprite, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "FocusMode get_focusMode() const", AS_METHODPR(Sprite, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Sprite, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Sprite, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Sprite, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const VariantMap& get_globalVars() const", AS_METHODPR(Sprite, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "int GetHeight() const", AS_METHODPR(Sprite, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_height() const", AS_METHODPR(Sprite, GetHeight, () const, int), AS_CALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "HorizontalAlignment GetHorizontalAlignment() const", AS_METHODPR(Sprite, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "HorizontalAlignment get_horizontalAlignment() const", AS_METHODPR(Sprite, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    // const IntVector2& Sprite::GetHotSpot() const | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "const IntVector2& GetHotSpot() const", AS_METHODPR(Sprite, GetHotSpot, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const IntVector2& get_hotSpot() const", AS_METHODPR(Sprite, GetHotSpot, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntRect& Sprite::GetImageRect() const | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "const IntRect& GetImageRect() const", AS_METHODPR(Sprite, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const IntRect& get_imageRect() const", AS_METHODPR(Sprite, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "int GetIndent() const", AS_METHODPR(Sprite, GetIndent, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_indent() const", AS_METHODPR(Sprite, GetIndent, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "int GetIndentSpacing() const", AS_METHODPR(Sprite, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_indentSpacing() const", AS_METHODPR(Sprite, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "int GetIndentWidth() const", AS_METHODPR(Sprite, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_indentWidth() const", AS_METHODPR(Sprite, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Sprite, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const IntRect& GetLayoutBorder() const", AS_METHODPR(Sprite, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const IntRect& get_layoutBorder() const", AS_METHODPR(Sprite, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "int GetLayoutElementMaxSize() const", AS_METHODPR(Sprite, GetLayoutElementMaxSize, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const Vector2& GetLayoutFlexScale() const", AS_METHODPR(Sprite, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const Vector2& get_layoutFlexScale() const", AS_METHODPR(Sprite, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "LayoutMode GetLayoutMode() const", AS_METHODPR(Sprite, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "LayoutMode get_layoutMode() const", AS_METHODPR(Sprite, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "int GetLayoutSpacing() const", AS_METHODPR(Sprite, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_layoutSpacing() const", AS_METHODPR(Sprite, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const Vector2& GetMaxAnchor() const", AS_METHODPR(Sprite, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const Vector2& get_maxAnchor() const", AS_METHODPR(Sprite, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "int GetMaxHeight() const", AS_METHODPR(Sprite, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_maxHeight() const", AS_METHODPR(Sprite, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const IntVector2& GetMaxOffset() const", AS_METHODPR(Sprite, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const IntVector2& get_maxOffset() const", AS_METHODPR(Sprite, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const IntVector2& GetMaxSize() const", AS_METHODPR(Sprite, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const IntVector2& get_maxSize() const", AS_METHODPR(Sprite, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "int GetMaxWidth() const", AS_METHODPR(Sprite, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_maxWidth() const", AS_METHODPR(Sprite, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const Vector2& GetMinAnchor() const", AS_METHODPR(Sprite, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const Vector2& get_minAnchor() const", AS_METHODPR(Sprite, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "int GetMinHeight() const", AS_METHODPR(Sprite, GetMinHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_minHeight() const", AS_METHODPR(Sprite, GetMinHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const IntVector2& GetMinOffset() const", AS_METHODPR(Sprite, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const IntVector2& get_minOffset() const", AS_METHODPR(Sprite, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const IntVector2& GetMinSize() const", AS_METHODPR(Sprite, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const IntVector2& get_minSize() const", AS_METHODPR(Sprite, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "int GetMinWidth() const", AS_METHODPR(Sprite, GetMinWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_minWidth() const", AS_METHODPR(Sprite, GetMinWidth, () const, int), AS_CALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const String& GetName() const", AS_METHODPR(Sprite, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const String& get_name() const", AS_METHODPR(Sprite, GetName, () const, const String&), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "uint GetNumAttributes() const", AS_METHODPR(Sprite, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "uint get_numAttributes() const", AS_METHODPR(Sprite, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "uint GetNumChildren(bool = false) const", AS_METHODPR(Sprite, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "uint get_numChildren(bool = false) const", AS_METHODPR(Sprite, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "uint GetNumNetworkAttributes() const", AS_METHODPR(Sprite, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(Sprite, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(Sprite, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(Sprite, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "float GetOpacity() const", AS_METHODPR(Sprite, GetOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "float get_opacity() const", AS_METHODPR(Sprite, GetOpacity, () const, float), AS_CALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "UIElement@+ GetParent() const", AS_METHODPR(Sprite, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "UIElement@+ get_parent() const", AS_METHODPR(Sprite, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const Vector2& GetPivot() const", AS_METHODPR(Sprite, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const Vector2& get_pivot() const", AS_METHODPR(Sprite, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    // const Vector2& Sprite::GetPosition() const | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "const Vector2& GetPosition() const", AS_METHODPR(Sprite, GetPosition, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const Vector2& get_position() const", AS_METHODPR(Sprite, GetPosition, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "int GetPriority() const", AS_METHODPR(Sprite, GetPriority, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_priority() const", AS_METHODPR(Sprite, GetPriority, () const, int), AS_CALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "UIElement@+ GetRoot() const", AS_METHODPR(Sprite, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "UIElement@+ get_root() const", AS_METHODPR(Sprite, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    // float Sprite::GetRotation() const | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "float GetRotation() const", AS_METHODPR(Sprite, GetRotation, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "float get_rotation() const", AS_METHODPR(Sprite, GetRotation, () const, float), AS_CALL_THISCALL);
    // const Vector2& Sprite::GetScale() const | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "const Vector2& GetScale() const", AS_METHODPR(Sprite, GetScale, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const Vector2& get_scale() const", AS_METHODPR(Sprite, GetScale, () const, const Vector2&), AS_CALL_THISCALL);
    // const IntVector2& Sprite::GetScreenPosition() const override | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "const IntVector2& GetScreenPosition() const", AS_METHODPR(Sprite, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const IntVector2& get_screenPosition() const", AS_METHODPR(Sprite, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const IntVector2& GetSize() const", AS_METHODPR(Sprite, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const IntVector2& get_size() const", AS_METHODPR(Sprite, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool GetSortChildren() const", AS_METHODPR(Sprite, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_sortChildren() const", AS_METHODPR(Sprite, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Sprite, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "Array<String>@ GetTags() const", AS_FUNCTION_OBJFIRST(Sprite_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Sprite", "Array<String>@ get_tags() const", AS_FUNCTION_OBJFIRST(Sprite_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    // Texture* Sprite::GetTexture() const | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "Texture@+ GetTexture() const", AS_METHODPR(Sprite, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "Texture@+ get_texture() const", AS_METHODPR(Sprite, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    // ResourceRef Sprite::GetTextureAttr() const | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "ResourceRef GetTextureAttr() const", AS_METHODPR(Sprite, GetTextureAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // const Matrix3x4& Sprite::GetTransform() const | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "const Matrix3x4& GetTransform() const", AS_METHODPR(Sprite, GetTransform, () const, const Matrix3x4&), AS_CALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "TraversalMode GetTraversalMode() const", AS_METHODPR(Sprite, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "TraversalMode get_traversalMode() const", AS_METHODPR(Sprite, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "StringHash GetType() const", AS_METHODPR(Sprite, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "StringHash get_type() const", AS_METHODPR(Sprite, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "const String& GetTypeName() const", AS_METHODPR(Sprite, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "const String& get_typeName() const", AS_METHODPR(Sprite, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool GetUseDerivedOpacity() const", AS_METHODPR(Sprite, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_useDerivedOpacity() const", AS_METHODPR(Sprite, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const Variant& GetVar(const StringHash&in) const", AS_METHODPR(Sprite, GetVar, (const StringHash&) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "const VariantMap& GetVars() const", AS_METHODPR(Sprite, GetVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "VerticalAlignment GetVerticalAlignment() const", AS_METHODPR(Sprite, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "VerticalAlignment get_verticalAlignment() const", AS_METHODPR(Sprite, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "int GetWidth() const", AS_METHODPR(Sprite, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_width() const", AS_METHODPR(Sprite, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool HasColorGradient() const", AS_METHODPR(Sprite, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_colorGradient() const", AS_METHODPR(Sprite, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "bool HasEventHandlers() const", AS_METHODPR(Sprite, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool HasFocus() const", AS_METHODPR(Sprite, HasFocus, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_focus() const", AS_METHODPR(Sprite, HasFocus, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Sprite, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Sprite, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool HasTag(const String&in) const", AS_METHODPR(Sprite, HasTag, (const String&) const, bool), AS_CALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void InsertChild(uint, UIElement@+)", AS_METHODPR(Sprite, InsertChild, (unsigned, UIElement*), void), AS_CALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsChildOf(UIElement@+) const", AS_METHODPR(Sprite, IsChildOf, (UIElement*) const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsEditable() const", AS_METHODPR(Sprite, IsEditable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_editable() const", AS_METHODPR(Sprite, IsEditable, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsElementEventSender() const", AS_METHODPR(Sprite, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_elementEventSender() const", AS_METHODPR(Sprite, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsEnabled() const", AS_METHODPR(Sprite, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_enabled() const", AS_METHODPR(Sprite, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsEnabledSelf() const", AS_METHODPR(Sprite, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_enabledSelf() const", AS_METHODPR(Sprite, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsFixedHeight() const", AS_METHODPR(Sprite, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_fixedHeight() const", AS_METHODPR(Sprite, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsFixedSize() const", AS_METHODPR(Sprite, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_fixedSize() const", AS_METHODPR(Sprite, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsFixedWidth() const", AS_METHODPR(Sprite, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_fixedWidth() const", AS_METHODPR(Sprite, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsHovering() const", AS_METHODPR(Sprite, IsHovering, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_hovering() const", AS_METHODPR(Sprite, IsHovering, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsInside(IntVector2, bool)", AS_METHODPR(Sprite, IsInside, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsInsideCombined(IntVector2, bool)", AS_METHODPR(Sprite, IsInsideCombined, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Sprite, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsInternal() const", AS_METHODPR(Sprite, IsInternal, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_internal() const", AS_METHODPR(Sprite, IsInternal, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsSelected() const", AS_METHODPR(Sprite, IsSelected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_selected() const", AS_METHODPR(Sprite, IsSelected, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "bool IsTemporary() const", AS_METHODPR(Sprite, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_temporary() const", AS_METHODPR(Sprite, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsVisible() const", AS_METHODPR(Sprite, IsVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_visible() const", AS_METHODPR(Sprite, IsVisible, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsVisibleEffective() const", AS_METHODPR(Sprite, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool get_visibleEffective() const", AS_METHODPR(Sprite, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool IsWheelHandler() const", AS_METHODPR(Sprite, IsWheelHandler, () const, bool), AS_CALL_THISCALL);
    // bool Sprite::IsWithinScissor(const IntRect& currentScissor) override | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "bool IsWithinScissor(const IntRect&in)", AS_METHODPR(Sprite, IsWithinScissor, (const IntRect&), bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "bool Load(Deserializer&)", AS_METHODPR(Sprite, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(Sprite, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Sprite, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Sprite, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool LoadXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(Sprite, LoadXML, (const XMLElement&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool LoadXML(Deserializer&)", AS_METHODPR(Sprite, LoadXML, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "void MarkNetworkUpdate()", AS_METHODPR(Sprite, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Sprite, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", AS_METHODPR(Sprite, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Sprite, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Sprite, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(Sprite, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool OnDragDropFinish(UIElement@+)", AS_METHODPR(Sprite, OnDragDropFinish, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool OnDragDropTest(UIElement@+)", AS_METHODPR(Sprite, OnDragDropTest, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(Sprite, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Sprite, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Sprite, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Sprite, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Sprite, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnIndentSet()", AS_METHODPR(Sprite, OnIndentSet, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", AS_METHODPR(Sprite, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // void Sprite::OnPositionSet(const IntVector2& newPosition) override | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void OnPositionSet(const IntVector2&in)", AS_METHODPR(Sprite, OnPositionSet, (const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnResize(const IntVector2&in, const IntVector2&in)", AS_METHODPR(Sprite, OnResize, (const IntVector2&, const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Sprite, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnSetEditable()", AS_METHODPR(Sprite, OnSetEditable, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnTextInput(const String&in)", AS_METHODPR(Sprite, OnTextInput, (const String&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", AS_METHODPR(Sprite, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Sprite, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Sprite, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Sprite", "int Refs() const", AS_METHODPR(Sprite, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_refs() const", AS_METHODPR(Sprite, Refs, () const, int), AS_CALL_THISCALL);
    // static void Sprite::RegisterObject(Context* context) | File: ../UI/Sprite.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Sprite", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Sprite, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void Remove()", AS_METHODPR(Sprite, Remove, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void RemoveAllChildren()", AS_METHODPR(Sprite, RemoveAllChildren, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void RemoveAllTags()", AS_METHODPR(Sprite, RemoveAllTags, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(Sprite, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void RemoveChild(UIElement@+, uint = 0)", AS_METHODPR(Sprite, RemoveChild, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void RemoveChildAtIndex(uint)", AS_METHODPR(Sprite, RemoveChildAtIndex, (unsigned), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "void RemoveInstanceDefault()", AS_METHODPR(Sprite, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "void RemoveObjectAnimation()", AS_METHODPR(Sprite, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool RemoveTag(const String&in)", AS_METHODPR(Sprite, RemoveTag, (const String&), bool), AS_CALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void ResetDeepEnabled()", AS_METHODPR(Sprite, ResetDeepEnabled, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "void ResetToDefault()", AS_METHODPR(Sprite, ResetToDefault, (), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "bool Save(Serializer&) const", AS_METHODPR(Sprite, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "bool SaveDefaultAttributes() const", AS_METHODPR(Sprite, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "bool SaveJSON(JSONValue&) const", AS_METHODPR(Sprite, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool SaveXML(XMLElement&) const", AS_METHODPR(Sprite, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool SaveXML(Serializer&, const String&in = \"\t\") const", AS_METHODPR(Sprite, SaveXML, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);
    // IntVector2 Sprite::ScreenToElement(const IntVector2& screenPosition) override | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "IntVector2 ScreenToElement(const IntVector2&in)", AS_METHODPR(Sprite, ScreenToElement, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "void SendEvent(StringHash)", AS_METHODPR(Sprite, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Sprite, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", AS_METHODPR(Sprite, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "void SetAnimationEnabled(bool)", AS_METHODPR(Sprite, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_animationEnabled(bool)", AS_METHODPR(Sprite, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "void SetAnimationTime(float)", AS_METHODPR(Sprite, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Sprite, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Sprite, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Sprite, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Sprite, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(Sprite, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(Sprite, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Sprite, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Sprite::SetBlendMode(BlendMode mode) | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetBlendMode(BlendMode)", AS_METHODPR(Sprite, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_blendMode(BlendMode)", AS_METHODPR(Sprite, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "void SetBlockEvents(bool)", AS_METHODPR(Sprite, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetBringToBack(bool)", AS_METHODPR(Sprite, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_bringToBack(bool)", AS_METHODPR(Sprite, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetBringToFront(bool)", AS_METHODPR(Sprite, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_bringToFront(bool)", AS_METHODPR(Sprite, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetChildOffset(const IntVector2&in)", AS_METHODPR(Sprite, SetChildOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetClipBorder(const IntRect&in)", AS_METHODPR(Sprite, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_clipBorder(const IntRect&in)", AS_METHODPR(Sprite, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetClipChildren(bool)", AS_METHODPR(Sprite, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_clipChildren(bool)", AS_METHODPR(Sprite, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetColor(const Color&in)", AS_METHODPR(Sprite, SetColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_color(const Color&in)", AS_METHODPR(Sprite, SetColor, (const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetColor(Corner, const Color&in)", AS_METHODPR(Sprite, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_colors(Corner, const Color&in)", AS_METHODPR(Sprite, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetDeepEnabled(bool)", AS_METHODPR(Sprite, SetDeepEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetDefaultStyle(XMLFile@+)", AS_METHODPR(Sprite, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_defaultStyle(XMLFile@+)", AS_METHODPR(Sprite, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetDragDropMode(DragAndDropModeFlags)", AS_METHODPR(Sprite, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_dragDropMode(DragAndDropModeFlags)", AS_METHODPR(Sprite, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetEditable(bool)", AS_METHODPR(Sprite, SetEditable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_editable(bool)", AS_METHODPR(Sprite, SetEditable, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetElementEventSender(bool)", AS_METHODPR(Sprite, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_elementEventSender(bool)", AS_METHODPR(Sprite, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetEnableAnchor(bool)", AS_METHODPR(Sprite, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_enableAnchor(bool)", AS_METHODPR(Sprite, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetEnabled(bool)", AS_METHODPR(Sprite, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_enabled(bool)", AS_METHODPR(Sprite, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetEnabledRecursive(bool)", AS_METHODPR(Sprite, SetEnabledRecursive, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetFixedHeight(int)", AS_METHODPR(Sprite, SetFixedHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetFixedSize(const IntVector2&in)", AS_METHODPR(Sprite, SetFixedSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetFixedSize(int, int)", AS_METHODPR(Sprite, SetFixedSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetFixedWidth(int)", AS_METHODPR(Sprite, SetFixedWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetFocus(bool)", AS_METHODPR(Sprite, SetFocus, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_focus(bool)", AS_METHODPR(Sprite, SetFocus, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetFocusMode(FocusMode)", AS_METHODPR(Sprite, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_focusMode(FocusMode)", AS_METHODPR(Sprite, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    // void Sprite::SetFullImageRect() | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetFullImageRect()", AS_METHODPR(Sprite, SetFullImageRect, (), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Sprite, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Sprite, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetHeight(int)", AS_METHODPR(Sprite, SetHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_height(int)", AS_METHODPR(Sprite, SetHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetHorizontalAlignment(HorizontalAlignment)", AS_METHODPR(Sprite, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_horizontalAlignment(HorizontalAlignment)", AS_METHODPR(Sprite, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    // void Sprite::SetHotSpot(const IntVector2& hotSpot) | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetHotSpot(const IntVector2&in)", AS_METHODPR(Sprite, SetHotSpot, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_hotSpot(const IntVector2&in)", AS_METHODPR(Sprite, SetHotSpot, (const IntVector2&), void), AS_CALL_THISCALL);
    // void Sprite::SetHotSpot(int x, int y) | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetHotSpot(int, int)", AS_METHODPR(Sprite, SetHotSpot, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetHovering(bool)", AS_METHODPR(Sprite, SetHovering, (bool), void), AS_CALL_THISCALL);
    // void Sprite::SetImageRect(const IntRect& rect) | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetImageRect(const IntRect&in)", AS_METHODPR(Sprite, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_imageRect(const IntRect&in)", AS_METHODPR(Sprite, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetIndent(int)", AS_METHODPR(Sprite, SetIndent, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_indent(int)", AS_METHODPR(Sprite, SetIndent, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetIndentSpacing(int)", AS_METHODPR(Sprite, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_indentSpacing(int)", AS_METHODPR(Sprite, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "void SetInstanceDefault(bool)", AS_METHODPR(Sprite, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Sprite, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetInternal(bool)", AS_METHODPR(Sprite, SetInternal, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_internal(bool)", AS_METHODPR(Sprite, SetInternal, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", AS_METHODPR(Sprite, SetLayout, (LayoutMode, int, const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetLayoutBorder(const IntRect&in)", AS_METHODPR(Sprite, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_layoutBorder(const IntRect&in)", AS_METHODPR(Sprite, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetLayoutFlexScale(const Vector2&in)", AS_METHODPR(Sprite, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_layoutFlexScale(const Vector2&in)", AS_METHODPR(Sprite, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetLayoutMode(LayoutMode)", AS_METHODPR(Sprite, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_layoutMode(LayoutMode)", AS_METHODPR(Sprite, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetLayoutSpacing(int)", AS_METHODPR(Sprite, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_layoutSpacing(int)", AS_METHODPR(Sprite, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMaxAnchor(const Vector2&in)", AS_METHODPR(Sprite, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_maxAnchor(const Vector2&in)", AS_METHODPR(Sprite, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMaxAnchor(float, float)", AS_METHODPR(Sprite, SetMaxAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMaxHeight(int)", AS_METHODPR(Sprite, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_maxHeight(int)", AS_METHODPR(Sprite, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMaxOffset(const IntVector2&in)", AS_METHODPR(Sprite, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_maxOffset(const IntVector2&in)", AS_METHODPR(Sprite, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMaxSize(const IntVector2&in)", AS_METHODPR(Sprite, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_maxSize(const IntVector2&in)", AS_METHODPR(Sprite, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMaxSize(int, int)", AS_METHODPR(Sprite, SetMaxSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMaxWidth(int)", AS_METHODPR(Sprite, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_maxWidth(int)", AS_METHODPR(Sprite, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMinAnchor(const Vector2&in)", AS_METHODPR(Sprite, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_minAnchor(const Vector2&in)", AS_METHODPR(Sprite, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMinAnchor(float, float)", AS_METHODPR(Sprite, SetMinAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMinHeight(int)", AS_METHODPR(Sprite, SetMinHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_minHeight(int)", AS_METHODPR(Sprite, SetMinHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMinOffset(const IntVector2&in)", AS_METHODPR(Sprite, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_minOffset(const IntVector2&in)", AS_METHODPR(Sprite, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMinSize(const IntVector2&in)", AS_METHODPR(Sprite, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_minSize(const IntVector2&in)", AS_METHODPR(Sprite, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMinSize(int, int)", AS_METHODPR(Sprite, SetMinSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetMinWidth(int)", AS_METHODPR(Sprite, SetMinWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_minWidth(int)", AS_METHODPR(Sprite, SetMinWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetName(const String&in)", AS_METHODPR(Sprite, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_name(const String&in)", AS_METHODPR(Sprite, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(Sprite, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(Sprite, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Sprite", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(Sprite, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetOpacity(float)", AS_METHODPR(Sprite, SetOpacity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_opacity(float)", AS_METHODPR(Sprite, SetOpacity, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", AS_METHODPR(Sprite, SetParent, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetPivot(const Vector2&in)", AS_METHODPR(Sprite, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_pivot(const Vector2&in)", AS_METHODPR(Sprite, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetPivot(float, float)", AS_METHODPR(Sprite, SetPivot, (float, float), void), AS_CALL_THISCALL);
    // void Sprite::SetPosition(const Vector2& position) | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetPosition(const Vector2&in)", AS_METHODPR(Sprite, SetPosition, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_position(const Vector2&in)", AS_METHODPR(Sprite, SetPosition, (const Vector2&), void), AS_CALL_THISCALL);
    // void Sprite::SetPosition(float x, float y) | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetPosition(float, float)", AS_METHODPR(Sprite, SetPosition, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetPriority(int)", AS_METHODPR(Sprite, SetPriority, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_priority(int)", AS_METHODPR(Sprite, SetPriority, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetRenderTexture(Texture2D@+)", AS_METHODPR(Sprite, SetRenderTexture, (Texture2D*), void), AS_CALL_THISCALL);
    // void Sprite::SetRotation(float angle) | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetRotation(float)", AS_METHODPR(Sprite, SetRotation, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_rotation(float)", AS_METHODPR(Sprite, SetRotation, (float), void), AS_CALL_THISCALL);
    // void Sprite::SetScale(const Vector2& scale) | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetScale(const Vector2&in)", AS_METHODPR(Sprite, SetScale, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_scale(const Vector2&in)", AS_METHODPR(Sprite, SetScale, (const Vector2&), void), AS_CALL_THISCALL);
    // void Sprite::SetScale(float x, float y) | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetScale(float, float)", AS_METHODPR(Sprite, SetScale, (float, float), void), AS_CALL_THISCALL);
    // void Sprite::SetScale(float scale) | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetScale(float)", AS_METHODPR(Sprite, SetScale, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetSelected(bool)", AS_METHODPR(Sprite, SetSelected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_selected(bool)", AS_METHODPR(Sprite, SetSelected, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetSize(const IntVector2&in)", AS_METHODPR(Sprite, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_size(const IntVector2&in)", AS_METHODPR(Sprite, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetSize(int, int)", AS_METHODPR(Sprite, SetSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetSortChildren(bool)", AS_METHODPR(Sprite, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_sortChildren(bool)", AS_METHODPR(Sprite, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool SetStyle(const String&in, XMLFile@+ = null)", AS_METHODPR(Sprite, SetStyle, (const String&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool SetStyle(const XMLElement&in)", AS_METHODPR(Sprite, SetStyle, (const XMLElement&), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "bool SetStyleAuto(XMLFile@+ = null)", AS_METHODPR(Sprite, SetStyleAuto, (XMLFile*), bool), AS_CALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(Sprite_SetTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "void SetTemporary(bool)", AS_METHODPR(Sprite, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_temporary(bool)", AS_METHODPR(Sprite, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Sprite::SetTexture(Texture* texture) | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetTexture(Texture@+)", AS_METHODPR(Sprite, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_texture(Texture@+)", AS_METHODPR(Sprite, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    // void Sprite::SetTextureAttr(const ResourceRef& value) | File: ../UI/Sprite.h
    engine->RegisterObjectMethod("Sprite", "void SetTextureAttr(const ResourceRef&in)", AS_METHODPR(Sprite, SetTextureAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetTraversalMode(TraversalMode)", AS_METHODPR(Sprite, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_traversalMode(TraversalMode)", AS_METHODPR(Sprite, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetUseDerivedOpacity(bool)", AS_METHODPR(Sprite, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_useDerivedOpacity(bool)", AS_METHODPR(Sprite, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetVar(StringHash, const Variant&in)", AS_METHODPR(Sprite, SetVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetVerticalAlignment(VerticalAlignment)", AS_METHODPR(Sprite, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_verticalAlignment(VerticalAlignment)", AS_METHODPR(Sprite, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetVisible(bool)", AS_METHODPR(Sprite, SetVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_visible(bool)", AS_METHODPR(Sprite, SetVisible, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SetWidth(int)", AS_METHODPR(Sprite, SetWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "void set_width(int)", AS_METHODPR(Sprite, SetWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void SortChildren()", AS_METHODPR(Sprite, SortChildren, (), void), AS_CALL_THISCALL);
    // explicit Sprite::Sprite(Context* context) | File: ../UI/Sprite.h
    engine->RegisterObjectBehaviour("Sprite", asBEHAVE_FACTORY, "Sprite@+ f()", AS_FUNCTION(Sprite_Sprite_Context), AS_CALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "void UnsubscribeFromAllEvents()", AS_METHODPR(Sprite, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Sprite_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Sprite, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Sprite, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Sprite, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void UIElement::Update(float timeStep) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void Update(float)", AS_METHODPR(Sprite, Update, (float), void), AS_CALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Sprite", "void UpdateLayout()", AS_METHODPR(Sprite, UpdateLayout, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Sprite", "int WeakRefs() const", AS_METHODPR(Sprite, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite", "int get_weakRefs() const", AS_METHODPR(Sprite, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Sprite, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Sprite, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Sprite", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Sprite, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("Sprite2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Sprite2D, AddRef, (), void), AS_CALL_THISCALL);
    // bool Sprite2D::BeginLoad(Deserializer& source) override | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "bool BeginLoad(Deserializer&)", AS_METHODPR(Sprite2D, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool Sprite2D::EndLoad() override | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "bool EndLoad()", AS_METHODPR(Sprite2D, EndLoad, (), bool), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(Sprite2D, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "bool GetBlockEvents() const", AS_METHODPR(Sprite2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "const String& GetCategory() const", AS_METHODPR(Sprite2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "const String& get_category() const", AS_METHODPR(Sprite2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // bool Sprite2D::GetDrawRectangle(Rect& rect, bool flipX=false, bool flipY=false) const | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "bool GetDrawRectangle(Rect&, bool = false, bool = false) const", AS_METHODPR(Sprite2D, GetDrawRectangle, (Rect&, bool, bool) const, bool), AS_CALL_THISCALL);
    // bool Sprite2D::GetDrawRectangle(Rect& rect, const Vector2& hotSpot, bool flipX=false, bool flipY=false) const | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "bool GetDrawRectangle(Rect&, const Vector2&in, bool = false, bool = false) const", AS_METHODPR(Sprite2D, GetDrawRectangle, (Rect&, const Vector2&, bool, bool) const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(Sprite2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "Object@+ GetEventSender() const", AS_METHODPR(Sprite2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Sprite2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Sprite2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Sprite2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "const VariantMap& get_globalVars() const", AS_METHODPR(Sprite2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // const Vector2& Sprite2D::GetHotSpot() const | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "const Vector2& GetHotSpot() const", AS_METHODPR(Sprite2D, GetHotSpot, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "const Vector2& get_hotSpot() const", AS_METHODPR(Sprite2D, GetHotSpot, () const, const Vector2&), AS_CALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "uint GetMemoryUse() const", AS_METHODPR(Sprite2D, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "uint get_memoryUse() const", AS_METHODPR(Sprite2D, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "const String& GetName() const", AS_METHODPR(Sprite2D, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "const String& get_name() const", AS_METHODPR(Sprite2D, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "StringHash GetNameHash() const", AS_METHODPR(Sprite2D, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // const IntVector2& Sprite2D::GetOffset() const | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "const IntVector2& GetOffset() const", AS_METHODPR(Sprite2D, GetOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "const IntVector2& get_offset() const", AS_METHODPR(Sprite2D, GetOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntRect& Sprite2D::GetRectangle() const | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "const IntRect& GetRectangle() const", AS_METHODPR(Sprite2D, GetRectangle, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "const IntRect& get_rectangle() const", AS_METHODPR(Sprite2D, GetRectangle, () const, const IntRect&), AS_CALL_THISCALL);
    // SpriteSheet2D* Sprite2D::GetSpriteSheet() const | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "SpriteSheet2D@+ GetSpriteSheet() const", AS_METHODPR(Sprite2D, GetSpriteSheet, () const, SpriteSheet2D*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Sprite2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // Texture2D* Sprite2D::GetTexture() const | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "Texture2D@+ GetTexture() const", AS_METHODPR(Sprite2D, GetTexture, () const, Texture2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "Texture2D@+ get_texture() const", AS_METHODPR(Sprite2D, GetTexture, () const, Texture2D*), AS_CALL_THISCALL);
    // float Sprite2D::GetTextureEdgeOffset() const | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "float GetTextureEdgeOffset() const", AS_METHODPR(Sprite2D, GetTextureEdgeOffset, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "float get_textureEdgeOffset() const", AS_METHODPR(Sprite2D, GetTextureEdgeOffset, () const, float), AS_CALL_THISCALL);
    // bool Sprite2D::GetTextureRectangle(Rect& rect, bool flipX=false, bool flipY=false) const | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "bool GetTextureRectangle(Rect&, bool = false, bool = false) const", AS_METHODPR(Sprite2D, GetTextureRectangle, (Rect&, bool, bool) const, bool), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "StringHash GetType() const", AS_METHODPR(Sprite2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "StringHash get_type() const", AS_METHODPR(Sprite2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "const String& GetTypeName() const", AS_METHODPR(Sprite2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "const String& get_typeName() const", AS_METHODPR(Sprite2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "uint GetUseTimer()", AS_METHODPR(Sprite2D, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "uint get_useTimer()", AS_METHODPR(Sprite2D, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "bool HasEventHandlers() const", AS_METHODPR(Sprite2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Sprite2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Sprite2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Sprite2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "bool Load(Deserializer&)", AS_METHODPR(Sprite2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "bool LoadFile(const String&in)", AS_METHODPR(Sprite2D, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "bool Load(const String&in)", AS_METHODPR(Sprite2D, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // static Sprite2D* Sprite2D::LoadFromResourceRef(Object* object, const ResourceRef& value) | File: ../Urho2D/Sprite2D.h
    engine->SetDefaultNamespace("Sprite2D");
    engine->RegisterGlobalFunction("Sprite2D@+ LoadFromResourceRef(Object@+, const ResourceRef&in)", AS_FUNCTIONPR(Sprite2D::LoadFromResourceRef, (Object*, const ResourceRef&), Sprite2D*), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Sprite2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Sprite2D", "int Refs() const", AS_METHODPR(Sprite2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "int get_refs() const", AS_METHODPR(Sprite2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void Sprite2D::RegisterObject(Context* context) | File: ../Urho2D/Sprite2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Sprite2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Sprite2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "void ResetUseTimer()", AS_METHODPR(Sprite2D, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "bool Save(Serializer&) const", AS_METHODPR(Sprite2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "bool SaveFile(const String&in) const", AS_METHODPR(Sprite2D, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "bool Save(const String&in) const", AS_METHODPR(Sprite2D, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // static ResourceRef Sprite2D::SaveToResourceRef(Sprite2D* sprite) | File: ../Urho2D/Sprite2D.h
    engine->SetDefaultNamespace("Sprite2D");
    engine->RegisterGlobalFunction("ResourceRef SaveToResourceRef(Sprite2D@+)", AS_FUNCTIONPR(Sprite2D::SaveToResourceRef, (Sprite2D*), ResourceRef), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "void SendEvent(StringHash)", AS_METHODPR(Sprite2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Sprite2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(Sprite2D, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "void SetBlockEvents(bool)", AS_METHODPR(Sprite2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Sprite2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Sprite2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Sprite2D::SetHotSpot(const Vector2& hotSpot) | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "void SetHotSpot(const Vector2&in)", AS_METHODPR(Sprite2D, SetHotSpot, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "void set_hotSpot(const Vector2&in)", AS_METHODPR(Sprite2D, SetHotSpot, (const Vector2&), void), AS_CALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "void SetMemoryUse(uint)", AS_METHODPR(Sprite2D, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Sprite2D", "void SetName(const String&in)", AS_METHODPR(Sprite2D, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "void set_name(const String&in)", AS_METHODPR(Sprite2D, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Sprite2D::SetOffset(const IntVector2& offset) | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "void SetOffset(const IntVector2&in)", AS_METHODPR(Sprite2D, SetOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "void set_offset(const IntVector2&in)", AS_METHODPR(Sprite2D, SetOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void Sprite2D::SetRectangle(const IntRect& rectangle) | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "void SetRectangle(const IntRect&in)", AS_METHODPR(Sprite2D, SetRectangle, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "void set_rectangle(const IntRect&in)", AS_METHODPR(Sprite2D, SetRectangle, (const IntRect&), void), AS_CALL_THISCALL);
    // void Sprite2D::SetSpriteSheet(SpriteSheet2D* spriteSheet) | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "void SetSpriteSheet(SpriteSheet2D@+)", AS_METHODPR(Sprite2D, SetSpriteSheet, (SpriteSheet2D*), void), AS_CALL_THISCALL);
    // void Sprite2D::SetTexture(Texture2D* texture) | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "void SetTexture(Texture2D@+)", AS_METHODPR(Sprite2D, SetTexture, (Texture2D*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "void set_texture(Texture2D@+)", AS_METHODPR(Sprite2D, SetTexture, (Texture2D*), void), AS_CALL_THISCALL);
    // void Sprite2D::SetTextureEdgeOffset(float offset) | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectMethod("Sprite2D", "void SetTextureEdgeOffset(float)", AS_METHODPR(Sprite2D, SetTextureEdgeOffset, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "void set_textureEdgeOffset(float)", AS_METHODPR(Sprite2D, SetTextureEdgeOffset, (float), void), AS_CALL_THISCALL);
    // explicit Sprite2D::Sprite2D(Context* context) | File: ../Urho2D/Sprite2D.h
    engine->RegisterObjectBehaviour("Sprite2D", asBEHAVE_FACTORY, "Sprite2D@+ f()", AS_FUNCTION(Sprite2D_Sprite2D_Context), AS_CALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(Sprite2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Sprite2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Sprite2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Sprite2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Sprite2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Sprite2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Sprite2D", "int WeakRefs() const", AS_METHODPR(Sprite2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "int get_weakRefs() const", AS_METHODPR(Sprite2D, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("SpriteSheet2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(SpriteSheet2D, AddRef, (), void), AS_CALL_THISCALL);
    // bool SpriteSheet2D::BeginLoad(Deserializer& source) override | File: ../Urho2D/SpriteSheet2D.h
    engine->RegisterObjectMethod("SpriteSheet2D", "bool BeginLoad(Deserializer&)", AS_METHODPR(SpriteSheet2D, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void SpriteSheet2D::DefineSprite(const String& name, const IntRect& rectangle, const Vector2& hotSpot=Vector2(0.5f, 0.5f), const IntVector2& offset=IntVector2::ZERO) | File: ../Urho2D/SpriteSheet2D.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void DefineSprite(const String&in, const IntRect&in, const Vector2&in = Vector2(0.5f, 0.5f), const IntVector2&in = IntVector2::ZERO)", AS_METHODPR(SpriteSheet2D, DefineSprite, (const String&, const IntRect&, const Vector2&, const IntVector2&), void), AS_CALL_THISCALL);
    // bool SpriteSheet2D::EndLoad() override | File: ../Urho2D/SpriteSheet2D.h
    engine->RegisterObjectMethod("SpriteSheet2D", "bool EndLoad()", AS_METHODPR(SpriteSheet2D, EndLoad, (), bool), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(SpriteSheet2D, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "bool GetBlockEvents() const", AS_METHODPR(SpriteSheet2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "const String& GetCategory() const", AS_METHODPR(SpriteSheet2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "const String& get_category() const", AS_METHODPR(SpriteSheet2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(SpriteSheet2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "Object@+ GetEventSender() const", AS_METHODPR(SpriteSheet2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(SpriteSheet2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(SpriteSheet2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(SpriteSheet2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "const VariantMap& get_globalVars() const", AS_METHODPR(SpriteSheet2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "uint GetMemoryUse() const", AS_METHODPR(SpriteSheet2D, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "uint get_memoryUse() const", AS_METHODPR(SpriteSheet2D, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "const String& GetName() const", AS_METHODPR(SpriteSheet2D, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "const String& get_name() const", AS_METHODPR(SpriteSheet2D, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "StringHash GetNameHash() const", AS_METHODPR(SpriteSheet2D, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // Sprite2D* SpriteSheet2D::GetSprite(const String& name) const | File: ../Urho2D/SpriteSheet2D.h
    engine->RegisterObjectMethod("SpriteSheet2D", "Sprite2D@+ GetSprite(const String&in) const", AS_METHODPR(SpriteSheet2D, GetSprite, (const String&) const, Sprite2D*), AS_CALL_THISCALL);
    // const HashMap<String, SharedPtr<Sprite2D>>& SpriteSheet2D::GetSpriteMapping() const | File: ../Urho2D/SpriteSheet2D.h
    // Error: type "const HashMap<String, SharedPtr<Sprite2D>>&" can not automatically bind
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(SpriteSheet2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // Texture2D* SpriteSheet2D::GetTexture() const | File: ../Urho2D/SpriteSheet2D.h
    engine->RegisterObjectMethod("SpriteSheet2D", "Texture2D@+ GetTexture() const", AS_METHODPR(SpriteSheet2D, GetTexture, () const, Texture2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "Texture2D@+ get_texture() const", AS_METHODPR(SpriteSheet2D, GetTexture, () const, Texture2D*), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "StringHash GetType() const", AS_METHODPR(SpriteSheet2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "StringHash get_type() const", AS_METHODPR(SpriteSheet2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "const String& GetTypeName() const", AS_METHODPR(SpriteSheet2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "const String& get_typeName() const", AS_METHODPR(SpriteSheet2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "uint GetUseTimer()", AS_METHODPR(SpriteSheet2D, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "uint get_useTimer()", AS_METHODPR(SpriteSheet2D, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "bool HasEventHandlers() const", AS_METHODPR(SpriteSheet2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(SpriteSheet2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(SpriteSheet2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(SpriteSheet2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "bool Load(Deserializer&)", AS_METHODPR(SpriteSheet2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "bool LoadFile(const String&in)", AS_METHODPR(SpriteSheet2D, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "bool Load(const String&in)", AS_METHODPR(SpriteSheet2D, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(SpriteSheet2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SpriteSheet2D", "int Refs() const", AS_METHODPR(SpriteSheet2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "int get_refs() const", AS_METHODPR(SpriteSheet2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void SpriteSheet2D::RegisterObject(Context* context) | File: ../Urho2D/SpriteSheet2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("SpriteSheet2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(SpriteSheet2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void ResetUseTimer()", AS_METHODPR(SpriteSheet2D, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "bool Save(Serializer&) const", AS_METHODPR(SpriteSheet2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "bool SaveFile(const String&in) const", AS_METHODPR(SpriteSheet2D, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "bool Save(const String&in) const", AS_METHODPR(SpriteSheet2D, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void SendEvent(StringHash)", AS_METHODPR(SpriteSheet2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(SpriteSheet2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(SpriteSheet2D, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void SetBlockEvents(bool)", AS_METHODPR(SpriteSheet2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(SpriteSheet2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(SpriteSheet2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void SetMemoryUse(uint)", AS_METHODPR(SpriteSheet2D, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void SetName(const String&in)", AS_METHODPR(SpriteSheet2D, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "void set_name(const String&in)", AS_METHODPR(SpriteSheet2D, SetName, (const String&), void), AS_CALL_THISCALL);
    // void SpriteSheet2D::SetTexture(Texture2D* texture) | File: ../Urho2D/SpriteSheet2D.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void SetTexture(Texture2D@+)", AS_METHODPR(SpriteSheet2D, SetTexture, (Texture2D*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "void set_texture(Texture2D@+)", AS_METHODPR(SpriteSheet2D, SetTexture, (Texture2D*), void), AS_CALL_THISCALL);
    // explicit SpriteSheet2D::SpriteSheet2D(Context* context) | File: ../Urho2D/SpriteSheet2D.h
    engine->RegisterObjectBehaviour("SpriteSheet2D", asBEHAVE_FACTORY, "SpriteSheet2D@+ f()", AS_FUNCTION(SpriteSheet2D_SpriteSheet2D_Context), AS_CALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(SpriteSheet2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(SpriteSheet2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(SpriteSheet2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(SpriteSheet2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("SpriteSheet2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(SpriteSheet2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("SpriteSheet2D", "int WeakRefs() const", AS_METHODPR(SpriteSheet2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "int get_weakRefs() const", AS_METHODPR(SpriteSheet2D, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("StaticModel", "void AddLight(Light@+)", AS_METHODPR(StaticModel, AddLight, (Light*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("StaticModel", asBEHAVE_ADDREF, "void f()", AS_METHODPR(StaticModel, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void AddVertexLight(Light@+)", AS_METHODPR(StaticModel, AddVertexLight, (Light*), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "void AllocateNetworkState()", AS_METHODPR(StaticModel, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "void ApplyAttributes()", AS_METHODPR(StaticModel, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void StaticModel::ApplyMaterialList(const String& fileName=String::EMPTY) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "void ApplyMaterialList(const String&in = String::EMPTY)", AS_METHODPR(StaticModel, ApplyMaterialList, (const String&), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(StaticModel, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool StaticModel::DrawOcclusion(OcclusionBuffer* buffer) override | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "bool DrawOcclusion(OcclusionBuffer@+)", AS_METHODPR(StaticModel, DrawOcclusion, (OcclusionBuffer*), bool), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "bool GetAnimationEnabled() const", AS_METHODPR(StaticModel, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "bool get_animationEnabled() const", AS_METHODPR(StaticModel, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "Variant GetAttribute(uint) const", AS_METHODPR(StaticModel, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "Variant get_attributes(uint) const", AS_METHODPR(StaticModel, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "Variant GetAttribute(const String&in) const", AS_METHODPR(StaticModel, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(StaticModel, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(StaticModel, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(StaticModel, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(StaticModel, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "Variant GetAttributeDefault(uint) const", AS_METHODPR(StaticModel, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "Variant get_attributeDefaults(uint) const", AS_METHODPR(StaticModel, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(StaticModel, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "bool GetBlockEvents() const", AS_METHODPR(StaticModel, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "const BoundingBox& GetBoundingBox() const", AS_METHODPR(StaticModel, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "const BoundingBox& get_boundingBox() const", AS_METHODPR(StaticModel, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "bool GetCastShadows() const", AS_METHODPR(StaticModel, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "bool get_castShadows() const", AS_METHODPR(StaticModel, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "const String& GetCategory() const", AS_METHODPR(StaticModel, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "const String& get_category() const", AS_METHODPR(StaticModel, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "Component@+ GetComponent(StringHash) const", AS_METHODPR(StaticModel, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("StaticModel", "float GetDistance() const", AS_METHODPR(StaticModel, GetDistance, () const, float), AS_CALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "uint8 GetDrawableFlags() const", AS_METHODPR(StaticModel, GetDrawableFlags, () const, unsigned char), AS_CALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "float GetDrawDistance() const", AS_METHODPR(StaticModel, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "float get_drawDistance() const", AS_METHODPR(StaticModel, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "VariantMap& GetEventDataMap() const", AS_METHODPR(StaticModel, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "Object@+ GetEventSender() const", AS_METHODPR(StaticModel, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "Light@+ GetFirstLight() const", AS_METHODPR(StaticModel, GetFirstLight, () const, Light*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(StaticModel, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(StaticModel, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "const VariantMap& GetGlobalVars() const", AS_METHODPR(StaticModel, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "const VariantMap& get_globalVars() const", AS_METHODPR(StaticModel, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "uint GetID() const", AS_METHODPR(StaticModel, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "uint get_id() const", AS_METHODPR(StaticModel, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(StaticModel, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "uint GetLightMask() const", AS_METHODPR(StaticModel, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "uint get_lightMask() const", AS_METHODPR(StaticModel, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "Array<Light@>@ GetLights() const", AS_FUNCTION_OBJFIRST(StaticModel_GetLights_void), AS_CALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "float GetLodBias() const", AS_METHODPR(StaticModel, GetLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "float get_lodBias() const", AS_METHODPR(StaticModel, GetLodBias, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "float GetLodDistance() const", AS_METHODPR(StaticModel, GetLodDistance, () const, float), AS_CALL_THISCALL);
    // Geometry* StaticModel::GetLodGeometry(unsigned batchIndex, unsigned level) override | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "Geometry@+ GetLodGeometry(uint, uint)", AS_METHODPR(StaticModel, GetLodGeometry, (unsigned, unsigned), Geometry*), AS_CALL_THISCALL);
    // virtual Material* StaticModel::GetMaterial() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "Material@+ GetMaterial() const", AS_METHODPR(StaticModel, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "Material@+ get_material() const", AS_METHODPR(StaticModel, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    // virtual Material* StaticModel::GetMaterial(unsigned index) const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "Material@+ GetMaterial(uint) const", AS_METHODPR(StaticModel, GetMaterial, (unsigned) const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "Material@+ get_materials(uint) const", AS_METHODPR(StaticModel, GetMaterial, (unsigned) const, Material*), AS_CALL_THISCALL);
    // const ResourceRefList& StaticModel::GetMaterialsAttr() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "const ResourceRefList& GetMaterialsAttr() const", AS_METHODPR(StaticModel, GetMaterialsAttr, () const, const ResourceRefList&), AS_CALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "uint GetMaxLights() const", AS_METHODPR(StaticModel, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "uint get_maxLights() const", AS_METHODPR(StaticModel, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "float GetMaxZ() const", AS_METHODPR(StaticModel, GetMaxZ, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "float GetMinZ() const", AS_METHODPR(StaticModel, GetMinZ, () const, float), AS_CALL_THISCALL);
    // Model* StaticModel::GetModel() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "Model@+ GetModel() const", AS_METHODPR(StaticModel, GetModel, () const, Model*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "Model@+ get_model() const", AS_METHODPR(StaticModel, GetModel, () const, Model*), AS_CALL_THISCALL);
    // ResourceRef StaticModel::GetModelAttr() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "ResourceRef GetModelAttr() const", AS_METHODPR(StaticModel, GetModelAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "Node@+ GetNode() const", AS_METHODPR(StaticModel, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "Node@+ get_node() const", AS_METHODPR(StaticModel, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "uint GetNumAttributes() const", AS_METHODPR(StaticModel, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "uint get_numAttributes() const", AS_METHODPR(StaticModel, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned StaticModel::GetNumGeometries() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "uint GetNumGeometries() const", AS_METHODPR(StaticModel, GetNumGeometries, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "uint get_numGeometries() const", AS_METHODPR(StaticModel, GetNumGeometries, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "uint GetNumNetworkAttributes() const", AS_METHODPR(StaticModel, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned StaticModel::GetNumOccluderTriangles() override | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "uint GetNumOccluderTriangles()", AS_METHODPR(StaticModel, GetNumOccluderTriangles, (), unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(StaticModel, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(StaticModel, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(StaticModel, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // unsigned StaticModel::GetOcclusionLodLevel() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "uint GetOcclusionLodLevel() const", AS_METHODPR(StaticModel, GetOcclusionLodLevel, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "uint get_occlusionLodLevel() const", AS_METHODPR(StaticModel, GetOcclusionLodLevel, () const, unsigned), AS_CALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "Scene@+ GetScene() const", AS_METHODPR(StaticModel, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "float GetShadowDistance() const", AS_METHODPR(StaticModel, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "float get_shadowDistance() const", AS_METHODPR(StaticModel, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "uint GetShadowMask() const", AS_METHODPR(StaticModel, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "uint get_shadowMask() const", AS_METHODPR(StaticModel, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "float GetSortValue() const", AS_METHODPR(StaticModel, GetSortValue, () const, float), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(StaticModel, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "StringHash GetType() const", AS_METHODPR(StaticModel, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "StringHash get_type() const", AS_METHODPR(StaticModel, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "const String& GetTypeName() const", AS_METHODPR(StaticModel, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "const String& get_typeName() const", AS_METHODPR(StaticModel, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // virtual UpdateGeometryType Drawable::GetUpdateGeometryType() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "UpdateGeometryType GetUpdateGeometryType()", AS_METHODPR(StaticModel, GetUpdateGeometryType, (), UpdateGeometryType), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "Array<Light@>@ GetVertexLights() const", AS_FUNCTION_OBJFIRST(StaticModel_GetVertexLights_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "uint GetViewMask() const", AS_METHODPR(StaticModel, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "uint get_viewMask() const", AS_METHODPR(StaticModel, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "const BoundingBox& GetWorldBoundingBox()", AS_METHODPR(StaticModel, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "const BoundingBox& get_worldBoundingBox()", AS_METHODPR(StaticModel, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "Zone@+ GetZone() const", AS_METHODPR(StaticModel, GetZone, () const, Zone*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "Zone@+ get_zone() const", AS_METHODPR(StaticModel, GetZone, () const, Zone*), AS_CALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "uint GetZoneMask() const", AS_METHODPR(StaticModel, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "uint get_zoneMask() const", AS_METHODPR(StaticModel, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "bool HasBasePass(uint) const", AS_METHODPR(StaticModel, HasBasePass, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "bool HasEventHandlers() const", AS_METHODPR(StaticModel, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(StaticModel, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(StaticModel, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "bool IsEnabled() const", AS_METHODPR(StaticModel, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "bool get_enabled() const", AS_METHODPR(StaticModel, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "bool IsEnabledEffective() const", AS_METHODPR(StaticModel, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "bool get_enabledEffective() const", AS_METHODPR(StaticModel, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool StaticModel::IsInside(const Vector3& point) const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "bool IsInside(const Vector3&in) const", AS_METHODPR(StaticModel, IsInside, (const Vector3&) const, bool), AS_CALL_THISCALL);
    // bool StaticModel::IsInsideLocal(const Vector3& point) const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "bool IsInsideLocal(const Vector3&in) const", AS_METHODPR(StaticModel, IsInsideLocal, (const Vector3&) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "bool IsInstanceOf(StringHash) const", AS_METHODPR(StaticModel, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "bool IsInView() const", AS_METHODPR(StaticModel, IsInView, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "bool get_inView() const", AS_METHODPR(StaticModel, IsInView, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "bool IsInView(Camera@+) const", AS_METHODPR(StaticModel, IsInView, (Camera*) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "bool IsInView(const FrameInfo&in, bool = false) const", AS_METHODPR(StaticModel, IsInView, (const FrameInfo&, bool) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "bool IsOccludee() const", AS_METHODPR(StaticModel, IsOccludee, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "bool get_occludee() const", AS_METHODPR(StaticModel, IsOccludee, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "bool IsOccluder() const", AS_METHODPR(StaticModel, IsOccluder, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "bool get_occluder() const", AS_METHODPR(StaticModel, IsOccluder, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "bool IsReplicated() const", AS_METHODPR(StaticModel, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "bool get_replicated() const", AS_METHODPR(StaticModel, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "bool IsTemporary() const", AS_METHODPR(StaticModel, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "bool get_temporary() const", AS_METHODPR(StaticModel, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "bool IsZoneDirty() const", AS_METHODPR(StaticModel, IsZoneDirty, () const, bool), AS_CALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void LimitLights()", AS_METHODPR(StaticModel, LimitLights, (), void), AS_CALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void LimitVertexLights(bool)", AS_METHODPR(StaticModel, LimitVertexLights, (bool), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "bool Load(Deserializer&)", AS_METHODPR(StaticModel, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(StaticModel, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "bool LoadXML(const XMLElement&in)", AS_METHODPR(StaticModel, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void MarkForUpdate()", AS_METHODPR(StaticModel, MarkForUpdate, (), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void MarkInView(const FrameInfo&in)", AS_METHODPR(StaticModel, MarkInView, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void MarkInView(uint)", AS_METHODPR(StaticModel, MarkInView, (unsigned), void), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "void MarkNetworkUpdate()", AS_METHODPR(StaticModel, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(StaticModel, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(StaticModel, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(StaticModel, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Drawable::OnSetEnabled() override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void OnSetEnabled()", AS_METHODPR(StaticModel, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "void PrepareNetworkUpdate()", AS_METHODPR(StaticModel, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void StaticModel::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override | File: ../Graphics/StaticModel.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(StaticModel, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(StaticModel, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("StaticModel", "int Refs() const", AS_METHODPR(StaticModel, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "int get_refs() const", AS_METHODPR(StaticModel, Refs, () const, int), AS_CALL_THISCALL);
    // static void StaticModel::RegisterObject(Context* context) | File: ../Graphics/StaticModel.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("StaticModel", asBEHAVE_RELEASE, "void f()", AS_METHODPR(StaticModel, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "void Remove()", AS_METHODPR(StaticModel, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(StaticModel, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "void RemoveInstanceDefault()", AS_METHODPR(StaticModel, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "void RemoveObjectAnimation()", AS_METHODPR(StaticModel, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "void ResetToDefault()", AS_METHODPR(StaticModel, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "bool Save(Serializer&) const", AS_METHODPR(StaticModel, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "bool SaveDefaultAttributes() const", AS_METHODPR(StaticModel, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "bool SaveJSON(JSONValue&) const", AS_METHODPR(StaticModel, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "bool SaveXML(XMLElement&) const", AS_METHODPR(StaticModel, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "void SendEvent(StringHash)", AS_METHODPR(StaticModel, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(StaticModel, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "void SetAnimationEnabled(bool)", AS_METHODPR(StaticModel, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_animationEnabled(bool)", AS_METHODPR(StaticModel, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "void SetAnimationTime(float)", AS_METHODPR(StaticModel, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(StaticModel, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(StaticModel, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(StaticModel, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(StaticModel, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(StaticModel, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(StaticModel, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(StaticModel, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetBasePass(uint)", AS_METHODPR(StaticModel, SetBasePass, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "void SetBlockEvents(bool)", AS_METHODPR(StaticModel, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetCastShadows(bool)", AS_METHODPR(StaticModel, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_castShadows(bool)", AS_METHODPR(StaticModel, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetDrawDistance(float)", AS_METHODPR(StaticModel, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_drawDistance(float)", AS_METHODPR(StaticModel, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModel", "void SetEnabled(bool)", AS_METHODPR(StaticModel, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_enabled(bool)", AS_METHODPR(StaticModel, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(StaticModel, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(StaticModel, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "void SetInstanceDefault(bool)", AS_METHODPR(StaticModel, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(StaticModel, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetLightMask(uint)", AS_METHODPR(StaticModel, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_lightMask(uint)", AS_METHODPR(StaticModel, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetLodBias(float)", AS_METHODPR(StaticModel, SetLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_lodBias(float)", AS_METHODPR(StaticModel, SetLodBias, (float), void), AS_CALL_THISCALL);
    // virtual void StaticModel::SetMaterial(Material* material) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "void SetMaterial(Material@+)", AS_METHODPR(StaticModel, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_material(Material@+)", AS_METHODPR(StaticModel, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    // virtual bool StaticModel::SetMaterial(unsigned index, Material* material) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "bool SetMaterial(uint, Material@+)", AS_METHODPR(StaticModel, SetMaterial, (unsigned, Material*), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "bool set_materials(uint, Material@+)", AS_METHODPR(StaticModel, SetMaterial, (unsigned, Material*), bool), AS_CALL_THISCALL);
    // void StaticModel::SetMaterialsAttr(const ResourceRefList& value) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "void SetMaterialsAttr(const ResourceRefList&in)", AS_METHODPR(StaticModel, SetMaterialsAttr, (const ResourceRefList&), void), AS_CALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetMaxLights(uint)", AS_METHODPR(StaticModel, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_maxLights(uint)", AS_METHODPR(StaticModel, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetMinMaxZ(float, float)", AS_METHODPR(StaticModel, SetMinMaxZ, (float, float), void), AS_CALL_THISCALL);
    // virtual void StaticModel::SetModel(Model* model) | File: ../Graphics/StaticModel.h
    // Not registered because have @manualbind mark
    // void StaticModel::SetModelAttr(const ResourceRef& value) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "void SetModelAttr(const ResourceRef&in)", AS_METHODPR(StaticModel, SetModelAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(StaticModel, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(StaticModel, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModel", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(StaticModel, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetOccludee(bool)", AS_METHODPR(StaticModel, SetOccludee, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_occludee(bool)", AS_METHODPR(StaticModel, SetOccludee, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetOccluder(bool)", AS_METHODPR(StaticModel, SetOccluder, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_occluder(bool)", AS_METHODPR(StaticModel, SetOccluder, (bool), void), AS_CALL_THISCALL);
    // void StaticModel::SetOcclusionLodLevel(unsigned level) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "void SetOcclusionLodLevel(uint)", AS_METHODPR(StaticModel, SetOcclusionLodLevel, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_occlusionLodLevel(uint)", AS_METHODPR(StaticModel, SetOcclusionLodLevel, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetShadowDistance(float)", AS_METHODPR(StaticModel, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_shadowDistance(float)", AS_METHODPR(StaticModel, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetShadowMask(uint)", AS_METHODPR(StaticModel, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_shadowMask(uint)", AS_METHODPR(StaticModel, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetSortValue(float)", AS_METHODPR(StaticModel, SetSortValue, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "void SetTemporary(bool)", AS_METHODPR(StaticModel, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_temporary(bool)", AS_METHODPR(StaticModel, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetViewMask(uint)", AS_METHODPR(StaticModel, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_viewMask(uint)", AS_METHODPR(StaticModel, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetZone(Zone@+, bool = false)", AS_METHODPR(StaticModel, SetZone, (Zone*, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void SetZoneMask(uint)", AS_METHODPR(StaticModel, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "void set_zoneMask(uint)", AS_METHODPR(StaticModel, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    // explicit StaticModel::StaticModel(Context* context) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectBehaviour("StaticModel", asBEHAVE_FACTORY, "StaticModel@+ f()", AS_FUNCTION(StaticModel_StaticModel_Context), AS_CALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "void UnsubscribeFromAllEvents()", AS_METHODPR(StaticModel, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(StaticModel_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(StaticModel, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(StaticModel, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModel", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(StaticModel, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void Update(const FrameInfo&in)", AS_METHODPR(StaticModel, Update, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void StaticModel::UpdateBatches(const FrameInfo& frame) override | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModel", "void UpdateBatches(const FrameInfo&in)", AS_METHODPR(StaticModel, UpdateBatches, (const FrameInfo&), void), AS_CALL_THISCALL);
    // virtual void Drawable::UpdateGeometry(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModel", "void UpdateGeometry(const FrameInfo&in)", AS_METHODPR(StaticModel, UpdateGeometry, (const FrameInfo&), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("StaticModel", "int WeakRefs() const", AS_METHODPR(StaticModel, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModel", "int get_weakRefs() const", AS_METHODPR(StaticModel, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(StaticModel, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(StaticModel, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModel", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(StaticModel, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("StaticModelGroup", "void AddInstanceNode(Node@+)", AS_METHODPR(StaticModelGroup, AddInstanceNode, (Node*), void), AS_CALL_THISCALL);
    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void AddLight(Light@+)", AS_METHODPR(StaticModelGroup, AddLight, (Light*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("StaticModelGroup", asBEHAVE_ADDREF, "void f()", AS_METHODPR(StaticModelGroup, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void AddVertexLight(Light@+)", AS_METHODPR(StaticModelGroup, AddVertexLight, (Light*), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void AllocateNetworkState()", AS_METHODPR(StaticModelGroup, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void StaticModelGroup::ApplyAttributes() override | File: ../Graphics/StaticModelGroup.h
    engine->RegisterObjectMethod("StaticModelGroup", "void ApplyAttributes()", AS_METHODPR(StaticModelGroup, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void StaticModel::ApplyMaterialList(const String& fileName=String::EMPTY) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "void ApplyMaterialList(const String&in = String::EMPTY)", AS_METHODPR(StaticModelGroup, ApplyMaterialList, (const String&), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(StaticModelGroup, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool StaticModelGroup::DrawOcclusion(OcclusionBuffer* buffer) override | File: ../Graphics/StaticModelGroup.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool DrawOcclusion(OcclusionBuffer@+)", AS_METHODPR(StaticModelGroup, DrawOcclusion, (OcclusionBuffer*), bool), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool GetAnimationEnabled() const", AS_METHODPR(StaticModelGroup, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "bool get_animationEnabled() const", AS_METHODPR(StaticModelGroup, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "Variant GetAttribute(uint) const", AS_METHODPR(StaticModelGroup, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "Variant get_attributes(uint) const", AS_METHODPR(StaticModelGroup, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "Variant GetAttribute(const String&in) const", AS_METHODPR(StaticModelGroup, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(StaticModelGroup, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(StaticModelGroup, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(StaticModelGroup, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(StaticModelGroup, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "Variant GetAttributeDefault(uint) const", AS_METHODPR(StaticModelGroup, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "Variant get_attributeDefaults(uint) const", AS_METHODPR(StaticModelGroup, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(StaticModelGroup, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool GetBlockEvents() const", AS_METHODPR(StaticModelGroup, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "const BoundingBox& GetBoundingBox() const", AS_METHODPR(StaticModelGroup, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "const BoundingBox& get_boundingBox() const", AS_METHODPR(StaticModelGroup, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool GetCastShadows() const", AS_METHODPR(StaticModelGroup, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "bool get_castShadows() const", AS_METHODPR(StaticModelGroup, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "const String& GetCategory() const", AS_METHODPR(StaticModelGroup, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "const String& get_category() const", AS_METHODPR(StaticModelGroup, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "Component@+ GetComponent(StringHash) const", AS_METHODPR(StaticModelGroup, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("StaticModelGroup", "float GetDistance() const", AS_METHODPR(StaticModelGroup, GetDistance, () const, float), AS_CALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint8 GetDrawableFlags() const", AS_METHODPR(StaticModelGroup, GetDrawableFlags, () const, unsigned char), AS_CALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "float GetDrawDistance() const", AS_METHODPR(StaticModelGroup, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "float get_drawDistance() const", AS_METHODPR(StaticModelGroup, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "VariantMap& GetEventDataMap() const", AS_METHODPR(StaticModelGroup, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "Object@+ GetEventSender() const", AS_METHODPR(StaticModelGroup, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "Light@+ GetFirstLight() const", AS_METHODPR(StaticModelGroup, GetFirstLight, () const, Light*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(StaticModelGroup, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(StaticModelGroup, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "const VariantMap& GetGlobalVars() const", AS_METHODPR(StaticModelGroup, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "const VariantMap& get_globalVars() const", AS_METHODPR(StaticModelGroup, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint GetID() const", AS_METHODPR(StaticModelGroup, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "uint get_id() const", AS_METHODPR(StaticModelGroup, GetID, () const, unsigned), AS_CALL_THISCALL);
    // Node* StaticModelGroup::GetInstanceNode(unsigned index) const | File: ../Graphics/StaticModelGroup.h
    engine->RegisterObjectMethod("StaticModelGroup", "Node@+ GetInstanceNode(uint) const", AS_METHODPR(StaticModelGroup, GetInstanceNode, (unsigned) const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "Node@+ get_instanceNodes(uint) const", AS_METHODPR(StaticModelGroup, GetInstanceNode, (unsigned) const, Node*), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(StaticModelGroup, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint GetLightMask() const", AS_METHODPR(StaticModelGroup, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "uint get_lightMask() const", AS_METHODPR(StaticModelGroup, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "Array<Light@>@ GetLights() const", AS_FUNCTION_OBJFIRST(StaticModelGroup_GetLights_void), AS_CALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "float GetLodBias() const", AS_METHODPR(StaticModelGroup, GetLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "float get_lodBias() const", AS_METHODPR(StaticModelGroup, GetLodBias, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "float GetLodDistance() const", AS_METHODPR(StaticModelGroup, GetLodDistance, () const, float), AS_CALL_THISCALL);
    // Geometry* StaticModel::GetLodGeometry(unsigned batchIndex, unsigned level) override | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "Geometry@+ GetLodGeometry(uint, uint)", AS_METHODPR(StaticModelGroup, GetLodGeometry, (unsigned, unsigned), Geometry*), AS_CALL_THISCALL);
    // virtual Material* StaticModel::GetMaterial() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "Material@+ GetMaterial() const", AS_METHODPR(StaticModelGroup, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "Material@+ get_material() const", AS_METHODPR(StaticModelGroup, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    // virtual Material* StaticModel::GetMaterial(unsigned index) const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "Material@+ GetMaterial(uint) const", AS_METHODPR(StaticModelGroup, GetMaterial, (unsigned) const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "Material@+ get_materials(uint) const", AS_METHODPR(StaticModelGroup, GetMaterial, (unsigned) const, Material*), AS_CALL_THISCALL);
    // const ResourceRefList& StaticModel::GetMaterialsAttr() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "const ResourceRefList& GetMaterialsAttr() const", AS_METHODPR(StaticModelGroup, GetMaterialsAttr, () const, const ResourceRefList&), AS_CALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint GetMaxLights() const", AS_METHODPR(StaticModelGroup, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "uint get_maxLights() const", AS_METHODPR(StaticModelGroup, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "float GetMaxZ() const", AS_METHODPR(StaticModelGroup, GetMaxZ, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "float GetMinZ() const", AS_METHODPR(StaticModelGroup, GetMinZ, () const, float), AS_CALL_THISCALL);
    // Model* StaticModel::GetModel() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "Model@+ GetModel() const", AS_METHODPR(StaticModelGroup, GetModel, () const, Model*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "Model@+ get_model() const", AS_METHODPR(StaticModelGroup, GetModel, () const, Model*), AS_CALL_THISCALL);
    // ResourceRef StaticModel::GetModelAttr() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "ResourceRef GetModelAttr() const", AS_METHODPR(StaticModelGroup, GetModelAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "Node@+ GetNode() const", AS_METHODPR(StaticModelGroup, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "Node@+ get_node() const", AS_METHODPR(StaticModelGroup, GetNode, () const, Node*), AS_CALL_THISCALL);
    // const VariantVector& StaticModelGroup::GetNodeIDsAttr() const | File: ../Graphics/StaticModelGroup.h
    // Error: type "const VariantVector&" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint GetNumAttributes() const", AS_METHODPR(StaticModelGroup, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "uint get_numAttributes() const", AS_METHODPR(StaticModelGroup, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned StaticModel::GetNumGeometries() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint GetNumGeometries() const", AS_METHODPR(StaticModelGroup, GetNumGeometries, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "uint get_numGeometries() const", AS_METHODPR(StaticModelGroup, GetNumGeometries, () const, unsigned), AS_CALL_THISCALL);
    // unsigned StaticModelGroup::GetNumInstanceNodes() const | File: ../Graphics/StaticModelGroup.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint GetNumInstanceNodes() const", AS_METHODPR(StaticModelGroup, GetNumInstanceNodes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "uint get_numInstanceNodes() const", AS_METHODPR(StaticModelGroup, GetNumInstanceNodes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint GetNumNetworkAttributes() const", AS_METHODPR(StaticModelGroup, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned StaticModelGroup::GetNumOccluderTriangles() override | File: ../Graphics/StaticModelGroup.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint GetNumOccluderTriangles()", AS_METHODPR(StaticModelGroup, GetNumOccluderTriangles, (), unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(StaticModelGroup, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(StaticModelGroup, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(StaticModelGroup, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // unsigned StaticModel::GetOcclusionLodLevel() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint GetOcclusionLodLevel() const", AS_METHODPR(StaticModelGroup, GetOcclusionLodLevel, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "uint get_occlusionLodLevel() const", AS_METHODPR(StaticModelGroup, GetOcclusionLodLevel, () const, unsigned), AS_CALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "Scene@+ GetScene() const", AS_METHODPR(StaticModelGroup, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "float GetShadowDistance() const", AS_METHODPR(StaticModelGroup, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "float get_shadowDistance() const", AS_METHODPR(StaticModelGroup, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint GetShadowMask() const", AS_METHODPR(StaticModelGroup, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "uint get_shadowMask() const", AS_METHODPR(StaticModelGroup, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "float GetSortValue() const", AS_METHODPR(StaticModelGroup, GetSortValue, () const, float), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(StaticModelGroup, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "StringHash GetType() const", AS_METHODPR(StaticModelGroup, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "StringHash get_type() const", AS_METHODPR(StaticModelGroup, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "const String& GetTypeName() const", AS_METHODPR(StaticModelGroup, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "const String& get_typeName() const", AS_METHODPR(StaticModelGroup, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // virtual UpdateGeometryType Drawable::GetUpdateGeometryType() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "UpdateGeometryType GetUpdateGeometryType()", AS_METHODPR(StaticModelGroup, GetUpdateGeometryType, (), UpdateGeometryType), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "Array<Light@>@ GetVertexLights() const", AS_FUNCTION_OBJFIRST(StaticModelGroup_GetVertexLights_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint GetViewMask() const", AS_METHODPR(StaticModelGroup, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "uint get_viewMask() const", AS_METHODPR(StaticModelGroup, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "const BoundingBox& GetWorldBoundingBox()", AS_METHODPR(StaticModelGroup, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "const BoundingBox& get_worldBoundingBox()", AS_METHODPR(StaticModelGroup, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "Zone@+ GetZone() const", AS_METHODPR(StaticModelGroup, GetZone, () const, Zone*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "Zone@+ get_zone() const", AS_METHODPR(StaticModelGroup, GetZone, () const, Zone*), AS_CALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "uint GetZoneMask() const", AS_METHODPR(StaticModelGroup, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "uint get_zoneMask() const", AS_METHODPR(StaticModelGroup, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool HasBasePass(uint) const", AS_METHODPR(StaticModelGroup, HasBasePass, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool HasEventHandlers() const", AS_METHODPR(StaticModelGroup, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(StaticModelGroup, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(StaticModelGroup, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsEnabled() const", AS_METHODPR(StaticModelGroup, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "bool get_enabled() const", AS_METHODPR(StaticModelGroup, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsEnabledEffective() const", AS_METHODPR(StaticModelGroup, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "bool get_enabledEffective() const", AS_METHODPR(StaticModelGroup, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool StaticModel::IsInside(const Vector3& point) const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsInside(const Vector3&in) const", AS_METHODPR(StaticModelGroup, IsInside, (const Vector3&) const, bool), AS_CALL_THISCALL);
    // bool StaticModel::IsInsideLocal(const Vector3& point) const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsInsideLocal(const Vector3&in) const", AS_METHODPR(StaticModelGroup, IsInsideLocal, (const Vector3&) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsInstanceOf(StringHash) const", AS_METHODPR(StaticModelGroup, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsInView() const", AS_METHODPR(StaticModelGroup, IsInView, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "bool get_inView() const", AS_METHODPR(StaticModelGroup, IsInView, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsInView(Camera@+) const", AS_METHODPR(StaticModelGroup, IsInView, (Camera*) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsInView(const FrameInfo&in, bool = false) const", AS_METHODPR(StaticModelGroup, IsInView, (const FrameInfo&, bool) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsOccludee() const", AS_METHODPR(StaticModelGroup, IsOccludee, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "bool get_occludee() const", AS_METHODPR(StaticModelGroup, IsOccludee, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsOccluder() const", AS_METHODPR(StaticModelGroup, IsOccluder, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "bool get_occluder() const", AS_METHODPR(StaticModelGroup, IsOccluder, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsReplicated() const", AS_METHODPR(StaticModelGroup, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "bool get_replicated() const", AS_METHODPR(StaticModelGroup, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsTemporary() const", AS_METHODPR(StaticModelGroup, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "bool get_temporary() const", AS_METHODPR(StaticModelGroup, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool IsZoneDirty() const", AS_METHODPR(StaticModelGroup, IsZoneDirty, () const, bool), AS_CALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void LimitLights()", AS_METHODPR(StaticModelGroup, LimitLights, (), void), AS_CALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void LimitVertexLights(bool)", AS_METHODPR(StaticModelGroup, LimitVertexLights, (bool), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool Load(Deserializer&)", AS_METHODPR(StaticModelGroup, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(StaticModelGroup, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool LoadXML(const XMLElement&in)", AS_METHODPR(StaticModelGroup, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void MarkForUpdate()", AS_METHODPR(StaticModelGroup, MarkForUpdate, (), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void MarkInView(const FrameInfo&in)", AS_METHODPR(StaticModelGroup, MarkInView, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void MarkInView(uint)", AS_METHODPR(StaticModelGroup, MarkInView, (unsigned), void), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "void MarkNetworkUpdate()", AS_METHODPR(StaticModelGroup, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(StaticModelGroup, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(StaticModelGroup, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(StaticModelGroup, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Drawable::OnSetEnabled() override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void OnSetEnabled()", AS_METHODPR(StaticModelGroup, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "void PrepareNetworkUpdate()", AS_METHODPR(StaticModelGroup, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void StaticModelGroup::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override | File: ../Graphics/StaticModelGroup.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(StaticModelGroup, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(StaticModelGroup, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("StaticModelGroup", "int Refs() const", AS_METHODPR(StaticModelGroup, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "int get_refs() const", AS_METHODPR(StaticModelGroup, Refs, () const, int), AS_CALL_THISCALL);
    // static void StaticModelGroup::RegisterObject(Context* context) | File: ../Graphics/StaticModelGroup.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("StaticModelGroup", asBEHAVE_RELEASE, "void f()", AS_METHODPR(StaticModelGroup, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "void Remove()", AS_METHODPR(StaticModelGroup, Remove, (), void), AS_CALL_THISCALL);
    // void StaticModelGroup::RemoveAllInstanceNodes() | File: ../Graphics/StaticModelGroup.h
    engine->RegisterObjectMethod("StaticModelGroup", "void RemoveAllInstanceNodes()", AS_METHODPR(StaticModelGroup, RemoveAllInstanceNodes, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(StaticModelGroup, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void RemoveInstanceDefault()", AS_METHODPR(StaticModelGroup, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void StaticModelGroup::RemoveInstanceNode(Node* node) | File: ../Graphics/StaticModelGroup.h
    engine->RegisterObjectMethod("StaticModelGroup", "void RemoveInstanceNode(Node@+)", AS_METHODPR(StaticModelGroup, RemoveInstanceNode, (Node*), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void RemoveObjectAnimation()", AS_METHODPR(StaticModelGroup, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void ResetToDefault()", AS_METHODPR(StaticModelGroup, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool Save(Serializer&) const", AS_METHODPR(StaticModelGroup, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool SaveDefaultAttributes() const", AS_METHODPR(StaticModelGroup, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool SaveJSON(JSONValue&) const", AS_METHODPR(StaticModelGroup, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool SaveXML(XMLElement&) const", AS_METHODPR(StaticModelGroup, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SendEvent(StringHash)", AS_METHODPR(StaticModelGroup, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(StaticModelGroup, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetAnimationEnabled(bool)", AS_METHODPR(StaticModelGroup, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_animationEnabled(bool)", AS_METHODPR(StaticModelGroup, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetAnimationTime(float)", AS_METHODPR(StaticModelGroup, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(StaticModelGroup, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(StaticModelGroup, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(StaticModelGroup, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(StaticModelGroup, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(StaticModelGroup, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(StaticModelGroup, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(StaticModelGroup, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetBasePass(uint)", AS_METHODPR(StaticModelGroup, SetBasePass, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetBlockEvents(bool)", AS_METHODPR(StaticModelGroup, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetCastShadows(bool)", AS_METHODPR(StaticModelGroup, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_castShadows(bool)", AS_METHODPR(StaticModelGroup, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetDrawDistance(float)", AS_METHODPR(StaticModelGroup, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_drawDistance(float)", AS_METHODPR(StaticModelGroup, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetEnabled(bool)", AS_METHODPR(StaticModelGroup, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_enabled(bool)", AS_METHODPR(StaticModelGroup, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(StaticModelGroup, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(StaticModelGroup, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetInstanceDefault(bool)", AS_METHODPR(StaticModelGroup, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(StaticModelGroup, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetLightMask(uint)", AS_METHODPR(StaticModelGroup, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_lightMask(uint)", AS_METHODPR(StaticModelGroup, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetLodBias(float)", AS_METHODPR(StaticModelGroup, SetLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_lodBias(float)", AS_METHODPR(StaticModelGroup, SetLodBias, (float), void), AS_CALL_THISCALL);
    // virtual void StaticModel::SetMaterial(Material* material) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetMaterial(Material@+)", AS_METHODPR(StaticModelGroup, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_material(Material@+)", AS_METHODPR(StaticModelGroup, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    // virtual bool StaticModel::SetMaterial(unsigned index, Material* material) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "bool SetMaterial(uint, Material@+)", AS_METHODPR(StaticModelGroup, SetMaterial, (unsigned, Material*), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "bool set_materials(uint, Material@+)", AS_METHODPR(StaticModelGroup, SetMaterial, (unsigned, Material*), bool), AS_CALL_THISCALL);
    // void StaticModel::SetMaterialsAttr(const ResourceRefList& value) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetMaterialsAttr(const ResourceRefList&in)", AS_METHODPR(StaticModelGroup, SetMaterialsAttr, (const ResourceRefList&), void), AS_CALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetMaxLights(uint)", AS_METHODPR(StaticModelGroup, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_maxLights(uint)", AS_METHODPR(StaticModelGroup, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetMinMaxZ(float, float)", AS_METHODPR(StaticModelGroup, SetMinMaxZ, (float, float), void), AS_CALL_THISCALL);
    // virtual void StaticModel::SetModel(Model* model) | File: ../Graphics/StaticModel.h
    // Not registered because have @manualbind mark
    // void StaticModel::SetModelAttr(const ResourceRef& value) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetModelAttr(const ResourceRef&in)", AS_METHODPR(StaticModelGroup, SetModelAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void StaticModelGroup::SetNodeIDsAttr(const VariantVector& value) | File: ../Graphics/StaticModelGroup.h
    // Error: type "const VariantVector&" can not automatically bind
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(StaticModelGroup, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(StaticModelGroup, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(StaticModelGroup, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetOccludee(bool)", AS_METHODPR(StaticModelGroup, SetOccludee, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_occludee(bool)", AS_METHODPR(StaticModelGroup, SetOccludee, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetOccluder(bool)", AS_METHODPR(StaticModelGroup, SetOccluder, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_occluder(bool)", AS_METHODPR(StaticModelGroup, SetOccluder, (bool), void), AS_CALL_THISCALL);
    // void StaticModel::SetOcclusionLodLevel(unsigned level) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetOcclusionLodLevel(uint)", AS_METHODPR(StaticModelGroup, SetOcclusionLodLevel, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_occlusionLodLevel(uint)", AS_METHODPR(StaticModelGroup, SetOcclusionLodLevel, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetShadowDistance(float)", AS_METHODPR(StaticModelGroup, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_shadowDistance(float)", AS_METHODPR(StaticModelGroup, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetShadowMask(uint)", AS_METHODPR(StaticModelGroup, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_shadowMask(uint)", AS_METHODPR(StaticModelGroup, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetSortValue(float)", AS_METHODPR(StaticModelGroup, SetSortValue, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetTemporary(bool)", AS_METHODPR(StaticModelGroup, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_temporary(bool)", AS_METHODPR(StaticModelGroup, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetViewMask(uint)", AS_METHODPR(StaticModelGroup, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_viewMask(uint)", AS_METHODPR(StaticModelGroup, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetZone(Zone@+, bool = false)", AS_METHODPR(StaticModelGroup, SetZone, (Zone*, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void SetZoneMask(uint)", AS_METHODPR(StaticModelGroup, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "void set_zoneMask(uint)", AS_METHODPR(StaticModelGroup, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    // explicit StaticModelGroup::StaticModelGroup(Context* context) | File: ../Graphics/StaticModelGroup.h
    engine->RegisterObjectBehaviour("StaticModelGroup", asBEHAVE_FACTORY, "StaticModelGroup@+ f()", AS_FUNCTION(StaticModelGroup_StaticModelGroup_Context), AS_CALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "void UnsubscribeFromAllEvents()", AS_METHODPR(StaticModelGroup, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(StaticModelGroup_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(StaticModelGroup, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(StaticModelGroup, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticModelGroup", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(StaticModelGroup, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void Update(const FrameInfo&in)", AS_METHODPR(StaticModelGroup, Update, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void StaticModelGroup::UpdateBatches(const FrameInfo& frame) override | File: ../Graphics/StaticModelGroup.h
    engine->RegisterObjectMethod("StaticModelGroup", "void UpdateBatches(const FrameInfo&in)", AS_METHODPR(StaticModelGroup, UpdateBatches, (const FrameInfo&), void), AS_CALL_THISCALL);
    // virtual void Drawable::UpdateGeometry(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void UpdateGeometry(const FrameInfo&in)", AS_METHODPR(StaticModelGroup, UpdateGeometry, (const FrameInfo&), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("StaticModelGroup", "int WeakRefs() const", AS_METHODPR(StaticModelGroup, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticModelGroup", "int get_weakRefs() const", AS_METHODPR(StaticModelGroup, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(StaticModelGroup, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(StaticModelGroup, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticModelGroup", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(StaticModelGroup, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("StaticSprite2D", "void AddLight(Light@+)", AS_METHODPR(StaticSprite2D, AddLight, (Light*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("StaticSprite2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(StaticSprite2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void AddVertexLight(Light@+)", AS_METHODPR(StaticSprite2D, AddVertexLight, (Light*), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void AllocateNetworkState()", AS_METHODPR(StaticSprite2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void ApplyAttributes()", AS_METHODPR(StaticSprite2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(StaticSprite2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool DrawOcclusion(OcclusionBuffer@+)", AS_METHODPR(StaticSprite2D, DrawOcclusion, (OcclusionBuffer*), bool), AS_CALL_THISCALL);
    // float StaticSprite2D::GetAlpha() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "float GetAlpha() const", AS_METHODPR(StaticSprite2D, GetAlpha, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "float get_alpha() const", AS_METHODPR(StaticSprite2D, GetAlpha, () const, float), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool GetAnimationEnabled() const", AS_METHODPR(StaticSprite2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_animationEnabled() const", AS_METHODPR(StaticSprite2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "Variant GetAttribute(uint) const", AS_METHODPR(StaticSprite2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "Variant get_attributes(uint) const", AS_METHODPR(StaticSprite2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(StaticSprite2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(StaticSprite2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(StaticSprite2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(StaticSprite2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(StaticSprite2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(StaticSprite2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(StaticSprite2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(StaticSprite2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // BlendMode StaticSprite2D::GetBlendMode() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "BlendMode GetBlendMode() const", AS_METHODPR(StaticSprite2D, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "BlendMode get_blendMode() const", AS_METHODPR(StaticSprite2D, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool GetBlockEvents() const", AS_METHODPR(StaticSprite2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "const BoundingBox& GetBoundingBox() const", AS_METHODPR(StaticSprite2D, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "const BoundingBox& get_boundingBox() const", AS_METHODPR(StaticSprite2D, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool GetCastShadows() const", AS_METHODPR(StaticSprite2D, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_castShadows() const", AS_METHODPR(StaticSprite2D, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "const String& GetCategory() const", AS_METHODPR(StaticSprite2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "const String& get_category() const", AS_METHODPR(StaticSprite2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // const Color& StaticSprite2D::GetColor() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "const Color& GetColor() const", AS_METHODPR(StaticSprite2D, GetColor, () const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "const Color& get_color() const", AS_METHODPR(StaticSprite2D, GetColor, () const, const Color&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(StaticSprite2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // Material* StaticSprite2D::GetCustomMaterial() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "Material@+ GetCustomMaterial() const", AS_METHODPR(StaticSprite2D, GetCustomMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "Material@+ get_customMaterial() const", AS_METHODPR(StaticSprite2D, GetCustomMaterial, () const, Material*), AS_CALL_THISCALL);
    // ResourceRef StaticSprite2D::GetCustomMaterialAttr() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "ResourceRef GetCustomMaterialAttr() const", AS_METHODPR(StaticSprite2D, GetCustomMaterialAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // float Drawable::GetDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "float GetDistance() const", AS_METHODPR(StaticSprite2D, GetDistance, () const, float), AS_CALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "uint8 GetDrawableFlags() const", AS_METHODPR(StaticSprite2D, GetDrawableFlags, () const, unsigned char), AS_CALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "float GetDrawDistance() const", AS_METHODPR(StaticSprite2D, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "float get_drawDistance() const", AS_METHODPR(StaticSprite2D, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    // const Rect& StaticSprite2D::GetDrawRect() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "const Rect& GetDrawRect() const", AS_METHODPR(StaticSprite2D, GetDrawRect, () const, const Rect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "const Rect& get_drawRect() const", AS_METHODPR(StaticSprite2D, GetDrawRect, () const, const Rect&), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(StaticSprite2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "Object@+ GetEventSender() const", AS_METHODPR(StaticSprite2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "Light@+ GetFirstLight() const", AS_METHODPR(StaticSprite2D, GetFirstLight, () const, Light*), AS_CALL_THISCALL);
    // bool StaticSprite2D::GetFlipX() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool GetFlipX() const", AS_METHODPR(StaticSprite2D, GetFlipX, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_flipX() const", AS_METHODPR(StaticSprite2D, GetFlipX, () const, bool), AS_CALL_THISCALL);
    // bool StaticSprite2D::GetFlipY() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool GetFlipY() const", AS_METHODPR(StaticSprite2D, GetFlipY, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_flipY() const", AS_METHODPR(StaticSprite2D, GetFlipY, () const, bool), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(StaticSprite2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(StaticSprite2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(StaticSprite2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "const VariantMap& get_globalVars() const", AS_METHODPR(StaticSprite2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // const Vector2& StaticSprite2D::GetHotSpot() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "const Vector2& GetHotSpot() const", AS_METHODPR(StaticSprite2D, GetHotSpot, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "const Vector2& get_hotSpot() const", AS_METHODPR(StaticSprite2D, GetHotSpot, () const, const Vector2&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "uint GetID() const", AS_METHODPR(StaticSprite2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "uint get_id() const", AS_METHODPR(StaticSprite2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(StaticSprite2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // int Drawable2D::GetLayer() const | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "int GetLayer() const", AS_METHODPR(StaticSprite2D, GetLayer, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "int get_layer() const", AS_METHODPR(StaticSprite2D, GetLayer, () const, int), AS_CALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "uint GetLightMask() const", AS_METHODPR(StaticSprite2D, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "uint get_lightMask() const", AS_METHODPR(StaticSprite2D, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "Array<Light@>@ GetLights() const", AS_FUNCTION_OBJFIRST(StaticSprite2D_GetLights_void), AS_CALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "float GetLodBias() const", AS_METHODPR(StaticSprite2D, GetLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "float get_lodBias() const", AS_METHODPR(StaticSprite2D, GetLodBias, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "float GetLodDistance() const", AS_METHODPR(StaticSprite2D, GetLodDistance, () const, float), AS_CALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "Geometry@+ GetLodGeometry(uint, uint)", AS_METHODPR(StaticSprite2D, GetLodGeometry, (unsigned, unsigned), Geometry*), AS_CALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "uint GetMaxLights() const", AS_METHODPR(StaticSprite2D, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "uint get_maxLights() const", AS_METHODPR(StaticSprite2D, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "float GetMaxZ() const", AS_METHODPR(StaticSprite2D, GetMaxZ, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "float GetMinZ() const", AS_METHODPR(StaticSprite2D, GetMinZ, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "Node@+ GetNode() const", AS_METHODPR(StaticSprite2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "Node@+ get_node() const", AS_METHODPR(StaticSprite2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "uint GetNumAttributes() const", AS_METHODPR(StaticSprite2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "uint get_numAttributes() const", AS_METHODPR(StaticSprite2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(StaticSprite2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "uint GetNumOccluderTriangles()", AS_METHODPR(StaticSprite2D, GetNumOccluderTriangles, (), unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(StaticSprite2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(StaticSprite2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(StaticSprite2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // int Drawable2D::GetOrderInLayer() const | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "int GetOrderInLayer() const", AS_METHODPR(StaticSprite2D, GetOrderInLayer, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "int get_orderInLayer() const", AS_METHODPR(StaticSprite2D, GetOrderInLayer, () const, int), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "Scene@+ GetScene() const", AS_METHODPR(StaticSprite2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "float GetShadowDistance() const", AS_METHODPR(StaticSprite2D, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "float get_shadowDistance() const", AS_METHODPR(StaticSprite2D, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "uint GetShadowMask() const", AS_METHODPR(StaticSprite2D, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "uint get_shadowMask() const", AS_METHODPR(StaticSprite2D, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "float GetSortValue() const", AS_METHODPR(StaticSprite2D, GetSortValue, () const, float), AS_CALL_THISCALL);
    // const Vector<SourceBatch2D>& Drawable2D::GetSourceBatches() | File: ../Urho2D/Drawable2D.h
    // Error: type "const Vector<SourceBatch2D>&" can not automatically bind
    // Sprite2D* StaticSprite2D::GetSprite() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "Sprite2D@+ GetSprite() const", AS_METHODPR(StaticSprite2D, GetSprite, () const, Sprite2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "Sprite2D@+ get_sprite() const", AS_METHODPR(StaticSprite2D, GetSprite, () const, Sprite2D*), AS_CALL_THISCALL);
    // ResourceRef StaticSprite2D::GetSpriteAttr() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "ResourceRef GetSpriteAttr() const", AS_METHODPR(StaticSprite2D, GetSpriteAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(StaticSprite2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // bool StaticSprite2D::GetSwapXY() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool GetSwapXY() const", AS_METHODPR(StaticSprite2D, GetSwapXY, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_swapXY() const", AS_METHODPR(StaticSprite2D, GetSwapXY, () const, bool), AS_CALL_THISCALL);
    // const Rect& StaticSprite2D::GetTextureRect() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "const Rect& GetTextureRect() const", AS_METHODPR(StaticSprite2D, GetTextureRect, () const, const Rect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "const Rect& get_textureRect() const", AS_METHODPR(StaticSprite2D, GetTextureRect, () const, const Rect&), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "StringHash GetType() const", AS_METHODPR(StaticSprite2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "StringHash get_type() const", AS_METHODPR(StaticSprite2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "const String& GetTypeName() const", AS_METHODPR(StaticSprite2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "const String& get_typeName() const", AS_METHODPR(StaticSprite2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // virtual UpdateGeometryType Drawable::GetUpdateGeometryType() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "UpdateGeometryType GetUpdateGeometryType()", AS_METHODPR(StaticSprite2D, GetUpdateGeometryType, (), UpdateGeometryType), AS_CALL_THISCALL);
    // bool StaticSprite2D::GetUseDrawRect() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool GetUseDrawRect() const", AS_METHODPR(StaticSprite2D, GetUseDrawRect, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_useDrawRect() const", AS_METHODPR(StaticSprite2D, GetUseDrawRect, () const, bool), AS_CALL_THISCALL);
    // bool StaticSprite2D::GetUseHotSpot() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool GetUseHotSpot() const", AS_METHODPR(StaticSprite2D, GetUseHotSpot, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_useHotSpot() const", AS_METHODPR(StaticSprite2D, GetUseHotSpot, () const, bool), AS_CALL_THISCALL);
    // bool StaticSprite2D::GetUseTextureRect() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool GetUseTextureRect() const", AS_METHODPR(StaticSprite2D, GetUseTextureRect, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_useTextureRect() const", AS_METHODPR(StaticSprite2D, GetUseTextureRect, () const, bool), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "Array<Light@>@ GetVertexLights() const", AS_FUNCTION_OBJFIRST(StaticSprite2D_GetVertexLights_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "uint GetViewMask() const", AS_METHODPR(StaticSprite2D, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "uint get_viewMask() const", AS_METHODPR(StaticSprite2D, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "const BoundingBox& GetWorldBoundingBox()", AS_METHODPR(StaticSprite2D, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "const BoundingBox& get_worldBoundingBox()", AS_METHODPR(StaticSprite2D, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "Zone@+ GetZone() const", AS_METHODPR(StaticSprite2D, GetZone, () const, Zone*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "Zone@+ get_zone() const", AS_METHODPR(StaticSprite2D, GetZone, () const, Zone*), AS_CALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "uint GetZoneMask() const", AS_METHODPR(StaticSprite2D, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "uint get_zoneMask() const", AS_METHODPR(StaticSprite2D, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool HasBasePass(uint) const", AS_METHODPR(StaticSprite2D, HasBasePass, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool HasEventHandlers() const", AS_METHODPR(StaticSprite2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(StaticSprite2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(StaticSprite2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool IsEnabled() const", AS_METHODPR(StaticSprite2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_enabled() const", AS_METHODPR(StaticSprite2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool IsEnabledEffective() const", AS_METHODPR(StaticSprite2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_enabledEffective() const", AS_METHODPR(StaticSprite2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(StaticSprite2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool IsInView() const", AS_METHODPR(StaticSprite2D, IsInView, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_inView() const", AS_METHODPR(StaticSprite2D, IsInView, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool IsInView(Camera@+) const", AS_METHODPR(StaticSprite2D, IsInView, (Camera*) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool IsInView(const FrameInfo&in, bool = false) const", AS_METHODPR(StaticSprite2D, IsInView, (const FrameInfo&, bool) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool IsOccludee() const", AS_METHODPR(StaticSprite2D, IsOccludee, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_occludee() const", AS_METHODPR(StaticSprite2D, IsOccludee, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool IsOccluder() const", AS_METHODPR(StaticSprite2D, IsOccluder, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_occluder() const", AS_METHODPR(StaticSprite2D, IsOccluder, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool IsReplicated() const", AS_METHODPR(StaticSprite2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_replicated() const", AS_METHODPR(StaticSprite2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool IsTemporary() const", AS_METHODPR(StaticSprite2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_temporary() const", AS_METHODPR(StaticSprite2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool IsZoneDirty() const", AS_METHODPR(StaticSprite2D, IsZoneDirty, () const, bool), AS_CALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void LimitLights()", AS_METHODPR(StaticSprite2D, LimitLights, (), void), AS_CALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void LimitVertexLights(bool)", AS_METHODPR(StaticSprite2D, LimitVertexLights, (bool), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool Load(Deserializer&)", AS_METHODPR(StaticSprite2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(StaticSprite2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(StaticSprite2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void MarkForUpdate()", AS_METHODPR(StaticSprite2D, MarkForUpdate, (), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void MarkInView(const FrameInfo&in)", AS_METHODPR(StaticSprite2D, MarkInView, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void MarkInView(uint)", AS_METHODPR(StaticSprite2D, MarkInView, (unsigned), void), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "void MarkNetworkUpdate()", AS_METHODPR(StaticSprite2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(StaticSprite2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(StaticSprite2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(StaticSprite2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Drawable2D::OnSetEnabled() override | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void OnSetEnabled()", AS_METHODPR(StaticSprite2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "void PrepareNetworkUpdate()", AS_METHODPR(StaticSprite2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) | File: ../Graphics/Drawable.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(StaticSprite2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(StaticSprite2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("StaticSprite2D", "int Refs() const", AS_METHODPR(StaticSprite2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "int get_refs() const", AS_METHODPR(StaticSprite2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void StaticSprite2D::RegisterObject(Context* context) | File: ../Urho2D/StaticSprite2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("StaticSprite2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(StaticSprite2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "void Remove()", AS_METHODPR(StaticSprite2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(StaticSprite2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void RemoveInstanceDefault()", AS_METHODPR(StaticSprite2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void RemoveObjectAnimation()", AS_METHODPR(StaticSprite2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void ResetToDefault()", AS_METHODPR(StaticSprite2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool Save(Serializer&) const", AS_METHODPR(StaticSprite2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool SaveDefaultAttributes() const", AS_METHODPR(StaticSprite2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(StaticSprite2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(StaticSprite2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SendEvent(StringHash)", AS_METHODPR(StaticSprite2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(StaticSprite2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void StaticSprite2D::SetAlpha(float alpha) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetAlpha(float)", AS_METHODPR(StaticSprite2D, SetAlpha, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_alpha(float)", AS_METHODPR(StaticSprite2D, SetAlpha, (float), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetAnimationEnabled(bool)", AS_METHODPR(StaticSprite2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_animationEnabled(bool)", AS_METHODPR(StaticSprite2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetAnimationTime(float)", AS_METHODPR(StaticSprite2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(StaticSprite2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(StaticSprite2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(StaticSprite2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(StaticSprite2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(StaticSprite2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(StaticSprite2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(StaticSprite2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetBasePass(uint)", AS_METHODPR(StaticSprite2D, SetBasePass, (unsigned), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetBlendMode(BlendMode blendMode) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetBlendMode(BlendMode)", AS_METHODPR(StaticSprite2D, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_blendMode(BlendMode)", AS_METHODPR(StaticSprite2D, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetBlockEvents(bool)", AS_METHODPR(StaticSprite2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetCastShadows(bool)", AS_METHODPR(StaticSprite2D, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_castShadows(bool)", AS_METHODPR(StaticSprite2D, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetColor(const Color& color) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetColor(const Color&in)", AS_METHODPR(StaticSprite2D, SetColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_color(const Color&in)", AS_METHODPR(StaticSprite2D, SetColor, (const Color&), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetCustomMaterial(Material* customMaterial) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetCustomMaterial(Material@+)", AS_METHODPR(StaticSprite2D, SetCustomMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_customMaterial(Material@+)", AS_METHODPR(StaticSprite2D, SetCustomMaterial, (Material*), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetCustomMaterialAttr(const ResourceRef& value) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetCustomMaterialAttr(const ResourceRef&in)", AS_METHODPR(StaticSprite2D, SetCustomMaterialAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetDrawDistance(float)", AS_METHODPR(StaticSprite2D, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_drawDistance(float)", AS_METHODPR(StaticSprite2D, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetDrawRect(const Rect& rect) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetDrawRect(const Rect&in)", AS_METHODPR(StaticSprite2D, SetDrawRect, (const Rect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_drawRect(const Rect&in)", AS_METHODPR(StaticSprite2D, SetDrawRect, (const Rect&), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetEnabled(bool)", AS_METHODPR(StaticSprite2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_enabled(bool)", AS_METHODPR(StaticSprite2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetFlip(bool flipX, bool flipY, bool swapXY=false) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetFlip(bool, bool, bool = false)", AS_METHODPR(StaticSprite2D, SetFlip, (bool, bool, bool), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetFlipX(bool flipX) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetFlipX(bool)", AS_METHODPR(StaticSprite2D, SetFlipX, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_flipX(bool)", AS_METHODPR(StaticSprite2D, SetFlipX, (bool), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetFlipY(bool flipY) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetFlipY(bool)", AS_METHODPR(StaticSprite2D, SetFlipY, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_flipY(bool)", AS_METHODPR(StaticSprite2D, SetFlipY, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(StaticSprite2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(StaticSprite2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetHotSpot(const Vector2& hotspot) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetHotSpot(const Vector2&in)", AS_METHODPR(StaticSprite2D, SetHotSpot, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_hotSpot(const Vector2&in)", AS_METHODPR(StaticSprite2D, SetHotSpot, (const Vector2&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetInstanceDefault(bool)", AS_METHODPR(StaticSprite2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(StaticSprite2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Drawable2D::SetLayer(int layer) | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetLayer(int)", AS_METHODPR(StaticSprite2D, SetLayer, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_layer(int)", AS_METHODPR(StaticSprite2D, SetLayer, (int), void), AS_CALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetLightMask(uint)", AS_METHODPR(StaticSprite2D, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_lightMask(uint)", AS_METHODPR(StaticSprite2D, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetLodBias(float)", AS_METHODPR(StaticSprite2D, SetLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_lodBias(float)", AS_METHODPR(StaticSprite2D, SetLodBias, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetMaxLights(uint)", AS_METHODPR(StaticSprite2D, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_maxLights(uint)", AS_METHODPR(StaticSprite2D, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetMinMaxZ(float, float)", AS_METHODPR(StaticSprite2D, SetMinMaxZ, (float, float), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(StaticSprite2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(StaticSprite2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(StaticSprite2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetOccludee(bool)", AS_METHODPR(StaticSprite2D, SetOccludee, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_occludee(bool)", AS_METHODPR(StaticSprite2D, SetOccludee, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetOccluder(bool)", AS_METHODPR(StaticSprite2D, SetOccluder, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_occluder(bool)", AS_METHODPR(StaticSprite2D, SetOccluder, (bool), void), AS_CALL_THISCALL);
    // void Drawable2D::SetOrderInLayer(int orderInLayer) | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetOrderInLayer(int)", AS_METHODPR(StaticSprite2D, SetOrderInLayer, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_orderInLayer(int)", AS_METHODPR(StaticSprite2D, SetOrderInLayer, (int), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetShadowDistance(float)", AS_METHODPR(StaticSprite2D, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_shadowDistance(float)", AS_METHODPR(StaticSprite2D, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetShadowMask(uint)", AS_METHODPR(StaticSprite2D, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_shadowMask(uint)", AS_METHODPR(StaticSprite2D, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetSortValue(float)", AS_METHODPR(StaticSprite2D, SetSortValue, (float), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetSprite(Sprite2D* sprite) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetSprite(Sprite2D@+)", AS_METHODPR(StaticSprite2D, SetSprite, (Sprite2D*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_sprite(Sprite2D@+)", AS_METHODPR(StaticSprite2D, SetSprite, (Sprite2D*), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetSpriteAttr(const ResourceRef& value) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetSpriteAttr(const ResourceRef&in)", AS_METHODPR(StaticSprite2D, SetSpriteAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetSwapXY(bool swapXY) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetSwapXY(bool)", AS_METHODPR(StaticSprite2D, SetSwapXY, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_swapXY(bool)", AS_METHODPR(StaticSprite2D, SetSwapXY, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetTemporary(bool)", AS_METHODPR(StaticSprite2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_temporary(bool)", AS_METHODPR(StaticSprite2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetTextureRect(const Rect& rect) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetTextureRect(const Rect&in)", AS_METHODPR(StaticSprite2D, SetTextureRect, (const Rect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_textureRect(const Rect&in)", AS_METHODPR(StaticSprite2D, SetTextureRect, (const Rect&), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetUseDrawRect(bool useDrawRect) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetUseDrawRect(bool)", AS_METHODPR(StaticSprite2D, SetUseDrawRect, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_useDrawRect(bool)", AS_METHODPR(StaticSprite2D, SetUseDrawRect, (bool), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetUseHotSpot(bool useHotSpot) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetUseHotSpot(bool)", AS_METHODPR(StaticSprite2D, SetUseHotSpot, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_useHotSpot(bool)", AS_METHODPR(StaticSprite2D, SetUseHotSpot, (bool), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetUseTextureRect(bool useTextureRect) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetUseTextureRect(bool)", AS_METHODPR(StaticSprite2D, SetUseTextureRect, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_useTextureRect(bool)", AS_METHODPR(StaticSprite2D, SetUseTextureRect, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetViewMask(uint)", AS_METHODPR(StaticSprite2D, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_viewMask(uint)", AS_METHODPR(StaticSprite2D, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetZone(Zone@+, bool = false)", AS_METHODPR(StaticSprite2D, SetZone, (Zone*, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void SetZoneMask(uint)", AS_METHODPR(StaticSprite2D, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_zoneMask(uint)", AS_METHODPR(StaticSprite2D, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    // explicit StaticSprite2D::StaticSprite2D(Context* context) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectBehaviour("StaticSprite2D", asBEHAVE_FACTORY, "StaticSprite2D@+ f()", AS_FUNCTION(StaticSprite2D_StaticSprite2D_Context), AS_CALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(StaticSprite2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(StaticSprite2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(StaticSprite2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(StaticSprite2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StaticSprite2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(StaticSprite2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void Update(const FrameInfo&in)", AS_METHODPR(StaticSprite2D, Update, (const FrameInfo&), void), AS_CALL_THISCALL);
    // virtual void Drawable::UpdateBatches(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void UpdateBatches(const FrameInfo&in)", AS_METHODPR(StaticSprite2D, UpdateBatches, (const FrameInfo&), void), AS_CALL_THISCALL);
    // virtual void Drawable::UpdateGeometry(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void UpdateGeometry(const FrameInfo&in)", AS_METHODPR(StaticSprite2D, UpdateGeometry, (const FrameInfo&), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("StaticSprite2D", "int WeakRefs() const", AS_METHODPR(StaticSprite2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "int get_weakRefs() const", AS_METHODPR(StaticSprite2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(StaticSprite2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(StaticSprite2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StaticSprite2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(StaticSprite2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("StretchableSprite2D", "void AddLight(Light@+)", AS_METHODPR(StretchableSprite2D, AddLight, (Light*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("StretchableSprite2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(StretchableSprite2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void AddVertexLight(Light@+)", AS_METHODPR(StretchableSprite2D, AddVertexLight, (Light*), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void AllocateNetworkState()", AS_METHODPR(StretchableSprite2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void ApplyAttributes()", AS_METHODPR(StretchableSprite2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(StretchableSprite2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool DrawOcclusion(OcclusionBuffer@+)", AS_METHODPR(StretchableSprite2D, DrawOcclusion, (OcclusionBuffer*), bool), AS_CALL_THISCALL);
    // float StaticSprite2D::GetAlpha() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "float GetAlpha() const", AS_METHODPR(StretchableSprite2D, GetAlpha, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "float get_alpha() const", AS_METHODPR(StretchableSprite2D, GetAlpha, () const, float), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool GetAnimationEnabled() const", AS_METHODPR(StretchableSprite2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_animationEnabled() const", AS_METHODPR(StretchableSprite2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Variant GetAttribute(uint) const", AS_METHODPR(StretchableSprite2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "Variant get_attributes(uint) const", AS_METHODPR(StretchableSprite2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(StretchableSprite2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(StretchableSprite2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(StretchableSprite2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(StretchableSprite2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(StretchableSprite2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(StretchableSprite2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(StretchableSprite2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(StretchableSprite2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // BlendMode StaticSprite2D::GetBlendMode() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "BlendMode GetBlendMode() const", AS_METHODPR(StretchableSprite2D, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "BlendMode get_blendMode() const", AS_METHODPR(StretchableSprite2D, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool GetBlockEvents() const", AS_METHODPR(StretchableSprite2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const IntRect& StretchableSprite2D::GetBorder() const | File: ../Urho2D/StretchableSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "const IntRect& GetBorder() const", AS_METHODPR(StretchableSprite2D, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "const IntRect& get_border() const", AS_METHODPR(StretchableSprite2D, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "const BoundingBox& GetBoundingBox() const", AS_METHODPR(StretchableSprite2D, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "const BoundingBox& get_boundingBox() const", AS_METHODPR(StretchableSprite2D, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool GetCastShadows() const", AS_METHODPR(StretchableSprite2D, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_castShadows() const", AS_METHODPR(StretchableSprite2D, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "const String& GetCategory() const", AS_METHODPR(StretchableSprite2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "const String& get_category() const", AS_METHODPR(StretchableSprite2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // const Color& StaticSprite2D::GetColor() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "const Color& GetColor() const", AS_METHODPR(StretchableSprite2D, GetColor, () const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "const Color& get_color() const", AS_METHODPR(StretchableSprite2D, GetColor, () const, const Color&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(StretchableSprite2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // Material* StaticSprite2D::GetCustomMaterial() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Material@+ GetCustomMaterial() const", AS_METHODPR(StretchableSprite2D, GetCustomMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "Material@+ get_customMaterial() const", AS_METHODPR(StretchableSprite2D, GetCustomMaterial, () const, Material*), AS_CALL_THISCALL);
    // ResourceRef StaticSprite2D::GetCustomMaterialAttr() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "ResourceRef GetCustomMaterialAttr() const", AS_METHODPR(StretchableSprite2D, GetCustomMaterialAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // float Drawable::GetDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "float GetDistance() const", AS_METHODPR(StretchableSprite2D, GetDistance, () const, float), AS_CALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "uint8 GetDrawableFlags() const", AS_METHODPR(StretchableSprite2D, GetDrawableFlags, () const, unsigned char), AS_CALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "float GetDrawDistance() const", AS_METHODPR(StretchableSprite2D, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "float get_drawDistance() const", AS_METHODPR(StretchableSprite2D, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    // const Rect& StaticSprite2D::GetDrawRect() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "const Rect& GetDrawRect() const", AS_METHODPR(StretchableSprite2D, GetDrawRect, () const, const Rect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "const Rect& get_drawRect() const", AS_METHODPR(StretchableSprite2D, GetDrawRect, () const, const Rect&), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(StretchableSprite2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Object@+ GetEventSender() const", AS_METHODPR(StretchableSprite2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Light@+ GetFirstLight() const", AS_METHODPR(StretchableSprite2D, GetFirstLight, () const, Light*), AS_CALL_THISCALL);
    // bool StaticSprite2D::GetFlipX() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool GetFlipX() const", AS_METHODPR(StretchableSprite2D, GetFlipX, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_flipX() const", AS_METHODPR(StretchableSprite2D, GetFlipX, () const, bool), AS_CALL_THISCALL);
    // bool StaticSprite2D::GetFlipY() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool GetFlipY() const", AS_METHODPR(StretchableSprite2D, GetFlipY, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_flipY() const", AS_METHODPR(StretchableSprite2D, GetFlipY, () const, bool), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(StretchableSprite2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(StretchableSprite2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(StretchableSprite2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "const VariantMap& get_globalVars() const", AS_METHODPR(StretchableSprite2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // const Vector2& StaticSprite2D::GetHotSpot() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "const Vector2& GetHotSpot() const", AS_METHODPR(StretchableSprite2D, GetHotSpot, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "const Vector2& get_hotSpot() const", AS_METHODPR(StretchableSprite2D, GetHotSpot, () const, const Vector2&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "uint GetID() const", AS_METHODPR(StretchableSprite2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "uint get_id() const", AS_METHODPR(StretchableSprite2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(StretchableSprite2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // int Drawable2D::GetLayer() const | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "int GetLayer() const", AS_METHODPR(StretchableSprite2D, GetLayer, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "int get_layer() const", AS_METHODPR(StretchableSprite2D, GetLayer, () const, int), AS_CALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "uint GetLightMask() const", AS_METHODPR(StretchableSprite2D, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "uint get_lightMask() const", AS_METHODPR(StretchableSprite2D, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Array<Light@>@ GetLights() const", AS_FUNCTION_OBJFIRST(StretchableSprite2D_GetLights_void), AS_CALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "float GetLodBias() const", AS_METHODPR(StretchableSprite2D, GetLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "float get_lodBias() const", AS_METHODPR(StretchableSprite2D, GetLodBias, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "float GetLodDistance() const", AS_METHODPR(StretchableSprite2D, GetLodDistance, () const, float), AS_CALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Geometry@+ GetLodGeometry(uint, uint)", AS_METHODPR(StretchableSprite2D, GetLodGeometry, (unsigned, unsigned), Geometry*), AS_CALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "uint GetMaxLights() const", AS_METHODPR(StretchableSprite2D, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "uint get_maxLights() const", AS_METHODPR(StretchableSprite2D, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "float GetMaxZ() const", AS_METHODPR(StretchableSprite2D, GetMaxZ, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "float GetMinZ() const", AS_METHODPR(StretchableSprite2D, GetMinZ, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Node@+ GetNode() const", AS_METHODPR(StretchableSprite2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "Node@+ get_node() const", AS_METHODPR(StretchableSprite2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "uint GetNumAttributes() const", AS_METHODPR(StretchableSprite2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "uint get_numAttributes() const", AS_METHODPR(StretchableSprite2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(StretchableSprite2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "uint GetNumOccluderTriangles()", AS_METHODPR(StretchableSprite2D, GetNumOccluderTriangles, (), unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(StretchableSprite2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(StretchableSprite2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(StretchableSprite2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // int Drawable2D::GetOrderInLayer() const | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "int GetOrderInLayer() const", AS_METHODPR(StretchableSprite2D, GetOrderInLayer, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "int get_orderInLayer() const", AS_METHODPR(StretchableSprite2D, GetOrderInLayer, () const, int), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Scene@+ GetScene() const", AS_METHODPR(StretchableSprite2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "float GetShadowDistance() const", AS_METHODPR(StretchableSprite2D, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "float get_shadowDistance() const", AS_METHODPR(StretchableSprite2D, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "uint GetShadowMask() const", AS_METHODPR(StretchableSprite2D, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "uint get_shadowMask() const", AS_METHODPR(StretchableSprite2D, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "float GetSortValue() const", AS_METHODPR(StretchableSprite2D, GetSortValue, () const, float), AS_CALL_THISCALL);
    // const Vector<SourceBatch2D>& Drawable2D::GetSourceBatches() | File: ../Urho2D/Drawable2D.h
    // Error: type "const Vector<SourceBatch2D>&" can not automatically bind
    // Sprite2D* StaticSprite2D::GetSprite() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Sprite2D@+ GetSprite() const", AS_METHODPR(StretchableSprite2D, GetSprite, () const, Sprite2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "Sprite2D@+ get_sprite() const", AS_METHODPR(StretchableSprite2D, GetSprite, () const, Sprite2D*), AS_CALL_THISCALL);
    // ResourceRef StaticSprite2D::GetSpriteAttr() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "ResourceRef GetSpriteAttr() const", AS_METHODPR(StretchableSprite2D, GetSpriteAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(StretchableSprite2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // bool StaticSprite2D::GetSwapXY() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool GetSwapXY() const", AS_METHODPR(StretchableSprite2D, GetSwapXY, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_swapXY() const", AS_METHODPR(StretchableSprite2D, GetSwapXY, () const, bool), AS_CALL_THISCALL);
    // const Rect& StaticSprite2D::GetTextureRect() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "const Rect& GetTextureRect() const", AS_METHODPR(StretchableSprite2D, GetTextureRect, () const, const Rect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "const Rect& get_textureRect() const", AS_METHODPR(StretchableSprite2D, GetTextureRect, () const, const Rect&), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "StringHash GetType() const", AS_METHODPR(StretchableSprite2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "StringHash get_type() const", AS_METHODPR(StretchableSprite2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "const String& GetTypeName() const", AS_METHODPR(StretchableSprite2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "const String& get_typeName() const", AS_METHODPR(StretchableSprite2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // virtual UpdateGeometryType Drawable::GetUpdateGeometryType() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "UpdateGeometryType GetUpdateGeometryType()", AS_METHODPR(StretchableSprite2D, GetUpdateGeometryType, (), UpdateGeometryType), AS_CALL_THISCALL);
    // bool StaticSprite2D::GetUseDrawRect() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool GetUseDrawRect() const", AS_METHODPR(StretchableSprite2D, GetUseDrawRect, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_useDrawRect() const", AS_METHODPR(StretchableSprite2D, GetUseDrawRect, () const, bool), AS_CALL_THISCALL);
    // bool StaticSprite2D::GetUseHotSpot() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool GetUseHotSpot() const", AS_METHODPR(StretchableSprite2D, GetUseHotSpot, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_useHotSpot() const", AS_METHODPR(StretchableSprite2D, GetUseHotSpot, () const, bool), AS_CALL_THISCALL);
    // bool StaticSprite2D::GetUseTextureRect() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool GetUseTextureRect() const", AS_METHODPR(StretchableSprite2D, GetUseTextureRect, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_useTextureRect() const", AS_METHODPR(StretchableSprite2D, GetUseTextureRect, () const, bool), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Array<Light@>@ GetVertexLights() const", AS_FUNCTION_OBJFIRST(StretchableSprite2D_GetVertexLights_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "uint GetViewMask() const", AS_METHODPR(StretchableSprite2D, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "uint get_viewMask() const", AS_METHODPR(StretchableSprite2D, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "const BoundingBox& GetWorldBoundingBox()", AS_METHODPR(StretchableSprite2D, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "const BoundingBox& get_worldBoundingBox()", AS_METHODPR(StretchableSprite2D, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "Zone@+ GetZone() const", AS_METHODPR(StretchableSprite2D, GetZone, () const, Zone*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "Zone@+ get_zone() const", AS_METHODPR(StretchableSprite2D, GetZone, () const, Zone*), AS_CALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "uint GetZoneMask() const", AS_METHODPR(StretchableSprite2D, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "uint get_zoneMask() const", AS_METHODPR(StretchableSprite2D, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool HasBasePass(uint) const", AS_METHODPR(StretchableSprite2D, HasBasePass, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool HasEventHandlers() const", AS_METHODPR(StretchableSprite2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(StretchableSprite2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(StretchableSprite2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool IsEnabled() const", AS_METHODPR(StretchableSprite2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_enabled() const", AS_METHODPR(StretchableSprite2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool IsEnabledEffective() const", AS_METHODPR(StretchableSprite2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_enabledEffective() const", AS_METHODPR(StretchableSprite2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(StretchableSprite2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool IsInView() const", AS_METHODPR(StretchableSprite2D, IsInView, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_inView() const", AS_METHODPR(StretchableSprite2D, IsInView, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool IsInView(Camera@+) const", AS_METHODPR(StretchableSprite2D, IsInView, (Camera*) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool IsInView(const FrameInfo&in, bool = false) const", AS_METHODPR(StretchableSprite2D, IsInView, (const FrameInfo&, bool) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool IsOccludee() const", AS_METHODPR(StretchableSprite2D, IsOccludee, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_occludee() const", AS_METHODPR(StretchableSprite2D, IsOccludee, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool IsOccluder() const", AS_METHODPR(StretchableSprite2D, IsOccluder, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_occluder() const", AS_METHODPR(StretchableSprite2D, IsOccluder, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool IsReplicated() const", AS_METHODPR(StretchableSprite2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_replicated() const", AS_METHODPR(StretchableSprite2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool IsTemporary() const", AS_METHODPR(StretchableSprite2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool get_temporary() const", AS_METHODPR(StretchableSprite2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool IsZoneDirty() const", AS_METHODPR(StretchableSprite2D, IsZoneDirty, () const, bool), AS_CALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void LimitLights()", AS_METHODPR(StretchableSprite2D, LimitLights, (), void), AS_CALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void LimitVertexLights(bool)", AS_METHODPR(StretchableSprite2D, LimitVertexLights, (bool), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool Load(Deserializer&)", AS_METHODPR(StretchableSprite2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(StretchableSprite2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(StretchableSprite2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void MarkForUpdate()", AS_METHODPR(StretchableSprite2D, MarkForUpdate, (), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void MarkInView(const FrameInfo&in)", AS_METHODPR(StretchableSprite2D, MarkInView, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void MarkInView(uint)", AS_METHODPR(StretchableSprite2D, MarkInView, (unsigned), void), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void MarkNetworkUpdate()", AS_METHODPR(StretchableSprite2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(StretchableSprite2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(StretchableSprite2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(StretchableSprite2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Drawable2D::OnSetEnabled() override | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void OnSetEnabled()", AS_METHODPR(StretchableSprite2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void PrepareNetworkUpdate()", AS_METHODPR(StretchableSprite2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) | File: ../Graphics/Drawable.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(StretchableSprite2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(StretchableSprite2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("StretchableSprite2D", "int Refs() const", AS_METHODPR(StretchableSprite2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "int get_refs() const", AS_METHODPR(StretchableSprite2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void StretchableSprite2D::RegisterObject(Context* context) | File: ../Urho2D/StretchableSprite2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("StretchableSprite2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(StretchableSprite2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void Remove()", AS_METHODPR(StretchableSprite2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(StretchableSprite2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void RemoveInstanceDefault()", AS_METHODPR(StretchableSprite2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void RemoveObjectAnimation()", AS_METHODPR(StretchableSprite2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void ResetToDefault()", AS_METHODPR(StretchableSprite2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool Save(Serializer&) const", AS_METHODPR(StretchableSprite2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool SaveDefaultAttributes() const", AS_METHODPR(StretchableSprite2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(StretchableSprite2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(StretchableSprite2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SendEvent(StringHash)", AS_METHODPR(StretchableSprite2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(StretchableSprite2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void StaticSprite2D::SetAlpha(float alpha) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetAlpha(float)", AS_METHODPR(StretchableSprite2D, SetAlpha, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_alpha(float)", AS_METHODPR(StretchableSprite2D, SetAlpha, (float), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetAnimationEnabled(bool)", AS_METHODPR(StretchableSprite2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_animationEnabled(bool)", AS_METHODPR(StretchableSprite2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetAnimationTime(float)", AS_METHODPR(StretchableSprite2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(StretchableSprite2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(StretchableSprite2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(StretchableSprite2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(StretchableSprite2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(StretchableSprite2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(StretchableSprite2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(StretchableSprite2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetBasePass(uint)", AS_METHODPR(StretchableSprite2D, SetBasePass, (unsigned), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetBlendMode(BlendMode blendMode) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetBlendMode(BlendMode)", AS_METHODPR(StretchableSprite2D, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_blendMode(BlendMode)", AS_METHODPR(StretchableSprite2D, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetBlockEvents(bool)", AS_METHODPR(StretchableSprite2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void StretchableSprite2D::SetBorder(const IntRect& border) | File: ../Urho2D/StretchableSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetBorder(const IntRect&in)", AS_METHODPR(StretchableSprite2D, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_border(const IntRect&in)", AS_METHODPR(StretchableSprite2D, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetCastShadows(bool)", AS_METHODPR(StretchableSprite2D, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_castShadows(bool)", AS_METHODPR(StretchableSprite2D, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetColor(const Color& color) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetColor(const Color&in)", AS_METHODPR(StretchableSprite2D, SetColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_color(const Color&in)", AS_METHODPR(StretchableSprite2D, SetColor, (const Color&), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetCustomMaterial(Material* customMaterial) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetCustomMaterial(Material@+)", AS_METHODPR(StretchableSprite2D, SetCustomMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_customMaterial(Material@+)", AS_METHODPR(StretchableSprite2D, SetCustomMaterial, (Material*), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetCustomMaterialAttr(const ResourceRef& value) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetCustomMaterialAttr(const ResourceRef&in)", AS_METHODPR(StretchableSprite2D, SetCustomMaterialAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetDrawDistance(float)", AS_METHODPR(StretchableSprite2D, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_drawDistance(float)", AS_METHODPR(StretchableSprite2D, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetDrawRect(const Rect& rect) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetDrawRect(const Rect&in)", AS_METHODPR(StretchableSprite2D, SetDrawRect, (const Rect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_drawRect(const Rect&in)", AS_METHODPR(StretchableSprite2D, SetDrawRect, (const Rect&), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetEnabled(bool)", AS_METHODPR(StretchableSprite2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_enabled(bool)", AS_METHODPR(StretchableSprite2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetFlip(bool flipX, bool flipY, bool swapXY=false) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetFlip(bool, bool, bool = false)", AS_METHODPR(StretchableSprite2D, SetFlip, (bool, bool, bool), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetFlipX(bool flipX) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetFlipX(bool)", AS_METHODPR(StretchableSprite2D, SetFlipX, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_flipX(bool)", AS_METHODPR(StretchableSprite2D, SetFlipX, (bool), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetFlipY(bool flipY) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetFlipY(bool)", AS_METHODPR(StretchableSprite2D, SetFlipY, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_flipY(bool)", AS_METHODPR(StretchableSprite2D, SetFlipY, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(StretchableSprite2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(StretchableSprite2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetHotSpot(const Vector2& hotspot) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetHotSpot(const Vector2&in)", AS_METHODPR(StretchableSprite2D, SetHotSpot, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_hotSpot(const Vector2&in)", AS_METHODPR(StretchableSprite2D, SetHotSpot, (const Vector2&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetInstanceDefault(bool)", AS_METHODPR(StretchableSprite2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(StretchableSprite2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Drawable2D::SetLayer(int layer) | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetLayer(int)", AS_METHODPR(StretchableSprite2D, SetLayer, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_layer(int)", AS_METHODPR(StretchableSprite2D, SetLayer, (int), void), AS_CALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetLightMask(uint)", AS_METHODPR(StretchableSprite2D, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_lightMask(uint)", AS_METHODPR(StretchableSprite2D, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetLodBias(float)", AS_METHODPR(StretchableSprite2D, SetLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_lodBias(float)", AS_METHODPR(StretchableSprite2D, SetLodBias, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetMaxLights(uint)", AS_METHODPR(StretchableSprite2D, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_maxLights(uint)", AS_METHODPR(StretchableSprite2D, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetMinMaxZ(float, float)", AS_METHODPR(StretchableSprite2D, SetMinMaxZ, (float, float), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(StretchableSprite2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(StretchableSprite2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(StretchableSprite2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetOccludee(bool)", AS_METHODPR(StretchableSprite2D, SetOccludee, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_occludee(bool)", AS_METHODPR(StretchableSprite2D, SetOccludee, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetOccluder(bool)", AS_METHODPR(StretchableSprite2D, SetOccluder, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_occluder(bool)", AS_METHODPR(StretchableSprite2D, SetOccluder, (bool), void), AS_CALL_THISCALL);
    // void Drawable2D::SetOrderInLayer(int orderInLayer) | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetOrderInLayer(int)", AS_METHODPR(StretchableSprite2D, SetOrderInLayer, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_orderInLayer(int)", AS_METHODPR(StretchableSprite2D, SetOrderInLayer, (int), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetShadowDistance(float)", AS_METHODPR(StretchableSprite2D, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_shadowDistance(float)", AS_METHODPR(StretchableSprite2D, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetShadowMask(uint)", AS_METHODPR(StretchableSprite2D, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_shadowMask(uint)", AS_METHODPR(StretchableSprite2D, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetSortValue(float)", AS_METHODPR(StretchableSprite2D, SetSortValue, (float), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetSprite(Sprite2D* sprite) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetSprite(Sprite2D@+)", AS_METHODPR(StretchableSprite2D, SetSprite, (Sprite2D*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_sprite(Sprite2D@+)", AS_METHODPR(StretchableSprite2D, SetSprite, (Sprite2D*), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetSpriteAttr(const ResourceRef& value) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetSpriteAttr(const ResourceRef&in)", AS_METHODPR(StretchableSprite2D, SetSpriteAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetSwapXY(bool swapXY) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetSwapXY(bool)", AS_METHODPR(StretchableSprite2D, SetSwapXY, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_swapXY(bool)", AS_METHODPR(StretchableSprite2D, SetSwapXY, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetTemporary(bool)", AS_METHODPR(StretchableSprite2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_temporary(bool)", AS_METHODPR(StretchableSprite2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetTextureRect(const Rect& rect) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetTextureRect(const Rect&in)", AS_METHODPR(StretchableSprite2D, SetTextureRect, (const Rect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_textureRect(const Rect&in)", AS_METHODPR(StretchableSprite2D, SetTextureRect, (const Rect&), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetUseDrawRect(bool useDrawRect) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetUseDrawRect(bool)", AS_METHODPR(StretchableSprite2D, SetUseDrawRect, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_useDrawRect(bool)", AS_METHODPR(StretchableSprite2D, SetUseDrawRect, (bool), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetUseHotSpot(bool useHotSpot) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetUseHotSpot(bool)", AS_METHODPR(StretchableSprite2D, SetUseHotSpot, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_useHotSpot(bool)", AS_METHODPR(StretchableSprite2D, SetUseHotSpot, (bool), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetUseTextureRect(bool useTextureRect) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetUseTextureRect(bool)", AS_METHODPR(StretchableSprite2D, SetUseTextureRect, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_useTextureRect(bool)", AS_METHODPR(StretchableSprite2D, SetUseTextureRect, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetViewMask(uint)", AS_METHODPR(StretchableSprite2D, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_viewMask(uint)", AS_METHODPR(StretchableSprite2D, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetZone(Zone@+, bool = false)", AS_METHODPR(StretchableSprite2D, SetZone, (Zone*, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void SetZoneMask(uint)", AS_METHODPR(StretchableSprite2D, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "void set_zoneMask(uint)", AS_METHODPR(StretchableSprite2D, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    // explicit StretchableSprite2D::StretchableSprite2D(Context* context) | File: ../Urho2D/StretchableSprite2D.h
    engine->RegisterObjectBehaviour("StretchableSprite2D", asBEHAVE_FACTORY, "StretchableSprite2D@+ f()", AS_FUNCTION(StretchableSprite2D_StretchableSprite2D_Context), AS_CALL_CDECL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(StretchableSprite2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(StretchableSprite2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(StretchableSprite2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(StretchableSprite2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(StretchableSprite2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void Update(const FrameInfo&in)", AS_METHODPR(StretchableSprite2D, Update, (const FrameInfo&), void), AS_CALL_THISCALL);
    // virtual void Drawable::UpdateBatches(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void UpdateBatches(const FrameInfo&in)", AS_METHODPR(StretchableSprite2D, UpdateBatches, (const FrameInfo&), void), AS_CALL_THISCALL);
    // virtual void Drawable::UpdateGeometry(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void UpdateGeometry(const FrameInfo&in)", AS_METHODPR(StretchableSprite2D, UpdateGeometry, (const FrameInfo&), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("StretchableSprite2D", "int WeakRefs() const", AS_METHODPR(StretchableSprite2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StretchableSprite2D", "int get_weakRefs() const", AS_METHODPR(StretchableSprite2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(StretchableSprite2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(StretchableSprite2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("StretchableSprite2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(StretchableSprite2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("String", "String& Append(const String&in)", AS_METHODPR(String, Append, (const String&), String&), AS_CALL_THISCALL);
    // String& String::Append(const char* str) | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // String& String::Append(char c) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& Append(int8)", AS_METHODPR(String, Append, (char), String&), AS_CALL_THISCALL);
    // String& String::Append(const char* str, unsigned length) | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // String& String::AppendUTF8(unsigned unicodeChar) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& AppendUTF8(uint)", AS_METHODPR(String, AppendUTF8, (unsigned), String&), AS_CALL_THISCALL);
    // String& String::AppendWithFormat(const char* formatString,...) | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // String& String::AppendWithFormatArgs(const char* formatString, va_list args) | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // char& String::At(unsigned index) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "int8& At(uint)", AS_METHODPR(String, At, (unsigned), char&), AS_CALL_THISCALL);
    // const char& String::At(unsigned index) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "const int8& At(uint) const", AS_METHODPR(String, At, (unsigned) const, const char&), AS_CALL_THISCALL);
    // unsigned String::AtUTF8(unsigned index) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "uint AtUTF8(uint) const", AS_METHODPR(String, AtUTF8, (unsigned) const, unsigned), AS_CALL_THISCALL);
    // char String::Back() const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "int8 Back() const", AS_METHODPR(String, Back, () const, char), AS_CALL_THISCALL);
    // Iterator String::Begin() | File: ../Container/Str.h
    // Error: type "Iterator" can not automatically bind
    // ConstIterator String::Begin() const | File: ../Container/Str.h
    // Error: type "ConstIterator" can not automatically bind
    // unsigned String::ByteOffsetUTF8(unsigned index) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "uint ByteOffsetUTF8(uint) const", AS_METHODPR(String, ByteOffsetUTF8, (unsigned) const, unsigned), AS_CALL_THISCALL);
    // unsigned String::Capacity() const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "uint Capacity() const", AS_METHODPR(String, Capacity, () const, unsigned), AS_CALL_THISCALL);
    // void String::Clear() | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void Clear()", AS_METHODPR(String, Clear, (), void), AS_CALL_THISCALL);
    // void String::Compact() | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void Compact()", AS_METHODPR(String, Compact, (), void), AS_CALL_THISCALL);
    // int String::Compare(const String& str, bool caseSensitive=true) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "int Compare(const String&in, bool = true) const", AS_METHODPR(String, Compare, (const String&, bool) const, int), AS_CALL_THISCALL);
    // int String::Compare(const char* str, bool caseSensitive=true) const | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // static int String::Compare(const char* lhs, const char* rhs, bool caseSensitive) | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // bool String::Contains(const String& str, bool caseSensitive=true) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "bool Contains(const String&in, bool = true) const", AS_METHODPR(String, Contains, (const String&, bool) const, bool), AS_CALL_THISCALL);
    // bool String::Contains(char c, bool caseSensitive=true) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "bool Contains(int8, bool = true) const", AS_METHODPR(String, Contains, (char, bool) const, bool), AS_CALL_THISCALL);
    // const char* String::CString() const | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // static unsigned String::CStringLength(const char* str) | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // static unsigned String::DecodeUTF8(const char*& src) | File: ../Container/Str.h
    // Error: type "const char*&" can not automatically bind
    // bool String::Empty() const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "bool Empty() const", AS_METHODPR(String, Empty, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("String", "bool get_empty() const", AS_METHODPR(String, Empty, () const, bool), AS_CALL_THISCALL);
    // static void String::EncodeUTF8(char*& dest, unsigned unicodeChar) | File: ../Container/Str.h
    // Error: type "char*&" can not automatically bind
    // Iterator String::End() | File: ../Container/Str.h
    // Error: type "Iterator" can not automatically bind
    // ConstIterator String::End() const | File: ../Container/Str.h
    // Error: type "ConstIterator" can not automatically bind
    // bool String::EndsWith(const String& str, bool caseSensitive=true) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "bool EndsWith(const String&in, bool = true) const", AS_METHODPR(String, EndsWith, (const String&, bool) const, bool), AS_CALL_THISCALL);
    // void String::Erase(unsigned pos, unsigned length=1) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void Erase(uint, uint = 1)", AS_METHODPR(String, Erase, (unsigned, unsigned), void), AS_CALL_THISCALL);
    // Iterator String::Erase(const Iterator& it) | File: ../Container/Str.h
    // Error: type "const Iterator&" can not automatically bind
    // Iterator String::Erase(const Iterator& start, const Iterator& end) | File: ../Container/Str.h
    // Error: type "const Iterator&" can not automatically bind
    // unsigned String::Find(const String& str, unsigned startPos=0, bool caseSensitive=true) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "uint Find(const String&in, uint = 0, bool = true) const", AS_METHODPR(String, Find, (const String&, unsigned, bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned String::Find(char c, unsigned startPos=0, bool caseSensitive=true) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "uint Find(int8, uint = 0, bool = true) const", AS_METHODPR(String, Find, (char, unsigned, bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned String::FindLast(const String& str, unsigned startPos=NPOS, bool caseSensitive=true) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "uint FindLast(const String&in, uint = String::NPOS, bool = true) const", AS_METHODPR(String, FindLast, (const String&, unsigned, bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned String::FindLast(char c, unsigned startPos=NPOS, bool caseSensitive=true) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "uint FindLast(int8, uint = String::NPOS, bool = true) const", AS_METHODPR(String, FindLast, (char, unsigned, bool) const, unsigned), AS_CALL_THISCALL);
    // char String::Front() const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "int8 Front() const", AS_METHODPR(String, Front, () const, char), AS_CALL_THISCALL);
    // void String::Insert(unsigned pos, const String& str) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void Insert(uint, const String&in)", AS_METHODPR(String, Insert, (unsigned, const String&), void), AS_CALL_THISCALL);
    // void String::Insert(unsigned pos, char c) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void Insert(uint, int8)", AS_METHODPR(String, Insert, (unsigned, char), void), AS_CALL_THISCALL);
    // Iterator String::Insert(const Iterator& dest, const String& str) | File: ../Container/Str.h
    // Error: type "const Iterator&" can not automatically bind
    // Iterator String::Insert(const Iterator& dest, const Iterator& start, const Iterator& end) | File: ../Container/Str.h
    // Error: type "const Iterator&" can not automatically bind
    // Iterator String::Insert(const Iterator& dest, char c) | File: ../Container/Str.h
    // Error: type "const Iterator&" can not automatically bind
    // void String::Join(const Vector<String>& subStrings, const String& glue) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void Join(Array<String>@+, const String&in)", AS_FUNCTION_OBJFIRST(String_Join_VectorString_String), AS_CALL_CDECL_OBJFIRST);
    // static String String::Joined(const Vector<String>& subStrings, const String& glue) | File: ../Container/Str.h
    // Not registered because have @manualbind mark
    // unsigned String::Length() const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "uint Length() const", AS_METHODPR(String, Length, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("String", "uint get_length() const", AS_METHODPR(String, Length, () const, unsigned), AS_CALL_THISCALL);
    // unsigned String::LengthUTF8() const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "uint LengthUTF8() const", AS_METHODPR(String, LengthUTF8, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("String", "uint get_utf8Length() const", AS_METHODPR(String, LengthUTF8, () const, unsigned), AS_CALL_THISCALL);
    // unsigned String::NextUTF8Char(unsigned& byteOffset) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "uint NextUTF8Char(uint&) const", AS_METHODPR(String, NextUTF8Char, (unsigned&) const, unsigned), AS_CALL_THISCALL);
    // String String::operator+(const String& rhs) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String opAdd(const String&in) const", AS_METHODPR(String, operator+, (const String&) const, String), AS_CALL_THISCALL);
    // String String::operator+(const char* rhs) const | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // String& String::operator+=(const String& rhs) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& opAddAssign(const String&in)", AS_METHODPR(String, operator+=, (const String&), String&), AS_CALL_THISCALL);
    // String& String::operator+=(const char* rhs) | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // String& String::operator+=(char rhs) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& opAddAssign(int8)", AS_METHODPR(String, operator+=, (char), String&), AS_CALL_THISCALL);
    // String& String::operator+=(int rhs) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& opAddAssign(int)", AS_METHODPR(String, operator+=, (int), String&), AS_CALL_THISCALL);
    // String& String::operator+=(short rhs) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& opAddAssign(int16)", AS_METHODPR(String, operator+=, (short), String&), AS_CALL_THISCALL);
    // String& String::operator+=(long rhs) | File: ../Container/Str.h
    // Not registered because have @nobind mark
    // String& String::operator+=(long long rhs) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& opAddAssign(int64)", AS_METHODPR(String, operator+=, (long long), String&), AS_CALL_THISCALL);
    // String& String::operator+=(unsigned rhs) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& opAddAssign(uint)", AS_METHODPR(String, operator+=, (unsigned), String&), AS_CALL_THISCALL);
    // String& String::operator+=(unsigned short rhs) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& opAddAssign(uint16)", AS_METHODPR(String, operator+=, (unsigned short), String&), AS_CALL_THISCALL);
    // String& String::operator+=(unsigned long rhs) | File: ../Container/Str.h
    // Not registered because have @nobind mark
    // String& String::operator+=(unsigned long long rhs) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& opAddAssign(uint64)", AS_METHODPR(String, operator+=, (unsigned long long), String&), AS_CALL_THISCALL);
    // String& String::operator+=(float rhs) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& opAddAssign(float)", AS_METHODPR(String, operator+=, (float), String&), AS_CALL_THISCALL);
    // String& String::operator+=(bool rhs) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& opAddAssign(bool)", AS_METHODPR(String, operator+=, (bool), String&), AS_CALL_THISCALL);
    // template<class T> String& String::operator+=(const T& rhs) | File: ../Container/Str.h
    // Not registered because template
    // String& String::operator=(const String& rhs) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String& opAssign(const String&in)", AS_METHODPR(String, operator=, (const String&), String&), AS_CALL_THISCALL);
    // String& String::operator=(String&& rhs) noexcept | File: ../Container/Str.h
    // Error: type "String&&" can not automatically bind
    // String& String::operator=(const char* rhs) | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // bool String::operator==(const String& rhs) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "bool opEquals(const String&in) const", AS_METHODPR(String, operator==, (const String&) const, bool), AS_CALL_THISCALL);
    // bool String::operator==(const char* rhs) const | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // char& String::operator[](unsigned index) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "int8& opIndex(uint)", AS_METHODPR(String, operator[], (unsigned), char&), AS_CALL_THISCALL);
    // const char& String::operator[](unsigned index) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "const int8& opIndex(uint) const", AS_METHODPR(String, operator[], (unsigned) const, const char&), AS_CALL_THISCALL);
    // void String::Replace(char replaceThis, char replaceWith, bool caseSensitive=true) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void Replace(int8, int8, bool = true)", AS_METHODPR(String, Replace, (char, char, bool), void), AS_CALL_THISCALL);
    // void String::Replace(const String& replaceThis, const String& replaceWith, bool caseSensitive=true) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void Replace(const String&in, const String&in, bool = true)", AS_METHODPR(String, Replace, (const String&, const String&, bool), void), AS_CALL_THISCALL);
    // void String::Replace(unsigned pos, unsigned length, const String& replaceWith) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void Replace(uint, uint, const String&in)", AS_METHODPR(String, Replace, (unsigned, unsigned, const String&), void), AS_CALL_THISCALL);
    // void String::Replace(unsigned pos, unsigned length, const char* replaceWith) | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // Iterator String::Replace(const Iterator& start, const Iterator& end, const String& replaceWith) | File: ../Container/Str.h
    // Error: type "const Iterator&" can not automatically bind
    // String String::Replaced(char replaceThis, char replaceWith, bool caseSensitive=true) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String Replaced(int8, int8, bool = true) const", AS_METHODPR(String, Replaced, (char, char, bool) const, String), AS_CALL_THISCALL);
    // String String::Replaced(const String& replaceThis, const String& replaceWith, bool caseSensitive=true) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String Replaced(const String&in, const String&in, bool = true) const", AS_METHODPR(String, Replaced, (const String&, const String&, bool) const, String), AS_CALL_THISCALL);
    // void String::ReplaceUTF8(unsigned index, unsigned unicodeChar) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void ReplaceUTF8(uint, uint)", AS_METHODPR(String, ReplaceUTF8, (unsigned, unsigned), void), AS_CALL_THISCALL);
    // void String::Reserve(unsigned newCapacity) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void Reserve(uint)", AS_METHODPR(String, Reserve, (unsigned), void), AS_CALL_THISCALL);
    // void String::Resize(unsigned newLength) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void Resize(uint)", AS_METHODPR(String, Resize, (unsigned), void), AS_CALL_THISCALL);
    // void String::SetUTF8FromLatin1(const char* str) | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // void String::SetUTF8FromWChar(const wchar_t* str) | File: ../Container/Str.h
    // Error: type "const wchar_t*" can not automatically bind
    // Vector<String> String::Split(char separator, bool keepEmptyStrings=false) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "Array<String>@ Split(int8, bool = false) const", AS_FUNCTION_OBJFIRST(String_Split_char_bool), AS_CALL_CDECL_OBJFIRST);
    // static Vector<String> String::Split(const char* str, char separator, bool keepEmptyStrings=false) | File: ../Container/Str.h
    // Error: type "const char*" can not automatically bind
    // bool String::StartsWith(const String& str, bool caseSensitive=true) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "bool StartsWith(const String&in, bool = true) const", AS_METHODPR(String, StartsWith, (const String&, bool) const, bool), AS_CALL_THISCALL);
    // String::String(const String& str) | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(const String&in)", AS_FUNCTION_OBJFIRST(String_String_String), AS_CALL_CDECL_OBJFIRST);
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
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(int)", AS_FUNCTION_OBJFIRST(String_String_int), AS_CALL_CDECL_OBJFIRST);
    // explicit String::String(short value) | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(int16)", AS_FUNCTION_OBJFIRST(String_String_short), AS_CALL_CDECL_OBJFIRST);
    // explicit String::String(long value) | File: ../Container/Str.h
    // Not registered because have @nobind mark
    // explicit String::String(long long value) | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(int64)", AS_FUNCTION_OBJFIRST(String_String_longlong), AS_CALL_CDECL_OBJFIRST);
    // explicit String::String(unsigned value) | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(uint)", AS_FUNCTION_OBJFIRST(String_String_unsigned), AS_CALL_CDECL_OBJFIRST);
    // explicit String::String(unsigned short value) | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(uint16)", AS_FUNCTION_OBJFIRST(String_String_unsignedshort), AS_CALL_CDECL_OBJFIRST);
    // explicit String::String(unsigned long value) | File: ../Container/Str.h
    // Not registered because have @nobind mark
    // explicit String::String(unsigned long long value) | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(uint64)", AS_FUNCTION_OBJFIRST(String_String_unsignedlonglong), AS_CALL_CDECL_OBJFIRST);
    // explicit String::String(float value) | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(float)", AS_FUNCTION_OBJFIRST(String_String_float), AS_CALL_CDECL_OBJFIRST);
    // explicit String::String(double value) | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(double)", AS_FUNCTION_OBJFIRST(String_String_double), AS_CALL_CDECL_OBJFIRST);
    // explicit String::String(bool value) | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(bool)", AS_FUNCTION_OBJFIRST(String_String_bool), AS_CALL_CDECL_OBJFIRST);
    // explicit String::String(char value) | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(int8)", AS_FUNCTION_OBJFIRST(String_String_char), AS_CALL_CDECL_OBJFIRST);
    // explicit String::String(char value, unsigned length) | File: ../Container/Str.h
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(int8, uint)", AS_FUNCTION_OBJFIRST(String_String_char_unsigned), AS_CALL_CDECL_OBJFIRST);
    // template<class T> explicit String::String(const T& value) | File: ../Container/Str.h
    // Not registered because template
    // String String::Substring(unsigned pos) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String Substring(uint) const", AS_METHODPR(String, Substring, (unsigned) const, String), AS_CALL_THISCALL);
    // String String::Substring(unsigned pos, unsigned length) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String Substring(uint, uint) const", AS_METHODPR(String, Substring, (unsigned, unsigned) const, String), AS_CALL_THISCALL);
    // String String::SubstringUTF8(unsigned pos) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String SubstringUTF8(uint) const", AS_METHODPR(String, SubstringUTF8, (unsigned) const, String), AS_CALL_THISCALL);
    // String String::SubstringUTF8(unsigned pos, unsigned length) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String SubstringUTF8(uint, uint) const", AS_METHODPR(String, SubstringUTF8, (unsigned, unsigned) const, String), AS_CALL_THISCALL);
    // void String::Swap(String& str) | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "void Swap(String&)", AS_METHODPR(String, Swap, (String&), void), AS_CALL_THISCALL);
    // unsigned String::ToHash() const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "uint ToHash() const", AS_METHODPR(String, ToHash, () const, unsigned), AS_CALL_THISCALL);
    // String String::ToLower() const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String ToLower() const", AS_METHODPR(String, ToLower, () const, String), AS_CALL_THISCALL);
    // String String::ToUpper() const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String ToUpper() const", AS_METHODPR(String, ToUpper, () const, String), AS_CALL_THISCALL);
    // String String::Trimmed() const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "String Trimmed() const", AS_METHODPR(String, Trimmed, () const, String), AS_CALL_THISCALL);
    // bool String::operator<(const String& rhs) const | File: ../Container/Str.h
    // bool String::operator>(const String& rhs) const | File: ../Container/Str.h
    engine->RegisterObjectMethod("String", "int opCmp(const String&in) const", AS_FUNCTION_OBJFIRST(String_Comparison), AS_CALL_CDECL_OBJFIRST);
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
    engine->RegisterObjectMethod("StringHash", "bool opConv() const", AS_METHODPR(StringHash, operator bool, () const, bool), AS_CALL_THISCALL);
    // StringHash StringHash::operator+(const StringHash& rhs) const | File: ../Math/StringHash.h
    engine->RegisterObjectMethod("StringHash", "StringHash opAdd(const StringHash&in) const", AS_METHODPR(StringHash, operator+, (const StringHash&) const, StringHash), AS_CALL_THISCALL);
    // StringHash& StringHash::operator+=(const StringHash& rhs) | File: ../Math/StringHash.h
    engine->RegisterObjectMethod("StringHash", "StringHash& opAddAssign(const StringHash&in)", AS_METHODPR(StringHash, operator+=, (const StringHash&), StringHash&), AS_CALL_THISCALL);
    // StringHash& StringHash::operator=(const StringHash& rhs) noexcept=default | File: ../Math/StringHash.h
    engine->RegisterObjectMethod("StringHash", "StringHash& opAssign(const StringHash&in)", AS_METHODPR(StringHash, operator=, (const StringHash&), StringHash&), AS_CALL_THISCALL);
    // bool StringHash::operator==(const StringHash& rhs) const | File: ../Math/StringHash.h
    engine->RegisterObjectMethod("StringHash", "bool opEquals(const StringHash&in) const", AS_METHODPR(StringHash, operator==, (const StringHash&) const, bool), AS_CALL_THISCALL);
    // String StringHash::Reverse() const | File: ../Math/StringHash.h
    engine->RegisterObjectMethod("StringHash", "String Reverse() const", AS_METHODPR(StringHash, Reverse, () const, String), AS_CALL_THISCALL);
    // StringHash::StringHash(const StringHash& rhs) noexcept=default | File: ../Math/StringHash.h
    engine->RegisterObjectBehaviour("StringHash", asBEHAVE_CONSTRUCT, "void f(const StringHash&in)", AS_FUNCTION_OBJFIRST(StringHash_StringHash_StringHash), AS_CALL_CDECL_OBJFIRST);
    // explicit StringHash::StringHash(unsigned value) noexcept | File: ../Math/StringHash.h
    engine->RegisterObjectBehaviour("StringHash", asBEHAVE_CONSTRUCT, "void f(uint)", AS_FUNCTION_OBJFIRST(StringHash_StringHash_unsigned), AS_CALL_CDECL_OBJFIRST);
    // StringHash::StringHash(const char* str) noexcept | File: ../Math/StringHash.h
    // Error: type "const char*" can not automatically bind
    // StringHash::StringHash(const String& str) noexcept | File: ../Math/StringHash.h
    engine->RegisterObjectBehaviour("StringHash", asBEHAVE_CONSTRUCT, "void f(const String&in)", AS_FUNCTION_OBJFIRST(StringHash_StringHash_String), AS_CALL_CDECL_OBJFIRST);
    // unsigned StringHash::ToHash() const | File: ../Math/StringHash.h
    engine->RegisterObjectMethod("StringHash", "uint ToHash() const", AS_METHODPR(StringHash, ToHash, () const, unsigned), AS_CALL_THISCALL);
    // String StringHash::ToString() const | File: ../Math/StringHash.h
    engine->RegisterObjectMethod("StringHash", "String ToString() const", AS_METHODPR(StringHash, ToString, () const, String), AS_CALL_THISCALL);
    // unsigned StringHash::Value() const | File: ../Math/StringHash.h
    engine->RegisterObjectMethod("StringHash", "uint Value() const", AS_METHODPR(StringHash, Value, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("StringHash", "uint get_value() const", AS_METHODPR(StringHash, Value, () const, unsigned), AS_CALL_THISCALL);
    // bool StringHash::operator<(const StringHash& rhs) const | File: ../Math/StringHash.h
    // bool StringHash::operator>(const StringHash& rhs) const | File: ../Math/StringHash.h
    engine->RegisterObjectMethod("StringHash", "int opCmp(const StringHash&in) const", AS_FUNCTION_OBJFIRST(StringHash_Comparison), AS_CALL_CDECL_OBJFIRST);
#ifdef REGISTER_MANUAL_PART_StringHash
    REGISTER_MANUAL_PART_StringHash(StringHash, "StringHash")
#endif

    // bool StringHashRegister::Contains(const StringHash& hash) const | File: ../Core/StringHashRegister.h
    engine->RegisterObjectMethod("StringHashRegister", "bool Contains(const StringHash&in) const", AS_METHODPR(StringHashRegister, Contains, (const StringHash&) const, bool), AS_CALL_THISCALL);
    // const StringMap& StringHashRegister::GetInternalMap() const | File: ../Core/StringHashRegister.h
    // Error: type "const StringMap&" can not automatically bind
    // const String& StringHashRegister::GetString(const StringHash& hash) const | File: ../Core/StringHashRegister.h
    engine->RegisterObjectMethod("StringHashRegister", "const String& GetString(const StringHash&in) const", AS_METHODPR(StringHashRegister, GetString, (const StringHash&) const, const String&), AS_CALL_THISCALL);
    // String StringHashRegister::GetStringCopy(const StringHash& hash) const | File: ../Core/StringHashRegister.h
    engine->RegisterObjectMethod("StringHashRegister", "String GetStringCopy(const StringHash&in) const", AS_METHODPR(StringHashRegister, GetStringCopy, (const StringHash&) const, String), AS_CALL_THISCALL);
    // StringHash StringHashRegister::RegisterString(const StringHash& hash, const char* string) | File: ../Core/StringHashRegister.h
    // Error: type "const char*" can not automatically bind
    // StringHash StringHashRegister::RegisterString(const char* string) | File: ../Core/StringHashRegister.h
    // Error: type "const char*" can not automatically bind
    // StringHashRegister::StringHashRegister(bool threadSafe) | File: ../Core/StringHashRegister.h
    engine->RegisterObjectBehaviour("StringHashRegister", asBEHAVE_CONSTRUCT, "void f(bool)", AS_FUNCTION_OBJFIRST(StringHashRegister_StringHashRegister_bool), AS_CALL_CDECL_OBJFIRST);
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
    engine->RegisterObjectMethod("SourceBatch", "SourceBatch& opAssign(const SourceBatch&in)", AS_METHODPR(SourceBatch, operator=, (const SourceBatch&), SourceBatch&), AS_CALL_THISCALL);
    // SourceBatch::SourceBatch(const SourceBatch& batch) | File: ../Graphics/Drawable.h
    engine->RegisterObjectBehaviour("SourceBatch", asBEHAVE_CONSTRUCT, "void f(const SourceBatch&in)", AS_FUNCTION_OBJFIRST(SourceBatch_SourceBatch_SourceBatch), AS_CALL_CDECL_OBJFIRST);
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
    engine->RegisterObjectBehaviour("StoredLogMessage", asBEHAVE_CONSTRUCT, "void f(const String&in, int, bool)", AS_FUNCTION_OBJFIRST(StoredLogMessage_StoredLogMessage_String_int_bool), AS_CALL_CDECL_OBJFIRST);
    // StoredLogMessage& StoredLogMessage::operator=(const StoredLogMessage&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<StoredLogMessage>(engine, "StoredLogMessage");
#ifdef REGISTER_MANUAL_PART_StoredLogMessage
    REGISTER_MANUAL_PART_StoredLogMessage(StoredLogMessage, "StoredLogMessage")
#endif

}

}
