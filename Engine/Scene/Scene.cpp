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
#include "XMLFile.h"

OBJECTTYPESTATIC(Scene);

Scene::Scene(Context* context) :
    Node(context),
    nodeID_(1),
    componentID_(1),
    active_(true)
{
    // Assign an ID to self so that nodes can refer to this node as a parent
    NodeAdded(this);
    
    SubscribeToEvent(E_UPDATE, HANDLER(Scene, HandleUpdate));
}

Scene::~Scene()
{
    // Remove scene reference from all nodes that still exist
    for (std::map<unsigned, Node*>::iterator i = allNodes_.begin(); i != allNodes_.end(); ++i)
        i->second->setScene(0);
}

void Scene::RegisterObject(Context* context)
{
    context->RegisterFactory<Scene>();
    context->CopyBaseAttributes<Node, Scene>();
}

bool Scene::Load(Deserializer& source)
{
    // Check ID
    if (source.ReadID() != "USCN")
    {
        LOGERROR(source.GetName() + " is not a valid scene file");
        return false;
    }
    
    // Load the whole scene, then perform post-load if successfully loaded
    /// \todo Async loading support
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
    // Load the whole scene, then perform post-load if successfully loaded
    /// \todo Async loading support
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

void Scene::Update(float timeStep)
{
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

void Scene::NodeAdded(Node* node)
{
    if ((!node) || (node->GetScene()))
        return;
    
    // Assign ID if not already set
    if (!node->GetID())
    {
        while (allNodes_.find(nodeID_) != allNodes_.end())
            GetNextNodeID();
        node->SetID(nodeID_);
    }
    
    node->setScene(this);
    allNodes_[node->GetID()] = node;
    GetNextNodeID();
}

void Scene::NodeRemoved(Node* node)
{
    if ((!node) || (node->GetScene() != this))
        return;
    
    allNodes_.erase(node->GetID());
    node->SetID(0);
    node->setScene(0);
}

void Scene::ComponentAdded(Component* component)
{
    if (!component)
        return;
    
    // Assign ID if not already set
    if (!component->GetID())
    {
        while (allComponents_.find(componentID_) != allComponents_.end())
            GetNextComponentID();
        component->SetID(componentID_);
    }
    
    allComponents_[component->GetID()] = component;
    GetNextComponentID();
}

void Scene::ComponentRemoved(Component* component)
{
    if (!component)
        return;
    
    allComponents_.erase(component->GetID());
    component->SetID(0);
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

void Scene::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;
    
    if (active_)
        Update(eventData[P_TIMESTEP].GetFloat());
}

void RegisterSceneLibrary(Context* context)
{
    Node::RegisterObject(context);
    Scene::RegisterObject(context);
}
