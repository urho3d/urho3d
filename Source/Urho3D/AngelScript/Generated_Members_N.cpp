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
    engine->RegisterObjectBehaviour("NamedPipe", asBEHAVE_ADDREF, "void f()", asMETHODPR(NamedPipe, AddRef, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void NamedPipe::Close() | File: ../IO/NamedPipe.h
    engine->RegisterObjectMethod("NamedPipe", "void Close()", asMETHODPR(NamedPipe, Close, (), void), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "bool GetBlockEvents() const", asMETHODPR(NamedPipe, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "const String& GetCategory() const", asMETHODPR(NamedPipe, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "const String& get_category() const", asMETHODPR(NamedPipe, GetCategory, () const, const String&), asCALL_THISCALL);
    // virtual unsigned Deserializer::GetChecksum() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "uint GetChecksum()", asMETHODPR(NamedPipe, GetChecksum, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "uint get_checksum()", asMETHODPR(NamedPipe, GetChecksum, (), unsigned), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "VariantMap& GetEventDataMap() const", asMETHODPR(NamedPipe, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "Object@+ GetEventSender() const", asMETHODPR(NamedPipe, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(NamedPipe, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "const Variant& get_globalVar(StringHash) const", asMETHODPR(NamedPipe, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "const VariantMap& GetGlobalVars() const", asMETHODPR(NamedPipe, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "const VariantMap& get_globalVars() const", asMETHODPR(NamedPipe, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // const String& AbstractFile::GetName() const override | File: ../IO/AbstractFile.h
    engine->RegisterObjectMethod("NamedPipe", "const String& GetName() const", asMETHODPR(NamedPipe, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "const String& get_name() const", asMETHODPR(NamedPipe, GetName, () const, const String&), asCALL_THISCALL);
    // unsigned Deserializer::GetPosition() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "uint GetPosition() const", asMETHODPR(NamedPipe, GetPosition, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "uint get_position() const", asMETHODPR(NamedPipe, GetPosition, () const, unsigned), asCALL_THISCALL);
    // unsigned Deserializer::GetSize() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "uint GetSize() const", asMETHODPR(NamedPipe, GetSize, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "uint get_size() const", asMETHODPR(NamedPipe, GetSize, () const, unsigned), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(NamedPipe, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "StringHash GetType() const", asMETHODPR(NamedPipe, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "StringHash get_type() const", asMETHODPR(NamedPipe, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "const String& GetTypeName() const", asMETHODPR(NamedPipe, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "const String& get_typeName() const", asMETHODPR(NamedPipe, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "bool HasEventHandlers() const", asMETHODPR(NamedPipe, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(NamedPipe, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(NamedPipe, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool NamedPipe::IsEof() const override | File: ../IO/NamedPipe.h
    engine->RegisterObjectMethod("NamedPipe", "bool IsEof() const", asMETHODPR(NamedPipe, IsEof, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "bool get_eof() const", asMETHODPR(NamedPipe, IsEof, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "bool IsInstanceOf(StringHash) const", asMETHODPR(NamedPipe, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool NamedPipe::IsOpen() const | File: ../IO/NamedPipe.h
    engine->RegisterObjectMethod("NamedPipe", "bool IsOpen() const", asMETHODPR(NamedPipe, IsOpen, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "bool get_open() const", asMETHODPR(NamedPipe, IsOpen, () const, bool), asCALL_THISCALL);
    // bool NamedPipe::IsServer() const | File: ../IO/NamedPipe.h
    engine->RegisterObjectMethod("NamedPipe", "bool IsServer() const", asMETHODPR(NamedPipe, IsServer, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "bool get_server() const", asMETHODPR(NamedPipe, IsServer, () const, bool), asCALL_THISCALL);
    // explicit NamedPipe::NamedPipe(Context* context) | File: ../IO/NamedPipe.h
    engine->RegisterObjectBehaviour("NamedPipe", asBEHAVE_FACTORY, "NamedPipe@+ f()", asFUNCTION(NamedPipe_NamedPipe_Context), asCALL_CDECL);
    // NamedPipe::NamedPipe(Context* context, const String& name, bool isServer) | File: ../IO/NamedPipe.h
    engine->RegisterObjectBehaviour("NamedPipe", asBEHAVE_FACTORY, "NamedPipe@+ f(const String&in, bool)", asFUNCTION(NamedPipe_NamedPipe_Context_String_bool), asCALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(NamedPipe, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // bool NamedPipe::Open(const String& name, bool isServer) | File: ../IO/NamedPipe.h
    engine->RegisterObjectMethod("NamedPipe", "bool Open(const String&in, bool)", asMETHODPR(NamedPipe, Open, (const String&, bool), bool), asCALL_THISCALL);
    // unsigned NamedPipe::Read(void* dest, unsigned size) override | File: ../IO/NamedPipe.h
    // Error: type "void*" can not automatically bind
    // bool Deserializer::ReadBool() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool ReadBool()", asMETHODPR(NamedPipe, ReadBool, (), bool), asCALL_THISCALL);
    // BoundingBox Deserializer::ReadBoundingBox() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "BoundingBox ReadBoundingBox()", asMETHODPR(NamedPipe, ReadBoundingBox, (), BoundingBox), asCALL_THISCALL);
    // PODVector<unsigned char> Deserializer::ReadBuffer() | File: ../IO/Deserializer.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // signed char Deserializer::ReadByte() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "int8 ReadByte()", asMETHODPR(NamedPipe, ReadByte, (), signed char), asCALL_THISCALL);
    // Color Deserializer::ReadColor() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Color ReadColor()", asMETHODPR(NamedPipe, ReadColor, (), Color), asCALL_THISCALL);
    // double Deserializer::ReadDouble() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "double ReadDouble()", asMETHODPR(NamedPipe, ReadDouble, (), double), asCALL_THISCALL);
    // String Deserializer::ReadFileID() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "String ReadFileID()", asMETHODPR(NamedPipe, ReadFileID, (), String), asCALL_THISCALL);
    // float Deserializer::ReadFloat() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "float ReadFloat()", asMETHODPR(NamedPipe, ReadFloat, (), float), asCALL_THISCALL);
    // int Deserializer::ReadInt() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "int ReadInt()", asMETHODPR(NamedPipe, ReadInt, (), int), asCALL_THISCALL);
    // long long Deserializer::ReadInt64() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "int64 ReadInt64()", asMETHODPR(NamedPipe, ReadInt64, (), long long), asCALL_THISCALL);
    // IntRect Deserializer::ReadIntRect() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "IntRect ReadIntRect()", asMETHODPR(NamedPipe, ReadIntRect, (), IntRect), asCALL_THISCALL);
    // IntVector2 Deserializer::ReadIntVector2() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "IntVector2 ReadIntVector2()", asMETHODPR(NamedPipe, ReadIntVector2, (), IntVector2), asCALL_THISCALL);
    // IntVector3 Deserializer::ReadIntVector3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "IntVector3 ReadIntVector3()", asMETHODPR(NamedPipe, ReadIntVector3, (), IntVector3), asCALL_THISCALL);
    // String Deserializer::ReadLine() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "String ReadLine()", asMETHODPR(NamedPipe, ReadLine, (), String), asCALL_THISCALL);
    // Matrix3 Deserializer::ReadMatrix3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Matrix3 ReadMatrix3()", asMETHODPR(NamedPipe, ReadMatrix3, (), Matrix3), asCALL_THISCALL);
    // Matrix3x4 Deserializer::ReadMatrix3x4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Matrix3x4 ReadMatrix3x4()", asMETHODPR(NamedPipe, ReadMatrix3x4, (), Matrix3x4), asCALL_THISCALL);
    // Matrix4 Deserializer::ReadMatrix4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Matrix4 ReadMatrix4()", asMETHODPR(NamedPipe, ReadMatrix4, (), Matrix4), asCALL_THISCALL);
    // unsigned Deserializer::ReadNetID() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "uint ReadNetID()", asMETHODPR(NamedPipe, ReadNetID, (), unsigned), asCALL_THISCALL);
    // Quaternion Deserializer::ReadPackedQuaternion() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Quaternion ReadPackedQuaternion()", asMETHODPR(NamedPipe, ReadPackedQuaternion, (), Quaternion), asCALL_THISCALL);
    // Vector3 Deserializer::ReadPackedVector3(float maxAbsCoord) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Vector3 ReadPackedVector3(float)", asMETHODPR(NamedPipe, ReadPackedVector3, (float), Vector3), asCALL_THISCALL);
    // Quaternion Deserializer::ReadQuaternion() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Quaternion ReadQuaternion()", asMETHODPR(NamedPipe, ReadQuaternion, (), Quaternion), asCALL_THISCALL);
    // Rect Deserializer::ReadRect() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Rect ReadRect()", asMETHODPR(NamedPipe, ReadRect, (), Rect), asCALL_THISCALL);
    // ResourceRef Deserializer::ReadResourceRef() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "ResourceRef ReadResourceRef()", asMETHODPR(NamedPipe, ReadResourceRef, (), ResourceRef), asCALL_THISCALL);
    // ResourceRefList Deserializer::ReadResourceRefList() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "ResourceRefList ReadResourceRefList()", asMETHODPR(NamedPipe, ReadResourceRefList, (), ResourceRefList), asCALL_THISCALL);
    // short Deserializer::ReadShort() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "int16 ReadShort()", asMETHODPR(NamedPipe, ReadShort, (), short), asCALL_THISCALL);
    // String Deserializer::ReadString() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "String ReadString()", asMETHODPR(NamedPipe, ReadString, (), String), asCALL_THISCALL);
    // StringHash Deserializer::ReadStringHash() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "StringHash ReadStringHash()", asMETHODPR(NamedPipe, ReadStringHash, (), StringHash), asCALL_THISCALL);
    // StringVector Deserializer::ReadStringVector() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Array<String>@ ReadStringVector()", asFUNCTION(NamedPipe_ReadStringVector_void), asCALL_CDECL_OBJFIRST);
    // unsigned char Deserializer::ReadUByte() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "uint8 ReadUByte()", asMETHODPR(NamedPipe, ReadUByte, (), unsigned char), asCALL_THISCALL);
    // unsigned Deserializer::ReadUInt() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "uint ReadUInt()", asMETHODPR(NamedPipe, ReadUInt, (), unsigned), asCALL_THISCALL);
    // unsigned long long Deserializer::ReadUInt64() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "uint64 ReadUInt64()", asMETHODPR(NamedPipe, ReadUInt64, (), unsigned long long), asCALL_THISCALL);
    // unsigned short Deserializer::ReadUShort() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "uint16 ReadUShort()", asMETHODPR(NamedPipe, ReadUShort, (), unsigned short), asCALL_THISCALL);
    // Variant Deserializer::ReadVariant() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Variant ReadVariant()", asMETHODPR(NamedPipe, ReadVariant, (), Variant), asCALL_THISCALL);
    // Variant Deserializer::ReadVariant(VariantType type) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Variant ReadVariant(VariantType)", asMETHODPR(NamedPipe, ReadVariant, (VariantType), Variant), asCALL_THISCALL);
    // VariantMap Deserializer::ReadVariantMap() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "VariantMap ReadVariantMap()", asMETHODPR(NamedPipe, ReadVariantMap, (), VariantMap), asCALL_THISCALL);
    // VariantVector Deserializer::ReadVariantVector() | File: ../IO/Deserializer.h
    // Error: type "VariantVector" can not automatically bind
    // Vector2 Deserializer::ReadVector2() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Vector2 ReadVector2()", asMETHODPR(NamedPipe, ReadVector2, (), Vector2), asCALL_THISCALL);
    // Vector3 Deserializer::ReadVector3() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Vector3 ReadVector3()", asMETHODPR(NamedPipe, ReadVector3, (), Vector3), asCALL_THISCALL);
    // Vector4 Deserializer::ReadVector4() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "Vector4 ReadVector4()", asMETHODPR(NamedPipe, ReadVector4, (), Vector4), asCALL_THISCALL);
    // unsigned Deserializer::ReadVLE() | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "uint ReadVLE()", asMETHODPR(NamedPipe, ReadVLE, (), unsigned), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("NamedPipe", "int Refs() const", asMETHODPR(NamedPipe, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "int get_refs() const", asMETHODPR(NamedPipe, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("NamedPipe", asBEHAVE_RELEASE, "void f()", asMETHODPR(NamedPipe, ReleaseRef, (), void), asCALL_THISCALL);
    // unsigned NamedPipe::Seek(unsigned position) override | File: ../IO/NamedPipe.h
    engine->RegisterObjectMethod("NamedPipe", "uint Seek(uint)", asMETHODPR(NamedPipe, Seek, (unsigned), unsigned), asCALL_THISCALL);
    // unsigned Deserializer::SeekRelative(int delta) | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "uint SeekRelative(int)", asMETHODPR(NamedPipe, SeekRelative, (int), unsigned), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "void SendEvent(StringHash)", asMETHODPR(NamedPipe, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(NamedPipe, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "void SetBlockEvents(bool)", asMETHODPR(NamedPipe, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(NamedPipe, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(NamedPipe, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void NamedPipe::SetName(const String& name) override | File: ../IO/NamedPipe.h
    engine->RegisterObjectMethod("NamedPipe", "void SetName(const String&in)", asMETHODPR(NamedPipe, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "void set_name(const String&in)", asMETHODPR(NamedPipe, SetName, (const String&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // unsigned Deserializer::Tell() const | File: ../IO/Deserializer.h
    engine->RegisterObjectMethod("NamedPipe", "uint Tell() const", asMETHODPR(NamedPipe, Tell, () const, unsigned), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "void UnsubscribeFromAllEvents()", asMETHODPR(NamedPipe, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(NamedPipe_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(NamedPipe, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(NamedPipe, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NamedPipe", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(NamedPipe, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("NamedPipe", "int WeakRefs() const", asMETHODPR(NamedPipe, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("NamedPipe", "int get_weakRefs() const", asMETHODPR(NamedPipe, WeakRefs, () const, int), asCALL_THISCALL);
    // unsigned NamedPipe::Write(const void* data, unsigned size) override | File: ../IO/NamedPipe.h
    // Error: type "const void*" can not automatically bind
    // bool Serializer::WriteBool(bool value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteBool(bool)", asMETHODPR(NamedPipe, WriteBool, (bool), bool), asCALL_THISCALL);
    // bool Serializer::WriteBoundingBox(const BoundingBox& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteBoundingBox(const BoundingBox&in)", asMETHODPR(NamedPipe, WriteBoundingBox, (const BoundingBox&), bool), asCALL_THISCALL);
    // bool Serializer::WriteBuffer(const PODVector<unsigned char>& value) | File: ../IO/Serializer.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // bool Serializer::WriteByte(signed char value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteByte(int8)", asMETHODPR(NamedPipe, WriteByte, (signed char), bool), asCALL_THISCALL);
    // bool Serializer::WriteColor(const Color& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteColor(const Color&in)", asMETHODPR(NamedPipe, WriteColor, (const Color&), bool), asCALL_THISCALL);
    // bool Serializer::WriteDouble(double value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteDouble(double)", asMETHODPR(NamedPipe, WriteDouble, (double), bool), asCALL_THISCALL);
    // bool Serializer::WriteFileID(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteFileID(const String&in)", asMETHODPR(NamedPipe, WriteFileID, (const String&), bool), asCALL_THISCALL);
    // bool Serializer::WriteFloat(float value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteFloat(float)", asMETHODPR(NamedPipe, WriteFloat, (float), bool), asCALL_THISCALL);
    // bool Serializer::WriteInt(int value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteInt(int)", asMETHODPR(NamedPipe, WriteInt, (int), bool), asCALL_THISCALL);
    // bool Serializer::WriteInt64(long long value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteInt64(int64)", asMETHODPR(NamedPipe, WriteInt64, (long long), bool), asCALL_THISCALL);
    // bool Serializer::WriteIntRect(const IntRect& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteIntRect(const IntRect&in)", asMETHODPR(NamedPipe, WriteIntRect, (const IntRect&), bool), asCALL_THISCALL);
    // bool Serializer::WriteIntVector2(const IntVector2& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteIntVector2(const IntVector2&in)", asMETHODPR(NamedPipe, WriteIntVector2, (const IntVector2&), bool), asCALL_THISCALL);
    // bool Serializer::WriteIntVector3(const IntVector3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteIntVector3(const IntVector3&in)", asMETHODPR(NamedPipe, WriteIntVector3, (const IntVector3&), bool), asCALL_THISCALL);
    // bool Serializer::WriteLine(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteLine(const String&in)", asMETHODPR(NamedPipe, WriteLine, (const String&), bool), asCALL_THISCALL);
    // bool Serializer::WriteMatrix3(const Matrix3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteMatrix3(const Matrix3&in)", asMETHODPR(NamedPipe, WriteMatrix3, (const Matrix3&), bool), asCALL_THISCALL);
    // bool Serializer::WriteMatrix3x4(const Matrix3x4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteMatrix3x4(const Matrix3x4&in)", asMETHODPR(NamedPipe, WriteMatrix3x4, (const Matrix3x4&), bool), asCALL_THISCALL);
    // bool Serializer::WriteMatrix4(const Matrix4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteMatrix4(const Matrix4&in)", asMETHODPR(NamedPipe, WriteMatrix4, (const Matrix4&), bool), asCALL_THISCALL);
    // bool Serializer::WriteNetID(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteNetID(uint)", asMETHODPR(NamedPipe, WriteNetID, (unsigned), bool), asCALL_THISCALL);
    // bool Serializer::WritePackedQuaternion(const Quaternion& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WritePackedQuaternion(const Quaternion&in)", asMETHODPR(NamedPipe, WritePackedQuaternion, (const Quaternion&), bool), asCALL_THISCALL);
    // bool Serializer::WritePackedVector3(const Vector3& value, float maxAbsCoord) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WritePackedVector3(const Vector3&in, float)", asMETHODPR(NamedPipe, WritePackedVector3, (const Vector3&, float), bool), asCALL_THISCALL);
    // bool Serializer::WriteQuaternion(const Quaternion& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteQuaternion(const Quaternion&in)", asMETHODPR(NamedPipe, WriteQuaternion, (const Quaternion&), bool), asCALL_THISCALL);
    // bool Serializer::WriteRect(const Rect& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteRect(const Rect&in)", asMETHODPR(NamedPipe, WriteRect, (const Rect&), bool), asCALL_THISCALL);
    // bool Serializer::WriteResourceRef(const ResourceRef& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteResourceRef(const ResourceRef&in)", asMETHODPR(NamedPipe, WriteResourceRef, (const ResourceRef&), bool), asCALL_THISCALL);
    // bool Serializer::WriteResourceRefList(const ResourceRefList& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteResourceRefList(const ResourceRefList&in)", asMETHODPR(NamedPipe, WriteResourceRefList, (const ResourceRefList&), bool), asCALL_THISCALL);
    // bool Serializer::WriteShort(short value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteShort(int16)", asMETHODPR(NamedPipe, WriteShort, (short), bool), asCALL_THISCALL);
    // bool Serializer::WriteString(const String& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteString(const String&in)", asMETHODPR(NamedPipe, WriteString, (const String&), bool), asCALL_THISCALL);
    // bool Serializer::WriteStringHash(const StringHash& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteStringHash(const StringHash&in)", asMETHODPR(NamedPipe, WriteStringHash, (const StringHash&), bool), asCALL_THISCALL);
    // bool Serializer::WriteStringVector(const StringVector& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteStringVector(Array<String>@+)", asFUNCTION(NamedPipe_WriteStringVector_StringVector), asCALL_CDECL_OBJFIRST);
    // bool Serializer::WriteUByte(unsigned char value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteUByte(uint8)", asMETHODPR(NamedPipe, WriteUByte, (unsigned char), bool), asCALL_THISCALL);
    // bool Serializer::WriteUInt(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteUInt(uint)", asMETHODPR(NamedPipe, WriteUInt, (unsigned), bool), asCALL_THISCALL);
    // bool Serializer::WriteUInt64(unsigned long long value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteUInt64(uint64)", asMETHODPR(NamedPipe, WriteUInt64, (unsigned long long), bool), asCALL_THISCALL);
    // bool Serializer::WriteUShort(unsigned short value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteUShort(uint16)", asMETHODPR(NamedPipe, WriteUShort, (unsigned short), bool), asCALL_THISCALL);
    // bool Serializer::WriteVariant(const Variant& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteVariant(const Variant&in)", asMETHODPR(NamedPipe, WriteVariant, (const Variant&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVariantData(const Variant& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteVariantData(const Variant&in)", asMETHODPR(NamedPipe, WriteVariantData, (const Variant&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVariantMap(const VariantMap& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteVariantMap(const VariantMap&in)", asMETHODPR(NamedPipe, WriteVariantMap, (const VariantMap&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVariantVector(const VariantVector& value) | File: ../IO/Serializer.h
    // Error: type "const VariantVector&" can not automatically bind
    // bool Serializer::WriteVector2(const Vector2& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteVector2(const Vector2&in)", asMETHODPR(NamedPipe, WriteVector2, (const Vector2&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVector3(const Vector3& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteVector3(const Vector3&in)", asMETHODPR(NamedPipe, WriteVector3, (const Vector3&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVector4(const Vector4& value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteVector4(const Vector4&in)", asMETHODPR(NamedPipe, WriteVector4, (const Vector4&), bool), asCALL_THISCALL);
    // bool Serializer::WriteVLE(unsigned value) | File: ../IO/Serializer.h
    engine->RegisterObjectMethod("NamedPipe", "bool WriteVLE(uint)", asMETHODPR(NamedPipe, WriteVLE, (unsigned), bool), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("NavArea", asBEHAVE_ADDREF, "void f()", asMETHODPR(NavArea, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "void AllocateNetworkState()", asMETHODPR(NavArea, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "void ApplyAttributes()", asMETHODPR(NavArea, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void NavArea::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Navigation/NavArea.h
    engine->RegisterObjectMethod("NavArea", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(NavArea, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "bool GetAnimationEnabled() const", asMETHODPR(NavArea, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "bool get_animationEnabled() const", asMETHODPR(NavArea, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // unsigned NavArea::GetAreaID() const | File: ../Navigation/NavArea.h
    engine->RegisterObjectMethod("NavArea", "uint GetAreaID() const", asMETHODPR(NavArea, GetAreaID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "uint get_areaID() const", asMETHODPR(NavArea, GetAreaID, () const, unsigned), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "Variant GetAttribute(uint) const", asMETHODPR(NavArea, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "Variant get_attributes(uint) const", asMETHODPR(NavArea, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "Variant GetAttribute(const String&in) const", asMETHODPR(NavArea, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(NavArea, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(NavArea, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(NavArea, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(NavArea, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "Variant GetAttributeDefault(uint) const", asMETHODPR(NavArea, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "Variant get_attributeDefaults(uint) const", asMETHODPR(NavArea, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(NavArea, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "bool GetBlockEvents() const", asMETHODPR(NavArea, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // BoundingBox NavArea::GetBoundingBox() const | File: ../Navigation/NavArea.h
    engine->RegisterObjectMethod("NavArea", "BoundingBox GetBoundingBox() const", asMETHODPR(NavArea, GetBoundingBox, () const, BoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "BoundingBox get_boundingBox() const", asMETHODPR(NavArea, GetBoundingBox, () const, BoundingBox), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "const String& GetCategory() const", asMETHODPR(NavArea, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "const String& get_category() const", asMETHODPR(NavArea, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "Component@+ GetComponent(StringHash) const", asMETHODPR(NavArea, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("NavArea", "VariantMap& GetEventDataMap() const", asMETHODPR(NavArea, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "Object@+ GetEventSender() const", asMETHODPR(NavArea, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(NavArea, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "const Variant& get_globalVar(StringHash) const", asMETHODPR(NavArea, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "const VariantMap& GetGlobalVars() const", asMETHODPR(NavArea, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "const VariantMap& get_globalVars() const", asMETHODPR(NavArea, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "uint GetID() const", asMETHODPR(NavArea, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "uint get_id() const", asMETHODPR(NavArea, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(NavArea, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "Node@+ GetNode() const", asMETHODPR(NavArea, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "Node@+ get_node() const", asMETHODPR(NavArea, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "uint GetNumAttributes() const", asMETHODPR(NavArea, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "uint get_numAttributes() const", asMETHODPR(NavArea, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "uint GetNumNetworkAttributes() const", asMETHODPR(NavArea, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(NavArea, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(NavArea, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(NavArea, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "Scene@+ GetScene() const", asMETHODPR(NavArea, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(NavArea, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "StringHash GetType() const", asMETHODPR(NavArea, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "StringHash get_type() const", asMETHODPR(NavArea, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "const String& GetTypeName() const", asMETHODPR(NavArea, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "const String& get_typeName() const", asMETHODPR(NavArea, GetTypeName, () const, const String&), asCALL_THISCALL);
    // BoundingBox NavArea::GetWorldBoundingBox() const | File: ../Navigation/NavArea.h
    engine->RegisterObjectMethod("NavArea", "BoundingBox GetWorldBoundingBox() const", asMETHODPR(NavArea, GetWorldBoundingBox, () const, BoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "BoundingBox get_worldBoundingBox() const", asMETHODPR(NavArea, GetWorldBoundingBox, () const, BoundingBox), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "bool HasEventHandlers() const", asMETHODPR(NavArea, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(NavArea, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(NavArea, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "bool IsEnabled() const", asMETHODPR(NavArea, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "bool get_enabled() const", asMETHODPR(NavArea, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "bool IsEnabledEffective() const", asMETHODPR(NavArea, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "bool get_enabledEffective() const", asMETHODPR(NavArea, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "bool IsInstanceOf(StringHash) const", asMETHODPR(NavArea, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "bool IsReplicated() const", asMETHODPR(NavArea, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "bool get_replicated() const", asMETHODPR(NavArea, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "bool IsTemporary() const", asMETHODPR(NavArea, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "bool get_temporary() const", asMETHODPR(NavArea, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "bool Load(Deserializer&)", asMETHODPR(NavArea, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "bool LoadJSON(const JSONValue&in)", asMETHODPR(NavArea, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "bool LoadXML(const XMLElement&in)", asMETHODPR(NavArea, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "void MarkNetworkUpdate()", asMETHODPR(NavArea, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // explicit NavArea::NavArea(Context* context) | File: ../Navigation/NavArea.h
    engine->RegisterObjectBehaviour("NavArea", asBEHAVE_FACTORY, "NavArea@+ f()", asFUNCTION(NavArea_NavArea_Context), asCALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(NavArea, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(NavArea, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(NavArea, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "void OnSetEnabled()", asMETHODPR(NavArea, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "void PrepareNetworkUpdate()", asMETHODPR(NavArea, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(NavArea, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(NavArea, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("NavArea", "int Refs() const", asMETHODPR(NavArea, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "int get_refs() const", asMETHODPR(NavArea, Refs, () const, int), asCALL_THISCALL);
    // static void NavArea::RegisterObject(Context* context) | File: ../Navigation/NavArea.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("NavArea", asBEHAVE_RELEASE, "void f()", asMETHODPR(NavArea, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "void Remove()", asMETHODPR(NavArea, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(NavArea, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "void RemoveInstanceDefault()", asMETHODPR(NavArea, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "void RemoveObjectAnimation()", asMETHODPR(NavArea, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "void ResetToDefault()", asMETHODPR(NavArea, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "bool Save(Serializer&) const", asMETHODPR(NavArea, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "bool SaveDefaultAttributes() const", asMETHODPR(NavArea, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "bool SaveJSON(JSONValue&) const", asMETHODPR(NavArea, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "bool SaveXML(XMLElement&) const", asMETHODPR(NavArea, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "void SendEvent(StringHash)", asMETHODPR(NavArea, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(NavArea, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "void SetAnimationEnabled(bool)", asMETHODPR(NavArea, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "void set_animationEnabled(bool)", asMETHODPR(NavArea, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "void SetAnimationTime(float)", asMETHODPR(NavArea, SetAnimationTime, (float), void), asCALL_THISCALL);
    // void NavArea::SetAreaID(unsigned newID) | File: ../Navigation/NavArea.h
    engine->RegisterObjectMethod("NavArea", "void SetAreaID(uint)", asMETHODPR(NavArea, SetAreaID, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "void set_areaID(uint)", asMETHODPR(NavArea, SetAreaID, (unsigned), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(NavArea, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "bool set_attributes(uint, const Variant&in)", asMETHODPR(NavArea, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(NavArea, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(NavArea, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(NavArea, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(NavArea, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(NavArea, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "void SetBlockEvents(bool)", asMETHODPR(NavArea, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void NavArea::SetBoundingBox(const BoundingBox& bnds) | File: ../Navigation/NavArea.h
    engine->RegisterObjectMethod("NavArea", "void SetBoundingBox(const BoundingBox&in)", asMETHODPR(NavArea, SetBoundingBox, (const BoundingBox&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "void set_boundingBox(const BoundingBox&in)", asMETHODPR(NavArea, SetBoundingBox, (const BoundingBox&), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavArea", "void SetEnabled(bool)", asMETHODPR(NavArea, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "void set_enabled(bool)", asMETHODPR(NavArea, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(NavArea, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(NavArea, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "void SetInstanceDefault(bool)", asMETHODPR(NavArea, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(NavArea, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(NavArea, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(NavArea, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavArea", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(NavArea, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "void SetTemporary(bool)", asMETHODPR(NavArea, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "void set_temporary(bool)", asMETHODPR(NavArea, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "void UnsubscribeFromAllEvents()", asMETHODPR(NavArea, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(NavArea_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(NavArea, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(NavArea, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavArea", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(NavArea, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("NavArea", "int WeakRefs() const", asMETHODPR(NavArea, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavArea", "int get_weakRefs() const", asMETHODPR(NavArea, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(NavArea, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(NavArea, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavArea", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(NavArea, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("Navigable", asBEHAVE_ADDREF, "void f()", asMETHODPR(Navigable, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "void AllocateNetworkState()", asMETHODPR(Navigable, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "void ApplyAttributes()", asMETHODPR(Navigable, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(Navigable, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "bool GetAnimationEnabled() const", asMETHODPR(Navigable, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "bool get_animationEnabled() const", asMETHODPR(Navigable, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "Variant GetAttribute(uint) const", asMETHODPR(Navigable, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "Variant get_attributes(uint) const", asMETHODPR(Navigable, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "Variant GetAttribute(const String&in) const", asMETHODPR(Navigable, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(Navigable, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(Navigable, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(Navigable, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(Navigable, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "Variant GetAttributeDefault(uint) const", asMETHODPR(Navigable, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "Variant get_attributeDefaults(uint) const", asMETHODPR(Navigable, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Navigable, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "bool GetBlockEvents() const", asMETHODPR(Navigable, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "const String& GetCategory() const", asMETHODPR(Navigable, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "const String& get_category() const", asMETHODPR(Navigable, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "Component@+ GetComponent(StringHash) const", asMETHODPR(Navigable, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Navigable", "VariantMap& GetEventDataMap() const", asMETHODPR(Navigable, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "Object@+ GetEventSender() const", asMETHODPR(Navigable, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Navigable, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Navigable, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "const VariantMap& GetGlobalVars() const", asMETHODPR(Navigable, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "const VariantMap& get_globalVars() const", asMETHODPR(Navigable, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "uint GetID() const", asMETHODPR(Navigable, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "uint get_id() const", asMETHODPR(Navigable, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Navigable, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "Node@+ GetNode() const", asMETHODPR(Navigable, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "Node@+ get_node() const", asMETHODPR(Navigable, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "uint GetNumAttributes() const", asMETHODPR(Navigable, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "uint get_numAttributes() const", asMETHODPR(Navigable, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "uint GetNumNetworkAttributes() const", asMETHODPR(Navigable, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(Navigable, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(Navigable, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(Navigable, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "Scene@+ GetScene() const", asMETHODPR(Navigable, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Navigable, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "StringHash GetType() const", asMETHODPR(Navigable, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "StringHash get_type() const", asMETHODPR(Navigable, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "const String& GetTypeName() const", asMETHODPR(Navigable, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "const String& get_typeName() const", asMETHODPR(Navigable, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "bool HasEventHandlers() const", asMETHODPR(Navigable, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Navigable, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Navigable, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "bool IsEnabled() const", asMETHODPR(Navigable, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "bool get_enabled() const", asMETHODPR(Navigable, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "bool IsEnabledEffective() const", asMETHODPR(Navigable, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "bool get_enabledEffective() const", asMETHODPR(Navigable, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "bool IsInstanceOf(StringHash) const", asMETHODPR(Navigable, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Navigable::IsRecursive() const | File: ../Navigation/Navigable.h
    engine->RegisterObjectMethod("Navigable", "bool IsRecursive() const", asMETHODPR(Navigable, IsRecursive, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "bool get_recursive() const", asMETHODPR(Navigable, IsRecursive, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "bool IsReplicated() const", asMETHODPR(Navigable, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "bool get_replicated() const", asMETHODPR(Navigable, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "bool IsTemporary() const", asMETHODPR(Navigable, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "bool get_temporary() const", asMETHODPR(Navigable, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "bool Load(Deserializer&)", asMETHODPR(Navigable, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Navigable, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "bool LoadXML(const XMLElement&in)", asMETHODPR(Navigable, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "void MarkNetworkUpdate()", asMETHODPR(Navigable, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // explicit Navigable::Navigable(Context* context) | File: ../Navigation/Navigable.h
    engine->RegisterObjectBehaviour("Navigable", asBEHAVE_FACTORY, "Navigable@+ f()", asFUNCTION(Navigable_Navigable_Context), asCALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Navigable, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Navigable, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Navigable, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "void OnSetEnabled()", asMETHODPR(Navigable, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "void PrepareNetworkUpdate()", asMETHODPR(Navigable, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Navigable, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Navigable, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Navigable", "int Refs() const", asMETHODPR(Navigable, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "int get_refs() const", asMETHODPR(Navigable, Refs, () const, int), asCALL_THISCALL);
    // static void Navigable::RegisterObject(Context* context) | File: ../Navigation/Navigable.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Navigable", asBEHAVE_RELEASE, "void f()", asMETHODPR(Navigable, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "void Remove()", asMETHODPR(Navigable, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(Navigable, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "void RemoveInstanceDefault()", asMETHODPR(Navigable, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "void RemoveObjectAnimation()", asMETHODPR(Navigable, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "void ResetToDefault()", asMETHODPR(Navigable, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "bool Save(Serializer&) const", asMETHODPR(Navigable, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "bool SaveDefaultAttributes() const", asMETHODPR(Navigable, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "bool SaveJSON(JSONValue&) const", asMETHODPR(Navigable, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "bool SaveXML(XMLElement&) const", asMETHODPR(Navigable, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "void SendEvent(StringHash)", asMETHODPR(Navigable, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Navigable, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "void SetAnimationEnabled(bool)", asMETHODPR(Navigable, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "void set_animationEnabled(bool)", asMETHODPR(Navigable, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "void SetAnimationTime(float)", asMETHODPR(Navigable, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Navigable, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Navigable, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Navigable, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Navigable, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(Navigable, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(Navigable, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Navigable, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "void SetBlockEvents(bool)", asMETHODPR(Navigable, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Navigable", "void SetEnabled(bool)", asMETHODPR(Navigable, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "void set_enabled(bool)", asMETHODPR(Navigable, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Navigable, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Navigable, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "void SetInstanceDefault(bool)", asMETHODPR(Navigable, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Navigable, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(Navigable, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(Navigable, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Navigable", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(Navigable, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Navigable::SetRecursive(bool enable) | File: ../Navigation/Navigable.h
    engine->RegisterObjectMethod("Navigable", "void SetRecursive(bool)", asMETHODPR(Navigable, SetRecursive, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "void set_recursive(bool)", asMETHODPR(Navigable, SetRecursive, (bool), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "void SetTemporary(bool)", asMETHODPR(Navigable, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "void set_temporary(bool)", asMETHODPR(Navigable, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "void UnsubscribeFromAllEvents()", asMETHODPR(Navigable, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Navigable_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Navigable, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Navigable, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Navigable", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Navigable, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Navigable", "int WeakRefs() const", asMETHODPR(Navigable, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "int get_weakRefs() const", asMETHODPR(Navigable, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Navigable, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Navigable, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Navigable", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Navigable, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("NavigationMesh", asBEHAVE_ADDREF, "void f()", asMETHODPR(NavigationMesh, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // virtual bool NavigationMesh::AddTile(const PODVector<unsigned char>& tileData) | File: ../Navigation/NavigationMesh.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // virtual bool NavigationMesh::Allocate(const BoundingBox& boundingBox, unsigned maxTiles) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "bool Allocate(const BoundingBox&in, uint)", asMETHODPR(NavigationMesh, Allocate, (const BoundingBox&, unsigned), bool), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "void AllocateNetworkState()", asMETHODPR(NavigationMesh, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "void ApplyAttributes()", asMETHODPR(NavigationMesh, ApplyAttributes, (), void), asCALL_THISCALL);
    // virtual bool NavigationMesh::Build() | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "bool Build()", asMETHODPR(NavigationMesh, Build, (), bool), asCALL_THISCALL);
    // virtual bool NavigationMesh::Build(const BoundingBox& boundingBox) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "bool Build(const BoundingBox&in)", asMETHODPR(NavigationMesh, Build, (const BoundingBox&), bool), asCALL_THISCALL);
    // virtual bool NavigationMesh::Build(const IntVector2& from, const IntVector2& to) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "bool Build(const IntVector2&in, const IntVector2&in)", asMETHODPR(NavigationMesh, Build, (const IntVector2&, const IntVector2&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void NavigationMesh::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(NavigationMesh, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // void NavigationMesh::DrawDebugGeometry(bool depthTest) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void DrawDebugGeometry(bool)", asMETHODPR(NavigationMesh, DrawDebugGeometry, (bool), void), asCALL_THISCALL);
    // Vector3 NavigationMesh::FindNearestPoint(const Vector3& point, const Vector3& extents=Vector3::ONE, const dtQueryFilter* filter=nullptr, dtPolyRef* nearestRef=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "const dtQueryFilter*" can not automatically bind
    // void NavigationMesh::FindPath(PODVector<Vector3>& dest, const Vector3& start, const Vector3& end, const Vector3& extents=Vector3::ONE, const dtQueryFilter* filter=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "PODVector<Vector3>&" can not automatically bind
    // void NavigationMesh::FindPath(PODVector<NavigationPathPoint>& dest, const Vector3& start, const Vector3& end, const Vector3& extents=Vector3::ONE, const dtQueryFilter* filter=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "PODVector<NavigationPathPoint>&" can not automatically bind
    // float NavigationMesh::GetAgentHeight() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetAgentHeight() const", asMETHODPR(NavigationMesh, GetAgentHeight, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_agentHeight() const", asMETHODPR(NavigationMesh, GetAgentHeight, () const, float), asCALL_THISCALL);
    // float NavigationMesh::GetAgentMaxClimb() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetAgentMaxClimb() const", asMETHODPR(NavigationMesh, GetAgentMaxClimb, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_agentMaxClimb() const", asMETHODPR(NavigationMesh, GetAgentMaxClimb, () const, float), asCALL_THISCALL);
    // float NavigationMesh::GetAgentMaxSlope() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetAgentMaxSlope() const", asMETHODPR(NavigationMesh, GetAgentMaxSlope, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_agentMaxSlope() const", asMETHODPR(NavigationMesh, GetAgentMaxSlope, () const, float), asCALL_THISCALL);
    // float NavigationMesh::GetAgentRadius() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetAgentRadius() const", asMETHODPR(NavigationMesh, GetAgentRadius, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_agentRadius() const", asMETHODPR(NavigationMesh, GetAgentRadius, () const, float), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "bool GetAnimationEnabled() const", asMETHODPR(NavigationMesh, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "bool get_animationEnabled() const", asMETHODPR(NavigationMesh, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // float NavigationMesh::GetAreaCost(unsigned areaID) const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetAreaCost(uint) const", asMETHODPR(NavigationMesh, GetAreaCost, (unsigned) const, float), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "Variant GetAttribute(uint) const", asMETHODPR(NavigationMesh, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "Variant get_attributes(uint) const", asMETHODPR(NavigationMesh, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "Variant GetAttribute(const String&in) const", asMETHODPR(NavigationMesh, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(NavigationMesh, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(NavigationMesh, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(NavigationMesh, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(NavigationMesh, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "Variant GetAttributeDefault(uint) const", asMETHODPR(NavigationMesh, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "Variant get_attributeDefaults(uint) const", asMETHODPR(NavigationMesh, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(NavigationMesh, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "bool GetBlockEvents() const", asMETHODPR(NavigationMesh, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const BoundingBox& NavigationMesh::GetBoundingBox() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "const BoundingBox& GetBoundingBox() const", asMETHODPR(NavigationMesh, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "const BoundingBox& get_boundingBox() const", asMETHODPR(NavigationMesh, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "const String& GetCategory() const", asMETHODPR(NavigationMesh, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "const String& get_category() const", asMETHODPR(NavigationMesh, GetCategory, () const, const String&), asCALL_THISCALL);
    // float NavigationMesh::GetCellHeight() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetCellHeight() const", asMETHODPR(NavigationMesh, GetCellHeight, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_cellHeight() const", asMETHODPR(NavigationMesh, GetCellHeight, () const, float), asCALL_THISCALL);
    // float NavigationMesh::GetCellSize() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetCellSize() const", asMETHODPR(NavigationMesh, GetCellSize, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_cellSize() const", asMETHODPR(NavigationMesh, GetCellSize, () const, float), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "Component@+ GetComponent(StringHash) const", asMETHODPR(NavigationMesh, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    // float NavigationMesh::GetDetailSampleDistance() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetDetailSampleDistance() const", asMETHODPR(NavigationMesh, GetDetailSampleDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_detailSampleDistance() const", asMETHODPR(NavigationMesh, GetDetailSampleDistance, () const, float), asCALL_THISCALL);
    // float NavigationMesh::GetDetailSampleMaxError() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetDetailSampleMaxError() const", asMETHODPR(NavigationMesh, GetDetailSampleMaxError, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_detailSampleMaxError() const", asMETHODPR(NavigationMesh, GetDetailSampleMaxError, () const, float), asCALL_THISCALL);
    // float NavigationMesh::GetDistanceToWall(const Vector3& point, float radius, const Vector3& extents=Vector3::ONE, const dtQueryFilter* filter=nullptr, Vector3* hitPos=nullptr, Vector3* hitNormal=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "const dtQueryFilter*" can not automatically bind
    // bool NavigationMesh::GetDrawNavAreas() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "bool GetDrawNavAreas() const", asMETHODPR(NavigationMesh, GetDrawNavAreas, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "bool get_drawNavAreas() const", asMETHODPR(NavigationMesh, GetDrawNavAreas, () const, bool), asCALL_THISCALL);
    // bool NavigationMesh::GetDrawOffMeshConnections() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "bool GetDrawOffMeshConnections() const", asMETHODPR(NavigationMesh, GetDrawOffMeshConnections, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "bool get_drawOffMeshConnections() const", asMETHODPR(NavigationMesh, GetDrawOffMeshConnections, () const, bool), asCALL_THISCALL);
    // float NavigationMesh::GetEdgeMaxError() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetEdgeMaxError() const", asMETHODPR(NavigationMesh, GetEdgeMaxError, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_edgeMaxError() const", asMETHODPR(NavigationMesh, GetEdgeMaxError, () const, float), asCALL_THISCALL);
    // float NavigationMesh::GetEdgeMaxLength() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetEdgeMaxLength() const", asMETHODPR(NavigationMesh, GetEdgeMaxLength, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_edgeMaxLength() const", asMETHODPR(NavigationMesh, GetEdgeMaxLength, () const, float), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "VariantMap& GetEventDataMap() const", asMETHODPR(NavigationMesh, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "Object@+ GetEventSender() const", asMETHODPR(NavigationMesh, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(NavigationMesh, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "const Variant& get_globalVar(StringHash) const", asMETHODPR(NavigationMesh, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "const VariantMap& GetGlobalVars() const", asMETHODPR(NavigationMesh, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "const VariantMap& get_globalVars() const", asMETHODPR(NavigationMesh, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "uint GetID() const", asMETHODPR(NavigationMesh, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "uint get_id() const", asMETHODPR(NavigationMesh, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(NavigationMesh, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // String NavigationMesh::GetMeshName() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "String GetMeshName() const", asMETHODPR(NavigationMesh, GetMeshName, () const, String), asCALL_THISCALL);
    // virtual PODVector<unsigned char> NavigationMesh::GetNavigationDataAttr() const | File: ../Navigation/NavigationMesh.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "Node@+ GetNode() const", asMETHODPR(NavigationMesh, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "Node@+ get_node() const", asMETHODPR(NavigationMesh, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "uint GetNumAttributes() const", asMETHODPR(NavigationMesh, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "uint get_numAttributes() const", asMETHODPR(NavigationMesh, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "uint GetNumNetworkAttributes() const", asMETHODPR(NavigationMesh, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // IntVector2 NavigationMesh::GetNumTiles() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "IntVector2 GetNumTiles() const", asMETHODPR(NavigationMesh, GetNumTiles, () const, IntVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "IntVector2 get_numTiles() const", asMETHODPR(NavigationMesh, GetNumTiles, () const, IntVector2), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(NavigationMesh, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(NavigationMesh, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(NavigationMesh, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // const Vector3& NavigationMesh::GetPadding() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "const Vector3& GetPadding() const", asMETHODPR(NavigationMesh, GetPadding, () const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "const Vector3& get_padding() const", asMETHODPR(NavigationMesh, GetPadding, () const, const Vector3&), asCALL_THISCALL);
    // NavmeshPartitionType NavigationMesh::GetPartitionType() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "NavmeshPartitionType GetPartitionType() const", asMETHODPR(NavigationMesh, GetPartitionType, () const, NavmeshPartitionType), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "NavmeshPartitionType get_partitionType() const", asMETHODPR(NavigationMesh, GetPartitionType, () const, NavmeshPartitionType), asCALL_THISCALL);
    // Vector3 NavigationMesh::GetRandomPoint(const dtQueryFilter* filter=nullptr, dtPolyRef* randomRef=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "const dtQueryFilter*" can not automatically bind
    // Vector3 NavigationMesh::GetRandomPointInCircle(const Vector3& center, float radius, const Vector3& extents=Vector3::ONE, const dtQueryFilter* filter=nullptr, dtPolyRef* randomRef=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "const dtQueryFilter*" can not automatically bind
    // float NavigationMesh::GetRegionMergeSize() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetRegionMergeSize() const", asMETHODPR(NavigationMesh, GetRegionMergeSize, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_regionMergeSize() const", asMETHODPR(NavigationMesh, GetRegionMergeSize, () const, float), asCALL_THISCALL);
    // float NavigationMesh::GetRegionMinSize() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "float GetRegionMinSize() const", asMETHODPR(NavigationMesh, GetRegionMinSize, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_regionMinSize() const", asMETHODPR(NavigationMesh, GetRegionMinSize, () const, float), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "Scene@+ GetScene() const", asMETHODPR(NavigationMesh, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(NavigationMesh, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // BoundingBox NavigationMesh::GetTileBoundingBox(const IntVector2& tile) const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "BoundingBox GetTileBoundingBox(const IntVector2&in) const", asMETHODPR(NavigationMesh, GetTileBoundingBox, (const IntVector2&) const, BoundingBox), asCALL_THISCALL);
    // virtual PODVector<unsigned char> NavigationMesh::GetTileData(const IntVector2& tile) const | File: ../Navigation/NavigationMesh.h
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // IntVector2 NavigationMesh::GetTileIndex(const Vector3& position) const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "IntVector2 GetTileIndex(const Vector3&in) const", asMETHODPR(NavigationMesh, GetTileIndex, (const Vector3&) const, IntVector2), asCALL_THISCALL);
    // int NavigationMesh::GetTileSize() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "int GetTileSize() const", asMETHODPR(NavigationMesh, GetTileSize, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "int get_tileSize() const", asMETHODPR(NavigationMesh, GetTileSize, () const, int), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "StringHash GetType() const", asMETHODPR(NavigationMesh, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "StringHash get_type() const", asMETHODPR(NavigationMesh, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "const String& GetTypeName() const", asMETHODPR(NavigationMesh, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "const String& get_typeName() const", asMETHODPR(NavigationMesh, GetTypeName, () const, const String&), asCALL_THISCALL);
    // BoundingBox NavigationMesh::GetWorldBoundingBox() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "BoundingBox GetWorldBoundingBox() const", asMETHODPR(NavigationMesh, GetWorldBoundingBox, () const, BoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "BoundingBox get_worldBoundingBox() const", asMETHODPR(NavigationMesh, GetWorldBoundingBox, () const, BoundingBox), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "bool HasEventHandlers() const", asMETHODPR(NavigationMesh, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(NavigationMesh, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(NavigationMesh, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool NavigationMesh::HasTile(const IntVector2& tile) const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "bool HasTile(const IntVector2&in) const", asMETHODPR(NavigationMesh, HasTile, (const IntVector2&) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "bool IsEnabled() const", asMETHODPR(NavigationMesh, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "bool get_enabled() const", asMETHODPR(NavigationMesh, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "bool IsEnabledEffective() const", asMETHODPR(NavigationMesh, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "bool get_enabledEffective() const", asMETHODPR(NavigationMesh, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool NavigationMesh::IsInitialized() const | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "bool IsInitialized() const", asMETHODPR(NavigationMesh, IsInitialized, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "bool get_initialized() const", asMETHODPR(NavigationMesh, IsInitialized, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "bool IsInstanceOf(StringHash) const", asMETHODPR(NavigationMesh, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "bool IsReplicated() const", asMETHODPR(NavigationMesh, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "bool get_replicated() const", asMETHODPR(NavigationMesh, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "bool IsTemporary() const", asMETHODPR(NavigationMesh, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "bool get_temporary() const", asMETHODPR(NavigationMesh, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "bool Load(Deserializer&)", asMETHODPR(NavigationMesh, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "bool LoadJSON(const JSONValue&in)", asMETHODPR(NavigationMesh, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "bool LoadXML(const XMLElement&in)", asMETHODPR(NavigationMesh, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "void MarkNetworkUpdate()", asMETHODPR(NavigationMesh, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // Vector3 NavigationMesh::MoveAlongSurface(const Vector3& start, const Vector3& end, const Vector3& extents=Vector3::ONE, int maxVisited=3, const dtQueryFilter* filter=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "const dtQueryFilter*" can not automatically bind
    // explicit NavigationMesh::NavigationMesh(Context* context) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectBehaviour("NavigationMesh", asBEHAVE_FACTORY, "NavigationMesh@+ f()", asFUNCTION(NavigationMesh_NavigationMesh_Context), asCALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(NavigationMesh, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(NavigationMesh, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(NavigationMesh, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "void OnSetEnabled()", asMETHODPR(NavigationMesh, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "void PrepareNetworkUpdate()", asMETHODPR(NavigationMesh, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // Vector3 NavigationMesh::Raycast(const Vector3& start, const Vector3& end, const Vector3& extents=Vector3::ONE, const dtQueryFilter* filter=nullptr, Vector3* hitNormal=nullptr) | File: ../Navigation/NavigationMesh.h
    // Error: type "const dtQueryFilter*" can not automatically bind
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(NavigationMesh, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(NavigationMesh, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("NavigationMesh", "int Refs() const", asMETHODPR(NavigationMesh, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "int get_refs() const", asMETHODPR(NavigationMesh, Refs, () const, int), asCALL_THISCALL);
    // static void NavigationMesh::RegisterObject(Context* context) | File: ../Navigation/NavigationMesh.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("NavigationMesh", asBEHAVE_RELEASE, "void f()", asMETHODPR(NavigationMesh, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "void Remove()", asMETHODPR(NavigationMesh, Remove, (), void), asCALL_THISCALL);
    // virtual void NavigationMesh::RemoveAllTiles() | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void RemoveAllTiles()", asMETHODPR(NavigationMesh, RemoveAllTiles, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(NavigationMesh, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "void RemoveInstanceDefault()", asMETHODPR(NavigationMesh, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "void RemoveObjectAnimation()", asMETHODPR(NavigationMesh, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // virtual void NavigationMesh::RemoveTile(const IntVector2& tile) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void RemoveTile(const IntVector2&in)", asMETHODPR(NavigationMesh, RemoveTile, (const IntVector2&), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "void ResetToDefault()", asMETHODPR(NavigationMesh, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "bool Save(Serializer&) const", asMETHODPR(NavigationMesh, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "bool SaveDefaultAttributes() const", asMETHODPR(NavigationMesh, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "bool SaveJSON(JSONValue&) const", asMETHODPR(NavigationMesh, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "bool SaveXML(XMLElement&) const", asMETHODPR(NavigationMesh, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "void SendEvent(StringHash)", asMETHODPR(NavigationMesh, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(NavigationMesh, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void NavigationMesh::SetAgentHeight(float height) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetAgentHeight(float)", asMETHODPR(NavigationMesh, SetAgentHeight, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_agentHeight(float)", asMETHODPR(NavigationMesh, SetAgentHeight, (float), void), asCALL_THISCALL);
    // void NavigationMesh::SetAgentMaxClimb(float maxClimb) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetAgentMaxClimb(float)", asMETHODPR(NavigationMesh, SetAgentMaxClimb, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_agentMaxClimb(float)", asMETHODPR(NavigationMesh, SetAgentMaxClimb, (float), void), asCALL_THISCALL);
    // void NavigationMesh::SetAgentMaxSlope(float maxSlope) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetAgentMaxSlope(float)", asMETHODPR(NavigationMesh, SetAgentMaxSlope, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_agentMaxSlope(float)", asMETHODPR(NavigationMesh, SetAgentMaxSlope, (float), void), asCALL_THISCALL);
    // void NavigationMesh::SetAgentRadius(float radius) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetAgentRadius(float)", asMETHODPR(NavigationMesh, SetAgentRadius, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_agentRadius(float)", asMETHODPR(NavigationMesh, SetAgentRadius, (float), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetAnimationEnabled(bool)", asMETHODPR(NavigationMesh, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_animationEnabled(bool)", asMETHODPR(NavigationMesh, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetAnimationTime(float)", asMETHODPR(NavigationMesh, SetAnimationTime, (float), void), asCALL_THISCALL);
    // void NavigationMesh::SetAreaCost(unsigned areaID, float cost) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetAreaCost(uint, float)", asMETHODPR(NavigationMesh, SetAreaCost, (unsigned, float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(NavigationMesh, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "bool set_attributes(uint, const Variant&in)", asMETHODPR(NavigationMesh, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(NavigationMesh, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(NavigationMesh, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(NavigationMesh, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(NavigationMesh, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(NavigationMesh, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetBlockEvents(bool)", asMETHODPR(NavigationMesh, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void NavigationMesh::SetCellHeight(float height) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetCellHeight(float)", asMETHODPR(NavigationMesh, SetCellHeight, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_cellHeight(float)", asMETHODPR(NavigationMesh, SetCellHeight, (float), void), asCALL_THISCALL);
    // void NavigationMesh::SetCellSize(float size) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetCellSize(float)", asMETHODPR(NavigationMesh, SetCellSize, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_cellSize(float)", asMETHODPR(NavigationMesh, SetCellSize, (float), void), asCALL_THISCALL);
    // void NavigationMesh::SetDetailSampleDistance(float distance) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetDetailSampleDistance(float)", asMETHODPR(NavigationMesh, SetDetailSampleDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_detailSampleDistance(float)", asMETHODPR(NavigationMesh, SetDetailSampleDistance, (float), void), asCALL_THISCALL);
    // void NavigationMesh::SetDetailSampleMaxError(float error) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetDetailSampleMaxError(float)", asMETHODPR(NavigationMesh, SetDetailSampleMaxError, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_detailSampleMaxError(float)", asMETHODPR(NavigationMesh, SetDetailSampleMaxError, (float), void), asCALL_THISCALL);
    // void NavigationMesh::SetDrawNavAreas(bool enable) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetDrawNavAreas(bool)", asMETHODPR(NavigationMesh, SetDrawNavAreas, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_drawNavAreas(bool)", asMETHODPR(NavigationMesh, SetDrawNavAreas, (bool), void), asCALL_THISCALL);
    // void NavigationMesh::SetDrawOffMeshConnections(bool enable) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetDrawOffMeshConnections(bool)", asMETHODPR(NavigationMesh, SetDrawOffMeshConnections, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_drawOffMeshConnections(bool)", asMETHODPR(NavigationMesh, SetDrawOffMeshConnections, (bool), void), asCALL_THISCALL);
    // void NavigationMesh::SetEdgeMaxError(float error) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetEdgeMaxError(float)", asMETHODPR(NavigationMesh, SetEdgeMaxError, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_edgeMaxError(float)", asMETHODPR(NavigationMesh, SetEdgeMaxError, (float), void), asCALL_THISCALL);
    // void NavigationMesh::SetEdgeMaxLength(float length) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetEdgeMaxLength(float)", asMETHODPR(NavigationMesh, SetEdgeMaxLength, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_edgeMaxLength(float)", asMETHODPR(NavigationMesh, SetEdgeMaxLength, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetEnabled(bool)", asMETHODPR(NavigationMesh, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_enabled(bool)", asMETHODPR(NavigationMesh, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(NavigationMesh, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(NavigationMesh, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetInstanceDefault(bool)", asMETHODPR(NavigationMesh, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(NavigationMesh, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void NavigationMesh::SetMeshName(const String& newName) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetMeshName(const String&in)", asMETHODPR(NavigationMesh, SetMeshName, (const String&), void), asCALL_THISCALL);
    // virtual void NavigationMesh::SetNavigationDataAttr(const PODVector<unsigned char>& value) | File: ../Navigation/NavigationMesh.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(NavigationMesh, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(NavigationMesh, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(NavigationMesh, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void NavigationMesh::SetPadding(const Vector3& padding) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetPadding(const Vector3&in)", asMETHODPR(NavigationMesh, SetPadding, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_padding(const Vector3&in)", asMETHODPR(NavigationMesh, SetPadding, (const Vector3&), void), asCALL_THISCALL);
    // void NavigationMesh::SetPartitionType(NavmeshPartitionType partitionType) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetPartitionType(NavmeshPartitionType)", asMETHODPR(NavigationMesh, SetPartitionType, (NavmeshPartitionType), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_partitionType(NavmeshPartitionType)", asMETHODPR(NavigationMesh, SetPartitionType, (NavmeshPartitionType), void), asCALL_THISCALL);
    // void NavigationMesh::SetRegionMergeSize(float size) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetRegionMergeSize(float)", asMETHODPR(NavigationMesh, SetRegionMergeSize, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_regionMergeSize(float)", asMETHODPR(NavigationMesh, SetRegionMergeSize, (float), void), asCALL_THISCALL);
    // void NavigationMesh::SetRegionMinSize(float size) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetRegionMinSize(float)", asMETHODPR(NavigationMesh, SetRegionMinSize, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_regionMinSize(float)", asMETHODPR(NavigationMesh, SetRegionMinSize, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetTemporary(bool)", asMETHODPR(NavigationMesh, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_temporary(bool)", asMETHODPR(NavigationMesh, SetTemporary, (bool), void), asCALL_THISCALL);
    // void NavigationMesh::SetTileSize(int size) | File: ../Navigation/NavigationMesh.h
    engine->RegisterObjectMethod("NavigationMesh", "void SetTileSize(int)", asMETHODPR(NavigationMesh, SetTileSize, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_tileSize(int)", asMETHODPR(NavigationMesh, SetTileSize, (int), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "void UnsubscribeFromAllEvents()", asMETHODPR(NavigationMesh, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(NavigationMesh_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(NavigationMesh, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(NavigationMesh, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NavigationMesh", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(NavigationMesh, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("NavigationMesh", "int WeakRefs() const", asMETHODPR(NavigationMesh, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "int get_weakRefs() const", asMETHODPR(NavigationMesh, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(NavigationMesh, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(NavigationMesh, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NavigationMesh", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(NavigationMesh, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("Network", asBEHAVE_ADDREF, "void f()", asMETHODPR(Network, AddRef, (), void), asCALL_THISCALL);
    // void Network::AttemptNATPunchtrough(const String& guid, Scene* scene, const VariantMap& identity=Variant::emptyVariantMap) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void AttemptNATPunchtrough(const String&in, Scene@+, const VariantMap&in = VariantMap())", asMETHODPR(Network, AttemptNATPunchtrough, (const String&, Scene*, const VariantMap&), void), asCALL_THISCALL);
    // void Network::BanAddress(const String& address) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void BanAddress(const String&in)", asMETHODPR(Network, BanAddress, (const String&), void), asCALL_THISCALL);
    // void Network::BroadcastMessage(int msgID, bool reliable, bool inOrder, const VectorBuffer& msg, unsigned contentID=0) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void BroadcastMessage(int, bool, bool, const VectorBuffer&in, uint = 0)", asMETHODPR(Network, BroadcastMessage, (int, bool, bool, const VectorBuffer&, unsigned), void), asCALL_THISCALL);
    // void Network::BroadcastMessage(int msgID, bool reliable, bool inOrder, const unsigned char* data, unsigned numBytes, unsigned contentID=0) | File: ../Network/Network.h
    // Error: type "const unsigned char*" can not automatically bind
    // void Network::BroadcastRemoteEvent(StringHash eventType, bool inOrder, const VariantMap& eventData=Variant::emptyVariantMap) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void BroadcastRemoteEvent(StringHash, bool, const VariantMap&in = VariantMap())", asMETHODPR(Network, BroadcastRemoteEvent, (StringHash, bool, const VariantMap&), void), asCALL_THISCALL);
    // void Network::BroadcastRemoteEvent(Scene* scene, StringHash eventType, bool inOrder, const VariantMap& eventData=Variant::emptyVariantMap) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void BroadcastRemoteEvent(Scene@+, StringHash, bool, const VariantMap&in = VariantMap())", asMETHODPR(Network, BroadcastRemoteEvent, (Scene*, StringHash, bool, const VariantMap&), void), asCALL_THISCALL);
    // void Network::BroadcastRemoteEvent(Node* node, StringHash eventType, bool inOrder, const VariantMap& eventData=Variant::emptyVariantMap) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void BroadcastRemoteEvent(Node@+, StringHash, bool, const VariantMap&in = VariantMap())", asMETHODPR(Network, BroadcastRemoteEvent, (Node*, StringHash, bool, const VariantMap&), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool Network::CheckRemoteEvent(StringHash eventType) const | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "bool CheckRemoteEvent(StringHash) const", asMETHODPR(Network, CheckRemoteEvent, (StringHash) const, bool), asCALL_THISCALL);
    // void Network::ClientDisconnected(const SLNet::AddressOrGUID& connection) | File: ../Network/Network.h
    // Error: type "const SLNet::AddressOrGUID&" can not automatically bind
    // bool Network::Connect(const String& address, unsigned short port, Scene* scene, const VariantMap& identity=Variant::emptyVariantMap) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "bool Connect(const String&in, uint16, Scene@+, const VariantMap&in = VariantMap())", asMETHODPR(Network, Connect, (const String&, unsigned short, Scene*, const VariantMap&), bool), asCALL_THISCALL);
    // void Network::Disconnect(int waitMSec=0) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void Disconnect(int = 0)", asMETHODPR(Network, Disconnect, (int), void), asCALL_THISCALL);
    // void Network::DiscoverHosts(unsigned port) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void DiscoverHosts(uint)", asMETHODPR(Network, DiscoverHosts, (unsigned), void), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "bool GetBlockEvents() const", asMETHODPR(Network, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "const String& GetCategory() const", asMETHODPR(Network, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "const String& get_category() const", asMETHODPR(Network, GetCategory, () const, const String&), asCALL_THISCALL);
    // Vector<SharedPtr<Connection>> Network::GetClientConnections() const | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "Array<Connection@>@ GetClientConnections() const", asFUNCTION(Network_GetClientConnections_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Network", "Array<Connection@>@ get_clientConnections() const", asFUNCTION(Network_GetClientConnections_void), asCALL_CDECL_OBJFIRST);
    // Connection* Network::GetConnection(const SLNet::AddressOrGUID& connection) const | File: ../Network/Network.h
    // Error: type "const SLNet::AddressOrGUID&" can not automatically bind
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "VariantMap& GetEventDataMap() const", asMETHODPR(Network, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "Object@+ GetEventSender() const", asMETHODPR(Network, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Network, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Network, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "const VariantMap& GetGlobalVars() const", asMETHODPR(Network, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "const VariantMap& get_globalVars() const", asMETHODPR(Network, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // const String& Network::GetGUID() const | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "const String& GetGUID() const", asMETHODPR(Network, GetGUID, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "const String& get_guid() const", asMETHODPR(Network, GetGUID, () const, const String&), asCALL_THISCALL);
    // const String& Network::GetPackageCacheDir() const | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "const String& GetPackageCacheDir() const", asMETHODPR(Network, GetPackageCacheDir, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "const String& get_packageCacheDir() const", asMETHODPR(Network, GetPackageCacheDir, () const, const String&), asCALL_THISCALL);
    // Connection* Network::GetServerConnection() const | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "Connection@+ GetServerConnection() const", asMETHODPR(Network, GetServerConnection, () const, Connection*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "Connection@+ get_serverConnection() const", asMETHODPR(Network, GetServerConnection, () const, Connection*), asCALL_THISCALL);
    // int Network::GetSimulatedLatency() const | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "int GetSimulatedLatency() const", asMETHODPR(Network, GetSimulatedLatency, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "int get_simulatedLatency() const", asMETHODPR(Network, GetSimulatedLatency, () const, int), asCALL_THISCALL);
    // float Network::GetSimulatedPacketLoss() const | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "float GetSimulatedPacketLoss() const", asMETHODPR(Network, GetSimulatedPacketLoss, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "float get_simulatedPacketLoss() const", asMETHODPR(Network, GetSimulatedPacketLoss, () const, float), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Network, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "StringHash GetType() const", asMETHODPR(Network, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "StringHash get_type() const", asMETHODPR(Network, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "const String& GetTypeName() const", asMETHODPR(Network, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "const String& get_typeName() const", asMETHODPR(Network, GetTypeName, () const, const String&), asCALL_THISCALL);
    // int Network::GetUpdateFps() const | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "int GetUpdateFps() const", asMETHODPR(Network, GetUpdateFps, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "int get_updateFps() const", asMETHODPR(Network, GetUpdateFps, () const, int), asCALL_THISCALL);
    // void Network::HandleMessage(const SLNet::AddressOrGUID& source, int packetID, int msgID, const char* data, size_t numBytes) | File: ../Network/Network.h
    // Error: type "const SLNet::AddressOrGUID&" can not automatically bind
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "bool HasEventHandlers() const", asMETHODPR(Network, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Network, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Network, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "bool IsInstanceOf(StringHash) const", asMETHODPR(Network, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Network::IsServerRunning() const | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "bool IsServerRunning() const", asMETHODPR(Network, IsServerRunning, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "bool get_serverRunning() const", asMETHODPR(Network, IsServerRunning, () const, bool), asCALL_THISCALL);
    // SharedPtr<HttpRequest> Network::MakeHttpRequest(const String& url, const String& verb=String::EMPTY, const Vector<String>& headers=Vector<String>(), const String& postData=String::EMPTY) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "HttpRequest@+ MakeHttpRequest(const String&in, const String&in = String::EMPTY, Array<String>@+ = null, const String&in = String::EMPTY)", asFUNCTION(Network_MakeHttpRequest_String_String_VectorString_String), asCALL_CDECL_OBJFIRST);
    // explicit Network::Network(Context* context) | File: ../Network/Network.h
    engine->RegisterObjectBehaviour("Network", asBEHAVE_FACTORY, "Network@+ f()", asFUNCTION(Network_Network_Context), asCALL_CDECL);
    // void Network::NewConnectionEstablished(const SLNet::AddressOrGUID& connection) | File: ../Network/Network.h
    // Error: type "const SLNet::AddressOrGUID&" can not automatically bind
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Network, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // void Network::PostUpdate(float timeStep) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void PostUpdate(float)", asMETHODPR(Network, PostUpdate, (float), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Network", "int Refs() const", asMETHODPR(Network, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "int get_refs() const", asMETHODPR(Network, Refs, () const, int), asCALL_THISCALL);
    // void Network::RegisterRemoteEvent(StringHash eventType) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void RegisterRemoteEvent(StringHash)", asMETHODPR(Network, RegisterRemoteEvent, (StringHash), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Network", asBEHAVE_RELEASE, "void f()", asMETHODPR(Network, ReleaseRef, (), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "void SendEvent(StringHash)", asMETHODPR(Network, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Network, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Network::SendPackageToClients(Scene* scene, PackageFile* package) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void SendPackageToClients(Scene@+, PackageFile@+)", asMETHODPR(Network, SendPackageToClients, (Scene*, PackageFile*), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "void SetBlockEvents(bool)", asMETHODPR(Network, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Network::SetDiscoveryBeacon(const VariantMap& data) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void SetDiscoveryBeacon(const VariantMap&in)", asMETHODPR(Network, SetDiscoveryBeacon, (const VariantMap&), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Network, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Network, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Network::SetNATServerInfo(const String& address, unsigned short port) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void SetNATServerInfo(const String&in, uint16)", asMETHODPR(Network, SetNATServerInfo, (const String&, unsigned short), void), asCALL_THISCALL);
    // void Network::SetPackageCacheDir(const String& path) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void SetPackageCacheDir(const String&in)", asMETHODPR(Network, SetPackageCacheDir, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void set_packageCacheDir(const String&in)", asMETHODPR(Network, SetPackageCacheDir, (const String&), void), asCALL_THISCALL);
    // void Network::SetPassword(const String& password) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void SetPassword(const String&in)", asMETHODPR(Network, SetPassword, (const String&), void), asCALL_THISCALL);
    // void Network::SetSimulatedLatency(int ms) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void SetSimulatedLatency(int)", asMETHODPR(Network, SetSimulatedLatency, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void set_simulatedLatency(int)", asMETHODPR(Network, SetSimulatedLatency, (int), void), asCALL_THISCALL);
    // void Network::SetSimulatedPacketLoss(float probability) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void SetSimulatedPacketLoss(float)", asMETHODPR(Network, SetSimulatedPacketLoss, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void set_simulatedPacketLoss(float)", asMETHODPR(Network, SetSimulatedPacketLoss, (float), void), asCALL_THISCALL);
    // void Network::SetUpdateFps(int fps) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void SetUpdateFps(int)", asMETHODPR(Network, SetUpdateFps, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "void set_updateFps(int)", asMETHODPR(Network, SetUpdateFps, (int), void), asCALL_THISCALL);
    // void Network::StartNATClient() | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void StartNATClient()", asMETHODPR(Network, StartNATClient, (), void), asCALL_THISCALL);
    // bool Network::StartServer(unsigned short port, unsigned int maxConnections=128) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "bool StartServer(uint16, uint = 128)", asMETHODPR(Network, StartServer, (unsigned short, unsigned int), bool), asCALL_THISCALL);
    // void Network::StopServer() | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void StopServer()", asMETHODPR(Network, StopServer, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Network::UnregisterAllRemoteEvents() | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void UnregisterAllRemoteEvents()", asMETHODPR(Network, UnregisterAllRemoteEvents, (), void), asCALL_THISCALL);
    // void Network::UnregisterRemoteEvent(StringHash eventType) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void UnregisterRemoteEvent(StringHash)", asMETHODPR(Network, UnregisterRemoteEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "void UnsubscribeFromAllEvents()", asMETHODPR(Network, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Network_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Network, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Network, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Network", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Network, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void Network::Update(float timeStep) | File: ../Network/Network.h
    engine->RegisterObjectMethod("Network", "void Update(float)", asMETHODPR(Network, Update, (float), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Network", "int WeakRefs() const", asMETHODPR(Network, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Network", "int get_weakRefs() const", asMETHODPR(Network, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("NetworkPriority", asBEHAVE_ADDREF, "void f()", asMETHODPR(NetworkPriority, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "void AllocateNetworkState()", asMETHODPR(NetworkPriority, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "void ApplyAttributes()", asMETHODPR(NetworkPriority, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool NetworkPriority::CheckUpdate(float distance, float& accumulator) | File: ../Network/NetworkPriority.h
    engine->RegisterObjectMethod("NetworkPriority", "bool CheckUpdate(float, float&)", asMETHODPR(NetworkPriority, CheckUpdate, (float, float&), bool), asCALL_THISCALL);
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(NetworkPriority, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool NetworkPriority::GetAlwaysUpdateOwner() const | File: ../Network/NetworkPriority.h
    engine->RegisterObjectMethod("NetworkPriority", "bool GetAlwaysUpdateOwner() const", asMETHODPR(NetworkPriority, GetAlwaysUpdateOwner, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "bool get_alwaysUpdateOwner() const", asMETHODPR(NetworkPriority, GetAlwaysUpdateOwner, () const, bool), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "bool GetAnimationEnabled() const", asMETHODPR(NetworkPriority, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "bool get_animationEnabled() const", asMETHODPR(NetworkPriority, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "Variant GetAttribute(uint) const", asMETHODPR(NetworkPriority, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "Variant get_attributes(uint) const", asMETHODPR(NetworkPriority, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "Variant GetAttribute(const String&in) const", asMETHODPR(NetworkPriority, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(NetworkPriority, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(NetworkPriority, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(NetworkPriority, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(NetworkPriority, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "Variant GetAttributeDefault(uint) const", asMETHODPR(NetworkPriority, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "Variant get_attributeDefaults(uint) const", asMETHODPR(NetworkPriority, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(NetworkPriority, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // float NetworkPriority::GetBasePriority() const | File: ../Network/NetworkPriority.h
    engine->RegisterObjectMethod("NetworkPriority", "float GetBasePriority() const", asMETHODPR(NetworkPriority, GetBasePriority, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "float get_basePriority() const", asMETHODPR(NetworkPriority, GetBasePriority, () const, float), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "bool GetBlockEvents() const", asMETHODPR(NetworkPriority, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "const String& GetCategory() const", asMETHODPR(NetworkPriority, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "const String& get_category() const", asMETHODPR(NetworkPriority, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "Component@+ GetComponent(StringHash) const", asMETHODPR(NetworkPriority, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    // float NetworkPriority::GetDistanceFactor() const | File: ../Network/NetworkPriority.h
    engine->RegisterObjectMethod("NetworkPriority", "float GetDistanceFactor() const", asMETHODPR(NetworkPriority, GetDistanceFactor, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "float get_distanceFactor() const", asMETHODPR(NetworkPriority, GetDistanceFactor, () const, float), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "VariantMap& GetEventDataMap() const", asMETHODPR(NetworkPriority, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "Object@+ GetEventSender() const", asMETHODPR(NetworkPriority, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(NetworkPriority, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "const Variant& get_globalVar(StringHash) const", asMETHODPR(NetworkPriority, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "const VariantMap& GetGlobalVars() const", asMETHODPR(NetworkPriority, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "const VariantMap& get_globalVars() const", asMETHODPR(NetworkPriority, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "uint GetID() const", asMETHODPR(NetworkPriority, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "uint get_id() const", asMETHODPR(NetworkPriority, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(NetworkPriority, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // float NetworkPriority::GetMinPriority() const | File: ../Network/NetworkPriority.h
    engine->RegisterObjectMethod("NetworkPriority", "float GetMinPriority() const", asMETHODPR(NetworkPriority, GetMinPriority, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "float get_minPriority() const", asMETHODPR(NetworkPriority, GetMinPriority, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "Node@+ GetNode() const", asMETHODPR(NetworkPriority, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "Node@+ get_node() const", asMETHODPR(NetworkPriority, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "uint GetNumAttributes() const", asMETHODPR(NetworkPriority, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "uint get_numAttributes() const", asMETHODPR(NetworkPriority, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "uint GetNumNetworkAttributes() const", asMETHODPR(NetworkPriority, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(NetworkPriority, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(NetworkPriority, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(NetworkPriority, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "Scene@+ GetScene() const", asMETHODPR(NetworkPriority, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(NetworkPriority, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "StringHash GetType() const", asMETHODPR(NetworkPriority, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "StringHash get_type() const", asMETHODPR(NetworkPriority, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "const String& GetTypeName() const", asMETHODPR(NetworkPriority, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "const String& get_typeName() const", asMETHODPR(NetworkPriority, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "bool HasEventHandlers() const", asMETHODPR(NetworkPriority, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(NetworkPriority, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(NetworkPriority, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "bool IsEnabled() const", asMETHODPR(NetworkPriority, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "bool get_enabled() const", asMETHODPR(NetworkPriority, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "bool IsEnabledEffective() const", asMETHODPR(NetworkPriority, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "bool get_enabledEffective() const", asMETHODPR(NetworkPriority, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "bool IsInstanceOf(StringHash) const", asMETHODPR(NetworkPriority, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "bool IsReplicated() const", asMETHODPR(NetworkPriority, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "bool get_replicated() const", asMETHODPR(NetworkPriority, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "bool IsTemporary() const", asMETHODPR(NetworkPriority, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "bool get_temporary() const", asMETHODPR(NetworkPriority, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "bool Load(Deserializer&)", asMETHODPR(NetworkPriority, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "bool LoadJSON(const JSONValue&in)", asMETHODPR(NetworkPriority, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "bool LoadXML(const XMLElement&in)", asMETHODPR(NetworkPriority, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "void MarkNetworkUpdate()", asMETHODPR(NetworkPriority, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // explicit NetworkPriority::NetworkPriority(Context* context) | File: ../Network/NetworkPriority.h
    engine->RegisterObjectBehaviour("NetworkPriority", asBEHAVE_FACTORY, "NetworkPriority@+ f()", asFUNCTION(NetworkPriority_NetworkPriority_Context), asCALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(NetworkPriority, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(NetworkPriority, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(NetworkPriority, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "void OnSetEnabled()", asMETHODPR(NetworkPriority, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "void PrepareNetworkUpdate()", asMETHODPR(NetworkPriority, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(NetworkPriority, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(NetworkPriority, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("NetworkPriority", "int Refs() const", asMETHODPR(NetworkPriority, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "int get_refs() const", asMETHODPR(NetworkPriority, Refs, () const, int), asCALL_THISCALL);
    // static void NetworkPriority::RegisterObject(Context* context) | File: ../Network/NetworkPriority.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("NetworkPriority", asBEHAVE_RELEASE, "void f()", asMETHODPR(NetworkPriority, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "void Remove()", asMETHODPR(NetworkPriority, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(NetworkPriority, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "void RemoveInstanceDefault()", asMETHODPR(NetworkPriority, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "void RemoveObjectAnimation()", asMETHODPR(NetworkPriority, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "void ResetToDefault()", asMETHODPR(NetworkPriority, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "bool Save(Serializer&) const", asMETHODPR(NetworkPriority, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "bool SaveDefaultAttributes() const", asMETHODPR(NetworkPriority, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "bool SaveJSON(JSONValue&) const", asMETHODPR(NetworkPriority, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "bool SaveXML(XMLElement&) const", asMETHODPR(NetworkPriority, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "void SendEvent(StringHash)", asMETHODPR(NetworkPriority, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(NetworkPriority, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void NetworkPriority::SetAlwaysUpdateOwner(bool enable) | File: ../Network/NetworkPriority.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetAlwaysUpdateOwner(bool)", asMETHODPR(NetworkPriority, SetAlwaysUpdateOwner, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "void set_alwaysUpdateOwner(bool)", asMETHODPR(NetworkPriority, SetAlwaysUpdateOwner, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetAnimationEnabled(bool)", asMETHODPR(NetworkPriority, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "void set_animationEnabled(bool)", asMETHODPR(NetworkPriority, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetAnimationTime(float)", asMETHODPR(NetworkPriority, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(NetworkPriority, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "bool set_attributes(uint, const Variant&in)", asMETHODPR(NetworkPriority, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(NetworkPriority, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(NetworkPriority, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(NetworkPriority, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(NetworkPriority, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(NetworkPriority, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void NetworkPriority::SetBasePriority(float priority) | File: ../Network/NetworkPriority.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetBasePriority(float)", asMETHODPR(NetworkPriority, SetBasePriority, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "void set_basePriority(float)", asMETHODPR(NetworkPriority, SetBasePriority, (float), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetBlockEvents(bool)", asMETHODPR(NetworkPriority, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void NetworkPriority::SetDistanceFactor(float factor) | File: ../Network/NetworkPriority.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetDistanceFactor(float)", asMETHODPR(NetworkPriority, SetDistanceFactor, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "void set_distanceFactor(float)", asMETHODPR(NetworkPriority, SetDistanceFactor, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetEnabled(bool)", asMETHODPR(NetworkPriority, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "void set_enabled(bool)", asMETHODPR(NetworkPriority, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(NetworkPriority, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(NetworkPriority, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetInstanceDefault(bool)", asMETHODPR(NetworkPriority, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(NetworkPriority, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void NetworkPriority::SetMinPriority(float priority) | File: ../Network/NetworkPriority.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetMinPriority(float)", asMETHODPR(NetworkPriority, SetMinPriority, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "void set_minPriority(float)", asMETHODPR(NetworkPriority, SetMinPriority, (float), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(NetworkPriority, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(NetworkPriority, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(NetworkPriority, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "void SetTemporary(bool)", asMETHODPR(NetworkPriority, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "void set_temporary(bool)", asMETHODPR(NetworkPriority, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "void UnsubscribeFromAllEvents()", asMETHODPR(NetworkPriority, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(NetworkPriority_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(NetworkPriority, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(NetworkPriority, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("NetworkPriority", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(NetworkPriority, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("NetworkPriority", "int WeakRefs() const", asMETHODPR(NetworkPriority, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("NetworkPriority", "int get_weakRefs() const", asMETHODPR(NetworkPriority, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(NetworkPriority, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(NetworkPriority, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("NetworkPriority", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(NetworkPriority, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Node", "void AddChild(Node@+, uint = M_MAX_UNSIGNED)", asMETHODPR(Node, AddChild, (Node*, unsigned), void), asCALL_THISCALL);
    // void Node::AddComponent(Component* component, unsigned id, CreateMode mode) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void AddComponent(Component@+, uint, CreateMode)", asMETHODPR(Node, AddComponent, (Component*, unsigned, CreateMode), void), asCALL_THISCALL);
    // void Node::AddListener(Component* component) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void AddListener(Component@+)", asMETHODPR(Node, AddListener, (Component*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Node", asBEHAVE_ADDREF, "void f()", asMETHODPR(Node, AddRef, (), void), asCALL_THISCALL);
    // virtual void Node::AddReplicationState(NodeReplicationState* state) | File: ../Scene/Node.h
    // Error: type "NodeReplicationState*" can not automatically bind
    // void Node::AddTag(const String& tag) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void AddTag(const String&in)", asMETHODPR(Node, AddTag, (const String&), void), asCALL_THISCALL);
    // void Node::AddTags(const String& tags, char separator=';') | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void AddTags(const String&in, int8 = ';')", asMETHODPR(Node, AddTags, (const String&, char), void), asCALL_THISCALL);
    // void Node::AddTags(const StringVector& tags) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void AddTags(Array<String>@+)", asFUNCTION(Node_AddTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "void AllocateNetworkState()", asMETHODPR(Node, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void Node::ApplyAttributes() override | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void ApplyAttributes()", asMETHODPR(Node, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Node::CleanupConnection(Connection* connection) | File: ../Scene/Node.h
    // Not registered because have @manualbind mark
    // Node* Node::Clone(CreateMode mode=REPLICATED) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Node@+ Clone(CreateMode = REPLICATED)", asMETHODPR(Node, Clone, (CreateMode), Node*), asCALL_THISCALL);
    // Component* Node::CloneComponent(Component* component, unsigned id=0) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Component@+ CloneComponent(Component@+, uint = 0)", asMETHODPR(Node, CloneComponent, (Component*, unsigned), Component*), asCALL_THISCALL);
    // Component* Node::CloneComponent(Component* component, CreateMode mode, unsigned id=0) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Component@+ CloneComponent(Component@+, CreateMode, uint = 0)", asMETHODPR(Node, CloneComponent, (Component*, CreateMode, unsigned), Component*), asCALL_THISCALL);
    // Node* Node::CreateChild(const String& name=String::EMPTY, CreateMode mode=REPLICATED, unsigned id=0, bool temporary=false) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Node@+ CreateChild(const String&in = String::EMPTY, CreateMode = REPLICATED, uint = 0, bool = false)", asMETHODPR(Node, CreateChild, (const String&, CreateMode, unsigned, bool), Node*), asCALL_THISCALL);
    // Node* Node::CreateChild(unsigned id, CreateMode mode, bool temporary=false) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Node@+ CreateChild(uint, CreateMode, bool = false)", asMETHODPR(Node, CreateChild, (unsigned, CreateMode, bool), Node*), asCALL_THISCALL);
    // Component* Node::CreateComponent(StringHash type, CreateMode mode=REPLICATED, unsigned id=0) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Component@+ CreateComponent(StringHash, CreateMode = REPLICATED, uint = 0)", asMETHODPR(Node, CreateComponent, (StringHash, CreateMode, unsigned), Component*), asCALL_THISCALL);
    // template<class T> T*  Node::CreateComponent(CreateMode mode=REPLICATED, unsigned id=0) | File: ../Scene/Node.h
    // Not registered because template
    // Node* Node::CreateTemporaryChild(const String& name=String::EMPTY, CreateMode mode=REPLICATED, unsigned id=0) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Node@+ CreateTemporaryChild(const String&in = String::EMPTY, CreateMode = REPLICATED, uint = 0)", asMETHODPR(Node, CreateTemporaryChild, (const String&, CreateMode, unsigned), Node*), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "bool GetAnimationEnabled() const", asMETHODPR(Node, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "bool get_animationEnabled() const", asMETHODPR(Node, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "Variant GetAttribute(uint) const", asMETHODPR(Node, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Variant get_attributes(uint) const", asMETHODPR(Node, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "Variant GetAttribute(const String&in) const", asMETHODPR(Node, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(Node, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(Node, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(Node, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(Node, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "Variant GetAttributeDefault(uint) const", asMETHODPR(Node, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Variant get_attributeDefaults(uint) const", asMETHODPR(Node, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Node, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "bool GetBlockEvents() const", asMETHODPR(Node, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "const String& GetCategory() const", asMETHODPR(Node, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "const String& get_category() const", asMETHODPR(Node, GetCategory, () const, const String&), asCALL_THISCALL);
    // Node* Node::GetChild(unsigned index) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Node@+ GetChild(uint) const", asMETHODPR(Node, GetChild, (unsigned) const, Node*), asCALL_THISCALL);
    // Node* Node::GetChild(const String& name, bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Node@+ GetChild(const String&in, bool = false) const", asMETHODPR(Node, GetChild, (const String&, bool) const, Node*), asCALL_THISCALL);
    // Node* Node::GetChild(const char* name, bool recursive=false) const | File: ../Scene/Node.h
    // Error: type "const char*" can not automatically bind
    // Node* Node::GetChild(StringHash nameHash, bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Node@+ GetChild(StringHash, bool = false) const", asMETHODPR(Node, GetChild, (StringHash, bool) const, Node*), asCALL_THISCALL);
    // const Vector<SharedPtr<Node>>& Node::GetChildren() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Array<Node@>@ GetChildren() const", asFUNCTION(Node_GetChildren_void), asCALL_CDECL_OBJFIRST);
    // void Node::GetChildren(PODVector<Node*>& dest, bool recursive=false) const | File: ../Scene/Node.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // PODVector<Node*> Node::GetChildren(bool recursive) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Array<Node@>@ GetChildren(bool) const", asFUNCTION(Node_GetChildren_bool), asCALL_CDECL_OBJFIRST);
    // void Node::GetChildrenWithComponent(PODVector<Node*>& dest, StringHash type, bool recursive=false) const | File: ../Scene/Node.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // PODVector<Node*> Node::GetChildrenWithComponent(StringHash type, bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Array<Node@>@ GetChildrenWithComponent(StringHash, bool = false) const", asFUNCTION(Node_GetChildrenWithComponent_StringHash_bool), asCALL_CDECL_OBJFIRST);
    // template<class T> void Node::GetChildrenWithComponent(PODVector<Node*>& dest, bool recursive=false) const | File: ../Scene/Node.h
    // Not registered because template
    // void Node::GetChildrenWithTag(PODVector<Node*>& dest, const String& tag, bool recursive=false) const | File: ../Scene/Node.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // PODVector<Node*> Node::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Array<Node@>@ GetChildrenWithTag(const String&in, bool = false) const", asFUNCTION(Node_GetChildrenWithTag_String_bool), asCALL_CDECL_OBJFIRST);
    // Component* Node::GetComponent(StringHash type, bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Component@+ GetComponent(StringHash, bool = false) const", asMETHODPR(Node, GetComponent, (StringHash, bool) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Node::GetComponent(bool recursive=false) const | File: ../Scene/Node.h
    // Not registered because template
    // const Vector<SharedPtr<Component>>& Node::GetComponents() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Array<Component@>@ GetComponents() const", asFUNCTION(Node_GetComponents_void), asCALL_CDECL_OBJFIRST);
    // void Node::GetComponents(PODVector<Component*>& dest, StringHash type, bool recursive=false) const | File: ../Scene/Node.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Node::GetComponents(PODVector<T*>& dest, bool recursive=false) const | File: ../Scene/Node.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // const PODVector<Node*>& Node::GetDependencyNodes() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Array<Node@>@ GetDependencyNodes() const", asFUNCTION(Node_GetDependencyNodes_void), asCALL_CDECL_OBJFIRST);
    // template<class T> T*  Node::GetDerivedComponent(bool recursive=false) const | File: ../Scene/Node.h
    // Not registered because template
    // template<class T> void Node::GetDerivedComponents(PODVector<T*>& dest, bool recursive=false, bool clearVector=true) const | File: ../Scene/Node.h
    // Not registered because template
    // Vector3 Node::GetDirection() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 GetDirection() const", asMETHODPR(Node, GetDirection, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector3 get_direction() const", asMETHODPR(Node, GetDirection, () const, Vector3), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "VariantMap& GetEventDataMap() const", asMETHODPR(Node, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "Object@+ GetEventSender() const", asMETHODPR(Node, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Node, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Node, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "const VariantMap& GetGlobalVars() const", asMETHODPR(Node, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "const VariantMap& get_globalVars() const", asMETHODPR(Node, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Node::GetID() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "uint GetID() const", asMETHODPR(Node, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "uint get_id() const", asMETHODPR(Node, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Node, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // const Vector<WeakPtr<Component>> Node::GetListeners() const | File: ../Scene/Node.h
    // Error: type "const Vector<WeakPtr<Component>>" can not automatically bind
    // const String& Node::GetName() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "const String& GetName() const", asMETHODPR(Node, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "const String& get_name() const", asMETHODPR(Node, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Node::GetNameHash() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "StringHash GetNameHash() const", asMETHODPR(Node, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // const PODVector<unsigned char>& Node::GetNetParentAttr() const | File: ../Scene/Node.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // const Vector3& Node::GetNetPositionAttr() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "const Vector3& GetNetPositionAttr() const", asMETHODPR(Node, GetNetPositionAttr, () const, const Vector3&), asCALL_THISCALL);
    // const PODVector<unsigned char>& Node::GetNetRotationAttr() const | File: ../Scene/Node.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "uint GetNumAttributes() const", asMETHODPR(Node, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "uint get_numAttributes() const", asMETHODPR(Node, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Node::GetNumChildren(bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "uint GetNumChildren(bool = false) const", asMETHODPR(Node, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    // unsigned Node::GetNumComponents() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "uint GetNumComponents() const", asMETHODPR(Node, GetNumComponents, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "uint get_numComponents() const", asMETHODPR(Node, GetNumComponents, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "uint GetNumNetworkAttributes() const", asMETHODPR(Node, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Node::GetNumNetworkComponents() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "uint GetNumNetworkComponents() const", asMETHODPR(Node, GetNumNetworkComponents, () const, unsigned), asCALL_THISCALL);
    // unsigned Node::GetNumPersistentChildren() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "uint GetNumPersistentChildren() const", asMETHODPR(Node, GetNumPersistentChildren, () const, unsigned), asCALL_THISCALL);
    // unsigned Node::GetNumPersistentComponents() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "uint GetNumPersistentComponents() const", asMETHODPR(Node, GetNumPersistentComponents, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(Node, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(Node, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(Node, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Component* Node::GetOrCreateComponent(StringHash type, CreateMode mode=REPLICATED, unsigned id=0) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Component@+ GetOrCreateComponent(StringHash, CreateMode = REPLICATED, uint = 0)", asMETHODPR(Node, GetOrCreateComponent, (StringHash, CreateMode, unsigned), Component*), asCALL_THISCALL);
    // template<class T> T*  Node::GetOrCreateComponent(CreateMode mode=REPLICATED, unsigned id=0) | File: ../Scene/Node.h
    // Not registered because template
    // Connection* Node::GetOwner() const | File: ../Scene/Node.h
    // Not registered because have @manualbind mark
    // Node* Node::GetParent() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Node@+ GetParent() const", asMETHODPR(Node, GetParent, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Node@+ get_parent() const", asMETHODPR(Node, GetParent, () const, Node*), asCALL_THISCALL);
    // Component* Node::GetParentComponent(StringHash type, bool fullTraversal=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Component@+ GetParentComponent(StringHash, bool = false) const", asMETHODPR(Node, GetParentComponent, (StringHash, bool) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Node::GetParentComponent(bool fullTraversal=false) const | File: ../Scene/Node.h
    // Not registered because template
    // template<class T> T*  Node::GetParentDerivedComponent(bool fullTraversal=false) const | File: ../Scene/Node.h
    // Not registered because template
    // const Vector3& Node::GetPosition() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "const Vector3& GetPosition() const", asMETHODPR(Node, GetPosition, () const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "const Vector3& get_position() const", asMETHODPR(Node, GetPosition, () const, const Vector3&), asCALL_THISCALL);
    // Vector2 Node::GetPosition2D() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector2 GetPosition2D() const", asMETHODPR(Node, GetPosition2D, () const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector2 get_position2D() const", asMETHODPR(Node, GetPosition2D, () const, Vector2), asCALL_THISCALL);
    // Vector3 Node::GetRight() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 GetRight() const", asMETHODPR(Node, GetRight, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector3 get_right() const", asMETHODPR(Node, GetRight, () const, Vector3), asCALL_THISCALL);
    // const Quaternion& Node::GetRotation() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "const Quaternion& GetRotation() const", asMETHODPR(Node, GetRotation, () const, const Quaternion&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "const Quaternion& get_rotation() const", asMETHODPR(Node, GetRotation, () const, const Quaternion&), asCALL_THISCALL);
    // float Node::GetRotation2D() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "float GetRotation2D() const", asMETHODPR(Node, GetRotation2D, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "float get_rotation2D() const", asMETHODPR(Node, GetRotation2D, () const, float), asCALL_THISCALL);
    // const Vector3& Node::GetScale() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "const Vector3& GetScale() const", asMETHODPR(Node, GetScale, () const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "const Vector3& get_scale() const", asMETHODPR(Node, GetScale, () const, const Vector3&), asCALL_THISCALL);
    // Vector2 Node::GetScale2D() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector2 GetScale2D() const", asMETHODPR(Node, GetScale2D, () const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector2 get_scale2D() const", asMETHODPR(Node, GetScale2D, () const, Vector2), asCALL_THISCALL);
    // Scene* Node::GetScene() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Scene@+ GetScene() const", asMETHODPR(Node, GetScene, () const, Scene*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Scene@+ get_scene() const", asMETHODPR(Node, GetScene, () const, Scene*), asCALL_THISCALL);
    // Vector3 Node::GetSignedWorldScale() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 GetSignedWorldScale() const", asMETHODPR(Node, GetSignedWorldScale, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector3 get_signedWorldScale() const", asMETHODPR(Node, GetSignedWorldScale, () const, Vector3), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Node, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& Node::GetTags() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Array<String>@ GetTags() const", asFUNCTION(Node_GetTags_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Node", "Array<String>@ get_tags() const", asFUNCTION(Node_GetTags_void), asCALL_CDECL_OBJFIRST);
    // Matrix3x4 Node::GetTransform() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Matrix3x4 GetTransform() const", asMETHODPR(Node, GetTransform, () const, Matrix3x4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Matrix3x4 get_transform() const", asMETHODPR(Node, GetTransform, () const, Matrix3x4), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "StringHash GetType() const", asMETHODPR(Node, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "StringHash get_type() const", asMETHODPR(Node, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "const String& GetTypeName() const", asMETHODPR(Node, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "const String& get_typeName() const", asMETHODPR(Node, GetTypeName, () const, const String&), asCALL_THISCALL);
    // Vector3 Node::GetUp() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 GetUp() const", asMETHODPR(Node, GetUp, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector3 get_up() const", asMETHODPR(Node, GetUp, () const, Vector3), asCALL_THISCALL);
    // const Variant& Node::GetVar(StringHash key) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "const Variant& GetVar(StringHash) const", asMETHODPR(Node, GetVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Node::GetVars() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "const VariantMap& GetVars() const", asMETHODPR(Node, GetVars, () const, const VariantMap&), asCALL_THISCALL);
    // Vector3 Node::GetWorldDirection() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 GetWorldDirection() const", asMETHODPR(Node, GetWorldDirection, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector3 get_worldDirection() const", asMETHODPR(Node, GetWorldDirection, () const, Vector3), asCALL_THISCALL);
    // Vector3 Node::GetWorldPosition() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 GetWorldPosition() const", asMETHODPR(Node, GetWorldPosition, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector3 get_worldPosition() const", asMETHODPR(Node, GetWorldPosition, () const, Vector3), asCALL_THISCALL);
    // Vector2 Node::GetWorldPosition2D() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector2 GetWorldPosition2D() const", asMETHODPR(Node, GetWorldPosition2D, () const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector2 get_worldPosition2D() const", asMETHODPR(Node, GetWorldPosition2D, () const, Vector2), asCALL_THISCALL);
    // Vector3 Node::GetWorldRight() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 GetWorldRight() const", asMETHODPR(Node, GetWorldRight, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector3 get_worldRight() const", asMETHODPR(Node, GetWorldRight, () const, Vector3), asCALL_THISCALL);
    // Quaternion Node::GetWorldRotation() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Quaternion GetWorldRotation() const", asMETHODPR(Node, GetWorldRotation, () const, Quaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Quaternion get_worldRotation() const", asMETHODPR(Node, GetWorldRotation, () const, Quaternion), asCALL_THISCALL);
    // float Node::GetWorldRotation2D() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "float GetWorldRotation2D() const", asMETHODPR(Node, GetWorldRotation2D, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "float get_worldRotation2D() const", asMETHODPR(Node, GetWorldRotation2D, () const, float), asCALL_THISCALL);
    // Vector3 Node::GetWorldScale() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 GetWorldScale() const", asMETHODPR(Node, GetWorldScale, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector3 get_worldScale() const", asMETHODPR(Node, GetWorldScale, () const, Vector3), asCALL_THISCALL);
    // Vector2 Node::GetWorldScale2D() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector2 GetWorldScale2D() const", asMETHODPR(Node, GetWorldScale2D, () const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector2 get_worldScale2D() const", asMETHODPR(Node, GetWorldScale2D, () const, Vector2), asCALL_THISCALL);
    // const Matrix3x4& Node::GetWorldTransform() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "const Matrix3x4& GetWorldTransform() const", asMETHODPR(Node, GetWorldTransform, () const, const Matrix3x4&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "const Matrix3x4& get_worldTransform() const", asMETHODPR(Node, GetWorldTransform, () const, const Matrix3x4&), asCALL_THISCALL);
    // Vector3 Node::GetWorldUp() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 GetWorldUp() const", asMETHODPR(Node, GetWorldUp, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "Vector3 get_worldUp() const", asMETHODPR(Node, GetWorldUp, () const, Vector3), asCALL_THISCALL);
    // bool Node::HasComponent(StringHash type) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool HasComponent(StringHash) const", asMETHODPR(Node, HasComponent, (StringHash) const, bool), asCALL_THISCALL);
    // template<class T> bool Node::HasComponent() const | File: ../Scene/Node.h
    // Not registered because template
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "bool HasEventHandlers() const", asMETHODPR(Node, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Node, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Node, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Node::HasTag(const String& tag) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool HasTag(const String&in) const", asMETHODPR(Node, HasTag, (const String&) const, bool), asCALL_THISCALL);
    // bool Node::IsChildOf(Node* node) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool IsChildOf(Node@+) const", asMETHODPR(Node, IsChildOf, (Node*) const, bool), asCALL_THISCALL);
    // bool Node::IsDirty() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool IsDirty() const", asMETHODPR(Node, IsDirty, () const, bool), asCALL_THISCALL);
    // bool Node::IsEnabled() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool IsEnabled() const", asMETHODPR(Node, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "bool get_enabled() const", asMETHODPR(Node, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Node::IsEnabledSelf() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool IsEnabledSelf() const", asMETHODPR(Node, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "bool get_enabledSelf() const", asMETHODPR(Node, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "bool IsInstanceOf(StringHash) const", asMETHODPR(Node, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Node::IsReplicated() const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool IsReplicated() const", asMETHODPR(Node, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "bool get_replicated() const", asMETHODPR(Node, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "bool IsTemporary() const", asMETHODPR(Node, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "bool get_temporary() const", asMETHODPR(Node, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool Node::Load(Deserializer& source) override | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool Load(Deserializer&)", asMETHODPR(Node, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Node::Load(Deserializer& source, SceneResolver& resolver, bool loadChildren=true, bool rewriteIDs=false, CreateMode mode=REPLICATED) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool Load(Deserializer&, SceneResolver&, bool = true, bool = false, CreateMode = REPLICATED)", asMETHODPR(Node, Load, (Deserializer&, SceneResolver&, bool, bool, CreateMode), bool), asCALL_THISCALL);
    // bool Node::LoadJSON(const JSONValue& source) override | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Node, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Node::LoadJSON(const JSONValue& source, SceneResolver& resolver, bool loadChildren=true, bool rewriteIDs=false, CreateMode mode=REPLICATED) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool LoadJSON(const JSONValue&in, SceneResolver&, bool = true, bool = false, CreateMode = REPLICATED)", asMETHODPR(Node, LoadJSON, (const JSONValue&, SceneResolver&, bool, bool, CreateMode), bool), asCALL_THISCALL);
    // bool Node::LoadXML(const XMLElement& source) override | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool LoadXML(const XMLElement&in)", asMETHODPR(Node, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // bool Node::LoadXML(const XMLElement& source, SceneResolver& resolver, bool loadChildren=true, bool rewriteIDs=false, CreateMode mode=REPLICATED) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool LoadXML(const XMLElement&in, SceneResolver&, bool = true, bool = false, CreateMode = REPLICATED)", asMETHODPR(Node, LoadXML, (const XMLElement&, SceneResolver&, bool, bool, CreateMode), bool), asCALL_THISCALL);
    // Vector3 Node::LocalToWorld(const Vector3& position) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 LocalToWorld(const Vector3&in) const", asMETHODPR(Node, LocalToWorld, (const Vector3&) const, Vector3), asCALL_THISCALL);
    // Vector3 Node::LocalToWorld(const Vector4& vector) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 LocalToWorld(const Vector4&in) const", asMETHODPR(Node, LocalToWorld, (const Vector4&) const, Vector3), asCALL_THISCALL);
    // Vector2 Node::LocalToWorld2D(const Vector2& vector) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector2 LocalToWorld2D(const Vector2&in) const", asMETHODPR(Node, LocalToWorld2D, (const Vector2&) const, Vector2), asCALL_THISCALL);
    // bool Node::LookAt(const Vector3& target, const Vector3& up=Vector3::UP, TransformSpace space=TS_WORLD) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool LookAt(const Vector3&in, const Vector3&in = Vector3::UP, TransformSpace = TS_WORLD)", asMETHODPR(Node, LookAt, (const Vector3&, const Vector3&, TransformSpace), bool), asCALL_THISCALL);
    // void Node::MarkDirty() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void MarkDirty()", asMETHODPR(Node, MarkDirty, (), void), asCALL_THISCALL);
    // void Node::MarkNetworkUpdate() override | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void MarkNetworkUpdate()", asMETHODPR(Node, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // void Node::MarkReplicationDirty() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void MarkReplicationDirty()", asMETHODPR(Node, MarkReplicationDirty, (), void), asCALL_THISCALL);
    // explicit Node::Node(Context* context) | File: ../Scene/Node.h
    engine->RegisterObjectBehaviour("Node", asBEHAVE_FACTORY, "Node@+ f()", asFUNCTION(Node_Node_Context), asCALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Node, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Node, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Node, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Node::Pitch(float angle, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void Pitch(float, TransformSpace = TS_LOCAL)", asMETHODPR(Node, Pitch, (float, TransformSpace), void), asCALL_THISCALL);
    // void Node::PrepareNetworkUpdate() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void PrepareNetworkUpdate()", asMETHODPR(Node, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Node, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Node, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Node", "int Refs() const", asMETHODPR(Node, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "int get_refs() const", asMETHODPR(Node, Refs, () const, int), asCALL_THISCALL);
    // static void Node::RegisterObject(Context* context) | File: ../Scene/Node.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Node", asBEHAVE_RELEASE, "void f()", asMETHODPR(Node, ReleaseRef, (), void), asCALL_THISCALL);
    // void Node::Remove() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void Remove()", asMETHODPR(Node, Remove, (), void), asCALL_THISCALL);
    // void Node::RemoveAllChildren() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void RemoveAllChildren()", asMETHODPR(Node, RemoveAllChildren, (), void), asCALL_THISCALL);
    // void Node::RemoveAllComponents() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void RemoveAllComponents()", asMETHODPR(Node, RemoveAllComponents, (), void), asCALL_THISCALL);
    // void Node::RemoveAllTags() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void RemoveAllTags()", asMETHODPR(Node, RemoveAllTags, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(Node, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Node::RemoveChild(Node* node) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void RemoveChild(Node@+)", asMETHODPR(Node, RemoveChild, (Node*), void), asCALL_THISCALL);
    // void Node::RemoveChildren(bool removeReplicated, bool removeLocal, bool recursive) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void RemoveChildren(bool, bool, bool)", asMETHODPR(Node, RemoveChildren, (bool, bool, bool), void), asCALL_THISCALL);
    // void Node::RemoveComponent(Component* component) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void RemoveComponent(Component@+)", asMETHODPR(Node, RemoveComponent, (Component*), void), asCALL_THISCALL);
    // void Node::RemoveComponent(StringHash type) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void RemoveComponent(StringHash)", asMETHODPR(Node, RemoveComponent, (StringHash), void), asCALL_THISCALL);
    // template<class T> void Node::RemoveComponent() | File: ../Scene/Node.h
    // Not registered because template
    // void Node::RemoveComponents(bool removeReplicated, bool removeLocal) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void RemoveComponents(bool, bool)", asMETHODPR(Node, RemoveComponents, (bool, bool), void), asCALL_THISCALL);
    // void Node::RemoveComponents(StringHash type) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void RemoveComponents(StringHash)", asMETHODPR(Node, RemoveComponents, (StringHash), void), asCALL_THISCALL);
    // template<class T> void Node::RemoveComponents() | File: ../Scene/Node.h
    // Not registered because template
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "void RemoveInstanceDefault()", asMETHODPR(Node, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Node::RemoveListener(Component* component) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void RemoveListener(Component@+)", asMETHODPR(Node, RemoveListener, (Component*), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "void RemoveObjectAnimation()", asMETHODPR(Node, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // bool Node::RemoveTag(const String& tag) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool RemoveTag(const String&in)", asMETHODPR(Node, RemoveTag, (const String&), bool), asCALL_THISCALL);
    // void Node::ReorderComponent(Component* component, unsigned index) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void ReorderComponent(Component@+, uint)", asMETHODPR(Node, ReorderComponent, (Component*, unsigned), void), asCALL_THISCALL);
    // void Node::ResetDeepEnabled() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void ResetDeepEnabled()", asMETHODPR(Node, ResetDeepEnabled, (), void), asCALL_THISCALL);
    // void Node::ResetScene() | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void ResetScene()", asMETHODPR(Node, ResetScene, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "void ResetToDefault()", asMETHODPR(Node, ResetToDefault, (), void), asCALL_THISCALL);
    // void Node::Roll(float angle, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void Roll(float, TransformSpace = TS_LOCAL)", asMETHODPR(Node, Roll, (float, TransformSpace), void), asCALL_THISCALL);
    // void Node::Rotate(const Quaternion& delta, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void Rotate(const Quaternion&in, TransformSpace = TS_LOCAL)", asMETHODPR(Node, Rotate, (const Quaternion&, TransformSpace), void), asCALL_THISCALL);
    // void Node::Rotate2D(float delta, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void Rotate2D(float, TransformSpace = TS_LOCAL)", asMETHODPR(Node, Rotate2D, (float, TransformSpace), void), asCALL_THISCALL);
    // void Node::RotateAround(const Vector3& point, const Quaternion& delta, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void RotateAround(const Vector3&in, const Quaternion&in, TransformSpace = TS_LOCAL)", asMETHODPR(Node, RotateAround, (const Vector3&, const Quaternion&, TransformSpace), void), asCALL_THISCALL);
    // void Node::RotateAround2D(const Vector2& point, float delta, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void RotateAround2D(const Vector2&in, float, TransformSpace = TS_LOCAL)", asMETHODPR(Node, RotateAround2D, (const Vector2&, float, TransformSpace), void), asCALL_THISCALL);
    // bool Node::Save(Serializer& dest) const override | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool Save(Serializer&) const", asMETHODPR(Node, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // bool Node::SaveDefaultAttributes() const override | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool SaveDefaultAttributes() const", asMETHODPR(Node, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Node::SaveJSON(JSONValue& dest) const override | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool SaveJSON(JSONValue&) const", asMETHODPR(Node, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Node::SaveJSON(Serializer& dest, const String& indentation="\t") const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool SaveJSON(Serializer&, const String&in = \"\t\") const", asMETHODPR(Node, SaveJSON, (Serializer&, const String&) const, bool), asCALL_THISCALL);
    // bool Node::SaveXML(XMLElement& dest) const override | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool SaveXML(XMLElement&) const", asMETHODPR(Node, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // bool Node::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "bool SaveXML(Serializer&, const String&in = \"\t\") const", asMETHODPR(Node, SaveXML, (Serializer&, const String&) const, bool), asCALL_THISCALL);
    // void Node::Scale(float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void Scale(float)", asMETHODPR(Node, Scale, (float), void), asCALL_THISCALL);
    // void Node::Scale(const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void Scale(const Vector3&in)", asMETHODPR(Node, Scale, (const Vector3&), void), asCALL_THISCALL);
    // void Node::Scale2D(const Vector2& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void Scale2D(const Vector2&in)", asMETHODPR(Node, Scale2D, (const Vector2&), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "void SendEvent(StringHash)", asMETHODPR(Node, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Node, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "void SetAnimationEnabled(bool)", asMETHODPR(Node, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_animationEnabled(bool)", asMETHODPR(Node, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "void SetAnimationTime(float)", asMETHODPR(Node, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Node, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Node, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Node, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Node, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(Node, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(Node, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Node, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "void SetBlockEvents(bool)", asMETHODPR(Node, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Node::SetDeepEnabled(bool enable) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetDeepEnabled(bool)", asMETHODPR(Node, SetDeepEnabled, (bool), void), asCALL_THISCALL);
    // void Node::SetDirection(const Vector3& direction) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetDirection(const Vector3&in)", asMETHODPR(Node, SetDirection, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_direction(const Vector3&in)", asMETHODPR(Node, SetDirection, (const Vector3&), void), asCALL_THISCALL);
    // void Node::SetEnabled(bool enable) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetEnabled(bool)", asMETHODPR(Node, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_enabled(bool)", asMETHODPR(Node, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Node::SetEnabledRecursive(bool enable) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetEnabledRecursive(bool)", asMETHODPR(Node, SetEnabledRecursive, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Node, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Node, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Node::SetID(unsigned id) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetID(uint)", asMETHODPR(Node, SetID, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_id(uint)", asMETHODPR(Node, SetID, (unsigned), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "void SetInstanceDefault(bool)", asMETHODPR(Node, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Node, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Node::SetName(const String& name) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetName(const String&in)", asMETHODPR(Node, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_name(const String&in)", asMETHODPR(Node, SetName, (const String&), void), asCALL_THISCALL);
    // void Node::SetNetParentAttr(const PODVector<unsigned char>& value) | File: ../Scene/Node.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void Node::SetNetPositionAttr(const Vector3& value) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetNetPositionAttr(const Vector3&in)", asMETHODPR(Node, SetNetPositionAttr, (const Vector3&), void), asCALL_THISCALL);
    // void Node::SetNetRotationAttr(const PODVector<unsigned char>& value) | File: ../Scene/Node.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(Node, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(Node, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Node", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(Node, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Node::SetOwner(Connection* owner) | File: ../Scene/Node.h
    // Not registered because have @manualbind mark
    // void Node::SetParent(Node* parent) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetParent(Node@+)", asMETHODPR(Node, SetParent, (Node*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_parent(Node@+)", asMETHODPR(Node, SetParent, (Node*), void), asCALL_THISCALL);
    // void Node::SetPosition(const Vector3& position) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetPosition(const Vector3&in)", asMETHODPR(Node, SetPosition, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_position(const Vector3&in)", asMETHODPR(Node, SetPosition, (const Vector3&), void), asCALL_THISCALL);
    // void Node::SetPosition2D(const Vector2& position) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetPosition2D(const Vector2&in)", asMETHODPR(Node, SetPosition2D, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_position2D(const Vector2&in)", asMETHODPR(Node, SetPosition2D, (const Vector2&), void), asCALL_THISCALL);
    // void Node::SetPosition2D(float x, float y) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetPosition2D(float, float)", asMETHODPR(Node, SetPosition2D, (float, float), void), asCALL_THISCALL);
    // void Node::SetPositionSilent(const Vector3& position) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetPositionSilent(const Vector3&in)", asMETHODPR(Node, SetPositionSilent, (const Vector3&), void), asCALL_THISCALL);
    // void Node::SetRotation(const Quaternion& rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetRotation(const Quaternion&in)", asMETHODPR(Node, SetRotation, (const Quaternion&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_rotation(const Quaternion&in)", asMETHODPR(Node, SetRotation, (const Quaternion&), void), asCALL_THISCALL);
    // void Node::SetRotation2D(float rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetRotation2D(float)", asMETHODPR(Node, SetRotation2D, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_rotation2D(float)", asMETHODPR(Node, SetRotation2D, (float), void), asCALL_THISCALL);
    // void Node::SetRotationSilent(const Quaternion& rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetRotationSilent(const Quaternion&in)", asMETHODPR(Node, SetRotationSilent, (const Quaternion&), void), asCALL_THISCALL);
    // void Node::SetScale(float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetScale(float)", asMETHODPR(Node, SetScale, (float), void), asCALL_THISCALL);
    // void Node::SetScale(const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetScale(const Vector3&in)", asMETHODPR(Node, SetScale, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_scale(const Vector3&in)", asMETHODPR(Node, SetScale, (const Vector3&), void), asCALL_THISCALL);
    // void Node::SetScale2D(const Vector2& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetScale2D(const Vector2&in)", asMETHODPR(Node, SetScale2D, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_scale2D(const Vector2&in)", asMETHODPR(Node, SetScale2D, (const Vector2&), void), asCALL_THISCALL);
    // void Node::SetScale2D(float x, float y) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetScale2D(float, float)", asMETHODPR(Node, SetScale2D, (float, float), void), asCALL_THISCALL);
    // void Node::SetScaleSilent(const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetScaleSilent(const Vector3&in)", asMETHODPR(Node, SetScaleSilent, (const Vector3&), void), asCALL_THISCALL);
    // void Node::SetScene(Scene* scene) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetScene(Scene@+)", asMETHODPR(Node, SetScene, (Scene*), void), asCALL_THISCALL);
    // void Node::SetTags(const StringVector& tags) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetTags(Array<String>@+)", asFUNCTION(Node_SetTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "void SetTemporary(bool)", asMETHODPR(Node, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_temporary(bool)", asMETHODPR(Node, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Node::SetTransform(const Vector3& position, const Quaternion& rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetTransform(const Vector3&in, const Quaternion&in)", asMETHODPR(Node, SetTransform, (const Vector3&, const Quaternion&), void), asCALL_THISCALL);
    // void Node::SetTransform(const Vector3& position, const Quaternion& rotation, float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetTransform(const Vector3&in, const Quaternion&in, float)", asMETHODPR(Node, SetTransform, (const Vector3&, const Quaternion&, float), void), asCALL_THISCALL);
    // void Node::SetTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetTransform(const Vector3&in, const Quaternion&in, const Vector3&in)", asMETHODPR(Node, SetTransform, (const Vector3&, const Quaternion&, const Vector3&), void), asCALL_THISCALL);
    // void Node::SetTransform(const Matrix3x4& matrix) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetTransform(const Matrix3x4&in)", asMETHODPR(Node, SetTransform, (const Matrix3x4&), void), asCALL_THISCALL);
    // void Node::SetTransform2D(const Vector2& position, float rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetTransform2D(const Vector2&in, float)", asMETHODPR(Node, SetTransform2D, (const Vector2&, float), void), asCALL_THISCALL);
    // void Node::SetTransform2D(const Vector2& position, float rotation, float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetTransform2D(const Vector2&in, float, float)", asMETHODPR(Node, SetTransform2D, (const Vector2&, float, float), void), asCALL_THISCALL);
    // void Node::SetTransform2D(const Vector2& position, float rotation, const Vector2& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetTransform2D(const Vector2&in, float, const Vector2&in)", asMETHODPR(Node, SetTransform2D, (const Vector2&, float, const Vector2&), void), asCALL_THISCALL);
    // void Node::SetTransformSilent(const Vector3& position, const Quaternion& rotation, const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetTransformSilent(const Vector3&in, const Quaternion&in, const Vector3&in)", asMETHODPR(Node, SetTransformSilent, (const Vector3&, const Quaternion&, const Vector3&), void), asCALL_THISCALL);
    // void Node::SetVar(StringHash key, const Variant& value) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetVar(StringHash, const Variant&in)", asMETHODPR(Node, SetVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Node::SetWorldDirection(const Vector3& direction) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldDirection(const Vector3&in)", asMETHODPR(Node, SetWorldDirection, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_worldDirection(const Vector3&in)", asMETHODPR(Node, SetWorldDirection, (const Vector3&), void), asCALL_THISCALL);
    // void Node::SetWorldPosition(const Vector3& position) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldPosition(const Vector3&in)", asMETHODPR(Node, SetWorldPosition, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_worldPosition(const Vector3&in)", asMETHODPR(Node, SetWorldPosition, (const Vector3&), void), asCALL_THISCALL);
    // void Node::SetWorldPosition2D(const Vector2& position) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldPosition2D(const Vector2&in)", asMETHODPR(Node, SetWorldPosition2D, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_worldPosition2D(const Vector2&in)", asMETHODPR(Node, SetWorldPosition2D, (const Vector2&), void), asCALL_THISCALL);
    // void Node::SetWorldPosition2D(float x, float y) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldPosition2D(float, float)", asMETHODPR(Node, SetWorldPosition2D, (float, float), void), asCALL_THISCALL);
    // void Node::SetWorldRotation(const Quaternion& rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldRotation(const Quaternion&in)", asMETHODPR(Node, SetWorldRotation, (const Quaternion&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_worldRotation(const Quaternion&in)", asMETHODPR(Node, SetWorldRotation, (const Quaternion&), void), asCALL_THISCALL);
    // void Node::SetWorldRotation2D(float rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldRotation2D(float)", asMETHODPR(Node, SetWorldRotation2D, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_worldRotation2D(float)", asMETHODPR(Node, SetWorldRotation2D, (float), void), asCALL_THISCALL);
    // void Node::SetWorldScale(float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldScale(float)", asMETHODPR(Node, SetWorldScale, (float), void), asCALL_THISCALL);
    // void Node::SetWorldScale(const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldScale(const Vector3&in)", asMETHODPR(Node, SetWorldScale, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_worldScale(const Vector3&in)", asMETHODPR(Node, SetWorldScale, (const Vector3&), void), asCALL_THISCALL);
    // void Node::SetWorldScale2D(const Vector2& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldScale2D(const Vector2&in)", asMETHODPR(Node, SetWorldScale2D, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "void set_worldScale2D(const Vector2&in)", asMETHODPR(Node, SetWorldScale2D, (const Vector2&), void), asCALL_THISCALL);
    // void Node::SetWorldScale2D(float x, float y) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldScale2D(float, float)", asMETHODPR(Node, SetWorldScale2D, (float, float), void), asCALL_THISCALL);
    // void Node::SetWorldTransform(const Vector3& position, const Quaternion& rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldTransform(const Vector3&in, const Quaternion&in)", asMETHODPR(Node, SetWorldTransform, (const Vector3&, const Quaternion&), void), asCALL_THISCALL);
    // void Node::SetWorldTransform(const Vector3& position, const Quaternion& rotation, float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldTransform(const Vector3&in, const Quaternion&in, float)", asMETHODPR(Node, SetWorldTransform, (const Vector3&, const Quaternion&, float), void), asCALL_THISCALL);
    // void Node::SetWorldTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldTransform(const Vector3&in, const Quaternion&in, const Vector3&in)", asMETHODPR(Node, SetWorldTransform, (const Vector3&, const Quaternion&, const Vector3&), void), asCALL_THISCALL);
    // void Node::SetWorldTransform(const Matrix3x4& worldTransform) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldTransform(const Matrix3x4&in)", asMETHODPR(Node, SetWorldTransform, (const Matrix3x4&), void), asCALL_THISCALL);
    // void Node::SetWorldTransform2D(const Vector2& position, float rotation) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldTransform2D(const Vector2&in, float)", asMETHODPR(Node, SetWorldTransform2D, (const Vector2&, float), void), asCALL_THISCALL);
    // void Node::SetWorldTransform2D(const Vector2& position, float rotation, float scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldTransform2D(const Vector2&in, float, float)", asMETHODPR(Node, SetWorldTransform2D, (const Vector2&, float, float), void), asCALL_THISCALL);
    // void Node::SetWorldTransform2D(const Vector2& position, float rotation, const Vector2& scale) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void SetWorldTransform2D(const Vector2&in, float, const Vector2&in)", asMETHODPR(Node, SetWorldTransform2D, (const Vector2&, float, const Vector2&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Node::Translate(const Vector3& delta, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void Translate(const Vector3&in, TransformSpace = TS_LOCAL)", asMETHODPR(Node, Translate, (const Vector3&, TransformSpace), void), asCALL_THISCALL);
    // void Node::Translate2D(const Vector2& delta, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void Translate2D(const Vector2&in, TransformSpace = TS_LOCAL)", asMETHODPR(Node, Translate2D, (const Vector2&, TransformSpace), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "void UnsubscribeFromAllEvents()", asMETHODPR(Node, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Node_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Node, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Node, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Node", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Node, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Node", "int WeakRefs() const", asMETHODPR(Node, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Node", "int get_weakRefs() const", asMETHODPR(Node, WeakRefs, () const, int), asCALL_THISCALL);
    // Vector3 Node::WorldToLocal(const Vector3& position) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 WorldToLocal(const Vector3&in) const", asMETHODPR(Node, WorldToLocal, (const Vector3&) const, Vector3), asCALL_THISCALL);
    // Vector3 Node::WorldToLocal(const Vector4& vector) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector3 WorldToLocal(const Vector4&in) const", asMETHODPR(Node, WorldToLocal, (const Vector4&) const, Vector3), asCALL_THISCALL);
    // Vector2 Node::WorldToLocal2D(const Vector2& vector) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "Vector2 WorldToLocal2D(const Vector2&in) const", asMETHODPR(Node, WorldToLocal2D, (const Vector2&) const, Vector2), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Node, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Node, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Node", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Node, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Node::Yaw(float angle, TransformSpace space=TS_LOCAL) | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Node", "void Yaw(float, TransformSpace = TS_LOCAL)", asMETHODPR(Node, Yaw, (float, TransformSpace), void), asCALL_THISCALL);
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
