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

#include "../Precompiled.h"

#include "../Scene/Component.h"
#include "../Core/Context.h"
#include "../Navigation/CrowdAgent.h"
#include "../Navigation/CrowdManager.h"
#include "../Graphics/DebugRenderer.h"
#include "../Navigation/DynamicNavigationMesh.h"
#include "../IO/Log.h"
#include "../Navigation/NavigationEvents.h"
#include "../Navigation/NavigationMesh.h"
#include "../Scene/Node.h"
#include "../Core/Profiler.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneEvents.h"
#include "../Container/Vector.h"

#include <DetourCrowd/DetourCrowd.h>
#include <Recast/Recast.h>

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* NAVIGATION_CATEGORY;

static const unsigned DEFAULT_MAX_AGENTS = 512;
static const float DEFAULT_MAX_AGENT_RADIUS = 0.f;

void CrowdAgentUpdateCallback(dtCrowdAgent* ag, float dt)
{
    static_cast<CrowdAgent*>(ag->params.userData)->OnCrowdUpdate(ag, dt);
}

CrowdManager::CrowdManager(Context* context) :
    Component(context),
    crowd_(0),
    maxAgents_(DEFAULT_MAX_AGENTS),
    maxAgentRadius_(DEFAULT_MAX_AGENT_RADIUS)
{
}

CrowdManager::~CrowdManager()
{
    dtFreeCrowd(crowd_);
    crowd_ = 0;
}

void CrowdManager::RegisterObject(Context* context)
{
    context->RegisterFactory<CrowdManager>(NAVIGATION_CATEGORY);

    ATTRIBUTE("Max Agents", unsigned, maxAgents_, DEFAULT_MAX_AGENTS, AM_DEFAULT);
    ATTRIBUTE("Max Agent Radius", float, maxAgentRadius_, DEFAULT_MAX_AGENT_RADIUS, AM_DEFAULT);
    //TODO: add attribute for navmesh
}

void CrowdManager::ApplyAttributes()
{
    // Values from Editor, saved-file, or network must be checked before applying
    maxAgents_ = Max(1, maxAgents_);
    maxAgentRadius_ = Max(0.f, maxAgentRadius_);

    if (crowd_ && (crowd_->getAgentCount() != maxAgents_ || crowd_->getMaxAgentRadius() != (maxAgentRadius_ > 0.f ? maxAgentRadius_ : navigationMesh_->GetAgentRadius())))
        CreateCrowd(true);
}

void CrowdManager::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (debug && crowd_)
    {
        // Current position-to-target line
        for (int i = 0; i < crowd_->getAgentCount(); i++)
        {
            const dtCrowdAgent* ag = crowd_->getAgent(i);
            if (!ag->active)
                continue;

            // Draw CrowdAgent shape (from its radius & height)
            CrowdAgent* crowdAgent = static_cast<CrowdAgent*>(ag->params.userData);
            crowdAgent->DrawDebugGeometry(debug, depthTest);

            // Draw move target if any
            if (crowdAgent->GetTargetState() == CA_TARGET_NONE)
                continue;

            Color color(0.6f, 0.2f, 0.2f, 1.0f);

            // Draw line to target
            Vector3 pos1(ag->npos[0], ag->npos[1], ag->npos[2]);
            Vector3 pos2;
            for (int i = 0; i < ag->ncorners; ++i)
            {
                pos2.x_ = ag->cornerVerts[i * 3];
                pos2.y_ = ag->cornerVerts[i * 3 + 1];
                pos2.z_ = ag->cornerVerts[i * 3 + 2];
                debug->AddLine(pos1, pos2, color, depthTest);
                pos1 = pos2;
            }
            pos2.x_ = ag->targetPos[0];
            pos2.y_ = ag->targetPos[1];
            pos2.z_ = ag->targetPos[2];
            debug->AddLine(pos1, pos2, color, depthTest);

            // Draw target circle
            debug->AddSphere(Sphere(pos2, 0.5f), color, depthTest);
        }
    }
}

