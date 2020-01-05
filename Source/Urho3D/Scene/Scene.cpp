//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Core/CoreEvents.h"
#include "../Core/Profiler.h"
#include "../Core/WorkQueue.h"
#include "../IO/File.h"
#include "../IO/Log.h"
#include "../IO/PackageFile.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/ResourceEvents.h"
#include "../Resource/XMLFile.h"
#include "../Resource/JSONFile.h"
#include "../Scene/Component.h"
#include "../Scene/ObjectAnimation.h"
#include "../Scene/ReplicationState.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneEvents.h"
#include "../Scene/SmoothedTransform.h"
#include "../Scene/SplinePath.h"
#include "../Scene/UnknownComponent.h"
#include "../Scene/ValueAnimation.h"

#include "../DebugNew.h"

namespace Urho3D
{

const char* SCENE_CATEGORY = "Scene";
const char* LOGIC_CATEGORY = "Logic";
const char* SUBSYSTEM_CATEGORY = "Subsystem";

static const float DEFAULT_SMOOTHING_CONSTANT = 50.0f;
static const float DEFAULT_SNAP_THRESHOLD = 5.0f;

Scene::Scene(Context* context) :
    Node(context),
    replicatedNodeID_(FIRST_REPLICATED_ID),
    replicatedComponentID_(FIRST_REPLICATED_ID),
    localNodeID_(FIRST_LOCAL_ID),
    localComponentID_(FIRST_LOCAL_ID),
    checksum_(0),
    asyncLoadingMs_(5),
    timeScale_(1.0f),
    elapsedTime_(0),
    smoothingConstant_(DEFAULT_SMOOTHING_CONSTANT),
    snapThreshold_(DEFAULT_SNAP_THRESHOLD),
    updateEnabled_(true),
    asyncLoading_(false),
    threadedUpdate_(false)
{
    // Assign an ID to self so that nodes can refer to this node as a parent
    SetID(GetFreeNodeID(REPLICATED));
    NodeAdded(this);

    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Scene, HandleUpdate));
    SubscribeToEvent(E_RESOURCEBACKGROUNDLOADED, URHO3D_HANDLER(Scene, HandleResourceBackgroundLoaded));
}

Scene::~Scene()
{
    // Remove root-level components first, so that scene subsystems such as the octree destroy themselves. This will speed up
    // the removal of child nodes' components
    RemoveAllComponents();
    RemoveAllChildren();

    // Remove scene reference and owner from all nodes that still exist
    for (HashMap<unsigned, Node*>::Iterator i = replicatedNodes_.Begin(); i != replicatedNodes_.End(); ++i)
        i->second_->ResetScene();
    for (HashMap<unsigned, Node*>::Iterator i = localNodes_.Begin(); i != localNodes_.End(); ++i)
        i->second_->ResetScene();
}

void Scene::RegisterObject(Context* context)
{
    context->RegisterFactory<Scene>();

    URHO3D_ACCESSOR_ATTRIBUTE("Name", GetName, SetName, String, String::EMPTY, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Time Scale", GetTimeScale, SetTimeScale, float, 1.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Smoothing Constant", GetSmoothingConstant, SetSmoothingConstant, float, DEFAULT_SMOOTHING_CONSTANT,
        AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Snap Threshold", GetSnapThreshold, SetSnapThreshold, float, DEFAULT_SNAP_THRESHOLD, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Elapsed Time", GetElapsedTime, SetElapsedTime, float, 0.0f, AM_FILE);
    URHO3D_ATTRIBUTE("Next Replicated Node ID", unsigned, replicatedNodeID_, FIRST_REPLICATED_ID, AM_FILE | AM_NOEDIT);
    URHO3D_ATTRIBUTE("Next Replicated Component ID", unsigned, replicatedComponentID_, FIRST_REPLICATED_ID, AM_FILE | AM_NOEDIT);
    URHO3D_ATTRIBUTE("Next Local Node ID", unsigned, localNodeID_, FIRST_LOCAL_ID, AM_FILE | AM_NOEDIT);
    URHO3D_ATTRIBUTE("Next Local Component ID", unsigned, localComponentID_, FIRST_LOCAL_ID, AM_FILE | AM_NOEDIT);
    URHO3D_ATTRIBUTE("Variables", VariantMap, vars_, Variant::emptyVariantMap, AM_FILE); // Network replication of vars uses custom data
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Variable Names", GetVarNamesAttr, SetVarNamesAttr, String, String::EMPTY, AM_FILE | AM_NOEDIT);
}

bool Scene::Load(Deserializer& source)
{
    URHO3D_PROFILE(LoadScene);

    StopAsyncLoading();

    // Check ID
    if (source.ReadFileID() != "USCN")
    {
        URHO3D_LOGERROR(source.GetName() + " is not a valid scene file");
        return false;
    }

    URHO3D_LOGINFO("Loading scene from " + source.GetName());

    Clear();

    // Load the whole scene, then perform post-load if successfully loaded
    if (Node::Load(source))
    {
        FinishLoading(&source);
        return true;
    }
    else
        return false;
}

bool Scene::Save(Serializer& dest) const
{
    URHO3D_PROFILE(SaveScene);

    // Write ID first
    if (!dest.WriteFileID("USCN"))
    {
        URHO3D_LOGERROR("Could not save scene, writing to stream failed");
        return false;
    }

    auto* ptr = dynamic_cast<Deserializer*>(&dest);
    if (ptr)
        URHO3D_LOGINFO("Saving scene to " + ptr->GetName());

    if (Node::Save(dest))
    {
        FinishSaving(&dest);
        return true;
    }
    else
        return false;
}

bool Scene::LoadXML(const XMLElement& source)
{
    URHO3D_PROFILE(LoadSceneXML);

    StopAsyncLoading();

    // Load the whole scene, then perform post-load if successfully loaded
    // Note: the scene filename and checksum can not be set, as we only used an XML element
    if (Node::LoadXML(source))
    {
        FinishLoading(nullptr);
        return true;
    }
    else
        return false;
}

