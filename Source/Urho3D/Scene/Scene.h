// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

/// \file

#pragma once

#include "../Container/HashSet.h"
#include "../Core/Mutex.h"
#include "../Resource/XMLElement.h"
#include "../Resource/JSONFile.h"
#include "../Scene/Node.h"
#include "../Scene/SceneResolver.h"

namespace Urho3D
{

class File;
class PackageFile;

static const unsigned FIRST_REPLICATED_ID = 0x1;
static const unsigned LAST_REPLICATED_ID = 0xffffff;
static const unsigned FIRST_LOCAL_ID = 0x01000000;
static const unsigned LAST_LOCAL_ID = 0xffffffff;

/// Asynchronous scene loading mode.
enum LoadMode
{
    /// Preload resources used by a scene or object prefab file, but do not load any scene content.
    LOAD_RESOURCES_ONLY = 0,
    /// Load scene content without preloading. Resources will be requested synchronously when encountered.
    LOAD_SCENE,
    /// Default mode: preload resources used by the scene first, then load the scene content.
    LOAD_SCENE_AND_RESOURCES
};

/// Asynchronous loading progress of a scene.
struct AsyncProgress
{
    /// File for binary mode.
    SharedPtr<File> file_;
    /// XML file for XML mode.
    SharedPtr<XMLFile> xmlFile_;
    /// JSON file for JSON mode.
    SharedPtr<JSONFile> jsonFile_;

    /// Current XML element for XML mode.
    XMLElement xmlElement_;

    /// Current JSON child array and for JSON mode.
    i32 jsonIndex_;

    /// Current load mode.
    LoadMode mode_;
    /// Resource name hashes left to load.
    HashSet<StringHash> resources_;
    /// Loaded resources.
    i32 loadedResources_;
    /// Total resources.
    i32 totalResources_;
    /// Loaded root-level nodes.
    i32 loadedNodes_;
    /// Total root-level nodes.
    i32 totalNodes_;
};

/// Root scene node, represents the whole scene.
class URHO3D_API Scene : public Node
{
    URHO3D_OBJECT(Scene, Node);

public:
    /// @manualbind
    using Node::GetComponent;
    /// @manualbind
    using Node::SaveXML;
    /// @manualbind
    using Node::SaveJSON;

    /// Construct.
    explicit Scene(Context* context);
    /// Destruct.
    ~Scene() override;
    /// Register object factory. Node must be registered first.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Load from binary data. Removes all existing child nodes and components first. Return true if successful.
    bool Load(Deserializer& source) override;
    /// Save to binary data. Return true if successful.
    bool Save(Serializer& dest) const override;
    /// Load from XML data. Removes all existing child nodes and components first. Return true if successful.
    bool LoadXML(const XMLElement& source) override;
    /// Load from JSON data. Removes all existing child nodes and components first. Return true if successful.
    bool LoadJSON(const JSONValue& source) override;
    /// Mark for attribute check on the next network update.
    void MarkNetworkUpdate() override;
    /// Add a replication state that is tracking this scene.
    void AddReplicationState(NodeReplicationState* state) override;

    /// Load from an XML file. Return true if successful.
    bool LoadXML(Deserializer& source);
    /// Load from a JSON file. Return true if successful.
    bool LoadJSON(Deserializer& source);
    /// Save to an XML file. Return true if successful.
    bool SaveXML(Serializer& dest, const String& indentation = "\t") const;
    /// Save to a JSON file. Return true if successful.
    bool SaveJSON(Serializer& dest, const String& indentation = "\t") const;
    /// Load from a binary file asynchronously. Return true if started successfully. The LOAD_RESOURCES_ONLY mode can also be used to preload resources from object prefab files.
    bool LoadAsync(File* file, LoadMode mode = LOAD_SCENE_AND_RESOURCES);
    /// Load from an XML file asynchronously. Return true if started successfully. The LOAD_RESOURCES_ONLY mode can also be used to preload resources from object prefab files.
    bool LoadAsyncXML(File* file, LoadMode mode = LOAD_SCENE_AND_RESOURCES);
    /// Load from a JSON file asynchronously. Return true if started successfully. The LOAD_RESOURCES_ONLY mode can also be used to preload resources from object prefab files.
    bool LoadAsyncJSON(File* file, LoadMode mode = LOAD_SCENE_AND_RESOURCES);
    /// Stop asynchronous loading.
    void StopAsyncLoading();
    /// Instantiate scene content from binary data. Return root node if successful.
    Node* Instantiate(Deserializer& source, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED);
    /// Instantiate scene content from XML data. Return root node if successful.
    Node* InstantiateXML
        (const XMLElement& source, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED);
    /// Instantiate scene content from XML data. Return root node if successful.
    Node* InstantiateXML(Deserializer& source, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED);
    /// Instantiate scene content from JSON data. Return root node if successful.
    Node* InstantiateJSON
        (const JSONValue& source, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED);
    /// Instantiate scene content from JSON data. Return root node if successful.
    Node* InstantiateJSON(Deserializer& source, const Vector3& position, const Quaternion& rotation, CreateMode mode = REPLICATED);

