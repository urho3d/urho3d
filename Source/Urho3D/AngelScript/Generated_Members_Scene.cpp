// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/GeneratedClassMembers.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

// struct AsyncProgress | File: ../Scene/Scene.h
void CollectMembers_AsyncProgress(MemberCollection& members)
{
    // SharedPtr<File> AsyncProgress::file_
    // Error: type "SharedPtr<File>" can not automatically bind
    // SharedPtr<XMLFile> AsyncProgress::xmlFile_
    // Error: type "SharedPtr<XMLFile>" can not automatically bind
    // SharedPtr<JSONFile> AsyncProgress::jsonFile_
    // Error: type "SharedPtr<JSONFile>" can not automatically bind
    // HashSet<StringHash> AsyncProgress::resources_
    // Error: type "HashSet<StringHash>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("XMLElement AsyncProgress::xmlElement_", "XMLElement xmlElement", offsetof(AsyncProgress, xmlElement_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned AsyncProgress::jsonIndex_", "uint jsonIndex", offsetof(AsyncProgress, jsonIndex_)));
    members.fields_.Push(RegisterObjectPropertyArgs("LoadMode AsyncProgress::mode_", "LoadMode mode", offsetof(AsyncProgress, mode_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned AsyncProgress::loadedResources_", "uint loadedResources", offsetof(AsyncProgress, loadedResources_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned AsyncProgress::totalResources_", "uint totalResources", offsetof(AsyncProgress, totalResources_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned AsyncProgress::loadedNodes_", "uint loadedNodes", offsetof(AsyncProgress, loadedNodes_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned AsyncProgress::totalNodes_", "uint totalNodes", offsetof(AsyncProgress, totalNodes_)));

}

// struct DirtyBits | File: ../Scene/ReplicationState.h
void CollectMembers_DirtyBits(MemberCollection& members)
{
    // unsigned char DirtyBits::data_[MAX_NETWORK_ATTRIBUTES/8]
    // Not registered because array

    members.fields_.Push(RegisterObjectPropertyArgs("unsigned char DirtyBits::count_", "uint8 count", offsetof(DirtyBits, count_)));

}

// struct NetworkState | File: ../Scene/ReplicationState.h
void CollectMembers_NetworkState(MemberCollection& members)
{
    // const Vector<AttributeInfo>* NetworkState::attributes_
    // Not registered because pointer
    // Vector<Variant> NetworkState::currentValues_
    // Error: type "Vector<Variant>" can not automatically bind
    // Vector<Variant> NetworkState::previousValues_
    // Error: type "Vector<Variant>" can not automatically bind
    // PODVector<ReplicationState*> NetworkState::replicationStates_
    // Error: type "PODVector<ReplicationState*>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("VariantMap NetworkState::previousVars_", "VariantMap previousVars", offsetof(NetworkState, previousVars_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned long long NetworkState::interceptMask_", "uint64 interceptMask", offsetof(NetworkState, interceptMask_)));

}

// struct NodeImpl | File: ../Scene/Node.h
void CollectMembers_NodeImpl(MemberCollection& members)
{
    // PODVector<Node*> NodeImpl::dependencyNodes_
    // Error: type "PODVector<Node*>" can not automatically bind
    // Connection* NodeImpl::owner_
    // Not registered because pointer
    // StringVector NodeImpl::tags_
    // Error: type "StringVector" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("String NodeImpl::name_", "String name", offsetof(NodeImpl, name_)));
    members.fields_.Push(RegisterObjectPropertyArgs("StringHash NodeImpl::nameHash_", "StringHash nameHash", offsetof(NodeImpl, nameHash_)));
    members.fields_.Push(RegisterObjectPropertyArgs("VectorBuffer NodeImpl::attrBuffer_", "VectorBuffer attrBuffer", offsetof(NodeImpl, attrBuffer_)));

}

// struct ReplicationState | File: ../Scene/ReplicationState.h
void CollectMembers_ReplicationState(MemberCollection& members)
{
    // Connection* ReplicationState::connection_
    // Not registered because pointer

}

// class SceneResolver | File: ../Scene/SceneResolver.h
void CollectMembers_SceneResolver(MemberCollection& members)
{
}

// struct VAnimEventFrame | File: ../Scene/ValueAnimation.h
void CollectMembers_VAnimEventFrame(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("float VAnimEventFrame::time_", "float time", offsetof(VAnimEventFrame, time_)));
    members.fields_.Push(RegisterObjectPropertyArgs("StringHash VAnimEventFrame::eventType_", "StringHash eventType", offsetof(VAnimEventFrame, eventType_)));
    members.fields_.Push(RegisterObjectPropertyArgs("VariantMap VAnimEventFrame::eventData_", "VariantMap eventData", offsetof(VAnimEventFrame, eventData_)));

}

// struct VAnimKeyFrame | File: ../Scene/ValueAnimation.h
void CollectMembers_VAnimKeyFrame(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("float VAnimKeyFrame::time_", "float time", offsetof(VAnimKeyFrame, time_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Variant VAnimKeyFrame::value_", "Variant value", offsetof(VAnimKeyFrame, value_)));

}

// struct ComponentReplicationState | File: ../Scene/ReplicationState.h
void CollectMembers_ComponentReplicationState(MemberCollection& members)
{
    CollectMembers_ReplicationState(members);

    // NodeReplicationState* ComponentReplicationState::nodeState_
    // Not registered because pointer
    // WeakPtr<Component> ComponentReplicationState::component_
    // Error: type "WeakPtr<Component>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("DirtyBits ComponentReplicationState::dirtyAttributes_", "DirtyBits dirtyAttributes", offsetof(ComponentReplicationState, dirtyAttributes_)));

}

// struct NodeReplicationState | File: ../Scene/ReplicationState.h
void CollectMembers_NodeReplicationState(MemberCollection& members)
{
    CollectMembers_ReplicationState(members);

    // SceneReplicationState* NodeReplicationState::sceneState_
    // Not registered because pointer
    // WeakPtr<Node> NodeReplicationState::node_
    // Error: type "WeakPtr<Node>" can not automatically bind
    // HashSet<StringHash> NodeReplicationState::dirtyVars_
    // Error: type "HashSet<StringHash>" can not automatically bind
    // HashMap<unsigned, ComponentReplicationState> NodeReplicationState::componentStates_
    // Error: type "HashMap<unsigned, ComponentReplicationState>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("DirtyBits NodeReplicationState::dirtyAttributes_", "DirtyBits dirtyAttributes", offsetof(NodeReplicationState, dirtyAttributes_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float NodeReplicationState::priorityAcc_", "float priorityAcc", offsetof(NodeReplicationState, priorityAcc_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool NodeReplicationState::markedDirty_", "bool markedDirty", offsetof(NodeReplicationState, markedDirty_)));

}

// struct SceneReplicationState | File: ../Scene/ReplicationState.h
void CollectMembers_SceneReplicationState(MemberCollection& members)
{
    CollectMembers_ReplicationState(members);

    // HashMap<unsigned, NodeReplicationState> SceneReplicationState::nodeStates_
    // Error: type "HashMap<unsigned, NodeReplicationState>" can not automatically bind
    // HashSet<unsigned> SceneReplicationState::dirtyNodes_
    // Error: type "HashSet<unsigned>" can not automatically bind

}

// class ValueAnimationInfo | File: ../Scene/ValueAnimationInfo.h
void CollectMembers_ValueAnimationInfo(MemberCollection& members)
{
    CollectMembers_RefCounted(members);

}

// class AttributeAnimationInfo | File: ../Scene/Animatable.h
void CollectMembers_AttributeAnimationInfo(MemberCollection& members)
{
    CollectMembers_ValueAnimationInfo(members);

}

// class Serializable | File: ../Scene/Serializable.h
void CollectMembers_Serializable(MemberCollection& members)
{
    CollectMembers_Object(members);

    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const
    // Error: type "NetworkState*" can not automatically bind

}

// class Animatable | File: ../Scene/Animatable.h
void CollectMembers_Animatable(MemberCollection& members)
{
    CollectMembers_Serializable(members);

    Remove(members.methods_, "virtual bool Serializable::LoadJSON(const JSONValue& source)");
    Remove(members.methods_, "virtual bool Serializable::LoadXML(const XMLElement& source)");
    Remove(members.methods_, "virtual bool Serializable::SaveJSON(JSONValue& dest) const");
    Remove(members.methods_, "virtual bool Serializable::SaveXML(XMLElement& dest) const");

    // static void Animatable::RegisterObject(Context* context)
    // Not registered because have @nobind mark

}

// class ObjectAnimation | File: ../Scene/ObjectAnimation.h
void CollectMembers_ObjectAnimation(MemberCollection& members)
{
    CollectMembers_Resource(members);

    Remove(members.methods_, "virtual bool Resource::BeginLoad(Deserializer& source)");
    Remove(members.methods_, "virtual bool Resource::Save(Serializer& dest) const");

    // const HashMap<String, SharedPtr<ValueAnimationInfo>>& ObjectAnimation::GetAttributeAnimationInfos() const
    // Error: type "const HashMap<String, SharedPtr<ValueAnimationInfo>>&" can not automatically bind

    // static void ObjectAnimation::RegisterObject(Context* context)
    // Not registered because have @nobind mark

}

// class ValueAnimation | File: ../Scene/ValueAnimation.h
void CollectMembers_ValueAnimation(MemberCollection& members)
{
    CollectMembers_Resource(members);

    Remove(members.methods_, "virtual bool Resource::BeginLoad(Deserializer& source)");
    Remove(members.methods_, "virtual bool Resource::Save(Serializer& dest) const");

    // void ValueAnimation::GetEventFrames(float beginTime, float endTime, PODVector<const VAnimEventFrame*>& eventFrames) const
    // Error: type "PODVector<const VAnimEventFrame*>&" can not automatically bind
    // const Vector<VAnimKeyFrame>& ValueAnimation::GetKeyFrames() const
    // Error: type "const Vector<VAnimKeyFrame>&" can not automatically bind
    // void* ValueAnimation::GetOwner() const
    // Error: type "void*" can not automatically bind
    // void ValueAnimation::SetOwner(void* owner)
    // Error: type "void*" can not automatically bind

    // static void ValueAnimation::RegisterObject(Context* context)
    // Not registered because have @nobind mark

}

// class Component | File: ../Scene/Component.h
void CollectMembers_Component(MemberCollection& members)
{
    CollectMembers_Animatable(members);

    Remove(members.methods_, "bool Animatable::SaveJSON(JSONValue& dest) const override");
    Remove(members.methods_, "bool Animatable::SaveXML(XMLElement& dest) const override");
    Remove(members.methods_, "virtual bool Serializable::Save(Serializer& dest) const");
    Remove(members.methods_, "virtual void Serializable::MarkNetworkUpdate()");

    // void Component::AddReplicationState(ComponentReplicationState* state)
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Component::CleanupConnection(Connection* connection)
    // Not registered because have @manualbind mark
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const
    // Error: type "PODVector<Component*>&" can not automatically bind
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest)
    // Error: type "PODVector<Node*>&" can not automatically bind

    // template <class T> T* Component::GetComponent() const
    // Not registered because template
    // template <class T> void Component::GetComponents(PODVector<T*>& dest) const
    // Not registered because template

}

// class Node | File: ../Scene/Node.h
void CollectMembers_Node(MemberCollection& members)
{
    CollectMembers_Animatable(members);

    Remove(members.methods_, "bool Animatable::LoadJSON(const JSONValue& source) override");
    Remove(members.methods_, "bool Animatable::LoadXML(const XMLElement& source) override");
    Remove(members.methods_, "bool Animatable::SaveJSON(JSONValue& dest) const override");
    Remove(members.methods_, "bool Animatable::SaveXML(XMLElement& dest) const override");
    Remove(members.methods_, "virtual bool Serializable::Load(Deserializer& source)");
    Remove(members.methods_, "virtual bool Serializable::Save(Serializer& dest) const");
    Remove(members.methods_, "virtual bool Serializable::SaveDefaultAttributes() const");
    Remove(members.methods_, "virtual void Serializable::ApplyAttributes()");
    Remove(members.methods_, "virtual void Serializable::MarkNetworkUpdate()");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

    // virtual void Node::AddReplicationState(NodeReplicationState* state)
    // Error: type "NodeReplicationState*" can not automatically bind
    // void Node::CleanupConnection(Connection* connection)
    // Not registered because have @manualbind mark
    // Node* Node::GetChild(const char* name, bool recursive = false) const
    // Error: type "const char*" can not automatically bind
    // void Node::GetChildren(PODVector<Node*>& dest, bool recursive = false) const
    // Error: type "PODVector<Node*>&" can not automatically bind
    // void Node::GetChildrenWithComponent(PODVector<Node*>& dest, StringHash type, bool recursive = false) const
    // Error: type "PODVector<Node*>&" can not automatically bind
    // void Node::GetChildrenWithTag(PODVector<Node*>& dest, const String& tag, bool recursive = false) const
    // Error: type "PODVector<Node*>&" can not automatically bind
    // void Node::GetComponents(PODVector<Component*>& dest, StringHash type, bool recursive = false) const
    // Error: type "PODVector<Component*>&" can not automatically bind
    // const Vector<WeakPtr<Component>> Node::GetListeners() const
    // Error: type "const Vector<WeakPtr<Component>>" can not automatically bind
    // const PODVector<unsigned char>& Node::GetNetParentAttr() const
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // const PODVector<unsigned char>& Node::GetNetRotationAttr() const
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // Connection* Node::GetOwner() const
    // Not registered because have @manualbind mark
    // void Node::SetNetParentAttr(const PODVector<unsigned char>& value)
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void Node::SetNetRotationAttr(const PODVector<unsigned char>& value)
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void Node::SetOwner(Connection* owner)
    // Not registered because have @manualbind mark

    // template <class T> T* Node::CreateComponent(CreateMode mode = REPLICATED, unsigned id = 0)
    // Not registered because template
    // template <class T> void Node::GetChildrenWithComponent(PODVector<Node*>& dest, bool recursive = false) const
    // Not registered because template
    // template <class T> T* Node::GetComponent(bool recursive = false) const
    // Not registered because template
    // template <class T> void Node::GetComponents(PODVector<T*>& dest, bool recursive = false) const
    // Not registered because template
    // template <class T> T* Node::GetDerivedComponent(bool recursive = false) const
    // Not registered because template
    // template <class T> void Node::GetDerivedComponents(PODVector<T*>& dest, bool recursive = false, bool clearVector = true) const
    // Not registered because template
    // template <class T> T* Node::GetOrCreateComponent(CreateMode mode = REPLICATED, unsigned id = 0)
    // Not registered because template
    // template <class T> T* Node::GetParentComponent(bool fullTraversal = false) const
    // Not registered because template
    // template <class T> T* Node::GetParentDerivedComponent(bool fullTraversal = false) const
    // Not registered because template
    // template <class T> bool Node::HasComponent() const
    // Not registered because template
    // template <class T> void Node::RemoveComponent()
    // Not registered because template
    // template <class T> void Node::RemoveComponents()
    // Not registered because template

}

// class LogicComponent | File: ../Scene/LogicComponent.h
void CollectMembers_LogicComponent(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.methods_, "virtual void Component::OnSetEnabled()");

}

// class Scene | File: ../Scene/Scene.h
void CollectMembers_Scene(MemberCollection& members)
{
    CollectMembers_Node(members);

    Remove(members.methods_, "Component* Node::GetComponent(StringHash type, bool recursive = false) const");
    Remove(members.methods_, "bool Node::Load(Deserializer& source) override");
    Remove(members.methods_, "bool Node::Load(Deserializer& source, SceneResolver& resolver, bool loadChildren = true, bool rewriteIDs = false, CreateMode mode = REPLICATED)");
    Remove(members.methods_, "bool Node::LoadJSON(const JSONValue& source) override");
    Remove(members.methods_, "bool Node::LoadJSON(const JSONValue& source, SceneResolver& resolver, bool loadChildren = true, bool rewriteIDs = false, CreateMode mode = REPLICATED)");
    Remove(members.methods_, "bool Node::LoadXML(const XMLElement& source) override");
    Remove(members.methods_, "bool Node::LoadXML(const XMLElement& source, SceneResolver& resolver, bool loadChildren = true, bool rewriteIDs = false, CreateMode mode = REPLICATED)");
    Remove(members.methods_, "bool Node::Save(Serializer& dest) const override");
    Remove(members.methods_, "bool Node::SaveJSON(JSONValue& dest) const override");
    Remove(members.methods_, "bool Node::SaveJSON(Serializer& dest, const String& indentation = \"\t\") const");
    Remove(members.methods_, "bool Node::SaveXML(Serializer& dest, const String& indentation = \"\t\") const");
    Remove(members.methods_, "bool Node::SaveXML(XMLElement& dest) const override");
    Remove(members.methods_, "template <class T> T* Node::GetComponent(bool recursive = false) const");
    Remove(members.methods_, "virtual void Node::AddReplicationState(NodeReplicationState* state)");
    Remove(members.methods_, "void Node::CleanupConnection(Connection* connection)");
    Remove(members.methods_, "void Node::MarkNetworkUpdate() override");
    Remove(members.methods_, "void Node::MarkReplicationDirty()");
    Remove(members.methods_, "void Node::PrepareNetworkUpdate()");

    Remove(members.staticMethods_, "static void Node::RegisterObject(Context* context)");

    // bool Scene::GetNodesWithTag(PODVector<Node*>& dest, const String& tag) const
    // Error: type "PODVector<Node*>&" can not automatically bind

}

// class SmoothedTransform | File: ../Scene/SmoothedTransform.h
void CollectMembers_SmoothedTransform(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

}

// class SplinePath | File: ../Scene/SplinePath.h
void CollectMembers_SplinePath(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.methods_, "virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)");
    Remove(members.methods_, "virtual void Serializable::ApplyAttributes()");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

    // const VariantVector& SplinePath::GetControlPointIdsAttr() const
    // Error: type "const VariantVector&" can not automatically bind
    // void SplinePath::SetControlPointIdsAttr(const VariantVector& value)
    // Error: type "const VariantVector&" can not automatically bind

}