bool Scene::LoadJSON(const JSONValue& source)
{
    URHO3D_PROFILE(LoadSceneJSON);

    StopAsyncLoading();

    // Load the whole scene, then perform post-load if successfully loaded
    // Note: the scene filename and checksum can not be set, as we only used an XML element
    if (Node::LoadJSON(source))
    {
        FinishLoading(nullptr);
        return true;
    }
    else
        return false;
}

void Scene::MarkNetworkUpdate()
{
    if (!networkUpdate_)
    {
        MarkNetworkUpdate(this);
        networkUpdate_ = true;
    }
}

void Scene::AddReplicationState(NodeReplicationState* state)
{
    Node::AddReplicationState(state);

    // This is the first update for a new connection. Mark all replicated nodes dirty
    for (HashMap<unsigned, Node*>::ConstIterator i = replicatedNodes_.Begin(); i != replicatedNodes_.End(); ++i)
        state->sceneState_->dirtyNodes_.Insert(i->first_);
}

bool Scene::LoadXML(Deserializer& source)
{
    URHO3D_PROFILE(LoadSceneXML);

    StopAsyncLoading();

    SharedPtr<XMLFile> xml(new XMLFile(context_));
    if (!xml->Load(source))
        return false;

    URHO3D_LOGINFO("Loading scene from " + source.GetName());

    Clear();

    if (Node::LoadXML(xml->GetRoot()))
    {
        FinishLoading(&source);
        return true;
    }
    else
        return false;
}

bool Scene::LoadJSON(Deserializer& source)
{
    URHO3D_PROFILE(LoadSceneJSON);

    StopAsyncLoading();

    SharedPtr<JSONFile> json(new JSONFile(context_));
    if (!json->Load(source))
        return false;

    URHO3D_LOGINFO("Loading scene from " + source.GetName());

    Clear();

    if (Node::LoadJSON(json->GetRoot()))
    {
        FinishLoading(&source);
        return true;
    }
    else
        return false;
}

bool Scene::SaveXML(Serializer& dest, const String& indentation) const
{
    URHO3D_PROFILE(SaveSceneXML);

    SharedPtr<XMLFile> xml(new XMLFile(context_));
    XMLElement rootElem = xml->CreateRoot("scene");
    if (!SaveXML(rootElem))
        return false;

    auto* ptr = dynamic_cast<Deserializer*>(&dest);
    if (ptr)
        URHO3D_LOGINFO("Saving scene to " + ptr->GetName());

    if (xml->Save(dest, indentation))
    {
        FinishSaving(&dest);
        return true;
    }
    else
        return false;
}

bool Scene::SaveJSON(Serializer& dest, const String& indentation) const
{
    URHO3D_PROFILE(SaveSceneJSON);

    SharedPtr<JSONFile> json(new JSONFile(context_));
    JSONValue rootVal;
    if (!SaveJSON(rootVal))
        return false;

    auto* ptr = dynamic_cast<Deserializer*>(&dest);
    if (ptr)
        URHO3D_LOGINFO("Saving scene to " + ptr->GetName());

    json->GetRoot() = rootVal;

    if (json->Save(dest, indentation))
    {
        FinishSaving(&dest);
        return true;
    }
    else
        return false;
}

bool Scene::LoadAsync(File* file, LoadMode mode)
{
    if (!file)
    {
        URHO3D_LOGERROR("Null file for async loading");
        return false;
    }

    StopAsyncLoading();

    // Check ID
    bool isSceneFile = file->ReadFileID() == "USCN";
    if (!isSceneFile)
    {
        // In resource load mode can load also object prefabs, which have no identifier
        if (mode > LOAD_RESOURCES_ONLY)
        {
            URHO3D_LOGERROR(file->GetName() + " is not a valid scene file");
            return false;
        }
        else
            file->Seek(0);
    }

    if (mode > LOAD_RESOURCES_ONLY)
    {
        URHO3D_LOGINFO("Loading scene from " + file->GetName());
        Clear();
    }

    asyncLoading_ = true;
    asyncProgress_.file_ = file;
    asyncProgress_.mode_ = mode;
    asyncProgress_.loadedNodes_ = asyncProgress_.totalNodes_ = asyncProgress_.loadedResources_ = asyncProgress_.totalResources_ = 0;
    asyncProgress_.resources_.Clear();

    if (mode > LOAD_RESOURCES_ONLY)
    {
        // Preload resources if appropriate, then return to the original position for loading the scene content
        if (mode != LOAD_SCENE)
        {
            URHO3D_PROFILE(FindResourcesToPreload);

            unsigned currentPos = file->GetPosition();
            PreloadResources(file, isSceneFile);
            file->Seek(currentPos);
        }

        // Store own old ID for resolving possible root node references
        unsigned nodeID = file->ReadUInt();
        resolver_.AddNode(nodeID, this);

        // Load root level components first
        if (!Node::Load(*file, resolver_, false))
        {
            StopAsyncLoading();
            return false;
        }

        // Then prepare to load child nodes in the async updates
        asyncProgress_.totalNodes_ = file->ReadVLE();
    }
    else
    {
        URHO3D_PROFILE(FindResourcesToPreload);

        URHO3D_LOGINFO("Preloading resources from " + file->GetName());
        PreloadResources(file, isSceneFile);
    }

    return true;
}

