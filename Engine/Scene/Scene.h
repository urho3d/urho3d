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

/// First replicated node/component ID
static const unsigned FIRST_NONLOCAL_ID = 0x1;
/// Last replicated node/component ID
static const unsigned LAST_NONLOCAL_ID = 0xffffff;
/// First local node/component ID
static const unsigned FIRST_LOCAL_ID = 0x01000000;
/// Last local node/component ID
static const unsigned LAST_LOCAL_ID = 0xffffffff;

/// Scene's networking mode
enum NetworkMode
{
    NM_NONETWORK,
    NM_SERVER,
    NM_CLIENT
};

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
    /// Set networking mode
    void SetNetworkMode(NetworkMode mode);
    /// Set active flag. Only active scenes will be updated automatically
    void SetActive(bool enable);
    
    /// Return node from the whole scene by ID, or null if not found
    Node* GetNodeByID(unsigned id) const;
    /// Return component from the whole scene by ID, or null if not found
    Component* GetComponentByID(unsigned id) const;
    /// Return networking mode
    NetworkMode GetNetworkMode() const { return networkMode_; }
    /// Return active flag
    bool IsActive() const { return active_; }
    
    /// Get free node ID, either non-local or local
    unsigned GetFreeNodeID(bool local);
    /// Get free component ID, either non-local or local
    unsigned GetFreeComponentID(bool local);
    /// Node added. Assign scene pointer and add to ID map
    void NodeAdded(Node* node);
    /// Node removed. Remove from ID map
    void NodeRemoved(Node* node);
    /// Component added. Add to ID map
    void ComponentAdded(Component* component);
    /// Component removed. Remove from ID map
    void ComponentRemoved(Component* component);
    
private:
    /// Handle the logic update event to update the scene, if active
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    
    /// Map of scene nodes by ID
    std::map<unsigned, Node*> allNodes_;
    /// Map of components by ID
    std::map<unsigned, Component*> allComponents_;
    /// Networking mode
    NetworkMode networkMode_;
    /// Next free non-local node ID
    unsigned nonLocalNodeID_;
    /// Next free local node ID
    unsigned localNodeID_;
    /// Next free non-local component ID
    unsigned nonLocalComponentID_;
    /// Next free local component ID
    unsigned localComponentID_;
    /// Active flag
    bool active_;
};

/// Register Scene library objects
void RegisterSceneLibrary(Context* context);
