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

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/Manual_Scene.h"

#ifdef URHO3D_PHYSICS
#include "../Physics/PhysicsWorld.h"
#endif

#ifdef URHO3D_URHO2D
#include "../Urho2D/PhysicsWorld2D.h"
#endif

namespace Urho3D
{

// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst_Scene(asIScriptEngine* engine)
{
}

// ========================================================================================

#ifdef URHO3D_PHYSICS
// template<class T> T * Node::GetComponent(bool recursive=false) const | File: ../Scene/Node.h
static PhysicsWorld* SceneGetPhysicsWorld(Scene* ptr)
{
    return ptr->GetComponent<PhysicsWorld>();
}
#endif


#ifdef URHO3D_URHO2D
// template<class T> T * Node::GetComponent(bool recursive=false) const | File: ../Scene/Node.h
static PhysicsWorld2D* SceneGetPhysicsWorld2D(Scene* ptr)
{
    return ptr->GetComponent<PhysicsWorld2D>();
}
#endif

// This function is called after ASRegisterGenerated()
void ASRegisterManualLast_Scene(asIScriptEngine* engine)
{
#ifdef URHO3D_PHYSICS
    // template<class T> T * Node::GetComponent(bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "PhysicsWorld@+ get_physicsWorld() const", asFUNCTION(SceneGetPhysicsWorld), asCALL_CDECL_OBJLAST);
#endif

#ifdef URHO3D_URHO2D
    // template<class T> T * Node::GetComponent(bool recursive=false) const | File: ../Scene/Node.h
    engine->RegisterObjectMethod("Scene", "PhysicsWorld2D@+ get_physicsWorld2D() const", asFUNCTION(SceneGetPhysicsWorld2D), asCALL_CDECL_OBJLAST);
#endif
}

// ========================================================================================

static const AttributeInfo noAttributeInfo{};

const AttributeInfo& SerializableGetAttributeInfo(unsigned index, Serializable* ptr)
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

// ========================================================================================

// bool Node::SaveXML(Serializer &dest, const String &indentation="\t") const | File: ../Scene/Node.h
bool NodeSaveXML(File* file, const String& indentation, Node* ptr)
{
    return file && ptr->SaveXML(*file, indentation);
}

// bool Node::SaveXML(Serializer &dest, const String &indentation="\t") const | File: ../Scene/Node.h
bool NodeSaveXMLVectorBuffer(VectorBuffer& buffer, const String& indentation, Node* ptr)
{
    return ptr->SaveXML(buffer, indentation);
}

// bool Node::SaveJSON(Serializer &dest, const String &indentation="\t") const | File: ../Scene/Node.h
bool NodeSaveJSON(File* file, Node* ptr)
{
    return file && ptr->SaveJSON(*file);
}

// bool Node::SaveJSON(Serializer &dest, const String &indentation="\t") const | File: ../Scene/Node.h
bool NodeSaveJSONVectorBuffer(VectorBuffer& buffer, Node* ptr)
{
    return ptr->SaveJSON(buffer);
}

// template<class T> void Node::GetChildrenWithComponent(PODVector< Node * > &dest, bool recursive=false) const | File: ../Scene/Node.h
CScriptArray* NodeGetChildrenWithScript(bool recursive, Node* ptr)
{
    PODVector<Node*> nodes;
    ptr->GetChildrenWithComponent<ScriptInstance>(nodes, recursive);
    return VectorToHandleArray<Node>(nodes, "Array<Node@>");
}

// template<class T> void Node::GetChildrenWithComponent(PODVector< Node * > &dest, bool recursive=false) const | File: ../Scene/Node.h
CScriptArray* NodeGetChildrenWithClassName(const String& className, bool recursive, Node* ptr)
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
            if (auto* instance = (*j)->Cast<ScriptInstance>())
            {
                if (instance->IsA(className))
                    result.Push(node);
            }
        }
    }

    return VectorToHandleArray<Node>(result, "Array<Node@>");
}

// void Node::GetComponents(PODVector< Component * > &dest, StringHash type, bool recursive=false) const | File: ../Scene/Node.h
CScriptArray* NodeGetComponentsWithType(const String& typeName, bool recursive, Node* ptr)
{
    PODVector<Component*> components;
    ptr->GetComponents(components, typeName, recursive);
    return VectorToHandleArray<Component>(components, "Array<Component@>");
}

// unsigned Node::GetNumChildren(bool recursive=false) const | File: ../Scene/Node.h
unsigned NodeGetNumChildrenNonRecursive(Node* ptr)
{
    return ptr->GetNumChildren(false);
}

// unsigned Node::GetNumChildren(bool recursive=false) const | File: ../Scene/Node.h
unsigned NodeGetNumChildrenRecursive(Node* ptr)
{
    return ptr->GetNumChildren(true);
}

// Node* Node::GetChild(unsigned index) const | File: ../Scene/Node.h
Node* NodeGetChild(unsigned index, Node* ptr)
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

// Node* Node::GetChild(const String &name, bool recursive=false) const | File: ../Scene/Node.h
Node* NodeGetChildByName(const String& name, Node* ptr)
{
    return ptr->GetChild(name);
}