bool Scene::LoadAsyncXML(File* file, LoadMode mode)
{
    if (!file)
    {
        URHO3D_LOGERROR("Null file for async loading");
        return false;
    }

    StopAsyncLoading();

    SharedPtr<XMLFile> xml(new XMLFile(context_));
    if (!xml->Load(*file))
        return false;

    if (mode > LOAD_RESOURCES_ONLY)
    {
        URHO3D_LOGINFO("Loading scene from " + file->GetName());
        Clear();
    }

    asyncLoading_ = true;
    asyncProgress_.xmlFile_ = xml;
    asyncProgress_.file_ = file;
    asyncProgress_.mode_ = mode;
    asyncProgress_.loadedNodes_ = asyncProgress_.totalNodes_ = asyncProgress_.loadedResources_ = asyncProgress_.totalResources_ = 0;
    asyncProgress_.resources_.Clear();

    if (mode > LOAD_RESOURCES_ONLY)
    {
        XMLElement rootElement = xml->GetRoot();

        // Preload resources if appropriate
        if (mode != LOAD_SCENE)
        {
            URHO3D_PROFILE(FindResourcesToPreload);

            PreloadResourcesXML(rootElement);
        }

        // Store own old ID for resolving possible root node references
        unsigned nodeID = rootElement.GetUInt("id");
        resolver_.AddNode(nodeID, this);

        // Load the root level components first
        if (!Node::LoadXML(rootElement, resolver_, false))
            return false;

        // Then prepare for loading all root level child nodes in the async update
        XMLElement childNodeElement = rootElement.GetChild("node");
        asyncProgress_.xmlElement_ = childNodeElement;

        // Count the amount of child nodes
        while (childNodeElement)
        {
            ++asyncProgress_.totalNodes_;
            childNodeElement = childNodeElement.GetNext("node");
        }
    }
    else
    {
        URHO3D_PROFILE(FindResourcesToPreload);

        URHO3D_LOGINFO("Preloading resources from " + file->GetName());
        PreloadResourcesXML(xml->GetRoot());
    }

    return true;
}

bool Scene::LoadAsyncJSON(File* file, LoadMode mode)
{
    if (!file)
    {
        URHO3D_LOGERROR("Null file for async loading");
        return false;
    }

    StopAsyncLoading();

    SharedPtr<JSONFile> json(new JSONFile(context_));
    if (!json->Load(*file))
        return false;

    if (mode > LOAD_RESOURCES_ONLY)
    {
        URHO3D_LOGINFO("Loading scene from " + file->GetName());
        Clear();
    }

    asyncLoading_ = true;
    asyncProgress_.jsonFile_ = json;
    asyncProgress_.file_ = file;
    asyncProgress_.mode_ = mode;
    asyncProgress_.loadedNodes_ = asyncProgress_.totalNodes_ = asyncProgress_.loadedResources_ = asyncProgress_.totalResources_ = 0;
    asyncProgress_.resources_.Clear();

    if (mode > LOAD_RESOURCES_ONLY)
    {
        JSONValue rootVal = json->GetRoot();

        // Preload resources if appropriate
        if (mode != LOAD_SCENE)
        {
            URHO3D_PROFILE(FindResourcesToPreload);

            PreloadResourcesJSON(rootVal);
        }

        // Store own old ID for resolving possible root node references
        unsigned nodeID = rootVal.Get("id").GetUInt();
        resolver_.AddNode(nodeID, this);

        // Load the root level components first
        if (!Node::LoadJSON(rootVal, resolver_, false))
            return false;

        // Then prepare for loading all root level child nodes in the async update
        JSONArray childrenArray = rootVal.Get("children").GetArray();
        asyncProgress_.jsonIndex_ = 0;

        // Count the amount of child nodes
        asyncProgress_.totalNodes_ = childrenArray.Size();
    }
    else
    {
        URHO3D_PROFILE(FindResourcesToPreload);

        URHO3D_LOGINFO("Preloading resources from " + file->GetName());
        PreloadResourcesJSON(json->GetRoot());
    }

    return true;
}

void Scene::StopAsyncLoading()
{
    asyncLoading_ = false;
    asyncProgress_.file_.Reset();
    asyncProgress_.xmlFile_.Reset();
    asyncProgress_.jsonFile_.Reset();
    asyncProgress_.xmlElement_ = XMLElement::EMPTY;
    asyncProgress_.jsonIndex_ = 0;
    asyncProgress_.resources_.Clear();
    resolver_.Reset();
}

Node* Scene::Instantiate(Deserializer& source, const Vector3& position, const Quaternion& rotation, CreateMode mode)
{
    URHO3D_PROFILE(Instantiate);

    SceneResolver resolver;
    unsigned nodeID = source.ReadUInt();
    // Rewrite IDs when instantiating
    Node* node = CreateChild(0, mode);
    resolver.AddNode(nodeID, node);
    if (node->Load(source, resolver, true, true, mode))
    {
        resolver.Resolve();
        node->SetTransform(position, rotation);
        node->ApplyAttributes();
        return node;
    }
    else
    {
        node->Remove();
        return nullptr;
    }
}

Node* Scene::InstantiateXML(const XMLElement& source, const Vector3& position, const Quaternion& rotation, CreateMode mode)
{
    URHO3D_PROFILE(InstantiateXML);

    SceneResolver resolver;
    unsigned nodeID = source.GetUInt("id");
    // Rewrite IDs when instantiating
    Node* node = CreateChild(0, mode);
    resolver.AddNode(nodeID, node);
    if (node->LoadXML(source, resolver, true, true, mode))
    {
        resolver.Resolve();
        node->SetTransform(position, rotation);
        node->ApplyAttributes();
        return node;
    }
    else
    {
        node->Remove();
        return nullptr;
    }
}

Node* Scene::InstantiateJSON(const JSONValue& source, const Vector3& position, const Quaternion& rotation, CreateMode mode)
{
    URHO3D_PROFILE(InstantiateJSON);

    SceneResolver resolver;
    unsigned nodeID = source.Get("id").GetUInt();
    // Rewrite IDs when instantiating
    Node* node = CreateChild(0, mode);
    resolver.AddNode(nodeID, node);
    if (node->LoadJSON(source, resolver, true, true, mode))
    {
        resolver.Resolve();
        node->SetTransform(position, rotation);
        node->ApplyAttributes();
        return node;
    }
    else
    {
        node->Remove();
        return nullptr;
    }
}