void CrowdManager::DrawDebugGeometry(bool depthTest)
{
    Scene* scene = GetScene();
    if (scene)
    {
        DebugRenderer* debug = scene->GetComponent<DebugRenderer>();
        if (debug)
            DrawDebugGeometry(debug, depthTest);
    }
}

void CrowdManager::SetAreaCost(unsigned filterID, unsigned areaID, float cost)
{
    dtQueryFilter* filter = crowd_->getEditableFilter(filterID);
    if (filter)
        filter->setAreaCost((int)areaID, cost);
}

void CrowdManager::SetCrowdTarget(const Vector3& position, Node* node)
{
    if (!crowd_)
        return;

    PODVector<CrowdAgent*> agents = GetAgents(node, false);     // Get all crowd agent components
    Vector3 moveTarget(position);
    for (unsigned i = 0; i < agents.Size(); ++i)
    {
        CrowdAgent* agent = agents[i];
        // Give application a chance to determine the desired crowd formation when they reach the target position
        using namespace CrowdAgentFormation;

        VariantMap& map = GetEventDataMap();
        map[P_NODE] = agent->GetNode();
        map[P_CROWD_AGENT] = agent;
        map[P_INDEX] = i;
        map[P_SIZE] = agents.Size();
        map[P_POSITION] = moveTarget;   // Expect the event handler will modify this position accordingly

        SendEvent(E_CROWD_AGENT_FORMATION, map);

        moveTarget = map[P_POSITION].GetVector3();
        agent->SetTargetPosition(moveTarget);
    }
}

void CrowdManager::SetCrowdVelocity(const Vector3& velocity, Node* node)
{
    if (!crowd_)
        return;

    PODVector<CrowdAgent*> agents = GetAgents(node, true);      // Get only crowd agent components already in the crowd
    for (unsigned i = 0; i < agents.Size(); ++i)
        agents[i]->SetTargetVelocity(velocity);
}

void CrowdManager::ResetCrowdTarget(Node* node)
{
    if (!crowd_)
        return;

    PODVector<CrowdAgent*> agents = GetAgents(node, true);
    for (unsigned i = 0; i < agents.Size(); ++i)
        agents[i]->ResetTarget();
}

void CrowdManager::SetMaxAgents(unsigned maxAgents)
{
    if (maxAgents != maxAgents_ && maxAgents > 0)
    {
        maxAgents_ = maxAgents;
        CreateCrowd(true);
        MarkNetworkUpdate();
    }
}

void CrowdManager::SetMaxAgentRadius(float maxAgentRadius)
{
    if (maxAgentRadius != maxAgentRadius_ && maxAgentRadius > 0.f)
    {
        maxAgentRadius_ = maxAgentRadius;
        CreateCrowd(true);
        MarkNetworkUpdate();
    }
}

void CrowdManager::SetNavigationMesh(NavigationMesh* navMesh)
{
    if (navMesh != navigationMesh_ && navMesh)
    {
        navigationMesh_ = navMesh;
        CreateCrowd(true);
        MarkNetworkUpdate();
    }
}

float CrowdManager::GetAreaCost(unsigned filterID, unsigned areaID) const
{
    if (crowd_ && navigationMesh_)
    {
        const dtQueryFilter* filter = crowd_->getFilter((int)filterID);
        if (filter)
            return filter->getAreaCost((int)areaID);
    }
    return 0.0f;
}

PODVector<CrowdAgent*> CrowdManager::GetAgents(Node* node, bool inCrowdFilter) const
{
    if (!node)
        node = GetScene();
    PODVector<CrowdAgent*> agents;
    node->GetComponents<CrowdAgent>(agents, true);
    if (inCrowdFilter)
    {
        PODVector<CrowdAgent*>::Iterator i = agents.Begin();
        while (i != agents.End())
        {
            if ((*i)->IsInCrowd())
                ++i;
            else
                i = agents.Erase(i);
        }
    }
    return agents;
}