    /// Clear scene completely of either replicated, local or all nodes and components.
    void Clear(bool clearReplicated = true, bool clearLocal = true);
    /// Enable or disable scene update.
    /// @property
    void SetUpdateEnabled(bool enable);
    /// Set update time scale. 1.0 = real time (default).
    /// @property
    void SetTimeScale(float scale);
    /// Set elapsed time in seconds. This can be used to prevent inaccuracy in the timer if the scene runs for a long time.
    /// @property
    void SetElapsedTime(float time);
    /// Set network client motion smoothing constant.
    /// @property
    void SetSmoothingConstant(float constant);
    /// Set network client motion smoothing snap threshold.
    /// @property
    void SetSnapThreshold(float threshold);
    /// Set maximum milliseconds per frame to spend on async scene loading.
    /// @property
    void SetAsyncLoadingMs(int ms);
    /// Add a required package file for networking. To be called on the server.
    void AddRequiredPackageFile(PackageFile* package);
    /// Clear required package files.
    void ClearRequiredPackageFiles();
    /// Register a node user variable hash reverse mapping (for editing).
    void RegisterVar(const String& name);
    /// Unregister a node user variable hash reverse mapping.
    void UnregisterVar(const String& name);
    /// Clear all registered node user variable hash reverse mappings.
    void UnregisterAllVars();

    /// Return node from the whole scene by ID, or null if not found.
    Node* GetNode(unsigned id) const;
    /// Return component from the whole scene by ID, or null if not found.
    Component* GetComponent(unsigned id) const;
    /// Get nodes with specific tag from the whole scene, return false if empty.
    bool GetNodesWithTag(Vector<Node*>& dest, const String& tag)  const;

    /// Return whether updates are enabled.
    /// @property
    bool IsUpdateEnabled() const { return updateEnabled_; }

    /// Return whether an asynchronous loading operation is in progress.
    /// @property
    bool IsAsyncLoading() const { return asyncLoading_; }

    /// Return asynchronous loading progress between 0.0 and 1.0, or 1.0 if not in progress.
    /// @property
    float GetAsyncProgress() const;

    /// Return the load mode of the current asynchronous loading operation.
    /// @property
    LoadMode GetAsyncLoadMode() const { return asyncProgress_.mode_; }

    /// Return source file name.
    /// @property
    const String& GetFileName() const { return fileName_; }

    /// Return source file checksum.
    /// @property
    hash32 GetChecksum() const { return checksum_; }

    /// Return update time scale.
    /// @property
    float GetTimeScale() const { return timeScale_; }

    /// Return elapsed time in seconds.
    /// @property
    float GetElapsedTime() const { return elapsedTime_; }

    /// Return motion smoothing constant.
    /// @property
    float GetSmoothingConstant() const { return smoothingConstant_; }

    /// Return motion smoothing snap threshold.
    /// @property
    float GetSnapThreshold() const { return snapThreshold_; }

    /// Return maximum milliseconds per frame to spend on async loading.
    /// @property
    int GetAsyncLoadingMs() const { return asyncLoadingMs_; }

    /// Return required package files.
    /// @property
    const Vector<SharedPtr<PackageFile>>& GetRequiredPackageFiles() const { return requiredPackageFiles_; }

    /// Return a node user variable name, or empty if not registered.
    const String& GetVarName(StringHash hash) const;

    /// Update scene. Called by HandleUpdate.
    void Update(float timeStep);
    /// Begin a threaded update. During threaded update components can choose to delay dirty processing.
    void BeginThreadedUpdate();
    /// End a threaded update. Notify components that marked themselves for delayed dirty processing.
    void EndThreadedUpdate();
    /// Add a component to the delayed dirty notify queue. Is thread-safe.
    void DelayedMarkedDirty(Component* component);

    /// Return threaded update flag.
    bool IsThreadedUpdate() const { return threadedUpdate_; }

    /// Get free node ID, either non-local or local.
    unsigned GetFreeNodeID(CreateMode mode);
    /// Get free component ID, either non-local or local.
    unsigned GetFreeComponentID(CreateMode mode);
    /// Return whether the specified id is a replicated id.
    static bool IsReplicatedID(unsigned id) { return id < FIRST_LOCAL_ID; }