Node* Scene::InstantiateXML(Deserializer& source, const Vector3& position, const Quaternion& rotation, CreateMode mode)
{
    SharedPtr<XMLFile> xml(new XMLFile(context_));
    if (!xml->Load(source))
        return nullptr;

    return InstantiateXML(xml->GetRoot(), position, rotation, mode);
}

Node* Scene::InstantiateJSON(Deserializer& source, const Vector3& position, const Quaternion& rotation, CreateMode mode)
{
    SharedPtr<JSONFile> json(new JSONFile(context_));
    if (!json->Load(source))
        return nullptr;

    return InstantiateJSON(json->GetRoot(), position, rotation, mode);
}

void Scene::Clear(bool clearReplicated, bool clearLocal)
{
    StopAsyncLoading();

    RemoveChildren(clearReplicated, clearLocal, true);
    RemoveComponents(clearReplicated, clearLocal);

    // Only clear name etc. if clearing completely
    if (clearReplicated && clearLocal)
    {
        UnregisterAllVars();
        SetName(String::EMPTY);
        fileName_.Clear();
        checksum_ = 0;
    }

    // Reset ID generators
    if (clearReplicated)
    {
        replicatedNodeID_ = FIRST_REPLICATED_ID;
        replicatedComponentID_ = FIRST_REPLICATED_ID;
    }
    if (clearLocal)
    {
        localNodeID_ = FIRST_LOCAL_ID;
        localComponentID_ = FIRST_LOCAL_ID;
    }
}

void Scene::SetUpdateEnabled(bool enable)
{
    updateEnabled_ = enable;
}

void Scene::SetTimeScale(float scale)
{
    timeScale_ = Max(scale, M_EPSILON);
    Node::MarkNetworkUpdate();
}

void Scene::SetSmoothingConstant(float constant)
{
    smoothingConstant_ = Max(constant, M_EPSILON);
    Node::MarkNetworkUpdate();
}

void Scene::SetSnapThreshold(float threshold)
{
    snapThreshold_ = Max(threshold, 0.0f);
    Node::MarkNetworkUpdate();
}

void Scene::SetAsyncLoadingMs(int ms)
{
    asyncLoadingMs_ = Max(ms, 1);
}

void Scene::SetElapsedTime(float time)
{
    elapsedTime_ = time;
}

void Scene::AddRequiredPackageFile(PackageFile* package)
{
    // Do not add packages that failed to load
    if (!package || !package->GetNumFiles())
        return;

    requiredPackageFiles_.Push(SharedPtr<PackageFile>(package));
}

void Scene::ClearRequiredPackageFiles()
{
    requiredPackageFiles_.Clear();
}

void Scene::RegisterVar(const String& name)
{
    varNames_[name] = name;
}

void Scene::UnregisterVar(const String& name)
{
    varNames_.Erase(name);
}

void Scene::UnregisterAllVars()
{
    varNames_.Clear();
}

Node* Scene::GetNode(unsigned id) const
{
    if (IsReplicatedID(id))
    {
        HashMap<unsigned, Node*>::ConstIterator i = replicatedNodes_.Find(id);
        return i != replicatedNodes_.End() ? i->second_ : nullptr;
    }
    else
    {
        HashMap<unsigned, Node*>::ConstIterator i = localNodes_.Find(id);
        return i != localNodes_.End() ? i->second_ : nullptr;
    }
}

bool Scene::GetNodesWithTag(PODVector<Node*>& dest, const String& tag) const
{
    dest.Clear();
    HashMap<StringHash, PODVector<Node*> >::ConstIterator it = taggedNodes_.Find(tag);
    if (it != taggedNodes_.End())
    {
        dest = it->second_;
        return true;
    }
    else
        return false;
}

Component* Scene::GetComponent(unsigned id) const
{
    if (IsReplicatedID(id))
    {
        HashMap<unsigned, Component*>::ConstIterator i = replicatedComponents_.Find(id);
        return i != replicatedComponents_.End() ? i->second_ : nullptr;
    }
    else
    {
        HashMap<unsigned, Component*>::ConstIterator i = localComponents_.Find(id);
        return i != localComponents_.End() ? i->second_ : nullptr;
    }
}

float Scene::GetAsyncProgress() const
{
    return !asyncLoading_ || asyncProgress_.totalNodes_ + asyncProgress_.totalResources_ == 0 ? 1.0f :
        (float)(asyncProgress_.loadedNodes_ + asyncProgress_.loadedResources_) /
        (float)(asyncProgress_.totalNodes_ + asyncProgress_.totalResources_);
}

const String& Scene::GetVarName(StringHash hash) const
{
    HashMap<StringHash, String>::ConstIterator i = varNames_.Find(hash);
    return i != varNames_.End() ? i->second_ : String::EMPTY;
}

void Scene::Update(float timeStep)
{
    if (asyncLoading_)
    {
        UpdateAsyncLoading();
        // If only preloading resources, scene update can continue
        if (asyncProgress_.mode_ > LOAD_RESOURCES_ONLY)
            return;
    }

    URHO3D_PROFILE(UpdateScene);

    timeStep *= timeScale_;

    using namespace SceneUpdate;

    VariantMap& eventData = GetEventDataMap();
    eventData[P_SCENE] = this;
    eventData[P_TIMESTEP] = timeStep;

    // Update variable timestep logic
    SendEvent(E_SCENEUPDATE, eventData);

    // Update scene attribute animation.
    SendEvent(E_ATTRIBUTEANIMATIONUPDATE, eventData);

    // Update scene subsystems. If a physics world is present, it will be updated, triggering fixed timestep logic updates
    SendEvent(E_SCENESUBSYSTEMUPDATE, eventData);

    // Update transform smoothing
    {
        URHO3D_PROFILE(UpdateSmoothing);

        float constant = 1.0f - Clamp(powf(2.0f, -timeStep * smoothingConstant_), 0.0f, 1.0f);
        float squaredSnapThreshold = snapThreshold_ * snapThreshold_;

        using namespace UpdateSmoothing;

        smoothingData_[P_CONSTANT] = constant;
        smoothingData_[P_SQUAREDSNAPTHRESHOLD] = squaredSnapThreshold;
        SendEvent(E_UPDATESMOOTHING, smoothingData_);
    }

    // Post-update variable timestep logic
    SendEvent(E_SCENEPOSTUPDATE, eventData);

    // Note: using a float for elapsed time accumulation is inherently inaccurate. The purpose of this value is
    // primarily to update material animation effects, as it is available to shaders. It can be reset by calling
    // SetElapsedTime()
    elapsedTime_ += timeStep;
}

