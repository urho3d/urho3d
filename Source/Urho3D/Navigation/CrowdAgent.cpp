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
#include "../Core/Profiler.h"
#include "../Graphics/DebugRenderer.h"
#include "../IO/Log.h"
#include "../IO/MemoryBuffer.h"
#include "../Navigation/NavigationEvents.h"
#include "../Navigation/NavigationMesh.h"
#include "../Navigation/CrowdAgent.h"
#include "../Scene/Node.h"
#include "../Scene/Scene.h"

#include <Detour/DetourCommon.h>
#include <DetourCrowd/DetourCrowd.h>

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* NAVIGATION_CATEGORY;

static const CrowdAgentRequestedTarget DEFAULT_AGENT_REQUEST_TARGET_TYPE = CA_REQUESTEDTARGET_NONE;
static const float DEFAULT_AGENT_MAX_SPEED = 0.f;
static const float DEFAULT_AGENT_MAX_ACCEL = 0.f;
static const unsigned DEFAULT_AGENT_QUERY_FILTER_TYPE = 0;
static const unsigned DEFAULT_AGENT_OBSTACLE_AVOIDANCE_TYPE = 0;
static const NavigationQuality DEFAULT_AGENT_AVOIDANCE_QUALITY = NAVIGATIONQUALITY_HIGH;
static const NavigationPushiness DEFAULT_AGENT_NAVIGATION_PUSHINESS = NAVIGATIONPUSHINESS_MEDIUM;

static const unsigned SCOPE_NAVIGATION_QUALITY_PARAMS = 1;
static const unsigned SCOPE_NAVIGATION_PUSHINESS_PARAMS = 2;
static const unsigned SCOPE_BASE_PARAMS = M_MAX_UNSIGNED & ~SCOPE_NAVIGATION_QUALITY_PARAMS & ~SCOPE_NAVIGATION_PUSHINESS_PARAMS;

static const char* crowdAgentRequestedTargetTypeNames[] = {
    "None",
    "Position",
    "Velocity",
    nullptr
};

static const char* crowdAgentAvoidanceQualityNames[] = {
    "Low",
    "Medium",
    "High",
    nullptr
};

static const char* crowdAgentPushinessNames[] = {
    "Low",
    "Medium",
    "High",
    "None",
    nullptr
};

CrowdAgent::CrowdAgent(Context* context) :
    Component(context),
    agentCrowdId_(-1),
    requestedTargetType_(DEFAULT_AGENT_REQUEST_TARGET_TYPE),
    updateNodePosition_(true),
    maxAccel_(DEFAULT_AGENT_MAX_ACCEL),
    maxSpeed_(DEFAULT_AGENT_MAX_SPEED),
    radius_(0.0f),
    height_(0.0f),
    queryFilterType_(DEFAULT_AGENT_QUERY_FILTER_TYPE),
    obstacleAvoidanceType_(DEFAULT_AGENT_OBSTACLE_AVOIDANCE_TYPE),
    navQuality_(DEFAULT_AGENT_AVOIDANCE_QUALITY),
    navPushiness_(DEFAULT_AGENT_NAVIGATION_PUSHINESS),
    previousTargetState_(CA_TARGET_NONE),
    previousAgentState_(CA_STATE_WALKING),
    ignoreTransformChanges_(false)
{
    SubscribeToEvent(E_NAVIGATION_TILE_ADDED, URHO3D_HANDLER(CrowdAgent, HandleNavigationTileAdded));
}

CrowdAgent::~CrowdAgent()
{
    RemoveAgentFromCrowd();
}

