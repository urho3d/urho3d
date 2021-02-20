//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Graphics/Skeleton.h"
#include "../Scene/Scene.h"
#include "../Graphics/Octree.h"
#include "../Graphics/DebugRenderer.h"
#include "../IO/PackageFile.h"

namespace Urho3D
{

#ifdef URHO3D_NETWORK
    static const bool URHO3D_NETWORK_DEFINED = true;
#else
    static const bool URHO3D_NETWORK_DEFINED = false;
#endif

const AttributeInfo& SerializableGetAttributeInfo(unsigned index, Serializable* ptr);

#define REGISTER_MANUAL_PART_Serializable(T, className) \
    engine->RegisterObjectMethod(className, "const AttributeInfo& get_attributeInfos(uint) const", asFUNCTION(SerializableGetAttributeInfo), asCALL_CDECL_OBJLAST);

// ========================================================================================

// bool Node::SaveXML(Serializer &dest, const String &indentation="\t") const | File: ../Scene/Node.h
bool NodeSaveXML(File* file, const String& indentation, Node* ptr);
// bool Node::SaveXML(Serializer &dest, const String &indentation="\t") const | File: ../Scene/Node.h
bool NodeSaveXMLVectorBuffer(VectorBuffer& buffer, const String& indentation, Node* ptr);
// bool Node::SaveJSON(Serializer &dest, const String &indentation="\t") const | File: ../Scene/Node.h
bool NodeSaveJSON(File* file, Node* ptr);
// bool Node::SaveJSON(Serializer &dest, const String &indentation="\t") const | File: ../Scene/Node.h
bool NodeSaveJSONVectorBuffer(VectorBuffer& buffer, Node* ptr);
// template<class T> void Node::GetChildrenWithComponent(PODVector< Node * > &dest, bool recursive=false) const | File: ../Scene/Node.h
CScriptArray* NodeGetChildrenWithScript(bool recursive, Node* ptr);
// template<class T> void Node::GetChildrenWithComponent(PODVector< Node * > &dest, bool recursive=false) const | File: ../Scene/Node.h
CScriptArray* NodeGetChildrenWithClassName(const String& className, bool recursive, Node* ptr);
// void Node::GetComponents(PODVector< Component * > &dest, StringHash type, bool recursive=false) const | File: ../Scene/Node.h
CScriptArray* NodeGetComponentsWithType(const String& typeName, bool recursive, Node* ptr);
// unsigned Node::GetNumChildren(bool recursive=false) const | File: ../Scene/Node.h
unsigned NodeGetNumChildrenNonRecursive(Node* ptr);
// unsigned Node::GetNumChildren(bool recursive=false) const | File: ../Scene/Node.h
unsigned NodeGetNumChildrenRecursive(Node* ptr);
// Node* Node::GetChild(unsigned index) const | File: ../Scene/Node.h
Node* NodeGetChild(unsigned index, Node* ptr);
// Node* Node::GetChild(const String &name, bool recursive=false) const | File: ../Scene/Node.h
Node* NodeGetChildByName(const String& name, Node* ptr);
// Node* Node::GetChild(const String &name, bool recursive=false) const | File: ../Scene/Node.h
Node* NodeGetChildByNameRecursive(const String& name, Node* ptr);
// const VariantMap& Node::GetVars() const | File: ../Scene/Node.h
VariantMap& NodeGetVars(Node* ptr);
// const Vector<SharedPtr<Component> >& Node::GetComponents() const | File: ../Scene/Node.h
Component* NodeGetComponent(unsigned index, Node* ptr);

#define REGISTER_MANUAL_PART_Node(T, className) \
    RegisterNamedObjectConstructor<T>(engine, className); \
    /* bool Node::SaveXML(Serializer &dest, const String &indentation="\t") const | File: ../Scene/Node.h */ \
    engine->RegisterObjectMethod(className, "bool SaveXML(File@+, const String&in indentation = \"\t\")", asFUNCTION(NodeSaveXML), asCALL_CDECL_OBJLAST); \
    /* bool Node::SaveXML(Serializer &dest, const String &indentation="\t") const | File: ../Scene/Node.h */ \
    engine->RegisterObjectMethod(className, "bool SaveXML(VectorBuffer&, const String&in indentation = \"\t\")", asFUNCTION(NodeSaveXMLVectorBuffer), asCALL_CDECL_OBJLAST); \
    /* bool Node::SaveJSON(Serializer &dest, const String &indentation="\t") const | File: ../Scene/Node.h */ \
    engine->RegisterObjectMethod(className, "bool SaveJSON(File@+)", asFUNCTION(NodeSaveJSON), asCALL_CDECL_OBJLAST); \
    /* bool Node::SaveJSON(Serializer &dest, const String &indentation="\t") const | File: ../Scene/Node.h */ \
    engine->RegisterObjectMethod(className, "bool SaveJSON(VectorBuffer&)", asFUNCTION(NodeSaveJSONVectorBuffer), asCALL_CDECL_OBJLAST); \
    /* template<class T> void Node::GetChildrenWithComponent(PODVector< Node * > &dest, bool recursive=false) const | File: ../Scene/Node.h */ \
    engine->RegisterObjectMethod(className, "Array<Node@>@ GetChildrenWithScript(bool recursive = false) const", asFUNCTION(NodeGetChildrenWithScript), asCALL_CDECL_OBJLAST); \
    /* template<class T> void Node::GetChildrenWithComponent(PODVector< Node * > &dest, bool recursive=false) const | File: ../Scene/Node.h */ \
    engine->RegisterObjectMethod(className, "Array<Node@>@ GetChildrenWithScript(const String&in, bool recursive = false) const", asFUNCTION(NodeGetChildrenWithClassName), asCALL_CDECL_OBJLAST); \
    /* void Node::GetComponents(PODVector< Component * > &dest, StringHash type, bool recursive=false) const | File: ../Scene/Node.h */ \
    engine->RegisterObjectMethod(className, "Array<Component@>@ GetComponents(const String&in, bool recursive = false) const", asFUNCTION(NodeGetComponentsWithType), asCALL_CDECL_OBJLAST); \
    /* unsigned Node::GetNumChildren(bool recursive=false) const | File: ../Scene/Node.h */ \
    engine->RegisterObjectMethod(className, "uint get_numChildren() const", asFUNCTION(NodeGetNumChildrenNonRecursive), asCALL_CDECL_OBJLAST); \
    /* unsigned Node::GetNumChildren(bool recursive=false) const | File: ../Scene/Node.h */ \
    engine->RegisterObjectMethod(className, "uint get_numAllChildren() const", asFUNCTION(NodeGetNumChildrenRecursive), asCALL_CDECL_OBJLAST); \
    /* Node* Node::GetChild(unsigned index) const | File: ../Scene/Node.h */ \
    engine->RegisterObjectMethod(className, "Node@+ get_children(uint) const", asFUNCTION(NodeGetChild), asCALL_CDECL_OBJLAST); \
    /* Node* Node::GetChild(const String &name, bool recursive=false) const | File: ../Scene/Node.h */ \
    engine->RegisterObjectMethod(className, "Node@+ get_childrenByName(const String&in) const", asFUNCTION(NodeGetChildByName), asCALL_CDECL_OBJLAST); \
    /* Node* Node::GetChild(const String &name, bool recursive=false) const | File: ../Scene/Node.h */ \
    engine->RegisterObjectMethod(className, "Node@+ get_allChildrenByName(const String&in) const", asFUNCTION(NodeGetChildByNameRecursive), asCALL_CDECL_OBJLAST); \
    /* const Vector<SharedPtr<Component> >& Node::GetComponents() const | File: ../Scene/Node.h */ \
    engine->RegisterObjectMethod(className, "Component@+ get_components(uint) const", asFUNCTION(NodeGetComponent), asCALL_CDECL_OBJLAST); \
    /* const VariantMap& Node::GetVars() const | File: ../Scene/Node.h */ \
    engine->RegisterObjectMethod(className, "VariantMap& get_vars()", asFUNCTION(NodeGetVars), asCALL_CDECL_OBJLAST); \
    /* Workarounds for Connection that used outside URHO3D_NETWORK define */ \
    if (URHO3D_NETWORK_DEFINED) \
    { \
        /* void Node::SetOwner(Connection* owner) | File: ../Scene/Node.h */ \
        engine->RegisterObjectMethod(className, "void SetOwner(Connection@+)", asMETHODPR(T, SetOwner, (Connection*), void), asCALL_THISCALL); \
        engine->RegisterObjectMethod(className, "void set_owner(Connection@+)", asMETHODPR(T, SetOwner, (Connection*), void), asCALL_THISCALL); \
        /* Connection* Node::GetOwner() const | File: ../Scene/Node.h */ \
        engine->RegisterObjectMethod(className, "Connection@+ GetOwner() const", asMETHODPR(T, GetOwner, () const, Connection*), asCALL_THISCALL); \
        engine->RegisterObjectMethod(className, "Connection@+ get_owner() const", asMETHODPR(T, GetOwner, () const, Connection*), asCALL_THISCALL); \
        /* void Node::CleanupConnection(Connection* connection) | File: ../Scene/Node.h */ \
        engine->RegisterObjectMethod(className, "void CleanupConnection(Connection@+)", asMETHODPR(T, CleanupConnection, (Connection*), void), asCALL_THISCALL); \
    }

// ========================================================================================

// bool Scene::LoadXML(Deserializer &source) | File: ../Scene/Scene.h
bool SceneLoadXML(File* file, Scene* ptr);
// bool Scene::LoadXML(Deserializer &source) | File: ../Scene/Scene.h
bool SceneLoadXMLVectorBuffer(VectorBuffer& buffer, Scene* ptr);
// bool Scene::LoadJSON(Deserializer &source) | File: ../Scene/Scene.h
bool SceneLoadJSON(File* file, Scene* ptr);
// bool Scene::LoadJSON(Deserializer &source) | File: ../Scene/Scene.h
bool SceneLoadJSONVectorBuffer(VectorBuffer& buffer, Scene* ptr);
// Node* Scene::Instantiate(Deserializer &source, const Vector3 &position, const Quaternion &rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
Node* SceneInstantiate(File* file, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr);
// Node* Scene::Instantiate(Deserializer &source, const Vector3 &position, const Quaternion &rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
Node* SceneInstantiateVectorBuffer(VectorBuffer& buffer, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr);
// Node* Scene::InstantiateXML(Deserializer &source, const Vector3 &position, const Quaternion &rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
Node* SceneInstantiateXML(File* file, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr);
// Node* Scene::InstantiateXML(Deserializer &source, const Vector3 &position, const Quaternion &rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
Node* SceneInstantiateXMLVectorBuffer(VectorBuffer& buffer, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr);
// Node* Scene::InstantiateXML(Deserializer &source, const Vector3 &position, const Quaternion &rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
Node* SceneInstantiateXMLFile(XMLFile* xml, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr);
// Node* Scene::InstantiateJSON(Deserializer &source, const Vector3 &position, const Quaternion &rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
Node* SceneInstantiateJSON(File* file, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr);
// Node* Scene::InstantiateJSON(Deserializer &source, const Vector3 &position, const Quaternion &rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
Node* SceneInstantiateJSONVectorBuffer(VectorBuffer& buffer, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr);
// Node* Scene::InstantiateJSON(Deserializer &source, const Vector3 &position, const Quaternion &rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
Node* SceneInstantiateJSONFile(JSONFile* json, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr);
// bool Scene::GetNodesWithTag(PODVector< Node * > &dest, const String &tag) const | File: ../Scene/Scene.h
CScriptArray* SceneGetNodesWithTag(const String& tag, Scene* ptr);
// template<class T> T * Node::GetComponent(bool recursive=false) const | File: ../Scene/Node.h
DebugRenderer* SceneGetDebugRenderer(Scene* ptr);
// template<class T> T * Node::GetComponent(bool recursive=false) const | File: ../Scene/Node.h
Octree* SceneGetOctree(Scene* ptr);

#define REGISTER_MANUAL_PART_Scene(T, className) \
    /* bool Scene::LoadXML(Deserializer &source) | File: ../Scene/Scene.h */ \
    engine->RegisterObjectMethod(className, "bool LoadXML(File@+)", asFUNCTION(SceneLoadXML), asCALL_CDECL_OBJLAST); \
    /* bool Scene::LoadXML(Deserializer &source) | File: ../Scene/Scene.h */ \
    engine->RegisterObjectMethod(className, "bool LoadXML(VectorBuffer&)", asFUNCTION(SceneLoadXMLVectorBuffer), asCALL_CDECL_OBJLAST); \
    /* bool Scene::LoadJSON(Deserializer &source) | File: ../Scene/Scene.h */ \
    engine->RegisterObjectMethod(className, "bool LoadJSON(File@+)", asFUNCTION(SceneLoadJSON), asCALL_CDECL_OBJLAST); \
    /* bool Scene::LoadJSON(Deserializer &source) | File: ../Scene/Scene.h */ \
    engine->RegisterObjectMethod(className, "bool LoadJSON(VectorBuffer&)", asFUNCTION(SceneLoadJSONVectorBuffer), asCALL_CDECL_OBJLAST); \
    /* Node* Scene::Instantiate(Deserializer &source, const Vector3 &position, const Quaternion &rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h */ \
    engine->RegisterObjectMethod(className, "Node@+ Instantiate(File@+, const Vector3&in, const Quaternion&in, CreateMode mode = REPLICATED)", asFUNCTION(SceneInstantiate), asCALL_CDECL_OBJLAST); \
    /* Node* Scene::Instantiate(Deserializer &source, const Vector3 &position, const Quaternion &rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h */ \
    /* Node* Scene::InstantiateXML(Deserializer &source, const Vector3 &position, const Quaternion &rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h */ \
    engine->RegisterObjectMethod(className, "Node@+ Instantiate(VectorBuffer&, const Vector3&in, const Quaternion&in, CreateMode mode = REPLICATED)", asFUNCTION(SceneInstantiateVectorBuffer), asCALL_CDECL_OBJLAST); \
    /* Node* Scene::InstantiateXML(Deserializer &source, const Vector3 &position, const Quaternion &rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h */ \
    engine->RegisterObjectMethod(className, "Node@+ InstantiateXML(File@+, const Vector3&in, const Quaternion&in, CreateMode mode = REPLICATED)", asFUNCTION(SceneInstantiateXML), asCALL_CDECL_OBJLAST); \
    /* Node* Scene::InstantiateXML(Deserializer &source, const Vector3 &position, const Quaternion &rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h */ \
    engine->RegisterObjectMethod(className, "Node@+ InstantiateXML(VectorBuffer&, const Vector3&in, const Quaternion&in, CreateMode mode = REPLICATED)", asFUNCTION(SceneInstantiateXMLVectorBuffer), asCALL_CDECL_OBJLAST); \
    /* Node* Scene::InstantiateXML(Deserializer &source, const Vector3 &position, const Quaternion &rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h */ \
    engine->RegisterObjectMethod(className, "Node@+ InstantiateXML(XMLFile@+, const Vector3&in, const Quaternion&in, CreateMode mode = REPLICATED)", asFUNCTION(SceneInstantiateXMLFile), asCALL_CDECL_OBJLAST); \
    /* Node* Scene::InstantiateJSON(Deserializer &source, const Vector3 &position, const Quaternion &rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h */ \
    engine->RegisterObjectMethod(className, "Node@+ InstantiateJSON(File@+, const Vector3&in, const Quaternion&in, CreateMode mode = REPLICATED)", asFUNCTION(SceneInstantiateJSON), asCALL_CDECL_OBJLAST); \
    /* Node* Scene::InstantiateJSON(Deserializer &source, const Vector3 &position, const Quaternion &rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h */ \
    engine->RegisterObjectMethod(className, "Node@+ InstantiateJSON(VectorBuffer&, const Vector3&in, const Quaternion&in, CreateMode mode = REPLICATED)", asFUNCTION(SceneInstantiateJSONVectorBuffer), asCALL_CDECL_OBJLAST); \
    /* Node* Scene::InstantiateJSON(Deserializer &source, const Vector3 &position, const Quaternion &rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h */ \
    engine->RegisterObjectMethod(className, "Node@+ InstantiateJSON(JSONFile@+, const Vector3&in, const Quaternion&in, CreateMode mode = REPLICATED)", asFUNCTION(SceneInstantiateJSONFile), asCALL_CDECL_OBJLAST); \
    /* bool Scene::GetNodesWithTag(PODVector< Node * > &dest, const String &tag) const | File: ../Scene/Scene.h */ \
    engine->RegisterObjectMethod(className, "Array<Node@>@ GetNodesWithTag(const String&in) const", asFUNCTION(SceneGetNodesWithTag), asCALL_CDECL_OBJLAST); \
    /* Component* Node::GetComponent(StringHash type, bool recursive=false) const | File: ../Scene/Scene.h */ \
    /* Workaround Doxygen bug: have no const flag in xml */ \
    engine->RegisterObjectMethod(className, "Component@+ GetComponent(StringHash, bool = false) const", asMETHODPR(T, GetComponent, (StringHash, bool) const, Component*), asCALL_THISCALL); \
    /* bool Node::SaveXML(XMLElement &dest) const override | File: ../Scene/Scene.h */ \
    /* Workaround Doxygen bug: have no const flag in xml */ \
    engine->RegisterObjectMethod(className, "bool SaveXML(XMLElement&) const", asMETHODPR(T, SaveXML, (XMLElement &) const, bool), asCALL_THISCALL); \
    /* bool Node::SaveJSON(JSONValue &dest) const override | File: ../Scene/Scene.h */\
    /* Workaround Doxygen bug: have no const flag in xml */ \
    engine->RegisterObjectMethod(className, "bool SaveJSON(JSONValue&) const", asMETHODPR(T, SaveJSON, (JSONValue &) const, bool), asCALL_THISCALL); \
    /* template<class T> T * Node::GetComponent(bool recursive=false) const | File: ../Scene/Node.h */ \
    engine->RegisterObjectMethod(className, "DebugRenderer@+ get_debugRenderer() const", asFUNCTION(SceneGetDebugRenderer), asCALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "Octree@+ get_octree() const", asFUNCTION(SceneGetOctree), asCALL_CDECL_OBJLAST);

// ========================================================================================

// WeakPtr<Node> Bone::node_ | File: ../Graphics/Skeleton.h
Node* BoneGetNode(Bone* ptr);
// WeakPtr<Node> Bone::node_ | File: ../Graphics/Skeleton.h
void BoneSetNode(Node* node, Bone* ptr);

#define REGISTER_MANUAL_PART_Bone(T, className) \
    /* WeakPtr<Node> Bone::node_ | File: ../Graphics/Skeleton.h */ \
    engine->RegisterObjectMethod(className, "void set_node(Node@+)", asFUNCTION(BoneSetNode), asCALL_CDECL_OBJLAST); \
    /* WeakPtr<Node> Bone::node_ | File: ../Graphics/Skeleton.h */ \
    engine->RegisterObjectMethod(className, "Node@+ get_node() const", asFUNCTION(BoneGetNode), asCALL_CDECL_OBJLAST);

// ========================================================================================

#define REGISTER_MANUAL_PART_Component(T, className) \
    /* Workarounds for Connection that used outside URHO3D_NETWORK define */ \
    if (URHO3D_NETWORK_DEFINED) \
    { \
        /* void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h */ \
        engine->RegisterObjectMethod(className, "void CleanupConnection(Connection@+)", asMETHODPR(T, CleanupConnection, (Connection*), void), asCALL_THISCALL); \
    }

}
