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

#include "Precompiled.h"

#include "../Scene/Component.h"
#include "../Core/Context.h"
#include "../Navigation/CrowdAgent.h"
#include "../Graphics/DebugRenderer.h"
#include "../Navigation/DetourCrowdManager.h"
#include "../Navigation/DynamicNavigationMesh.h"
#include "../IO/Log.h"
#include "../Navigation/NavigationEvents.h"
#include "../Navigation/NavigationMesh.h"
#include "../Scene/Node.h"
#include "../Core/Profiler.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneEvents.h"
#include "../Container/Vector.h"

#ifdef URHO3D_PHYSICS
#include "../Physics/PhysicsEvents.h"
#endif

#include <DetourCrowd/DetourCrowd.h>
#include <Recast/Recast.h>

#include "../DebugNew.h"

namespace Urho3D
{
    
extern const char* NAVIGATION_CATEGORY;

static const unsigned DEFAULT_MAX_AGENTS = 512;

DetourCrowdManager::DetourCrowdManager(Context* context) :
    Component(context),
    maxAgents_(DEFAULT_MAX_AGENTS),
    crowd_(0),
    navigationMesh_(0),
    agentDebug_(NULL)
{
    agentBuffer_.Resize(maxAgents_);
}

DetourCrowdManager::~DetourCrowdManager()
{
    dtFreeCrowd(crowd_);
    if (agentDebug_)
        delete agentDebug_;
}

void DetourCrowdManager::RegisterObject(Context* context)
{
    context->RegisterFactory<DetourCrowdManager>(NAVIGATION_CATEGORY);
    
    ACCESSOR_ATTRIBUTE("Max Agents", GetMaxAgents, SetMaxAgents, unsigned, DEFAULT_MAX_AGENTS, AM_DEFAULT);
}

void DetourCrowdManager::SetNavigationMesh(NavigationMesh* navMesh)
{
    navigationMesh_ = WeakPtr<NavigationMesh>(navMesh);
    if (navigationMesh_ && navigationMesh_->navMeshQuery_ == 0)
        navigationMesh_->InitializeQuery();
    CreateCrowd();
    MarkNetworkUpdate();
}

void DetourCrowdManager::SetAreaTypeCost(unsigned filterID, unsigned areaType, float weight)
{
    dtQueryFilter* filter = crowd_->getEditableFilter(filterID);
    if (filter)
        filter->setAreaCost((int)areaType, weight);
}

void DetourCrowdManager::SetMaxAgents(unsigned agentCt)
{
    maxAgents_ = agentCt;
    if (crowd_ && crowd_->getAgentCount() > 0)
        LOGERROR("DetourCrowdManager contains active agents, their state will be lost");
    agentBuffer_.Resize(maxAgents_);
    CreateCrowd();
    if (crowd_)
    {
        PODVector<CrowdAgent*> agents = agents_;
        // Reset the existing values in the agent
        for (unsigned i = 0; i < agents.Size(); ++i)
        {
            agents[i]->inCrowd_ = false;
            agents[i]->agentCrowdId_ = -1;
        }
        // Add the agents back in
        for (unsigned i = 0; i < agents.Size() && i < maxAgents_; ++i)
            agents[i]->AddAgentToCrowd();
        if (agents.Size() > maxAgents_)
            LOGERROR("DetourCrowdManager: resize left " + String(agents.Size() - maxAgents_) + " agents orphaned");
    }
    MarkNetworkUpdate();
}

NavigationMesh* DetourCrowdManager::GetNavigationMesh()
{
    return navigationMesh_.Get();
}

float DetourCrowdManager::GetAreaTypeCost(unsigned filterID, unsigned areaType) const
{
    if (crowd_ && navigationMesh_)
    {
        const dtQueryFilter* filter = crowd_->getFilter((int)filterID);
        if (filter)
            return filter->getAreaCost((int)areaType);
    }
    return 0.0f;
}

unsigned DetourCrowdManager::GetAgentCount() const
{
    if (crowd_)
        return crowd_->getAgentCount();
    return 0;
}

void DetourCrowdManager::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (debug && navigationMesh_.NotNull() && crowd_)
    {
        // Current position-to-target line
        for (int i = 0; i < crowd_->getAgentCount(); i++)
        {
            const dtCrowdAgent* ag = crowd_->getAgent(i);
            if (!ag->active)
                continue;

            Color color(0.6f, 0.2f, 0.2f, 1.0f);

            // Render line to target:
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

            // Target circle
            debug->AddSphere(Sphere(pos2, 0.5f), color, depthTest);
        }
    }
}

bool DetourCrowdManager::CreateCrowd()
{
    if (!navigationMesh_) 
        return false;

    if (navigationMesh_->navMesh_ == 0)
        return false;

    if (crowd_)
    {
        dtFreeCrowd(crowd_);
        crowd_ = 0;
    }

    if (crowd_ == 0)
        crowd_ = dtAllocCrowd();
    if (agentDebug_ == NULL)
        agentDebug_ = new dtCrowdAgentDebugInfo();

    // Initialize the crowd
    bool b = crowd_->init(maxAgents_, navigationMesh_->GetAgentRadius(), navigationMesh_->navMesh_);
    if (b == false)
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

    return true;
}