void Scene::BeginThreadedUpdate()
{
    // Check the work queue subsystem whether it actually has created worker threads. If not, do not enter threaded mode.
    if (GetSubsystem<WorkQueue>()->GetNumThreads())
        threadedUpdate_ = true;
}

void Scene::EndThreadedUpdate()
{
    if (!threadedUpdate_)
        return;

    threadedUpdate_ = false;

    if (!delayedDirtyComponents_.Empty())
    {
        URHO3D_PROFILE(EndThreadedUpdate);

        for (PODVector<Component*>::ConstIterator i = delayedDirtyComponents_.Begin(); i != delayedDirtyComponents_.End(); ++i)
            (*i)->OnMarkedDirty((*i)->GetNode());
        delayedDirtyComponents_.Clear();
    }
}

void Scene::DelayedMarkedDirty(Component* component)
{
    MutexLock lock(sceneMutex_);
    delayedDirtyComponents_.Push(component);
}

unsigned Scene::GetFreeNodeID(CreateMode mode)
{
    if (mode == REPLICATED)
    {
        for (;;)
        {
            unsigned ret = replicatedNodeID_;
            if (replicatedNodeID_ < LAST_REPLICATED_ID)
                ++replicatedNodeID_;
            else
                replicatedNodeID_ = FIRST_REPLICATED_ID;

            if (!replicatedNodes_.Contains(ret))
                return ret;
        }
    }
    else
    {
        for (;;)
        {
            unsigned ret = localNodeID_;
            if (localNodeID_ < LAST_LOCAL_ID)
                ++localNodeID_;
            else
                localNodeID_ = FIRST_LOCAL_ID;

            if (!localNodes_.Contains(ret))
                return ret;
        }
    }
}

unsigned Scene::GetFreeComponentID(CreateMode mode)
{
    if (mode == REPLICATED)
    {
        for (;;)
        {
            unsigned ret = replicatedComponentID_;
            if (replicatedComponentID_ < LAST_REPLICATED_ID)
                ++replicatedComponentID_;
            else
                replicatedComponentID_ = FIRST_REPLICATED_ID;

            if (!replicatedComponents_.Contains(ret))
                return ret;
        }
    }
    else
    {
        for (;;)
        {
            unsigned ret = localComponentID_;
            if (localComponentID_ < LAST_LOCAL_ID)
                ++localComponentID_;
            else
                localComponentID_ = FIRST_LOCAL_ID;

            if (!localComponents_.Contains(ret))
                return ret;
        }
    }
}

void Scene::NodeAdded(Node* node)
{
    if (!node || node->GetScene() == this)
        return;

    // Remove from old scene first
    Scene* oldScene = node->GetScene();
    if (oldScene)
        oldScene->NodeRemoved(node);

    node->SetScene(this);

    // If the new node has an ID of zero (default), assign a replicated ID now
    unsigned id = node->GetID();
    if (!id)
    {
        id = GetFreeNodeID(REPLICATED);
        node->SetID(id);
    }

    // If node with same ID exists, remove the scene reference from it and overwrite with the new node
    if (IsReplicatedID(id))
    {
        HashMap<unsigned, Node*>::Iterator i = replicatedNodes_.Find(id);
        if (i != replicatedNodes_.End() && i->second_ != node)
        {
            URHO3D_LOGWARNING("Overwriting node with ID " + String(id));
            NodeRemoved(i->second_);
        }

        replicatedNodes_[id] = node;

        MarkNetworkUpdate(node);
        MarkReplicationDirty(node);
    }
    else
    {
        HashMap<unsigned, Node*>::Iterator i = localNodes_.Find(id);
        if (i != localNodes_.End() && i->second_ != node)
        {
            URHO3D_LOGWARNING("Overwriting node with ID " + String(id));
            NodeRemoved(i->second_);
        }
        localNodes_[id] = node;
    }

    // Cache tag if already tagged.
    if (!node->GetTags().Empty())
    {
        const StringVector& tags = node->GetTags();
        for (unsigned i = 0; i < tags.Size(); ++i)
            taggedNodes_[tags[i]].Push(node);
    }

    // Add already created components and child nodes now
    const Vector<SharedPtr<Component> >& components = node->GetComponents();
    for (Vector<SharedPtr<Component> >::ConstIterator i = components.Begin(); i != components.End(); ++i)
        ComponentAdded(*i);
    const Vector<SharedPtr<Node> >& children = node->GetChildren();
    for (Vector<SharedPtr<Node> >::ConstIterator i = children.Begin(); i != children.End(); ++i)
        NodeAdded(*i);
}

void Scene::NodeTagAdded(Node* node, const String& tag)
{
    taggedNodes_[tag].Push(node);
}

void Scene::NodeTagRemoved(Node* node, const String& tag)
{
    taggedNodes_[tag].Remove(node);
}

