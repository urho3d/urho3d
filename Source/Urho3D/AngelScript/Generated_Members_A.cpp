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
    engine->RegisterObjectMethod("AbstractFile", "uint GetChecksum()", asMETHODPR(AbstractFile, GetChecksum, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AbstractFile", "uint get_checksum()", asMETHODPR(AbstractFile, GetChecksum, (), unsigned), asCALL_THISCALL);
    // const String& AbstractFile::GetName() const override | File: ../IO/AbstractFile.h
    engine->RegisterObjectMethod("AbstractFile", "const String& GetName() const", asMETHODPR(AbstractFile, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AbstractFile", "const String& get_name() const", asMETHODPR(AbstractFile, GetName, () const, const String&), asCALL_THISCALL);
    // unsigned Deserializer::GetPosition() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "uint GetPosition() const", asMETHODPR(AbstractFile, GetPosition, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AbstractFile", "uint get_position() const", asMETHODPR(AbstractFile, GetPosition, () const, unsigned), asCALL_THISCALL);
    // unsigned Deserializer::GetSize() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "uint GetSize() const", asMETHODPR(AbstractFile, GetSize, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AbstractFile", "uint get_size() const", asMETHODPR(AbstractFile, GetSize, () const, unsigned), asCALL_THISCALL);
    // virtual bool Deserializer::IsEof() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool IsEof() const", asMETHODPR(AbstractFile, IsEof, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AbstractFile", "bool get_eof() const", asMETHODPR(AbstractFile, IsEof, () const, bool), asCALL_THISCALL);
    // virtual unsigned Deserializer::Read(void* dest, unsigned size)=0 | File: ../IO/Deserializer.h
    // Error: type "void*" can not automatically bind
    // bool Deserializer::ReadBool() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool ReadBool()", asMETHODPR(AbstractFile, ReadBool, (), bool), asCALL_THISCALL);
    // BoundingBox Deserializer::ReadBoundingBox() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "BoundingBox ReadBoundingBox()", asMETHODPR(AbstractFile, ReadBoundingBox, (), BoundingBox), asCALL_THISCALL);
    // PODVector<unsigned char> Deserializer::ReadBuffer() | File: ../IO/Deserializer.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // signed char Deserializer::ReadByte() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "int8 ReadByte()", asMETHODPR(AbstractFile, ReadByte, (), signed char), asCALL_THISCALL);
    // Color Deserializer::ReadColor() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Color ReadColor()", asMETHODPR(AbstractFile, ReadColor, (), Color), asCALL_THISCALL);
    // double Deserializer::ReadDouble() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "double ReadDouble()", asMETHODPR(AbstractFile, ReadDouble, (), double), asCALL_THISCALL);
    // String Deserializer::ReadFileID() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "String ReadFileID()", asMETHODPR(AbstractFile, ReadFileID, (), String), asCALL_THISCALL);
    // float Deserializer::ReadFloat() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "float ReadFloat()", asMETHODPR(AbstractFile, ReadFloat, (), float), asCALL_THISCALL);
    // int Deserializer::ReadInt() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "int ReadInt()", asMETHODPR(AbstractFile, ReadInt, (), int), asCALL_THISCALL);
    // long long Deserializer::ReadInt64() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "int64 ReadInt64()", asMETHODPR(AbstractFile, ReadInt64, (), long long), asCALL_THISCALL);
    // IntRect Deserializer::ReadIntRect() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "IntRect ReadIntRect()", asMETHODPR(AbstractFile, ReadIntRect, (), IntRect), asCALL_THISCALL);
    // IntVector2 Deserializer::ReadIntVector2() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "IntVector2 ReadIntVector2()", asMETHODPR(AbstractFile, ReadIntVector2, (), IntVector2), asCALL_THISCALL);
    // IntVector3 Deserializer::ReadIntVector3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "IntVector3 ReadIntVector3()", asMETHODPR(AbstractFile, ReadIntVector3, (), IntVector3), asCALL_THISCALL);
    // String Deserializer::ReadLine() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "String ReadLine()", asMETHODPR(AbstractFile, ReadLine, (), String), asCALL_THISCALL);
    // Matrix3 Deserializer::ReadMatrix3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Matrix3 ReadMatrix3()", asMETHODPR(AbstractFile, ReadMatrix3, (), Matrix3), asCALL_THISCALL);
    // Matrix3x4 Deserializer::ReadMatrix3x4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Matrix3x4 ReadMatrix3x4()", asMETHODPR(AbstractFile, ReadMatrix3x4, (), Matrix3x4), asCALL_THISCALL);
    // Matrix4 Deserializer::ReadMatrix4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Matrix4 ReadMatrix4()", asMETHODPR(AbstractFile, ReadMatrix4, (), Matrix4), asCALL_THISCALL);
    // unsigned Deserializer::ReadNetID() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "uint ReadNetID()", asMETHODPR(AbstractFile, ReadNetID, (), unsigned), asCALL_THISCALL);
    // Quaternion Deserializer::ReadPackedQuaternion() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Quaternion ReadPackedQuaternion()", asMETHODPR(AbstractFile, ReadPackedQuaternion, (), Quaternion), asCALL_THISCALL);
    // Vector3 Deserializer::ReadPackedVector3(float maxAbsCoord) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Vector3 ReadPackedVector3(float)", asMETHODPR(AbstractFile, ReadPackedVector3, (float), Vector3), asCALL_THISCALL);
    // Quaternion Deserializer::ReadQuaternion() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Quaternion ReadQuaternion()", asMETHODPR(AbstractFile, ReadQuaternion, (), Quaternion), asCALL_THISCALL);
    // Rect Deserializer::ReadRect() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Rect ReadRect()", asMETHODPR(AbstractFile, ReadRect, (), Rect), asCALL_THISCALL);
    // ResourceRef Deserializer::ReadResourceRef() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "ResourceRef ReadResourceRef()", asMETHODPR(AbstractFile, ReadResourceRef, (), ResourceRef), asCALL_THISCALL);
    // ResourceRefList Deserializer::ReadResourceRefList() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "ResourceRefList ReadResourceRefList()", asMETHODPR(AbstractFile, ReadResourceRefList, (), ResourceRefList), asCALL_THISCALL);
    // short Deserializer::ReadShort() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "int16 ReadShort()", asMETHODPR(AbstractFile, ReadShort, (), short), asCALL_THISCALL);
    // String Deserializer::ReadString() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "String ReadString()", asMETHODPR(AbstractFile, ReadString, (), String), asCALL_THISCALL);
    // StringHash Deserializer::ReadStringHash() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "StringHash ReadStringHash()", asMETHODPR(AbstractFile, ReadStringHash, (), StringHash), asCALL_THISCALL);
    // StringVector Deserializer::ReadStringVector() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Array<String>@ ReadStringVector()", asFUNCTION(AbstractFile_ReadStringVector_void), asCALL_CDECL_OBJFIRST);
    // unsigned char Deserializer::ReadUByte() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "uint8 ReadUByte()", asMETHODPR(AbstractFile, ReadUByte, (), unsigned char), asCALL_THISCALL);
    // unsigned Deserializer::ReadUInt() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "uint ReadUInt()", asMETHODPR(AbstractFile, ReadUInt, (), unsigned), asCALL_THISCALL);
    // unsigned long long Deserializer::ReadUInt64() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "uint64 ReadUInt64()", asMETHODPR(AbstractFile, ReadUInt64, (), unsigned long long), asCALL_THISCALL);
    // unsigned short Deserializer::ReadUShort() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "uint16 ReadUShort()", asMETHODPR(AbstractFile, ReadUShort, (), unsigned short), asCALL_THISCALL);
    // Variant Deserializer::ReadVariant() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Variant ReadVariant()", asMETHODPR(AbstractFile, ReadVariant, (), Variant), asCALL_THISCALL);
    // Variant Deserializer::ReadVariant(VariantType type) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Variant ReadVariant(VariantType)", asMETHODPR(AbstractFile, ReadVariant, (VariantType), Variant), asCALL_THISCALL);
    // VariantMap Deserializer::ReadVariantMap() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "VariantMap ReadVariantMap()", asMETHODPR(AbstractFile, ReadVariantMap, (), VariantMap), asCALL_THISCALL);
    // VariantVector Deserializer::ReadVariantVector() | File: ../IO/Deserializer.h
    // Error: type "VariantVector" can not automatically bind
    // Vector2 Deserializer::ReadVector2() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Vector2 ReadVector2()", asMETHODPR(AbstractFile, ReadVector2, (), Vector2), asCALL_THISCALL);
    // Vector3 Deserializer::ReadVector3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Vector3 ReadVector3()", asMETHODPR(AbstractFile, ReadVector3, (), Vector3), asCALL_THISCALL);
    // Vector4 Deserializer::ReadVector4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "Vector4 ReadVector4()", asMETHODPR(AbstractFile, ReadVector4, (), Vector4), asCALL_THISCALL);
    // unsigned Deserializer::ReadVLE() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "uint ReadVLE()", asMETHODPR(AbstractFile, ReadVLE, (), unsigned), asCALL_THISCALL);
    // virtual unsigned Deserializer::Seek(unsigned position)=0 | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "uint Seek(uint)", asMETHODPR(AbstractFile, Seek, (unsigned), unsigned), asCALL_THISCALL);
    // unsigned Deserializer::SeekRelative(int delta) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "uint SeekRelative(int)", asMETHODPR(AbstractFile, SeekRelative, (int), unsigned), asCALL_THISCALL);
    // virtual void AbstractFile::SetName(const String& name) | File: ../IO/AbstractFile.h
    engine->RegisterObjectMethod("AbstractFile", "void SetName(const String&in)", asMETHODPR(AbstractFile, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AbstractFile", "void set_name(const String&in)", asMETHODPR(AbstractFile, SetName, (const String&), void), asCALL_THISCALL);
    // unsigned Deserializer::Tell() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("AbstractFile", "uint Tell() const", asMETHODPR(AbstractFile, Tell, () const, unsigned), asCALL_THISCALL);
    // virtual unsigned Serializer::Write(const void* data, unsigned size)=0 | File: ../IO/Serializer.h
    // Error: type "const void*" can not automatically bind
    // bool Serializer::WriteBool(bool value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteBool(bool)", asMETHODPR(AbstractFile, WriteBool, (bool), bool), asCALL_THISCALL);
    // bool Serializer::WriteBoundingBox(const BoundingBox& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteBoundingBox(const BoundingBox&in)", asMETHODPR(AbstractFile, WriteBoundingBox, (const BoundingBox&), bool), asCALL_THISCALL);
    // bool Serializer::WriteBuffer(const PODVector<unsigned char>& value) | File: ../IO/Serializer.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // bool Serializer::WriteByte(signed char value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteByte(int8)", asMETHODPR(AbstractFile, WriteByte, (signed char), bool), asCALL_THISCALL);
    // bool Serializer::WriteColor(const Color& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteColor(const Color&in)", asMETHODPR(AbstractFile, WriteColor, (const Color&), bool), asCALL_THISCALL);
    // bool Serializer::WriteDouble(double value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteDouble(double)", asMETHODPR(AbstractFile, WriteDouble, (double), bool), asCALL_THISCALL);
    // bool Serializer::WriteFileID(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteFileID(const String&in)", asMETHODPR(AbstractFile, WriteFileID, (const String&), bool), asCALL_THISCALL);
    // bool Serializer::WriteFloat(float value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteFloat(float)", asMETHODPR(AbstractFile, WriteFloat, (float), bool), asCALL_THISCALL);
    // bool Serializer::WriteInt(int value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteInt(int)", asMETHODPR(AbstractFile, WriteInt, (int), bool), asCALL_THISCALL);
    // bool Serializer::WriteInt64(long long value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteInt64(int64)", asMETHODPR(AbstractFile, WriteInt64, (long long), bool), asCALL_THISCALL);
    // bool Serializer::WriteIntRect(const IntRect& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteIntRect(const IntRect&in)", asMETHODPR(AbstractFile, WriteIntRect, (const IntRect&), bool), asCALL_THISCALL);
    // bool Serializer::WriteIntVector2(const IntVector2& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteIntVector2(const IntVector2&in)", asMETHODPR(AbstractFile, WriteIntVector2, (const IntVector2&), bool), asCALL_THISCALL);
    // bool Serializer::WriteIntVector3(const IntVector3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteIntVector3(const IntVector3&in)", asMETHODPR(AbstractFile, WriteIntVector3, (const IntVector3&), bool), asCALL_THISCALL);
    // bool Serializer::WriteLine(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteLine(const String&in)", asMETHODPR(AbstractFile, WriteLine, (const String&), bool), asCALL_THISCALL);
    // bool Serializer::WriteMatrix3(const Matrix3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteMatrix3(const Matrix3&in)", asMETHODPR(AbstractFile, WriteMatrix3, (const Matrix3&), bool), asCALL_THISCALL);
    // bool Serializer::WriteMatrix3x4(const Matrix3x4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteMatrix3x4(const Matrix3x4&in)", asMETHODPR(AbstractFile, WriteMatrix3x4, (const Matrix3x4&), bool), asCALL_THISCALL);
    // bool Serializer::WriteMatrix4(const Matrix4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteMatrix4(const Matrix4&in)", asMETHODPR(AbstractFile, WriteMatrix4, (const Matrix4&), bool), asCALL_THISCALL);
    // bool Serializer::WriteNetID(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteNetID(uint)", asMETHODPR(AbstractFile, WriteNetID, (unsigned), bool), asCALL_THISCALL);
    // bool Serializer::WritePackedQuaternion(const Quaternion& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WritePackedQuaternion(const Quaternion&in)", asMETHODPR(AbstractFile, WritePackedQuaternion, (const Quaternion&), bool), asCALL_THISCALL);
    // bool Serializer::WritePackedVector3(const Vector3& value, float maxAbsCoord) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WritePackedVector3(const Vector3&in, float)", asMETHODPR(AbstractFile, WritePackedVector3, (const Vector3&, float), bool), asCALL_THISCALL);
    // bool Serializer::WriteQuaternion(const Quaternion& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteQuaternion(const Quaternion&in)", asMETHODPR(AbstractFile, WriteQuaternion, (const Quaternion&), bool), asCALL_THISCALL);
    // bool Serializer::WriteRect(const Rect& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteRect(const Rect&in)", asMETHODPR(AbstractFile, WriteRect, (const Rect&), bool), asCALL_THISCALL);
    // bool Serializer::WriteResourceRef(const ResourceRef& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteResourceRef(const ResourceRef&in)", asMETHODPR(AbstractFile, WriteResourceRef, (const ResourceRef&), bool), asCALL_THISCALL);
    // bool Serializer::WriteResourceRefList(const ResourceRefList& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteResourceRefList(const ResourceRefList&in)", asMETHODPR(AbstractFile, WriteResourceRefList, (const ResourceRefList&), bool), asCALL_THISCALL);
    // bool Serializer::WriteShort(short value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteShort(int16)", asMETHODPR(AbstractFile, WriteShort, (short), bool), asCALL_THISCALL);
    // bool Serializer::WriteString(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteString(const String&in)", asMETHODPR(AbstractFile, WriteString, (const String&), bool), asCALL_THISCALL);
    // bool Serializer::WriteStringHash(const StringHash& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteStringHash(const StringHash&in)", asMETHODPR(AbstractFile, WriteStringHash, (const StringHash&), bool), asCALL_THISCALL);
    // bool Serializer::WriteStringVector(const StringVector& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteStringVector(Array<String>@+)", asFUNCTION(AbstractFile_WriteStringVector_StringVector), asCALL_CDECL_OBJFIRST);
    // bool Serializer::WriteUByte(unsigned char value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteUByte(uint8)", asMETHODPR(AbstractFile, WriteUByte, (unsigned char), bool), asCALL_THISCALL);
    // bool Serializer::WriteUInt(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteUInt(uint)", asMETHODPR(AbstractFile, WriteUInt, (unsigned), bool), asCALL_THISCALL);
    // bool Serializer::WriteUInt64(unsigned long long value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteUInt64(uint64)", asMETHODPR(AbstractFile, WriteUInt64, (unsigned long long), bool), asCALL_THISCALL);
    // bool Serializer::WriteUShort(unsigned short value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteUShort(uint16)", asMETHODPR(AbstractFile, WriteUShort, (unsigned short), bool), asCALL_THISCALL);
    // bool Serializer::WriteVariant(const Variant& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteVariant(const Variant&in)", asMETHODPR(AbstractFile, WriteVariant, (const Variant&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVariantData(const Variant& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteVariantData(const Variant&in)", asMETHODPR(AbstractFile, WriteVariantData, (const Variant&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVariantMap(const VariantMap& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteVariantMap(const VariantMap&in)", asMETHODPR(AbstractFile, WriteVariantMap, (const VariantMap&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVariantVector(const VariantVector& value) | File: ../IO/Serializer.h
    // Error: type "const VariantVector&" can not automatically bind
    // bool Serializer::WriteVector2(const Vector2& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteVector2(const Vector2&in)", asMETHODPR(AbstractFile, WriteVector2, (const Vector2&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVector3(const Vector3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteVector3(const Vector3&in)", asMETHODPR(AbstractFile, WriteVector3, (const Vector3&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVector4(const Vector4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteVector4(const Vector4&in)", asMETHODPR(AbstractFile, WriteVector4, (const Vector4&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVLE(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("AbstractFile", "bool WriteVLE(uint)", asMETHODPR(AbstractFile, WriteVLE, (unsigned), bool), asCALL_THISCALL);
    // AbstractFile& AbstractFile::operator=(const AbstractFile&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AbstractFile>(engine, "AbstractFile");
    engine->RegisterObjectBehaviour("AbstractFile", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("AbstractFile", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
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
    engine->RegisterObjectBehaviour("Animatable", asBEHAVE_ADDREF, "void f()", asMETHODPR(Animatable, AddRef, (), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void AllocateNetworkState()", asMETHODPR(Animatable, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void ApplyAttributes()", asMETHODPR(Animatable, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "bool GetAnimationEnabled() const", asMETHODPR(Animatable, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "bool get_animationEnabled() const", asMETHODPR(Animatable, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "Variant GetAttribute(uint) const", asMETHODPR(Animatable, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "Variant get_attributes(uint) const", asMETHODPR(Animatable, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "Variant GetAttribute(const String&in) const", asMETHODPR(Animatable, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(Animatable, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(Animatable, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(Animatable, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(Animatable, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "Variant GetAttributeDefault(uint) const", asMETHODPR(Animatable, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "Variant get_attributeDefaults(uint) const", asMETHODPR(Animatable, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Animatable, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "bool GetBlockEvents() const", asMETHODPR(Animatable, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "const String& GetCategory() const", asMETHODPR(Animatable, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "const String& get_category() const", asMETHODPR(Animatable, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "VariantMap& GetEventDataMap() const", asMETHODPR(Animatable, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "Object@+ GetEventSender() const", asMETHODPR(Animatable, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Animatable, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Animatable, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "const VariantMap& GetGlobalVars() const", asMETHODPR(Animatable, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "const VariantMap& get_globalVars() const", asMETHODPR(Animatable, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Animatable, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "uint GetNumAttributes() const", asMETHODPR(Animatable, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "uint get_numAttributes() const", asMETHODPR(Animatable, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "uint GetNumNetworkAttributes() const", asMETHODPR(Animatable, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(Animatable, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(Animatable, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(Animatable, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Animatable, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "StringHash GetType() const", asMETHODPR(Animatable, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "StringHash get_type() const", asMETHODPR(Animatable, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "const String& GetTypeName() const", asMETHODPR(Animatable, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "const String& get_typeName() const", asMETHODPR(Animatable, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "bool HasEventHandlers() const", asMETHODPR(Animatable, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Animatable, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Animatable, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "bool IsInstanceOf(StringHash) const", asMETHODPR(Animatable, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "bool IsTemporary() const", asMETHODPR(Animatable, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "bool get_temporary() const", asMETHODPR(Animatable, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "bool Load(Deserializer&)", asMETHODPR(Animatable, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Animatable, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "bool LoadXML(const XMLElement&in)", asMETHODPR(Animatable, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void MarkNetworkUpdate()", asMETHODPR(Animatable, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Animatable, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Animatable, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Animatable, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Animatable, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Animatable, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Animatable", "int Refs() const", asMETHODPR(Animatable, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "int get_refs() const", asMETHODPR(Animatable, Refs, () const, int), asCALL_THISCALL);
    // static void Animatable::RegisterObject(Context* context) | File: ../Scene/Animatable.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Animatable", asBEHAVE_RELEASE, "void f()", asMETHODPR(Animatable, ReleaseRef, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(Animatable, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void RemoveInstanceDefault()", asMETHODPR(Animatable, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "void RemoveObjectAnimation()", asMETHODPR(Animatable, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void ResetToDefault()", asMETHODPR(Animatable, ResetToDefault, (), void), asCALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "bool Save(Serializer&) const", asMETHODPR(Animatable, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "bool SaveDefaultAttributes() const", asMETHODPR(Animatable, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "bool SaveJSON(JSONValue&) const", asMETHODPR(Animatable, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Animatable::SaveXML(XMLElement& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "bool SaveXML(XMLElement&) const", asMETHODPR(Animatable, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "void SendEvent(StringHash)", asMETHODPR(Animatable, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Animatable, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "void SetAnimationEnabled(bool)", asMETHODPR(Animatable, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "void set_animationEnabled(bool)", asMETHODPR(Animatable, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "void SetAnimationTime(float)", asMETHODPR(Animatable, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Animatable, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Animatable, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Animatable, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Animatable, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(Animatable, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(Animatable, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Animatable, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "void SetBlockEvents(bool)", asMETHODPR(Animatable, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Animatable, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Animatable, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void SetInstanceDefault(bool)", asMETHODPR(Animatable, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Animatable, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(Animatable, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(Animatable, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Animatable", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(Animatable, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void SetTemporary(bool)", asMETHODPR(Animatable, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "void set_temporary(bool)", asMETHODPR(Animatable, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "void UnsubscribeFromAllEvents()", asMETHODPR(Animatable, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Animatable_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Animatable, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Animatable, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animatable", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Animatable, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Animatable", "int WeakRefs() const", asMETHODPR(Animatable, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animatable", "int get_weakRefs() const", asMETHODPR(Animatable, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Animatable, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Animatable, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Animatable", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Animatable, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("AnimatedModel", "AnimationState@+ AddAnimationState(Animation@+)", asMETHODPR(AnimatedModel, AddAnimationState, (Animation*), AnimationState*), asCALL_THISCALL);
    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void AddLight(Light@+)", asMETHODPR(AnimatedModel, AddLight, (Light*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("AnimatedModel", asBEHAVE_ADDREF, "void f()", asMETHODPR(AnimatedModel, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void AddVertexLight(Light@+)", asMETHODPR(AnimatedModel, AddVertexLight, (Light*), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "void AllocateNetworkState()", asMETHODPR(AnimatedModel, AllocateNetworkState, (), void), asCALL_THISCALL);
    // explicit AnimatedModel::AnimatedModel(Context* context) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectBehaviour("AnimatedModel", asBEHAVE_FACTORY, "AnimatedModel@+ f()", asFUNCTION(AnimatedModel_AnimatedModel_Context), asCALL_CDECL);
    // void AnimatedModel::ApplyAnimation() | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void ApplyAnimation()", asMETHODPR(AnimatedModel, ApplyAnimation, (), void), asCALL_THISCALL);
    // void AnimatedModel::ApplyAttributes() override | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void ApplyAttributes()", asMETHODPR(AnimatedModel, ApplyAttributes, (), void), asCALL_THISCALL);
    // void StaticModel::ApplyMaterialList(const String& fileName=String::EMPTY) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void ApplyMaterialList(const String&in = String::EMPTY)", asMETHODPR(AnimatedModel, ApplyMaterialList, (const String&), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void AnimatedModel::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(AnimatedModel, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool StaticModel::DrawOcclusion(OcclusionBuffer* buffer) override | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "bool DrawOcclusion(OcclusionBuffer@+)", asMETHODPR(AnimatedModel, DrawOcclusion, (OcclusionBuffer*), bool), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool GetAnimationEnabled() const", asMETHODPR(AnimatedModel, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool get_animationEnabled() const", asMETHODPR(AnimatedModel, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // float AnimatedModel::GetAnimationLodBias() const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetAnimationLodBias() const", asMETHODPR(AnimatedModel, GetAnimationLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "float get_animationLodBias() const", asMETHODPR(AnimatedModel, GetAnimationLodBias, () const, float), asCALL_THISCALL);
    // AnimationState* AnimatedModel::GetAnimationState(Animation* animation) const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "AnimationState@+ GetAnimationState(Animation@+) const", asMETHODPR(AnimatedModel, GetAnimationState, (Animation*) const, AnimationState*), asCALL_THISCALL);
    // AnimationState* AnimatedModel::GetAnimationState(const String& animationName) const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "AnimationState@+ GetAnimationState(const String&in) const", asMETHODPR(AnimatedModel, GetAnimationState, (const String&) const, AnimationState*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "AnimationState@+ get_animationStates(const String&in) const", asMETHODPR(AnimatedModel, GetAnimationState, (const String&) const, AnimationState*), asCALL_THISCALL);
    // AnimationState* AnimatedModel::GetAnimationState(StringHash animationNameHash) const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "AnimationState@+ GetAnimationState(StringHash) const", asMETHODPR(AnimatedModel, GetAnimationState, (StringHash) const, AnimationState*), asCALL_THISCALL);
    // AnimationState* AnimatedModel::GetAnimationState(unsigned index) const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "AnimationState@+ GetAnimationState(uint) const", asMETHODPR(AnimatedModel, GetAnimationState, (unsigned) const, AnimationState*), asCALL_THISCALL);
    // const Vector<SharedPtr<AnimationState>>& AnimatedModel::GetAnimationStates() const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "Array<AnimationState@>@ GetAnimationStates() const", asFUNCTION(AnimatedModel_GetAnimationStates_void), asCALL_CDECL_OBJFIRST);
    // VariantVector AnimatedModel::GetAnimationStatesAttr() const | File: ../Graphics/AnimatedModel.h
    // Error: type "VariantVector" can not automatically bind
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "Variant GetAttribute(uint) const", asMETHODPR(AnimatedModel, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "Variant get_attributes(uint) const", asMETHODPR(AnimatedModel, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "Variant GetAttribute(const String&in) const", asMETHODPR(AnimatedModel, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(AnimatedModel, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(AnimatedModel, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(AnimatedModel, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(AnimatedModel, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "Variant GetAttributeDefault(uint) const", asMETHODPR(AnimatedModel, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "Variant get_attributeDefaults(uint) const", asMETHODPR(AnimatedModel, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(AnimatedModel, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "bool GetBlockEvents() const", asMETHODPR(AnimatedModel, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // VariantVector AnimatedModel::GetBonesEnabledAttr() const | File: ../Graphics/AnimatedModel.h
    // Error: type "VariantVector" can not automatically bind
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "const BoundingBox& GetBoundingBox() const", asMETHODPR(AnimatedModel, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "const BoundingBox& get_boundingBox() const", asMETHODPR(AnimatedModel, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool GetCastShadows() const", asMETHODPR(AnimatedModel, GetCastShadows, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool get_castShadows() const", asMETHODPR(AnimatedModel, GetCastShadows, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "const String& GetCategory() const", asMETHODPR(AnimatedModel, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "const String& get_category() const", asMETHODPR(AnimatedModel, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "Component@+ GetComponent(StringHash) const", asMETHODPR(AnimatedModel, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("AnimatedModel", "float GetDistance() const", asMETHODPR(AnimatedModel, GetDistance, () const, float), asCALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "uint8 GetDrawableFlags() const", asMETHODPR(AnimatedModel, GetDrawableFlags, () const, unsigned char), asCALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetDrawDistance() const", asMETHODPR(AnimatedModel, GetDrawDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "float get_drawDistance() const", asMETHODPR(AnimatedModel, GetDrawDistance, () const, float), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "VariantMap& GetEventDataMap() const", asMETHODPR(AnimatedModel, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "Object@+ GetEventSender() const", asMETHODPR(AnimatedModel, GetEventSender, () const, Object*), asCALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "Light@+ GetFirstLight() const", asMETHODPR(AnimatedModel, GetFirstLight, () const, Light*), asCALL_THISCALL);
    // const Vector<PODVector<unsigned>>& AnimatedModel::GetGeometryBoneMappings() const | File: ../Graphics/AnimatedModel.h
    // Error: type "const Vector<PODVector<unsigned>>&" can not automatically bind
    // const Vector<PODVector<Matrix3x4>>& AnimatedModel::GetGeometrySkinMatrices() const | File: ../Graphics/AnimatedModel.h
    // Error: type "const Vector<PODVector<Matrix3x4>>&" can not automatically bind
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(AnimatedModel, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "const Variant& get_globalVar(StringHash) const", asMETHODPR(AnimatedModel, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "const VariantMap& GetGlobalVars() const", asMETHODPR(AnimatedModel, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "const VariantMap& get_globalVars() const", asMETHODPR(AnimatedModel, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetID() const", asMETHODPR(AnimatedModel, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_id() const", asMETHODPR(AnimatedModel, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(AnimatedModel, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetLightMask() const", asMETHODPR(AnimatedModel, GetLightMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_lightMask() const", asMETHODPR(AnimatedModel, GetLightMask, () const, unsigned), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "Array<Light@>@ GetLights() const", asFUNCTION(AnimatedModel_GetLights_void), asCALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetLodBias() const", asMETHODPR(AnimatedModel, GetLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "float get_lodBias() const", asMETHODPR(AnimatedModel, GetLodBias, () const, float), asCALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetLodDistance() const", asMETHODPR(AnimatedModel, GetLodDistance, () const, float), asCALL_THISCALL);
    // Geometry* StaticModel::GetLodGeometry(unsigned batchIndex, unsigned level) override | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "Geometry@+ GetLodGeometry(uint, uint)", asMETHODPR(AnimatedModel, GetLodGeometry, (unsigned, unsigned), Geometry*), asCALL_THISCALL);
    // virtual Material* StaticModel::GetMaterial() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "Material@+ GetMaterial() const", asMETHODPR(AnimatedModel, GetMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "Material@+ get_material() const", asMETHODPR(AnimatedModel, GetMaterial, () const, Material*), asCALL_THISCALL);
    // virtual Material* StaticModel::GetMaterial(unsigned index) const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "Material@+ GetMaterial(uint) const", asMETHODPR(AnimatedModel, GetMaterial, (unsigned) const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "Material@+ get_materials(uint) const", asMETHODPR(AnimatedModel, GetMaterial, (unsigned) const, Material*), asCALL_THISCALL);
    // const ResourceRefList& StaticModel::GetMaterialsAttr() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "const ResourceRefList& GetMaterialsAttr() const", asMETHODPR(AnimatedModel, GetMaterialsAttr, () const, const ResourceRefList&), asCALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetMaxLights() const", asMETHODPR(AnimatedModel, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_maxLights() const", asMETHODPR(AnimatedModel, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetMaxZ() const", asMETHODPR(AnimatedModel, GetMaxZ, () const, float), asCALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetMinZ() const", asMETHODPR(AnimatedModel, GetMinZ, () const, float), asCALL_THISCALL);
    // Model* StaticModel::GetModel() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "Model@+ GetModel() const", asMETHODPR(AnimatedModel, GetModel, () const, Model*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "Model@+ get_model() const", asMETHODPR(AnimatedModel, GetModel, () const, Model*), asCALL_THISCALL);
    // ResourceRef AnimatedModel::GetModelAttr() const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "ResourceRef GetModelAttr() const", asMETHODPR(AnimatedModel, GetModelAttr, () const, ResourceRef), asCALL_THISCALL);
    // const Vector<ModelMorph>& AnimatedModel::GetMorphs() const | File: ../Graphics/AnimatedModel.h
    // Error: type "const Vector<ModelMorph>&" can not automatically bind
    // const PODVector<unsigned char>& AnimatedModel::GetMorphsAttr() const | File: ../Graphics/AnimatedModel.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // const Vector<SharedPtr<VertexBuffer>>& AnimatedModel::GetMorphVertexBuffers() const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "Array<VertexBuffer@>@ GetMorphVertexBuffers() const", asFUNCTION(AnimatedModel_GetMorphVertexBuffers_void), asCALL_CDECL_OBJFIRST);
    // float AnimatedModel::GetMorphWeight(unsigned index) const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetMorphWeight(uint) const", asMETHODPR(AnimatedModel, GetMorphWeight, (unsigned) const, float), asCALL_THISCALL);
    // float AnimatedModel::GetMorphWeight(const String& name) const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetMorphWeight(const String&in) const", asMETHODPR(AnimatedModel, GetMorphWeight, (const String&) const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "float get_morphWeights(const String&in) const", asMETHODPR(AnimatedModel, GetMorphWeight, (const String&) const, float), asCALL_THISCALL);
    // float AnimatedModel::GetMorphWeight(StringHash nameHash) const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetMorphWeight(StringHash) const", asMETHODPR(AnimatedModel, GetMorphWeight, (StringHash) const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "Node@+ GetNode() const", asMETHODPR(AnimatedModel, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "Node@+ get_node() const", asMETHODPR(AnimatedModel, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned AnimatedModel::GetNumAnimationStates() const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetNumAnimationStates() const", asMETHODPR(AnimatedModel, GetNumAnimationStates, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_numAnimationStates() const", asMETHODPR(AnimatedModel, GetNumAnimationStates, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetNumAttributes() const", asMETHODPR(AnimatedModel, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_numAttributes() const", asMETHODPR(AnimatedModel, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned StaticModel::GetNumGeometries() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetNumGeometries() const", asMETHODPR(AnimatedModel, GetNumGeometries, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_numGeometries() const", asMETHODPR(AnimatedModel, GetNumGeometries, () const, unsigned), asCALL_THISCALL);
    // unsigned AnimatedModel::GetNumMorphs() const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetNumMorphs() const", asMETHODPR(AnimatedModel, GetNumMorphs, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_numMorphs() const", asMETHODPR(AnimatedModel, GetNumMorphs, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetNumNetworkAttributes() const", asMETHODPR(AnimatedModel, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned StaticModel::GetNumOccluderTriangles() override | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetNumOccluderTriangles()", asMETHODPR(AnimatedModel, GetNumOccluderTriangles, (), unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(AnimatedModel, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(AnimatedModel, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(AnimatedModel, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // unsigned StaticModel::GetOcclusionLodLevel() const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetOcclusionLodLevel() const", asMETHODPR(AnimatedModel, GetOcclusionLodLevel, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_occlusionLodLevel() const", asMETHODPR(AnimatedModel, GetOcclusionLodLevel, () const, unsigned), asCALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "Scene@+ GetScene() const", asMETHODPR(AnimatedModel, GetScene, () const, Scene*), asCALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetShadowDistance() const", asMETHODPR(AnimatedModel, GetShadowDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "float get_shadowDistance() const", asMETHODPR(AnimatedModel, GetShadowDistance, () const, float), asCALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetShadowMask() const", asMETHODPR(AnimatedModel, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_shadowMask() const", asMETHODPR(AnimatedModel, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    // Skeleton& AnimatedModel::GetSkeleton() | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "Skeleton& GetSkeleton()", asMETHODPR(AnimatedModel, GetSkeleton, (), Skeleton&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "Skeleton& get_skeleton()", asMETHODPR(AnimatedModel, GetSkeleton, (), Skeleton&), asCALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "float GetSortValue() const", asMETHODPR(AnimatedModel, GetSortValue, () const, float), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(AnimatedModel, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "StringHash GetType() const", asMETHODPR(AnimatedModel, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "StringHash get_type() const", asMETHODPR(AnimatedModel, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "const String& GetTypeName() const", asMETHODPR(AnimatedModel, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "const String& get_typeName() const", asMETHODPR(AnimatedModel, GetTypeName, () const, const String&), asCALL_THISCALL);
    // UpdateGeometryType AnimatedModel::GetUpdateGeometryType() override | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "UpdateGeometryType GetUpdateGeometryType()", asMETHODPR(AnimatedModel, GetUpdateGeometryType, (), UpdateGeometryType), asCALL_THISCALL);
    // bool AnimatedModel::GetUpdateInvisible() const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "bool GetUpdateInvisible() const", asMETHODPR(AnimatedModel, GetUpdateInvisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool get_updateInvisible() const", asMETHODPR(AnimatedModel, GetUpdateInvisible, () const, bool), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "Array<Light@>@ GetVertexLights() const", asFUNCTION(AnimatedModel_GetVertexLights_void), asCALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetViewMask() const", asMETHODPR(AnimatedModel, GetViewMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_viewMask() const", asMETHODPR(AnimatedModel, GetViewMask, () const, unsigned), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "const BoundingBox& GetWorldBoundingBox()", asMETHODPR(AnimatedModel, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "const BoundingBox& get_worldBoundingBox()", asMETHODPR(AnimatedModel, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "Zone@+ GetZone() const", asMETHODPR(AnimatedModel, GetZone, () const, Zone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "Zone@+ get_zone() const", asMETHODPR(AnimatedModel, GetZone, () const, Zone*), asCALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "uint GetZoneMask() const", asMETHODPR(AnimatedModel, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "uint get_zoneMask() const", asMETHODPR(AnimatedModel, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool HasBasePass(uint) const", asMETHODPR(AnimatedModel, HasBasePass, (unsigned) const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "bool HasEventHandlers() const", asMETHODPR(AnimatedModel, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(AnimatedModel, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(AnimatedModel, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsEnabled() const", asMETHODPR(AnimatedModel, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool get_enabled() const", asMETHODPR(AnimatedModel, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsEnabledEffective() const", asMETHODPR(AnimatedModel, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool get_enabledEffective() const", asMETHODPR(AnimatedModel, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool StaticModel::IsInside(const Vector3& point) const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsInside(const Vector3&in) const", asMETHODPR(AnimatedModel, IsInside, (const Vector3&) const, bool), asCALL_THISCALL);
    // bool StaticModel::IsInsideLocal(const Vector3& point) const | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsInsideLocal(const Vector3&in) const", asMETHODPR(AnimatedModel, IsInsideLocal, (const Vector3&) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsInstanceOf(StringHash) const", asMETHODPR(AnimatedModel, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsInView() const", asMETHODPR(AnimatedModel, IsInView, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool get_inView() const", asMETHODPR(AnimatedModel, IsInView, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsInView(Camera@+) const", asMETHODPR(AnimatedModel, IsInView, (Camera*) const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsInView(const FrameInfo&in, bool = false) const", asMETHODPR(AnimatedModel, IsInView, (const FrameInfo&, bool) const, bool), asCALL_THISCALL);
    // bool AnimatedModel::IsMaster() const | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsMaster() const", asMETHODPR(AnimatedModel, IsMaster, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsOccludee() const", asMETHODPR(AnimatedModel, IsOccludee, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool get_occludee() const", asMETHODPR(AnimatedModel, IsOccludee, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsOccluder() const", asMETHODPR(AnimatedModel, IsOccluder, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool get_occluder() const", asMETHODPR(AnimatedModel, IsOccluder, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsReplicated() const", asMETHODPR(AnimatedModel, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool get_replicated() const", asMETHODPR(AnimatedModel, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsTemporary() const", asMETHODPR(AnimatedModel, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool get_temporary() const", asMETHODPR(AnimatedModel, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool IsZoneDirty() const", asMETHODPR(AnimatedModel, IsZoneDirty, () const, bool), asCALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void LimitLights()", asMETHODPR(AnimatedModel, LimitLights, (), void), asCALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void LimitVertexLights(bool)", asMETHODPR(AnimatedModel, LimitVertexLights, (bool), void), asCALL_THISCALL);
    // bool AnimatedModel::Load(Deserializer& source) override | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "bool Load(Deserializer&)", asMETHODPR(AnimatedModel, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool AnimatedModel::LoadJSON(const JSONValue& source) override | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "bool LoadJSON(const JSONValue&in)", asMETHODPR(AnimatedModel, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool AnimatedModel::LoadXML(const XMLElement& source) override | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "bool LoadXML(const XMLElement&in)", asMETHODPR(AnimatedModel, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void MarkForUpdate()", asMETHODPR(AnimatedModel, MarkForUpdate, (), void), asCALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void MarkInView(const FrameInfo&in)", asMETHODPR(AnimatedModel, MarkInView, (const FrameInfo&), void), asCALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void MarkInView(uint)", asMETHODPR(AnimatedModel, MarkInView, (unsigned), void), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "void MarkNetworkUpdate()", asMETHODPR(AnimatedModel, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(AnimatedModel, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(AnimatedModel, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(AnimatedModel, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Drawable::OnSetEnabled() override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void OnSetEnabled()", asMETHODPR(AnimatedModel, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "void PrepareNetworkUpdate()", asMETHODPR(AnimatedModel, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // void AnimatedModel::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override | File: ../Graphics/AnimatedModel.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(AnimatedModel, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(AnimatedModel, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AnimatedModel", "int Refs() const", asMETHODPR(AnimatedModel, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "int get_refs() const", asMETHODPR(AnimatedModel, Refs, () const, int), asCALL_THISCALL);
    // static void AnimatedModel::RegisterObject(Context* context) | File: ../Graphics/AnimatedModel.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("AnimatedModel", asBEHAVE_RELEASE, "void f()", asMETHODPR(AnimatedModel, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "void Remove()", asMETHODPR(AnimatedModel, Remove, (), void), asCALL_THISCALL);
    // void AnimatedModel::RemoveAllAnimationStates() | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void RemoveAllAnimationStates()", asMETHODPR(AnimatedModel, RemoveAllAnimationStates, (), void), asCALL_THISCALL);
    // void AnimatedModel::RemoveAnimationState(Animation* animation) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void RemoveAnimationState(Animation@+)", asMETHODPR(AnimatedModel, RemoveAnimationState, (Animation*), void), asCALL_THISCALL);
    // void AnimatedModel::RemoveAnimationState(const String& animationName) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void RemoveAnimationState(const String&in)", asMETHODPR(AnimatedModel, RemoveAnimationState, (const String&), void), asCALL_THISCALL);
    // void AnimatedModel::RemoveAnimationState(StringHash animationNameHash) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void RemoveAnimationState(StringHash)", asMETHODPR(AnimatedModel, RemoveAnimationState, (StringHash), void), asCALL_THISCALL);
    // void AnimatedModel::RemoveAnimationState(AnimationState* state) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void RemoveAnimationState(AnimationState@+)", asMETHODPR(AnimatedModel, RemoveAnimationState, (AnimationState*), void), asCALL_THISCALL);
    // void AnimatedModel::RemoveAnimationState(unsigned index) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void RemoveAnimationState(uint)", asMETHODPR(AnimatedModel, RemoveAnimationState, (unsigned), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(AnimatedModel, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "void RemoveInstanceDefault()", asMETHODPR(AnimatedModel, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "void RemoveObjectAnimation()", asMETHODPR(AnimatedModel, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void AnimatedModel::ResetMorphWeights() | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void ResetMorphWeights()", asMETHODPR(AnimatedModel, ResetMorphWeights, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "void ResetToDefault()", asMETHODPR(AnimatedModel, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "bool Save(Serializer&) const", asMETHODPR(AnimatedModel, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool SaveDefaultAttributes() const", asMETHODPR(AnimatedModel, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "bool SaveJSON(JSONValue&) const", asMETHODPR(AnimatedModel, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "bool SaveXML(XMLElement&) const", asMETHODPR(AnimatedModel, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "void SendEvent(StringHash)", asMETHODPR(AnimatedModel, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(AnimatedModel, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetAnimationEnabled(bool)", asMETHODPR(AnimatedModel, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_animationEnabled(bool)", asMETHODPR(AnimatedModel, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void AnimatedModel::SetAnimationLodBias(float bias) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetAnimationLodBias(float)", asMETHODPR(AnimatedModel, SetAnimationLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_animationLodBias(float)", asMETHODPR(AnimatedModel, SetAnimationLodBias, (float), void), asCALL_THISCALL);
    // void AnimatedModel::SetAnimationStatesAttr(const VariantVector& value) | File: ../Graphics/AnimatedModel.h
    // Error: type "const VariantVector&" can not automatically bind
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetAnimationTime(float)", asMETHODPR(AnimatedModel, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(AnimatedModel, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool set_attributes(uint, const Variant&in)", asMETHODPR(AnimatedModel, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(AnimatedModel, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(AnimatedModel, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(AnimatedModel, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(AnimatedModel, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(AnimatedModel, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetBasePass(uint)", asMETHODPR(AnimatedModel, SetBasePass, (unsigned), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetBlockEvents(bool)", asMETHODPR(AnimatedModel, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void AnimatedModel::SetBonesEnabledAttr(const VariantVector& value) | File: ../Graphics/AnimatedModel.h
    // Error: type "const VariantVector&" can not automatically bind
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetCastShadows(bool)", asMETHODPR(AnimatedModel, SetCastShadows, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_castShadows(bool)", asMETHODPR(AnimatedModel, SetCastShadows, (bool), void), asCALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetDrawDistance(float)", asMETHODPR(AnimatedModel, SetDrawDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_drawDistance(float)", asMETHODPR(AnimatedModel, SetDrawDistance, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetEnabled(bool)", asMETHODPR(AnimatedModel, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_enabled(bool)", asMETHODPR(AnimatedModel, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(AnimatedModel, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(AnimatedModel, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetInstanceDefault(bool)", asMETHODPR(AnimatedModel, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(AnimatedModel, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetLightMask(uint)", asMETHODPR(AnimatedModel, SetLightMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_lightMask(uint)", asMETHODPR(AnimatedModel, SetLightMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetLodBias(float)", asMETHODPR(AnimatedModel, SetLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_lodBias(float)", asMETHODPR(AnimatedModel, SetLodBias, (float), void), asCALL_THISCALL);
    // virtual void StaticModel::SetMaterial(Material* material) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetMaterial(Material@+)", asMETHODPR(AnimatedModel, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_material(Material@+)", asMETHODPR(AnimatedModel, SetMaterial, (Material*), void), asCALL_THISCALL);
    // virtual bool StaticModel::SetMaterial(unsigned index, Material* material) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "bool SetMaterial(uint, Material@+)", asMETHODPR(AnimatedModel, SetMaterial, (unsigned, Material*), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "bool set_materials(uint, Material@+)", asMETHODPR(AnimatedModel, SetMaterial, (unsigned, Material*), bool), asCALL_THISCALL);
    // void StaticModel::SetMaterialsAttr(const ResourceRefList& value) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetMaterialsAttr(const ResourceRefList&in)", asMETHODPR(AnimatedModel, SetMaterialsAttr, (const ResourceRefList&), void), asCALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetMaxLights(uint)", asMETHODPR(AnimatedModel, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_maxLights(uint)", asMETHODPR(AnimatedModel, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetMinMaxZ(float, float)", asMETHODPR(AnimatedModel, SetMinMaxZ, (float, float), void), asCALL_THISCALL);
    // void AnimatedModel::SetModel(Model* model, bool createBones=true) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetModel(Model@+, bool = true)", asMETHODPR(AnimatedModel, SetModel, (Model*, bool), void), asCALL_THISCALL);
    // void AnimatedModel::SetModelAttr(const ResourceRef& value) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetModelAttr(const ResourceRef&in)", asMETHODPR(AnimatedModel, SetModelAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void AnimatedModel::SetMorphsAttr(const PODVector<unsigned char>& value) | File: ../Graphics/AnimatedModel.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void AnimatedModel::SetMorphWeight(unsigned index, float weight) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetMorphWeight(uint, float)", asMETHODPR(AnimatedModel, SetMorphWeight, (unsigned, float), void), asCALL_THISCALL);
    // void AnimatedModel::SetMorphWeight(const String& name, float weight) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetMorphWeight(const String&in, float)", asMETHODPR(AnimatedModel, SetMorphWeight, (const String&, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_morphWeights(const String&in, float)", asMETHODPR(AnimatedModel, SetMorphWeight, (const String&, float), void), asCALL_THISCALL);
    // void AnimatedModel::SetMorphWeight(StringHash nameHash, float weight) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetMorphWeight(StringHash, float)", asMETHODPR(AnimatedModel, SetMorphWeight, (StringHash, float), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(AnimatedModel, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(AnimatedModel, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(AnimatedModel, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetOccludee(bool)", asMETHODPR(AnimatedModel, SetOccludee, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_occludee(bool)", asMETHODPR(AnimatedModel, SetOccludee, (bool), void), asCALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetOccluder(bool)", asMETHODPR(AnimatedModel, SetOccluder, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_occluder(bool)", asMETHODPR(AnimatedModel, SetOccluder, (bool), void), asCALL_THISCALL);
    // void StaticModel::SetOcclusionLodLevel(unsigned level) | File: ../Graphics/StaticModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetOcclusionLodLevel(uint)", asMETHODPR(AnimatedModel, SetOcclusionLodLevel, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_occlusionLodLevel(uint)", asMETHODPR(AnimatedModel, SetOcclusionLodLevel, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetShadowDistance(float)", asMETHODPR(AnimatedModel, SetShadowDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_shadowDistance(float)", asMETHODPR(AnimatedModel, SetShadowDistance, (float), void), asCALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetShadowMask(uint)", asMETHODPR(AnimatedModel, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_shadowMask(uint)", asMETHODPR(AnimatedModel, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetSortValue(float)", asMETHODPR(AnimatedModel, SetSortValue, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetTemporary(bool)", asMETHODPR(AnimatedModel, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_temporary(bool)", asMETHODPR(AnimatedModel, SetTemporary, (bool), void), asCALL_THISCALL);
    // void AnimatedModel::SetUpdateInvisible(bool enable) | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetUpdateInvisible(bool)", asMETHODPR(AnimatedModel, SetUpdateInvisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_updateInvisible(bool)", asMETHODPR(AnimatedModel, SetUpdateInvisible, (bool), void), asCALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetViewMask(uint)", asMETHODPR(AnimatedModel, SetViewMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_viewMask(uint)", asMETHODPR(AnimatedModel, SetViewMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetZone(Zone@+, bool = false)", asMETHODPR(AnimatedModel, SetZone, (Zone*, bool), void), asCALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedModel", "void SetZoneMask(uint)", asMETHODPR(AnimatedModel, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "void set_zoneMask(uint)", asMETHODPR(AnimatedModel, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "void UnsubscribeFromAllEvents()", asMETHODPR(AnimatedModel, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(AnimatedModel_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(AnimatedModel, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(AnimatedModel, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedModel", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(AnimatedModel, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void AnimatedModel::Update(const FrameInfo& frame) override | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void Update(const FrameInfo&in)", asMETHODPR(AnimatedModel, Update, (const FrameInfo&), void), asCALL_THISCALL);
    // void AnimatedModel::UpdateBatches(const FrameInfo& frame) override | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void UpdateBatches(const FrameInfo&in)", asMETHODPR(AnimatedModel, UpdateBatches, (const FrameInfo&), void), asCALL_THISCALL);
    // void AnimatedModel::UpdateBoneBoundingBox() | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void UpdateBoneBoundingBox()", asMETHODPR(AnimatedModel, UpdateBoneBoundingBox, (), void), asCALL_THISCALL);
    // void AnimatedModel::UpdateGeometry(const FrameInfo& frame) override | File: ../Graphics/AnimatedModel.h
    engine->RegisterObjectMethod("AnimatedModel", "void UpdateGeometry(const FrameInfo&in)", asMETHODPR(AnimatedModel, UpdateGeometry, (const FrameInfo&), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AnimatedModel", "int WeakRefs() const", asMETHODPR(AnimatedModel, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedModel", "int get_weakRefs() const", asMETHODPR(AnimatedModel, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(AnimatedModel, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(AnimatedModel, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedModel", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(AnimatedModel, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("AnimatedSprite2D", "void AddLight(Light@+)", asMETHODPR(AnimatedSprite2D, AddLight, (Light*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("AnimatedSprite2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(AnimatedSprite2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void AddVertexLight(Light@+)", asMETHODPR(AnimatedSprite2D, AddVertexLight, (Light*), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void AllocateNetworkState()", asMETHODPR(AnimatedSprite2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // explicit AnimatedSprite2D::AnimatedSprite2D(Context* context) | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectBehaviour("AnimatedSprite2D", asBEHAVE_FACTORY, "AnimatedSprite2D@+ f()", asFUNCTION(AnimatedSprite2D_AnimatedSprite2D_Context), asCALL_CDECL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void ApplyAttributes()", asMETHODPR(AnimatedSprite2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(AnimatedSprite2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool DrawOcclusion(OcclusionBuffer@+)", asMETHODPR(AnimatedSprite2D, DrawOcclusion, (OcclusionBuffer*), bool), asCALL_THISCALL);
    // float StaticSprite2D::GetAlpha() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "float GetAlpha() const", asMETHODPR(AnimatedSprite2D, GetAlpha, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "float get_alpha() const", asMETHODPR(AnimatedSprite2D, GetAlpha, () const, float), asCALL_THISCALL);
    // const String& AnimatedSprite2D::GetAnimation() const | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "const String& GetAnimation() const", asMETHODPR(AnimatedSprite2D, GetAnimation, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "const String& get_animation() const", asMETHODPR(AnimatedSprite2D, GetAnimation, () const, const String&), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool GetAnimationEnabled() const", asMETHODPR(AnimatedSprite2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_animationEnabled() const", asMETHODPR(AnimatedSprite2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // AnimationSet2D* AnimatedSprite2D::GetAnimationSet() const | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "AnimationSet2D@+ GetAnimationSet() const", asMETHODPR(AnimatedSprite2D, GetAnimationSet, () const, AnimationSet2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "AnimationSet2D@+ get_animationSet() const", asMETHODPR(AnimatedSprite2D, GetAnimationSet, () const, AnimationSet2D*), asCALL_THISCALL);
    // ResourceRef AnimatedSprite2D::GetAnimationSetAttr() const | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "ResourceRef GetAnimationSetAttr() const", asMETHODPR(AnimatedSprite2D, GetAnimationSetAttr, () const, ResourceRef), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Variant GetAttribute(uint) const", asMETHODPR(AnimatedSprite2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "Variant get_attributes(uint) const", asMETHODPR(AnimatedSprite2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Variant GetAttribute(const String&in) const", asMETHODPR(AnimatedSprite2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(AnimatedSprite2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(AnimatedSprite2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(AnimatedSprite2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(AnimatedSprite2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(AnimatedSprite2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(AnimatedSprite2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(AnimatedSprite2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // BlendMode StaticSprite2D::GetBlendMode() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "BlendMode GetBlendMode() const", asMETHODPR(AnimatedSprite2D, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "BlendMode get_blendMode() const", asMETHODPR(AnimatedSprite2D, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool GetBlockEvents() const", asMETHODPR(AnimatedSprite2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "const BoundingBox& GetBoundingBox() const", asMETHODPR(AnimatedSprite2D, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "const BoundingBox& get_boundingBox() const", asMETHODPR(AnimatedSprite2D, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool GetCastShadows() const", asMETHODPR(AnimatedSprite2D, GetCastShadows, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_castShadows() const", asMETHODPR(AnimatedSprite2D, GetCastShadows, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "const String& GetCategory() const", asMETHODPR(AnimatedSprite2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "const String& get_category() const", asMETHODPR(AnimatedSprite2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // const Color& StaticSprite2D::GetColor() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "const Color& GetColor() const", asMETHODPR(AnimatedSprite2D, GetColor, () const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "const Color& get_color() const", asMETHODPR(AnimatedSprite2D, GetColor, () const, const Color&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(AnimatedSprite2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // Material* StaticSprite2D::GetCustomMaterial() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Material@+ GetCustomMaterial() const", asMETHODPR(AnimatedSprite2D, GetCustomMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "Material@+ get_customMaterial() const", asMETHODPR(AnimatedSprite2D, GetCustomMaterial, () const, Material*), asCALL_THISCALL);
    // ResourceRef StaticSprite2D::GetCustomMaterialAttr() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "ResourceRef GetCustomMaterialAttr() const", asMETHODPR(AnimatedSprite2D, GetCustomMaterialAttr, () const, ResourceRef), asCALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // float Drawable::GetDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "float GetDistance() const", asMETHODPR(AnimatedSprite2D, GetDistance, () const, float), asCALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint8 GetDrawableFlags() const", asMETHODPR(AnimatedSprite2D, GetDrawableFlags, () const, unsigned char), asCALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "float GetDrawDistance() const", asMETHODPR(AnimatedSprite2D, GetDrawDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "float get_drawDistance() const", asMETHODPR(AnimatedSprite2D, GetDrawDistance, () const, float), asCALL_THISCALL);
    // const Rect& StaticSprite2D::GetDrawRect() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "const Rect& GetDrawRect() const", asMETHODPR(AnimatedSprite2D, GetDrawRect, () const, const Rect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "const Rect& get_drawRect() const", asMETHODPR(AnimatedSprite2D, GetDrawRect, () const, const Rect&), asCALL_THISCALL);
    // const String& AnimatedSprite2D::GetEntity() const | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "const String& GetEntity() const", asMETHODPR(AnimatedSprite2D, GetEntity, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "const String& get_entity() const", asMETHODPR(AnimatedSprite2D, GetEntity, () const, const String&), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "VariantMap& GetEventDataMap() const", asMETHODPR(AnimatedSprite2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Object@+ GetEventSender() const", asMETHODPR(AnimatedSprite2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Light@+ GetFirstLight() const", asMETHODPR(AnimatedSprite2D, GetFirstLight, () const, Light*), asCALL_THISCALL);
    // bool StaticSprite2D::GetFlipX() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool GetFlipX() const", asMETHODPR(AnimatedSprite2D, GetFlipX, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_flipX() const", asMETHODPR(AnimatedSprite2D, GetFlipX, () const, bool), asCALL_THISCALL);
    // bool StaticSprite2D::GetFlipY() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool GetFlipY() const", asMETHODPR(AnimatedSprite2D, GetFlipY, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_flipY() const", asMETHODPR(AnimatedSprite2D, GetFlipY, () const, bool), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(AnimatedSprite2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(AnimatedSprite2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(AnimatedSprite2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "const VariantMap& get_globalVars() const", asMETHODPR(AnimatedSprite2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // const Vector2& StaticSprite2D::GetHotSpot() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "const Vector2& GetHotSpot() const", asMETHODPR(AnimatedSprite2D, GetHotSpot, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "const Vector2& get_hotSpot() const", asMETHODPR(AnimatedSprite2D, GetHotSpot, () const, const Vector2&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint GetID() const", asMETHODPR(AnimatedSprite2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint get_id() const", asMETHODPR(AnimatedSprite2D, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(AnimatedSprite2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // int Drawable2D::GetLayer() const | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "int GetLayer() const", asMETHODPR(AnimatedSprite2D, GetLayer, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "int get_layer() const", asMETHODPR(AnimatedSprite2D, GetLayer, () const, int), asCALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint GetLightMask() const", asMETHODPR(AnimatedSprite2D, GetLightMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint get_lightMask() const", asMETHODPR(AnimatedSprite2D, GetLightMask, () const, unsigned), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Array<Light@>@ GetLights() const", asFUNCTION(AnimatedSprite2D_GetLights_void), asCALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "float GetLodBias() const", asMETHODPR(AnimatedSprite2D, GetLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "float get_lodBias() const", asMETHODPR(AnimatedSprite2D, GetLodBias, () const, float), asCALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "float GetLodDistance() const", asMETHODPR(AnimatedSprite2D, GetLodDistance, () const, float), asCALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Geometry@+ GetLodGeometry(uint, uint)", asMETHODPR(AnimatedSprite2D, GetLodGeometry, (unsigned, unsigned), Geometry*), asCALL_THISCALL);
    // LoopMode2D AnimatedSprite2D::GetLoopMode() const | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "LoopMode2D GetLoopMode() const", asMETHODPR(AnimatedSprite2D, GetLoopMode, () const, LoopMode2D), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "LoopMode2D get_loopMode() const", asMETHODPR(AnimatedSprite2D, GetLoopMode, () const, LoopMode2D), asCALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint GetMaxLights() const", asMETHODPR(AnimatedSprite2D, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint get_maxLights() const", asMETHODPR(AnimatedSprite2D, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "float GetMaxZ() const", asMETHODPR(AnimatedSprite2D, GetMaxZ, () const, float), asCALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "float GetMinZ() const", asMETHODPR(AnimatedSprite2D, GetMinZ, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Node@+ GetNode() const", asMETHODPR(AnimatedSprite2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "Node@+ get_node() const", asMETHODPR(AnimatedSprite2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint GetNumAttributes() const", asMETHODPR(AnimatedSprite2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint get_numAttributes() const", asMETHODPR(AnimatedSprite2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint GetNumNetworkAttributes() const", asMETHODPR(AnimatedSprite2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint GetNumOccluderTriangles()", asMETHODPR(AnimatedSprite2D, GetNumOccluderTriangles, (), unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(AnimatedSprite2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(AnimatedSprite2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(AnimatedSprite2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // int Drawable2D::GetOrderInLayer() const | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "int GetOrderInLayer() const", asMETHODPR(AnimatedSprite2D, GetOrderInLayer, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "int get_orderInLayer() const", asMETHODPR(AnimatedSprite2D, GetOrderInLayer, () const, int), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Scene@+ GetScene() const", asMETHODPR(AnimatedSprite2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "float GetShadowDistance() const", asMETHODPR(AnimatedSprite2D, GetShadowDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "float get_shadowDistance() const", asMETHODPR(AnimatedSprite2D, GetShadowDistance, () const, float), asCALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint GetShadowMask() const", asMETHODPR(AnimatedSprite2D, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint get_shadowMask() const", asMETHODPR(AnimatedSprite2D, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "float GetSortValue() const", asMETHODPR(AnimatedSprite2D, GetSortValue, () const, float), asCALL_THISCALL);
    // const Vector<SourceBatch2D>& Drawable2D::GetSourceBatches() | File: ../Urho2D/Drawable2D.h
    // Error: type "const Vector<SourceBatch2D>&" can not automatically bind
    // float AnimatedSprite2D::GetSpeed() const | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "float GetSpeed() const", asMETHODPR(AnimatedSprite2D, GetSpeed, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "float get_speed() const", asMETHODPR(AnimatedSprite2D, GetSpeed, () const, float), asCALL_THISCALL);
    // Sprite2D* StaticSprite2D::GetSprite() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Sprite2D@+ GetSprite() const", asMETHODPR(AnimatedSprite2D, GetSprite, () const, Sprite2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "Sprite2D@+ get_sprite() const", asMETHODPR(AnimatedSprite2D, GetSprite, () const, Sprite2D*), asCALL_THISCALL);
    // ResourceRef StaticSprite2D::GetSpriteAttr() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "ResourceRef GetSpriteAttr() const", asMETHODPR(AnimatedSprite2D, GetSpriteAttr, () const, ResourceRef), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(AnimatedSprite2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // bool StaticSprite2D::GetSwapXY() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool GetSwapXY() const", asMETHODPR(AnimatedSprite2D, GetSwapXY, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_swapXY() const", asMETHODPR(AnimatedSprite2D, GetSwapXY, () const, bool), asCALL_THISCALL);
    // const Rect& StaticSprite2D::GetTextureRect() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "const Rect& GetTextureRect() const", asMETHODPR(AnimatedSprite2D, GetTextureRect, () const, const Rect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "const Rect& get_textureRect() const", asMETHODPR(AnimatedSprite2D, GetTextureRect, () const, const Rect&), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "StringHash GetType() const", asMETHODPR(AnimatedSprite2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "StringHash get_type() const", asMETHODPR(AnimatedSprite2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "const String& GetTypeName() const", asMETHODPR(AnimatedSprite2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "const String& get_typeName() const", asMETHODPR(AnimatedSprite2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // virtual UpdateGeometryType Drawable::GetUpdateGeometryType() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "UpdateGeometryType GetUpdateGeometryType()", asMETHODPR(AnimatedSprite2D, GetUpdateGeometryType, (), UpdateGeometryType), asCALL_THISCALL);
    // bool StaticSprite2D::GetUseDrawRect() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool GetUseDrawRect() const", asMETHODPR(AnimatedSprite2D, GetUseDrawRect, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_useDrawRect() const", asMETHODPR(AnimatedSprite2D, GetUseDrawRect, () const, bool), asCALL_THISCALL);
    // bool StaticSprite2D::GetUseHotSpot() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool GetUseHotSpot() const", asMETHODPR(AnimatedSprite2D, GetUseHotSpot, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_useHotSpot() const", asMETHODPR(AnimatedSprite2D, GetUseHotSpot, () const, bool), asCALL_THISCALL);
    // bool StaticSprite2D::GetUseTextureRect() const | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool GetUseTextureRect() const", asMETHODPR(AnimatedSprite2D, GetUseTextureRect, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_useTextureRect() const", asMETHODPR(AnimatedSprite2D, GetUseTextureRect, () const, bool), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Array<Light@>@ GetVertexLights() const", asFUNCTION(AnimatedSprite2D_GetVertexLights_void), asCALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint GetViewMask() const", asMETHODPR(AnimatedSprite2D, GetViewMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint get_viewMask() const", asMETHODPR(AnimatedSprite2D, GetViewMask, () const, unsigned), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "const BoundingBox& GetWorldBoundingBox()", asMETHODPR(AnimatedSprite2D, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "const BoundingBox& get_worldBoundingBox()", asMETHODPR(AnimatedSprite2D, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "Zone@+ GetZone() const", asMETHODPR(AnimatedSprite2D, GetZone, () const, Zone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "Zone@+ get_zone() const", asMETHODPR(AnimatedSprite2D, GetZone, () const, Zone*), asCALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint GetZoneMask() const", asMETHODPR(AnimatedSprite2D, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "uint get_zoneMask() const", asMETHODPR(AnimatedSprite2D, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool HasBasePass(uint) const", asMETHODPR(AnimatedSprite2D, HasBasePass, (unsigned) const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool HasEventHandlers() const", asMETHODPR(AnimatedSprite2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(AnimatedSprite2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(AnimatedSprite2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool IsEnabled() const", asMETHODPR(AnimatedSprite2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_enabled() const", asMETHODPR(AnimatedSprite2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool IsEnabledEffective() const", asMETHODPR(AnimatedSprite2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_enabledEffective() const", asMETHODPR(AnimatedSprite2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(AnimatedSprite2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool IsInView() const", asMETHODPR(AnimatedSprite2D, IsInView, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_inView() const", asMETHODPR(AnimatedSprite2D, IsInView, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool IsInView(Camera@+) const", asMETHODPR(AnimatedSprite2D, IsInView, (Camera*) const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool IsInView(const FrameInfo&in, bool = false) const", asMETHODPR(AnimatedSprite2D, IsInView, (const FrameInfo&, bool) const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool IsOccludee() const", asMETHODPR(AnimatedSprite2D, IsOccludee, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_occludee() const", asMETHODPR(AnimatedSprite2D, IsOccludee, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool IsOccluder() const", asMETHODPR(AnimatedSprite2D, IsOccluder, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_occluder() const", asMETHODPR(AnimatedSprite2D, IsOccluder, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool IsReplicated() const", asMETHODPR(AnimatedSprite2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_replicated() const", asMETHODPR(AnimatedSprite2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool IsTemporary() const", asMETHODPR(AnimatedSprite2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool get_temporary() const", asMETHODPR(AnimatedSprite2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool IsZoneDirty() const", asMETHODPR(AnimatedSprite2D, IsZoneDirty, () const, bool), asCALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void LimitLights()", asMETHODPR(AnimatedSprite2D, LimitLights, (), void), asCALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void LimitVertexLights(bool)", asMETHODPR(AnimatedSprite2D, LimitVertexLights, (bool), void), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool Load(Deserializer&)", asMETHODPR(AnimatedSprite2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(AnimatedSprite2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(AnimatedSprite2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void MarkForUpdate()", asMETHODPR(AnimatedSprite2D, MarkForUpdate, (), void), asCALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void MarkInView(const FrameInfo&in)", asMETHODPR(AnimatedSprite2D, MarkInView, (const FrameInfo&), void), asCALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void MarkInView(uint)", asMETHODPR(AnimatedSprite2D, MarkInView, (unsigned), void), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void MarkNetworkUpdate()", asMETHODPR(AnimatedSprite2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(AnimatedSprite2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(AnimatedSprite2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(AnimatedSprite2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void AnimatedSprite2D::OnSetEnabled() override | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void OnSetEnabled()", asMETHODPR(AnimatedSprite2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void PrepareNetworkUpdate()", asMETHODPR(AnimatedSprite2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) | File: ../Graphics/Drawable.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(AnimatedSprite2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(AnimatedSprite2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "int Refs() const", asMETHODPR(AnimatedSprite2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "int get_refs() const", asMETHODPR(AnimatedSprite2D, Refs, () const, int), asCALL_THISCALL);
    // static void AnimatedSprite2D::RegisterObject(Context* context) | File: ../Urho2D/AnimatedSprite2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("AnimatedSprite2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(AnimatedSprite2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void Remove()", asMETHODPR(AnimatedSprite2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(AnimatedSprite2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void RemoveInstanceDefault()", asMETHODPR(AnimatedSprite2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void RemoveObjectAnimation()", asMETHODPR(AnimatedSprite2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void ResetToDefault()", asMETHODPR(AnimatedSprite2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool Save(Serializer&) const", asMETHODPR(AnimatedSprite2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool SaveDefaultAttributes() const", asMETHODPR(AnimatedSprite2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(AnimatedSprite2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool SaveXML(XMLElement&) const", asMETHODPR(AnimatedSprite2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SendEvent(StringHash)", asMETHODPR(AnimatedSprite2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(AnimatedSprite2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void StaticSprite2D::SetAlpha(float alpha) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetAlpha(float)", asMETHODPR(AnimatedSprite2D, SetAlpha, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_alpha(float)", asMETHODPR(AnimatedSprite2D, SetAlpha, (float), void), asCALL_THISCALL);
    // void AnimatedSprite2D::SetAnimation(const String& name, LoopMode2D loopMode=LM_DEFAULT) | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetAnimation(const String&in, LoopMode2D = LM_DEFAULT)", asMETHODPR(AnimatedSprite2D, SetAnimation, (const String&, LoopMode2D), void), asCALL_THISCALL);
    // void AnimatedSprite2D::SetAnimationAttr(const String& name) | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetAnimationAttr(const String&in)", asMETHODPR(AnimatedSprite2D, SetAnimationAttr, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_animation(const String&in)", asMETHODPR(AnimatedSprite2D, SetAnimationAttr, (const String&), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetAnimationEnabled(bool)", asMETHODPR(AnimatedSprite2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_animationEnabled(bool)", asMETHODPR(AnimatedSprite2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void AnimatedSprite2D::SetAnimationSet(AnimationSet2D* animationSet) | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetAnimationSet(AnimationSet2D@+)", asMETHODPR(AnimatedSprite2D, SetAnimationSet, (AnimationSet2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_animationSet(AnimationSet2D@+)", asMETHODPR(AnimatedSprite2D, SetAnimationSet, (AnimationSet2D*), void), asCALL_THISCALL);
    // void AnimatedSprite2D::SetAnimationSetAttr(const ResourceRef& value) | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetAnimationSetAttr(const ResourceRef&in)", asMETHODPR(AnimatedSprite2D, SetAnimationSetAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetAnimationTime(float)", asMETHODPR(AnimatedSprite2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(AnimatedSprite2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(AnimatedSprite2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(AnimatedSprite2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(AnimatedSprite2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(AnimatedSprite2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(AnimatedSprite2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(AnimatedSprite2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetBasePass(uint)", asMETHODPR(AnimatedSprite2D, SetBasePass, (unsigned), void), asCALL_THISCALL);
    // void StaticSprite2D::SetBlendMode(BlendMode blendMode) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetBlendMode(BlendMode)", asMETHODPR(AnimatedSprite2D, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_blendMode(BlendMode)", asMETHODPR(AnimatedSprite2D, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetBlockEvents(bool)", asMETHODPR(AnimatedSprite2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetCastShadows(bool)", asMETHODPR(AnimatedSprite2D, SetCastShadows, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_castShadows(bool)", asMETHODPR(AnimatedSprite2D, SetCastShadows, (bool), void), asCALL_THISCALL);
    // void StaticSprite2D::SetColor(const Color& color) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetColor(const Color&in)", asMETHODPR(AnimatedSprite2D, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_color(const Color&in)", asMETHODPR(AnimatedSprite2D, SetColor, (const Color&), void), asCALL_THISCALL);
    // void StaticSprite2D::SetCustomMaterial(Material* customMaterial) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetCustomMaterial(Material@+)", asMETHODPR(AnimatedSprite2D, SetCustomMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_customMaterial(Material@+)", asMETHODPR(AnimatedSprite2D, SetCustomMaterial, (Material*), void), asCALL_THISCALL);
    // void StaticSprite2D::SetCustomMaterialAttr(const ResourceRef& value) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetCustomMaterialAttr(const ResourceRef&in)", asMETHODPR(AnimatedSprite2D, SetCustomMaterialAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetDrawDistance(float)", asMETHODPR(AnimatedSprite2D, SetDrawDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_drawDistance(float)", asMETHODPR(AnimatedSprite2D, SetDrawDistance, (float), void), asCALL_THISCALL);
    // void StaticSprite2D::SetDrawRect(const Rect& rect) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetDrawRect(const Rect&in)", asMETHODPR(AnimatedSprite2D, SetDrawRect, (const Rect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_drawRect(const Rect&in)", asMETHODPR(AnimatedSprite2D, SetDrawRect, (const Rect&), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetEnabled(bool)", asMETHODPR(AnimatedSprite2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_enabled(bool)", asMETHODPR(AnimatedSprite2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void AnimatedSprite2D::SetEntity(const String& entity) | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetEntity(const String&in)", asMETHODPR(AnimatedSprite2D, SetEntity, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_entity(const String&in)", asMETHODPR(AnimatedSprite2D, SetEntity, (const String&), void), asCALL_THISCALL);
    // void StaticSprite2D::SetFlip(bool flipX, bool flipY, bool swapXY=false) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetFlip(bool, bool, bool = false)", asMETHODPR(AnimatedSprite2D, SetFlip, (bool, bool, bool), void), asCALL_THISCALL);
    // void StaticSprite2D::SetFlipX(bool flipX) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetFlipX(bool)", asMETHODPR(AnimatedSprite2D, SetFlipX, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_flipX(bool)", asMETHODPR(AnimatedSprite2D, SetFlipX, (bool), void), asCALL_THISCALL);
    // void StaticSprite2D::SetFlipY(bool flipY) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetFlipY(bool)", asMETHODPR(AnimatedSprite2D, SetFlipY, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_flipY(bool)", asMETHODPR(AnimatedSprite2D, SetFlipY, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(AnimatedSprite2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(AnimatedSprite2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void StaticSprite2D::SetHotSpot(const Vector2& hotspot) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetHotSpot(const Vector2&in)", asMETHODPR(AnimatedSprite2D, SetHotSpot, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_hotSpot(const Vector2&in)", asMETHODPR(AnimatedSprite2D, SetHotSpot, (const Vector2&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetInstanceDefault(bool)", asMETHODPR(AnimatedSprite2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(AnimatedSprite2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Drawable2D::SetLayer(int layer) | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetLayer(int)", asMETHODPR(AnimatedSprite2D, SetLayer, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_layer(int)", asMETHODPR(AnimatedSprite2D, SetLayer, (int), void), asCALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetLightMask(uint)", asMETHODPR(AnimatedSprite2D, SetLightMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_lightMask(uint)", asMETHODPR(AnimatedSprite2D, SetLightMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetLodBias(float)", asMETHODPR(AnimatedSprite2D, SetLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_lodBias(float)", asMETHODPR(AnimatedSprite2D, SetLodBias, (float), void), asCALL_THISCALL);
    // void AnimatedSprite2D::SetLoopMode(LoopMode2D loopMode) | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetLoopMode(LoopMode2D)", asMETHODPR(AnimatedSprite2D, SetLoopMode, (LoopMode2D), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_loopMode(LoopMode2D)", asMETHODPR(AnimatedSprite2D, SetLoopMode, (LoopMode2D), void), asCALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetMaxLights(uint)", asMETHODPR(AnimatedSprite2D, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_maxLights(uint)", asMETHODPR(AnimatedSprite2D, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetMinMaxZ(float, float)", asMETHODPR(AnimatedSprite2D, SetMinMaxZ, (float, float), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(AnimatedSprite2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(AnimatedSprite2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(AnimatedSprite2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetOccludee(bool)", asMETHODPR(AnimatedSprite2D, SetOccludee, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_occludee(bool)", asMETHODPR(AnimatedSprite2D, SetOccludee, (bool), void), asCALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetOccluder(bool)", asMETHODPR(AnimatedSprite2D, SetOccluder, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_occluder(bool)", asMETHODPR(AnimatedSprite2D, SetOccluder, (bool), void), asCALL_THISCALL);
    // void Drawable2D::SetOrderInLayer(int orderInLayer) | File: ../Urho2D/Drawable2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetOrderInLayer(int)", asMETHODPR(AnimatedSprite2D, SetOrderInLayer, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_orderInLayer(int)", asMETHODPR(AnimatedSprite2D, SetOrderInLayer, (int), void), asCALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetShadowDistance(float)", asMETHODPR(AnimatedSprite2D, SetShadowDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_shadowDistance(float)", asMETHODPR(AnimatedSprite2D, SetShadowDistance, (float), void), asCALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetShadowMask(uint)", asMETHODPR(AnimatedSprite2D, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_shadowMask(uint)", asMETHODPR(AnimatedSprite2D, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetSortValue(float)", asMETHODPR(AnimatedSprite2D, SetSortValue, (float), void), asCALL_THISCALL);
    // void AnimatedSprite2D::SetSpeed(float speed) | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetSpeed(float)", asMETHODPR(AnimatedSprite2D, SetSpeed, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_speed(float)", asMETHODPR(AnimatedSprite2D, SetSpeed, (float), void), asCALL_THISCALL);
    // void StaticSprite2D::SetSprite(Sprite2D* sprite) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetSprite(Sprite2D@+)", asMETHODPR(AnimatedSprite2D, SetSprite, (Sprite2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_sprite(Sprite2D@+)", asMETHODPR(AnimatedSprite2D, SetSprite, (Sprite2D*), void), asCALL_THISCALL);
    // void StaticSprite2D::SetSpriteAttr(const ResourceRef& value) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetSpriteAttr(const ResourceRef&in)", asMETHODPR(AnimatedSprite2D, SetSpriteAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void StaticSprite2D::SetSwapXY(bool swapXY) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetSwapXY(bool)", asMETHODPR(AnimatedSprite2D, SetSwapXY, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_swapXY(bool)", asMETHODPR(AnimatedSprite2D, SetSwapXY, (bool), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetTemporary(bool)", asMETHODPR(AnimatedSprite2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_temporary(bool)", asMETHODPR(AnimatedSprite2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void StaticSprite2D::SetTextureRect(const Rect& rect) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetTextureRect(const Rect&in)", asMETHODPR(AnimatedSprite2D, SetTextureRect, (const Rect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_textureRect(const Rect&in)", asMETHODPR(AnimatedSprite2D, SetTextureRect, (const Rect&), void), asCALL_THISCALL);
    // void StaticSprite2D::SetUseDrawRect(bool useDrawRect) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetUseDrawRect(bool)", asMETHODPR(AnimatedSprite2D, SetUseDrawRect, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_useDrawRect(bool)", asMETHODPR(AnimatedSprite2D, SetUseDrawRect, (bool), void), asCALL_THISCALL);
    // void StaticSprite2D::SetUseHotSpot(bool useHotSpot) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetUseHotSpot(bool)", asMETHODPR(AnimatedSprite2D, SetUseHotSpot, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_useHotSpot(bool)", asMETHODPR(AnimatedSprite2D, SetUseHotSpot, (bool), void), asCALL_THISCALL);
    // void StaticSprite2D::SetUseTextureRect(bool useTextureRect) | File: ../Urho2D/StaticSprite2D.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetUseTextureRect(bool)", asMETHODPR(AnimatedSprite2D, SetUseTextureRect, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_useTextureRect(bool)", asMETHODPR(AnimatedSprite2D, SetUseTextureRect, (bool), void), asCALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetViewMask(uint)", asMETHODPR(AnimatedSprite2D, SetViewMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_viewMask(uint)", asMETHODPR(AnimatedSprite2D, SetViewMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetZone(Zone@+, bool = false)", asMETHODPR(AnimatedSprite2D, SetZone, (Zone*, bool), void), asCALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetZoneMask(uint)", asMETHODPR(AnimatedSprite2D, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_zoneMask(uint)", asMETHODPR(AnimatedSprite2D, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void UnsubscribeFromAllEvents()", asMETHODPR(AnimatedSprite2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(AnimatedSprite2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(AnimatedSprite2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(AnimatedSprite2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(AnimatedSprite2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void Update(const FrameInfo&in)", asMETHODPR(AnimatedSprite2D, Update, (const FrameInfo&), void), asCALL_THISCALL);
    // virtual void Drawable::UpdateBatches(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void UpdateBatches(const FrameInfo&in)", asMETHODPR(AnimatedSprite2D, UpdateBatches, (const FrameInfo&), void), asCALL_THISCALL);
    // virtual void Drawable::UpdateGeometry(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void UpdateGeometry(const FrameInfo&in)", asMETHODPR(AnimatedSprite2D, UpdateGeometry, (const FrameInfo&), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "int WeakRefs() const", asMETHODPR(AnimatedSprite2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "int get_weakRefs() const", asMETHODPR(AnimatedSprite2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(AnimatedSprite2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(AnimatedSprite2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimatedSprite2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(AnimatedSprite2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Animation", "void AddMetadata(const String&in, const Variant&in)", asMETHODPR(Animation, AddMetadata, (const String&, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "void set_metadata(const String&in, const Variant&in)", asMETHODPR(Animation, AddMetadata, (const String&, const Variant&), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Animation", asBEHAVE_ADDREF, "void f()", asMETHODPR(Animation, AddRef, (), void), asCALL_THISCALL);
    // void Animation::AddTrigger(const AnimationTriggerPoint& trigger) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "void AddTrigger(const AnimationTriggerPoint&in)", asMETHODPR(Animation, AddTrigger, (const AnimationTriggerPoint&), void), asCALL_THISCALL);
    // void Animation::AddTrigger(float time, bool timeIsNormalized, const Variant& data) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "void AddTrigger(float, bool, const Variant&in)", asMETHODPR(Animation, AddTrigger, (float, bool, const Variant&), void), asCALL_THISCALL);
    // explicit Animation::Animation(Context* context) | File: ../Graphics/Animation.h
    engine->RegisterObjectBehaviour("Animation", asBEHAVE_FACTORY, "Animation@+ f()", asFUNCTION(Animation_Animation_Context), asCALL_CDECL);
    // bool Animation::BeginLoad(Deserializer& source) override | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "bool BeginLoad(Deserializer&)", asMETHODPR(Animation, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // SharedPtr<Animation> Animation::Clone(const String& cloneName=String::EMPTY) const | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "Animation@+ Clone(const String&in = String::EMPTY) const", asFUNCTION(Animation_Clone_String), asCALL_CDECL_OBJFIRST);
    // AnimationTrack* Animation::CreateTrack(const String& name) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "AnimationTrack@+ CreateTrack(const String&in)", asMETHODPR(Animation, CreateTrack, (const String&), AnimationTrack*), asCALL_THISCALL);
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "bool EndLoad()", asMETHODPR(Animation, EndLoad, (), bool), asCALL_THISCALL);
    // const String& Animation::GetAnimationName() const | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "const String& GetAnimationName() const", asMETHODPR(Animation, GetAnimationName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "const String& get_animationName() const", asMETHODPR(Animation, GetAnimationName, () const, const String&), asCALL_THISCALL);
    // StringHash Animation::GetAnimationNameHash() const | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "StringHash GetAnimationNameHash() const", asMETHODPR(Animation, GetAnimationNameHash, () const, StringHash), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(Animation, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "bool GetBlockEvents() const", asMETHODPR(Animation, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "const String& GetCategory() const", asMETHODPR(Animation, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "const String& get_category() const", asMETHODPR(Animation, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "VariantMap& GetEventDataMap() const", asMETHODPR(Animation, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "Object@+ GetEventSender() const", asMETHODPR(Animation, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Animation, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Animation, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "const VariantMap& GetGlobalVars() const", asMETHODPR(Animation, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "const VariantMap& get_globalVars() const", asMETHODPR(Animation, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // float Animation::GetLength() const | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "float GetLength() const", asMETHODPR(Animation, GetLength, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "float get_length() const", asMETHODPR(Animation, GetLength, () const, float), asCALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "uint GetMemoryUse() const", asMETHODPR(Animation, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "uint get_memoryUse() const", asMETHODPR(Animation, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // const Variant& ResourceWithMetadata::GetMetadata(const String& name) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "const Variant& GetMetadata(const String&in) const", asMETHODPR(Animation, GetMetadata, (const String&) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "const Variant& get_metadata(const String&in) const", asMETHODPR(Animation, GetMetadata, (const String&) const, const Variant&), asCALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "const String& GetName() const", asMETHODPR(Animation, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "const String& get_name() const", asMETHODPR(Animation, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "StringHash GetNameHash() const", asMETHODPR(Animation, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // unsigned Animation::GetNumTracks() const | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "uint GetNumTracks() const", asMETHODPR(Animation, GetNumTracks, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "uint get_numTracks() const", asMETHODPR(Animation, GetNumTracks, () const, unsigned), asCALL_THISCALL);
    // unsigned Animation::GetNumTriggers() const | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "uint GetNumTriggers() const", asMETHODPR(Animation, GetNumTriggers, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "uint get_numTriggers() const", asMETHODPR(Animation, GetNumTriggers, () const, unsigned), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Animation, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // AnimationTrack* Animation::GetTrack(unsigned index) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "AnimationTrack@+ GetTrack(uint)", asMETHODPR(Animation, GetTrack, (unsigned), AnimationTrack*), asCALL_THISCALL);
    // AnimationTrack* Animation::GetTrack(const String& name) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "AnimationTrack@+ GetTrack(const String&in)", asMETHODPR(Animation, GetTrack, (const String&), AnimationTrack*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "AnimationTrack@+ get_tracks(const String&in)", asMETHODPR(Animation, GetTrack, (const String&), AnimationTrack*), asCALL_THISCALL);
    // AnimationTrack* Animation::GetTrack(StringHash nameHash) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "AnimationTrack@+ GetTrack(StringHash)", asMETHODPR(Animation, GetTrack, (StringHash), AnimationTrack*), asCALL_THISCALL);
    // const HashMap<StringHash, AnimationTrack>& Animation::GetTracks() const | File: ../Graphics/Animation.h
    // Error: type "const HashMap<StringHash, AnimationTrack>&" can not automatically bind
    // AnimationTriggerPoint* Animation::GetTrigger(unsigned index) | File: ../Graphics/Animation.h
    // Error: type "AnimationTriggerPoint*" can not automatically bind
    // const Vector<AnimationTriggerPoint>& Animation::GetTriggers() const | File: ../Graphics/Animation.h
    // Error: type "const Vector<AnimationTriggerPoint>&" can not automatically bind
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "StringHash GetType() const", asMETHODPR(Animation, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "StringHash get_type() const", asMETHODPR(Animation, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "const String& GetTypeName() const", asMETHODPR(Animation, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "const String& get_typeName() const", asMETHODPR(Animation, GetTypeName, () const, const String&), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "uint GetUseTimer()", asMETHODPR(Animation, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "uint get_useTimer()", asMETHODPR(Animation, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "bool HasEventHandlers() const", asMETHODPR(Animation, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool ResourceWithMetadata::HasMetadata() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "bool HasMetadata() const", asMETHODPR(Animation, HasMetadata, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "bool get_hasMetadata() const", asMETHODPR(Animation, HasMetadata, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Animation, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Animation, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "bool IsInstanceOf(StringHash) const", asMETHODPR(Animation, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "bool Load(Deserializer&)", asMETHODPR(Animation, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "bool LoadFile(const String&in)", asMETHODPR(Animation, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "bool Load(const String&in)", asMETHODPR(Animation, LoadFile, (const String&), bool), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Animation, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Animation", "int Refs() const", asMETHODPR(Animation, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "int get_refs() const", asMETHODPR(Animation, Refs, () const, int), asCALL_THISCALL);
    // static void Animation::RegisterObject(Context* context) | File: ../Graphics/Animation.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Animation", asBEHAVE_RELEASE, "void f()", asMETHODPR(Animation, ReleaseRef, (), void), asCALL_THISCALL);
    // void ResourceWithMetadata::RemoveAllMetadata() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "void RemoveAllMetadata()", asMETHODPR(Animation, RemoveAllMetadata, (), void), asCALL_THISCALL);
    // void Animation::RemoveAllTracks() | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "void RemoveAllTracks()", asMETHODPR(Animation, RemoveAllTracks, (), void), asCALL_THISCALL);
    // void Animation::RemoveAllTriggers() | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "void RemoveAllTriggers()", asMETHODPR(Animation, RemoveAllTriggers, (), void), asCALL_THISCALL);
    // void ResourceWithMetadata::RemoveMetadata(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "void RemoveMetadata(const String&in)", asMETHODPR(Animation, RemoveMetadata, (const String&), void), asCALL_THISCALL);
    // bool Animation::RemoveTrack(const String& name) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "bool RemoveTrack(const String&in)", asMETHODPR(Animation, RemoveTrack, (const String&), bool), asCALL_THISCALL);
    // void Animation::RemoveTrigger(unsigned index) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "void RemoveTrigger(uint)", asMETHODPR(Animation, RemoveTrigger, (unsigned), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "void ResetUseTimer()", asMETHODPR(Animation, ResetUseTimer, (), void), asCALL_THISCALL);
    // bool Animation::Save(Serializer& dest) const override | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "bool Save(Serializer&) const", asMETHODPR(Animation, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "bool SaveFile(const String&in) const", asMETHODPR(Animation, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "bool Save(const String&in) const", asMETHODPR(Animation, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "void SendEvent(StringHash)", asMETHODPR(Animation, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Animation, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animation::SetAnimationName(const String& name) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "void SetAnimationName(const String&in)", asMETHODPR(Animation, SetAnimationName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "void set_animationName(const String&in)", asMETHODPR(Animation, SetAnimationName, (const String&), void), asCALL_THISCALL);
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(Animation, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "void SetBlockEvents(bool)", asMETHODPR(Animation, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Animation, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Animation, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Animation::SetLength(float length) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "void SetLength(float)", asMETHODPR(Animation, SetLength, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "void set_length(float)", asMETHODPR(Animation, SetLength, (float), void), asCALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "void SetMemoryUse(uint)", asMETHODPR(Animation, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Animation", "void SetName(const String&in)", asMETHODPR(Animation, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "void set_name(const String&in)", asMETHODPR(Animation, SetName, (const String&), void), asCALL_THISCALL);
    // void Animation::SetNumTriggers(unsigned num) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "void SetNumTriggers(uint)", asMETHODPR(Animation, SetNumTriggers, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "void set_numTriggers(uint)", asMETHODPR(Animation, SetNumTriggers, (unsigned), void), asCALL_THISCALL);
    // void Animation::SetTrigger(unsigned index, const AnimationTriggerPoint& trigger) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("Animation", "void SetTrigger(uint, const AnimationTriggerPoint&in)", asMETHODPR(Animation, SetTrigger, (unsigned, const AnimationTriggerPoint&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "void set_triggers(uint, const AnimationTriggerPoint&in)", asMETHODPR(Animation, SetTrigger, (unsigned, const AnimationTriggerPoint&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "void UnsubscribeFromAllEvents()", asMETHODPR(Animation, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Animation_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Animation, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Animation, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Animation", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Animation, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Animation", "int WeakRefs() const", asMETHODPR(Animation, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation", "int get_weakRefs() const", asMETHODPR(Animation, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("AnimationController", asBEHAVE_ADDREF, "void f()", asMETHODPR(AnimationController, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "void AllocateNetworkState()", asMETHODPR(AnimationController, AllocateNetworkState, (), void), asCALL_THISCALL);
    // explicit AnimationController::AnimationController(Context* context) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectBehaviour("AnimationController", asBEHAVE_FACTORY, "AnimationController@+ f()", asFUNCTION(AnimationController_AnimationController_Context), asCALL_CDECL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "void ApplyAttributes()", asMETHODPR(AnimationController, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(AnimationController, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool AnimationController::Fade(const String& name, float targetWeight, float fadeTime) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool Fade(const String&in, float, float)", asMETHODPR(AnimationController, Fade, (const String&, float, float), bool), asCALL_THISCALL);
    // bool AnimationController::FadeOthers(const String& name, float targetWeight, float fadeTime) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool FadeOthers(const String&in, float, float)", asMETHODPR(AnimationController, FadeOthers, (const String&, float, float), bool), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "bool GetAnimationEnabled() const", asMETHODPR(AnimationController, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool get_animationEnabled() const", asMETHODPR(AnimationController, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // const Vector<AnimationControl>& AnimationController::GetAnimations() const | File: ../Graphics/AnimationController.h
    // Error: type "const Vector<AnimationControl>&" can not automatically bind
    // VariantVector AnimationController::GetAnimationsAttr() const | File: ../Graphics/AnimationController.h
    // Error: type "VariantVector" can not automatically bind
    // AnimationState* AnimationController::GetAnimationState(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "AnimationState@+ GetAnimationState(const String&in) const", asMETHODPR(AnimationController, GetAnimationState, (const String&) const, AnimationState*), asCALL_THISCALL);
    // AnimationState* AnimationController::GetAnimationState(StringHash nameHash) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "AnimationState@+ GetAnimationState(StringHash) const", asMETHODPR(AnimationController, GetAnimationState, (StringHash) const, AnimationState*), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "Variant GetAttribute(uint) const", asMETHODPR(AnimationController, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "Variant get_attributes(uint) const", asMETHODPR(AnimationController, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "Variant GetAttribute(const String&in) const", asMETHODPR(AnimationController, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(AnimationController, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(AnimationController, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(AnimationController, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(AnimationController, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "Variant GetAttributeDefault(uint) const", asMETHODPR(AnimationController, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "Variant get_attributeDefaults(uint) const", asMETHODPR(AnimationController, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(AnimationController, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // float AnimationController::GetAutoFade(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "float GetAutoFade(const String&in) const", asMETHODPR(AnimationController, GetAutoFade, (const String&) const, float), asCALL_THISCALL);
    // AnimationBlendMode AnimationController::GetBlendMode(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "AnimationBlendMode GetBlendMode(const String&in) const", asMETHODPR(AnimationController, GetBlendMode, (const String&) const, AnimationBlendMode), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "bool GetBlockEvents() const", asMETHODPR(AnimationController, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "const String& GetCategory() const", asMETHODPR(AnimationController, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "const String& get_category() const", asMETHODPR(AnimationController, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "Component@+ GetComponent(StringHash) const", asMETHODPR(AnimationController, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("AnimationController", "VariantMap& GetEventDataMap() const", asMETHODPR(AnimationController, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "Object@+ GetEventSender() const", asMETHODPR(AnimationController, GetEventSender, () const, Object*), asCALL_THISCALL);
    // float AnimationController::GetFadeTarget(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "float GetFadeTarget(const String&in) const", asMETHODPR(AnimationController, GetFadeTarget, (const String&) const, float), asCALL_THISCALL);
    // float AnimationController::GetFadeTime(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "float GetFadeTime(const String&in) const", asMETHODPR(AnimationController, GetFadeTime, (const String&) const, float), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(AnimationController, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "const Variant& get_globalVar(StringHash) const", asMETHODPR(AnimationController, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "const VariantMap& GetGlobalVars() const", asMETHODPR(AnimationController, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "const VariantMap& get_globalVars() const", asMETHODPR(AnimationController, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "uint GetID() const", asMETHODPR(AnimationController, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "uint get_id() const", asMETHODPR(AnimationController, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(AnimationController, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // unsigned char AnimationController::GetLayer(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "uint8 GetLayer(const String&in) const", asMETHODPR(AnimationController, GetLayer, (const String&) const, unsigned char), asCALL_THISCALL);
    // float AnimationController::GetLength(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "float GetLength(const String&in) const", asMETHODPR(AnimationController, GetLength, (const String&) const, float), asCALL_THISCALL);
    // const PODVector<unsigned char>& AnimationController::GetNetAnimationsAttr() const | File: ../Graphics/AnimationController.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "Node@+ GetNode() const", asMETHODPR(AnimationController, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "Node@+ get_node() const", asMETHODPR(AnimationController, GetNode, () const, Node*), asCALL_THISCALL);
    // VariantVector AnimationController::GetNodeAnimationStatesAttr() const | File: ../Graphics/AnimationController.h
    // Error: type "VariantVector" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "uint GetNumAttributes() const", asMETHODPR(AnimationController, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "uint get_numAttributes() const", asMETHODPR(AnimationController, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "uint GetNumNetworkAttributes() const", asMETHODPR(AnimationController, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(AnimationController, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(AnimationController, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(AnimationController, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // bool AnimationController::GetRemoveOnCompletion(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool GetRemoveOnCompletion(const String&in) const", asMETHODPR(AnimationController, GetRemoveOnCompletion, (const String&) const, bool), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "Scene@+ GetScene() const", asMETHODPR(AnimationController, GetScene, () const, Scene*), asCALL_THISCALL);
    // float AnimationController::GetSpeed(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "float GetSpeed(const String&in) const", asMETHODPR(AnimationController, GetSpeed, (const String&) const, float), asCALL_THISCALL);
    // Bone* AnimationController::GetStartBone(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "Bone@+ GetStartBone(const String&in) const", asMETHODPR(AnimationController, GetStartBone, (const String&) const, Bone*), asCALL_THISCALL);
    // const String& AnimationController::GetStartBoneName(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "const String& GetStartBoneName(const String&in) const", asMETHODPR(AnimationController, GetStartBoneName, (const String&) const, const String&), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(AnimationController, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // float AnimationController::GetTime(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "float GetTime(const String&in) const", asMETHODPR(AnimationController, GetTime, (const String&) const, float), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "StringHash GetType() const", asMETHODPR(AnimationController, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "StringHash get_type() const", asMETHODPR(AnimationController, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "const String& GetTypeName() const", asMETHODPR(AnimationController, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "const String& get_typeName() const", asMETHODPR(AnimationController, GetTypeName, () const, const String&), asCALL_THISCALL);
    // float AnimationController::GetWeight(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "float GetWeight(const String&in) const", asMETHODPR(AnimationController, GetWeight, (const String&) const, float), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "bool HasEventHandlers() const", asMETHODPR(AnimationController, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(AnimationController, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(AnimationController, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool AnimationController::IsAtEnd(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool IsAtEnd(const String&in) const", asMETHODPR(AnimationController, IsAtEnd, (const String&) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "bool IsEnabled() const", asMETHODPR(AnimationController, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool get_enabled() const", asMETHODPR(AnimationController, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "bool IsEnabledEffective() const", asMETHODPR(AnimationController, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool get_enabledEffective() const", asMETHODPR(AnimationController, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool AnimationController::IsFadingIn(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool IsFadingIn(const String&in) const", asMETHODPR(AnimationController, IsFadingIn, (const String&) const, bool), asCALL_THISCALL);
    // bool AnimationController::IsFadingOut(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool IsFadingOut(const String&in) const", asMETHODPR(AnimationController, IsFadingOut, (const String&) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "bool IsInstanceOf(StringHash) const", asMETHODPR(AnimationController, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool AnimationController::IsLooped(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool IsLooped(const String&in) const", asMETHODPR(AnimationController, IsLooped, (const String&) const, bool), asCALL_THISCALL);
    // bool AnimationController::IsPlaying(const String& name) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool IsPlaying(const String&in) const", asMETHODPR(AnimationController, IsPlaying, (const String&) const, bool), asCALL_THISCALL);
    // bool AnimationController::IsPlaying(unsigned char layer) const | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool IsPlaying(uint8) const", asMETHODPR(AnimationController, IsPlaying, (unsigned char) const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "bool IsReplicated() const", asMETHODPR(AnimationController, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool get_replicated() const", asMETHODPR(AnimationController, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "bool IsTemporary() const", asMETHODPR(AnimationController, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool get_temporary() const", asMETHODPR(AnimationController, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "bool Load(Deserializer&)", asMETHODPR(AnimationController, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "bool LoadJSON(const JSONValue&in)", asMETHODPR(AnimationController, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "bool LoadXML(const XMLElement&in)", asMETHODPR(AnimationController, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "void MarkNetworkUpdate()", asMETHODPR(AnimationController, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(AnimationController, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(AnimationController, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(AnimationController, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void AnimationController::OnSetEnabled() override | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "void OnSetEnabled()", asMETHODPR(AnimationController, OnSetEnabled, (), void), asCALL_THISCALL);
    // bool AnimationController::Play(const String& name, unsigned char layer, bool looped, float fadeInTime=0.0f) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool Play(const String&in, uint8, bool, float = 0.0f)", asMETHODPR(AnimationController, Play, (const String&, unsigned char, bool, float), bool), asCALL_THISCALL);
    // bool AnimationController::PlayExclusive(const String& name, unsigned char layer, bool looped, float fadeTime=0.0f) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool PlayExclusive(const String&in, uint8, bool, float = 0.0f)", asMETHODPR(AnimationController, PlayExclusive, (const String&, unsigned char, bool, float), bool), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "void PrepareNetworkUpdate()", asMETHODPR(AnimationController, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(AnimationController, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(AnimationController, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AnimationController", "int Refs() const", asMETHODPR(AnimationController, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "int get_refs() const", asMETHODPR(AnimationController, Refs, () const, int), asCALL_THISCALL);
    // static void AnimationController::RegisterObject(Context* context) | File: ../Graphics/AnimationController.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("AnimationController", asBEHAVE_RELEASE, "void f()", asMETHODPR(AnimationController, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "void Remove()", asMETHODPR(AnimationController, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(AnimationController, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "void RemoveInstanceDefault()", asMETHODPR(AnimationController, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "void RemoveObjectAnimation()", asMETHODPR(AnimationController, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "void ResetToDefault()", asMETHODPR(AnimationController, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "bool Save(Serializer&) const", asMETHODPR(AnimationController, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "bool SaveDefaultAttributes() const", asMETHODPR(AnimationController, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "bool SaveJSON(JSONValue&) const", asMETHODPR(AnimationController, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "bool SaveXML(XMLElement&) const", asMETHODPR(AnimationController, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "void SendEvent(StringHash)", asMETHODPR(AnimationController, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(AnimationController, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "void SetAnimationEnabled(bool)", asMETHODPR(AnimationController, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "void set_animationEnabled(bool)", asMETHODPR(AnimationController, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void AnimationController::SetAnimationsAttr(const VariantVector& value) | File: ../Graphics/AnimationController.h
    // Error: type "const VariantVector&" can not automatically bind
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "void SetAnimationTime(float)", asMETHODPR(AnimationController, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(AnimationController, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "bool set_attributes(uint, const Variant&in)", asMETHODPR(AnimationController, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(AnimationController, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(AnimationController, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(AnimationController, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(AnimationController, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(AnimationController, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // bool AnimationController::SetAutoFade(const String& name, float fadeOutTime) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool SetAutoFade(const String&in, float)", asMETHODPR(AnimationController, SetAutoFade, (const String&, float), bool), asCALL_THISCALL);
    // bool AnimationController::SetBlendMode(const String& name, AnimationBlendMode mode) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool SetBlendMode(const String&in, AnimationBlendMode)", asMETHODPR(AnimationController, SetBlendMode, (const String&, AnimationBlendMode), bool), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "void SetBlockEvents(bool)", asMETHODPR(AnimationController, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("AnimationController", "void SetEnabled(bool)", asMETHODPR(AnimationController, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "void set_enabled(bool)", asMETHODPR(AnimationController, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(AnimationController, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(AnimationController, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "void SetInstanceDefault(bool)", asMETHODPR(AnimationController, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(AnimationController, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // bool AnimationController::SetLayer(const String& name, unsigned char layer) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool SetLayer(const String&in, uint8)", asMETHODPR(AnimationController, SetLayer, (const String&, unsigned char), bool), asCALL_THISCALL);
    // bool AnimationController::SetLooped(const String& name, bool enable) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool SetLooped(const String&in, bool)", asMETHODPR(AnimationController, SetLooped, (const String&, bool), bool), asCALL_THISCALL);
    // void AnimationController::SetNetAnimationsAttr(const PODVector<unsigned char>& value) | File: ../Graphics/AnimationController.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void AnimationController::SetNodeAnimationStatesAttr(const VariantVector& value) | File: ../Graphics/AnimationController.h
    // Error: type "const VariantVector&" can not automatically bind
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(AnimationController, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(AnimationController, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AnimationController", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(AnimationController, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // bool AnimationController::SetRemoveOnCompletion(const String& name, bool removeOnCompletion) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool SetRemoveOnCompletion(const String&in, bool)", asMETHODPR(AnimationController, SetRemoveOnCompletion, (const String&, bool), bool), asCALL_THISCALL);
    // bool AnimationController::SetSpeed(const String& name, float speed) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool SetSpeed(const String&in, float)", asMETHODPR(AnimationController, SetSpeed, (const String&, float), bool), asCALL_THISCALL);
    // bool AnimationController::SetStartBone(const String& name, const String& startBoneName) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool SetStartBone(const String&in, const String&in)", asMETHODPR(AnimationController, SetStartBone, (const String&, const String&), bool), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "void SetTemporary(bool)", asMETHODPR(AnimationController, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "void set_temporary(bool)", asMETHODPR(AnimationController, SetTemporary, (bool), void), asCALL_THISCALL);
    // bool AnimationController::SetTime(const String& name, float time) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool SetTime(const String&in, float)", asMETHODPR(AnimationController, SetTime, (const String&, float), bool), asCALL_THISCALL);
    // bool AnimationController::SetWeight(const String& name, float weight) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool SetWeight(const String&in, float)", asMETHODPR(AnimationController, SetWeight, (const String&, float), bool), asCALL_THISCALL);
    // bool AnimationController::Stop(const String& name, float fadeOutTime=0.0f) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "bool Stop(const String&in, float = 0.0f)", asMETHODPR(AnimationController, Stop, (const String&, float), bool), asCALL_THISCALL);
    // void AnimationController::StopAll(float fadeOutTime=0.0f) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "void StopAll(float = 0.0f)", asMETHODPR(AnimationController, StopAll, (float), void), asCALL_THISCALL);
    // void AnimationController::StopLayer(unsigned char layer, float fadeOutTime=0.0f) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "void StopLayer(uint8, float = 0.0f)", asMETHODPR(AnimationController, StopLayer, (unsigned char, float), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "void UnsubscribeFromAllEvents()", asMETHODPR(AnimationController, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(AnimationController_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(AnimationController, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(AnimationController, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationController", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(AnimationController, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void AnimationController::Update(float timeStep) | File: ../Graphics/AnimationController.h
    engine->RegisterObjectMethod("AnimationController", "void Update(float)", asMETHODPR(AnimationController, Update, (float), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AnimationController", "int WeakRefs() const", asMETHODPR(AnimationController, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationController", "int get_weakRefs() const", asMETHODPR(AnimationController, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(AnimationController, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(AnimationController, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("AnimationController", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(AnimationController, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("AnimationSet2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(AnimationSet2D, AddRef, (), void), asCALL_THISCALL);
    // explicit AnimationSet2D::AnimationSet2D(Context* context) | File: ../Urho2D/AnimationSet2D.h
    engine->RegisterObjectBehaviour("AnimationSet2D", asBEHAVE_FACTORY, "AnimationSet2D@+ f()", asFUNCTION(AnimationSet2D_AnimationSet2D_Context), asCALL_CDECL);
    // bool AnimationSet2D::BeginLoad(Deserializer& source) override | File: ../Urho2D/AnimationSet2D.h
    engine->RegisterObjectMethod("AnimationSet2D", "bool BeginLoad(Deserializer&)", asMETHODPR(AnimationSet2D, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool AnimationSet2D::EndLoad() override | File: ../Urho2D/AnimationSet2D.h
    engine->RegisterObjectMethod("AnimationSet2D", "bool EndLoad()", asMETHODPR(AnimationSet2D, EndLoad, (), bool), asCALL_THISCALL);
    // String AnimationSet2D::GetAnimation(unsigned index) const | File: ../Urho2D/AnimationSet2D.h
    engine->RegisterObjectMethod("AnimationSet2D", "String GetAnimation(uint) const", asMETHODPR(AnimationSet2D, GetAnimation, (unsigned) const, String), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(AnimationSet2D, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "bool GetBlockEvents() const", asMETHODPR(AnimationSet2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "const String& GetCategory() const", asMETHODPR(AnimationSet2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "const String& get_category() const", asMETHODPR(AnimationSet2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "VariantMap& GetEventDataMap() const", asMETHODPR(AnimationSet2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "Object@+ GetEventSender() const", asMETHODPR(AnimationSet2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(AnimationSet2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(AnimationSet2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(AnimationSet2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "const VariantMap& get_globalVars() const", asMETHODPR(AnimationSet2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "uint GetMemoryUse() const", asMETHODPR(AnimationSet2D, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "uint get_memoryUse() const", asMETHODPR(AnimationSet2D, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "const String& GetName() const", asMETHODPR(AnimationSet2D, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "const String& get_name() const", asMETHODPR(AnimationSet2D, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "StringHash GetNameHash() const", asMETHODPR(AnimationSet2D, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // unsigned AnimationSet2D::GetNumAnimations() const | File: ../Urho2D/AnimationSet2D.h
    engine->RegisterObjectMethod("AnimationSet2D", "uint GetNumAnimations() const", asMETHODPR(AnimationSet2D, GetNumAnimations, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "uint get_numAnimations() const", asMETHODPR(AnimationSet2D, GetNumAnimations, () const, unsigned), asCALL_THISCALL);
    // Sprite2D* AnimationSet2D::GetSprite() const | File: ../Urho2D/AnimationSet2D.h
    engine->RegisterObjectMethod("AnimationSet2D", "Sprite2D@+ GetSprite() const", asMETHODPR(AnimationSet2D, GetSprite, () const, Sprite2D*), asCALL_THISCALL);
    // Spriter::SpriterData* AnimationSet2D::GetSpriterData() const | File: ../Urho2D/AnimationSet2D.h
    // Error: type "Spriter::SpriterData*" can not automatically bind
    // Sprite2D* AnimationSet2D::GetSpriterFileSprite(int folderId, int fileId) const | File: ../Urho2D/AnimationSet2D.h
    engine->RegisterObjectMethod("AnimationSet2D", "Sprite2D@+ GetSpriterFileSprite(int, int) const", asMETHODPR(AnimationSet2D, GetSpriterFileSprite, (int, int) const, Sprite2D*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(AnimationSet2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "StringHash GetType() const", asMETHODPR(AnimationSet2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "StringHash get_type() const", asMETHODPR(AnimationSet2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "const String& GetTypeName() const", asMETHODPR(AnimationSet2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "const String& get_typeName() const", asMETHODPR(AnimationSet2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "uint GetUseTimer()", asMETHODPR(AnimationSet2D, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "uint get_useTimer()", asMETHODPR(AnimationSet2D, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // bool AnimationSet2D::HasAnimation(const String& animationName) const | File: ../Urho2D/AnimationSet2D.h
    engine->RegisterObjectMethod("AnimationSet2D", "bool HasAnimation(const String&in) const", asMETHODPR(AnimationSet2D, HasAnimation, (const String&) const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "bool HasEventHandlers() const", asMETHODPR(AnimationSet2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(AnimationSet2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(AnimationSet2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(AnimationSet2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "bool Load(Deserializer&)", asMETHODPR(AnimationSet2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "bool LoadFile(const String&in)", asMETHODPR(AnimationSet2D, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "bool Load(const String&in)", asMETHODPR(AnimationSet2D, LoadFile, (const String&), bool), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(AnimationSet2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AnimationSet2D", "int Refs() const", asMETHODPR(AnimationSet2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "int get_refs() const", asMETHODPR(AnimationSet2D, Refs, () const, int), asCALL_THISCALL);
    // static void AnimationSet2D::RegisterObject(Context* context) | File: ../Urho2D/AnimationSet2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("AnimationSet2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(AnimationSet2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "void ResetUseTimer()", asMETHODPR(AnimationSet2D, ResetUseTimer, (), void), asCALL_THISCALL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "bool Save(Serializer&) const", asMETHODPR(AnimationSet2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "bool SaveFile(const String&in) const", asMETHODPR(AnimationSet2D, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "bool Save(const String&in) const", asMETHODPR(AnimationSet2D, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "void SendEvent(StringHash)", asMETHODPR(AnimationSet2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(AnimationSet2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(AnimationSet2D, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "void SetBlockEvents(bool)", asMETHODPR(AnimationSet2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(AnimationSet2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(AnimationSet2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "void SetMemoryUse(uint)", asMETHODPR(AnimationSet2D, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("AnimationSet2D", "void SetName(const String&in)", asMETHODPR(AnimationSet2D, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "void set_name(const String&in)", asMETHODPR(AnimationSet2D, SetName, (const String&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "void UnsubscribeFromAllEvents()", asMETHODPR(AnimationSet2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(AnimationSet2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(AnimationSet2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(AnimationSet2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("AnimationSet2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(AnimationSet2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AnimationSet2D", "int WeakRefs() const", asMETHODPR(AnimationSet2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "int get_weakRefs() const", asMETHODPR(AnimationSet2D, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("AnimationState", asBEHAVE_ADDREF, "void f()", asMETHODPR(AnimationState, AddRef, (), void), asCALL_THISCALL);
    // void AnimationState::AddTime(float delta) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "void AddTime(float)", asMETHODPR(AnimationState, AddTime, (float), void), asCALL_THISCALL);
    // void AnimationState::AddWeight(float delta) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "void AddWeight(float)", asMETHODPR(AnimationState, AddWeight, (float), void), asCALL_THISCALL);
    // AnimationState::AnimationState(AnimatedModel* model, Animation* animation) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectBehaviour("AnimationState", asBEHAVE_FACTORY, "AnimationState@+ f(AnimatedModel@+, Animation@+)", asFUNCTION(AnimationState_AnimationState_AnimatedModel_Animation), asCALL_CDECL);
    // AnimationState::AnimationState(Node* node, Animation* animation) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectBehaviour("AnimationState", asBEHAVE_FACTORY, "AnimationState@+ f(Node@+, Animation@+)", asFUNCTION(AnimationState_AnimationState_Node_Animation), asCALL_CDECL);
    // void AnimationState::Apply() | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "void Apply()", asMETHODPR(AnimationState, Apply, (), void), asCALL_THISCALL);
    // Animation* AnimationState::GetAnimation() const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "Animation@+ GetAnimation() const", asMETHODPR(AnimationState, GetAnimation, () const, Animation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "Animation@+ get_animation() const", asMETHODPR(AnimationState, GetAnimation, () const, Animation*), asCALL_THISCALL);
    // AnimationBlendMode AnimationState::GetBlendMode() const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "AnimationBlendMode GetBlendMode() const", asMETHODPR(AnimationState, GetBlendMode, () const, AnimationBlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "AnimationBlendMode get_blendMode() const", asMETHODPR(AnimationState, GetBlendMode, () const, AnimationBlendMode), asCALL_THISCALL);
    // float AnimationState::GetBoneWeight(unsigned index) const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "float GetBoneWeight(uint) const", asMETHODPR(AnimationState, GetBoneWeight, (unsigned) const, float), asCALL_THISCALL);
    // float AnimationState::GetBoneWeight(const String& name) const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "float GetBoneWeight(const String&in) const", asMETHODPR(AnimationState, GetBoneWeight, (const String&) const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "float get_boneWeights(const String&in) const", asMETHODPR(AnimationState, GetBoneWeight, (const String&) const, float), asCALL_THISCALL);
    // float AnimationState::GetBoneWeight(StringHash nameHash) const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "float GetBoneWeight(StringHash) const", asMETHODPR(AnimationState, GetBoneWeight, (StringHash) const, float), asCALL_THISCALL);
    // unsigned char AnimationState::GetLayer() const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "uint8 GetLayer() const", asMETHODPR(AnimationState, GetLayer, () const, unsigned char), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "uint8 get_layer() const", asMETHODPR(AnimationState, GetLayer, () const, unsigned char), asCALL_THISCALL);
    // float AnimationState::GetLength() const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "float GetLength() const", asMETHODPR(AnimationState, GetLength, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "float get_length() const", asMETHODPR(AnimationState, GetLength, () const, float), asCALL_THISCALL);
    // AnimatedModel* AnimationState::GetModel() const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "AnimatedModel@+ GetModel() const", asMETHODPR(AnimationState, GetModel, () const, AnimatedModel*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "AnimatedModel@+ get_model() const", asMETHODPR(AnimationState, GetModel, () const, AnimatedModel*), asCALL_THISCALL);
    // Node* AnimationState::GetNode() const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "Node@+ GetNode() const", asMETHODPR(AnimationState, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "Node@+ get_node() const", asMETHODPR(AnimationState, GetNode, () const, Node*), asCALL_THISCALL);
    // Bone* AnimationState::GetStartBone() const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "Bone@+ GetStartBone() const", asMETHODPR(AnimationState, GetStartBone, () const, Bone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "Bone@+ get_startBone() const", asMETHODPR(AnimationState, GetStartBone, () const, Bone*), asCALL_THISCALL);
    // float AnimationState::GetTime() const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "float GetTime() const", asMETHODPR(AnimationState, GetTime, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "float get_time() const", asMETHODPR(AnimationState, GetTime, () const, float), asCALL_THISCALL);
    // unsigned AnimationState::GetTrackIndex(Node* node) const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "uint GetTrackIndex(Node@+) const", asMETHODPR(AnimationState, GetTrackIndex, (Node*) const, unsigned), asCALL_THISCALL);
    // unsigned AnimationState::GetTrackIndex(const String& name) const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "uint GetTrackIndex(const String&in) const", asMETHODPR(AnimationState, GetTrackIndex, (const String&) const, unsigned), asCALL_THISCALL);
    // unsigned AnimationState::GetTrackIndex(StringHash nameHash) const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "uint GetTrackIndex(StringHash) const", asMETHODPR(AnimationState, GetTrackIndex, (StringHash) const, unsigned), asCALL_THISCALL);
    // float AnimationState::GetWeight() const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "float GetWeight() const", asMETHODPR(AnimationState, GetWeight, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "float get_weight() const", asMETHODPR(AnimationState, GetWeight, () const, float), asCALL_THISCALL);
    // bool AnimationState::IsEnabled() const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "bool IsEnabled() const", asMETHODPR(AnimationState, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "bool get_enabled() const", asMETHODPR(AnimationState, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool AnimationState::IsLooped() const | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "bool IsLooped() const", asMETHODPR(AnimationState, IsLooped, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "bool get_looped() const", asMETHODPR(AnimationState, IsLooped, () const, bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AnimationState", "int Refs() const", asMETHODPR(AnimationState, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "int get_refs() const", asMETHODPR(AnimationState, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("AnimationState", asBEHAVE_RELEASE, "void f()", asMETHODPR(AnimationState, ReleaseRef, (), void), asCALL_THISCALL);
    // void AnimationState::SetBlendMode(AnimationBlendMode mode) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "void SetBlendMode(AnimationBlendMode)", asMETHODPR(AnimationState, SetBlendMode, (AnimationBlendMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void set_blendMode(AnimationBlendMode)", asMETHODPR(AnimationState, SetBlendMode, (AnimationBlendMode), void), asCALL_THISCALL);
    // void AnimationState::SetBoneWeight(unsigned index, float weight, bool recursive=false) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "void SetBoneWeight(uint, float, bool = false)", asMETHODPR(AnimationState, SetBoneWeight, (unsigned, float, bool), void), asCALL_THISCALL);
    // void AnimationState::SetBoneWeight(const String& name, float weight, bool recursive=false) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "void SetBoneWeight(const String&in, float, bool = false)", asMETHODPR(AnimationState, SetBoneWeight, (const String&, float, bool), void), asCALL_THISCALL);
    // void AnimationState::SetBoneWeight(StringHash nameHash, float weight, bool recursive=false) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "void SetBoneWeight(StringHash, float, bool = false)", asMETHODPR(AnimationState, SetBoneWeight, (StringHash, float, bool), void), asCALL_THISCALL);
    // void AnimationState::SetLayer(unsigned char layer) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "void SetLayer(uint8)", asMETHODPR(AnimationState, SetLayer, (unsigned char), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void set_layer(uint8)", asMETHODPR(AnimationState, SetLayer, (unsigned char), void), asCALL_THISCALL);
    // void AnimationState::SetLooped(bool looped) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "void SetLooped(bool)", asMETHODPR(AnimationState, SetLooped, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void set_looped(bool)", asMETHODPR(AnimationState, SetLooped, (bool), void), asCALL_THISCALL);
    // void AnimationState::SetStartBone(Bone* startBone) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "void SetStartBone(Bone@+)", asMETHODPR(AnimationState, SetStartBone, (Bone*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void set_startBone(Bone@+)", asMETHODPR(AnimationState, SetStartBone, (Bone*), void), asCALL_THISCALL);
    // void AnimationState::SetTime(float time) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "void SetTime(float)", asMETHODPR(AnimationState, SetTime, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void set_time(float)", asMETHODPR(AnimationState, SetTime, (float), void), asCALL_THISCALL);
    // void AnimationState::SetWeight(float weight) | File: ../Graphics/AnimationState.h
    engine->RegisterObjectMethod("AnimationState", "void SetWeight(float)", asMETHODPR(AnimationState, SetWeight, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "void set_weight(float)", asMETHODPR(AnimationState, SetWeight, (float), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AnimationState", "int WeakRefs() const", asMETHODPR(AnimationState, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationState", "int get_weakRefs() const", asMETHODPR(AnimationState, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(AnimationState, "AnimationState")
#endif
#ifdef REGISTER_MANUAL_PART_AnimationState
    REGISTER_MANUAL_PART_AnimationState(AnimationState, "AnimationState")
#endif
    RegisterSubclass<RefCounted, AnimationState>(engine, "RefCounted", "AnimationState");

    // bool AreaAllocator::Allocate(int width, int height, int& x, int& y) | File: ../Math/AreaAllocator.h
    engine->RegisterObjectMethod("AreaAllocator", "bool Allocate(int, int, int&, int&)", asMETHODPR(AreaAllocator, Allocate, (int, int, int&, int&), bool), asCALL_THISCALL);
    // AreaAllocator::AreaAllocator(int width, int height, bool fastMode=true) | File: ../Math/AreaAllocator.h
    engine->RegisterObjectBehaviour("AreaAllocator", asBEHAVE_CONSTRUCT, "void f(int, int, bool = true)", asFUNCTION(AreaAllocator_AreaAllocator_int_int_bool), asCALL_CDECL_OBJFIRST);
    // AreaAllocator::AreaAllocator(int width, int height, int maxWidth, int maxHeight, bool fastMode=true) | File: ../Math/AreaAllocator.h
    engine->RegisterObjectBehaviour("AreaAllocator", asBEHAVE_CONSTRUCT, "void f(int, int, int, int, bool = true)", asFUNCTION(AreaAllocator_AreaAllocator_int_int_int_int_bool), asCALL_CDECL_OBJFIRST);
    // bool AreaAllocator::GetFastMode() const | File: ../Math/AreaAllocator.h
    engine->RegisterObjectMethod("AreaAllocator", "bool GetFastMode() const", asMETHODPR(AreaAllocator, GetFastMode, () const, bool), asCALL_THISCALL);
    // int AreaAllocator::GetHeight() const | File: ../Math/AreaAllocator.h
    engine->RegisterObjectMethod("AreaAllocator", "int GetHeight() const", asMETHODPR(AreaAllocator, GetHeight, () const, int), asCALL_THISCALL);
    // int AreaAllocator::GetWidth() const | File: ../Math/AreaAllocator.h
    engine->RegisterObjectMethod("AreaAllocator", "int GetWidth() const", asMETHODPR(AreaAllocator, GetWidth, () const, int), asCALL_THISCALL);
    // void AreaAllocator::Reset(int width, int height, int maxWidth=0, int maxHeight=0, bool fastMode=true) | File: ../Math/AreaAllocator.h
    engine->RegisterObjectMethod("AreaAllocator", "void Reset(int, int, int = 0, int = 0, bool = true)", asMETHODPR(AreaAllocator, Reset, (int, int, int, int, bool), void), asCALL_THISCALL);
    // AreaAllocator& AreaAllocator::operator=(const AreaAllocator&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AreaAllocator>(engine, "AreaAllocator");
#ifdef REGISTER_MANUAL_PART_AreaAllocator
    REGISTER_MANUAL_PART_AreaAllocator(AreaAllocator, "AreaAllocator")
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("AttributeAccessor", asBEHAVE_ADDREF, "void f()", asMETHODPR(AttributeAccessor, AddRef, (), void), asCALL_THISCALL);
    // virtual void AttributeAccessor::Get(const Serializable* ptr, Variant& dest) const =0 | File: ../Core/Attribute.h
    engine->RegisterObjectMethod("AttributeAccessor", "void Get(Serializable@+, Variant&) const", asMETHODPR(AttributeAccessor, Get, (const Serializable*, Variant&) const, void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AttributeAccessor", "int Refs() const", asMETHODPR(AttributeAccessor, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("AttributeAccessor", "int get_refs() const", asMETHODPR(AttributeAccessor, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("AttributeAccessor", asBEHAVE_RELEASE, "void f()", asMETHODPR(AttributeAccessor, ReleaseRef, (), void), asCALL_THISCALL);
    // virtual void AttributeAccessor::Set(Serializable* ptr, const Variant& src)=0 | File: ../Core/Attribute.h
    engine->RegisterObjectMethod("AttributeAccessor", "void Set(Serializable@+, const Variant&in)", asMETHODPR(AttributeAccessor, Set, (Serializable*, const Variant&), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AttributeAccessor", "int WeakRefs() const", asMETHODPR(AttributeAccessor, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("AttributeAccessor", "int get_weakRefs() const", asMETHODPR(AttributeAccessor, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(AttributeAccessor, "AttributeAccessor")
#endif
#ifdef REGISTER_MANUAL_PART_AttributeAccessor
    REGISTER_MANUAL_PART_AttributeAccessor(AttributeAccessor, "AttributeAccessor")
#endif
    RegisterSubclass<RefCounted, AttributeAccessor>(engine, "RefCounted", "AttributeAccessor");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("AttributeAnimationInfo", asBEHAVE_ADDREF, "void f()", asMETHODPR(AttributeAnimationInfo, AddRef, (), void), asCALL_THISCALL);
    // AttributeAnimationInfo::AttributeAnimationInfo(Animatable* animatable, const AttributeInfo& attributeInfo, ValueAnimation* attributeAnimation, WrapMode wrapMode, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectBehaviour("AttributeAnimationInfo", asBEHAVE_FACTORY, "AttributeAnimationInfo@+ f(Animatable@+, const AttributeInfo&in, ValueAnimation@+, WrapMode, float)", asFUNCTION(AttributeAnimationInfo_AttributeAnimationInfo_Animatable_AttributeInfo_ValueAnimation_WrapMode_float), asCALL_CDECL);
    // AttributeAnimationInfo::AttributeAnimationInfo(const AttributeAnimationInfo& other) | File: ../Scene/Animatable.h
    engine->RegisterObjectBehaviour("AttributeAnimationInfo", asBEHAVE_FACTORY, "AttributeAnimationInfo@+ f(const AttributeAnimationInfo&in)", asFUNCTION(AttributeAnimationInfo_AttributeAnimationInfo_AttributeAnimationInfo), asCALL_CDECL);
    // ValueAnimation* ValueAnimationInfo::GetAnimation() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("AttributeAnimationInfo", "ValueAnimation@+ GetAnimation() const", asMETHODPR(AttributeAnimationInfo, GetAnimation, () const, ValueAnimation*), asCALL_THISCALL);
    // const AttributeInfo& AttributeAnimationInfo::GetAttributeInfo() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("AttributeAnimationInfo", "const AttributeInfo& GetAttributeInfo() const", asMETHODPR(AttributeAnimationInfo, GetAttributeInfo, () const, const AttributeInfo&), asCALL_THISCALL);
    // float ValueAnimationInfo::GetSpeed() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("AttributeAnimationInfo", "float GetSpeed() const", asMETHODPR(AttributeAnimationInfo, GetSpeed, () const, float), asCALL_THISCALL);
    // Object* ValueAnimationInfo::GetTarget() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("AttributeAnimationInfo", "Object@+ GetTarget() const", asMETHODPR(AttributeAnimationInfo, GetTarget, () const, Object*), asCALL_THISCALL);
    // float ValueAnimationInfo::GetTime() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("AttributeAnimationInfo", "float GetTime() const", asMETHODPR(AttributeAnimationInfo, GetTime, () const, float), asCALL_THISCALL);
    // WrapMode ValueAnimationInfo::GetWrapMode() const | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("AttributeAnimationInfo", "WrapMode GetWrapMode() const", asMETHODPR(AttributeAnimationInfo, GetWrapMode, () const, WrapMode), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AttributeAnimationInfo", "int Refs() const", asMETHODPR(AttributeAnimationInfo, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("AttributeAnimationInfo", "int get_refs() const", asMETHODPR(AttributeAnimationInfo, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("AttributeAnimationInfo", asBEHAVE_RELEASE, "void f()", asMETHODPR(AttributeAnimationInfo, ReleaseRef, (), void), asCALL_THISCALL);
    // void ValueAnimationInfo::SetSpeed(float speed) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("AttributeAnimationInfo", "void SetSpeed(float)", asMETHODPR(AttributeAnimationInfo, SetSpeed, (float), void), asCALL_THISCALL);
    // bool ValueAnimationInfo::SetTime(float time) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("AttributeAnimationInfo", "bool SetTime(float)", asMETHODPR(AttributeAnimationInfo, SetTime, (float), bool), asCALL_THISCALL);
    // void ValueAnimationInfo::SetWrapMode(WrapMode wrapMode) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("AttributeAnimationInfo", "void SetWrapMode(WrapMode)", asMETHODPR(AttributeAnimationInfo, SetWrapMode, (WrapMode), void), asCALL_THISCALL);
    // bool ValueAnimationInfo::Update(float timeStep) | File: ../Scene/ValueAnimationInfo.h
    engine->RegisterObjectMethod("AttributeAnimationInfo", "bool Update(float)", asMETHODPR(AttributeAnimationInfo, Update, (float), bool), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("AttributeAnimationInfo", "int WeakRefs() const", asMETHODPR(AttributeAnimationInfo, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("AttributeAnimationInfo", "int get_weakRefs() const", asMETHODPR(AttributeAnimationInfo, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("Audio", asBEHAVE_ADDREF, "void f()", asMETHODPR(Audio, AddRef, (), void), asCALL_THISCALL);
    // void Audio::AddSoundSource(SoundSource* soundSource) | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "void AddSoundSource(SoundSource@+)", asMETHODPR(Audio, AddSoundSource, (SoundSource*), void), asCALL_THISCALL);
    // explicit Audio::Audio(Context* context) | File: ../Audio/Audio.h
    engine->RegisterObjectBehaviour("Audio", asBEHAVE_FACTORY, "Audio@+ f()", asFUNCTION(Audio_Audio_Context), asCALL_CDECL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "bool GetBlockEvents() const", asMETHODPR(Audio, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "const String& GetCategory() const", asMETHODPR(Audio, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "const String& get_category() const", asMETHODPR(Audio, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "VariantMap& GetEventDataMap() const", asMETHODPR(Audio, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "Object@+ GetEventSender() const", asMETHODPR(Audio, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Audio, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Audio, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "const VariantMap& GetGlobalVars() const", asMETHODPR(Audio, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "const VariantMap& get_globalVars() const", asMETHODPR(Audio, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // bool Audio::GetInterpolation() const | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "bool GetInterpolation() const", asMETHODPR(Audio, GetInterpolation, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "bool get_interpolation() const", asMETHODPR(Audio, GetInterpolation, () const, bool), asCALL_THISCALL);
    // SoundListener* Audio::GetListener() const | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "SoundListener@+ GetListener() const", asMETHODPR(Audio, GetListener, () const, SoundListener*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "SoundListener@+ get_listener() const", asMETHODPR(Audio, GetListener, () const, SoundListener*), asCALL_THISCALL);
    // float Audio::GetMasterGain(const String& type) const | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "float GetMasterGain(const String&in) const", asMETHODPR(Audio, GetMasterGain, (const String&) const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "float get_masterGain(const String&in) const", asMETHODPR(Audio, GetMasterGain, (const String&) const, float), asCALL_THISCALL);
    // int Audio::GetMixRate() const | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "int GetMixRate() const", asMETHODPR(Audio, GetMixRate, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "int get_mixRate() const", asMETHODPR(Audio, GetMixRate, () const, int), asCALL_THISCALL);
    // Mutex& Audio::GetMutex() | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "Mutex& GetMutex()", asMETHODPR(Audio, GetMutex, (), Mutex&), asCALL_THISCALL);
    // unsigned Audio::GetSampleSize() const | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "uint GetSampleSize() const", asMETHODPR(Audio, GetSampleSize, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "uint get_sampleSize() const", asMETHODPR(Audio, GetSampleSize, () const, unsigned), asCALL_THISCALL);
    // float Audio::GetSoundSourceMasterGain(StringHash typeHash) const | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "float GetSoundSourceMasterGain(StringHash) const", asMETHODPR(Audio, GetSoundSourceMasterGain, (StringHash) const, float), asCALL_THISCALL);
    // const PODVector<SoundSource*>& Audio::GetSoundSources() const | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "Array<SoundSource@>@ GetSoundSources() const", asFUNCTION(Audio_GetSoundSources_void), asCALL_CDECL_OBJFIRST);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Audio, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "StringHash GetType() const", asMETHODPR(Audio, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "StringHash get_type() const", asMETHODPR(Audio, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "const String& GetTypeName() const", asMETHODPR(Audio, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "const String& get_typeName() const", asMETHODPR(Audio, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "bool HasEventHandlers() const", asMETHODPR(Audio, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Audio::HasMasterGain(const String& type) const | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "bool HasMasterGain(const String&in) const", asMETHODPR(Audio, HasMasterGain, (const String&) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Audio, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Audio, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Audio::IsInitialized() const | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "bool IsInitialized() const", asMETHODPR(Audio, IsInitialized, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "bool get_initialized() const", asMETHODPR(Audio, IsInitialized, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "bool IsInstanceOf(StringHash) const", asMETHODPR(Audio, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Audio::IsPlaying() const | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "bool IsPlaying() const", asMETHODPR(Audio, IsPlaying, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "bool get_playing() const", asMETHODPR(Audio, IsPlaying, () const, bool), asCALL_THISCALL);
    // bool Audio::IsSoundTypePaused(const String& type) const | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "bool IsSoundTypePaused(const String&in) const", asMETHODPR(Audio, IsSoundTypePaused, (const String&) const, bool), asCALL_THISCALL);
    // bool Audio::IsStereo() const | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "bool IsStereo() const", asMETHODPR(Audio, IsStereo, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "bool get_stereo() const", asMETHODPR(Audio, IsStereo, () const, bool), asCALL_THISCALL);
    // void Audio::MixOutput(void* dest, unsigned samples) | File: ../Audio/Audio.h
    // Error: type "void*" can not automatically bind
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Audio, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // void Audio::PauseSoundType(const String& type) | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "void PauseSoundType(const String&in)", asMETHODPR(Audio, PauseSoundType, (const String&), void), asCALL_THISCALL);
    // bool Audio::Play() | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "bool Play()", asMETHODPR(Audio, Play, (), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Audio", "int Refs() const", asMETHODPR(Audio, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "int get_refs() const", asMETHODPR(Audio, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Audio", asBEHAVE_RELEASE, "void f()", asMETHODPR(Audio, ReleaseRef, (), void), asCALL_THISCALL);
    // void Audio::RemoveSoundSource(SoundSource* soundSource) | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "void RemoveSoundSource(SoundSource@+)", asMETHODPR(Audio, RemoveSoundSource, (SoundSource*), void), asCALL_THISCALL);
    // void Audio::ResumeAll() | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "void ResumeAll()", asMETHODPR(Audio, ResumeAll, (), void), asCALL_THISCALL);
    // void Audio::ResumeSoundType(const String& type) | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "void ResumeSoundType(const String&in)", asMETHODPR(Audio, ResumeSoundType, (const String&), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "void SendEvent(StringHash)", asMETHODPR(Audio, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Audio, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "void SetBlockEvents(bool)", asMETHODPR(Audio, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Audio, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Audio, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Audio::SetListener(SoundListener* listener) | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "void SetListener(SoundListener@+)", asMETHODPR(Audio, SetListener, (SoundListener*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "void set_listener(SoundListener@+)", asMETHODPR(Audio, SetListener, (SoundListener*), void), asCALL_THISCALL);
    // void Audio::SetMasterGain(const String& type, float gain) | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "void SetMasterGain(const String&in, float)", asMETHODPR(Audio, SetMasterGain, (const String&, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "void set_masterGain(const String&in, float)", asMETHODPR(Audio, SetMasterGain, (const String&, float), void), asCALL_THISCALL);
    // bool Audio::SetMode(int bufferLengthMSec, int mixRate, bool stereo, bool interpolation=true) | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "bool SetMode(int, int, bool, bool = true)", asMETHODPR(Audio, SetMode, (int, int, bool, bool), bool), asCALL_THISCALL);
    // void Audio::Stop() | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "void Stop()", asMETHODPR(Audio, Stop, (), void), asCALL_THISCALL);
    // void Audio::StopSound(Sound* sound) | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "void StopSound(Sound@+)", asMETHODPR(Audio, StopSound, (Sound*), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "void UnsubscribeFromAllEvents()", asMETHODPR(Audio, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Audio_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Audio, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Audio, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Audio", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Audio, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void Audio::Update(float timeStep) | File: ../Audio/Audio.h
    engine->RegisterObjectMethod("Audio", "void Update(float)", asMETHODPR(Audio, Update, (float), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Audio", "int WeakRefs() const", asMETHODPR(Audio, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Audio", "int get_weakRefs() const", asMETHODPR(Audio, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("AnimationControl", asBEHAVE_FACTORY, "AnimationControl@+ f()", asFUNCTION(AnimationControl_AnimationControl_void), asCALL_CDECL);
    // AnimationControl& AnimationControl::operator=(const AnimationControl&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AnimationControl>(engine, "AnimationControl");
    engine->RegisterObjectBehaviour("AnimationControl", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("AnimationControl", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
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
    engine->RegisterObjectMethod("AnimationTrack", "void AddKeyFrame(const AnimationKeyFrame&in)", asMETHODPR(AnimationTrack, AddKeyFrame, (const AnimationKeyFrame&), void), asCALL_THISCALL);
    // AnimationTrack::AnimationTrack() | File: ../Graphics/Animation.h
    engine->RegisterObjectBehaviour("AnimationTrack", asBEHAVE_FACTORY, "AnimationTrack@+ f()", asFUNCTION(AnimationTrack_AnimationTrack_void), asCALL_CDECL);
    // AnimationKeyFrame* AnimationTrack::GetKeyFrame(unsigned index) | File: ../Graphics/Animation.h
    // Error: type "AnimationKeyFrame*" can not automatically bind
    // bool AnimationTrack::GetKeyFrameIndex(float time, unsigned& index) const | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("AnimationTrack", "bool GetKeyFrameIndex(float, uint&) const", asMETHODPR(AnimationTrack, GetKeyFrameIndex, (float, unsigned&) const, bool), asCALL_THISCALL);
    // unsigned AnimationTrack::GetNumKeyFrames() const | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("AnimationTrack", "uint GetNumKeyFrames() const", asMETHODPR(AnimationTrack, GetNumKeyFrames, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationTrack", "uint get_numKeyFrames() const", asMETHODPR(AnimationTrack, GetNumKeyFrames, () const, unsigned), asCALL_THISCALL);
    // void AnimationTrack::InsertKeyFrame(unsigned index, const AnimationKeyFrame& keyFrame) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("AnimationTrack", "void InsertKeyFrame(uint, const AnimationKeyFrame&in)", asMETHODPR(AnimationTrack, InsertKeyFrame, (unsigned, const AnimationKeyFrame&), void), asCALL_THISCALL);
    // void AnimationTrack::RemoveAllKeyFrames() | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("AnimationTrack", "void RemoveAllKeyFrames()", asMETHODPR(AnimationTrack, RemoveAllKeyFrames, (), void), asCALL_THISCALL);
    // void AnimationTrack::RemoveKeyFrame(unsigned index) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("AnimationTrack", "void RemoveKeyFrame(uint)", asMETHODPR(AnimationTrack, RemoveKeyFrame, (unsigned), void), asCALL_THISCALL);
    // void AnimationTrack::SetKeyFrame(unsigned index, const AnimationKeyFrame& keyFrame) | File: ../Graphics/Animation.h
    engine->RegisterObjectMethod("AnimationTrack", "void SetKeyFrame(uint, const AnimationKeyFrame&in)", asMETHODPR(AnimationTrack, SetKeyFrame, (unsigned, const AnimationKeyFrame&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationTrack", "void set_keyFrames(uint, const AnimationKeyFrame&in)", asMETHODPR(AnimationTrack, SetKeyFrame, (unsigned, const AnimationKeyFrame&), void), asCALL_THISCALL);
    // AnimationTrack& AnimationTrack::operator=(const AnimationTrack&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AnimationTrack>(engine, "AnimationTrack");
    engine->RegisterObjectBehaviour("AnimationTrack", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("AnimationTrack", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
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
    engine->RegisterObjectMethod("AttributeInfo", "const Variant& GetMetadata(const StringHash&in) const", asMETHODPR(AttributeInfo, GetMetadata, (const StringHash&) const, const Variant&), asCALL_THISCALL);
    // template<class T> T AttributeInfo::GetMetadata(const StringHash& key) const | File: ../Core/Attribute.h
    // Not registered because template
    // AttributeInfo& AttributeInfo::operator=(const AttributeInfo&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<AttributeInfo>(engine, "AttributeInfo");
#ifdef REGISTER_MANUAL_PART_AttributeInfo
    REGISTER_MANUAL_PART_AttributeInfo(AttributeInfo, "AttributeInfo")
#endif

}

}