int DetourCrowdManager::AddAgent(CrowdAgent* agent, const Vector3& pos)
{
    if (crowd_ == 0 || navigationMesh_.Expired())
        return -1;
    dtCrowdAgentParams params;
    if (agent->radius_ <= 0.0f)
        params.radius = agent->radius_ = navigationMesh_->GetAgentRadius();
    else
        params.radius = agent->radius_;
    if (agent->height_ <= 0.0f)
        params.height = agent->height_ = navigationMesh_->GetAgentHeight();
    else
        params.height = agent->height_;
    params.queryFilterType = (unsigned char)agent->filterType_;
    params.maxAcceleration = agent->maxAccel_;
    params.maxSpeed = agent->maxSpeed_;
    params.collisionQueryRange = params.radius * 8.0f;
    params.pathOptimizationRange = params.radius * 30.0f;
    params.updateFlags = DT_CROWD_ANTICIPATE_TURNS
        | DT_CROWD_OPTIMIZE_VIS
        | DT_CROWD_OPTIMIZE_TOPO
        | DT_CROWD_OBSTACLE_AVOIDANCE;
    params.obstacleAvoidanceType = 3;
    params.separationWeight = 2.0f;
    params.queryFilterType = 0;
    dtPolyRef polyRef;
    float nearestPos[3];
    rcVcopy(nearestPos, &pos.x_);
    dtStatus status = navigationMesh_->navMeshQuery_->findNearestPoly(
        pos.Data(),
        crowd_->getQueryExtents(),
        crowd_->getFilter(agent->filterType_),
        &polyRef,
        nearestPos);

    
    const int agentID = crowd_->addAgent(nearestPos, &params);
    if (agentID != -1)
        agents_.Push(agent);
    return agentID;
}

void DetourCrowdManager::RemoveAgent(CrowdAgent* agent)
{
    if (crowd_ == 0)
        return;
    // Clear user data
    dtCrowdAgent* agt = crowd_->getEditableAgent(agent->GetAgentCrowdId());
    if (agt)
        agt->params.userData = 0;
    crowd_->removeAgent(agent->GetAgentCrowdId());
    agents_.Remove(agent);
}

void DetourCrowdManager::UpdateAgentNavigationQuality(CrowdAgent* agent, NavigationQuality nq)
{
    if (crowd_ == 0)
        return;

    dtCrowdAgentParams params = crowd_->getAgent(agent->GetAgentCrowdId())->params;
    switch (nq)
    {
    case NAVIGATIONQUALITY_LOW:
        {
            params.updateFlags &= ~0
                & ~DT_CROWD_ANTICIPATE_TURNS
                & ~DT_CROWD_OPTIMIZE_VIS
                & ~DT_CROWD_OPTIMIZE_TOPO
                & ~DT_CROWD_OBSTACLE_AVOIDANCE;
        }
        break;

    case NAVIGATIONQUALITY_MEDIUM:
        {
            params.updateFlags |= 0;
            params.updateFlags &= ~0
                & ~DT_CROWD_OBSTACLE_AVOIDANCE
                & ~DT_CROWD_ANTICIPATE_TURNS
                & ~DT_CROWD_OPTIMIZE_VIS
                & ~DT_CROWD_OPTIMIZE_TOPO;
        }
        break;

    case NAVIGATIONQUALITY_HIGH:
        {
            params.obstacleAvoidanceType = 3;
            params.updateFlags |= 0
                | DT_CROWD_ANTICIPATE_TURNS
                | DT_CROWD_OPTIMIZE_VIS
                | DT_CROWD_OPTIMIZE_TOPO
                | DT_CROWD_OBSTACLE_AVOIDANCE;
        }
        break;
    }

    crowd_->updateAgentParameters(agent->GetAgentCrowdId(), &params);
}

void DetourCrowdManager::UpdateAgentPushiness(CrowdAgent* agent, NavigationPushiness pushiness)
{
    if (crowd_ == 0)
        return;

    dtCrowdAgentParams params = crowd_->getAgent(agent->GetAgentCrowdId())->params;
    switch (pushiness)
    {
    case PUSHINESS_LOW:
        params.separationWeight = 4.0f;
        params.collisionQueryRange = params.radius * 16.0f;
        break;

    case PUSHINESS_MEDIUM:
        params.separationWeight = 2.0f;
        params.collisionQueryRange = params.radius * 8.0f;
        break;

    case PUSHINESS_HIGH:
        params.separationWeight = 0.5f;
        params.collisionQueryRange = params.radius * 1.0f;
        break;
    }
    crowd_->updateAgentParameters(agent->GetAgentCrowdId(), &params);
}

