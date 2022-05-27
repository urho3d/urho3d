// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../IO/Log.h"
#include "../Scene/Component.h"
#include "../Scene/SceneResolver.h"
#include "../Scene/Node.h"

#include "../DebugNew.h"

namespace Urho3D
{

SceneResolver::SceneResolver() = default;

SceneResolver::~SceneResolver() = default;

void SceneResolver::Reset()
{
    nodes_.Clear();
    components_.Clear();
}

void SceneResolver::AddNode(unsigned oldID, Node* node)
{
    if (node)
        nodes_[oldID] = node;
}

void SceneResolver::AddComponent(unsigned oldID, Component* component)
{
    if (component)
        components_[oldID] = component;
}

void SceneResolver::Resolve()
{
    // Nodes do not have component or node ID attributes, so only have to go through components
    HashSet<StringHash> noIDAttributes;
    for (HashMap<unsigned, WeakPtr<Component>>::ConstIterator i = components_.Begin(); i != components_.End(); ++i)
    {
        Component* component = i->second_;
        if (!component || noIDAttributes.Contains(component->GetType()))
            continue;

        bool hasIDAttributes = false;
        const Vector<AttributeInfo>* attributes = component->GetAttributes();
        if (!attributes)
        {
            noIDAttributes.Insert(component->GetType());
            continue;
        }

        for (unsigned j = 0; j < attributes->Size(); ++j)
        {
            const AttributeInfo& info = attributes->At(j);
            if (info.mode_ & AM_NODEID)
            {
                hasIDAttributes = true;
                unsigned oldNodeID = component->GetAttribute(j).GetUInt();

                if (oldNodeID)
                {
                    HashMap<unsigned, WeakPtr<Node>>::ConstIterator k = nodes_.Find(oldNodeID);

                    if (k != nodes_.End() && k->second_)
                    {
                        unsigned newNodeID = k->second_->GetID();
                        component->SetAttribute(j, Variant(newNodeID));
                    }
                    else
                        URHO3D_LOGWARNING("Could not resolve node ID " + String(oldNodeID));
                }
            }
            else if (info.mode_ & AM_COMPONENTID)
            {
                hasIDAttributes = true;
                unsigned oldComponentID = component->GetAttribute(j).GetUInt();

                if (oldComponentID)
                {
                    HashMap<unsigned, WeakPtr<Component>>::ConstIterator k = components_.Find(oldComponentID);

                    if (k != components_.End() && k->second_)
                    {
                        unsigned newComponentID = k->second_->GetID();
                        component->SetAttribute(j, Variant(newComponentID));
                    }
                    else
                        URHO3D_LOGWARNING("Could not resolve component ID " + String(oldComponentID));
                }
            }
            else if (info.mode_ & AM_NODEIDVECTOR)
            {
                hasIDAttributes = true;
                Variant attrValue = component->GetAttribute(j);
                const VariantVector& oldNodeIDs = attrValue.GetVariantVector();

                if (oldNodeIDs.Size())
                {
                    // The first index stores the number of IDs redundantly. This is for editing
                    unsigned numIDs = oldNodeIDs[0].GetUInt();
                    VariantVector newIDs;
                    newIDs.Push(numIDs);

                    for (unsigned k = 1; k < oldNodeIDs.Size(); ++k)
                    {
                        unsigned oldNodeID = oldNodeIDs[k].GetUInt();
                        HashMap<unsigned, WeakPtr<Node>>::ConstIterator l = nodes_.Find(oldNodeID);

                        if (l != nodes_.End() && l->second_)
                            newIDs.Push(l->second_->GetID());
                        else
                        {
                            // If node was not found, retain number of elements, just store ID 0
                            newIDs.Push(0);
                            URHO3D_LOGWARNING("Could not resolve node ID " + String(oldNodeID));
                        }
                    }

                    component->SetAttribute(j, newIDs);
                }
            }
        }

        // If component type had no ID attributes, cache this fact for optimization
        if (!hasIDAttributes)
            noIDAttributes.Insert(component->GetType());
    }

    // Attributes have been resolved, so no need to remember the nodes after this
    Reset();
}

}
