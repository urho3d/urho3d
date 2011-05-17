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
#include "XMLElement.h"

class File;
class PackageFile;

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

/// Scene's asynchronous loading progress
struct AsyncProgress
{
    /// File for binary mode
    SharedPtr<File> file_;
    /// XML file for XML mode
    SharedPtr<XMLFile> xmlFile_;
    /// Current XML element for XML mode
    XMLElement xmlElement_;
    /// Loaded root-level nodes
    unsigned loadedNodes_;
    /// Total root-level nodes
    unsigned totalNodes_;
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
    
    /// Update scene
    void Update(float timeStep);
    /// Load from an XML file. Return true if successful
    bool LoadXML(Deserializer& source);
    /// Save to an XML file. Return true if successful
    bool SaveXML(Serializer& dest);
    /// Load from a binary file asynchronously. Return true if started successfully
    bool LoadAsync(File* file);
    /// Load from an XML file asynchronously. Return true if started successfully
    bool LoadAsyncXML(File* file);
    /// Stop asynchronous loading
    void StopAsyncLoading();
    /// Set networking mode
    void SetNetworkMode(NetworkMode mode);
    /// Set active flag. Only active scenes will be updated automatically
    void SetActive(bool enable);
    /// Clear scene completely of nodes and components
    void Clear();
    /// Clear scene of all non-local child nodes. Note: if they have local children, they will be removed as well
    void ClearNonLocal();
    /// Add a required package file for multiplayer. To be called on the server
    void AddRequiredPackageFile(PackageFile* file);
    /// Clear required package files
    void ClearRequiredPackageFiles();
    /// Reset specific owner reference from nodes on disconnect
    void ResetOwner(Connection* owner);
    
    /// Return node from the whole scene by ID, or null if not found
    Node* GetNodeByID(unsigned id) const;
    /// Return component from the whole scene by ID, or null if not found
    Component* GetComponentByID(unsigned id) const;
    /// Return networking mode
    NetworkMode GetNetworkMode() const { return networkMode_; }
    /// Return active flag
    bool IsActive() const { return active_; }
    /// Return asynchronous loading flag
    bool IsAsyncLoading() const { return asyncLoading_; }
    /// Return asynchronous loading progress between 0.0 and 1.0, or 1.0 if not in progress
    float GetAsyncProgress() const;
    /// Return source file name
    const String& GetFileName() const { return fileName_; }
    /// Return source file checksum
    unsigned GetChecksum() const { return checksum_; }
    /// Return required package files
    const Vector<SharedPtr<PackageFile> >& GetRequiredPackageFiles() const { return requiredPackageFiles_; }
    /// Return all nodes
    const Map<unsigned, Node*>& GetAllNodes() const { return allNodes_; }
    /// Return all components
    const Map<unsigned, Component*>& GetAllComponents() const { return allComponents_; }
    
    /// Get free node ID, either non-local or local
    unsigned GetFreeunsigned(bool local);
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
    /// Update asynchronous loading
    void UpdateAsyncLoading();
    /// Finish asynchronous loading
    void FinishAsyncLoading();
    /// Finish loading
    void FinishLoading(Deserializer* source);
    
    /// Map of scene nodes by ID
    Map<unsigned, Node*> allNodes_;
    /// Map of components by ID
    Map<unsigned, Component*> allComponents_;
    /// Networking mode
    NetworkMode networkMode_;
    /// Asynchronous loading progress
    AsyncProgress asyncProgress_;
    /// Source file name
    String fileName_;
    /// Required package files for multiplayer
    Vector<SharedPtr<PackageFile> > requiredPackageFiles_;
    /// Next free non-local node ID
    unsigned nonLocalNodeID_;
    /// Next free local node ID
    unsigned localNodeID_;
    /// Next free non-local component ID
    unsigned nonLocalComponentID_;
    /// Next free local component ID
    unsigned localComponentID_;
    /// Scene source file checksum
    unsigned checksum_;
    /// Active flag
    bool active_;
    /// Asynchronous loading flag
    bool asyncLoading_;
};

/// Register Scene library objects
void RegisterSceneLibrary(Context* context);