    /// Cache node by tag if tag not zero, no checking if already added. Used internaly in Node::AddTag.
    void NodeTagAdded(Node* node, const String& tag);
    /// Cache node by tag if tag not zero.
    void NodeTagRemoved(Node* node, const String& tag);

    /// Node added. Assign scene pointer and add to ID map.
    void NodeAdded(Node* node);
    /// Node removed. Remove from ID map.
    void NodeRemoved(Node* node);
    /// Component added. Add to ID map.
    void ComponentAdded(Component* component);
    /// Component removed. Remove from ID map.
    void ComponentRemoved(Component* component);
    /// Set node user variable reverse mappings.
    void SetVarNamesAttr(const String& value);
    /// Return node user variable reverse mappings.
    String GetVarNamesAttr() const;
    /// Prepare network update by comparing attributes and marking replication states dirty as necessary.
    void PrepareNetworkUpdate();
    /// Clean up all references to a network connection that is about to be removed.
    /// @manualbind
    void CleanupConnection(Connection* connection);
    /// Mark a node for attribute check on the next network update.
    void MarkNetworkUpdate(Node* node);
    /// Mark a component for attribute check on the next network update.
    void MarkNetworkUpdate(Component* component);
    /// Mark a node dirty in scene replication states. The node does not need to have own replication state yet.
    void MarkReplicationDirty(Node* node);

private:
    /// Handle the logic update event to update the scene, if active.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle a background loaded resource completing.
    void HandleResourceBackgroundLoaded(StringHash eventType, VariantMap& eventData);
    /// Update asynchronous loading.
    void UpdateAsyncLoading();
    /// Finish asynchronous loading.
    void FinishAsyncLoading();
    /// Finish loading. Sets the scene filename and checksum.
    void FinishLoading(Deserializer* source);
    /// Finish saving. Sets the scene filename and checksum.
    void FinishSaving(Serializer* dest) const;
    /// Preload resources from a binary scene or object prefab file.
    void PreloadResources(File* file, bool isSceneFile);
    /// Preload resources from an XML scene or object prefab file.
    void PreloadResourcesXML(const XMLElement& element);
    /// Preload resources from a JSON scene or object prefab file.
    void PreloadResourcesJSON(const JSONValue& value);

    /// Replicated scene nodes by ID.
    HashMap<unsigned, Node*> replicatedNodes_;
    /// Local scene nodes by ID.
    HashMap<unsigned, Node*> localNodes_;
    /// Replicated components by ID.
    HashMap<unsigned, Component*> replicatedComponents_;
    /// Local components by ID.
    HashMap<unsigned, Component*> localComponents_;
    /// Cached tagged nodes by tag.
    HashMap<StringHash, Vector<Node*>> taggedNodes_;
    /// Asynchronous loading progress.
    AsyncProgress asyncProgress_;
    /// Node and component ID resolver for asynchronous loading.
    SceneResolver resolver_;
    /// Source file name.
    mutable String fileName_;
    /// Required package files for networking.
    Vector<SharedPtr<PackageFile>> requiredPackageFiles_;
    /// Registered node user variable reverse mappings.
    HashMap<StringHash, String> varNames_;
    /// Nodes to check for attribute changes on the next network update.
    HashSet<unsigned> networkUpdateNodes_;
    /// Components to check for attribute changes on the next network update.
    HashSet<unsigned> networkUpdateComponents_;
    /// Delayed dirty notification queue for components.
    Vector<Component*> delayedDirtyComponents_;
    /// Mutex for the delayed dirty notification queue.
    Mutex sceneMutex_;
    /// Preallocated event data map for smoothing update events.
    VariantMap smoothingData_;
    /// Next free non-local node ID.
    unsigned replicatedNodeID_;
    /// Next free non-local component ID.
    unsigned replicatedComponentID_;
    /// Next free local node ID.
    unsigned localNodeID_;
    /// Next free local component ID.
    unsigned localComponentID_;
    /// Scene source file checksum.
    mutable hash32 checksum_;
    /// Maximum milliseconds per frame to spend on async scene loading.
    int asyncLoadingMs_;
    /// Scene update time scale.
    float timeScale_;
    /// Elapsed time accumulator.
    float elapsedTime_;
    /// Motion smoothing constant.
    float smoothingConstant_;
    /// Motion smoothing snap threshold.
    float snapThreshold_;
    /// Update enabled flag.
    bool updateEnabled_;
    /// Asynchronous loading flag.
    bool asyncLoading_;
    /// Threaded update flag.
    bool threadedUpdate_;
};

/// Register Scene library objects.
/// @nobind
void URHO3D_API RegisterSceneLibrary(Context* context);

}
