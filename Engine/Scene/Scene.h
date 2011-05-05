//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#include "Node.h"

/// Root scene node, represents the whole scene
class Scene : public Node
{
    OBJECT(Scene);

    using Node::SaveXML;
        
public:
    /// Construct
    Scene(Context* context);
    /// Destruct
    virtual ~Scene();
    /// Register object factory. Node must be registered first
    static void RegisterObject(Context* context);
    
    /// Load from binary data. Return true if successful
    virtual bool Load(Deserializer& source);
    /// Save to binary data. Return true if successful
    virtual bool Save(Serializer& dest);
    /// Load from XML data. Return true if successful
    virtual bool LoadXML(const XMLElement& source);
    
    /// Load from an XML file. Return true if successful
    bool LoadXML(Deserializer& source);
    /// Save to an XML file. Return true if successful
    bool SaveXML(Serializer& dest);
    /// Update scene
    void Update(float timeStep);
    /// Set active flag. Only active scenes will be updated automatically
    void SetActive(bool enable);
    /// Node added. Assign scene pointer & ID
    void NodeAdded(Node* node);
    /// Node removed. Remove ID assignment
    void NodeRemoved(Node* node);
    /// Component added. Assign ID
    void ComponentAdded(Component* component);
    /// Component removed. Remove ID assignment
    void ComponentRemoved(Component* component);
    
    /// Return active flag
    bool IsActive() const { return active_; }
    /// Return node from the whole scene by ID, or null if not found
    Node* GetNodeByID(unsigned id) const;
    /// Return component from the whole scene by ID, or null if not found
    Component* GetComponentByID(unsigned id) const;
    
private:
    /// Handle the logic update event to update the scene, if active
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    
    inline void GetNextNodeID()
    {
        ++nodeID_;
        if (!nodeID_)
            nodeID_ = 1;
    }
    
    inline void GetNextComponentID()
    {
        ++componentID_;
        if (!componentID_)
            componentID_ = 1;
    }
    
    /// Next free node ID
    unsigned nodeID_;
    /// Next free component ID
    unsigned componentID_;
    /// Map of scene nodes by ID
    std::map<unsigned, Node*> allNodes_;
    /// Map of components by ID
    std::map<unsigned, Component*> allComponents_;
    /// Active flag
    bool active_;
};

/// Register Scene library objects
void RegisterSceneLibrary(Context* context);
