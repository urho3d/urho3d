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

#include "Precompiled.h"
#include "Component.h"
#include "Context.h"
#include "CoreEvents.h"
#include "File.h"
#include "Log.h"
#include "Profiler.h"
#include "Scene.h"
#include "SceneEvents.h"
#include "StringUtils.h"
#include "XMLFile.h"

OBJECTTYPESTATIC(Scene);

static const int ASYNC_LOAD_MIN_FPS = 50;
static const int ASYNC_LOAD_MAX_MSEC = (int)(1000.0f / ASYNC_LOAD_MIN_FPS);

Scene::Scene(Context* context) :
    Node(context),
    networkMode_(NM_NONETWORK),
    nonLocalNodeID_(FIRST_NONLOCAL_ID),
    nonLocalComponentID_(FIRST_NONLOCAL_ID),
    localNodeID_(FIRST_LOCAL_ID),
    localComponentID_(FIRST_LOCAL_ID),
    active_(true),
    asyncLoading_(false)
{
    // Assign an ID to self so that nodes can refer to this node as a parent
    SetID(GetFreeNodeID(false));
    NodeAdded(this);
    
    SubscribeToEvent(E_UPDATE, HANDLER(Scene, HandleUpdate));
}

Scene::~Scene()
{
    // Remove scene reference from all nodes that still exist
    for (std::map<unsigned, Node*>::iterator i = allNodes_.begin(); i != allNodes_.end(); ++i)
        i->second->SetScene(0);
}

void Scene::RegisterObject(Context* context)
{
    context->RegisterFactory<Scene>();
    context->CopyBaseAttributes<Node, Scene>();
    
    ATTRIBUTE(Scene, VAR_INT, "Next Non-Local Node ID", nonLocalNodeID_, FIRST_NONLOCAL_ID);
    ATTRIBUTE(Scene, VAR_INT, "Next Non-Local Component ID", nonLocalComponentID_, FIRST_NONLOCAL_ID);
    ATTRIBUTE(Scene, VAR_INT, "Next Local Node ID", localNodeID_, FIRST_LOCAL_ID);
    ATTRIBUTE(Scene, VAR_INT, "Next Local Component ID", localComponentID_, FIRST_LOCAL_ID);
}

bool Scene::Load(Deserializer& source)
{
    StopAsyncLoading();
    
    // Check ID
    if (source.ReadID() != "USCN")
    {
        LOGERROR(source.GetName() + " is not a valid scene file");
        return false;
    }
    
    // Load the whole scene, then perform post-load if successfully loaded
    if (Node::Load(source))
    {
        PostLoad();
        return true;
    }
    else
        return false;
}

bool Scene::Save(Serializer& dest)
{
    // Write ID first
    if (!dest.WriteID("USCN"))
    {
        LOGERROR("Could not save scene, writing to stream failed");
        return false;
    }
    
    return Node::Save(dest);
}

bool Scene::LoadXML(const XMLElement& source)
{
    StopAsyncLoading();
    
    // Load the whole scene, then perform post-load if successfully loaded
    if (Node::LoadXML(source))
    {
        PostLoad();
        return true;
    }
    else
        return false;
}

bool Scene::LoadXML(Deserializer& source)
{
    StopAsyncLoading();
    
    SharedPtr<XMLFile> xml(new XMLFile(context_));
    if (!xml->Load(source))
        return false;
    
    return LoadXML(xml->GetRootElement());
}

bool Scene::SaveXML(Serializer& dest)
{
    SharedPtr<XMLFile> xml(new XMLFile(context_));
    XMLElement rootElem = xml->CreateRootElement("scene");
    if (!SaveXML(rootElem))
        return false;
    
    return xml->Save(dest);
}

bool Scene::LoadAsync(File* file)
{
    if (!file)
    {
        LOGERROR("Null file for async loading");
        return false;
    }
    
    StopAsyncLoading();
    
    // Check ID
    if (file->ReadID() != "USCN")
    {
        LOGERROR(file->GetName() + " is not a valid scene file");
        return false;
    }
    
    // Clear the previous scene and load the root level components first
    if (!Node::Load(*file, false))
        return false;
    
    // Then prepare for loading all root level child nodes in the async update
    asyncLoading_ = true;
    asyncProgress_.file_ = file;
    asyncProgress_.xmlFile_.Reset();
    asyncProgress_.xmlElement_ = XMLElement();
    asyncProgress_.loadedNodes_ = 0;
    asyncProgress_.totalNodes_ = file->ReadVLE();
    
    return true;
}