// Node* Node::GetChild(const String &name, bool recursive=false) const | File: ../Scene/Node.h
Node* NodeGetChildByNameRecursive(const String& name, Node* ptr)
{
    return ptr->GetChild(name, true);
}

// const VariantMap& Node::GetVars() const | File: ../Scene/Node.h
VariantMap& NodeGetVars(Node* ptr)
{
    // Assume that the vars will be modified and queue a network update attribute check
    ptr->MarkNetworkUpdate();
    return const_cast<VariantMap&>(ptr->GetVars());
}

// const Vector<SharedPtr<Component> >& Node::GetComponents() const | File: ../Scene/Node.h
Component* NodeGetComponent(unsigned index, Node* ptr)
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

// ========================================================================================

// bool Scene::LoadXML(Deserializer &source) | File: ../Scene/Scene.h
bool SceneLoadXML(File* file, Scene* ptr)
{
    return file && ptr->LoadXML(*file);
}

// bool Scene::LoadXML(Deserializer &source) | File: ../Scene/Scene.h
bool SceneLoadXMLVectorBuffer(VectorBuffer& buffer, Scene* ptr)
{
    return ptr->LoadXML(buffer);
}

// bool Scene::LoadJSON(Deserializer &source) | File: ../Scene/Scene.h
bool SceneLoadJSON(File* file, Scene* ptr)
{
    return file && ptr->LoadJSON(*file);
}

// bool Scene::LoadJSON(Deserializer &source) | File: ../Scene/Scene.h
bool SceneLoadJSONVectorBuffer(VectorBuffer& buffer, Scene* ptr)
{
    return ptr->LoadJSON(buffer);
}

// Node* Scene::Instantiate(Deserializer &source, const Vector3 &position, const Quaternion &rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
Node* SceneInstantiate(File* file, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr)
{
    return file ? ptr->Instantiate(*file, position, rotation, mode) : nullptr;
}

// Node* Scene::Instantiate(Deserializer &source, const Vector3 &position, const Quaternion &rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
Node* SceneInstantiateVectorBuffer(VectorBuffer& buffer, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr)
{
    return ptr->Instantiate(buffer, position, rotation, mode);
}

// Node* Scene::InstantiateXML(Deserializer &source, const Vector3 &position, const Quaternion &rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
Node* SceneInstantiateXML(File* file, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr)
{
    return file ? ptr->InstantiateXML(*file, position, rotation, mode) : nullptr;
}

// Node* Scene::InstantiateXML(Deserializer &source, const Vector3 &position, const Quaternion &rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
Node* SceneInstantiateXMLVectorBuffer(VectorBuffer& buffer, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr)
{
    return ptr->InstantiateXML(buffer, position, rotation, mode);
}

// Node* Scene::InstantiateXML(Deserializer &source, const Vector3 &position, const Quaternion &rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
Node* SceneInstantiateXMLFile(XMLFile* xml, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr)
{
    return xml ? ptr->InstantiateXML(xml->GetRoot(), position, rotation, mode) : nullptr;
}

// Node* Scene::InstantiateJSON(Deserializer &source, const Vector3 &position, const Quaternion &rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
Node* SceneInstantiateJSON(File* file, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr)
{
    return file ? ptr->InstantiateJSON(*file, position, rotation, mode) : nullptr;
}

// Node* Scene::InstantiateJSON(Deserializer &source, const Vector3 &position, const Quaternion &rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
Node* SceneInstantiateJSONVectorBuffer(VectorBuffer& buffer, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr)
{
    return ptr->InstantiateJSON(buffer, position, rotation, mode);
}

// Node* Scene::InstantiateJSON(Deserializer &source, const Vector3 &position, const Quaternion &rotation, CreateMode mode=REPLICATED) | File: ../Scene/Scene.h
Node* SceneInstantiateJSONFile(JSONFile* json, const Vector3& position, const Quaternion& rotation, CreateMode mode, Scene* ptr)
{
    return json ? ptr->InstantiateJSON(json->GetRoot(), position, rotation, mode) : nullptr;
}

// bool Scene::GetNodesWithTag(PODVector< Node * > &dest, const String &tag) const | File: ../Scene/Scene.h
CScriptArray* SceneGetNodesWithTag(const String& tag, Scene* ptr)
{
    PODVector<Node*> nodes;
    ptr->GetNodesWithTag(nodes, tag);
    return VectorToHandleArray<Node>(nodes, "Array<Node@>");
}

// template<class T> T * Node::GetComponent(bool recursive=false) const | File: ../Scene/Node.h
DebugRenderer* SceneGetDebugRenderer(Scene* ptr)
{
    return ptr->GetComponent<DebugRenderer>();
}

// template<class T> T * Node::GetComponent(bool recursive=false) const | File: ../Scene/Node.h
Octree* SceneGetOctree(Scene* ptr)
{
    return ptr->GetComponent<Octree>();
}

// ========================================================================================

// WeakPtr<Node> Bone::node_ | File: ../Graphics/Skeleton.h
Node* BoneGetNode(Bone* ptr)
{
    return ptr->node_;
}

// WeakPtr<Node> Bone::node_ | File: ../Graphics/Skeleton.h
void BoneSetNode(Node* node, Bone* ptr)
{
    ptr->node_ = node;
}

}
