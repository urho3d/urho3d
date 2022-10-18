// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Resource/JSONValue.h"
#include "../Scene/Component.h"
#include "../Scene/ReplicationState.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneEvents.h"
#ifdef URHO3D_PHYSICS
#include "../Physics/PhysicsWorld.h"
#endif
#ifdef URHO3D_PHYSICS2D
#include "../Physics2D/PhysicsWorld2D.h"
#endif

#include "../DebugNew.h"

namespace Urho3D
{

const char* autoRemoveModeNames[] = {
    "Disabled",
    "Component",
    "Node",
    nullptr
};

Component::Component(Context* context) :
    Animatable(context),
    node_(nullptr),
    id_(0),
    networkUpdate_(false),
    enabled_(true)
{
}

Component::~Component() = default;

bool Component::Save(Serializer& dest) const
{
    // Write type and ID
    if (!dest.WriteStringHash(GetType()))
        return false;
    if (!dest.WriteU32(id_))
        return false;

    // Write attributes
    return Animatable::Save(dest);
}

bool Component::SaveXML(XMLElement& dest) const
{
    // Write type and ID
    if (!dest.SetString("type", GetTypeName()))
        return false;
    if (!dest.SetUInt("id", id_))
        return false;

    // Write attributes
    return Animatable::SaveXML(dest);
}

bool Component::SaveJSON(JSONValue& dest) const
{
    // Write type and ID
    dest.Set("type", GetTypeName());
    dest.Set("id", id_);

    // Write attributes
    return Animatable::SaveJSON(dest);
}

void Component::MarkNetworkUpdate()
{
    if (!networkUpdate_ && IsReplicated())
    {
        Scene* scene = GetScene();
        if (scene)
        {
            scene->MarkNetworkUpdate(this);
            networkUpdate_ = true;
        }
    }
}

void Component::GetDependencyNodes(Vector<Node*>& dest)
{
}

void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
}

void Component::SetEnabled(bool enable)
{
    if (enable != enabled_)
    {
        enabled_ = enable;
        OnSetEnabled();
        MarkNetworkUpdate();

        // Send change event for the component
        Scene* scene = GetScene();
        if (scene)
        {
            using namespace ComponentEnabledChanged;

            VariantMap& eventData = GetEventDataMap();
            eventData[P_SCENE] = scene;
            eventData[P_NODE] = node_;
            eventData[P_COMPONENT] = this;

            scene->SendEvent(E_COMPONENTENABLEDCHANGED, eventData);
        }
    }
}

void Component::Remove()
{
    if (node_)
        node_->RemoveComponent(this);
}

bool Component::IsReplicated() const
{
    return Scene::IsReplicatedID(id_);
}

Scene* Component::GetScene() const
{
    return node_ ? node_->GetScene() : nullptr;
}

void Component::AddReplicationState(ComponentReplicationState* state)
{
    if (!networkState_)
        AllocateNetworkState();

    networkState_->replicationStates_.Push(state);
}

void Component::PrepareNetworkUpdate()
{
    if (!networkState_)
        AllocateNetworkState();

    const Vector<AttributeInfo>* attributes = networkState_->attributes_;
    if (!attributes)
        return;

    unsigned numAttributes = attributes->Size();

    // Check for attribute changes
    for (unsigned i = 0; i < numAttributes; ++i)
    {
        const AttributeInfo& attr = attributes->At(i);

        if (animationEnabled_ && IsAnimatedNetworkAttribute(attr))
            continue;

        OnGetAttribute(attr, networkState_->currentValues_[i]);

        if (networkState_->currentValues_[i] != networkState_->previousValues_[i])
        {
            networkState_->previousValues_[i] = networkState_->currentValues_[i];

            // Mark the attribute dirty in all replication states that are tracking this component
            for (Vector<ReplicationState*>::Iterator j = networkState_->replicationStates_.Begin();
                 j != networkState_->replicationStates_.End(); ++j)
            {
                auto* compState = static_cast<ComponentReplicationState*>(*j);
                compState->dirtyAttributes_.Set(i);

                // Add component's parent node to the dirty set if not added yet
                NodeReplicationState* nodeState = compState->nodeState_;
                if (!nodeState->markedDirty_)
                {
                    nodeState->markedDirty_ = true;
                    nodeState->sceneState_->dirtyNodes_.Insert(node_->GetID());
                }
            }
        }
    }

    networkUpdate_ = false;
}

void Component::CleanupConnection(Connection* connection)
{
    if (networkState_)
    {
        for (i32 i = networkState_->replicationStates_.Size() - 1; i >= 0; --i)
        {
            if (networkState_->replicationStates_[i]->connection_ == connection)
                networkState_->replicationStates_.Erase(i);
        }
    }
}

void Component::OnAttributeAnimationAdded()
{
    if (attributeAnimationInfos_.Size() == 1)
        SubscribeToEvent(GetScene(), E_ATTRIBUTEANIMATIONUPDATE, URHO3D_HANDLER(Component, HandleAttributeAnimationUpdate));
}

void Component::OnAttributeAnimationRemoved()
{
    if (attributeAnimationInfos_.Empty())
        UnsubscribeFromEvent(GetScene(), E_ATTRIBUTEANIMATIONUPDATE);
}

void Component::OnNodeSet(Node* node)
{
}

void Component::OnSceneSet(Scene* scene)
{
}

void Component::OnMarkedDirty(Node* node)
{
}

void Component::OnNodeSetEnabled(Node* node)
{
}

void Component::SetID(unsigned id)
{
    id_ = id;
}

void Component::SetNode(Node* node)
{
    node_ = node;
    OnNodeSet(node_);
}

Component* Component::GetComponent(StringHash type) const
{
    return node_ ? node_->GetComponent(type) : nullptr;
}

bool Component::IsEnabledEffective() const
{
    return enabled_ && node_ && node_->IsEnabled();
}

void Component::GetComponents(Vector<Component*>& dest, StringHash type) const
{
    if (node_)
        node_->GetComponents(dest, type);
    else
        dest.Clear();
}

void Component::HandleAttributeAnimationUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace AttributeAnimationUpdate;

    UpdateAttributeAnimations(eventData[P_TIMESTEP].GetFloat());
}

Component* Component::GetFixedUpdateSource()
{
    Component* ret = nullptr;
    Scene* scene = GetScene();

    if (scene)
    {
#ifdef URHO3D_PHYSICS
        ret = scene->GetComponent<PhysicsWorld>();
#endif
#ifdef URHO3D_PHYSICS2D
        if (!ret)
            ret = scene->GetComponent<PhysicsWorld2D>();
#endif
    }

    return ret;
}

void Component::DoAutoRemove(AutoRemoveMode mode)
{
    switch (mode)
    {
    case REMOVE_COMPONENT:
        Remove();
        return;

    case REMOVE_NODE:
        if (node_)
            node_->Remove();
        return;

    default:
        return;
    }
}

}