bool Scene::LoadAsyncXML(File* file)
{
    if (!file)
    {
        LOGERROR("Null file for async loading");
        return false;
    }
    
    StopAsyncLoading();
    
    SharedPtr<XMLFile> xmlFile(new XMLFile(context_));
    if (!xmlFile->Load(*file))
        return false;
    
    // Clear the previous scene and load the root level components first
    XMLElement rootElement = xmlFile->GetRootElement();
    if (!Node::LoadXML(rootElement, false))
        return false;
    
    // Then prepare for loading all root level child nodes in the async update
    XMLElement childNodeElement = rootElement.GetChildElement("node");
    asyncLoading_ = true;
    asyncProgress_.file_.Reset();
    asyncProgress_.xmlFile_ = xmlFile;
    asyncProgress_.xmlElement_ = childNodeElement;
    asyncProgress_.loadedNodes_ = 0;
    asyncProgress_.totalNodes_ = 0;
    
    // Count the amount of child nodes
    while (childNodeElement)
    {
        ++asyncProgress_.totalNodes_;
        childNodeElement = childNodeElement.GetNextElement("node");
    }
    
    return true;
}

void Scene::StopAsyncLoading()
{
    asyncLoading_ = false;
    asyncProgress_.file_.Reset();
    asyncProgress_.xmlFile_.Reset();
    asyncProgress_.xmlElement_ = XMLElement();
}

void Scene::Update(float timeStep)
{
    if (asyncLoading_)
    {
        UpdateAsyncLoading();
        return;
    }
    
    PROFILE(UpdateScene);
    
    using namespace SceneUpdate;
    
    VariantMap eventData;
    eventData[P_SCENE] = (void*)this;
    eventData[P_TIMESTEP] = timeStep;
    
    // Update variable timestep logic
    SendEvent(E_SCENEUPDATE, eventData);
    
    // Update scene subsystems. If a physics world is present, it will be updated, triggering fixed timestep logic updates
    SendEvent(E_SCENESUBSYSTEMUPDATE, eventData);
    
    // Post-update variable timestep logic
    SendEvent(E_SCENEPOSTUPDATE, eventData);
}

void Scene::SetActive(bool enable)
{
    active_ = enable;
}

void Scene::SetNetworkMode(NetworkMode mode)
{
    networkMode_ = mode;
}

Node* Scene::GetNodeByID(unsigned id) const
{
    std::map<unsigned, Node*>::const_iterator i = allNodes_.find(id);
    if (i != allNodes_.end())
        return i->second;
    else
        return 0;
}

Component* Scene::GetComponentByID(unsigned id) const
{
    std::map<unsigned, Component*>::const_iterator i = allComponents_.find(id);
    if (i != allComponents_.end())
        return i->second;
    else
        return 0;
}

float Scene::GetAsyncProgress() const
{
    if ((!asyncLoading_) || (!asyncProgress_.totalNodes_))
        return 1.0f;
    else
        return (float)asyncProgress_.loadedNodes_ / (float)asyncProgress_.totalNodes_;
}

unsigned Scene::GetFreeNodeID(bool local)
{
    if (!local)
    {
        for (;;)
        {
            if (allNodes_.find(nonLocalNodeID_) == allNodes_.end())
                return nonLocalNodeID_;
            
            if (nonLocalNodeID_ != LAST_NONLOCAL_ID)
                ++nonLocalNodeID_;
            else
                nonLocalNodeID_ = FIRST_NONLOCAL_ID;
        }
    }
    else
    {
        for (;;)
        {
            if (allNodes_.find(localNodeID_) == allNodes_.end())
                return localNodeID_;
            
            if (localNodeID_ != LAST_LOCAL_ID)
                ++localNodeID_;
            else
                localNodeID_ = FIRST_LOCAL_ID;
        }
    }
}