Vector3 CrowdManager::FindNearestPoint(const Vector3& point, int filterType, dtPolyRef* nearestRef)
{
    if (nearestRef)
        *nearestRef = 0;
    return crowd_ && navigationMesh_ ? navigationMesh_->FindNearestPoint(point, crowd_->getQueryExtents(), crowd_->getFilter(filterType), nearestRef) : point;
}

Vector3 CrowdManager::MoveAlongSurface(const Vector3& start, const Vector3& end, int filterType, int maxVisited)
{
    return crowd_ && navigationMesh_ ? navigationMesh_->MoveAlongSurface(start, end, crowd_->getQueryExtents(), maxVisited, crowd_->getFilter(filterType)) : end;
}

void CrowdManager::FindPath(PODVector<Vector3>& dest, const Vector3& start, const Vector3& end, int filterType)
{
    if (crowd_ && navigationMesh_)
        navigationMesh_->FindPath(dest, start, end, crowd_->getQueryExtents(), crowd_->getFilter(filterType));
}

Vector3 CrowdManager::GetRandomPoint(int filterType, dtPolyRef* randomRef)
{
    if (randomRef)
        *randomRef = 0;
    return crowd_ && navigationMesh_ ? navigationMesh_->GetRandomPoint(crowd_->getFilter(filterType), randomRef) : Vector3::ZERO;
}

Vector3 CrowdManager::GetRandomPointInCircle(const Vector3& center, float radius, int filterType, dtPolyRef* randomRef)
{
    if (randomRef)
        *randomRef = 0;
    return crowd_ && navigationMesh_ ? navigationMesh_->GetRandomPointInCircle(center, radius, crowd_->getQueryExtents(), crowd_->getFilter(filterType), randomRef) : center;
}

float CrowdManager::GetDistanceToWall(const Vector3& point, float radius, int filterType, Vector3* hitPos, Vector3* hitNormal)
{
    if (hitPos)
        *hitPos = Vector3::ZERO;
    if (hitNormal)
        *hitNormal = Vector3::DOWN;
    return crowd_ && navigationMesh_ ? navigationMesh_->GetDistanceToWall(point, radius, crowd_->getQueryExtents(), crowd_->getFilter(filterType), hitPos, hitNormal) : radius;
}

Vector3 CrowdManager::Raycast(const Vector3& start, const Vector3& end, int filterType, Vector3* hitNormal)
{
    if (hitNormal)
        *hitNormal = Vector3::DOWN;
    return crowd_ && navigationMesh_ ? navigationMesh_->Raycast(start, end, crowd_->getQueryExtents(), crowd_->getFilter(filterType), hitNormal) : end;
}

bool CrowdManager::CreateCrowd(bool readdCrowdAgents)
{
    if (!navigationMesh_ || !navigationMesh_->InitializeQuery())
        return false;

    if (crowd_)
        dtFreeCrowd(crowd_);
    crowd_ = dtAllocCrowd();

    // Initialize the crowd
    if (!crowd_->init(maxAgents_, maxAgentRadius_ > 0.f ? maxAgentRadius_ : navigationMesh_->GetAgentRadius(), navigationMesh_->navMesh_, CrowdAgentUpdateCallback))
    {
        LOGERROR("Could not initialize DetourCrowd");
        return false;
    }

    // Setup local avoidance params to different qualities.
    dtObstacleAvoidanceParams params;
    memcpy(&params, crowd_->getObstacleAvoidanceParams(0), sizeof(dtObstacleAvoidanceParams));

    // Low (11)
    params.velBias = 0.5f;
    params.adaptiveDivs = 5;
    params.adaptiveRings = 2;
    params.adaptiveDepth = 1;
    crowd_->setObstacleAvoidanceParams(0, &params);

    // Medium (22)
    params.velBias = 0.5f;
    params.adaptiveDivs = 5;
    params.adaptiveRings = 2;
    params.adaptiveDepth = 2;
    crowd_->setObstacleAvoidanceParams(1, &params);

    // Good (45)
    params.velBias = 0.5f;
    params.adaptiveDivs = 7;
    params.adaptiveRings = 2;
    params.adaptiveDepth = 3;
    crowd_->setObstacleAvoidanceParams(2, &params);

    // High (66)
    params.velBias = 0.5f;
    params.adaptiveDivs = 7;
    params.adaptiveRings = 3;
    params.adaptiveDepth = 3;
    crowd_->setObstacleAvoidanceParams(3, &params);

    if (readdCrowdAgents)
    {
        PODVector<CrowdAgent*> agents = GetAgents();
        for (unsigned i = 0; i < agents.Size(); ++i)
        {
            // Keep adding until the crowd cannot take it anymore
            if (agents[i]->AddAgentToCrowd(true) == -1)
            {
                LOGWARNINGF("CrowdManager: %d crowd agents orphaned", agents.Size() - i);
                break;
            }
        }
    }

    return true;
}