void Scene::NodeRemoved(Node* node)
{
    if (!node || node->GetScene() != this)
        return;

    unsigned id = node->GetID();
    if (Scene::IsReplicatedID(id))
    {
        replicatedNodes_.Erase(id);
        MarkReplicationDirty(node);
    }
    else
        localNodes_.Erase(id);

    node->ResetScene();

    // Remove node from tag cache
    if (!node->GetTags().Empty())
    {
        const StringVector& tags = node->GetTags();
        for (unsigned i = 0; i < tags.Size(); ++i)
            taggedNodes_[tags[i]].Remove(node);
    }

    // Remove components and child nodes as well
    const Vector<SharedPtr<Component> >& components = node->GetComponents();
    for (Vector<SharedPtr<Component> >::ConstIterator i = components.Begin(); i != components.End(); ++i)
        ComponentRemoved(*i);
    const Vector<SharedPtr<Node> >& children = node->GetChildren();
    for (Vector<SharedPtr<Node> >::ConstIterator i = children.Begin(); i != children.End(); ++i)
        NodeRemoved(*i);
}

void Scene::ComponentAdded(Component* component)
{
    if (!component)
        return;

    unsigned id = component->GetID();

    // If the new component has an ID of zero (default), assign a replicated ID now
    if (!id)
    {
        id = GetFreeComponentID(REPLICATED);
        component->SetID(id);
    }

    if (IsReplicatedID(id))
    {
        HashMap<unsigned, Component*>::Iterator i = replicatedComponents_.Find(id);
        if (i != replicatedComponents_.End() && i->second_ != component)
        {
            URHO3D_LOGWARNING("Overwriting component with ID " + String(id));
            ComponentRemoved(i->second_);
        }

        replicatedComponents_[id] = component;
    }
    else
    {
        HashMap<unsigned, Component*>::Iterator i = localComponents_.Find(id);
        if (i != localComponents_.End() && i->second_ != component)
        {
            URHO3D_LOGWARNING("Overwriting component with ID " + String(id));
            ComponentRemoved(i->second_);
        }

        localComponents_[id] = component;
    }

    component->OnSceneSet(this);
}

void Scene::ComponentRemoved(Component* component)
{
    if (!component)
        return;

    unsigned id = component->GetID();
    if (Scene::IsReplicatedID(id))
        replicatedComponents_.Erase(id);
    else
        localComponents_.Erase(id);

    component->SetID(0);
    component->OnSceneSet(nullptr);
}

void Scene::SetVarNamesAttr(const String& value)
{
    Vector<String> varNames = value.Split(';');

    varNames_.Clear();
    for (Vector<String>::ConstIterator i = varNames.Begin(); i != varNames.End(); ++i)
        varNames_[*i] = *i;
}

String Scene::GetVarNamesAttr() const
{
    String ret;

    if (!varNames_.Empty())
    {
        for (HashMap<StringHash, String>::ConstIterator i = varNames_.Begin(); i != varNames_.End(); ++i)
            ret += i->second_ + ";";

        ret.Resize(ret.Length() - 1);
    }

    return ret;
}

void Scene::PrepareNetworkUpdate()
{
    for (HashSet<unsigned>::Iterator i = networkUpdateNodes_.Begin(); i != networkUpdateNodes_.End(); ++i)
    {
        Node* node = GetNode(*i);
        if (node)
            node->PrepareNetworkUpdate();
    }

    for (HashSet<unsigned>::Iterator i = networkUpdateComponents_.Begin(); i != networkUpdateComponents_.End(); ++i)
    {
        Component* component = GetComponent(*i);
        if (component)
            component->PrepareNetworkUpdate();
    }

    networkUpdateNodes_.Clear();
    networkUpdateComponents_.Clear();
}

void Scene::CleanupConnection(Connection* connection)
{
    Node::CleanupConnection(connection);

    for (HashMap<unsigned, Node*>::Iterator i = replicatedNodes_.Begin(); i != replicatedNodes_.End(); ++i)
        i->second_->CleanupConnection(connection);

    for (HashMap<unsigned, Component*>::Iterator i = replicatedComponents_.Begin(); i != replicatedComponents_.End(); ++i)
        i->second_->CleanupConnection(connection);
}

void Scene::MarkNetworkUpdate(Node* node)
{
    if (node)
    {
        if (!threadedUpdate_)
            networkUpdateNodes_.Insert(node->GetID());
        else
        {
            MutexLock lock(sceneMutex_);
            networkUpdateNodes_.Insert(node->GetID());
        }
    }
}

void Scene::MarkNetworkUpdate(Component* component)
{
    if (component)
    {
        if (!threadedUpdate_)
            networkUpdateComponents_.Insert(component->GetID());
        else
        {
            MutexLock lock(sceneMutex_);
            networkUpdateComponents_.Insert(component->GetID());
        }
    }
}

void Scene::MarkReplicationDirty(Node* node)
{
    if (networkState_ && node->IsReplicated())
    {
        unsigned id = node->GetID();
        for (PODVector<ReplicationState*>::Iterator i = networkState_->replicationStates_.Begin();
             i != networkState_->replicationStates_.End(); ++i)
        {
            auto* nodeState = static_cast<NodeReplicationState*>(*i);
            nodeState->sceneState_->dirtyNodes_.Insert(id);
        }
    }
}

void Scene::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    if (!updateEnabled_)
        return;

    using namespace Update;
    Update(eventData[P_TIMESTEP].GetFloat());
}

void Scene::HandleResourceBackgroundLoaded(StringHash eventType, VariantMap& eventData)
{
    using namespace ResourceBackgroundLoaded;

    if (asyncLoading_)
    {
        auto* resource = static_cast<Resource*>(eventData[P_RESOURCE].GetPtr());
        if (asyncProgress_.resources_.Contains(resource->GetNameHash()))
        {
            asyncProgress_.resources_.Erase(resource->GetNameHash());
            ++asyncProgress_.loadedResources_;
        }
    }
}