unsigned Scene::GetFreeComponentID(bool local)
{
    if (!local)
    {
        for (;;)
        {
            if (allComponents_.find(nonLocalComponentID_) == allComponents_.end())
                return nonLocalComponentID_;
            
            if (nonLocalComponentID_ != LAST_NONLOCAL_ID)
                ++nonLocalComponentID_;
            else
                nonLocalComponentID_ = FIRST_NONLOCAL_ID;
        }
    }
    else
    {
        for (;;)
        {
            if (allComponents_.find(localComponentID_) == allComponents_.end())
                return localComponentID_;
            
            if (localComponentID_ != LAST_LOCAL_ID)
                ++localComponentID_;
            else
                localComponentID_ = FIRST_LOCAL_ID;
        }
    }
}


void Scene::NodeAdded(Node* node)
{
    if ((!node) || (node->GetScene()))
        return;
    
    node->SetScene(this);
    
    // If we already have an existing node with the same ID, must remove the scene reference from it
    unsigned id = node->GetID();
    std::map<unsigned, Node*>::iterator i = allNodes_.find(id);
    if ((i != allNodes_.end()) && (i->second != node))
    {
        LOGWARNING("Overwriting node with ID " + ToString(id));
        i->second->SetScene(0);
    }
    
    allNodes_[id] = node;
}

void Scene::NodeRemoved(Node* node)
{
    if ((!node) || (node->GetScene() != this))
        return;
    
    allNodes_.erase(node->GetID());
    node->SetID(0);
    node->SetScene(0);
}

void Scene::ComponentAdded(Component* component)
{
    if (!component)
        return;
    
    allComponents_[component->GetID()] = component;
}

void Scene::ComponentRemoved(Component* component)
{
    if (!component)
        return;
    
    allComponents_.erase(component->GetID());
    component->SetID(0);
}

void Scene::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;
    
    if (active_)
        Update(eventData[P_TIMESTEP].GetFloat());
}

void Scene::UpdateAsyncLoading()
{
    PROFILE(UpdateAsyncLoading);
    
    Timer asyncLoadTimer;
    
    for (;;)
    {
        if (asyncProgress_.loadedNodes_ >= asyncProgress_.totalNodes_)
        {
            FinishAsyncLoading();
            return;
        }
        
        // Read one child node either from binary or XML
        if ((asyncProgress_.file_) && (!asyncProgress_.file_->IsEof()))
        {
            Node* newNode = CreateChild(asyncProgress_.file_->ReadUInt(), false);
            newNode->Load(*asyncProgress_.file_);
        }
        if (asyncProgress_.xmlElement_)
        {
            Node* newNode = CreateChild(asyncProgress_.xmlElement_.GetInt("id"), false);
            newNode->LoadXML(asyncProgress_.xmlElement_);
            asyncProgress_.xmlElement_ = asyncProgress_.xmlElement_.GetNextElement("node");
        }
        
        ++asyncProgress_.loadedNodes_;
        
        // Break if time limit exceeded, so that we keep sufficient FPS
        if (asyncLoadTimer.GetMSec(true) >= ASYNC_LOAD_MAX_MSEC)
            break;
    }
    
    using namespace AsyncLoadProgress;
    
    VariantMap eventData;
    eventData[P_SCENE] = (void*)this;
    eventData[P_PROGRESS] = (float)asyncProgress_.loadedNodes_ / (float)asyncProgress_.totalNodes_;
    eventData[P_LOADEDNODES]  = asyncProgress_.loadedNodes_;
    eventData[P_TOTALNODES]  = asyncProgress_.totalNodes_;
    SendEvent(E_ASYNCLOADPROGRESS, eventData);
}

void Scene::FinishAsyncLoading()
{
    PostLoad();
    StopAsyncLoading();
    
    using namespace AsyncLoadFinished;
    
    VariantMap eventData;
    eventData[P_SCENE] = (void*)this;
    SendEvent(E_ASYNCLOADFINISHED, eventData);
}

void RegisterSceneLibrary(Context* context)
{
    Node::RegisterObject(context);
    Scene::RegisterObject(context);
}