int CrowdManager::AddAgent(CrowdAgent* agent, const Vector3& pos)
{
    if (!crowd_ || !navigationMesh_ || !agent)
        return -1;
    dtCrowdAgentParams params;
    params.userData = agent;
    if (agent->radius_ == 0.f)
        agent->radius_ = navigationMesh_->GetAgentRadius();
    if (agent->height_ == 0.f)
        agent->height_ = navigationMesh_->GetAgentHeight();
    return crowd_->addAgent(pos.Data(), &params);
}

void CrowdManager::RemoveAgent(CrowdAgent* agent)
{
    if (!crowd_ || !agent)
        return;
    dtCrowdAgent* agt = crowd_->getEditableAgent(agent->GetAgentCrowdId());
    if (agt)
        agt->params.userData = 0;
    crowd_->removeAgent(agent->GetAgentCrowdId());
}

void CrowdManager::Update(float delta)
{
    if (!crowd_ || !navigationMesh_)
        return;
    PROFILE(UpdateCrowd);
    crowd_->update(delta, 0);
}

const dtCrowdAgent* CrowdManager::GetCrowdAgent(int agent)
{
    return crowd_ ? crowd_->getAgent(agent) : 0;
}

void CrowdManager::HandleSceneSubsystemUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace SceneSubsystemUpdate;

    if (IsEnabledEffective())
        Update(eventData[P_TIMESTEP].GetFloat());
}

void CrowdManager::HandleNavMeshFullRebuild(StringHash eventType, VariantMap& eventData)
{
    using namespace NavigationMeshRebuilt;

    // The mesh being rebuilt may not have existed before
    SetNavigationMesh(static_cast<NavigationMesh*>(eventData[P_MESH].GetPtr()));
}

void DetourCrowdManager::OnSceneSet(Scene* scene)
{
    // Subscribe to the scene subsystem update, which will trigger the crowd update step, and grab a reference
    // to the scene's NavigationMesh
    if (scene)
    {
        SubscribeToEvent(scene, E_SCENESUBSYSTEMUPDATE, HANDLER(CrowdManager, HandleSceneSubsystemUpdate));
        NavigationMesh* mesh = GetScene()->GetDerivedComponent<NavigationMesh>();
        if (mesh)
        {
            SubscribeToEvent(mesh, E_NAVIGATION_MESH_REBUILT, HANDLER(CrowdManager, HandleNavMeshFullRebuild));
            SetNavigationMesh(mesh);
        }
        else
            LOGERROR("CrowdManager requires an existing navigation mesh");
    }
    else
    {
        UnsubscribeFromEvent(E_SCENESUBSYSTEMUPDATE);
        UnsubscribeFromEvent(E_NAVIGATION_MESH_REBUILT);
        navigationMesh_.Reset();
    }
}

}