// class UnknownComponent | File: ../Scene/UnknownComponent.h
void CollectMembers_UnknownComponent(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.methods_, "bool Animatable::LoadJSON(const JSONValue& source) override");
    Remove(members.methods_, "bool Animatable::LoadXML(const XMLElement& source) override");
    Remove(members.methods_, "bool Component::Save(Serializer& dest) const override");
    Remove(members.methods_, "bool Component::SaveJSON(JSONValue& dest) const override");
    Remove(members.methods_, "bool Component::SaveXML(XMLElement& dest) const override");
    Remove(members.methods_, "virtual StringHash Object::GetType() const = 0");
    Remove(members.methods_, "virtual bool Serializable::Load(Deserializer& source)");
    Remove(members.methods_, "virtual const String& Object::GetTypeName() const = 0");
    Remove(members.methods_, "virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

    // const PODVector<unsigned char>& UnknownComponent::GetBinaryAttributes() const
    // Error: type "const PODVector<unsigned char>&" can not automatically bind

    // static Urho3D::StringHash UnknownComponent::GetTypeStatic()
    // Error: type "Urho3D::StringHash" can not automatically bind
    // static const Urho3D::String& UnknownComponent::GetTypeNameStatic()
    // Error: type "const Urho3D::String&" can not automatically bind

}

} // namespace Urho3D
