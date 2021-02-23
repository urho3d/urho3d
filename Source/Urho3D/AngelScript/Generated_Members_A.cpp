// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// StringVector Deserializer::ReadStringVector() | File: ../IO/Deserializer.h
static CScriptArray* AbstractFile_ReadStringVector_void(AbstractFile* ptr)
{
    StringVector result = ptr->ReadStringVector();
    return VectorToArray<String>(result, "Array<String>");
}

// bool Serializer::WriteStringVector(const StringVector& value) | File: ../IO/Serializer.h
static bool AbstractFile_WriteStringVector_StringVector(AbstractFile* ptr, CScriptArray* value_conv)
{
    StringVector value = ArrayToVector<String>(value_conv);
    bool result = ptr->WriteStringVector(value);
    return result;
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Animatable_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Animatable* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit AnimatedModel::AnimatedModel(Context* context) | File: ../Graphics/AnimatedModel.h
static AnimatedModel* AnimatedModel_AnimatedModel_Context()
{
    return new AnimatedModel(GetScriptContext());
}

// const Vector<SharedPtr<AnimationState>>& AnimatedModel::GetAnimationStates() const | File: ../Graphics/AnimatedModel.h
static CScriptArray* AnimatedModel_GetAnimationStates_void(AnimatedModel* ptr)
{
    const Vector<SharedPtr<AnimationState>>& result = ptr->GetAnimationStates();
    return VectorToHandleArray(result, "Array<AnimationState@>");
}

// const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
static CScriptArray* AnimatedModel_GetLights_void(AnimatedModel* ptr)
{
    const PODVector<Light*>& result = ptr->GetLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// const Vector<SharedPtr<VertexBuffer>>& AnimatedModel::GetMorphVertexBuffers() const | File: ../Graphics/AnimatedModel.h
static CScriptArray* AnimatedModel_GetMorphVertexBuffers_void(AnimatedModel* ptr)
{
    const Vector<SharedPtr<VertexBuffer>>& result = ptr->GetMorphVertexBuffers();
    return VectorToHandleArray(result, "Array<VertexBuffer@>");
}

// const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
static CScriptArray* AnimatedModel_GetVertexLights_void(AnimatedModel* ptr)
{
    const PODVector<Light*>& result = ptr->GetVertexLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void AnimatedModel_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(AnimatedModel* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

#ifdef URHO3D_URHO2D
// explicit AnimatedSprite2D::AnimatedSprite2D(Context* context) | File: ../Urho2D/AnimatedSprite2D.h
static AnimatedSprite2D* AnimatedSprite2D_AnimatedSprite2D_Context()
{
    return new AnimatedSprite2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
static CScriptArray* AnimatedSprite2D_GetLights_void(AnimatedSprite2D* ptr)
{
    const PODVector<Light*>& result = ptr->GetLights();
    return VectorToHandleArray(result, "Array<Light@>");
}
#endif

#ifdef URHO3D_URHO2D
// const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
static CScriptArray* AnimatedSprite2D_GetVertexLights_void(AnimatedSprite2D* ptr)
{
    const PODVector<Light*>& result = ptr->GetVertexLights();
    return VectorToHandleArray(result, "Array<Light@>");
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void AnimatedSprite2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(AnimatedSprite2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

// explicit Animation::Animation(Context* context) | File: ../Graphics/Animation.h
static Animation* Animation_Animation_Context()
{
    return new Animation(GetScriptContext());
}

// SharedPtr<Animation> Animation::Clone(const String& cloneName=String::EMPTY) const | File: ../Graphics/Animation.h
static Animation* Animation_Clone_String(Animation* ptr, const String& cloneName)
{
    SharedPtr<Animation> result = ptr->Clone(cloneName);
    return result.Detach();
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Animation_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Animation* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit AnimationController::AnimationController(Context* context) | File: ../Graphics/AnimationController.h
static AnimationController* AnimationController_AnimationController_Context()
{
    return new AnimationController(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void AnimationController_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(AnimationController* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

#ifdef URHO3D_URHO2D
// explicit AnimationSet2D::AnimationSet2D(Context* context) | File: ../Urho2D/AnimationSet2D.h
static AnimationSet2D* AnimationSet2D_AnimationSet2D_Context()
{
    return new AnimationSet2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void AnimationSet2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(AnimationSet2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

// AnimationState::AnimationState(AnimatedModel* model, Animation* animation) | File: ../Graphics/AnimationState.h
static AnimationState* AnimationState_AnimationState_AnimatedModel_Animation(AnimatedModel *model, Animation *animation)
{
    return new AnimationState(model, animation);
}

// AnimationState::AnimationState(Node* node, Animation* animation) | File: ../Graphics/AnimationState.h
static AnimationState* AnimationState_AnimationState_Node_Animation(Node *node, Animation *animation)
{
    return new AnimationState(node, animation);
}

// AreaAllocator::AreaAllocator(int width, int height, bool fastMode=true) | File: ../Math/AreaAllocator.h
static void AreaAllocator_AreaAllocator_int_int_bool(AreaAllocator* ptr, int width, int height, bool fastMode=true)
{
    new(ptr) AreaAllocator(width, height, fastMode);
}

// AreaAllocator::AreaAllocator(int width, int height, int maxWidth, int maxHeight, bool fastMode=true) | File: ../Math/AreaAllocator.h
static void AreaAllocator_AreaAllocator_int_int_int_int_bool(AreaAllocator* ptr, int width, int height, int maxWidth, int maxHeight, bool fastMode=true)
{
    new(ptr) AreaAllocator(width, height, maxWidth, maxHeight, fastMode);
}

// AttributeAnimationInfo::AttributeAnimationInfo(Animatable* animatable, const AttributeInfo& attributeInfo, ValueAnimation* attributeAnimation, WrapMode wrapMode, float speed) | File: ../Scene/Animatable.h
static AttributeAnimationInfo* AttributeAnimationInfo_AttributeAnimationInfo_Animatable_AttributeInfo_ValueAnimation_WrapMode_float(Animatable *animatable, const AttributeInfo &attributeInfo, ValueAnimation *attributeAnimation, WrapMode wrapMode, float speed)
{
    return new AttributeAnimationInfo(animatable, attributeInfo, attributeAnimation, wrapMode, speed);
}

// AttributeAnimationInfo::AttributeAnimationInfo(const AttributeAnimationInfo& other) | File: ../Scene/Animatable.h
static AttributeAnimationInfo* AttributeAnimationInfo_AttributeAnimationInfo_AttributeAnimationInfo(const AttributeAnimationInfo &other)
{
    return new AttributeAnimationInfo(other);
}

// explicit Audio::Audio(Context* context) | File: ../Audio/Audio.h
static Audio* Audio_Audio_Context()
{
    return new Audio(GetScriptContext());
}

// const PODVector<SoundSource*>& Audio::GetSoundSources() const | File: ../Audio/Audio.h
static CScriptArray* Audio_GetSoundSources_void(Audio* ptr)
{
    const PODVector<SoundSource*>& result = ptr->GetSoundSources();
    return VectorToHandleArray(result, "Array<SoundSource@>");
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Audio_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Audio* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// AnimationControl::AnimationControl() | File: ../Graphics/AnimationController.h
static AnimationControl* AnimationControl_AnimationControl_void()
{
    return new AnimationControl();
}

// AnimationTrack::AnimationTrack() | File: ../Graphics/Animation.h
static AnimationTrack* AnimationTrack_AnimationTrack_void()
{
    return new AnimationTrack();
}

void ASRegisterGenerated_Members_A(asIScriptEngine* engine)
{
    // virtual unsigned Deserializer::GetChecksum() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "uint GetChecksum()", AS_METHODPR(AbstractFile, GetChecksum, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AbstractFile", "uint get_checksum()", AS_METHODPR(AbstractFile, GetChecksum, (), unsigned), AS_CALL_THISCALL);
    // const String& AbstractFile::GetName() const override | File: ../IO/AbstractFile.h
    engine->RegisterObjectMethod("AbstractFile", "const String& GetName() const", AS_METHODPR(AbstractFile, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AbstractFile", "const String& get_name() const", AS_METHODPR(AbstractFile, GetName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Deserializer::GetPosition() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "uint GetPosition() const", AS_METHODPR(AbstractFile, GetPosition, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AbstractFile", "uint get_position() const", AS_METHODPR(AbstractFile, GetPosition, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Deserializer::GetSize() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "uint GetSize() const", AS_METHODPR(AbstractFile, GetSize, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AbstractFile", "uint get_size() const", AS_METHODPR(AbstractFile, GetSize, () const, unsigned), AS_CALL_THISCALL);
    // virtual bool Deserializer::IsEof() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool IsEof() const", AS_METHODPR(AbstractFile, IsEof, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AbstractFile", "bool get_eof() const", AS_METHODPR(AbstractFile, IsEof, () const, bool), AS_CALL_THISCALL);
    // virtual unsigned Deserializer::Read(void* dest, unsigned size)=0 | File: ../IO/Deserializer.h
    // Error: type "void*" can not automatically bind
    // bool Deserializer::ReadBool() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool ReadBool()", AS_METHODPR(AbstractFile, ReadBool, (), bool), AS_CALL_THISCALL);
    // BoundingBox Deserializer::ReadBoundingBox() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "BoundingBox ReadBoundingBox()", AS_METHODPR(AbstractFile, ReadBoundingBox, (), BoundingBox), AS_CALL_THISCALL);
    // PODVector<unsigned char> Deserializer::ReadBuffer() | File: ../IO/Deserializer.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // signed char Deserializer::ReadByte() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "int8 ReadByte()", AS_METHODPR(AbstractFile, ReadByte, (), signed char), AS_CALL_THISCALL);
    // Color Deserializer::ReadColor() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Color ReadColor()", AS_METHODPR(AbstractFile, ReadColor, (), Color), AS_CALL_THISCALL);
    // double Deserializer::ReadDouble() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "double ReadDouble()", AS_METHODPR(AbstractFile, ReadDouble, (), double), AS_CALL_THISCALL);
    // String Deserializer::ReadFileID() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "String ReadFileID()", AS_METHODPR(AbstractFile, ReadFileID, (), String), AS_CALL_THISCALL);
    // float Deserializer::ReadFloat() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "float ReadFloat()", AS_METHODPR(AbstractFile, ReadFloat, (), float), AS_CALL_THISCALL);
    // int Deserializer::ReadInt() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "int ReadInt()", AS_METHODPR(AbstractFile, ReadInt, (), int), AS_CALL_THISCALL);
    // long long Deserializer::ReadInt64() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "int64 ReadInt64()", AS_METHODPR(AbstractFile, ReadInt64, (), long long), AS_CALL_THISCALL);
    // IntRect Deserializer::ReadIntRect() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "IntRect ReadIntRect()", AS_METHODPR(AbstractFile, ReadIntRect, (), IntRect), AS_CALL_THISCALL);
    // IntVector2 Deserializer::ReadIntVector2() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "IntVector2 ReadIntVector2()", AS_METHODPR(AbstractFile, ReadIntVector2, (), IntVector2), AS_CALL_THISCALL);
    // IntVector3 Deserializer::ReadIntVector3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "IntVector3 ReadIntVector3()", AS_METHODPR(AbstractFile, ReadIntVector3, (), IntVector3), AS_CALL_THISCALL);
    // String Deserializer::ReadLine() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "String ReadLine()", AS_METHODPR(AbstractFile, ReadLine, (), String), AS_CALL_THISCALL);
    // Matrix3 Deserializer::ReadMatrix3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Matrix3 ReadMatrix3()", AS_METHODPR(AbstractFile, ReadMatrix3, (), Matrix3), AS_CALL_THISCALL);
    // Matrix3x4 Deserializer::ReadMatrix3x4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Matrix3x4 ReadMatrix3x4()", AS_METHODPR(AbstractFile, ReadMatrix3x4, (), Matrix3x4), AS_CALL_THISCALL);
    // Matrix4 Deserializer::ReadMatrix4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Matrix4 ReadMatrix4()", AS_METHODPR(AbstractFile, ReadMatrix4, (), Matrix4), AS_CALL_THISCALL);
    // unsigned Deserializer::ReadNetID() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "uint ReadNetID()", AS_METHODPR(AbstractFile, ReadNetID, (), unsigned), AS_CALL_THISCALL);
    // Quaternion Deserializer::ReadPackedQuaternion() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Quaternion ReadPackedQuaternion()", AS_METHODPR(AbstractFile, ReadPackedQuaternion, (), Quaternion), AS_CALL_THISCALL);
    // Vector3 Deserializer::ReadPackedVector3(float maxAbsCoord) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Vector3 ReadPackedVector3(float)", AS_METHODPR(AbstractFile, ReadPackedVector3, (float), Vector3), AS_CALL_THISCALL);
    // Quaternion Deserializer::ReadQuaternion() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Quaternion ReadQuaternion()", AS_METHODPR(AbstractFile, ReadQuaternion, (), Quaternion), AS_CALL_THISCALL);
    // Rect Deserializer::ReadRect() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Rect ReadRect()", AS_METHODPR(AbstractFile, ReadRect, (), Rect), AS_CALL_THISCALL);
    // ResourceRef Deserializer::ReadResourceRef() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "ResourceRef ReadResourceRef()", AS_METHODPR(AbstractFile, ReadResourceRef, (), ResourceRef), AS_CALL_THISCALL);
    // ResourceRefList Deserializer::ReadResourceRefList() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "ResourceRefList ReadResourceRefList()", AS_METHODPR(AbstractFile, ReadResourceRefList, (), ResourceRefList), AS_CALL_THISCALL);
    // short Deserializer::ReadShort() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "int16 ReadShort()", AS_METHODPR(AbstractFile, ReadShort, (), short), AS_CALL_THISCALL);
    // String Deserializer::ReadString() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "String ReadString()", AS_METHODPR(AbstractFile, ReadString, (), String), AS_CALL_THISCALL);
    // StringHash Deserializer::ReadStringHash() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "StringHash ReadStringHash()", AS_METHODPR(AbstractFile, ReadStringHash, (), StringHash), AS_CALL_THISCALL);
    // StringVector Deserializer::ReadStringVector() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Array<String>@ ReadStringVector()", AS_FUNCTION_OBJFIRST(AbstractFile_ReadStringVector_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned char Deserializer::ReadUByte() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "uint8 ReadUByte()", AS_METHODPR(AbstractFile, ReadUByte, (), unsigned char), AS_CALL_THISCALL);
    // unsigned Deserializer::ReadUInt() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "uint ReadUInt()", AS_METHODPR(AbstractFile, ReadUInt, (), unsigned), AS_CALL_THISCALL);
    // unsigned long long Deserializer::ReadUInt64() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "uint64 ReadUInt64()", AS_METHODPR(AbstractFile, ReadUInt64, (), unsigned long long), AS_CALL_THISCALL);
    // unsigned short Deserializer::ReadUShort() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "uint16 ReadUShort()", AS_METHODPR(AbstractFile, ReadUShort, (), unsigned short), AS_CALL_THISCALL);
    // Variant Deserializer::ReadVariant() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Variant ReadVariant()", AS_METHODPR(AbstractFile, ReadVariant, (), Variant), AS_CALL_THISCALL);
    // Variant Deserializer::ReadVariant(VariantType type) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Variant ReadVariant(VariantType)", AS_METHODPR(AbstractFile, ReadVariant, (VariantType), Variant), AS_CALL_THISCALL);
    // VariantMap Deserializer::ReadVariantMap() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "VariantMap ReadVariantMap()", AS_METHODPR(AbstractFile, ReadVariantMap, (), VariantMap), AS_CALL_THISCALL);
    // VariantVector Deserializer::ReadVariantVector() | File: ../IO/Deserializer.h
    // Error: type "VariantVector" can not automatically bind
    // Vector2 Deserializer::ReadVector2() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Vector2 ReadVector2()", AS_METHODPR(AbstractFile, ReadVector2, (), Vector2), AS_CALL_THISCALL);
    // Vector3 Deserializer::ReadVector3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Vector3 ReadVector3()", AS_METHODPR(AbstractFile, ReadVector3, (), Vector3), AS_CALL_THISCALL);
    // Vector4 Deserializer::ReadVector4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Vector4 ReadVector4()", AS_METHODPR(AbstractFile, ReadVector4, (), Vector4), AS_CALL_THISCALL);
    // unsigned Deserializer::ReadVLE() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "uint ReadVLE()", AS_METHODPR(AbstractFile, ReadVLE, (), unsigned), AS_CALL_THISCALL);
    // virtual unsigned Deserializer::Seek(unsigned position)=0 | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "uint Seek(uint)", AS_METHODPR(AbstractFile, Seek, (unsigned), unsigned), AS_CALL_THISCALL);
    // unsigned Deserializer::SeekRelative(int delta) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "uint SeekRelative(int)", AS_METHODPR(AbstractFile, SeekRelative, (int), unsigned), AS_CALL_THISCALL);
    // virtual void AbstractFile::SetName(const String& name) | File: ../IO/AbstractFile.h
    engine->RegisterObjectMethod("AbstractFile", "void SetName(const String&in)", AS_METHODPR(AbstractFile, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AbstractFile", "void set_name(const String&in)", AS_METHODPR(AbstractFile, SetName, (const String&), void), AS_CALL_THISCALL);
    // unsigned Deserializer::Tell() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "uint Tell() const", AS_METHODPR(AbstractFile, Tell, () const, unsigned), AS_CALL_THISCALL);
    // virtual unsigned Serializer::Write(const void* data, unsigned size)=0 | File: ../IO/Serializer.h
    // Error: type "const void*" can not automatically bind
    // bool Serializer::WriteBool(bool value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteBool(bool)", AS_METHODPR(AbstractFile, WriteBool, (bool), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteBoundingBox(const BoundingBox& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteBoundingBox(const BoundingBox&in)", AS_METHODPR(AbstractFile, WriteBoundingBox, (const BoundingBox&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteBuffer(const PODVector<unsigned char>& value) | File: ../IO/Serializer.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // bool Serializer::WriteByte(signed char value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteByte(int8)", AS_METHODPR(AbstractFile, WriteByte, (signed char), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteColor(const Color& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteColor(const Color&in)", AS_METHODPR(AbstractFile, WriteColor, (const Color&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteDouble(double value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteDouble(double)", AS_METHODPR(AbstractFile, WriteDouble, (double), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteFileID(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteFileID(const String&in)", AS_METHODPR(AbstractFile, WriteFileID, (const String&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteFloat(float value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteFloat(float)", AS_METHODPR(AbstractFile, WriteFloat, (float), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteInt(int value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteInt(int)", AS_METHODPR(AbstractFile, WriteInt, (int), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteInt64(long long value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteInt64(int64)", AS_METHODPR(AbstractFile, WriteInt64, (long long), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteIntRect(const IntRect& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteIntRect(const IntRect&in)", AS_METHODPR(AbstractFile, WriteIntRect, (const IntRect&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteIntVector2(const IntVector2& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteIntVector2(const IntVector2&in)", AS_METHODPR(AbstractFile, WriteIntVector2, (const IntVector2&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteIntVector3(const IntVector3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteIntVector3(const IntVector3&in)", AS_METHODPR(AbstractFile, WriteIntVector3, (const IntVector3&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteLine(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteLine(const String&in)", AS_METHODPR(AbstractFile, WriteLine, (const String&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteMatrix3(const Matrix3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteMatrix3(const Matrix3&in)", AS_METHODPR(AbstractFile, WriteMatrix3, (const Matrix3&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteMatrix3x4(const Matrix3x4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteMatrix3x4(const Matrix3x4&in)", AS_METHODPR(AbstractFile, WriteMatrix3x4, (const Matrix3x4&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteMatrix4(const Matrix4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteMatrix4(const Matrix4&in)", AS_METHODPR(AbstractFile, WriteMatrix4, (const Matrix4&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteNetID(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteNetID(uint)", AS_METHODPR(AbstractFile, WriteNetID, (unsigned), bool), AS_CALL_THISCALL);
    // bool Serializer::WritePackedQuaternion(const Quaternion& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WritePackedQuaternion(const Quaternion&in)", AS_METHODPR(AbstractFile, WritePackedQuaternion, (const Quaternion&), bool), AS_CALL_THISCALL);
    // bool Serializer::WritePackedVector3(const Vector3& value, float maxAbsCoord) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WritePackedVector3(const Vector3&in, float)", AS_METHODPR(AbstractFile, WritePackedVector3, (const Vector3&, float), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteQuaternion(const Quaternion& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteQuaternion(const Quaternion&in)", AS_METHODPR(AbstractFile, WriteQuaternion, (const Quaternion&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteRect(const Rect& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteRect(const Rect&in)", AS_METHODPR(AbstractFile, WriteRect, (const Rect&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteResourceRef(const ResourceRef& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteResourceRef(const ResourceRef&in)", AS_METHODPR(AbstractFile, WriteResourceRef, (const ResourceRef&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteResourceRefList(const ResourceRefList& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteResourceRefList(const ResourceRefList&in)", AS_METHODPR(AbstractFile, WriteResourceRefList, (const ResourceRefList&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteShort(short value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteShort(int16)", AS_METHODPR(AbstractFile, WriteShort, (short), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteString(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteString(const String&in)", AS_METHODPR(AbstractFile, WriteString, (const String&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteStringHash(const StringHash& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteStringHash(const StringHash&in)", AS_METHODPR(AbstractFile, WriteStringHash, (const StringHash&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteStringVector(const StringVector& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteStringVector(Array<String>@+)", AS_FUNCTION_OBJFIRST(AbstractFile_WriteStringVector_StringVector), AS_CALL_CDECL_OBJFIRST);
    // bool Serializer::WriteUByte(unsigned char value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteUByte(uint8)", AS_METHODPR(AbstractFile, WriteUByte, (unsigned char), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteUInt(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteUInt(uint)", AS_METHODPR(AbstractFile, WriteUInt, (unsigned), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteUInt64(unsigned long long value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteUInt64(uint64)", AS_METHODPR(AbstractFile, WriteUInt64, (unsigned long long), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteUShort(unsigned short value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteUShort(uint16)", AS_METHODPR(AbstractFile, WriteUShort, (unsigned short), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVariant(const Variant& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteVariant(const Variant&in)", AS_METHODPR(AbstractFile, WriteVariant, (const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVariantData(const Variant& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteVariantData(const Variant&in)", AS_METHODPR(AbstractFile, WriteVariantData, (const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVariantMap(const VariantMap& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteVariantMap(const VariantMap&in)", AS_METHODPR(AbstractFile, WriteVariantMap, (const VariantMap&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVariantVector(const VariantVector& value) | File: ../IO/Serializer.h
    // Error: type "const VariantVector&" can not automatically bind
    // bool Serializer::WriteVector2(const Vector2& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteVector2(const Vector2&in)", AS_METHODPR(AbstractFile, WriteVector2, (const Vector2&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVector3(const Vector3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteVector3(const Vector3&in)", AS_METHODPR(AbstractFile, WriteVector3, (const Vector3&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVector4(const Vector4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteVector4(const Vector4&in)", AS_METHODPR(AbstractFile, WriteVector4, (const Vector4&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVLE(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteVLE(uint)", AS_METHODPR(AbstractFile, WriteVLE, (unsigned), bool), AS_CALL_THISCALL);
    // AbstractFile& AbstractFile::operator=(const AbstractFile&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AbstractFile>(engine, "AbstractFile");
    engine->RegisterObjectBehaviour("AbstractFile", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("AbstractFile", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);
#ifdef REGISTER_MANUAL_PART_Deserializer
    REGISTER_MANUAL_PART_Deserializer(AbstractFile, "AbstractFile")
#endif
#ifdef REGISTER_MANUAL_PART_Serializer
    REGISTER_MANUAL_PART_Serializer(AbstractFile, "AbstractFile")
#endif
#ifdef REGISTER_MANUAL_PART_AbstractFile
    REGISTER_MANUAL_PART_AbstractFile(AbstractFile, "AbstractFile")
#endif
    RegisterSubclass<Deserializer, AbstractFile>(engine, "Deserializer", "AbstractFile");
    RegisterSubclass<Serializer, AbstractFile>(engine, "Serializer", "AbstractFile");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Animatable", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Animatable, AddRef, (), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void AllocateNetworkState()", AS_METHODPR(Animatable, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void ApplyAttributes()", AS_METHODPR(Animatable, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "bool GetAnimationEnabled() const", AS_METHODPR(Animatable, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "bool get_animationEnabled() const", AS_METHODPR(Animatable, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "Variant GetAttribute(uint) const", AS_METHODPR(Animatable, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "Variant get_attributes(uint) const", AS_METHODPR(Animatable, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "Variant GetAttribute(const String&in) const", AS_METHODPR(Animatable, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(Animatable, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(Animatable, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(Animatable, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(Animatable, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Animatable, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Animatable, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Animatable, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "bool GetBlockEvents() const", AS_METHODPR(Animatable, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "const String& GetCategory() const", AS_METHODPR(Animatable, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "const String& get_category() const", AS_METHODPR(Animatable, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "VariantMap& GetEventDataMap() const", AS_METHODPR(Animatable, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "Object@+ GetEventSender() const", AS_METHODPR(Animatable, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Animatable, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Animatable, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Animatable, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "const VariantMap& get_globalVars() const", AS_METHODPR(Animatable, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Animatable, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "uint GetNumAttributes() const", AS_METHODPR(Animatable, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "uint get_numAttributes() const", AS_METHODPR(Animatable, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "uint GetNumNetworkAttributes() const", AS_METHODPR(Animatable, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(Animatable, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(Animatable, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(Animatable, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Animatable, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "StringHash GetType() const", AS_METHODPR(Animatable, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "StringHash get_type() const", AS_METHODPR(Animatable, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "const String& GetTypeName() const", AS_METHODPR(Animatable, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "const String& get_typeName() const", AS_METHODPR(Animatable, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "bool HasEventHandlers() const", AS_METHODPR(Animatable, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Animatable, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Animatable, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Animatable, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "bool IsTemporary() const", AS_METHODPR(Animatable, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "bool get_temporary() const", AS_METHODPR(Animatable, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "bool Load(Deserializer&)", AS_METHODPR(Animatable, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Animatable, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Animatable, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void MarkNetworkUpdate()", AS_METHODPR(Animatable, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Animatable, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Animatable, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Animatable, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Animatable, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Animatable, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Animatable", "int Refs() const", AS_METHODPR(Animatable, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "int get_refs() const", AS_METHODPR(Animatable, Refs, () const, int), AS_CALL_THISCALL);
    // static void Animatable::RegisterObject(Context* context) | File: ../Scene/Animatable.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Animatable", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Animatable, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(Animatable, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void RemoveInstanceDefault()", AS_METHODPR(Animatable, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "void RemoveObjectAnimation()", AS_METHODPR(Animatable, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void ResetToDefault()", AS_METHODPR(Animatable, ResetToDefault, (), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "bool Save(Serializer&) const", AS_METHODPR(Animatable, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "bool SaveDefaultAttributes() const", AS_METHODPR(Animatable, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "bool SaveJSON(JSONValue&) const", AS_METHODPR(Animatable, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Animatable::SaveXML(XMLElement& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "bool SaveXML(XMLElement&) const", AS_METHODPR(Animatable, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "void SendEvent(StringHash)", AS_METHODPR(Animatable, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Animatable, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "void SetAnimationEnabled(bool)", AS_METHODPR(Animatable, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "void set_animationEnabled(bool)", AS_METHODPR(Animatable, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "void SetAnimationTime(float)", AS_METHODPR(Animatable, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Animatable, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Animatable, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Animatable, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Animatable, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(Animatable, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(Animatable, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Animatable, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "void SetBlockEvents(bool)", AS_METHODPR(Animatable, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Animatable, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Animatable, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void SetInstanceDefault(bool)", AS_METHODPR(Animatable, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Animatable, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(Animatable, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(Animatable, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(Animatable, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void SetTemporary(bool)", AS_METHODPR(Animatable, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "void set_temporary(bool)", AS_METHODPR(Animatable, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "void UnsubscribeFromAllEvents()", AS_METHODPR(Animatable, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Animatable_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Animatable, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Animatable, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Animatable, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Animatable", "int WeakRefs() const", AS_METHODPR(Animatable, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "int get_weakRefs() const", AS_METHODPR(Animatable, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Animatable, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Animatable, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Animatable, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Animatable, "Animatable")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Animatable, "Animatable")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Animatable, "Animatable")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(Animatable, "Animatable")
#endif
    RegisterSubclass<Serializable, Animatable>(engine, "Serializable", "Animatable");
    RegisterSubclass<Object, Animatable>(engine, "Object", "Animatable");
    RegisterSubclass<RefCounted, Animatable>(engine, "RefCounted", "Animatable");

    // AnimationState* AnimatedModel::AddAnimationState(Animation* animation) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "AnimationState@+ AddAnimationState(Animation@+)", AS_METHODPR(AnimatedModel, AddAnimationState, (Animation*), AnimationState*), AS_CALL_THISCALL);
    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void AddLight(Light@+)", AS_METHODPR(AnimatedModel, AddLight, (Light*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("AnimatedModel", asBEHAVE_ADDREF, "void f()", AS_METHODPR(AnimatedModel, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void AddVertexLight(Light@+)", AS_METHODPR(AnimatedModel, AddVertexLight, (Light*), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "void AllocateNetworkState()", AS_METHODPR(AnimatedModel, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // explicit AnimatedModel::AnimatedModel(Context* context) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectBehaviour("AnimatedModel", asBEHAVE_FACTORY, "AnimatedModel@+ f()", AS_FUNCTION(AnimatedModel_AnimatedModel_Context), AS_CALL_CDECL);
    // void AnimatedModel::ApplyAnimation() | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void ApplyAnimation()", AS_METHODPR(AnimatedModel, ApplyAnimation, (), void), AS_CALL_THISCALL);
    // void AnimatedModel::ApplyAttributes() override | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void ApplyAttributes()", AS_METHODPR(AnimatedModel, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void StaticModel::ApplyMaterialList(const String& fileName=String::EMPTY) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void ApplyMaterialList(const String&in = String::EMPTY)", AS_METHODPR(AnimatedModel, ApplyMaterialList, (const String&), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void AnimatedModel::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(AnimatedModel, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool StaticModel::DrawOcclusion(OcclusionBuffer* buffer) override | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "bool DrawOcclusion(OcclusionBuffer@+)", AS_METHODPR(AnimatedModel, DrawOcclusion, (OcclusionBuffer*), bool), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool GetAnimationEnabled() const", AS_METHODPR(AnimatedModel, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool get_animationEnabled() const", AS_METHODPR(AnimatedModel, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // float AnimatedModel::GetAnimationLodBias() const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetAnimationLodBias() const", AS_METHODPR(AnimatedModel, GetAnimationLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "float get_animationLodBias() const", AS_METHODPR(AnimatedModel, GetAnimationLodBias, () const, float), AS_CALL_THISCALL);
    // AnimationState* AnimatedModel::GetAnimationState(Animation* animation) const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "AnimationState@+ GetAnimationState(Animation@+) const", AS_METHODPR(AnimatedModel, GetAnimationState, (Animation*) const, AnimationState*), AS_CALL_THISCALL);
    // AnimationState* AnimatedModel::GetAnimationState(const String& animationName) const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "AnimationState@+ GetAnimationState(const String&in) const", AS_METHODPR(AnimatedModel, GetAnimationState, (const String&) const, AnimationState*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "AnimationState@+ get_animationStates(const String&in) const", AS_METHODPR(AnimatedModel, GetAnimationState, (const String&) const, AnimationState*), AS_CALL_THISCALL);
    // AnimationState* AnimatedModel::GetAnimationState(StringHash animationNameHash) const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "AnimationState@+ GetAnimationState(StringHash) const", AS_METHODPR(AnimatedModel, GetAnimationState, (StringHash) const, AnimationState*), AS_CALL_THISCALL);
    // AnimationState* AnimatedModel::GetAnimationState(unsigned index) const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "AnimationState@+ GetAnimationState(uint) const", AS_METHODPR(AnimatedModel, GetAnimationState, (unsigned) const, AnimationState*), AS_CALL_THISCALL);
    // const Vector<SharedPtr<AnimationState>>& AnimatedModel::GetAnimationStates() const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "Array<AnimationState@>@ GetAnimationStates() const", AS_FUNCTION_OBJFIRST(AnimatedModel_GetAnimationStates_void), AS_CALL_CDECL_OBJFIRST);
    // VariantVector AnimatedModel::GetAnimationStatesAttr() const | File: ../Graphics/AnimatedModel.h
    // Error: type "VariantVector" can not automatically bind
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "Variant GetAttribute(uint) const", AS_METHODPR(AnimatedModel, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "Variant get_attributes(uint) const", AS_METHODPR(AnimatedModel, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "Variant GetAttribute(const String&in) const", AS_METHODPR(AnimatedModel, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(AnimatedModel, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(AnimatedModel, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(AnimatedModel, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(AnimatedModel, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "Variant GetAttributeDefault(uint) const", AS_METHODPR(AnimatedModel, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "Variant get_attributeDefaults(uint) const", AS_METHODPR(AnimatedModel, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(AnimatedModel, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "bool GetBlockEvents() const", AS_METHODPR(AnimatedModel, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // VariantVector AnimatedModel::GetBonesEnabledAttr() const | File: ../Graphics/AnimatedModel.h
    // Error: type "VariantVector" can not automatically bind
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "const BoundingBox& GetBoundingBox() const", AS_METHODPR(AnimatedModel, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "const BoundingBox& get_boundingBox() const", AS_METHODPR(AnimatedModel, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool GetCastShadows() const", AS_METHODPR(AnimatedModel, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool get_castShadows() const", AS_METHODPR(AnimatedModel, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "const String& GetCategory() const", AS_METHODPR(AnimatedModel, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "const String& get_category() const", AS_METHODPR(AnimatedModel, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "Component@+ GetComponent(StringHash) const", AS_METHODPR(AnimatedModel, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("AnimatedModel", "float GetDistance() const", AS_METHODPR(AnimatedModel, GetDistance, () const, float), AS_CALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "uint8 GetDrawableFlags() const", AS_METHODPR(AnimatedModel, GetDrawableFlags, () const, unsigned char), AS_CALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetDrawDistance() const", AS_METHODPR(AnimatedModel, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "float get_drawDistance() const", AS_METHODPR(AnimatedModel, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "VariantMap& GetEventDataMap() const", AS_METHODPR(AnimatedModel, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "Object@+ GetEventSender() const", AS_METHODPR(AnimatedModel, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "Light@+ GetFirstLight() const", AS_METHODPR(AnimatedModel, GetFirstLight, () const, Light*), AS_CALL_THISCALL);
    // const Vector<PODVector<unsigned>>& AnimatedModel::GetGeometryBoneMappings() const | File: ../Graphics/AnimatedModel.h
    // Error: type "const Vector<PODVector<unsigned>>&" can not automatically bind
    // const Vector<PODVector<Matrix3x4>>& AnimatedModel::GetGeometrySkinMatrices() const | File: ../Graphics/AnimatedModel.h
    // Error: type "const Vector<PODVector<Matrix3x4>>&" can not automatically bind
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(AnimatedModel, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(AnimatedModel, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "const VariantMap& GetGlobalVars() const", AS_METHODPR(AnimatedModel, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "const VariantMap& get_globalVars() const", AS_METHODPR(AnimatedModel, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetID() const", AS_METHODPR(AnimatedModel, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_id() const", AS_METHODPR(AnimatedModel, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(AnimatedModel, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetLightMask() const", AS_METHODPR(AnimatedModel, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_lightMask() const", AS_METHODPR(AnimatedModel, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "Array<Light@>@ GetLights() const", AS_FUNCTION_OBJFIRST(AnimatedModel_GetLights_void), AS_CALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetLodBias() const", AS_METHODPR(AnimatedModel, GetLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "float get_lodBias() const", AS_METHODPR(AnimatedModel, GetLodBias, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetLodDistance() const", AS_METHODPR(AnimatedModel, GetLodDistance, () const, float), AS_CALL_THISCALL);
    // Geometry* StaticModel::GetLodGeometry(unsigned batchIndex, unsigned level) override | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "Geometry@+ GetLodGeometry(uint, uint)", AS_METHODPR(AnimatedModel, GetLodGeometry, (unsigned, unsigned), Geometry*), AS_CALL_THISCALL);
    // virtual Material* StaticModel::GetMaterial() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "Material@+ GetMaterial() const", AS_METHODPR(AnimatedModel, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "Material@+ get_material() const", AS_METHODPR(AnimatedModel, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    // virtual Material* StaticModel::GetMaterial(unsigned index) const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "Material@+ GetMaterial(uint) const", AS_METHODPR(AnimatedModel, GetMaterial, (unsigned) const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "Material@+ get_materials(uint) const", AS_METHODPR(AnimatedModel, GetMaterial, (unsigned) const, Material*), AS_CALL_THISCALL);
    // const ResourceRefList& StaticModel::GetMaterialsAttr() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "const ResourceRefList& GetMaterialsAttr() const", AS_METHODPR(AnimatedModel, GetMaterialsAttr, () const, const ResourceRefList&), AS_CALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetMaxLights() const", AS_METHODPR(AnimatedModel, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_maxLights() const", AS_METHODPR(AnimatedModel, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetMaxZ() const", AS_METHODPR(AnimatedModel, GetMaxZ, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetMinZ() const", AS_METHODPR(AnimatedModel, GetMinZ, () const, float), AS_CALL_THISCALL);
    // Model* StaticModel::GetModel() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "Model@+ GetModel() const", AS_METHODPR(AnimatedModel, GetModel, () const, Model*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "Model@+ get_model() const", AS_METHODPR(AnimatedModel, GetModel, () const, Model*), AS_CALL_THISCALL);
    // ResourceRef AnimatedModel::GetModelAttr() const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "ResourceRef GetModelAttr() const", AS_METHODPR(AnimatedModel, GetModelAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // const Vector<ModelMorph>& AnimatedModel::GetMorphs() const | File: ../Graphics/AnimatedModel.h
    // Error: type "const Vector<ModelMorph>&" can not automatically bind
    // const PODVector<unsigned char>& AnimatedModel::GetMorphsAttr() const | File: ../Graphics/AnimatedModel.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // const Vector<SharedPtr<VertexBuffer>>& AnimatedModel::GetMorphVertexBuffers() const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "Array<VertexBuffer@>@ GetMorphVertexBuffers() const", AS_FUNCTION_OBJFIRST(AnimatedModel_GetMorphVertexBuffers_void), AS_CALL_CDECL_OBJFIRST);
    // float AnimatedModel::GetMorphWeight(unsigned index) const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetMorphWeight(uint) const", AS_METHODPR(AnimatedModel, GetMorphWeight, (unsigned) const, float), AS_CALL_THISCALL);
    // float AnimatedModel::GetMorphWeight(const String& name) const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetMorphWeight(const String&in) const", AS_METHODPR(AnimatedModel, GetMorphWeight, (const String&) const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "float get_morphWeights(const String&in) const", AS_METHODPR(AnimatedModel, GetMorphWeight, (const String&) const, float), AS_CALL_THISCALL);
    // float AnimatedModel::GetMorphWeight(StringHash nameHash) const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetMorphWeight(StringHash) const", AS_METHODPR(AnimatedModel, GetMorphWeight, (StringHash) const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "Node@+ GetNode() const", AS_METHODPR(AnimatedModel, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "Node@+ get_node() const", AS_METHODPR(AnimatedModel, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned AnimatedModel::GetNumAnimationStates() const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetNumAnimationStates() const", AS_METHODPR(AnimatedModel, GetNumAnimationStates, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_numAnimationStates() const", AS_METHODPR(AnimatedModel, GetNumAnimationStates, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetNumAttributes() const", AS_METHODPR(AnimatedModel, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_numAttributes() const", AS_METHODPR(AnimatedModel, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned StaticModel::GetNumGeometries() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetNumGeometries() const", AS_METHODPR(AnimatedModel, GetNumGeometries, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_numGeometries() const", AS_METHODPR(AnimatedModel, GetNumGeometries, () const, unsigned), AS_CALL_THISCALL);
    // unsigned AnimatedModel::GetNumMorphs() const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetNumMorphs() const", AS_METHODPR(AnimatedModel, GetNumMorphs, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_numMorphs() const", AS_METHODPR(AnimatedModel, GetNumMorphs, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetNumNetworkAttributes() const", AS_METHODPR(AnimatedModel, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned StaticModel::GetNumOccluderTriangles() override | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetNumOccluderTriangles()", AS_METHODPR(AnimatedModel, GetNumOccluderTriangles, (), unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(AnimatedModel, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(AnimatedModel, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(AnimatedModel, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // unsigned StaticModel::GetOcclusionLodLevel() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetOcclusionLodLevel() const", AS_METHODPR(AnimatedModel, GetOcclusionLodLevel, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_occlusionLodLevel() const", AS_METHODPR(AnimatedModel, GetOcclusionLodLevel, () const, unsigned), AS_CALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "Scene@+ GetScene() const", AS_METHODPR(AnimatedModel, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetShadowDistance() const", AS_METHODPR(AnimatedModel, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "float get_shadowDistance() const", AS_METHODPR(AnimatedModel, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetShadowMask() const", AS_METHODPR(AnimatedModel, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_shadowMask() const", AS_METHODPR(AnimatedModel, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    // Skeleton& AnimatedModel::GetSkeleton() | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "Skeleton& GetSkeleton()", AS_METHODPR(AnimatedModel, GetSkeleton, (), Skeleton&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "Skeleton& get_skeleton()", AS_METHODPR(AnimatedModel, GetSkeleton, (), Skeleton&), AS_CALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetSortValue() const", AS_METHODPR(AnimatedModel, GetSortValue, () const, float), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(AnimatedModel, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "StringHash GetType() const", AS_METHODPR(AnimatedModel, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "StringHash get_type() const", AS_METHODPR(AnimatedModel, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "const String& GetTypeName() const", AS_METHODPR(AnimatedModel, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "const String& get_typeName() const", AS_METHODPR(AnimatedModel, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // UpdateGeometryType AnimatedModel::GetUpdateGeometryType() override | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "UpdateGeometryType GetUpdateGeometryType()", AS_METHODPR(AnimatedModel, GetUpdateGeometryType, (), UpdateGeometryType), AS_CALL_THISCALL);
    // bool AnimatedModel::GetUpdateInvisible() const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "bool GetUpdateInvisible() const", AS_METHODPR(AnimatedModel, GetUpdateInvisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool get_updateInvisible() const", AS_METHODPR(AnimatedModel, GetUpdateInvisible, () const, bool), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "Array<Light@>@ GetVertexLights() const", AS_FUNCTION_OBJFIRST(AnimatedModel_GetVertexLights_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetViewMask() const", AS_METHODPR(AnimatedModel, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_viewMask() const", AS_METHODPR(AnimatedModel, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "const BoundingBox& GetWorldBoundingBox()", AS_METHODPR(AnimatedModel, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "const BoundingBox& get_worldBoundingBox()", AS_METHODPR(AnimatedModel, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "Zone@+ GetZone() const", AS_METHODPR(AnimatedModel, GetZone, () const, Zone*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "Zone@+ get_zone() const", AS_METHODPR(AnimatedModel, GetZone, () const, Zone*), AS_CALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetZoneMask() const", AS_METHODPR(AnimatedModel, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_zoneMask() const", AS_METHODPR(AnimatedModel, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool HasBasePass(uint) const", AS_METHODPR(AnimatedModel, HasBasePass, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "bool HasEventHandlers() const", AS_METHODPR(AnimatedModel, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(AnimatedModel, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(AnimatedModel, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsEnabled() const", AS_METHODPR(AnimatedModel, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool get_enabled() const", AS_METHODPR(AnimatedModel, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsEnabledEffective() const", AS_METHODPR(AnimatedModel, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool get_enabledEffective() const", AS_METHODPR(AnimatedModel, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool StaticModel::IsInside(const Vector3& point) const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsInside(const Vector3&in) const", AS_METHODPR(AnimatedModel, IsInside, (const Vector3&) const, bool), AS_CALL_THISCALL);
    // bool StaticModel::IsInsideLocal(const Vector3& point) const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsInsideLocal(const Vector3&in) const", AS_METHODPR(AnimatedModel, IsInsideLocal, (const Vector3&) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsInstanceOf(StringHash) const", AS_METHODPR(AnimatedModel, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsInView() const", AS_METHODPR(AnimatedModel, IsInView, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool get_inView() const", AS_METHODPR(AnimatedModel, IsInView, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsInView(Camera@+) const", AS_METHODPR(AnimatedModel, IsInView, (Camera*) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsInView(const FrameInfo&in, bool = false) const", AS_METHODPR(AnimatedModel, IsInView, (const FrameInfo&, bool) const, bool), AS_CALL_THISCALL);
    // bool AnimatedModel::IsMaster() const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsMaster() const", AS_METHODPR(AnimatedModel, IsMaster, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsOccludee() const", AS_METHODPR(AnimatedModel, IsOccludee, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool get_occludee() const", AS_METHODPR(AnimatedModel, IsOccludee, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsOccluder() const", AS_METHODPR(AnimatedModel, IsOccluder, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool get_occluder() const", AS_METHODPR(AnimatedModel, IsOccluder, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsReplicated() const", AS_METHODPR(AnimatedModel, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool get_replicated() const", AS_METHODPR(AnimatedModel, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsTemporary() const", AS_METHODPR(AnimatedModel, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool get_temporary() const", AS_METHODPR(AnimatedModel, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsZoneDirty() const", AS_METHODPR(AnimatedModel, IsZoneDirty, () const, bool), AS_CALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void LimitLights()", AS_METHODPR(AnimatedModel, LimitLights, (), void), AS_CALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void LimitVertexLights(bool)", AS_METHODPR(AnimatedModel, LimitVertexLights, (bool), void), AS_CALL_THISCALL);
    // bool AnimatedModel::Load(Deserializer& source) override | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "bool Load(Deserializer&)", AS_METHODPR(AnimatedModel, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool AnimatedModel::LoadJSON(const JSONValue& source) override | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(AnimatedModel, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool AnimatedModel::LoadXML(const XMLElement& source) override | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "bool LoadXML(const XMLElement&in)", AS_METHODPR(AnimatedModel, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void MarkForUpdate()", AS_METHODPR(AnimatedModel, MarkForUpdate, (), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void MarkInView(const FrameInfo&in)", AS_METHODPR(AnimatedModel, MarkInView, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void MarkInView(uint)", AS_METHODPR(AnimatedModel, MarkInView, (unsigned), void), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "void MarkNetworkUpdate()", AS_METHODPR(AnimatedModel, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(AnimatedModel, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(AnimatedModel, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(AnimatedModel, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Drawable::OnSetEnabled() override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void OnSetEnabled()", AS_METHODPR(AnimatedModel, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "void PrepareNetworkUpdate()", AS_METHODPR(AnimatedModel, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void AnimatedModel::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override | File: ../Graphics/AnimatedModel.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(AnimatedModel, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(AnimatedModel, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AnimatedModel", "int Refs() const", AS_METHODPR(AnimatedModel, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "int get_refs() const", AS_METHODPR(AnimatedModel, Refs, () const, int), AS_CALL_THISCALL);
    // static void AnimatedModel::RegisterObject(Context* context) | File: ../Graphics/AnimatedModel.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("AnimatedModel", asBEHAVE_RELEASE, "void f()", AS_METHODPR(AnimatedModel, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "void Remove()", AS_METHODPR(AnimatedModel, Remove, (), void), AS_CALL_THISCALL);
    // void AnimatedModel::RemoveAllAnimationStates() | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void RemoveAllAnimationStates()", AS_METHODPR(AnimatedModel, RemoveAllAnimationStates, (), void), AS_CALL_THISCALL);
    // void AnimatedModel::RemoveAnimationState(Animation* animation) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void RemoveAnimationState(Animation@+)", AS_METHODPR(AnimatedModel, RemoveAnimationState, (Animation*), void), AS_CALL_THISCALL);
    // void AnimatedModel::RemoveAnimationState(const String& animationName) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void RemoveAnimationState(const String&in)", AS_METHODPR(AnimatedModel, RemoveAnimationState, (const String&), void), AS_CALL_THISCALL);
    // void AnimatedModel::RemoveAnimationState(StringHash animationNameHash) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void RemoveAnimationState(StringHash)", AS_METHODPR(AnimatedModel, RemoveAnimationState, (StringHash), void), AS_CALL_THISCALL);
    // void AnimatedModel::RemoveAnimationState(AnimationState* state) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void RemoveAnimationState(AnimationState@+)", AS_METHODPR(AnimatedModel, RemoveAnimationState, (AnimationState*), void), AS_CALL_THISCALL);
    // void AnimatedModel::RemoveAnimationState(unsigned index) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void RemoveAnimationState(uint)", AS_METHODPR(AnimatedModel, RemoveAnimationState, (unsigned), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(AnimatedModel, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "void RemoveInstanceDefault()", AS_METHODPR(AnimatedModel, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "void RemoveObjectAnimation()", AS_METHODPR(AnimatedModel, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void AnimatedModel::ResetMorphWeights() | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void ResetMorphWeights()", AS_METHODPR(AnimatedModel, ResetMorphWeights, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "void ResetToDefault()", AS_METHODPR(AnimatedModel, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "bool Save(Serializer&) const", AS_METHODPR(AnimatedModel, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool SaveDefaultAttributes() const", AS_METHODPR(AnimatedModel, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "bool SaveJSON(JSONValue&) const", AS_METHODPR(AnimatedModel, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "bool SaveXML(XMLElement&) const", AS_METHODPR(AnimatedModel, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "void SendEvent(StringHash)", AS_METHODPR(AnimatedModel, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(AnimatedModel, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetAnimationEnabled(bool)", AS_METHODPR(AnimatedModel, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_animationEnabled(bool)", AS_METHODPR(AnimatedModel, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void AnimatedModel::SetAnimationLodBias(float bias) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetAnimationLodBias(float)", AS_METHODPR(AnimatedModel, SetAnimationLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_animationLodBias(float)", AS_METHODPR(AnimatedModel, SetAnimationLodBias, (float), void), AS_CALL_THISCALL);
    // void AnimatedModel::SetAnimationStatesAttr(const VariantVector& value) | File: ../Graphics/AnimatedModel.h
    // Error: type "const VariantVector&" can not automatically bind
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetAnimationTime(float)", AS_METHODPR(AnimatedModel, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(AnimatedModel, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(AnimatedModel, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(AnimatedModel, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(AnimatedModel, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(AnimatedModel, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(AnimatedModel, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(AnimatedModel, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetBasePass(uint)", AS_METHODPR(AnimatedModel, SetBasePass, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetBlockEvents(bool)", AS_METHODPR(AnimatedModel, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void AnimatedModel::SetBonesEnabledAttr(const VariantVector& value) | File: ../Graphics/AnimatedModel.h
    // Error: type "const VariantVector&" can not automatically bind
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetCastShadows(bool)", AS_METHODPR(AnimatedModel, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_castShadows(bool)", AS_METHODPR(AnimatedModel, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetDrawDistance(float)", AS_METHODPR(AnimatedModel, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_drawDistance(float)", AS_METHODPR(AnimatedModel, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetEnabled(bool)", AS_METHODPR(AnimatedModel, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_enabled(bool)", AS_METHODPR(AnimatedModel, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(AnimatedModel, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(AnimatedModel, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetInstanceDefault(bool)", AS_METHODPR(AnimatedModel, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(AnimatedModel, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetLightMask(uint)", AS_METHODPR(AnimatedModel, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_lightMask(uint)", AS_METHODPR(AnimatedModel, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetLodBias(float)", AS_METHODPR(AnimatedModel, SetLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_lodBias(float)", AS_METHODPR(AnimatedModel, SetLodBias, (float), void), AS_CALL_THISCALL);
    // virtual void StaticModel::SetMaterial(Material* material) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetMaterial(Material@+)", AS_METHODPR(AnimatedModel, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_material(Material@+)", AS_METHODPR(AnimatedModel, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    // virtual bool StaticModel::SetMaterial(unsigned index, Material* material) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "bool SetMaterial(uint, Material@+)", AS_METHODPR(AnimatedModel, SetMaterial, (unsigned, Material*), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool set_materials(uint, Material@+)", AS_METHODPR(AnimatedModel, SetMaterial, (unsigned, Material*), bool), AS_CALL_THISCALL);
    // void StaticModel::SetMaterialsAttr(const ResourceRefList& value) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetMaterialsAttr(const ResourceRefList&in)", AS_METHODPR(AnimatedModel, SetMaterialsAttr, (const ResourceRefList&), void), AS_CALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetMaxLights(uint)", AS_METHODPR(AnimatedModel, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_maxLights(uint)", AS_METHODPR(AnimatedModel, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetMinMaxZ(float, float)", AS_METHODPR(AnimatedModel, SetMinMaxZ, (float, float), void), AS_CALL_THISCALL);
    // void AnimatedModel::SetModel(Model* model, bool createBones=true) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetModel(Model@+, bool = true)", AS_METHODPR(AnimatedModel, SetModel, (Model*, bool), void), AS_CALL_THISCALL);
    // void AnimatedModel::SetModelAttr(const ResourceRef& value) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetModelAttr(const ResourceRef&in)", AS_METHODPR(AnimatedModel, SetModelAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void AnimatedModel::SetMorphsAttr(const PODVector<unsigned char>& value) | File: ../Graphics/AnimatedModel.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void AnimatedModel::SetMorphWeight(unsigned index, float weight) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetMorphWeight(uint, float)", AS_METHODPR(AnimatedModel, SetMorphWeight, (unsigned, float), void), AS_CALL_THISCALL);
    // void AnimatedModel::SetMorphWeight(const String& name, float weight) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetMorphWeight(const String&in, float)", AS_METHODPR(AnimatedModel, SetMorphWeight, (const String&, float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_morphWeights(const String&in, float)", AS_METHODPR(AnimatedModel, SetMorphWeight, (const String&, float), void), AS_CALL_THISCALL);
    // void AnimatedModel::SetMorphWeight(StringHash nameHash, float weight) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetMorphWeight(StringHash, float)", AS_METHODPR(AnimatedModel, SetMorphWeight, (StringHash, float), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(AnimatedModel, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(AnimatedModel, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(AnimatedModel, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetOccludee(bool)", AS_METHODPR(AnimatedModel, SetOccludee, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_occludee(bool)", AS_METHODPR(AnimatedModel, SetOccludee, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetOccluder(bool)", AS_METHODPR(AnimatedModel, SetOccluder, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_occluder(bool)", AS_METHODPR(AnimatedModel, SetOccluder, (bool), void), AS_CALL_THISCALL);
    // void StaticModel::SetOcclusionLodLevel(unsigned level) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetOcclusionLodLevel(uint)", AS_METHODPR(AnimatedModel, SetOcclusionLodLevel, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_occlusionLodLevel(uint)", AS_METHODPR(AnimatedModel, SetOcclusionLodLevel, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetShadowDistance(float)", AS_METHODPR(AnimatedModel, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_shadowDistance(float)", AS_METHODPR(AnimatedModel, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetShadowMask(uint)", AS_METHODPR(AnimatedModel, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_shadowMask(uint)", AS_METHODPR(AnimatedModel, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetSortValue(float)", AS_METHODPR(AnimatedModel, SetSortValue, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetTemporary(bool)", AS_METHODPR(AnimatedModel, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_temporary(bool)", AS_METHODPR(AnimatedModel, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void AnimatedModel::SetUpdateInvisible(bool enable) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetUpdateInvisible(bool)", AS_METHODPR(AnimatedModel, SetUpdateInvisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_updateInvisible(bool)", AS_METHODPR(AnimatedModel, SetUpdateInvisible, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetViewMask(uint)", AS_METHODPR(AnimatedModel, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_viewMask(uint)", AS_METHODPR(AnimatedModel, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetZone(Zone@+, bool = false)", AS_METHODPR(AnimatedModel, SetZone, (Zone*, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetZoneMask(uint)", AS_METHODPR(AnimatedModel, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_zoneMask(uint)", AS_METHODPR(AnimatedModel, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "void UnsubscribeFromAllEvents()", AS_METHODPR(AnimatedModel, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(AnimatedModel_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(AnimatedModel, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(AnimatedModel, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(AnimatedModel, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void AnimatedModel::Update(const FrameInfo& frame) override | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void Update(const FrameInfo&in)", AS_METHODPR(AnimatedModel, Update, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void AnimatedModel::UpdateBatches(const FrameInfo& frame) override | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void UpdateBatches(const FrameInfo&in)", AS_METHODPR(AnimatedModel, UpdateBatches, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void AnimatedModel::UpdateBoneBoundingBox() | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void UpdateBoneBoundingBox()", AS_METHODPR(AnimatedModel, UpdateBoneBoundingBox, (), void), AS_CALL_THISCALL);
    // void AnimatedModel::UpdateGeometry(const FrameInfo& frame) override | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void UpdateGeometry(const FrameInfo&in)", AS_METHODPR(AnimatedModel, UpdateGeometry, (const FrameInfo&), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AnimatedModel", "int WeakRefs() const", AS_METHODPR(AnimatedModel, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "int get_weakRefs() const", AS_METHODPR(AnimatedModel, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(AnimatedModel, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(AnimatedModel, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(AnimatedModel, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_StaticModel
    REGISTER_MANUAL_PART_StaticModel(AnimatedModel, "AnimatedModel")
#endif
#ifdef REGISTER_MANUAL_PART_Drawable
    REGISTER_MANUAL_PART_Drawable(AnimatedModel, "AnimatedModel")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(AnimatedModel, "AnimatedModel")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(AnimatedModel, "AnimatedModel")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(AnimatedModel, "AnimatedModel")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(AnimatedModel, "AnimatedModel")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(AnimatedModel, "AnimatedModel")
#endif
#ifdef REGISTER_MANUAL_PART_AnimatedModel
    REGISTER_MANUAL_PART_AnimatedModel(AnimatedModel, "AnimatedModel")
#endif
    RegisterSubclass<StaticModel, AnimatedModel>(engine, "StaticModel", "AnimatedModel");
    RegisterSubclass<Drawable, AnimatedModel>(engine, "Drawable", "AnimatedModel");
    RegisterSubclass<Component, AnimatedModel>(engine, "Component", "AnimatedModel");
    RegisterSubclass<Animatable, AnimatedModel>(engine, "Animatable", "AnimatedModel");
    RegisterSubclass<Serializable, AnimatedModel>(engine, "Serializable", "AnimatedModel");
    RegisterSubclass<Object, AnimatedModel>(engine, "Object", "AnimatedModel");
    RegisterSubclass<RefCounted, AnimatedModel>(engine, "RefCounted", "AnimatedModel");

#ifdef URHO3D_URHO2D
    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void AddLight(Light@+)", AS_METHODPR(AnimatedSprite2D, AddLight, (Light*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("AnimatedSprite2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(AnimatedSprite2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void AddVertexLight(Light@+)", AS_METHODPR(AnimatedSprite2D, AddVertexLight, (Light*), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void AllocateNetworkState()", AS_METHODPR(AnimatedSprite2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // explicit AnimatedSprite2D::AnimatedSprite2D(Context* context) | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectBehaviour("AnimatedSprite2D", asBEHAVE_FACTORY, "AnimatedSprite2D@+ f()", AS_FUNCTION(AnimatedSprite2D_AnimatedSprite2D_Context), AS_CALL_CDECL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void ApplyAttributes()", AS_METHODPR(AnimatedSprite2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(AnimatedSprite2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool DrawOcclusion(OcclusionBuffer@+)", AS_METHODPR(AnimatedSprite2D, DrawOcclusion, (OcclusionBuffer*), bool), AS_CALL_THISCALL);
    // float StaticSprite2D::GetAlpha() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "float GetAlpha() const", AS_METHODPR(AnimatedSprite2D, GetAlpha, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "float get_alpha() const", AS_METHODPR(AnimatedSprite2D, GetAlpha, () const, float), AS_CALL_THISCALL);
    // const String& AnimatedSprite2D::GetAnimation() const | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "const String& GetAnimation() const", AS_METHODPR(AnimatedSprite2D, GetAnimation, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "const String& get_animation() const", AS_METHODPR(AnimatedSprite2D, GetAnimation, () const, const String&), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool GetAnimationEnabled() const", AS_METHODPR(AnimatedSprite2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_animationEnabled() const", AS_METHODPR(AnimatedSprite2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // AnimationSet2D* AnimatedSprite2D::GetAnimationSet() const | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "AnimationSet2D@+ GetAnimationSet() const", AS_METHODPR(AnimatedSprite2D, GetAnimationSet, () const, AnimationSet2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "AnimationSet2D@+ get_animationSet() const", AS_METHODPR(AnimatedSprite2D, GetAnimationSet, () const, AnimationSet2D*), AS_CALL_THISCALL);
    // ResourceRef AnimatedSprite2D::GetAnimationSetAttr() const | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "ResourceRef GetAnimationSetAttr() const", AS_METHODPR(AnimatedSprite2D, GetAnimationSetAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Variant GetAttribute(uint) const", AS_METHODPR(AnimatedSprite2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "Variant get_attributes(uint) const", AS_METHODPR(AnimatedSprite2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(AnimatedSprite2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(AnimatedSprite2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(AnimatedSprite2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(AnimatedSprite2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(AnimatedSprite2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(AnimatedSprite2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(AnimatedSprite2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(AnimatedSprite2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // BlendMode StaticSprite2D::GetBlendMode() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "BlendMode GetBlendMode() const", AS_METHODPR(AnimatedSprite2D, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "BlendMode get_blendMode() const", AS_METHODPR(AnimatedSprite2D, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool GetBlockEvents() const", AS_METHODPR(AnimatedSprite2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "const BoundingBox& GetBoundingBox() const", AS_METHODPR(AnimatedSprite2D, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "const BoundingBox& get_boundingBox() const", AS_METHODPR(AnimatedSprite2D, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool GetCastShadows() const", AS_METHODPR(AnimatedSprite2D, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_castShadows() const", AS_METHODPR(AnimatedSprite2D, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "const String& GetCategory() const", AS_METHODPR(AnimatedSprite2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "const String& get_category() const", AS_METHODPR(AnimatedSprite2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // const Color& StaticSprite2D::GetColor() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "const Color& GetColor() const", AS_METHODPR(AnimatedSprite2D, GetColor, () const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "const Color& get_color() const", AS_METHODPR(AnimatedSprite2D, GetColor, () const, const Color&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(AnimatedSprite2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // Material* StaticSprite2D::GetCustomMaterial() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Material@+ GetCustomMaterial() const", AS_METHODPR(AnimatedSprite2D, GetCustomMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "Material@+ get_customMaterial() const", AS_METHODPR(AnimatedSprite2D, GetCustomMaterial, () const, Material*), AS_CALL_THISCALL);
    // ResourceRef StaticSprite2D::GetCustomMaterialAttr() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "ResourceRef GetCustomMaterialAttr() const", AS_METHODPR(AnimatedSprite2D, GetCustomMaterialAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // float Drawable::GetDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "float GetDistance() const", AS_METHODPR(AnimatedSprite2D, GetDistance, () const, float), AS_CALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint8 GetDrawableFlags() const", AS_METHODPR(AnimatedSprite2D, GetDrawableFlags, () const, unsigned char), AS_CALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "float GetDrawDistance() const", AS_METHODPR(AnimatedSprite2D, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "float get_drawDistance() const", AS_METHODPR(AnimatedSprite2D, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    // const Rect& StaticSprite2D::GetDrawRect() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "const Rect& GetDrawRect() const", AS_METHODPR(AnimatedSprite2D, GetDrawRect, () const, const Rect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "const Rect& get_drawRect() const", AS_METHODPR(AnimatedSprite2D, GetDrawRect, () const, const Rect&), AS_CALL_THISCALL);
    // const String& AnimatedSprite2D::GetEntity() const | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "const String& GetEntity() const", AS_METHODPR(AnimatedSprite2D, GetEntity, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "const String& get_entity() const", AS_METHODPR(AnimatedSprite2D, GetEntity, () const, const String&), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(AnimatedSprite2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Object@+ GetEventSender() const", AS_METHODPR(AnimatedSprite2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Light@+ GetFirstLight() const", AS_METHODPR(AnimatedSprite2D, GetFirstLight, () const, Light*), AS_CALL_THISCALL);
    // bool StaticSprite2D::GetFlipX() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool GetFlipX() const", AS_METHODPR(AnimatedSprite2D, GetFlipX, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_flipX() const", AS_METHODPR(AnimatedSprite2D, GetFlipX, () const, bool), AS_CALL_THISCALL);
    // bool StaticSprite2D::GetFlipY() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool GetFlipY() const", AS_METHODPR(AnimatedSprite2D, GetFlipY, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_flipY() const", AS_METHODPR(AnimatedSprite2D, GetFlipY, () const, bool), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(AnimatedSprite2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(AnimatedSprite2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(AnimatedSprite2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "const VariantMap& get_globalVars() const", AS_METHODPR(AnimatedSprite2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // const Vector2& StaticSprite2D::GetHotSpot() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "const Vector2& GetHotSpot() const", AS_METHODPR(AnimatedSprite2D, GetHotSpot, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "const Vector2& get_hotSpot() const", AS_METHODPR(AnimatedSprite2D, GetHotSpot, () const, const Vector2&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint GetID() const", AS_METHODPR(AnimatedSprite2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint get_id() const", AS_METHODPR(AnimatedSprite2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(AnimatedSprite2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // int Drawable2D::GetLayer() const | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "int GetLayer() const", AS_METHODPR(AnimatedSprite2D, GetLayer, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "int get_layer() const", AS_METHODPR(AnimatedSprite2D, GetLayer, () const, int), AS_CALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint GetLightMask() const", AS_METHODPR(AnimatedSprite2D, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint get_lightMask() const", AS_METHODPR(AnimatedSprite2D, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Array<Light@>@ GetLights() const", AS_FUNCTION_OBJFIRST(AnimatedSprite2D_GetLights_void), AS_CALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "float GetLodBias() const", AS_METHODPR(AnimatedSprite2D, GetLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "float get_lodBias() const", AS_METHODPR(AnimatedSprite2D, GetLodBias, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "float GetLodDistance() const", AS_METHODPR(AnimatedSprite2D, GetLodDistance, () const, float), AS_CALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Geometry@+ GetLodGeometry(uint, uint)", AS_METHODPR(AnimatedSprite2D, GetLodGeometry, (unsigned, unsigned), Geometry*), AS_CALL_THISCALL);
    // LoopMode2D AnimatedSprite2D::GetLoopMode() const | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "LoopMode2D GetLoopMode() const", AS_METHODPR(AnimatedSprite2D, GetLoopMode, () const, LoopMode2D), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "LoopMode2D get_loopMode() const", AS_METHODPR(AnimatedSprite2D, GetLoopMode, () const, LoopMode2D), AS_CALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint GetMaxLights() const", AS_METHODPR(AnimatedSprite2D, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint get_maxLights() const", AS_METHODPR(AnimatedSprite2D, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "float GetMaxZ() const", AS_METHODPR(AnimatedSprite2D, GetMaxZ, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "float GetMinZ() const", AS_METHODPR(AnimatedSprite2D, GetMinZ, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Node@+ GetNode() const", AS_METHODPR(AnimatedSprite2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "Node@+ get_node() const", AS_METHODPR(AnimatedSprite2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint GetNumAttributes() const", AS_METHODPR(AnimatedSprite2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint get_numAttributes() const", AS_METHODPR(AnimatedSprite2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(AnimatedSprite2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint GetNumOccluderTriangles()", AS_METHODPR(AnimatedSprite2D, GetNumOccluderTriangles, (), unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(AnimatedSprite2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(AnimatedSprite2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(AnimatedSprite2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // int Drawable2D::GetOrderInLayer() const | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "int GetOrderInLayer() const", AS_METHODPR(AnimatedSprite2D, GetOrderInLayer, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "int get_orderInLayer() const", AS_METHODPR(AnimatedSprite2D, GetOrderInLayer, () const, int), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Scene@+ GetScene() const", AS_METHODPR(AnimatedSprite2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "float GetShadowDistance() const", AS_METHODPR(AnimatedSprite2D, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "float get_shadowDistance() const", AS_METHODPR(AnimatedSprite2D, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint GetShadowMask() const", AS_METHODPR(AnimatedSprite2D, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint get_shadowMask() const", AS_METHODPR(AnimatedSprite2D, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "float GetSortValue() const", AS_METHODPR(AnimatedSprite2D, GetSortValue, () const, float), AS_CALL_THISCALL);
    // const Vector<SourceBatch2D>& Drawable2D::GetSourceBatches() | File: ../Urho2D/Drawable2D.h
    // Error: type "const Vector<SourceBatch2D>&" can not automatically bind
    // float AnimatedSprite2D::GetSpeed() const | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "float GetSpeed() const", AS_METHODPR(AnimatedSprite2D, GetSpeed, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "float get_speed() const", AS_METHODPR(AnimatedSprite2D, GetSpeed, () const, float), AS_CALL_THISCALL);
    // Sprite2D* StaticSprite2D::GetSprite() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Sprite2D@+ GetSprite() const", AS_METHODPR(AnimatedSprite2D, GetSprite, () const, Sprite2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "Sprite2D@+ get_sprite() const", AS_METHODPR(AnimatedSprite2D, GetSprite, () const, Sprite2D*), AS_CALL_THISCALL);
    // ResourceRef StaticSprite2D::GetSpriteAttr() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "ResourceRef GetSpriteAttr() const", AS_METHODPR(AnimatedSprite2D, GetSpriteAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(AnimatedSprite2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // bool StaticSprite2D::GetSwapXY() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool GetSwapXY() const", AS_METHODPR(AnimatedSprite2D, GetSwapXY, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_swapXY() const", AS_METHODPR(AnimatedSprite2D, GetSwapXY, () const, bool), AS_CALL_THISCALL);
    // const Rect& StaticSprite2D::GetTextureRect() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "const Rect& GetTextureRect() const", AS_METHODPR(AnimatedSprite2D, GetTextureRect, () const, const Rect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "const Rect& get_textureRect() const", AS_METHODPR(AnimatedSprite2D, GetTextureRect, () const, const Rect&), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "StringHash GetType() const", AS_METHODPR(AnimatedSprite2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "StringHash get_type() const", AS_METHODPR(AnimatedSprite2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "const String& GetTypeName() const", AS_METHODPR(AnimatedSprite2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "const String& get_typeName() const", AS_METHODPR(AnimatedSprite2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // virtual UpdateGeometryType Drawable::GetUpdateGeometryType() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "UpdateGeometryType GetUpdateGeometryType()", AS_METHODPR(AnimatedSprite2D, GetUpdateGeometryType, (), UpdateGeometryType), AS_CALL_THISCALL);
    // bool StaticSprite2D::GetUseDrawRect() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool GetUseDrawRect() const", AS_METHODPR(AnimatedSprite2D, GetUseDrawRect, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_useDrawRect() const", AS_METHODPR(AnimatedSprite2D, GetUseDrawRect, () const, bool), AS_CALL_THISCALL);
    // bool StaticSprite2D::GetUseHotSpot() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool GetUseHotSpot() const", AS_METHODPR(AnimatedSprite2D, GetUseHotSpot, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_useHotSpot() const", AS_METHODPR(AnimatedSprite2D, GetUseHotSpot, () const, bool), AS_CALL_THISCALL);
    // bool StaticSprite2D::GetUseTextureRect() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool GetUseTextureRect() const", AS_METHODPR(AnimatedSprite2D, GetUseTextureRect, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_useTextureRect() const", AS_METHODPR(AnimatedSprite2D, GetUseTextureRect, () const, bool), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Array<Light@>@ GetVertexLights() const", AS_FUNCTION_OBJFIRST(AnimatedSprite2D_GetVertexLights_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint GetViewMask() const", AS_METHODPR(AnimatedSprite2D, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint get_viewMask() const", AS_METHODPR(AnimatedSprite2D, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "const BoundingBox& GetWorldBoundingBox()", AS_METHODPR(AnimatedSprite2D, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "const BoundingBox& get_worldBoundingBox()", AS_METHODPR(AnimatedSprite2D, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Zone@+ GetZone() const", AS_METHODPR(AnimatedSprite2D, GetZone, () const, Zone*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "Zone@+ get_zone() const", AS_METHODPR(AnimatedSprite2D, GetZone, () const, Zone*), AS_CALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint GetZoneMask() const", AS_METHODPR(AnimatedSprite2D, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint get_zoneMask() const", AS_METHODPR(AnimatedSprite2D, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool HasBasePass(uint) const", AS_METHODPR(AnimatedSprite2D, HasBasePass, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool HasEventHandlers() const", AS_METHODPR(AnimatedSprite2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(AnimatedSprite2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(AnimatedSprite2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool IsEnabled() const", AS_METHODPR(AnimatedSprite2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_enabled() const", AS_METHODPR(AnimatedSprite2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool IsEnabledEffective() const", AS_METHODPR(AnimatedSprite2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_enabledEffective() const", AS_METHODPR(AnimatedSprite2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(AnimatedSprite2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool IsInView() const", AS_METHODPR(AnimatedSprite2D, IsInView, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_inView() const", AS_METHODPR(AnimatedSprite2D, IsInView, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool IsInView(Camera@+) const", AS_METHODPR(AnimatedSprite2D, IsInView, (Camera*) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool IsInView(const FrameInfo&in, bool = false) const", AS_METHODPR(AnimatedSprite2D, IsInView, (const FrameInfo&, bool) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool IsOccludee() const", AS_METHODPR(AnimatedSprite2D, IsOccludee, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_occludee() const", AS_METHODPR(AnimatedSprite2D, IsOccludee, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool IsOccluder() const", AS_METHODPR(AnimatedSprite2D, IsOccluder, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_occluder() const", AS_METHODPR(AnimatedSprite2D, IsOccluder, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool IsReplicated() const", AS_METHODPR(AnimatedSprite2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_replicated() const", AS_METHODPR(AnimatedSprite2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool IsTemporary() const", AS_METHODPR(AnimatedSprite2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_temporary() const", AS_METHODPR(AnimatedSprite2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool IsZoneDirty() const", AS_METHODPR(AnimatedSprite2D, IsZoneDirty, () const, bool), AS_CALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void LimitLights()", AS_METHODPR(AnimatedSprite2D, LimitLights, (), void), AS_CALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void LimitVertexLights(bool)", AS_METHODPR(AnimatedSprite2D, LimitVertexLights, (bool), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool Load(Deserializer&)", AS_METHODPR(AnimatedSprite2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(AnimatedSprite2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(AnimatedSprite2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void MarkForUpdate()", AS_METHODPR(AnimatedSprite2D, MarkForUpdate, (), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void MarkInView(const FrameInfo&in)", AS_METHODPR(AnimatedSprite2D, MarkInView, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void MarkInView(uint)", AS_METHODPR(AnimatedSprite2D, MarkInView, (unsigned), void), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void MarkNetworkUpdate()", AS_METHODPR(AnimatedSprite2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(AnimatedSprite2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(AnimatedSprite2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(AnimatedSprite2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void AnimatedSprite2D::OnSetEnabled() override | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void OnSetEnabled()", AS_METHODPR(AnimatedSprite2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void PrepareNetworkUpdate()", AS_METHODPR(AnimatedSprite2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) | File: ../Graphics/Drawable.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(AnimatedSprite2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(AnimatedSprite2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "int Refs() const", AS_METHODPR(AnimatedSprite2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "int get_refs() const", AS_METHODPR(AnimatedSprite2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void AnimatedSprite2D::RegisterObject(Context* context) | File: ../Urho2D/AnimatedSprite2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("AnimatedSprite2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(AnimatedSprite2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void Remove()", AS_METHODPR(AnimatedSprite2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(AnimatedSprite2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void RemoveInstanceDefault()", AS_METHODPR(AnimatedSprite2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void RemoveObjectAnimation()", AS_METHODPR(AnimatedSprite2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void ResetToDefault()", AS_METHODPR(AnimatedSprite2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool Save(Serializer&) const", AS_METHODPR(AnimatedSprite2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool SaveDefaultAttributes() const", AS_METHODPR(AnimatedSprite2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(AnimatedSprite2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(AnimatedSprite2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SendEvent(StringHash)", AS_METHODPR(AnimatedSprite2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(AnimatedSprite2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void StaticSprite2D::SetAlpha(float alpha) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetAlpha(float)", AS_METHODPR(AnimatedSprite2D, SetAlpha, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_alpha(float)", AS_METHODPR(AnimatedSprite2D, SetAlpha, (float), void), AS_CALL_THISCALL);
    // void AnimatedSprite2D::SetAnimation(const String& name, LoopMode2D loopMode=LM_DEFAULT) | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetAnimation(const String&in, LoopMode2D = LM_DEFAULT)", AS_METHODPR(AnimatedSprite2D, SetAnimation, (const String&, LoopMode2D), void), AS_CALL_THISCALL);
    // void AnimatedSprite2D::SetAnimationAttr(const String& name) | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetAnimationAttr(const String&in)", AS_METHODPR(AnimatedSprite2D, SetAnimationAttr, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_animation(const String&in)", AS_METHODPR(AnimatedSprite2D, SetAnimationAttr, (const String&), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetAnimationEnabled(bool)", AS_METHODPR(AnimatedSprite2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_animationEnabled(bool)", AS_METHODPR(AnimatedSprite2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void AnimatedSprite2D::SetAnimationSet(AnimationSet2D* animationSet) | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetAnimationSet(AnimationSet2D@+)", AS_METHODPR(AnimatedSprite2D, SetAnimationSet, (AnimationSet2D*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_animationSet(AnimationSet2D@+)", AS_METHODPR(AnimatedSprite2D, SetAnimationSet, (AnimationSet2D*), void), AS_CALL_THISCALL);
    // void AnimatedSprite2D::SetAnimationSetAttr(const ResourceRef& value) | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetAnimationSetAttr(const ResourceRef&in)", AS_METHODPR(AnimatedSprite2D, SetAnimationSetAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetAnimationTime(float)", AS_METHODPR(AnimatedSprite2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(AnimatedSprite2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(AnimatedSprite2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(AnimatedSprite2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(AnimatedSprite2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(AnimatedSprite2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(AnimatedSprite2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(AnimatedSprite2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetBasePass(uint)", AS_METHODPR(AnimatedSprite2D, SetBasePass, (unsigned), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetBlendMode(BlendMode blendMode) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetBlendMode(BlendMode)", AS_METHODPR(AnimatedSprite2D, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_blendMode(BlendMode)", AS_METHODPR(AnimatedSprite2D, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetBlockEvents(bool)", AS_METHODPR(AnimatedSprite2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetCastShadows(bool)", AS_METHODPR(AnimatedSprite2D, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_castShadows(bool)", AS_METHODPR(AnimatedSprite2D, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetColor(const Color& color) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetColor(const Color&in)", AS_METHODPR(AnimatedSprite2D, SetColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_color(const Color&in)", AS_METHODPR(AnimatedSprite2D, SetColor, (const Color&), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetCustomMaterial(Material* customMaterial) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetCustomMaterial(Material@+)", AS_METHODPR(AnimatedSprite2D, SetCustomMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_customMaterial(Material@+)", AS_METHODPR(AnimatedSprite2D, SetCustomMaterial, (Material*), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetCustomMaterialAttr(const ResourceRef& value) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetCustomMaterialAttr(const ResourceRef&in)", AS_METHODPR(AnimatedSprite2D, SetCustomMaterialAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetDrawDistance(float)", AS_METHODPR(AnimatedSprite2D, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_drawDistance(float)", AS_METHODPR(AnimatedSprite2D, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetDrawRect(const Rect& rect) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetDrawRect(const Rect&in)", AS_METHODPR(AnimatedSprite2D, SetDrawRect, (const Rect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_drawRect(const Rect&in)", AS_METHODPR(AnimatedSprite2D, SetDrawRect, (const Rect&), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetEnabled(bool)", AS_METHODPR(AnimatedSprite2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_enabled(bool)", AS_METHODPR(AnimatedSprite2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void AnimatedSprite2D::SetEntity(const String& entity) | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetEntity(const String&in)", AS_METHODPR(AnimatedSprite2D, SetEntity, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_entity(const String&in)", AS_METHODPR(AnimatedSprite2D, SetEntity, (const String&), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetFlip(bool flipX, bool flipY, bool swapXY=false) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetFlip(bool, bool, bool = false)", AS_METHODPR(AnimatedSprite2D, SetFlip, (bool, bool, bool), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetFlipX(bool flipX) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetFlipX(bool)", AS_METHODPR(AnimatedSprite2D, SetFlipX, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_flipX(bool)", AS_METHODPR(AnimatedSprite2D, SetFlipX, (bool), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetFlipY(bool flipY) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetFlipY(bool)", AS_METHODPR(AnimatedSprite2D, SetFlipY, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_flipY(bool)", AS_METHODPR(AnimatedSprite2D, SetFlipY, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(AnimatedSprite2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(AnimatedSprite2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetHotSpot(const Vector2& hotspot) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetHotSpot(const Vector2&in)", AS_METHODPR(AnimatedSprite2D, SetHotSpot, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_hotSpot(const Vector2&in)", AS_METHODPR(AnimatedSprite2D, SetHotSpot, (const Vector2&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetInstanceDefault(bool)", AS_METHODPR(AnimatedSprite2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(AnimatedSprite2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Drawable2D::SetLayer(int layer) | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetLayer(int)", AS_METHODPR(AnimatedSprite2D, SetLayer, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_layer(int)", AS_METHODPR(AnimatedSprite2D, SetLayer, (int), void), AS_CALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetLightMask(uint)", AS_METHODPR(AnimatedSprite2D, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_lightMask(uint)", AS_METHODPR(AnimatedSprite2D, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetLodBias(float)", AS_METHODPR(AnimatedSprite2D, SetLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_lodBias(float)", AS_METHODPR(AnimatedSprite2D, SetLodBias, (float), void), AS_CALL_THISCALL);
    // void AnimatedSprite2D::SetLoopMode(LoopMode2D loopMode) | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetLoopMode(LoopMode2D)", AS_METHODPR(AnimatedSprite2D, SetLoopMode, (LoopMode2D), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_loopMode(LoopMode2D)", AS_METHODPR(AnimatedSprite2D, SetLoopMode, (LoopMode2D), void), AS_CALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetMaxLights(uint)", AS_METHODPR(AnimatedSprite2D, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_maxLights(uint)", AS_METHODPR(AnimatedSprite2D, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetMinMaxZ(float, float)", AS_METHODPR(AnimatedSprite2D, SetMinMaxZ, (float, float), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(AnimatedSprite2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(AnimatedSprite2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(AnimatedSprite2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetOccludee(bool)", AS_METHODPR(AnimatedSprite2D, SetOccludee, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_occludee(bool)", AS_METHODPR(AnimatedSprite2D, SetOccludee, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetOccluder(bool)", AS_METHODPR(AnimatedSprite2D, SetOccluder, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_occluder(bool)", AS_METHODPR(AnimatedSprite2D, SetOccluder, (bool), void), AS_CALL_THISCALL);
    // void Drawable2D::SetOrderInLayer(int orderInLayer) | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetOrderInLayer(int)", AS_METHODPR(AnimatedSprite2D, SetOrderInLayer, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_orderInLayer(int)", AS_METHODPR(AnimatedSprite2D, SetOrderInLayer, (int), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetShadowDistance(float)", AS_METHODPR(AnimatedSprite2D, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_shadowDistance(float)", AS_METHODPR(AnimatedSprite2D, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetShadowMask(uint)", AS_METHODPR(AnimatedSprite2D, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_shadowMask(uint)", AS_METHODPR(AnimatedSprite2D, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetSortValue(float)", AS_METHODPR(AnimatedSprite2D, SetSortValue, (float), void), AS_CALL_THISCALL);
    // void AnimatedSprite2D::SetSpeed(float speed) | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetSpeed(float)", AS_METHODPR(AnimatedSprite2D, SetSpeed, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_speed(float)", AS_METHODPR(AnimatedSprite2D, SetSpeed, (float), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetSprite(Sprite2D* sprite) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetSprite(Sprite2D@+)", AS_METHODPR(AnimatedSprite2D, SetSprite, (Sprite2D*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_sprite(Sprite2D@+)", AS_METHODPR(AnimatedSprite2D, SetSprite, (Sprite2D*), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetSpriteAttr(const ResourceRef& value) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetSpriteAttr(const ResourceRef&in)", AS_METHODPR(AnimatedSprite2D, SetSpriteAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetSwapXY(bool swapXY) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetSwapXY(bool)", AS_METHODPR(AnimatedSprite2D, SetSwapXY, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_swapXY(bool)", AS_METHODPR(AnimatedSprite2D, SetSwapXY, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetTemporary(bool)", AS_METHODPR(AnimatedSprite2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_temporary(bool)", AS_METHODPR(AnimatedSprite2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetTextureRect(const Rect& rect) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetTextureRect(const Rect&in)", AS_METHODPR(AnimatedSprite2D, SetTextureRect, (const Rect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_textureRect(const Rect&in)", AS_METHODPR(AnimatedSprite2D, SetTextureRect, (const Rect&), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetUseDrawRect(bool useDrawRect) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetUseDrawRect(bool)", AS_METHODPR(AnimatedSprite2D, SetUseDrawRect, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_useDrawRect(bool)", AS_METHODPR(AnimatedSprite2D, SetUseDrawRect, (bool), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetUseHotSpot(bool useHotSpot) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetUseHotSpot(bool)", AS_METHODPR(AnimatedSprite2D, SetUseHotSpot, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_useHotSpot(bool)", AS_METHODPR(AnimatedSprite2D, SetUseHotSpot, (bool), void), AS_CALL_THISCALL);
    // void StaticSprite2D::SetUseTextureRect(bool useTextureRect) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetUseTextureRect(bool)", AS_METHODPR(AnimatedSprite2D, SetUseTextureRect, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_useTextureRect(bool)", AS_METHODPR(AnimatedSprite2D, SetUseTextureRect, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetViewMask(uint)", AS_METHODPR(AnimatedSprite2D, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_viewMask(uint)", AS_METHODPR(AnimatedSprite2D, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetZone(Zone@+, bool = false)", AS_METHODPR(AnimatedSprite2D, SetZone, (Zone*, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetZoneMask(uint)", AS_METHODPR(AnimatedSprite2D, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_zoneMask(uint)", AS_METHODPR(AnimatedSprite2D, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(AnimatedSprite2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(AnimatedSprite2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(AnimatedSprite2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(AnimatedSprite2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(AnimatedSprite2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void Update(const FrameInfo&in)", AS_METHODPR(AnimatedSprite2D, Update, (const FrameInfo&), void), AS_CALL_THISCALL);
    // virtual void Drawable::UpdateBatches(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void UpdateBatches(const FrameInfo&in)", AS_METHODPR(AnimatedSprite2D, UpdateBatches, (const FrameInfo&), void), AS_CALL_THISCALL);
    // virtual void Drawable::UpdateGeometry(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void UpdateGeometry(const FrameInfo&in)", AS_METHODPR(AnimatedSprite2D, UpdateGeometry, (const FrameInfo&), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "int WeakRefs() const", AS_METHODPR(AnimatedSprite2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "int get_weakRefs() const", AS_METHODPR(AnimatedSprite2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(AnimatedSprite2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(AnimatedSprite2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(AnimatedSprite2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_StaticSprite2D
    REGISTER_MANUAL_PART_StaticSprite2D(AnimatedSprite2D, "AnimatedSprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_Drawable2D
    REGISTER_MANUAL_PART_Drawable2D(AnimatedSprite2D, "AnimatedSprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_Drawable
    REGISTER_MANUAL_PART_Drawable(AnimatedSprite2D, "AnimatedSprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(AnimatedSprite2D, "AnimatedSprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(AnimatedSprite2D, "AnimatedSprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(AnimatedSprite2D, "AnimatedSprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(AnimatedSprite2D, "AnimatedSprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(AnimatedSprite2D, "AnimatedSprite2D")
#endif
#ifdef REGISTER_MANUAL_PART_AnimatedSprite2D
    REGISTER_MANUAL_PART_AnimatedSprite2D(AnimatedSprite2D, "AnimatedSprite2D")
#endif
    RegisterSubclass<StaticSprite2D, AnimatedSprite2D>(engine, "StaticSprite2D", "AnimatedSprite2D");
    RegisterSubclass<Drawable2D, AnimatedSprite2D>(engine, "Drawable2D", "AnimatedSprite2D");
    RegisterSubclass<Drawable, AnimatedSprite2D>(engine, "Drawable", "AnimatedSprite2D");
    RegisterSubclass<Component, AnimatedSprite2D>(engine, "Component", "AnimatedSprite2D");
    RegisterSubclass<Animatable, AnimatedSprite2D>(engine, "Animatable", "AnimatedSprite2D");
    RegisterSubclass<Serializable, AnimatedSprite2D>(engine, "Serializable", "AnimatedSprite2D");
    RegisterSubclass<Object, AnimatedSprite2D>(engine, "Object", "AnimatedSprite2D");
    RegisterSubclass<RefCounted, AnimatedSprite2D>(engine, "RefCounted", "AnimatedSprite2D");
#endif

    // void ResourceWithMetadata::AddMetadata(const String& name, const Variant& value) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "void AddMetadata(const String&in, const Variant&in)", AS_METHODPR(Animation, AddMetadata, (const String&, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "void set_metadata(const String&in, const Variant&in)", AS_METHODPR(Animation, AddMetadata, (const String&, const Variant&), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Animation", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Animation, AddRef, (), void), AS_CALL_THISCALL);
    // void Animation::AddTrigger(const AnimationTriggerPoint& trigger) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "void AddTrigger(const AnimationTriggerPoint&in)", AS_METHODPR(Animation, AddTrigger, (const AnimationTriggerPoint&), void), AS_CALL_THISCALL);
    // void Animation::AddTrigger(float time, bool timeIsNormalized, const Variant& data) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "void AddTrigger(float, bool, const Variant&in)", AS_METHODPR(Animation, AddTrigger, (float, bool, const Variant&), void), AS_CALL_THISCALL);
    // explicit Animation::Animation(Context* context) | File: ../Graphics/Animation.h
    engine->RegisterObjectBehaviour("Animation", asBEHAVE_FACTORY, "Animation@+ f()", AS_FUNCTION(Animation_Animation_Context), AS_CALL_CDECL);
    // bool Animation::BeginLoad(Deserializer& source) override | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "bool BeginLoad(Deserializer&)", AS_METHODPR(Animation, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // SharedPtr<Animation> Animation::Clone(const String& cloneName=String::EMPTY) const | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "Animation@+ Clone(const String&in = String::EMPTY) const", AS_FUNCTION_OBJFIRST(Animation_Clone_String), AS_CALL_CDECL_OBJFIRST);
    // AnimationTrack* Animation::CreateTrack(const String& name) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "AnimationTrack@+ CreateTrack(const String&in)", AS_METHODPR(Animation, CreateTrack, (const String&), AnimationTrack*), AS_CALL_THISCALL);
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "bool EndLoad()", AS_METHODPR(Animation, EndLoad, (), bool), AS_CALL_THISCALL);
    // const String& Animation::GetAnimationName() const | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "const String& GetAnimationName() const", AS_METHODPR(Animation, GetAnimationName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "const String& get_animationName() const", AS_METHODPR(Animation, GetAnimationName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Animation::GetAnimationNameHash() const | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "StringHash GetAnimationNameHash() const", AS_METHODPR(Animation, GetAnimationNameHash, () const, StringHash), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(Animation, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "bool GetBlockEvents() const", AS_METHODPR(Animation, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "const String& GetCategory() const", AS_METHODPR(Animation, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "const String& get_category() const", AS_METHODPR(Animation, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "VariantMap& GetEventDataMap() const", AS_METHODPR(Animation, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "Object@+ GetEventSender() const", AS_METHODPR(Animation, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Animation, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Animation, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Animation, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "const VariantMap& get_globalVars() const", AS_METHODPR(Animation, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // float Animation::GetLength() const | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "float GetLength() const", AS_METHODPR(Animation, GetLength, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "float get_length() const", AS_METHODPR(Animation, GetLength, () const, float), AS_CALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "uint GetMemoryUse() const", AS_METHODPR(Animation, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "uint get_memoryUse() const", AS_METHODPR(Animation, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // const Variant& ResourceWithMetadata::GetMetadata(const String& name) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "const Variant& GetMetadata(const String&in) const", AS_METHODPR(Animation, GetMetadata, (const String&) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "const Variant& get_metadata(const String&in) const", AS_METHODPR(Animation, GetMetadata, (const String&) const, const Variant&), AS_CALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "const String& GetName() const", AS_METHODPR(Animation, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "const String& get_name() const", AS_METHODPR(Animation, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "StringHash GetNameHash() const", AS_METHODPR(Animation, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // unsigned Animation::GetNumTracks() const | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "uint GetNumTracks() const", AS_METHODPR(Animation, GetNumTracks, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "uint get_numTracks() const", AS_METHODPR(Animation, GetNumTracks, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Animation::GetNumTriggers() const | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "uint GetNumTriggers() const", AS_METHODPR(Animation, GetNumTriggers, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "uint get_numTriggers() const", AS_METHODPR(Animation, GetNumTriggers, () const, unsigned), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Animation, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // AnimationTrack* Animation::GetTrack(unsigned index) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "AnimationTrack@+ GetTrack(uint)", AS_METHODPR(Animation, GetTrack, (unsigned), AnimationTrack*), AS_CALL_THISCALL);
    // AnimationTrack* Animation::GetTrack(const String& name) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "AnimationTrack@+ GetTrack(const String&in)", AS_METHODPR(Animation, GetTrack, (const String&), AnimationTrack*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "AnimationTrack@+ get_tracks(const String&in)", AS_METHODPR(Animation, GetTrack, (const String&), AnimationTrack*), AS_CALL_THISCALL);
    // AnimationTrack* Animation::GetTrack(StringHash nameHash) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "AnimationTrack@+ GetTrack(StringHash)", AS_METHODPR(Animation, GetTrack, (StringHash), AnimationTrack*), AS_CALL_THISCALL);
    // const HashMap<StringHash, AnimationTrack>& Animation::GetTracks() const | File: ../Graphics/Animation.h
    // Error: type "const HashMap<StringHash, AnimationTrack>&" can not automatically bind
    // AnimationTriggerPoint* Animation::GetTrigger(unsigned index) | File: ../Graphics/Animation.h
    // Error: type "AnimationTriggerPoint*" can not automatically bind
    // const Vector<AnimationTriggerPoint>& Animation::GetTriggers() const | File: ../Graphics/Animation.h
    // Error: type "const Vector<AnimationTriggerPoint>&" can not automatically bind
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "StringHash GetType() const", AS_METHODPR(Animation, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "StringHash get_type() const", AS_METHODPR(Animation, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "const String& GetTypeName() const", AS_METHODPR(Animation, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "const String& get_typeName() const", AS_METHODPR(Animation, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "uint GetUseTimer()", AS_METHODPR(Animation, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "uint get_useTimer()", AS_METHODPR(Animation, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "bool HasEventHandlers() const", AS_METHODPR(Animation, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool ResourceWithMetadata::HasMetadata() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "bool HasMetadata() const", AS_METHODPR(Animation, HasMetadata, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "bool get_hasMetadata() const", AS_METHODPR(Animation, HasMetadata, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Animation, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Animation, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Animation, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "bool Load(Deserializer&)", AS_METHODPR(Animation, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "bool LoadFile(const String&in)", AS_METHODPR(Animation, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "bool Load(const String&in)", AS_METHODPR(Animation, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Animation, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Animation", "int Refs() const", AS_METHODPR(Animation, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "int get_refs() const", AS_METHODPR(Animation, Refs, () const, int), AS_CALL_THISCALL);
    // static void Animation::RegisterObject(Context* context) | File: ../Graphics/Animation.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Animation", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Animation, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void ResourceWithMetadata::RemoveAllMetadata() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "void RemoveAllMetadata()", AS_METHODPR(Animation, RemoveAllMetadata, (), void), AS_CALL_THISCALL);
    // void Animation::RemoveAllTracks() | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "void RemoveAllTracks()", AS_METHODPR(Animation, RemoveAllTracks, (), void), AS_CALL_THISCALL);
    // void Animation::RemoveAllTriggers() | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "void RemoveAllTriggers()", AS_METHODPR(Animation, RemoveAllTriggers, (), void), AS_CALL_THISCALL);
    // void ResourceWithMetadata::RemoveMetadata(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "void RemoveMetadata(const String&in)", AS_METHODPR(Animation, RemoveMetadata, (const String&), void), AS_CALL_THISCALL);
    // bool Animation::RemoveTrack(const String& name) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "bool RemoveTrack(const String&in)", AS_METHODPR(Animation, RemoveTrack, (const String&), bool), AS_CALL_THISCALL);
    // void Animation::RemoveTrigger(unsigned index) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "void RemoveTrigger(uint)", AS_METHODPR(Animation, RemoveTrigger, (unsigned), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "void ResetUseTimer()", AS_METHODPR(Animation, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // bool Animation::Save(Serializer& dest) const override | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "bool Save(Serializer&) const", AS_METHODPR(Animation, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "bool SaveFile(const String&in) const", AS_METHODPR(Animation, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "bool Save(const String&in) const", AS_METHODPR(Animation, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "void SendEvent(StringHash)", AS_METHODPR(Animation, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Animation, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animation::SetAnimationName(const String& name) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "void SetAnimationName(const String&in)", AS_METHODPR(Animation, SetAnimationName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "void set_animationName(const String&in)", AS_METHODPR(Animation, SetAnimationName, (const String&), void), AS_CALL_THISCALL);
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(Animation, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "void SetBlockEvents(bool)", AS_METHODPR(Animation, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Animation, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Animation, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Animation::SetLength(float length) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "void SetLength(float)", AS_METHODPR(Animation, SetLength, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "void set_length(float)", AS_METHODPR(Animation, SetLength, (float), void), AS_CALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "void SetMemoryUse(uint)", AS_METHODPR(Animation, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "void SetName(const String&in)", AS_METHODPR(Animation, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "void set_name(const String&in)", AS_METHODPR(Animation, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Animation::SetNumTriggers(unsigned num) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "void SetNumTriggers(uint)", AS_METHODPR(Animation, SetNumTriggers, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "void set_numTriggers(uint)", AS_METHODPR(Animation, SetNumTriggers, (unsigned), void), AS_CALL_THISCALL);
    // void Animation::SetTrigger(unsigned index, const AnimationTriggerPoint& trigger) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "void SetTrigger(uint, const AnimationTriggerPoint&in)", AS_METHODPR(Animation, SetTrigger, (unsigned, const AnimationTriggerPoint&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "void set_triggers(uint, const AnimationTriggerPoint&in)", AS_METHODPR(Animation, SetTrigger, (unsigned, const AnimationTriggerPoint&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "void UnsubscribeFromAllEvents()", AS_METHODPR(Animation, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Animation_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Animation, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Animation, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Animation, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Animation", "int WeakRefs() const", AS_METHODPR(Animation, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "int get_weakRefs() const", AS_METHODPR(Animation, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_ResourceWithMetadata
    REGISTER_MANUAL_PART_ResourceWithMetadata(Animation, "Animation")
#endif
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(Animation, "Animation")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Animation, "Animation")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Animation, "Animation")
#endif
#ifdef REGISTER_MANUAL_PART_Animation
    REGISTER_MANUAL_PART_Animation(Animation, "Animation")
#endif
    RegisterSubclass<ResourceWithMetadata, Animation>(engine, "ResourceWithMetadata", "Animation");
    RegisterSubclass<Resource, Animation>(engine, "Resource", "Animation");
    RegisterSubclass<Object, Animation>(engine, "Object", "Animation");
    RegisterSubclass<RefCounted, Animation>(engine, "RefCounted", "Animation");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("AnimationController", asBEHAVE_ADDREF, "void f()", AS_METHODPR(AnimationController, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "void AllocateNetworkState()", AS_METHODPR(AnimationController, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // explicit AnimationController::AnimationController(Context* context) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectBehaviour("AnimationController", asBEHAVE_FACTORY, "AnimationController@+ f()", AS_FUNCTION(AnimationController_AnimationController_Context), AS_CALL_CDECL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "void ApplyAttributes()", AS_METHODPR(AnimationController, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(AnimationController, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool AnimationController::Fade(const String& name, float targetWeight, float fadeTime) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool Fade(const String&in, float, float)", AS_METHODPR(AnimationController, Fade, (const String&, float, float), bool), AS_CALL_THISCALL);
    // bool AnimationController::FadeOthers(const String& name, float targetWeight, float fadeTime) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool FadeOthers(const String&in, float, float)", AS_METHODPR(AnimationController, FadeOthers, (const String&, float, float), bool), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "bool GetAnimationEnabled() const", AS_METHODPR(AnimationController, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool get_animationEnabled() const", AS_METHODPR(AnimationController, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // const Vector<AnimationControl>& AnimationController::GetAnimations() const | File: ../Graphics/AnimationController.h
    // Error: type "const Vector<AnimationControl>&" can not automatically bind
    // VariantVector AnimationController::GetAnimationsAttr() const | File: ../Graphics/AnimationController.h
    // Error: type "VariantVector" can not automatically bind
    // AnimationState* AnimationController::GetAnimationState(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "AnimationState@+ GetAnimationState(const String&in) const", AS_METHODPR(AnimationController, GetAnimationState, (const String&) const, AnimationState*), AS_CALL_THISCALL);
    // AnimationState* AnimationController::GetAnimationState(StringHash nameHash) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "AnimationState@+ GetAnimationState(StringHash) const", AS_METHODPR(AnimationController, GetAnimationState, (StringHash) const, AnimationState*), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "Variant GetAttribute(uint) const", AS_METHODPR(AnimationController, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "Variant get_attributes(uint) const", AS_METHODPR(AnimationController, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "Variant GetAttribute(const String&in) const", AS_METHODPR(AnimationController, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(AnimationController, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(AnimationController, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(AnimationController, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(AnimationController, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "Variant GetAttributeDefault(uint) const", AS_METHODPR(AnimationController, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "Variant get_attributeDefaults(uint) const", AS_METHODPR(AnimationController, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(AnimationController, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // float AnimationController::GetAutoFade(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "float GetAutoFade(const String&in) const", AS_METHODPR(AnimationController, GetAutoFade, (const String&) const, float), AS_CALL_THISCALL);
    // AnimationBlendMode AnimationController::GetBlendMode(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "AnimationBlendMode GetBlendMode(const String&in) const", AS_METHODPR(AnimationController, GetBlendMode, (const String&) const, AnimationBlendMode), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "bool GetBlockEvents() const", AS_METHODPR(AnimationController, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "const String& GetCategory() const", AS_METHODPR(AnimationController, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "const String& get_category() const", AS_METHODPR(AnimationController, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "Component@+ GetComponent(StringHash) const", AS_METHODPR(AnimationController, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("AnimationController", "VariantMap& GetEventDataMap() const", AS_METHODPR(AnimationController, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "Object@+ GetEventSender() const", AS_METHODPR(AnimationController, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // float AnimationController::GetFadeTarget(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "float GetFadeTarget(const String&in) const", AS_METHODPR(AnimationController, GetFadeTarget, (const String&) const, float), AS_CALL_THISCALL);
    // float AnimationController::GetFadeTime(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "float GetFadeTime(const String&in) const", AS_METHODPR(AnimationController, GetFadeTime, (const String&) const, float), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(AnimationController, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(AnimationController, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "const VariantMap& GetGlobalVars() const", AS_METHODPR(AnimationController, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "const VariantMap& get_globalVars() const", AS_METHODPR(AnimationController, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "uint GetID() const", AS_METHODPR(AnimationController, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "uint get_id() const", AS_METHODPR(AnimationController, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(AnimationController, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // unsigned char AnimationController::GetLayer(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "uint8 GetLayer(const String&in) const", AS_METHODPR(AnimationController, GetLayer, (const String&) const, unsigned char), AS_CALL_THISCALL);
    // float AnimationController::GetLength(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "float GetLength(const String&in) const", AS_METHODPR(AnimationController, GetLength, (const String&) const, float), AS_CALL_THISCALL);
    // const PODVector<unsigned char>& AnimationController::GetNetAnimationsAttr() const | File: ../Graphics/AnimationController.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "Node@+ GetNode() const", AS_METHODPR(AnimationController, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "Node@+ get_node() const", AS_METHODPR(AnimationController, GetNode, () const, Node*), AS_CALL_THISCALL);
    // VariantVector AnimationController::GetNodeAnimationStatesAttr() const | File: ../Graphics/AnimationController.h
    // Error: type "VariantVector" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "uint GetNumAttributes() const", AS_METHODPR(AnimationController, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "uint get_numAttributes() const", AS_METHODPR(AnimationController, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "uint GetNumNetworkAttributes() const", AS_METHODPR(AnimationController, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(AnimationController, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(AnimationController, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(AnimationController, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // bool AnimationController::GetRemoveOnCompletion(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool GetRemoveOnCompletion(const String&in) const", AS_METHODPR(AnimationController, GetRemoveOnCompletion, (const String&) const, bool), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "Scene@+ GetScene() const", AS_METHODPR(AnimationController, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // float AnimationController::GetSpeed(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "float GetSpeed(const String&in) const", AS_METHODPR(AnimationController, GetSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // Bone* AnimationController::GetStartBone(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "Bone@+ GetStartBone(const String&in) const", AS_METHODPR(AnimationController, GetStartBone, (const String&) const, Bone*), AS_CALL_THISCALL);
    // const String& AnimationController::GetStartBoneName(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "const String& GetStartBoneName(const String&in) const", AS_METHODPR(AnimationController, GetStartBoneName, (const String&) const, const String&), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(AnimationController, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // float AnimationController::GetTime(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "float GetTime(const String&in) const", AS_METHODPR(AnimationController, GetTime, (const String&) const, float), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "StringHash GetType() const", AS_METHODPR(AnimationController, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "StringHash get_type() const", AS_METHODPR(AnimationController, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "const String& GetTypeName() const", AS_METHODPR(AnimationController, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "const String& get_typeName() const", AS_METHODPR(AnimationController, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // float AnimationController::GetWeight(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "float GetWeight(const String&in) const", AS_METHODPR(AnimationController, GetWeight, (const String&) const, float), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "bool HasEventHandlers() const", AS_METHODPR(AnimationController, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(AnimationController, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(AnimationController, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool AnimationController::IsAtEnd(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool IsAtEnd(const String&in) const", AS_METHODPR(AnimationController, IsAtEnd, (const String&) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "bool IsEnabled() const", AS_METHODPR(AnimationController, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool get_enabled() const", AS_METHODPR(AnimationController, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "bool IsEnabledEffective() const", AS_METHODPR(AnimationController, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool get_enabledEffective() const", AS_METHODPR(AnimationController, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool AnimationController::IsFadingIn(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool IsFadingIn(const String&in) const", AS_METHODPR(AnimationController, IsFadingIn, (const String&) const, bool), AS_CALL_THISCALL);
    // bool AnimationController::IsFadingOut(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool IsFadingOut(const String&in) const", AS_METHODPR(AnimationController, IsFadingOut, (const String&) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "bool IsInstanceOf(StringHash) const", AS_METHODPR(AnimationController, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool AnimationController::IsLooped(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool IsLooped(const String&in) const", AS_METHODPR(AnimationController, IsLooped, (const String&) const, bool), AS_CALL_THISCALL);
    // bool AnimationController::IsPlaying(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool IsPlaying(const String&in) const", AS_METHODPR(AnimationController, IsPlaying, (const String&) const, bool), AS_CALL_THISCALL);
    // bool AnimationController::IsPlaying(unsigned char layer) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool IsPlaying(uint8) const", AS_METHODPR(AnimationController, IsPlaying, (unsigned char) const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "bool IsReplicated() const", AS_METHODPR(AnimationController, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool get_replicated() const", AS_METHODPR(AnimationController, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "bool IsTemporary() const", AS_METHODPR(AnimationController, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool get_temporary() const", AS_METHODPR(AnimationController, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "bool Load(Deserializer&)", AS_METHODPR(AnimationController, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(AnimationController, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "bool LoadXML(const XMLElement&in)", AS_METHODPR(AnimationController, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "void MarkNetworkUpdate()", AS_METHODPR(AnimationController, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(AnimationController, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(AnimationController, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(AnimationController, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void AnimationController::OnSetEnabled() override | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "void OnSetEnabled()", AS_METHODPR(AnimationController, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // bool AnimationController::Play(const String& name, unsigned char layer, bool looped, float fadeInTime=0.0f) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool Play(const String&in, uint8, bool, float = 0.0f)", AS_METHODPR(AnimationController, Play, (const String&, unsigned char, bool, float), bool), AS_CALL_THISCALL);
    // bool AnimationController::PlayExclusive(const String& name, unsigned char layer, bool looped, float fadeTime=0.0f) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool PlayExclusive(const String&in, uint8, bool, float = 0.0f)", AS_METHODPR(AnimationController, PlayExclusive, (const String&, unsigned char, bool, float), bool), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "void PrepareNetworkUpdate()", AS_METHODPR(AnimationController, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(AnimationController, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(AnimationController, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AnimationController", "int Refs() const", AS_METHODPR(AnimationController, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "int get_refs() const", AS_METHODPR(AnimationController, Refs, () const, int), AS_CALL_THISCALL);
    // static void AnimationController::RegisterObject(Context* context) | File: ../Graphics/AnimationController.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("AnimationController", asBEHAVE_RELEASE, "void f()", AS_METHODPR(AnimationController, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "void Remove()", AS_METHODPR(AnimationController, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(AnimationController, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "void RemoveInstanceDefault()", AS_METHODPR(AnimationController, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "void RemoveObjectAnimation()", AS_METHODPR(AnimationController, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "void ResetToDefault()", AS_METHODPR(AnimationController, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "bool Save(Serializer&) const", AS_METHODPR(AnimationController, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "bool SaveDefaultAttributes() const", AS_METHODPR(AnimationController, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "bool SaveJSON(JSONValue&) const", AS_METHODPR(AnimationController, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "bool SaveXML(XMLElement&) const", AS_METHODPR(AnimationController, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "void SendEvent(StringHash)", AS_METHODPR(AnimationController, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(AnimationController, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "void SetAnimationEnabled(bool)", AS_METHODPR(AnimationController, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "void set_animationEnabled(bool)", AS_METHODPR(AnimationController, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void AnimationController::SetAnimationsAttr(const VariantVector& value) | File: ../Graphics/AnimationController.h
    // Error: type "const VariantVector&" can not automatically bind
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "void SetAnimationTime(float)", AS_METHODPR(AnimationController, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(AnimationController, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(AnimationController, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(AnimationController, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(AnimationController, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(AnimationController, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(AnimationController, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(AnimationController, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // bool AnimationController::SetAutoFade(const String& name, float fadeOutTime) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool SetAutoFade(const String&in, float)", AS_METHODPR(AnimationController, SetAutoFade, (const String&, float), bool), AS_CALL_THISCALL);
    // bool AnimationController::SetBlendMode(const String& name, AnimationBlendMode mode) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool SetBlendMode(const String&in, AnimationBlendMode)", AS_METHODPR(AnimationController, SetBlendMode, (const String&, AnimationBlendMode), bool), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "void SetBlockEvents(bool)", AS_METHODPR(AnimationController, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "void SetEnabled(bool)", AS_METHODPR(AnimationController, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "void set_enabled(bool)", AS_METHODPR(AnimationController, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(AnimationController, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(AnimationController, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "void SetInstanceDefault(bool)", AS_METHODPR(AnimationController, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(AnimationController, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // bool AnimationController::SetLayer(const String& name, unsigned char layer) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool SetLayer(const String&in, uint8)", AS_METHODPR(AnimationController, SetLayer, (const String&, unsigned char), bool), AS_CALL_THISCALL);
    // bool AnimationController::SetLooped(const String& name, bool enable) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool SetLooped(const String&in, bool)", AS_METHODPR(AnimationController, SetLooped, (const String&, bool), bool), AS_CALL_THISCALL);
    // void AnimationController::SetNetAnimationsAttr(const PODVector<unsigned char>& value) | File: ../Graphics/AnimationController.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void AnimationController::SetNodeAnimationStatesAttr(const VariantVector& value) | File: ../Graphics/AnimationController.h
    // Error: type "const VariantVector&" can not automatically bind
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(AnimationController, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(AnimationController, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(AnimationController, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // bool AnimationController::SetRemoveOnCompletion(const String& name, bool removeOnCompletion) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool SetRemoveOnCompletion(const String&in, bool)", AS_METHODPR(AnimationController, SetRemoveOnCompletion, (const String&, bool), bool), AS_CALL_THISCALL);
    // bool AnimationController::SetSpeed(const String& name, float speed) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool SetSpeed(const String&in, float)", AS_METHODPR(AnimationController, SetSpeed, (const String&, float), bool), AS_CALL_THISCALL);
    // bool AnimationController::SetStartBone(const String& name, const String& startBoneName) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool SetStartBone(const String&in, const String&in)", AS_METHODPR(AnimationController, SetStartBone, (const String&, const String&), bool), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "void SetTemporary(bool)", AS_METHODPR(AnimationController, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "void set_temporary(bool)", AS_METHODPR(AnimationController, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // bool AnimationController::SetTime(const String& name, float time) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool SetTime(const String&in, float)", AS_METHODPR(AnimationController, SetTime, (const String&, float), bool), AS_CALL_THISCALL);
    // bool AnimationController::SetWeight(const String& name, float weight) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool SetWeight(const String&in, float)", AS_METHODPR(AnimationController, SetWeight, (const String&, float), bool), AS_CALL_THISCALL);
    // bool AnimationController::Stop(const String& name, float fadeOutTime=0.0f) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool Stop(const String&in, float = 0.0f)", AS_METHODPR(AnimationController, Stop, (const String&, float), bool), AS_CALL_THISCALL);
    // void AnimationController::StopAll(float fadeOutTime=0.0f) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "void StopAll(float = 0.0f)", AS_METHODPR(AnimationController, StopAll, (float), void), AS_CALL_THISCALL);
    // void AnimationController::StopLayer(unsigned char layer, float fadeOutTime=0.0f) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "void StopLayer(uint8, float = 0.0f)", AS_METHODPR(AnimationController, StopLayer, (unsigned char, float), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "void UnsubscribeFromAllEvents()", AS_METHODPR(AnimationController, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(AnimationController_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(AnimationController, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(AnimationController, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(AnimationController, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void AnimationController::Update(float timeStep) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "void Update(float)", AS_METHODPR(AnimationController, Update, (float), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AnimationController", "int WeakRefs() const", AS_METHODPR(AnimationController, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "int get_weakRefs() const", AS_METHODPR(AnimationController, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(AnimationController, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(AnimationController, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(AnimationController, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(AnimationController, "AnimationController")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(AnimationController, "AnimationController")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(AnimationController, "AnimationController")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(AnimationController, "AnimationController")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(AnimationController, "AnimationController")
#endif
#ifdef REGISTER_MANUAL_PART_AnimationController
    REGISTER_MANUAL_PART_AnimationController(AnimationController, "AnimationController")
#endif
    RegisterSubclass<Component, AnimationController>(engine, "Component", "AnimationController");
    RegisterSubclass<Animatable, AnimationController>(engine, "Animatable", "AnimationController");
    RegisterSubclass<Serializable, AnimationController>(engine, "Serializable", "AnimationController");
    RegisterSubclass<Object, AnimationController>(engine, "Object", "AnimationController");
    RegisterSubclass<RefCounted, AnimationController>(engine, "RefCounted", "AnimationController");

#ifdef URHO3D_URHO2D
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("AnimationSet2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(AnimationSet2D, AddRef, (), void), AS_CALL_THISCALL);
    // explicit AnimationSet2D::AnimationSet2D(Context* context) | File: ../Urho2D/AnimationSet2D.h
    engine->RegisterObjectBehaviour("AnimationSet2D", asBEHAVE_FACTORY, "AnimationSet2D@+ f()", AS_FUNCTION(AnimationSet2D_AnimationSet2D_Context), AS_CALL_CDECL);
    // bool AnimationSet2D::BeginLoad(Deserializer& source) override | File: ../Urho2D/AnimationSet2D.h
    engine->RegisterObjectMethod("AnimationSet2D", "bool BeginLoad(Deserializer&)", AS_METHODPR(AnimationSet2D, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool AnimationSet2D::EndLoad() override | File: ../Urho2D/AnimationSet2D.h
    engine->RegisterObjectMethod("AnimationSet2D", "bool EndLoad()", AS_METHODPR(AnimationSet2D, EndLoad, (), bool), AS_CALL_THISCALL);
    // String AnimationSet2D::GetAnimation(unsigned index) const | File: ../Urho2D/AnimationSet2D.h
    engine->RegisterObjectMethod("AnimationSet2D", "String GetAnimation(uint) const", AS_METHODPR(AnimationSet2D, GetAnimation, (unsigned) const, String), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(AnimationSet2D, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "bool GetBlockEvents() const", AS_METHODPR(AnimationSet2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "const String& GetCategory() const", AS_METHODPR(AnimationSet2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "const String& get_category() const", AS_METHODPR(AnimationSet2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(AnimationSet2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "Object@+ GetEventSender() const", AS_METHODPR(AnimationSet2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(AnimationSet2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(AnimationSet2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(AnimationSet2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "const VariantMap& get_globalVars() const", AS_METHODPR(AnimationSet2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "uint GetMemoryUse() const", AS_METHODPR(AnimationSet2D, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "uint get_memoryUse() const", AS_METHODPR(AnimationSet2D, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "const String& GetName() const", AS_METHODPR(AnimationSet2D, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "const String& get_name() const", AS_METHODPR(AnimationSet2D, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "StringHash GetNameHash() const", AS_METHODPR(AnimationSet2D, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // unsigned AnimationSet2D::GetNumAnimations() const | File: ../Urho2D/AnimationSet2D.h
    engine->RegisterObjectMethod("AnimationSet2D", "uint GetNumAnimations() const", AS_METHODPR(AnimationSet2D, GetNumAnimations, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "uint get_numAnimations() const", AS_METHODPR(AnimationSet2D, GetNumAnimations, () const, unsigned), AS_CALL_THISCALL);
    // Sprite2D* AnimationSet2D::GetSprite() const | File: ../Urho2D/AnimationSet2D.h
    engine->RegisterObjectMethod("AnimationSet2D", "Sprite2D@+ GetSprite() const", AS_METHODPR(AnimationSet2D, GetSprite, () const, Sprite2D*), AS_CALL_THISCALL);
    // Spriter::SpriterData* AnimationSet2D::GetSpriterData() const | File: ../Urho2D/AnimationSet2D.h
    // Error: type "Spriter::SpriterData*" can not automatically bind
    // Sprite2D* AnimationSet2D::GetSpriterFileSprite(int folderId, int fileId) const | File: ../Urho2D/AnimationSet2D.h
    engine->RegisterObjectMethod("AnimationSet2D", "Sprite2D@+ GetSpriterFileSprite(int, int) const", AS_METHODPR(AnimationSet2D, GetSpriterFileSprite, (int, int) const, Sprite2D*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(AnimationSet2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "StringHash GetType() const", AS_METHODPR(AnimationSet2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "StringHash get_type() const", AS_METHODPR(AnimationSet2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "const String& GetTypeName() const", AS_METHODPR(AnimationSet2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "const String& get_typeName() const", AS_METHODPR(AnimationSet2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "uint GetUseTimer()", AS_METHODPR(AnimationSet2D, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "uint get_useTimer()", AS_METHODPR(AnimationSet2D, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // bool AnimationSet2D::HasAnimation(const String& animationName) const | File: ../Urho2D/AnimationSet2D.h
    engine->RegisterObjectMethod("AnimationSet2D", "bool HasAnimation(const String&in) const", AS_METHODPR(AnimationSet2D, HasAnimation, (const String&) const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "bool HasEventHandlers() const", AS_METHODPR(AnimationSet2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(AnimationSet2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(AnimationSet2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(AnimationSet2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "bool Load(Deserializer&)", AS_METHODPR(AnimationSet2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "bool LoadFile(const String&in)", AS_METHODPR(AnimationSet2D, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "bool Load(const String&in)", AS_METHODPR(AnimationSet2D, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(AnimationSet2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AnimationSet2D", "int Refs() const", AS_METHODPR(AnimationSet2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "int get_refs() const", AS_METHODPR(AnimationSet2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void AnimationSet2D::RegisterObject(Context* context) | File: ../Urho2D/AnimationSet2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("AnimationSet2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(AnimationSet2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "void ResetUseTimer()", AS_METHODPR(AnimationSet2D, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "bool Save(Serializer&) const", AS_METHODPR(AnimationSet2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "bool SaveFile(const String&in) const", AS_METHODPR(AnimationSet2D, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "bool Save(const String&in) const", AS_METHODPR(AnimationSet2D, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "void SendEvent(StringHash)", AS_METHODPR(AnimationSet2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(AnimationSet2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(AnimationSet2D, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "void SetBlockEvents(bool)", AS_METHODPR(AnimationSet2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(AnimationSet2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(AnimationSet2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "void SetMemoryUse(uint)", AS_METHODPR(AnimationSet2D, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "void SetName(const String&in)", AS_METHODPR(AnimationSet2D, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "void set_name(const String&in)", AS_METHODPR(AnimationSet2D, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(AnimationSet2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(AnimationSet2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(AnimationSet2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(AnimationSet2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(AnimationSet2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AnimationSet2D", "int WeakRefs() const", AS_METHODPR(AnimationSet2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "int get_weakRefs() const", AS_METHODPR(AnimationSet2D, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(AnimationSet2D, "AnimationSet2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(AnimationSet2D, "AnimationSet2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(AnimationSet2D, "AnimationSet2D")
#endif
#ifdef REGISTER_MANUAL_PART_AnimationSet2D
    REGISTER_MANUAL_PART_AnimationSet2D(AnimationSet2D, "AnimationSet2D")
#endif
    RegisterSubclass<Resource, AnimationSet2D>(engine, "Resource", "AnimationSet2D");
    RegisterSubclass<Object, AnimationSet2D>(engine, "Object", "AnimationSet2D");
    RegisterSubclass<RefCounted, AnimationSet2D>(engine, "RefCounted", "AnimationSet2D");
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("AnimationState", asBEHAVE_ADDREF, "void f()", AS_METHODPR(AnimationState, AddRef, (), void), AS_CALL_THISCALL);
    // void AnimationState::AddTime(float delta) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "void AddTime(float)", AS_METHODPR(AnimationState, AddTime, (float), void), AS_CALL_THISCALL);
    // void AnimationState::AddWeight(float delta) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "void AddWeight(float)", AS_METHODPR(AnimationState, AddWeight, (float), void), AS_CALL_THISCALL);
    // AnimationState::AnimationState(AnimatedModel* model, Animation* animation) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectBehaviour("AnimationState", asBEHAVE_FACTORY, "AnimationState@+ f(AnimatedModel@+, Animation@+)", AS_FUNCTION(AnimationState_AnimationState_AnimatedModel_Animation), AS_CALL_CDECL);
    // AnimationState::AnimationState(Node* node, Animation* animation) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectBehaviour("AnimationState", asBEHAVE_FACTORY, "AnimationState@+ f(Node@+, Animation@+)", AS_FUNCTION(AnimationState_AnimationState_Node_Animation), AS_CALL_CDECL);
    // void AnimationState::Apply() | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "void Apply()", AS_METHODPR(AnimationState, Apply, (), void), AS_CALL_THISCALL);
    // Animation* AnimationState::GetAnimation() const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "Animation@+ GetAnimation() const", AS_METHODPR(AnimationState, GetAnimation, () const, Animation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "Animation@+ get_animation() const", AS_METHODPR(AnimationState, GetAnimation, () const, Animation*), AS_CALL_THISCALL);
    // AnimationBlendMode AnimationState::GetBlendMode() const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "AnimationBlendMode GetBlendMode() const", AS_METHODPR(AnimationState, GetBlendMode, () const, AnimationBlendMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "AnimationBlendMode get_blendMode() const", AS_METHODPR(AnimationState, GetBlendMode, () const, AnimationBlendMode), AS_CALL_THISCALL);
    // float AnimationState::GetBoneWeight(unsigned index) const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "float GetBoneWeight(uint) const", AS_METHODPR(AnimationState, GetBoneWeight, (unsigned) const, float), AS_CALL_THISCALL);
    // float AnimationState::GetBoneWeight(const String& name) const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "float GetBoneWeight(const String&in) const", AS_METHODPR(AnimationState, GetBoneWeight, (const String&) const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "float get_boneWeights(const String&in) const", AS_METHODPR(AnimationState, GetBoneWeight, (const String&) const, float), AS_CALL_THISCALL);
    // float AnimationState::GetBoneWeight(StringHash nameHash) const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "float GetBoneWeight(StringHash) const", AS_METHODPR(AnimationState, GetBoneWeight, (StringHash) const, float), AS_CALL_THISCALL);
    // unsigned char AnimationState::GetLayer() const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "uint8 GetLayer() const", AS_METHODPR(AnimationState, GetLayer, () const, unsigned char), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "uint8 get_layer() const", AS_METHODPR(AnimationState, GetLayer, () const, unsigned char), AS_CALL_THISCALL);
    // float AnimationState::GetLength() const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "float GetLength() const", AS_METHODPR(AnimationState, GetLength, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "float get_length() const", AS_METHODPR(AnimationState, GetLength, () const, float), AS_CALL_THISCALL);
    // AnimatedModel* AnimationState::GetModel() const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "AnimatedModel@+ GetModel() const", AS_METHODPR(AnimationState, GetModel, () const, AnimatedModel*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "AnimatedModel@+ get_model() const", AS_METHODPR(AnimationState, GetModel, () const, AnimatedModel*), AS_CALL_THISCALL);
    // Node* AnimationState::GetNode() const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "Node@+ GetNode() const", AS_METHODPR(AnimationState, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "Node@+ get_node() const", AS_METHODPR(AnimationState, GetNode, () const, Node*), AS_CALL_THISCALL);
    // Bone* AnimationState::GetStartBone() const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "Bone@+ GetStartBone() const", AS_METHODPR(AnimationState, GetStartBone, () const, Bone*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "Bone@+ get_startBone() const", AS_METHODPR(AnimationState, GetStartBone, () const, Bone*), AS_CALL_THISCALL);
    // float AnimationState::GetTime() const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "float GetTime() const", AS_METHODPR(AnimationState, GetTime, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "float get_time() const", AS_METHODPR(AnimationState, GetTime, () const, float), AS_CALL_THISCALL);
    // unsigned AnimationState::GetTrackIndex(Node* node) const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "uint GetTrackIndex(Node@+) const", AS_METHODPR(AnimationState, GetTrackIndex, (Node*) const, unsigned), AS_CALL_THISCALL);
    // unsigned AnimationState::GetTrackIndex(const String& name) const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "uint GetTrackIndex(const String&in) const", AS_METHODPR(AnimationState, GetTrackIndex, (const String&) const, unsigned), AS_CALL_THISCALL);
    // unsigned AnimationState::GetTrackIndex(StringHash nameHash) const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "uint GetTrackIndex(StringHash) const", AS_METHODPR(AnimationState, GetTrackIndex, (StringHash) const, unsigned), AS_CALL_THISCALL);
    // float AnimationState::GetWeight() const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "float GetWeight() const", AS_METHODPR(AnimationState, GetWeight, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "float get_weight() const", AS_METHODPR(AnimationState, GetWeight, () const, float), AS_CALL_THISCALL);
    // bool AnimationState::IsEnabled() const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "bool IsEnabled() const", AS_METHODPR(AnimationState, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "bool get_enabled() const", AS_METHODPR(AnimationState, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool AnimationState::IsLooped() const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "bool IsLooped() const", AS_METHODPR(AnimationState, IsLooped, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "bool get_looped() const", AS_METHODPR(AnimationState, IsLooped, () const, bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AnimationState", "int Refs() const", AS_METHODPR(AnimationState, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "int get_refs() const", AS_METHODPR(AnimationState, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("AnimationState", asBEHAVE_RELEASE, "void f()", AS_METHODPR(AnimationState, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void AnimationState::SetBlendMode(AnimationBlendMode mode) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "void SetBlendMode(AnimationBlendMode)", AS_METHODPR(AnimationState, SetBlendMode, (AnimationBlendMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void set_blendMode(AnimationBlendMode)", AS_METHODPR(AnimationState, SetBlendMode, (AnimationBlendMode), void), AS_CALL_THISCALL);
    // void AnimationState::SetBoneWeight(unsigned index, float weight, bool recursive=false) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "void SetBoneWeight(uint, float, bool = false)", AS_METHODPR(AnimationState, SetBoneWeight, (unsigned, float, bool), void), AS_CALL_THISCALL);
    // void AnimationState::SetBoneWeight(const String& name, float weight, bool recursive=false) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "void SetBoneWeight(const String&in, float, bool = false)", AS_METHODPR(AnimationState, SetBoneWeight, (const String&, float, bool), void), AS_CALL_THISCALL);
    // void AnimationState::SetBoneWeight(StringHash nameHash, float weight, bool recursive=false) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "void SetBoneWeight(StringHash, float, bool = false)", AS_METHODPR(AnimationState, SetBoneWeight, (StringHash, float, bool), void), AS_CALL_THISCALL);
    // void AnimationState::SetLayer(unsigned char layer) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "void SetLayer(uint8)", AS_METHODPR(AnimationState, SetLayer, (unsigned char), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void set_layer(uint8)", AS_METHODPR(AnimationState, SetLayer, (unsigned char), void), AS_CALL_THISCALL);
    // void AnimationState::SetLooped(bool looped) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "void SetLooped(bool)", AS_METHODPR(AnimationState, SetLooped, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void set_looped(bool)", AS_METHODPR(AnimationState, SetLooped, (bool), void), AS_CALL_THISCALL);
    // void AnimationState::SetStartBone(Bone* startBone) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "void SetStartBone(Bone@+)", AS_METHODPR(AnimationState, SetStartBone, (Bone*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void set_startBone(Bone@+)", AS_METHODPR(AnimationState, SetStartBone, (Bone*), void), AS_CALL_THISCALL);
    // void AnimationState::SetTime(float time) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "void SetTime(float)", AS_METHODPR(AnimationState, SetTime, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void set_time(float)", AS_METHODPR(AnimationState, SetTime, (float), void), AS_CALL_THISCALL);
    // void AnimationState::SetWeight(float weight) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "void SetWeight(float)", AS_METHODPR(AnimationState, SetWeight, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void set_weight(float)", AS_METHODPR(AnimationState, SetWeight, (float), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AnimationState", "int WeakRefs() const", AS_METHODPR(AnimationState, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "int get_weakRefs() const", AS_METHODPR(AnimationState, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(AnimationState, "AnimationState")
#endif
#ifdef REGISTER_MANUAL_PART_AnimationState
    REGISTER_MANUAL_PART_AnimationState(AnimationState, "AnimationState")
#endif
    RegisterSubclass<RefCounted, AnimationState>(engine, "RefCounted", "AnimationState");

    // bool AreaAllocator::Allocate(int width, int height, int& x, int& y) | File: ../Math/AreaAllocator.h
    engine->RegisterObjectMethod("AreaAllocator", "bool Allocate(int, int, int&, int&)", AS_METHODPR(AreaAllocator, Allocate, (int, int, int&, int&), bool), AS_CALL_THISCALL);
    // AreaAllocator::AreaAllocator(int width, int height, bool fastMode=true) | File: ../Math/AreaAllocator.h
    engine->RegisterObjectBehaviour("AreaAllocator", asBEHAVE_CONSTRUCT, "void f(int, int, bool = true)", AS_FUNCTION_OBJFIRST(AreaAllocator_AreaAllocator_int_int_bool), AS_CALL_CDECL_OBJFIRST);
    // AreaAllocator::AreaAllocator(int width, int height, int maxWidth, int maxHeight, bool fastMode=true) | File: ../Math/AreaAllocator.h
    engine->RegisterObjectBehaviour("AreaAllocator", asBEHAVE_CONSTRUCT, "void f(int, int, int, int, bool = true)", AS_FUNCTION_OBJFIRST(AreaAllocator_AreaAllocator_int_int_int_int_bool), AS_CALL_CDECL_OBJFIRST);
    // bool AreaAllocator::GetFastMode() const | File: ../Math/AreaAllocator.h
    engine->RegisterObjectMethod("AreaAllocator", "bool GetFastMode() const", AS_METHODPR(AreaAllocator, GetFastMode, () const, bool), AS_CALL_THISCALL);
    // int AreaAllocator::GetHeight() const | File: ../Math/AreaAllocator.h
    engine->RegisterObjectMethod("AreaAllocator", "int GetHeight() const", AS_METHODPR(AreaAllocator, GetHeight, () const, int), AS_CALL_THISCALL);
    // int AreaAllocator::GetWidth() const | File: ../Math/AreaAllocator.h
    engine->RegisterObjectMethod("AreaAllocator", "int GetWidth() const", AS_METHODPR(AreaAllocator, GetWidth, () const, int), AS_CALL_THISCALL);
    // void AreaAllocator::Reset(int width, int height, int maxWidth=0, int maxHeight=0, bool fastMode=true) | File: ../Math/AreaAllocator.h
    engine->RegisterObjectMethod("AreaAllocator", "void Reset(int, int, int = 0, int = 0, bool = true)", AS_METHODPR(AreaAllocator, Reset, (int, int, int, int, bool), void), AS_CALL_THISCALL);
    // AreaAllocator& AreaAllocator::operator=(const AreaAllocator&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AreaAllocator>(engine, "AreaAllocator");
#ifdef REGISTER_MANUAL_PART_AreaAllocator
    REGISTER_MANUAL_PART_AreaAllocator(AreaAllocator, "AreaAllocator")
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("AttributeAccessor", asBEHAVE_ADDREF, "void f()", AS_METHODPR(AttributeAccessor, AddRef, (), void), AS_CALL_THISCALL);
    // virtual void AttributeAccessor::Get(const Serializable* ptr, Variant& dest) const =0 | File: ../Core/Attribute.h
    engine->RegisterObjectMethod("AttributeAccessor", "void Get(Serializable@+, Variant&) const", AS_METHODPR(AttributeAccessor, Get, (const Serializable*, Variant&) const, void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AttributeAccessor", "int Refs() const", AS_METHODPR(AttributeAccessor, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AttributeAccessor", "int get_refs() const", AS_METHODPR(AttributeAccessor, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("AttributeAccessor", asBEHAVE_RELEASE, "void f()", AS_METHODPR(AttributeAccessor, ReleaseRef, (), void), AS_CALL_THISCALL);
    // virtual void AttributeAccessor::Set(Serializable* ptr, const Variant& src)=0 | File: ../Core/Attribute.h
    engine->RegisterObjectMethod("AttributeAccessor", "void Set(Serializable@+, const Variant&in)", AS_METHODPR(AttributeAccessor, Set, (Serializable*, const Variant&), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AttributeAccessor", "int WeakRefs() const", AS_METHODPR(AttributeAccessor, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AttributeAccessor", "int get_weakRefs() const", AS_METHODPR(AttributeAccessor, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(AttributeAccessor, "AttributeAccessor")
#endif
#ifdef REGISTER_MANUAL_PART_AttributeAccessor
    REGISTER_MANUAL_PART_AttributeAccessor(AttributeAccessor, "AttributeAccessor")
#endif
    RegisterSubclass<RefCounted, AttributeAccessor>(engine, "RefCounted", "AttributeAccessor");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("AttributeAnimationInfo", asBEHAVE_ADDREF, "void f()", AS_METHODPR(AttributeAnimationInfo, AddRef, (), void), AS_CALL_THISCALL);
    // AttributeAnimationInfo::AttributeAnimationInfo(Animatable* animatable, const AttributeInfo& attributeInfo, ValueAnimation* attributeAnimation, WrapMode wrapMode, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectBehaviour("AttributeAnimationInfo", asBEHAVE_FACTORY, "AttributeAnimationInfo@+ f(Animatable@+, const AttributeInfo&in, ValueAnimation@+, WrapMode, float)", AS_FUNCTION(AttributeAnimationInfo_AttributeAnimationInfo_Animatable_AttributeInfo_ValueAnimation_WrapMode_float), AS_CALL_CDECL);
    // AttributeAnimationInfo::AttributeAnimationInfo(const AttributeAnimationInfo& other) | File: ../Scene/Animatable.h
    engine->RegisterObjectBehaviour("AttributeAnimationInfo", asBEHAVE_FACTORY, "AttributeAnimationInfo@+ f(const AttributeAnimationInfo&in)", AS_FUNCTION(AttributeAnimationInfo_AttributeAnimationInfo_AttributeAnimationInfo), AS_CALL_CDECL);
    // ValueAnimation* ValueAnimationInfo::GetAnimation() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("AttributeAnimationInfo", "ValueAnimation@+ GetAnimation() const", AS_METHODPR(AttributeAnimationInfo, GetAnimation, () const, ValueAnimation*), AS_CALL_THISCALL);
    // const AttributeInfo& AttributeAnimationInfo::GetAttributeInfo() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AttributeAnimationInfo", "const AttributeInfo& GetAttributeInfo() const", AS_METHODPR(AttributeAnimationInfo, GetAttributeInfo, () const, const AttributeInfo&), AS_CALL_THISCALL);
    // float ValueAnimationInfo::GetSpeed() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("AttributeAnimationInfo", "float GetSpeed() const", AS_METHODPR(AttributeAnimationInfo, GetSpeed, () const, float), AS_CALL_THISCALL);
    // Object* ValueAnimationInfo::GetTarget() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("AttributeAnimationInfo", "Object@+ GetTarget() const", AS_METHODPR(AttributeAnimationInfo, GetTarget, () const, Object*), AS_CALL_THISCALL);
    // float ValueAnimationInfo::GetTime() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("AttributeAnimationInfo", "float GetTime() const", AS_METHODPR(AttributeAnimationInfo, GetTime, () const, float), AS_CALL_THISCALL);
    // WrapMode ValueAnimationInfo::GetWrapMode() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("AttributeAnimationInfo", "WrapMode GetWrapMode() const", AS_METHODPR(AttributeAnimationInfo, GetWrapMode, () const, WrapMode), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AttributeAnimationInfo", "int Refs() const", AS_METHODPR(AttributeAnimationInfo, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AttributeAnimationInfo", "int get_refs() const", AS_METHODPR(AttributeAnimationInfo, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("AttributeAnimationInfo", asBEHAVE_RELEASE, "void f()", AS_METHODPR(AttributeAnimationInfo, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void ValueAnimationInfo::SetSpeed(float speed) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("AttributeAnimationInfo", "void SetSpeed(float)", AS_METHODPR(AttributeAnimationInfo, SetSpeed, (float), void), AS_CALL_THISCALL);
    // bool ValueAnimationInfo::SetTime(float time) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("AttributeAnimationInfo", "bool SetTime(float)", AS_METHODPR(AttributeAnimationInfo, SetTime, (float), bool), AS_CALL_THISCALL);
    // void ValueAnimationInfo::SetWrapMode(WrapMode wrapMode) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("AttributeAnimationInfo", "void SetWrapMode(WrapMode)", AS_METHODPR(AttributeAnimationInfo, SetWrapMode, (WrapMode), void), AS_CALL_THISCALL);
    // bool ValueAnimationInfo::Update(float timeStep) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("AttributeAnimationInfo", "bool Update(float)", AS_METHODPR(AttributeAnimationInfo, Update, (float), bool), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AttributeAnimationInfo", "int WeakRefs() const", AS_METHODPR(AttributeAnimationInfo, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AttributeAnimationInfo", "int get_weakRefs() const", AS_METHODPR(AttributeAnimationInfo, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_ValueAnimationInfo
    REGISTER_MANUAL_PART_ValueAnimationInfo(AttributeAnimationInfo, "AttributeAnimationInfo")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(AttributeAnimationInfo, "AttributeAnimationInfo")
#endif
#ifdef REGISTER_MANUAL_PART_AttributeAnimationInfo
    REGISTER_MANUAL_PART_AttributeAnimationInfo(AttributeAnimationInfo, "AttributeAnimationInfo")
#endif
    RegisterSubclass<ValueAnimationInfo, AttributeAnimationInfo>(engine, "ValueAnimationInfo", "AttributeAnimationInfo");
    RegisterSubclass<RefCounted, AttributeAnimationInfo>(engine, "RefCounted", "AttributeAnimationInfo");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Audio", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Audio, AddRef, (), void), AS_CALL_THISCALL);
    // void Audio::AddSoundSource(SoundSource* soundSource) | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "void AddSoundSource(SoundSource@+)", AS_METHODPR(Audio, AddSoundSource, (SoundSource*), void), AS_CALL_THISCALL);
    // explicit Audio::Audio(Context* context) | File: ../Audio/Audio.h
    engine->RegisterObjectBehaviour("Audio", asBEHAVE_FACTORY, "Audio@+ f()", AS_FUNCTION(Audio_Audio_Context), AS_CALL_CDECL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "bool GetBlockEvents() const", AS_METHODPR(Audio, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "const String& GetCategory() const", AS_METHODPR(Audio, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "const String& get_category() const", AS_METHODPR(Audio, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "VariantMap& GetEventDataMap() const", AS_METHODPR(Audio, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "Object@+ GetEventSender() const", AS_METHODPR(Audio, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Audio, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Audio, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Audio, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "const VariantMap& get_globalVars() const", AS_METHODPR(Audio, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // bool Audio::GetInterpolation() const | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "bool GetInterpolation() const", AS_METHODPR(Audio, GetInterpolation, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "bool get_interpolation() const", AS_METHODPR(Audio, GetInterpolation, () const, bool), AS_CALL_THISCALL);
    // SoundListener* Audio::GetListener() const | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "SoundListener@+ GetListener() const", AS_METHODPR(Audio, GetListener, () const, SoundListener*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "SoundListener@+ get_listener() const", AS_METHODPR(Audio, GetListener, () const, SoundListener*), AS_CALL_THISCALL);
    // float Audio::GetMasterGain(const String& type) const | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "float GetMasterGain(const String&in) const", AS_METHODPR(Audio, GetMasterGain, (const String&) const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "float get_masterGain(const String&in) const", AS_METHODPR(Audio, GetMasterGain, (const String&) const, float), AS_CALL_THISCALL);
    // int Audio::GetMixRate() const | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "int GetMixRate() const", AS_METHODPR(Audio, GetMixRate, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "int get_mixRate() const", AS_METHODPR(Audio, GetMixRate, () const, int), AS_CALL_THISCALL);
    // Mutex& Audio::GetMutex() | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "Mutex& GetMutex()", AS_METHODPR(Audio, GetMutex, (), Mutex&), AS_CALL_THISCALL);
    // unsigned Audio::GetSampleSize() const | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "uint GetSampleSize() const", AS_METHODPR(Audio, GetSampleSize, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "uint get_sampleSize() const", AS_METHODPR(Audio, GetSampleSize, () const, unsigned), AS_CALL_THISCALL);
    // float Audio::GetSoundSourceMasterGain(StringHash typeHash) const | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "float GetSoundSourceMasterGain(StringHash) const", AS_METHODPR(Audio, GetSoundSourceMasterGain, (StringHash) const, float), AS_CALL_THISCALL);
    // const PODVector<SoundSource*>& Audio::GetSoundSources() const | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "Array<SoundSource@>@ GetSoundSources() const", AS_FUNCTION_OBJFIRST(Audio_GetSoundSources_void), AS_CALL_CDECL_OBJFIRST);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Audio, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "StringHash GetType() const", AS_METHODPR(Audio, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "StringHash get_type() const", AS_METHODPR(Audio, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "const String& GetTypeName() const", AS_METHODPR(Audio, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "const String& get_typeName() const", AS_METHODPR(Audio, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "bool HasEventHandlers() const", AS_METHODPR(Audio, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Audio::HasMasterGain(const String& type) const | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "bool HasMasterGain(const String&in) const", AS_METHODPR(Audio, HasMasterGain, (const String&) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Audio, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Audio, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Audio::IsInitialized() const | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "bool IsInitialized() const", AS_METHODPR(Audio, IsInitialized, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "bool get_initialized() const", AS_METHODPR(Audio, IsInitialized, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Audio, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Audio::IsPlaying() const | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "bool IsPlaying() const", AS_METHODPR(Audio, IsPlaying, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "bool get_playing() const", AS_METHODPR(Audio, IsPlaying, () const, bool), AS_CALL_THISCALL);
    // bool Audio::IsSoundTypePaused(const String& type) const | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "bool IsSoundTypePaused(const String&in) const", AS_METHODPR(Audio, IsSoundTypePaused, (const String&) const, bool), AS_CALL_THISCALL);
    // bool Audio::IsStereo() const | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "bool IsStereo() const", AS_METHODPR(Audio, IsStereo, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "bool get_stereo() const", AS_METHODPR(Audio, IsStereo, () const, bool), AS_CALL_THISCALL);
    // void Audio::MixOutput(void* dest, unsigned samples) | File: ../Audio/Audio.h
    // Error: type "void*" can not automatically bind
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Audio, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // void Audio::PauseSoundType(const String& type) | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "void PauseSoundType(const String&in)", AS_METHODPR(Audio, PauseSoundType, (const String&), void), AS_CALL_THISCALL);
    // bool Audio::Play() | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "bool Play()", AS_METHODPR(Audio, Play, (), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Audio", "int Refs() const", AS_METHODPR(Audio, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "int get_refs() const", AS_METHODPR(Audio, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Audio", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Audio, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Audio::RemoveSoundSource(SoundSource* soundSource) | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "void RemoveSoundSource(SoundSource@+)", AS_METHODPR(Audio, RemoveSoundSource, (SoundSource*), void), AS_CALL_THISCALL);
    // void Audio::ResumeAll() | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "void ResumeAll()", AS_METHODPR(Audio, ResumeAll, (), void), AS_CALL_THISCALL);
    // void Audio::ResumeSoundType(const String& type) | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "void ResumeSoundType(const String&in)", AS_METHODPR(Audio, ResumeSoundType, (const String&), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "void SendEvent(StringHash)", AS_METHODPR(Audio, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Audio, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "void SetBlockEvents(bool)", AS_METHODPR(Audio, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Audio, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Audio, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Audio::SetListener(SoundListener* listener) | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "void SetListener(SoundListener@+)", AS_METHODPR(Audio, SetListener, (SoundListener*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "void set_listener(SoundListener@+)", AS_METHODPR(Audio, SetListener, (SoundListener*), void), AS_CALL_THISCALL);
    // void Audio::SetMasterGain(const String& type, float gain) | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "void SetMasterGain(const String&in, float)", AS_METHODPR(Audio, SetMasterGain, (const String&, float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "void set_masterGain(const String&in, float)", AS_METHODPR(Audio, SetMasterGain, (const String&, float), void), AS_CALL_THISCALL);
    // bool Audio::SetMode(int bufferLengthMSec, int mixRate, bool stereo, bool interpolation=true) | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "bool SetMode(int, int, bool, bool = true)", AS_METHODPR(Audio, SetMode, (int, int, bool, bool), bool), AS_CALL_THISCALL);
    // void Audio::Stop() | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "void Stop()", AS_METHODPR(Audio, Stop, (), void), AS_CALL_THISCALL);
    // void Audio::StopSound(Sound* sound) | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "void StopSound(Sound@+)", AS_METHODPR(Audio, StopSound, (Sound*), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "void UnsubscribeFromAllEvents()", AS_METHODPR(Audio, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Audio_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Audio, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Audio, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Audio, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void Audio::Update(float timeStep) | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "void Update(float)", AS_METHODPR(Audio, Update, (float), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Audio", "int WeakRefs() const", AS_METHODPR(Audio, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "int get_weakRefs() const", AS_METHODPR(Audio, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Audio, "Audio")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Audio, "Audio")
#endif
#ifdef REGISTER_MANUAL_PART_Audio
    REGISTER_MANUAL_PART_Audio(Audio, "Audio")
#endif
    RegisterSubclass<Object, Audio>(engine, "Object", "Audio");
    RegisterSubclass<RefCounted, Audio>(engine, "RefCounted", "Audio");

    // unsigned AllocatorBlock::capacity_ | File: ../Container/Allocator.h
    engine->RegisterObjectProperty("AllocatorBlock", "uint capacity", offsetof(AllocatorBlock, capacity_));
    // AllocatorNode* AllocatorBlock::free_ | File: ../Container/Allocator.h
    // AllocatorNode* can not be registered
    // AllocatorBlock* AllocatorBlock::next_ | File: ../Container/Allocator.h
    // AllocatorBlock* can not be registered
    // unsigned AllocatorBlock::nodeSize_ | File: ../Container/Allocator.h
    engine->RegisterObjectProperty("AllocatorBlock", "uint nodeSize", offsetof(AllocatorBlock, nodeSize_));
    // AllocatorBlock& AllocatorBlock::operator=(const AllocatorBlock&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AllocatorBlock>(engine, "AllocatorBlock");
#ifdef REGISTER_MANUAL_PART_AllocatorBlock
    REGISTER_MANUAL_PART_AllocatorBlock(AllocatorBlock, "AllocatorBlock")
#endif

    // AllocatorNode* AllocatorNode::next_ | File: ../Container/Allocator.h
    // AllocatorNode* can not be registered
    // AllocatorNode& AllocatorNode::operator=(const AllocatorNode&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AllocatorNode>(engine, "AllocatorNode");
#ifdef REGISTER_MANUAL_PART_AllocatorNode
    REGISTER_MANUAL_PART_AllocatorNode(AllocatorNode, "AllocatorNode")
#endif

    // float AnimationControl::autoFadeTime_ | File: ../Graphics/AnimationController.h
    engine->RegisterObjectProperty("AnimationControl", "float autoFadeTime", offsetof(AnimationControl, autoFadeTime_));
    // float AnimationControl::fadeTime_ | File: ../Graphics/AnimationController.h
    engine->RegisterObjectProperty("AnimationControl", "float fadeTime", offsetof(AnimationControl, fadeTime_));
    // StringHash AnimationControl::hash_ | File: ../Graphics/AnimationController.h
    engine->RegisterObjectProperty("AnimationControl", "StringHash hash", offsetof(AnimationControl, hash_));
    // String AnimationControl::name_ | File: ../Graphics/AnimationController.h
    engine->RegisterObjectProperty("AnimationControl", "String name", offsetof(AnimationControl, name_));
    // bool AnimationControl::removeOnCompletion_ | File: ../Graphics/AnimationController.h
    engine->RegisterObjectProperty("AnimationControl", "bool removeOnCompletion", offsetof(AnimationControl, removeOnCompletion_));
    // unsigned short AnimationControl::setTime_ | File: ../Graphics/AnimationController.h
    engine->RegisterObjectProperty("AnimationControl", "uint16 setTime", offsetof(AnimationControl, setTime_));
    // unsigned char AnimationControl::setTimeRev_ | File: ../Graphics/AnimationController.h
    engine->RegisterObjectProperty("AnimationControl", "uint8 setTimeRev", offsetof(AnimationControl, setTimeRev_));
    // float AnimationControl::setTimeTtl_ | File: ../Graphics/AnimationController.h
    engine->RegisterObjectProperty("AnimationControl", "float setTimeTtl", offsetof(AnimationControl, setTimeTtl_));
    // unsigned char AnimationControl::setWeight_ | File: ../Graphics/AnimationController.h
    engine->RegisterObjectProperty("AnimationControl", "uint8 setWeight", offsetof(AnimationControl, setWeight_));
    // unsigned char AnimationControl::setWeightRev_ | File: ../Graphics/AnimationController.h
    engine->RegisterObjectProperty("AnimationControl", "uint8 setWeightRev", offsetof(AnimationControl, setWeightRev_));
    // float AnimationControl::setWeightTtl_ | File: ../Graphics/AnimationController.h
    engine->RegisterObjectProperty("AnimationControl", "float setWeightTtl", offsetof(AnimationControl, setWeightTtl_));
    // float AnimationControl::speed_ | File: ../Graphics/AnimationController.h
    engine->RegisterObjectProperty("AnimationControl", "float speed", offsetof(AnimationControl, speed_));
    // float AnimationControl::targetWeight_ | File: ../Graphics/AnimationController.h
    engine->RegisterObjectProperty("AnimationControl", "float targetWeight", offsetof(AnimationControl, targetWeight_));
    // AnimationControl::AnimationControl() | File: ../Graphics/AnimationController.h
    engine->RegisterObjectBehaviour("AnimationControl", asBEHAVE_FACTORY, "AnimationControl@+ f()", AS_FUNCTION(AnimationControl_AnimationControl_void), AS_CALL_CDECL);
    // AnimationControl& AnimationControl::operator=(const AnimationControl&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AnimationControl>(engine, "AnimationControl");
    engine->RegisterObjectBehaviour("AnimationControl", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("AnimationControl", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);
#ifdef REGISTER_MANUAL_PART_AnimationControl
    REGISTER_MANUAL_PART_AnimationControl(AnimationControl, "AnimationControl")
#endif

    // Vector3 AnimationKeyFrame::position_ | File: ../Graphics/Animation.h
    engine->RegisterObjectProperty("AnimationKeyFrame", "Vector3 position", offsetof(AnimationKeyFrame, position_));
    // Quaternion AnimationKeyFrame::rotation_ | File: ../Graphics/Animation.h
    engine->RegisterObjectProperty("AnimationKeyFrame", "Quaternion rotation", offsetof(AnimationKeyFrame, rotation_));
    // Vector3 AnimationKeyFrame::scale_ | File: ../Graphics/Animation.h
    engine->RegisterObjectProperty("AnimationKeyFrame", "Vector3 scale", offsetof(AnimationKeyFrame, scale_));
    // float AnimationKeyFrame::time_ | File: ../Graphics/Animation.h
    engine->RegisterObjectProperty("AnimationKeyFrame", "float time", offsetof(AnimationKeyFrame, time_));
    // AnimationKeyFrame& AnimationKeyFrame::operator=(const AnimationKeyFrame&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AnimationKeyFrame>(engine, "AnimationKeyFrame");
#ifdef REGISTER_MANUAL_PART_AnimationKeyFrame
    REGISTER_MANUAL_PART_AnimationKeyFrame(AnimationKeyFrame, "AnimationKeyFrame")
#endif

    // Bone* AnimationStateTrack::bone_ | File: ../Graphics/AnimationState.h
    // Bone* can not be registered
    // unsigned AnimationStateTrack::keyFrame_ | File: ../Graphics/AnimationState.h
    engine->RegisterObjectProperty("AnimationStateTrack", "uint keyFrame", offsetof(AnimationStateTrack, keyFrame_));
    // WeakPtr<Node> AnimationStateTrack::node_ | File: ../Graphics/AnimationState.h
    // Error: type "WeakPtr<Node>" can not automatically bind
    // const AnimationTrack* AnimationStateTrack::track_ | File: ../Graphics/AnimationState.h
    // const AnimationTrack* can not be registered
    // float AnimationStateTrack::weight_ | File: ../Graphics/AnimationState.h
    engine->RegisterObjectProperty("AnimationStateTrack", "float weight", offsetof(AnimationStateTrack, weight_));
    // AnimationStateTrack& AnimationStateTrack::operator=(const AnimationStateTrack&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AnimationStateTrack>(engine, "AnimationStateTrack");
#ifdef REGISTER_MANUAL_PART_AnimationStateTrack
    REGISTER_MANUAL_PART_AnimationStateTrack(AnimationStateTrack, "AnimationStateTrack")
#endif

    // AnimationChannelFlags AnimationTrack::channelMask_ | File: ../Graphics/Animation.h
    engine->RegisterObjectProperty("AnimationTrack", "AnimationChannelFlags channelMask", offsetof(AnimationTrack, channelMask_));
    // Vector<AnimationKeyFrame> AnimationTrack::keyFrames_ | File: ../Graphics/Animation.h
    // Error: type "Vector<AnimationKeyFrame>" can not automatically bind
    // String AnimationTrack::name_ | File: ../Graphics/Animation.h
    engine->RegisterObjectProperty("AnimationTrack", "String name", offsetof(AnimationTrack, name_));
    // StringHash AnimationTrack::nameHash_ | File: ../Graphics/Animation.h
    engine->RegisterObjectProperty("AnimationTrack", "StringHash nameHash", offsetof(AnimationTrack, nameHash_));
    // void AnimationTrack::AddKeyFrame(const AnimationKeyFrame& keyFrame) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("AnimationTrack", "void AddKeyFrame(const AnimationKeyFrame&in)", AS_METHODPR(AnimationTrack, AddKeyFrame, (const AnimationKeyFrame&), void), AS_CALL_THISCALL);
    // AnimationTrack::AnimationTrack() | File: ../Graphics/Animation.h
    engine->RegisterObjectBehaviour("AnimationTrack", asBEHAVE_FACTORY, "AnimationTrack@+ f()", AS_FUNCTION(AnimationTrack_AnimationTrack_void), AS_CALL_CDECL);
    // AnimationKeyFrame* AnimationTrack::GetKeyFrame(unsigned index) | File: ../Graphics/Animation.h
    // Error: type "AnimationKeyFrame*" can not automatically bind
    // bool AnimationTrack::GetKeyFrameIndex(float time, unsigned& index) const | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("AnimationTrack", "bool GetKeyFrameIndex(float, uint&) const", AS_METHODPR(AnimationTrack, GetKeyFrameIndex, (float, unsigned&) const, bool), AS_CALL_THISCALL);
    // unsigned AnimationTrack::GetNumKeyFrames() const | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("AnimationTrack", "uint GetNumKeyFrames() const", AS_METHODPR(AnimationTrack, GetNumKeyFrames, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationTrack", "uint get_numKeyFrames() const", AS_METHODPR(AnimationTrack, GetNumKeyFrames, () const, unsigned), AS_CALL_THISCALL);
    // void AnimationTrack::InsertKeyFrame(unsigned index, const AnimationKeyFrame& keyFrame) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("AnimationTrack", "void InsertKeyFrame(uint, const AnimationKeyFrame&in)", AS_METHODPR(AnimationTrack, InsertKeyFrame, (unsigned, const AnimationKeyFrame&), void), AS_CALL_THISCALL);
    // void AnimationTrack::RemoveAllKeyFrames() | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("AnimationTrack", "void RemoveAllKeyFrames()", AS_METHODPR(AnimationTrack, RemoveAllKeyFrames, (), void), AS_CALL_THISCALL);
    // void AnimationTrack::RemoveKeyFrame(unsigned index) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("AnimationTrack", "void RemoveKeyFrame(uint)", AS_METHODPR(AnimationTrack, RemoveKeyFrame, (unsigned), void), AS_CALL_THISCALL);
    // void AnimationTrack::SetKeyFrame(unsigned index, const AnimationKeyFrame& keyFrame) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("AnimationTrack", "void SetKeyFrame(uint, const AnimationKeyFrame&in)", AS_METHODPR(AnimationTrack, SetKeyFrame, (unsigned, const AnimationKeyFrame&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("AnimationTrack", "void set_keyFrames(uint, const AnimationKeyFrame&in)", AS_METHODPR(AnimationTrack, SetKeyFrame, (unsigned, const AnimationKeyFrame&), void), AS_CALL_THISCALL);
    // AnimationTrack& AnimationTrack::operator=(const AnimationTrack&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AnimationTrack>(engine, "AnimationTrack");
    engine->RegisterObjectBehaviour("AnimationTrack", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("AnimationTrack", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);
#ifdef REGISTER_MANUAL_PART_AnimationTrack
    REGISTER_MANUAL_PART_AnimationTrack(AnimationTrack, "AnimationTrack")
#endif

    // Variant AnimationTriggerPoint::data_ | File: ../Graphics/Animation.h
    engine->RegisterObjectProperty("AnimationTriggerPoint", "Variant data", offsetof(AnimationTriggerPoint, data_));
    // float AnimationTriggerPoint::time_ | File: ../Graphics/Animation.h
    engine->RegisterObjectProperty("AnimationTriggerPoint", "float time", offsetof(AnimationTriggerPoint, time_));
    // AnimationTriggerPoint& AnimationTriggerPoint::operator=(const AnimationTriggerPoint&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AnimationTriggerPoint>(engine, "AnimationTriggerPoint");
#ifdef REGISTER_MANUAL_PART_AnimationTriggerPoint
    REGISTER_MANUAL_PART_AnimationTriggerPoint(AnimationTriggerPoint, "AnimationTriggerPoint")
#endif

    // SharedPtr<File> AsyncProgress::file_ | File: ../Scene/Scene.h
    // Error: type "SharedPtr<File>" can not automatically bind
    // SharedPtr<JSONFile> AsyncProgress::jsonFile_ | File: ../Scene/Scene.h
    // Error: type "SharedPtr<JSONFile>" can not automatically bind
    // unsigned AsyncProgress::jsonIndex_ | File: ../Scene/Scene.h
    engine->RegisterObjectProperty("AsyncProgress", "uint jsonIndex", offsetof(AsyncProgress, jsonIndex_));
    // unsigned AsyncProgress::loadedNodes_ | File: ../Scene/Scene.h
    engine->RegisterObjectProperty("AsyncProgress", "uint loadedNodes", offsetof(AsyncProgress, loadedNodes_));
    // unsigned AsyncProgress::loadedResources_ | File: ../Scene/Scene.h
    engine->RegisterObjectProperty("AsyncProgress", "uint loadedResources", offsetof(AsyncProgress, loadedResources_));
    // LoadMode AsyncProgress::mode_ | File: ../Scene/Scene.h
    engine->RegisterObjectProperty("AsyncProgress", "LoadMode mode", offsetof(AsyncProgress, mode_));
    // HashSet<StringHash> AsyncProgress::resources_ | File: ../Scene/Scene.h
    // Error: type "HashSet<StringHash>" can not automatically bind
    // unsigned AsyncProgress::totalNodes_ | File: ../Scene/Scene.h
    engine->RegisterObjectProperty("AsyncProgress", "uint totalNodes", offsetof(AsyncProgress, totalNodes_));
    // unsigned AsyncProgress::totalResources_ | File: ../Scene/Scene.h
    engine->RegisterObjectProperty("AsyncProgress", "uint totalResources", offsetof(AsyncProgress, totalResources_));
    // XMLElement AsyncProgress::xmlElement_ | File: ../Scene/Scene.h
    engine->RegisterObjectProperty("AsyncProgress", "XMLElement xmlElement", offsetof(AsyncProgress, xmlElement_));
    // SharedPtr<XMLFile> AsyncProgress::xmlFile_ | File: ../Scene/Scene.h
    // Error: type "SharedPtr<XMLFile>" can not automatically bind
    // AsyncProgress& AsyncProgress::operator=(const AsyncProgress&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AsyncProgress>(engine, "AsyncProgress");
#ifdef REGISTER_MANUAL_PART_AsyncProgress
    REGISTER_MANUAL_PART_AsyncProgress(AsyncProgress, "AsyncProgress")
#endif

    // SharedPtr<AttributeAccessor> AttributeInfo::accessor_ | File: ../Core/Attribute.h
    // Error: type "SharedPtr<AttributeAccessor>" can not automatically bind
    // Variant AttributeInfo::defaultValue_ | File: ../Core/Attribute.h
    engine->RegisterObjectProperty("AttributeInfo", "Variant defaultValue", offsetof(AttributeInfo, defaultValue_));
    // const char** AttributeInfo::enumNames_ | File: ../Core/Attribute.h
    // Error: type "const char**" can not automatically bind
    // VariantMap AttributeInfo::metadata_ | File: ../Core/Attribute.h
    engine->RegisterObjectProperty("AttributeInfo", "VariantMap metadata", offsetof(AttributeInfo, metadata_));
    // AttributeModeFlags AttributeInfo::mode_ | File: ../Core/Attribute.h
    engine->RegisterObjectProperty("AttributeInfo", "AttributeModeFlags mode", offsetof(AttributeInfo, mode_));
    // String AttributeInfo::name_ | File: ../Core/Attribute.h
    engine->RegisterObjectProperty("AttributeInfo", "String name", offsetof(AttributeInfo, name_));
    // void* AttributeInfo::ptr_ | File: ../Core/Attribute.h
    // void* can not be registered
    // VariantType AttributeInfo::type_ | File: ../Core/Attribute.h
    engine->RegisterObjectProperty("AttributeInfo", "VariantType type", offsetof(AttributeInfo, type_));
    // AttributeInfo::AttributeInfo(VariantType type, const char* name, const SharedPtr<AttributeAccessor>& accessor, const char** enumNames, const Variant& defaultValue, AttributeModeFlags mode) | File: ../Core/Attribute.h
    // Error: type "const char*" can not automatically bind
    // const Variant& AttributeInfo::GetMetadata(const StringHash& key) const | File: ../Core/Attribute.h
    engine->RegisterObjectMethod("AttributeInfo", "const Variant& GetMetadata(const StringHash&in) const", AS_METHODPR(AttributeInfo, GetMetadata, (const StringHash&) const, const Variant&), AS_CALL_THISCALL);
    // template<class T> T AttributeInfo::GetMetadata(const StringHash& key) const | File: ../Core/Attribute.h
    // Not registered because template
    // AttributeInfo& AttributeInfo::operator=(const AttributeInfo&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AttributeInfo>(engine, "AttributeInfo");
#ifdef REGISTER_MANUAL_PART_AttributeInfo
    REGISTER_MANUAL_PART_AttributeInfo(AttributeInfo, "AttributeInfo")
#endif

}

}
