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
    engine->RegisterObjectMethod("HashBase", "bool Empty() const", asMETHODPR(HashBase, Empty, () const, bool), asCALL_THISCALL);
    // unsigned HashBase::NumBuckets() const | File: ../Container/HashBase.h
    engine->RegisterObjectMethod("HashBase", "uint NumBuckets() const", asMETHODPR(HashBase, NumBuckets, () const, unsigned), asCALL_THISCALL);
    // unsigned HashBase::Size() const | File: ../Container/HashBase.h
    engine->RegisterObjectMethod("HashBase", "uint Size() const", asMETHODPR(HashBase, Size, () const, unsigned), asCALL_THISCALL);
    // void HashBase::Swap(HashBase& rhs) | File: ../Container/HashBase.h
    engine->RegisterObjectMethod("HashBase", "void Swap(HashBase&)", asMETHODPR(HashBase, Swap, (HashBase&), void), asCALL_THISCALL);
    // HashBase& HashBase::operator=(const HashBase&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<HashBase>(engine, "HashBase");
#ifdef REGISTER_MANUAL_PART_HashBase
    REGISTER_MANUAL_PART_HashBase(HashBase, "HashBase")
#endif

    // static long long HiresTimer::GetFrequency() | File: ../Core/Timer.h
    engine->SetDefaultNamespace("HiresTimer");
    engine->RegisterGlobalFunction("int64 GetFrequency()", asFUNCTIONPR(HiresTimer::GetFrequency, (), long long), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // long long HiresTimer::GetUSec(bool reset) | File: ../Core/Timer.h
    engine->RegisterObjectMethod("HiresTimer", "int64 GetUSec(bool)", asMETHODPR(HiresTimer, GetUSec, (bool), long long), asCALL_THISCALL);
    // static bool HiresTimer::IsSupported() | File: ../Core/Timer.h
    engine->SetDefaultNamespace("HiresTimer");
    engine->RegisterGlobalFunction("bool IsSupported()", asFUNCTIONPR(HiresTimer::IsSupported, (), bool), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // void HiresTimer::Reset() | File: ../Core/Timer.h
    engine->RegisterObjectMethod("HiresTimer", "void Reset()", asMETHODPR(HiresTimer, Reset, (), void), asCALL_THISCALL);
    // HiresTimer& HiresTimer::operator=(const HiresTimer&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<HiresTimer>(engine, "HiresTimer");
#ifdef REGISTER_MANUAL_PART_HiresTimer
    REGISTER_MANUAL_PART_HiresTimer(HiresTimer, "HiresTimer")
#endif

#ifdef URHO3D_NETWORK
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("HttpRequest", asBEHAVE_ADDREF, "void f()", asMETHODPR(HttpRequest, AddRef, (), void), asCALL_THISCALL);
    // unsigned HttpRequest::GetAvailableSize() const | File: ../Network/HttpRequest.h
    engine->RegisterObjectMethod("HttpRequest", "uint GetAvailableSize() const", asMETHODPR(HttpRequest, GetAvailableSize, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "uint get_availableSize() const", asMETHODPR(HttpRequest, GetAvailableSize, () const, unsigned), asCALL_THISCALL);
    // virtual unsigned Deserializer::GetChecksum() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "uint GetChecksum()", asMETHODPR(HttpRequest, GetChecksum, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "uint get_checksum()", asMETHODPR(HttpRequest, GetChecksum, (), unsigned), asCALL_THISCALL);
    // static ThreadID Thread::GetCurrentThreadID() | File: ../Core/Thread.h
    // Not registered because have @nobind mark
    // String HttpRequest::GetError() const | File: ../Network/HttpRequest.h
    engine->RegisterObjectMethod("HttpRequest", "String GetError() const", asMETHODPR(HttpRequest, GetError, () const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "String get_error() const", asMETHODPR(HttpRequest, GetError, () const, String), asCALL_THISCALL);
    // virtual const String& Deserializer::GetName() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "const String& GetName() const", asMETHODPR(HttpRequest, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "const String& get_name() const", asMETHODPR(HttpRequest, GetName, () const, const String&), asCALL_THISCALL);
    // unsigned Deserializer::GetPosition() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "uint GetPosition() const", asMETHODPR(HttpRequest, GetPosition, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "uint get_position() const", asMETHODPR(HttpRequest, GetPosition, () const, unsigned), asCALL_THISCALL);
    // unsigned Deserializer::GetSize() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "uint GetSize() const", asMETHODPR(HttpRequest, GetSize, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "uint get_size() const", asMETHODPR(HttpRequest, GetSize, () const, unsigned), asCALL_THISCALL);
    // HttpRequestState HttpRequest::GetState() const | File: ../Network/HttpRequest.h
    engine->RegisterObjectMethod("HttpRequest", "HttpRequestState GetState() const", asMETHODPR(HttpRequest, GetState, () const, HttpRequestState), asCALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "HttpRequestState get_state() const", asMETHODPR(HttpRequest, GetState, () const, HttpRequestState), asCALL_THISCALL);
    // const String& HttpRequest::GetURL() const | File: ../Network/HttpRequest.h
    engine->RegisterObjectMethod("HttpRequest", "const String& GetURL() const", asMETHODPR(HttpRequest, GetURL, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "const String& get_url() const", asMETHODPR(HttpRequest, GetURL, () const, const String&), asCALL_THISCALL);
    // const String& HttpRequest::GetVerb() const | File: ../Network/HttpRequest.h
    engine->RegisterObjectMethod("HttpRequest", "const String& GetVerb() const", asMETHODPR(HttpRequest, GetVerb, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "const String& get_verb() const", asMETHODPR(HttpRequest, GetVerb, () const, const String&), asCALL_THISCALL);
    // HttpRequest::HttpRequest(const String& url, const String& verb, const Vector<String>& headers, const String& postData) | File: ../Network/HttpRequest.h
    // Error: type "const Vector<String>&" can not automatically bind
    // bool HttpRequest::IsEof() const override | File: ../Network/HttpRequest.h
    engine->RegisterObjectMethod("HttpRequest", "bool IsEof() const", asMETHODPR(HttpRequest, IsEof, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "bool get_eof() const", asMETHODPR(HttpRequest, IsEof, () const, bool), asCALL_THISCALL);
    // static bool Thread::IsMainThread() | File: ../Core/Thread.h
    engine->SetDefaultNamespace("HttpRequest");
    engine->RegisterGlobalFunction("bool IsMainThread()", asFUNCTIONPR(HttpRequest::IsMainThread, (), bool), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool HttpRequest::IsOpen() const | File: ../Network/HttpRequest.h
    engine->RegisterObjectMethod("HttpRequest", "bool IsOpen() const", asMETHODPR(HttpRequest, IsOpen, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "bool get_open() const", asMETHODPR(HttpRequest, IsOpen, () const, bool), asCALL_THISCALL);
    // bool Thread::IsStarted() const | File: ../Core/Thread.h
    engine->RegisterObjectMethod("HttpRequest", "bool IsStarted() const", asMETHODPR(HttpRequest, IsStarted, () const, bool), asCALL_THISCALL);
    // unsigned HttpRequest::Read(void* dest, unsigned size) override | File: ../Network/HttpRequest.h
    // Error: type "void*" can not automatically bind
    // bool Deserializer::ReadBool() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "bool ReadBool()", asMETHODPR(HttpRequest, ReadBool, (), bool), asCALL_THISCALL);
    // BoundingBox Deserializer::ReadBoundingBox() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "BoundingBox ReadBoundingBox()", asMETHODPR(HttpRequest, ReadBoundingBox, (), BoundingBox), asCALL_THISCALL);
    // PODVector<unsigned char> Deserializer::ReadBuffer() | File: ../IO/Deserializer.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // signed char Deserializer::ReadByte() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "int8 ReadByte()", asMETHODPR(HttpRequest, ReadByte, (), signed char), asCALL_THISCALL);
    // Color Deserializer::ReadColor() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Color ReadColor()", asMETHODPR(HttpRequest, ReadColor, (), Color), asCALL_THISCALL);
    // double Deserializer::ReadDouble() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "double ReadDouble()", asMETHODPR(HttpRequest, ReadDouble, (), double), asCALL_THISCALL);
    // String Deserializer::ReadFileID() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "String ReadFileID()", asMETHODPR(HttpRequest, ReadFileID, (), String), asCALL_THISCALL);
    // float Deserializer::ReadFloat() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "float ReadFloat()", asMETHODPR(HttpRequest, ReadFloat, (), float), asCALL_THISCALL);
    // int Deserializer::ReadInt() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "int ReadInt()", asMETHODPR(HttpRequest, ReadInt, (), int), asCALL_THISCALL);
    // long long Deserializer::ReadInt64() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "int64 ReadInt64()", asMETHODPR(HttpRequest, ReadInt64, (), long long), asCALL_THISCALL);
    // IntRect Deserializer::ReadIntRect() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "IntRect ReadIntRect()", asMETHODPR(HttpRequest, ReadIntRect, (), IntRect), asCALL_THISCALL);
    // IntVector2 Deserializer::ReadIntVector2() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "IntVector2 ReadIntVector2()", asMETHODPR(HttpRequest, ReadIntVector2, (), IntVector2), asCALL_THISCALL);
    // IntVector3 Deserializer::ReadIntVector3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "IntVector3 ReadIntVector3()", asMETHODPR(HttpRequest, ReadIntVector3, (), IntVector3), asCALL_THISCALL);
    // String Deserializer::ReadLine() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "String ReadLine()", asMETHODPR(HttpRequest, ReadLine, (), String), asCALL_THISCALL);
    // Matrix3 Deserializer::ReadMatrix3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Matrix3 ReadMatrix3()", asMETHODPR(HttpRequest, ReadMatrix3, (), Matrix3), asCALL_THISCALL);
    // Matrix3x4 Deserializer::ReadMatrix3x4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Matrix3x4 ReadMatrix3x4()", asMETHODPR(HttpRequest, ReadMatrix3x4, (), Matrix3x4), asCALL_THISCALL);
    // Matrix4 Deserializer::ReadMatrix4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Matrix4 ReadMatrix4()", asMETHODPR(HttpRequest, ReadMatrix4, (), Matrix4), asCALL_THISCALL);
    // unsigned Deserializer::ReadNetID() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "uint ReadNetID()", asMETHODPR(HttpRequest, ReadNetID, (), unsigned), asCALL_THISCALL);
    // Quaternion Deserializer::ReadPackedQuaternion() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Quaternion ReadPackedQuaternion()", asMETHODPR(HttpRequest, ReadPackedQuaternion, (), Quaternion), asCALL_THISCALL);
    // Vector3 Deserializer::ReadPackedVector3(float maxAbsCoord) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Vector3 ReadPackedVector3(float)", asMETHODPR(HttpRequest, ReadPackedVector3, (float), Vector3), asCALL_THISCALL);
    // Quaternion Deserializer::ReadQuaternion() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Quaternion ReadQuaternion()", asMETHODPR(HttpRequest, ReadQuaternion, (), Quaternion), asCALL_THISCALL);
    // Rect Deserializer::ReadRect() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Rect ReadRect()", asMETHODPR(HttpRequest, ReadRect, (), Rect), asCALL_THISCALL);
    // ResourceRef Deserializer::ReadResourceRef() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "ResourceRef ReadResourceRef()", asMETHODPR(HttpRequest, ReadResourceRef, (), ResourceRef), asCALL_THISCALL);
    // ResourceRefList Deserializer::ReadResourceRefList() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "ResourceRefList ReadResourceRefList()", asMETHODPR(HttpRequest, ReadResourceRefList, (), ResourceRefList), asCALL_THISCALL);
    // short Deserializer::ReadShort() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "int16 ReadShort()", asMETHODPR(HttpRequest, ReadShort, (), short), asCALL_THISCALL);
    // String Deserializer::ReadString() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "String ReadString()", asMETHODPR(HttpRequest, ReadString, (), String), asCALL_THISCALL);
    // StringHash Deserializer::ReadStringHash() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "StringHash ReadStringHash()", asMETHODPR(HttpRequest, ReadStringHash, (), StringHash), asCALL_THISCALL);
    // StringVector Deserializer::ReadStringVector() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Array<String>@ ReadStringVector()", asFUNCTION(HttpRequest_ReadStringVector_void), asCALL_CDECL_OBJFIRST);
    // unsigned char Deserializer::ReadUByte() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "uint8 ReadUByte()", asMETHODPR(HttpRequest, ReadUByte, (), unsigned char), asCALL_THISCALL);
    // unsigned Deserializer::ReadUInt() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "uint ReadUInt()", asMETHODPR(HttpRequest, ReadUInt, (), unsigned), asCALL_THISCALL);
    // unsigned long long Deserializer::ReadUInt64() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "uint64 ReadUInt64()", asMETHODPR(HttpRequest, ReadUInt64, (), unsigned long long), asCALL_THISCALL);
    // unsigned short Deserializer::ReadUShort() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "uint16 ReadUShort()", asMETHODPR(HttpRequest, ReadUShort, (), unsigned short), asCALL_THISCALL);
    // Variant Deserializer::ReadVariant() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Variant ReadVariant()", asMETHODPR(HttpRequest, ReadVariant, (), Variant), asCALL_THISCALL);
    // Variant Deserializer::ReadVariant(VariantType type) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Variant ReadVariant(VariantType)", asMETHODPR(HttpRequest, ReadVariant, (VariantType), Variant), asCALL_THISCALL);
    // VariantMap Deserializer::ReadVariantMap() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "VariantMap ReadVariantMap()", asMETHODPR(HttpRequest, ReadVariantMap, (), VariantMap), asCALL_THISCALL);
    // VariantVector Deserializer::ReadVariantVector() | File: ../IO/Deserializer.h
    // Error: type "VariantVector" can not automatically bind
    // Vector2 Deserializer::ReadVector2() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Vector2 ReadVector2()", asMETHODPR(HttpRequest, ReadVector2, (), Vector2), asCALL_THISCALL);
    // Vector3 Deserializer::ReadVector3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Vector3 ReadVector3()", asMETHODPR(HttpRequest, ReadVector3, (), Vector3), asCALL_THISCALL);
    // Vector4 Deserializer::ReadVector4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "Vector4 ReadVector4()", asMETHODPR(HttpRequest, ReadVector4, (), Vector4), asCALL_THISCALL);
    // unsigned Deserializer::ReadVLE() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "uint ReadVLE()", asMETHODPR(HttpRequest, ReadVLE, (), unsigned), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("HttpRequest", "int Refs() const", asMETHODPR(HttpRequest, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "int get_refs() const", asMETHODPR(HttpRequest, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("HttpRequest", asBEHAVE_RELEASE, "void f()", asMETHODPR(HttpRequest, ReleaseRef, (), void), asCALL_THISCALL);
    // bool Thread::Run() | File: ../Core/Thread.h
    engine->RegisterObjectMethod("HttpRequest", "bool Run()", asMETHODPR(HttpRequest, Run, (), bool), asCALL_THISCALL);
    // unsigned HttpRequest::Seek(unsigned position) override | File: ../Network/HttpRequest.h
    engine->RegisterObjectMethod("HttpRequest", "uint Seek(uint)", asMETHODPR(HttpRequest, Seek, (unsigned), unsigned), asCALL_THISCALL);
    // unsigned Deserializer::SeekRelative(int delta) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "uint SeekRelative(int)", asMETHODPR(HttpRequest, SeekRelative, (int), unsigned), asCALL_THISCALL);
    // static void Thread::SetMainThread() | File: ../Core/Thread.h
    engine->SetDefaultNamespace("HttpRequest");
    engine->RegisterGlobalFunction("void SetMainThread()", asFUNCTIONPR(HttpRequest::SetMainThread, (), void), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // void Thread::SetPriority(int priority) | File: ../Core/Thread.h
    engine->RegisterObjectMethod("HttpRequest", "void SetPriority(int)", asMETHODPR(HttpRequest, SetPriority, (int), void), asCALL_THISCALL);
    // void Thread::Stop() | File: ../Core/Thread.h
    engine->RegisterObjectMethod("HttpRequest", "void Stop()", asMETHODPR(HttpRequest, Stop, (), void), asCALL_THISCALL);
    // unsigned Deserializer::Tell() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("HttpRequest", "uint Tell() const", asMETHODPR(HttpRequest, Tell, () const, unsigned), asCALL_THISCALL);
    // void HttpRequest::ThreadFunction() override | File: ../Network/HttpRequest.h
    engine->RegisterObjectMethod("HttpRequest", "void ThreadFunction()", asMETHODPR(HttpRequest, ThreadFunction, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("HttpRequest", "int WeakRefs() const", asMETHODPR(HttpRequest, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("HttpRequest", "int get_weakRefs() const", asMETHODPR(HttpRequest, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("HashIteratorBase", "void GotoNext()", asMETHODPR(HashIteratorBase, GotoNext, (), void), asCALL_THISCALL);
    // void HashIteratorBase::GotoPrev() | File: ../Container/HashBase.h
    engine->RegisterObjectMethod("HashIteratorBase", "void GotoPrev()", asMETHODPR(HashIteratorBase, GotoPrev, (), void), asCALL_THISCALL);
    // explicit HashIteratorBase::HashIteratorBase(HashNodeBase* ptr) | File: ../Container/HashBase.h
    // Error: type "HashNodeBase*" can not automatically bind
    // bool HashIteratorBase::operator==(const HashIteratorBase& rhs) const | File: ../Container/HashBase.h
    engine->RegisterObjectMethod("HashIteratorBase", "bool opEquals(const HashIteratorBase&in) const", asMETHODPR(HashIteratorBase, operator==, (const HashIteratorBase&) const, bool), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("HeightfieldData", asBEHAVE_ADDREF, "void f()", asMETHODPR(HeightfieldData, AddRef, (), void), asCALL_THISCALL);
    // HeightfieldData::HeightfieldData(Terrain* terrain, unsigned lodLevel) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectBehaviour("HeightfieldData", asBEHAVE_FACTORY, "HeightfieldData@+ f(Terrain@+, uint)", asFUNCTION(HeightfieldData_HeightfieldData_Terrain_unsigned), asCALL_CDECL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("HeightfieldData", "int Refs() const", asMETHODPR(HeightfieldData, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("HeightfieldData", "int get_refs() const", asMETHODPR(HeightfieldData, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("HeightfieldData", asBEHAVE_RELEASE, "void f()", asMETHODPR(HeightfieldData, ReleaseRef, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("HeightfieldData", "int WeakRefs() const", asMETHODPR(HeightfieldData, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("HeightfieldData", "int get_weakRefs() const", asMETHODPR(HeightfieldData, WeakRefs, () const, int), asCALL_THISCALL);
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
