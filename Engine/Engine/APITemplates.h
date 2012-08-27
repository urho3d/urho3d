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

#pragma once

#include "Addons.h"
#include "BorderImage.h"
#include "Context.h"
#include "Drawable.h"
#include "File.h"
#include "HashSet.h"
#include "Node.h"
#include "Renderer.h"
#include "Resource.h"
#include "Script.h"
#include "ScriptInstance.h"
#include "Sort.h"
#include "SoundSource.h"
#include "Texture.h"

#include <angelscript.h>
#include <cstring>

namespace Urho3D
{

/// Template function for dynamic cast between two script classes.
template <class T, class U> U* RefCast(T* t)
{
    if (!t)
        return 0;
    
    return dynamic_cast<U*>(t);
}

/// Template function for returning a Variant pointer type cast to specific class.
template <class T> T* GetVariantPtr(Variant* ptr)
{
    // An attempt at type safety. Probably can not guarantee that this could not be made to invoke UDB
    T* ptrA = static_cast<T*>(ptr->GetPtr());
    RefCounted* ptrB = static_cast<RefCounted*>(ptrA);
    if (dynamic_cast<T*>(ptrB) == ptrA)
        return ptrA;
    else
        return 0;
}

/// Template function for Vector to array conversion.
template <class T> CScriptArray* VectorToArray(const Vector<T>& vector, const char* arrayName)
{
    asIScriptContext *context = asGetActiveContext();
    if (context)
    {
        asIObjectType* type = GetScriptContext()->GetSubsystem<Script>()->GetObjectType(arrayName);
        CScriptArray* arr = new CScriptArray(vector.Size(), type);
        
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
    asIScriptContext *context = asGetActiveContext();
    if (context)
    {
        asIObjectType* type = GetScriptContext()->GetSubsystem<Script>()->GetObjectType(arrayName);
        CScriptArray* arr = new CScriptArray(vector.Size(), type);
        
        for (unsigned i = 0; i < arr->GetSize(); ++i)
            *(static_cast<T*>(arr->At(i))) = vector[i];
        
        return arr;
    }
    else
        return 0;
}

/// Template function for Vector to handle array conversion.
template <class T> CScriptArray* VectorToHandleArray(const Vector<T*>& vector, const char* arrayName)
{
    asIScriptContext *context = asGetActiveContext();
    if (context)
    {
        asIObjectType* type = GetScriptContext()->GetSubsystem<Script>()->GetObjectType(arrayName);
        CScriptArray* arr = new CScriptArray(vector.Size(), type);
        
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
    asIScriptContext *context = asGetActiveContext();
    if (context)
    {
        asIObjectType* type = GetScriptContext()->GetSubsystem<Script>()->GetObjectType(arrayName);
        CScriptArray* arr = new CScriptArray(vector.Size(), type);
        
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
    asIScriptContext *context = asGetActiveContext();
    if (context)
    {
        asIObjectType* type = GetScriptContext()->GetSubsystem<Script>()->GetObjectType(arrayName);
        CScriptArray* arr = new CScriptArray(vector.Size(), type);
        
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

/// Template function for registering implicit casts between base and subclass.
template <class T, class U> void RegisterSubclass(asIScriptEngine* engine, const char* classNameT, const char* classNameU)
{
    if (!strcmp(classNameT, classNameU))
        return;
    
    String declReturnT(String(classNameT) + "@+ f()");
    String declReturnU(String(classNameU) + "@+ f()");
    
    engine->RegisterObjectBehaviour(classNameT, asBEHAVE_IMPLICIT_REF_CAST, declReturnU.CString(), asFUNCTION((RefCast<T, U>)), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour(classNameU, asBEHAVE_IMPLICIT_REF_CAST, declReturnT.CString(), asFUNCTION((RefCast<U, T>)), asCALL_CDECL_OBJLAST);
}

/// Template function for registering a class derived from Serializer.
template <class T> void RegisterSerializer(asIScriptEngine* engine, const char* className)
{
    engine->RegisterObjectMethod(className, "bool WriteInt(int)", asMETHODPR(T, WriteInt, (int), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteShort(int16)", asMETHODPR(T, WriteShort, (short), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteByte(int8)", asMETHODPR(T, WriteByte, (signed char), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteUInt(uint)", asMETHODPR(T, WriteUInt, (unsigned), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteUShort(uint16)", asMETHODPR(T, WriteUShort, (unsigned short), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteUByte(uint8)", asMETHODPR(T, WriteUByte, (unsigned char), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteBool(bool)", asMETHODPR(T, WriteBool, (bool), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteFloat(float)", asMETHODPR(T, WriteFloat, (float), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteIntRect(const IntRect&in)", asMETHODPR(T, WriteIntRect, (const IntRect&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteIntVector2(const IntVector2&in)", asMETHODPR(T, WriteIntVector2, (const IntVector2&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteVector2(const Vector2&in)", asMETHODPR(T, WriteVector2, (const Vector2&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteVector3(const Vector3&in)", asMETHODPR(T, WriteVector3, (const Vector3&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WritePackedVector3(const Vector3&in, float)", asMETHODPR(T, WritePackedVector3, (const Vector3&, float), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteVector4(const Vector4&in)", asMETHODPR(T, WriteVector4, (const Vector4&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteQuaternion(const Quaternion&in)", asMETHODPR(T, WriteQuaternion, (const Quaternion&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WritePackedQuaternion(const Quaternion&in)", asMETHODPR(T, WritePackedQuaternion, (const Quaternion&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteColor(const Color&in)", asMETHODPR(T, WriteColor, (const Color&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteBoundingBox(const BoundingBox&in)", asMETHODPR(T, WriteBoundingBox, (const BoundingBox&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteString(const String&in)", asMETHODPR(T, WriteString, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteFileID(const String&in)", asMETHODPR(T, WriteFileID, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteStringHash(const StringHash&in)", asMETHODPR(T, WriteStringHash, (const StringHash&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteShortStringHash(const ShortStringHash&in)", asMETHODPR(T, WriteShortStringHash, (const ShortStringHash&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteVariant(const Variant&in)", asMETHODPR(T, WriteVariant, (const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteVariantMap(const VariantMap&in)", asMETHODPR(T, WriteVariantMap, (const VariantMap&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteVLE(uint)", asMETHODPR(T, WriteVLE, (unsigned), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteNetID(uint)", asMETHODPR(T, WriteNetID, (unsigned), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool WriteLine(const String&in)", asMETHODPR(T, WriteLine, (const String&), bool), asCALL_THISCALL);
}

/// Template function for registering a class derived from Deserializer.
template <class T> void RegisterDeserializer(asIScriptEngine* engine, const char* className)
{
    engine->RegisterObjectMethod(className, "int ReadInt()", asMETHODPR(T, ReadInt, (), int), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int16 ReadShort()", asMETHODPR(T, ReadShort, (), short), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int8 ReadByte()", asMETHODPR(T, ReadByte, (), signed char), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint ReadUInt()", asMETHODPR(T, ReadUInt, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint16 ReadUShort()", asMETHODPR(T, ReadUShort, (), unsigned short), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint8 ReadUByte()", asMETHODPR(T, ReadUByte, (), unsigned char), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool ReadBool()", asMETHODPR(T, ReadBool, (), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float ReadFloat()", asMETHODPR(T, ReadFloat, (), float), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "IntRect ReadIntRect()", asMETHODPR(T, ReadIntRect, (), IntRect), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "IntVector2 ReadIntVector2()", asMETHODPR(T, ReadIntVector2, (), IntVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector2 ReadVector2()", asMETHODPR(T, ReadVector2, (), Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector3 ReadVector3()", asMETHODPR(T, ReadVector3, (), Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector3 ReadPackedVector3(float)", asMETHODPR(T, ReadPackedVector3, (float), Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector4 ReadVector4()", asMETHODPR(T, ReadVector4, (), Vector4), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Quaternion ReadQuaternion()", asMETHODPR(T, ReadQuaternion, (), Quaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Quaternion ReadPackedQuaternion()", asMETHODPR(T, ReadPackedQuaternion, (), Quaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Color ReadColor()", asMETHODPR(T, ReadColor, (), Color), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "BoundingBox ReadBoundingBox()", asMETHODPR(T, ReadBoundingBox, (), BoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "String ReadString()", asMETHODPR(T, ReadString, (), String), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "String ReadFileID()", asMETHODPR(T, ReadFileID, (), String), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "StringHash ReadStringHash()", asMETHODPR(T, ReadStringHash, (), StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "ShortStringHash ReadShortStringHash()", asMETHODPR(T, ReadShortStringHash, (), ShortStringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Variant ReadVariant()", asMETHODPR(T, ReadVariant, (), Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "VariantMap ReadVariantMap()", asMETHODPR(T, ReadVariantMap, (), VariantMap), asCALL_THISCALL);
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
}

/// Template function for registering a class derived from Object.
template <class T> void RegisterObject(asIScriptEngine* engine, const char* className)
{
    engine->RegisterObjectType(className, 0, asOBJ_REF);
    engine->RegisterObjectBehaviour(className, asBEHAVE_ADDREF, "void f()", asMETHODPR(T, AddRef, (), void), asCALL_THISCALL);
    engine->RegisterObjectBehaviour(className, asBEHAVE_RELEASE, "void f()", asMETHODPR(T, ReleaseRef, (), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "ShortStringHash get_type() const", asMETHODPR(T, GetType, () const, ShortStringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const String& get_typeName() const", asMETHODPR(T, GetTypeName, () const, const String&), asCALL_THISCALL);
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

static bool SerializableLoad(File* file, Serializable* ptr)
{
    if (file)
        return ptr->Load(*file);
    else
        return false;
}

static bool SerializableSave(File* file, Serializable* ptr)
{
    if (file)
        return ptr->Save(*file);
    else
        return false;
}

/// Template function for registering a class derived from Serializable.
template <class T> void RegisterSerializable(asIScriptEngine* engine, const char* className)
{
    RegisterObject<T>(engine, className);
    engine->RegisterObjectMethod(className, "bool Load(File@+)", asFUNCTION(SerializableLoad), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "bool Save(File@+)", asFUNCTION(SerializableSave), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "bool LoadXML(const XMLElement&)", asMETHODPR(T, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool SaveXML(XMLElement&)", asMETHODPR(T, SaveXML, (XMLElement&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void ApplyAttributes()", asMETHODPR(T, ApplyAttributes, (), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(T, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Variant GetAttribute(const String&in)", asMETHODPR(T, GetAttribute, (const String&), Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_numAttributes() const", asMETHODPR(T, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool set_attributes(uint, const Variant&in) const", asMETHODPR(T, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Variant get_attributes(uint) const", asMETHODPR(T, GetAttribute, (unsigned), Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const AttributeInfo& get_attributeInfos(uint) const", asFUNCTION(SerializableGetAttributeInfo), asCALL_CDECL_OBJLAST);
    RegisterSubclass<Object, T>(engine, "Serializable", className);
}

/// Template function for registering a class derived from Component.
template <class T> void RegisterComponent(asIScriptEngine* engine, const char* className, bool nodeRegistered = true, bool debugRendererRegistered = true)
{
    RegisterSerializable<T>(engine, className);
    RegisterSubclass<Component, T>(engine, "Component", className);
    engine->RegisterObjectMethod(className, "void Remove()", asMETHODPR(T, Remove, (), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void MarkNetworkUpdate() const", asMETHODPR(T, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_id()", asMETHODPR(T, GetID, () const, unsigned), asCALL_THISCALL);
    if (nodeRegistered)
        engine->RegisterObjectMethod(className, "Node@+ get_node() const", asMETHODPR(T, GetNode, () const, Node*), asCALL_THISCALL);
    if (debugRendererRegistered)
        engine->RegisterObjectMethod(className, "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(T, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
}

static Component* NodeCreateComponent(const String& typeName, CreateMode mode, Node* ptr)
{
    return ptr->CreateComponent(ShortStringHash(typeName), mode);
}

static Component* NodeGetOrCreateComponent(const String& typeName, CreateMode mode, Node* ptr)
{
    return ptr->GetOrCreateComponent(ShortStringHash(typeName), mode);
}

static void NodeRemoveComponent(const String& typeName, Node* ptr)
{
    ptr->RemoveComponent(ShortStringHash(typeName));
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

static Component* NodeGetComponentWithType(const String& typeName, Node* ptr)
{
    return ptr->GetComponent(ShortStringHash(typeName));
}

static CScriptArray* NodeGetComponents(Node* ptr)
{
    return VectorToHandleArray<Component>(ptr->GetComponents(), "Array<Component@>");
}

static CScriptArray* NodeGetComponentsWithType(const String& typeName, Node* ptr)
{
    PODVector<Component*> components;
    ptr->GetComponents(components, ShortStringHash(typeName));
    return VectorToHandleArray<Component>(components, "Array<Component@>");
}

static bool NodeHasComponent(const String& typeName, Node* ptr)
{
    return ptr->HasComponent(ShortStringHash(typeName));
}

static CScriptArray* NodeGetChildren(bool recursive, Node* ptr)
{
    PODVector<Node*> nodes;
    ptr->GetChildren(nodes, recursive);
    return VectorToHandleArray<Node>(nodes, "Array<Node@>");
}

static CScriptArray* NodeGetChildrenWithComponent(String& typeName, bool recursive, Node* ptr)
{
    PODVector<Node*> nodes;
    ptr->GetChildrenWithComponent(nodes, ShortStringHash(typeName), recursive);
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
        Node* node = (*i);
        const Vector<SharedPtr<Component> >& components = node->GetComponents();
        for (Vector<SharedPtr<Component> >::ConstIterator j = components.Begin(); j != components.End(); ++j)
        {
            if ((*j)->GetType() == ScriptInstance::GetTypeStatic())
            {
                ScriptInstance* instance = static_cast<ScriptInstance*>(j->Get());
                if (instance->GetClassName() == className)
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
    RegisterSerializable<T>(engine, className);
    RegisterSubclass<Node, T>(engine, "Node", className);
    engine->RegisterObjectMethod(className, "void SetScale(float)", asMETHODPR(T, SetScale, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetTransform(const Vector3&in, const Quaternion&in)", asMETHODPR(T, SetTransform, (const Vector3&, const Quaternion&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetTransform(const Vector3&in, const Quaternion&in, float)", asMETHODPR(T, SetTransform, (const Vector3&, const Quaternion&, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetTransform(const Vector3&in, const Quaternion&in, const Vector3&in)", asMETHODPR(T, SetTransform, (const Vector3&, const Quaternion&, const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetWorldTransform(const Vector3&in, const Quaternion&in)", asMETHODPR(T, SetWorldTransform, (const Vector3&, const Quaternion&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetWorldTransform(const Vector3&in, const Quaternion&in, float)", asMETHODPR(T, SetWorldTransform, (const Vector3&, const Quaternion&, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetWorldTransform(const Vector3&in, const Quaternion&in, const Vector3&in)", asMETHODPR(T, SetWorldTransform, (const Vector3&, const Quaternion&, const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void Translate(const Vector3&in)", asMETHOD(T, Translate), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void TranslateRelative(const Vector3&in)", asMETHOD(T, TranslateRelative), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void Rotate(const Quaternion&in, bool fixedAxis = false)", asMETHOD(T, Rotate), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void Pitch(float, bool fixedAxis = false)", asMETHOD(T, Pitch), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void Yaw(float, bool fixedAxis = false)", asMETHOD(T, Yaw), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void Roll(float, bool fixedAxis = false)", asMETHOD(T, Roll), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void LookAt(const Vector3&in, const Vector3&in upAxis = Vector3(0, 1, 0), bool worldSpace = false)", asMETHOD(T, LookAt), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void Scale(float)", asMETHODPR(T, Scale, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void Scale(const Vector3&in)", asMETHODPR(T, Scale, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Node@+ CreateChild(const String&in name = \"\", CreateMode mode = REPLICATED)", asMETHODPR(T, CreateChild, (const String&, CreateMode), Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void AddChild(Node@+)", asMETHOD(T, AddChild), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void RemoveChild(Node@+)", asMETHODPR(T, RemoveChild, (Node*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void RemoveAllChildren()", asMETHOD(T, RemoveAllChildren), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void Remove()", asMETHOD(T, Remove), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Component@+ CreateComponent(const String&in, CreateMode mode = REPLICATED)", asFUNCTION(NodeCreateComponent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "Component@+ GetOrCreateComponent(const String&in, CreateMode mode = REPLICATED)", asFUNCTION(NodeGetOrCreateComponent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "void RemoveComponent(Component@+)", asMETHODPR(T, RemoveComponent, (Component*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void RemoveComponent(const String&in)", asFUNCTION(NodeRemoveComponent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "Array<Node@>@ GetChildren(bool recursive = false) const", asFUNCTION(NodeGetChildren), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "Array<Node@>@ GetChildrenWithComponent(const String&in, bool recursive = false) const", asFUNCTION(NodeGetChildrenWithComponent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "Array<Node@>@ GetChildrenWithScript(bool recursive = false) const", asFUNCTION(NodeGetChildrenWithScript), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "Array<Node@>@ GetChildrenWithScript(const String&in, bool recursive = false) const", asFUNCTION(NodeGetChildrenWithClassName), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "Node@+ GetChild(const String&in, bool recursive = false) const", asMETHODPR(T, GetChild, (const String&, bool) const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Array<Component@>@ GetComponents() const", asFUNCTION(NodeGetComponents), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "Array<Component@>@ GetComponents(const String&in) const", asFUNCTION(NodeGetComponentsWithType), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "Component@+ GetComponent(const String&in) const", asFUNCTION(NodeGetComponentWithType), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "bool HasComponent(const String&in) const", asFUNCTION(NodeHasComponent), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "Vector3 LocalToWorld(const Vector3&in) const", asMETHODPR(T, LocalToWorld, (const Vector3&) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector3 LocalToWorld(const Vector4&in) const", asMETHODPR(T, LocalToWorld, (const Vector4&) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector3 WorldToLocal(const Vector3&in) const", asMETHODPR(T, WorldToLocal, (const Vector3&) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector3 WorldToLocal(const Vector4&in) const", asMETHODPR(T, WorldToLocal, (const Vector4&) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_position(const Vector3&in)", asMETHOD(T, SetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Vector3& get_position() const", asMETHOD(T, GetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_rotation(const Quaternion&in)", asMETHOD(T, SetRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Quaternion& get_rotation() const", asMETHOD(T, GetRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_direction(const Vector3&in)", asMETHOD(T, SetDirection), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector3 get_direction() const", asMETHOD(T, GetDirection), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_scale(const Vector3&in)", asMETHODPR(T, SetScale, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Vector3& get_scale() const", asMETHOD(T, GetScale), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_worldPosition(const Vector3&in)", asMETHOD(T, SetWorldPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector3 get_worldPosition()", asMETHOD(T, GetWorldPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_worldRotation(const Quaternion&in)", asMETHOD(T, SetWorldRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Quaternion get_worldRotation()", asMETHOD(T, GetWorldRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_worldDirection(const Vector3&in)", asMETHOD(T, SetWorldDirection), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector3 get_worldDirection()", asMETHOD(T, GetWorldDirection), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_worldScale(const Vector3&in)", asMETHODPR(T, SetWorldScale, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector3 get_worldScale()", asMETHOD(T, GetWorldScale), asCALL_THISCALL);
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
    if (file)
        return ptr->Load(*file);
    else
        return false;
}

static bool ResourceSave(File* file, XMLFile* ptr)
{
    if (file)
        return ptr->Save(*file);
    else
        return false;
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
    engine->RegisterObjectMethod(className, "bool Save(File@+)", asFUNCTION(ResourceSave), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "void set_name(const String&in) const", asMETHODPR(T, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const String& get_name() const", asMETHODPR(T, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_memoryUse() const", asMETHODPR(T, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_useTimer()" ,asMETHODPR(T, GetUseTimer, (), unsigned), asCALL_THISCALL);
}

static bool DrawableIsInView(Drawable* ptr)
{
    // Get the last frame number processed by the Renderer to be able to check
    Renderer* renderer = GetScriptContext()->GetSubsystem<Renderer>();
    if (!renderer)
        return false;
    const FrameInfo& frame = renderer->GetFrameInfo();
    return ptr->IsInView(frame.frameNumber_);
}

/// Template function for registering a class derived from Drawable.
template <class T> void RegisterDrawable(asIScriptEngine* engine, const char* className)
{
    RegisterComponent<T>(engine, className);
    RegisterSubclass<Drawable, T>(engine, "Drawable", className);
    engine->RegisterObjectMethod(className, "bool get_inView() const", asFUNCTION(DrawableIsInView), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "void set_visible(bool)", asMETHOD(T, SetVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_visible() const", asMETHOD(T, IsVisible), asCALL_THISCALL);
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
    engine->RegisterObjectMethod(className, "void set_soundType(SoundType)", asMETHOD(T, SetSoundType), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "SoundType get_soundType() const", asMETHOD(T, GetSoundType), asCALL_THISCALL);
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
    engine->RegisterObjectMethod(className, "void set_backupTexture(Texture@+)", asMETHOD(T, SetBackupTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Texture@+ get_backupTexture() const", asMETHOD(T, GetBackupTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_dataLost() const", asMETHODPR(T, IsDataLost, () const, bool), asCALL_THISCALL);
}

static bool UIElementLoadXML(File* file, UIElement* ptr)
{
    if (file)
        return ptr->LoadXML(*file);
    else
        return false;
}

static bool UIElementSaveXML(File* file, UIElement* ptr)
{
    if (file)
        return ptr->SaveXML(*file);
    else
        return false;
}

static UIElement* UIElementCreateChild(const String& typeName, const String& name, UIElement* ptr)
{
    return ptr->CreateChild(ShortStringHash(typeName), name);
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

static VariantMap& UIElementGetVars(UIElement* ptr)
{
    return const_cast<VariantMap&>(ptr->GetVars());
}

/// Template function for registering a class derived from UIElement.
template <class T> void RegisterUIElement(asIScriptEngine* engine, const char* className)
{
    RegisterSerializable<T>(engine, className);
    RegisterObjectConstructor<T>(engine, className);
    RegisterNamedObjectConstructor<T>(engine, className);
    RegisterSubclass<UIElement, T>(engine, "UIElement", className);
    engine->RegisterObjectMethod(className, "bool LoadXML(File@+)", asFUNCTION(UIElementLoadXML), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "bool SaveXML(File@+)", asFUNCTION(UIElementSaveXML), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "void SetStyle(const XMLElement&in)", asMETHODPR(T, SetStyle, (const XMLElement&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetStyle(XMLFile@+, const String&in)", asMETHODPR(T, SetStyle, (XMLFile*, const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetStyleAuto(XMLFile@+)", asMETHODPR(T, SetStyleAuto, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetPosition(int, int)", asMETHODPR(T, SetPosition, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetSize(int, int)", asMETHODPR(T, SetSize, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetMinSize(int, int)", asMETHODPR(T, SetMinSize, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetMaxSize(int, int)", asMETHODPR(T, SetMaxSize, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetFixedSize(int, int)", asMETHODPR(T, SetFixedSize, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetFixedWidth(int)", asMETHOD(T, SetFixedWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetFixedHeight(int)", asMETHOD(T, SetFixedHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetAlignment(HorizontalAlignment, VerticalAlignment)", asMETHOD(T, SetAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetLayout(LayoutMode, int spacing = 0, const IntRect& border = IntRect(0, 0, 0, 0))", asMETHOD(T, SetLayout), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void UpdateLayout()", asMETHOD(T, UpdateLayout), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void DisableLayoutUpdate()", asMETHOD(T, DisableLayoutUpdate), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void EnableLayoutUpdate()", asMETHOD(T, EnableLayoutUpdate), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void BringToFront()", asMETHOD(T, BringToFront), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "UIElement@+ CreateChild(const String&in, const String&in name = String())", asFUNCTION(UIElementCreateChild), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "void AddChild(UIElement@+)", asMETHOD(T, AddChild), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void InsertChild(uint, UIElement@+)", asMETHOD(T, InsertChild), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void RemoveChild(UIElement@+)", asMETHOD(T, RemoveChild), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void RemoveAllChildren()", asMETHOD(T, RemoveAllChildren), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void Remove()", asMETHOD(T, Remove), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "UIElement@+ GetChild(const String&in, bool recursive = false) const", asMETHODPR(T, GetChild, (const String&, bool) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Array<UIElement@>@ GetChildren(bool recursive = false) const", asFUNCTION(UIElementGetChildren), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "IntVector2 ScreenToElement(const IntVector2&in)", asMETHOD(T, ScreenToElement), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "IntVector2 ElementToScreen(const IntVector2&in)", asMETHOD(T, ElementToScreen), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool IsInside(IntVector2, bool)", asMETHOD(T, IsInside), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool IsInsideCombined(IntVector2, bool)", asMETHOD(T, IsInsideCombined), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_style(XMLFile@+)", asMETHODPR(T, SetStyleAuto, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_name(const String&in)", asMETHOD(T, SetName), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const String& get_name() const", asMETHOD(T, GetName), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_position(const IntVector2&in)", asMETHODPR(T, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const IntVector2& get_position() const", asMETHOD(T, GetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_size(const IntVector2&in)", asMETHODPR(T, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const IntVector2& get_size() const", asMETHOD(T, GetSize), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_width(int)", asMETHOD(T, SetWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_width() const", asMETHOD(T, GetWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_height(int)", asMETHOD(T, SetHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_height() const", asMETHOD(T, GetHeight), asCALL_THISCALL);
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
    engine->RegisterObjectMethod(className, "void set_horizontalAlignment(HorizontalAlignment)", asMETHOD(T, SetHorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "HorizontalAlignment get_horizontalAlignment() const", asMETHOD(T, GetHorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_verticalAlignment(VerticalAlignment)", asMETHOD(T, SetVerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "VerticalAlignment get_verticalAlignment() const", asMETHOD(T, GetVerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_clipBorder(const IntRect&in)", asMETHODPR(T, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const IntRect& get_clipBorder() const", asMETHOD(T, GetClipBorder), asCALL_THISCALL);
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
    engine->RegisterObjectMethod(className, "void set_clipChildren(bool)", asMETHOD(T, SetClipChildren), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_clipChildren() const", asMETHOD(T, GetClipChildren), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_sortChildren(bool)", asMETHOD(T, SetSortChildren), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_sortChildren() const", asMETHOD(T, GetSortChildren), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_active(bool)", asMETHOD(T, SetActive), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_active() const", asMETHOD(T, IsActive), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_focus(bool)", asMETHOD(T, SetFocus), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_focus() const", asMETHOD(T, HasFocus), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_selected(bool)", asMETHOD(T, SetSelected), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_selected() const", asMETHOD(T, IsSelected), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_visible(bool)", asMETHOD(T, SetVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_visible() const", asMETHOD(T, IsVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_hovering() const", asMETHOD(T, IsHovering), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_colorGradient() const", asMETHOD(T, HasColorGradient), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_focusMode(FocusMode)", asMETHOD(T, SetFocusMode), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "FocusMode get_focusMode() const", asMETHOD(T, GetFocusMode), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_dragDropMode(uint)", asMETHOD(T, SetDragDropMode), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_dragDropMode() const", asMETHOD(T, GetDragDropMode), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_layoutMode(LayoutMode)", asMETHOD(T, SetLayoutMode), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "LayoutMode get_layoutMode() const", asMETHOD(T, GetLayoutMode), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_layoutSpacing(int)", asMETHOD(T, SetLayoutSpacing), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_layoutSpacing() const", asMETHOD(T, GetLayoutSpacing), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_layoutBorder(const IntRect&)", asMETHOD(T, SetLayoutBorder), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const IntRect& get_layoutBorder() const", asMETHOD(T, GetLayoutBorder), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const IntVector2& get_childOffset() const", asMETHOD(T, GetChildOffset), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_numChildren() const", asFUNCTION(UIElementGetNumChildrenNonRecursive), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "uint get_numAllChildren() const", asFUNCTION(UIElementGetNumChildrenRecursive), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod(className, "uint get_numChildren(bool) const", asMETHOD(T, GetNumChildren), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "UIElement@+ get_children(uint) const", asMETHODPR(T, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "UIElement@+ get_parent() const", asMETHOD(T, GetParent), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "UIElement@+ get_root() const", asMETHOD(T, GetRoot), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "IntVector2 get_screenPosition()", asMETHOD(T, GetScreenPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_derivedOpacity()", asMETHOD(T, GetDerivedOpacity), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "IntRect get_combinedScreenRect()", asMETHOD(T, GetCombinedScreenRect), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "VariantMap& get_vars()", asFUNCTION(UIElementGetVars), asCALL_CDECL_OBJLAST);
}

/// Template function for registering a class derived from BorderImage.
template <class T> void RegisterBorderImage(asIScriptEngine* engine, const char* className)
{
    RegisterUIElement<T>(engine, className);
    engine->RegisterObjectMethod(className, "void SetFullImageRect()", asMETHOD(T, SetFullImageRect), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetHoverOffset(int, int)", asMETHODPR(T, SetHoverOffset, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_texture(Texture@+)", asMETHOD(T, SetTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Texture@+ get_texture() const", asMETHOD(T, SetTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_imageRect(const IntRect&in)", asMETHODPR(T, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const IntRect& get_imageRect() const", asMETHOD(T, GetImageRect), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_border(const IntRect&in)", asMETHODPR(T, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const IntRect& get_border() const", asMETHOD(T, GetBorder), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_hoverOffset(const IntVector2&in)", asMETHODPR(T, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const IntVector2& get_hoverOffset() const", asMETHOD(T, GetHoverOffset), asCALL_THISCALL);
}

/// Template function for registering a class derived from Button.
template <class T> void RegisterButton(asIScriptEngine* engine, const char* className)
{
    RegisterBorderImage<T>(engine, className);
    engine->RegisterObjectMethod(className, "void SetPressedOffset(int, int)", asMETHODPR(T, SetPressedOffset, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetLabelOffset(int, int)", asMETHODPR(T, SetLabelOffset, (int, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetRepeat(float, float)", asMETHOD(T, SetRepeat), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_pressedOffset(const IntVector2&in)", asMETHODPR(T, SetPressedOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const IntVector2& get_pressedOffset() const", asMETHOD(T, GetPressedOffset), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_labelOffset(const IntVector2&in)", asMETHODPR(T, SetLabelOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const IntVector2& get_labelOffset() const", asMETHOD(T, GetLabelOffset), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_repeatDelay(float)", asMETHOD(T, SetRepeatDelay), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_repeatDelay() const", asMETHOD(T, GetRepeatDelay), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_repeatRate(float)", asMETHOD(T, SetRepeatRate), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_repeatRate() const", asMETHOD(T, GetRepeatRate), asCALL_THISCALL);
}

}
