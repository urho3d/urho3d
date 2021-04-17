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

static const AttributeInfo noAttributeInfo;

template <class T> const AttributeInfo& Serializable_GetAttributeInfo(unsigned index, T* ptr)
{
    const Vector<AttributeInfo>* attributes = ptr->GetAttributes();
    if (!attributes || index >= attributes->Size())
    {
        GetActiveASContext()->SetException("Index out of bounds");
        return noAttributeInfo;
    }
    else
        return attributes->At(index);
}

#define REGISTER_MEMBERS_MANUAL_PART_Serializable() \
    engine->RegisterObjectMethod(className, "const AttributeInfo& get_attributeInfos(uint) const", AS_FUNCTION_OBJLAST(Serializable_GetAttributeInfo<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// bool Node::SaveXML(Serializer& dest, const String& indentation = "\t") const | File: ../Scene/Node.h
template <class T> bool Node_SaveXML_File(File* file, const String& indentation, T* ptr)
{
    return file && ptr->SaveXML(*file, indentation);
}

// bool Node::SaveXML(Serializer& dest, const String& indentation = "\t") const | File: ../Scene/Node.h
template <class T> bool Node_SaveXML_VectorBuffer(VectorBuffer& buffer, const String& indentation, T* ptr)
{
    return ptr->SaveXML(buffer, indentation);
}

// bool Node::SaveJSON(Serializer& dest, const String& indentation = "\t") const | File: ../Scene/Node.h
template <class T> bool Node_SaveJSON_File(File* file, T* ptr)
{
    return file && ptr->SaveJSON(*file);
}

// bool Node::SaveJSON(Serializer& dest, const String& indentation = "\t") const | File: ../Scene/Node.h
template <class T> bool Node_SaveJSON_VectorBuffer(VectorBuffer& buffer, T* ptr)
{
    return ptr->SaveJSON(buffer);
}

// template <class T> void Node::GetChildrenWithComponent(PODVector<Node*>& dest, bool recursive = false) const | File: ../Scene/Node.h
template <class T> CScriptArray* Node_GetChildren_Script(bool recursive, T* ptr)
{
    PODVector<Node*> nodes;
    ptr->template GetChildrenWithComponent<ScriptInstance>(nodes, recursive);
    return VectorToHandleArray<Node>(nodes, "Array<Node@>");
}

// template <class T> void Node::GetChildrenWithComponent(PODVector<Node*>& dest, bool recursive = false) const | File: ../Scene/Node.h
template <class T> CScriptArray* Node_GetChildren_Script_ClassName(const String& className, bool recursive, T* ptr)
{
    PODVector<Node*> nodes;
    ptr->template GetChildrenWithComponent<ScriptInstance>(nodes, recursive);

    PODVector<Node*> result;

    for (PODVector<Node*>::Iterator i = nodes.Begin(); i != nodes.End(); ++i)
    {
        Node* node = *i;
        const Vector<SharedPtr<Component> >& components = node->GetComponents();
        for (Vector<SharedPtr<Component> >::ConstIterator j = components.Begin(); j != components.End(); ++j)
        {
            if (auto* instance = (*j)->Cast<ScriptInstance>())
            {
                if (instance->IsA(className))
                    result.Push(node);
            }
        }
    }

    return VectorToHandleArray<Node>(result, "Array<Node@>");
}

// void Node::GetComponents(PODVector<Component*>& dest, StringHash type, bool recursive = false) const | File: ../Scene/Node.h
template <class T> CScriptArray* Node_GetComponents_Type(const String& typeName, bool recursive, T* ptr)
{
    PODVector<Component*> components;
    ptr->GetComponents(components, typeName, recursive);
    return VectorToHandleArray<Component>(components, "Array<Component@>");
}

// unsigned Node::GetNumChildren(bool recursive = false) const | File: ../Scene/Node.h
template <class T> unsigned Node_GetNumChildren_NonRecursive(T* ptr)
{
    return ptr->GetNumChildren(false);
}

// unsigned Node::GetNumChildren(bool recursive = false) const | File: ../Scene/Node.h
template <class T> unsigned Node_GetNumChildren_Recursive(T* ptr)
{
    return ptr->GetNumChildren(true);
}

// Node* Node::GetChild(unsigned index) const | File: ../Scene/Node.h
template <class T> Node* Node_GetChild(unsigned index, T* ptr)
{
    const Vector<SharedPtr<Node> >& children = ptr->GetChildren();
    if (index >= children.Size())
    {
        GetActiveASContext()->SetException("Index out of bounds");
        return nullptr;
    }
    else
        return children[index].Get();
}

// Node* Node::GetChild(const String& name, bool recursive = false) const | File: ../Scene/Node.h
template <class T> Node* Node_GetChild_Name_NonRecursive(const String& name, T* ptr)
{
    return ptr->GetChild(name, false);
}

// Node* Node::GetChild(const String& name, bool recursive = false) const | File: ../Scene/Node.h
template <class T> Node* Node_GetChild_Name_Recursive(const String& name, T* ptr)
{
    return ptr->GetChild(name, true);
}

// const Vector<SharedPtr<Component>>& Node::GetComponents() const | File: ../Scene/Node.h
template <class T> Component* Node_GetComponent(unsigned index, T* ptr)
{
    const Vector<SharedPtr<Component> >& components = ptr->GetComponents();
    if (index >= components.Size())
    {
        GetActiveASContext()->SetException("Index out of bounds");
        return nullptr;
    }
    else
        return components[index];
}

// const VariantMap& Node::GetVars() const | File: ../Scene/Node.h
template <class T> VariantMap& Node_GetVars(T* ptr)
{
    // Assume that the vars will be modified and queue a network update attribute check
    ptr->MarkNetworkUpdate();
    return const_cast<VariantMap&>(ptr->GetVars());
}

#define REGISTER_MEMBERS_MANUAL_PART_Node() \
    RegisterNamedObjectConstructor<T>(engine, className); \
    \
    /* bool Node::SaveXML(Serializer& dest, const String& indentation = "\t") const | File: ../Scene/Node.h */ \
    engine->RegisterObjectMethod(className, "bool SaveXML(File@+, const String&in = \"\t\")", AS_FUNCTION_OBJLAST(Node_SaveXML_File<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "bool SaveXML(VectorBuffer&, const String&in = \"\t\")", AS_FUNCTION_OBJLAST(Node_SaveXML_VectorBuffer<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* bool Node::SaveJSON(Serializer& dest, const String& indentation = "\t") const | File: ../Scene/Node.h */ \
    engine->RegisterObjectMethod(className, "bool SaveJSON(File@+)", AS_FUNCTION_OBJLAST(Node_SaveJSON_File<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "bool SaveJSON(VectorBuffer&)", AS_FUNCTION_OBJLAST(Node_SaveJSON_VectorBuffer<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* template <class T> void Node::GetChildrenWithComponent(PODVector<Node*>& dest, bool recursive = false) const | File: ../Scene/Node.h */ \
    engine->RegisterObjectMethod(className, "Array<Node@>@ GetChildrenWithScript(bool = false) const", AS_FUNCTION_OBJLAST(Node_GetChildren_Script<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "Array<Node@>@ GetChildrenWithScript(const String&in, bool = false) const", AS_FUNCTION_OBJLAST(Node_GetChildren_Script_ClassName<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* void Node::GetComponents(PODVector<Component*>& dest, StringHash type, bool recursive = false) const | File: ../Scene/Node.h */ \
    engine->RegisterObjectMethod(className, "Array<Component@>@ GetComponents(const String&in, bool = false) const", AS_FUNCTION_OBJLAST(Node_GetComponents_Type<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* unsigned Node::GetNumChildren(bool recursive = false) const | File: ../Scene/Node.h */ \
    engine->RegisterObjectMethod(className, "uint get_numChildren() const", AS_FUNCTION_OBJLAST(Node_GetNumChildren_NonRecursive<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "uint get_numAllChildren() const", AS_FUNCTION_OBJLAST(Node_GetNumChildren_Recursive<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* Node* Node::GetChild(unsigned index) const | File: ../Scene/Node.h */ \
    engine->RegisterObjectMethod(className, "Node@+ get_children(uint) const", AS_FUNCTION_OBJLAST(Node_GetChild<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* Node* Node::GetChild(const String& name, bool recursive = false) const | File: ../Scene/Node.h */ \
    engine->RegisterObjectMethod(className, "Node@+ get_childrenByName(const String&in) const", AS_FUNCTION_OBJLAST(Node_GetChild_Name_NonRecursive<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "Node@+ get_allChildrenByName(const String&in) const", AS_FUNCTION_OBJLAST(Node_GetChild_Name_Recursive<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* const Vector<SharedPtr<Component>>& Node::GetComponents() const | File: ../Scene/Node.h */ \
    engine->RegisterObjectMethod(className, "Component@+ get_components(uint) const", AS_FUNCTION_OBJLAST(Node_GetComponent<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* const VariantMap& Node::GetVars() const | File: ../Scene/Node.h */ \
    engine->RegisterObjectMethod(className, "VariantMap& get_vars()", AS_FUNCTION_OBJLAST(Node_GetVars<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* Workarounds for Connection that used outside URHO3D_NETWORK define */ \
    if (URHO3D_NETWORK_DEFINED) \
    { \
        /* void Node::SetOwner(Connection* owner) | File: ../Scene/Node.h */ \
        engine->RegisterObjectMethod(className, "void SetOwner(Connection@+)", AS_METHOD(T, SetOwner), AS_CALL_THISCALL); \
        engine->RegisterObjectMethod(className, "void set_owner(Connection@+)", AS_METHOD(T, SetOwner), AS_CALL_THISCALL); \
        \
        /* Connection* Node::GetOwner() const | File: ../Scene/Node.h */ \
        engine->RegisterObjectMethod(className, "Connection@+ GetOwner() const", AS_METHOD(T, GetOwner), AS_CALL_THISCALL); \
        engine->RegisterObjectMethod(className, "Connection@+ get_owner() const", AS_METHOD(T, GetOwner), AS_CALL_THISCALL); \
        \
        /* void Node::CleanupConnection(Connection* connection) | File: ../Scene/Node.h */ \
        engine->RegisterObjectMethod(className, "void CleanupConnection(Connection@+)", AS_METHOD(T, CleanupConnection), AS_CALL_THISCALL); \
    }

// ========================================================================================

// bool Scene::LoadXML(Deserializer& source) | File: ../Scene/Scene.h
template <class T> bool Scene_LoadXML_File(File* file, T* ptr)
{
    return file && ptr->LoadXML(*file);
}

// bool Scene::LoadXML(Deserializer& source) | File: ../Scene/Scene.h
template <class T> bool Scene_LoadXML_VectorBuffer(VectorBuffer& buffer, T* ptr)
{
    return ptr->LoadXML(buffer);
}

// bool Scene::LoadJSON(Deserializer& source) | File: ../Scene/Scene.h
template <class T> bool Scene_LoadJSON_File(File* file, T* ptr)
{
    return file && ptr->LoadJSON(*file);
}

// bool Scene::LoadJSON(Deserializer& source) | File: ../Scene/Scene.h
template <class T> bool Scene_LoadJSON_VectorBuffer(VectorBuffer& buffer, T* ptr)
{
    return ptr->LoadJSON(buffer);
}

// Node* Scene::Instantiate(Deserializer& source, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED) | File: ../Scene/Scene.h
template <class T> Node* Scene_Instantiate_File(File* file, const Vector3& position, const Quaternion& rotation, CreateMode mode, T* ptr)
{
    return file ? ptr->Instantiate(*file, position, rotation, mode) : nullptr;
}

// Node* Scene::Instantiate(Deserializer& source, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED) | File: ../Scene/Scene.h
template <class T> Node* Scene_Instantiate_VectorBuffer(VectorBuffer& buffer, const Vector3& position, const Quaternion& rotation, CreateMode mode, T* ptr)
{
    return ptr->Instantiate(buffer, position, rotation, mode);
}

// Node* Scene::InstantiateXML(Deserializer& source, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED) | File: ../Scene/Scene.h
template <class T> Node* Scene_InstantiateXML_File(File* file, const Vector3& position, const Quaternion& rotation, CreateMode mode, T* ptr)
{
    return file ? ptr->InstantiateXML(*file, position, rotation, mode) : nullptr;
}

// Node* Scene::InstantiateXML(Deserializer& source, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED) | File: ../Scene/Scene.h
template <class T> Node* Scene_InstantiateXML_VectorBuffer(VectorBuffer& buffer, const Vector3& position, const Quaternion& rotation, CreateMode mode, T* ptr)
{
    return ptr->InstantiateXML(buffer, position, rotation, mode);
}

// Node* Scene::InstantiateJSON(Deserializer& source, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED) | File: ../Scene/Scene.h
template <class T> Node* Scene_InstantiateJSON_File(File* file, const Vector3& position, const Quaternion& rotation, CreateMode mode, T* ptr)
{
    return file ? ptr->InstantiateJSON(*file, position, rotation, mode) : nullptr;
}

// Node* Scene::InstantiateJSON(Deserializer& source, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED) | File: ../Scene/Scene.h
template <class T> Node* Scene_InstantiateJSON_VectorBuffer(VectorBuffer& buffer, const Vector3& position, const Quaternion& rotation, CreateMode mode, T* ptr)
{
    return ptr->InstantiateJSON(buffer, position, rotation, mode);
}

// Node* Scene::InstantiateXML(const XMLElement& source, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED) | File: ../Scene/Scene.h
template <class T> Node* Scene_InstantiateXML_XMLFile(XMLFile* xml, const Vector3& position, const Quaternion& rotation, CreateMode mode, T* ptr)
{
    return xml ? ptr->InstantiateXML(xml->GetRoot(), position, rotation, mode) : nullptr;
}

// Node* Scene::InstantiateJSON(const JSONValue& source, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED)  | File: ../Scene/Scene.h
template <class T> Node* Scene_InstantiateJSON_JSONFile(JSONFile* json, const Vector3& position, const Quaternion& rotation, CreateMode mode, T* ptr)
{
    return json ? ptr->InstantiateJSON(json->GetRoot(), position, rotation, mode) : nullptr;
}

// bool Scene::GetNodesWithTag(PODVector<Node*>& dest, const String& tag) const | File: ../Scene/Scene.h
template <class T> CScriptArray* Scene_GetNodesWithTag(const String& tag, T* ptr)
{
    PODVector<Node*> nodes;
    ptr->GetNodesWithTag(nodes, tag);
    return VectorToHandleArray<Node>(nodes, "Array<Node@>");
}

// template <class T> T* Scene::GetComponent(bool recursive = false) const | File: ../Scene/Node.h
template <class T> DebugRenderer* Scene_GetDebugRenderer(T* ptr)
{
    return ptr->template GetComponent<DebugRenderer>();
}

// template <class T> T* Scene::GetComponent(bool recursive = false) const | File: ../Scene/Node.h
template <class T> Octree* Scene_GetOctree(T* ptr)
{
    return ptr->template GetComponent<Octree>();
}

#define REGISTER_MEMBERS_MANUAL_PART_Scene() \
    /* bool Scene::LoadXML(Deserializer& source) | File: ../Scene/Scene.h */ \
    engine->RegisterObjectMethod(className, "bool LoadXML(File@+)", AS_FUNCTION_OBJLAST(Scene_LoadXML_File<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "bool LoadXML(VectorBuffer&)", AS_FUNCTION_OBJLAST(Scene_LoadXML_VectorBuffer<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* bool Scene::LoadJSON(Deserializer& source) | File: ../Scene/Scene.h */ \
    engine->RegisterObjectMethod(className, "bool LoadJSON(File@+)", AS_FUNCTION_OBJLAST(Scene_LoadJSON_File<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "bool LoadJSON(VectorBuffer&)", AS_FUNCTION_OBJLAST(Scene_LoadJSON_VectorBuffer<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* Node* Scene::Instantiate(Deserializer& source, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED) | File: ../Scene/Scene.h */ \
    engine->RegisterObjectMethod(className, "Node@+ Instantiate(File@+, const Vector3&in, const Quaternion&in, CreateMode = REPLICATED)", AS_FUNCTION_OBJLAST(Scene_Instantiate_File<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "Node@+ Instantiate(VectorBuffer&, const Vector3&in, const Quaternion&in, CreateMode = REPLICATED)", AS_FUNCTION_OBJLAST(Scene_Instantiate_VectorBuffer<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* Node* Scene::InstantiateXML(Deserializer& source, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED) | File: ../Scene/Scene.h */ \
    engine->RegisterObjectMethod(className, "Node@+ InstantiateXML(File@+, const Vector3&in, const Quaternion&in, CreateMode = REPLICATED)", AS_FUNCTION_OBJLAST(Scene_InstantiateXML_File<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "Node@+ InstantiateXML(VectorBuffer&, const Vector3&in, const Quaternion&in, CreateMode = REPLICATED)", AS_FUNCTION_OBJLAST(Scene_InstantiateXML_VectorBuffer<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /*Node* Scene::InstantiateJSON(Deserializer& source, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED) | File: ../Scene/Scene.h */ \
    engine->RegisterObjectMethod(className, "Node@+ InstantiateJSON(File@+, const Vector3&in, const Quaternion&in, CreateMode = REPLICATED)", AS_FUNCTION_OBJLAST(Scene_InstantiateJSON_File<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "Node@+ InstantiateJSON(VectorBuffer&, const Vector3&in, const Quaternion&in, CreateMode = REPLICATED)", AS_FUNCTION_OBJLAST(Scene_InstantiateJSON_VectorBuffer<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* Node* Scene::InstantiateXML(const XMLElement& source, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED) | File: ../Scene/Scene.h */ \
    engine->RegisterObjectMethod(className, "Node@+ InstantiateXML(XMLFile@+, const Vector3&in, const Quaternion&in, CreateMode = REPLICATED)", AS_FUNCTION_OBJLAST(Scene_InstantiateXML_XMLFile<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* Node* Scene::InstantiateJSON(const JSONValue& source, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED)  | File: ../Scene/Scene.h */ \
    engine->RegisterObjectMethod(className, "Node@+ InstantiateJSON(JSONFile@+, const Vector3&in, const Quaternion&in, CreateMode = REPLICATED)", AS_FUNCTION_OBJLAST(Scene_InstantiateJSON_JSONFile<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* bool Scene::GetNodesWithTag(PODVector<Node*>& dest, const String& tag) const | File: ../Scene/Scene.h */ \
    engine->RegisterObjectMethod(className, "Array<Node@>@ GetNodesWithTag(const String&in) const", AS_FUNCTION_OBJLAST(Scene_GetNodesWithTag<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* template <class T> T* Scene::GetComponent(bool recursive = false) const | File: ../Scene/Node.h */ \
    engine->RegisterObjectMethod(className, "DebugRenderer@+ get_debugRenderer() const", AS_FUNCTION_OBJLAST(Scene_GetDebugRenderer<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "Octree@+ get_octree() const", AS_FUNCTION_OBJLAST(Scene_GetOctree<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* Workaround Doxygen bug: have no const flag in xml (but already registered in template because string GetSignature(const MethodAnalyzer& method) ignores const) */ \
    /* Component* Node::GetComponent(StringHash type, bool recursive=false) const | File: ../Scene/Scene.h */ \
    /*engine->RegisterObjectMethod(className, "Component@+ GetComponent(StringHash, bool = false) const", AS_METHODPR(Scene, GetComponent, (StringHash, bool) const, Component*), AS_CALL_THISCALL);*/ \
    /* bool Node::SaveXML(XMLElement &dest) const override | File: ../Scene/Scene.h */ \
    /*engine->RegisterObjectMethod(className, "bool SaveXML(XMLElement&) const", AS_METHODPR(Scene, SaveXML, (XMLElement &) const, bool), AS_CALL_THISCALL);*/ \
    /* bool Node::SaveJSON(JSONValue &dest) const override | File: ../Scene/Scene.h */ \
    /*engine->RegisterObjectMethod(className, "bool SaveJSON(JSONValue&) const", AS_METHODPR(Scene, SaveJSON, (JSONValue &) const, bool), AS_CALL_THISCALL);*/

// ========================================================================================

// WeakPtr<Node> Bone::node_ | File: ../Graphics/Skeleton.h
template <class T> Node* Bone_GetNode(T* ptr)
{
    return ptr->node_;
}

// WeakPtr<Node> Bone::node_ | File: ../Graphics/Skeleton.h
template <class T> void Bone_SetNode(Node* node, T* ptr)
{
    ptr->node_ = node;
}

#define REGISTER_MEMBERS_MANUAL_PART_Bone() \
    /* WeakPtr<Node> Bone::node_ | File: ../Graphics/Skeleton.h */ \
    engine->RegisterObjectMethod(className, "void set_node(Node@+)", AS_FUNCTION_OBJLAST(Bone_SetNode<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "Node@+ get_node() const", AS_FUNCTION_OBJLAST(Bone_GetNode<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

#define REGISTER_MEMBERS_MANUAL_PART_Component() \
    /* Workarounds for Connection that used outside URHO3D_NETWORK define */ \
    if (URHO3D_NETWORK_DEFINED) \
    { \
        /* void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h */ \
        engine->RegisterObjectMethod(className, "void CleanupConnection(Connection@+)", AS_METHODPR(T, CleanupConnection, (Connection*), void), AS_CALL_THISCALL); \
    }

}