void Scene::UpdateAsyncLoading()
{
    URHO3D_PROFILE(UpdateAsyncLoading);

    // If resources left to load, do not load nodes yet
    if (asyncProgress_.loadedResources_ < asyncProgress_.totalResources_)
        return;

    HiresTimer asyncLoadTimer;

    for (;;)
    {
        if (asyncProgress_.loadedNodes_ >= asyncProgress_.totalNodes_)
        {
            FinishAsyncLoading();
            return;
        }


        // Read one child node with its full sub-hierarchy either from binary, JSON, or XML
        /// \todo Works poorly in scenes where one root-level child node contains all content
        if (asyncProgress_.xmlFile_)
        {
            unsigned nodeID = asyncProgress_.xmlElement_.GetUInt("id");
            Node* newNode = CreateChild(nodeID, IsReplicatedID(nodeID) ? REPLICATED : LOCAL);
            resolver_.AddNode(nodeID, newNode);
            newNode->LoadXML(asyncProgress_.xmlElement_, resolver_);
            asyncProgress_.xmlElement_ = asyncProgress_.xmlElement_.GetNext("node");
        }
        else if (asyncProgress_.jsonFile_) // Load from JSON
        {
            const JSONValue& childValue = asyncProgress_.jsonFile_->GetRoot().Get("children").GetArray().At(asyncProgress_.jsonIndex_);

            unsigned nodeID =childValue.Get("id").GetUInt();
            Node* newNode = CreateChild(nodeID, IsReplicatedID(nodeID) ? REPLICATED : LOCAL);
            resolver_.AddNode(nodeID, newNode);
            newNode->LoadJSON(childValue, resolver_);
            ++asyncProgress_.jsonIndex_;
        }
        else // Load from binary
        {
            unsigned nodeID = asyncProgress_.file_->ReadUInt();
            Node* newNode = CreateChild(nodeID, IsReplicatedID(nodeID) ? REPLICATED : LOCAL);
            resolver_.AddNode(nodeID, newNode);
            newNode->Load(*asyncProgress_.file_, resolver_);
        }

        ++asyncProgress_.loadedNodes_;

        // Break if time limit exceeded, so that we keep sufficient FPS
        if (asyncLoadTimer.GetUSec(false) >= asyncLoadingMs_ * 1000LL)
            break;
    }

    using namespace AsyncLoadProgress;

    VariantMap& eventData = GetEventDataMap();
    eventData[P_SCENE] = this;
    eventData[P_PROGRESS] = GetAsyncProgress();
    eventData[P_LOADEDNODES] = asyncProgress_.loadedNodes_;
    eventData[P_TOTALNODES] = asyncProgress_.totalNodes_;
    eventData[P_LOADEDRESOURCES] = asyncProgress_.loadedResources_;
    eventData[P_TOTALRESOURCES] = asyncProgress_.totalResources_;
    SendEvent(E_ASYNCLOADPROGRESS, eventData);
}

void Scene::FinishAsyncLoading()
{
    if (asyncProgress_.mode_ > LOAD_RESOURCES_ONLY)
    {
        resolver_.Resolve();
        ApplyAttributes();
        FinishLoading(asyncProgress_.file_);
    }

    StopAsyncLoading();

    using namespace AsyncLoadFinished;

    VariantMap& eventData = GetEventDataMap();
    eventData[P_SCENE] = this;
    SendEvent(E_ASYNCLOADFINISHED, eventData);
}

void Scene::FinishLoading(Deserializer* source)
{
    if (source)
    {
        fileName_ = source->GetName();
        checksum_ = source->GetChecksum();
    }
}

void Scene::FinishSaving(Serializer* dest) const
{
    auto* ptr = dynamic_cast<Deserializer*>(dest);
    if (ptr)
    {
        fileName_ = ptr->GetName();
        checksum_ = ptr->GetChecksum();
    }
}

void Scene::PreloadResources(File* file, bool isSceneFile)
{
    // If not threaded, can not background load resources, so rather load synchronously later when needed
#ifdef URHO3D_THREADING
    auto* cache = GetSubsystem<ResourceCache>();

    // Read node ID (not needed)
    /*unsigned nodeID = */file->ReadUInt();

    // Read Node or Scene attributes; these do not include any resources
    const Vector<AttributeInfo>* attributes = context_->GetAttributes(isSceneFile ? Scene::GetTypeStatic() : Node::GetTypeStatic());
    assert(attributes);

    for (unsigned i = 0; i < attributes->Size(); ++i)
    {
        const AttributeInfo& attr = attributes->At(i);
        if (!(attr.mode_ & AM_FILE))
            continue;
        /*Variant varValue = */file->ReadVariant(attr.type_);
    }

    // Read component attributes
    unsigned numComponents = file->ReadVLE();
    for (unsigned i = 0; i < numComponents; ++i)
    {
        VectorBuffer compBuffer(*file, file->ReadVLE());
        StringHash compType = compBuffer.ReadStringHash();
        // Read component ID (not needed)
        /*unsigned compID = */compBuffer.ReadUInt();

        attributes = context_->GetAttributes(compType);
        if (attributes)
        {
            for (unsigned j = 0; j < attributes->Size(); ++j)
            {
                const AttributeInfo& attr = attributes->At(j);
                if (!(attr.mode_ & AM_FILE))
                    continue;
                Variant varValue = compBuffer.ReadVariant(attr.type_);
                if (attr.type_ == VAR_RESOURCEREF)
                {
                    const ResourceRef& ref = varValue.GetResourceRef();
                    // Sanitate resource name beforehand so that when we get the background load event, the name matches exactly
                    String name = cache->SanitateResourceName(ref.name_);
                    bool success = cache->BackgroundLoadResource(ref.type_, name);
                    if (success)
                    {
                        ++asyncProgress_.totalResources_;
                        asyncProgress_.resources_.Insert(StringHash(name));
                    }
                }
                else if (attr.type_ == VAR_RESOURCEREFLIST)
                {
                    const ResourceRefList& refList = varValue.GetResourceRefList();
                    for (unsigned k = 0; k < refList.names_.Size(); ++k)
                    {
                        String name = cache->SanitateResourceName(refList.names_[k]);
                        bool success = cache->BackgroundLoadResource(refList.type_, name);
                        if (success)
                        {
                            ++asyncProgress_.totalResources_;
                            asyncProgress_.resources_.Insert(StringHash(name));
                        }
                    }
                }
            }
        }
    }

    // Read child nodes
    unsigned numChildren = file->ReadVLE();
    for (unsigned i = 0; i < numChildren; ++i)
        PreloadResources(file, false);
#endif
}

