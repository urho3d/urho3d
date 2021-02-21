// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

#ifdef URHO3D_NETWORK
// StringVector Deserializer::ReadStringVector() | File: ../IO/Deserializer.h
static CScriptArray* HttpRequest_ReadStringVector_void(HttpRequest* ptr)
{
    StringVector result = ptr->ReadStringVector();
    return VectorToArray<String>(result, "Array<String>");
}
#endif

#ifdef URHO3D_PHYSICS
// HeightfieldData::HeightfieldData(Terrain* terrain, unsigned lodLevel) | File: ../Physics/CollisionShape.h
static HeightfieldData* HeightfieldData_HeightfieldData_Terrain_unsigned(Terrain *terrain, unsigned lodLevel)
{
    return new HeightfieldData(terrain, lodLevel);
}
#endif

void ASRegisterGenerated_Members_H(asIScriptEngine* engine)
{
    // const unsigned HashBase::MAX_LOAD_FACTOR | File: ../Container/HashBase.h
    engine->SetDefaultNamespace("HashBase");
    engine->RegisterGlobalProperty("const uint MAX_LOAD_FACTOR", (void*)&HashBase::MAX_LOAD_FACTOR);
    engine->SetDefaultNamespace("");
    // const unsigned HashBase::MIN_BUCKETS | File: ../Container/HashBase.h
    engine->SetDefaultNamespace("HashBase");
    engine->RegisterGlobalProperty("const uint MIN_BUCKETS", (void*)&HashBase::MIN_BUCKETS);
    engine->SetDefaultNamespace("");
    // bool HashBase::Empty() const | File: ../Container/HashBase.h
    engine->RegisterObjectMethod("HashBase", "bool Empty() const", AS_METHODPR(HashBase, Empty, () const, bool), AS_CALL_THISCALL);
    // unsigned HashBase::NumBuckets() const | File: ../Container/HashBase.h
    engine->RegisterObjectMethod("HashBase", "uint NumBuckets() const", AS_METHODPR(HashBase, NumBuckets, () const, unsigned), AS_CALL_THISCALL);
    // unsigned HashBase::Size() const | File: ../Container/HashBase.h
    engine->RegisterObjectMethod("HashBase", "uint Size() const", AS_METHODPR(HashBase, Size, () const, unsigned), AS_CALL_THISCALL);
    // void HashBase::Swap(HashBase& rhs) | File: ../Container/HashBase.h
    engine->RegisterObjectMethod("HashBase", "void Swap(HashBase&)", AS_METHODPR(HashBase, Swap, (HashBase&), void), AS_CALL_THISCALL);
    // HashBase& HashBase::operator=(const HashBase&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<HashBase>(engine, "HashBase");
#ifdef REGISTER_MANUAL_PART_HashBase
    REGISTER_MANUAL_PART_HashBase(HashBase, "HashBase")
#endif

    // static long long HiresTimer::GetFrequency() | File: ../Core/Timer.h
    engine->SetDefaultNamespace("HiresTimer");
    engine->RegisterGlobalFunction("int64 GetFrequency()", AS_FUNCTIONPR(HiresTimer::GetFrequency, (), long long), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // long long HiresTimer::GetUSec(bool reset) | File: ../Core/Timer.h
    engine->RegisterObjectMethod("HiresTimer", "int64 GetUSec(bool)", AS_METHODPR(HiresTimer, GetUSec, (bool), long long), AS_CALL_THISCALL);
    // static bool HiresTimer::IsSupported() | File: ../Core/Timer.h
    engine->SetDefaultNamespace("HiresTimer");
    engine->RegisterGlobalFunction("bool IsSupported()", AS_FUNCTIONPR(HiresTimer::IsSupported, (), bool), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // void HiresTimer::Reset() | File: ../Core/Timer.h
    engine->RegisterObjectMethod("HiresTimer", "void Reset()", AS_METHODPR(HiresTimer, Reset, (), void), AS_CALL_THISCALL);
    // HiresTimer& HiresTimer::operator=(const HiresTimer&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<HiresTimer>(engine, "HiresTimer");
#ifdef REGISTER_MANUAL_PART_HiresTimer
    REGISTER_MANUAL_PART_HiresTimer(HiresTimer, "HiresTimer")
#endif

#ifdef URHO3D_NETWORK
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("HttpRequest", asBEHAVE_ADDREF, "void f()", AS_METHODPR(HttpRequest, AddRef, (), void), AS_CALL_THISCALL);
    // unsigned HttpRequest::GetAvailableSize() const | File: ../Network/HttpRequest.h
    engine->RegisterObjectMethod("HttpRequest", "uint GetAvailableSize() const", AS_METHODPR(HttpRequest, GetAvailableSize, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "uint get_availableSize() const", AS_METHODPR(HttpRequest, GetAvailableSize, () const, unsigned), AS_CALL_THISCALL);
    // virtual unsigned Deserializer::GetChecksum() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "uint GetChecksum()", AS_METHODPR(HttpRequest, GetChecksum, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "uint get_checksum()", AS_METHODPR(HttpRequest, GetChecksum, (), unsigned), AS_CALL_THISCALL);
    // static ThreadID Thread::GetCurrentThreadID() | File: ../Core/Thread.h
    // Not registered because have @nobind mark
    // String HttpRequest::GetError() const | File: ../Network/HttpRequest.h
    engine->RegisterObjectMethod("HttpRequest", "String GetError() const", AS_METHODPR(HttpRequest, GetError, () const, String), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "String get_error() const", AS_METHODPR(HttpRequest, GetError, () const, String), AS_CALL_THISCALL);
    // virtual const String& Deserializer::GetName() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "const String& GetName() const", AS_METHODPR(HttpRequest, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "const String& get_name() const", AS_METHODPR(HttpRequest, GetName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Deserializer::GetPosition() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "uint GetPosition() const", AS_METHODPR(HttpRequest, GetPosition, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "uint get_position() const", AS_METHODPR(HttpRequest, GetPosition, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Deserializer::GetSize() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "uint GetSize() const", AS_METHODPR(HttpRequest, GetSize, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "uint get_size() const", AS_METHODPR(HttpRequest, GetSize, () const, unsigned), AS_CALL_THISCALL);
    // HttpRequestState HttpRequest::GetState() const | File: ../Network/HttpRequest.h
    engine->RegisterObjectMethod("HttpRequest", "HttpRequestState GetState() const", AS_METHODPR(HttpRequest, GetState, () const, HttpRequestState), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "HttpRequestState get_state() const", AS_METHODPR(HttpRequest, GetState, () const, HttpRequestState), AS_CALL_THISCALL);
    // const String& HttpRequest::GetURL() const | File: ../Network/HttpRequest.h
    engine->RegisterObjectMethod("HttpRequest", "const String& GetURL() const", AS_METHODPR(HttpRequest, GetURL, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "const String& get_url() const", AS_METHODPR(HttpRequest, GetURL, () const, const String&), AS_CALL_THISCALL);
    // const String& HttpRequest::GetVerb() const | File: ../Network/HttpRequest.h
    engine->RegisterObjectMethod("HttpRequest", "const String& GetVerb() const", AS_METHODPR(HttpRequest, GetVerb, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "const String& get_verb() const", AS_METHODPR(HttpRequest, GetVerb, () const, const String&), AS_CALL_THISCALL);
    // HttpRequest::HttpRequest(const String& url, const String& verb, const Vector<String>& headers, const String& postData) | File: ../Network/HttpRequest.h
    // Error: type "const Vector<String>&" can not automatically bind
    // bool HttpRequest::IsEof() const override | File: ../Network/HttpRequest.h
    engine->RegisterObjectMethod("HttpRequest", "bool IsEof() const", AS_METHODPR(HttpRequest, IsEof, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "bool get_eof() const", AS_METHODPR(HttpRequest, IsEof, () const, bool), AS_CALL_THISCALL);
    // static bool Thread::IsMainThread() | File: ../Core/Thread.h
    engine->SetDefaultNamespace("HttpRequest");
    engine->RegisterGlobalFunction("bool IsMainThread()", AS_FUNCTIONPR(HttpRequest::IsMainThread, (), bool), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool HttpRequest::IsOpen() const | File: ../Network/HttpRequest.h
    engine->RegisterObjectMethod("HttpRequest", "bool IsOpen() const", AS_METHODPR(HttpRequest, IsOpen, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "bool get_open() const", AS_METHODPR(HttpRequest, IsOpen, () const, bool), AS_CALL_THISCALL);
    // bool Thread::IsStarted() const | File: ../Core/Thread.h
    engine->RegisterObjectMethod("HttpRequest", "bool IsStarted() const", AS_METHODPR(HttpRequest, IsStarted, () const, bool), AS_CALL_THISCALL);
    // unsigned HttpRequest::Read(void* dest, unsigned size) override | File: ../Network/HttpRequest.h
    // Error: type "void*" can not automatically bind
    // bool Deserializer::ReadBool() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "bool ReadBool()", AS_METHODPR(HttpRequest, ReadBool, (), bool), AS_CALL_THISCALL);
    // BoundingBox Deserializer::ReadBoundingBox() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "BoundingBox ReadBoundingBox()", AS_METHODPR(HttpRequest, ReadBoundingBox, (), BoundingBox), AS_CALL_THISCALL);
    // PODVector<unsigned char> Deserializer::ReadBuffer() | File: ../IO/Deserializer.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // signed char Deserializer::ReadByte() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "int8 ReadByte()", AS_METHODPR(HttpRequest, ReadByte, (), signed char), AS_CALL_THISCALL);
    // Color Deserializer::ReadColor() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Color ReadColor()", AS_METHODPR(HttpRequest, ReadColor, (), Color), AS_CALL_THISCALL);
    // double Deserializer::ReadDouble() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "double ReadDouble()", AS_METHODPR(HttpRequest, ReadDouble, (), double), AS_CALL_THISCALL);
    // String Deserializer::ReadFileID() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "String ReadFileID()", AS_METHODPR(HttpRequest, ReadFileID, (), String), AS_CALL_THISCALL);
    // float Deserializer::ReadFloat() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "float ReadFloat()", AS_METHODPR(HttpRequest, ReadFloat, (), float), AS_CALL_THISCALL);
    // int Deserializer::ReadInt() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "int ReadInt()", AS_METHODPR(HttpRequest, ReadInt, (), int), AS_CALL_THISCALL);
    // long long Deserializer::ReadInt64() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "int64 ReadInt64()", AS_METHODPR(HttpRequest, ReadInt64, (), long long), AS_CALL_THISCALL);
    // IntRect Deserializer::ReadIntRect() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "IntRect ReadIntRect()", AS_METHODPR(HttpRequest, ReadIntRect, (), IntRect), AS_CALL_THISCALL);
    // IntVector2 Deserializer::ReadIntVector2() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "IntVector2 ReadIntVector2()", AS_METHODPR(HttpRequest, ReadIntVector2, (), IntVector2), AS_CALL_THISCALL);
    // IntVector3 Deserializer::ReadIntVector3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "IntVector3 ReadIntVector3()", AS_METHODPR(HttpRequest, ReadIntVector3, (), IntVector3), AS_CALL_THISCALL);
    // String Deserializer::ReadLine() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "String ReadLine()", AS_METHODPR(HttpRequest, ReadLine, (), String), AS_CALL_THISCALL);
    // Matrix3 Deserializer::ReadMatrix3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Matrix3 ReadMatrix3()", AS_METHODPR(HttpRequest, ReadMatrix3, (), Matrix3), AS_CALL_THISCALL);
    // Matrix3x4 Deserializer::ReadMatrix3x4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Matrix3x4 ReadMatrix3x4()", AS_METHODPR(HttpRequest, ReadMatrix3x4, (), Matrix3x4), AS_CALL_THISCALL);
    // Matrix4 Deserializer::ReadMatrix4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Matrix4 ReadMatrix4()", AS_METHODPR(HttpRequest, ReadMatrix4, (), Matrix4), AS_CALL_THISCALL);
    // unsigned Deserializer::ReadNetID() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "uint ReadNetID()", AS_METHODPR(HttpRequest, ReadNetID, (), unsigned), AS_CALL_THISCALL);
    // Quaternion Deserializer::ReadPackedQuaternion() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Quaternion ReadPackedQuaternion()", AS_METHODPR(HttpRequest, ReadPackedQuaternion, (), Quaternion), AS_CALL_THISCALL);
    // Vector3 Deserializer::ReadPackedVector3(float maxAbsCoord) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Vector3 ReadPackedVector3(float)", AS_METHODPR(HttpRequest, ReadPackedVector3, (float), Vector3), AS_CALL_THISCALL);
    // Quaternion Deserializer::ReadQuaternion() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Quaternion ReadQuaternion()", AS_METHODPR(HttpRequest, ReadQuaternion, (), Quaternion), AS_CALL_THISCALL);
    // Rect Deserializer::ReadRect() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Rect ReadRect()", AS_METHODPR(HttpRequest, ReadRect, (), Rect), AS_CALL_THISCALL);
    // ResourceRef Deserializer::ReadResourceRef() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "ResourceRef ReadResourceRef()", AS_METHODPR(HttpRequest, ReadResourceRef, (), ResourceRef), AS_CALL_THISCALL);
    // ResourceRefList Deserializer::ReadResourceRefList() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "ResourceRefList ReadResourceRefList()", AS_METHODPR(HttpRequest, ReadResourceRefList, (), ResourceRefList), AS_CALL_THISCALL);
    // short Deserializer::ReadShort() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "int16 ReadShort()", AS_METHODPR(HttpRequest, ReadShort, (), short), AS_CALL_THISCALL);
    // String Deserializer::ReadString() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "String ReadString()", AS_METHODPR(HttpRequest, ReadString, (), String), AS_CALL_THISCALL);
    // StringHash Deserializer::ReadStringHash() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "StringHash ReadStringHash()", AS_METHODPR(HttpRequest, ReadStringHash, (), StringHash), AS_CALL_THISCALL);
    // StringVector Deserializer::ReadStringVector() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Array<String>@ ReadStringVector()", AS_FUNCTION_OBJFIRST(HttpRequest_ReadStringVector_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned char Deserializer::ReadUByte() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "uint8 ReadUByte()", AS_METHODPR(HttpRequest, ReadUByte, (), unsigned char), AS_CALL_THISCALL);
    // unsigned Deserializer::ReadUInt() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "uint ReadUInt()", AS_METHODPR(HttpRequest, ReadUInt, (), unsigned), AS_CALL_THISCALL);
    // unsigned long long Deserializer::ReadUInt64() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "uint64 ReadUInt64()", AS_METHODPR(HttpRequest, ReadUInt64, (), unsigned long long), AS_CALL_THISCALL);
    // unsigned short Deserializer::ReadUShort() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "uint16 ReadUShort()", AS_METHODPR(HttpRequest, ReadUShort, (), unsigned short), AS_CALL_THISCALL);
    // Variant Deserializer::ReadVariant() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Variant ReadVariant()", AS_METHODPR(HttpRequest, ReadVariant, (), Variant), AS_CALL_THISCALL);
    // Variant Deserializer::ReadVariant(VariantType type) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Variant ReadVariant(VariantType)", AS_METHODPR(HttpRequest, ReadVariant, (VariantType), Variant), AS_CALL_THISCALL);
    // VariantMap Deserializer::ReadVariantMap() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "VariantMap ReadVariantMap()", AS_METHODPR(HttpRequest, ReadVariantMap, (), VariantMap), AS_CALL_THISCALL);
    // VariantVector Deserializer::ReadVariantVector() | File: ../IO/Deserializer.h
    // Error: type "VariantVector" can not automatically bind
    // Vector2 Deserializer::ReadVector2() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Vector2 ReadVector2()", AS_METHODPR(HttpRequest, ReadVector2, (), Vector2), AS_CALL_THISCALL);
    // Vector3 Deserializer::ReadVector3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Vector3 ReadVector3()", AS_METHODPR(HttpRequest, ReadVector3, (), Vector3), AS_CALL_THISCALL);
    // Vector4 Deserializer::ReadVector4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Vector4 ReadVector4()", AS_METHODPR(HttpRequest, ReadVector4, (), Vector4), AS_CALL_THISCALL);
    // unsigned Deserializer::ReadVLE() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "uint ReadVLE()", AS_METHODPR(HttpRequest, ReadVLE, (), unsigned), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("HttpRequest", "int Refs() const", AS_METHODPR(HttpRequest, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "int get_refs() const", AS_METHODPR(HttpRequest, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("HttpRequest", asBEHAVE_RELEASE, "void f()", AS_METHODPR(HttpRequest, ReleaseRef, (), void), AS_CALL_THISCALL);
    // bool Thread::Run() | File: ../Core/Thread.h
    engine->RegisterObjectMethod("HttpRequest", "bool Run()", AS_METHODPR(HttpRequest, Run, (), bool), AS_CALL_THISCALL);
    // unsigned HttpRequest::Seek(unsigned position) override | File: ../Network/HttpRequest.h
    engine->RegisterObjectMethod("HttpRequest", "uint Seek(uint)", AS_METHODPR(HttpRequest, Seek, (unsigned), unsigned), AS_CALL_THISCALL);
    // unsigned Deserializer::SeekRelative(int delta) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "uint SeekRelative(int)", AS_METHODPR(HttpRequest, SeekRelative, (int), unsigned), AS_CALL_THISCALL);
    // static void Thread::SetMainThread() | File: ../Core/Thread.h
    engine->SetDefaultNamespace("HttpRequest");
    engine->RegisterGlobalFunction("void SetMainThread()", AS_FUNCTIONPR(HttpRequest::SetMainThread, (), void), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // void Thread::SetPriority(int priority) | File: ../Core/Thread.h
    engine->RegisterObjectMethod("HttpRequest", "void SetPriority(int)", AS_METHODPR(HttpRequest, SetPriority, (int), void), AS_CALL_THISCALL);
    // void Thread::Stop() | File: ../Core/Thread.h
    engine->RegisterObjectMethod("HttpRequest", "void Stop()", AS_METHODPR(HttpRequest, Stop, (), void), AS_CALL_THISCALL);
    // unsigned Deserializer::Tell() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "uint Tell() const", AS_METHODPR(HttpRequest, Tell, () const, unsigned), AS_CALL_THISCALL);
    // void HttpRequest::ThreadFunction() override | File: ../Network/HttpRequest.h
    engine->RegisterObjectMethod("HttpRequest", "void ThreadFunction()", AS_METHODPR(HttpRequest, ThreadFunction, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("HttpRequest", "int WeakRefs() const", AS_METHODPR(HttpRequest, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "int get_weakRefs() const", AS_METHODPR(HttpRequest, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(HttpRequest, "HttpRequest")
#endif
#ifdef REGISTER_MANUAL_PART_Deserializer
    REGISTER_MANUAL_PART_Deserializer(HttpRequest, "HttpRequest")
#endif
#ifdef REGISTER_MANUAL_PART_Thread
    REGISTER_MANUAL_PART_Thread(HttpRequest, "HttpRequest")
#endif
#ifdef REGISTER_MANUAL_PART_HttpRequest
    REGISTER_MANUAL_PART_HttpRequest(HttpRequest, "HttpRequest")
#endif
    RegisterSubclass<RefCounted, HttpRequest>(engine, "RefCounted", "HttpRequest");
    RegisterSubclass<Deserializer, HttpRequest>(engine, "Deserializer", "HttpRequest");
#endif

    // HashNodeBase* HashIteratorBase::ptr_ | File: ../Container/HashBase.h
    // HashNodeBase* can not be registered
    // void HashIteratorBase::GotoNext() | File: ../Container/HashBase.h
    engine->RegisterObjectMethod("HashIteratorBase", "void GotoNext()", AS_METHODPR(HashIteratorBase, GotoNext, (), void), AS_CALL_THISCALL);
    // void HashIteratorBase::GotoPrev() | File: ../Container/HashBase.h
    engine->RegisterObjectMethod("HashIteratorBase", "void GotoPrev()", AS_METHODPR(HashIteratorBase, GotoPrev, (), void), AS_CALL_THISCALL);
    // explicit HashIteratorBase::HashIteratorBase(HashNodeBase* ptr) | File: ../Container/HashBase.h
    // Error: type "HashNodeBase*" can not automatically bind
    // bool HashIteratorBase::operator==(const HashIteratorBase& rhs) const | File: ../Container/HashBase.h
    engine->RegisterObjectMethod("HashIteratorBase", "bool opEquals(const HashIteratorBase&in) const", AS_METHODPR(HashIteratorBase, operator==, (const HashIteratorBase&) const, bool), AS_CALL_THISCALL);
    // HashIteratorBase& HashIteratorBase::operator=(const HashIteratorBase&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<HashIteratorBase>(engine, "HashIteratorBase");
#ifdef REGISTER_MANUAL_PART_HashIteratorBase
    REGISTER_MANUAL_PART_HashIteratorBase(HashIteratorBase, "HashIteratorBase")
#endif

    // HashNodeBase* HashNodeBase::down_ | File: ../Container/HashBase.h
    // HashNodeBase* can not be registered
    // HashNodeBase* HashNodeBase::next_ | File: ../Container/HashBase.h
    // HashNodeBase* can not be registered
    // HashNodeBase* HashNodeBase::prev_ | File: ../Container/HashBase.h
    // HashNodeBase* can not be registered
    // HashNodeBase& HashNodeBase::operator=(const HashNodeBase&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<HashNodeBase>(engine, "HashNodeBase");
#ifdef REGISTER_MANUAL_PART_HashNodeBase
    REGISTER_MANUAL_PART_HashNodeBase(HashNodeBase, "HashNodeBase")
#endif

#ifdef URHO3D_PHYSICS
    // SharedArrayPtr<float> HeightfieldData::heightData_ | File: ../Physics/CollisionShape.h
    // Error: type "SharedArrayPtr<float>" can not automatically bind
    // float HeightfieldData::maxHeight_ | File: ../Physics/CollisionShape.h
    engine->RegisterObjectProperty("HeightfieldData", "float maxHeight", offsetof(HeightfieldData, maxHeight_));
    // float HeightfieldData::minHeight_ | File: ../Physics/CollisionShape.h
    engine->RegisterObjectProperty("HeightfieldData", "float minHeight", offsetof(HeightfieldData, minHeight_));
    // IntVector2 HeightfieldData::size_ | File: ../Physics/CollisionShape.h
    engine->RegisterObjectProperty("HeightfieldData", "IntVector2 size", offsetof(HeightfieldData, size_));
    // Vector3 HeightfieldData::spacing_ | File: ../Physics/CollisionShape.h
    engine->RegisterObjectProperty("HeightfieldData", "Vector3 spacing", offsetof(HeightfieldData, spacing_));
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("HeightfieldData", asBEHAVE_ADDREF, "void f()", AS_METHODPR(HeightfieldData, AddRef, (), void), AS_CALL_THISCALL);
    // HeightfieldData::HeightfieldData(Terrain* terrain, unsigned lodLevel) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectBehaviour("HeightfieldData", asBEHAVE_FACTORY, "HeightfieldData@+ f(Terrain@+, uint)", AS_FUNCTION(HeightfieldData_HeightfieldData_Terrain_unsigned), AS_CALL_CDECL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("HeightfieldData", "int Refs() const", AS_METHODPR(HeightfieldData, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("HeightfieldData", "int get_refs() const", AS_METHODPR(HeightfieldData, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("HeightfieldData", asBEHAVE_RELEASE, "void f()", AS_METHODPR(HeightfieldData, ReleaseRef, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("HeightfieldData", "int WeakRefs() const", AS_METHODPR(HeightfieldData, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("HeightfieldData", "int get_weakRefs() const", AS_METHODPR(HeightfieldData, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_CollisionGeometryData
    REGISTER_MANUAL_PART_CollisionGeometryData(HeightfieldData, "HeightfieldData")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(HeightfieldData, "HeightfieldData")
#endif
#ifdef REGISTER_MANUAL_PART_HeightfieldData
    REGISTER_MANUAL_PART_HeightfieldData(HeightfieldData, "HeightfieldData")
#endif
    RegisterSubclass<CollisionGeometryData, HeightfieldData>(engine, "CollisionGeometryData", "HeightfieldData");
    RegisterSubclass<RefCounted, HeightfieldData>(engine, "RefCounted", "HeightfieldData");
#endif

}

}
