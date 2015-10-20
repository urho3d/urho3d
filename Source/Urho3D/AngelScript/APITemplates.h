//
// Copyright (c) 2008-2015 the Urho3D project.
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

#pragma once

#include "../AngelScript/Addons.h"
#include "../AngelScript/Script.h"
#include "../AngelScript/ScriptInstance.h"
#include "../Audio/SoundSource.h"
#include "../Core/Context.h"
#include "../Container/HashSet.h"
#include "../Container/Sort.h"
#include "../Graphics/Drawable.h"
#include "../Graphics/StaticModel.h"
#include "../Graphics/Texture.h"
#include "../IO/File.h"
#include "../IO/Log.h"
#include "../IO/VectorBuffer.h"
#include "../Resource/Resource.h"
#include "../Scene/Animatable.h"
#include "../Scene/Node.h"
#include "../UI/BorderImage.h"

#include <AngelScript/angelscript.h>
#include <cstring>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4505)
#endif

namespace Urho3D
{

class Camera;

/// Template function for dynamic cast between two script classes.
template <class T, class U> U* RefCast(T* t)
{
    if (!t)
        return 0;

    return dynamic_cast<U*>(t);
}

/// Template function for Vector to array conversion.
template <class T> CScriptArray* VectorToArray(const Vector<T>& vector, const char* arrayName)
{
    asIScriptContext* context = asGetActiveContext();
    if (context)
    {
        asIObjectType* type = GetScriptContext()->GetSubsystem<Script>()->GetObjectType(arrayName);
        CScriptArray* arr = CScriptArray::Create(type, vector.Size());

        for (unsigned i = 0; i < arr->GetSize(); ++i)
            *(static_cast<T*>(arr->At(i))) = vector[i];

        return arr;
    }
    else
        return 0;
}

/// Template function for PODVector to array conversion.
template <class T> CScriptArray* VectorToArray(const PODVector<T>& vector, const char* arrayName)
{
    asIScriptContext* context = asGetActiveContext();
    if (context)
    {
        asIObjectType* type = GetScriptContext()->GetSubsystem<Script>()->GetObjectType(arrayName);
        CScriptArray* arr = CScriptArray::Create(type, vector.Size());

        for (unsigned i = 0; i < arr->GetSize(); ++i)
            *(static_cast<T*>(arr->At(i))) = vector[i];

        return arr;
    }
    else
        return 0;
}

/// Template function for data buffer to array conversion.
template <class T> CScriptArray* BufferToArray(const T* buffer, unsigned size, const char* arrayName)
{
    asIScriptContext* context = asGetActiveContext();
    if (context)
    {
        asIObjectType* type = GetScriptContext()->GetSubsystem<Script>()->GetObjectType(arrayName);
        CScriptArray* arr = CScriptArray::Create(type, size);

        for (unsigned i = 0; i < arr->GetSize(); ++i)
            *(static_cast<T*>(arr->At(i))) = buffer[i];

        return arr;
    }
    else
        return 0;
}

/// Template function for Vector to handle array conversion.
template <class T> CScriptArray* VectorToHandleArray(const Vector<T*>& vector, const char* arrayName)
{
    asIScriptContext* context = asGetActiveContext();
    if (context)
    {
        asIObjectType* type = GetScriptContext()->GetSubsystem<Script>()->GetObjectType(arrayName);
        CScriptArray* arr = CScriptArray::Create(type, vector.Size());

        for (unsigned i = 0; i < arr->GetSize(); ++i)
        {
            // Increment reference count for storing in the array
            T* ptr = vector[i];
            if (ptr)
                ptr->AddRef();
            *(static_cast<T**>(arr->At(i))) = ptr;
        }

        return arr;
    }
    else
        return 0;
}

/// Template function for PODVector to handle array conversion.
template <class T> CScriptArray* VectorToHandleArray(const PODVector<T*>& vector, const char* arrayName)
{
    asIScriptContext* context = asGetActiveContext();
    if (context)
    {
        asIObjectType* type = GetScriptContext()->GetSubsystem<Script>()->GetObjectType(arrayName);
        CScriptArray* arr = CScriptArray::Create(type, vector.Size());

        for (unsigned i = 0; i < arr->GetSize(); ++i)
        {
            // Increment reference count for storing in the array
            T* ptr = vector[i];
            if (ptr)
                ptr->AddRef();
            *(static_cast<T**>(arr->At(i))) = ptr;
        }

        return arr;
    }
    else
        return 0;
}

/// Template function for shared pointer Vector to handle array conversion.
template <class T> CScriptArray* VectorToHandleArray(const Vector<SharedPtr<T> >& vector, const char* arrayName)
{
    asIScriptContext* context = asGetActiveContext();
    if (context)
    {
        asIObjectType* type = GetScriptContext()->GetSubsystem<Script>()->GetObjectType(arrayName);
        CScriptArray* arr = CScriptArray::Create(type, vector.Size());

        for (unsigned i = 0; i < arr->GetSize(); ++i)
        {
            // Increment reference count for storing in the array
            T* ptr = vector[i];
            if (ptr)
                ptr->AddRef();
            *(static_cast<T**>(arr->At(i))) = ptr;
        }

        return arr;
    }
    else
        return 0;
}

/// Template function for array to Vector conversion.
template <class T> Vector<T> ArrayToVector(CScriptArray* arr)
{
    Vector<T> dest(arr ? arr->GetSize() : 0);
    if (arr)
    {
        for (unsigned i = 0; i < arr->GetSize(); ++i)
            dest[i] = *static_cast<T*>(arr->At(i));
    }
    return dest;
}

/// Template function for array to PODVector conversion.
template <class T> PODVector<T> ArrayToPODVector(CScriptArray* arr)
{
    PODVector<T> dest(arr ? arr->GetSize() : 0);
    if (arr)
    {
        for (unsigned i = 0; i < arr->GetSize(); ++i)
            dest[i] = *static_cast<T*>(arr->At(i));
    }
    return dest;
}

/// Template function for registering implicit casts between base and subclass.
template <class T, class U> void RegisterSubclass(asIScriptEngine* engine, const char* classNameT, const char* classNameU)
{
    if (!strcmp(classNameT, classNameU))
        return;

    String declReturnT(String(classNameT) + "@+ opImplCast()");
    String declReturnU(String(classNameU) + "@+ opImplCast()");

    engine->RegisterObjectMethod(classNameT, declReturnU.CString(), asFUNCTION((RefCast<T, U>)), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(classNameU, declReturnT.CString(), asFUNCTION((RefCast<U, T>)), asCALL_CDECL_OBJLAST);
}

/// Template function for writing to a serializer from an array.
template <class T> unsigned SerializerWrite(CScriptArray* arr, T* ptr)
{
    unsigned bytesToWrite = arr->GetSize();
    return bytesToWrite ? ptr->Write(arr->At(0), bytesToWrite) : 0;
}

/// Template function for writing a VectorBuffer to a serializer.
template <class T> bool SerializerWriteVectorBuffer(VectorBuffer* src, T* ptr)
{
    return ptr->Write(src->GetData(), src->GetSize()) == src->GetSize();
}

/// Template function for registering a class derived from Serializer.
template <class T> void RegisterSerializer(asIScriptEngine* engine, const char* className)
{
    engine->RegisterObjectMethod(className, "uint Write(Array<uint8>@+)", asFUNCTION(SerializerWrite<T>), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "bool WriteInt(int)", asMETHODPR(T, WriteInt, (int), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteShort(int16)", asMETHODPR(T, WriteShort, (short), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteByte(int8)", asMETHODPR(T, WriteByte, (signed char), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteUInt(uint)", asMETHODPR(T, WriteUInt, (unsigned), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteUShort(uint16)", asMETHODPR(T, WriteUShort, (unsigned short), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteUByte(uint8)", asMETHODPR(T, WriteUByte, (unsigned char), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteBool(bool)", asMETHODPR(T, WriteBool, (bool), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteFloat(float)", asMETHODPR(T, WriteFloat, (float), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteDouble(double)", asMETHODPR(T, WriteDouble, (double), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteIntRect(const IntRect&in)", asMETHODPR(T, WriteIntRect, (const IntRect&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteIntVector2(const IntVector2&in)", asMETHODPR(T, WriteIntVector2, (const IntVector2&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteVector2(const Vector2&in)", asMETHODPR(T, WriteVector2, (const Vector2&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteVector3(const Vector3&in)", asMETHODPR(T, WriteVector3, (const Vector3&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WritePackedVector3(const Vector3&in, float)", asMETHODPR(T, WritePackedVector3, (const Vector3&, float), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteVector4(const Vector4&in)", asMETHODPR(T, WriteVector4, (const Vector4&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteQuaternion(const Quaternion&in)", asMETHODPR(T, WriteQuaternion, (const Quaternion&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WritePackedQuaternion(const Quaternion&in)", asMETHODPR(T, WritePackedQuaternion, (const Quaternion&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteMatrix3(const Matrix3&in)", asMETHODPR(T, WriteMatrix3, (const Matrix3&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteMatrix3x4(const Matrix3x4&in)", asMETHODPR(T, WriteMatrix3x4, (const Matrix3x4&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteMatrix4(const Matrix4&in)", asMETHODPR(T, WriteMatrix4, (const Matrix4&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteColor(const Color&in)", asMETHODPR(T, WriteColor, (const Color&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteBoundingBox(const BoundingBox&in)", asMETHODPR(T, WriteBoundingBox, (const BoundingBox&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteString(const String&in)", asMETHODPR(T, WriteString, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteFileID(const String&in)", asMETHODPR(T, WriteFileID, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteStringHash(const StringHash&in)", asMETHODPR(T, WriteStringHash, (const StringHash&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteVariant(const Variant&in)", asMETHODPR(T, WriteVariant, (const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteVariantMap(const VariantMap&in)", asMETHODPR(T, WriteVariantMap, (const VariantMap&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteVectorBuffer(const VectorBuffer&in)", asFUNCTION(SerializerWriteVectorBuffer<T>), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "bool WriteVLE(uint)", asMETHODPR(T, WriteVLE, (unsigned), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteNetID(uint)", asMETHODPR(T, WriteNetID, (unsigned), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteLine(const String&in)", asMETHODPR(T, WriteLine, (const String&), bool), asCALL_THISCALL);
}

/// Template function for reading from a deserializer into an array.
template <class T> CScriptArray* DeserializerRead(unsigned size, T* ptr)
{
    PODVector<unsigned char> vector(size);
    unsigned bytesRead = size ? ptr->Read(&vector[0], size) : 0;
    vector.Resize(bytesRead);
    return VectorToArray(vector, "Array<uint8>");
}

/// Template function for reading from a deserializer into a VectorBuffer.
template <class T> VectorBuffer DeserializerReadVectorBuffer(unsigned size, T* ptr)
{
    return VectorBuffer(*ptr, size);
}

/// Template function for registering a class derived from Deserializer.
template <class T> void RegisterDeserializer(asIScriptEngine* engine, const char* className)
{
    engine->RegisterObjectMethod(className, "Array<uint8>@ Read(uint)", asFUNCTION(DeserializerRead<T>), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "int ReadInt()", asMETHODPR(T, ReadInt, (), int), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int16 ReadShort()", asMETHODPR(T, ReadShort, (), short), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int8 ReadByte()", asMETHODPR(T, ReadByte, (), signed char), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint ReadUInt()", asMETHODPR(T, ReadUInt, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint16 ReadUShort()", asMETHODPR(T, ReadUShort, (), unsigned short), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint8 ReadUByte()", asMETHODPR(T, ReadUByte, (), unsigned char), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool ReadBool()", asMETHODPR(T, ReadBool, (), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float ReadFloat()", asMETHODPR(T, ReadFloat, (), float), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "double ReadDouble()", asMETHODPR(T, ReadDouble, (), double), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "IntRect ReadIntRect()", asMETHODPR(T, ReadIntRect, (), IntRect), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "IntVector2 ReadIntVector2()", asMETHODPR(T, ReadIntVector2, (), IntVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector2 ReadVector2()", asMETHODPR(T, ReadVector2, (), Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector3 ReadVector3()", asMETHODPR(T, ReadVector3, (), Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector3 ReadPackedVector3(float)", asMETHODPR(T, ReadPackedVector3, (float), Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector4 ReadVector4()", asMETHODPR(T, ReadVector4, (), Vector4), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Quaternion ReadQuaternion()", asMETHODPR(T, ReadQuaternion, (), Quaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Quaternion ReadPackedQuaternion()", asMETHODPR(T, ReadPackedQuaternion, (), Quaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Matrix3 ReadMatrix3()", asMETHODPR(T, ReadMatrix3, (), Matrix3), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Matrix3x4 ReadMatrix3x4()", asMETHODPR(T, ReadMatrix3x4, (), Matrix3x4), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Matrix4 ReadMatrix4()", asMETHODPR(T, ReadMatrix4, (), Matrix4), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Color ReadColor()", asMETHODPR(T, ReadColor, (), Color), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "BoundingBox ReadBoundingBox()", asMETHODPR(T, ReadBoundingBox, (), BoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "String ReadString()", asMETHODPR(T, ReadString, (), String), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "String ReadFileID()", asMETHODPR(T, ReadFileID, (), String), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "StringHash ReadStringHash()", asMETHODPR(T, ReadStringHash, (), StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Variant ReadVariant()", asMETHODPR(T, ReadVariant, (), Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "VariantMap ReadVariantMap()", asMETHODPR(T, ReadVariantMap, (), VariantMap), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "VectorBuffer ReadVectorBuffer(uint)", asFUNCTION(DeserializerReadVectorBuffer<T>), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "uint ReadVLE()", asMETHODPR(T, ReadVLE, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint ReadNetID()", asMETHODPR(T, ReadNetID, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "String ReadLine()", asMETHODPR(T, ReadLine, (), String), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint Seek(uint)", asMETHODPR(T, Seek, (unsigned), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const String& get_name() const", asMETHODPR(T, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_checksum()", asMETHODPR(T, GetChecksum, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_position() const", asMETHODPR(T, GetPosition, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_size() const", asMETHODPR(T, GetSize, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_eof() const", asMETHODPR(T, IsEof, () const, bool), asCALL_THISCALL);
}

/// Template function for registering a class derived from RefCounted.
template <class T> void RegisterRefCounted(asIScriptEngine* engine, const char* className)
{
    engine->RegisterObjectType(className, 0, asOBJ_REF);
    engine->RegisterObjectBehaviour(className, asBEHAVE_ADDREF, "void f()", asMETHODPR(T, AddRef, (), void), asCALL_THISCALL);
    engine->RegisterObjectBehaviour(className, asBEHAVE_RELEASE, "void f()", asMETHODPR(T, ReleaseRef, (), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_refs() const", asMETHODPR(T, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_weakRefs() const", asMETHODPR(T, WeakRefs, () const, int), asCALL_THISCALL);
    RegisterSubclass<RefCounted, T>(engine, "RefCounted", className);
}

template <class T> void ObjectSendEvent(const String& eventType, VariantMap& eventData, T* ptr)
{
    if (ptr)
        ptr->SendEvent(StringHash(eventType), eventData);
}

/// Template function for registering a class derived from Object.
template <class T> void RegisterObject(asIScriptEngine* engine, const char* className)
{
    RegisterRefCounted<T>(engine, className);
    engine->RegisterObjectMethod(className, "StringHash get_type() const", asMETHODPR(T, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const String& get_typeName() const", asMETHODPR(T, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const String& get_category() const", asMETHODPR(T, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SendEvent(const String&in, VariantMap& eventData = VariantMap())", asFUNCTION(ObjectSendEvent<T>), asCALL_CDECL_OBJLAST);
    RegisterSubclass<Object, T>(engine, "Object", className);
}

template <class T> T* ConstructObject()
{
    return new T(GetScriptContext());
}

template <class T> T* ConstructNamedObject(const String& name)
{
    T* object = new T(GetScriptContext());
    object->SetName(name);
    return object;
}

/// Template function for registering a default constructor for a class derived from Object.
template <class T> void RegisterObjectConstructor(asIScriptEngine* engine, const char* className)
{
    String declFactory(String(className) + "@+ f()");
    engine->RegisterObjectBehaviour(className, asBEHAVE_FACTORY, declFactory.CString(), asFUNCTION(ConstructObject<T>), asCALL_CDECL);
}

/// Template function for registering a named constructor for a class derived from Object.
template <class T> void RegisterNamedObjectConstructor(asIScriptEngine* engine, const char* className)
{
    String declFactoryWithName(String(className) + "@+ f(const String&in)");
    engine->RegisterObjectBehaviour(className, asBEHAVE_FACTORY, declFactoryWithName.CString(), asFUNCTION(ConstructNamedObject<T>), asCALL_CDECL);
}

static const AttributeInfo noAttributeInfo;

// To keep Xcode LLVM/Clang happy - it erroneosly warns on unused functions defined below which are actually being referenced in the code
#if __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
#endif

static const AttributeInfo& SerializableGetAttributeInfo(unsigned index, Serializable* ptr)
{
    const Vector<AttributeInfo>* attributes = ptr->GetAttributes();
    if (!attributes || index >= attributes->Size())
    {
        asGetActiveContext()->SetException("Index out of bounds");
        return noAttributeInfo;
    }
    else
        return attributes->At(index);
}

static bool SerializableLoad(File* file, bool setInstanceDefault, Serializable* ptr)
{
    return file && ptr->Load(*file, setInstanceDefault);
}

static bool SerializableLoadVectorBuffer(VectorBuffer& buffer, bool setInstanceDefault, Serializable* ptr)
{
    return ptr->Load(buffer, setInstanceDefault);
}

static bool SerializableSave(File* file, Serializable* ptr)
{
    return file && ptr->Save(*file);
}

static bool SerializableSaveVectorBuffer(VectorBuffer& buffer, Serializable* ptr)
{
    return ptr->Save(buffer);
}

/// Template function for registering a class derived from Serializable.
template <class T> void RegisterSerializable(asIScriptEngine* engine, const char* className)
{
    RegisterObject<T>(engine, className);
    engine->RegisterObjectMethod(className, "bool Load(File@+, bool setInstanceDefault = false)", asFUNCTION(SerializableLoad), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "bool Load(VectorBuffer&, bool setInstanceDefault = false)", asFUNCTION(SerializableLoadVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "bool Save(File@+) const", asFUNCTION(SerializableSave), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "bool Save(VectorBuffer&) const", asFUNCTION(SerializableSaveVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "bool LoadXML(const XMLElement&, bool setInstanceDefault = false)", asMETHODPR(T, LoadXML, (const XMLElement&, bool), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool SaveXML(XMLElement&) const", asMETHODPR(T, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void MarkNetworkUpdate() const", asMETHODPR(T, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void ApplyAttributes()", asMETHODPR(T, ApplyAttributes, (), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(T, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void ResetToDefault()", asMETHOD(T, ResetToDefault), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void RemoveInstanceDefault()", asMETHOD(T, RemoveInstanceDefault), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Variant GetAttribute(const String&in) const", asMETHODPR(T, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Variant GetAttributeDefault(const String&in) const", asMETHODPR(T, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(T, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(T, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_numAttributes() const", asMETHODPR(T, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool set_attributes(uint, const Variant&in) const", asMETHODPR(T, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Variant get_attributes(uint) const", asMETHODPR(T, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Variant get_attributeDefaults(uint) const", asMETHODPR(T, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const AttributeInfo& get_attributeInfos(uint) const", asFUNCTION(SerializableGetAttributeInfo), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "void set_temporary(bool)", asMETHODPR(T, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_temporary() const", asMETHODPR(T, IsTemporary, () const, bool), asCALL_THISCALL);
    RegisterSubclass<Object, T>(engine, "Serializable", className);
}

/// Template function for registering a class derived from Animatable.
template <class T> void RegisterAnimatable(asIScriptEngine* engine, const char* className)
{
    RegisterSerializable<T>(engine, className);
    RegisterSubclass<Animatable, T>(engine, "Animatable", className);

    engine->RegisterObjectMethod(className, "void set_animationEnabled(bool)", asMETHODPR(T, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_animationEnabled() const", asMETHODPR(T, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(T, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(T, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode wrapMode=WM_LOOP, float speed=1.0f)", asMETHODPR(T, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(T, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(T, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(T, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(T, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(T, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void RemoveObjectAnimation()", asMETHODPR(T, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void RemoveAttributeAnimation(const String&in)", asMETHODPR(T, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetAnimationTime(float time)", asMETHODPR(T, SetAnimationTime, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(T, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(T, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
}

/// Template function for registering a class derived from Component.
template <class T> void RegisterComponent(asIScriptEngine* engine, const char* className, bool nodeRegistered = true, bool debugRendererRegistered = true)
{
    RegisterAnimatable<T>(engine, className);
    RegisterSubclass<Component, T>(engine, "Component", className);
    engine->RegisterObjectMethod(className, "void Remove()", asMETHODPR(T, Remove, (), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_enabled(bool)", asMETHODPR(T, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_enabled() const", asMETHODPR(T, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_enabledEffective() const", asMETHODPR(T, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_id()", asMETHODPR(T, GetID, () const, unsigned), asCALL_THISCALL);
    if (nodeRegistered)
        engine->RegisterObjectMethod(className, "Node@+ get_node() const", asMETHODPR(T, GetNode, () const, Node*), asCALL_THISCALL);
    if (debugRendererRegistered)
        engine->RegisterObjectMethod(className, "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(T, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
}

static Component* NodeCreateComponent(const String& typeName, CreateMode mode, unsigned id, Node* ptr)
{
    return ptr->CreateComponent(typeName, mode, id);
}

static Component* NodeGetOrCreateComponent(const String& typeName, CreateMode mode, unsigned id, Node* ptr)
{
    return ptr->GetOrCreateComponent(typeName, mode, id);
}

static void NodeRemoveComponent(const String& typeName, Node* ptr)
{
    ptr->RemoveComponent(typeName);
}

static void NodeRemoveComponents(const String& typeName, Node* ptr)
{
    ptr->RemoveComponents(typeName);
}

static Component* NodeGetComponent(unsigned index, Node* ptr)
{
    const Vector<SharedPtr<Component> >& components = ptr->GetComponents();
    if (index >= components.Size())
    {
        asGetActiveContext()->SetException("Index out of bounds");
        return 0;
    }
    else
        return components[index];
}

static Component* NodeGetComponentWithType(const String& typeName, bool recursive, Node* ptr)
{
    return ptr->GetComponent(typeName, recursive);
}

static Component* NodeGetParentComponentWithType(const String& typeName, bool fullTraversal, Node* ptr)
{
    return ptr->GetParentComponent(typeName, fullTraversal);
}

static CScriptArray* NodeGetComponents(Node* ptr)
{
    return VectorToHandleArray<Component>(ptr->GetComponents(), "Array<Component@>");
}

static CScriptArray* NodeGetComponentsWithType(const String& typeName, bool recursive, Node* ptr)
{
    PODVector<Component*> components;
    ptr->GetComponents(components, typeName, recursive);
    return VectorToHandleArray<Component>(components, "Array<Component@>");
}

static bool NodeHasComponent(const String& typeName, Node* ptr)
{
    return ptr->HasComponent(typeName);
}

static CScriptArray* NodeGetChildren(bool recursive, Node* ptr)
{
    PODVector<Node*> nodes;
    ptr->GetChildren(nodes, recursive);
    return VectorToHandleArray<Node>(nodes, "Array<Node@>");
}

static CScriptArray* NodeGetChildrenWithComponent(const String& typeName, bool recursive, Node* ptr)
{
    PODVector<Node*> nodes;
    ptr->GetChildrenWithComponent(nodes, typeName, recursive);
    return VectorToHandleArray<Node>(nodes, "Array<Node@>");
}

static unsigned NodeGetNumChildrenNonRecursive(Node* ptr)
{
    return ptr->GetNumChildren(false);
}

static unsigned NodeGetNumChildrenRecursive(Node* ptr)
{
    return ptr->GetNumChildren(true);
}

static Node* NodeGetChild(unsigned index, Node* ptr)
{
    const Vector<SharedPtr<Node> >& children = ptr->GetChildren();
    if (index >= children.Size())
    {
        asGetActiveContext()->SetException("Index out of bounds");
        return 0;
    }
    else
        return children[index].Get();
}

static CScriptArray* NodeGetChildrenWithScript(bool recursive, Node* ptr)
{
    PODVector<Node*> nodes;
    ptr->GetChildrenWithComponent<ScriptInstance>(nodes, recursive);
    return VectorToHandleArray<Node>(nodes, "Array<Node@>");
}

static CScriptArray* NodeGetChildrenWithClassName(const String& className, bool recursive, Node* ptr)
{
    PODVector<Node*> nodes;
    PODVector<Node*> result;

    ptr->GetChildrenWithComponent<ScriptInstance>(nodes, recursive);
    for (PODVector<Node*>::Iterator i = nodes.Begin(); i != nodes.End(); ++i)
    {
        Node* node = *i;
        const Vector<SharedPtr<Component> >& components = node->GetComponents();
        for (Vector<SharedPtr<Component> >::ConstIterator j = components.Begin(); j != components.End(); ++j)
        {
            if ((*j)->IsInstanceOf<ScriptInstance>())
            {
                ScriptInstance* instance = static_cast<ScriptInstance*>(j->Get());
                if (instance->IsA(className))
                    result.Push(node);
            }
        }
    }

    return VectorToHandleArray<Node>(result, "Array<Node@>");
}

static VariantMap& NodeGetVars(Node* ptr)
{
    // Assume that the vars will be modified and queue a network update attribute check
    ptr->MarkNetworkUpdate();
    return const_cast<VariantMap&>(ptr->GetVars());
}

/// Template function for registering a class derived from Node.
template <class T> void RegisterNode(asIScriptEngine* engine, const char* className)
{
    RegisterAnimatable<T>(engine, className);
    RegisterSubclass<Node, T>(engine, "Node", className);
    engine->RegisterObjectMethod(className, "void SetPosition2D(float, float)", asMETHODPR(T, SetPosition2D, (float, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetScale(float)", asMETHODPR(T, SetScale, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetScale2D(float, float)", asMETHODPR(T, SetScale2D, (float, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetTransform(const Vector3&in, const Quaternion&in)", asMETHODPR(T, SetTransform, (const Vector3&, const Quaternion&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetTransform(const Vector3&in, const Quaternion&in, const Vector3&in)", asMETHODPR(T, SetTransform, (const Vector3&, const Quaternion&, const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetTransform(const Vector3&in, const Quaternion&in, float)", asMETHODPR(T, SetTransform, (const Vector3&, const Quaternion&, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetTransform2D(const Vector2&in, float)", asMETHODPR(T, SetTransform2D, (const Vector2&, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetTransform2D(const Vector2&in, float, const Vector2&in)", asMETHODPR(T, SetTransform2D, (const Vector2&, float, const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetTransform2D(const Vector2&in, float, float)", asMETHODPR(T, SetTransform2D, (const Vector2&, float, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetWorldTransform(const Vector3&in, const Quaternion&in)", asMETHODPR(T, SetWorldTransform, (const Vector3&, const Quaternion&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetWorldTransform(const Vector3&in, const Quaternion&in, const Vector3&in)", asMETHODPR(T, SetWorldTransform, (const Vector3&, const Quaternion&, const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetWorldTransform(const Vector3&in, const Quaternion&in, float)", asMETHODPR(T, SetWorldTransform, (const Vector3&, const Quaternion&, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetWorldTransform2D(const Vector2&in, float)", asMETHODPR(T, SetWorldTransform2D, (const Vector2&, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetWorldTransform2D(const Vector2&in, float, const Vector2&in)", asMETHODPR(T, SetWorldTransform2D, (const Vector2&, float, const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetWorldTransform2D(const Vector2&in, float, float)", asMETHODPR(T, SetWorldTransform2D, (const Vector2&, float, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void Translate(const Vector3&in, TransformSpace space = TS_LOCAL)", asMETHODPR(T, Translate, (const Vector3&, TransformSpace), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void Translate2D(const Vector2&in, TransformSpace space = TS_LOCAL)", asMETHODPR(T, Translate2D, (const Vector2&, TransformSpace), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void Rotate(const Quaternion&in, TransformSpace space = TS_LOCAL)", asMETHODPR(T, Rotate, (const Quaternion&, TransformSpace), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void Rotate2D(float, TransformSpace space = TS_LOCAL)", asMETHODPR(T, Rotate2D, (float, TransformSpace), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void RotateAround(const Vector3&in, const Quaternion&in, TransformSpace space = TS_LOCAL)", asMETHODPR(T, RotateAround, (const Vector3&, const Quaternion&, TransformSpace), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void RotateAround2D(const Vector2&in, float, TransformSpace space = TS_LOCAL)", asMETHODPR(T, RotateAround2D, (const Vector2&, float, TransformSpace), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void Pitch(float, TransformSpace space = TS_LOCAL)", asMETHOD(T, Pitch), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void Yaw(float, TransformSpace space = TS_LOCAL)", asMETHOD(T, Yaw), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void Roll(float, TransformSpace space = TS_LOCAL)", asMETHOD(T, Roll), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool LookAt(const Vector3&in, const Vector3&in up = Vector3(0, 1, 0), TransformSpace space = TS_WORLD)", asMETHOD(T, LookAt), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void Scale(float)", asMETHODPR(T, Scale, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void Scale(const Vector3&in)", asMETHODPR(T, Scale, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void Scale2D(const Vector2&in)", asMETHODPR(T, Scale2D, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Node@+ CreateChild(const String&in name = String(), CreateMode mode = REPLICATED, uint id = 0)", asMETHODPR(T, CreateChild, (const String&, CreateMode, unsigned), Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void AddChild(Node@+, uint index = M_MAX_UNSIGNED)", asMETHOD(T, AddChild), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void RemoveChild(Node@+)", asMETHODPR(T, RemoveChild, (Node*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void RemoveAllChildren()", asMETHOD(T, RemoveAllChildren), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void RemoveChildren(bool, bool, bool)", asMETHOD(T, RemoveChildren), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void Remove()", asMETHOD(T, Remove), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Component@+ CreateComponent(const String&in, CreateMode mode = REPLICATED, uint id = 0)", asFUNCTION(NodeCreateComponent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "Component@+ GetOrCreateComponent(const String&in, CreateMode mode = REPLICATED, uint id = 0)", asFUNCTION(NodeGetOrCreateComponent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "Component@+ CloneComponent(Component@+, uint id = 0)", asMETHODPR(T, CloneComponent, (Component*, unsigned), Component*), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Component@+ CloneComponent(Component@+, CreateMode, uint id = 0)", asMETHODPR(T, CloneComponent, (Component*, CreateMode, unsigned), Component*), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void RemoveComponent(Component@+)", asMETHODPR(T, RemoveComponent, (Component*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void RemoveComponent(const String&in)", asFUNCTION(NodeRemoveComponent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "void RemoveComponents(bool, bool)", asMETHODPR(T, RemoveComponents, (bool, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void RemoveComponents(const String&in)", asFUNCTION(NodeRemoveComponents), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "void RemoveAllComponents()", asMETHOD(T, RemoveAllComponents), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Array<Node@>@ GetChildren(bool recursive = false) const", asFUNCTION(NodeGetChildren), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "Array<Node@>@ GetChildrenWithComponent(const String&in, bool recursive = false) const", asFUNCTION(NodeGetChildrenWithComponent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "Array<Node@>@ GetChildrenWithScript(bool recursive = false) const", asFUNCTION(NodeGetChildrenWithScript), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "Array<Node@>@ GetChildrenWithScript(const String&in, bool recursive = false) const", asFUNCTION(NodeGetChildrenWithClassName), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "Node@+ GetChild(const String&in, bool recursive = false) const", asMETHODPR(T, GetChild, (const String&, bool) const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Array<Component@>@ GetComponents() const", asFUNCTION(NodeGetComponents), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "Array<Component@>@ GetComponents(const String&in, bool recursive = false) const", asFUNCTION(NodeGetComponentsWithType), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "Component@+ GetComponent(const String&in, bool recursive = false) const", asFUNCTION(NodeGetComponentWithType), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "Component@+ GetParentComponent(const String&in, bool fullTraversal = false) const", asFUNCTION(NodeGetParentComponentWithType), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "bool HasComponent(const String&in) const", asFUNCTION(NodeHasComponent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "Vector3 LocalToWorld(const Vector3&in) const", asMETHODPR(T, LocalToWorld, (const Vector3&) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector3 LocalToWorld(const Vector4&in) const", asMETHODPR(T, LocalToWorld, (const Vector4&) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector2 LocalToWorld2D(const Vector2&in) const", asMETHODPR(T, LocalToWorld2D, (const Vector2&) const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector3 WorldToLocal(const Vector3&in) const", asMETHODPR(T, WorldToLocal, (const Vector3&) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector3 WorldToLocal(const Vector4&in) const", asMETHODPR(T, WorldToLocal, (const Vector4&) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector2 WorldToLocal2D(const Vector2&in) const", asMETHODPR(T, WorldToLocal2D, (const Vector2&) const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_position(const Vector3&in)", asMETHODPR(T, SetPosition, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Vector3& get_position() const", asMETHOD(T, GetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_position2D(const Vector2&in)", asMETHODPR(T, SetPosition2D, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector2 get_position2D() const", asMETHOD(T, GetPosition2D), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_rotation(const Quaternion&in)", asMETHODPR(T, SetRotation, (const Quaternion&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Quaternion& get_rotation() const", asMETHOD(T, GetRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_rotation2D(float)", asMETHODPR(T, SetRotation2D, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_rotation2D() const", asMETHOD(T, GetRotation2D), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_direction(const Vector3&in)", asMETHOD(T, SetDirection), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector3 get_direction() const", asMETHOD(T, GetDirection), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector3 get_up() const", asMETHOD(T, GetUp), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector3 get_right() const", asMETHOD(T, GetRight), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_scale(const Vector3&in)", asMETHODPR(T, SetScale, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Vector3& get_scale() const", asMETHOD(T, GetScale), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_scale2D(const Vector2&in)", asMETHODPR(T, SetScale2D, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector2 get_scale2D() const", asMETHOD(T, GetScale2D), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_worldPosition(const Vector3&in)", asMETHODPR(T, SetWorldPosition, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector3 get_worldPosition()", asMETHOD(T, GetWorldPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_worldPosition2D(const Vector2&in)", asMETHODPR(T, SetWorldPosition2D, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector2 get_worldPosition2D()", asMETHOD(T, GetWorldPosition2D), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_worldRotation(const Quaternion&in)", asMETHODPR(T, SetWorldRotation, (const Quaternion&in), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Quaternion get_worldRotation()", asMETHOD(T, GetWorldRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_worldRotation2D(float)", asMETHODPR(T, SetWorldRotation2D, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_worldRotation2D()", asMETHOD(T, GetWorldRotation2D), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_worldDirection(const Vector3&in)", asMETHOD(T, SetWorldDirection), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector3 get_worldDirection()", asMETHOD(T, GetWorldDirection), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector3 get_worldUp()", asMETHOD(T, GetWorldUp), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector3 get_worldRight()", asMETHOD(T, GetWorldRight), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_worldScale(const Vector3&in)", asMETHODPR(T, SetWorldScale, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector3 get_worldScale()", asMETHOD(T, GetWorldScale), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_worldScale2D(const Vector2&in)", asMETHODPR(T, SetWorldScale2D, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector2 get_worldScale2D()", asMETHOD(T, GetWorldScale2D), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Matrix3x4 get_transform() const", asMETHOD(T, GetTransform), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Matrix3x4& get_worldTransform() const", asMETHOD(T, GetWorldTransform), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_id()", asMETHOD(T, GetID), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_numChildren() const", asFUNCTION(NodeGetNumChildrenNonRecursive), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "uint get_numAllChildren() const", asFUNCTION(NodeGetNumChildrenRecursive), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "Node@+ get_children(uint) const", asFUNCTION(NodeGetChild), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "uint get_numComponents() const", asMETHOD(T, GetNumComponents), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Component@+ get_components(uint) const", asFUNCTION(NodeGetComponent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "void set_name(const String&in)", asMETHOD(T, SetName), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const String& get_name() const", asMETHOD(T, GetName), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_parent(Node@+)", asMETHOD(T, SetParent), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Node@+ get_parent() const", asMETHOD(T, GetParent), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "VariantMap& get_vars()", asFUNCTION(NodeGetVars), asCALL_CDECL_OBJLAST);
}

static bool ResourceLoad(File* file, XMLFile* ptr)
{
    return file && ptr->Load(*file);
}

static bool ResourceLoadVectorBuffer(VectorBuffer& buffer, XMLFile* ptr)
{
    return ptr->Load(buffer);
}

static bool ResourceSave(File* file, XMLFile* ptr)
{
    return file && ptr->Save(*file);
}

static bool ResourceSaveVectorBuffer(VectorBuffer& buffer, XMLFile* ptr)
{
    return ptr->Save(buffer);
}

/// Template function for registering a class derived from Resource.
template <class T> void RegisterResource(asIScriptEngine* engine, const char* className)
{
    RegisterObject<T>(engine, className);
    RegisterSubclass<Resource, T>(engine, "Resource", className);
    // Do not register factory for the base class
    if (strcmp("Resource", className))
    {
        RegisterObjectConstructor<T>(engine, className);
        RegisterNamedObjectConstructor<T>(engine, className);
    }
    engine->RegisterObjectMethod(className, "bool Load(File@+)", asFUNCTION(ResourceLoad), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "bool Load(VectorBuffer&)", asFUNCTION(ResourceLoadVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "bool Save(File@+) const", asFUNCTION(ResourceSave), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "bool Save(VectorBuffer&) const", asFUNCTION(ResourceSaveVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "void set_name(const String&in) const", asMETHODPR(T, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const String& get_name() const", asMETHODPR(T, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_memoryUse() const", asMETHODPR(T, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_useTimer()" ,asMETHODPR(T, GetUseTimer, (), unsigned), asCALL_THISCALL);
}

/// Template function for registering a class derived from Drawable.
template <class T> void RegisterDrawable(asIScriptEngine* engine, const char* className)
{
    RegisterComponent<T>(engine, className);
    RegisterSubclass<Drawable, T>(engine, "Drawable", className);
    engine->RegisterObjectMethod(className, "bool IsInView(Camera@+) const", asMETHODPR(Drawable, IsInView, (Camera*) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_inView() const", asMETHODPR(Drawable, IsInView, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_castShadows(bool)", asMETHOD(T, SetCastShadows), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_castShadows() const", asMETHOD(T, GetCastShadows), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_occluder(bool)", asMETHOD(T, SetOccluder), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_occluder() const", asMETHOD(T, IsOccluder), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_occludee(bool)", asMETHOD(T, SetOccludee), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_occludee() const", asMETHOD(T, IsOccludee), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_drawDistance(float)", asMETHOD(T, SetDrawDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_drawDistance() const", asMETHOD(T, GetDrawDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_shadowDistance(float)", asMETHOD(T, SetShadowDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_shadowDistance() const", asMETHOD(T, GetShadowDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_lodBias(float)", asMETHOD(T, SetLodBias), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_lodBias() const", asMETHOD(T, GetLodBias), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_viewMask(uint)", asMETHOD(T, SetViewMask), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_viewMask() const", asMETHOD(T, GetViewMask), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_lightMask(uint)", asMETHOD(T, SetLightMask), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_lightMask() const", asMETHOD(T, GetLightMask), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_shadowMask(uint)", asMETHOD(T, SetShadowMask), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_shadowMask() const", asMETHOD(T, GetShadowMask), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_zoneMask(uint)", asMETHOD(T, SetZoneMask), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_zoneMask() const", asMETHOD(T, GetZoneMask), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_maxLights(uint)", asMETHOD(T, SetMaxLights), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_maxLights() const", asMETHOD(T, GetMaxLights), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const BoundingBox& get_boundingBox() const", asMETHOD(T, GetBoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const BoundingBox& get_worldBoundingBox()", asMETHOD(T, GetWorldBoundingBox), asCALL_THISCALL);
}

/// Template function for registering a class derived from SoundSource.
template <class T> void RegisterSoundSource(asIScriptEngine* engine, const char* className)
{
    RegisterComponent<T>(engine, className);
    RegisterSubclass<SoundSource, T>(engine, "SoundSource", className);
    engine->RegisterObjectMethod(className, "void Play(Sound@+)", asMETHODPR(T, Play, (Sound*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void Play(Sound@+, float)", asMETHODPR(T, Play, (Sound*, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void Play(Sound@+, float, float)", asMETHODPR(T, Play, (Sound*, float, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void Play(Sound@+, float, float, float)", asMETHODPR(T, Play, (Sound*, float, float, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void Stop()", asMETHOD(T, Stop), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_soundType(const String&in)", asMETHOD(T, SetSoundType), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "String get_soundType() const", asMETHOD(T, GetSoundType), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_frequency(float)", asMETHOD(T, SetFrequency), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_frequency() const", asMETHOD(T, GetFrequency), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_gain(float)", asMETHOD(T, SetGain), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_gain() const", asMETHOD(T, GetGain), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_panning(float)", asMETHOD(T, SetPanning), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_panning() const", asMETHOD(T, GetPanning), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Sound@+ get_sound() const", asMETHOD(T, GetSound), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_timePosition() const", asMETHOD(T, GetTimePosition), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_attenuation() const", asMETHOD(T, GetAttenuation), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_autoRemove(bool)", asMETHOD(T, SetAutoRemove), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_autoRemove() const", asMETHOD(T, GetAutoRemove), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_playing() const", asMETHOD(T, IsPlaying), asCALL_THISCALL);
}

/// Template function for registering a class derived from Texture.
template <class T> void RegisterTexture(asIScriptEngine* engine, const char* className)
{
    RegisterResource<T>(engine, className);
    RegisterSubclass<Texture, T>(engine, "Texture", className);
    engine->RegisterObjectMethod(className, "void SetNumLevels(uint)", asMETHOD(T, SetNumLevels), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void ClearDataLost()", asMETHODPR(T, ClearDataLost, (), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "TextureUsage get_usage() const", asMETHOD(T, GetUsage), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_format() const", asMETHOD(T, GetFormat), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_compressed() const", asMETHOD(T, IsCompressed), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_levels() const", asMETHOD(T, GetLevels), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_width() const", asMETHOD(T, GetWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_height() const", asMETHOD(T, GetHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_levelWidth(uint) const", asMETHOD(T, GetLevelWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_levelHeight(uint) const", asMETHOD(T, GetLevelHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_filterMode(TextureFilterMode)", asMETHOD(T, SetFilterMode), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "TextureFilterMode get_filterMode() const", asMETHOD(T, GetFilterMode), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_addressMode(TextureCoordinate, TextureAddressMode)", asMETHOD(T, SetAddressMode), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "TextureAddressMode get_addressMode(TextureCoordinate) const", asMETHOD(T, GetAddressMode), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_borderColor(const Color&in)", asMETHOD(T, SetBorderColor), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Color& get_borderColor() const", asMETHOD(T, GetBorderColor), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_sRGB(bool)", asMETHOD(T, SetSRGB), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_sRGB() const", asMETHOD(T, GetSRGB), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_backupTexture(Texture@+)", asMETHOD(T, SetBackupTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Texture@+ get_backupTexture() const", asMETHOD(T, GetBackupTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_mipsToSkip(int, int)", asMETHOD(T, SetMipsToSkip), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_mipsToSkip(int) const", asMETHOD(T, GetMipsToSkip), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_dataLost() const", asMETHODPR(T, IsDataLost, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_components() const", asMETHOD(T, GetComponents), asCALL_THISCALL);
}

/// Template function for registering a class derived from StaticModel.
template <class T> void RegisterStaticModel(asIScriptEngine* engine, const char* className, bool registerSetModel)
{
    RegisterDrawable<T>(engine, className);
    RegisterSubclass<StaticModel, T>(engine, "StaticModel", className);
    engine->RegisterObjectMethod(className, "void ApplyMaterialList(const String&in fileName = String())", asMETHOD(T, ApplyMaterialList), asCALL_THISCALL);
    if (registerSetModel)
        engine->RegisterObjectMethod(className, "void set_model(Model@+)", asMETHOD(T, SetModel), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Model@+ get_model() const", asMETHOD(T, GetModel), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_material(Material@+)", asMETHODPR(T, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool set_materials(uint, Material@+)", asMETHODPR(T, SetMaterial, (unsigned, Material*), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Material@+ get_materials(uint) const", asMETHOD(T, GetMaterial), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_numGeometries() const", asMETHOD(T, GetNumGeometries), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Zone@+ get_zone() const", asMETHOD(T, GetZone), asCALL_THISCALL);
}

static bool UIElementLoadXML(File* file, UIElement* ptr)
{
    return file && ptr->LoadXML(*file);
}

static bool UIElementLoadXMLVectorBuffer(VectorBuffer& buffer, UIElement* ptr)
{
    return ptr->LoadXML(buffer);
}

static bool UIElementLoadXML(XMLFile* file, XMLFile* styleFile, UIElement* ptr)
{
    if (file)
    {
        XMLElement rootElem = file->GetRoot("element");
        return rootElem && ptr->LoadXML(rootElem, styleFile);
    }
    else
        return false;
}

static bool UIElementLoadChildXML(XMLFile* file, XMLFile* styleFile, UIElement* ptr)
{
    if (file)
    {
        XMLElement rootElem = file->GetRoot("element");
        return rootElem && ptr->LoadChildXML(rootElem, styleFile);
    }
    else
        return false;
}

static bool UIElementSaveXML(File* file, const String& indentation, UIElement* ptr)
{
    return file && ptr->SaveXML(*file);
}

static bool UIElementSaveXMLVectorBuffer(VectorBuffer& buffer, const String& indentation, UIElement* ptr)
{
    return ptr->SaveXML(buffer);
}

static UIElement* UIElementCreateChild(const String& typeName, const String& name, unsigned index, UIElement* ptr)
{
    return ptr->CreateChild(typeName, name, index);
}

static void UIElementRemoveChild(UIElement* child, unsigned index, UIElement* ptr)
{
    ptr->RemoveChild(child, index);
}

static void UIElementRemoveChild(unsigned index, UIElement* ptr)
{
    ptr->RemoveChildAtIndex(index);
}

static CScriptArray* UIElementGetChildren(bool recursive, UIElement* ptr)
{
    PODVector<UIElement*> elements;
    ptr->GetChildren(elements, recursive);
    return VectorToHandleArray<UIElement>(elements, "Array<UIElement@>");
}

static unsigned UIElementGetNumChildrenNonRecursive(UIElement* ptr)
{
    return ptr->GetNumChildren(false);
}

static unsigned UIElementGetNumChildrenRecursive(UIElement* ptr)
{
    return ptr->GetNumChildren(true);
}

static void UIElementSetParent(UIElement* parent, UIElement* ptr)
{
    ptr->SetParent(parent);
}

static VariantMap& UIElementGetVars(UIElement* ptr)
{
    return const_cast<VariantMap&>(ptr->GetVars());
}

static void UIElementSetStyle(const String& styleName, UIElement* ptr)
{
    if (styleName.Empty())
        ptr->SetStyleAuto();
    else
        ptr->SetStyle(styleName);
}

static XMLFile* UIElementGetDefaultStyle(UIElement* ptr)
{
    return ptr->GetDefaultStyle();
}

#if __clang__
#pragma clang diagnostic pop
#endif

/// Template function for registering a class derived from UIElement.
template <class T> void RegisterUIElement(asIScriptEngine* engine, const char* className, bool isSprite = false)
{
    RegisterAnimatable<T>(engine, className);
    RegisterObjectConstructor<T>(engine, className);
    RegisterNamedObjectConstructor<T>(engine, className);
    RegisterSubclass<UIElement, T>(engine, "UIElement", className);
    engine->RegisterObjectMethod(className, "bool LoadXML(const XMLElement&in, XMLFile@+, bool arg2 = false)", asMETHODPR(T, LoadXML, (const XMLElement&, XMLFile*, bool), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool LoadXML(File@+)", asFUNCTIONPR(UIElementLoadXML, (File*, UIElement*), bool), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "bool LoadXML(VectorBuffer&)", asFUNCTIONPR(UIElementLoadXMLVectorBuffer, (VectorBuffer&, UIElement*), bool), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "bool LoadXML(XMLFile@+, XMLFile@+)", asFUNCTIONPR(UIElementLoadXML, (XMLFile*, XMLFile*, UIElement*), bool), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "bool LoadChildXML(const XMLElement&in, XMLFile@+ arg1 = null, bool arg2 = false)", asMETHOD(T, LoadChildXML), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool LoadChildXML(XMLFile@+, XMLFile@+ arg1 = null)", asFUNCTION(UIElementLoadChildXML), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "bool SaveXML(File@+, const String&in indentation = \"\t\")", asFUNCTION(UIElementSaveXML), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "bool SaveXML(VectorBuffer&, const String&in indentation = \"\t\")", asFUNCTION(UIElementSaveXMLVectorBuffer), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "bool SetStyle(const XMLElement&in)", asMETHODPR(T, SetStyle, (const XMLElement&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool SetStyle(const String&in, XMLFile@+ arg1 = null)", asMETHODPR(T, SetStyle, (const String&, XMLFile*), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool SetStyleAuto(XMLFile@+ arg0 = null)", asMETHOD(T, SetStyleAuto), asCALL_THISCALL);
    if (!isSprite)
        engine->RegisterObjectMethod(className, "void SetPosition(int, int)", asMETHODPR(UIElement, SetPosition, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetSize(int, int)", asMETHODPR(T, SetSize, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetMinSize(int, int)", asMETHODPR(T, SetMinSize, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetMaxSize(int, int)", asMETHODPR(T, SetMaxSize, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetFixedSize(int, int)", asMETHODPR(T, SetFixedSize, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetFixedWidth(int)", asMETHOD(T, SetFixedWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetFixedHeight(int)", asMETHOD(T, SetFixedHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetAlignment(HorizontalAlignment, VerticalAlignment)", asMETHOD(T, SetAlignment), asCALL_THISCALL);
    if (!isSprite)
    {
        engine->RegisterObjectMethod(className, "void SetLayout(LayoutMode, int spacing = 0, const IntRect& border = IntRect(0, 0, 0, 0))", asMETHOD(T, SetLayout), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "void UpdateLayout()", asMETHOD(T, UpdateLayout), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "void DisableLayoutUpdate()", asMETHOD(T, DisableLayoutUpdate), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "void EnableLayoutUpdate()", asMETHOD(T, EnableLayoutUpdate), asCALL_THISCALL);
    }
    engine->RegisterObjectMethod(className, "void BringToFront()", asMETHOD(T, BringToFront), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "UIElement@+ CreateChild(const String&in, const String&in name = String(), uint index = M_MAX_UNSIGNED)", asFUNCTION(UIElementCreateChild), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "void AddChild(UIElement@+)", asMETHOD(T, AddChild), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void InsertChild(uint, UIElement@+)", asMETHOD(T, InsertChild), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void RemoveChild(UIElement@+, uint arg1 = 0)", asFUNCTIONPR(UIElementRemoveChild, (UIElement*, unsigned, UIElement*), void), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "void RemoveChild(uint)", asFUNCTIONPR(UIElementRemoveChild, (unsigned, UIElement*), void), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "void RemoveAllChildren()", asMETHOD(T, RemoveAllChildren), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void Remove()", asMETHOD(T, Remove), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint FindChild(UIElement@+) const", asMETHOD(T, FindChild), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetParent(UIElement@+, uint index = M_MAX_UNSIGNED)", asMETHOD(T, SetParent), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "UIElement@+ GetChild(const String&in, bool recursive = false) const", asMETHODPR(T, GetChild, (const String&, bool) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "UIElement@+ GetChild(const StringHash&in, const Variant&in value = Variant(), bool recursive = false) const", asMETHODPR(T, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Array<UIElement@>@ GetChildren(bool recursive = false) const", asFUNCTION(UIElementGetChildren), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "UIElement@+ GetElementEventSender() const", asMETHOD(T, GetElementEventSender), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Variant& GetVar(const StringHash&in)", asMETHOD(T, GetVar), asCALL_THISCALL);
    if (!isSprite)
    {
        engine->RegisterObjectMethod(className, "IntVector2 ScreenToElement(const IntVector2&in)", asMETHOD(T, ScreenToElement), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "IntVector2 ElementToScreen(const IntVector2&in)", asMETHOD(T, ElementToScreen), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "bool IsInside(IntVector2, bool)", asMETHOD(T, IsInside), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "bool IsInsideCombined(IntVector2, bool)", asMETHOD(T, IsInsideCombined), asCALL_THISCALL);
    }
    engine->RegisterObjectMethod(className, "void set_style(const String&in)", asFUNCTION(UIElementSetStyle), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "const String& get_style() const", asMETHOD(T, GetAppliedStyle), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_name(const String&in)", asMETHOD(T, SetName), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const String& get_name() const", asMETHOD(T, GetName), asCALL_THISCALL);
    if (!isSprite)
    {
        engine->RegisterObjectMethod(className, "void set_position(const IntVector2&in)", asMETHODPR(UIElement, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "const IntVector2& get_position() const", asMETHOD(T, GetPosition), asCALL_THISCALL);
    }
    engine->RegisterObjectMethod(className, "void set_size(const IntVector2&in)", asMETHODPR(T, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const IntVector2& get_size() const", asMETHOD(T, GetSize), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_width(int)", asMETHOD(T, SetWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_width() const", asMETHOD(T, GetWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_height(int)", asMETHOD(T, SetHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_height() const", asMETHOD(T, GetHeight), asCALL_THISCALL);
    if (!isSprite)
    {
        engine->RegisterObjectMethod(className, "void set_minSize(const IntVector2&in)", asMETHODPR(T, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "const IntVector2& get_minSize() const", asMETHOD(T, GetMinSize), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "void set_minWidth(int)", asMETHOD(T, SetMinWidth), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "int get_minWidth() const", asMETHOD(T, GetMinWidth), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "void set_minHeight(int)", asMETHOD(T, SetMinHeight), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "int get_minHeight() const", asMETHOD(T, GetMinHeight), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "void set_maxSize(const IntVector2&in)", asMETHODPR(T, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "const IntVector2& get_maxSize() const", asMETHOD(T, GetMaxSize), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "void set_maxWidth(int)", asMETHOD(T, SetMaxWidth), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "int get_maxWidth() const", asMETHOD(T, GetMaxWidth), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "void set_maxHeight(int)", asMETHOD(T, SetMaxHeight), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "int get_maxHeight() const", asMETHOD(T, GetMaxHeight), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "bool get_fixedSize() const", asMETHOD(T, IsFixedSize), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "bool get_fixedWidth() const", asMETHOD(T, IsFixedWidth), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "bool get_fixedHeight() const", asMETHOD(T, IsFixedHeight), asCALL_THISCALL);
    }
    engine->RegisterObjectMethod(className, "void set_horizontalAlignment(HorizontalAlignment)", asMETHOD(T, SetHorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "HorizontalAlignment get_horizontalAlignment() const", asMETHOD(T, GetHorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_verticalAlignment(VerticalAlignment)", asMETHOD(T, SetVerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "VerticalAlignment get_verticalAlignment() const", asMETHOD(T, GetVerticalAlignment), asCALL_THISCALL);
    if (!isSprite)
    {
        engine->RegisterObjectMethod(className, "void set_clipBorder(const IntRect&in)", asMETHODPR(T, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "const IntRect& get_clipBorder() const", asMETHOD(T, GetClipBorder), asCALL_THISCALL);
    }
    engine->RegisterObjectMethod(className, "void set_color(const Color&in)", asMETHODPR(T, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_colors(Corner, const Color&in)", asMETHODPR(T, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Color& get_colors(Corner) const", asMETHOD(T, GetColor), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_priority(int)", asMETHOD(T, SetPriority), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_priority() const", asMETHOD(T, GetPriority), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_opacity(float)", asMETHOD(T, SetOpacity), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_opacity() const", asMETHOD(T, GetOpacity), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_bringToFront(bool)", asMETHOD(T, SetBringToFront), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_bringToFront() const", asMETHOD(T, SetBringToFront), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_bringToBack(bool)", asMETHOD(T, SetBringToBack), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_bringToBack() const", asMETHOD(T, GetBringToBack), asCALL_THISCALL);
    if (!isSprite)
    {
        engine->RegisterObjectMethod(className, "void set_clipChildren(bool)", asMETHOD(T, SetClipChildren), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "bool get_clipChildren() const", asMETHOD(T, GetClipChildren), asCALL_THISCALL);
    }
    engine->RegisterObjectMethod(className, "void set_sortChildren(bool)", asMETHOD(T, SetSortChildren), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_sortChildren() const", asMETHOD(T, GetSortChildren), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_useDerivedOpacity(bool)", asMETHOD(T, SetUseDerivedOpacity), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_useDerivedOpacity() const", asMETHOD(T, GetUseDerivedOpacity), asCALL_THISCALL);
    if (!isSprite)
    {
        engine->RegisterObjectMethod(className, "void SetDeepEnabled(bool)", asMETHOD(T, SetDeepEnabled), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "void ResetDeepEnabled()", asMETHOD(T, ResetDeepEnabled), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "void SetEnabledRecursive(bool)", asMETHOD(T, SetEnabledRecursive), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "void set_enabled(bool)", asMETHOD(T, SetEnabled), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "bool get_enabled() const", asMETHOD(T, IsEnabled), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "bool get_enabledSelf() const", asMETHOD(T, IsEnabledSelf), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "void set_editable(bool)", asMETHOD(T, SetEditable), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "bool get_editable() const", asMETHOD(T, IsEditable), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "void set_focus(bool)", asMETHOD(T, SetFocus), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "bool get_focus() const", asMETHOD(T, HasFocus), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "void set_selected(bool)", asMETHOD(T, SetSelected), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "bool get_selected() const", asMETHOD(T, IsSelected), asCALL_THISCALL);
    }
    engine->RegisterObjectMethod(className, "void set_visible(bool)", asMETHOD(T, SetVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_visible() const", asMETHOD(T, IsVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_visibleEffective() const", asMETHOD(T, IsVisibleEffective), asCALL_THISCALL);
    if (!isSprite)
    {
        engine->RegisterObjectMethod(className, "bool get_hovering() const", asMETHOD(T, IsHovering), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "void set_internal(bool) const", asMETHOD(T, SetInternal), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "bool get_internal() const", asMETHOD(T, IsInternal), asCALL_THISCALL);
    }
    engine->RegisterObjectMethod(className, "bool get_colorGradient() const", asMETHOD(T, HasColorGradient), asCALL_THISCALL);
    if (!isSprite)
    {
        engine->RegisterObjectMethod(className, "void set_focusMode(FocusMode)", asMETHOD(T, SetFocusMode), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "FocusMode get_focusMode() const", asMETHOD(T, GetFocusMode), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "void set_dragDropMode(uint)", asMETHOD(T, SetDragDropMode), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "uint get_dragDropMode() const", asMETHOD(T, GetDragDropMode), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "void set_traversalMode(TraversalMode)", asMETHOD(T, SetTraversalMode), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "TraversalMode get_traversalMode() const", asMETHOD(T, GetTraversalMode), asCALL_THISCALL);
    }
    engine->RegisterObjectMethod(className, "void set_defaultStyle(XMLFile@+)", asMETHOD(T, SetDefaultStyle), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "XMLFile@+ get_defaultStyle() const", asFUNCTION(UIElementGetDefaultStyle), asCALL_CDECL_OBJLAST);
    if (!isSprite)
    {
        engine->RegisterObjectMethod(className, "void set_layoutMode(LayoutMode)", asMETHOD(T, SetLayoutMode), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "LayoutMode get_layoutMode() const", asMETHOD(T, GetLayoutMode), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "void set_layoutSpacing(int)", asMETHOD(T, SetLayoutSpacing), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "int get_layoutSpacing() const", asMETHOD(T, GetLayoutSpacing), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "void set_layoutBorder(const IntRect&)", asMETHOD(T, SetLayoutBorder), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "const IntRect& get_layoutBorder() const", asMETHOD(T, GetLayoutBorder), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "void set_layoutFlexScale(const Vector2&)", asMETHOD(T, SetLayoutFlexScale), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "const Vector2& get_layoutFlexScale() const", asMETHOD(T, GetLayoutFlexScale), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "void set_indent(int)", asMETHOD(T, SetIndent), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "int get_indent() const", asMETHOD(T, GetIndent), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "void set_indentSpacing(int)", asMETHOD(T, SetIndentSpacing), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "int get_indentSpacing() const", asMETHOD(T, GetIndentSpacing), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "int get_indentWidth() const", asMETHOD(T, GetIndentWidth), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "const IntVector2& get_childOffset() const", asMETHOD(T, GetChildOffset), asCALL_THISCALL);
    }
    engine->RegisterObjectMethod(className, "void set_elementEventSender(bool)", asMETHOD(T, SetElementEventSender), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_elementEventSender() const", asMETHOD(T, IsElementEventSender), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_numChildren() const", asFUNCTION(UIElementGetNumChildrenNonRecursive), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "uint get_numAllChildren() const", asFUNCTION(UIElementGetNumChildrenRecursive), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "uint GetNumChildren(bool) const", asMETHOD(T, GetNumChildren), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "UIElement@+ get_children(uint) const", asMETHODPR(T, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_parent(UIElement@+)", asFUNCTION(UIElementSetParent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "UIElement@+ get_parent() const", asMETHOD(T, GetParent), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "UIElement@+ get_root() const", asMETHOD(T, GetRoot), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_dragButtonCount() const", asMETHOD(T, GetDragButtonCount), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_dragButtonCombo() const", asMETHOD(T, GetDragButtonCombo), asCALL_THISCALL);
    if (!isSprite)
    {
        engine->RegisterObjectMethod(className, "const IntVector2& get_screenPosition()", asMETHOD(T, GetScreenPosition), asCALL_THISCALL);
        engine->RegisterObjectMethod(className, "IntRect get_combinedScreenRect()", asMETHOD(T, GetCombinedScreenRect), asCALL_THISCALL);
    }
    engine->RegisterObjectMethod(className, "float get_derivedOpacity()", asMETHOD(T, GetDerivedOpacity), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "VariantMap& get_vars()", asFUNCTION(UIElementGetVars), asCALL_CDECL_OBJLAST);
}

/// Template function for registering a class derived from BorderImage.
template <class T> void RegisterBorderImage(asIScriptEngine* engine, const char* className)
{
    RegisterUIElement<T>(engine, className);
    engine->RegisterObjectMethod(className, "void SetFullImageRect()", asMETHOD(T, SetFullImageRect), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetHoverOffset(int, int)", asMETHODPR(T, SetHoverOffset, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_texture(Texture@+)", asMETHOD(T, SetTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Texture@+ get_texture() const", asMETHOD(T, GetTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_imageRect(const IntRect&in)", asMETHODPR(T, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const IntRect& get_imageRect() const", asMETHOD(T, GetImageRect), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_border(const IntRect&in)", asMETHODPR(T, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const IntRect& get_border() const", asMETHOD(T, GetBorder), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_imageBorder(const IntRect&in)", asMETHODPR(T, SetImageBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const IntRect& get_imageBorder() const", asMETHOD(T, GetImageBorder), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_hoverOffset(const IntVector2&in)", asMETHODPR(T, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const IntVector2& get_hoverOffset() const", asMETHOD(T, GetHoverOffset), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_blendMode(BlendMode)", asMETHOD(T, SetBlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "BlendMode get_blendMode() const", asMETHOD(T, GetBlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_tiled(bool)", asMETHOD(T, SetTiled), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_tiled() const", asMETHOD(T, IsTiled), asCALL_THISCALL);
}

/// Template function for registering a class derived from Window.
template <class T> void RegisterWindow(asIScriptEngine* engine, const char* className)
{
    RegisterBorderImage<T>(engine, className);
    engine->RegisterObjectMethod(className, "void set_movable(bool)", asMETHOD(T, SetMovable), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_movable() const", asMETHOD(T, IsMovable), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_resizable(bool)", asMETHOD(T, SetResizable), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_resizable() const", asMETHOD(T, IsResizable), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_resizeBorder(const IntRect&in)", asMETHODPR(T, SetResizeBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const IntRect& get_resizeBorder() const", asMETHOD(T, GetResizeBorder), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_modal(bool)", asMETHOD(T, SetModal), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_modal() const", asMETHOD(T, IsModal), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_modalShadeColor(const Color&in)", asMETHOD(T, SetModalShadeColor), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Color& get_modalShadeColor() const", asMETHOD(T, GetModalShadeColor), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_modalFrameColor(const Color&in)", asMETHOD(T, SetModalFrameColor), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Color& get_modalFrameColor() const", asMETHOD(T, GetModalFrameColor), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_modalFrameSize(const IntVector2&in)", asMETHOD(T, SetModalFrameSize), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const IntVector2& get_modalFrameSize() const", asMETHOD(T, GetModalFrameSize), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_modalAutoDismiss(bool)", asMETHOD(T, SetModalAutoDismiss), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_modalAutoDismiss() const", asMETHOD(T, GetModalAutoDismiss), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_fixedWidthResizing(bool)", asMETHOD(T, SetFixedWidthResizing), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_fixedWidthResizing() const", asMETHOD(T, GetFixedWidthResizing), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_fixedHeightResizing(bool)", asMETHOD(T, SetFixedHeightResizing), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_fixedHeightResizing() const", asMETHOD(T, GetFixedHeightResizing), asCALL_THISCALL);
}

/// Template function for registering a class derived from Button.
template <class T> void RegisterButton(asIScriptEngine* engine, const char* className)
{
    RegisterBorderImage<T>(engine, className);
    engine->RegisterObjectMethod(className, "void SetPressedOffset(int, int)", asMETHODPR(T, SetPressedOffset, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetPressedChildOffset(int, int)", asMETHODPR(T, SetPressedChildOffset, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetRepeat(float, float)", asMETHOD(T, SetRepeat), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_pressedOffset(const IntVector2&in)", asMETHODPR(T, SetPressedOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const IntVector2& get_pressedOffset() const", asMETHOD(T, GetPressedOffset), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_pressedChildOffset(const IntVector2&in)", asMETHODPR(T, SetPressedChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const IntVector2& get_pressedChildOffset() const", asMETHOD(T, GetPressedChildOffset), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_repeatDelay(float)", asMETHOD(T, SetRepeatDelay), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_repeatDelay() const", asMETHOD(T, GetRepeatDelay), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_repeatRate(float)", asMETHOD(T, SetRepeatRate), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_repeatRate() const", asMETHOD(T, GetRepeatRate), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_pressed() const", asMETHOD(T, IsPressed), asCALL_THISCALL);
}

}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