void CrowdAgent::RegisterObject(Context* context)
{
    context->RegisterFactory<CrowdAgent>(NAVIGATION_CATEGORY);

    URHO3D_ATTRIBUTE("Target Position", Vector3, targetPosition_, Vector3::ZERO, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Target Velocity", Vector3, targetVelocity_, Vector3::ZERO, AM_DEFAULT);
    URHO3D_ENUM_ATTRIBUTE("Requested Target Type", requestedTargetType_, crowdAgentRequestedTargetTypeNames,
        DEFAULT_AGENT_REQUEST_TARGET_TYPE, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Update Node Position", GetUpdateNodePosition, SetUpdateNodePosition, bool, true, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Max Accel", float, maxAccel_, DEFAULT_AGENT_MAX_ACCEL, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Max Speed", float, maxSpeed_, DEFAULT_AGENT_MAX_SPEED, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Radius", float, radius_, 0.0f, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Height", float, height_, 0.0f, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Query Filter Type", unsigned, queryFilterType_, DEFAULT_AGENT_QUERY_FILTER_TYPE, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Obstacle Avoidance Type", unsigned, obstacleAvoidanceType_, DEFAULT_AGENT_OBSTACLE_AVOIDANCE_TYPE, AM_DEFAULT);
    URHO3D_ENUM_ATTRIBUTE("Navigation Pushiness", navPushiness_, crowdAgentPushinessNames, DEFAULT_AGENT_NAVIGATION_PUSHINESS, AM_DEFAULT);
    URHO3D_ENUM_ATTRIBUTE("Navigation Quality", navQuality_, crowdAgentAvoidanceQualityNames, DEFAULT_AGENT_AVOIDANCE_QUALITY, AM_DEFAULT);
}

void CrowdAgent::ApplyAttributes()
{
    // Values from Editor, saved-file, or network must be checked before applying
    maxAccel_ = Max(0.f, maxAccel_);
    maxSpeed_ = Max(0.f, maxSpeed_);
    radius_ = Max(0.f, radius_);
    height_ = Max(0.f, height_);
    queryFilterType_ = Min(queryFilterType_, (unsigned)DT_CROWD_MAX_QUERY_FILTER_TYPE - 1);
    obstacleAvoidanceType_ = Min(obstacleAvoidanceType_, (unsigned)DT_CROWD_MAX_OBSTAVOIDANCE_PARAMS - 1);

    UpdateParameters();

    // Set or reset target after we have attributes applied to the agent's parameters.
    CrowdAgentRequestedTarget requestedTargetType = requestedTargetType_;
    if (CA_REQUESTEDTARGET_NONE != requestedTargetType_)
    {
        // Assign a dummy value such that the value check in the setter method passes
        requestedTargetType_ = CA_REQUESTEDTARGET_NONE;
        if (requestedTargetType == CA_REQUESTEDTARGET_POSITION)
            SetTargetPosition(targetPosition_);
        else
            SetTargetVelocity(targetVelocity_);
    }
    else
    {
        requestedTargetType_ = CA_REQUESTEDTARGET_POSITION;
        ResetTarget();
    }
}

void CrowdAgent::OnSetEnabled()
{
    bool enabled = IsEnabledEffective();

    if (enabled && !IsInCrowd())
        AddAgentToCrowd();
    else if (!enabled && IsInCrowd())
        RemoveAgentFromCrowd();
}

void CrowdAgent::DrawDebugGeometry(bool depthTest)
{
    Scene* scene = GetScene();
    if (scene)
    {
        auto* debug = scene->GetComponent<DebugRenderer>();
        if (debug)
            DrawDebugGeometry(debug, depthTest);
    }
}

void CrowdAgent::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (node_)
    {
        const Vector3 pos = GetPosition();
        const Vector3 vel = GetActualVelocity();
        const Vector3 desiredVel = GetDesiredVelocity();
        const Vector3 agentHeightVec(0, height_, 0);

        debug->AddLine(pos + 0.5f * agentHeightVec, pos + vel + 0.5f * agentHeightVec, Color::GREEN, depthTest);
        debug->AddLine(pos + 0.25f * agentHeightVec, pos + desiredVel + 0.25f * agentHeightVec, Color::RED, depthTest);
        debug->AddCylinder(pos, radius_, height_, HasArrived() ? Color::GREEN : Color::WHITE, depthTest);
    }
}

void CrowdAgent::UpdateParameters(unsigned scope)
{
    const dtCrowdAgent* agent = GetDetourCrowdAgent();
    if (agent)
    {
        dtCrowdAgentParams params = agent->params;

        if (scope & SCOPE_NAVIGATION_QUALITY_PARAMS)
        {
            switch (navQuality_)
            {
            case NAVIGATIONQUALITY_LOW:
                params.updateFlags = 0u
                                     | DT_CROWD_OPTIMIZE_VIS
                                     | DT_CROWD_ANTICIPATE_TURNS;
                break;

            case NAVIGATIONQUALITY_MEDIUM:
                params.updateFlags = 0u
                                     | DT_CROWD_OPTIMIZE_TOPO
                                     | DT_CROWD_OPTIMIZE_VIS
                                     | DT_CROWD_ANTICIPATE_TURNS
                                     | DT_CROWD_SEPARATION;
                break;

            case NAVIGATIONQUALITY_HIGH:
                params.updateFlags = 0u
                                     // Path finding
                                     | DT_CROWD_OPTIMIZE_TOPO
                                     | DT_CROWD_OPTIMIZE_VIS
                                     // Steering
                                     | DT_CROWD_ANTICIPATE_TURNS
                                     | DT_CROWD_SEPARATION
                                     // Velocity planning
                                     | DT_CROWD_OBSTACLE_AVOIDANCE;
                break;
            }
        }

        if (scope & SCOPE_NAVIGATION_PUSHINESS_PARAMS)
        {
            switch (navPushiness_)
            {
            case NAVIGATIONPUSHINESS_LOW:
                params.separationWeight = 4.0f;
                params.collisionQueryRange = radius_ * 16.0f;
                break;

            case NAVIGATIONPUSHINESS_MEDIUM:
                params.separationWeight = 2.0f;
                params.collisionQueryRange = radius_ * 8.0f;
                break;

            case NAVIGATIONPUSHINESS_HIGH:
                params.separationWeight = 0.5f;
                params.collisionQueryRange = radius_ * 1.0f;
                break;

            case NAVIGATIONPUSHINESS_NONE:
                params.separationWeight = 0.0f;
                params.collisionQueryRange = radius_ * 1.0f;
                break;
            }
        }

        if (scope & SCOPE_BASE_PARAMS)
        {
            params.radius = radius_;
            params.height = height_;
            params.maxAcceleration = maxAccel_;
            params.maxSpeed = maxSpeed_;
            params.pathOptimizationRange = radius_ * 30.0f;
            params.queryFilterType = (unsigned char)queryFilterType_;
            params.obstacleAvoidanceType = (unsigned char)obstacleAvoidanceType_;
        }

        crowdManager_->GetCrowd()->updateAgentParameters(agentCrowdId_, &params);
    }
}

int CrowdAgent::AddAgentToCrowd(bool force)
{
    if (!node_ || !crowdManager_ || !crowdManager_->crowd_)
        return -1;

    if (force || !IsInCrowd())
    {
        URHO3D_PROFILE(AddAgentToCrowd);

        agentCrowdId_ = crowdManager_->AddAgent(this, node_->GetWorldPosition());
        if (agentCrowdId_ == -1)
            return -1;

        ApplyAttributes();

        previousAgentState_ = GetAgentState();
        previousTargetState_ = GetTargetState();

        // Agent created, but initial state is invalid and needs to be addressed
        if (previousAgentState_ == CA_STATE_INVALID)
        {
            using namespace CrowdAgentFailure;

            VariantMap& map = GetEventDataMap();
            map[P_NODE] = GetNode();
            map[P_CROWD_AGENT] = this;
            map[P_CROWD_TARGET_STATE] = previousTargetState_;
            map[P_CROWD_AGENT_STATE] = previousAgentState_;
            map[P_POSITION] = GetPosition();
            map[P_VELOCITY] = GetActualVelocity();
            crowdManager_->SendEvent(E_CROWD_AGENT_FAILURE, map);
            Node* node = GetNode();
            if (node)
                node->SendEvent(E_CROWD_AGENT_NODE_FAILURE, map);

            // Reevaluate states as handling of event may have resulted in changes
            previousAgentState_ = GetAgentState();
            previousTargetState_ = GetTargetState();
        }

        // Save the initial position to prevent CrowdAgentReposition event being triggered unnecessarily
        previousPosition_ = GetPosition();
    }

    return agentCrowdId_;
}

void CrowdAgent::RemoveAgentFromCrowd()
{
    if (IsInCrowd())
    {
        crowdManager_->RemoveAgent(this);
        agentCrowdId_ = -1;
    }
}

void CrowdAgent::SetTargetPosition(const Vector3& position)
{
    if (position != targetPosition_ || CA_REQUESTEDTARGET_POSITION != requestedTargetType_)
    {
        targetPosition_ = position;
        requestedTargetType_ = CA_REQUESTEDTARGET_POSITION;
        MarkNetworkUpdate();

        if (!IsInCrowd())
            AddAgentToCrowd();
        if (IsInCrowd())   // Make sure the previous method call is successful
        {
            dtPolyRef nearestRef;
            Vector3 nearestPos = crowdManager_->FindNearestPoint(position, queryFilterType_, &nearestRef);
            crowdManager_->GetCrowd()->requestMoveTarget(agentCrowdId_, nearestRef, nearestPos.Data());
        }
    }
}

void CrowdAgent::SetTargetVelocity(const Vector3& velocity)
{
    if (velocity != targetVelocity_ || CA_REQUESTEDTARGET_VELOCITY != requestedTargetType_)
    {
        targetVelocity_ = velocity;
        requestedTargetType_ = CA_REQUESTEDTARGET_VELOCITY;
        MarkNetworkUpdate();

        if (IsInCrowd())
            crowdManager_->GetCrowd()->requestMoveVelocity(agentCrowdId_, velocity.Data());
    }
}

void CrowdAgent::ResetTarget()
{
    if (CA_REQUESTEDTARGET_NONE != requestedTargetType_)
    {
        requestedTargetType_ = CA_REQUESTEDTARGET_NONE;
        MarkNetworkUpdate();

        if (IsInCrowd())
            crowdManager_->GetCrowd()->resetMoveTarget(agentCrowdId_);
    }
}

void CrowdAgent::SetUpdateNodePosition(bool unodepos)
{
    if (unodepos != updateNodePosition_)
    {
        updateNodePosition_ = unodepos;
        MarkNetworkUpdate();
    }
}

void CrowdAgent::SetMaxAccel(float maxAccel)
{
    if (maxAccel != maxAccel_ && maxAccel >= 0.f)
    {
        maxAccel_ = maxAccel;
        UpdateParameters(SCOPE_BASE_PARAMS);
        MarkNetworkUpdate();
    }
}

void CrowdAgent::SetMaxSpeed(float maxSpeed)
{
    if (maxSpeed != maxSpeed_ && maxSpeed >= 0.f)
    {
        maxSpeed_ = maxSpeed;
        UpdateParameters(SCOPE_BASE_PARAMS);
        MarkNetworkUpdate();
    }
}

void CrowdAgent::SetRadius(float radius)
{
    if (radius != radius_ && radius > 0.f)
    {
        radius_ = radius;
        UpdateParameters(SCOPE_BASE_PARAMS | SCOPE_NAVIGATION_PUSHINESS_PARAMS);
        MarkNetworkUpdate();
    }
}

void CrowdAgent::SetHeight(float height)
{
    if (height != height_ && height > 0.f)
    {
        height_ = height;
        UpdateParameters(SCOPE_BASE_PARAMS);
        MarkNetworkUpdate();
    }
}

void CrowdAgent::SetQueryFilterType(unsigned queryFilterType)
{
    if (queryFilterType != queryFilterType_)
    {
        if (queryFilterType >= DT_CROWD_MAX_QUERY_FILTER_TYPE)
        {
            URHO3D_LOGERRORF("The specified filter type index (%d) exceeds the maximum allowed value (%d)", queryFilterType,
                DT_CROWD_MAX_QUERY_FILTER_TYPE);
            return;
        }

        queryFilterType_ = queryFilterType;
        UpdateParameters(SCOPE_BASE_PARAMS);
        MarkNetworkUpdate();
    }
}

void CrowdAgent::SetObstacleAvoidanceType(unsigned obstacleAvoidanceType)
{
    if (obstacleAvoidanceType != obstacleAvoidanceType_)
    {
        if (obstacleAvoidanceType >= DT_CROWD_MAX_OBSTAVOIDANCE_PARAMS)
        {
            URHO3D_LOGERRORF("The specified obstacle avoidance type index (%d) exceeds the maximum allowed value (%d)",
                obstacleAvoidanceType, DT_CROWD_MAX_OBSTAVOIDANCE_PARAMS);
            return;
        }

        obstacleAvoidanceType_ = obstacleAvoidanceType;
        UpdateParameters(SCOPE_BASE_PARAMS);
        MarkNetworkUpdate();
    }
}

void CrowdAgent::SetNavigationQuality(NavigationQuality val)
{
    if (val != navQuality_)
    {
        navQuality_ = val;
        UpdateParameters(SCOPE_NAVIGATION_QUALITY_PARAMS);
        MarkNetworkUpdate();
    }
}

void CrowdAgent::SetNavigationPushiness(NavigationPushiness val)
{
    if (val != navPushiness_)
    {
        navPushiness_ = val;
        UpdateParameters(SCOPE_NAVIGATION_PUSHINESS_PARAMS);
        MarkNetworkUpdate();
    }
}

Vector3 CrowdAgent::GetPosition() const
{
    const dtCrowdAgent* agent = GetDetourCrowdAgent();
    return agent ? Vector3(agent->npos) : node_->GetWorldPosition();
}

Vector3 CrowdAgent::GetDesiredVelocity() const
{
    const dtCrowdAgent* agent = GetDetourCrowdAgent();
    return agent ? Vector3(agent->dvel) : Vector3::ZERO;
}

Vector3 CrowdAgent::GetActualVelocity() const
{
    const dtCrowdAgent* agent = GetDetourCrowdAgent();
    return agent ? Vector3(agent->vel) : Vector3::ZERO;
}

CrowdAgentState CrowdAgent::GetAgentState() const
{
    const dtCrowdAgent* agent = GetDetourCrowdAgent();
    return agent ? (CrowdAgentState)agent->state : CA_STATE_INVALID;
}

CrowdAgentTargetState CrowdAgent::GetTargetState() const
{
    const dtCrowdAgent* agent = GetDetourCrowdAgent();
    return agent ? (CrowdAgentTargetState)agent->targetState : CA_TARGET_NONE;
}

bool CrowdAgent::HasArrived() const
{
    // Is the agent at or near the end of its path and within its own radius of the goal?
    const dtCrowdAgent* agent = GetDetourCrowdAgent();
    return agent && (!agent->ncorners || (agent->cornerFlags[agent->ncorners - 1] & DT_STRAIGHTPATH_END &&
                                          dtVdist2D(agent->npos, &agent->cornerVerts[(agent->ncorners - 1) * 3]) <=
                                          agent->params.radius));
}

bool CrowdAgent::IsInCrowd() const
{
    return crowdManager_ && agentCrowdId_ != -1;
}

void CrowdAgent::OnCrowdUpdate(dtCrowdAgent* ag, float dt)
{
    assert (ag);
    if (node_)
    {
        // Use pointer to self to check for destruction after sending events
        WeakPtr<CrowdAgent> self(this);

        Vector3 newPos(ag->npos);
        Vector3 newVel(ag->vel);

        // Notify parent node of the reposition
        if (newPos != previousPosition_)
        {
            previousPosition_ = newPos;

            if (updateNodePosition_)
            {
                ignoreTransformChanges_ = true;
                node_->SetWorldPosition(newPos);
                ignoreTransformChanges_ = false;
            }

            using namespace CrowdAgentReposition;

            VariantMap& map = GetEventDataMap();
            map[P_NODE] = node_;
            map[P_CROWD_AGENT] = this;
            map[P_POSITION] = newPos;
            map[P_VELOCITY] = newVel;
            map[P_ARRIVED] = HasArrived();
            map[P_TIMESTEP] = dt;
            crowdManager_->SendEvent(E_CROWD_AGENT_REPOSITION, map);
            if (self.Expired())
                return;
            node_->SendEvent(E_CROWD_AGENT_NODE_REPOSITION, map);
            if (self.Expired())
                return;
        }

        // Send a notification event if we've reached the destination
        CrowdAgentTargetState newTargetState = GetTargetState();
        CrowdAgentState newAgentState = GetAgentState();
        if (newAgentState != previousAgentState_ || newTargetState != previousTargetState_)
        {
            using namespace CrowdAgentStateChanged;

            VariantMap& map = GetEventDataMap();
            map[P_NODE] = node_;
            map[P_CROWD_AGENT] = this;
            map[P_CROWD_TARGET_STATE] = newTargetState;
            map[P_CROWD_AGENT_STATE] = newAgentState;
            map[P_POSITION] = newPos;
            map[P_VELOCITY] = newVel;
            crowdManager_->SendEvent(E_CROWD_AGENT_STATE_CHANGED, map);
            if (self.Expired())
                return;
            node_->SendEvent(E_CROWD_AGENT_NODE_STATE_CHANGED, map);
            if (self.Expired())
                return;

            // Send a failure event if either state is a failed status
            if (newAgentState == CA_STATE_INVALID || newTargetState == CA_TARGET_FAILED)
            {
                VariantMap& map = GetEventDataMap();
                map[P_NODE] = node_;
                map[P_CROWD_AGENT] = this;
                map[P_CROWD_TARGET_STATE] = newTargetState;
                map[P_CROWD_AGENT_STATE] = newAgentState;
                map[P_POSITION] = newPos;
                map[P_VELOCITY] = newVel;
                crowdManager_->SendEvent(E_CROWD_AGENT_FAILURE, map);
                if (self.Expired())
                    return;
                node_->SendEvent(E_CROWD_AGENT_NODE_FAILURE, map);
                if (self.Expired())
                    return;
            }

            // State may have been altered during the handling of the event
            previousAgentState_ = GetAgentState();
            previousTargetState_ = GetTargetState();
        }
    }
}

void CrowdAgent::OnNodeSet(Node* node)
{
    if (node)
        node->AddListener(this);
}

void CrowdAgent::OnSceneSet(Scene* scene)
{
    if (scene)
    {
        if (scene == node_)
            URHO3D_LOGERROR(GetTypeName() + " should not be created to the root scene node");
        crowdManager_ = scene->GetOrCreateComponent<CrowdManager>();
        AddAgentToCrowd();
    }
    else
        RemoveAgentFromCrowd();
}

void CrowdAgent::OnMarkedDirty(Node* node)
{
    if (!ignoreTransformChanges_ && IsEnabledEffective())
    {
        auto* agent = const_cast<dtCrowdAgent*>(GetDetourCrowdAgent());
        if (agent)
        {
            auto& agentPos = reinterpret_cast<Vector3&>(agent->npos);
            Vector3 nodePos = node->GetWorldPosition();

            // Only reset position / state if actually changed
            if (nodePos != agentPos)
            {
                agentPos = nodePos;

                // If the node has been externally altered, provide the opportunity for DetourCrowd to reevaluate the crowd agent
                if (agent->state == CA_STATE_INVALID)
                    agent->state = CA_STATE_WALKING;
            }
        }
    }
}

const dtCrowdAgent* CrowdAgent::GetDetourCrowdAgent() const
{
    return IsInCrowd() ? crowdManager_->GetDetourCrowdAgent(agentCrowdId_) : nullptr;
}

void CrowdAgent::HandleNavigationTileAdded(StringHash eventType, VariantMap& eventData)
{
    if (!crowdManager_)
        return;

    auto* mesh = static_cast<NavigationMesh*>(eventData[NavigationTileAdded::P_MESH].GetPtr());
    if (crowdManager_->GetNavigationMesh() != mesh)
        return;

    const IntVector2 tile = eventData[NavigationTileRemoved::P_TILE].GetIntVector2();
    const IntVector2 agentTile = mesh->GetTileIndex(node_->GetWorldPosition());
    const BoundingBox boundingBox = mesh->GetTileBoundingBox(agentTile);
    if (tile == agentTile && IsInCrowd())
    {
        RemoveAgentFromCrowd();
        AddAgentToCrowd();
    }
}

}
