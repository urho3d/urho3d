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

#pragma once

#include "../Container/HashMap.h"
#include "../Container/Ptr.h"

namespace Urho3D
{

class Component;
class Node;

/// Utility class that resolves node & component IDs after a scene or partial scene load.
class URHO3D_API SceneResolver
{
public:
    /// Construct.
    SceneResolver();
    /// Destruct.
    ~SceneResolver();
    
    /// Reset. Clear all remembered nodes and components.
    void Reset();
    /// Remember a created node.
    void AddNode(unsigned oldID, Node* node);
    /// Remember a created component.
    void AddComponent(unsigned oldID, Component* component);
    /// Resolve component and node ID attributes and reset.
    void Resolve();
    
private:
    /// Nodes.
    HashMap<unsigned, WeakPtr<Node> > nodes_;
    /// Components.
    HashMap<unsigned, WeakPtr<Component> > components_;
};

}
