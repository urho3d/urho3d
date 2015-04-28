//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Scene/Component.h"
#include "../Container/HashSet.h"
#include "../Scene/SceneResolver.h"
#include "../IO/Log.h"
#include "../Scene/Node.h"

#include "../DebugNew.h"

namespace Urho3D
{

SceneResolver::SceneResolver()
{
}

SceneResolver::~SceneResolver()
{
}

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
    for (HashMap<unsigned, WeakPtr<Component> >::ConstIterator i = components_.Begin(); i != components_.End(); ++i)
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
                    HashMap<unsigned, WeakPtr<Node> >::ConstIterator k = nodes_.Find(oldNodeID);
                    
                    if (k != nodes_.End() && k->second_)
                    {
                        unsigned newNodeID = k->second_->GetID();
                        component->SetAttribute(j, Variant(newNodeID));
                    }
                    else
                        LOGWARNING("Could not resolve node ID " + String(oldNodeID));
                }
            }
            else if (info.mode_ & AM_COMPONENTID)
            {
                hasIDAttributes = true;
                unsigned oldComponentID = component->GetAttribute(j).GetUInt();

                if (oldComponentID)
                {
                    HashMap<unsigned, WeakPtr<Component> >::ConstIterator k = components_.Find(oldComponentID);
                    
                    if (k != components_.End() && k->second_)
                    {
                        unsigned newComponentID = k->second_->GetID();
                        component->SetAttribute(j, Variant(newComponentID));
                    }
                    else
                        LOGWARNING("Could not resolve component ID " + String(oldComponentID));
                }
            }
            else if (info.mode_ & AM_NODEIDVECTOR)
            {
                hasIDAttributes = true;
                const VariantVector& oldNodeIDs = component->GetAttribute(j).GetVariantVector();
                
                if (oldNodeIDs.Size())
                {
                    // The first index stores the number of IDs redundantly. This is for editing
                    unsigned numIDs = oldNodeIDs[0].GetUInt();
                    VariantVector newIDs;
                    newIDs.Push(numIDs);
                    
                    for (unsigned k = 1; k < oldNodeIDs.Size(); ++k)
                    {
                        unsigned oldNodeID = oldNodeIDs[k].GetUInt();
                        HashMap<unsigned, WeakPtr<Node> >::ConstIterator l = nodes_.Find(oldNodeID);
                    
                        if (l != nodes_.End() && l->second_)
                            newIDs.Push(l->second_->GetID());
                        else
                        {
                            // If node was not found, retain number of elements, just store ID 0
                            newIDs.Push(0);
                            LOGWARNING("Could not resolve node ID " + String(oldNodeID));
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