bool DetourCrowdManager::SetAgentTarget(CrowdAgent* agent, Vector3 target)
{
    if (crowd_ == 0)
        return false;
    dtPolyRef polyRef;
    float nearestPos[3];
    dtStatus status = navigationMesh_->navMeshQuery_->findNearestPoly(
        target.Data(),
        crowd_->getQueryExtents(),
        crowd_->getFilter(agent->filterType_),
        &polyRef,
        nearestPos);

    if (!dtStatusFailed(status))
    {
        if (!crowd_->requestMoveTarget(agent->GetAgentCrowdId(), polyRef, nearestPos))
            return false;
    }
    else
        return false;
    return true;
}

bool DetourCrowdManager::SetAgentTarget(CrowdAgent* agent, Vector3 target, unsigned int& targetRef)
{
    if (crowd_ == 0)
        return false;
    float nearestPos[3];
    dtStatus status = navigationMesh_->navMeshQuery_->findNearestPoly(
        target.Data(),
        crowd_->getQueryExtents(),
        crowd_->getFilter(agent->filterType_),
        &targetRef,
        nearestPos);

    if (!dtStatusFailed(status))
    {
        if (!crowd_->requestMoveTarget(agent->GetAgentCrowdId(), targetRef, nearestPos))
            return false;
        // Return true if detour has determined it can do something with our move target
        return crowd_->getAgent(agent->GetAgentCrowdId())->targetState != DT_CROWDAGENT_TARGET_FAILED;
    }
    else
        return false;
    return true;
}

Vector3 DetourCrowdManager::GetClosestWalkablePosition(Vector3 pos)
{
    if (crowd_ == 0)
        return Vector3();
    float closest[3];
    const static float extents[] = { 1.0f, 20.0f, 1.0f };
    dtPolyRef closestPoly;
    dtQueryFilter filter;
    dtStatus status = navigationMesh_->navMeshQuery_->findNearestPoly(
        pos.Data(),
        crowd_->getQueryExtents(),
        &filter,
        &closestPoly,
        closest);
    return Vector3(closest);
}

void DetourCrowdManager::Update(float delta)
{
    if (crowd_ == 0)
        return;

    PROFILE(UpdateCrowd);
        
    crowd_->update(delta, agentDebug_);

    memset(&agentBuffer_[0], 0, maxAgents_ * sizeof(dtCrowdAgent*));
    const int count = crowd_->getActiveAgents(&agentBuffer_[0], maxAgents_);
    
    {
        PROFILE(ApplyCrowdUpdates);
        for (int i = 0; i < count; i++)
        {
            dtCrowdAgent* agent = agentBuffer_[i];
            if (agent)
            {
                CrowdAgent* crowdAgent = static_cast<CrowdAgent*>(agent->params.userData);	
                if (crowdAgent)
                    crowdAgent->OnCrowdAgentReposition(Vector3(agent->npos), Vector3(agent->vel));
            }
        }
    }
}

const dtCrowdAgent* DetourCrowdManager::GetCrowdAgent(int agent)
{
    if (crowd_ == 0)
        return NULL;
    return crowd_->getAgent(agent);
}

dtCrowd* DetourCrowdManager::GetCrowd()
{
    return crowd_;
}

void DetourCrowdManager::HandleFixedUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace PhysicsPreStep;

    if (IsEnabledEffective())
        Update(eventData[P_TIMESTEP].GetFloat());
}

void DetourCrowdManager::HandleNavMeshFullRebuild(StringHash eventType, VariantMap& eventData)
{
    using namespace NavigationMeshRebuilt;

    // The mesh being rebuilt may not have existed before
    NavigationMesh* navMesh = static_cast<NavigationMesh*>(eventData[P_MESH].GetPtr());
    if (!navigationMesh_ || crowd_ == 0)
    {
        SetNavigationMesh(navMesh);

        // Scan for existing agents that are potentially important
        PODVector<Node*> agents;
        GetScene()->GetChildrenWithComponent<CrowdAgent>(agents, true);
        for (unsigned i = 0; i < agents.Size(); ++i)
        {
            CrowdAgent* agent = agents[i]->GetComponent<CrowdAgent>();
            if (agent && agent->IsEnabledEffective())
                agent->AddAgentToCrowd();
        }
    }
}

void DetourCrowdManager::OnNodeSet(Node* node)
{
    // Subscribe to the scene subsystem update, which will trigger the crowd update step, and grab a reference
    // to the scene's NavigationMesh
    if (node)
    {
        // No physics, then no navigation? Correct or Not?
#ifdef URHO3D_PHYSICS
        SubscribeToEvent(E_PHYSICSPRESTEP, HANDLER(DetourCrowdManager, HandleFixedUpdate));
#endif
        SubscribeToEvent(node, E_NAVIGATION_MESH_REBUILT, HANDLER(DetourCrowdManager, HandleNavMeshFullRebuild));
            
        NavigationMesh* mesh = GetScene()->GetComponent<NavigationMesh>();
        if (!mesh)
            mesh = GetScene()->GetComponent<DynamicNavigationMesh>();
        if (mesh) {
            SetNavigationMesh(mesh);
        }
        else
            LOGERROR("DetourCrowdManager requires an existing navigation mesh");
    }
}

}