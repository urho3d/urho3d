//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Core/Context.h"
#include "../IceWeaselMods/Gravity.h"
#include "../IceWeaselMods/GravityProbe.h"
#include "../IceWeaselMods/IceWeasel.h"
#include "../Scene/SceneEvents.h"
#include "../Scene/Node.h"

namespace Urho3D
{


// ----------------------------------------------------------------------------
Gravity::Gravity(Context* context)
    : Component(context),
    gravity_(9.81f)
{
    SubscribeToEvent(E_COMPONENTADDED, URHO3D_HANDLER(Gravity, HandleComponentAdded));
    SubscribeToEvent(E_COMPONENTREMOVED, URHO3D_HANDLER(Gravity, HandleComponentRemoved));
    SubscribeToEvent(E_NODEADDED, URHO3D_HANDLER(Gravity, HandleNodeAdded));
    SubscribeToEvent(E_NODEREMOVED, URHO3D_HANDLER(Gravity, HandleNodeRemoved));
}

// ----------------------------------------------------------------------------
Gravity::~Gravity()
{
}

// ----------------------------------------------------------------------------
void Gravity::RegisterObject(Context* context)
{
    context->RegisterFactory<Gravity>(ICEWEASELMODS_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Global Gravity", GetGlobalGravity, SetGlobalGravity, float, 9.81, AM_DEFAULT);
}

// ----------------------------------------------------------------------------
Vector3 Gravity::QueryGravity(Vector3 worldLocation)
{
    // TODO Really shitty method of finding closest node
    float distance = std::numeric_limits<float>::max();
    PODVector<Node*>::ConstIterator it = gravityProbeNodes_.Begin();
    GravityProbe* foundProbe = NULL;
    for(; it != gravityProbeNodes_.End(); ++it)
    {
        GravityProbe* probe = (*it)->GetComponent<GravityProbe>();
        float newDistance = (worldLocation - probe->GetPosition()).Length();
        if(newDistance < distance)
        {
            foundProbe = probe;
            distance = newDistance;
        }
    }

    // No probe was found? No gravity probes exist. Provide default vector
    if(!foundProbe)
        return Vector3::DOWN * gravity_;

    return foundProbe->GetDirection() * foundProbe->GetForceFactor() * gravity_;
}

// ----------------------------------------------------------------------------
void Gravity::RebuildTetrahedralMesh()
{
    // TODO Build tetrahedral mesh from gravity probes
}

// ----------------------------------------------------------------------------
/*
 * This section maintains a list of nodes that have gravity probes
 * attached to them. Whenever nodes are deleted or added to the scene, or
 * whenever components are added or removed from nodes, we must check to see
 * which of those nodes have/had a gravity probe attached to it and update
 * our internal list accordingly.
 *
 * Unfortunately, E_COMPONENTREMOVED and E_COMPONENTADDED do not fire when a
 * parent node is removed/added containing gravity probe nodes, so we must
 * also monitor E_NODEREMOVED AND E_NODEADDED.
 */

// ----------------------------------------------------------------------------
void Gravity::OnSceneSet(Scene* scene)
{
    (void)scene;

    // do a full search for gravityProbe nodes
    gravityProbeNodes_.Clear();
    AddGravityProbeNodesRecursively(node_);
    RebuildTetrahedralMesh();
}

// ----------------------------------------------------------------------------
void Gravity::AddGravityProbeNodesRecursively(Node* node)
{
    // Recursively retrieve all nodes that have a gravity probe component and
    // add them to our internal list of gravity probe nodes. Note that it
    // should not be possible for there to be duplicates; scene graphs can't
    // have loops.
    PODVector<Node*> gravityProbeNodesToAdd;
    node->GetChildrenWithComponent<GravityProbe>(gravityProbeNodesToAdd, true);
    // Don't forget to check this node's components as well
    if(node->GetComponent<GravityProbe>())
        gravityProbeNodesToAdd.Push(node);

    gravityProbeNodes_.Push(gravityProbeNodesToAdd);
}

// ----------------------------------------------------------------------------
void Gravity::RemoveGravityProbeNodesRecursively(Node* node)
{
    // Recursively retrieve all nodes that have a gravity probe component
    PODVector<Node*> gravityProbeNodesToRemove;
    node->GetChildrenWithComponent<GravityProbe>(gravityProbeNodesToRemove, true);
    // Don't forget to check this node's components as well
    if(node->GetComponent<GravityProbe>())
        gravityProbeNodesToRemove.Push(node);

    // search for found components and remove them from our internal list
    PODVector<Node*>::ConstIterator it = gravityProbeNodesToRemove.Begin();
    for(; it != gravityProbeNodesToRemove.End(); ++it)
    {
        PODVector<Node*>::Iterator gravityProbeNode = gravityProbeNodes_.Find(*it);
        if(gravityProbeNode != gravityProbeNodes_.End())
            gravityProbeNodes_.Erase(gravityProbeNode);
    }
}

// ----------------------------------------------------------------------------
void Gravity::HandleComponentAdded(StringHash eventType, VariantMap& eventData)
{
    using namespace ComponentAdded;
    (void)eventType;

    // We only care about nodes that are descendants of us
    if(!node_->IsAncestorOf(static_cast<Node*>(eventData[P_NODE].GetPtr())))
        return;

    // Check if the component that was added is an IK gravityProbe. If not, then it
    // does not concern us.
    Component* component = static_cast<Component*>(eventData[P_COMPONENT].GetPtr());
    if(component->GetType() != GravityProbe::GetTypeStatic())
        return;

    Node* node = static_cast<Node*>(eventData[P_NODE].GetPtr());
    gravityProbeNodes_.Push(node);
    RebuildTetrahedralMesh();
}

// ----------------------------------------------------------------------------
void Gravity::HandleComponentRemoved(StringHash eventType, VariantMap& eventData)
{
    using namespace ComponentRemoved;
    (void)eventType;

    // We only care about nodes that are descendants of us
    if(!node_->IsAncestorOf(static_cast<Node*>(eventData[P_NODE].GetPtr())))
        return;

    // Check if the component that was removed was an IK gravityProbe. If not,
    // then it does not concern us.
    Component* component = static_cast<Component*>(eventData[P_COMPONENT].GetPtr());
    if(component->GetType() != GravityProbe::GetTypeStatic())
        return;

    Node* node = static_cast<Node*>(eventData[P_NODE].GetPtr());
    gravityProbeNodes_.Remove(node);
    RebuildTetrahedralMesh();
}

// ----------------------------------------------------------------------------
void Gravity::HandleNodeAdded(StringHash eventType, VariantMap& eventData)
{
    using namespace NodeAdded;
    (void)eventType;

    // We only care about nodes that are descendants of us
    Node* addedNode = static_cast<Node*>(eventData[P_NODE].GetPtr());
    if(!node_->IsAncestorOf(addedNode))
        return;

    AddGravityProbeNodesRecursively(addedNode);
    RebuildTetrahedralMesh();
}

// ----------------------------------------------------------------------------
void Gravity::HandleNodeRemoved(StringHash eventType, VariantMap& eventData)
{
    using namespace NodeRemoved;
    (void)eventType;

    // We only care about nodes that are descendants of us
    Node* removedNode = static_cast<Node*>(eventData[P_NODE].GetPtr());
    if(!node_->IsAncestorOf(removedNode))
        return;

    RemoveGravityProbeNodesRecursively(static_cast<Node*>(eventData[P_NODE].GetPtr()));
    RebuildTetrahedralMesh();
}

} // namespace Urho3D
