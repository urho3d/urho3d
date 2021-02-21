// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// explicit NamedPipe::NamedPipe(Context* context) | File: ../IO/NamedPipe.h
static NamedPipe* NamedPipe_NamedPipe_Context()
{
    return new NamedPipe(GetScriptContext());
}

// NamedPipe::NamedPipe(Context* context, const String& name, bool isServer) | File: ../IO/NamedPipe.h
static NamedPipe* NamedPipe_NamedPipe_Context_String_bool(const String &name, bool isServer)
{
    return new NamedPipe(GetScriptContext(), name, isServer);
}

// StringVector Deserializer::ReadStringVector() | File: ../IO/Deserializer.h
static CScriptArray* NamedPipe_ReadStringVector_void(NamedPipe* ptr)
{
    StringVector result = ptr->ReadStringVector();
    return VectorToArray<String>(result, "Array<String>");
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void NamedPipe_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(NamedPipe* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// bool Serializer::WriteStringVector(const StringVector& value) | File: ../IO/Serializer.h
static bool NamedPipe_WriteStringVector_StringVector(NamedPipe* ptr, CScriptArray* value_conv)
{
    StringVector value = ArrayToVector<String>(value_conv);
    bool result = ptr->WriteStringVector(value);
    return result;
}

#ifdef URHO3D_NAVIGATION
// explicit NavArea::NavArea(Context* context) | File: ../Navigation/NavArea.h
static NavArea* NavArea_NavArea_Context()
{
    return new NavArea(GetScriptContext());
}
#endif

#ifdef URHO3D_NAVIGATION
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void NavArea_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(NavArea* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_NAVIGATION
// explicit Navigable::Navigable(Context* context) | File: ../Navigation/Navigable.h
static Navigable* Navigable_Navigable_Context()
{
    return new Navigable(GetScriptContext());
}
#endif

#ifdef URHO3D_NAVIGATION
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Navigable_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Navigable* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_NAVIGATION
// explicit NavigationMesh::NavigationMesh(Context* context) | File: ../Navigation/NavigationMesh.h
static NavigationMesh* NavigationMesh_NavigationMesh_Context()
{
    return new NavigationMesh(GetScriptContext());
}
#endif

#ifdef URHO3D_NAVIGATION
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void NavigationMesh_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(NavigationMesh* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_NETWORK
// Vector<SharedPtr<Connection>> Network::GetClientConnections() const | File: ../Network/Network.h
static CScriptArray* Network_GetClientConnections_void(Network* ptr)
{
    Vector<SharedPtr<Connection>> result = ptr->GetClientConnections();
    return VectorToHandleArray(result, "Array<Connection@>");
}
#endif

#ifdef URHO3D_NETWORK
// SharedPtr<HttpRequest> Network::MakeHttpRequest(const String& url, const String& verb=String::EMPTY, const Vector<String>& headers=Vector<String>(), const String& postData=String::EMPTY) | File: ../Network/Network.h
static HttpRequest* Network_MakeHttpRequest_String_String_VectorString_String(Network* ptr, const String& url, const String& verb, CScriptArray* headers_conv, const String& postData)
{
    Vector<String> headers = ArrayToVector<String>(headers_conv);
    SharedPtr<HttpRequest> result = ptr->MakeHttpRequest(url, verb, headers, postData);
    return result.Detach();
}
#endif

#ifdef URHO3D_NETWORK
// explicit Network::Network(Context* context) | File: ../Network/Network.h
static Network* Network_Network_Context()
{
    return new Network(GetScriptContext());
}
#endif

#ifdef URHO3D_NETWORK
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Network_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Network* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_NETWORK
// explicit NetworkPriority::NetworkPriority(Context* context) | File: ../Network/NetworkPriority.h
static NetworkPriority* NetworkPriority_NetworkPriority_Context()
{
    return new NetworkPriority(GetScriptContext());
}
#endif

#ifdef URHO3D_NETWORK
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void NetworkPriority_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(NetworkPriority* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

// void Node::AddTags(const StringVector& tags) | File: ../Scene/Node.h
static void Node_AddTags_StringVector(Node* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->AddTags(tags);
}

// const Vector<SharedPtr<Node>>& Node::GetChildren() const | File: ../Scene/Node.h
static CScriptArray* Node_GetChildren_void(Node* ptr)
{
    const Vector<SharedPtr<Node>>& result = ptr->GetChildren();
    return VectorToHandleArray(result, "Array<Node@>");
}

// PODVector<Node*> Node::GetChildren(bool recursive) const | File: ../Scene/Node.h
static CScriptArray* Node_GetChildren_bool(Node* ptr, bool recursive)
{
    PODVector<Node*> result = ptr->GetChildren(recursive);
    return VectorToHandleArray(result, "Array<Node@>");
}

// PODVector<Node*> Node::GetChildrenWithComponent(StringHash type, bool recursive=false) const | File: ../Scene/Node.h
static CScriptArray* Node_GetChildrenWithComponent_StringHash_bool(Node* ptr, StringHash type, bool recursive)
{
    PODVector<Node*> result = ptr->GetChildrenWithComponent(type, recursive);
    return VectorToHandleArray(result, "Array<Node@>");
}

// PODVector<Node*> Node::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../Scene/Node.h
static CScriptArray* Node_GetChildrenWithTag_String_bool(Node* ptr, const String& tag, bool recursive)
{
    PODVector<Node*> result = ptr->GetChildrenWithTag(tag, recursive);
    return VectorToHandleArray(result, "Array<Node@>");
}

// const Vector<SharedPtr<Component>>& Node::GetComponents() const | File: ../Scene/Node.h
static CScriptArray* Node_GetComponents_void(Node* ptr)
{
    const Vector<SharedPtr<Component>>& result = ptr->GetComponents();
    return VectorToHandleArray(result, "Array<Component@>");
}

// const PODVector<Node*>& Node::GetDependencyNodes() const | File: ../Scene/Node.h
static CScriptArray* Node_GetDependencyNodes_void(Node* ptr)
{
    const PODVector<Node*>& result = ptr->GetDependencyNodes();
    return VectorToHandleArray(result, "Array<Node@>");
}

// const StringVector& Node::GetTags() const | File: ../Scene/Node.h
static CScriptArray* Node_GetTags_void(Node* ptr)
{
    const StringVector& result = ptr->GetTags();
    return VectorToArray<String>(result, "Array<String>");
}

// explicit Node::Node(Context* context) | File: ../Scene/Node.h
static Node* Node_Node_Context()
{
    return new Node(GetScriptContext());
}

// void Node::SetTags(const StringVector& tags) | File: ../Scene/Node.h
static void Node_SetTags_StringVector(Node* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->SetTags(tags);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Node_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Node* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

void ASRegisterGenerated_Members_N(asIScriptEngine* engine)
{
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("NamedPipe", asBEHAVE_ADDREF, "void f()", AS_METHODPR(NamedPipe, AddRef, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void NamedPipe::Close() | File: ../IO/NamedPipe.h
    engine->RegisterObjectMethod("NamedPipe", "void Close()", AS_METHODPR(NamedPipe, Close, (), void), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "bool GetBlockEvents() const", AS_METHODPR(NamedPipe, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "const String& GetCategory() const", AS_METHODPR(NamedPipe, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "const String& get_category() const", AS_METHODPR(NamedPipe, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // virtual unsigned Deserializer::GetChecksum() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "uint GetChecksum()", AS_METHODPR(NamedPipe, GetChecksum, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "uint get_checksum()", AS_METHODPR(NamedPipe, GetChecksum, (), unsigned), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "VariantMap& GetEventDataMap() const", AS_METHODPR(NamedPipe, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "Object@+ GetEventSender() const", AS_METHODPR(NamedPipe, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(NamedPipe, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(NamedPipe, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "const VariantMap& GetGlobalVars() const", AS_METHODPR(NamedPipe, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "const VariantMap& get_globalVars() const", AS_METHODPR(NamedPipe, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // const String& AbstractFile::GetName() const override | File: ../IO/AbstractFile.h
    engine->RegisterObjectMethod("NamedPipe", "const String& GetName() const", AS_METHODPR(NamedPipe, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "const String& get_name() const", AS_METHODPR(NamedPipe, GetName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Deserializer::GetPosition() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "uint GetPosition() const", AS_METHODPR(NamedPipe, GetPosition, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "uint get_position() const", AS_METHODPR(NamedPipe, GetPosition, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Deserializer::GetSize() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "uint GetSize() const", AS_METHODPR(NamedPipe, GetSize, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "uint get_size() const", AS_METHODPR(NamedPipe, GetSize, () const, unsigned), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(NamedPipe, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "StringHash GetType() const", AS_METHODPR(NamedPipe, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "StringHash get_type() const", AS_METHODPR(NamedPipe, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "const String& GetTypeName() const", AS_METHODPR(NamedPipe, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "const String& get_typeName() const", AS_METHODPR(NamedPipe, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "bool HasEventHandlers() const", AS_METHODPR(NamedPipe, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(NamedPipe, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(NamedPipe, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool NamedPipe::IsEof() const override | File: ../IO/NamedPipe.h
    engine->RegisterObjectMethod("NamedPipe", "bool IsEof() const", AS_METHODPR(NamedPipe, IsEof, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "bool get_eof() const", AS_METHODPR(NamedPipe, IsEof, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "bool IsInstanceOf(StringHash) const", AS_METHODPR(NamedPipe, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool NamedPipe::IsOpen() const | File: ../IO/NamedPipe.h
    engine->RegisterObjectMethod("NamedPipe", "bool IsOpen() const", AS_METHODPR(NamedPipe, IsOpen, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "bool get_open() const", AS_METHODPR(NamedPipe, IsOpen, () const, bool), AS_CALL_THISCALL);
    // bool NamedPipe::IsServer() const | File: ../IO/NamedPipe.h
    engine->RegisterObjectMethod("NamedPipe", "bool IsServer() const", AS_METHODPR(NamedPipe, IsServer, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "bool get_server() const", AS_METHODPR(NamedPipe, IsServer, () const, bool), AS_CALL_THISCALL);
    // explicit NamedPipe::NamedPipe(Context* context) | File: ../IO/NamedPipe.h
    engine->RegisterObjectBehaviour("NamedPipe", asBEHAVE_FACTORY, "NamedPipe@+ f()", AS_FUNCTION(NamedPipe_NamedPipe_Context), AS_CALL_CDECL);
    // NamedPipe::NamedPipe(Context* context, const String& name, bool isServer) | File: ../IO/NamedPipe.h
    engine->RegisterObjectBehaviour("NamedPipe", asBEHAVE_FACTORY, "NamedPipe@+ f(const String&in, bool)", AS_FUNCTION(NamedPipe_NamedPipe_Context_String_bool), AS_CALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(NamedPipe, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // bool NamedPipe::Open(const String& name, bool isServer) | File: ../IO/NamedPipe.h
    engine->RegisterObjectMethod("NamedPipe", "bool Open(const String&in, bool)", AS_METHODPR(NamedPipe, Open, (const String&, bool), bool), AS_CALL_THISCALL);
    // unsigned NamedPipe::Read(void* dest, unsigned size) override | File: ../IO/NamedPipe.h
    // Error: type "void*" can not automatically bind
    // bool Deserializer::ReadBool() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool ReadBool()", AS_METHODPR(NamedPipe, ReadBool, (), bool), AS_CALL_THISCALL);
    // BoundingBox Deserializer::ReadBoundingBox() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "BoundingBox ReadBoundingBox()", AS_METHODPR(NamedPipe, ReadBoundingBox, (), BoundingBox), AS_CALL_THISCALL);
    // PODVector<unsigned char> Deserializer::ReadBuffer() | File: ../IO/Deserializer.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // signed char Deserializer::ReadByte() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "int8 ReadByte()", AS_METHODPR(NamedPipe, ReadByte, (), signed char), AS_CALL_THISCALL);
    // Color Deserializer::ReadColor() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Color ReadColor()", AS_METHODPR(NamedPipe, ReadColor, (), Color), AS_CALL_THISCALL);
    // double Deserializer::ReadDouble() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "double ReadDouble()", AS_METHODPR(NamedPipe, ReadDouble, (), double), AS_CALL_THISCALL);
    // String Deserializer::ReadFileID() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "String ReadFileID()", AS_METHODPR(NamedPipe, ReadFileID, (), String), AS_CALL_THISCALL);
    // float Deserializer::ReadFloat() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "float ReadFloat()", AS_METHODPR(NamedPipe, ReadFloat, (), float), AS_CALL_THISCALL);
    // int Deserializer::ReadInt() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "int ReadInt()", AS_METHODPR(NamedPipe, ReadInt, (), int), AS_CALL_THISCALL);
    // long long Deserializer::ReadInt64() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "int64 ReadInt64()", AS_METHODPR(NamedPipe, ReadInt64, (), long long), AS_CALL_THISCALL);
    // IntRect Deserializer::ReadIntRect() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "IntRect ReadIntRect()", AS_METHODPR(NamedPipe, ReadIntRect, (), IntRect), AS_CALL_THISCALL);
    // IntVector2 Deserializer::ReadIntVector2() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "IntVector2 ReadIntVector2()", AS_METHODPR(NamedPipe, ReadIntVector2, (), IntVector2), AS_CALL_THISCALL);
    // IntVector3 Deserializer::ReadIntVector3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "IntVector3 ReadIntVector3()", AS_METHODPR(NamedPipe, ReadIntVector3, (), IntVector3), AS_CALL_THISCALL);
    // String Deserializer::ReadLine() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "String ReadLine()", AS_METHODPR(NamedPipe, ReadLine, (), String), AS_CALL_THISCALL);
    // Matrix3 Deserializer::ReadMatrix3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Matrix3 ReadMatrix3()", AS_METHODPR(NamedPipe, ReadMatrix3, (), Matrix3), AS_CALL_THISCALL);
    // Matrix3x4 Deserializer::ReadMatrix3x4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Matrix3x4 ReadMatrix3x4()", AS_METHODPR(NamedPipe, ReadMatrix3x4, (), Matrix3x4), AS_CALL_THISCALL);
    // Matrix4 Deserializer::ReadMatrix4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Matrix4 ReadMatrix4()", AS_METHODPR(NamedPipe, ReadMatrix4, (), Matrix4), AS_CALL_THISCALL);
    // unsigned Deserializer::ReadNetID() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "uint ReadNetID()", AS_METHODPR(NamedPipe, ReadNetID, (), unsigned), AS_CALL_THISCALL);
    // Quaternion Deserializer::ReadPackedQuaternion() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Quaternion ReadPackedQuaternion()", AS_METHODPR(NamedPipe, ReadPackedQuaternion, (), Quaternion), AS_CALL_THISCALL);
    // Vector3 Deserializer::ReadPackedVector3(float maxAbsCoord) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Vector3 ReadPackedVector3(float)", AS_METHODPR(NamedPipe, ReadPackedVector3, (float), Vector3), AS_CALL_THISCALL);
    // Quaternion Deserializer::ReadQuaternion() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Quaternion ReadQuaternion()", AS_METHODPR(NamedPipe, ReadQuaternion, (), Quaternion), AS_CALL_THISCALL);
    // Rect Deserializer::ReadRect() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Rect ReadRect()", AS_METHODPR(NamedPipe, ReadRect, (), Rect), AS_CALL_THISCALL);
    // ResourceRef Deserializer::ReadResourceRef() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "ResourceRef ReadResourceRef()", AS_METHODPR(NamedPipe, ReadResourceRef, (), ResourceRef), AS_CALL_THISCALL);
    // ResourceRefList Deserializer::ReadResourceRefList() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "ResourceRefList ReadResourceRefList()", AS_METHODPR(NamedPipe, ReadResourceRefList, (), ResourceRefList), AS_CALL_THISCALL);
    // short Deserializer::ReadShort() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "int16 ReadShort()", AS_METHODPR(NamedPipe, ReadShort, (), short), AS_CALL_THISCALL);
    // String Deserializer::ReadString() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "String ReadString()", AS_METHODPR(NamedPipe, ReadString, (), String), AS_CALL_THISCALL);
    // StringHash Deserializer::ReadStringHash() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "StringHash ReadStringHash()", AS_METHODPR(NamedPipe, ReadStringHash, (), StringHash), AS_CALL_THISCALL);
    // StringVector Deserializer::ReadStringVector() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Array<String>@ ReadStringVector()", AS_FUNCTION_OBJFIRST(NamedPipe_ReadStringVector_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned char Deserializer::ReadUByte() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "uint8 ReadUByte()", AS_METHODPR(NamedPipe, ReadUByte, (), unsigned char), AS_CALL_THISCALL);
    // unsigned Deserializer::ReadUInt() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "uint ReadUInt()", AS_METHODPR(NamedPipe, ReadUInt, (), unsigned), AS_CALL_THISCALL);
    // unsigned long long Deserializer::ReadUInt64() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "uint64 ReadUInt64()", AS_METHODPR(NamedPipe, ReadUInt64, (), unsigned long long), AS_CALL_THISCALL);
    // unsigned short Deserializer::ReadUShort() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "uint16 ReadUShort()", AS_METHODPR(NamedPipe, ReadUShort, (), unsigned short), AS_CALL_THISCALL);
    // Variant Deserializer::ReadVariant() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Variant ReadVariant()", AS_METHODPR(NamedPipe, ReadVariant, (), Variant), AS_CALL_THISCALL);
    // Variant Deserializer::ReadVariant(VariantType type) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Variant ReadVariant(VariantType)", AS_METHODPR(NamedPipe, ReadVariant, (VariantType), Variant), AS_CALL_THISCALL);
    // VariantMap Deserializer::ReadVariantMap() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "VariantMap ReadVariantMap()", AS_METHODPR(NamedPipe, ReadVariantMap, (), VariantMap), AS_CALL_THISCALL);
    // VariantVector Deserializer::ReadVariantVector() | File: ../IO/Deserializer.h
    // Error: type "VariantVector" can not automatically bind
    // Vector2 Deserializer::ReadVector2() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Vector2 ReadVector2()", AS_METHODPR(NamedPipe, ReadVector2, (), Vector2), AS_CALL_THISCALL);
    // Vector3 Deserializer::ReadVector3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Vector3 ReadVector3()", AS_METHODPR(NamedPipe, ReadVector3, (), Vector3), AS_CALL_THISCALL);
    // Vector4 Deserializer::ReadVector4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Vector4 ReadVector4()", AS_METHODPR(NamedPipe, ReadVector4, (), Vector4), AS_CALL_THISCALL);
    // unsigned Deserializer::ReadVLE() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "uint ReadVLE()", AS_METHODPR(NamedPipe, ReadVLE, (), unsigned), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("NamedPipe", "int Refs() const", AS_METHODPR(NamedPipe, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "int get_refs() const", AS_METHODPR(NamedPipe, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("NamedPipe", asBEHAVE_RELEASE, "void f()", AS_METHODPR(NamedPipe, ReleaseRef, (), void), AS_CALL_THISCALL);
    // unsigned NamedPipe::Seek(unsigned position) override | File: ../IO/NamedPipe.h
    engine->RegisterObjectMethod("NamedPipe", "uint Seek(uint)", AS_METHODPR(NamedPipe, Seek, (unsigned), unsigned), AS_CALL_THISCALL);
    // unsigned Deserializer::SeekRelative(int delta) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "uint SeekRelative(int)", AS_METHODPR(NamedPipe, SeekRelative, (int), unsigned), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "void SendEvent(StringHash)", AS_METHODPR(NamedPipe, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(NamedPipe, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "void SetBlockEvents(bool)", AS_METHODPR(NamedPipe, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(NamedPipe, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(NamedPipe, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void NamedPipe::SetName(const String& name) override | File: ../IO/NamedPipe.h
    engine->RegisterObjectMethod("NamedPipe", "void SetName(const String&in)", AS_METHODPR(NamedPipe, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "void set_name(const String&in)", AS_METHODPR(NamedPipe, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // unsigned Deserializer::Tell() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "uint Tell() const", AS_METHODPR(NamedPipe, Tell, () const, unsigned), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "void UnsubscribeFromAllEvents()", AS_METHODPR(NamedPipe, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(NamedPipe_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(NamedPipe, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(NamedPipe, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(NamedPipe, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("NamedPipe", "int WeakRefs() const", AS_METHODPR(NamedPipe, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "int get_weakRefs() const", AS_METHODPR(NamedPipe, WeakRefs, () const, int), AS_CALL_THISCALL);
    // unsigned NamedPipe::Write(const void* data, unsigned size) override | File: ../IO/NamedPipe.h
    // Error: type "const void*" can not automatically bind
    // bool Serializer::WriteBool(bool value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteBool(bool)", AS_METHODPR(NamedPipe, WriteBool, (bool), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteBoundingBox(const BoundingBox& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteBoundingBox(const BoundingBox&in)", AS_METHODPR(NamedPipe, WriteBoundingBox, (const BoundingBox&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteBuffer(const PODVector<unsigned char>& value) | File: ../IO/Serializer.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // bool Serializer::WriteByte(signed char value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteByte(int8)", AS_METHODPR(NamedPipe, WriteByte, (signed char), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteColor(const Color& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteColor(const Color&in)", AS_METHODPR(NamedPipe, WriteColor, (const Color&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteDouble(double value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteDouble(double)", AS_METHODPR(NamedPipe, WriteDouble, (double), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteFileID(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteFileID(const String&in)", AS_METHODPR(NamedPipe, WriteFileID, (const String&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteFloat(float value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteFloat(float)", AS_METHODPR(NamedPipe, WriteFloat, (float), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteInt(int value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteInt(int)", AS_METHODPR(NamedPipe, WriteInt, (int), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteInt64(long long value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteInt64(int64)", AS_METHODPR(NamedPipe, WriteInt64, (long long), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteIntRect(const IntRect& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteIntRect(const IntRect&in)", AS_METHODPR(NamedPipe, WriteIntRect, (const IntRect&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteIntVector2(const IntVector2& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteIntVector2(const IntVector2&in)", AS_METHODPR(NamedPipe, WriteIntVector2, (const IntVector2&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteIntVector3(const IntVector3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteIntVector3(const IntVector3&in)", AS_METHODPR(NamedPipe, WriteIntVector3, (const IntVector3&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteLine(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteLine(const String&in)", AS_METHODPR(NamedPipe, WriteLine, (const String&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteMatrix3(const Matrix3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteMatrix3(const Matrix3&in)", AS_METHODPR(NamedPipe, WriteMatrix3, (const Matrix3&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteMatrix3x4(const Matrix3x4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteMatrix3x4(const Matrix3x4&in)", AS_METHODPR(NamedPipe, WriteMatrix3x4, (const Matrix3x4&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteMatrix4(const Matrix4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteMatrix4(const Matrix4&in)", AS_METHODPR(NamedPipe, WriteMatrix4, (const Matrix4&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteNetID(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteNetID(uint)", AS_METHODPR(NamedPipe, WriteNetID, (unsigned), bool), AS_CALL_THISCALL);
    // bool Serializer::WritePackedQuaternion(const Quaternion& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WritePackedQuaternion(const Quaternion&in)", AS_METHODPR(NamedPipe, WritePackedQuaternion, (const Quaternion&), bool), AS_CALL_THISCALL);
    // bool Serializer::WritePackedVector3(const Vector3& value, float maxAbsCoord) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WritePackedVector3(const Vector3&in, float)", AS_METHODPR(NamedPipe, WritePackedVector3, (const Vector3&, float), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteQuaternion(const Quaternion& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteQuaternion(const Quaternion&in)", AS_METHODPR(NamedPipe, WriteQuaternion, (const Quaternion&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteRect(const Rect& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteRect(const Rect&in)", AS_METHODPR(NamedPipe, WriteRect, (const Rect&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteResourceRef(const ResourceRef& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteResourceRef(const ResourceRef&in)", AS_METHODPR(NamedPipe, WriteResourceRef, (const ResourceRef&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteResourceRefList(const ResourceRefList& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteResourceRefList(const ResourceRefList&in)", AS_METHODPR(NamedPipe, WriteResourceRefList, (const ResourceRefList&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteShort(short value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteShort(int16)", AS_METHODPR(NamedPipe, WriteShort, (short), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteString(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteString(const String&in)", AS_METHODPR(NamedPipe, WriteString, (const String&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteStringHash(const StringHash& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteStringHash(const StringHash&in)", AS_METHODPR(NamedPipe, WriteStringHash, (const StringHash&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteStringVector(const StringVector& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteStringVector(Array<String>@+)", AS_FUNCTION_OBJFIRST(NamedPipe_WriteStringVector_StringVector), AS_CALL_CDECL_OBJFIRST);
    // bool Serializer::WriteUByte(unsigned char value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteUByte(uint8)", AS_METHODPR(NamedPipe, WriteUByte, (unsigned char), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteUInt(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteUInt(uint)", AS_METHODPR(NamedPipe, WriteUInt, (unsigned), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteUInt64(unsigned long long value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteUInt64(uint64)", AS_METHODPR(NamedPipe, WriteUInt64, (unsigned long long), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteUShort(unsigned short value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteUShort(uint16)", AS_METHODPR(NamedPipe, WriteUShort, (unsigned short), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVariant(const Variant& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteVariant(const Variant&in)", AS_METHODPR(NamedPipe, WriteVariant, (const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVariantData(const Variant& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteVariantData(const Variant&in)", AS_METHODPR(NamedPipe, WriteVariantData, (const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVariantMap(const VariantMap& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteVariantMap(const VariantMap&in)", AS_METHODPR(NamedPipe, WriteVariantMap, (const VariantMap&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVariantVector(const VariantVector& value) | File: ../IO/Serializer.h
    // Error: type "const VariantVector&" can not automatically bind
    // bool Serializer::WriteVector2(const Vector2& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteVector2(const Vector2&in)", AS_METHODPR(NamedPipe, WriteVector2, (const Vector2&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVector3(const Vector3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteVector3(const Vector3&in)", AS_METHODPR(NamedPipe, WriteVector3, (const Vector3&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVector4(const Vector4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteVector4(const Vector4&in)", AS_METHODPR(NamedPipe, WriteVector4, (const Vector4&), bool), AS_CALL_THISCALL);
    // bool Serializer::WriteVLE(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteVLE(uint)", AS_METHODPR(NamedPipe, WriteVLE, (unsigned), bool), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(NamedPipe, "NamedPipe")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(NamedPipe, "NamedPipe")
#endif
#ifdef REGISTER_MANUAL_PART_AbstractFile
    REGISTER_MANUAL_PART_AbstractFile(NamedPipe, "NamedPipe")
#endif
#ifdef REGISTER_MANUAL_PART_Deserializer
    REGISTER_MANUAL_PART_Deserializer(NamedPipe, "NamedPipe")
#endif
#ifdef REGISTER_MANUAL_PART_Serializer
    REGISTER_MANUAL_PART_Serializer(NamedPipe, "NamedPipe")
#endif
#ifdef REGISTER_MANUAL_PART_NamedPipe
    REGISTER_MANUAL_PART_NamedPipe(NamedPipe, "NamedPipe")
#endif
    RegisterSubclass<Object, NamedPipe>(engine, "Object", "NamedPipe");
    RegisterSubclass<RefCounted, NamedPipe>(engine, "RefCounted", "NamedPipe");
    RegisterSubclass<AbstractFile, NamedPipe>(engine, "AbstractFile", "NamedPipe");
    RegisterSubclass<Deserializer, NamedPipe>(engine, "Deserializer", "NamedPipe");
    RegisterSubclass<Serializer, NamedPipe>(engine, "Serializer", "NamedPipe");

#ifdef URHO3D_NAVIGATION
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("NavArea", asBEHAVE_ADDREF, "void f()", AS_METHODPR(NavArea, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "void AllocateNetworkState()", AS_METHODPR(NavArea, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "void ApplyAttributes()", AS_METHODPR(NavArea, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void NavArea::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Navigation/NavArea.h
    engine->RegisterObjectMethod("NavArea", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(NavArea, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "bool GetAnimationEnabled() const", AS_METHODPR(NavArea, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "bool get_animationEnabled() const", AS_METHODPR(NavArea, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // unsigned NavArea::GetAreaID() const | File: ../Navigation/NavArea.h
    engine->RegisterObjectMethod("NavArea", "uint GetAreaID() const", AS_METHODPR(NavArea, GetAreaID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "uint get_areaID() const", AS_METHODPR(NavArea, GetAreaID, () const, unsigned), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "Variant GetAttribute(uint) const", AS_METHODPR(NavArea, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "Variant get_attributes(uint) const", AS_METHODPR(NavArea, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "Variant GetAttribute(const String&in) const", AS_METHODPR(NavArea, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(NavArea, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(NavArea, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(NavArea, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(NavArea, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "Variant GetAttributeDefault(uint) const", AS_METHODPR(NavArea, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "Variant get_attributeDefaults(uint) const", AS_METHODPR(NavArea, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(NavArea, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "bool GetBlockEvents() const", AS_METHODPR(NavArea, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // BoundingBox NavArea::GetBoundingBox() const | File: ../Navigation/NavArea.h
    engine->RegisterObjectMethod("NavArea", "BoundingBox GetBoundingBox() const", AS_METHODPR(NavArea, GetBoundingBox, () const, BoundingBox), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "BoundingBox get_boundingBox() const", AS_METHODPR(NavArea, GetBoundingBox, () const, BoundingBox), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "const String& GetCategory() const", AS_METHODPR(NavArea, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "const String& get_category() const", AS_METHODPR(NavArea, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "Component@+ GetComponent(StringHash) const", AS_METHODPR(NavArea, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("NavArea", "VariantMap& GetEventDataMap() const", AS_METHODPR(NavArea, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "Object@+ GetEventSender() const", AS_METHODPR(NavArea, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(NavArea, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(NavArea, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "const VariantMap& GetGlobalVars() const", AS_METHODPR(NavArea, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "const VariantMap& get_globalVars() const", AS_METHODPR(NavArea, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "uint GetID() const", AS_METHODPR(NavArea, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "uint get_id() const", AS_METHODPR(NavArea, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(NavArea, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "Node@+ GetNode() const", AS_METHODPR(NavArea, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "Node@+ get_node() const", AS_METHODPR(NavArea, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "uint GetNumAttributes() const", AS_METHODPR(NavArea, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "uint get_numAttributes() const", AS_METHODPR(NavArea, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "uint GetNumNetworkAttributes() const", AS_METHODPR(NavArea, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(NavArea, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(NavArea, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(NavArea, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "Scene@+ GetScene() const", AS_METHODPR(NavArea, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(NavArea, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "StringHash GetType() const", AS_METHODPR(NavArea, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "StringHash get_type() const", AS_METHODPR(NavArea, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "const String& GetTypeName() const", AS_METHODPR(NavArea, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "const String& get_typeName() const", AS_METHODPR(NavArea, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // BoundingBox NavArea::GetWorldBoundingBox() const | File: ../Navigation/NavArea.h
    engine->RegisterObjectMethod("NavArea", "BoundingBox GetWorldBoundingBox() const", AS_METHODPR(NavArea, GetWorldBoundingBox, () const, BoundingBox), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "BoundingBox get_worldBoundingBox() const", AS_METHODPR(NavArea, GetWorldBoundingBox, () const, BoundingBox), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "bool HasEventHandlers() const", AS_METHODPR(NavArea, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(NavArea, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(NavArea, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "bool IsEnabled() const", AS_METHODPR(NavArea, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "bool get_enabled() const", AS_METHODPR(NavArea, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "bool IsEnabledEffective() const", AS_METHODPR(NavArea, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "bool get_enabledEffective() const", AS_METHODPR(NavArea, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "bool IsInstanceOf(StringHash) const", AS_METHODPR(NavArea, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "bool IsReplicated() const", AS_METHODPR(NavArea, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "bool get_replicated() const", AS_METHODPR(NavArea, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "bool IsTemporary() const", AS_METHODPR(NavArea, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "bool get_temporary() const", AS_METHODPR(NavArea, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "bool Load(Deserializer&)", AS_METHODPR(NavArea, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(NavArea, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "bool LoadXML(const XMLElement&in)", AS_METHODPR(NavArea, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "void MarkNetworkUpdate()", AS_METHODPR(NavArea, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // explicit NavArea::NavArea(Context* context) | File: ../Navigation/NavArea.h
    engine->RegisterObjectBehaviour("NavArea", asBEHAVE_FACTORY, "NavArea@+ f()", AS_FUNCTION(NavArea_NavArea_Context), AS_CALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(NavArea, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(NavArea, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(NavArea, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "void OnSetEnabled()", AS_METHODPR(NavArea, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "void PrepareNetworkUpdate()", AS_METHODPR(NavArea, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(NavArea, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(NavArea, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("NavArea", "int Refs() const", AS_METHODPR(NavArea, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "int get_refs() const", AS_METHODPR(NavArea, Refs, () const, int), AS_CALL_THISCALL);
    // static void NavArea::RegisterObject(Context* context) | File: ../Navigation/NavArea.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("NavArea", asBEHAVE_RELEASE, "void f()", AS_METHODPR(NavArea, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "void Remove()", AS_METHODPR(NavArea, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(NavArea, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "void RemoveInstanceDefault()", AS_METHODPR(NavArea, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "void RemoveObjectAnimation()", AS_METHODPR(NavArea, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "void ResetToDefault()", AS_METHODPR(NavArea, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "bool Save(Serializer&) const", AS_METHODPR(NavArea, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "bool SaveDefaultAttributes() const", AS_METHODPR(NavArea, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "bool SaveJSON(JSONValue&) const", AS_METHODPR(NavArea, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "bool SaveXML(XMLElement&) const", AS_METHODPR(NavArea, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "void SendEvent(StringHash)", AS_METHODPR(NavArea, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(NavArea, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "void SetAnimationEnabled(bool)", AS_METHODPR(NavArea, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "void set_animationEnabled(bool)", AS_METHODPR(NavArea, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "void SetAnimationTime(float)", AS_METHODPR(NavArea, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // void NavArea::SetAreaID(unsigned newID) | File: ../Navigation/NavArea.h
    engine->RegisterObjectMethod("NavArea", "void SetAreaID(uint)", AS_METHODPR(NavArea, SetAreaID, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "void set_areaID(uint)", AS_METHODPR(NavArea, SetAreaID, (unsigned), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(NavArea, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(NavArea, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(NavArea, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(NavArea, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(NavArea, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(NavArea, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(NavArea, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "void SetBlockEvents(bool)", AS_METHODPR(NavArea, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void NavArea::SetBoundingBox(const BoundingBox& bnds) | File: ../Navigation/NavArea.h
    engine->RegisterObjectMethod("NavArea", "void SetBoundingBox(const BoundingBox&in)", AS_METHODPR(NavArea, SetBoundingBox, (const BoundingBox&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "void set_boundingBox(const BoundingBox&in)", AS_METHODPR(NavArea, SetBoundingBox, (const BoundingBox&), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "void SetEnabled(bool)", AS_METHODPR(NavArea, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "void set_enabled(bool)", AS_METHODPR(NavArea, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(NavArea, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(NavArea, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "void SetInstanceDefault(bool)", AS_METHODPR(NavArea, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(NavArea, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(NavArea, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(NavArea, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(NavArea, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "void SetTemporary(bool)", AS_METHODPR(NavArea, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "void set_temporary(bool)", AS_METHODPR(NavArea, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "void UnsubscribeFromAllEvents()", AS_METHODPR(NavArea, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(NavArea_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(NavArea, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(NavArea, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(NavArea, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("NavArea", "int WeakRefs() const", AS_METHODPR(NavArea, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "int get_weakRefs() const", AS_METHODPR(NavArea, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(NavArea, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(NavArea, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(NavArea, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(NavArea, "NavArea")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(NavArea, "NavArea")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(NavArea, "NavArea")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(NavArea, "NavArea")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(NavArea, "NavArea")
#endif
#ifdef REGISTER_MANUAL_PART_NavArea
    REGISTER_MANUAL_PART_NavArea(NavArea, "NavArea")
#endif
    RegisterSubclass<Component, NavArea>(engine, "Component", "NavArea");
    RegisterSubclass<Animatable, NavArea>(engine, "Animatable", "NavArea");
    RegisterSubclass<Serializable, NavArea>(engine, "Serializable", "NavArea");
    RegisterSubclass<Object, NavArea>(engine, "Object", "NavArea");
    RegisterSubclass<RefCounted, NavArea>(engine, "RefCounted", "NavArea");
#endif

#ifdef URHO3D_NAVIGATION
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Navigable", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Navigable, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "void AllocateNetworkState()", AS_METHODPR(Navigable, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "void ApplyAttributes()", AS_METHODPR(Navigable, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(Navigable, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "bool GetAnimationEnabled() const", AS_METHODPR(Navigable, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "bool get_animationEnabled() const", AS_METHODPR(Navigable, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "Variant GetAttribute(uint) const", AS_METHODPR(Navigable, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "Variant get_attributes(uint) const", AS_METHODPR(Navigable, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "Variant GetAttribute(const String&in) const", AS_METHODPR(Navigable, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(Navigable, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(Navigable, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(Navigable, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(Navigable, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Navigable, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Navigable, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Navigable, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "bool GetBlockEvents() const", AS_METHODPR(Navigable, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "const String& GetCategory() const", AS_METHODPR(Navigable, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "const String& get_category() const", AS_METHODPR(Navigable, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "Component@+ GetComponent(StringHash) const", AS_METHODPR(Navigable, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Navigable", "VariantMap& GetEventDataMap() const", AS_METHODPR(Navigable, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "Object@+ GetEventSender() const", AS_METHODPR(Navigable, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Navigable, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Navigable, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Navigable, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "const VariantMap& get_globalVars() const", AS_METHODPR(Navigable, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "uint GetID() const", AS_METHODPR(Navigable, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "uint get_id() const", AS_METHODPR(Navigable, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Navigable, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "Node@+ GetNode() const", AS_METHODPR(Navigable, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "Node@+ get_node() const", AS_METHODPR(Navigable, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "uint GetNumAttributes() const", AS_METHODPR(Navigable, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "uint get_numAttributes() const", AS_METHODPR(Navigable, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "uint GetNumNetworkAttributes() const", AS_METHODPR(Navigable, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(Navigable, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(Navigable, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(Navigable, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "Scene@+ GetScene() const", AS_METHODPR(Navigable, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Navigable, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "StringHash GetType() const", AS_METHODPR(Navigable, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "StringHash get_type() const", AS_METHODPR(Navigable, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "const String& GetTypeName() const", AS_METHODPR(Navigable, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "const String& get_typeName() const", AS_METHODPR(Navigable, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "bool HasEventHandlers() const", AS_METHODPR(Navigable, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Navigable, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Navigable, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "bool IsEnabled() const", AS_METHODPR(Navigable, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "bool get_enabled() const", AS_METHODPR(Navigable, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "bool IsEnabledEffective() const", AS_METHODPR(Navigable, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "bool get_enabledEffective() const", AS_METHODPR(Navigable, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Navigable, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Navigable::IsRecursive() const | File: ../Navigation/Navigable.h
    engine->RegisterObjectMethod("Navigable", "bool IsRecursive() const", AS_METHODPR(Navigable, IsRecursive, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "bool get_recursive() const", AS_METHODPR(Navigable, IsRecursive, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "bool IsReplicated() const", AS_METHODPR(Navigable, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "bool get_replicated() const", AS_METHODPR(Navigable, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "bool IsTemporary() const", AS_METHODPR(Navigable, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "bool get_temporary() const", AS_METHODPR(Navigable, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "bool Load(Deserializer&)", AS_METHODPR(Navigable, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Navigable, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Navigable, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "void MarkNetworkUpdate()", AS_METHODPR(Navigable, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // explicit Navigable::Navigable(Context* context) | File: ../Navigation/Navigable.h
    engine->RegisterObjectBehaviour("Navigable", asBEHAVE_FACTORY, "Navigable@+ f()", AS_FUNCTION(Navigable_Navigable_Context), AS_CALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Navigable, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Navigable, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Navigable, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "void OnSetEnabled()", AS_METHODPR(Navigable, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "void PrepareNetworkUpdate()", AS_METHODPR(Navigable, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Navigable, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Navigable, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Navigable", "int Refs() const", AS_METHODPR(Navigable, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "int get_refs() const", AS_METHODPR(Navigable, Refs, () const, int), AS_CALL_THISCALL);
    // static void Navigable::RegisterObject(Context* context) | File: ../Navigation/Navigable.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Navigable", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Navigable, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "void Remove()", AS_METHODPR(Navigable, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(Navigable, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "void RemoveInstanceDefault()", AS_METHODPR(Navigable, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "void RemoveObjectAnimation()", AS_METHODPR(Navigable, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "void ResetToDefault()", AS_METHODPR(Navigable, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "bool Save(Serializer&) const", AS_METHODPR(Navigable, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "bool SaveDefaultAttributes() const", AS_METHODPR(Navigable, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "bool SaveJSON(JSONValue&) const", AS_METHODPR(Navigable, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "bool SaveXML(XMLElement&) const", AS_METHODPR(Navigable, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "void SendEvent(StringHash)", AS_METHODPR(Navigable, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Navigable, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "void SetAnimationEnabled(bool)", AS_METHODPR(Navigable, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "void set_animationEnabled(bool)", AS_METHODPR(Navigable, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "void SetAnimationTime(float)", AS_METHODPR(Navigable, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Navigable, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Navigable, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Navigable, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Navigable, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(Navigable, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(Navigable, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Navigable, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "void SetBlockEvents(bool)", AS_METHODPR(Navigable, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "void SetEnabled(bool)", AS_METHODPR(Navigable, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "void set_enabled(bool)", AS_METHODPR(Navigable, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Navigable, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Navigable, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "void SetInstanceDefault(bool)", AS_METHODPR(Navigable, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Navigable, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(Navigable, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(Navigable, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(Navigable, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Navigable::SetRecursive(bool enable) | File: ../Navigation/Navigable.h
    engine->RegisterObjectMethod("Navigable", "void SetRecursive(bool)", AS_METHODPR(Navigable, SetRecursive, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "void set_recursive(bool)", AS_METHODPR(Navigable, SetRecursive, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "void SetTemporary(bool)", AS_METHODPR(Navigable, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "void set_temporary(bool)", AS_METHODPR(Navigable, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "void UnsubscribeFromAllEvents()", AS_METHODPR(Navigable, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Navigable_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Navigable, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Navigable, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Navigable, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Navigable", "int WeakRefs() const", AS_METHODPR(Navigable, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "int get_weakRefs() const", AS_METHODPR(Navigable, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Navigable, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Navigable, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Navigable, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(Navigable, "Navigable")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(Navigable, "Navigable")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Navigable, "Navigable")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Navigable, "Navigable")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Navigable, "Navigable")
#endif
#ifdef REGISTER_MANUAL_PART_Navigable
    REGISTER_MANUAL_PART_Navigable(Navigable, "Navigable")
#endif
    RegisterSubclass<Component, Navigable>(engine, "Component", "Navigable");
    RegisterSubclass<Animatable, Navigable>(engine, "Animatable", "Navigable");
    RegisterSubclass<Serializable, Navigable>(engine, "Serializable", "Navigable");
    RegisterSubclass<Object, Navigable>(engine, "Object", "Navigable");
    RegisterSubclass<RefCounted, Navigable>(engine, "RefCounted", "Navigable");
#endif

#ifdef URHO3D_NAVIGATION
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("NavigationMesh", asBEHAVE_ADDREF, "void f()", AS_METHODPR(NavigationMesh, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // virtual bool NavigationMesh::AddTile(const PODVector<unsigned char>& tileData) | File: ../Navigation/NavigationMesh.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // virtual bool NavigationMesh::Allocate(const BoundingBox& boundingBox, unsigned maxTiles) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "bool Allocate(const BoundingBox&in, uint)", AS_METHODPR(NavigationMesh, Allocate, (const BoundingBox&, unsigned), bool), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "void AllocateNetworkState()", AS_METHODPR(NavigationMesh, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "void ApplyAttributes()", AS_METHODPR(NavigationMesh, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // virtual bool NavigationMesh::Build() | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "bool Build()", AS_METHODPR(NavigationMesh, Build, (), bool), AS_CALL_THISCALL);
    // virtual bool NavigationMesh::Build(const BoundingBox& boundingBox) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "bool Build(const BoundingBox&in)", AS_METHODPR(NavigationMesh, Build, (const BoundingBox&), bool), AS_CALL_THISCALL);
    // virtual bool NavigationMesh::Build(const IntVector2& from, const IntVector2& to) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "bool Build(const IntVector2&in, const IntVector2&in)", AS_METHODPR(NavigationMesh, Build, (const IntVector2&, const IntVector2&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void NavigationMesh::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(NavigationMesh, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // void NavigationMesh::DrawDebugGeometry(bool depthTest) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void DrawDebugGeometry(bool)", AS_METHODPR(NavigationMesh, DrawDebugGeometry, (bool), void), AS_CALL_THISCALL);
    // Vector3 NavigationMesh::FindNearestPoint(const Vector3& point, const Vector3& extents=Vector3::ONE, const dtQueryFilter* filter=nullptr, dtPolyRef* nearestRef=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "const dtQueryFilter*" can not automatically bind
    // void NavigationMesh::FindPath(PODVector<Vector3>& dest, const Vector3& start, const Vector3& end, const Vector3& extents=Vector3::ONE, const dtQueryFilter* filter=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "PODVector<Vector3>&" can not automatically bind
    // void NavigationMesh::FindPath(PODVector<NavigationPathPoint>& dest, const Vector3& start, const Vector3& end, const Vector3& extents=Vector3::ONE, const dtQueryFilter* filter=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "PODVector<NavigationPathPoint>&" can not automatically bind
    // float NavigationMesh::GetAgentHeight() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetAgentHeight() const", AS_METHODPR(NavigationMesh, GetAgentHeight, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_agentHeight() const", AS_METHODPR(NavigationMesh, GetAgentHeight, () const, float), AS_CALL_THISCALL);
    // float NavigationMesh::GetAgentMaxClimb() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetAgentMaxClimb() const", AS_METHODPR(NavigationMesh, GetAgentMaxClimb, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_agentMaxClimb() const", AS_METHODPR(NavigationMesh, GetAgentMaxClimb, () const, float), AS_CALL_THISCALL);
    // float NavigationMesh::GetAgentMaxSlope() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetAgentMaxSlope() const", AS_METHODPR(NavigationMesh, GetAgentMaxSlope, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_agentMaxSlope() const", AS_METHODPR(NavigationMesh, GetAgentMaxSlope, () const, float), AS_CALL_THISCALL);
    // float NavigationMesh::GetAgentRadius() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetAgentRadius() const", AS_METHODPR(NavigationMesh, GetAgentRadius, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_agentRadius() const", AS_METHODPR(NavigationMesh, GetAgentRadius, () const, float), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "bool GetAnimationEnabled() const", AS_METHODPR(NavigationMesh, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "bool get_animationEnabled() const", AS_METHODPR(NavigationMesh, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // float NavigationMesh::GetAreaCost(unsigned areaID) const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetAreaCost(uint) const", AS_METHODPR(NavigationMesh, GetAreaCost, (unsigned) const, float), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "Variant GetAttribute(uint) const", AS_METHODPR(NavigationMesh, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "Variant get_attributes(uint) const", AS_METHODPR(NavigationMesh, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "Variant GetAttribute(const String&in) const", AS_METHODPR(NavigationMesh, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(NavigationMesh, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(NavigationMesh, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(NavigationMesh, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(NavigationMesh, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "Variant GetAttributeDefault(uint) const", AS_METHODPR(NavigationMesh, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "Variant get_attributeDefaults(uint) const", AS_METHODPR(NavigationMesh, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(NavigationMesh, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "bool GetBlockEvents() const", AS_METHODPR(NavigationMesh, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const BoundingBox& NavigationMesh::GetBoundingBox() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "const BoundingBox& GetBoundingBox() const", AS_METHODPR(NavigationMesh, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "const BoundingBox& get_boundingBox() const", AS_METHODPR(NavigationMesh, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "const String& GetCategory() const", AS_METHODPR(NavigationMesh, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "const String& get_category() const", AS_METHODPR(NavigationMesh, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // float NavigationMesh::GetCellHeight() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetCellHeight() const", AS_METHODPR(NavigationMesh, GetCellHeight, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_cellHeight() const", AS_METHODPR(NavigationMesh, GetCellHeight, () const, float), AS_CALL_THISCALL);
    // float NavigationMesh::GetCellSize() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetCellSize() const", AS_METHODPR(NavigationMesh, GetCellSize, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_cellSize() const", AS_METHODPR(NavigationMesh, GetCellSize, () const, float), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "Component@+ GetComponent(StringHash) const", AS_METHODPR(NavigationMesh, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    // float NavigationMesh::GetDetailSampleDistance() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetDetailSampleDistance() const", AS_METHODPR(NavigationMesh, GetDetailSampleDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_detailSampleDistance() const", AS_METHODPR(NavigationMesh, GetDetailSampleDistance, () const, float), AS_CALL_THISCALL);
    // float NavigationMesh::GetDetailSampleMaxError() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetDetailSampleMaxError() const", AS_METHODPR(NavigationMesh, GetDetailSampleMaxError, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_detailSampleMaxError() const", AS_METHODPR(NavigationMesh, GetDetailSampleMaxError, () const, float), AS_CALL_THISCALL);
    // float NavigationMesh::GetDistanceToWall(const Vector3& point, float radius, const Vector3& extents=Vector3::ONE, const dtQueryFilter* filter=nullptr, Vector3* hitPos=nullptr, Vector3* hitNormal=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "const dtQueryFilter*" can not automatically bind
    // bool NavigationMesh::GetDrawNavAreas() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "bool GetDrawNavAreas() const", AS_METHODPR(NavigationMesh, GetDrawNavAreas, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "bool get_drawNavAreas() const", AS_METHODPR(NavigationMesh, GetDrawNavAreas, () const, bool), AS_CALL_THISCALL);
    // bool NavigationMesh::GetDrawOffMeshConnections() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "bool GetDrawOffMeshConnections() const", AS_METHODPR(NavigationMesh, GetDrawOffMeshConnections, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "bool get_drawOffMeshConnections() const", AS_METHODPR(NavigationMesh, GetDrawOffMeshConnections, () const, bool), AS_CALL_THISCALL);
    // float NavigationMesh::GetEdgeMaxError() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetEdgeMaxError() const", AS_METHODPR(NavigationMesh, GetEdgeMaxError, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_edgeMaxError() const", AS_METHODPR(NavigationMesh, GetEdgeMaxError, () const, float), AS_CALL_THISCALL);
    // float NavigationMesh::GetEdgeMaxLength() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetEdgeMaxLength() const", AS_METHODPR(NavigationMesh, GetEdgeMaxLength, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_edgeMaxLength() const", AS_METHODPR(NavigationMesh, GetEdgeMaxLength, () const, float), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "VariantMap& GetEventDataMap() const", AS_METHODPR(NavigationMesh, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "Object@+ GetEventSender() const", AS_METHODPR(NavigationMesh, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(NavigationMesh, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(NavigationMesh, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "const VariantMap& GetGlobalVars() const", AS_METHODPR(NavigationMesh, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "const VariantMap& get_globalVars() const", AS_METHODPR(NavigationMesh, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "uint GetID() const", AS_METHODPR(NavigationMesh, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "uint get_id() const", AS_METHODPR(NavigationMesh, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(NavigationMesh, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // String NavigationMesh::GetMeshName() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "String GetMeshName() const", AS_METHODPR(NavigationMesh, GetMeshName, () const, String), AS_CALL_THISCALL);
    // virtual PODVector<unsigned char> NavigationMesh::GetNavigationDataAttr() const | File: ../Navigation/NavigationMesh.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "Node@+ GetNode() const", AS_METHODPR(NavigationMesh, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "Node@+ get_node() const", AS_METHODPR(NavigationMesh, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "uint GetNumAttributes() const", AS_METHODPR(NavigationMesh, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "uint get_numAttributes() const", AS_METHODPR(NavigationMesh, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "uint GetNumNetworkAttributes() const", AS_METHODPR(NavigationMesh, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // IntVector2 NavigationMesh::GetNumTiles() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "IntVector2 GetNumTiles() const", AS_METHODPR(NavigationMesh, GetNumTiles, () const, IntVector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "IntVector2 get_numTiles() const", AS_METHODPR(NavigationMesh, GetNumTiles, () const, IntVector2), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(NavigationMesh, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(NavigationMesh, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(NavigationMesh, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // const Vector3& NavigationMesh::GetPadding() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "const Vector3& GetPadding() const", AS_METHODPR(NavigationMesh, GetPadding, () const, const Vector3&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "const Vector3& get_padding() const", AS_METHODPR(NavigationMesh, GetPadding, () const, const Vector3&), AS_CALL_THISCALL);
    // NavmeshPartitionType NavigationMesh::GetPartitionType() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "NavmeshPartitionType GetPartitionType() const", AS_METHODPR(NavigationMesh, GetPartitionType, () const, NavmeshPartitionType), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "NavmeshPartitionType get_partitionType() const", AS_METHODPR(NavigationMesh, GetPartitionType, () const, NavmeshPartitionType), AS_CALL_THISCALL);
    // Vector3 NavigationMesh::GetRandomPoint(const dtQueryFilter* filter=nullptr, dtPolyRef* randomRef=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "const dtQueryFilter*" can not automatically bind
    // Vector3 NavigationMesh::GetRandomPointInCircle(const Vector3& center, float radius, const Vector3& extents=Vector3::ONE, const dtQueryFilter* filter=nullptr, dtPolyRef* randomRef=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "const dtQueryFilter*" can not automatically bind
    // float NavigationMesh::GetRegionMergeSize() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetRegionMergeSize() const", AS_METHODPR(NavigationMesh, GetRegionMergeSize, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_regionMergeSize() const", AS_METHODPR(NavigationMesh, GetRegionMergeSize, () const, float), AS_CALL_THISCALL);
    // float NavigationMesh::GetRegionMinSize() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetRegionMinSize() const", AS_METHODPR(NavigationMesh, GetRegionMinSize, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_regionMinSize() const", AS_METHODPR(NavigationMesh, GetRegionMinSize, () const, float), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "Scene@+ GetScene() const", AS_METHODPR(NavigationMesh, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(NavigationMesh, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // BoundingBox NavigationMesh::GetTileBoundingBox(const IntVector2& tile) const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "BoundingBox GetTileBoundingBox(const IntVector2&in) const", AS_METHODPR(NavigationMesh, GetTileBoundingBox, (const IntVector2&) const, BoundingBox), AS_CALL_THISCALL);
    // virtual PODVector<unsigned char> NavigationMesh::GetTileData(const IntVector2& tile) const | File: ../Navigation/NavigationMesh.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // IntVector2 NavigationMesh::GetTileIndex(const Vector3& position) const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "IntVector2 GetTileIndex(const Vector3&in) const", AS_METHODPR(NavigationMesh, GetTileIndex, (const Vector3&) const, IntVector2), AS_CALL_THISCALL);
    // int NavigationMesh::GetTileSize() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "int GetTileSize() const", AS_METHODPR(NavigationMesh, GetTileSize, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "int get_tileSize() const", AS_METHODPR(NavigationMesh, GetTileSize, () const, int), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "StringHash GetType() const", AS_METHODPR(NavigationMesh, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "StringHash get_type() const", AS_METHODPR(NavigationMesh, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "const String& GetTypeName() const", AS_METHODPR(NavigationMesh, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "const String& get_typeName() const", AS_METHODPR(NavigationMesh, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // BoundingBox NavigationMesh::GetWorldBoundingBox() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "BoundingBox GetWorldBoundingBox() const", AS_METHODPR(NavigationMesh, GetWorldBoundingBox, () const, BoundingBox), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "BoundingBox get_worldBoundingBox() const", AS_METHODPR(NavigationMesh, GetWorldBoundingBox, () const, BoundingBox), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "bool HasEventHandlers() const", AS_METHODPR(NavigationMesh, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(NavigationMesh, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(NavigationMesh, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool NavigationMesh::HasTile(const IntVector2& tile) const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "bool HasTile(const IntVector2&in) const", AS_METHODPR(NavigationMesh, HasTile, (const IntVector2&) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "bool IsEnabled() const", AS_METHODPR(NavigationMesh, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "bool get_enabled() const", AS_METHODPR(NavigationMesh, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "bool IsEnabledEffective() const", AS_METHODPR(NavigationMesh, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "bool get_enabledEffective() const", AS_METHODPR(NavigationMesh, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool NavigationMesh::IsInitialized() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "bool IsInitialized() const", AS_METHODPR(NavigationMesh, IsInitialized, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "bool get_initialized() const", AS_METHODPR(NavigationMesh, IsInitialized, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "bool IsInstanceOf(StringHash) const", AS_METHODPR(NavigationMesh, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "bool IsReplicated() const", AS_METHODPR(NavigationMesh, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "bool get_replicated() const", AS_METHODPR(NavigationMesh, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "bool IsTemporary() const", AS_METHODPR(NavigationMesh, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "bool get_temporary() const", AS_METHODPR(NavigationMesh, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "bool Load(Deserializer&)", AS_METHODPR(NavigationMesh, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(NavigationMesh, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "bool LoadXML(const XMLElement&in)", AS_METHODPR(NavigationMesh, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "void MarkNetworkUpdate()", AS_METHODPR(NavigationMesh, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // Vector3 NavigationMesh::MoveAlongSurface(const Vector3& start, const Vector3& end, const Vector3& extents=Vector3::ONE, int maxVisited=3, const dtQueryFilter* filter=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "const dtQueryFilter*" can not automatically bind
    // explicit NavigationMesh::NavigationMesh(Context* context) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectBehaviour("NavigationMesh", asBEHAVE_FACTORY, "NavigationMesh@+ f()", AS_FUNCTION(NavigationMesh_NavigationMesh_Context), AS_CALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(NavigationMesh, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(NavigationMesh, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(NavigationMesh, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "void OnSetEnabled()", AS_METHODPR(NavigationMesh, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "void PrepareNetworkUpdate()", AS_METHODPR(NavigationMesh, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // Vector3 NavigationMesh::Raycast(const Vector3& start, const Vector3& end, const Vector3& extents=Vector3::ONE, const dtQueryFilter* filter=nullptr, Vector3* hitNormal=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "const dtQueryFilter*" can not automatically bind
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(NavigationMesh, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(NavigationMesh, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("NavigationMesh", "int Refs() const", AS_METHODPR(NavigationMesh, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "int get_refs() const", AS_METHODPR(NavigationMesh, Refs, () const, int), AS_CALL_THISCALL);
    // static void NavigationMesh::RegisterObject(Context* context) | File: ../Navigation/NavigationMesh.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("NavigationMesh", asBEHAVE_RELEASE, "void f()", AS_METHODPR(NavigationMesh, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "void Remove()", AS_METHODPR(NavigationMesh, Remove, (), void), AS_CALL_THISCALL);
    // virtual void NavigationMesh::RemoveAllTiles() | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void RemoveAllTiles()", AS_METHODPR(NavigationMesh, RemoveAllTiles, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(NavigationMesh, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "void RemoveInstanceDefault()", AS_METHODPR(NavigationMesh, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "void RemoveObjectAnimation()", AS_METHODPR(NavigationMesh, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // virtual void NavigationMesh::RemoveTile(const IntVector2& tile) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void RemoveTile(const IntVector2&in)", AS_METHODPR(NavigationMesh, RemoveTile, (const IntVector2&), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "void ResetToDefault()", AS_METHODPR(NavigationMesh, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "bool Save(Serializer&) const", AS_METHODPR(NavigationMesh, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "bool SaveDefaultAttributes() const", AS_METHODPR(NavigationMesh, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "bool SaveJSON(JSONValue&) const", AS_METHODPR(NavigationMesh, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "bool SaveXML(XMLElement&) const", AS_METHODPR(NavigationMesh, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "void SendEvent(StringHash)", AS_METHODPR(NavigationMesh, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(NavigationMesh, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void NavigationMesh::SetAgentHeight(float height) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetAgentHeight(float)", AS_METHODPR(NavigationMesh, SetAgentHeight, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_agentHeight(float)", AS_METHODPR(NavigationMesh, SetAgentHeight, (float), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetAgentMaxClimb(float maxClimb) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetAgentMaxClimb(float)", AS_METHODPR(NavigationMesh, SetAgentMaxClimb, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_agentMaxClimb(float)", AS_METHODPR(NavigationMesh, SetAgentMaxClimb, (float), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetAgentMaxSlope(float maxSlope) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetAgentMaxSlope(float)", AS_METHODPR(NavigationMesh, SetAgentMaxSlope, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_agentMaxSlope(float)", AS_METHODPR(NavigationMesh, SetAgentMaxSlope, (float), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetAgentRadius(float radius) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetAgentRadius(float)", AS_METHODPR(NavigationMesh, SetAgentRadius, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_agentRadius(float)", AS_METHODPR(NavigationMesh, SetAgentRadius, (float), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetAnimationEnabled(bool)", AS_METHODPR(NavigationMesh, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_animationEnabled(bool)", AS_METHODPR(NavigationMesh, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetAnimationTime(float)", AS_METHODPR(NavigationMesh, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetAreaCost(unsigned areaID, float cost) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetAreaCost(uint, float)", AS_METHODPR(NavigationMesh, SetAreaCost, (unsigned, float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(NavigationMesh, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(NavigationMesh, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(NavigationMesh, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(NavigationMesh, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(NavigationMesh, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(NavigationMesh, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(NavigationMesh, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetBlockEvents(bool)", AS_METHODPR(NavigationMesh, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetCellHeight(float height) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetCellHeight(float)", AS_METHODPR(NavigationMesh, SetCellHeight, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_cellHeight(float)", AS_METHODPR(NavigationMesh, SetCellHeight, (float), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetCellSize(float size) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetCellSize(float)", AS_METHODPR(NavigationMesh, SetCellSize, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_cellSize(float)", AS_METHODPR(NavigationMesh, SetCellSize, (float), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetDetailSampleDistance(float distance) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetDetailSampleDistance(float)", AS_METHODPR(NavigationMesh, SetDetailSampleDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_detailSampleDistance(float)", AS_METHODPR(NavigationMesh, SetDetailSampleDistance, (float), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetDetailSampleMaxError(float error) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetDetailSampleMaxError(float)", AS_METHODPR(NavigationMesh, SetDetailSampleMaxError, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_detailSampleMaxError(float)", AS_METHODPR(NavigationMesh, SetDetailSampleMaxError, (float), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetDrawNavAreas(bool enable) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetDrawNavAreas(bool)", AS_METHODPR(NavigationMesh, SetDrawNavAreas, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_drawNavAreas(bool)", AS_METHODPR(NavigationMesh, SetDrawNavAreas, (bool), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetDrawOffMeshConnections(bool enable) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetDrawOffMeshConnections(bool)", AS_METHODPR(NavigationMesh, SetDrawOffMeshConnections, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_drawOffMeshConnections(bool)", AS_METHODPR(NavigationMesh, SetDrawOffMeshConnections, (bool), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetEdgeMaxError(float error) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetEdgeMaxError(float)", AS_METHODPR(NavigationMesh, SetEdgeMaxError, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_edgeMaxError(float)", AS_METHODPR(NavigationMesh, SetEdgeMaxError, (float), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetEdgeMaxLength(float length) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetEdgeMaxLength(float)", AS_METHODPR(NavigationMesh, SetEdgeMaxLength, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_edgeMaxLength(float)", AS_METHODPR(NavigationMesh, SetEdgeMaxLength, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetEnabled(bool)", AS_METHODPR(NavigationMesh, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_enabled(bool)", AS_METHODPR(NavigationMesh, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(NavigationMesh, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(NavigationMesh, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetInstanceDefault(bool)", AS_METHODPR(NavigationMesh, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(NavigationMesh, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetMeshName(const String& newName) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetMeshName(const String&in)", AS_METHODPR(NavigationMesh, SetMeshName, (const String&), void), AS_CALL_THISCALL);
    // virtual void NavigationMesh::SetNavigationDataAttr(const PODVector<unsigned char>& value) | File: ../Navigation/NavigationMesh.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(NavigationMesh, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(NavigationMesh, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(NavigationMesh, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetPadding(const Vector3& padding) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetPadding(const Vector3&in)", AS_METHODPR(NavigationMesh, SetPadding, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_padding(const Vector3&in)", AS_METHODPR(NavigationMesh, SetPadding, (const Vector3&), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetPartitionType(NavmeshPartitionType partitionType) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetPartitionType(NavmeshPartitionType)", AS_METHODPR(NavigationMesh, SetPartitionType, (NavmeshPartitionType), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_partitionType(NavmeshPartitionType)", AS_METHODPR(NavigationMesh, SetPartitionType, (NavmeshPartitionType), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetRegionMergeSize(float size) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetRegionMergeSize(float)", AS_METHODPR(NavigationMesh, SetRegionMergeSize, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_regionMergeSize(float)", AS_METHODPR(NavigationMesh, SetRegionMergeSize, (float), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetRegionMinSize(float size) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetRegionMinSize(float)", AS_METHODPR(NavigationMesh, SetRegionMinSize, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_regionMinSize(float)", AS_METHODPR(NavigationMesh, SetRegionMinSize, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetTemporary(bool)", AS_METHODPR(NavigationMesh, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_temporary(bool)", AS_METHODPR(NavigationMesh, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void NavigationMesh::SetTileSize(int size) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetTileSize(int)", AS_METHODPR(NavigationMesh, SetTileSize, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_tileSize(int)", AS_METHODPR(NavigationMesh, SetTileSize, (int), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "void UnsubscribeFromAllEvents()", AS_METHODPR(NavigationMesh, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(NavigationMesh_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(NavigationMesh, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(NavigationMesh, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(NavigationMesh, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("NavigationMesh", "int WeakRefs() const", AS_METHODPR(NavigationMesh, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "int get_weakRefs() const", AS_METHODPR(NavigationMesh, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(NavigationMesh, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(NavigationMesh, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(NavigationMesh, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(NavigationMesh, "NavigationMesh")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(NavigationMesh, "NavigationMesh")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(NavigationMesh, "NavigationMesh")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(NavigationMesh, "NavigationMesh")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(NavigationMesh, "NavigationMesh")
#endif
#ifdef REGISTER_MANUAL_PART_NavigationMesh
    REGISTER_MANUAL_PART_NavigationMesh(NavigationMesh, "NavigationMesh")
#endif
    RegisterSubclass<Component, NavigationMesh>(engine, "Component", "NavigationMesh");
    RegisterSubclass<Animatable, NavigationMesh>(engine, "Animatable", "NavigationMesh");
    RegisterSubclass<Serializable, NavigationMesh>(engine, "Serializable", "NavigationMesh");
    RegisterSubclass<Object, NavigationMesh>(engine, "Object", "NavigationMesh");
    RegisterSubclass<RefCounted, NavigationMesh>(engine, "RefCounted", "NavigationMesh");
#endif

#ifdef URHO3D_NETWORK
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Network", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Network, AddRef, (), void), AS_CALL_THISCALL);
    // void Network::AttemptNATPunchtrough(const String& guid, Scene* scene, const VariantMap& identity=Variant::emptyVariantMap) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void AttemptNATPunchtrough(const String&in, Scene@+, const VariantMap&in = VariantMap())", AS_METHODPR(Network, AttemptNATPunchtrough, (const String&, Scene*, const VariantMap&), void), AS_CALL_THISCALL);
    // void Network::BanAddress(const String& address) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void BanAddress(const String&in)", AS_METHODPR(Network, BanAddress, (const String&), void), AS_CALL_THISCALL);
    // void Network::BroadcastMessage(int msgID, bool reliable, bool inOrder, const VectorBuffer& msg, unsigned contentID=0) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void BroadcastMessage(int, bool, bool, const VectorBuffer&in, uint = 0)", AS_METHODPR(Network, BroadcastMessage, (int, bool, bool, const VectorBuffer&, unsigned), void), AS_CALL_THISCALL);
    // void Network::BroadcastMessage(int msgID, bool reliable, bool inOrder, const unsigned char* data, unsigned numBytes, unsigned contentID=0) | File: ../Network/Network.h
    // Error: type "const unsigned char*" can not automatically bind
    // void Network::BroadcastRemoteEvent(StringHash eventType, bool inOrder, const VariantMap& eventData=Variant::emptyVariantMap) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void BroadcastRemoteEvent(StringHash, bool, const VariantMap&in = VariantMap())", AS_METHODPR(Network, BroadcastRemoteEvent, (StringHash, bool, const VariantMap&), void), AS_CALL_THISCALL);
    // void Network::BroadcastRemoteEvent(Scene* scene, StringHash eventType, bool inOrder, const VariantMap& eventData=Variant::emptyVariantMap) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void BroadcastRemoteEvent(Scene@+, StringHash, bool, const VariantMap&in = VariantMap())", AS_METHODPR(Network, BroadcastRemoteEvent, (Scene*, StringHash, bool, const VariantMap&), void), AS_CALL_THISCALL);
    // void Network::BroadcastRemoteEvent(Node* node, StringHash eventType, bool inOrder, const VariantMap& eventData=Variant::emptyVariantMap) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void BroadcastRemoteEvent(Node@+, StringHash, bool, const VariantMap&in = VariantMap())", AS_METHODPR(Network, BroadcastRemoteEvent, (Node*, StringHash, bool, const VariantMap&), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool Network::CheckRemoteEvent(StringHash eventType) const | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "bool CheckRemoteEvent(StringHash) const", AS_METHODPR(Network, CheckRemoteEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // void Network::ClientDisconnected(const SLNet::AddressOrGUID& connection) | File: ../Network/Network.h
    // Error: type "const SLNet::AddressOrGUID&" can not automatically bind
    // bool Network::Connect(const String& address, unsigned short port, Scene* scene, const VariantMap& identity=Variant::emptyVariantMap) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "bool Connect(const String&in, uint16, Scene@+, const VariantMap&in = VariantMap())", AS_METHODPR(Network, Connect, (const String&, unsigned short, Scene*, const VariantMap&), bool), AS_CALL_THISCALL);
    // void Network::Disconnect(int waitMSec=0) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void Disconnect(int = 0)", AS_METHODPR(Network, Disconnect, (int), void), AS_CALL_THISCALL);
    // void Network::DiscoverHosts(unsigned port) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void DiscoverHosts(uint)", AS_METHODPR(Network, DiscoverHosts, (unsigned), void), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "bool GetBlockEvents() const", AS_METHODPR(Network, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "const String& GetCategory() const", AS_METHODPR(Network, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Network", "const String& get_category() const", AS_METHODPR(Network, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Vector<SharedPtr<Connection>> Network::GetClientConnections() const | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "Array<Connection@>@ GetClientConnections() const", AS_FUNCTION_OBJFIRST(Network_GetClientConnections_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Network", "Array<Connection@>@ get_clientConnections() const", AS_FUNCTION_OBJFIRST(Network_GetClientConnections_void), AS_CALL_CDECL_OBJFIRST);
    // Connection* Network::GetConnection(const SLNet::AddressOrGUID& connection) const | File: ../Network/Network.h
    // Error: type "const SLNet::AddressOrGUID&" can not automatically bind
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "VariantMap& GetEventDataMap() const", AS_METHODPR(Network, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "Object@+ GetEventSender() const", AS_METHODPR(Network, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Network, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Network", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Network, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Network, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Network", "const VariantMap& get_globalVars() const", AS_METHODPR(Network, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // const String& Network::GetGUID() const | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "const String& GetGUID() const", AS_METHODPR(Network, GetGUID, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Network", "const String& get_guid() const", AS_METHODPR(Network, GetGUID, () const, const String&), AS_CALL_THISCALL);
    // const String& Network::GetPackageCacheDir() const | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "const String& GetPackageCacheDir() const", AS_METHODPR(Network, GetPackageCacheDir, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Network", "const String& get_packageCacheDir() const", AS_METHODPR(Network, GetPackageCacheDir, () const, const String&), AS_CALL_THISCALL);
    // Connection* Network::GetServerConnection() const | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "Connection@+ GetServerConnection() const", AS_METHODPR(Network, GetServerConnection, () const, Connection*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Network", "Connection@+ get_serverConnection() const", AS_METHODPR(Network, GetServerConnection, () const, Connection*), AS_CALL_THISCALL);
    // int Network::GetSimulatedLatency() const | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "int GetSimulatedLatency() const", AS_METHODPR(Network, GetSimulatedLatency, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Network", "int get_simulatedLatency() const", AS_METHODPR(Network, GetSimulatedLatency, () const, int), AS_CALL_THISCALL);
    // float Network::GetSimulatedPacketLoss() const | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "float GetSimulatedPacketLoss() const", AS_METHODPR(Network, GetSimulatedPacketLoss, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Network", "float get_simulatedPacketLoss() const", AS_METHODPR(Network, GetSimulatedPacketLoss, () const, float), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Network, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "StringHash GetType() const", AS_METHODPR(Network, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Network", "StringHash get_type() const", AS_METHODPR(Network, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "const String& GetTypeName() const", AS_METHODPR(Network, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Network", "const String& get_typeName() const", AS_METHODPR(Network, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // int Network::GetUpdateFps() const | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "int GetUpdateFps() const", AS_METHODPR(Network, GetUpdateFps, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Network", "int get_updateFps() const", AS_METHODPR(Network, GetUpdateFps, () const, int), AS_CALL_THISCALL);
    // void Network::HandleMessage(const SLNet::AddressOrGUID& source, int packetID, int msgID, const char* data, size_t numBytes) | File: ../Network/Network.h
    // Error: type "const SLNet::AddressOrGUID&" can not automatically bind
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "bool HasEventHandlers() const", AS_METHODPR(Network, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Network, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Network, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Network, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Network::IsServerRunning() const | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "bool IsServerRunning() const", AS_METHODPR(Network, IsServerRunning, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Network", "bool get_serverRunning() const", AS_METHODPR(Network, IsServerRunning, () const, bool), AS_CALL_THISCALL);
    // SharedPtr<HttpRequest> Network::MakeHttpRequest(const String& url, const String& verb=String::EMPTY, const Vector<String>& headers=Vector<String>(), const String& postData=String::EMPTY) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "HttpRequest@+ MakeHttpRequest(const String&in, const String&in = String::EMPTY, Array<String>@+ = null, const String&in = String::EMPTY)", AS_FUNCTION_OBJFIRST(Network_MakeHttpRequest_String_String_VectorString_String), AS_CALL_CDECL_OBJFIRST);
    // explicit Network::Network(Context* context) | File: ../Network/Network.h
    engine->RegisterObjectBehaviour("Network", asBEHAVE_FACTORY, "Network@+ f()", AS_FUNCTION(Network_Network_Context), AS_CALL_CDECL);
    // void Network::NewConnectionEstablished(const SLNet::AddressOrGUID& connection) | File: ../Network/Network.h
    // Error: type "const SLNet::AddressOrGUID&" can not automatically bind
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Network, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // void Network::PostUpdate(float timeStep) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void PostUpdate(float)", AS_METHODPR(Network, PostUpdate, (float), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Network", "int Refs() const", AS_METHODPR(Network, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Network", "int get_refs() const", AS_METHODPR(Network, Refs, () const, int), AS_CALL_THISCALL);
    // void Network::RegisterRemoteEvent(StringHash eventType) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void RegisterRemoteEvent(StringHash)", AS_METHODPR(Network, RegisterRemoteEvent, (StringHash), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Network", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Network, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "void SendEvent(StringHash)", AS_METHODPR(Network, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Network, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Network::SendPackageToClients(Scene* scene, PackageFile* package) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void SendPackageToClients(Scene@+, PackageFile@+)", AS_METHODPR(Network, SendPackageToClients, (Scene*, PackageFile*), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "void SetBlockEvents(bool)", AS_METHODPR(Network, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Network::SetDiscoveryBeacon(const VariantMap& data) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void SetDiscoveryBeacon(const VariantMap&in)", AS_METHODPR(Network, SetDiscoveryBeacon, (const VariantMap&), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Network, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Network, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Network::SetNATServerInfo(const String& address, unsigned short port) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void SetNATServerInfo(const String&in, uint16)", AS_METHODPR(Network, SetNATServerInfo, (const String&, unsigned short), void), AS_CALL_THISCALL);
    // void Network::SetPackageCacheDir(const String& path) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void SetPackageCacheDir(const String&in)", AS_METHODPR(Network, SetPackageCacheDir, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void set_packageCacheDir(const String&in)", AS_METHODPR(Network, SetPackageCacheDir, (const String&), void), AS_CALL_THISCALL);
    // void Network::SetPassword(const String& password) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void SetPassword(const String&in)", AS_METHODPR(Network, SetPassword, (const String&), void), AS_CALL_THISCALL);
    // void Network::SetSimulatedLatency(int ms) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void SetSimulatedLatency(int)", AS_METHODPR(Network, SetSimulatedLatency, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void set_simulatedLatency(int)", AS_METHODPR(Network, SetSimulatedLatency, (int), void), AS_CALL_THISCALL);
    // void Network::SetSimulatedPacketLoss(float probability) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void SetSimulatedPacketLoss(float)", AS_METHODPR(Network, SetSimulatedPacketLoss, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void set_simulatedPacketLoss(float)", AS_METHODPR(Network, SetSimulatedPacketLoss, (float), void), AS_CALL_THISCALL);
    // void Network::SetUpdateFps(int fps) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void SetUpdateFps(int)", AS_METHODPR(Network, SetUpdateFps, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void set_updateFps(int)", AS_METHODPR(Network, SetUpdateFps, (int), void), AS_CALL_THISCALL);
    // void Network::StartNATClient() | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void StartNATClient()", AS_METHODPR(Network, StartNATClient, (), void), AS_CALL_THISCALL);
    // bool Network::StartServer(unsigned short port, unsigned int maxConnections=128) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "bool StartServer(uint16, uint = 128)", AS_METHODPR(Network, StartServer, (unsigned short, unsigned int), bool), AS_CALL_THISCALL);
    // void Network::StopServer() | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void StopServer()", AS_METHODPR(Network, StopServer, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Network::UnregisterAllRemoteEvents() | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void UnregisterAllRemoteEvents()", AS_METHODPR(Network, UnregisterAllRemoteEvents, (), void), AS_CALL_THISCALL);
    // void Network::UnregisterRemoteEvent(StringHash eventType) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void UnregisterRemoteEvent(StringHash)", AS_METHODPR(Network, UnregisterRemoteEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "void UnsubscribeFromAllEvents()", AS_METHODPR(Network, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Network_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Network, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Network, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Network, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void Network::Update(float timeStep) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void Update(float)", AS_METHODPR(Network, Update, (float), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Network", "int WeakRefs() const", AS_METHODPR(Network, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Network", "int get_weakRefs() const", AS_METHODPR(Network, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Network, "Network")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Network, "Network")
#endif
#ifdef REGISTER_MANUAL_PART_Network
    REGISTER_MANUAL_PART_Network(Network, "Network")
#endif
    RegisterSubclass<Object, Network>(engine, "Object", "Network");
    RegisterSubclass<RefCounted, Network>(engine, "RefCounted", "Network");
#endif

#ifdef URHO3D_NETWORK
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("NetworkPriority", asBEHAVE_ADDREF, "void f()", AS_METHODPR(NetworkPriority, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "void AllocateNetworkState()", AS_METHODPR(NetworkPriority, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "void ApplyAttributes()", AS_METHODPR(NetworkPriority, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool NetworkPriority::CheckUpdate(float distance, float& accumulator) | File: ../Network/NetworkPriority.h
    engine->RegisterObjectMethod("NetworkPriority", "bool CheckUpdate(float, float&)", AS_METHODPR(NetworkPriority, CheckUpdate, (float, float&), bool), AS_CALL_THISCALL);
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(NetworkPriority, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool NetworkPriority::GetAlwaysUpdateOwner() const | File: ../Network/NetworkPriority.h
    engine->RegisterObjectMethod("NetworkPriority", "bool GetAlwaysUpdateOwner() const", AS_METHODPR(NetworkPriority, GetAlwaysUpdateOwner, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "bool get_alwaysUpdateOwner() const", AS_METHODPR(NetworkPriority, GetAlwaysUpdateOwner, () const, bool), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "bool GetAnimationEnabled() const", AS_METHODPR(NetworkPriority, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "bool get_animationEnabled() const", AS_METHODPR(NetworkPriority, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "Variant GetAttribute(uint) const", AS_METHODPR(NetworkPriority, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "Variant get_attributes(uint) const", AS_METHODPR(NetworkPriority, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "Variant GetAttribute(const String&in) const", AS_METHODPR(NetworkPriority, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(NetworkPriority, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(NetworkPriority, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(NetworkPriority, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(NetworkPriority, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "Variant GetAttributeDefault(uint) const", AS_METHODPR(NetworkPriority, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "Variant get_attributeDefaults(uint) const", AS_METHODPR(NetworkPriority, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(NetworkPriority, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // float NetworkPriority::GetBasePriority() const | File: ../Network/NetworkPriority.h
    engine->RegisterObjectMethod("NetworkPriority", "float GetBasePriority() const", AS_METHODPR(NetworkPriority, GetBasePriority, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "float get_basePriority() const", AS_METHODPR(NetworkPriority, GetBasePriority, () const, float), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "bool GetBlockEvents() const", AS_METHODPR(NetworkPriority, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "const String& GetCategory() const", AS_METHODPR(NetworkPriority, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "const String& get_category() const", AS_METHODPR(NetworkPriority, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "Component@+ GetComponent(StringHash) const", AS_METHODPR(NetworkPriority, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    // float NetworkPriority::GetDistanceFactor() const | File: ../Network/NetworkPriority.h
    engine->RegisterObjectMethod("NetworkPriority", "float GetDistanceFactor() const", AS_METHODPR(NetworkPriority, GetDistanceFactor, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "float get_distanceFactor() const", AS_METHODPR(NetworkPriority, GetDistanceFactor, () const, float), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "VariantMap& GetEventDataMap() const", AS_METHODPR(NetworkPriority, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "Object@+ GetEventSender() const", AS_METHODPR(NetworkPriority, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(NetworkPriority, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(NetworkPriority, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "const VariantMap& GetGlobalVars() const", AS_METHODPR(NetworkPriority, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "const VariantMap& get_globalVars() const", AS_METHODPR(NetworkPriority, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "uint GetID() const", AS_METHODPR(NetworkPriority, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "uint get_id() const", AS_METHODPR(NetworkPriority, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(NetworkPriority, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // float NetworkPriority::GetMinPriority() const | File: ../Network/NetworkPriority.h
    engine->RegisterObjectMethod("NetworkPriority", "float GetMinPriority() const", AS_METHODPR(NetworkPriority, GetMinPriority, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "float get_minPriority() const", AS_METHODPR(NetworkPriority, GetMinPriority, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "Node@+ GetNode() const", AS_METHODPR(NetworkPriority, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "Node@+ get_node() const", AS_METHODPR(NetworkPriority, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "uint GetNumAttributes() const", AS_METHODPR(NetworkPriority, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "uint get_numAttributes() const", AS_METHODPR(NetworkPriority, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "uint GetNumNetworkAttributes() const", AS_METHODPR(NetworkPriority, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(NetworkPriority, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(NetworkPriority, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(NetworkPriority, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "Scene@+ GetScene() const", AS_METHODPR(NetworkPriority, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(NetworkPriority, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "StringHash GetType() const", AS_METHODPR(NetworkPriority, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "StringHash get_type() const", AS_METHODPR(NetworkPriority, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "const String& GetTypeName() const", AS_METHODPR(NetworkPriority, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "const String& get_typeName() const", AS_METHODPR(NetworkPriority, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "bool HasEventHandlers() const", AS_METHODPR(NetworkPriority, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(NetworkPriority, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(NetworkPriority, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "bool IsEnabled() const", AS_METHODPR(NetworkPriority, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "bool get_enabled() const", AS_METHODPR(NetworkPriority, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "bool IsEnabledEffective() const", AS_METHODPR(NetworkPriority, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "bool get_enabledEffective() const", AS_METHODPR(NetworkPriority, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "bool IsInstanceOf(StringHash) const", AS_METHODPR(NetworkPriority, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "bool IsReplicated() const", AS_METHODPR(NetworkPriority, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "bool get_replicated() const", AS_METHODPR(NetworkPriority, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "bool IsTemporary() const", AS_METHODPR(NetworkPriority, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "bool get_temporary() const", AS_METHODPR(NetworkPriority, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "bool Load(Deserializer&)", AS_METHODPR(NetworkPriority, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(NetworkPriority, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "bool LoadXML(const XMLElement&in)", AS_METHODPR(NetworkPriority, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "void MarkNetworkUpdate()", AS_METHODPR(NetworkPriority, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // explicit NetworkPriority::NetworkPriority(Context* context) | File: ../Network/NetworkPriority.h
    engine->RegisterObjectBehaviour("NetworkPriority", asBEHAVE_FACTORY, "NetworkPriority@+ f()", AS_FUNCTION(NetworkPriority_NetworkPriority_Context), AS_CALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(NetworkPriority, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(NetworkPriority, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(NetworkPriority, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "void OnSetEnabled()", AS_METHODPR(NetworkPriority, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "void PrepareNetworkUpdate()", AS_METHODPR(NetworkPriority, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(NetworkPriority, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(NetworkPriority, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("NetworkPriority", "int Refs() const", AS_METHODPR(NetworkPriority, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "int get_refs() const", AS_METHODPR(NetworkPriority, Refs, () const, int), AS_CALL_THISCALL);
    // static void NetworkPriority::RegisterObject(Context* context) | File: ../Network/NetworkPriority.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("NetworkPriority", asBEHAVE_RELEASE, "void f()", AS_METHODPR(NetworkPriority, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "void Remove()", AS_METHODPR(NetworkPriority, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(NetworkPriority, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "void RemoveInstanceDefault()", AS_METHODPR(NetworkPriority, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "void RemoveObjectAnimation()", AS_METHODPR(NetworkPriority, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "void ResetToDefault()", AS_METHODPR(NetworkPriority, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "bool Save(Serializer&) const", AS_METHODPR(NetworkPriority, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "bool SaveDefaultAttributes() const", AS_METHODPR(NetworkPriority, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "bool SaveJSON(JSONValue&) const", AS_METHODPR(NetworkPriority, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "bool SaveXML(XMLElement&) const", AS_METHODPR(NetworkPriority, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "void SendEvent(StringHash)", AS_METHODPR(NetworkPriority, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(NetworkPriority, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void NetworkPriority::SetAlwaysUpdateOwner(bool enable) | File: ../Network/NetworkPriority.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetAlwaysUpdateOwner(bool)", AS_METHODPR(NetworkPriority, SetAlwaysUpdateOwner, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "void set_alwaysUpdateOwner(bool)", AS_METHODPR(NetworkPriority, SetAlwaysUpdateOwner, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetAnimationEnabled(bool)", AS_METHODPR(NetworkPriority, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "void set_animationEnabled(bool)", AS_METHODPR(NetworkPriority, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetAnimationTime(float)", AS_METHODPR(NetworkPriority, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(NetworkPriority, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(NetworkPriority, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(NetworkPriority, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(NetworkPriority, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(NetworkPriority, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(NetworkPriority, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(NetworkPriority, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void NetworkPriority::SetBasePriority(float priority) | File: ../Network/NetworkPriority.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetBasePriority(float)", AS_METHODPR(NetworkPriority, SetBasePriority, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "void set_basePriority(float)", AS_METHODPR(NetworkPriority, SetBasePriority, (float), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetBlockEvents(bool)", AS_METHODPR(NetworkPriority, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void NetworkPriority::SetDistanceFactor(float factor) | File: ../Network/NetworkPriority.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetDistanceFactor(float)", AS_METHODPR(NetworkPriority, SetDistanceFactor, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "void set_distanceFactor(float)", AS_METHODPR(NetworkPriority, SetDistanceFactor, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetEnabled(bool)", AS_METHODPR(NetworkPriority, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "void set_enabled(bool)", AS_METHODPR(NetworkPriority, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(NetworkPriority, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(NetworkPriority, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetInstanceDefault(bool)", AS_METHODPR(NetworkPriority, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(NetworkPriority, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void NetworkPriority::SetMinPriority(float priority) | File: ../Network/NetworkPriority.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetMinPriority(float)", AS_METHODPR(NetworkPriority, SetMinPriority, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "void set_minPriority(float)", AS_METHODPR(NetworkPriority, SetMinPriority, (float), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(NetworkPriority, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(NetworkPriority, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(NetworkPriority, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetTemporary(bool)", AS_METHODPR(NetworkPriority, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "void set_temporary(bool)", AS_METHODPR(NetworkPriority, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "void UnsubscribeFromAllEvents()", AS_METHODPR(NetworkPriority, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(NetworkPriority_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(NetworkPriority, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(NetworkPriority, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(NetworkPriority, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("NetworkPriority", "int WeakRefs() const", AS_METHODPR(NetworkPriority, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "int get_weakRefs() const", AS_METHODPR(NetworkPriority, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(NetworkPriority, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(NetworkPriority, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(NetworkPriority, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(NetworkPriority, "NetworkPriority")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(NetworkPriority, "NetworkPriority")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(NetworkPriority, "NetworkPriority")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(NetworkPriority, "NetworkPriority")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(NetworkPriority, "NetworkPriority")
#endif
#ifdef REGISTER_MANUAL_PART_NetworkPriority
    REGISTER_MANUAL_PART_NetworkPriority(NetworkPriority, "NetworkPriority")
#endif
    RegisterSubclass<Component, NetworkPriority>(engine, "Component", "NetworkPriority");
    RegisterSubclass<Animatable, NetworkPriority>(engine, "Animatable", "NetworkPriority");
    RegisterSubclass<Serializable, NetworkPriority>(engine, "Serializable", "NetworkPriority");
    RegisterSubclass<Object, NetworkPriority>(engine, "Object", "NetworkPriority");
    RegisterSubclass<RefCounted, NetworkPriority>(engine, "RefCounted", "NetworkPriority");
#endif

    // void Node::AddChild(Node* node, unsigned index=M_MAX_UNSIGNED) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void AddChild(Node@+, uint = M_MAX_UNSIGNED)", AS_METHODPR(Node, AddChild, (Node*, unsigned), void), AS_CALL_THISCALL);
    // void Node::AddComponent(Component* component, unsigned id, CreateMode mode) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void AddComponent(Component@+, uint, CreateMode)", AS_METHODPR(Node, AddComponent, (Component*, unsigned, CreateMode), void), AS_CALL_THISCALL);
    // void Node::AddListener(Component* component) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void AddListener(Component@+)", AS_METHODPR(Node, AddListener, (Component*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Node", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Node, AddRef, (), void), AS_CALL_THISCALL);
    // virtual void Node::AddReplicationState(NodeReplicationState* state) | File: ../Scene/Node.h
    // Error: type "NodeReplicationState*" can not automatically bind
    // void Node::AddTag(const String& tag) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void AddTag(const String&in)", AS_METHODPR(Node, AddTag, (const String&), void), AS_CALL_THISCALL);
    // void Node::AddTags(const String& tags, char separator=';') | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void AddTags(const String&in, int8 = ';')", AS_METHODPR(Node, AddTags, (const String&, char), void), AS_CALL_THISCALL);
    // void Node::AddTags(const StringVector& tags) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void AddTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(Node_AddTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "void AllocateNetworkState()", AS_METHODPR(Node, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void Node::ApplyAttributes() override | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void ApplyAttributes()", AS_METHODPR(Node, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Node::CleanupConnection(Connection* connection) | File: ../Scene/Node.h
    // Not registered because have @manualbind mark
    // Node* Node::Clone(CreateMode mode=REPLICATED) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Node@+ Clone(CreateMode = REPLICATED)", AS_METHODPR(Node, Clone, (CreateMode), Node*), AS_CALL_THISCALL);
    // Component* Node::CloneComponent(Component* component, unsigned id=0) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Component@+ CloneComponent(Component@+, uint = 0)", AS_METHODPR(Node, CloneComponent, (Component*, unsigned), Component*), AS_CALL_THISCALL);
    // Component* Node::CloneComponent(Component* component, CreateMode mode, unsigned id=0) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Component@+ CloneComponent(Component@+, CreateMode, uint = 0)", AS_METHODPR(Node, CloneComponent, (Component*, CreateMode, unsigned), Component*), AS_CALL_THISCALL);
    // Node* Node::CreateChild(const String& name=String::EMPTY, CreateMode mode=REPLICATED, unsigned id=0, bool temporary=false) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Node@+ CreateChild(const String&in = String::EMPTY, CreateMode = REPLICATED, uint = 0, bool = false)", AS_METHODPR(Node, CreateChild, (const String&, CreateMode, unsigned, bool), Node*), AS_CALL_THISCALL);
    // Node* Node::CreateChild(unsigned id, CreateMode mode, bool temporary=false) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Node@+ CreateChild(uint, CreateMode, bool = false)", AS_METHODPR(Node, CreateChild, (unsigned, CreateMode, bool), Node*), AS_CALL_THISCALL);
    // Component* Node::CreateComponent(StringHash type, CreateMode mode=REPLICATED, unsigned id=0) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Component@+ CreateComponent(StringHash, CreateMode = REPLICATED, uint = 0)", AS_METHODPR(Node, CreateComponent, (StringHash, CreateMode, unsigned), Component*), AS_CALL_THISCALL);
    // template<class T> T* Node::CreateComponent(CreateMode mode=REPLICATED, unsigned id=0) | File: ../Scene/Node.h
    // Not registered because template
    // Node* Node::CreateTemporaryChild(const String& name=String::EMPTY, CreateMode mode=REPLICATED, unsigned id=0) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Node@+ CreateTemporaryChild(const String&in = String::EMPTY, CreateMode = REPLICATED, uint = 0)", AS_METHODPR(Node, CreateTemporaryChild, (const String&, CreateMode, unsigned), Node*), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "bool GetAnimationEnabled() const", AS_METHODPR(Node, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "bool get_animationEnabled() const", AS_METHODPR(Node, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "Variant GetAttribute(uint) const", AS_METHODPR(Node, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Variant get_attributes(uint) const", AS_METHODPR(Node, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "Variant GetAttribute(const String&in) const", AS_METHODPR(Node, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(Node, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(Node, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(Node, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(Node, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Node, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Node, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Node, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "bool GetBlockEvents() const", AS_METHODPR(Node, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "const String& GetCategory() const", AS_METHODPR(Node, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "const String& get_category() const", AS_METHODPR(Node, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Node* Node::GetChild(unsigned index) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Node@+ GetChild(uint) const", AS_METHODPR(Node, GetChild, (unsigned) const, Node*), AS_CALL_THISCALL);
    // Node* Node::GetChild(const String& name, bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Node@+ GetChild(const String&in, bool = false) const", AS_METHODPR(Node, GetChild, (const String&, bool) const, Node*), AS_CALL_THISCALL);
    // Node* Node::GetChild(const char* name, bool recursive=false) const | File: ../Scene/Node.h
    // Error: type "const char*" can not automatically bind
    // Node* Node::GetChild(StringHash nameHash, bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Node@+ GetChild(StringHash, bool = false) const", AS_METHODPR(Node, GetChild, (StringHash, bool) const, Node*), AS_CALL_THISCALL);
    // const Vector<SharedPtr<Node>>& Node::GetChildren() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Array<Node@>@ GetChildren() const", AS_FUNCTION_OBJFIRST(Node_GetChildren_void), AS_CALL_CDECL_OBJFIRST);
    // void Node::GetChildren(PODVector<Node*>& dest, bool recursive=false) const | File: ../Scene/Node.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // PODVector<Node*> Node::GetChildren(bool recursive) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Array<Node@>@ GetChildren(bool) const", AS_FUNCTION_OBJFIRST(Node_GetChildren_bool), AS_CALL_CDECL_OBJFIRST);
    // void Node::GetChildrenWithComponent(PODVector<Node*>& dest, StringHash type, bool recursive=false) const | File: ../Scene/Node.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // PODVector<Node*> Node::GetChildrenWithComponent(StringHash type, bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Array<Node@>@ GetChildrenWithComponent(StringHash, bool = false) const", AS_FUNCTION_OBJFIRST(Node_GetChildrenWithComponent_StringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // template<class T> void Node::GetChildrenWithComponent(PODVector<Node*>& dest, bool recursive=false) const | File: ../Scene/Node.h
    // Not registered because template
    // void Node::GetChildrenWithTag(PODVector<Node*>& dest, const String& tag, bool recursive=false) const | File: ../Scene/Node.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // PODVector<Node*> Node::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Array<Node@>@ GetChildrenWithTag(const String&in, bool = false) const", AS_FUNCTION_OBJFIRST(Node_GetChildrenWithTag_String_bool), AS_CALL_CDECL_OBJFIRST);
    // Component* Node::GetComponent(StringHash type, bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Component@+ GetComponent(StringHash, bool = false) const", AS_METHODPR(Node, GetComponent, (StringHash, bool) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Node::GetComponent(bool recursive=false) const | File: ../Scene/Node.h
    // Not registered because template
    // const Vector<SharedPtr<Component>>& Node::GetComponents() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Array<Component@>@ GetComponents() const", AS_FUNCTION_OBJFIRST(Node_GetComponents_void), AS_CALL_CDECL_OBJFIRST);
    // void Node::GetComponents(PODVector<Component*>& dest, StringHash type, bool recursive=false) const | File: ../Scene/Node.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Node::GetComponents(PODVector<T*>& dest, bool recursive=false) const | File: ../Scene/Node.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // const PODVector<Node*>& Node::GetDependencyNodes() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Array<Node@>@ GetDependencyNodes() const", AS_FUNCTION_OBJFIRST(Node_GetDependencyNodes_void), AS_CALL_CDECL_OBJFIRST);
    // template<class T> T* Node::GetDerivedComponent(bool recursive=false) const | File: ../Scene/Node.h
    // Not registered because template
    // template<class T> void Node::GetDerivedComponents(PODVector<T*>& dest, bool recursive=false, bool clearVector=true) const | File: ../Scene/Node.h
    // Not registered because template
    // Vector3 Node::GetDirection() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 GetDirection() const", AS_METHODPR(Node, GetDirection, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector3 get_direction() const", AS_METHODPR(Node, GetDirection, () const, Vector3), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "VariantMap& GetEventDataMap() const", AS_METHODPR(Node, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "Object@+ GetEventSender() const", AS_METHODPR(Node, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Node, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Node, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Node, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "const VariantMap& get_globalVars() const", AS_METHODPR(Node, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Node::GetID() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "uint GetID() const", AS_METHODPR(Node, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "uint get_id() const", AS_METHODPR(Node, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Node, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // const Vector<WeakPtr<Component>> Node::GetListeners() const | File: ../Scene/Node.h
    // Error: type "const Vector<WeakPtr<Component>>" can not automatically bind
    // const String& Node::GetName() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "const String& GetName() const", AS_METHODPR(Node, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "const String& get_name() const", AS_METHODPR(Node, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Node::GetNameHash() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "StringHash GetNameHash() const", AS_METHODPR(Node, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // const PODVector<unsigned char>& Node::GetNetParentAttr() const | File: ../Scene/Node.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // const Vector3& Node::GetNetPositionAttr() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "const Vector3& GetNetPositionAttr() const", AS_METHODPR(Node, GetNetPositionAttr, () const, const Vector3&), AS_CALL_THISCALL);
    // const PODVector<unsigned char>& Node::GetNetRotationAttr() const | File: ../Scene/Node.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "uint GetNumAttributes() const", AS_METHODPR(Node, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "uint get_numAttributes() const", AS_METHODPR(Node, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Node::GetNumChildren(bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "uint GetNumChildren(bool = false) const", AS_METHODPR(Node, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned Node::GetNumComponents() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "uint GetNumComponents() const", AS_METHODPR(Node, GetNumComponents, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "uint get_numComponents() const", AS_METHODPR(Node, GetNumComponents, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "uint GetNumNetworkAttributes() const", AS_METHODPR(Node, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Node::GetNumNetworkComponents() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "uint GetNumNetworkComponents() const", AS_METHODPR(Node, GetNumNetworkComponents, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Node::GetNumPersistentChildren() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "uint GetNumPersistentChildren() const", AS_METHODPR(Node, GetNumPersistentChildren, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Node::GetNumPersistentComponents() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "uint GetNumPersistentComponents() const", AS_METHODPR(Node, GetNumPersistentComponents, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(Node, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(Node, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(Node, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Component* Node::GetOrCreateComponent(StringHash type, CreateMode mode=REPLICATED, unsigned id=0) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Component@+ GetOrCreateComponent(StringHash, CreateMode = REPLICATED, uint = 0)", AS_METHODPR(Node, GetOrCreateComponent, (StringHash, CreateMode, unsigned), Component*), AS_CALL_THISCALL);
    // template<class T> T* Node::GetOrCreateComponent(CreateMode mode=REPLICATED, unsigned id=0) | File: ../Scene/Node.h
    // Not registered because template
    // Connection* Node::GetOwner() const | File: ../Scene/Node.h
    // Not registered because have @manualbind mark
    // Node* Node::GetParent() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Node@+ GetParent() const", AS_METHODPR(Node, GetParent, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Node@+ get_parent() const", AS_METHODPR(Node, GetParent, () const, Node*), AS_CALL_THISCALL);
    // Component* Node::GetParentComponent(StringHash type, bool fullTraversal=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Component@+ GetParentComponent(StringHash, bool = false) const", AS_METHODPR(Node, GetParentComponent, (StringHash, bool) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Node::GetParentComponent(bool fullTraversal=false) const | File: ../Scene/Node.h
    // Not registered because template
    // template<class T> T* Node::GetParentDerivedComponent(bool fullTraversal=false) const | File: ../Scene/Node.h
    // Not registered because template
    // const Vector3& Node::GetPosition() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "const Vector3& GetPosition() const", AS_METHODPR(Node, GetPosition, () const, const Vector3&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "const Vector3& get_position() const", AS_METHODPR(Node, GetPosition, () const, const Vector3&), AS_CALL_THISCALL);
    // Vector2 Node::GetPosition2D() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector2 GetPosition2D() const", AS_METHODPR(Node, GetPosition2D, () const, Vector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector2 get_position2D() const", AS_METHODPR(Node, GetPosition2D, () const, Vector2), AS_CALL_THISCALL);
    // Vector3 Node::GetRight() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 GetRight() const", AS_METHODPR(Node, GetRight, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector3 get_right() const", AS_METHODPR(Node, GetRight, () const, Vector3), AS_CALL_THISCALL);
    // const Quaternion& Node::GetRotation() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "const Quaternion& GetRotation() const", AS_METHODPR(Node, GetRotation, () const, const Quaternion&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "const Quaternion& get_rotation() const", AS_METHODPR(Node, GetRotation, () const, const Quaternion&), AS_CALL_THISCALL);
    // float Node::GetRotation2D() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "float GetRotation2D() const", AS_METHODPR(Node, GetRotation2D, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "float get_rotation2D() const", AS_METHODPR(Node, GetRotation2D, () const, float), AS_CALL_THISCALL);
    // const Vector3& Node::GetScale() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "const Vector3& GetScale() const", AS_METHODPR(Node, GetScale, () const, const Vector3&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "const Vector3& get_scale() const", AS_METHODPR(Node, GetScale, () const, const Vector3&), AS_CALL_THISCALL);
    // Vector2 Node::GetScale2D() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector2 GetScale2D() const", AS_METHODPR(Node, GetScale2D, () const, Vector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector2 get_scale2D() const", AS_METHODPR(Node, GetScale2D, () const, Vector2), AS_CALL_THISCALL);
    // Scene* Node::GetScene() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Scene@+ GetScene() const", AS_METHODPR(Node, GetScene, () const, Scene*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Scene@+ get_scene() const", AS_METHODPR(Node, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Vector3 Node::GetSignedWorldScale() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 GetSignedWorldScale() const", AS_METHODPR(Node, GetSignedWorldScale, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector3 get_signedWorldScale() const", AS_METHODPR(Node, GetSignedWorldScale, () const, Vector3), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Node, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& Node::GetTags() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Array<String>@ GetTags() const", AS_FUNCTION_OBJFIRST(Node_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Node", "Array<String>@ get_tags() const", AS_FUNCTION_OBJFIRST(Node_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    // Matrix3x4 Node::GetTransform() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Matrix3x4 GetTransform() const", AS_METHODPR(Node, GetTransform, () const, Matrix3x4), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Matrix3x4 get_transform() const", AS_METHODPR(Node, GetTransform, () const, Matrix3x4), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "StringHash GetType() const", AS_METHODPR(Node, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "StringHash get_type() const", AS_METHODPR(Node, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "const String& GetTypeName() const", AS_METHODPR(Node, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "const String& get_typeName() const", AS_METHODPR(Node, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // Vector3 Node::GetUp() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 GetUp() const", AS_METHODPR(Node, GetUp, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector3 get_up() const", AS_METHODPR(Node, GetUp, () const, Vector3), AS_CALL_THISCALL);
    // const Variant& Node::GetVar(StringHash key) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "const Variant& GetVar(StringHash) const", AS_METHODPR(Node, GetVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Node::GetVars() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "const VariantMap& GetVars() const", AS_METHODPR(Node, GetVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // Vector3 Node::GetWorldDirection() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 GetWorldDirection() const", AS_METHODPR(Node, GetWorldDirection, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector3 get_worldDirection() const", AS_METHODPR(Node, GetWorldDirection, () const, Vector3), AS_CALL_THISCALL);
    // Vector3 Node::GetWorldPosition() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 GetWorldPosition() const", AS_METHODPR(Node, GetWorldPosition, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector3 get_worldPosition() const", AS_METHODPR(Node, GetWorldPosition, () const, Vector3), AS_CALL_THISCALL);
    // Vector2 Node::GetWorldPosition2D() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector2 GetWorldPosition2D() const", AS_METHODPR(Node, GetWorldPosition2D, () const, Vector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector2 get_worldPosition2D() const", AS_METHODPR(Node, GetWorldPosition2D, () const, Vector2), AS_CALL_THISCALL);
    // Vector3 Node::GetWorldRight() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 GetWorldRight() const", AS_METHODPR(Node, GetWorldRight, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector3 get_worldRight() const", AS_METHODPR(Node, GetWorldRight, () const, Vector3), AS_CALL_THISCALL);
    // Quaternion Node::GetWorldRotation() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Quaternion GetWorldRotation() const", AS_METHODPR(Node, GetWorldRotation, () const, Quaternion), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Quaternion get_worldRotation() const", AS_METHODPR(Node, GetWorldRotation, () const, Quaternion), AS_CALL_THISCALL);
    // float Node::GetWorldRotation2D() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "float GetWorldRotation2D() const", AS_METHODPR(Node, GetWorldRotation2D, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "float get_worldRotation2D() const", AS_METHODPR(Node, GetWorldRotation2D, () const, float), AS_CALL_THISCALL);
    // Vector3 Node::GetWorldScale() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 GetWorldScale() const", AS_METHODPR(Node, GetWorldScale, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector3 get_worldScale() const", AS_METHODPR(Node, GetWorldScale, () const, Vector3), AS_CALL_THISCALL);
    // Vector2 Node::GetWorldScale2D() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector2 GetWorldScale2D() const", AS_METHODPR(Node, GetWorldScale2D, () const, Vector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector2 get_worldScale2D() const", AS_METHODPR(Node, GetWorldScale2D, () const, Vector2), AS_CALL_THISCALL);
    // const Matrix3x4& Node::GetWorldTransform() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "const Matrix3x4& GetWorldTransform() const", AS_METHODPR(Node, GetWorldTransform, () const, const Matrix3x4&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "const Matrix3x4& get_worldTransform() const", AS_METHODPR(Node, GetWorldTransform, () const, const Matrix3x4&), AS_CALL_THISCALL);
    // Vector3 Node::GetWorldUp() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 GetWorldUp() const", AS_METHODPR(Node, GetWorldUp, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector3 get_worldUp() const", AS_METHODPR(Node, GetWorldUp, () const, Vector3), AS_CALL_THISCALL);
    // bool Node::HasComponent(StringHash type) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool HasComponent(StringHash) const", AS_METHODPR(Node, HasComponent, (StringHash) const, bool), AS_CALL_THISCALL);
    // template<class T> bool Node::HasComponent() const | File: ../Scene/Node.h
    // Not registered because template
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "bool HasEventHandlers() const", AS_METHODPR(Node, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Node, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Node, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Node::HasTag(const String& tag) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool HasTag(const String&in) const", AS_METHODPR(Node, HasTag, (const String&) const, bool), AS_CALL_THISCALL);
    // bool Node::IsChildOf(Node* node) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool IsChildOf(Node@+) const", AS_METHODPR(Node, IsChildOf, (Node*) const, bool), AS_CALL_THISCALL);
    // bool Node::IsDirty() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool IsDirty() const", AS_METHODPR(Node, IsDirty, () const, bool), AS_CALL_THISCALL);
    // bool Node::IsEnabled() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool IsEnabled() const", AS_METHODPR(Node, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "bool get_enabled() const", AS_METHODPR(Node, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Node::IsEnabledSelf() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool IsEnabledSelf() const", AS_METHODPR(Node, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "bool get_enabledSelf() const", AS_METHODPR(Node, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Node, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Node::IsReplicated() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool IsReplicated() const", AS_METHODPR(Node, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "bool get_replicated() const", AS_METHODPR(Node, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "bool IsTemporary() const", AS_METHODPR(Node, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "bool get_temporary() const", AS_METHODPR(Node, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool Node::Load(Deserializer& source) override | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool Load(Deserializer&)", AS_METHODPR(Node, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Node::Load(Deserializer& source, SceneResolver& resolver, bool loadChildren=true, bool rewriteIDs=false, CreateMode mode=REPLICATED) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool Load(Deserializer&, SceneResolver&, bool = true, bool = false, CreateMode = REPLICATED)", AS_METHODPR(Node, Load, (Deserializer&, SceneResolver&, bool, bool, CreateMode), bool), AS_CALL_THISCALL);
    // bool Node::LoadJSON(const JSONValue& source) override | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Node, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Node::LoadJSON(const JSONValue& source, SceneResolver& resolver, bool loadChildren=true, bool rewriteIDs=false, CreateMode mode=REPLICATED) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool LoadJSON(const JSONValue&in, SceneResolver&, bool = true, bool = false, CreateMode = REPLICATED)", AS_METHODPR(Node, LoadJSON, (const JSONValue&, SceneResolver&, bool, bool, CreateMode), bool), AS_CALL_THISCALL);
    // bool Node::LoadXML(const XMLElement& source) override | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Node, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // bool Node::LoadXML(const XMLElement& source, SceneResolver& resolver, bool loadChildren=true, bool rewriteIDs=false, CreateMode mode=REPLICATED) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool LoadXML(const XMLElement&in, SceneResolver&, bool = true, bool = false, CreateMode = REPLICATED)", AS_METHODPR(Node, LoadXML, (const XMLElement&, SceneResolver&, bool, bool, CreateMode), bool), AS_CALL_THISCALL);
    // Vector3 Node::LocalToWorld(const Vector3& position) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 LocalToWorld(const Vector3&in) const", AS_METHODPR(Node, LocalToWorld, (const Vector3&) const, Vector3), AS_CALL_THISCALL);
    // Vector3 Node::LocalToWorld(const Vector4& vector) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 LocalToWorld(const Vector4&in) const", AS_METHODPR(Node, LocalToWorld, (const Vector4&) const, Vector3), AS_CALL_THISCALL);
    // Vector2 Node::LocalToWorld2D(const Vector2& vector) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector2 LocalToWorld2D(const Vector2&in) const", AS_METHODPR(Node, LocalToWorld2D, (const Vector2&) const, Vector2), AS_CALL_THISCALL);
    // bool Node::LookAt(const Vector3& target, const Vector3& up=Vector3::UP, TransformSpace space=TS_WORLD) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool LookAt(const Vector3&in, const Vector3&in = Vector3::UP, TransformSpace = TS_WORLD)", AS_METHODPR(Node, LookAt, (const Vector3&, const Vector3&, TransformSpace), bool), AS_CALL_THISCALL);
    // void Node::MarkDirty() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void MarkDirty()", AS_METHODPR(Node, MarkDirty, (), void), AS_CALL_THISCALL);
    // void Node::MarkNetworkUpdate() override | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void MarkNetworkUpdate()", AS_METHODPR(Node, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void Node::MarkReplicationDirty() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void MarkReplicationDirty()", AS_METHODPR(Node, MarkReplicationDirty, (), void), AS_CALL_THISCALL);
    // explicit Node::Node(Context* context) | File: ../Scene/Node.h
    engine->RegisterObjectBehaviour("Node", asBEHAVE_FACTORY, "Node@+ f()", AS_FUNCTION(Node_Node_Context), AS_CALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Node, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Node, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Node, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Node::Pitch(float angle, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void Pitch(float, TransformSpace = TS_LOCAL)", AS_METHODPR(Node, Pitch, (float, TransformSpace), void), AS_CALL_THISCALL);
    // void Node::PrepareNetworkUpdate() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void PrepareNetworkUpdate()", AS_METHODPR(Node, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Node, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Node, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Node", "int Refs() const", AS_METHODPR(Node, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "int get_refs() const", AS_METHODPR(Node, Refs, () const, int), AS_CALL_THISCALL);
    // static void Node::RegisterObject(Context* context) | File: ../Scene/Node.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Node", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Node, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Node::Remove() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void Remove()", AS_METHODPR(Node, Remove, (), void), AS_CALL_THISCALL);
    // void Node::RemoveAllChildren() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void RemoveAllChildren()", AS_METHODPR(Node, RemoveAllChildren, (), void), AS_CALL_THISCALL);
    // void Node::RemoveAllComponents() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void RemoveAllComponents()", AS_METHODPR(Node, RemoveAllComponents, (), void), AS_CALL_THISCALL);
    // void Node::RemoveAllTags() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void RemoveAllTags()", AS_METHODPR(Node, RemoveAllTags, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(Node, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Node::RemoveChild(Node* node) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void RemoveChild(Node@+)", AS_METHODPR(Node, RemoveChild, (Node*), void), AS_CALL_THISCALL);
    // void Node::RemoveChildren(bool removeReplicated, bool removeLocal, bool recursive) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void RemoveChildren(bool, bool, bool)", AS_METHODPR(Node, RemoveChildren, (bool, bool, bool), void), AS_CALL_THISCALL);
    // void Node::RemoveComponent(Component* component) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void RemoveComponent(Component@+)", AS_METHODPR(Node, RemoveComponent, (Component*), void), AS_CALL_THISCALL);
    // void Node::RemoveComponent(StringHash type) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void RemoveComponent(StringHash)", AS_METHODPR(Node, RemoveComponent, (StringHash), void), AS_CALL_THISCALL);
    // template<class T> void Node::RemoveComponent() | File: ../Scene/Node.h
    // Not registered because template
    // void Node::RemoveComponents(bool removeReplicated, bool removeLocal) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void RemoveComponents(bool, bool)", AS_METHODPR(Node, RemoveComponents, (bool, bool), void), AS_CALL_THISCALL);
    // void Node::RemoveComponents(StringHash type) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void RemoveComponents(StringHash)", AS_METHODPR(Node, RemoveComponents, (StringHash), void), AS_CALL_THISCALL);
    // template<class T> void Node::RemoveComponents() | File: ../Scene/Node.h
    // Not registered because template
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "void RemoveInstanceDefault()", AS_METHODPR(Node, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Node::RemoveListener(Component* component) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void RemoveListener(Component@+)", AS_METHODPR(Node, RemoveListener, (Component*), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "void RemoveObjectAnimation()", AS_METHODPR(Node, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // bool Node::RemoveTag(const String& tag) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool RemoveTag(const String&in)", AS_METHODPR(Node, RemoveTag, (const String&), bool), AS_CALL_THISCALL);
    // void Node::ReorderComponent(Component* component, unsigned index) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void ReorderComponent(Component@+, uint)", AS_METHODPR(Node, ReorderComponent, (Component*, unsigned), void), AS_CALL_THISCALL);
    // void Node::ResetDeepEnabled() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void ResetDeepEnabled()", AS_METHODPR(Node, ResetDeepEnabled, (), void), AS_CALL_THISCALL);
    // void Node::ResetScene() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void ResetScene()", AS_METHODPR(Node, ResetScene, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "void ResetToDefault()", AS_METHODPR(Node, ResetToDefault, (), void), AS_CALL_THISCALL);
    // void Node::Roll(float angle, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void Roll(float, TransformSpace = TS_LOCAL)", AS_METHODPR(Node, Roll, (float, TransformSpace), void), AS_CALL_THISCALL);
    // void Node::Rotate(const Quaternion& delta, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void Rotate(const Quaternion&in, TransformSpace = TS_LOCAL)", AS_METHODPR(Node, Rotate, (const Quaternion&, TransformSpace), void), AS_CALL_THISCALL);
    // void Node::Rotate2D(float delta, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void Rotate2D(float, TransformSpace = TS_LOCAL)", AS_METHODPR(Node, Rotate2D, (float, TransformSpace), void), AS_CALL_THISCALL);
    // void Node::RotateAround(const Vector3& point, const Quaternion& delta, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void RotateAround(const Vector3&in, const Quaternion&in, TransformSpace = TS_LOCAL)", AS_METHODPR(Node, RotateAround, (const Vector3&, const Quaternion&, TransformSpace), void), AS_CALL_THISCALL);
    // void Node::RotateAround2D(const Vector2& point, float delta, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void RotateAround2D(const Vector2&in, float, TransformSpace = TS_LOCAL)", AS_METHODPR(Node, RotateAround2D, (const Vector2&, float, TransformSpace), void), AS_CALL_THISCALL);
    // bool Node::Save(Serializer& dest) const override | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool Save(Serializer&) const", AS_METHODPR(Node, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // bool Node::SaveDefaultAttributes() const override | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool SaveDefaultAttributes() const", AS_METHODPR(Node, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Node::SaveJSON(JSONValue& dest) const override | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool SaveJSON(JSONValue&) const", AS_METHODPR(Node, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Node::SaveJSON(Serializer& dest, const String& indentation="\t") const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool SaveJSON(Serializer&, const String&in = \"\t\") const", AS_METHODPR(Node, SaveJSON, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);
    // bool Node::SaveXML(XMLElement& dest) const override | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool SaveXML(XMLElement&) const", AS_METHODPR(Node, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // bool Node::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool SaveXML(Serializer&, const String&in = \"\t\") const", AS_METHODPR(Node, SaveXML, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);
    // void Node::Scale(float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void Scale(float)", AS_METHODPR(Node, Scale, (float), void), AS_CALL_THISCALL);
    // void Node::Scale(const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void Scale(const Vector3&in)", AS_METHODPR(Node, Scale, (const Vector3&), void), AS_CALL_THISCALL);
    // void Node::Scale2D(const Vector2& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void Scale2D(const Vector2&in)", AS_METHODPR(Node, Scale2D, (const Vector2&), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "void SendEvent(StringHash)", AS_METHODPR(Node, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Node, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "void SetAnimationEnabled(bool)", AS_METHODPR(Node, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_animationEnabled(bool)", AS_METHODPR(Node, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "void SetAnimationTime(float)", AS_METHODPR(Node, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Node, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Node, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Node, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Node, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(Node, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(Node, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Node, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "void SetBlockEvents(bool)", AS_METHODPR(Node, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Node::SetDeepEnabled(bool enable) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetDeepEnabled(bool)", AS_METHODPR(Node, SetDeepEnabled, (bool), void), AS_CALL_THISCALL);
    // void Node::SetDirection(const Vector3& direction) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetDirection(const Vector3&in)", AS_METHODPR(Node, SetDirection, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_direction(const Vector3&in)", AS_METHODPR(Node, SetDirection, (const Vector3&), void), AS_CALL_THISCALL);
    // void Node::SetEnabled(bool enable) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetEnabled(bool)", AS_METHODPR(Node, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_enabled(bool)", AS_METHODPR(Node, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Node::SetEnabledRecursive(bool enable) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetEnabledRecursive(bool)", AS_METHODPR(Node, SetEnabledRecursive, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Node, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Node, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Node::SetID(unsigned id) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetID(uint)", AS_METHODPR(Node, SetID, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_id(uint)", AS_METHODPR(Node, SetID, (unsigned), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "void SetInstanceDefault(bool)", AS_METHODPR(Node, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Node, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Node::SetName(const String& name) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetName(const String&in)", AS_METHODPR(Node, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_name(const String&in)", AS_METHODPR(Node, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Node::SetNetParentAttr(const PODVector<unsigned char>& value) | File: ../Scene/Node.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void Node::SetNetPositionAttr(const Vector3& value) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetNetPositionAttr(const Vector3&in)", AS_METHODPR(Node, SetNetPositionAttr, (const Vector3&), void), AS_CALL_THISCALL);
    // void Node::SetNetRotationAttr(const PODVector<unsigned char>& value) | File: ../Scene/Node.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(Node, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(Node, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(Node, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Node::SetOwner(Connection* owner) | File: ../Scene/Node.h
    // Not registered because have @manualbind mark
    // void Node::SetParent(Node* parent) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetParent(Node@+)", AS_METHODPR(Node, SetParent, (Node*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_parent(Node@+)", AS_METHODPR(Node, SetParent, (Node*), void), AS_CALL_THISCALL);
    // void Node::SetPosition(const Vector3& position) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetPosition(const Vector3&in)", AS_METHODPR(Node, SetPosition, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_position(const Vector3&in)", AS_METHODPR(Node, SetPosition, (const Vector3&), void), AS_CALL_THISCALL);
    // void Node::SetPosition2D(const Vector2& position) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetPosition2D(const Vector2&in)", AS_METHODPR(Node, SetPosition2D, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_position2D(const Vector2&in)", AS_METHODPR(Node, SetPosition2D, (const Vector2&), void), AS_CALL_THISCALL);
    // void Node::SetPosition2D(float x, float y) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetPosition2D(float, float)", AS_METHODPR(Node, SetPosition2D, (float, float), void), AS_CALL_THISCALL);
    // void Node::SetPositionSilent(const Vector3& position) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetPositionSilent(const Vector3&in)", AS_METHODPR(Node, SetPositionSilent, (const Vector3&), void), AS_CALL_THISCALL);
    // void Node::SetRotation(const Quaternion& rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetRotation(const Quaternion&in)", AS_METHODPR(Node, SetRotation, (const Quaternion&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_rotation(const Quaternion&in)", AS_METHODPR(Node, SetRotation, (const Quaternion&), void), AS_CALL_THISCALL);
    // void Node::SetRotation2D(float rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetRotation2D(float)", AS_METHODPR(Node, SetRotation2D, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_rotation2D(float)", AS_METHODPR(Node, SetRotation2D, (float), void), AS_CALL_THISCALL);
    // void Node::SetRotationSilent(const Quaternion& rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetRotationSilent(const Quaternion&in)", AS_METHODPR(Node, SetRotationSilent, (const Quaternion&), void), AS_CALL_THISCALL);
    // void Node::SetScale(float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetScale(float)", AS_METHODPR(Node, SetScale, (float), void), AS_CALL_THISCALL);
    // void Node::SetScale(const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetScale(const Vector3&in)", AS_METHODPR(Node, SetScale, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_scale(const Vector3&in)", AS_METHODPR(Node, SetScale, (const Vector3&), void), AS_CALL_THISCALL);
    // void Node::SetScale2D(const Vector2& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetScale2D(const Vector2&in)", AS_METHODPR(Node, SetScale2D, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_scale2D(const Vector2&in)", AS_METHODPR(Node, SetScale2D, (const Vector2&), void), AS_CALL_THISCALL);
    // void Node::SetScale2D(float x, float y) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetScale2D(float, float)", AS_METHODPR(Node, SetScale2D, (float, float), void), AS_CALL_THISCALL);
    // void Node::SetScaleSilent(const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetScaleSilent(const Vector3&in)", AS_METHODPR(Node, SetScaleSilent, (const Vector3&), void), AS_CALL_THISCALL);
    // void Node::SetScene(Scene* scene) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetScene(Scene@+)", AS_METHODPR(Node, SetScene, (Scene*), void), AS_CALL_THISCALL);
    // void Node::SetTags(const StringVector& tags) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(Node_SetTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "void SetTemporary(bool)", AS_METHODPR(Node, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_temporary(bool)", AS_METHODPR(Node, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Node::SetTransform(const Vector3& position, const Quaternion& rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetTransform(const Vector3&in, const Quaternion&in)", AS_METHODPR(Node, SetTransform, (const Vector3&, const Quaternion&), void), AS_CALL_THISCALL);
    // void Node::SetTransform(const Vector3& position, const Quaternion& rotation, float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetTransform(const Vector3&in, const Quaternion&in, float)", AS_METHODPR(Node, SetTransform, (const Vector3&, const Quaternion&, float), void), AS_CALL_THISCALL);
    // void Node::SetTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetTransform(const Vector3&in, const Quaternion&in, const Vector3&in)", AS_METHODPR(Node, SetTransform, (const Vector3&, const Quaternion&, const Vector3&), void), AS_CALL_THISCALL);
    // void Node::SetTransform(const Matrix3x4& matrix) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetTransform(const Matrix3x4&in)", AS_METHODPR(Node, SetTransform, (const Matrix3x4&), void), AS_CALL_THISCALL);
    // void Node::SetTransform2D(const Vector2& position, float rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetTransform2D(const Vector2&in, float)", AS_METHODPR(Node, SetTransform2D, (const Vector2&, float), void), AS_CALL_THISCALL);
    // void Node::SetTransform2D(const Vector2& position, float rotation, float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetTransform2D(const Vector2&in, float, float)", AS_METHODPR(Node, SetTransform2D, (const Vector2&, float, float), void), AS_CALL_THISCALL);
    // void Node::SetTransform2D(const Vector2& position, float rotation, const Vector2& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetTransform2D(const Vector2&in, float, const Vector2&in)", AS_METHODPR(Node, SetTransform2D, (const Vector2&, float, const Vector2&), void), AS_CALL_THISCALL);
    // void Node::SetTransformSilent(const Vector3& position, const Quaternion& rotation, const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetTransformSilent(const Vector3&in, const Quaternion&in, const Vector3&in)", AS_METHODPR(Node, SetTransformSilent, (const Vector3&, const Quaternion&, const Vector3&), void), AS_CALL_THISCALL);
    // void Node::SetVar(StringHash key, const Variant& value) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetVar(StringHash, const Variant&in)", AS_METHODPR(Node, SetVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Node::SetWorldDirection(const Vector3& direction) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldDirection(const Vector3&in)", AS_METHODPR(Node, SetWorldDirection, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_worldDirection(const Vector3&in)", AS_METHODPR(Node, SetWorldDirection, (const Vector3&), void), AS_CALL_THISCALL);
    // void Node::SetWorldPosition(const Vector3& position) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldPosition(const Vector3&in)", AS_METHODPR(Node, SetWorldPosition, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_worldPosition(const Vector3&in)", AS_METHODPR(Node, SetWorldPosition, (const Vector3&), void), AS_CALL_THISCALL);
    // void Node::SetWorldPosition2D(const Vector2& position) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldPosition2D(const Vector2&in)", AS_METHODPR(Node, SetWorldPosition2D, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_worldPosition2D(const Vector2&in)", AS_METHODPR(Node, SetWorldPosition2D, (const Vector2&), void), AS_CALL_THISCALL);
    // void Node::SetWorldPosition2D(float x, float y) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldPosition2D(float, float)", AS_METHODPR(Node, SetWorldPosition2D, (float, float), void), AS_CALL_THISCALL);
    // void Node::SetWorldRotation(const Quaternion& rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldRotation(const Quaternion&in)", AS_METHODPR(Node, SetWorldRotation, (const Quaternion&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_worldRotation(const Quaternion&in)", AS_METHODPR(Node, SetWorldRotation, (const Quaternion&), void), AS_CALL_THISCALL);
    // void Node::SetWorldRotation2D(float rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldRotation2D(float)", AS_METHODPR(Node, SetWorldRotation2D, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_worldRotation2D(float)", AS_METHODPR(Node, SetWorldRotation2D, (float), void), AS_CALL_THISCALL);
    // void Node::SetWorldScale(float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldScale(float)", AS_METHODPR(Node, SetWorldScale, (float), void), AS_CALL_THISCALL);
    // void Node::SetWorldScale(const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldScale(const Vector3&in)", AS_METHODPR(Node, SetWorldScale, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_worldScale(const Vector3&in)", AS_METHODPR(Node, SetWorldScale, (const Vector3&), void), AS_CALL_THISCALL);
    // void Node::SetWorldScale2D(const Vector2& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldScale2D(const Vector2&in)", AS_METHODPR(Node, SetWorldScale2D, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_worldScale2D(const Vector2&in)", AS_METHODPR(Node, SetWorldScale2D, (const Vector2&), void), AS_CALL_THISCALL);
    // void Node::SetWorldScale2D(float x, float y) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldScale2D(float, float)", AS_METHODPR(Node, SetWorldScale2D, (float, float), void), AS_CALL_THISCALL);
    // void Node::SetWorldTransform(const Vector3& position, const Quaternion& rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldTransform(const Vector3&in, const Quaternion&in)", AS_METHODPR(Node, SetWorldTransform, (const Vector3&, const Quaternion&), void), AS_CALL_THISCALL);
    // void Node::SetWorldTransform(const Vector3& position, const Quaternion& rotation, float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldTransform(const Vector3&in, const Quaternion&in, float)", AS_METHODPR(Node, SetWorldTransform, (const Vector3&, const Quaternion&, float), void), AS_CALL_THISCALL);
    // void Node::SetWorldTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldTransform(const Vector3&in, const Quaternion&in, const Vector3&in)", AS_METHODPR(Node, SetWorldTransform, (const Vector3&, const Quaternion&, const Vector3&), void), AS_CALL_THISCALL);
    // void Node::SetWorldTransform(const Matrix3x4& worldTransform) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldTransform(const Matrix3x4&in)", AS_METHODPR(Node, SetWorldTransform, (const Matrix3x4&), void), AS_CALL_THISCALL);
    // void Node::SetWorldTransform2D(const Vector2& position, float rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldTransform2D(const Vector2&in, float)", AS_METHODPR(Node, SetWorldTransform2D, (const Vector2&, float), void), AS_CALL_THISCALL);
    // void Node::SetWorldTransform2D(const Vector2& position, float rotation, float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldTransform2D(const Vector2&in, float, float)", AS_METHODPR(Node, SetWorldTransform2D, (const Vector2&, float, float), void), AS_CALL_THISCALL);
    // void Node::SetWorldTransform2D(const Vector2& position, float rotation, const Vector2& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldTransform2D(const Vector2&in, float, const Vector2&in)", AS_METHODPR(Node, SetWorldTransform2D, (const Vector2&, float, const Vector2&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Node::Translate(const Vector3& delta, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void Translate(const Vector3&in, TransformSpace = TS_LOCAL)", AS_METHODPR(Node, Translate, (const Vector3&, TransformSpace), void), AS_CALL_THISCALL);
    // void Node::Translate2D(const Vector2& delta, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void Translate2D(const Vector2&in, TransformSpace = TS_LOCAL)", AS_METHODPR(Node, Translate2D, (const Vector2&, TransformSpace), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "void UnsubscribeFromAllEvents()", AS_METHODPR(Node, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Node_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Node, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Node, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Node, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Node", "int WeakRefs() const", AS_METHODPR(Node, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Node", "int get_weakRefs() const", AS_METHODPR(Node, WeakRefs, () const, int), AS_CALL_THISCALL);
    // Vector3 Node::WorldToLocal(const Vector3& position) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 WorldToLocal(const Vector3&in) const", AS_METHODPR(Node, WorldToLocal, (const Vector3&) const, Vector3), AS_CALL_THISCALL);
    // Vector3 Node::WorldToLocal(const Vector4& vector) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 WorldToLocal(const Vector4&in) const", AS_METHODPR(Node, WorldToLocal, (const Vector4&) const, Vector3), AS_CALL_THISCALL);
    // Vector2 Node::WorldToLocal2D(const Vector2& vector) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector2 WorldToLocal2D(const Vector2&in) const", AS_METHODPR(Node, WorldToLocal2D, (const Vector2&) const, Vector2), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Node, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Node, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Node, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Node::Yaw(float angle, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void Yaw(float, TransformSpace = TS_LOCAL)", AS_METHODPR(Node, Yaw, (float, TransformSpace), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(Node, "Node")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Node, "Node")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Node, "Node")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Node, "Node")
#endif
#ifdef REGISTER_MANUAL_PART_Node
    REGISTER_MANUAL_PART_Node(Node, "Node")
#endif
    RegisterSubclass<Animatable, Node>(engine, "Animatable", "Node");
    RegisterSubclass<Serializable, Node>(engine, "Serializable", "Node");
    RegisterSubclass<Object, Node>(engine, "Object", "Node");
    RegisterSubclass<RefCounted, Node>(engine, "RefCounted", "Node");

#ifdef URHO3D_NAVIGATION
    // unsigned char NavAreaStub::areaID_ | File: ../Navigation/NavBuildData.h
    engine->RegisterObjectProperty("NavAreaStub", "uint8 areaID", offsetof(NavAreaStub, areaID_));
    // BoundingBox NavAreaStub::bounds_ | File: ../Navigation/NavBuildData.h
    engine->RegisterObjectProperty("NavAreaStub", "BoundingBox bounds", offsetof(NavAreaStub, bounds_));
    // NavAreaStub& NavAreaStub::operator=(const NavAreaStub&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<NavAreaStub>(engine, "NavAreaStub");
#ifdef REGISTER_MANUAL_PART_NavAreaStub
    REGISTER_MANUAL_PART_NavAreaStub(NavAreaStub, "NavAreaStub")
#endif
#endif

#ifdef URHO3D_NAVIGATION
    // rcCompactHeightfield* NavBuildData::compactHeightField_ | File: ../Navigation/NavBuildData.h
    // rcCompactHeightfield* can not be registered
    // rcContext* NavBuildData::ctx_ | File: ../Navigation/NavBuildData.h
    // rcContext* can not be registered
    // rcHeightfield* NavBuildData::heightField_ | File: ../Navigation/NavBuildData.h
    // rcHeightfield* can not be registered
    // PODVector<int> NavBuildData::indices_ | File: ../Navigation/NavBuildData.h
    // Error: type "PODVector<int>" can not automatically bind
    // PODVector<NavAreaStub> NavBuildData::navAreas_ | File: ../Navigation/NavBuildData.h
    // Error: type "PODVector<NavAreaStub>" can not automatically bind
    // PODVector<unsigned char> NavBuildData::offMeshAreas_ | File: ../Navigation/NavBuildData.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // PODVector<unsigned char> NavBuildData::offMeshDir_ | File: ../Navigation/NavBuildData.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // PODVector<unsigned short> NavBuildData::offMeshFlags_ | File: ../Navigation/NavBuildData.h
    // Error: type "PODVector<unsigned short>" can not automatically bind
    // PODVector<float> NavBuildData::offMeshRadii_ | File: ../Navigation/NavBuildData.h
    // Error: type "PODVector<float>" can not automatically bind
    // PODVector<Vector3> NavBuildData::offMeshVertices_ | File: ../Navigation/NavBuildData.h
    // Error: type "PODVector<Vector3>" can not automatically bind
    // PODVector<Vector3> NavBuildData::vertices_ | File: ../Navigation/NavBuildData.h
    // Error: type "PODVector<Vector3>" can not automatically bind
    // BoundingBox NavBuildData::worldBoundingBox_ | File: ../Navigation/NavBuildData.h
    engine->RegisterObjectProperty("NavBuildData", "BoundingBox worldBoundingBox", offsetof(NavBuildData, worldBoundingBox_));
    // NavBuildData& NavBuildData::operator=(const NavBuildData&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<NavBuildData>(engine, "NavBuildData");
#ifdef REGISTER_MANUAL_PART_NavBuildData
    REGISTER_MANUAL_PART_NavBuildData(NavBuildData, "NavBuildData")
#endif
#endif

#ifdef URHO3D_NAVIGATION
    // BoundingBox NavigationGeometryInfo::boundingBox_ | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectProperty("NavigationGeometryInfo", "BoundingBox boundingBox", offsetof(NavigationGeometryInfo, boundingBox_));
    // Component* NavigationGeometryInfo::component_ | File: ../Navigation/NavigationMesh.h
    // Component* can not be registered
    // unsigned NavigationGeometryInfo::lodLevel_ | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectProperty("NavigationGeometryInfo", "uint lodLevel", offsetof(NavigationGeometryInfo, lodLevel_));
    // Matrix3x4 NavigationGeometryInfo::transform_ | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectProperty("NavigationGeometryInfo", "Matrix3x4 transform", offsetof(NavigationGeometryInfo, transform_));
    // NavigationGeometryInfo& NavigationGeometryInfo::operator=(const NavigationGeometryInfo&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<NavigationGeometryInfo>(engine, "NavigationGeometryInfo");
#ifdef REGISTER_MANUAL_PART_NavigationGeometryInfo
    REGISTER_MANUAL_PART_NavigationGeometryInfo(NavigationGeometryInfo, "NavigationGeometryInfo")
#endif
#endif

#ifdef URHO3D_NAVIGATION
    // unsigned char NavigationPathPoint::areaID_ | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectProperty("NavigationPathPoint", "uint8 areaID", offsetof(NavigationPathPoint, areaID_));
    // NavigationPathPointFlag NavigationPathPoint::flag_ | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectProperty("NavigationPathPoint", "NavigationPathPointFlag flag", offsetof(NavigationPathPoint, flag_));
    // Vector3 NavigationPathPoint::position_ | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectProperty("NavigationPathPoint", "Vector3 position", offsetof(NavigationPathPoint, position_));
    // NavigationPathPoint& NavigationPathPoint::operator=(const NavigationPathPoint&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<NavigationPathPoint>(engine, "NavigationPathPoint");
#ifdef REGISTER_MANUAL_PART_NavigationPathPoint
    REGISTER_MANUAL_PART_NavigationPathPoint(NavigationPathPoint, "NavigationPathPoint")
#endif
#endif

    // const Vector<AttributeInfo>* NetworkState::attributes_ | File: ../Scene/ReplicationState.h
    // const Vector<AttributeInfo>* can not be registered
    // Vector<Variant> NetworkState::currentValues_ | File: ../Scene/ReplicationState.h
    // Error: type "Vector<Variant>" can not automatically bind
    // unsigned long long NetworkState::interceptMask_ | File: ../Scene/ReplicationState.h
    engine->RegisterObjectProperty("NetworkState", "uint64 interceptMask", offsetof(NetworkState, interceptMask_));
    // Vector<Variant> NetworkState::previousValues_ | File: ../Scene/ReplicationState.h
    // Error: type "Vector<Variant>" can not automatically bind
    // VariantMap NetworkState::previousVars_ | File: ../Scene/ReplicationState.h
    engine->RegisterObjectProperty("NetworkState", "VariantMap previousVars", offsetof(NetworkState, previousVars_));
    // PODVector<ReplicationState*> NetworkState::replicationStates_ | File: ../Scene/ReplicationState.h
    // Error: type "PODVector<ReplicationState*>" can not automatically bind
    // NetworkState& NetworkState::operator=(const NetworkState&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<NetworkState>(engine, "NetworkState");
#ifdef REGISTER_MANUAL_PART_NetworkState
    REGISTER_MANUAL_PART_NetworkState(NetworkState, "NetworkState")
#endif

    // VectorBuffer NodeImpl::attrBuffer_ | File: ../Scene/Node.h
    engine->RegisterObjectProperty("NodeImpl", "VectorBuffer attrBuffer", offsetof(NodeImpl, attrBuffer_));
    // PODVector<Node*> NodeImpl::dependencyNodes_ | File: ../Scene/Node.h
    // Error: type "PODVector<Node*>" can not automatically bind
    // String NodeImpl::name_ | File: ../Scene/Node.h
    engine->RegisterObjectProperty("NodeImpl", "String name", offsetof(NodeImpl, name_));
    // StringHash NodeImpl::nameHash_ | File: ../Scene/Node.h
    engine->RegisterObjectProperty("NodeImpl", "StringHash nameHash", offsetof(NodeImpl, nameHash_));
    // Connection* NodeImpl::owner_ | File: ../Scene/Node.h
    // Connection* can not be registered
    // StringVector NodeImpl::tags_ | File: ../Scene/Node.h
    // Error: type "StringVector" can not automatically bind
    // NodeImpl& NodeImpl::operator=(const NodeImpl&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<NodeImpl>(engine, "NodeImpl");
#ifdef REGISTER_MANUAL_PART_NodeImpl
    REGISTER_MANUAL_PART_NodeImpl(NodeImpl, "NodeImpl")
#endif

    // HashMap<unsigned, ComponentReplicationState> NodeReplicationState::componentStates_ | File: ../Scene/ReplicationState.h
    // Error: type "HashMap<unsigned, ComponentReplicationState>" can not automatically bind
    // Connection* ReplicationState::connection_ | File: ../Scene/ReplicationState.h
    // Connection* can not be registered
    // DirtyBits NodeReplicationState::dirtyAttributes_ | File: ../Scene/ReplicationState.h
    engine->RegisterObjectProperty("NodeReplicationState", "DirtyBits dirtyAttributes", offsetof(NodeReplicationState, dirtyAttributes_));
    // HashSet<StringHash> NodeReplicationState::dirtyVars_ | File: ../Scene/ReplicationState.h
    // Error: type "HashSet<StringHash>" can not automatically bind
    // bool NodeReplicationState::markedDirty_ | File: ../Scene/ReplicationState.h
    engine->RegisterObjectProperty("NodeReplicationState", "bool markedDirty", offsetof(NodeReplicationState, markedDirty_));
    // WeakPtr<Node> NodeReplicationState::node_ | File: ../Scene/ReplicationState.h
    // Error: type "WeakPtr<Node>" can not automatically bind
    // float NodeReplicationState::priorityAcc_ | File: ../Scene/ReplicationState.h
    engine->RegisterObjectProperty("NodeReplicationState", "float priorityAcc", offsetof(NodeReplicationState, priorityAcc_));
    // SceneReplicationState* NodeReplicationState::sceneState_ | File: ../Scene/ReplicationState.h
    // SceneReplicationState* can not be registered
    // NodeReplicationState& NodeReplicationState::operator=(const NodeReplicationState&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<NodeReplicationState>(engine, "NodeReplicationState");
#ifdef REGISTER_MANUAL_PART_ReplicationState
    REGISTER_MANUAL_PART_ReplicationState(NodeReplicationState, "NodeReplicationState")
#endif
#ifdef REGISTER_MANUAL_PART_NodeReplicationState
    REGISTER_MANUAL_PART_NodeReplicationState(NodeReplicationState, "NodeReplicationState")
#endif

}

}