void Scene::PreloadResourcesXML(const XMLElement& element)
{
    // If not threaded, can not background load resources, so rather load synchronously later when needed
#ifdef URHO3D_THREADING
    auto* cache = GetSubsystem<ResourceCache>();

    // Node or Scene attributes do not include any resources; therefore skip to the components
    XMLElement compElem = element.GetChild("component");
    while (compElem)
    {
        String typeName = compElem.GetAttribute("type");
        const Vector<AttributeInfo>* attributes = context_->GetAttributes(StringHash(typeName));
        if (attributes)
        {
            XMLElement attrElem = compElem.GetChild("attribute");
            unsigned startIndex = 0;

            while (attrElem)
            {
                String name = attrElem.GetAttribute("name");
                unsigned i = startIndex;
                unsigned attempts = attributes->Size();

                while (attempts)
                {
                    const AttributeInfo& attr = attributes->At(i);
                    if ((attr.mode_ & AM_FILE) && !attr.name_.Compare(name, true))
                    {
                        if (attr.type_ == VAR_RESOURCEREF)
                        {
                            ResourceRef ref = attrElem.GetVariantValue(attr.type_).GetResourceRef();
                            String name = cache->SanitateResourceName(ref.name_);
                            bool success = cache->BackgroundLoadResource(ref.type_, name);
                            if (success)
                            {
                                ++asyncProgress_.totalResources_;
                                asyncProgress_.resources_.Insert(StringHash(name));
                            }
                        }
                        else if (attr.type_ == VAR_RESOURCEREFLIST)
                        {
                            ResourceRefList refList = attrElem.GetVariantValue(attr.type_).GetResourceRefList();
                            for (unsigned k = 0; k < refList.names_.Size(); ++k)
                            {
                                String name = cache->SanitateResourceName(refList.names_[k]);
                                bool success = cache->BackgroundLoadResource(refList.type_, name);
                                if (success)
                                {
                                    ++asyncProgress_.totalResources_;
                                    asyncProgress_.resources_.Insert(StringHash(name));
                                }
                            }
                        }

                        startIndex = (i + 1) % attributes->Size();
                        break;
                    }
                    else
                    {
                        i = (i + 1) % attributes->Size();
                        --attempts;
                    }
                }

                attrElem = attrElem.GetNext("attribute");
            }
        }

        compElem = compElem.GetNext("component");
    }

    XMLElement childElem = element.GetChild("node");
    while (childElem)
    {
        PreloadResourcesXML(childElem);
        childElem = childElem.GetNext("node");
    }
#endif
}

void Scene::PreloadResourcesJSON(const JSONValue& value)
{
    // If not threaded, can not background load resources, so rather load synchronously later when needed
#ifdef URHO3D_THREADING
    auto* cache = GetSubsystem<ResourceCache>();

    // Node or Scene attributes do not include any resources; therefore skip to the components
    JSONArray componentArray = value.Get("components").GetArray();

    for (unsigned i = 0; i < componentArray.Size(); i++)
    {
        const JSONValue& compValue = componentArray.At(i);
        String typeName = compValue.Get("type").GetString();

        const Vector<AttributeInfo>* attributes = context_->GetAttributes(StringHash(typeName));
        if (attributes)
        {
            JSONArray attributesArray = compValue.Get("attributes").GetArray();

            unsigned startIndex = 0;

            for (unsigned j = 0; j < attributesArray.Size(); j++)
            {
                const JSONValue& attrVal = attributesArray.At(j);
                String name = attrVal.Get("name").GetString();
                unsigned i = startIndex;
                unsigned attempts = attributes->Size();

                while (attempts)
                {
                    const AttributeInfo& attr = attributes->At(i);
                    if ((attr.mode_ & AM_FILE) && !attr.name_.Compare(name, true))
                    {
                        if (attr.type_ == VAR_RESOURCEREF)
                        {
                            ResourceRef ref = attrVal.Get("value").GetVariantValue(attr.type_).GetResourceRef();
                            String name = cache->SanitateResourceName(ref.name_);
                            bool success = cache->BackgroundLoadResource(ref.type_, name);
                            if (success)
                            {
                                ++asyncProgress_.totalResources_;
                                asyncProgress_.resources_.Insert(StringHash(name));
                            }
                        }
                        else if (attr.type_ == VAR_RESOURCEREFLIST)
                        {
                            ResourceRefList refList = attrVal.Get("value").GetVariantValue(attr.type_).GetResourceRefList();
                            for (unsigned k = 0; k < refList.names_.Size(); ++k)
                            {
                                String name = cache->SanitateResourceName(refList.names_[k]);
                                bool success = cache->BackgroundLoadResource(refList.type_, name);
                                if (success)
                                {
                                    ++asyncProgress_.totalResources_;
                                    asyncProgress_.resources_.Insert(StringHash(name));
                                }
                            }
                        }

                        startIndex = (i + 1) % attributes->Size();
                        break;
                    }
                    else
                    {
                        i = (i + 1) % attributes->Size();
                        --attempts;
                    }
                }

            }
        }

    }

    JSONArray childrenArray = value.Get("children").GetArray();
    for (unsigned i = 0; i < childrenArray.Size(); i++)
    {
        const JSONValue& childVal = childrenArray.At(i);
        PreloadResourcesJSON(childVal);
    }
#endif
}

void RegisterSceneLibrary(Context* context)
{
    ValueAnimation::RegisterObject(context);
    ObjectAnimation::RegisterObject(context);
    Node::RegisterObject(context);
    Scene::RegisterObject(context);
    SmoothedTransform::RegisterObject(context);
    UnknownComponent::RegisterObject(context);
    SplinePath::RegisterObject(context);
}

}
